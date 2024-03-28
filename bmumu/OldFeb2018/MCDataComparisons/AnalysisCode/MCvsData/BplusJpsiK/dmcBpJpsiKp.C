// Macro for performing data/MC comparison on B+->Jpsi/K+ channel
// uses unbinned ML fit to estimate number of bkg candidates 
// under the signal peak, as well as for estimation of fraction of
// continuos bkg candidates in the left sideband etc. (N.B. in "dtbgsub_mcrew" mode)
//
// Author: Iskander Ibragimov
// 19.09.2017
//
// in the file dmcBpJpsiKp.h are defined:
// - input data files for MC and data (single flat ntuples are curently supported)
// - output path for the plots and other output files 
// - cuts values and some special histogram binnings 
// - discriminating variables (name, binning, axislabel)
// 
// 
// 1 . if needed change source files for MC and data in *.h file (defined by the variables fdname and fmname)
// (in principle the code should also work with group ntuples on eos
// but those are not completely flat and missing preliminary and trigger selections
//
// 2. adjust CutAdd variable (in dmcBpJpsiKp.h) if needed (additional cuts to be applied)
//
// 3. adjust output path for the plots, etc.
//
// 4. to exectute do (after "root -l"):
// .x dmcBpJpsiKp.C("B_pT","dtbgsub_mcrew") //or any other variable name from dmcBpJpsiKp.h file
// OR
// .x dmcBpJpsiKp.C("systVars","dtbgsub_mcrew") // to run on all variables used for discrimination
// OR (faster, but on some OS stops after the first step - t.b.i)
// .L dmcBpJpsiKp.C++
// dmcBpJpsiKp("systVars","dtbgsub_mcrew")
// (N.B. in "dt_mc" mode histograms are compared "as is" i.e. w/o bkg subtraction)
//
//
// TBC: 
// B+ fit is made on all events, data/MC comparison is made on even-numbered events only
// uses only half of the B+ yield
//

#include "dmcBpJpsiKp.h"
using namespace std;


ofstream ofiletex(tabname);
TFile *fout = new TFile(ofilename,"RECREATE");

//store bkg fit data
bkg nbkgInfo;

//==========Forward declaration of functions===========

void getNbkgBpJpsiKp(TTree*);
void compare(VariableInfo, TString, TTree*, TTree*, TString, TString, bool, bool drawResiduals=true);
TH1F* getHistoFromTree(TTree*, VariableInfo, const char*, TCut);
//
// 2nd version used to get histogram for mass fit
//
TH1F* getHistoFromTree(TTree* tree, const char* var, const char* hname, TCut cut, Int_t NBins, Float_t XMin, Float_t XMax);
Double_t FuncTotWithExp(Double_t*, Double_t*);
Double_t FuncTotWithLin(Double_t*, Double_t*);
Double_t FuncBpS(Double_t*, Double_t*);
Double_t FuncBpS2(Double_t*, Double_t*);
Double_t FuncBkgTotWithExp(Double_t*, Double_t*);
Double_t FuncBkgTotWithLin(Double_t*, Double_t*);
Double_t FuncBkgLin(Double_t*, Double_t*);
TH1F* subtractMix(VariableInfo Variable, TTree* td, TString cw = "1==1",bool onlyRSB=false);

TLegend* defineLegendBox(TString what, Bool_t drawinlet);
TString getYAxisTitle(TString);

//=====================================================
Double_t lin_fn(Double_t* x,Double_t* par){
  return par[0]+par[1]*x[0];
};
Double_t exp_fn(Double_t* x,Double_t* par){
  return par[0]*TMath::Exp(par[1]*(x[0]-4930.0));
};
Double_t err_fn(Double_t* x,Double_t* par){
  return par[0]*TMath::Erfc((x[0]-par[1])/par[2]);//+par[3]*(1+par[4]*x[0]);// par[3]*TMath::Exp(par[4]*(x[0]-4930.0));
};
Double_t single_gaus(Double_t *x, Double_t *par){
  return par[0]*TMath::Gaus(x[0],par[1],par[2]);
};
Double_t double_gaus(Double_t* x, Double_t* par){
  return par[0]*TMath::Gaus(x[0],par[2],par[3])+(par[1])*TMath::Gaus(x[0],par[2],par[4]);
};
void dmcBpJpsiKp(TString compVar="", TString compMode="", TString dtlabel="MC B^{+}#rightarrow J/#psi K^{+}", TString mclabel="MC B_{s}#rightarrow #mu #mu", Bool_t verbose=true)
{
  //===========Make connections to tree's of two flat ntuple files=================================
  TFile *fd = new TFile(fdname);
  TFile *fm = new TFile(fmname);
  TTree *td = (TTree*)fd->Get(treename);
  TTree *tm = (TTree*)fm->Get(treename);

  if (verbose) {
    cout << "Using: "<< fdname << "<-dt file name|mc file name->"<<fmname << endl;
    cout << "TREE name used in both files: "<< treename<< endl;
  }
  //==========================================================================================
  //===========Define different comparison modes of two files=================================
  vector<TString> Modes;
  Modes.push_back("mcBp_mcBs");
  Modes.push_back("dtbgsub_mcrew");
  Modes.push_back("dtbgsub_mcrew_bisorew");

  //===========Output tex table with KS test results/variable=================================
  ofiletex << "\\begin{table}[htbp]\n";
  ofiletex << "\\caption{\\label{tab:sepVars}Data/MC agreement of separation variables}\n";
  ofiletex << "\\begin{center}\n";
  
  if (compVar=="systVars") ofiletex << "\\begin{tabular}{c|c|c}\n";
  else ofiletex << "\\begin{tabular}{c|c|c}\n";
  if (compVar=="systVars") ofiletex << "Variable & KS test & Chi2/ndf \\\\\n\\hline\n";
  else ofiletex << "Variable/Vertex type & 3-prong & 2-prong\\\\\n\\hline\n"; 
  //==========================================================================================

  //===========Calculate variables for bkg subtraction=================================
  fd->cd();
  if (compMode.Contains("dtbgsub")) getNbkgBpJpsiKp(td);
  //========================================================================================== 

  //===========Loop over variables and modes and do comparison================================= 
  for (int i=0;i<nVar;i++) {
    //cout << nVar << "| "<< i << endl;
    if ((compVar!="" && compVar.CompareTo(Variables[i].name)) && !(Variables[i].usedForSystematics && compVar=="systVars")) continue;
    cout << "INFO Processing variable: " << Variables[i].name<<endl;
    for (unsigned int j=0;j<Modes.size();j++) {
      if (compMode!="" && compMode.CompareTo(Modes[j])) continue;
      cout << "INFO Processing mode: " << Modes[j]<<endl;
      compare(Variables[i], Modes[j], td, tm, dtlabel, mclabel, true, true);
    }
  }
  fout->cd();
  fout->Close();
  //==========================================================================================
  //===========Finish writing out table ================================= 
  ofiletex << "\\end{tabular}\n";
  ofiletex << "\\end{center}\n";
  ofiletex << "\\end{table}\n";
  ofiletex.close();
  //==========================================================================================
}

