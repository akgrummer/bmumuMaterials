#include<TMath.h>
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasLabels.C"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasLabels.h"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasStyle.C"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasStyle.h"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasUtils.C"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasUtils.h"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/Plotting/NewVarComps/Iso_MultiROCs.h"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/Plotting/NewVarComps/getHistoFromTree.C"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/Plotting/NewVarComps/atlasLabel.C"

// #include "Iso_logAccept_ROCs_Module.C"
// #include "Iso_logAccept_ROCs.C"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/Plotting/NewVarComps/Iso_logAccept_ROCs_errors.C"

void makeROCplots(TString theYear = "", TString FileDate = "", TString ExtraCut = "", TString Pileup = ""){
    SetAtlasStyle();
    //this folder was renamed to:
    // /eos/home-a/agrummer/BsmumuData/FinalSkim/v3
// TString DirName = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/";
// TString DirName = "/eos/home-a/agrummer/BsmumuData/FinalSkim/v5/";
// TString DirName = "/eos/home-a/agrummer/BsmumuData/FinalSkim/v6/";
TString DirName = "/eos/home-a/agrummer/BsmumuData/AnalysisNtuples2020/v4/";


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
// TString filenameBkg = DirName + theYear+"All/LASTskim_"+theYear+"_All_2019May30.root";
// TString filenameBkg = DirName + theYear+"All/LASTskim_"+theYear+"_All_2019Jun3.root";
// TString filenameBkg = DirName + theYear+"All/LASTskim_"+theYear+"_All_2019Jun6.root";
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

TCut run1Weight;
CutRun1 = CutRun1dummy;
// CutRun1
CutRun1 = CutRun1*ExtraCut*PUcut;
TString ifilenameRun1;
TString ifilenameRun1_Bkg = "/eos/home-a/agrummer/BsmumuData/Run1/Data/data12_8TeVBsAllPeriodsUnblinded_doca3.root";
TString ifilenameRun1_Sig = "/eos/home-a/agrummer/BsmumuData/Run1/MC/mc12_8TeV.208426.Pythia8B_AU2_CTEQ6L1_Bs_mu3p5mu3p5.r3549.172133.staco.Bs2mumu_Bs.v12.s1.wTRUTHvarsANDnoMCPcuts_doca3.root";
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
                              closeTrkDOCA_3, CutRun1,
                              closeTrkDOCA_3, CutRun1,
                              run1Weight, ColorIndex);
}
ifilenameBkg_Run1->Close();
ifilenameSig_Run1->Close();


TString filenameBkg = DirName + "LASTskim.user.agrummer.Data1516.merged.root";

TString filenameSig("");
TString mcName("");
TString runName("");
TCut RunNumberCut("");
if (theYear.EqualTo("2016main")){
 mcName = "MC16a";
 runName = "2016 Run 302393";
 RunNumberCut = "run_number==302393";
 // filenameSig = DirName + mcName+"All/LASTskim_"+mcName+"_All_2019Jun5.root";
 // filenameSig = DirName + mcName+"All/LASTskim_"+mcName+"_All_2019Jun6.root";
}else if (theYear.EqualTo("2016main303846")){
 mcName = "MC16a303846";
 runName = "2016 Run 303846";
 RunNumberCut = "run_number==303846";
}else if(theYear.EqualTo("2017")){
 mcName = "MC16d";
  runName = "2017 Run 339849";
 RunNumberCut = "run_number==339849";
 // filenameSig = DirName + mcName+"All/LASTskim_"+mcName+"_All_2019Jun3.root";
 // filenameSig = DirName + mcName+"All/LASTskim_"+mcName+"_All_2019Jun6.root";
 }else if(theYear.EqualTo("2018")){
    mcName = "MC16e";
  runName = "2018 Run 358096";
 RunNumberCut = "run_number==358096";
 // filenameSig = DirName + mcName+"All/LASTskim_"+mcName+"_All_2019Jun3.root";
 // filenameSig = DirName + mcName+"All/LASTskim_"+mcName+"_All_2019Jun6.root";
 }
 filenameSig = DirName + "LASTskim.user.agrummer.mcBsmumu.merged.root";

 // filenameSig = DirName + mcName+"All/LASTskim_"+mcName+"_All_2019May30.root";
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
ColorIndex = 0;
TGraph* grROC_1516 = Iso_logAccept_ROCs(EvalTreeSig, EvalTreeBkg,
                              closeTrkDOCA_3, CutAddSig_Default,
                              closeTrkDOCA_3, CutAddBkg_Default,
                              Weight_Default, ColorIndex);
