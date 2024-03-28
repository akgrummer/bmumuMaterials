#include<TMath.h>
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasLabels.C"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasLabels.h"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasStyle.C"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasStyle.h"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasUtils.C"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasUtils.h"

//This script is based on KSTestEvaluationStep.cpp - 
// in reality the KS test should be used for "test" step, so the name is changed.

Char_t classNameTest;
TString ATestString;
Int_t classIDTest(0);
Float_t BDTvarTest(0.0);
Float_t TestWeight(0.);
vector <Float_t> bkgBDTtest;
vector <Float_t> sigBDTtest;
vector <Float_t> bkgBDTtestWeight;
vector <Float_t> sigBDTtestWeight;

Char_t classNameTrain;
TString ATrainString;
Int_t classIDTrain(0);
Float_t BDTvarTrain(0.0);
Float_t TrainWeight(0.);

vector <Float_t> bkgBDTtrain;
vector <Float_t> sigBDTtrain;
vector <Float_t> bkgBDTtrainWeight;
vector <Float_t> sigBDTtrainWeight;

Double_t BDTvarBkg(0.0);
Double_t BDTvarSig(0.0);

Double_t CombWeights(0.0);
Double_t PVWeights(0.0);
Double_t NPVweight(0.0);
Float_t Muon1_reco_eff_sf(0.0);
Float_t Muon2_reco_eff_sf(0.0);
Float_t Muon1_trigger_sf(0.0);
Float_t Muon2_trigger_sf(0.0);

vector <Double_t> bkgBDT;
vector <Double_t> sigBDT;
float B_MUCALC_massBkg;
float B_MUCALC_massSig;


TMultiGraph *mg;
TGraphAsymmErrors *gr1;

// void PlotBDTvariables(Float_t bkgBDTtest,
//                       Float_t sigBDTtest,
//                       Float_t bkgBDTtrain,
//                       Float_t sigBDTtrain);
TString GetDrawCommand(TString bname, Int_t numberBins, Double_t binMin, Double_t binMax , TString histName){
TString DrawCommand("");
DrawCommand = bname + ">>"+histName;
if (numberBins > 0 ){
        DrawCommand+=("(");
        DrawCommand+=numberBins;
        DrawCommand+=",";
        DrawCommand+=binMin;
        DrawCommand+=",";
        DrawCommand+=binMax;
        DrawCommand+=")";
    }
return DrawCommand;
}

