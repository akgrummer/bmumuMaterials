#include<TMath.h>
#include "../AnalysisTools/Utils/AtlasStyle/AtlasLabels.C"
#include "../AnalysisTools/Utils/AtlasStyle/AtlasLabels.h"
#include "../AnalysisTools/Utils/AtlasStyle/AtlasUtils.C"
#include "../AnalysisTools/Utils/AtlasStyle/AtlasUtils.h"
#include "../AnalysisTools/Utils/AtlasStyle/AtlasStyle.C"
#include "../AnalysisTools/Utils/AtlasStyle/AtlasStyle.h"
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

TMultiGraph *mg;
TGraphAsymmErrors *gr1;

// void PlotBDTvariables(Float_t bkgBDTtest,
//                       Float_t sigBDTtest,
//                       Float_t bkgBDTtrain,
//                       Float_t sigBDTtrain);
Double_t AidansKTest(Int_t na, const Double_t *a, Int_t nb, const Double_t *b, Option_t *option);
//this code is copied from KSTestFeb7
void KStest_ROCbdt(){
        SetAtlasStyle();
// TString DirName = "/home/agrummer/www/bmumu/myMVA/";
TString DirName = "/Users/agrummer/cernbox/www/bmumu/myMVA/";
TString MaxDepth = "4";
 TString MinNodeSize = "0.2";
  TString AdaBoostBeta= "0.5";
   TString NTrees = "500";
// TString FilePath = "/Users/agrummer/cernbox/www/bmumu/myMVA/";
// TString ParameterName = "out2";
// TString DirName = "OutputMVAMar8/";
TString ParameterName = "out_MaxDepth"+MaxDepth+"_MinNodeSize"+MinNodeSize+"_AdaBoostBeta"+AdaBoostBeta+"_NTrees"+NTrees;
TString FolderName = "IsolationStudies/out_2016run_AllTracks_PVweights";
// TString FolderName = "IsolationStudies/out_2016run_AllTracksVariables";
// TString FolderName = "IsolationStudies/out_2016run_Default";
TString filename = DirName + FolderName + "/"+"bdt2016.root";

TFile* ifilename = new TFile(filename);

// ifilename->cd("out/");
// TTree *TestTree = gROOT->FindTree("TrainTree");
TTree *TestTree = (TTree*)ifilename->Get(ParameterName + "/TestTree");
TTree *TrainTree = (TTree*)ifilename->Get(ParameterName + "/TrainTree");
// .ls
// TTree* TestTree = (TTree*)ifilename->Get(TestTree);
TestTree->SetBranchAddress("className",&classNameTest);
TestTree->SetBranchAddress("classID",&classIDTest);
TestTree->SetBranchAddress("BDT",&BDTvarTest);
TestTree->SetBranchAddress("weight",&TestWeight);

TrainTree->SetBranchAddress("className",&classNameTrain);
TrainTree->SetBranchAddress("classID",&classIDTrain);
TrainTree->SetBranchAddress("BDT",&BDTvarTrain);
TrainTree->SetBranchAddress("weight",&TrainWeight);

// nselected = TrainTree->Draw(tmpDummy.Data(),cut,"egoff"); 
// TCanvas* c1 = new TCanvas("c1", "BDT Variable",0.,0., 800, 600);
// TH1F *hret = (TH1F*)gDirectory->Get("BDT");
// hret->Draw();
// TString number = "";
// Long64_t myNumber = 12334;
// number+=myNumber;
cout<<"TestTree Entries: "<<TestTree->GetEntries()<<endl;
cout<<"TrainTree Entries: "<<TrainTree->GetEntries()<<endl;
    // TestTree->GetEntry(12334);
    // TestTree->GetEntry(12334);
    // if(classIDTest == 1){
    // cout<<classNameTest<<endl;
    
for(int i=0; i < TestTree->GetEntries(); i++){
    TestTree->GetEntry(i);
    // if(classIDTest == 1){
    // cout<<classIDTest<<endl;
    ATestString=(classNameTest);
    if(ATestString.EqualTo("B")){
            bkgBDTtest.push_back(BDTvarTest);
            bkgBDTtestWeight.push_back(TestWeight);
    }else if(ATestString.EqualTo("S")){
        sigBDTtest.push_back(BDTvarTest);
        sigBDTtestWeight.push_back(TestWeight);
        }
      }

for(int i=0; i < TrainTree->GetEntries(); i++){
    TrainTree->GetEntry(i);
    // if(classIDTrain == ){
    // cout<<classIDTrain<<endl;
    ATrainString=(classNameTrain);
    if(ATrainString.EqualTo("B")){
        bkgBDTtrain.push_back(BDTvarTrain);
        bkgBDTtrainWeight.push_back(TrainWeight);
    }else if(ATrainString.EqualTo("S")){
        sigBDTtrain.push_back(BDTvarTrain);
        sigBDTtrainWeight.push_back(TrainWeight);
      }
    }


cout<<bkgBDTtest.size()<<endl;
cout<<sigBDTtest.size()<<endl;
cout<<sigBDTtest.size() + bkgBDTtest.size()<<endl;

float sigBDTtestWeightAvg = accumulate( sigBDTtestWeight.begin(), sigBDTtestWeight.end(), 0.0)/sigBDTtestWeight.size(); 
float bkgBDTtestWeightAvg = accumulate( bkgBDTtestWeight.begin(), bkgBDTtestWeight.end(), 0.0)/bkgBDTtestWeight.size(); 
float sigBDTtrainWeightAvg = accumulate( sigBDTtrainWeight.begin(), sigBDTtrainWeight.end(), 0.0)/sigBDTtrainWeight.size(); 
float bkgBDTtrainWeightAvg = accumulate( bkgBDTtrainWeight.begin(), bkgBDTtrainWeight.end(), 0.0)/bkgBDTtrainWeight.size();
bkgBDTtrainWeight.erase(std::remove(bkgBDTtrainWeight.begin(), bkgBDTtrainWeight.end(), 0),bkgBDTtrainWeight.end()); 
bkgBDTtrainWeight.shrink_to_fit();
cout<<"sigBDTtestWeightAvg: "<< sigBDTtestWeightAvg << endl;
cout<<"bkgBDTtestWeightAvg: "<< bkgBDTtestWeightAvg << endl;
cout<<"sigBDTtrainWeightAvg: "<< sigBDTtrainWeightAvg << endl;
cout<<"bkgBDTtrainWeightAvg: "<< bkgBDTtrainWeightAvg << endl;


sort(sigBDTtest.begin(), sigBDTtest.end());
sort(sigBDTtrain.begin(), sigBDTtrain.end());
sort(bkgBDTtest.begin(), bkgBDTtest.end());
sort(bkgBDTtrain.begin(), bkgBDTtrain.end());

// cout<<TrainTree->GetEntries()<<endl;


// Float_t* a = &sigBDTtest[0];// the array that the vector points to!!!
// // cout<<sizeof(a)/sizeof(a[0])<<endl;// this doesn't give me size of array like StackOverflow says it should
// sort(a, a + sigBDTtest.size());
// cout<<a[0]<<" "<<a[sigBDTtest.size()-1]<<endl;

// Float_t* a = &sigBDTtest[0];// the array that the vector points to!!!
// // cout<<sizeof(a)/sizeof(a[0])<<endl;// this doesn't give me size of array like StackOverflow says it should
// sort(a, a + sigBDTtest.size());

vector<Float_t> vec = sigBDTtest;
vec.insert( vec.end(), bkgBDTtest.begin(), bkgBDTtest.end() );//merge sig and bkg vectors
sort(vec.begin(), vec.end());
vec.erase( unique( vec.begin(), vec.end() ), vec.end() );//select unique values in full vector for hist bins
// cout<<vec.back()<<endl;
// cout<<vec[vec.size()]<<endl;
cout<<" "<<vec.size()<<endl;
vec.push_back(vec.back()+ 0.01);
cout<<" "<<vec.size()<<endl;
Float_t* b = &vec[0];// the array that the vector points to!!!
sort(b, b + vec.size());


vector<Double_t> sigBDTtestDouble(sigBDTtest.begin(), sigBDTtest.end());
vector<Double_t> sigBDTtrainDouble(sigBDTtrain.begin(), sigBDTtrain.end());
vector<Double_t> bkgBDTtestDouble(bkgBDTtest.begin(), bkgBDTtest.end());
vector<Double_t> bkgBDTtrainDouble(bkgBDTtrain.begin(), bkgBDTtrain.end());

// cout<<bkgBDTtrain.back()<<endl;
// cout<<bkgBDTtrainDouble.back()<<endl;

Double_t KSvalSig = TMath::KolmogorovTest(sigBDTtestDouble.size(), &sigBDTtestDouble[0],sigBDTtrainDouble.size(), &sigBDTtrainDouble[0], "");
Double_t KSvalBkg = TMath::KolmogorovTest(bkgBDTtestDouble.size(), &bkgBDTtestDouble[0],bkgBDTtrainDouble.size(), &bkgBDTtrainDouble[0], "");
cout<<KSvalSig<<endl;
cout<<KSvalBkg<<endl;

// PlotBDTvariables(bkgBDTtest,sigBDTtest,bkgBDTtrain,sigBDTtrain);
// cout<<gDirectory<<endl;


////////PLOTTING
TCanvas* c1;
TH1F *hret;
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
// TH1F *hret = (TH1F*)gDirectory->Get("BDT");
hret = new TH1F("Name", "title", NumberOfBins, vec[0], vec.back());
hret2 = new TH1F("Name2", "title2", NumberOfBins, vec[0], vec.back());
hret3 = new TH1F("Name3", "title3", NumberOfBins, vec[0], vec.back());
hret4 = new TH1F("Name4", "title4", NumberOfBins, vec[0], vec.back());
hret->Sumw2();
hret2->Sumw2();
hret3->Sumw2();
hret4->Sumw2();
// for(int i = 0; i<sigBDTtest.size(); i++){
//     hret->Fill(sigBDTtest[i]);
// }
for(int i = 0; i<TestTree->GetEntries(); i++){
    TestTree->GetEntry(i);
    ATestString= classNameTest ;
    if (ATestString.EqualTo("S")){
        hret->Fill(BDTvarTest, TestWeight);}
    else if (ATestString.EqualTo("B")){
        hret2->Fill(BDTvarTest, TestWeight);
    }
    // if (i%10000 == 0) cout<<"Debug "<<TestWeight<<endl;
}
hret->Scale(1.0/hret->Integral(0, NumberOfBins));
hret->Draw("hist");
hret->SetLineColor(4);
// for(int i = 0; i<bkgBDTtest.size(); i++){
//   hret2->Fill(bkgBDTtest[i]);
// }
hret2->Scale(1.0/hret2->Integral(0, NumberOfBins));
hret2->Draw("hist same");
hret2->SetLineColor(2);
// mg = new TMultiGraph();

for(int i = 0; i<TrainTree->GetEntries(); i++){
    TrainTree->GetEntry(i);
    ATrainString= classNameTrain ;
    if (ATrainString.EqualTo("S")){
        hret3->Fill(BDTvarTrain, TrainWeight);}
    else if (ATrainString.EqualTo("B")){
        hret4->Fill(BDTvarTrain, TrainWeight);
    }
    // if (i%1000 == 0) cout<<TrainWeight<<endl;
}

// for(int i = 0; i<sigBDTtrain.size(); i++){
//   hret3->Fill(sigBDTtrain[i]);
// }
hret3->Scale(1.0/hret3->Integral(0, NumberOfBins));
hret3->Draw("pe0z same");
hret3->SetMarkerColor(4);
hret3->SetMarkerStyle(22);
hret3->SetMarkerSize(1);
hret3->SetLineColor(4);
hret3->SetLineWidth(0);


// for(int i = 0; i<bkgBDTtrain.size(); i++){
//   hret4->Fill(bkgBDTtrain[i]);
// }
hret4->Scale(1.0/hret4->Integral(0, NumberOfBins));
hret4->Draw("pe0z same");
hret4->SetMarkerColor(2);
hret4->SetMarkerStyle(22);
hret4->SetMarkerSize(1);
hret4->SetLineWidth(0);


hret->GetYaxis()->SetTitle("Events");
hret->GetXaxis()->SetTitle("BDT Variable");

// Double_t TwoThirds = 2/3;
// yHeight = hret2->GetMaximum();
yHeight = hret->GetMaximum();
// yHeight = yHeight;
hret->GetYaxis()->SetRangeUser(0, yHeight*3/2);

// leg = new TLegend(1, 0.06, 5, 0.08,NULL,"brNDC");
leg = new TLegend(0.218045, 0.756522, 0.418546, 0.909565,NULL,"brNDC");

sigTestCandidates = sigBDTtestDouble.size();
bkgTestCandidates = bkgBDTtestDouble.size();
sigTrainCandidates = sigBDTtrainDouble.size();
bkgTrainCandidates = bkgBDTtrainDouble.size();
hretLeg = Form( "Signal Test Sample (%5.f Candidates)", sigTestCandidates);
hret2Leg = Form( "Background Test Sample (%5.f Candidates)", bkgTestCandidates);
hret3Leg = Form( "Signal Train Sample (%5.f Candidates)", sigTrainCandidates);
hret4Leg = Form( "Background Train Sample (%5.f Candidates)", bkgTrainCandidates);

leg->AddEntry(hret, hretLeg.Data(),"l");
leg->AddEntry(hret2, hret2Leg.Data(),"l");
leg->AddEntry(hret3, hret3Leg.Data(),"p");
leg->AddEntry(hret4, hret4Leg.Data(),"p");
leg->SetBorderSize(0);  // no border
leg->SetLineColor(0);
leg->SetFillColor(0);
leg->SetTextSize(0.034468);
leg->Draw();

//Note, the hist test gets closer to the unbinned scenerio with higher number of bins. 
// With low number of bins the test gets closer to 1
// The option "X" provides a pseudo test, but seems to effect the the next instance of the test
kolS = hret3->KolmogorovTest( hret );
kolB = hret4->KolmogorovTest( hret2 );

// TString tex3text = Form( "K-S test: sig. (bkg.) prob. = %5.3g (%5.3g)", KSvalSig, KSvalBkg );
// tex3text = Form( "K-S test: sig. (bkg.) prob. = %5.3g (%5.3g)", kolS, kolB );
// // tex3text+=kolS;
// tex3 = new TLatex(-0.205266, yHeight + yHeight*0.06,tex3text.Data());
// tex3->SetTextFont(62);
// tex3->SetTextSize(0.034468);
// tex3->SetLineWidth(2);
// tex3->Draw();
// Double_t kolS2 = hret->KolmogorovTest( hret3 );

cout<<"kolS: "<< kolS<< endl;
// cout<<kolS2<<endl;
cout<<"kolB: "<< kolB << endl;










/////////////ROC
TH1F *hROC;
TH1F *hROC2;
TH1F *hROC3;
TH1F *hROC4;

int NumberOfBinsROC = 10000;
hROC = new TH1F("NameROC", "titleROC", NumberOfBinsROC, vec[0], vec.back());
hROC2 = new TH1F("NameROC2", "titleROC2", NumberOfBinsROC, vec[0], vec.back());
hROC3 = new TH1F("NameROC3", "titleROC3", NumberOfBinsROC, vec[0], vec.back());
hROC4 = new TH1F("NameROC4", "titleROC4", NumberOfBinsROC, vec[0], vec.back());
hROC->Sumw2();
hROC2->Sumw2();
hROC3->Sumw2();
hROC4->Sumw2();
for(int i = 0; i<TestTree->GetEntries(); i++){
    TestTree->GetEntry(i);
    ATestString= classNameTest ;
    if (ATestString.EqualTo("S")){
        hROC->Fill(BDTvarTest, TestWeight);}
    else if (ATestString.EqualTo("B")){
        hROC2->Fill(BDTvarTest, TestWeight);
    }
    // if (i%10000 == 0) cout<<"Debug "<<TestWeight<<endl;
}
for(int i = 0; i<TrainTree->GetEntries(); i++){
    TrainTree->GetEntry(i);
    ATrainString= classNameTrain ;
    if (ATrainString.EqualTo("S")){
        hROC3->Fill(BDTvarTrain, TrainWeight);}
    else if (ATrainString.EqualTo("B")){
        hROC4->Fill(BDTvarTrain, TrainWeight);
    }
    // if (i%1000 == 0) cout<<TrainWeight<<endl;
}
hROC->Scale(1.0/hROC->Integral(0, NumberOfBinsROC));
hROC2->Scale(1.0/hROC2->Integral(0, NumberOfBinsROC));
hROC3->Scale(1.0/hROC3->Integral(0, NumberOfBinsROC));
hROC4->Scale(1.0/hROC4->Integral(0, NumberOfBinsROC));

Double_t kolS_ROCbins = hROC3->KolmogorovTest( hROC );
Double_t kolB_ROCbins = hROC4->KolmogorovTest( hROC2 );
cout<<"kolS_ROCbins: "<< kolS_ROCbins<< endl;
// cout<<kolS2<<endl;
cout<<"kolB_ROCbins: "<< kolB_ROCbins << endl;

// vector<Double_t> sigTestIntegral;
// vector<Double_t> bkgTestIntegral;
// vector<Double_t> totalTestIntegral;

tex3text = Form( "K-S test: sig. (bkg.) prob. = %5.3g (%5.3g)", kolS_ROCbins, kolB_ROCbins );
// tex3text+=kolS;
tex3 = new TLatex(-0.205266, yHeight + yHeight*0.06,tex3text.Data());
tex3->SetTextFont(62);
tex3->SetTextSize(0.034468);
tex3->SetLineWidth(2);
tex3->Draw();





vector<Double_t> SigTestEff;
vector<Double_t> BkgTestRej;
for(int i = 0; i<NumberOfBinsROC; i++){
  // cout<<i<<endl;
  SigTestEff.push_back((hROC->Integral(NumberOfBinsROC-i, NumberOfBinsROC))/(hROC->Integral(0, NumberOfBinsROC))*100);
  BkgTestRej.push_back((1-(hROC2->Integral(NumberOfBinsROC-i, NumberOfBinsROC))/(hROC2->Integral(0, NumberOfBinsROC)))*100);
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
c1->SaveAs(DirName + FolderName+"/KS.pdf");
c2->SaveAs(DirName + FolderName+"/ROC.pdf");
ofstream ofileVals (DirName + FolderName+ "/ROCandKSvals.csv", ofstream::out);
ofileVals <<"MaxDepth,"<<"MinNodeSize,"<<"AdaBoostBeta,"<<"NTrees,"<<"ROC18,"<<"ROC36,"<<"ROC54," <<"KSvalSig,"<< "KSvalBkg" <<endl;
ofileVals <<MaxDepth<<","<<MinNodeSize<<","<<AdaBoostBeta<<","<<NTrees<<","<<sig18<<","<<sig36<<","<<sig54<<","<<kolS_ROCbins<< ","<< kolB_ROCbins <<endl;
ofileVals.close();

TFile ofile(DirName + FolderName+ "/ROC.root", "recreate");
grROC->Write();

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