void getNbkgBpJpsiKp(TTree* td)
{
  cout << endl;
  cout << "Performing Bplus fit to estimate # of signal events in signal region. Enough time to grap a coffee..." << endl;
  cout << endl;
  //
  //SAME selection criteria (Mass,Odd/Even,Fixes) as for yield calculation
  //

  Double_t binWidth = 10.0;
  Int_t NBins = (int) (BUpperMassCut-BLowerMassCut)/binWidth;
  Double_t FitMin=BLowerMassCut, FitMax=BUpperMassCut;
  const Int_t Npars = 10;

  TH1F* histo = getHistoFromTree(td, "B_VTX_mass", "B_VTX_mass_dt", CutAdd, NBins, BLowerMassCut, BUpperMassCut);
  histo->SetName("histo");
  TCanvas* cfit = new TCanvas("cfit","cfit",20,20,900,600);
  cfit->SetRightMargin(0.10);
  histo->SetMarkerStyle(20);
  histo->SetMarkerColor(2);
  histo->SetMarkerSize(0.7);
  histo->SetMinimum(0);
  histo->GetXaxis()->SetTitle("m_{J/#psi K} [MeV]");
  histo->GetYaxis()->SetTitleOffset(0.75);
  histo->GetYaxis()->SetTitle("B^{#pm} candidates / (10 MeV)");

  cout << endl;
  cout << "INFO got histo for fitting, entries: " << histo->GetEntries()<< endl;  //including over and underflows!
  cout << endl;

  histo->Draw("e"); 

  //----------------------------------------------------
  // Fit the invariant mass spectrum 
  // with a double Gaussian function + erfc + linear (in place of exponential)
  //----------------------------------------------------


  Double_t defInitFitPars[Npars];
  if (useEXP) {
    defInitFitPars[0] = 25000;
    defInitFitPars[1] = -1.2e-4;

    defInitFitPars[2] = 1000.0;
    defInitFitPars[3] = 5150.0;
    defInitFitPars[4] = 50.0;

    defInitFitPars[5] = 5500.0;
    defInitFitPars[6] = 6500.0;
    defInitFitPars[7] = 5280.0;
    defInitFitPars[8] = 20.0;
    defInitFitPars[9] = 40.0; //60.0
  } else {
    defInitFitPars[0] = 36000.0; //30K
    defInitFitPars[1] = -2.8;

    defInitFitPars[2] = 1000.0;
    defInitFitPars[3] = 5150.0;
    defInitFitPars[4] = 50.0;

    defInitFitPars[5] = 5500.0;
    defInitFitPars[6] = 6500.0;
    defInitFitPars[7] = 5280.0;
    defInitFitPars[8] = 20.0;
    defInitFitPars[9] = 40.0; //60.0
  }


  TF1 *functot; 
  if (useEXP) functot= new TF1("functot",FuncTotWithExp,FitMin,FitMax,Npars);
  else functot= new TF1("functot",FuncTotWithLin,FitMin,FitMax,Npars);

  for (int ip=0;ip<Npars;ip++) functot->SetParameter(ip, defInitFitPars[ip]);
  // functot->Draw();
 
  if (useEXP) {
    //0 cont bkg exp norm
    //1 cont bkg exp slope
    functot->SetParLimits(0, 1.0,100000.0);
    functot->SetParLimits(1,-0.5,0.000001);
    //2 prd erf norm
    //3 prd erf mu
    //4 prd erf sigma
    functot->SetParLimits(2,0.0,10000.0);
    functot->SetParLimits(3,5000.0,5200.0);
    functot->SetParLimits(4,1.0,200.0);
    //5 dgaus norm 1st
    //6 dgaus norm 2nd
    //7 dgaus mu
    //8 dgaus sig1
    //9 dgaus sig2
    functot->SetParLimits(5, 1.0,10000.0);
    functot->SetParLimits(6, 1.0,10000.0);   
    functot->SetParLimits(7, 5260.0,5300.0);
    functot->SetParLimits(8, 10.0,50.0);
    functot->SetParLimits(9, 35.0,100.0);
  } else {
    //0 cont bkg exp norm
    //1 cont bkg exp slope
    functot->SetParLimits(0, 1.0,100000.0);
    functot->SetParLimits(1,-5.0,-0.000001);
    //2 prd erf norm
    //3 prd erf mu
    //4 prd erf sigma
    functot->SetParLimits(2,0.0,10000.0);
    functot->SetParLimits(3,5000.0,5200.0);
    functot->SetParLimits(4,1.0,200.0);
    //5 dgaus norm 1st
    //6 dgaus norm 2nd
    //7 dgaus mu
    //8 dgaus sig1
    //9 dgaus sig2
    functot->SetParLimits(5, 1.0,10000.0);
    functot->SetParLimits(6, 1.0,10000.0);   
    functot->SetParLimits(7, 5260.0,5300.0);
    functot->SetParLimits(8, 10.0,50.0);
    functot->SetParLimits(9, 35.0,100.0);
  } 
  functot->SetLineColor(kBlue);
  functot->SetLineWidth(2);
  
  ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls(10000);
  TFitResultPtr r = histo->Fit(functot,"RLSBI");
  // R - use range
  // L - likelihood fit
  // S - save resilts
  // B - User defined parameter settings are used for predefined functions (if one or more params to be fixed) 
  // I - Use integral of function in bin, normalized by the bin volume, instead of value at bin center
  
  r = histo->Fit(functot,"RLSBI");
  r = histo->Fit(functot,"RLSBI");
  cout << " COV matrix status: "<< r->CovMatrixStatus() <<endl;
  /// covariance matrix status code
  /// using Minuit convention : =0 not calculated, =1 approximated, =2 made pos def , =3 accurate
  
  TF1 *gaus1 = new TF1("gaus1",FuncBpS,BLowerMassCut,BUpperMassCut,Npars);
  for(int i=0;i<Npars;i++) gaus1->SetParameter(i,functot->GetParameter(i));
  gaus1->SetLineColor(kGreen);
  gaus1->Draw("same");
 
  TF1 *gaus2 = new TF1("gaus2",FuncBpS2,BLowerMassCut,BUpperMassCut,Npars);
  for(int i=0;i<Npars;i++) gaus2->SetParameter(i,functot->GetParameter(i));
  gaus2->SetLineColor(kRed);
  gaus2->Draw("same"); 
 
  const int totNBkgPars = 5;
  TF1 *totbkg;
  if (useEXP) totbkg = new TF1("totbkg",FuncBkgTotWithExp,BLowerMassCut,BUpperMassCut,totNBkgPars);
  else totbkg = new TF1("totbkg",FuncBkgTotWithLin,BLowerMassCut,BUpperMassCut,totNBkgPars);
  for(int i=0;i<totNBkgPars;i++) totbkg->SetParameter(i,functot->GetParameter(i));
  totbkg->SetLineColor(kBlack);
  totbkg->Draw("same");

  const int totNSigPars = 5;
  TF1 *totsig;
  totsig = new TF1("totsig",double_gaus,BLowerMassCut,BUpperMassCut,totNSigPars);
  for(int i=0;i<totNSigPars;i++) totsig->SetParameter(i,functot->GetParameter(i+totNBkgPars));
  totsig->SetLineColor(kBlack);
  totsig->Draw("same");
  
  TF1 *contbkg;
  if (useEXP) contbkg = new TF1("contbkg",exp_fn,BLowerMassCut,BUpperMassCut,2);
  else contbkg = new TF1("contbkg",lin_fn,BLowerMassCut,BUpperMassCut,2);
  for(int i=0;i<2;i++) contbkg->SetParameter(i,functot->GetParameter(i));
  contbkg->SetLineColor(kOrange);
  contbkg->Draw("same");
  
  TF1 *partbkg;
  partbkg = new TF1("partbkg",err_fn,BLowerMassCut,BUpperMassCut,3);
  for(int i=0;i<3;i++) partbkg->SetParameter(i,functot->GetParameter(i+2));
  partbkg->SetLineColor(kMagenta);
  partbkg->Draw("same");

  Double_t NBkg = totbkg->Integral(SRLow,SRHigh)/binWidth;
  cout << "PAR: "<<totbkg->GetNpar()<< " bin width: "<< binWidth << endl;
  Double_t NPartBkgSR = partbkg->Integral(SRLow,SRHigh)/binWidth;
  Double_t NPartBkgLSB = partbkg->Integral(LSBLow,LSBHigh)/binWidth;
  Double_t NPartBkgRSB = partbkg->Integral(RSBLow,RSBHigh)/binWidth;
  Double_t NContBkgSR = contbkg->Integral(SRLow,SRHigh)/binWidth;
  Double_t NContBkgLSB = contbkg->Integral(LSBLow,LSBHigh)/binWidth;
  Double_t NContBkgRSB = contbkg->Integral(RSBLow,RSBHigh)/binWidth;
  Double_t NSigSR = totsig->Integral(SRLow,SRHigh)/binWidth;
  Double_t NSigLSB = totsig->Integral(LSBLow,LSBHigh)/binWidth;
  Double_t NSigRSB = totsig->Integral(RSBLow,RSBHigh)/binWidth;

  Double_t totbkgpars[totNBkgPars];
  Double_t contbkgpars[2];
  Double_t partbkgpars[3];
  for (int i=0;i<totNBkgPars;i++) {
    totbkgpars[i]=functot->GetParameter(i);
    if (i<2) contbkgpars[i] = functot->GetParameter(i);
    else partbkgpars[i-2] =functot->GetParameter(i);
  }
  Double_t totsigpars[totNSigPars];
  for (int i=0;i<totNSigPars;i++) totsigpars[i]=functot->GetParameter(i+totNBkgPars);

  TMatrixDSym cov = r->GetCovarianceMatrix();
  Double_t *fullmat;
  fullmat = cov.GetMatrixArray();
  TMatrixDSym corr = r->GetCorrelationMatrix();
  Double_t *corrmat;
  corrmat = corr.GetMatrixArray();

  Double_t totbkgmat[totNBkgPars*totNBkgPars];
  Double_t contbkgmat[2*2];
  Double_t partbkgmat[3*3];
  for(Int_t i=0;i<totNBkgPars;i++){
    for(Int_t j=0;j<totNBkgPars;j++) {
      totbkgmat[totNBkgPars*i+j]=fullmat[j+Npars*i];
      if (i<2 && j<2) contbkgmat[2*i+j]=fullmat[j+Npars*i];
      if (i>1 && j>1) partbkgmat[3*(i-2)+(j-2)]=fullmat[j+Npars*i];
      cout << i<<"|"<<j<<" "<< totbkgmat[totNBkgPars*i+j]<<endl;
    }
  }
  cout << endl;
  cout << "CORR MAT FOR SIGNAL:"<<endl;
  Double_t totsigmat[totNSigPars*totNSigPars];
  for(Int_t i=0;i<totNSigPars;i++){
    for(Int_t j=0;j<totNSigPars;j++) {
      totsigmat[totNSigPars*i+j]=fullmat[j+totNBkgPars+Npars*(i+totNBkgPars)];
      //	cout << i<<"|"<<j<<" "<< totsigmat[totNSigPars*i+j]<<endl;
      cout << corrmat[j+totNBkgPars+Npars*(i+totNBkgPars)]<<"\t\t";
    }
    cout << endl;
  }
  Double_t NBkgErr = totbkg->IntegralError(SRLow,SRHigh,totbkgpars,totbkgmat)/binWidth;
  Double_t NPartBkgSRErr = partbkg->IntegralError(SRLow,SRHigh,partbkgpars,partbkgmat)/binWidth;
  Double_t NPartBkgLSBErr = partbkg->IntegralError(LSBLow,LSBHigh,partbkgpars,partbkgmat)/binWidth;
  Double_t NPartBkgRSBErr = partbkg->IntegralError(RSBLow,RSBHigh,partbkgpars,partbkgmat)/binWidth;
  Double_t NContBkgSRErr = contbkg->IntegralError(SRLow,SRHigh,contbkgpars,contbkgmat)/binWidth;
  Double_t NContBkgLSBErr = contbkg->IntegralError(LSBLow,LSBHigh,contbkgpars,contbkgmat)/binWidth;
  Double_t NContBkgRSBErr = contbkg->IntegralError(RSBLow,RSBHigh,contbkgpars,contbkgmat)/binWidth;
  Double_t NSigSRErr = totsig->IntegralError(SRLow,SRHigh,totsigpars,totsigmat)/binWidth;
  Double_t NSigLSBErr = totsig->IntegralError(LSBLow,LSBHigh,totsigpars,totsigmat)/binWidth;
  Double_t NSigRSBErr = totsig->IntegralError(RSBLow,RSBHigh,totsigpars,totsigmat)/binWidth;

  cout << endl;
  cout << "Total N bkg in SR: " << NBkg << " pm: " << NBkgErr << endl;
  cout << "Partial N bkg in SR: " << NPartBkgSR << " pm: " << NPartBkgSRErr << endl;
  cout << "Partial N bkg in LSB: " << NPartBkgLSB << " pm: " << NPartBkgLSBErr << endl;
  cout << "Partial N bkg in RSB: " << NPartBkgRSB << " pm: " << NPartBkgRSBErr << endl;
  cout << "Continuum N bkg in SR: " << NContBkgSR << " pm: " << NContBkgSRErr << endl;
  cout << "Continuum N bkg in LSB: " << NContBkgLSB << " pm: " << NContBkgLSBErr << endl;
  cout << "Continuum N bkg in RSB: " << NContBkgRSB << " pm: " << NContBkgRSBErr << endl;
  cout << "Total N sig in SR: " << NSigSR << " pm: " << NSigSRErr << endl;
  cout << "Total N sig in LSB: " << NSigLSB << " pm: " << NSigLSBErr << endl;
  cout << "Total N sig in RSB: " << NSigRSB << " pm: " << NSigRSBErr << endl;
  cout << endl;

  nbkgInfo.nTotBkgSR = NBkg;
  nbkgInfo.nTotBkgSRErr = NBkgErr;
  
  nbkgInfo.nPartBkgSR = NPartBkgSR;
  nbkgInfo.nPartBkgSRErr = NPartBkgSRErr;
  
  nbkgInfo.nContBkgSR = NContBkgSR;
  nbkgInfo.nContBkgSRErr = NContBkgSRErr;

  nbkgInfo.nContBkgLSB = NContBkgLSB;
  nbkgInfo.nContBkgLSBErr = NContBkgLSBErr;

  nbkgInfo.nContBkgRSB = NContBkgRSB;
  nbkgInfo.nContBkgRSBErr = NContBkgRSBErr;

  // whole B_pT range
  //
  nbkgInfo.LowPt = 0;
  nbkgInfo.UpPt = 1000000;
  
  //+++++++++++++++++++++ Drawing Guide Lines and Labels  ++++++++++++++++++++++++++++++++++++++++++  
  //
  TPaveLabel *labSig = new TPaveLabel(0.25,0.8,0.45,0.88, Form("N_{sig}^{SR} = %4.1f #pm %3.1f", NSigSR, NSigSRErr),"rNDC");
  labSig->SetTextSize(0.52);
  labSig->SetTextAlign(31);
  labSig->SetFillColor(0);
  labSig->Draw();
  
  /*
    TPaveLabel *labBkg = new TPaveLabel(0.25,0.8,0.45,0.88, Form("N_{bkg}^{SR} = %4.1f #pm %3.1f", NBkg, NBkgErr),"rNDC");
    labBkg->SetTextSize(0.52);
    labBkg->SetTextAlign(31);
    labBkg->SetFillColor(0);
    labBkg->Draw();
  */
  TPaveLabel *labBkgLR = new TPaveLabel(0.25,0.7,0.45,0.78, Form("N_{bkgL(R)}^{SR} = %4.1f(%4.1f) #pm %3.1f(%3.1f)", NPartBkgSR, NContBkgSR, NPartBkgSRErr, NContBkgSRErr),"rNDC");
  labBkgLR->SetTextSize(0.52);
  labBkgLR->SetTextAlign(31);
  labBkgLR->SetFillColor(0);
  //labBkgLR->Draw();

  // draw SB and SR regions
  Double_t hmin=histo->GetMinimum();
  Double_t hmax=histo->GetMaximum();
 
  TLine *l_lsblow = new TLine(LSBLow, hmin,LSBLow,hmax);
  l_lsblow->SetLineColor(38);
  l_lsblow->SetLineStyle(2);
  l_lsblow->SetLineWidth(3);
  l_lsblow->Draw();
  TLine *l_lsbhigh = new TLine(LSBHigh, hmin,LSBHigh,hmax);
  l_lsbhigh->SetLineColor(38);
  l_lsbhigh->SetLineStyle(2);
  l_lsbhigh->SetLineWidth(3);
  l_lsbhigh->Draw();

  TLine *l_rsblow = new TLine(RSBLow, hmin,RSBLow,hmax);
  l_rsblow->SetLineColor(38);
  l_rsblow->SetLineStyle(2);
  l_rsblow->SetLineWidth(3);
  l_rsblow->Draw();
  TLine *l_rsbhigh = new TLine(RSBHigh, hmin,RSBHigh,hmax);
  l_rsbhigh->SetLineColor(38);
  l_rsbhigh->SetLineStyle(2);
  l_rsbhigh->SetLineWidth(3);
  l_rsbhigh->Draw();

  TLine *l_srlow = new TLine(SRLow, hmin,SRLow,hmax);
  l_srlow->SetLineColor(46);
  l_srlow->SetLineStyle(2);
  l_srlow->SetLineWidth(3);
  l_srlow->Draw();
  TLine *l_srhigh = new TLine(SRHigh, hmin,SRHigh,hmax);
  l_srhigh->SetLineColor(46);
  l_srhigh->SetLineStyle(2);
  l_srhigh->SetLineWidth(3);
  l_srhigh->Draw();
  
  cout  << "start writing " << endl;
  fout->cd();
  cfit->Write();
  cfit->SaveAs(outpath + TString("cfit.eps"));
  
  histo->Write();
  delete functot;

  cout << " Number of bkg events: "<< nbkgInfo.nTotBkgSR << " +/- "<<nbkgInfo.nTotBkgSRErr <<endl; 
}

