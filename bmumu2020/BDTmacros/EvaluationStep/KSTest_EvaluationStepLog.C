#include<TMath.h>

// TString filename = "/Users/agrummer/Desktop/Bmumu/Output/Trees/LSFJOB_Trees500/bdt2016test_0.root";
// TString FilePath = "/Users/agrummer/cernbox/www/bmumu/myMVA/";
// TString ParameterName = "out2";
// TString filename = FilePath + ParameterName + "/"+"bdt2016test.root";
// TString filename = "/Users/agrummer/cernbox/www/bmumu/myMVA/out500/bdt2016test.root";
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
Float_t Muon1_reco_eff_sf(0.0);
Float_t Muon2_reco_eff_sf(0.0);

vector <Double_t> bkgBDT;
vector <Double_t> sigBDT;
double B_MUCALC_massBkg;
double B_MUCALC_massSig;


TMultiGraph *mg;
TGraphAsymmErrors *gr1;

// void PlotBDTvariables(Float_t bkgBDTtest,
//                       Float_t sigBDTtest,
//                       Float_t bkgBDTtrain,
//                       Float_t sigBDTtrain);
Double_t AidansKTest(Int_t na, const Double_t *a, Int_t nb, const Double_t *b, Option_t *option);

void KSTest_EvaluationStepLog(){
// TString DirName = "/Users/agrummer/cernbox/www/bmumu/Data/";
TString DirName = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/SidebandTrained/";
// TString DirName = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimRightSideband/";
// TString DirName = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkimGBR4_Mar26/";
// TString DirName2 = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/EvalSetMC/";
TString DirName2 = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/SidebandTrained/";
// TString DirName2 = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/SignalMC/";
// TString DirName2 = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/SignalMC/";

//for 15 vars optimized
// TString MaxDepth = "4"; 
// TString MinNodeSize = "0.2";
// TString AdaBoostBeta= "0.5";
// TString NTrees = "500";

//for the 7 vars optimized
// TString MaxDepth = "6"; 
// TString MinNodeSize = "0.1";
// TString AdaBoostBeta= "0.2";
// TString NTrees = "500";


// TString MaxDepth = "8"; 
// TString MinNodeSize = "1.0";
// TString AdaBoostBeta= "0.1";
// TString NTrees = "500";



// TString FilePath = "/Users/agrummer/cernbox/www/bmumu/myMVA/";
// TString ParameterName = "out2";
// TString DirName = "OutputMVAMar8/";
//TString Tag = "_7vars_1";
// TString Tag = "_7vars_2";
// TString Tag = "_15vars";
// TString Tag = "_wDDWQLC";
// TString Tag = "_May24npv";
// TString Tag = "_Jun7_train1_test2";
// TString Tag = "_Jun7_train2_test1";
// TString Tag = "_Jun7_RS_train1_test2";

// TString Tag = "_Jun11_train1_test2";
// TString Tag = "_Jun11_train2_test3";
// TString Tag = "_Jun11_train3_test1";

// TString Tag = "_EVALcomboTEST";
TString Tag = "_EVALcombo_Jun12";


// TString Tag = "_SplitSet_3_BDT2016_Jun12_train1_test2";
// TString Tag = "_SplitSet_1_BDT2016_Jun12_train2_test3";
// TString Tag = "_SplitSet_2_BDT2016_Jun12_train3_test1";
// TString Tag = "_SplitSet_3_BDT2016_Jun13MuIso_train1_test2";

// TString Tag = "_Jun7_RS_train2_test1";
// TString Tag = "_May29_wQLCDDW";
// TString Tag = "_May29_trainPVstudy";
// TString Tag = "_May31_noPVweights";
// TString Tag = "_May31_noPVweightsBkg";
// TString Tag2 = "_Jun7_train1_test2";
// TString Tag2 = "_Jun7_train2_test1";
// TString Tag2 = "_Jun7_RS_train1_test2";
// TString Tag2 = "_Jun7_RS_train2_test1";

// TString Tag2 = "_Jun11_train1_test2";
// TString Tag2 = "_Jun11_train2_test3";
// TString Tag2 = "_Jun11_train3_test1";

// TString Tag2 = "_May24_ww";
// TString Tag = "_7varsOptimized";
// TString Tag = "";

// June1, _noPVweightsBkg is still old

// TString vBDT = "_BDT2016";
// TString vBDT = "_LowPileUp_BDT2016";
// TString vBDT2 = "_LowPileUp2_BDT2016";
// TString vBDT = "_HighPileUp_BDT2016";
// TString vBDT2 = "_HighPileUp2_BDT2016";
// TString vBDT = "_MiddlePileUp_BDT2016";
// TString vBDT2 = "_MiddlePileUp2_BDT2016";
// 
// TString vBDT = "_bdt2012v4QLC";

// TString vBDT = "_BDT2016";
// TString vBDT = "_BDT2016";
// TString vBDT2 = "_BDT2016";
// TString vBDT = "_BDT2016";

// TString vBDT = "_SplitSet_3_BDT2016";
// TString vBDT = "_SplitSet_1_BDT2016";
// TString vBDT = "_SplitSet_2_BDT2016";
TString vBDT = "";

// TString vBDT2 = "_BDT2016";
// TString vBDT = "_LowPileUp_BDT2016";
// TString vBDT2 = "_LowPileUp2_BDT2016";
// TString vBDT = "_HighPileUp_BDT2016";
// TString vBDT2 = "_HighPileUp2_BDT2016";
// TString vBDT = "_MiddlePileUp_BDT2016";
// TString vBDT2 = "_MiddlePileUp2_BDT2016";


// TString ParameterName = "out_MaxDepth"+MaxDepth+"_MinNodeSize"+MinNodeSize+"_AdaBoostBeta"+AdaBoostBeta+"_NTrees"+NTrees;
// TString filenameBkg = DirName + "data1516Bs_SplitSet_3"+vBDT+Tag+".root";
// TString filenameBkg = DirName + "data1516Bs_RightSideband_SplitSet_3"+vBDT+Tag+".root";
TString filenameBkg = DirName + "data1516Bs"+vBDT+Tag+".root";
// TString filenameBkg = DirName + "LASTskim.Data_2015HLTand2016HLTLxy_RightSideband_DOCAlt500"+vBDT+Tag+".root";
// TString filenameBkg = DirName + "LASTskim.bbmumuX2Bsmumu_combinatorial_GBRweight_DOCAlt500"+vBDT2+Tag+".root";
// TString filenameSig = DirName2 + "LASTskim.mc16Bs_EvalSet"+vBDT+Tag+".root";
TString filenameSig = DirName2 + "LASTskim.mc16Bs"+vBDT+Tag+".root";
// TString filenameSig = DirName2 + "LASTskim.MC16Bs_CombWeights_DOCAlt500_EvalSet"+vBDT2+Tag2+".root";

TFile* ifilenameBkg = new TFile(filenameBkg);
TFile* ifilenameSig = new TFile(filenameSig);

// ifilename->cd("out/");
// TTree *TestTree = gROOT->FindTree("TrainTree");
// TTree *TestTree = (TTree*)ifilename->Get(ParameterName + "/TestTree");
// TTree *TrainTree = (TTree*)ifilename->Get(ParameterName + "/TrainTree");
// .ls
// TTree* TestTree = (TTree*)ifilename->Get(TestTree);
// TestTree->SetBranchAddress("className",&classNameTest);
// TestTree->SetBranchAddress("classID",&classIDTest);
// TestTree->SetBranchAddress("BDT",&BDTvarTest);
// TestTree->SetBranchAddress("weight",&TestWeight);

// TrainTree->SetBranchAddress("className",&classNameTrain);
// TrainTree->SetBranchAddress("classID",&classIDTrain);
// TrainTree->SetBranchAddress("BDT",&BDTvarTrain);
// TrainTree->SetBranchAddress("weight",&TrainWeight);

TTree *EvalTreeBkg = (TTree*)ifilenameBkg->Get("T_mv");
EvalTreeBkg->SetBranchAddress("BDT_bb_2016",&BDTvarBkg);
EvalTreeBkg->SetBranchAddress("B_MUCALC_mass",&B_MUCALC_massBkg);


TTree *EvalTreeSig = (TTree*)ifilenameSig->Get("T_mv");
EvalTreeSig->SetBranchAddress("BDT_bb_2016",&BDTvarSig);

EvalTreeSig->SetBranchAddress("CombWeights",&CombWeights);
EvalTreeSig->SetBranchAddress("PVWeights",&PVWeights);
EvalTreeSig->SetBranchAddress("Muon1_reco_eff_sf",&Muon1_reco_eff_sf);
EvalTreeSig->SetBranchAddress("Muon2_reco_eff_sf",&Muon2_reco_eff_sf);

EvalTreeSig->SetBranchAddress("B_MUCALC_mass",&B_MUCALC_massSig);


// nselected = TrainTree->Draw(tmpDummy.Data(),cut,"egoff"); 
// TCanvas* c1 = new TCanvas("c1", "BDT Variable",0.,0., 800, 600);
// TH1F *hret = (TH1F*)gDirectory->Get("BDT");
// hret->Draw();
// TString number = "";
// Long64_t myNumber = 12334;
// number+=myNumber;
cout<<"EvalTreeBkg Entries: "<<EvalTreeBkg->GetEntries()<<endl;
cout<<"EvalTreeSig Entries: "<<EvalTreeSig->GetEntries()<<endl;
    // TestTree->GetEntry(12334);
    // TestTree->GetEntry(12334);
    // if(classIDTest == 1){
    // cout<<classNameTest<<endl;
    
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

// float sigBDTtestWeightAvg = accumulate( sigBDTtestWeight.begin(), sigBDTtestWeight.end(), 0.0)/sigBDTtestWeight.size(); 
// float bkgBDTtestWeightAvg = accumulate( bkgBDTtestWeight.begin(), bkgBDTtestWeight.end(), 0.0)/bkgBDTtestWeight.size(); 
// float sigBDTtrainWeightAvg = accumulate( sigBDTtrainWeight.begin(), sigBDTtrainWeight.end(), 0.0)/sigBDTtrainWeight.size(); 
// float bkgBDTtrainWeightAvg = accumulate( bkgBDTtrainWeight.begin(), bkgBDTtrainWeight.end(), 0.0)/bkgBDTtrainWeight.size();
// bkgBDTtrainWeight.erase(std::remove(bkgBDTtrainWeight.begin(), bkgBDTtrainWeight.end(), 0),bkgBDTtrainWeight.end()); 
// bkgBDTtrainWeight.shrink_to_fit();
// cout<<"sigBDTtestWeightAvg: "<< sigBDTtestWeightAvg << endl;
// cout<<"bkgBDTtestWeightAvg: "<< bkgBDTtestWeightAvg << endl;
// cout<<"sigBDTtrainWeightAvg: "<< sigBDTtrainWeightAvg << endl;
// cout<<"bkgBDTtrainWeightAvg: "<< bkgBDTtrainWeightAvg << endl;


sort(sigBDT.begin(), sigBDT.end());
sort(bkgBDT.begin(), bkgBDT.end());

// cout<<TrainTree->GetEntries()<<endl;


// Float_t* a = &sigBDTtest[0];// the array that the vector points to!!!
// // cout<<sizeof(a)/sizeof(a[0])<<endl;// this doesn't give me size of array like StackOverflow says it should
// sort(a, a + sigBDTtest.size());
// cout<<a[0]<<" "<<a[sigBDTtest.size()-1]<<endl;

// Float_t* a = &sigBDTtest[0];// the array that the vector points to!!!
// // cout<<sizeof(a)/sizeof(a[0])<<endl;// this doesn't give me size of array like StackOverflow says it should
// sort(a, a + sigBDTtest.size());

vector<Double_t> vec = sigBDT;
vec.insert( vec.end(), bkgBDT.begin(), bkgBDT.end() );//merge sig and bkg vectors
sort(vec.begin(), vec.end());
vec.erase( unique( vec.begin(), vec.end() ), vec.end() );//select unique values in full vector for hist bins
// cout<<vec.back()<<endl;
// cout<<vec[vec.size()]<<endl;
cout<<" vec size (sig+bkg)  "<<vec.size()<<endl;
vec.push_back(vec.back()+ 0.01);
cout<<" vec size + 1 "<<vec.size()<<endl;
Double_t* b = &vec[0];// the array that the vector points to!!!
sort(b, b + vec.size());


vector<Double_t> sigBDTDouble(sigBDT.begin(), sigBDT.end());
vector<Double_t> bkgBDTDouble(bkgBDT.begin(), bkgBDT.end());

// cout<<bkgBDTtrain.back()<<endl;
// cout<<bkgBDTtrainDouble.back()<<endl;

// Double_t KSvalSig = TMath::KolmogorovTest(sigBDTtestDouble.size(), &sigBDTtestDouble[0],sigBDTtrainDouble.size(), &sigBDTtrainDouble[0], "");
// Double_t KSvalBkg = TMath::KolmogorovTest(bkgBDTtestDouble.size(), &bkgBDTtestDouble[0],bkgBDTtrainDouble.size(), &bkgBDTtrainDouble[0], "");
// cout<<KSvalSig<<endl;
// cout<<KSvalBkg<<endl;

// PlotBDTvariables(bkgBDTtest,sigBDTtest,bkgBDTtrain,sigBDTtrain);
// cout<<gDirectory<<endl;


////////PLOTTING
TCanvas* c1;
TH1F *hret;
TH1F *hretSig;
TH1F *hretBkg;
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
// // TH1F *hret = (TH1F*)gDirectory->Get("BDT");
hretSig = new TH1F("Name", "title", NumberOfBins, vec[0], vec.back());
hretBkg = new TH1F("Name2", "title2", NumberOfBins, vec[0], vec.back());
// hret3 = new TH1F("Name3", "title3", NumberOfBins, vec[0], vec.back());
// hret4 = new TH1F("Name4", "title4", NumberOfBins, vec[0], vec.back());
hretSig->Sumw2();
hretBkg->Sumw2();

for(int i = 0; i<EvalTreeSig->GetEntries(); i++){
    EvalTreeSig->GetEntry(i);
    hretSig->Fill(BDTvarSig);
}
for(int i = 0; i<EvalTreeBkg->GetEntries(); i++){
    EvalTreeBkg->GetEntry(i);
    if (B_MUCALC_massBkg <=5526.0) continue;
    hretBkg->Fill(BDTvarBkg);
}


// hret3->Sumw2();
// hret4->Sumw2();
// // for(int i = 0; i<sigBDTtest.size(); i++){
// //     hret->Fill(sigBDTtest[i]);
// // }
// for(int i = 0; i<TestTree->GetEntries(); i++){
//     TestTree->GetEntry(i);
//     ATestString= classNameTest ;
//     if (ATestString.EqualTo("S")){
//         hret->Fill(BDTvarTest, TestWeight);}
//     else if (ATestString.EqualTo("B")){
//         hret2->Fill(BDTvarTest, TestWeight);
//     }
//     // if (i%10000 == 0) cout<<"Debug "<<TestWeight<<endl;
// }
hretSig->Scale(1.0/hretSig->Integral(0, NumberOfBins));
hretSig->Draw("hist");
hretSig->SetLineColor(4);
// // for(int i = 0; i<bkgBDTtest.size(); i++){
// //   hret2->Fill(bkgBDTtest[i]);
// // }
hretBkg->Scale(1.0/hretBkg->Integral(0, NumberOfBins));
hretBkg->Draw("hist same");
hretBkg->SetLineColor(2);
// // mg = new TMultiGraph();
// for(int i = 0; i<TrainTree->GetEntries(); i++){
//     TrainTree->GetEntry(i);
//     ATrainString= classNameTrain ;
//     if (ATrainString.EqualTo("S")){
//         hret3->Fill(BDTvarTrain, TrainWeight);}
//     else if (ATrainString.EqualTo("B")){
//         hret4->Fill(BDTvarTrain, TrainWeight);
//     }
//     // if (i%1000 == 0) cout<<TrainWeight<<endl;
// }

// // for(int i = 0; i<sigBDTtrain.size(); i++){
// //   hret3->Fill(sigBDTtrain[i]);
// // }
// hret3->Scale(1.0/hret3->Integral(0, NumberOfBins));
// hret3->Draw("pe0z same");
// hret3->SetMarkerColor(4);
// hret3->SetMarkerStyle(22);
// hret3->SetMarkerSize(1);
// hret3->SetLineColor(4);
// hret3->SetLineWidth(0);


// // for(int i = 0; i<bkgBDTtrain.size(); i++){
// //   hret4->Fill(bkgBDTtrain[i]);
// // }
// hret4->Scale(1.0/hret4->Integral(0, NumberOfBins));
// hret4->Draw("pe0z same");
// hret4->SetMarkerColor(2);
// hret4->SetMarkerStyle(22);
// hret4->SetMarkerSize(1);
// hret4->SetLineWidth(0);


hretSig->GetYaxis()->SetTitle("Events");
hretSig->GetXaxis()->SetTitle("BDT Variable");

// // Double_t TwoThirds = 2/3;
yHeight = hretBkg->GetMaximum();
// // yHeight = yHeight;
hretSig->GetYaxis()->SetRangeUser(0, yHeight*3/2);

// // leg = new TLegend(1, 0.06, 5, 0.08,NULL,"brNDC");
leg = new TLegend(0.218045, 0.756522, 0.418546, 0.909565,NULL,"brNDC");

// sigTestCandidates = sigBDTtestDouble.size();
// bkgTestCandidates = bkgBDTtestDouble.size();
// sigTrainCandidates = sigBDTtrainDouble.size();
// bkgTrainCandidates = bkgBDTtrainDouble.size();
// hretLeg = Form( "Signal Test Sample (%5.f Candidates)", sigTestCandidates);
// hret2Leg = Form( "Background Test Sample (%5.f Candidates)", bkgTestCandidates);
// hret3Leg = Form( "Signal Train Sample (%5.f Candidates)", sigTrainCandidates);
// hret4Leg = Form( "Background Train Sample (%5.f Candidates)", bkgTrainCandidates);

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
Double_t BDTCut18 = 0.424441;
Double_t BDTCut36 = 0.341969;
Double_t BDTCut54 = 0.258933;

TLine *line1;
TLine *line2;
TLine *line3;
line1 = new TLine(BDTCut18,0.,BDTCut18,yHeight*3/2);
line1->SetLineColorAlpha(kBlack, 0.4);
line1->Draw();
line2 = new TLine(BDTCut36,0.,BDTCut36,yHeight*3/2);
line2->SetLineColorAlpha(kBlack, 0.4);
line2->Draw();
line3 = new TLine(BDTCut54,0.,BDTCut54,yHeight*3/2);
line3->SetLineColorAlpha(kBlack, 0.4);
line3->Draw();




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










/////////////ROC
TH1F *hROC;
TH1F *hROCSig;
TH1F *hROCBkg;
TH1F *hROC2;
TH1F *hROC3;
TH1F *hROC4;

int NumberOfBinsROC = 10000;
hROCSig = new TH1F("NameROC", "titleROC", NumberOfBinsROC, vec[0], vec.back());
hROCBkg = new TH1F("NameROC2", "titleROC2", NumberOfBinsROC, vec[0], vec.back());
// hROC3 = new TH1F("NameROC3", "titleROC3", NumberOfBinsROC, vec[0], vec.back());
// hROC4 = new TH1F("NameROC4", "titleROC4", NumberOfBinsROC, vec[0], vec.back());
hROCSig->Sumw2();
hROCBkg->Sumw2();
// hROC3->Sumw2();
// hROC4->Sumw2();
//
// for(int i = 0; i<TestTree->GetEntries(); i++){
//     TestTree->GetEntry(i);
//     ATestString= classNameTest ;
//     if (ATestString.EqualTo("S")){
//         hROC->Fill(BDTvarTest, TestWeight);}
//     else if (ATestString.EqualTo("B")){
//         hROC2->Fill(BDTvarTest, TestWeight);
//     }
//     // if (i%10000 == 0) cout<<"Debug "<<TestWeight<<endl;
// }
//
for(int i = 0; i<EvalTreeSig->GetEntries(); i++){
    EvalTreeSig->GetEntry(i);
    hROCSig->Fill(BDTvarSig, CombWeights*PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf);
}
for(int i = 0; i<EvalTreeBkg->GetEntries(); i++){
    EvalTreeBkg->GetEntry(i);
    if (B_MUCALC_massBkg <=5526.0) continue;
    hROCBkg->Fill(BDTvarBkg);
}
// for(int i = 0; i<TrainTree->GetEntries(); i++){
//     TrainTree->GetEntry(i);
//     ATrainString= classNameTrain ;
//     if (ATrainString.EqualTo("S")){
//         hROC3->Fill(BDTvarTrain, TrainWeight);}
//     else if (ATrainString.EqualTo("B")){
//         hROC4->Fill(BDTvarTrain, TrainWeight);
//     }
//     // if (i%1000 == 0) cout<<TrainWeight<<endl;
// }
hROCSig->Scale(1.0/hROCSig->Integral(0, NumberOfBinsROC));
hROCBkg->Scale(1.0/hROCBkg->Integral(0, NumberOfBinsROC));
// hROC3->Scale(1.0/hROC3->Integral(0, NumberOfBinsROC));
// hROC4->Scale(1.0/hROC4->Integral(0, NumberOfBinsROC));

// Double_t kolS_ROCbins = hROC3->KolmogorovTest( hROC );
// Double_t kolB_ROCbins = hROC4->KolmogorovTest( hROC2 );
// cout<<"kolS_ROCbins: "<< kolS_ROCbins<< endl;
// // cout<<kolS2<<endl;
// cout<<"kolB_ROCbins: "<< kolB_ROCbins << endl;

// vector<Double_t> sigTestIntegral;
// vector<Double_t> bkgTestIntegral;
// vector<Double_t> totalTestIntegral;

// tex3text = Form( "K-S test: sig. (bkg.) prob. = %5.3g (%5.3g)", kolS_ROCbins, kolB_ROCbins );
// // tex3text+=kolS;
// tex3 = new TLatex(-0.205266, yHeight + yHeight*0.06,tex3text.Data());
// tex3->SetTextFont(62);
// tex3->SetTextSize(0.034468);
// tex3->SetLineWidth(2);
// tex3->Draw();





vector<Double_t> SigTestEff;
vector<Double_t> BkgTestRej;
for(int i = 0; i<NumberOfBinsROC; i++){
  // cout<<i<<endl;
  SigTestEff.push_back((hROCSig->Integral(NumberOfBinsROC-i, NumberOfBinsROC))/(hROCSig->Integral(0, NumberOfBinsROC))*100);
  BkgTestRej.push_back((1-(hROCBkg->Integral(NumberOfBinsROC-i, NumberOfBinsROC))/(hROCBkg->Integral(0, NumberOfBinsROC)))*100);

  if ((SigTestEff[i] > 17.95 && SigTestEff[i] < 18.05) || (SigTestEff[i] > 35.95 && SigTestEff[i] < 36.05) || (SigTestEff[i] > 53.95 && SigTestEff[i] < 54.05)){
      cout<<"Bkg Rej= "<< BkgTestRej[i]<< " at a signal efficiency: " << SigTestEff[i] 
      << " BDT value: "<< hROCSig->GetXaxis()->GetBinCenter(NumberOfBinsROC-i)
      <<" bkg: "<<hROCBkg->GetXaxis()->GetBinCenter(NumberOfBinsROC-i) << endl;
      }
  // totalTestIntegral.push_back(sigTestIntegral[i]+bkgTestIntegral[i]);
  // SigTestEff.push_back(sigTestIntegral[i]/totalTestIntegral[i]);
  // BkgTestRej.push_back(1-bkgTestIntegral[i]/totalTestIntegral[i]);
}
// cout<<SigTestEff.size()<<endl;

TCanvas* c2 = new TCanvas("c2", "ROC curve",0.,0., 800, 600);
TGraph *grROC = new TGraph(NumberOfBinsROC, &SigTestEff[0], &BkgTestRej[0]);
// for(int i = 0; i<NumberOfBinsROC; i++){
//   histROC->Fill(bkgBDTtrain[i]);
// }
grROC->Draw("al");
grROC->SetMarkerColor(4);
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
// TLatex *ROCtex2 = new TLatex(5, 55,ROCtext2.Data());
// ROCtex2->SetTextFont(62);
// ROCtex2->SetTextSize(0.038);
// ROCtex2->SetLineWidth(2);
// ROCtex2->Draw();
// TLatex *ROCtex3 = new TLatex(5, 50,ROCtext3.Data());
// ROCtex3->SetTextFont(62);
// ROCtex3->SetTextSize(0.038);
// ROCtex3->SetLineWidth(2);
// ROCtex3->Draw();



c2->Update();
// c1->SaveAs("/Users/agrummer/cernbox/www/bmumu/myMVAOut/EvalFolder/KS"+vBDT+Tag+".pdf");
// c2->SaveAs("/Users/agrummer/cernbox/www/bmumu/myMVAOut/EvalFolder/ROC"+vBDT+Tag+".pdf");

// c1->SaveAs("/afs/cern.ch/user/a/agrummer/www/bmumu/myMVAOut/EvalFolder/May24/KS"+vBDT+Tag+".pdf");
// c2->SaveAs("/afs/cern.ch/user/a/agrummer/www/bmumu/myMVAOut/EvalFolder/May24/ROC"+vBDT+Tag+".pdf");
// c1->SaveAs("/afs/cern.ch/user/a/agrummer/www/bmumu/OutMVA/EvalFolder2/May24npv/KS"+vBDT+Tag+".pdf");
// c2->SaveAs("/afs/cern.ch/user/a/agrummer/www/bmumu/OutMVA/EvalFolder2/May24npv/ROC"+vBDT+Tag+".pdf");

// TString ofilenames = "May29_PileupTrainedStudy";
// TString ofilenames = "May31_noPVweights";
// TString ofilenames = "May31_noPVweightsBkg";
// TString ofilenames = "OfficialMay24_WithWeights";
// TString ofilenames = "OfficialMay24_ww_pileupstudy";
// TString ofilenames = "Jun7_SidebandTraining/train1_test2";
// TString ofilenames = "Jun7_SidebandTraining/train2_test1";
// TString ofilenames = "Jun7_RightSidebandTraining/train1_test2";
// TString ofilenames = "Jun7_RightSidebandTraining/train2_test1";

// TString ofilenames = "Jun11_SidebandTrained/EvalComboTEST";
TString ofilenames = "Jun12_SidebandTrained/EvalCombo";
// TString ofilenames = "Jun12_SidebandTrained/BDT1";//train1
// TString ofilenames = "Jun12_SidebandTrained/BDT2";//train2
// TString ofilenames = "Jun12_SidebandTrained/BDT3";//train3
// TString ofilenames = "Jun13MuIso_SidebandTrained/BDT1";//train3

// TString ofilenames = "Jun11_SidebandTrained/eval1";
// TString ofilenames = "Jun11_SidebandTrained/eval2";
// TString ofilenames = "Jun11_SidebandTrained/eval3";

// TString ofilenames = "May29_PileupAndbbmumuXwQLC";
// TString ofilenames = "May29_PileupEvaluationDataset";

c1->SaveAs("/afs/cern.ch/user/a/agrummer/www/bmumu/OutMVA/EvalFolder2/"+ofilenames+"/KS"+vBDT+Tag+"Log.pdf");
// c2->SaveAs("/afs/cern.ch/user/a/agrummer/www/bmumu/OutMVA/EvalFolder2/"+ofilenames+"/ROC"+vBDT+Tag+".pdf");


// ofstream ofileVals (DirName + ParameterName+ "/ROCandKSvals.csv", ofstream::out);
// ofileVals <<"MaxDepth,"<<"MinNodeSize,"<<"AdaBoostBeta,"<<"NTrees,"<<"ROC18,"<<"ROC36,"<<"ROC54," <<"KSvalSig,"<< "KSvalBkg" <<endl;
// ofileVals <<MaxDepth<<","<<MinNodeSize<<","<<AdaBoostBeta<<","<<NTrees<<","<<sig18<<","<<sig36<<","<<sig54<<","<<kolS_ROCbins<< ","<< kolB_ROCbins <<endl;
// ofileVals.close();

// TFile ofile("/Users/agrummer/cernbox/www/bmumu/myMVAOut/EvalFolder/May16/ROC"+vBDT+Tag+".root", "recreate");
// TFile ofile("/afs/cern.ch/user/a/agrummer/www/bmumu/myMVAOut/EvalFolder/May24/ROC"+vBDT+Tag+".root", "recreate");
// TFile ofile("/afs/cern.ch/user/a/agrummer/www/bmumu/OutMVA/EvalFolder2/May24npv/ROC"+vBDT+Tag+".root", "recreate");
// TFile ofile("/afs/cern.ch/user/a/agrummer/www/bmumu/OutMVA/EvalFolder2/"+ofilenames+"/ROC"+vBDT+Tag+".root", "recreate");
// grROC->Write();

//     gr1 = new TGraphAsymmErrors(bkgBDTtest.size(), &bkgBDTtrain[0], &sigBDTtrain[0]);//, Errors, Errors, Errors, Errors);
//     gr1->SetMarkerStyle(20);
//     gr1->SetMarkerColor(kRed);
//     gr1->SetFillColor(kRed);
//     gr1->SetMarkerSize(0.2);
//     gr1->SetLineColor(1);
//     gr1->SetLineWidth(1);

//   mg->Add(gr1);
//   mg->Draw("AP");
//   c1->Update();

return 0;
}