void CreateAndSaveFiles(TString RunConfig, TCut MCWeight){
    SetAtlasStyle();
    // TString RunConfig("");
    // RunConfig = "Custom";
    // RunConfig = "Loose";
    // RunConfig = "Run1";
    // RunConfig = "Nom";
    cout<<"input vars: "<<RunConfig<<endl;
TString idir = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/AnalysisNtuples2020/v4/";
TString odir = "/afs/cern.ch/user/a/agrummer/www/bmumu2020/BDT/BDToutput/2020Jun16/";
TString odir2 = "/afs/cern.ch/user/a/agrummer/www/bmumu2020/BDT/BDToutput/2020Jun26/";
TString odir3 = "/afs/cern.ch/user/a/agrummer/www/bmumu2020/BDT/BDToutput/2020July16/";
TString odir4 = "/afs/cern.ch/user/a/agrummer/www/bmumu2020/BDT/BDToutput/2020July22/";
TString odir5 = "/afs/cern.ch/user/a/agrummer/www/bmumu2020/BDT/BDToutput/2020Aug6/";
TString ofileName("");
TString filenameBkg(""),filenameSig("");
if(RunConfig.EqualTo("Nom")){
    filenameSig = idir + "LASTskim.user.agrummer.mcBsmumu.merged_BDT2020_out_Nom.root";
    filenameBkg  = idir + "LASTskim.user.agrummer.Data1516.merged_BDT2020_out_Nom.root";
    ofileName = odir + "out_Nom/EvalROC_accept_error.root";
}
if(RunConfig.EqualTo("Custom")){
    filenameSig = idir + "LASTskim.user.agrummer.mcBsmumu.merged_BDT2020_out_Custom.root";
    filenameBkg  = idir + "LASTskim.user.agrummer.Data1516.merged_BDT2020_out_Custom.root";
    ofileName = odir + "out_Custom/EvalROC_accept_error.root";
}
if(RunConfig.EqualTo("Loose")){
    filenameSig = idir + "LASTskim.user.agrummer.mcBsmumu.merged_BDT2020_out_Loose.root";
    filenameBkg  = idir + "LASTskim.user.agrummer.Data1516.merged_BDT2020_out_Loose.root";
    ofileName = odir + "out_Loose/EvalROC_accept_error.root";
}
if(RunConfig.EqualTo("Run1")){
    // filenameSig = idir + "LASTskim.user.agrummer.mcBsmumu.merged_BDT2020_out_Run1.root";
    // filenameBkg  = idir + "LASTskim.user.agrummer.Data1516.merged_BDT2020_out_Run1.root";
    filenameSig = idir + "LASTskim.user.agrummer.mcBsmumu.merged.2.NPVweight_BDT2020_out_Run1.root";
    filenameBkg  = idir + "LASTskim.user.agrummer.Data1516.merged.2_BDT2020_out_Run1.root";
    ofileName = odir + "out_Run1/EvalROC_accept_error.root";
}
  if (RunConfig.EqualTo("Run1privxmu")){
    odir = odir2;
    filenameSig = idir + "LASTskim.user.agrummer.mcBsmumu.merged_BDT2020_out_Run1privxmu.root";
    filenameBkg  = idir + "LASTskim.user.agrummer.Data1516.merged_BDT2020_out_Run1privxmu.root";
    ofileName = odir + "out_Run1privxmu/EvalROC_accept_error.root";
  }
  if (RunConfig.EqualTo("Run1nPV")){
    odir = odir2;
    filenameSig = idir + "LASTskim.user.agrummer.mcBsmumu.merged_BDT2020_out_Run1nPV.root";
    filenameBkg  = idir + "LASTskim.user.agrummer.Data1516.merged_BDT2020_out_Run1nPV.root";
    ofileName = odir + "out_Run1nPV/EvalROC_accept_error.root";
  }
  if (RunConfig.EqualTo("BestSep")){
    odir = odir2;
    filenameSig = idir + "LASTskim.user.agrummer.mcBsmumu.merged_BDT2020_out_BestSep.root";
    filenameBkg  = idir + "LASTskim.user.agrummer.Data1516.merged_BDT2020_out_BestSep.root";
    ofileName = odir + "out_BestSep/EvalROC_accept_error.root";
  }
  if (RunConfig.EqualTo("Run1Custom")){
    odir = odir2;
    filenameSig = idir + "LASTskim.user.agrummer.mcBsmumu.merged_BDT2020_out_Run1Custom.root";
    filenameBkg  = idir + "LASTskim.user.agrummer.Data1516.merged_BDT2020_out_Run1Custom.root";
    ofileName = odir + "out_Run1Custom/EvalROC_accept_error.root";
  }  
  if (RunConfig.EqualTo("Run1privxmu_round")){
    odir = odir3;
    filenameSig = idir + "LASTskim.user.agrummer.mcBsmumu.merged.2.NPVweight_BDT2020_out_Run1privxmu_round.root";
    filenameBkg  = idir + "LASTskim.user.agrummer.Data1516.merged.2_BDT2020_out_Run1privxmu_round.root";
    ofileName = odir3 + "out_Run1privxmu_round/EvalROC_accept_error.root";
  }
  if (RunConfig.EqualTo("Run1nPV_npvweights")){
    odir = odir3;
    filenameSig = idir + "LASTskim.user.agrummer.mcBsmumu.merged.2.NPVweight_BDT2020_out_Run1nPV_npvweights.root";
    filenameBkg  = idir + "LASTskim.user.agrummer.Data1516.merged.2_BDT2020_out_Run1nPV_npvweights.root";
    ofileName = odir3 + "out_Run1nPV_npvweights/EvalROC_accept_error.root";
  }
  if (RunConfig.EqualTo("Run1_npvweights")){
    odir = odir4;
    filenameSig = idir + "LASTskim.user.agrummer.mcBsmumu.merged.2.NPVweight_BDT2020_out_Run1_npvweights.root";
    filenameBkg  = idir + "LASTskim.user.agrummer.Data1516.merged.2_BDT2020_out_Run1_npvweights.root";
    ofileName = odir + "out_Run1_npvweights/EvalROC_accept_error.root";
  }
  if (RunConfig.EqualTo("Custom_privxmu")){
    odir = odir5;
    filenameSig = idir + "LASTskim.user.agrummer.mcBsmumu.merged.2.NPVweight_BDT2020_Custom_privxmu.root";
    filenameBkg  = idir + "LASTskim.user.agrummer.Data1516.merged.2_BDT2020_Custom_privxmu.root";
    ofileName = odir + "Custom_privxmu/EvalROC_accept_error.root";
  }
  if (RunConfig.EqualTo("Custom_nPV")){
    odir = odir5;
    filenameSig = idir + "LASTskim.user.agrummer.mcBsmumu.merged.2.NPVweight_BDT2020_Custom_nPV.root";
    filenameBkg  = idir + "LASTskim.user.agrummer.Data1516.merged.2_BDT2020_Custom_nPV.root";
    ofileName = odir + "Custom_nPV/EvalROC_accept_error.root";
  }

TCut DataWeight("");

TFile* ifilenameBkg = new TFile(filenameBkg);
TFile* ifilenameSig = new TFile(filenameSig);

TTree *EvalTreeBkg = (TTree*)ifilenameBkg->Get("T_mv");
// EvalTreeBkg->SetBranchAddress("BDT_bb_2016",&BDTvarBkg);
EvalTreeBkg->SetBranchAddress("BDT_bb_2020",&BDTvarBkg);
EvalTreeBkg->SetBranchAddress("B_MUCALC_mass",&B_MUCALC_massBkg);


TTree *EvalTreeSig = (TTree*)ifilenameSig->Get("T_mv");
EvalTreeSig->SetBranchAddress("BDT_bb_2020",&BDTvarSig);

EvalTreeSig->SetBranchAddress("CombWeights",&CombWeights);
EvalTreeSig->SetBranchAddress("PVWeights",&PVWeights);
EvalTreeSig->SetBranchAddress("NPVweight",&NPVweight);
EvalTreeSig->SetBranchAddress("Muon1_reco_eff_sf",&Muon1_reco_eff_sf);
EvalTreeSig->SetBranchAddress("Muon2_reco_eff_sf",&Muon2_reco_eff_sf);
EvalTreeSig->SetBranchAddress("Muon1_trigger_sf",&Muon1_trigger_sf);
EvalTreeSig->SetBranchAddress("Muon2_trigger_sf",&Muon2_trigger_sf);

EvalTreeSig->SetBranchAddress("B_MUCALC_mass",&B_MUCALC_massSig);

cout<<"EvalTreeBkg Entries: "<<EvalTreeBkg->GetEntries()<<endl;
cout<<"EvalTreeSig Entries: "<<EvalTreeSig->GetEntries()<<endl;
    
for(int i=0; i < EvalTreeBkg->GetEntries(); i++){
    EvalTreeBkg->GetEntry(i);
    if (B_MUCALC_massBkg <=5526.0) continue;
    bkgBDT.push_back(BDTvarBkg);
      }

for(int i=0; i < EvalTreeSig->GetEntries(); i++){
    EvalTreeSig->GetEntry(i);
    sigBDT.push_back(BDTvarSig);
      }

cout<<"bkg vector size: "<<bkgBDT.size()<<endl;
cout<<"sig vector size: "<<sigBDT.size()<<endl;
cout<<"bkg+sig vector size: "<<bkgBDT.size() + sigBDT.size()<<endl;

sort(sigBDT.begin(), sigBDT.end());
sort(bkgBDT.begin(), bkgBDT.end());
vector<Double_t> vec = sigBDT;
vec.insert( vec.end(), bkgBDT.begin(), bkgBDT.end() );//merge sig and bkg vectors
sort(vec.begin(), vec.end());
vec.erase( unique( vec.begin(), vec.end() ), vec.end() );//select unique values in full vector for hist bins
cout<<" vec size (sig+bkg)  "<<vec.size()<<endl;
vec.push_back(vec.back()+ 0.01);
cout<<" vec size + 1 "<<vec.size()<<endl;
Double_t* b = &vec[0];// the array that the vector points to!!!
sort(b, b + vec.size());


vector<Double_t> sigBDTDouble(sigBDT.begin(), sigBDT.end());
vector<Double_t> bkgBDTDouble(bkgBDT.begin(), bkgBDT.end());
////////PLOTTING
TCanvas* c1;
TH1F *hret;
TH1F *hretSig(NULL);
TH1F *hretBkg(NULL);
TH1F *hret2;
TH1F *hret3;
TH1F *hret4;
Double_t yHeight;
TLegend* leg;
TString hretLeg;
TString hret2Leg;
TString hret3Leg;
TString hret4Leg;
Double_t sigTestCandidates;
Double_t bkgTestCandidates;
Double_t sigTrainCandidates;
Double_t bkgTrainCandidates;
Double_t kolS;
Double_t kolB;
TString tex3text;
TLatex *tex3;
int NumberOfBins;


NumberOfBins = 100;
c1 = new TCanvas("c1", "BDT Variable",0.,0., 800, 600);
// hretSig = new TH1F("Name", "title", NumberOfBins, vec[0], vec.back());
// hretBkg = new TH1F("Name2", "title2", NumberOfBins, vec[0], vec.back());

TString BDTbranchName = "BDT_bb_2020";
TString SigHistName = "hretSig";
TString BkgHistName = "hretBkg";
EvalTreeSig->Draw(GetDrawCommand(BDTbranchName, NumberOfBins, vec[0], vec.back(), SigHistName), MCWeight, "egoff");
hretSig = (TH1F*)gDirectory->Get("hretSig");
EvalTreeBkg->Draw(GetDrawCommand(BDTbranchName, NumberOfBins, vec[0], vec.back(), BkgHistName), DataWeight, "egoff");
hretBkg = (TH1F*)gDirectory->Get("hretBkg");
hretSig->Sumw2();
hretBkg->Sumw2();
// for(int i = 0; i<EvalTreeSig->GetEntries(); i++){
//     EvalTreeSig->GetEntry(i);
//     hretSig->Fill(BDTvarSig, MCWeights);
// }
// for(int i = 0; i<EvalTreeBkg->GetEntries(); i++){
//     EvalTreeBkg->GetEntry(i);
//     if (B_MUCALC_massBkg <=5526.0) continue;
//     hretBkg->Fill(BDTvarBkg);
// }
hretSig->Scale(1.0/hretSig->Integral(0, NumberOfBins));
hretSig->Draw("hist");
hretSig->SetLineColor(4);

hretBkg->Scale(1.0/hretBkg->Integral(0, NumberOfBins));
hretBkg->Draw("hist same");
hretBkg->SetLineColor(2);

hretSig->GetYaxis()->SetTitle("Events");
hretSig->GetXaxis()->SetTitle("BDT Variable");

yHeight = hretBkg->GetMaximum();
hretSig->GetYaxis()->SetRangeUser(0, yHeight*3/2);
leg = new TLegend(0.218045, 0.756522, 0.418546, 0.909565,NULL,"brNDC");

leg->AddEntry(hretSig, "Signal Eval. Sample","l");
leg->AddEntry(hretBkg, "Background Eval. Sample","l");
// leg->AddEntry(hret3, hret3Leg.Data(),"p");
// leg->AddEntry(hret4, hret4Leg.Data(),"p");
leg->SetBorderSize(0);  // no border
leg->SetLineColor(0);
leg->SetFillColor(0);
leg->SetTextSize(0.034468);
leg->Draw();


//Set these values by hand

Double_t BDTCutAll = -1;
//without weights - for May16 optimization file
// Double_t BDTCut18 = 0.440674;
// Double_t BDTCut36 = 0.328887;
// Double_t BDTCut54 = 0.236947;
//with DDW+QLC:
// Double_t BDTCut18 = 0.444896;
// Double_t BDTCut36 = 0.335002;
// Double_t BDTCut54 = 0.234417;
//with npv:
// Double_t BDTCut18 = 0.392569;
// Double_t BDTCut36 = 0.283511;
// Double_t BDTCut54 = 0.184143;
//officialMay24 With Weights
// Double_t BDTCut18 = 0.454493;
// Double_t BDTCut36 = 0.346763;
// Double_t BDTCut54 = 0.244674;
//June 12 new strategy
//
// Double_t BDTCut18 = 0.424441;
// Double_t BDTCut36 = 0.341969;
// Double_t BDTCut54 = 0.258933;
 Double_t BDTCut18, BDTCut36, BDTCut54;
//  // Run1privxmu_round:
//  BDTCut18 = 0.417643;
//  BDTCut36 = 0.346076;
//  BDTCut54 = 0.267268;
// // Run1nPV_npvweights
//  // BDTCut18 = 0.420502;
//  // BDTCut36 = 0.348225;
//  // BDTCut54 = 0.26861;
//  //run1:
//  // BDTCut18 = 0.429503;
//  // BDTCut36 = 0.353729;
//  // BDTCut54 = 0.272042;
    // "Custom_privxmu"
  // BDTCut18 = 0.420502;
 // BDTCut36 = 0.348225;
 // BDTCut54 = 0.26861;
    // "Custom_nPV";
  // BDTCut18 = 0.420502;
 // BDTCut36 = 0.348225;
 // BDTCut54 = 0.26861;
// TLine *line1;
// TLine *line2;
// TLine *line3;
// line1 = new TLine(BDTCut18,0.,BDTCut18,yHeight*3/2);
// line1->SetLineColorAlpha(kBlack, 0.4);
// line1->Draw();
// line2 = new TLine(BDTCut36,0.,BDTCut36,yHeight*3/2);
// line2->SetLineColorAlpha(kBlack, 0.4);
// line2->Draw();
// line3 = new TLine(BDTCut54,0.,BDTCut54,yHeight*3/2);
// line3->SetLineColorAlpha(kBlack, 0.4);
// line3->Draw();




// //Note, the hist test gets closer to the unbinned scenerio with higher number of bins. 
// // With low number of bins the test gets closer to 1
// // The option "X" provides a pseudo test, but seems to effect the the next instance of the test
// kolS = hret3->KolmogorovTest( hret );
// kolB = hret4->KolmogorovTest( hret2 );

// // TString tex3text = Form( "K-S test: sig. (bkg.) prob. = %5.3g (%5.3g)", KSvalSig, KSvalBkg );
// // tex3text = Form( "K-S test: sig. (bkg.) prob. = %5.3g (%5.3g)", kolS, kolB );
// // // tex3text+=kolS;
// // tex3 = new TLatex(-0.205266, yHeight + yHeight*0.06,tex3text.Data());
// // tex3->SetTextFont(62);
// // tex3->SetTextSize(0.034468);
// // tex3->SetLineWidth(2);
// // tex3->Draw();
// // Double_t kolS2 = hret->KolmogorovTest( hret3 );

// cout<<"kolS: "<< kolS<< endl;
// // cout<<kolS2<<endl;
// cout<<"kolB: "<< kolB << endl;


c1->SaveAs(odir + "out_"+RunConfig+"/BDTvariableWeights.pdf"); //odir is set to odir4 now.

delete c1;
// delete c2;
return 0;
}