// ///////1///////
// ColorIndex = 4;
// TGraph* grROC_customApprox = Iso_logAccept_ROCs(EvalTreeSig, EvalTreeBkg,
//                               closeTrkDOCA_LooSiHi1Pt05_corc2cnt_custom, CutAddSig_Default,
//                               closeTrkDOCA_LooSiHi1Pt05_corc2cnt_custom, CutAddBkg_Default,
//                               Weight_Default, ColorIndex);
// ///////2///////
ColorIndex = 2;
TGraph* grROC_customTrkPerigee = Iso_logAccept_ROCs(EvalTreeSig, EvalTreeBkg,
                              closeTrkDOCA_T0134217728_LooSiHi1Pt05_f2dc2, CutAddSig_Default,
                              closeTrkDOCA_T0134217728_LooSiHi1Pt05_f2dc2, CutAddBkg_Default,
                              Weight_Default, ColorIndex);
// ///////3///////
// ColorIndex = 1;
// TGraph* grROC_looseApprox = Iso_logAccept_ROCs(EvalTreeSig, EvalTreeBkg,
//                               closeTrkDOCA_LooSiHi1Pt05_corc2cnt_loose, CutAddSig_Default,
//                               closeTrkDOCA_LooSiHi1Pt05_corc2cnt_loose, CutAddBkg_Default,
//                               Weight_Default, ColorIndex);
// ///////4//////
ColorIndex = 1;
TGraph* grROC_looseTrkPerigee = Iso_logAccept_ROCs(EvalTreeSig, EvalTreeBkg,
                              closeTrkDOCA_T0008388608_LooSiHi1Pt05_f2dc2, CutAddSig_Default,
                              closeTrkDOCA_T0008388608_LooSiHi1Pt05_f2dc2, CutAddBkg_Default,
                              Weight_Default, ColorIndex);



TCanvas* c2 = new TCanvas("c2", "ROC curve",0.,0., 800, 600);
c2->SetLogy(1);
Double_t ymin = 2e-5;
Double_t ymax = 5e-1;
Double_t xmin = 0.;
Double_t xmax = 0.8;
// grROC_1516
// grROC_customApprox
// grROC_customTrkPerigee
// grROC_looseApprox
// grROC_looseTrkPerigee
grROC_1516->GetXaxis()->SetLimits(xmin, xmax);// along X
grROC_1516->GetHistogram()->SetMaximum(ymax);   // along          
grROC_1516->GetHistogram()->SetMinimum(ymin);  //   YgrROC_TTVA_custom_c1->Draw("al2");
// grROC_looseApprox->Draw("al2");
grROC_1516->Draw("al2");
// grROC_all_c7->Draw("same l2");
// grROC_all_c2->Draw("same l2");
// grROC_AllTrks_Chi6->Draw("same l");
// grROC_AllTrks_Chi5->Draw("same l");
// grROC_AllTrks_Chi4->Draw("same l");
// grROC_customApprox->Draw("same l2");
grROC_looseTrkPerigee->Draw("same l2");
grROC_customTrkPerigee->Draw("same l2");
// grROC_Run1->Draw("same l2");
// grROC_2017->Draw("same l");
// grROC_2018->Draw("same l");
if (!Pileup.EqualTo("high")){grROC_Run1->Draw("same l2");}
atlasLabel(0.5, 0.41, false, true, 1, true, false, true);

