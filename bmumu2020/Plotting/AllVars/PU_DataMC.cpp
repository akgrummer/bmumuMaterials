#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasLabels.C"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasLabels.h"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasStyle.C"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasStyle.h"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasUtils.C"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasUtils.h"

#include "AllVars.h"

TString GetDrawCommand(VariableInfo myVI, TString histName){
TString DrawCommand("");
// cout<<"Drawing: "<< myVI.bname<<endl;
DrawCommand = myVI.bname + ">>"+histName;
if (myVI.xtitle.Contains("GeV")){
    DrawCommand = myVI.bname + "/1000.0>>"+histName;
}
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
    h1->SetLineStyle(hg.theLineStyle);
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
        yAxisTitle+= Form("%.6f", BinWidth);
    }
    h1->GetYaxis()->SetTitle(yAxisTitle);
    h1->GetXaxis()->SetTitle(myVI.xtitle);
    h1->Scale(1./h1->Integral(0,myVI.nbins+1));
    return h1;
}

void makePlots(VariableInfo myVI, VariableInfo myVI2, CompParameters iCompParam){
    printf("Loaded files\n");
    Int_t nmucalc(0), nvtx(0), nvtxSigMUCALC(0), nvtxSigVTX(0), nvtxSigBOTH(0);
    // TH1F* h1 = GetHistogram(itreeMC, myVI, "hist1", MCweights*addCut, hgMC1);
    TH1F* h1 = GetHistogram(iCompParam.tree1, myVI, "hist1", iCompParam.cut1, iCompParam.hg1);
    TH1F* h2 = GetHistogram(iCompParam.tree2, myVI2, "hist2", iCompParam.cut2, iCompParam.hg2);
////////Set the canvas and pads
    TCanvas* c1 = new TCanvas("c1", "c1",0.,0., 800, 600);
    TPad *pad1, *pad2, *pad3;
    pad1 = new TPad("pad1","pad1",0,0.33,1,1); //xlow ylow xup yup
    pad2 = new TPad("pad2","pad2",0,0,1,0.31); //0.3
    pad3 = new TPad("pad3","pad3",0,0,1,1); //0.3
    bool drawResiduals(true);
    if (iCompParam.onlyMC) drawResiduals = false;
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
    if(drawResiduals) h2->GetXaxis()->SetLabelSize(0);
    // if (myVI.logScale){
    //     h1->SetMinimum(600.);
    //     h1->SetMinimum(0.);
    // }
////////Draw the histograms
    // h1->Draw("hist");
    // set the range using the same VI for both histograms
    h1->GetXaxis()->SetRangeUser(myVI.XMin,myVI.XMax);
    h1->GetYaxis()->SetRangeUser(myVI.YMin,myVI.YMax);
    h2->GetXaxis()->SetRangeUser(myVI.XMin,myVI.XMax);
    h2->GetYaxis()->SetRangeUser(myVI.YMin,myVI.YMax);
    h2->Draw(iCompParam.DrawOpt2);
    if (!iCompParam.onlyMC) h1->Draw(iCompParam.DrawOpt1+" same");
////////legend settings
    LegAndLabelPositions llPos = myVI.legLabPos;
    if(drawResiduals) pad3->cd();
    TLegend* leg;
    if (iCompParam.plotPositions.EqualTo("opt1")){
        leg = new TLegend(llPos.xLowData,llPos.yLowData,llPos.xHighData,llPos.yHighData,NULL,"brNDC");}
    if (iCompParam.plotPositions.EqualTo("opt2")){
        leg = new TLegend(llPos.xLowMC,llPos.yLowMC,llPos.xHighMC,llPos.yHighMC,NULL,"brNDC");}
    if (iCompParam.plotPositions.EqualTo("opt3")){
        leg = new TLegend(llPos.xLowbbmumuX,llPos.yLowbbmumuX,llPos.xHighbbmumuX,llPos.yHighbbmumuX,NULL,"brNDC");}
    if (!(myVI.legHeader).EqualTo("")) leg->SetHeader(myVI.legHeader);
    // leg->AddEntry(h1, "MC", "l");
    if (!iCompParam.onlyMC) leg->AddEntry(h1, iCompParam.LegText1, iCompParam.LegOpt1);
    leg->AddEntry(h2, iCompParam.LegText2, iCompParam.LegOpt2);
    leg->SetBorderSize(0);  // no border
    leg->SetLineColor(0);
    leg->SetFillColor(0);
    leg->SetTextSize(0.025);
    leg->Draw();
    if (iCompParam.plotPositions.EqualTo("opt1")) ATLASLabel(llPos.xLabelData,llPos.yLabelData,"Internal");
    if (iCompParam.plotPositions.EqualTo("opt2")) ATLASLabel(llPos.xLabelMC,llPos.yLabelMC,"Internal");
    if (iCompParam.plotPositions.EqualTo("opt3")) ATLASLabel(llPos.xLabelbbmumuX,llPos.yLabelbbmumuX,"Internal");

////////if draw Residuals draw the lower pad
    TH1F *hres(NULL);
    TLine *myLine;
    if (drawResiduals) {
        pad2->cd();
        hres = (TH1F*)h1->Clone("hres");
        // hres->Sumw2(); //this is already present
        hres->Divide(h1,h2,1.0,1.0);
        // hres->GetXaxis()->SetRangeUser(xmin, xmax);
        // hres->SetMaximum(myVI.pullYMax);   // along          
        // hres->SetMinimum(myVI.pullYMin);  //   Y 
        if (iCompParam.plotPositions.EqualTo("opt1")) hres->GetYaxis()->SetRangeUser(myVI.pullLimits.pullYMinData, myVI.pullLimits.pullYMaxData);
        if (iCompParam.plotPositions.EqualTo("opt2")) hres->GetYaxis()->SetRangeUser(myVI.pullLimits.pullYMinMC, myVI.pullLimits.pullYMaxMC);
        if (iCompParam.plotPositions.EqualTo("opt3")) hres->GetYaxis()->SetRangeUser(myVI.pullLimits.pullYMinbbmumuX, myVI.pullLimits.pullYMaxbbmumuX);
        hres->SetMarkerSize(0.7);
        hres->SetLineStyle(1);
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
        myLine  = new TLine(myVI.XMin, 1., myVI.XMax, 1.);
        // myLine  = new TLine(pad2->GetUxmin(), 1., pad2->GetUxmax(), 1.);
        myLine->SetLineStyle(1);
        myLine->SetLineWidth(1);
        myLine->SetLineColorAlpha(600+1, 0.5);
        myLine->Draw();
    }


    Int_t dcaACK(0.), dcaBEL(0.), dcaBGL(0.), total(0.);
    // TString odir = "/afs/cern.ch/user/a/agrummer/www/bmumu2020/SavePlots/IsolationVariables/2020May15/";
    // TString odir = "/afs/cern.ch/user/a/agrummer/www/bmumu2020/SavePlots/AllVars/NewOldnTuples/2020Jun4/";
    // TString odir = "/afs/cern.ch/user/a/agrummer/www/bmumu2020/SavePlots/AllVars/NewOldnTuples/2020Jun12/";
    // TString odir = "/afs/cern.ch/user/a/agrummer/www/bmumu2020/SavePlots/AllVars/2020July3/";
    // TString odir = "/afs/cern.ch/user/a/agrummer/www/bmumu2020/SavePlots/AllVars/2020July16/woNPVweights/";
    // TString odir = "/afs/cern.ch/user/a/agrummer/www/bmumu2020/SavePlots/AllVars/2020July16/NPVweights/";
    TString odir = "/afs/cern.ch/user/a/agrummer/www/bmumu2020/SavePlots/AllVars/2020July31/NPVweights/";
    // c1->SaveAs(odir + myVI.SaveName + "noweights4.pdf");

    if (iCompParam.onlyMC) c1->SaveAs(odir + myVI2.SaveName + iCompParam.saveTag + ".pdf");
    else c1->SaveAs(odir + myVI.SaveName + iCompParam.saveTag + ".pdf");
    delete c1;
    return 0;
}

