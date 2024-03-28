#include<TMath.h>
#include "/afs/cern.ch/user/a/agrummer/www/bmumu/AnalysisTools/Utils/AtlasStyle/AtlasLabels.C"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu/AnalysisTools/Utils/AtlasStyle/AtlasLabels.h"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu/AnalysisTools/Utils/AtlasStyle/AtlasUtils.C"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu/AnalysisTools/Utils/AtlasStyle/AtlasUtils.h"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu/AnalysisTools/Utils/AtlasStyle/AtlasStyle.C"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu/AnalysisTools/Utils/AtlasStyle/AtlasStyle.h"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu/IsoVarROCs/v8IsoScripts/Iso_MultiROCs.h"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu/IsoVarROCs/v8IsoScripts/getHistoFromTree.C"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu/IsoVarROCs/atlasLabel.C"
// #include "Iso_logAccept_ROCs_Module.C"
// #include "Iso_logAccept_ROCs.C"
// #include "Iso_logAccept_ROCs_Reverse.cpp"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu/IsoVarROCs/Iso_logAccept_ROCs_errors_Reverse.C"

void makeROCplots(TString theYear = "", TString FileDate = "", TString ExtraCut = "", TString Pileup = ""){
    SetAtlasStyle();
    //this folder was renamed to:
    // /eos/home-a/agrummer/BsmumuData/FinalSkim/v3
// TString DirName = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/";
// TString DirName = "/eos/home-a/agrummer/BsmumuData/FinalSkim/v5/";
TString DirName = "/eos/home-a/agrummer/BsmumuData/FinalSkim/v6/";


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
} 

TCut run1Weight;
// CutRun1
CutRun1 = CutRun1dummy;
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
    grROC_Run1 = Iso_logAccept_ROCs_reverse(EvalTreeSig_Run1, EvalTreeBkg_Run1,
                              closeTrkNtrks, CutRun1,
                              closeTrkNtrks, CutRun1,
                              run1Weight, ColorIndex);
}
ifilenameBkg_Run1->Close();
ifilenameSig_Run1->Close();


