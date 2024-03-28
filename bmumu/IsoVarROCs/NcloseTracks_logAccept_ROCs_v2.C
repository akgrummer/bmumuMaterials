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
// #include "Iso_logAccept_ROCs.C"
#include "Iso_logAccept_ROCs_Reverse.cpp"

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
// TGraph* grROC_Run1 = Iso_logAccept_ROCs(EvalTreeSig_Run1, EvalTreeBkg_Run1,
//                               Bisolation, CutAddSig_Run1,
//                               Run1iso, CutAddBkg_Run1,
//                               ColorIndex);
///////2016 trees////////
// TString theYear = "2018";
// TString filenameBkg_2016 = DirName + theYear+"All/LASTskim_"+theYear+"_All_2019May30.root";
// TString filenameBkg_2016 = DirName + theYear+"All/LASTskim_"+theYear+"_All_2019Jun3.root";
// TString filenameBkg_2016 = DirName + theYear+"All/LASTskim_"+theYear+"_All_2019Jun6.root";
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
TCut CutAddSig_2016_Default = CutAdd*"PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
TCut CutAddBkg_2016_Default = CutAdd;
Int_t ColorIndex = 0;
TGraph* grROC_2016_Default = Iso_logAccept_ROCs(EvalTreeSig_2016, EvalTreeBkg_2016,
                              closeTrkNtrks, CutAddSig_2016_Default,
                              closeTrkNtrks, CutAddBkg_2016_Default,
                              ColorIndex);
///////2016 TTVA loose////////
TCut CutAddSig_2016_TTVA_loose = CutAdd*RunNumberCut*"PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
TCut CutAddBkg_2016_TTVA_loose = CutAdd;
ColorIndex = 1;
TGraph* grROC_2016_TTVA_loose = Iso_logAccept_ROCs(EvalTreeSig_2016, EvalTreeBkg_2016,
                              var_closeTrkNtrks_TTVA_loose, CutAddSig_2016_TTVA_loose,
                              var_closeTrkNtrks_TTVA_loose, CutAddBkg_2016_TTVA_loose,
                              ColorIndex);
///////2016 all TTVA nominal////////
TCut CutAddSig_2016_TTVA_nominal = CutAdd*RunNumberCut*"PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
TCut CutAddBkg_2016_TTVA_nominal = CutAdd;
ColorIndex = 2;
TGraph* grROC_2016_TTVA_nominal = Iso_logAccept_ROCs(EvalTreeSig_2016, EvalTreeBkg_2016,
                              var_closeTrkNtrks_TTVA_nominal, CutAddSig_2016_TTVA_nominal,
                              var_closeTrkNtrks_TTVA_nominal, CutAddBkg_2016_TTVA_nominal,
                              ColorIndex);
///////2016 all TTVA tight////////
TCut CutAddSig_2016_TTVA_tight = CutAdd*RunNumberCut*"PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
TCut CutAddBkg_2016_TTVA_tight = CutAdd;
ColorIndex = 3;
TGraph* grROC_2016_TTVA_tight = Iso_logAccept_ROCs(EvalTreeSig_2016, EvalTreeBkg_2016,
                              var_closeTrkNtrks_TTVA_tight, CutAddSig_2016_TTVA_tight,
                              var_closeTrkNtrks_TTVA_tight, CutAddBkg_2016_TTVA_tight,
                              ColorIndex);



TCanvas* c2 = new TCanvas("c2", "ROC curve",0.,0., 800, 600);
c2->SetLogy(1);
Double_t ymin = 1e-1;
Double_t ymax = 50.;
Double_t xmin = 0;
Double_t xmax = 80;
grROC_2016_TTVA_tight->GetYaxis()->SetRangeUser(ymin, ymax);
grROC_2016_TTVA_tight->GetXaxis()->SetRangeUser(xmin, xmax);
grROC_2016_TTVA_tight->Draw("al");
grROC_2016_TTVA_nominal->Draw("same l");
grROC_2016_TTVA_loose->Draw("same l");
// grROC_2016_AllTrks_Chi6->Draw("same l");
// grROC_2016_AllTrks_Chi5->Draw("same l");
// grROC_2016_AllTrks_Chi4->Draw("same l");
grROC_2016_Default->Draw("same l");
// grROC_2017->Draw("same l");
// grROC_2018->Draw("same l");
// grROC_Run1->Draw("same l");
atlasLabel(0.5, 0.45, false, true, 1, true, false, true);

