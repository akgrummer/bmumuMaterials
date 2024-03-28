#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasLabels.C"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasLabels.h"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasStyle.C"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasStyle.h"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasUtils.C"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasUtils.h"

#include "AllVars.h"

TString GetDrawCommand(VariableInfo myVI, TString histName){
TString DrawCommand("");
DrawCommand = myVI.bname + ">>"+histName;
if (myVI.nbins > 0 ){
        DrawCommand+=("(");
        DrawCommand+=myVI.nbins;
        DrawCommand+=",";
        DrawCommand+=myVI.binLow;
        DrawCommand+=",";
        DrawCommand+=myVI.binHigh;
        DrawCommand+=")";
    }
return DrawCommand;
}

TH1F* GetHistogram(TTree *itree, VariableInfo myVI, TString histName, TCut iCut, HistGraphics hg){
    itree->Draw(GetDrawCommand(myVI, histName), iCut, "egoff");
    TH1F* h1 = (TH1F*)gDirectory->Get(histName);

    h1->SetLineColor(hg.theLineColor);
    h1->SetMarkerColor(hg.theMarkerColor);
    h1->SetMarkerStyle(hg.theMarkerStyle);
    if (hg.theFillStyle != 0) h1->SetFillColorAlpha(hg.theFillColor, hg.theAlpha);
    if (hg.theFillStyle != 0) h1->SetFillStyle(hg.theFillStyle);

    TString yAxisTitle = "Fraction of Events";
    Float_t BinWidth = (myVI.binHigh-myVI.binLow)/myVI.nbins;
    if (myVI.xtitle.Contains("GeV")){
        yAxisTitle+="/(";
        BinWidth = BinWidth*1000;
        yAxisTitle+= BinWidth;
        yAxisTitle+=" MeV)";
    }
    else{
        yAxisTitle+="/";
        yAxisTitle+= Form("%.2f", BinWidth);
    }
    h1->GetYaxis()->SetTitle(yAxisTitle);
    h1->GetXaxis()->SetTitle(myVI.xtitle);
    h1->GetXaxis()->SetRangeUser(myVI.XMin,myVI.XMax);
    h1->GetYaxis()->SetRangeUser(myVI.YMin,myVI.YMax);
    h1->Scale(1./h1->Integral(0,myVI.nbins+1));
    return h1;
}

void makePlots(VariableInfo myVI, VariableInfo myVI2, TTree *itreeMC, TTree *itreeData, TTree *itreeDataPartial){
    SetAtlasStyle();
    printf("Loaded files");
    Int_t nmucalc(0), nvtx(0), nvtxSigMUCALC(0), nvtxSigVTX(0), nvtxSigBOTH(0);
    // TString DrawCommand1 = ;
    // TString DrawCommand2= ;
    // TString DrawCommand3= ;
    // itreeMC->Draw(GetDrawCommand(myVI, "hist1"), MCweights*addCut, "egoff");
    // itreeData->Draw(GetDrawCommand(myVI, "hist2"), addCut, "egoff");
    // itreeDataPartial->Draw(GetDrawCommand(myVI2, "hist3"), addCut*CutSB, "egoff");
    // TH1F* h1 = (TH1F*)gDirectory->Get("hist1");
    // TH1F* h2 = (TH1F*)gDirectory->Get("hist2");
    // TH1F* h3 = (TH1F*)gDirectory->Get("hist3");
    TH1F* h1 = GetHistogram(itreeMC, myVI, "hist1", MCweights*addCut, hgMC1);
    TH1F* h2 = GetHistogram(itreeData, myVI, "hist2", addCut, hgData1);
    TH1F* h3 = GetHistogram(itreeDataPartial, myVI2, "hist3", addCut*CutSB, hgData2);

    // h1->Scale(1./h1->Integral(0,myVI.nbins+1));
    // h2->Scale(1./h2->Integral(0,myVI.nbins+1));
    // h3->Scale(1./h3->Integral(0,myVI2.nbins+1));
////////Set the canvas and pads
    TCanvas* c1 = new TCanvas("c1", "c1",0.,0., 800, 600);
    TPad *pad1, *pad2, *pad3;
    pad1 = new TPad("pad1","pad1",0,0.33,1,1); //xlow ylow xup yup
    pad2 = new TPad("pad2","pad2",0,0,1,0.31); //0.3
    pad3 = new TPad("pad3","pad3",0,0,1,1); //0.3
    bool drawResiduals(true);
    if (drawResiduals) {
        pad1->SetMargin(0.16,0.05,0.032,0.09);//left, right, bottom, top
        // pad1->SetMargin(0.12,0.05,0.028,0.09);
        pad1->SetBorderMode(0);
        pad1->SetLogy(myVI.logScale);
        pad2->SetMargin(0.16,0.05,0.38,0.05);
        // pad2->SetMargin(0.12,0.05,0.38,0.06);
        pad2->SetBorderMode(0);
        pad3->SetBorderMode(0);
        pad3->SetMargin(0.16,0.05,0.16,0.05);
        pad3->SetFillStyle(4000);
        pad1->Draw();
        pad2->Draw();
        pad3->Draw();
        pad1->cd();
    }else{
        c1->SetLogy(myVI.logScale);
    }
    if(drawResiduals) h1->GetXaxis()->SetLabelSize(0);
    // if (myVI.logScale){
    //     h1->SetMinimum(600.);
    //     h1->SetMinimum(0.);
    // }
////////Draw the histograms
    h1->Draw("hist");
    h3->Draw("p same");
    h2->Draw("p same");
////////legend settings
    if(drawResiduals) pad3->cd();
    TLegend* leg;
    leg = new TLegend(0.2,0.78,0.4,0.91,NULL,"brNDC");
    if (!(myVI.legHeader).EqualTo("")) leg->SetHeader(myVI.legHeader);
    leg->AddEntry(h1, "MC", "l");
    leg->AddEntry(h2, "Data (New nTuples)", "p");
    leg->AddEntry(h3, "Data (Old nTuples)", "p");
    leg->SetBorderSize(0);  // no border
    leg->SetLineColor(0);
    leg->SetFillColor(0);
    leg->SetTextSize(0.025);
    leg->Draw();
    ATLASLabel(0.6,0.85,"Internal");

////////if draw Residuals draw the lower pad
    TH1F *hres(NULL);
    if (drawResiduals) {
        pad2->cd();
        hres = (TH1F*)h2->Clone("hres");
        hres->Sumw2();
        hres->Divide(h2,h3,1.0,1.0);
        // hres->GetXaxis()->SetRangeUser(xmin, xmax);
        hres->SetMaximum(myVI.pullYMax);   // along          
        hres->SetMinimum(myVI.pullYMin);  //   Y 
        hres->SetMarkerSize(0.7);
        hres->GetXaxis()->SetTitleOffset(1.0); //0.95
        hres->GetXaxis()->SetTitleSize(0.17);
        hres->GetXaxis()->SetLabelSize(0.14); //0.17 0.1
        hres->GetXaxis()->SetTitle(myVI.xtitle);
        hres->GetYaxis()->SetTitleSize(0.12);
        hres->GetYaxis()->SetTitleOffset(0.47); //0.26
        hres->GetYaxis()->SetLabelSize(0.1);//0.17 //0.08
        hres->GetYaxis()->SetNdivisions(4,3,0); //4,5,0

        hres->GetYaxis()->SetTitle("New/Old");
        // hres->GetXaxis()->SetTitle(Xtitle);
        hres->SetMarkerColor(1);
        hres->SetLineColor(1);
        hres->Draw("e0p same");
    }


    Int_t dcaACK(0.), dcaBEL(0.), dcaBGL(0.), total(0.);
    // TString odir = "/afs/cern.ch/user/a/agrummer/www/bmumu2020/SavePlots/IsolationVariables/2020May15/";
    TString odir = "/afs/cern.ch/user/a/agrummer/www/bmumu2020/SavePlots/AllVars/2020Jun4/";
    c1->SaveAs(odir + myVI.SaveName + ".pdf");
    delete c1;
    return 0;
}

