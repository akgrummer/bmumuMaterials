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
#include "Iso_ROCs_Module.C"
// #include "Iso_ROCs_Module_errors.C"

void makeROCplots(TString theYear = "", TString FileDate = ""){
    SetAtlasStyle();
TString DirName = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/";


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
// TString filenameBkg_2016 = DirName + theYear+"All/LASTskim_"+theYear+"_All_2019May30.root";
// TString filenameBkg_2016 = DirName + theYear+"All/LASTskim_"+theYear+"_All_2019Jun3.root";
// TString filenameBkg_2016 = DirName + theYear+"All/LASTskim_"+theYear+"_All_2019Jun5.root";
// TString filenameBkg_2016 = DirName + theYear+"All/LASTskim_"+theYear+"_All_2019Jun6.root";
// TString filenameBkg_2016 = DirName + theYear+"All/LASTskim_"+theYear+"_All_2019Jun12.root";//chi2<6 in TTVAs
TString filenameBkg_2016 = DirName + theYear+"All/LASTskim_"+theYear+"_All_"+FileDate+".root";//chi2<6 in TTVAs
TString filenameSig_2016("");
TString mcName("");
TString runName("");
TCut RunNumberCut("");
if (theYear.EqualTo("2016")){
 mcName = "MC16a";
 runName = "2016 Run 302393";
 RunNumberCut = "run_number==302393";
}else if(theYear.EqualTo("2017")){
 mcName = "MC16d";
  runName = "2017 Run 339849";
 RunNumberCut = "run_number==339849";
 }else if(theYear.EqualTo("2018")){
    mcName = "MC16e";
  runName = "2018 Run 358096";
 RunNumberCut = "run_number==358096";
 }
 // filenameSig_2016 = DirName + mcName+"All/LASTskim_"+mcName+"_All_2019May30.root";
 // filenameSig_2016 = DirName + mcName+"All/LASTskim_"+mcName+"_All_2019Jun3.root";
 // filenameSig_2016 = DirName + mcName+"All/LASTskim_"+mcName+"_All_2019Jun5.root";
 // filenameSig_2016 = DirName + mcName+"All/LASTskim_"+mcName+"_All_2019Jun6.root";
 // filenameSig_2016 = DirName + mcName+"All/LASTskim_"+mcName+"_All_2019Jun6.root";//chi2<6 in TTVAs
 filenameSig_2016 = DirName + mcName+"All/LASTskim_"+mcName+"_All_"+FileDate+".root";
TFile* ifilenameBkg_2016 = new TFile(filenameBkg_2016);
TFile* ifilenameSig_2016 = new TFile(filenameSig_2016);
TTree *EvalTreeBkg_2016 = (TTree*)ifilenameBkg_2016->Get("T_mv");
TTree *EvalTreeSig_2016 = (TTree*)ifilenameSig_2016->Get("T_mv");
cout<<"EvalTreeBkg Entries: "<<EvalTreeBkg_2016->GetEntries()<<endl;
cout<<"EvalTreeSig Entries: "<<EvalTreeSig_2016->GetEntries()<<endl;
///////////////////
///////2016 Default////////
TCut Weight_2016_Default = "PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
TCut CutAddSig_2016_Default = CutAdd*"PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
TCut CutAddBkg_2016_Default = CutAdd;
Int_t ColorIndex = 0;
TGraph* grROC_2016_Default = Iso_ROCs(EvalTreeSig_2016, EvalTreeBkg_2016,
                              Bisolation, CutAddSig_2016_Default,
                              Bisolation, CutAddBkg_2016_Default,
                              ColorIndex);
/////// TTVA tight  + chi2SV<=2////////
TCut CutAddSig_2016_TTVA_tight_c2 = CutAdd*RunNumberCut*"PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
TCut CutAddBkg_2016_TTVA_tight_c2 = CutAdd;
ColorIndex = 1;
TGraph* grROC_2016_TTVA_tight_c2 = Iso_ROCs(EvalTreeSig_2016, EvalTreeBkg_2016,
                              B_Iso_TTVA_tight_c2, CutAddSig_2016_TTVA_tight_c2,
                              B_Iso_TTVA_tight_c2, CutAddBkg_2016_TTVA_tight_c2,
                              ColorIndex);
///////all tracks_chi2<= 5////////
TCut CutAddSig_2016_all_c5 = CutAdd*RunNumberCut*"PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
TCut CutAddBkg_2016_all_c5 = CutAdd;
ColorIndex = 2;
TGraph* grROC_2016_all_c5 = Iso_ROCs(EvalTreeSig_2016, EvalTreeBkg_2016,
                              B_Iso_all_c5, CutAddSig_2016_all_c5,
                              B_Iso_all_c5, CutAddBkg_2016_all_c5,
                              ColorIndex);


TCanvas* c2 = new TCanvas("c2", "ROC curve",0.,0., 800, 600);
grROC_2016_Default->Draw("ale3");
grROC_2016_TTVA_tight_c2->Draw("same le3");
grROC_2016_all_c5->Draw("same le3");

atlasLabel(0.2, 0.45, false, true, 1, true, false, true);

TLegend* leg2;

// leg2 = new TLegend(1, 0.06, 5, 0.08,NULL,"brNDC");
// leg2 = new TLegend(0.218045, 0.721739, 0.418546, 0.770435,NULL,"brNDC");
leg2 = new TLegend(0.218045, 0.2, 0.418546, 0.4,NULL,"brNDC");
leg2->SetHeader("B Isolation");
// leg2->AddEntry(grROC_Run1, "MC16a + Run 1","l");
// leg2->AddEntry(grROC_Run1, "MC16a + 15+16 Dataset","l");
// TString Run("");
TString legName1 = mcName + " + "+ runName + " Default";
leg2->AddEntry(grROC_2016_Default, legName1,"l");
TString legName2 = mcName + " + "+ runName + " TTVA Tight WP + #chi^{2}_{SV} #leq 2";
leg2->AddEntry(grROC_2016_TTVA_tight_c2, legName2,"l");
TString legName3 = mcName + " + "+ runName + " All Tracks and #chi^{2}_{PV} #leq 5";
leg2->AddEntry(grROC_2016_all_c5, legName3,"l");

leg2->SetBorderSize(0);  // no border
leg2->SetLineColor(0);
leg2->SetFillColor(0);
leg2->SetTextSize(0.025);
leg2->Draw();


// TString ofilenames = "Jun13MuIso_SidebandTrained/BDT1";//train3
TString OutdirName = "/afs/cern.ch/user/a/agrummer/www/bmumu/IsoVarROCs/";
// TString Tag = "Tracks_2016";
// TString Tag = "TTVA_Chi2"+theYear+"_2019Jun6";
TString Tag = "TTVA_Chi2"+theYear+"_"+FileDate;

// c2->SaveAs(OutdirName + "Figures/ROC_2019Jun6/ROC_"+Tag+".pdf");
// c2->SaveAs(OutdirName + "Figures/ROC_2019Jun17/"+FileDate+"/ROC_"+Tag+".pdf");
// c2->SaveAs(OutdirName + "Figures/ROC_2019Jun27/ROC_"+Tag+".pdf");
c2->SaveAs(OutdirName + "Figures/ROC_2019July1/ROC_"+Tag+"scaled.pdf");
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

void Iso_MultiROCs_TTVA_v2(){
TString FileDate = ""; //ID hits revised run 1 with IBL included
    // makeROCplots("2016", FileDate);
    // makeROCplots("2017", FileDate);
    // makeROCplots("2018", FileDate);

// FileDate = "2019Jun27"; //ID hits like run 1 (without IBL)
FileDate = "2019July1"; //ID hits like run 1 (without IBL)
    makeROCplots("2016", FileDate);
    makeROCplots("2017", FileDate);
    makeROCplots("2018", FileDate);
}