Double_t FuncBpS(Double_t *x, Double_t *par){  //Single Gauss
  Double_t FitBpS = par[5]*TMath::Gaus(x[0],par[7],par[8]);
  return FitBpS;
}

Double_t FuncBpS2(Double_t *x, Double_t *par){  //Single Gauss
  Double_t FitBpS = par[6]*TMath::Gaus(x[0],par[7],par[9]);
  return FitBpS;
}

Double_t FuncBkgGaus(Double_t *x, Double_t *par){  //Gauss Bkg
  Double_t FitBkgGaus = par[11]*TMath::Gaus(x[0], 5360.0, 60.0);
  return FitBkgGaus;
}

Double_t FuncBkgGausCp(Double_t *x, Double_t *par){
  return par[0]*TMath::Gaus(x[0], 5360.0, 60.0);
}

Double_t FuncBpD(Double_t *x, Double_t *par){  //Double Gauss
  if (par[8]<0) par[8]=-par[8]; // make sure sigma > 0
  if (par[10]<0) par[10]=-par[10]; // make sure sigma > 0
  Double_t arg1 = (x[0] - par[7])/par[8];
  Double_t arg2 = (x[0] - par[7])/par[10];
  return par[6]*TMath::Exp(-0.5*arg1*arg1)/(TMath::Sqrt(2*TMath::Pi())*par[8])+par[9]*TMath::Exp(-0.5*arg2*arg2)/(TMath::Sqrt(2*TMath::Pi())*par[10]);
}