void VariableComps(){
    TFile *ifileMC, *ifileData, *ifileDataPartial;
    TString idir = "/eos/home-a/agrummer/BsmumuData/AnalysisNtuples2020/v4/";
    TStopwatch sw;
    sw.Start();
    ifileMC = (TFile *)new TFile(idir+"LASTskim.user.agrummer.mcBsmumu.merged.root", "read");
    ifileData = (TFile *)new TFile(idir+"LASTskim.user.agrummer.Data1516.merged.root", "read");
    ifileDataPartial = (TFile *)new TFile("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/AnalysisNtuples/Bsmumu/data15a16/v3/data1516Bs_BDT2016_v2.root", "read");
    TTree *itreeMC = (TTree*)ifileMC->Get("T_mv");
    TTree *itreeData = (TTree*)ifileData->Get("T_mv");
    TTree *itreeDataPartial = (TTree*)ifileDataPartial->Get("T_mv");
    sw.Stop();
    sw.Print();
    // makePlots(B_iso_7_Chi2_5_LoosePt05, itreeMC, itreeData);
    // makePlots(B_iso_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127, itreeMC, itreeData);
    // makePlots(B_iso_10_noChi2_LooSiHi1Pt05_T0134217728, itreeMC, itreeData);
    // makePlots(B_iso_10_noChi2_LooSiHi1Pt05_T0008388608, itreeMC, itreeData);
VariableInfo IsoArray[8] {
B_iso_7_Chi2_5_LoosePt05,
muP_iso_7_Chi2_5_LoosePt05,
muM_iso_7_Chi2_5_LoosePt05,
B_iso_Ntracks_7_Chi2_5_LoosePt05,
muP_iso_Ntracks_7_Chi2_5_LoosePt05,
muM_iso_Ntracks_7_Chi2_5_LoosePt05,
closeTrkDOCA_3,
closeTrkNtrksChi2,
};
VariableInfo IsoArray2[8] {
B_iso_7_Chi2_5_LoosePt05,
muP_iso_7_chi2_5_LoosePt05,
muM_iso_7_chi2_5_LoosePt05,
B_iso_Ntracks_7_Chi2_5_LoosePt05,
muP_iso_Ntracks_7_chi2_5_LoosePt05,
muM_iso_Ntracks_7_chi2_5_LoosePt05,
closeTrkDOCA,
closeTrkNtrksChi2,
};
// for(int i=0; i<8; i++){
// makePlots(IsoArray[i], IsoArray2[i], itreeMC, itreeData, itreeDataPartial);
// }
// for(int i=0; i<8; i++){
makePlots(IsoArray[0], IsoArray2[0], itreeMC, itreeData, itreeDataPartial);
// }
    }
