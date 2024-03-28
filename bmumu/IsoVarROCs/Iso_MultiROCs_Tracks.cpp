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

void Iso_MultiROCs_Tracks(){
    SetAtlasStyle();
TString DirName = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/";


TString vBDT = "";
///////Run1////////
TString filenameBkg_Run1 = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun1/data/Bsmumu/data12_8TeVBsAllPeriodsUnblinded.root";
TString filenameSig_Run1 = DirName + "MC16aAll/LASTskim_MC16a_All_Studies_2019Apr24.root";
TFile* ifilenameBkg_Run1 = new TFile(filenameBkg_Run1);
TFile* ifilenameSig_Run1 = new TFile(filenameSig_Run1);
TTree *EvalTreeBkg_Run1 = (TTree*)ifilenameBkg_Run1->Get("T_mv");
TTree *EvalTreeSig_Run1 = (TTree*)ifilenameSig_Run1->Get("T_mv");
cout<<"EvalTreeBkg Entries: "<<EvalTreeBkg_Run1->GetEntries()<<endl;
cout<<"EvalTreeSig Entries: "<<EvalTreeSig_Run1->GetEntries()<<endl;
TCut CutAddSig_Run1 = CutAdd*"PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
TCut CutAddBkg_Run1 = CutSB && "Lxy>0.3 && a_2D<1.0 && DR<1.5 &&BDT_fakeMuon_1>-0.458 && BDT_fakeMuon_2>-0.458 && isCatN3";
;
Int_t ColorIndex = 0;
TGraph* grROC_Run1 = Iso_ROCs(EvalTreeSig_Run1, EvalTreeBkg_Run1,
                              Bisolation, CutAddSig_Run1,
                              Run1iso, CutAddBkg_Run1,
                              ColorIndex);
///////2016 default////////
TString filenameBkg_2016_Default = DirName + "2016All/LASTskim_2016_All_2019Apr29_testweight.root";
TString filenameSig_2016_Default = DirName + "MC16aAll/LASTskim_MC16a_All_Studies_2019Apr24.root";
TFile* ifilenameBkg_2016_Default = new TFile(filenameBkg_2016_Default);
TFile* ifilenameSig_2016_Default = new TFile(filenameSig_2016_Default);
TTree *EvalTreeBkg_2016_Default = (TTree*)ifilenameBkg_2016_Default->Get("T_mv");
TTree *EvalTreeSig_2016_Default = (TTree*)ifilenameSig_2016_Default->Get("T_mv");
cout<<"EvalTreeBkg Entries: "<<EvalTreeBkg_2016_Default->GetEntries()<<endl;
cout<<"EvalTreeSig Entries: "<<EvalTreeSig_2016_Default->GetEntries()<<endl;
TCut CutAddSig_2016_Default = CutAdd*"PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
TCut CutAddBkg_2016_Default = CutAdd;
;
ColorIndex = 1;
TGraph* grROC_2016_Default = Iso_ROCs(EvalTreeSig_2016_Default, EvalTreeBkg_2016_Default,
                              Bisolation, CutAddSig_2016_Default,
                              Bisolation, CutAddBkg_2016_Default,
                              ColorIndex);
///////2016 all tracks////////
TString filenameBkg_2016_AllTracks = DirName + "2016All/LASTskim_2016_All_2019Apr29_testweight.root";
TString filenameSig_2016_AllTracks = DirName + "MC16aAll/LASTskim_MC16a_All_Studies_2019Apr24.root";
TFile* ifilenameBkg_2016_AllTracks = new TFile(filenameBkg_2016_AllTracks);
TFile* ifilenameSig_2016_AllTracks = new TFile(filenameSig_2016_AllTracks);
TTree *EvalTreeBkg_2016_AllTracks = (TTree*)ifilenameBkg_2016_AllTracks->Get("T_mv");
TTree *EvalTreeSig_2016_AllTracks = (TTree*)ifilenameSig_2016_AllTracks->Get("T_mv");
cout<<"EvalTreeBkg Entries: "<<EvalTreeBkg_2016_AllTracks->GetEntries()<<endl;
cout<<"EvalTreeSig Entries: "<<EvalTreeSig_2016_AllTracks->GetEntries()<<endl;
TCut CutAddSig_2016_AllTracks = CutAdd*"PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
TCut CutAddBkg_2016_AllTracks = CutAdd;
;
ColorIndex = 2;
TGraph* grROC_2016_AllTracks = Iso_ROCs(EvalTreeSig_2016_AllTracks, EvalTreeBkg_2016_AllTracks,
                              isoAlltracks, CutAddSig_2016_AllTracks,
                              isoAlltracks, CutAddBkg_2016_AllTracks,
                              ColorIndex);
///////2016 all tracks////////
TString filenameBkg_2016_AllTracks_PVweights = DirName + "2016All/LASTskim_2016_All_2019Apr29_testweight.root";
TString filenameSig_2016_AllTracks_PVweights = DirName + "MC16aAll/LASTskim_MC16a_All_Studies_2019Apr24.root";
TFile* ifilenameBkg_2016_AllTracks_PVweights = new TFile(filenameBkg_2016_AllTracks_PVweights);
TFile* ifilenameSig_2016_AllTracks_PVweights = new TFile(filenameSig_2016_AllTracks_PVweights);
TTree *EvalTreeBkg_2016_AllTracks_PVweights = (TTree*)ifilenameBkg_2016_AllTracks_PVweights->Get("T_mv");
TTree *EvalTreeSig_2016_AllTracks_PVweights = (TTree*)ifilenameSig_2016_AllTracks_PVweights->Get("T_mv");
cout<<"EvalTreeBkg Entries: "<<EvalTreeBkg_2016_AllTracks_PVweights->GetEntries()<<endl;
cout<<"EvalTreeSig Entries: "<<EvalTreeSig_2016_AllTracks_PVweights->GetEntries()<<endl;
TCut CutAddSig_2016_AllTracks_PVweights = CutAdd*"PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
TCut CutAddBkg_2016_AllTracks_PVweights = CutAdd*"testweight";
;
ColorIndex = 3;
TGraph* grROC_2016_AllTracks_PVweights = Iso_ROCs(EvalTreeSig_2016_AllTracks_PVweights, EvalTreeBkg_2016_AllTracks_PVweights,
                              isoAlltracks, CutAddSig_2016_AllTracks_PVweights,
                              isoAlltracks, CutAddBkg_2016_AllTracks_PVweights,
                              ColorIndex);
// ///////2017////////
// TString filenameBkg_2017 = DirName + "2017All/LASTskim_2017_All_2019Apr29_testweight.root";
// TString filenameSig_2017 = DirName + "MC16dAll/LASTskim_MC16d_All_Studies_2019Apr24.root";
// TFile* ifilenameBkg_2017 = new TFile(filenameBkg_2017);
// TFile* ifilenameSig_2017 = new TFile(filenameSig_2017);
// TTree *EvalTreeBkg_2017 = (TTree*)ifilenameBkg_2017->Get("T_mv");
// TTree *EvalTreeSig_2017 = (TTree*)ifilenameSig_2017->Get("T_mv");
// cout<<"EvalTreeBkg Entries: "<<EvalTreeBkg_2017->GetEntries()<<endl;
// cout<<"EvalTreeSig Entries: "<<EvalTreeSig_2017->GetEntries()<<endl;
// TCut CutAddSig_2017 = CutAdd*"PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
// TCut CutAddBkg_2017 = CutAdd;
// ;
// ColorIndex = 2;
// TGraph* grROC_2017 = Iso_ROCs(EvalTreeSig_2017, EvalTreeBkg_2017,
//                               Bisolation, CutAddSig_2017,
//                               Run1iso, CutAddBkg_2017,
//                               ColorIndex);
// ///////2018////////
// TString filenameBkg_2018 = DirName + "2018All/LASTskim_2018_All_2019Apr29_testweight.root";
// TString filenameSig_2018 = DirName + "MC16eAll/LASTskim_MC16e_All_Studies_2019Apr24.root";
// TFile* ifilenameBkg_2018 = new TFile(filenameBkg_2018);
// TFile* ifilenameSig_2018 = new TFile(filenameSig_2018);
// TTree *EvalTreeBkg_2018 = (TTree*)ifilenameBkg_2018->Get("T_mv");
// TTree *EvalTreeSig_2018 = (TTree*)ifilenameSig_2018->Get("T_mv");
// cout<<"EvalTreeBkg Entries: "<<EvalTreeBkg_2018->GetEntries()<<endl;
// cout<<"EvalTreeSig Entries: "<<EvalTreeSig_2018->GetEntries()<<endl;
// TCut CutAddSig_2018 = CutAdd*"PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
// TCut CutAddBkg_2018 = CutAdd;
// ;
// ColorIndex = 3;
// TGraph* grROC_2018 = Iso_ROCs(EvalTreeSig_2018, EvalTreeBkg_2018,
//                               Bisolation, CutAddSig_2018,
//                               Run1iso, CutAddBkg_2018,
//                               ColorIndex);


TCanvas* c2 = new TCanvas("c2", "ROC curve",0.,0., 800, 600);
grROC_2016_Default->Draw("al");
grROC_2016_AllTracks->Draw("same l");
grROC_2016_AllTracks_PVweights->Draw("same l");
// grROC_2017->Draw("same l");
// grROC_2018->Draw("same l");
grROC_Run1->Draw("same l");
atlasLabel(0.2, 0.45, false, true, 1, true, false, true);

TLegend* leg2;
// leg2 = new TLegend(1, 0.06, 5, 0.08,NULL,"brNDC");
// leg2 = new TLegend(0.218045, 0.721739, 0.418546, 0.770435,NULL,"brNDC");
leg2 = new TLegend(0.218045, 0.25, 0.418546, 0.4,NULL,"brNDC");
leg2->SetHeader("B Isolation");
leg2->AddEntry(grROC_Run1, "MC16a + Run 1","l");
// leg2->AddEntry(grROC_Run1, "MC16a + 15+16 Dataset","l");
leg2->AddEntry(grROC_2016_Default, "MC16a + 2016 Run 302393 Default","l");
leg2->AddEntry(grROC_2016_AllTracks, "MC16a + 2016 Run 302393 All Tracks","l");
leg2->AddEntry(grROC_2016_AllTracks_PVweights, "MC16a + 2016 Run 302393 All Tracks and PV Weights","l");
// leg2->AddEntry(grROC_2017, "MC16d + 2017 Run 339849","l");
// leg2->AddEntry(grROC_2018, "MC16e + 2018 Run 358096","l");
leg2->SetBorderSize(0);  // no border
leg2->SetLineColor(0);
leg2->SetFillColor(0);
leg2->SetTextSize(0.025);
leg2->Draw();


// TString ofilenames = "Jun13MuIso_SidebandTrained/BDT1";//train3
TString OutdirName = "/afs/cern.ch/user/a/agrummer/www/bmumu/IsoVarROCs/";
TString Tag = "Tracks_2016";

c2->SaveAs(OutdirName + "Figures/ROC_"+Tag+".pdf");
TFile ofile(OutdirName + "RootFiles/ROC_"+Tag+".root", "recreate");
grROC_Run1->Write();
grROC_2016_Default->Write();
grROC_2016_AllTracks->Write();
grROC_2016_AllTracks_PVweights->Write();
// grROC_2017->Write();
// grROC_2018->Write();


return 0;
}
