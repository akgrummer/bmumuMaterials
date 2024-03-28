#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasLabels.C"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasLabels.h"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasStyle.C"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasStyle.h"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasUtils.C"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasUtils.h"

#include "IsolationPlots.h"
void makePlots(VariableInfo myVI, TTree *itreeMC, TTree *itreeData){
    SetAtlasStyle();
    printf("Loaded files");
    Int_t nmucalc(0), nvtx(0), nvtxSigMUCALC(0), nvtxSigVTX(0), nvtxSigBOTH(0);
    TString DrawCommand1("");
    TString DrawCommand2("");
    DrawCommand1 = myVI.bname + ">>hist1";
    DrawCommand2 = myVI.bname + ">>hist2";
    if (myVI.nbins > 0 ){
        DrawCommand1+=("(");
        DrawCommand1+=myVI.nbins;
        DrawCommand1+=",";
        DrawCommand1+=myVI.binLow;
        DrawCommand1+=",";
        DrawCommand1+=myVI.binHigh;
        DrawCommand1+=")";
        DrawCommand2+=("(");
        DrawCommand2+=myVI.nbins;
        DrawCommand2+=",";
        DrawCommand2+=myVI.binLow;
        DrawCommand2+=",";
        DrawCommand2+=myVI.binHigh;
        DrawCommand2+=")";
    }
    itreeMC->Draw(DrawCommand1, MCweights*addCut, "egoff");
    itreeData->Draw(DrawCommand2, addCut, "egoff");
    TH1F* h1 = (TH1F*)gDirectory->Get("hist1");
    TH1F* h2 = (TH1F*)gDirectory->Get("hist2");
    h1->Scale(1./h1->Integral(0,myVI.nbins+1));
    h2->Scale(1./h2->Integral(0,myVI.nbins+1));
    TCanvas* c1 = new TCanvas("c1", "c1",0.,0., 800, 600);
    c1->SetLogy(myVI.logScale);
    h1->SetLineColor(2);
    h1->SetMarkerColor(4);
    h1->SetFillColorAlpha(2, 0.35);
    h1->SetFillStyle(3254);
    h1->SetMarkerStyle(23);
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
    // if (myVI.logScale){
    //     h1->SetMinimum(600.);
    //     h1->SetMinimum(0.);
    // }
    h1->GetXaxis()->SetRangeUser(myVI.XMin,myVI.XMax);
    h1->GetYaxis()->SetRangeUser(myVI.YMin,myVI.YMax);
    h2->SetLineColor(1);
    h2->SetMarkerColor(1);
    h2->SetMarkerStyle(22);
    h1->Draw("hist");
    h2->Draw("p same");

    TLegend* leg;
    leg = new TLegend(0.3,0.75,0.5,0.9,NULL,"brNDC");
        leg->SetHeader(myVI.legHeader);
        leg->AddEntry(h1, "MC", "l");
        leg->AddEntry(h2, "Data", "p");
    leg->SetBorderSize(0);  // no border
    leg->SetLineColor(0);
    leg->SetFillColor(0);
    leg->SetTextSize(0.025);
    leg->Draw();
    Int_t dcaACK(0.), dcaBEL(0.), dcaBGL(0.), total(0.);
    TString odir = "/afs/cern.ch/user/a/agrummer/www/bmumu2020/SavePlots/IsolationVariables/";
    c1->SaveAs(odir + myVI.SaveName + ".pdf");
    delete c1;
    return 0;
}

void IsolationPlots(){
    TFile *ifileMC, *ifileData;
    TString idir = "/eos/home-a/agrummer/BsmumuData/AnalysisNtuples2020/v4/";
    TStopwatch sw;
    sw.Start();
    ifileMC = (TFile *)new TFile(idir+"LASTskim.user.agrummer.mcBsmumu.merged.root", "read");
    ifileData = (TFile *)new TFile(idir+"LASTskim.user.agrummer.Data1516.merged.root", "read");
    TTree *itreeMC = (TTree*)ifileMC->Get("T_mv");
    TTree *itreeData = (TTree*)ifileData->Get("T_mv");
    sw.Stop();
    sw.Print();
    makePlots(B_iso_7_Chi2_5_LoosePt05, itreeMC, itreeData);
    makePlots(B_iso_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127, itreeMC, itreeData);
    makePlots(B_iso_10_noChi2_LooSiHi1Pt05_T0134217728, itreeMC, itreeData);
    makePlots(B_iso_10_noChi2_LooSiHi1Pt05_T0008388608, itreeMC, itreeData);
VariableInfo IsoArray[26] {muP_iso_7_Chi2_5_LoosePt05,
muP_iso_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127,
muP_iso_10_noChi2_LooSiHi1Pt05_T0134217728,
muP_iso_10_noChi2_LooSiHi1Pt05_T0008388608,
muM_iso_7_Chi2_5_LoosePt05,
muM_iso_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127,
muM_iso_10_noChi2_LooSiHi1Pt05_T0134217728,
muM_iso_10_noChi2_LooSiHi1Pt05_T0008388608,
B_iso_Ntracks_7_Chi2_5_LoosePt05,
B_iso_Ntracks_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127,
B_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0134217728,
B_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0008388608,
muP_iso_Ntracks_7_Chi2_5_LoosePt05,
muP_iso_Ntracks_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127,
muP_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0134217728,
muP_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0008388608,
muM_iso_Ntracks_7_Chi2_5_LoosePt05,
muM_iso_Ntracks_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127,
muM_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0134217728,
muM_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0008388608,
closeTrkDOCA_3,
closeTrkDOCA_T0134217728_LooSiHi1Pt05_f2dc2,
closeTrkDOCA_T0008388608_LooSiHi1Pt05_f2dc2,
closeTrkNtrksChi2,
closeTrkNtrksChi2_T0134217728_LooSiHi1Pt05_f2dc2,
closeTrkNtrksChi2_T0008388608_LooSiHi1Pt05_f2dc2};
for(int i=0; i<26; i++){
makePlots(IsoArray[i], itreeMC, itreeData);
}
    }