TLegend* leg2;
TString theTracks="";
if (FileDate.EqualTo("2019Jun6")){
    theTracks = " #chi^{2}_{SV}<=1";
}
if (FileDate.EqualTo("2019Jun17")){
    theTracks = " #chi^{2}_{SV}<=2";
}
if (FileDate.EqualTo("2019Jun17_2")) {
    theTracks = " #chi^{2}_{SV}<=4";
}
// leg2 = new TLegend(1, 0.06, 5, 0.08,NULL,"brNDC");
// leg2 = new TLegend(0.218045, 0.721739, 0.418546, 0.770435,NULL,"brNDC");
leg2 = new TLegend(0.52, 0.2, 0.72, 0.4,NULL,"brNDC");
// leg2->SetHeader("Number of Close Tracks to B DV");
leg2->SetHeader("NcloseTrks "+theTracks);
// leg2->AddEntry(grROC_Run1, "MC16a + Run 1","l");
// leg2->AddEntry(grROC_Run1, "MC16a + 15+16 Dataset","l");
// TString Run("");
TString legName1 = mcName + " + "+ runName + " Default";
leg2->AddEntry(grROC_2016_Default, legName1,"l");
TString legName2 = mcName + " + "+ runName + " TTVA Loose WP";
leg2->AddEntry(grROC_2016_TTVA_loose, legName2,"l");
TString legName3 = mcName + " + "+ runName + " TTVA Nominal WP";
leg2->AddEntry(grROC_2016_TTVA_nominal, legName3,"l");
TString legName4 = mcName + " + "+ runName + " TTVA Tight WP";
leg2->AddEntry(grROC_2016_TTVA_tight, legName4,"l");
TString legName5 = mcName + " + "+ runName + " All Tracks #chi^{2}<6";
// leg2->AddEntry(grROC_2016_AllTrks_Chi6, legName5,"l");
// TString legName6 = mcName + " + "+ runName + " All Tracks #chi^{2}<5";
// leg2->AddEntry(grROC_2016_AllTrks_Chi5, legName6,"l");
// TString legName7 = mcName + " + "+ runName + " All Tracks #chi^{2}<4";
// leg2->AddEntry(grROC_2016_AllTrks_Chi4, legName7,"l");
// leg2->AddEntry(grROC_2017, "MC16d + 2017 Run 339849","l");
// leg2->AddEntry(grROC_2018, "MC16e + 2018 Run 358096","l");
leg2->SetBorderSize(0);  // no border
leg2->SetLineColor(0);
leg2->SetFillColor(0);
leg2->SetTextSize(0.025);
leg2->Draw();


// TString ofilenames = "Jun13MuIso_SidebandTrained/BDT1";//train3
TString OutdirName = "/afs/cern.ch/user/a/agrummer/www/bmumu/IsoVarROCs/";
// TString Tag = "Tracks_2016";
// TString Tag = "TTVA_Chi2"+theYear+"_logAccept_2019Jun3";
// TString Tag = "NcloseTracks_TTVA"+theYear+"_logAccept_2019Jun6";
// TString Tag = "NcloseTracks_TTVA"+theYear+"_logAccept_2019Jun10";
// TString Tag = "NcloseTracks_TTVA"+theYear+"_logAccept_2019Jun12";
TString Tag = "NcloseTracks_TTVA"+theYear+"_logAccept_2019Jun12_2";//jun12_2 made with jun 6 inputs

// c2->SaveAs(OutdirName + "Figures/ROC_2019Jun3/ROC_"+Tag+".pdf");
c2->SaveAs(OutdirName + "Figures/ROC_2019Jun27/"+FileDate+"/ROC_"+Tag+".pdf");
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

void NcloseTracks_logAccept_ROCs_v2(){
//     // ////TString FileDate = "2019Jun12"; //not good!! included chi2 PV cut
//     TString FileDate = "2019Jun6"; //NcloseTrks chi2SV <=1
// // TString FileDate = "2019Jun17"; //NcloseTrks chi2SV <=2
// // TString FileDate = "2019Jun17_2"; //NcloseTrks chi2SV <=4
//     makeROCplots("2016", FileDate);
//     makeROCplots("2017", FileDate);
//     makeROCplots("2018", FileDate);

TString FileDate = ""; //NcloseTrks chi2SV <=1
FileDate = "2019Jun6"; //NcloseTrks chi2SV <=1
    makeROCplots("2016", FileDate);
    makeROCplots("2017", FileDate);
    makeROCplots("2018", FileDate);

FileDate = "2019Jun17"; //NcloseTrks chi2SV <=2
    makeROCplots("2016", FileDate);
    makeROCplots("2017", FileDate);
    makeROCplots("2018", FileDate);

FileDate = "2019Jun17_2"; //NcloseTrks chi2SV <=4
    makeROCplots("2016", FileDate);
    makeROCplots("2017", FileDate);
    makeROCplots("2018", FileDate);

    }