void EvalStep_BDTvar(){
    SetAtlasStyle();
    TString RunConfig("");
    TCut MCWeightsNPV = "NPVweight*CombWeights*PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf*Muon1_trigger_sf*Muon2_trigger_sf";
    TCut MCWeightsNom = "CombWeights*PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf*Muon1_trigger_sf*Muon2_trigger_sf";
    // RunConfig = "Custom";
    // CreateAndSaveFiles(RunConfig, MCWeightsNom);
    // // RunConfig = "Loose";
    // // CreateAndSaveFiles(RunConfig);
    RunConfig = "Run1";
    CreateAndSaveFiles(RunConfig, MCWeightsNom);
    // // RunConfig = "Nom";
    // // CreateAndSaveFiles(RunConfig);
    // // RunConfig = "Run1privxmu";
    // // CreateAndSaveFiles(RunConfig);
    // // RunConfig = "Run1nPV";
    // // CreateAndSaveFiles(RunConfig);
    // // RunConfig = "BestSep";
    // // CreateAndSaveFiles(RunConfig);
    // // RunConfig = "Run1Custom";
    RunConfig = "Run1privxmu_round";
    CreateAndSaveFiles(RunConfig, MCWeightsNom);
    // // RunConfig = "Run1_npvweights";// don't need roc for this - just for efficiency studies...
    // // CreateAndSaveFiles(RunConfig, MCWeightsNPV);
    RunConfig = "Run1nPV_npvweights";//need to include NPVweight in ROCsig histogram
    CreateAndSaveFiles(RunConfig, MCWeightsNPV);
    // // cout<<"input vars: "<<RunConfig<<endl;
    RunConfig = "Custom_privxmu";//need to include NPVweight in ROCsig histogram
    CreateAndSaveFiles(RunConfig, MCWeightsNom);
    RunConfig = "Custom_nPV";//need to include NPVweight in ROCsig histogram
    CreateAndSaveFiles(RunConfig, MCWeightsNPV);
}