Double_t FuncBpD2(Double_t *x, Double_t *par){  //Double Gauss
  Double_t FitBpD = par[0]*TMath::Gaus(x[0],par[1],par[2])+par[3]*TMath::Gaus(x[0],par[1],par[4]);
  return FitBpD;
}

Double_t FuncBkgLin(Double_t *x, Double_t *par){  //linear
  return par[0]+par[1]*x[0];
}

Double_t FuncBkgErfcLin(Double_t *x, Double_t *par){  //erfc*lin
  Double_t t = (x[0]-par[4])/par[5];
  return (par[2]+par[3]*x[0])*TMath::Erfc(t);
}

Double_t FuncBkgErfcExp(Double_t *x, Double_t *par){  //erfc*exp
  Double_t t = (x[0]-par[4])/par[5];
  return exp(par[2]*par[3]*x[0])*TMath::Erfc(t);
}

Double_t FuncBkgTotWithLin(Double_t *x, Double_t *par){  //total bkg
  return FuncBkgLin(x,par)+FuncBkgErfcLin(x,par);
}

Double_t FuncBkgTotWithExp(Double_t *x, Double_t *par){  //total bkg
  return exp_fn(x,par)+err_fn(x,&par[2]);
}

Double_t FuncTotWithLin(Double_t *x, Double_t *par){  // total fit
  return lin_fn(x,par)+err_fn(x,&par[2])+double_gaus(x,&par[5]);
}

