#include<TMath.h>
#include "../../../AnalysisTools/Utils/AtlasStyle/AtlasLabels.C"
#include "../../../AnalysisTools/Utils/AtlasStyle/AtlasLabels.h"
#include "../../../AnalysisTools/Utils/AtlasStyle/AtlasUtils.C"
#include "../../../AnalysisTools/Utils/AtlasStyle/AtlasUtils.h"
#include "../../../AnalysisTools/Utils/AtlasStyle/AtlasStyle.C"
#include "../../../AnalysisTools/Utils/AtlasStyle/AtlasStyle.h"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu/IsoVarROCs/v8IsoScripts/Iso_MultiROCs.h"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu/IsoVarROCs/v8IsoScripts/getHistoFromTree.C"
#include "../../atlasLabel.C"
// #include "Iso_ROCs_Module_Reverse.cpp"
#include "../Iso_ROCs_Module_errors_Reverse.C"

void makeROCplots(TString theYear = "", TString FileDate = "", TString ExtraCut = "", TString Pileup = ""){
    SetAtlasStyle();
    //this folder was renamed to:
    // /eos/home-a/agrummer/BsmumuData/FinalSkim/v3
// TString DirName = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/";
// TString DirName = "/eos/home-a/agrummer/BsmumuData/FinalSkim/v5/";
// TString DirName = "/eos/home-a/agrummer/BsmumuData/FinalSkim/v6/";
TString DirName(""), DirName2(""), DirNameSig(""); 
DirName    = "/eos/home-a/agrummer/BsmumuData/2020nTuples/FinalSkim/v3/"; 
DirNameSig = "/eos/home-a/agrummer/BsmumuData/2020nTuples/FinalSkim/v3/"; 
DirName2   = "/eos/home-a/agrummer/BsmumuData/FinalSkim/v6/";

TString vBDT = "";
///////Run1////////
// TString filenameBkg_Run1 = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun1/data/Bsmumu/data12_8TeVBsAllPeriodsUnblinded.root";
// TString filenameSig_Run1 = DirName + "MC16aAll/LASTskim_MC16a_All_Studies_2019Apr24.root";
// TFile* ifilenameBkg_Run1 = new TFile(filenameBkg_Run1);
// TFile* ifilenameSig_Run1 = new TFile(filenameSig_Run1);
// TTree *EvalTreeBkg_Run1 = (TTree*)ifilenameBkg_Run1->Get("T_mv");
// TTree *EvalTreeSig_Run1 = (TTree*)ifilenameSig_Run1->Get("T_mv");
// cout<<"EvalTreeBkg Entries: "<<EvalTreeBkg_Run1->GetEntries()<<endl;
// cout<<"EvalTreeSig Entries: "<<EvalTreeSig_Run1->GetEntries()<<endl;
// TCut CutAddSig_Run1 = CutAdd*"PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
// TCut CutAddBkg_Run1 = CutSB && "Lxy>0.3 && a_2D<1.0 && DR<1.5 &&BDT_fakeMuon_1>-0.458 && BDT_fakeMuon_2>-0.458 && isCatN3";
// ;
// Int_t ColorIndex = 0;
// TGraph* grROC_Run1 = Iso_ROCs(EvalTreeSig_Run1, EvalTreeBkg_Run1,
//                               Bisolation, CutAddSig_Run1,
//                               Run1iso, CutAddBkg_Run1,
//                               ColorIndex);
///////2016 trees////////
// TString theYear = "2018";
// TString filenameBkg = DirName + theYear+"All/LASTskim_"+theYear+"_All_2019May30.root";
// TString filenameBkg = DirName + theYear+"All/LASTskim_"+theYear+"_All_2019Jun3.root";
// TString filenameBkg = DirName + theYear+"All/LASTskim_"+theYear+"_All_2019Jun6.root";//chi2<2 instead of <1
TCut PUcut = "";
if (Pileup.EqualTo("lowlow")) {
PUcut = PUcut*("PRIVX_mu >= 12. && PRIVX_mu <= 22.");
}if (Pileup.EqualTo("low")) {
PUcut = PUcut*("PRIVX_mu >= 23. && PRIVX_mu <= 33.");
}else if(Pileup.EqualTo("medium")) {
PUcut = PUcut*("PRIVX_mu >= 34. && PRIVX_mu <= 44.");
}else if(Pileup.EqualTo("high")) {
PUcut = PUcut*("PRIVX_mu >= 45. && PRIVX_mu <= 55.");
}else if(Pileup.EqualTo("all")) {
PUcut = PUcut;
} 

// TCut run1Weight;
// // CutRun1
// CutRun1 = CutRun1dummy;
// CutRun1 = CutRun1*ExtraCut*PUcut;
// TString ifilenameRun1;
// TString ifilenameRun1_Bkg = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun1/data/Bsmumu/data12_8TeVBsAllPeriodsUnblinded.root";
// TString ifilenameRun1_Sig = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun1/mc12/Bsmumu/mc12_8TeV.208426.Pythia8B_AU2_CTEQ6L1_Bs_mu3p5mu3p5.r3549.172133.staco.Bs2mumu_Bs.v12.s1.wTRUTHvarsANDnoMCPcuts.root";
// run1Weight = "PVWeights";
// TFile* ifilenameBkg_Run1 = new TFile(ifilenameRun1_Bkg);
// TFile* ifilenameSig_Run1 = new TFile(ifilenameRun1_Sig);
// TTree *EvalTreeBkg_Run1 = (TTree*)ifilenameBkg_Run1->Get("T_mv");
// TTree *EvalTreeSig_Run1 = (TTree*)ifilenameSig_Run1->Get("T_mv");
// cout<<"EvalTreeBkg Run 1 Entries: "<<EvalTreeBkg_Run1->GetEntries()<<endl;
// cout<<"EvalTreeSig Run 1 Entries: "<<EvalTreeSig_Run1->GetEntries()<<endl;
// Int_t ColorIndex = 3;
// TGraphErrors* grROC_Run1;
// if (!Pileup.EqualTo("high")){
//     grROC_Run1 = Iso_ROCs_reverse(EvalTreeSig_Run1, EvalTreeBkg_Run1,
//                               closeTrkNtrks, CutRun1,
//                               closeTrkNtrks, CutRun1,
//                               run1Weight, ColorIndex);
// }
// ifilenameBkg_Run1->Close();
// ifilenameSig_Run1->Close();
Int_t ColorIndex(0);


TString dummyYear="";
TString filenameBkg = DirName + theYear+"All/LASTskim_"+theYear+"_All_"+FileDate+".root";//chi2<2 instead of <1
if (theYear.Contains("2016")){ dummyYear =theYear; theYear = "2016"; }
TString filenameBkg2 = DirName2 + theYear+"All/LASTskim_"+theYear+"_All_2019Dec5.root";//chi2<6 in TTVAs
if (theYear.Contains("2016")){theYear = dummyYear;}
TString filenameSig("");
TString mcName("");
TString runName("");
TCut RunNumberCut("");
if (theYear.EqualTo("2016main")){
 mcName = "MC16a";
 runName = "2016 Run 302393";
 RunNumberCut = "run_number==302393";
}else if (theYear.EqualTo("2016main303846")){
 mcName = "MC16a303846";
 runName = "2016 Run 303846";
 RunNumberCut = "run_number==303846";
}else if(theYear.EqualTo("2017")){
 mcName = "MC16d";
  runName = "2017 Run 339849";
 RunNumberCut = "run_number==339849";
 }else if(theYear.EqualTo("2018")){
    mcName = "MC16e";
  runName = "2018 Run 358096";
 RunNumberCut = "run_number==358096";
 }
 // filenameSig = DirName + mcName+"All/LASTskim_"+mcName+"_All_2019May30.root";
 // filenameSig = DirName + mcName+"All/LASTskim_"+mcName+"_All_2019Jun3.root";
 // filenameSig = DirName + mcName+"All/LASTskim_"+mcName+"_All_2019Jun6.root";//chi2<2 instead of <1
filenameSig = DirNameSig + mcName+"All/LASTskim_"+mcName+"_All_"+FileDate+".root";
TString filenameSig2 = DirName2 + mcName+"All/LASTskim_"+mcName+"_All_2019Dec5.root";
TFile* ifilenameBkg = new TFile(filenameBkg);
TFile* ifilenameSig = new TFile(filenameSig);
TTree *EvalTreeBkg = (TTree*)ifilenameBkg->Get("T_mv");
TTree *EvalTreeSig = (TTree*)ifilenameSig->Get("T_mv");
cout<<"EvalTreeBkg Entries: "<<EvalTreeBkg->GetEntries()<<endl;
cout<<"EvalTreeSig Entries: "<<EvalTreeSig->GetEntries()<<endl;
///////////////////
///////2016 Default////////
TCut Weight_Default = "PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
TCut CutAddSig_Default = CutAdd*ExtraCut*PUcut;
TCut CutAddBkg_Default = CutAdd*ExtraCut*PUcut;
// ColorIndex = 0;
// grROC_1516
// grROC_customApprox
// grROC_customTrkPerigee
// grROC_looseApprox
// grROC_looseTrkPerigee
// closeTrkNtrksChi2_LooSiHi1Pt05_201516
// closeTrkNtrksChi2_LooSiHi1Pt05_corc2cnt_custom
// closeTrkNtrksChi2_LooSiHi1Pt05_f2dc2_custom
// closeTrkNtrksChi2_LooSiHi1Pt05_corc2cnt_loose
// closeTrkNtrksChi2_LooSiHi1Pt05_f2dc2_loose
// TGraph* grROC_1516 = Iso_ROCs_reverse(EvalTreeSig, EvalTreeBkg,
//                               closeTrkNtrksChi2_LooSiHi1Pt05_201516, CutAddSig_Default,
//                               closeTrkNtrksChi2_LooSiHi1Pt05_201516, CutAddBkg_Default,
//                               Weight_Default, ColorIndex);
///////1///////
ColorIndex = 4;
TGraph* grROC_customApprox = Iso_ROCs_reverse(EvalTreeSig, EvalTreeBkg,
                              closeTrkNtrksChi2_LooSiHi1Pt05_corc2cnt_custom, CutAddSig_Default,
                              closeTrkNtrksChi2_LooSiHi1Pt05_corc2cnt_custom, CutAddBkg_Default,
                              Weight_Default, ColorIndex);
///////2///////
ColorIndex = 2;
TGraph* grROC_customTrkPerigee = Iso_ROCs_reverse(EvalTreeSig, EvalTreeBkg,
                              closeTrkNtrksChi2_LooSiHi1Pt05_f2dc2_custom, CutAddSig_Default,
                              closeTrkNtrksChi2_LooSiHi1Pt05_f2dc2_custom, CutAddBkg_Default,
                              Weight_Default, ColorIndex);
///////2////////closeTrkNtrks_TTVA_custom_c2
ColorIndex = 1;
TGraph* grROC_TTVA_custom_c2NEW = Iso_ROCs_reverse(EvalTreeSig, EvalTreeBkg,
                              closeTrkNtrks_TTVA_custom_c2, CutAddSig_Default,
                              closeTrkNtrks_TTVA_custom_c2, CutAddBkg_Default,
                              Weight_Default, ColorIndex);

ifilenameBkg->Close();
ifilenameSig->Close();

// TFile* ifilenameBkg2 = new TFile(filenameBkg2);
// TFile* ifilenameSig2 = new TFile(filenameSig2);
// TTree *EvalTreeBkg2 = (TTree*)ifilenameBkg2->Get("T_mv");
// TTree *EvalTreeSig2 = (TTree*)ifilenameSig2->Get("T_mv");
// cout<<"EvalTreeBkg2 Entries: "<<EvalTreeBkg2->GetEntries()<<endl;
// cout<<"EvalTreeSig2 Entries: "<<EvalTreeSig2->GetEntries()<<endl;

// ColorIndex = 5;
// TGraph* grROC_TTVA_custom_c2OLD = Iso_ROCs_reverse(EvalTreeSig2, EvalTreeBkg2,
//                               closeTrkNtrks_TTVA_custom_c2, CutAddSig_Default,
//                               closeTrkNtrks_TTVA_custom_c2, CutAddBkg_Default,
//                               Weight_Default, ColorIndex);
// ifilenameBkg2->Close();
// ifilenameSig2->Close();

// /////3///////
// ColorIndex = 1;
// TGraph* grROC_looseApprox = Iso_ROCs_reverse(EvalTreeSig, EvalTreeBkg,
//                               closeTrkNtrksChi2_LooSiHi1Pt05_corc2cnt_loose, CutAddSig_Default,
//                               closeTrkNtrksChi2_LooSiHi1Pt05_corc2cnt_loose, CutAddBkg_Default,
//                               Weight_Default, ColorIndex);
// ///////4////////closeTrkNtrks_all_c2
// ColorIndex = 5;
// TGraph* grROC_looseTrkPerigee = Iso_ROCs_reverse(EvalTreeSig, EvalTreeBkg,
//                               closeTrkNtrksChi2_LooSiHi1Pt05_f2dc2_loose, CutAddSig_Default,
//                               closeTrkNtrksChi2_LooSiHi1Pt05_f2dc2_loose, CutAddBkg_Default,
//                               Weight_Default, ColorIndex);


TCanvas* c2 = new TCanvas("c2", "ROC curve",0.,0., 800, 600);
Double_t ymin = 0.;
Double_t ymax = 1.05;
Double_t xmin = 0.;
Double_t xmax = 1.05;
// grROC_1516
// grROC_customApprox
// grROC_customTrkPerigee
// grROC_looseApprox
// grROC_looseTrkPerigee
//
// grROC_customApprox
// grROC_customTrkPerigee
// grROC_TTVA_custom_c2NEW
// grROC_TTVA_custom_c2OLD
grROC_TTVA_custom_c2NEW->GetXaxis()->SetLimits(xmin, xmax);// along X
grROC_TTVA_custom_c2NEW->GetHistogram()->SetMaximum(ymax);   // along          
grROC_TTVA_custom_c2NEW->GetHistogram()->SetMinimum(ymin);  //   
// grROC_TTVA_custom_c2OLD->Draw("al2");
grROC_TTVA_custom_c2NEW->Draw("al2");
// grROC_all_c1->Draw("same l2");
// grROC_all_c2->Draw("same l2");
// grROC_AllTrks_Chi6->Draw("same l");
// grROC_AllTrks_Chi5->Draw("same l");
// grROC_AllTrks_Chi4->Draw("same l");
grROC_customApprox->Draw("same l2");
grROC_customTrkPerigee->Draw("same l2");
// grROC_looseTrkPerigee->Draw("same l2");
// grROC_Run1->Draw("same l2");
// grROC_2017->Draw("same l");
// grROC_2018->Draw("same l");
// if (!Pileup.EqualTo("high")){
//     grROC_Run1->Draw("same l2");
// }
atlasLabel(0.2, 0.42, false, true, 1, true, false, true);

TLegend* leg2;
TString theTracks="";
// leg2 = new TLegend(1, 0.06, 5, 0.08,NULL,"brNDC");
// leg2 = new TLegend(0.218045, 0.721739, 0.418546, 0.770435,NULL,"brNDC");
// leg2 = new TLegend(0.22, 0.2, 0.42, 0.4,NULL,"brNDC");
// leg2 = new TLegend(0.52, 0.55, 0.72, 0.75,NULL,"brNDC");

TString PileupHeader;
if (Pileup.EqualTo("lowlow")) {
    PileupHeader = ", 12. #leq PRIVX_mu #leq 22.";
}if (Pileup.EqualTo("low")) {
    PileupHeader = ", 23. #leq PRIVX_mu #leq 33.";
}else if(Pileup.EqualTo("medium")) {
    PileupHeader = ", 34. #leq PRIVX_mu #leq 44.";
}else if(Pileup.EqualTo("high")) {
    PileupHeader = ", 45. #leq PRIVX_mu #leq 55.";
}else if(Pileup.EqualTo("all")) {
    PileupHeader = " ";
}
leg2 = new TLegend(0.2, 0.2, 0.4, 0.4,NULL,"brNDC");
// leg2->SetHeader("Number of Close Tracks to B SV");
leg2->SetHeader("NcloseTrks "+PileupHeader+ExtraCut);
// leg2->AddEntry(grROC_Run1, "MC16a + Run 1","l");
// leg2->AddEntry(grROC_Run1, "MC16a + 15+16 Dataset","l");
// TString Run("");
// if (!Pileup.EqualTo("high")){
//     leg2->AddEntry(grROC_Run1, "MC12 + Run 1","l");
// }
// grROC_1516
// grROC_customApprox
// grROC_customTrkPerigee
// grROC_looseApprox
// grROC_looseTrkPerigee
//
// grROC_customApprox
// grROC_customTrkPerigee
// grROC_TTVA_custom_c2NEW
// grROC_TTVA_custom_c2OLD
// TString legName1 = mcName + " + "+ runName + " As in 2015+2016";
// leg2->AddEntry(grROC_1516, legName1,"l");
//
//
// Custom TVA old nTuple, from Trks
// Custom TVA new nTuple, from Trks
// Custom TVA Approx., new nTuple, Derviation
// Custom TVA Trk Perigee, new nTuple, derivation

TString legName3 = mcName + " + "+ theYear + " BEL, derivation";
leg2->AddEntry(grROC_customTrkPerigee, legName3,"l");
TString legName2 = mcName + " + "+ theYear + " BFM, derivation";
leg2->AddEntry(grROC_customApprox, legName2,"l");
TString legName1 = mcName + " + "+ theYear + " BFM, from trks";
leg2->AddEntry(grROC_TTVA_custom_c2NEW, legName1,"l");

// TString legName5 = mcName + " + "+ runName + " All Tracks #chi^{2}<6";
// leg2->AddEntry(grROC_AllTrks_Chi6, legName5,"l");
// TString legName6 = mcName + " + "+ runName + " All Tracks #chi^{2}<5";
// leg2->AddEntry(grROC_AllTrks_Chi5, legName6,"l");
// TString legName7 = mcName + " + "+ runName + " All Tracks #chi^{2}<4";
// leg2->AddEntry(grROC_AllTrks_Chi4, legName7,"l");
// leg2->AddEntry(grROC_2017, "MC16d + 2017 Run 339849","l");
// leg2->AddEntry(grROC_2018, "MC16e + 2018 Run 358096","l");
leg2->SetBorderSize(0);  // no border
leg2->SetLineColor(0);
leg2->SetFillColor(0);
leg2->SetTextSize(0.025);
leg2->Draw();


// TString ofilenames = "Jun13MuIso_SidebandTrained/BDT1";//train3
TString OutdirName = "/afs/cern.ch/user/a/agrummer/www/bmumu/IsoVarROCs/";
// TString Tag = "Tracks";
// TString Tag = "TTVA_Chi2"+theYear+"_2019Jun3";
// TString Tag = "NcloseTracks_TTVA"+theYear+"_2019Jun6";
// TString Tag = "NcloseTracks_TTVA"+theYear+"_2019Jun10";
// TString Tag = "NcloseTracks_TTVA"+theYear+"_2019Jun12";
// TString Tag = "NcloseTracks_TTVA"+theYear+"_2019Jun12_2";//jun12_2 made with jun 6 inputs
TString Tag = "NcloseTracks_TTVA"+theYear+"_"+FileDate+"_"+Pileup;
// TString Tag = "NcloseTracks_TTVA"+theYear+"_2019Jun12_chi2_2";
TString typeDir="ROC";
TString varDir="NcloseTracks";
// c2->SaveAs(OutdirName + "Figures/ROC_2019Jun3/ROC_"+Tag+".pdf");
// c2->SaveAs(OutdirName + "Figures/ROC_2019July17/ROC_"+Tag+ExtraCut+".pdf");
// c2->SaveAs(OutdirName + "Figures/ROC_2019July30/ROC_"+Tag+ExtraCut+".pdf");
// c2->SaveAs(OutdirName + "Figures/ROC_2019Nov21_v7/"+varDir+"/"+typeDir+"/ROC_"+Tag+ExtraCut+".pdf");
// c2->SaveAs(OutdirName + "Figures/ROC_2019Dec5_v7/"+varDir+"/"+typeDir+"/ROC_"+Tag+ExtraCut+".pdf");
c2->SaveAs(OutdirName + "Figures/ROC_2020Mar6_v8_mixVars_customD/"+varDir+"/"+typeDir+"/ROC_"+Tag+ExtraCut+".pdf");
// TFile ofile(OutdirName + "RootFiles/ROC_"+Tag+".root", "recreate");
// // grROC_Run1->Write();
// grROC_Default->Write();
// grROC_AllTracks->Write();
// grROC_AllTracks_PVweights->Write();
// // grROC_2017->Write();
// // grROC_2018->Write();

delete c2;
return 0;
}

