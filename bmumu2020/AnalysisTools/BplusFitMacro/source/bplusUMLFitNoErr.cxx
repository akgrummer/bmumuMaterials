//
// Macro performing extended unbinned maximum likelihood fit of B+/- data w/o taking MassErr into account
//
// The code has been used to produce plot on page 7 here (08.12.2017):
// https://indico.cern.ch/event/649804/contributions/2776826/attachments/1572182/2480944/BLS_PhysicsWSjamboree.pdf
//
// Author: Iskander Ibragimov
// 
//
// Following parameters are HARDCODED :
// 1. Data flat ntuple file names
// 2. Fit Mass Region and its binning
// 3. Definition of signal and sideband regions
// 4. TMVA loose cut (qCut) as the one used in Run1 analysis
//
// EXECUTE:
// root -l bplusUMLFit.C
//
// output: bplus mass plot with fit parameters on it, saved as UMLfitBp.eps
//
//
//
//
#include <TCanvas.h>
#include <TChain.h>
#include "TFile.h"
#include "TLegend.h"
#include "TAxis.h"
#include "TLatex.h"
#include "TStyle.h"
#include "TLine.h"

#include <RooRealVar.h>
#include <RooDataSet.h>
#include <RooProduct.h>
#include <RooGaussian.h>
#include <RooExponential.h>
#include <RooProdPdf.h>
#include <RooAddPdf.h>
#include <RooExtendPdf.h>
#include <RooPlot.h>
#include <RooFitResult.h>
#include <RooGenericPdf.h>
#include <RooGaussModel.h>
#include <RooHist.h>

#include "bplusUMLFitNoErr.h"

using namespace std;
using namespace RooFit;