Double_t FuncTotWithExp(Double_t *x, Double_t *par){  // total fit
  return exp_fn(x,par)+err_fn(x,&par[2])+double_gaus(x,&par[5]);
}

TH1F* getHistoFromTree(TTree* tree, VariableInfo Variable, const char* hname, TCut cut)
{
  cout << "GetHistoFromTree, getting histo "<< hname << " for variable " << Variable.name << " from tree "<< tree->GetName() << endl;
  //==================================================================================================
  //====create TString defining how the histogram will be retrieved with TTree::Draw method===========
  //================================================================================================== 
  TString tmp = Variable.name;
  TString axlab = Variable.axLabel;
  Int_t NBins = Variable.nbins;
  Float_t XMin = Variable.XMin;
  Float_t XMax = Variable.XMax;
  if (axlab.Contains("[GeV]")) tmp.Append("/1000.0");
  TString tmpDummy(tmp);
  tmp.Append(">>");
  tmp.Append(hname);
  if (NBins>0 && XMin!=XMax) {
    tmp+=("(");
    tmp+=NBins;
    tmp+=",";
    tmp+=XMin;
    tmp+=",";
    tmp+=XMax;
    tmp+=")";
  } else if (NBins == -1) { 
    tmpDummy.Append(">>+");
    tmpDummy.Append(hname);
  } else tmp.Append("(100)"); //restore default (ROOT) binning
  //==================================================================================================
  //====retrieve histo from TTree============
  //==================================================================================================
  TH1F *hret;
  int nselected(0);
  if (NBins == -1) { //variable binning for eta and pt taken from *.h file                                                                  
    if (tmpDummy.Contains("BvtxPt") || tmpDummy.Contains("B_pT") || tmpDummy.Contains("JPsiPt") || tmpDummy.Contains("BTruthPt")) hret = new TH1F(*hdummyPt); 
    else if (tmpDummy.Contains("eta") || tmpDummy.Contains("Eta")) hret = new TH1F(*hdummyEta);
    else if (tmpDummy.Contains("Iso") || tmpDummy.Contains("_iso_")) hret = new TH1F(*hdummyIso);
    else if (tmpDummy.Contains("Lxy")) hret = new TH1F(*hdummyLxy);
    else if (tmpDummy.Contains("ClassBDT")) hret = new TH1F(*hdummyClassBDT);
    else {
      cout << "Unknown binning, returning zero pointer..." <<endl;
      return NULL;
    }
    hret->SetName(hname);
    hret->Reset();
    hret->Sumw2();
    nselected = tree->Draw(tmpDummy.Data(),cut,"egoff"); 
    cout << "GetHistoFromTree, creating histo:" << tmpDummy << " event survived the cut(s): " << nselected << endl;
  } else {
    nselected = tree->Draw(tmp.Data(),cut,"egoff");
    cout << "GetHistoFromTree, creating histo:" << tmp << " event survived the cut(s): " << nselected << endl;
    hret = (TH1F*)gDirectory->Get(hname);
  }
 
  hret->GetXaxis()->SetTitle(axlab);
  hret->SetTitle(hname);
  cout << "Creating histo, title "<< hname <<", hret integral.."<< hret->Integral() <<endl; //cut out over- and unerflows
  cout << endl;
  return hret;
}

TH1F* getHistoFromTree(TTree* tree, const char* var, const char* hname, TCut cut, Int_t NBins, Float_t XMin, Float_t XMax)
{
  if (NBins==-1) {
    cout << "FATAL: simple GetVarHistoFromTree does not work with NBins==-1"<< endl;
    return NULL;
  } else cout << "GetVarHistoFromTree(simple), getting histo "<< hname << " for variable " << var << " from tree "<< tree->GetName()<<" , NBins = " << NBins << endl;
  TString tmp = var;
  tmp.Append(">>");
  tmp.Append(hname);
  if (NBins>0 && XMin!=XMax) {
    tmp+=("(");
    tmp+=NBins;
    tmp+=",";
    tmp+=XMin;
    tmp+=",";
    tmp+=XMax;
    tmp+=")";
  } else tmp.Append("(100)"); //restore default (ROOT) binning

  TH1F *hret;
  int nselected(0);
  nselected = tree->Draw(tmp.Data(),cut,"egoff");

  cout << "GetVarHistoFromTree, creating histo:" << tmp << " event survived the cut(s): " << nselected << endl; //they can hide in over- and unerflows!!!
  hret = (TH1F*)gDirectory->Get(hname);
  hret->SetTitle(hname);
  cout << "Creating histo, title "<< hname <<", hret integral.."<< hret->Integral() <<endl; //cut out over- and unerflows
  cout << endl;
  return hret;
}