void NcloseTracks_MultiROCs_TTVA_v8_customD(){
//     // ////TString FileDate = "2019Jun12"; //not good!! included chi2 PV cut
//     TString FileDate = "2019Jun6"; //NcloseTrks chi2SV <=1
// // TString FileDate = "2019Jun17"; //NcloseTrks chi2SV <=2
// // TString FileDate = "2019Jun17_2"; //NcloseTrks chi2SV <=4
//     makeROCplots("2016", FileDate);
//     makeROCplots("2017", FileDate);
//     makeROCplots("2018", FileDate);

TString FileDate = ""; //NcloseTrks chi2SV <=1
TString ExtraCut = ""; 
// ExtraCut = "Lxy>0.2"; 
// ExtraCut = "a_2D<0.1"; 

// FileDate = "2019Jun6"; //NcloseTrks chi2SV <=1
// FileDate = "2019July17"; //NcloseTrks chi2SV <=1
    // makeROCplots("2016", FileDate, ExtraCut, Pileup);
    // makeROCplots("2017", FileDate, ExtraCut, Pileup);
    // makeROCplots("2018", FileDate, ExtraCut, Pileup);

// FileDate = "2019Jun17"; //NcloseTrks chi2SV <=2
//     makeROCplots("2016", FileDate);
//     makeROCplots("2017", FileDate);
//     makeROCplots("2018", FileDate);

// FileDate = "2019Jun17_2"; //NcloseTrks chi2SV <=4
//     makeROCplots("2016", FileDate);
//     makeROCplots("2017", FileDate);
//     makeROCplots("2018", FileDate);
TString Pileup;
// FileDate = "2019July30"; 
// FileDate = "2019Nov21"; 
// FileDate = "2019Dec5"; 
FileDate = "2020Feb11"; 
    Pileup = "all";
    makeROCplots("2016main", FileDate, ExtraCut, Pileup);
    // makeROCplots("2016main303846", FileDate, ExtraCut, Pileup);
    makeROCplots("2017", FileDate, ExtraCut, Pileup);
    makeROCplots("2018", FileDate, ExtraCut, Pileup);
    Pileup = "lowlow";
    makeROCplots("2018", FileDate, ExtraCut, Pileup);
    Pileup = "low";
    makeROCplots("2017", FileDate, ExtraCut, Pileup);
    // makeROCplots("2018", FileDate, ExtraCut, Pileup);
    Pileup = "medium";
    makeROCplots("2017", FileDate, ExtraCut, Pileup);
    Pileup = "high";
    makeROCplots("2017", FileDate, ExtraCut, Pileup);

    }
