#include<TMath.h>
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasLabels.C"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasLabels.h"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasStyle.C"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasStyle.h"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasUtils.C"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasUtils.h"

// void MultiROC_wRun1(){
void PlotROCs_2020Jun26_PUtrained(){
    SetAtlasStyle();
// // TString dirName = "/Users/agrummer/cernbox/www/bmumu/myMVAOut/OutMVAmay10_bbeta05/";
// // TString dirName2 = "/Users/agrummer/cernbox/www/bmumu/myMVAOut/OutMVAmay10_7vars/";
// // TString DateName1 = "May24npv";
// // TString DateName1 = "OfficialMay24_WithWeights";
// // TString DateName1 = "Jun7_SidebandTraining/train1_test2";
// // TString DateName1 = "Jun7_RightSidebandTraining/train1_test2";
// // TString DateName1 = "May16";
// // TString dirName1 = "/Users/agrummer/cernbox/www/bmumu/OutMVA/EvalFolder2/"+DateName1+"/";
// // TString dirName1 = "/Users/agrummer/cernbox/www/bmumu/Data/May15/May24/out_MaxDepth4_MinNodeSize0.2_AdaBoostBeta0.5_NTrees500/";
// // TString dirName1 = "/Users/agrummer/cernbox/www/bmumu/OutMVA/EvalFolder2/OfficialMay24_WithWeights/";
// // TString DateName1 = "Jun11_SidebandTrained/EvalComboTEST";
// // TString DateName1 = "Jun12_SidebandTrained/EvalCombo";
// TString DateName1 = "Jun12_SidebandTrained/BDT1";
// // TString DateName1 = "Jun13MuIso_SidebandTrained/BDT1";
// TString dirName1 = "/Users/agrummer/cernbox/www/bmumu/OutMVA/EvalFolder2/"+DateName1+"/";

// // TString DateName1 = "Jun11_SidebandTrained/eval1";
// // TString dirName1 = "/Users/agrummer/cernbox/www/bmumu/OutMVA/EvalFolder2/"+DateName1+"/";
// // TString DateName2 = "May24";
// // TString DateName2 = "Jun7_SidebandTraining/train2_test1";
// // TString DateName2 = "Jun7_RightSidebandTraining/train2_test1";
// // TString DateName2 = "Jun11_SidebandTrained/eval2";
// TString DateName2 = "Jun12_SidebandTrained/BDT2";
// TString dirName2 = "/Users/agrummer/cernbox/www/bmumu/OutMVA/EvalFolder2/"+DateName2+"/";

// // TString DateName3 = "Jun11_SidebandTrained/eval3";
// TString DateName3 = "Jun12_SidebandTrained/BDT3";
// TString dirName3 = "/Users/agrummer/cernbox/www/bmumu/OutMVA/EvalFolder2/"+DateName3+"/";


// vector<TString> MaxDepth = {"4","6","8"};
// vector<TString> MinNodeSize = {"0.2","0.1","1.0"};
// vector<TString> AdaBoostBeta = {"0.5","0.2","0.1"};
// vector<TString> NTrees = {"500","500","500"};
// TString ROCFileNames = "ROC.root";


// // TString Tag = "_15varsOptimized";
// // TString Tag = "_May24npv";
// // TString Tag = "_May24_ww";
// // TString Tag = "_Jun7_train1_test2";
// // TString Tag = "_Jun7_RS_train1_test2";
// // TString Tag2 = "_7varsOptimized";
// // TString Tag2 = "_wDDWQLC";
// // TString Tag2 = "_wDDWQLC";
// // TString Tag2 = "_Jun7_train2_test1";
// // TString Tag2 = "_Jun7_RS_train2_test1";
// // TString Tag = "";

// // TString Tag = "_EVALcomboTEST";
// // TString Tag = "_EVALcombo_Jun12";

// TString Tag = "_SplitSet_3_BDT2016_Jun12_train1_test2";
// // TString Tag = "_SplitSet_3_BDT2016_Jun13MuIso_train1_test2";
// TString Tag2 = "_SplitSet_1_BDT2016_Jun12_train2_test3";
// TString Tag3 = "_SplitSet_2_BDT2016_Jun12_train3_test1";

// // TString vBDT = "_BDT2016";
// // TString vBDT = "_HighPileUp_BDT2016";
// // TString vBDT = "_MiddlePileUp_BDT2016";
// // TString vBDT = "_LowPileUp_BDT2016";
// // TString vBDT = "_bdt2012v4QLC";
// // TString vBDT = "";
// TString vBDT = "";
// TString vBDT2 = "";
// TString vBDT3 = "";
vector<TString> myfilenames;
// /afs/cern.ch/user/a/agrummer/www/bmumu2020/BDT/BDToutput/2020Jun16
TString dirNameRun1 = "/afs/cern.ch/user/a/agrummer/www/bmumu/OutMVA/EvalFolder2/";
// TString idir = "/Users/agrummer/cernbox/www/bmumu2020/BDT/BDToutput/2020May20/";
TString idir = "/afs/cern.ch/user/a/agrummer/www/bmumu2020/BDT/BDToutput/2020Jun16/";
TString idir2 = "/afs/cern.ch/user/a/agrummer/www/bmumu2020/BDT/BDToutput/2020Jun26/";
TString idir3 = "/afs/cern.ch/user/a/agrummer/www/bmumu2020/BDT/BDToutput/2020July16/";
// TString dirName1 = idir+"out_Custom/";
// TString dirName2 = idir2+"out_Run1privxmu/";
TString dirName2 = idir3+"out_Run1privxmu_round/";
TString dirName3 = idir+"out_Run1/";
// TString dirName4 = idir2+"out_Run1nPV/";
TString dirName4 = idir3+"out_Run1nPV_npvweights/";
// myfilenames.push_back(dirName +"ROC_15vars.root");
// myfilenames.push_back(dirName +"ROC_7vars_2.root");
// myfilenames.push_back(dirName1 +"EvalROC.root");
myfilenames.push_back(dirName2 +"EvalROC.root");
myfilenames.push_back(dirName3 +"EvalROC.root");
myfilenames.push_back(dirName4 +"EvalROC.root");
// myfilenames.push_back(dirNameRun1 +"ROC_bdt2012v4QLC.root");
// myfilenames.push_back(dirName +"out_MaxDepth"+ MaxDepth[0] +"_MinNodeSize" + MinNodeSize[0] +"_AdaBoostBeta"
//   + AdaBoostBeta[0]+"_NTrees" + NTrees[0] + "/" + ROCFileNames);
// myfilenames.push_back(dirName2 +"out_MaxDepth"+ MaxDepth[1] +"_MinNodeSize" + MinNodeSize[1] +"_AdaBoostBeta"
//   + AdaBoostBeta[1]+"_NTrees" + NTrees[1] + "/" + ROCFileNames);
// myfilenames.push_back(dirName +"out_MaxDepth"+ MaxDepth[2] +"_MinNodeSize" + MinNodeSize[2] +"_AdaBoostBeta"
//   + AdaBoostBeta[2]+"_NTrees" + NTrees[2] + "/" + ROCFileNames);

// filenames.push_back(dirName +'out_MaxDepth'+ str(mdval) +'_MinNodeSize' + str(minNode) +'_AdaBoostBeta'
//   + str(bbeta)+'_NTrees' + str(numTrees) + '/' + FileNames);


// TFile* ifilename1 = new TFile(myfilenames[0]);
TFile* ifilename2 = new TFile(myfilenames[0]);
// TFile* ifilename3 = new TFile(myfilenames[4]);
// TFile* ifilename3 = new TFile("/Users/agrummer/cernbox/www/bmumu/Data/rocsS1.root");
TFile* ifilename4 = new TFile(myfilenames[2]);
TFile* ifilename5 = new TFile(myfilenames[1]);

// Double_t ymin = 99.95;
// Double_t ymax = 100.;
// Double_t ymin = 99.97;
// Double_t ymin = 99.9988;
// // Double_t ymin = 99.955;
// // Double_t ymax = 100.02;
// Double_t ymax = 100.001;
// Double_t xmin = 0;
// Double_t xmax = 55;
Double_t ymin = 5e-6;
Double_t ymax = 0.1;
Double_t xmin = 0;
// Double_t xmax = 55;
Double_t xmax = 75;
// Double_t xmax = 57;
TCanvas* c2 = new TCanvas("c2", "Multi-ROC curve",0.,0., 800, 600);
c2->SetLogy(1);
// TGraph *graph1 = (TGraph*)ifilename1->Get("Graph");
// graph1->SetLineColor(kGreen+2);//kBlack
// graph1->SetFillColor(kGreen+2);//kBlack
// graph1->SetLineWidth(2);
// graph1->SetMarkerStyle(21);
// graph1->SetMarkerColor(kGreen+2);//kBlack
// graph1->SetMarkerSize(0.4);
// graph1->GetYaxis()->SetRangeUser(ymin, ymax);
// graph1->GetYaxis()->SetTitleOffset(1.2);
// graph1->GetXaxis()->SetRangeUser(xmin, xmax);
// graph1->GetXaxis()->SetTitle("Signal Efficiency [%]");
// graph1->GetYaxis()->SetTitle("Background Efficiency [%]");
// //Tag1
// const Int_t n = graph1->GetN();
// Double_t dx = 100.;
// Double_t *xs = graph1->GetY();
// for (Int_t i=0;i<n;i++) xs[i] = 100 - xs[i];



TGraph *graph2 = (TGraph*)ifilename2->Get("Graph");
graph2->SetLineColor(kRed+1);//kBlack
graph2->SetFillColor(kRed+1);//kBlack
graph2->SetLineWidth(2);
graph2->SetMarkerStyle(22);
graph2->SetMarkerColor(kRed+1);//kBlack
graph2->SetMarkerSize(0.4);
// graph2->GetYaxis()->SetRangeUser(98.95, 101.);
// graph2->GetXaxis()->SetRangeUser(0, 60);
const Int_t n2 = graph2->GetN();
Double_t dx2 = 100.;
Double_t *xs2 = graph2->GetY();
for (Int_t i=0;i<n2;i++) xs2[i] = 100 - xs2[i];
//Tag2

// TGraph *graph3 = (TGraph*)ifilename3->Get("Graph");
// graph3->SetLineColor(kBlue+1);//kBlack
// graph3->SetFillColor(kBlue+1);//kBlack
// graph3->SetLineWidth(2);
// graph3->SetMarkerStyle(23);
// graph3->SetMarkerColor(kBlue+1);//kBlack
// graph3->SetMarkerSize(0.4);
// // graph3->GetYaxis()->SetRangeUser(80., 100.02);
// // graph3->GetXaxis()->SetRangeUser(0, 40);
// const Int_t n3 = graph3->GetN();
// Double_t dx3 = 100.;
// Double_t *xs3 = graph3->GetY();
// for (Int_t i=0;i<n3;i++) xs3[i] = 100 - xs3[i];

// ///// Code from root forum to scale axis
// double scale(100.);
// int N=graph3->GetN(); 
// double *G3yaxis=graph3->GetY(); 
// double *G3xaxis=graph3->GetX(); 
// int i=0; 
// while(i<N) { 
//     G3yaxis[i]=G3yaxis[i]*scale; 
//     G3xaxis[i]=G3xaxis[i]*scale; 
//     i=i+1;
// }
//  graph3->GetHistogram()->Delete(); 
//  graph3->SetHistogram(0);
// // graph3->GetYaxis()->SetRangeUser(99.98, 100.02);
// graph3->GetXaxis()->SetRangeUser(0, 40);

TGraph *graph4 = (TGraph*)ifilename4->Get("Graph");
graph4->SetLineColor(kMagenta+2);//kBlack
graph4->SetFillColor(kMagenta+2);//kBlack
graph4->SetLineWidth(2);
graph4->SetMarkerStyle(32);
graph4->SetMarkerColor(kMagenta+2);//kBlack
graph4->SetMarkerSize(0.4);
// graph4->GetYaxis()->SetRangeUser(98.95, 101.);
// graph4->GetXaxis()->SetRangeUser(0, 60);
const Int_t n4 = graph4->GetN();
Double_t dx4 = 100.;
Double_t *xs4 = graph4->GetY();
for (Int_t i=0;i<n4;i++) xs4[i] = 100 - xs4[i];
//Tag3

// TGraph *graph5 = (TGraph*)ifilename5->Get("ROCDATA12BDT12_1_0");
TGraph *graph5 = (TGraph*)ifilename5->Get("Graph");
graph5->SetLineColor(kBlack);//kBlack
graph5->SetFillColor(kBlack);//kBlack
graph5->SetLineWidth(2);
graph5->SetMarkerStyle(33);
graph5->SetMarkerColor(kBlack);//kBlack
graph5->SetMarkerSize(0.4);
graph5->GetYaxis()->SetRangeUser(ymin, ymax);
graph5->GetYaxis()->SetTitleOffset(1.2);
graph5->GetXaxis()->SetRangeUser(xmin, xmax);
graph5->GetXaxis()->SetTitle("Signal Efficiency [%]");
graph5->GetYaxis()->SetTitle("Background Efficiency [%]");
// graph5->GetYaxis()->SetRangeUser(98.95, 101.);
// graph5->GetXaxis()->SetRangeUser(0, 60);
const Int_t n5 = graph5->GetN();
Double_t dx5 = 100.;
Double_t *xs5 = graph5->GetY();
for (Int_t i=0;i<n5;i++) xs5[i] = 100 - xs5[i];


graph5->Draw("ap");
graph2->Draw("Psame");
// graph3->Draw("Psame");
graph4->Draw("Psame");
// graph1->Draw("Psame");


TLegend* leg;
// leg = new TLegend(0.194842, 0.795789, 0.531519, 0.909474,NULL,"brNDC");
// leg = new TLegend(0.234336, 0.765217, 0.383459, 0.914783,NULL,"brNDC");
leg = new TLegend(0.233083, 0.717391, 0.382206, 0.868696,NULL,"brNDC");
leg->SetTextSize(0.034468);
// for (int i=0; i<3; i++){
// myfilenames[i].ReplaceAll(dirName, "");
// myfilenames[i].ReplaceAll("/"+ROCFileNames, "");
// myfilenames[i].ReplaceAll("_", " ");
// myfilenames[i].ReplaceAll("out ", "");
// }
// leg->AddEntry(graph1, "Run 2 BDT trained with nPV","f");
// leg->AddEntry(graph1, "Run 2 BDT Test Sample","f");
// leg->AddEntry(graph1, "Run 2 BDT with Weighted Signal MC Evaluation Sample","f");
// leg->SetHeader("Train and test with Right Sideband");
// leg->SetHeader("Train and test with Sidebands");
// leg->AddEntry(graph1, "Run 2 BDT","f");
// leg->AddEntry(graph1, "Run 2 BDT (15 vars)","f");
// leg->AddEntry(graph2, "Run 2 BDT switched background training and testing samples" ,"f");
// leg->AddEntry(graph2, "Run 2 BDT Eval Sample" ,"f");
// leg->AddEntry(graph2, "Run 2 BDT Pre-Evaluation Weights" ,"f");
// leg->AddEntry(graph2, "Run 2 BDT w/DDW+QLC weights" ,"f");
// leg->AddEntry(graph2, "Run 2 BDT (new optimization)" ,"f");
// leg->SetHeader("Sideband Data");
// leg->AddEntry(graph1, "Run 2 BDT","f");
//
//
// leg->AddEntry(graph1, "Run 2 BDT1","f");
// leg->AddEntry(graph2, "Run 2 BDT2" ,"f");
// leg->AddEntry(graph4, "Run 2 BDT3" ,"f");
// leg->AddEntry(graph3, "Run 1 BDT on Run 1 DATA" ,"f");
// leg->AddEntry(graph5, "Run 1 BDT on DATA '15/'16" ,"f");
// leg->AddEntry(graph1, "Custom Iso Vars","l");
leg->SetHeader("As in Run 1 B Iso and as in Run 2 closeTrk Vars");
leg->AddEntry(graph5, "No Extra PU Variable" ,"l");
// leg->AddEntry(graph2, "With PRIVX mu Variable" ,"l");
leg->AddEntry(graph2, "With PRIVX mu Variable (rounded)" ,"l");
// leg->AddEntry(graph4, "With nPV Variable" ,"l");
leg->AddEntry(graph4, "With nPV Variable (NPV weights)" ,"l");
// leg->AddEntry(graph3, "Run 1 BDT on Run 1 DATA" ,"pl");
// leg->AddEntry(graph5, "Run 1 BDT on DATA '15/'16" ,"f");
leg->SetBorderSize(0);  // no border
leg->SetLineColor(0);
leg->SetFillColor(0);
leg->Draw();
ATLASLabel(0.259398, 0.893913,"Internal",1);

c2->Update();
// c2->SaveAs(dirName1+"MultiROC_wRun1_zoom.pdf");
// c2->SaveAs(idir+"ROC_compareInputVars.pdf");
// c2->SaveAs(idir2+"ROC_Run1PUtrained.pdf");
c2->SaveAs(idir3+"ROC_Run1PUtrained_2020July16.pdf");

return(0);
}