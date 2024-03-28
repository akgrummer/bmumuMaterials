#include<TMath.h>
#include "../AnalysisTools/Utils/AtlasStyle/AtlasLabels.C"
#include "../AnalysisTools/Utils/AtlasStyle/AtlasLabels.h"
#include "../AnalysisTools/Utils/AtlasStyle/AtlasUtils.C"
#include "../AnalysisTools/Utils/AtlasStyle/AtlasUtils.h"
#include "../AnalysisTools/Utils/AtlasStyle/AtlasStyle.C"
#include "../AnalysisTools/Utils/AtlasStyle/AtlasStyle.h"
#include "Iso_MultiROCs.h"
#include "getHistoFromTree.C"
#include "atlasLabel.C"
// #include "Iso_ROCs_Module.C"

TH1F* RetrieveHist(TString tmpYear = "",  TString DataType = "", 
                    VariableInfo myVar = Bisolation, Int_t ColorIndex=0, 
                    TString FileDate="", TString Pileup=""){
// TString DirName = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/";
TString DirName = "/eos/home-a/agrummer/BsmumuData/FinalSkim/v4/";
TString ifilename("");
TString tmp_mcName("");
TString runName("");
TCut myCut("");
TCut RunNumberCut("");
TH1F* myHist(NULL);
if (tmpYear.EqualTo("2016")){
    tmp_mcName = "MC16a";
    runName = "2016 Run 302393";
    RunNumberCut = "run_number==302393";
}else if(tmpYear.EqualTo("2017")){
    tmp_mcName = "MC16d";
    runName = "2017 Run 339849";
    RunNumberCut = "run_number==339849";
 }else if(tmpYear.EqualTo("2018")){
    tmp_mcName = "MC16e";
    runName = "2018 Run 358096";
    RunNumberCut = "run_number==358096";
 }
if (DataType.EqualTo("data")) {
        ifilename = DirName + tmpYear+"All/LASTskim_"+tmpYear+"_All_"+FileDate+".root";
        cout<< "ifilename "<< ifilename<<endl;
        myCut = CutAdd;
    }
else if (DataType.EqualTo("mc")) { 
        ifilename = DirName + tmp_mcName+"All/LASTskim_"+tmp_mcName+"_All_"+FileDate+".root";
        cout<< "ifilename "<< ifilename<<endl;
        myCut= CutAdd*RunNumberCut*"PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
        // myCut= CutAdd*RunNumberCut;
    }
    //     if (theYear.Contains("MC")){
    //     legAll->AddEntry(h_chi2_PV_assPV_lowPU, "21<PRIVX_{#mu}<32" ,"l");
    //     legAll->AddEntry(h_chi2_PV_otherPV_mediumPU, "34<PRIVX_{#mu}<43" ,"l");
    //     legAll->AddEntry(h_chi2_PV_nonAss_highPU, "44<PRIVX_{#mu}<55" ,"l");
    //     }
    // else{
    //     legAll->AddEntry(h_chi2_PV_assPV_lowPU, "22.493<PRIVX_{#mu}<29.0" ,"l");
    //     legAll->AddEntry(h_chi2_PV_otherPV_mediumPU, "36.352<PRIVX_{#mu}<43.0" ,"l");
    //     legAll->AddEntry(h_chi2_PV_nonAss_highPU, "45.0<PRIVX_{#mu}<55.0" ,"l");

if (Pileup.EqualTo("lowlow")) {
myCut = myCut*("PRIVX_mu >= 12. && PRIVX_mu <= 22.");
}if (Pileup.EqualTo("low")) {
myCut = myCut*("PRIVX_mu >= 23. && PRIVX_mu <= 33.");
}else if(Pileup.EqualTo("medium")) {
myCut = myCut*("PRIVX_mu >= 34. && PRIVX_mu <= 44.");
}else if(Pileup.EqualTo("high")) {
myCut = myCut*("PRIVX_mu >= 45. && PRIVX_mu <= 55.");
} 

TFile* ifile = new TFile(ifilename);
TTree *myTree = (TTree*)ifile->Get("T_mv");
cout<<tmpYear <<" Tree Entries: "<<myTree->GetEntries()<<endl;
myHist = getHistoFromTree(myTree, myVar, myVar.name, myCut);

myHist->SetMarkerColor(ColorWheel[ColorIndex]);
myHist->SetLineColor(ColorWheel[ColorIndex]);
myHist->SetMarkerStyle(20);
if(DataType.EqualTo("data")) {
myHist->SetMarkerSize(0.9);
}
else{
myHist->SetMarkerSize(0);
}
myHist->SetLineWidth(2);
// myHist->SetLineStyle(ColorIndex+1);
// myHist->GetYaxis()->SetTitle("Bkg. Rejection [%]");
// myHist->GetXaxis()->SetTitle("Sig. Efficiency [%]");
myHist->Scale(1./myHist->Integral(0, myVar.nbins + 1));
myHist->GetYaxis()->SetTitle("a.u.");
return myHist;
}