void bplusUMLFitNoErr()
{
    const Double_t qCut = 0.24; // loose BDT cut to suppress combinatorial background
    bool  verbose       = true;
    bool  dofit         = true;

    float plot_lower = 4930;
    float plot_upper = 5630;
    int   nbins      = (plot_upper - plot_lower) / 5;

    // ===================================================================================================
    // ============ GETTING INPUTS ======================
    // ===================================================================================================

    TString ntuples="/nfs/monet_3/home/campoverde/Data/Data15_Skimmed/output_1117974.root";

    TChain tChainData("T_mv");
    tChainData.Add(ntuples.Data()); //skimmed 2015/16 ntuples in rel. 20.7 w/ BDT_bb_2012 variable

    // input variable: BDT classifier
    RooRealVar BDTclas("BDT_bb_2012","BDT class", qCut, 100.0,"flag");

    // input variable: B vertex mass
    RooRealVar M("B_VTX_mass","Mass",plot_lower,plot_upper,"MeV");
    M.setRange("Full_Range" ,plot_lower,plot_upper);
    M.setRange("Band_Left"  ,plot_lower,5130);
    M.setRange("Band_Center",5180,5380);
    M.setRange("Band_Right" ,5430,plot_upper);
    // ===================================================================================================
    // ============ DEFINING DATASETS ======================
    // ===================================================================================================
    std::cout << "Nentries " << tChainData.GetEntries() << std::endl;
    RooDataSet DataToFit("DataToFit", "DataToFit", &tChainData, RooArgSet(M));

    if (verbose) 
    {
	cout << endl;
	cout << "Number of enries to fit : "<< DataToFit.sumEntries() << endl;
	cout << endl;
    }

    // ===================================================================================================
    // ============ DEFINING FIT MODEL ======================
    // ===================================================================================================

    //======== Gaussian signal model (Fsignal)
    RooRealVar    MassMean("m","Mass mean",5280,5270,5290,"MeV");
    RooRealVar    nsig("N_{sig}","Signal events",8.5e5,100.0,10000000.0);
    RooRealVar    sigma1("sigma1","Sigma1",22,1,100);
    RooRealVar    sigma2("sigma2","Sigma2",46,30,200);
    RooGaussian	  SignalGaussian1("SignalGaussian1","Signal Gaussian1", M, MassMean, sigma1);
    RooGaussian   SignalGaussian2("SignalGaussian2","Signal Gaussian2", M, MassMean, sigma2);
    RooRealVar    sigGauss1frac("SigGauss1frac","fraction of component 1 in signal",0.35,0.,1.);
    RooAddPdf     SignalDoubleGaussian("SignalDoubleGaussian","Signal", RooArgList(SignalGaussian1, SignalGaussian2), sigGauss1frac);
    RooExtendPdf  Fsignal("Fsignal","(Nsig / (Nsig + Nbkg)) * PDFsig", SignalDoubleGaussian, nsig);

    //======= Exponential background model (ExtBkgExp)
    RooRealVar     Lambda("Lambda","Lambda",-2.95e-03,-1.0,1.0);
    RooExponential BkgExp("BkgExp","Background exponential",M,Lambda);
    RooRealVar     NbgExp("NbgExp","Background exponential events",5.0e5,0.0,10000000.0);
    RooExtendPdf   ExtBkgExp("ExtBkgExp","(NbgExp / Ntot) * PDFbg1", BkgExp, NbgExp);

    //======= Error function background model (ExtBkgErfc)
    RooRealVar     erfMean("erfMean", "erfMean", 5146.0, 5100, 5200);
    RooRealVar     erfSigma("erfSigma", "erfSigma", 42.0, 0.0, 400.0);
    RooRealVar     NbgErfc("NbgErfc", "Background Erfc events", 1.7e5, 0.0, 10000000.0);
    RooFormulaVar  sCurve("sCurve", "TMath::Erfc((@0-@1)/@2)", RooArgList(M,erfMean,erfSigma));
    RooGenericPdf  BkgErf("BkgErf", "@0", sCurve);
    RooExtendPdf   ExtBkgErfc("ExtBkgErfc", "(NbgExp / Ntot) * PDFbg1", BkgErf, NbgErfc);

    //======= Gaussian background model (ExtBkgGaus)
    RooRealVar     meanBkgGaus("meanBkgGaus", "meanBkgGaus", 5360.0);
    RooRealVar     sigmaBkgGaus("sigmaBkgGaus", "sigmaBkgGaus", 60.0);
    RooRealVar     NbgGaussian("NbgGaussian", "Background Gaussian events", 5.4e4, 0.0, 10000000.0);
    RooGaussian    BkgGaus("BkgGaus","Background gaussian", M, meanBkgGaus, sigmaBkgGaus);
    RooExtendPdf   ExtBkgGaus("ExtBkgGaus","(NbgExp / Ntot) * PDFbg1", BkgGaus, NbgGaussian);

    //======= Combined model
    RooAddPdf   Model("Model", "Signal + Background", RooArgList(Fsignal, ExtBkgExp, ExtBkgErfc, ExtBkgGaus));  
    if (verbose) Model.Print("t");
    // ===================================================================================================
    // Do fit
    // ===================================================================================================
    RooFitResult* FitResults(NULL);
    //if (dofit) FitResults = Model.fitTo(DataToFit, Save());
    // ===================================================================================================
    // Draw canvas with inset plot on the bottom
    // ===================================================================================================
    TCanvas can("can","can",900,600);
    can.cd();
    can.SetLeftMargin(0.15);

    TPad up("mypad1", "mypad1", 0.0, 0.30, 1.0, 1.00);
    up.SetMargin(0.12,0.05,0.028,0.09);
    up.SetBorderMode(0);
    up.Draw();

    TPad down("mypad2", "mypad2", 0.0, 0.00, 1.0, 0.30);
    down.SetMargin(0.12,0.05,0.38,0.00001);
    down.SetBorderMode(0);
    down.Draw();
    // ===================================================================================================
    // Create legend
    // ===================================================================================================
    TLegend leg(0.75,0.55,0.90,0.90,NULL,"brNDC");
    leg.SetBorderSize(0); //no shadow

    // Plotting results
    // ===================================================================================================
    RooPlot* fitPlotFrame = M.frame(nbins);
    DataToFit.plotOn(fitPlotFrame, RooFit::Name("data"), XErrorSize(0));
    leg.AddEntry(fitPlotFrame->findObject("data"),"Data 15/6","p");

    Model.plotOn(fitPlotFrame, ProjWData(M, DataToFit), RooFit::Name("total"), LineColor(kRed));			// Plot signal + background
    leg.AddEntry(fitPlotFrame->findObject("total"),"Total fit","l");

    RooHist* pull = fitPlotFrame->pullHist();
    pull->SetFillColor(kBlue);
    pull->SetLineWidth(0);

    Model.plotOn(fitPlotFrame, Components(ExtBkgExp), RooFit::Name("expbkg"), LineColor(kGreen), LineStyle(kDashed));	// Plot exp background over it
    leg.AddEntry(fitPlotFrame->findObject("expbkg"),"Comb. bkg.","l");

    Model.plotOn(fitPlotFrame, Components(ExtBkgErfc), RooFit::Name("prdbkg"), LineColor(kBlue), LineStyle(kDashed));        // Plot erfc background over it
    leg.AddEntry(fitPlotFrame->findObject("prdbkg"),"PRD","l");

    Model.plotOn(fitPlotFrame, Components(ExtBkgGaus), RooFit::Name("misidbkg"), LineColor(kMagenta), LineStyle(kDashed));      // Plot misID background over it
    leg.AddEntry(fitPlotFrame->findObject("misidbkg"),"B^{#pm}#rightarrow J/#psi #pi^{#pm}","l");

    Model.plotOn(fitPlotFrame, Components(Fsignal), RooFit::Name("sig"), LineColor(kBlack), LineStyle(kDotted));          //Plot signal over it
    leg.AddEntry(fitPlotFrame->findObject("sig"),"B^{#pm}#rightarrow J/#psi K^{#pm}","l");
    // =================================================================================================== 
    // =========== Get signal events with error in band center range
    // =================================================================================================== 

    double fitNsig = nsig.getVal();       // Get nsig from fit
    RooAbsReal* nsigSubRange = Fsignal.createIntegral(RooArgSet(M), NormSet(RooArgSet(M)), Range("Band_Center"));
    if (verbose) cout << "nsig: "<< fitNsig << " frac of pdf: "<< nsigSubRange->getVal() << endl;

    fitNsig *= nsigSubRange->getVal();

    if (verbose && dofit) 
    {
	// Print fit parameters
	Model.getVariables()->Print("v");
	std::cout<<"Covariance Matrix:"<<std::endl;
	if (FitResults) FitResults->covarianceMatrix().Print();
    }

    double m1Sigma_sig(0), p1Sigma_sig(0);
    if (FitResults) 
    {
	m1Sigma_sig = nsigSubRange->getPropagatedError(*FitResults);
	m1Sigma_sig*= nsig.getVal();
	p1Sigma_sig = m1Sigma_sig;
	if (verbose) 
	{
	    cout << m1Sigma_sig << " <-err|nsig-> "<< nsig.getVal() <<endl;
	    std::cout<<"Nsig in 'Band_Center': "<<fitNsig <<" +"<<p1Sigma_sig<<" / -"<<m1Sigma_sig<<std::endl;
	}
    }

    TLatex tex(0.14,0.85,"#font[72]{ATLAS }Internal #font[42]{#sqrt{s}= 13 TeV}");
    tex.SetNDC();
    tex.SetTextAlign(13);
    tex.SetTextFont(42);
    tex.SetTextSize(0.06);
    tex.SetLineWidth(2);
    tex.Draw();

    fitPlotFrame->addObject(&tex);
    // ===================================================================================================
    // drawing plot
    // ===================================================================================================
    up.cd();

    fitPlotFrame->GetYaxis()->SetLabelSize(0.06); //millions overlay with label
    fitPlotFrame->GetXaxis()->SetNoExponent();
    fitPlotFrame->GetXaxis()->SetLabelOffset(0.028);
    fitPlotFrame->GetYaxis()->SetTitleSize(0.08);
    fitPlotFrame->GetYaxis()->SetTitleOffset(0.52);
    fitPlotFrame->GetXaxis()->SetTitle("m_{J/#psi K^{#pm}} [MeV]");
    fitPlotFrame->GetYaxis()->SetTitle(Form("Events / %2.1f MeV", (plot_upper-plot_lower)/(1.0*nbins)) );

    fitPlotFrame->Draw();
    leg.Draw();

    down.cd();
    gStyle->SetOptStat(0);

    RooPlot* resPlotFrame = M.frame(nbins);
    resPlotFrame->addPlotable(pull, "B");
    resPlotFrame->SetMaximum(10.0);  //3.5 
    resPlotFrame->SetMinimum(-10.0); //-3.5

    resPlotFrame->GetXaxis()->SetTitleSize(0.17);
    resPlotFrame->GetXaxis()->SetLabelSize(0.17);
    resPlotFrame->GetXaxis()->SetNoExponent();


    resPlotFrame->GetYaxis()->SetTitle("(data-fit)/#sigma");
    resPlotFrame->GetXaxis()->SetTitle("m_{J/#psi K^{#pm}} [MeV]");
    resPlotFrame->GetYaxis()->SetLabelSize(0.12);
    resPlotFrame->GetYaxis()->SetNdivisions(5,5,0);
    resPlotFrame->GetYaxis()->SetTitleSize(0.17);
    resPlotFrame->GetYaxis()->SetTitleOffset(0.21);
    resPlotFrame->Draw();

    // ===================================================================================================
    // add base line
    // ===================================================================================================

    TLine line(plot_lower, 0, plot_upper, 0);
    line.SetLineColor(kBlue);
    line.SetLineStyle(2);
    line.Draw("SAME");

    can.SaveAs("UMLfitBp.eps");

    if (FitResults)	delete	FitResults;
}

