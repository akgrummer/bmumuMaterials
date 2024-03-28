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
#include "Iso_logAccept_ROCs_errors.C"
#include "Iso_logAccept_ROCs_errors_Reverse.C"

TGraphErrors* RetrieveTGraph(TString theYear="", VariableInfo myVar=Bisolation, Int_t ColorIndex = 0, TCut PUcut= "", TString ExtraCut = "", TString FileDate="", TString theVar=""){
TString DirName = "/eos/home-a/agrummer/BsmumuData/FinalSkim/v4/";
TString vBDT = "";
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
TCut myWeight = "PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
TCut CutAddSig = CutAdd*ExtraCut*PUcut;//MC run number cut already made on input files
TCut CutAddBkg = CutAdd*ExtraCut*PUcut;
TGraphErrors* grROC(NULL);
if(theVar.EqualTo("nCloseTrks")){
    grROC = Iso_logAccept_ROCs_reverse(EvalTreeSig_2016, EvalTreeBkg_2016,
                  myVar, CutAddSig,
                  myVar, CutAddBkg,
                  myWeight, ColorIndex);
}else{
    grROC = Iso_logAccept_ROCs(EvalTreeSig_2016, EvalTreeBkg_2016,
                  myVar, CutAddSig,
                  myVar, CutAddBkg,
                  myWeight, ColorIndex);
}

ifilenameBkg_2016->Close();
ifilenameSig_2016->Close();

return grROC;
}


TGraphErrors* RetrieveTGraphRun1(VariableInfo myVar=Bisolation, Int_t ColorIndex = 0, TCut PUcut= "", TString ExtraCut = "", TString FileDate="", TString theVar=""){
TString DirName = "/eos/home-a/agrummer/BsmumuData/FinalSkim/v4/";

TString vBDT = "";
TCut run1Weight;
// CutRun1
CutRun1 = CutRun1dummy;
CutRun1 = CutRun1*ExtraCut;
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

TGraphErrors* grROC(NULL);
if(theVar.EqualTo("nCloseTrks")){
    grROC = Iso_logAccept_ROCs_reverse(EvalTreeSig_Run1, EvalTreeBkg_Run1,
                  myVar, PUcut*CutRun1,
                  myVar, PUcut*CutRun1,
                  run1Weight, ColorIndex);
}else{
    grROC = Iso_logAccept_ROCs(EvalTreeSig_Run1, EvalTreeBkg_Run1,
                  myVar, PUcut*CutRun1,
                  myVar, PUcut*CutRun1,
                  run1Weight, ColorIndex);
}
ifilenameBkg_Run1->Close();
ifilenameSig_Run1->Close();

return grROC;
}


