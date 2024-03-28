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

/////////////ROC
TH1F *hROCSig(NULL);
TH1F *hROCSig_w2(NULL);
TH1F *hROCBkg(NULL);

int plotBinVal = 5;
int NumberOfBinsROC = plotBinVal*10000;//need large number of bins to determine BDT cuts to hight precision.
//the histograms will be rebinned before weights and errors are computed - and before plotting and saving.
// hROCSig = new TH1F("NameROC", "titleROC", NumberOfBinsROC, vec[0], vec.back());
// hROCBkg = new TH1F("NameROC2", "titleROC2", NumberOfBinsROC, vec[0], vec.back());
// hROCSig->Sumw2();
// hROCBkg->Sumw2();
TString BDTbranchName = "BDT_bb_2020";
TString SigHistName = "hROCSig";
TString SigHistName_w2 = "hROCSig_w2";
TString BkgHistName = "hROCBkg";
EvalTreeSig->Draw(GetDrawCommand(BDTbranchName, NumberOfBinsROC, vec[0], vec.back(), SigHistName), MCWeight, "egoff");
hROCSig = (TH1F*)gDirectory->Get("hROCSig");
EvalTreeSig->Draw(GetDrawCommand(BDTbranchName, NumberOfBinsROC, vec[0], vec.back(), SigHistName_w2), MCWeight*MCWeight, "egoff");
hROCSig_w2 = (TH1F*)gDirectory->Get("hROCSig_w2");
EvalTreeBkg->Draw(GetDrawCommand(BDTbranchName, NumberOfBinsROC, vec[0], vec.back(), BkgHistName), DataWeight, "egoff");
hROCBkg = (TH1F*)gDirectory->Get("hROCBkg");

// for(int i = 0; i<EvalTreeSig->GetEntries(); i++){
//     EvalTreeSig->GetEntry(i);
//     // hROCSig->Fill(BDTvarSig, NPVweight*CombWeights*PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf*Muon1_trigger_sf*Muon2_trigger_sf);
//     // hROCSig->Fill(BDTvarSig, CombWeights*PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf*Muon1_trigger_sf*Muon2_trigger_sf);
//     hROCSig->Fill(BDTvarSig, MCWeights);
// }
// for(int i = 0; i<EvalTreeBkg->GetEntries(); i++){
//     EvalTreeBkg->GetEntry(i);
//     if (B_MUCALC_massBkg <=5526.0) continue;
//     hROCBkg->Fill(BDTvarBkg);
// }
// hROCSig->Scale(1.0/hROCSig->Integral(0, NumberOfBinsROC));
// hROCBkg->Scale(1.0/hROCBkg->Integral(0, NumberOfBinsROC));

vector<Double_t> SigTestEff;
vector<Double_t> BkgTestRej;
vector<Double_t> BkgTestEff;
vector<Double_t> SigTestEff_err;
vector<Double_t> BkgTestEff_err;

///////////////
//determine BDT cuts here:
for(int i = 0; i<NumberOfBinsROC; i++){
  // cout<<i<<endl;
  SigTestEff.push_back((hROCSig->Integral(NumberOfBinsROC-i, NumberOfBinsROC))/(hROCSig->Integral(0, NumberOfBinsROC)));
  BkgTestRej.push_back((1-(hROCBkg->Integral(NumberOfBinsROC-i, NumberOfBinsROC))/(hROCBkg->Integral(0, NumberOfBinsROC))));
  BkgTestEff.push_back((hROCBkg->Integral(NumberOfBinsROC-i, NumberOfBinsROC))/(hROCBkg->Integral(0, NumberOfBinsROC)));


  if ((SigTestEff[i] > 0.17995 && SigTestEff[i] < 0.18005) || (SigTestEff[i] > 0.35995 && SigTestEff[i] < 0.36005) || (SigTestEff[i] > 0.53995 && SigTestEff[i] < 0.54005)){
      cout<<"Bkg Rej= "<< BkgTestRej[i]<< " at a signal efficiency: " << SigTestEff[i] 
      << " BDT value: "<< hROCSig->GetXaxis()->GetBinCenter(NumberOfBinsROC-i)
      // <<" bkg: "<<hROCBkg->GetXaxis()->GetBinCenter(NumberOfBinsROC-i) 
      << endl;
      }
}

  SigTestEff.clear();
  BkgTestRej.clear();
  BkgTestEff.clear();
