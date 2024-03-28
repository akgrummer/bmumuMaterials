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

void Iso_MultiROCs(){
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
///////2016////////
TString filenameBkg_2016 = DirName + "2016All/LASTskim_2016_All_2019Apr29_testweight.root";
TString filenameSig_2016 = DirName + "MC16aAll/LASTskim_MC16a_All_Studies_2019Apr24.root";
TFile* ifilenameBkg_2016 = new TFile(filenameBkg_2016);
TFile* ifilenameSig_2016 = new TFile(filenameSig_2016);
TTree *EvalTreeBkg_2016 = (TTree*)ifilenameBkg_2016->Get("T_mv");
TTree *EvalTreeSig_2016 = (TTree*)ifilenameSig_2016->Get("T_mv");
cout<<"EvalTreeBkg Entries: "<<EvalTreeBkg_2016->GetEntries()<<endl;
cout<<"EvalTreeSig Entries: "<<EvalTreeSig_2016->GetEntries()<<endl;
TCut CutAddSig_2016 = CutAdd*"PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
TCut CutAddBkg_2016 = CutAdd;
;
ColorIndex = 1;
TGraph* grROC_2016 = Iso_ROCs(EvalTreeSig_2016, EvalTreeBkg_2016,
                              Bisolation, CutAddSig_2016,
                              Bisolation, CutAddBkg_2016,
                              ColorIndex);
///////2017////////
TString filenameBkg_2017 = DirName + "2017All/LASTskim_2017_All_2019Apr29_testweight.root";
TString filenameSig_2017 = DirName + "MC16dAll/LASTskim_MC16d_All_Studies_2019Apr24.root";
TFile* ifilenameBkg_2017 = new TFile(filenameBkg_2017);
TFile* ifilenameSig_2017 = new TFile(filenameSig_2017);
TTree *EvalTreeBkg_2017 = (TTree*)ifilenameBkg_2017->Get("T_mv");
TTree *EvalTreeSig_2017 = (TTree*)ifilenameSig_2017->Get("T_mv");
cout<<"EvalTreeBkg Entries: "<<EvalTreeBkg_2017->GetEntries()<<endl;
cout<<"EvalTreeSig Entries: "<<EvalTreeSig_2017->GetEntries()<<endl;
TCut CutAddSig_2017 = CutAdd*"PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
TCut CutAddBkg_2017 = CutAdd;
;
ColorIndex = 2;
TGraph* grROC_2017 = Iso_ROCs(EvalTreeSig_2017, EvalTreeBkg_2017,
                              Bisolation, CutAddSig_2017,
                              Bisolation, CutAddBkg_2017,
                              ColorIndex);
///////2018////////
TString filenameBkg_2018 = DirName + "2018All/LASTskim_2018_All_2019Apr29_testweight.root";
TString filenameSig_2018 = DirName + "MC16eAll/LASTskim_MC16e_All_Studies_2019Apr24.root";
TFile* ifilenameBkg_2018 = new TFile(filenameBkg_2018);
TFile* ifilenameSig_2018 = new TFile(filenameSig_2018);
TTree *EvalTreeBkg_2018 = (TTree*)ifilenameBkg_2018->Get("T_mv");
TTree *EvalTreeSig_2018 = (TTree*)ifilenameSig_2018->Get("T_mv");
cout<<"EvalTreeBkg Entries: "<<EvalTreeBkg_2018->GetEntries()<<endl;
cout<<"EvalTreeSig Entries: "<<EvalTreeSig_2018->GetEntries()<<endl;
TCut CutAddSig_2018 = CutAdd*"PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
TCut CutAddBkg_2018 = CutAdd;
;
ColorIndex = 3;
TGraph* grROC_2018 = Iso_ROCs(EvalTreeSig_2018, EvalTreeBkg_2018,
                              Bisolation, CutAddSig_2018,
                              Bisolation, CutAddBkg_2018,
                              ColorIndex);


TCanvas* c2 = new TCanvas("c2", "ROC curve",0.,0., 800, 600);
grROC_2016->Draw("al");
grROC_2017->Draw("same l");
grROC_2018->Draw("same l");
grROC_Run1->Draw("same l");
atlasLabel(0.2, 0.45, false, true, 1, true, false, true);

TLegend* leg2;
// leg2 = new TLegend(1, 0.06, 5, 0.08,NULL,"brNDC");
// leg2 = new TLegend(0.218045, 0.721739, 0.418546, 0.770435,NULL,"brNDC");
leg2 = new TLegend(0.218045, 0.25, 0.418546, 0.4,NULL,"brNDC");
leg2->SetHeader("B Isolation");
leg2->AddEntry(grROC_Run1, "MC16a + Run 1","l");
// leg2->AddEntry(grROC_Run1, "MC16a + 15+16 Dataset","l");
leg2->AddEntry(grROC_2016, "MC16a + 2016 Run 302393","l");
leg2->AddEntry(grROC_2017, "MC16d + 2017 Run 339849","l");
leg2->AddEntry(grROC_2018, "MC16e + 2018 Run 358096","l");
leg2->SetBorderSize(0);  // no border
leg2->SetLineColor(0);
leg2->SetFillColor(0);
leg2->SetTextSize(0.025);
leg2->Draw();


// TString ofilenames = "Jun13MuIso_SidebandTrained/BDT1";//train3
TString OutdirName = "/afs/cern.ch/user/a/agrummer/www/bmumu/IsoVarROCs/";
TString Tag = "Default";
c2->SaveAs(OutdirName + "Figures/ROC_"+Tag+".pdf");
TFile ofile(OutdirName + "RootFiles/ROC_"+Tag+".root", "recreate");
grROC_Run1->Write();
grROC_2016->Write();
grROC_2017->Write();
grROC_2018->Write();


return 0;
}