void makeROCplots(TString DataType="", TString theVar = "", 
                    TString FileDate = "", 
                    TString ExtraCut = "", 
                    VariableInfo myVar = Bisolation, 
                    bool Run1set = false){
    SetAtlasStyle();
    //this folder was renamed to:
    // /eos/home-a/agrummer/BsmumuData/FinalSkim/v3
// TString DirName = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/";

TCut PUcut_lowlow = "";
TCut PUcut_low = "";
TCut PUcut_medium = "";
TCut PUcut_high = "";
PUcut_lowlow = ("PRIVX_mu >= 12. && PRIVX_mu <= 22.");
PUcut_low = ("PRIVX_mu >= 23. && PRIVX_mu <= 33.");
PUcut_medium = ("PRIVX_mu >= 34. && PRIVX_mu <= 44.");
PUcut_high = ("PRIVX_mu >= 45. && PRIVX_mu <= 55.");
TGraphErrors* grROC_lowlow(NULL);
TGraphErrors* grROC_low(NULL);
TGraphErrors* grROC_medium(NULL);
TGraphErrors* grROC_high(NULL);
Int_t ColorIndex(0);
if (!Run1set){
ColorIndex = 0;
grROC_lowlow = RetrieveTGraph("2018", myVar, ColorIndex, PUcut_lowlow, ExtraCut, FileDate, theVar);
ColorIndex = 1;
grROC_low = RetrieveTGraph("2017", myVar, ColorIndex, PUcut_low, ExtraCut, FileDate, theVar);
ColorIndex = 2;
grROC_medium = RetrieveTGraph("2017", myVar, ColorIndex, PUcut_medium, ExtraCut, FileDate, theVar);
ColorIndex = 3;
grROC_high = RetrieveTGraph("2017", myVar, ColorIndex, PUcut_high, ExtraCut, FileDate, theVar);
}else{
ColorIndex = 0;
grROC_lowlow = RetrieveTGraphRun1(myVar, ColorIndex, PUcut_lowlow, ExtraCut, FileDate, theVar);
ColorIndex = 1;
grROC_low = RetrieveTGraphRun1(myVar, ColorIndex, PUcut_low, ExtraCut, FileDate, theVar);
ColorIndex = 2;
grROC_medium = RetrieveTGraphRun1(myVar, ColorIndex, PUcut_medium, ExtraCut, FileDate, theVar);  
}

// //new file


TCanvas* c2 = new TCanvas("c2", "ROC curve",0.,0., 800, 600);
c2->SetLogy(1);
// grROC_low->Draw("ae3");
// grROC_2016_TTVA_custom->Draw("same e3");
// grROC_medium->Draw("same e3");
Double_t ymin(0.);
Double_t ymax(0.);
Double_t xmin(0.);
Double_t xmax(0.);
if(theVar.EqualTo("DOCA")){
    ymin = 2e-5;
    ymax = 5e-1;
    xmin = 0.;
    xmax = 0.8;
}else if(theVar.EqualTo("nCloseTrks")){
    ymin = 1e-4;
    ymax = 5e-1;
    xmin = 0;
    xmax = 0.8;
}else{
    ymin = 1e-3;
    ymax = 5e-1;
    xmin = 0;
    xmax = 0.8;
}
                 
grROC_lowlow->GetXaxis()->SetLimits(xmin, xmax);// along X
grROC_low->GetXaxis()->SetLimits(xmin, xmax);// along X
grROC_medium->GetXaxis()->SetLimits(xmin, xmax);// along X
if (!Run1set) grROC_high->GetXaxis()->SetLimits(xmin, xmax);// along X
grROC_lowlow->GetHistogram()->SetMaximum(ymax);   // along          
grROC_lowlow->GetHistogram()->SetMinimum(ymin);  //   Y
grROC_low->GetHistogram()->SetMaximum(ymax);   // along          
grROC_low->GetHistogram()->SetMinimum(ymin);  //   Y
grROC_medium->GetHistogram()->SetMaximum(ymax);   // along          
grROC_medium->GetHistogram()->SetMinimum(ymin);  //   Y
if (!Run1set) grROC_high->GetHistogram()->SetMaximum(ymax);   // along          
if (!Run1set) grROC_high->GetHistogram()->SetMinimum(ymin);  //   Y
grROC_lowlow->Draw("al2");
grROC_low->Draw("same l2");
grROC_medium->Draw("same l2");
if (!Run1set) grROC_high->Draw("same l2");

TLegend* leg2;


// leg2 = new TLegend(1, 0.06, 5, 0.08,NULL,"brNDC");
// leg2 = new TLegend(0.218045, 0.721739, 0.418546, 0.770435,NULL,"brNDC");

if(theVar.EqualTo("DOCA")){
    atlasLabel(0.5, 0.41, false, true, 1, true, false, true);
    leg2 = new TLegend(0.47, 0.2, 0.67, 0.4,NULL,"brNDC");

}else if(theVar.EqualTo("nCloseTrks")){
    atlasLabel(0.2, 0.45, false, true, 1, true, false, true);
    leg2 = new TLegend(0.218045, 0.2, 0.418546, 0.4,NULL,"brNDC");

}else{
    atlasLabel(0.5, 0.45, false, true, 1, true, false, true);
    leg2 = new TLegend(0.47, 0.2, 0.67, 0.44,NULL,"brNDC");
}


TString PileupHeader_lowlow;
TString PileupHeader_low;
TString PileupHeader_medium;
TString PileupHeader_high;
PileupHeader_lowlow = "12. #leq PRIVX_mu #leq 22.";
PileupHeader_low = "23. #leq PRIVX_mu #leq 33.";
PileupHeader_medium = "34. #leq PRIVX_mu #leq 44.";
PileupHeader_high = "45. #leq PRIVX_mu #leq 55.";

TString dummyVarName;
dummyVarName = myVar.name;
if (dummyVarName.EqualTo("B_iso_7_Chi2_5_LoosePt05")){
   leg2->SetHeader("2015+2016 Computation");
 
}else if (dummyVarName.EqualTo("B_iso_7_Chi2_5_MedPt05")){
   leg2->SetHeader("B Iso, Run 1");
}else if (dummyVarName.EqualTo("B_Iso_TTVA_custom")){
   leg2->SetHeader("B Iso, Custom TTVA WP");
}else if (dummyVarName.EqualTo("B_Iso_TTVA_custom_dr")){
   leg2->SetHeader("B Iso, Custom TTVA WP, #Delta R<1.0");
}else if (dummyVarName.EqualTo("B_Iso_all_c5")){
   leg2->SetHeader("B Iso, All Tracks, #chi^{2}_{PV} #leq 5");
}
else if (dummyVarName.EqualTo("closeTrkNtrksChi2")){
   if (!Run1set) leg2->SetHeader("N Close Trks, 2015+2016 Computation");
   else leg2->SetHeader("N Close Trks, Run 1");
}else if (dummyVarName.EqualTo("closeTrkNtrks_TTVA_custom_c1")){
   leg2->SetHeader("N Close Trks, Custom TTVA WP and #chi^{2}_{SV} #leq 1");
}else if (dummyVarName.EqualTo("closeTrkNtrks_TTVA_custom_c2")){
   leg2->SetHeader("N Close Trks, Custom TTVA WP and #chi^{2}_{SV} #leq 2");
}else if (dummyVarName.EqualTo("closeTrkNtrks_all_c1")){
   leg2->SetHeader("N Close Trks, Old Assoc., #chi^{2}_{SV} #leq 1");
}else if (dummyVarName.EqualTo("closeTrkNtrks_all_c2")){
   leg2->SetHeader("N Close Trks, Old Assoc., #chi^{2}_{PV} #leq 2");
}

else if (dummyVarName.EqualTo("closeTrkDOCA")){
   if (!Run1set) leg2->SetHeader("DOCA, 2015+2016 Computation");
   else leg2->SetHeader("DOCA, Run 1");
}else if (dummyVarName.EqualTo("closeTrkDOCA_TTVA_custom_c7")){
   leg2->SetHeader("DOCA, Custom TTVA WP, #chi^{2}_{SV} #leq 7");
}else if (dummyVarName.EqualTo("closeTrkDOCA_TTVA_custom_c2")){
   leg2->SetHeader("DOCA, Custom TTVA WP, #chi^{2}_{SV} #leq 2");
}else if (dummyVarName.EqualTo("closeTrkDOCA_all_c7")){
   leg2->SetHeader("DOCA, Old Assoc., #chi^{2}_{SV} #leq 7");
}else if (dummyVarName.EqualTo("closeTrkDOCA_all_c2")){
   leg2->SetHeader("DOCA, Old Assoc., #chi^{2}_{PV} #leq 2");
}

// leg2->AddEntry(grROC_Run1, "MC16a + Run 1","l");
// leg2->AddEntry(grROC_Run1, "MC16a + 15+16 Dataset","l");
// TString Run("");

// leg2->AddEntry(hRun1, ,"l");
leg2->AddEntry(grROC_lowlow, PileupHeader_lowlow,"l");
leg2->AddEntry(grROC_low, PileupHeader_low,"l");
leg2->AddEntry(grROC_medium, PileupHeader_medium,"l");
if (!Run1set) leg2->AddEntry(grROC_high, PileupHeader_high,"l");
leg2->SetBorderSize(0);  // no border
leg2->SetLineColor(0);
leg2->SetFillColor(0);
leg2->SetTextSize(0.025);
leg2->Draw();


// TString ofilenames = "Jun13MuIso_SidebandTrained/BDT1";//train3
TString OutdirName = "/afs/cern.ch/user/a/agrummer/www/bmumu/IsoVarROCs/";
// TString Tag = "Tracks_2016";
// TString Tag = "TTVA_Chi2"+theYear+"_2019Jun6";
TString Tag = "TTVA_Chi2_"+FileDate+"_";
Tag+="2019Aug13_";
Tag+=DataType;
Tag+="_";
if (Run1set){
 Tag+="Run1";   
}else{ 
Tag+=dummyVarName;
}
TString typeDir="";
if (DataType.EqualTo("ROC")){
    typeDir = "ROC";
}else{
    typeDir = "Accept";
}
TString varDir="";
if (theVar.EqualTo("nCloseTrks")){
    varDir = "NcloseTracks";
}else if (theVar.EqualTo("DOCA")){
    varDir = "DOCA";
}else{
    varDir = "BIso";
}
// c2->SaveAs(OutdirName + "Figures/ROC_2019Jun6/ROC_"+Tag+".pdf");


// c2->SaveAs(OutdirName + "Figures/ROC_2019Jun17/"+FileDate+"/ROC_"+Tag+".pdf");
// c2->SaveAs(OutdirName + "Figures/ROC_2019Jun27/ROC_"+Tag+".pdf");
// c2->SaveAs(OutdirName + "Figures/ROC_2019July17/ROC_"+Tag+ExtraCut+".pdf");
// c2->SaveAs(OutdirName + "Figures/ROC_2019July30/ROC_"+Tag+ExtraCut+".pdf");
c2->SaveAs(OutdirName + "Figures/ROC_2019Aug13/"+varDir+"/"+typeDir+"/ROC_"+Tag+ExtraCut+".pdf");
// TFile ofile(OutdirName + "RootFiles/ROC_"+Tag+".root", "recreate");
// // grROC_Run1->Write();
// grROC_low->Write();
// grROC_2016_AllTracks->Write();
// grROC_2016_AllTracks_PVweights->Write();
// // grROC_2017->Write();
// // grROC_2018->Write();

delete c2;
return 0;
}