void compare(VariableInfo Variable, TString mode, TTree* td, TTree* tm, TString dtlabel, TString mclabel, bool normalize, bool drawResiduals)
{
  TH1F* h1(NULL);
  TH1F* h2(NULL);
  TString h1title = Variable.name;
  if (h1title.Contains("TMath::Abs")) h1title.ReplaceAll("TMath::Abs","fabs");
  if (h1title.Contains('(')) h1title.ReplaceAll('(','_');
  if (h1title.Contains(')')) h1title.ReplaceAll(')','_');
  if (h1title.Contains('/')) h1title.ReplaceAll('/','_');

  TString h2title(h1title);
  TString htitle(h1title);
  TString hdivtitle(h1title);

  if (mode.EqualTo("mcBp_mcBs")) {
    h1title+="_mc10";
    h1 = getHistoFromTree(td, Variable, h1title, CutAdd && "(B_VTX_mass>5180 && B_VTX_mass<5380)*CombWeights*PVWeights*CatN1Weights*CatN2Weights*CatN3Weights*isSignal");
    h2title+="_mc11";
    h2 = getHistoFromTree(tm, Variable, h2title, CutAdd && "(B_MUCALC_mass>5126 && B_MUCALC_mass<5606)*CombWeights*PVWeights*CatN1Weights*CatN2Weights*CatN3Weights*isSignal");
  } else if (mode.EqualTo("dtbgsub_mcrew")) {
    h1title+="_dtbgsub";
    h1 = subtractMix(Variable, td); 
    fout->cd();
    h1->Write();
    h2title+="_mc";
    // if weights are avaliable
    // h2 = getHistoFromTree(tm, Variable, h2title, CutAdd);
    // below if weights are available
    h2 = getHistoFromTree(tm, Variable, h2title, (CutAdd && "K_charge>0")*"CombWeights"); //FIXME
    fout->cd();
    h2->Write();
  } 

  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) c1->Clear();
  else c1 = new TCanvas("c1","c1",0,45,800,600);
  c1->SetLogy(0);
  c1->SetLeftMargin(0.13);
  c1->SetRightMargin(0.10); //0.07
  c1->SetTopMargin(0.07);
  c1->SetBottomMargin(0.12);
  h1->SetLineWidth(2);        if (h2) h2->SetLineWidth(2); 
  h1->SetFillColor(0);        if (h2) h2->SetFillColor(0);//kRed);/*30*/
  h1->SetLineColor(kBlack);   if (h2) h2->SetLineColor(kRed); 
  h1->SetLineStyle(1);        if (h2) h2->SetLineStyle(1);/*22*/
  h1->SetMarkerSize(0.8);     if (h2) h2->SetMarkerSize(0.8);
  h1->SetMarkerStyle(20);     if (h2) h2->SetMarkerStyle(25);   
  h1->SetMarkerColor(kBlack); if (h2) h2->SetMarkerColor(kRed);
  if (h2) h2->SetFillStyle(3002);
  //if (h2) h2->SetMarkerSize(0);


  //  h2->SetFillStyle(3004);
  if (Variable.nbins>0 && Variable.XMin!= Variable.XMax) {
    h1->GetXaxis()->SetRangeUser(Variable.XMin,Variable.XMax);
    if (h2) h2->GetXaxis()->SetRangeUser(Variable.XMin,Variable.XMax);
  }
  else if (Variable.nbins!=-1) { 
    if (h2) h2->GetXaxis()->Set(h1->GetXaxis()->GetNbins(),h1->GetXaxis()->GetXmin(),h1->GetXaxis()->GetXmax());
  }
  if (normalize) {
    //typically means normalize MC(h2) to data (h1)
    //
    cout << endl;
    cout << "INFO Integral of entries of each histo BEFORE normalization: " << endl;
    cout << h1->GetTitle() <<": "<< h1->Integral();
    if (h2) cout << " "<< h2->GetTitle()<< ": "<< h2->Integral();
    cout << endl;
    cout << endl;
    
    h2->Scale(h1->Integral()/h2->Integral()); // ATTENTION under- and over-flows not taken into account!!!  
  }
  TString axLab = Variable.axLabel;
  h1->GetXaxis()->SetTitle(axLab);
  if (h2) {
    h2->GetXaxis()->SetTitle(axLab);
  }

  if (drawResiduals) {
    h1->GetYaxis()->SetTitleOffset(0.7); //0.57
    h1->GetYaxis()->SetTitleSize(0.08);
    if (h2) {
      h2->GetYaxis()->SetTitleOffset(0.7); //0.57
      h2->GetYaxis()->SetTitleSize(0.08);
    }
  }
  else {
    h1->GetYaxis()->SetTitleOffset(0.72);
    h1->GetYaxis()->SetTitleSize(0.07);
    if (h2) {
      h2->GetYaxis()->SetTitleOffset(0.72);
      h2->GetYaxis()->SetTitleSize(0.07);
    }
  }
 
  TString yAxisTitle = getYAxisTitle(Variable.name);
  if (Variable.nbins>0 && Variable.XMin!= Variable.XMax) {
    yAxisTitle +=" / ";
    char buf[20];
    sprintf(buf,"%3.2f",(Variable.XMax-Variable.XMin)/(double)Variable.nbins);
    yAxisTitle+=buf;
    yAxisTitle += " "; //FMPLOT
    TString dummyStr(axLab);
    dummyStr.Remove(0,dummyStr.Index('[')+1);
    dummyStr.Remove(dummyStr.Index(']'),dummyStr.Length());
    if (axLab.Contains("[")) yAxisTitle += dummyStr;
  }
  h1->GetYaxis()->SetTitle(yAxisTitle);
  if (h2) h2->GetYaxis()->SetTitle(yAxisTitle); 

  Double_t chi2_1(0.),ks1(0.);
  Int_t ndf_1(0), igood_1(0);
 
  if (h2) {
    h1->Chi2TestX(h2,chi2_1,ndf_1,igood_1,"WW P"); //Weighted Weighted Print
    ks1 = h1->KolmogorovTest(h2);
    TString tabentry(Variable.axLabel);
    if (tabentry.Contains("DeltaR")) tabentry.ReplaceAll("DeltaR","Delta~R");
    char buf[20];
    sprintf(buf,"%5.1f/%3d",chi2_1,ndf_1);
    ofiletex << "$"<< tabentry.ReplaceAll('#','\\') <<"$" << " & "<< ks1 << " & "<< buf << "\\\\\n\\hline\n";
  }

  TPad *pad1, *pad2;
  pad1 = new TPad("pad1","pad1",0,0.33,1,1); //xlow ylow xup yup
  pad2 = new TPad("pad2","pad2",0,0,1,0.33); //0.3

  if (drawResiduals) {
    pad1->SetMargin(0.12,0.05,0.028,0.09);
    pad1->SetBorderMode(0);
    if (Variable.logScale) pad1->SetLogy();
    if (h2) {
      pad2->SetMargin(0.12,0.05,0.38,0.06);
      pad2->SetBorderMode(0);
      pad1->Draw();
      pad2->Draw();
      pad1->cd();
    }
  }

  if (h2 && h2->GetMean()!=0 && h2->GetRMS()!=0) {
    h1->GetYaxis()->SetLabelSize(0.08);
    h1->GetXaxis()->SetNoExponent();
    h2->GetYaxis()->SetLabelSize(0.08);
    h2->GetXaxis()->SetNoExponent();
    h1->GetXaxis()->SetLabelOffset(0.028); //0.07
    h2->GetXaxis()->SetLabelOffset(0.028); //0.07
    h1->GetXaxis()->SetTitle("");
    h2->GetXaxis()->SetTitle("");
    cout << h1->GetMaximum() <<" <=h1max|h2max-> "<<h2->GetMaximum()<< endl;
    if (h1->GetMaximum()>h2->GetMaximum()) {
      h1->SetMaximum(h1->GetMaximum()*1.5);
      h1->Draw("");
      h1->Draw("epsame");
      h2->Draw("histsame");
      if(!h1->GetFillColor()) h1->Draw("epsame");
    } else {
      h2->SetMaximum(h2->GetMaximum()*1.5);
      h2->Draw("");
      h2->Draw("histsame");
      h1->Draw("epsame");
    }
  } else {
    h1->Draw("ep");
  }

  htitle+="_";
  htitle+=mode;

  TLegend *leg = defineLegendBox(Variable.name, drawResiduals);
  leg->SetBorderSize(0);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetTextFont(132);
  if (h2) {
    if (mode.Contains("dtbgsub_mcrew")) {
      leg->AddEntry(h1,"Background-subtracted data run 302393","p"); //FIXMELEGEND
      leg->AddEntry(h2,"B^{+}#rightarrow J/#psi K^{+} MC15","l"); 
    } else {
      dtlabel+=" (A)";
      mclabel+=" (B)";
      leg->AddEntry(h1,dtlabel,"elp");
      leg->AddEntry(h2,mclabel,"elp");
    }
  }
 
  leg->Draw();

  bool drawResError = true;
  if (drawResiduals) {
    pad2->cd();
    TH1F *hres = (TH1F*)h1->Clone("hres");
    cout << "Before plotting" << endl;
    hres->SetMarkerSize(0.7);
    hres->GetXaxis()->SetTitleOffset(1.0); //0.95
    hres->GetXaxis()->SetTitle(axLab);
    hres->GetXaxis()->SetTitleSize(0.17);
    hres->GetXaxis()->SetLabelSize(0.15); //0.17 0.1
    
    hres->GetYaxis()->SetTitleSize(0.17);
    hres->GetYaxis()->SetTitleOffset(0.32); //0.26
    if (mode.Contains("dtbgsub_mcrew")) hres->GetYaxis()->SetTitle("Data/MC"); //FIXMELEGEND
    else hres->GetYaxis()->SetTitle("A/B");
    hres->GetYaxis()->SetLabelSize(0.12);//0.17 //0.08
    hres->GetYaxis()->SetNdivisions(4,3,0); //4,5,0
    
    cout << "DEBUG " << " bin2 content: "<<h1->GetBinContent(2) << " error: "<< h1->GetBinError(2) << endl;
    if (h2) cout << "DEBUG " << " bin2 content: "<<h2->GetBinContent(2) << " error: "<< h2->GetBinError(2) << endl;
    cout << "DEBUG " << " bin4 content: "<<h1->GetBinContent(4) << " error: "<< h1->GetBinError(4) << endl;
    if (h2) cout << "DEBUG " << " bin4 content: "<<h2->GetBinContent(4) << " error: "<< h2->GetBinError(4) << endl;
    
    hres->Sumw2();
    
    hres->Divide(h1,h2,1.0,1.0); //RATIO
    hres->GetYaxis()->SetRangeUser(0,2);//0.55,1.75);

    hres->Draw("");
    hres->Draw("epsame");
    
    TLine *l = new TLine(h1->GetXaxis()->GetXmin(),1,h1->GetXaxis()->GetXmax(),1);
    l->SetLineColor(kBlack);
    l->SetLineStyle(2);
    l->SetLineWidth(3);
    l->Draw();
    
    TPaveText *chi2res = new TPaveText(0.72,0.76,0.98,0.95,"brNDC"); //0.62,0.56,0.88,0.75
    chi2res->SetName("chi2res");
    chi2res->SetFillStyle(0);
    chi2res->SetTextAlign(12);
    chi2res->SetTextSize(0.1);
    chi2res->SetBorderSize(0);
    char buf[20];
    sprintf(buf,"#chi^{2}/ndf = %5.1f/%3d",chi2_1,ndf_1);
    chi2res->AddText(buf);
    sprintf(buf,"KS test = %1.6f",ks1);
    chi2res->AddText(buf);
    chi2res->Draw();  //FIXME KSSTAT
  }

  fout->cd();
  
  h1->SetTitle("dataSR");
  h1->SetName("dataSR");

  if (h2) {
    // create histogram with data/MC ratios
    //
    h2->SetName("dataSB");
    h2->SetTitle("dataSB");
  
    TH1F* hdiv =(TH1F*)h1->Clone("hdiv");
    hdivtitle  = Variable.name;
    hdivtitle+="_div_data_by_mc";
    hdiv->Sumw2();
    hdiv->Divide(h1,h2,1.0/h1->Integral(),1.0/h2->Integral());
    for (Int_t i=1;i<=hdiv->GetNbinsX();i++) {
      if (hdiv->GetBinContent(i) < 0) {
	hdiv->SetBinContent(i, 1.0);
	hdiv->SetBinError(i, 0.);
      }
    }
    hdiv->SetTitle(hdivtitle);
    hdiv->SetName(hdivtitle);
    hdiv->Write();
  }

  c1->cd();
  c1->Update();
  c1->SaveAs(outpath+htitle+".eps");
  //
  //
  /*
  c1->SaveAs(outpath+htitle+".C");
  c1->SaveAs(outpath+htitle+".root");
  c1->SaveAs(outpath+htitle+".gif");
  */
  

  c1->Write(htitle);
  delete h1;
  delete h2;
  delete pad2;
  delete pad1;
  delete c1;
}