void PU_DataMC(){
    SetAtlasStyle();
    TFile *ifileMC, *ifileMCPartial, *ifileData, *ifileDataPartial, *ifilebbmumuX, *ifilebbmumuXpartial;
    TTree *itreeMC, *itreeMCPartial, *itreeData, *itreeDataPartial, *itreebbmumuX, *itreebbmumuXpartial;
    TString idir = "/eos/home-a/agrummer/BsmumuData/AnalysisNtuples2020/v4/";
    TString idirPartial = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/AnalysisNtuples/";
    TStopwatch sw;
    sw.Start();

    // ifileMC = (TFile *)new TFile(idir+"LASTskim.user.agrummer.mcBsmumu.merged.2.root", "read");
    ifileMC = (TFile *)new TFile(idir+"LASTskim.user.agrummer.mcBsmumu.merged.2.NPVweight.root", "read");
    // ifileMC = (TFile *)new TFile("/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/AnalysisNtuples2020/v4/LASTskim.user.agrummer.mcBsmumu.merged.SplitSet1.root", "read");
    itreeMC = (TTree*)ifileMC->Get("T_mv");
    // ifileData = (TFile *)new TFile(idir+"LASTskim.user.agrummer.Data1516.merged.root", "read");
    ifileData = (TFile *)new TFile(idir+"LASTskim.user.agrummer.Data1516.merged.2.root", "read");
    // ifileData = (TFile *)new TFile("/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/AnalysisNtuples2020/v4/LASTskim.user.agrummer.Data1516.merged.SplitSet1.root", "read");
    itreeData = (TTree*)ifileData->Get("T_mv");
    // ifilebbmumuX = (TFile *)new TFile(idir+"LASTskim.user.agrummer.bbmumuX.merged.root", "read");
    // itreebbmumuX = (TTree*)ifilebbmumuX->Get("T_mv");
    sw.Stop();
    sw.Print();
// partial run 2 MC signal:
    // /eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/AnalysisNtuples/Bsmumu/mc16a/v3/LASTskim.mc16Bs_BDT2016_v2.root
// partial run 2 Data sidebands:
    // /eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/AnalysisNtuples/Bsmumu/data15a16/v3/data1516Bs_BDT2016_v2.root
// partial run 2 bbmumuX:
    // /eos/home-a/agrummer/BsmumuData/partialRun2/LastSkimGBR4_Mar26/LASTskim.bbmumuX2Bsmumu_combinatorial_GBRweight.root
    // or better, Iskander put it here:
     // /eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/AnalysisNtuples/bbmumuXBs/v2/LASTskim.bbmumuX2Bsmumu_combinatorial_testweight.root
// new run 2 MC signal:
    // /eos/home-a/agrummer/BsmumuData/AnalysisNtuples2020/v4/LASTskim.user.agrummer.mcBsmumu.merged.root
// partial run 2 Data sidebands:
    // /eos/home-a/agrummer/BsmumuData/AnalysisNtuples2020/v4/LASTskim.user.agrummer.Data1516.merged.root
// partial run 2 bbmumuX:
    // /eos/home-a/agrummer/BsmumuData/AnalysisNtuples2020/v4/LASTskim.user.agrummer.bbmumuX.merged.root

    // makePlots(B_iso_7_Chi2_5_LoosePt05, itreeMC, itreeData);
    // makePlots(B_iso_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127, itreeMC, itreeData);
    // makePlots(B_iso_10_noChi2_LooSiHi1Pt05_T0134217728, itreeMC, itreeData);
    // makePlots(B_iso_10_noChi2_LooSiHi1Pt05_T0008388608, itreeMC, itreeData);

CompParameters cpDataMC = {itreeData, addCut, hgData1, "Sideband Data", "p", "p",
                      itreeMC, addCut*MCweights, hgMC3, "Signal MC", "l", "hist",
                      // "opt1", "7_round"};
                      "opt1", "", false};
CompParameters cpMCnoWeights = {itreeData, addCut, hgData1, "Sideband Data", "p", "p",
                      itreeMC, addCut, hgMC3, "Signal MC", "l", "hist",
                      // "opt1", "noweights7_round"};
                      "opt1", "", true};

CompParameters setCP;
setCP = cpDataMC;
// setCP = cpDataMCnoWeights;

VariableInfo MCweightsArray[10] {
varMCweightsAll,
varMCweights,
varPVWeights,
varMuon1_reco_eff_sf,
varMuon2_reco_eff_sf,
varMuon1_trigger_sf,
varMuon2_trigger_sf,
varCombWeights,
NPVweight,
varMCweightsAllnpv
};
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
// makePlots(Npv, Npv, setCP);
// makePlots(PRIVX_mu, PRIVX_mu, setCP);
// makePlots(PRIVX_mu, PRIVX_mu, cpDataMCnoWeights);
// makePlots(PRIVX_mu, PRIVX_mu_round, setCP);
// makePlots(PRIVX_mu, PRIVX_mu_round, cpDataMCnoWeights);
///////////////
///////////////
// for(int i=0; i<42; i++){     
//     makePlots(AllVarsArray[i], AllVarsArray[i], setCP);
// }
// for(int i=0; i<8; i++){     
//     makePlots(IsoArray[i], IsoArray[i], setCP);
// }
// for(int i=0; i<8; i++){     
//     makePlots(MCweightsArray[i], MCweightsArray[i], cpMCnoWeights);
// }
makePlots(NPVweightdata, NPVweight, cpMCnoWeights);
makePlots(varMCweightsAll, varMCweightsAll, cpMCnoWeights);
makePlots(varMCweightsAll, varMCweightsAllnpv, cpMCnoWeights);

}