TString filenameBkg = DirName + theYear+"All/LASTskim_"+theYear+"_All_"+FileDate+".root";
TString filenameSig("");
TString mcName("");
TString runName("");
TCut RunNumberCut("");
if (theYear.EqualTo("2016")){
 mcName = "MC16a";
 runName = "2016 Run 302393";
 RunNumberCut = "run_number==302393";
 // filenameSig = DirName + mcName+"All/LASTskim_"+mcName+"_All_2019Jun5.root";
 // filenameSig = DirName + mcName+"All/LASTskim_"+mcName+"_All_2019Jun6.root";
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
 filenameSig = DirName + mcName+"All/LASTskim_"+mcName+"_All_"+FileDate+".root";
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
TGraph* grROC_Default = Iso_logAccept_ROCs_reverse(EvalTreeSig, EvalTreeBkg,
                              closeTrkNtrks, CutAddSig_Default,
                              closeTrkNtrks, CutAddBkg_Default,
                              Weight_Default, ColorIndex);
///////1////////closeTrkNtrks_TTVA_loose_c2
ColorIndex = 1;
TGraph* grROC_TTVA_loose_c2 = Iso_logAccept_ROCs_reverse(EvalTreeSig, EvalTreeBkg,
                              closeTrkNtrks_TTVA_loose_c2, CutAddSig_Default,
                              closeTrkNtrks_TTVA_loose_c2, CutAddBkg_Default,
                              Weight_Default, ColorIndex);
///////2////////closeTrkNtrks_TTVA_custom_c2
ColorIndex = 2;
TGraph* grROC_TTVA_custom_c2 = Iso_logAccept_ROCs_reverse(EvalTreeSig, EvalTreeBkg,
                              closeTrkNtrks_TTVA_custom_c2, CutAddSig_Default,
                              closeTrkNtrks_TTVA_custom_c2, CutAddBkg_Default,
                              Weight_Default, ColorIndex);
///////3////////closeTrkNtrks_all_c1
// ColorIndex = 4;
// TGraph* grROC_all_c1 = Iso_logAccept_ROCs_reverse(EvalTreeSig, EvalTreeBkg,
//                               closeTrkNtrks_all_c1, CutAddSig_Default,
//                               closeTrkNtrks_all_c1, CutAddBkg_Default,
//                               Weight_Default, ColorIndex);
// ///////4////////closeTrkNtrks_all_c2
// ColorIndex = 5;
// TGraph* grROC_all_c2 = Iso_logAccept_ROCs_reverse(EvalTreeSig, EvalTreeBkg,
//                               closeTrkNtrks_all_c2, CutAddSig_Default,
//                               closeTrkNtrks_all_c2, CutAddBkg_Default,
//                               Weight_Default, ColorIndex);



TCanvas* c2 = new TCanvas("c2", "ROC curve",0.,0., 800, 600);
c2->SetLogy(1);
Double_t ymin = 1e-4;
Double_t ymax = 5e-1;
Double_t xmin = 0;
Double_t xmax = 0.8;
grROC_TTVA_loose_c2->GetXaxis()->SetLimits(xmin, xmax);// along X
grROC_TTVA_loose_c2->GetHistogram()->SetMaximum(ymax);   // along          
grROC_TTVA_loose_c2->GetHistogram()->SetMinimum(ymin);  //   YgrROC_TTVA_loose_c2->Draw("al2");
grROC_TTVA_loose_c2->Draw("al2");
grROC_TTVA_custom_c2->Draw("same l2");
// grROC_all_c2->Draw("same al2");
// grROC_all_c1->Draw("same l2");
// grROC_Run1->Draw("same l2");
// grROC_AllTrks_Chi6->Draw("same l");
// grROC_AllTrks_Chi5->Draw("same l");
// grROC_AllTrks_Chi4->Draw("same l");
grROC_Default->Draw("same l2");
// grROC_2017->Draw("same l");
// grROC_2018->Draw("same l");
if (!Pileup.EqualTo("high")){grROC_Run1->Draw("same l2");}
atlasLabel(0.5, 0.45, false, true, 1, true, false, true);

TLegend* leg2;
// TString theTracks="";
// if (FileDate.EqualTo("2019Jun6")){
//     theTracks = " #chi^{2}_{SV}<=1";
// }
// if (FileDate.EqualTo("2019Jun17")){
//     theTracks = " #chi^{2}_{SV}<=2";
// }
// if (FileDate.EqualTo("2019Jun17_2")) {
//     theTracks = " #chi^{2}_{SV}<=4";
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
leg2 = new TLegend(0.47, 0.2, 0.67, 0.44,NULL,"brNDC");
// leg2->SetHeader("Number of Close Tracks to B DV");
leg2->SetHeader("NcloseTrks "+PileupHeader+ExtraCut);
// leg2->AddEntry(grROC_Run1, "MC16a + Run 1","l");
// leg2->AddEntry(grROC_Run1, "MC16a + 15+16 Dataset","l");
// TString Run("");
if (!Pileup.EqualTo("high")){
        leg2->AddEntry(grROC_Run1, "MC12 + Run 1","l");
    }
TString legName1 = mcName + " + "+ runName + " Default";
leg2->AddEntry(grROC_Default, legName1,"l");
TString legName2 = mcName + " + "+ runName + " Loose TVA WP + #chi^{2}_{SV}<2";
leg2->AddEntry(grROC_TTVA_loose_c2, legName2,"l");
TString legName3 = mcName + " + "+ runName + " Custom TVA WP + #chi^{2}_{SV}<2";
leg2->AddEntry(grROC_TTVA_custom_c2, legName3,"l");
// TString legName4 = mcName + " + "+ runName + " Old Assoc. + #chi^{2}_{SV}<1";
// leg2->AddEntry(grROC_all_c1, legName4,"l");
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
TString OutdirName = "/afs/cern.ch/user/a/agrummer/www/bmumu/IsoVarROCs/";
// TString Tag = "Tracks";
// TString Tag = "TTVA_Chi2"+theYear+"_logAccept_2019Jun3";
// TString Tag = "NcloseTracks_TTVA"+theYear+"_logAccept_2019Jun6";
// TString Tag = "NcloseTracks_TTVA"+theYear+"_logAccept_2019Jun10";
// TString Tag = "NcloseTracks_TTVA"+theYear+"_logAccept_2019Jun12";
// TString Tag = "NcloseTracks_TTVA"+theYear+"_logAccept_2019Jun12_2";//jun12_2 made with jun 6 inputs
TString Tag = "NcloseTracks_TTVA"+theYear+"_logAccept_"+FileDate+"_"+Pileup;//jun12_2 made with jun 6 inputs
TString typeDir="Accept";
TString varDir="NcloseTracks";
// c2->SaveAs(OutdirName + "Figures/ROC_2019Jun3/ROC_"+Tag+".pdf");
// c2->SaveAs(OutdirName + "Figures/ROC_2019July17/ROC_"+Tag+ExtraCut+".pdf");
// c2->SaveAs(OutdirName + "Figures/ROC_2019July30/ROC_"+Tag+ExtraCut+".pdf");
// c2->SaveAs(OutdirName + "Figures/ROC_2019Nov21/ROC_"+Tag+ExtraCut+".pdf");
// c2->SaveAs(OutdirName + "Figures/ROC_2019Nov21_v7/"+varDir+"/"+typeDir+"/ROC_"+Tag+ExtraCut+".pdf");
// c2->SaveAs(OutdirName + "Figures/ROC_2019Nov21_v7_2/"+varDir+"/"+typeDir+"/ROC_"+Tag+ExtraCut+".pdf");
c2->SaveAs(OutdirName + "Figures/ROC_2020Mar24_v7_repeat/"+varDir+"/"+typeDir+"/ROC_"+Tag+ExtraCut+".pdf");
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

void NcloseTracks_logAccept_ROCs_v7_2(){
//     // ////TString FileDate = "2019Jun12"; //not good!! included chi2 PV cut
//     TString FileDate = "2019Jun6"; //NcloseTrks chi2SV <=1
// // TString FileDate = "2019Jun17"; //NcloseTrks chi2SV <=2
// // TString FileDate = "2019Jun17_2"; //NcloseTrks chi2SV <=4
//     makeROCplots("2016", FileDate);
//     makeROCplots("2017", FileDate);
//     makeROCplots("2018", FileDate);

TString FileDate = ""; //NcloseTrks chi2SV <=1
// FileDate = "2019Jun6"; //NcloseTrks chi2SV <=1
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
FileDate = "2019Dec5"; 
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