// void PlotBDTvariables(vector <Float_t> bkgBDTtest,
//                   vector <Float_t> sigBDTtest,
//                   vector <Float_t> bkgBDTtrain,
//                   vector <Float_t> sigBDTtrain){
// return 0;
// }
// myfile = new TFile("/Users/agrummer/Desktop/Bmumu/Output/Trees/LSFJOB_Trees500/bdt2016test_0.root")
// myfile->cd("out/")
// TLeaf *l = TestTree->GetLeaf("className");
// TBranch *b = TestTree->GetBranch("className");
// TLeaf *l = (TLeaf*)b->GetListOfLeaves()->At(0);
// TLeaf *l = (TLeaf*)b->GetListOfLeaves()->At(0); 
// if (l->GetLeafCounter()) { l->GetLeafCounter()->GetBranch()->GetEntry(2355); }
// l->GetLen()
// l->GetValue(5)
// TObjArray * somearray = TestTree->GetListOfBranches()
// TObjArray * somearray = TestTree->GetListOfLeaves()



/// ### Note:
 ///  A good description of the Kolmogorov test can be seen at:
 ///    http://www.itl.nist.gov/div898/handbook/eda/section3/eda35g.htm
 





 // Double_t AidansKTest(Int_t na, const Double_t *a, Int_t nb, const Double_t *b, Option_t *option)
 // {
 // //  LM: Nov 2010: clean up and returns now a zero distance when vectors are the same
 
 //    TString opt = option;
 //    opt.ToUpper();
 
 //    Double_t prob = -1;
 // //      Require at least two points in each graph
 //    if (!a || !b || na <= 2 || nb <= 2) {
 //       Error("KolmogorovTest","Sets must have more than 2 points");
 //       return prob;
 //    }
 // //     Constants needed
 //    Double_t rna = na;
 //    Double_t rnb = nb;
 //    Double_t sa  = 1./rna;
 //    Double_t sb  = 1./rnb;
 //    Double_t rdiff = 0;
 //    Double_t rdmax = 0;
 //    Int_t ia = 0;
 //    Int_t ib = 0;
 
 // //    Main loop over point sets to find max distance
 // //    rdiff is the running difference, and rdmax the max.
 //    Bool_t ok = kFALSE;
 //    for (Int_t i=0;i<na+nb;i++) {
 //       if (a[ia] < b[ib]) {
 //          rdiff -= sa;
 //          ia++;
 //          if (ia >= na) {ok = kTRUE; break;}
 //       } else if (a[ia] > b[ib]) {
 //          rdiff += sb;
 //          ib++;
 //          if (ib >= nb) {ok = kTRUE; break;}
 //       } else {
 //          // special cases for the ties
 //          double x = a[ia];
 //          while(ia < na && a[ia] == x) {
 //             rdiff -= sa;
 //             ia++;
 //          }
 //          while(ib < nb && b[ib] == x) {
 //             rdiff += sb;
 //             ib++;
 //          }
 //          if (ia >= na) {ok = kTRUE; break;}
 //          if (ib >= nb) {ok = kTRUE; break;}
 //       }
 //       rdmax = TMath::Max(rdmax,TMath::Abs(rdiff));
 //    }
 //    //    Should never terminate this loop with ok = kFALSE!
 //    R__ASSERT(ok);
 
 //    if (ok) {
 //       rdmax = TMath::Max(rdmax,TMath::Abs(rdiff));
 //       Double_t z = rdmax * TMath::Sqrt(rna*rnb/(rna+rnb));
 //       prob = TMath::KolmogorovProb(z);
 //    }
 //       // debug printout
 //    if (opt.Contains("D")) {
 //       printf(" Kolmogorov Probability = %g, Max Dist = %g\n",prob,rdmax);
 //    }
 //    if(opt.Contains("M")) return rdmax;
 //    else                  return prob;
 // }

// kolS: 0.0231378
// kolB: 0.709172
// kolS_ROCbins: 0.0143918
// kolB_ROCbins: 0.590686