TLegend* leg2;
TString theTracks="";
// if (FileDate.EqualTo("2019Jun6")){
//     theTracks = " #chi^{2}_{SV}<=1";
// }
// if (FileDate.EqualTo("2019Jun17")){
//     theTracks = " #chi^{2}_{SV}<=1";
// }
// if (FileDate.EqualTo("2019Jun17_2")) {
//     theTracks = " #chi^{2}_{SV}<=1";
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
}else if(Pileup.EqualTo("all")) {
    PileupHeader = " ";
}
leg2 = new TLegend(0.47, 0.2, 0.67, 0.4,NULL,"brNDC");
// leg2->SetHeader("DOCA_{xtrk}");
leg2->SetHeader("DOCA_{xtrk} "+PileupHeader+ExtraCut);
// leg2->AddEntry(grROC_Run1, "MC16a + Run 1","l");
// leg2->AddEntry(grROC_Run1, "MC16a + 15+16 Dataset","l");
// TString Run("");
if (!Pileup.EqualTo("high")){
    leg2->AddEntry(grROC_Run1, "MC12 + Run 1","l");
}
TString legName1 = mcName + " + "+ runName + " ACK (OOO)";
leg2->AddEntry(grROC_1516, legName1,"l");
// TString legName2 = mcName + " + "+ runName + " BFM (PVV)";
// leg2->AddEntry(grROC_customApprox, legName2,"l");
TString legName3 = mcName + " + "+ runName + " BEL (PPP)";
leg2->AddEntry(grROC_customTrkPerigee, legName3,"l");
// TString legName4 = mcName + " + "+ runName + " BGM (PPV)";
// leg2->AddEntry(grROC_looseApprox, legName4,"l");
TString legName5 = mcName + " + "+ runName + " BGL (PPP)";
leg2->AddEntry(grROC_looseTrkPerigee, legName5,"l");
// TString legName4 = mcName + " + "+ runName + " Old Assoc. + #chi^{2}_{SV}<7";
// leg2->AddEntry(grROC_all_c7, legName4,"l");
// TString legName5 = mcName + " + "+ runName + " Old Assoc. + #chi^{2}_{SV}<2";
// leg2->AddEntry(grROC_all_c2, legName5,"l");
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
TString OutdirName = "/afs/cern.ch/user/a/agrummer/www/bmumu2020/SavePlots/NewVarComps/";
// TString Tag = "Tracks";
// TString Tag = "TTVA_Chi2"+theYear+"_logAccept_2019Jun3";
// TString Tag = "DOCA_TTVA"+theYear+"_logAccept_2019Jun6";
// TString Tag = "DOCA_TTVA"+theYear+"_logAccept_2019Jun12";//jun12 made with jun6 inputs
TString Tag = "DOCA_TTVA"+theYear+"_logAccept_"+FileDate+"_"+Pileup;//jun12 made with jun6 inputs
TString typeDir="Accept";
TString varDir="DOCA";
// c2->SaveAs(OutdirName + "Figures/ROC_2019Jun3/ROC_"+Tag+".pdf");
// c2->SaveAs(OutdirName + "Figures/ROC_2019July17/ROC_"+Tag+ExtraCut+".pdf");
// c2->SaveAs(OutdirName + "Figures/ROC_2019July30/ROC_"+Tag+ExtraCut+".pdf");
// c2->SaveAs(OutdirName + "Figures/ROC_2019Nov21_v7/"+varDir+"/"+typeDir+"/ROC_"+Tag+ExtraCut+".pdf");
// c2->SaveAs(OutdirName + "Figures/ROC_2019Nov21_v7_2/"+varDir+"/"+typeDir+"/ROC_"+Tag+ExtraCut+".pdf");
// c2->SaveAs(OutdirName + "Figures/ROC_2019Dec5_v7/"+varDir+"/"+typeDir+"/ROC_"+Tag+ExtraCut+".pdf");
c2->SaveAs(OutdirName + "ROC_2020May14_v8_newVars/"+varDir+"/"+typeDir+"/ROC_"+Tag+ExtraCut+".pdf");
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

void DOCA_logAccept_ROCs_v8_newVars(){
//     // ////TString FileDate = "2019Jun12"; //not good!! included chi2 PV cut
//     TString FileDate = "2019Jun6"; //NcloseTrks chi2SV <=1
// // TString FileDate = "2019Jun17"; //NcloseTrks chi2SV <=2
// // TString FileDate = "2019Jun17_2"; //NcloseTrks chi2SV <=4
//     makeROCplots("2016", FileDate);
//     makeROCplots("2017", FileDate);
//     makeROCplots("2018", FileDate);
TString FileDate = ""; //NcloseTrks chi2SV <=1
// FileDate = "2019July17"; //NcloseTrks chi2SV <=1
TString ExtraCut = ""; 
// ExtraCut = "Lxy>0.2"; 
// ExtraCut = "a_2D<0.1"; 

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
FileDate = "2020May14"; 
    Pileup = "all";
    makeROCplots("", FileDate, ExtraCut, Pileup);
    // makeROCplots("2016main", FileDate, ExtraCut, Pileup);
    // // makeROCplots("2016main303846", FileDate, ExtraCut, Pileup);
    // makeROCplots("2017", FileDate, ExtraCut, Pileup);
    // makeROCplots("2018", FileDate, ExtraCut, Pileup);
    // Pileup = "lowlow";
    // makeROCplots("2018", FileDate, ExtraCut, Pileup);
    // Pileup = "low";
    // makeROCplots("2017", FileDate, ExtraCut, Pileup);
    // // makeROCplots("2018", FileDate, ExtraCut, Pileup);
    // Pileup = "medium";
    // makeROCplots("2017", FileDate, ExtraCut, Pileup);
    // Pileup = "high";
    // makeROCplots("2017", FileDate, ExtraCut, Pileup);

    }