void Iso_MultiROCs_TTVA_logAccept_v5(){
TString FileDate = ""; //ID hits revised run 1 with IBL included
    // makeROCplots("2016", FileDate);
    // makeROCplots("2017", FileDate);
    // makeROCplots("2018", FileDate);
TString ExtraCut = ""; 
// ExtraCut = "Lxy>0.2"; 
// ExtraCut = "a_2D<0.1"; 
TString Pileup = "";
TString whichVar = "";

// FileDate = "2019Jun27"; //ID hits like run 1 (without IBL)
// FileDate = "2019July17"; //ID hits like run 1 (without IBL)
 
    // makeROCplots("2016", FileDate, ExtraCut, Pileup);
    // Pileup = "lowlow";
    // makeROCplots("2018", FileDate, ExtraCut, Pileup);
    // Pileup = "low";
    // makeROCplots("2017", FileDate, ExtraCut, Pileup);
    // makeROCplots("2018", FileDate, ExtraCut, Pileup);
    // Pileup = "medium";
    // makeROCplots("2017", FileDate, ExtraCut, Pileup);
    bool Run1set(false);
    VariableInfo myVar = Bisolation;
    FileDate = "2019July30";

    whichVar = "BIso";
    myVar = Run1iso;
    Run1set = true;
    makeROCplots("accept", whichVar, FileDate, 
                    ExtraCut, myVar, Run1set);
    Run1set = false;

    myVar = Bisolation;
    makeROCplots("accept", whichVar, FileDate, 
                    ExtraCut, myVar, Run1set);
    myVar = B_Iso_TTVA_custom;
    makeROCplots("accept", whichVar, FileDate, 
                    ExtraCut, myVar, Run1set);
    myVar = B_Iso_TTVA_custom_dr;
    makeROCplots("accept", whichVar, FileDate, 
                    ExtraCut, myVar, Run1set);
    myVar = B_Iso_all_c5;
    makeROCplots("accept", whichVar, FileDate, 
                    ExtraCut, myVar, Run1set);
    // whichVar = "BIso";

    whichVar = "nCloseTrks";
    myVar = closeTrkNtrks_80;
    Run1set = true;
    makeROCplots("accept", whichVar, FileDate, 
                ExtraCut, myVar, Run1set);
    Run1set = false;

    myVar = closeTrkNtrks_80;
    makeROCplots("accept", whichVar, FileDate, 
                ExtraCut, myVar, Run1set);
    myVar = closeTrkNtrks_TTVA_custom_c1_80;
    makeROCplots("accept", whichVar, FileDate, 
                ExtraCut, myVar, Run1set);
    myVar = closeTrkNtrks_TTVA_custom_c2_80;
    makeROCplots("accept", whichVar, FileDate, 
                ExtraCut, myVar, Run1set);
    myVar = closeTrkNtrks_all_c1_80;
    makeROCplots("accept", whichVar, FileDate, 
                ExtraCut, myVar, Run1set);
    myVar = closeTrkNtrks_all_c2_80;
    makeROCplots("accept", whichVar, FileDate, 
                ExtraCut, myVar, Run1set);


    whichVar = "DOCA";
    myVar = closeTrkDOCA;
    Run1set = true;
    makeROCplots("accept", whichVar, FileDate, 
                ExtraCut, myVar, Run1set);
    Run1set = false;

    myVar = closeTrkDOCA;
    makeROCplots("accept", whichVar, FileDate, 
                ExtraCut, myVar, Run1set);
    myVar = closeTrkDOCA_TTVA_custom_c7;
    makeROCplots("accept", whichVar, FileDate, 
                ExtraCut, myVar, Run1set);
    myVar = closeTrkDOCA_TTVA_custom_c2;
    makeROCplots("accept", whichVar, FileDate, 
                ExtraCut, myVar, Run1set);
    myVar = closeTrkDOCA_all_c7;
    makeROCplots("accept", whichVar, FileDate, 
                ExtraCut, myVar, Run1set);
    myVar = closeTrkDOCA_all_c2;
    makeROCplots("accept", whichVar, FileDate, 
                ExtraCut, myVar, Run1set);
    myVar = closeTrkDOCA;
    makeROCplots("accept", whichVar, FileDate, 
                ExtraCut, myVar, Run1set);

    // makeROCplots("2017", FileDate, ExtraCut, Pileup);
    
}

