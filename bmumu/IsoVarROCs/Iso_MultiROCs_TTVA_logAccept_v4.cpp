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
// #include "Iso_logAccept_ROCs_Module.C"
#include "Iso_logAccept_ROCs_errors.C"

void makeROCplots(TString theYear = "", TString FileDate = "", TString ExtraCut = "", TString Pileup = ""){
    SetAtlasStyle();
    //this folder was renamed to:
    // /eos/home-a/agrummer/BsmumuData/FinalSkim/v3
// TString DirName = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/";
TString DirName = "/eos/home-a/agrummer/BsmumuData/FinalSkim/v4/";


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
// TGraphErrors* grROC_Run1 = Iso_logAccept_ROCs(EvalTreeSig_Run1, EvalTreeBkg_Run1,
//                               Bisolation, CutAddSig_Run1,
//                               Run1iso, CutAddBkg_Run1,
//                               ColorIndex);
///////2016 trees////////
// TString theYear = "2018";
// TString filenameBkg_2016 = DirName + theYear+"All/LASTskim_"+theYear+"_All_2019May30.root";
// TString filenameBkg_2016 = DirName + theYear+"All/LASTskim_"+theYear+"_All_2019Jun3.root";
// TString filenameBkg_2016 = DirName + theYear+"All/LASTskim_"+theYear+"_All_2019Jun6.root";
TCut PUcut = "";
if (Pileup.EqualTo("lowlow")) {
PUcut = PUcut*("PRIVX_mu >= 12. && PRIVX_mu <= 22.");
}if (Pileup.EqualTo("low")) {
PUcut = PUcut*("PRIVX_mu >= 23. && PRIVX_mu <= 33.");
}else if(Pileup.EqualTo("medium")) {
PUcut = PUcut*("PRIVX_mu >= 34. && PRIVX_mu <= 44.");
}else if(Pileup.EqualTo("high")) {
PUcut = PUcut*("PRIVX_mu >= 45. && PRIVX_mu <= 55.");
} 

TCut run1Weight;
// CutRun1
CutRun1 = CutRun1dummy;
CutRun1 = CutRun1*ExtraCut*PUcut;
TString ifilenameRun1;
TString ifilenameRun1_Bkg = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun1/data/Bsmumu/data12_8TeVBsAllPeriodsUnblinded.root";
TString ifilenameRun1_Sig = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun1/mc12/Bsmumu/mc12_8TeV.208426.Pythia8B_AU2_CTEQ6L1_Bs_mu3p5mu3p5.r3549.172133.staco.Bs2mumu_Bs.v12.s1.wTRUTHvarsANDnoMCPcuts.root";
run1Weight = "PVWeights";
TFile* ifilenameBkg_Run1 = new TFile(ifilenameRun1_Bkg);
TFile* ifilenameSig_Run1 = new TFile(ifilenameRun1_Sig);
TTree *EvalTreeBkg_Run1 = (TTree*)ifilenameBkg_Run1->Get("T_mv");
TTree *EvalTreeSig_Run1 = (TTree*)ifilenameSig_Run1->Get("T_mv");
cout<<"EvalTreeBkg Run 1 Entries: "<<EvalTreeBkg_Run1->GetEntries()<<endl;
cout<<"EvalTreeSig Run 1 Entries: "<<EvalTreeSig_Run1->GetEntries()<<endl;
Int_t ColorIndex = 3;
TGraphErrors* grROC_Run1;
if (!Pileup.EqualTo("high")){
    grROC_Run1 = Iso_logAccept_ROCs(EvalTreeSig_Run1, EvalTreeBkg_Run1,
                              Run1iso, CutRun1,
                              Run1iso, CutRun1,
                              run1Weight, ColorIndex);
}
ifilenameBkg_Run1->Close();
ifilenameSig_Run1->Close();

TString filenameBkg_2016 = DirName + theYear+"All/LASTskim_"+theYear+"_All_"+FileDate+".root";
TString filenameSig_2016("");
TString mcName("");
TString runName("");
TCut RunNumberCut("");
if (theYear.EqualTo("2016")){
 mcName = "MC16a";
 runName = "2016 Run 302393";
 RunNumberCut = "run_number==302393";
 // filenameSig_2016 = DirName + mcName+"All/LASTskim_"+mcName+"_All_2019Jun5.root";
 // filenameSig_2016 = DirName + mcName+"All/LASTskim_"+mcName+"_All_2019Jun6.root";
}else if(theYear.EqualTo("2017")){
 mcName = "MC16d";
  runName = "2017 Run 339849";
 RunNumberCut = "run_number==339849";
 // filenameSig_2016 = DirName + mcName+"All/LASTskim_"+mcName+"_All_2019Jun3.root";
 // filenameSig_2016 = DirName + mcName+"All/LASTskim_"+mcName+"_All_2019Jun6.root";
 }else if(theYear.EqualTo("2018")){
    mcName = "MC16e";
  runName = "2018 Run 358096";
 RunNumberCut = "run_number==358096";
 // filenameSig_2016 = DirName + mcName+"All/LASTskim_"+mcName+"_All_2019Jun3.root";
 // filenameSig_2016 = DirName + mcName+"All/LASTskim_"+mcName+"_All_2019Jun6.root";
 }
filenameSig_2016 = DirName + mcName+"All/LASTskim_"+mcName+"_All_"+FileDate+".root";
 // filenameSig_2016 = DirName + mcName+"All/LASTskim_"+mcName+"_All_2019May30.root";
TFile* ifilenameBkg_2016 = new TFile(filenameBkg_2016);
TFile* ifilenameSig_2016 = new TFile(filenameSig_2016);
TTree *EvalTreeBkg_2016 = (TTree*)ifilenameBkg_2016->Get("T_mv");
TTree *EvalTreeSig_2016 = (TTree*)ifilenameSig_2016->Get("T_mv");
cout<<"EvalTreeBkg Entries: "<<EvalTreeBkg_2016->GetEntries()<<endl;
cout<<"EvalTreeSig Entries: "<<EvalTreeSig_2016->GetEntries()<<endl;
///////////////////
///////2016 Default////////
TCut Weight_2016_Default = "PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
TCut CutAddSig_2016_Default = CutAdd*ExtraCut*PUcut;
TCut CutAddBkg_2016_Default = CutAdd*ExtraCut*PUcut;
ColorIndex = 0;
TGraphErrors* grROC_2016_Default = Iso_logAccept_ROCs(EvalTreeSig_2016, EvalTreeBkg_2016,
                              Bisolation, CutAddSig_2016_Default,
                              Bisolation, CutAddBkg_2016_Default,
                              Weight_2016_Default, ColorIndex);
/////// TTVA tight  + chi2SV<=2////////
TCut Weight_2016_TTVA_custom = "PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
TCut CutAddSig_2016_TTVA_custom = CutAdd*ExtraCut*PUcut;
TCut CutAddBkg_2016_TTVA_custom = CutAdd*ExtraCut*PUcut;
ColorIndex = 1;
TGraphErrors* grROC_2016_TTVA_custom = Iso_logAccept_ROCs(EvalTreeSig_2016, EvalTreeBkg_2016,
                              B_Iso_TTVA_custom, CutAddSig_2016_TTVA_custom,
                              B_Iso_TTVA_custom, CutAddBkg_2016_TTVA_custom,
                              Weight_2016_TTVA_custom, ColorIndex);
/////// TTVA tight  + chi2SV<=2////////
TCut Weight_2016_TTVA_custom_dr = "PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
TCut CutAddSig_2016_TTVA_custom_dr = CutAdd*ExtraCut*PUcut;
TCut CutAddBkg_2016_TTVA_custom_dr = CutAdd*ExtraCut*PUcut;
ColorIndex = 4;
TGraphErrors* grROC_2016_TTVA_custom_dr = Iso_logAccept_ROCs(EvalTreeSig_2016, EvalTreeBkg_2016,
                              B_Iso_TTVA_custom_dr, CutAddSig_2016_TTVA_custom_dr,
                              B_Iso_TTVA_custom_dr, CutAddBkg_2016_TTVA_custom_dr,
                              Weight_2016_TTVA_custom_dr, ColorIndex);
///////all tracks_chi2<= 5////////
TCut Weight_2016_all_c5 = "PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
TCut CutAddSig_2016_all_c5 = CutAdd*ExtraCut*PUcut;
TCut CutAddBkg_2016_all_c5 = CutAdd*ExtraCut*PUcut;
ColorIndex = 2;
TGraphErrors* grROC_2016_all_c5 = Iso_logAccept_ROCs(EvalTreeSig_2016, EvalTreeBkg_2016,
                              B_Iso_all_c5, CutAddSig_2016_all_c5,
                              B_Iso_all_c5, CutAddBkg_2016_all_c5,
                              Weight_2016_all_c5, ColorIndex);
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
// TCut Weight_2016_TTVA_custom_dr = "PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
// TCut CutAddSig_2016_TTVA_custom_dr = CutAdd*ExtraCut;
// TCut CutAddBkg_2016_TTVA_custom_dr = CutAdd*ExtraCut;
// ColorIndex = 4;
// TGraphErrors* grROC_2016_TTVA_custom_dr = Iso_logAccept_ROCs(EvalTreeSig_DR_1, EvalTreeBkg_DR_1,
//                               B_Iso_TTVA_custom, CutAddSig_2016_TTVA_custom_dr,
//                               B_Iso_TTVA_custom, CutAddBkg_2016_TTVA_custom_dr,
//                               Weight_2016_TTVA_custom_dr, ColorIndex);
// ///////all tracks_chi2<= 5 +DR<1////////
// TCut Weight_2016_all_c5_dr = "PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
// TCut CutAddSig_2016_all_c5_dr = CutAdd*ExtraCut;
// TCut CutAddBkg_2016_all_c5_dr = CutAdd*ExtraCut;
// ColorIndex = 5;
// TGraphErrors* grROC_2016_all_c5_dr = Iso_logAccept_ROCs(EvalTreeSig_DR_1, EvalTreeBkg_DR_1,
//                               B_Iso_all_c5, CutAddSig_2016_all_c5_dr,
//                               B_Iso_all_c5, CutAddBkg_2016_all_c5_dr,
//                               Weight_2016_all_c5_dr, ColorIndex);



TCanvas* c2 = new TCanvas("c2", "ROC curve",0.,0., 800, 600);
c2->SetLogy(1);
// grROC_2016_all_c5->Draw("al");
// grROC_2016_TTVA_custom->Draw("same l");
// grROC_2016_Default->Draw("same l");
Double_t ymin = 1e-3;
Double_t ymax = 5e-1;
Double_t xmin = 0;
Double_t xmax = 0.8;
grROC_2016_all_c5->GetXaxis()->SetLimits(xmin, xmax);// along X
grROC_2016_all_c5->GetHistogram()->SetMaximum(ymax);   // along          
grROC_2016_all_c5->GetHistogram()->SetMinimum(ymin);  //   YgrROC_TTVA_custom_c1->Draw("al2");
grROC_2016_all_c5->Draw("al2");
grROC_2016_Default->Draw("same l2");
grROC_2016_TTVA_custom->Draw("same l2");
grROC_2016_TTVA_custom_dr->Draw("same l2");
// grROC_Run1->Draw("same l2");
// grROC_2016_TTVA_custom_dr->Draw("same l2");
// grROC_2016_all_c5_dr->Draw("same l2");
// grROC_2017->Draw("same l");
// grROC_2018->Draw("same l");
if (!Pileup.EqualTo("high")){
    grROC_Run1->Draw("same l2");
}
atlasLabel(0.5, 0.45, false, true, 1, true, false, true);

TLegend* leg2;
TString theIDHits="";
// if (FileDate.EqualTo("2019May30")){
//     theIDHits = " ID Hits like Run 1";
// }
// if (FileDate.EqualTo("2019Jun6")){
//     theIDHits = " ID Hits with IBL";
// }
// if (FileDate.EqualTo("2019Jun12")){
//     theIDHits = " ID Hits with IBL + #chi^{2}<6";
// }
// if (FileDate.EqualTo("2019Jun17")){
//     theIDHits = " isTightPrimary";
// }
// if (FileDate.EqualTo("2019Jun17_2")){
//     theIDHits = " isTightPrimary + #chi^{2}<6";
// }

// leg2 = new TLegend(1, 0.06, 5, 0.08,NULL,"brNDC");
// leg2 = new TLegend(0.218045, 0.721739, 0.418546, 0.770435,NULL,"brNDC");

TString PileupHeader;
if (Pileup.EqualTo("lowlow")) {
    PileupHeader = ", 12. #leq PRIVX_mu #leq 22.";
}if (Pileup.EqualTo("low")) {
    PileupHeader = ", 23. #leq PRIVX_mu #leq 33.";
}else if(Pileup.EqualTo("medium")) {
    PileupHeader = ", 34. #leq PRIVX_mu #leq 44.";
}else if(Pileup.EqualTo("high")) {
    PileupHeader = ", 45. #leq PRIVX_mu #leq 55.";
}
leg2 = new TLegend(0.42, 0.2, 0.62, 0.4,NULL,"brNDC");
leg2->SetHeader("B Isolation "+PileupHeader+ExtraCut);
// leg2->AddEntry(grROC_Run1, "MC16a + Run 1","l");
// leg2->AddEntry(grROC_Run1, "MC16a + 15+16 Dataset","l");
// TString Run("");

TString legName1 = mcName + " + "+ runName + " Default";
leg2->AddEntry(grROC_2016_Default, legName1,"l");
TString legName2 = mcName + " + "+ runName + " Custom TTVA WP";
leg2->AddEntry(grROC_2016_TTVA_custom, legName2,"l");
TString legName4 = mcName + " + "+ runName + " Custom TTVA WP, #Delta R <1.0";
leg2->AddEntry(grROC_2016_TTVA_custom_dr, legName4,"l");
TString legName3 = mcName + " + "+ runName + " All Tracks and #chi^{2}_{PV} #leq 5";
leg2->AddEntry(grROC_2016_all_c5, legName3,"l");
// TString legName4 = mcName + " + "+ runName + " TTVA Tight WP + #chi^{2}_{SV} #leq 2 and #Delta R<1.";
// leg2->AddEntry(grROC_2016_TTVA_custom_dr, legName4,"l");
// TString legName5 = mcName + " + "+ runName + " All Tracks and #chi^{2}_{PV} #leq 5 and #Delta R<1.";
// leg2->AddEntry(grROC_2016_all_c5_dr, legName5,"l");
TString legName6 = "MC12 + Run 1";
if (!Pileup.EqualTo("high")){
    leg2->AddEntry(grROC_Run1, legName6,"l");
}


leg2->SetBorderSize(0);  // no border
leg2->SetLineColor(0);
leg2->SetFillColor(0);
leg2->SetTextSize(0.025);
leg2->Draw();


// TString ofilenames = "Jun13MuIso_SidebandTrained/BDT1";//train3
TString OutdirName = "/afs/cern.ch/user/a/agrummer/www/bmumu/IsoVarROCs/";
// TString Tag = "Tracks_2016";
// TString Tag = "TTVA_Chi2"+theYear+"_logAccept_2019Jun3";
// TString Tag = "TTVA_Chi2"+theYear+"_logAccept_2019Jun6";
TString Tag = "TTVA_Chi2"+theYear+"_logAccept_"+FileDate+"_"+Pileup;
TString typeDir="Accept";
TString varDir="BIso";
// c2->SaveAs(OutdirName + "Figures/ROC_2019Jun6/ROC_"+Tag+".pdf");
// c2->SaveAs(OutdirName + "Figures/ROC_2019July17/ROC_"+Tag+ExtraCut+".pdf");
// c2->SaveAs(OutdirName + "Figures/ROC_2019July30/ROC_"+Tag+ExtraCut+".pdf");
c2->SaveAs(OutdirName + "Figures/ROC_2019Nov21_v4/"+varDir+"/"+typeDir+"/ROC_"+Tag+ExtraCut+".pdf");
// TFile ofile(OutdirName + "RootFiles/ROC_"+Tag+".root", "recreate");
// // grROC_Run1->Write();
// grROC_2016_Default->Write();
// grROC_2016_AllTracks->Write();
// grROC_2016_AllTracks_PVweights->Write();
// // grROC_2017->Write();
// // grROC_2018->Write();

delete c2;
return 0;
}