/////////////////
  // fill vectors for plotting
///rebinning:
hROCSig->Rebin(plotBinVal);
hROCSig_w2->Rebin(plotBinVal);
hROCBkg->Rebin(plotBinVal);
NumberOfBinsROC = NumberOfBinsROC/plotBinVal;
///
for(int i = 0; i<NumberOfBinsROC; i++){
  // cout<<i<<endl;
  SigTestEff.push_back((hROCSig->Integral(NumberOfBinsROC-i, NumberOfBinsROC))/(hROCSig->Integral(0, NumberOfBinsROC)));
  BkgTestRej.push_back((1-(hROCBkg->Integral(NumberOfBinsROC-i, NumberOfBinsROC))/(hROCBkg->Integral(0, NumberOfBinsROC))));
  BkgTestEff.push_back((hROCBkg->Integral(NumberOfBinsROC-i, NumberOfBinsROC))/(hROCBkg->Integral(0, NumberOfBinsROC)));
}
// cout<<SigTestEff.size()<<endl;
// this occurs before weighting - so 


vector<Double_t> wp;
vector<Double_t> w2p;
vector<Double_t> wm;
vector<Double_t> w2m;
vector<Double_t> w2;


for(int i = 0; i<NumberOfBinsROC; i++){
  BkgTestEff_err.push_back(sqrt((BkgTestEff[i]*(1-BkgTestEff[i]))/(hROCBkg->Integral(0, NumberOfBinsROC) ) ) );
  // cout << BkgTestEff[i]<< " "<< 1-BkgTestEff[i] << " " << hROCBkg->Integral(0, NumberOfBinsROC)<<" "<< BkgTestEff_err[i]<<endl;
  wp.push_back(hROCSig->Integral(NumberOfBinsROC-i, NumberOfBinsROC));
  w2p.push_back(hROCSig_w2->Integral(NumberOfBinsROC-i, NumberOfBinsROC));
  wm.push_back(hROCSig->Integral(0, NumberOfBinsROC-i));
  w2m.push_back(hROCSig_w2->Integral(0, NumberOfBinsROC-i));
  w2.push_back((hROCSig->Integral(0, NumberOfBinsROC))*(hROCSig->Integral(0, NumberOfBinsROC)));
}
for(int i = 0; i<NumberOfBinsROC; i++){
  SigTestEff_err.push_back(sqrt(w2p[i]*wm[i]*wm[i]+w2m[i]*wp[i]*wp[i])/w2[i] ) ;
  // cout <<SigTestEff[i]<<" "<<w2p[i] <<" " <<wp[i] <<" " << SigTestEff_err[i]<<" "<<endl;
    }


TCanvas* c2 = new TCanvas("c2", "ROC curve",0.,0., 800, 600);
TGraphErrors *grROC = new TGraphErrors(NumberOfBinsROC, &SigTestEff[0], &BkgTestEff[0], &SigTestEff_err[0], &BkgTestEff_err[0]);
c2->SetLogy(1);
Double_t ymin = 1e-8;
Double_t ymax = 5e-2;
Double_t xmin = 0;
Double_t xmax = 0.7;
grROC->GetXaxis()->SetLimits(xmin, xmax);// along X
grROC->GetHistogram()->SetMaximum(ymax);   // along          
grROC->GetHistogram()->SetMinimum(ymin);  //   YgrROC_TTVA_custom_c1->Draw("al2");

grROC->Draw("al2");
grROC->SetMarkerColor(4);
grROC->SetFillColorAlpha(4, 0.4);
grROC->SetLineColor(4);
grROC->SetMarkerStyle(20);
grROC->SetMarkerSize(1);
grROC->SetLineWidth(1);
grROC->GetYaxis()->SetTitle("Bkg. Rejection [%]");
grROC->GetXaxis()->SetTitle("Sig. Efficiency [%]");

