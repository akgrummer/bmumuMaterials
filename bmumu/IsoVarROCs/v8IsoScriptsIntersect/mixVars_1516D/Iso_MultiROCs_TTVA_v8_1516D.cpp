#include<TMath.h>
#include "../../../AnalysisTools/Utils/AtlasStyle/AtlasLabels.C"
#include "../../../AnalysisTools/Utils/AtlasStyle/AtlasLabels.h"
#include "../../../AnalysisTools/Utils/AtlasStyle/AtlasUtils.C"
#include "../../../AnalysisTools/Utils/AtlasStyle/AtlasUtils.h"
#include "../../../AnalysisTools/Utils/AtlasStyle/AtlasStyle.C"
#include "../../../AnalysisTools/Utils/AtlasStyle/AtlasStyle.h"
#include "../Iso_MultiROCs.h"
#include "../getHistoFromTree.C"
#include "../../atlasLabel.C"
// #include "Iso_ROCs_Module.C"
#include "../Iso_ROCs_Module_errors.C"

void makeROCplots(TString theYear = "", TString FileDate = "", TString ExtraCut = "", TString Pileup = ""){
    SetAtlasStyle();
    //this folder was renamed to:
    // /eos/home-a/agrummer/BsmumuData/FinalSkim/v3
// TString DirName = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/";
// TString DirName = "/eos/home-a/agrummer/BsmumuData/FinalSkim/v5/";
// TString DirName = "/eos/home-a/agrummer/BsmumuData/FinalSkim/v6/";
TString DirName = "/eos/home-a/agrummer/BsmumuData/2020nTuples/FinalSkim/v1/";
TString DirName2 = "/eos/home-a/agrummer/BsmumuData/FinalSkim/v6/";


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
// TGraphErrors* grROC_Run1 = Iso_ROCs(EvalTreeSig_Run1, EvalTreeBkg_Run1,
//                               Bisolation, CutAddSig_Run1,
//                               Run1iso, CutAddBkg_Run1,
//                               ColorIndex);
///////2016 trees////////
// TString theYear = "2018";
// TString filenameBkg = DirName + theYear+"All/LASTskim_"+theYear+"_All_2019May30.root";
// TString filenameBkg = DirName + theYear+"All/LASTskim_"+theYear+"_All_2019Jun3.root";
// TString filenameBkg = DirName + theYear+"All/LASTskim_"+theYear+"_All_2019Jun5.root";
// TString filenameBkg = DirName + theYear+"All/LASTskim_"+theYear+"_All_2019Jun6.root";
// TString filenameBkg = DirName + theYear+"All/LASTskim_"+theYear+"_All_2019Jun12.root";//chi2<6 in TTVAs
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
// CutRun1 = PUcut*CutRun1*ExtraCut;
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
//     grROC_Run1 = Iso_ROCs(EvalTreeSig_Run1, EvalTreeBkg_Run1,
//                               Run1iso, CutRun1,
//                               Run1iso, CutRun1,
//                               run1Weight, ColorIndex);
// }
// ifilenameBkg_Run1->Close();
// ifilenameSig_Run1->Close();
Int_t ColorIndex(0);


TString dummyYear="";
TString filenameBkg = DirName + theYear+"All/LASTskim_"+theYear+"_All_"+FileDate+".root";//chi2<6 in TTVAs
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
 // filenameSig = DirName + mcName+"All/LASTskim_"+mcName+"_All_2019Jun5.root";
 // filenameSig = DirName + mcName+"All/LASTskim_"+mcName+"_All_2019Jun6.root";
 // filenameSig = DirName + mcName+"All/LASTskim_"+mcName+"_All_2019Jun6.root";//chi2<6 in TTVAs
 filenameSig = DirName + mcName+"All/LASTskim_"+mcName+"_All_"+FileDate+".root";
TString filenameSig2 = DirName2 + mcName+"All/LASTskim_"+mcName+"_All_2019Dec5.root";
TFile* ifilenameBkg = new TFile(filenameBkg);
TFile* ifilenameSig = new TFile(filenameSig);
TTree *EvalTreeBkg = (TTree*)ifilenameBkg->Get("T_mv");
TTree *EvalTreeSig = (TTree*)ifilenameSig->Get("T_mv");
cout<<"EvalTreeBkg Entries: "<<EvalTreeBkg->GetEntries()<<endl;
cout<<"EvalTreeSig Entries: "<<EvalTreeSig->GetEntries()<<endl;
///////2016 Default////////
TCut Weight_Default = "PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
TCut CutAddSig_Default = CutAdd*ExtraCut*PUcut;
TCut CutAddBkg_Default = CutAdd*ExtraCut*PUcut;
ColorIndex = 2;
TGraphErrors* grROC_1516 = Iso_ROCs(EvalTreeSig, EvalTreeBkg,
                              B_iso_7_Chi2_5_LooSiHi1Pt05, CutAddSig_Default,
                              B_iso_7_Chi2_5_LooSiHi1Pt05, CutAddBkg_Default,
                              Weight_Default, ColorIndex);
TCut Weight_TTVA_loose = "PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
TCut CutAddSig_TTVA_loose = CutAdd*ExtraCut*PUcut;
TCut CutAddBkg_TTVA_loose = CutAdd*ExtraCut*PUcut;
ColorIndex = 0;
TGraphErrors* grROC_asRun1 = Iso_ROCs(EvalTreeSig, EvalTreeBkg,
                              B_iso_7_Chi2_5_LooSiHi1Pt05_T0000000127, CutAddSig_TTVA_loose,
                              B_iso_7_Chi2_5_LooSiHi1Pt05_T0000000127, CutAddBkg_TTVA_loose,
                              Weight_TTVA_loose, ColorIndex);
/////////////
// TCut Weight_Default = "PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
// TCut CutAddSig_Default = CutAdd*ExtraCut*PUcut;
// TCut CutAddBkg_Default = CutAdd*ExtraCut*PUcut;
ColorIndex = 1;
TGraphErrors* grROC_DefaultNEW = Iso_ROCs(EvalTreeSig, EvalTreeBkg,
                              Bisolation, CutAddSig_Default,
                              Bisolation, CutAddBkg_Default,
                              Weight_Default, ColorIndex);
///////////////
TCut Weight_all_c5 = "PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
TCut CutAddSig_all_c5 = CutAdd*ExtraCut*PUcut;
TCut CutAddBkg_all_c5 = CutAdd*ExtraCut*PUcut;
ColorIndex = 5;
TGraphErrors* grROC_all_c5NEW = Iso_ROCs(EvalTreeSig, EvalTreeBkg,
                              B_Iso_all_c5, CutAddSig_all_c5,
                              B_Iso_all_c5, CutAddBkg_all_c5,
                              Weight_all_c5, ColorIndex);
ifilenameBkg->Close();
ifilenameSig->Close();

// TFile* ifilenameBkg2 = new TFile(filenameBkg2);
// TFile* ifilenameSig2 = new TFile(filenameSig2);
// TTree *EvalTreeBkg2 = (TTree*)ifilenameBkg2->Get("T_mv");
// TTree *EvalTreeSig2 = (TTree*)ifilenameSig2->Get("T_mv");
// cout<<"EvalTreeBkg2 Entries: "<<EvalTreeBkg2->GetEntries()<<endl;
// cout<<"EvalTreeSig2 Entries: "<<EvalTreeSig2->GetEntries()<<endl;
// //////////
// TCut Weight_Default2 = "PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
// TCut CutAddSig_Default2 = CutAdd*ExtraCut*PUcut;
// TCut CutAddBkg_Default2 = CutAdd*ExtraCut*PUcut;
// ColorIndex = 3;
// TGraphErrors* grROC_DefaultOLD = Iso_ROCs(EvalTreeSig2, EvalTreeBkg2,
//                               Bisolation, CutAddSig_Default2,
//                               Bisolation, CutAddBkg_Default2,
//                               Weight_Default2, ColorIndex);
// /////////////
// TCut Weight_all_c52 = "PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
// TCut CutAddSig_all_c52 = CutAdd*ExtraCut*PUcut;
// TCut CutAddBkg_all_c52 = CutAdd*ExtraCut*PUcut;
// ColorIndex = 4;
// TGraphErrors* grROC_all_c5OLD = Iso_ROCs(EvalTreeSig2, EvalTreeBkg2,
//                               B_Iso_all_c5, CutAddSig_all_c52,
//                               B_Iso_all_c5, CutAddBkg_all_c52,
//                               Weight_all_c52, ColorIndex);

// ifilenameBkg2->Close();
// ifilenameSig2->Close();

// //new file
// TString filenameBkg_DR_1 = DirName + theYear+"All/LASTskim_"+theYear+"_All_2019July2.root";//chi2<6 in TTVAs
// TString filenameSig_DR_1 = DirName + mcName+"All/LASTskim_"+mcName+"_All_2019July2.root";
// TFile* ifilenameBkg_DR_1 = new TFile(filenameBkg_DR_1);
// TFile* ifilenameSig_DR_1 = new TFile(filenameSig_DR_1);
// TTree *EvalTreeBkg_DR_1 = (TTree*)ifilenameBkg_DR_1->Get("T_mv");
// TTree *EvalTreeSig_DR_1 = (TTree*)ifilenameSig_DR_1->Get("T_mv");
// cout<<"EvalTreeBkg Entries DR_1: "<<EvalTreeBkg_DR_1->GetEntries()<<endl;
// cout<<"EvalTreeSig Entries DR_1: "<<EvalTreeSig_DR_1->GetEntries()<<endl;

// /////// TTVA tight  + chi2SV<=2 +DR<1////////
// TCut Weight_TTVA_custom_dr = "PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
// TCut CutAddSig_TTVA_custom_dr = CutAdd*ExtraCut;
// TCut CutAddBkg_TTVA_custom_dr = CutAdd*ExtraCut;
// ColorIndex = 4;
// TGraphErrors* grROC_TTVA_custom_dr = Iso_ROCs(EvalTreeSig_DR_1, EvalTreeBkg_DR_1,
//                               B_Iso_TTVA_custom, CutAddSig_TTVA_custom_dr,
//                               B_Iso_TTVA_custom, CutAddBkg_TTVA_custom_dr,
//                               Weight_TTVA_custom_dr, ColorIndex);
// ///////all trACK, derivations_chi2<= 5 +DR<1////////
// TCut Weight_all_c5_dr = "PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
// TCut CutAddSig_all_c5_dr = CutAdd*ExtraCut;
// TCut CutAddBkg_all_c5_dr = CutAdd*ExtraCut;
// ColorIndex = 5;
// TGraphErrors* grROC_all_c5_dr = Iso_ROCs(EvalTreeSig_DR_1, EvalTreeBkg_DR_1,
//                               B_Iso_all_c5, CutAddSig_all_c5_dr,
//                               B_Iso_all_c5, CutAddBkg_all_c5_dr,
//                               Weight_all_c5_dr, ColorIndex);
TCanvas* c2 = new TCanvas("c2", "ROC curve",0.,0., 800, 600);
// grROC_Default->Draw("ae3");
// grROC_all_c5->Draw("same e3");
Double_t ymin = 0.;
Double_t ymax = 1.05;
Double_t xmin = 0.;
Double_t xmax = 1.05; 
// grROC_1516
// grROC_asRun1
// grROC_DefaultNEW
// grROC_all_c5NEW
// grROC_DefaultOLD
// grROC_all_c5OLD
grROC_DefaultNEW->GetXaxis()->SetLimits(xmin, xmax);// along X
grROC_DefaultNEW->GetHistogram()->SetMaximum(ymax);   // along          
grROC_DefaultNEW->GetHistogram()->SetMinimum(ymin);  //   Y
// grROC_all_c5OLD->Draw("al2");
// grROC_DefaultOLD->Draw("same l2");
// grROC_all_c5NEW->Draw("same l2");
grROC_DefaultNEW->Draw("al2");
// grROC_asRun1->Draw("same l2");
grROC_1516->Draw("same l2");

atlasLabel(0.2, 0.45, false, true, 1, true, false, true);

TLegend* leg2;

// leg2 = new TLegend(1, 0.06, 5, 0.08,NULL,"brNDC");
// leg2 = new TLegend(0.218045, 0.721739, 0.418546, 0.770435,NULL,"brNDC");
leg2 = new TLegend(0.218045, 0.2, 0.418546, 0.4,NULL,"brNDC");


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

leg2->SetHeader("B Isolation "+PileupHeader+ExtraCut);

// grROC_1516
// grROC_asRun1
// grROC_DefaultNEW
// grROC_all_c5NEW
// grROC_DefaultOLD
// grROC_all_c5OLD

//  As in 2015+2016 new nTuple, Derivation
//  As in 2015+2016 new nTuple, default
//  As in 2015+2016 old nTuple, default
//  As in Run 1, new nTuple, Derivation
//  All trACK, derivations, chi2<5, new nTuple
//  All trACK, derivations, chi2<5, old nTuple

// TString legName1 = mcName + " + "+ theYear + " As in 2015+2016 new nTuple, Derivation";
TString legName1 = mcName + " + "+ theYear + " BCI, derivation";
leg2->AddEntry(grROC_1516, legName1,"l");
// TString legName4 = mcName + " + "+ theYear + " As in 2015+2016 new nTuple, default";
TString legName4 = mcName + " + "+ theYear + " ACH, derivation";
leg2->AddEntry(grROC_DefaultNEW, legName4,"l");
// TString legName3 = mcName + " + "+ theYear + " As in 2015+2016 old nTuple, default";
// leg2->AddEntry(grROC_DefaultOLD, legName3,"l");
// TString legName5 = mcName + " + "+ theYear + " As in Run 1, new nTuple, Derivation";
// leg2->AddEntry(grROC_asRun1, legName5,"l");
// TString legName2 = mcName + " + "+ theYear + " All trACK, derivations, chi2<5, new nTuple";
// leg2->AddEntry(grROC_all_c5NEW, legName2,"l");
// TString legName6 = mcName + " + "+ theYear + " All trACK, derivations, chi2<5, old nTuple";
// leg2->AddEntry(grROC_all_c5OLD, legName6,"l");

leg2->SetBorderSize(0);  // no border
leg2->SetLineColor(0);
leg2->SetFillColor(0);
leg2->SetTextSize(0.025);
leg2->Draw();


// TString ofilenames = "Jun13MuIso_SidebandTrained/BDT1";//train3
TString OutdirName = "/afs/cern.ch/user/a/agrummer/www/bmumu/IsoVarROCs/";
// TString Tag = "TrACK, derivations";
// TString Tag = "TTVA_Chi2"+theYear+"_2019Jun6";
TString Tag = "TTVA_Chi2"+theYear+"_"+FileDate+"_"+Pileup;
TString typeDir="ROC";
TString varDir="BIso";
// c2->SaveAs(OutdirName + "Figures/ROC_2019Jun6/ROC_"+Tag+".pdf");
// c2->SaveAs(OutdirName + "Figures/ROC_2019Jun17/"+FileDate+"/ROC_"+Tag+".pdf");
// c2->SaveAs(OutdirName + "Figures/ROC_2019Jun27/ROC_"+Tag+".pdf");
// c2->SaveAs(OutdirName + "Figures/ROC_2019July17/ROC_"+Tag+ExtraCut+".pdf");
// c2->SaveAs(OutdirName + "Figures/ROC_2019July30/ROC_"+Tag+ExtraCut+".pdf");
// c2->SaveAs(OutdirName + "Figures/ROC_2019Nov21_v7/"+varDir+"/"+typeDir+"/ROC_"+Tag+ExtraCut+".pdf");
// c2->SaveAs(OutdirName + "Figures/ROC_2019Dec5_v7/"+varDir+"/"+typeDir+"/ROC_"+Tag+ExtraCut+".pdf");
c2->SaveAs(OutdirName + "Figures/ROC_2020Feb19_v8_mixVars_1516D/"+varDir+"/"+typeDir+"/ROC_"+Tag+ExtraCut+".pdf");


delete c2;
return 0;
}

void Iso_MultiROCs_TTVA_v8_1516D(){
TString FileDate = ""; //ID hits revised run 1 with IBL included
    // makeROCplots("2016", FileDate);
    // makeROCplots("2017", FileDate);
    // makeROCplots("2018", FileDate);
TString ExtraCut = ""; 
// ExtraCut = "Lxy>0.2"; 
// ExtraCut = "a_2D<0.1"; 
TString Pileup = "";

// FileDate = "2019Jun27"; //ID hits like run 1 (without IBL)
// FileDate = "2019July17"; //ID hits like run 1 (without IBL)
// FileDate = "2019July30"; 
// FileDate = "2019Nov21"; 
// FileDate = "2019Dec5"; 
FileDate = "2020Feb11"; 
    // makeROCplots("2016", FileDate, ExtraCut, Pileup);
    Pileup = "all";
    makeROCplots("2016main", FileDate, ExtraCut, Pileup);
    makeROCplots("2016main303846", FileDate, ExtraCut, Pileup);
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