void Iso_MultiROCs_TTVA_logAccept_v4(){
//     TString FileDate = "2019Jun6"; //ID hits revised run 1 with IBL included
// // TString FileDate = "2019Jun12"; //ID hits revised run 1 with IBL included and chi2<6
// // TString FileDate = "2019Jun17"; //ID hits isTightPrimary
// // TString FileDate = "2019Jun17_2"; //ID hits isTightPrimary and chi2<6

//     makeROCplots("2016", FileDate);
//     makeROCplots("2017", FileDate);
//     makeROCplots("2018", FileDate);


TString FileDate = ""; 

// FileDate = "2019May30"; //ID hits like run 1 (without IBL)
//     makeROCplots("2016", FileDate);
//     makeROCplots("2017", FileDate);
//     makeROCplots("2018", FileDate);

// FileDate = "2019Jun5"; //No ID Hits
//     makeROCplots("2016", FileDate);
// FileDate = "2019Jun3"; //No ID Hits
//     makeROCplots("2017", FileDate);
//     makeROCplots("2018", FileDate);

// FileDate = "2019Jun27"; //ID hits revised run 1 with IBL included
// FileDate = "2019July17"; //ID hits revised run 1 with IBL included
TString ExtraCut = ""; 
// ExtraCut = "Lxy>0.2"; 
// ExtraCut = "a_2D<0.1"; 

    // makeROCplots("2016", FileDate, ExtraCut, Pileup);
    // makeROCplots("2017", FileDate, ExtraCut, Pileup);
    // makeROCplots("2018", FileDate, ExtraCut, Pileup);

// FileDate = "2019Jun12"; //ID hits revised run 1 with IBL included and chi2<6
//     makeROCplots("2016", FileDate);
//     makeROCplots("2017", FileDate);
//     makeROCplots("2018", FileDate);

// FileDate = "2019Jun17"; //ID hits isTightPrimary
//     makeROCplots("2016", FileDate);
//     makeROCplots("2017", FileDate);
//     makeROCplots("2018", FileDate);

// FileDate = "2019Jun17_2"; //ID hits isTightPrimary and chi2<6
//     makeROCplots("2016", FileDate);
//     makeROCplots("2017", FileDate);
//     makeROCplots("2018", FileDate);
TString Pileup;
FileDate = "2019July30"; 
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