TLegend* leg2;
// leg2 = new TLegend(1, 0.06, 5, 0.08,NULL,"brNDC");
leg2 = new TLegend(0.218045, 0.721739, 0.418546, 0.770435,NULL,"brNDC");
leg2->AddEntry(grROC, "ROC curve","l");
leg2->SetBorderSize(0);  // no border
leg2->SetLineColor(0);
leg2->SetFillColor(0);
leg2->SetTextSize(0.034468);
leg2->Draw();


Double_t sig18 = grROC->Eval(18);
Double_t sig36 = grROC->Eval(36);
Double_t sig54 = grROC->Eval(54);
TString ROCtext1 = "Bkg. Rej. at 18% Sig.Eff: ";
ROCtext1.Append(Form("%.6g", sig18));
TString ROCtext2 = "Bkg. Rej. at 36% Sig.Eff:";
 ROCtext2.Append(Form(" %.6g", sig36));
TString ROCtext3 = "Bkg. Rej. at 54% Sig.Eff:";
ROCtext3.Append(Form(" %.6g", sig54));
// TString newROCtext = "#splitline{a}{#splitline{b}{c}}";
TString newROCtext = "#splitline{" + ROCtext1 + "}{#splitline{" + ROCtext2 + "}{"+ROCtext3+"}}";
TLatex *ROCtex1 = new TLatex(8.60565, 70,newROCtext);
ROCtex1->SetTextFont(62);
ROCtex1->SetTextSize(0.034468);
ROCtex1->SetLineWidth(2);
ROCtex1->Draw();




c2->Update();

// c1->SaveAs(odir + "out_"+RunConfig+"/BDTvariable2.pdf"); //odir is set to odir4 now.
// c2->SaveAs(odir + "out_"+RunConfig+"/ROC_accept_error.pdf");
c2->SaveAs(odir + RunConfig+"/ROC_accept_error.pdf");

TFile ofile(ofileName, "recreate");
grROC->Write();

delete c2;
return 0;
}

void EvalStep_errors(){
    SetAtlasStyle();
    TString RunConfig("");
    TCut MCWeightsNPV = "NPVweight*CombWeights*PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf*Muon1_trigger_sf*Muon2_trigger_sf";
    TCut MCWeightsNom = "CombWeights*PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf*Muon1_trigger_sf*Muon2_trigger_sf";
    // RunConfig = "Custom";
    // CreateAndSaveFiles(RunConfig, MCWeightsNom);
    // // RunConfig = "Loose";
    // // CreateAndSaveFiles(RunConfig);
    // RunConfig = "Run1";
    // CreateAndSaveFiles(RunConfig, MCWeightsNom);
    // // RunConfig = "Nom";
    // // CreateAndSaveFiles(RunConfig);
    // // RunConfig = "Run1privxmu";
    // // CreateAndSaveFiles(RunConfig);
    // // RunConfig = "Run1nPV";
    // // CreateAndSaveFiles(RunConfig);
    // // RunConfig = "BestSep";
    // // CreateAndSaveFiles(RunConfig);
    // // RunConfig = "Run1Custom";
    // RunConfig = "Run1privxmu_round";
    // CreateAndSaveFiles(RunConfig, MCWeightsNom);
    // RunConfig = "Run1_npvweights";// don't need roc for this - just for efficiency studies...
    // CreateAndSaveFiles(RunConfig, MCWeightsNPV);
    // RunConfig = "Run1nPV_npvweights";//need to include NPVweight in ROCsig histogram
    // CreateAndSaveFiles(RunConfig, MCWeightsNPV);
    RunConfig = "Custom_privxmu";//need to include NPVweight in ROCsig histogram
    CreateAndSaveFiles(RunConfig, MCWeightsNom);
    RunConfig = "Custom_nPV";//need to include NPVweight in ROCsig histogram
    CreateAndSaveFiles(RunConfig, MCWeightsNPV);
    // cout<<"input vars: "<<RunConfig<<endl;
}