TH1F* RetrieveHistRun1(TString DataType = "", 
                    VariableInfo myVar = Bisolation, Int_t ColorIndex=0, TString Pileup="") {
TString ifilename("");
TString tmp_mcName("");
TString runName("");
TCut myCut("");
TCut RunNumberCut("");
TString tmpYear("Run1");
TH1F* myHist(NULL);
if (DataType.EqualTo("data")) {
        ifilename = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun1/data/Bsmumu/data12_8TeVBsAllPeriodsUnblinded.root";
        myCut = CutRun1;
    }
else if (DataType.EqualTo("mc")) { 
        ifilename = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun1/mc12/Bsmumu/mc12_8TeV.208426.Pythia8B_AU2_CTEQ6L1_Bs_mu3p5mu3p5.r3549.172133.staco.Bs2mumu_Bs.v12.s1.wTRUTHvarsANDnoMCPcuts.root";
        myCut= CutRun1*"PVWeights";
    }


if (Pileup.EqualTo("lowlow")) {
myCut = myCut*("PRIVX_mu >= 12. && PRIVX_mu <= 22.");
}if (Pileup.EqualTo("low")) {
myCut = myCut*("PRIVX_mu >= 23. && PRIVX_mu <= 33.");
}else if(Pileup.EqualTo("medium")) {
myCut = myCut*("PRIVX_mu >= 34. && PRIVX_mu <= 44.");
}else if(Pileup.EqualTo("high")) {
myCut = myCut*("PRIVX_mu >= 45. && PRIVX_mu <= 55.");
} 
    

TFile* ifile = new TFile(ifilename);
TTree *myTree = (TTree*)ifile->Get("T_mv");
cout<<tmpYear<<" "<< DataType <<" Tree Entries: "<<myTree->GetEntries()<<endl;
myHist = getHistoFromTree(myTree, myVar, myVar.name+tmpYear, myCut);

myHist->SetMarkerColor(ColorWheel[ColorIndex]);
myHist->SetLineColor(ColorWheel[ColorIndex]);
myHist->SetMarkerStyle(20);
if(DataType.EqualTo("data")) {
myHist->SetMarkerSize(0.9);
}
else{
myHist->SetMarkerSize(0);
}
myHist->SetLineWidth(2);
// myHist->SetLineStyle(ColorIndex+1);
// myHist->GetYaxis()->SetTitle("Bkg. Rejection [%]");
// myHist->GetXaxis()->SetTitle("Sig. Efficiency [%]");
myHist->Scale(1./myHist->Integral(0, myVar.nbins + 1));
myHist->GetYaxis()->SetTitle("a.u.");
// ifile->Close(); //apparently this breaks the histo from plotting.
return myHist;
}