TH1F* subtractMix(VariableInfo Variable, TTree* td, TString cw, bool onlyRSB)
{
  TH1F* h1(NULL);
  TString h1title = Variable.name;
  if (h1title.Contains('(')) h1title.ReplaceAll('(','_');
  if (h1title.Contains(')')) h1title.ReplaceAll(')','_');
  TString h2title(h1title);
  h2title+="_dtmixsb";
  h1title+="_dtsig";

  h1 = getHistoFromTree(td, Variable, h1title, (CutAdd && CutSR)*cw);
  h1->Write(h1title+"SRall");
  h1->SetDirectory(0);
  double Nsig = h1->Integral();
  cout << endl;
  cout << "INFO SIG integral before subtraction: "<< Nsig << endl;
 
  TH1F* h2p;
  TH1F *h2pr;
  TH1F *h2pl;
  
  TCut CutSubtraction = CutAdd;
  TCut CutSubtractionLeft = CutSubtraction && CutLSB;
  TCut CutSubtractionRight = CutSubtraction && CutRSB;
 
  double Nsb, sf, sfErr, sfRelErr, Nsbl, Nsbr, sfr, sfrErr;
  TString h2ptitle,h2pltitle,h2prtitle;
  TH1F *h2 = (TH1F*)h1->Clone(h2title);
  h2->Sumw2();
  h2->Reset();


  // GET SB Histo
  TCut allCutsLeft = Form("%s && B_pT>=%g && B_pT<%g", CutSubtractionLeft.GetTitle(),nbkgInfo.LowPt,nbkgInfo.UpPt);
  //cout << allCutsLeft.GetTitle() << endl;
  TCut allCutsRight = Form("%s && B_pT>=%g && B_pT<%g", CutSubtractionRight.GetTitle(),nbkgInfo.LowPt,nbkgInfo.UpPt);
  //cout << allCutsRight.GetTitle() << endl;
  
  h2pltitle =h2title;
  h2prtitle =h2title;
  h2ptitle =h2title;
  int ipt = 0;
  h2pltitle+=Form("%dl",ipt);
  h2prtitle+=Form("%dr",ipt);
  h2ptitle+=Form("%db",ipt);
  cout << h2pltitle << " left<-|->right "<< h2prtitle<< endl;

  h2pl = getHistoFromTree(td, Variable, h2pltitle, allCutsLeft*cw);
  h2pr = getHistoFromTree(td, Variable, h2prtitle, allCutsRight*cw);
  
  h2pl->Write();
  h2pr->Write();

  if (!onlyRSB) {
    //===================================================================
    //======LEFT SB TAKEN FULLY =========================================
    //===================================================================
    Nsbl = h2pl->Integral();
    h2p = (TH1F*)h2pl->Clone();
    h2p->Sumw2();
    
    //===================================================================
    //======RSB SHAPE TAKEN FULLY========================================
    //===================================================================
    Nsbr = h2pr->Integral();
    h2p->Add(h2pr);
  } else {
    h2p = (TH1F*)h2pr->Clone();
    h2p->Sumw2();
  }
  cout << endl;
  cout << "DEBUG: BKG SUBT bin "<< ipt << " pT range: "<< nbkgInfo.LowPt << ".."<< nbkgInfo.UpPt<< " bkgSR/bkgSRErr: " << nbkgInfo.nTotBkgSR<< "/" << nbkgInfo.nTotBkgSRErr<< endl;
  cout << " SB integral before/after scaling, left: " << Nsbl << "/"<< h2pl->Integral() << " ,right: " << Nsbr << "/"<< h2pr->Integral() << " h2entries: "<< h2->Integral() << endl;

  //===================================================================
  //=======Then scale combined LSB+RSB events to the===================
  //=======number of expected bkg events in signal region==============
  //===================================================================

  // SCALE SB Histo 
  Nsb = h2p->Integral();
  //  sf = nbkgInfo.nTotBkgSR/Nsb; //FIXME
  //sfRelErr = nbkgInfo.nTotBkgSRErr/nbkgInfo.nTotBkgSR;

  sf = nbkgInfo.nTotBkgSR/(nbkgInfo.nContBkgLSB+nbkgInfo.nContBkgRSB);

  sfErr = sf*sqrt(pow(nbkgInfo.nTotBkgSRErr/nbkgInfo.nTotBkgSR,2)+
		  pow(sqrt(pow(nbkgInfo.nContBkgLSBErr,2)+pow(nbkgInfo.nContBkgRSBErr,2))/(nbkgInfo.nContBkgLSB+nbkgInfo.nContBkgRSB),2));

  h2p->Scale(sf);
  // PROPAGATE scale factor ERROR
  for (Int_t ix=1;ix<=h2p->GetNbinsX();ix++) h2p->SetBinError(ix,sqrt(pow(h2p->GetBinError(ix),2)+pow(sfErr,2)*pow(h2p->GetBinContent(ix),2)));
  h2p->SetEntries(h2p->Integral());
  
    
  h2->Add(h2p);
  h2->Write();  
  cout << " SR BKG integral before/after scaling: " << Nsb << "/"<< h2p->Integral() << " h2entries: "<< h2->Integral() << endl;
  cout << endl;
    
  h2pltitle.Clear();
  h2prtitle.Clear();
  h2ptitle.Clear();

 
 
  cout << "INFO BKG subtraction, " << " SB integral after pt addition and scaling: " <<  h2->Integral() << endl;
  Int_t Ndiff = h1->Integral() - h2->Integral();
  h1->Add(h2, -1);
  h1->SetEntries(Ndiff);
 
  cout << "INFO SIG integral after SB subtraction: "<< h1->Integral() << endl;
  cout << endl;

  // change title of the subtracted histo
  h1title = Variable.name;
  h1title+="_dtSBsubmix";
  h1->SetTitle(h1title);
  cout << endl;
  return h1;
}