void makePlots(TString theYear="", TString DataType ="", 
                TString FileDate = "", TString myPileup=""){
    SetAtlasStyle();

///////////////////
// TString theYear="2018";
// TString DataType = "data";
// TString DataType = "mc";
TString theRunNumber("");
TString mcName("");
if (theYear.EqualTo("2016")){
    theRunNumber = " Run 302393";
    mcName = "MC16a";
}
else if (theYear.EqualTo("2017")){
    theRunNumber = " Run 339849";
    mcName = "MC16d";
}
else if (theYear.EqualTo("2018")){
    theRunNumber = " Run 358096";
    mcName = "MC16e";
}
// B_Iso_TTVA_custom
// B_Iso_all_c5
// B_Iso_all_c6
//
// B_Iso_Ntracks_TTVA_custom
// B_Iso_Ntracks_all_c5
// B_Iso_Ntracks_all_c6
Int_t ColorIndex(0);
ColorIndex = 3;
TH1F* hRun1 = RetrieveHistRun1(DataType, Run1iso, ColorIndex, myPileup);
ColorIndex = 0;
TH1F* h2016data_Default = RetrieveHist(theYear, DataType, Bisolation, ColorIndex, FileDate, myPileup);
ColorIndex = 1;
TH1F* h_TTVA_custom = RetrieveHist(theYear, DataType, B_Iso_TTVA_custom, ColorIndex, FileDate, myPileup);
ColorIndex = 4;
TH1F* h_TTVA_custom_dr = RetrieveHist(theYear, DataType, B_Iso_TTVA_custom_dr, ColorIndex, FileDate, myPileup);
ColorIndex = 2;
TH1F* h_all_c5 = RetrieveHist(theYear, DataType, B_Iso_all_c5, ColorIndex, FileDate, myPileup);
// cout<<"DEBUG: 1"<<endl;

TCanvas* c2 = new TCanvas("c2", "Var Comps",0.,0., 800, 600);
    TPad *pad1, *pad2;
    pad1 = new TPad("pad1","pad1",0,0,1,1); //xlow ylow xup yup
    // pad2 = new TPad("pad2","pad2",0,0,0,0); //0.3
    pad1->SetLogy();
    pad1->SetMargin(0.16,0.05,0.16,0.09);
    pad1->Draw();
    pad1->cd();
    // cout<<"DEBUG: 2"<<endl;
    Double_t ymin;
    Double_t ymax;
    Double_t xmin;
    Double_t xmax;
    if(DataType.EqualTo("data")){
        // h2016data->Draw("e0psame");
        ymin = 1e-5;
        ymax = 5e-1;
        h2016data_Default->SetMaximum(ymax);   // along          
        h2016data_Default->SetMinimum(ymin);  //   Y  
        h2016data_Default->Draw("e0p");
        h_TTVA_custom->Draw("e0psame");
        h_TTVA_custom_dr->Draw("e0psame");
        h_all_c5->Draw("e0psame");
        // cout<<"DEBUG: 2.5"<<endl;
        if (!myPileup.EqualTo("high")){hRun1->Draw("e0psame");}
        // cout<<"DEBUG: 3"<<endl;
    }
    else if(DataType.EqualTo("mc")){
        ymin = 8e-6;
        ymax = 5e0;
        h2016data_Default->SetMaximum(ymax);   // along          
        h2016data_Default->SetMinimum(ymin);  //   Y  
        h2016data_Default->SetMaximum(5.);
        h2016data_Default->Draw("hist e0");
        h_TTVA_custom->Draw("hist e0 same");
        h_TTVA_custom_dr->Draw("hist e0 same");
        h_all_c5->Draw("hist e0 same");
        if (!myPileup.EqualTo("high")){hRun1->Draw("hist e0 same");}
    }
// cout<<"DEBUG: 4"<<endl;

TLegend* leg2(NULL);
// leg2 = new TLegend(1, 0.06, 5, 0.08,NULL,"brNDC");
// leg2 = new TLegend(0.218045, 0.721739, 0.418546, 0.770435,NULL,"brNDC");

// leg2 = new TLegend(0.218045, 0.2, 0.418546, 0.4,NULL,"brNDC");
TString PileupHeader;
if (myPileup.EqualTo("lowlow")) {
    PileupHeader = ", 12. #leq PRIVX_mu #leq 22.";
}if (myPileup.EqualTo("low")) {
    PileupHeader = ", 23. #leq PRIVX_mu #leq 33.";
}else if(myPileup.EqualTo("medium")) {
    PileupHeader = ", 34. #leq PRIVX_mu #leq 44.";
}else if(myPileup.EqualTo("high")) {
    PileupHeader = ", 45. #leq PRIVX_mu #leq 55.";
}

if (DataType.EqualTo("data")) {
    atlasLabel(0.4, 0.47, false, true, 1, true, false, true);
    leg2 = new TLegend(0.42, 0.2, 0.62, 0.43,NULL,"brNDC");
    leg2->SetHeader(theYear + theRunNumber+PileupHeader);
}
else if (DataType.EqualTo("mc")) {
    atlasLabel(0.5, 0.83, false, true, 1, true, false, true);
    leg2 = new TLegend(0.22, 0.67, 0.42, 0.9,NULL,"brNDC");
    leg2->SetHeader(mcName + theRunNumber+PileupHeader);
}
// cout<<"DEBUG: 5"<<endl;
// leg2->SetHeader(mcName);
if(DataType.EqualTo("data")){
if (!myPileup.EqualTo("high")){leg2->AddEntry(hRun1, "Run 1","pe");}
leg2->AddEntry(h2016data_Default, "Default","pe");
leg2->AddEntry(h_TTVA_custom, "Custom TTVA WP","pe");
leg2->AddEntry(h_TTVA_custom_dr, "Custom TTVA WP, #Delta R<1.0","pe");
leg2->AddEntry(h_all_c5, "All Tracks and #chi^{2}_{PV} #leq 5","pe");
}else if(DataType.EqualTo("mc")){
if (!myPileup.EqualTo("high")){leg2->AddEntry(hRun1, "Run 1","l");}
leg2->AddEntry(h2016data_Default, "Default","l");
leg2->AddEntry(h_TTVA_custom, "Custom TTVA WP","l");
leg2->AddEntry(h_TTVA_custom_dr, "Custom TTVA WP, #Delta R<1.0","l");
leg2->AddEntry(h_all_c5, "All Tracks and #chi^{2}_{PV} #leq 5","l");
    }
// cout<<"DEBUG: 6"<<endl;
leg2->SetBorderSize(0);  // no border
leg2->SetLineColor(0);
leg2->SetFillColor(0);
leg2->SetTextSize(0.025);
leg2->Draw();

TString OutdirName = "/afs/cern.ch/user/a/agrummer/www/bmumu/IsoVarROCs/";
// TString Tag = "Tracks_2016";
// TString Tag = theYear;
TString Tag("");
if (DataType.EqualTo("data")) {
Tag = theYear + "TTVA_chi2";
}
else if (DataType.EqualTo("mc")) {
// Tag = mcName + "TTVA_chi2_2019Jun6";
Tag = mcName + "TTVA_chi2";
}
// Tag+="_2019Jun12_chi2_6"
// Tag+="_2019Jun13_chi2_6"
Tag+="_2019July30_";
// Tag+="_lowPU";
Tag+=myPileup;
// Tag+="_medPU";
// Tag+="_highPU";
// Tag+="_2019Jun17";
Tag+=FileDate;
cout<<"DEBUG: 7"<<endl;
TString varDir="BIso";
TString typeDir="";
if (DataType.EqualTo("data")){
    typeDir = "Data";
}else{
    typeDir = "MC";
}
// c2->SaveAs(OutdirName + "Figures/VarComps/VarComp_"+Tag+".pdf");
// c2->SaveAs(OutdirName + "Figures/VarComps2019Jun17/"+FileDate+"/VarComp_"+Tag+".pdf");
// c2->SaveAs(OutdirName + "Figures/VarComps2019Jun27/VarComp_"+Tag+".pdf");
// c2->SaveAs(OutdirName + "Figures/VarComps2019July17/VarComp_"+Tag+".pdf");
// c2->SaveAs(OutdirName + "Figures/VarComps2019July30_PU/VarComp_"+Tag+".pdf");
// c2->SaveAs(OutdirName + "Figures/VarComps2019Sep5_VarBinned/"+varDir+"/"+typeDir+"/VarComp_"+Tag+".pdf");
c2->SaveAs(OutdirName + "Figures/VarComps2019Nov21_VarBinned_v4/"+varDir+"/"+typeDir+"/VarComp_"+Tag+".pdf");
delete c2;
delete hRun1;
delete h2016data_Default;
delete h_TTVA_custom;
delete h_all_c5;
return 0;
}

void Iso_MultiVar_TTVA_v4_PU(){
    TString FileDate = "";
    FileDate = "2019July30";
    TString myPileup = "";
    myPileup = "lowlow";
    makePlots("2018", "data", FileDate, myPileup);
    makePlots("2018", "mc", FileDate, myPileup);
    // makePlots("2016", "data", FileDate, myPileup);
    // makePlots("2016", "mc", FileDate, myPileup);
    myPileup = "low";
    // makePlots("2018", "data", FileDate, myPileup);
    // makePlots("2018", "mc", FileDate, myPileup);
    makePlots("2017", "data", FileDate, myPileup);
    makePlots("2017", "mc", FileDate, myPileup);
    myPileup = "medium";
    makePlots("2017", "data", FileDate, myPileup);
    makePlots("2017", "mc", FileDate, myPileup);
    myPileup = "high";
    makePlots("2017", "data", FileDate, myPileup);
    makePlots("2017", "mc", FileDate, myPileup);
}