void atlasLabel(Double_t x,Double_t y, bool drawRes = true, bool Preliminary=true,Color_t color=1, bool drawLumi=true, bool enlarge=false)
{
  double delx = 0.115*696*gPad->GetWh()*3/(5*472*gPad->GetWw());
  double textsize;
  double dy = 0.065;
  if (!drawRes) {
    delx+=0.02;
    textsize = 0.040;
  } else {
    if (enlarge) {
      textsize = 0.075; 
      delx+=0.04;
      dy = 0.125;
    }
    else textsize = 0.045;
  }
  TLatex *tex = new TLatex(x,y,"ATLAS");
  tex->SetNDC();
  tex->SetTextSize(textsize);
  tex->SetTextFont(72);
  tex->SetLineWidth(2);
  tex->SetTextColor(color);
  tex->Draw();
  if (Preliminary) {
    tex = new TLatex(x+delx,y,"for approval"); //Preliminary
    tex->SetNDC();
    tex->SetTextSize(textsize);
    tex->SetTextFont(42); //42
    tex->SetLineWidth(2);
    tex->SetTextColor(color);
    tex->Draw();
  }
  tex = new TLatex(x+0.02,y-dy,"#sqrt{s} = 7 TeV");
  tex->SetNDC();
  tex->SetTextSize(textsize);
  tex->SetTextFont(42);
  tex->SetLineWidth(2);
  tex->SetTextColor(color);
  tex->Draw();
  if (drawLumi) {
    tex = new TLatex(x-0.01,y-2*dy,"#int Ldt = 4.9 fb^{-1}");
    tex->SetNDC();
    tex->SetTextSize(textsize);
    tex->SetTextFont(42);
    tex->SetLineWidth(2);
    tex->SetTextColor(color);
    tex->Draw();
  }
}

TLegend* defineLegendBox(TString what, Bool_t drawinlet){
  TLegend* leg;
  if (drawinlet){
    if (what.Contains("Iso") || what.Contains("_iso_7") || what.Contains("_iso_5")) leg = new TLegend(0.14,0.74,0.64,0.94,NULL,"brNDC"); //xbl,ybl,xur,yur
    else if (what.Contains("_iso_Ntracks")) leg = new TLegend(0.43,0.74,0.93,0.94,NULL,"brNDC");
    else if (what.Contains("DR")) leg = new TLegend(0.39,0.72,0.89,0.92,NULL,"brNDC");
    else if (what.Contains("Eta") || what.Contains("eta") || what.Contains("deltaPhi")) leg = new TLegend(0.12,0.22,0.62,0.42,NULL,"brNDC");
    else if (what.Contains("lnChi2") || what.Contains("Chi2Muons") || what.Contains("chi2_PVSV") || what.Contains("SumMuTrackPixHits")) leg = new TLegend(0.17,0.74,0.67,0.94,NULL,"brNDC");
    else if (what.Contains("BDT")) leg = new TLegend(0.12,0.66,0.85,0.82,NULL,"brNDC");
    else leg = new TLegend(0.45,0.74,0.95,0.94,NULL,"brNDC"); //xbl(0.71),ybl(0.62),xur(0.98),yur(0.98)
  } else {
    if (what.Contains("Iso") || what.Contains("d0") || what.Contains("Eta") || what.Contains("eta") || what.Contains("DCA") || what.Contains("BDT")) leg = new TLegend(0.15,0.64,0.68,0.92,NULL,"brNDC"); //xbl,ybl,xur,yur //0.09
    else if (what.Contains("DR")) leg = new TLegend(0.45,0.74,0.68,0.92,NULL,"brNDC");
    else leg = new TLegend(0.74,0.75,0.95,0.93,NULL,"brNDC"); //xbl(0.71,0.68),ybl(0.62),xur(0.98),yur(0.98)
  }
  return leg;
}

TString getYAxisTitle(TString what) {
  TString yAxisTitle;
  if (what.Contains("JPsi")) {
    yAxisTitle = "J/#psi candidates";
  } else if (what.Contains("Mu") && !what.Contains("Mult")) {
    yAxisTitle = "#mu candidates";
  } else if (what.Contains("Kaon")) {
    yAxisTitle = "Kaon candidates";
  }  else if (what.Contains("d0")) {
    yAxisTitle = "#mu tracks";
  }
  else {
    yAxisTitle = "Events";
    //yAxisTitle = "B^{#pm} candidates"; 
    //yAxisTitle = "B_{s} candidates";
  }
  return yAxisTitle;
}
