// MultiROCcomp.C
// Author: Aidan G
// Aug. 6, 2018
// 
// Code takes input root graphs and make comparison plots
// Converts Background rejection to Background efficiency
// Graph 2 and Graph 4 are not drawn (commented out) when plotting the combined Run2 BDT

// Change directory and filenames (presently lines 19 to 60) - output plot saved in dirName1

#include<TMath.h>
#include "../AnalysisTools/Utils/AtlasStyle/AtlasLabels.C"
#include "../AnalysisTools/Utils/AtlasStyle/AtlasLabels.h"
#include "../AnalysisTools/Utils/AtlasStyle/AtlasUtils.C"
#include "../AnalysisTools/Utils/AtlasStyle/AtlasUtils.h"
#include "../AnalysisTools/Utils/AtlasStyle/AtlasStyle.C"
#include "../AnalysisTools/Utils/AtlasStyle/AtlasStyle.h"

void MultiROCcomp(){
 SetAtlasStyle();
///////////////////////////////////////////////////////////////////////

TString myDir = "/Users/agrummer/cernbox/www/bmumu/OutMVA/EvalFolder2/";
TString DirName = "/Users/agrummer/cernbox/www/bmumu/myMVA/IsolationStudies/";
// TString DateName1 = "Jun12_SidebandTrained/BDT1";
// TString DateName1 = "Jun13MuIso_SidebandTrained/BDT1";
TString DateName1 = "Jun12_SidebandTrained/EvalCombo";
TString dirName1 = myDir + DateName1 + "/";

TString DateName2 = "Jun12_SidebandTrained/BDT2";
TString dirName2 = myDir + DateName2 + "/";

TString DateName3 = "Jun12_SidebandTrained/BDT3";
TString dirName3 = myDir + DateName3 + "/";

TString dirNameRun1 = myDir;

vector<TString> myfilenames;

TString Tag = "_EVALcombo_Jun12";
// TString Tag = "_SplitSet_3_BDT2016_Jun12_train1_test2";
// TString Tag = "_SplitSet_3_BDT2016_Jun13MuIso_train1_test2";
TString Tag2 = "_SplitSet_1_BDT2016_Jun12_train2_test3";
TString Tag3 = "_SplitSet_2_BDT2016_Jun12_train3_test1";

// TString vBDT = "_BDT2016";
// TString vBDT = "_HighPileUp_BDT2016";
// TString vBDT = "_MiddlePileUp_BDT2016";
// TString vBDT = "_LowPileUp_BDT2016";
// TString vBDT = "_bdt2012v4QLC";
TString vBDT = "";
TString vBDT2 = "";
TString vBDT3 = "";

// The file names in the order - 3 BDT ROCs (in the case of only one BDT ROC - for the combined BDT - the second two are not plotted),
//The last one is the run 1 BDT applied to Run 2 data 
// myfilenames.push_back(dirName1 +"ROC"+vBDT+Tag+".root");
// myfilenames.push_back(dirName2 +"ROC"+vBDT2+Tag2+".root");
// myfilenames.push_back(dirName3 +"ROC"+vBDT3+Tag3+".root");
myfilenames.push_back(DirName +"out_2016run_Default/ROC"+".root");
myfilenames.push_back(DirName +"out_2016run_AllTracksVariables/ROC"+".root");
myfilenames.push_back(DirName +"out_2016run_AllTracks_PVweights/ROC"+".root");
myfilenames.push_back(dirNameRun1 +"ROC_bdt2012v4QLC.root");

///////////////////////////////////////////////////////////////////////

//Load the files from the file names
//ifilename3 is taken from the run 1 analysis
//ifilename2 and ifilename4 should not be plotted in the case for the combined Run 2 BDT 
TFile* ifilename1 = new TFile(myfilenames[0]);
TFile* ifilename2 = new TFile(myfilenames[1]);
TFile* ifilename3 = new TFile("/Users/agrummer/cernbox/www/bmumu/Data/rocsS1.root");
TFile* ifilename4 = new TFile(myfilenames[2]);
TFile* ifilename5 = new TFile(myfilenames[3]);

// Double_t ymin = 99.95;
// Double_t ymax = 100.;
// Double_t ymin = 99.97;
// Double_t ymin = 99.9988;
Double_t ymin = 5e-5;
// Double_t ymin = 99.955;
// Double_t ymax = 100.02;
// Double_t ymax = 100.001;
Double_t ymax = 0.1;
Double_t xmin = 0;
Double_t xmax = 55;
// Double_t xmax = 57;
TCanvas* c2 = new TCanvas("c2", "Multi-ROC curve",0.,0., 800, 600);
//Log scale for the background efficiency plot
c2->SetLogy(1);
TGraph *graph1 = (TGraph*)ifilename1->Get("Graph");
graph1->SetLineColor(kGreen+2);//kBlack
graph1->SetFillColor(kGreen+2);//kBlack
graph1->SetLineWidth(1);
graph1->SetMarkerStyle(20);
graph1->SetMarkerColor(kGreen+2);//kBlack
graph1->SetMarkerSize(0.2);
graph1->GetYaxis()->SetRangeUser(ymin, ymax);
// graph1->SetMinimum(ymin);
graph1->GetYaxis()->SetTitleOffset(1.2);
graph1->GetXaxis()->SetRangeUser(xmin, xmax);
graph1->GetXaxis()->SetTitle("Signal Efficiency [%]");
graph1->GetYaxis()->SetTitle("Background Efficiency [%]");

// Change plots from Background rejection to Background efficiency
const Int_t n = graph1->GetN();
Double_t dx = 100.;
Double_t *xs = graph1->GetY();
for (Int_t i=0;i<n;i++) xs[i] = 100 - xs[i];
//Tag1
graph1->Draw("AP");



TGraph *graph2 = (TGraph*)ifilename2->Get("Graph");
graph2->SetLineColor(kRed+2);//kBlack
graph2->SetFillColor(kRed+2);//kBlack
graph2->SetLineWidth(1);
graph2->SetMarkerStyle(20);
graph2->SetMarkerColor(kRed+2);//kBlack
graph2->SetMarkerSize(0.2);
// graph2->GetYaxis()->SetRangeUser(98.95, 101.);
// graph2->GetXaxis()->SetRangeUser(0, 60);

// Change plots from Background rejection to Background efficiency
const Int_t n2 = graph2->GetN();
Double_t dx2 = 100.;
Double_t *xs2 = graph2->GetY();
for (Int_t i=0;i<n2;i++) xs2[i] = 100 - xs2[i];
//Tag2
graph2->Draw("Psame");

TGraph *graph3 = (TGraph*)ifilename3->Get("ROCDATA12BDT12_1_0");
graph3->SetLineColor(kBlue+2);//kBlack
graph3->SetFillColor(kBlue+2);//kBlack
graph3->SetLineWidth(1);
graph3->SetMarkerStyle(20);
graph3->SetMarkerColor(kBlue+2);//kBlack
graph3->SetMarkerSize(0.2);
// graph3->GetYaxis()->SetRangeUser(80., 100.02);
graph3->GetXaxis()->SetRangeUser(0, 40);

///// Code from root forum to scale axis
// Scales the ROC from run 1 analysis to be in percentage
double scale(100.);
int N=graph3->GetN(); 
double *G3yaxis=graph3->GetY(); 
double *G3xaxis=graph3->GetX(); 
int i=0; 
while(i<N) { 
    G3yaxis[i]=G3yaxis[i]*scale; 
    G3xaxis[i]=G3xaxis[i]*scale; 
    i=i+1;
}
 graph3->GetHistogram()->Delete(); 
 graph3->SetHistogram(0);
// graph3->GetYaxis()->SetRangeUser(99.98, 100.02);
// graph3->GetXaxis()->SetRangeUser(0, 40);

// Change plots from Background rejection to Background efficiency
const Int_t n3 = graph3->GetN();
Double_t dx3 = 100.;
Double_t *xs3 = graph3->GetY();
for (Int_t i=0;i<n3;i++) xs3[i] = 100 - xs3[i];
graph3->Draw("Psame");

TGraph *graph4 = (TGraph*)ifilename4->Get("Graph");
graph4->SetLineColor(kYellow);//kBlack
graph4->SetFillColor(kYellow);//kBlack
graph4->SetLineWidth(1);
graph4->SetMarkerStyle(20);
graph4->SetMarkerColor(kYellow);//kBlack
graph4->SetMarkerSize(0.2);
// graph4->GetYaxis()->SetRangeUser(98.95, 101.);
// graph4->GetXaxis()->SetRangeUser(0, 60);

// Change plots from Background rejection to Background efficiency
const Int_t n4 = graph4->GetN();
Double_t dx4 = 100.;
Double_t *xs4 = graph4->GetY();
for (Int_t i=0;i<n4;i++) xs4[i] = 100 - xs4[i];
//Tag3
graph4->Draw("Psame");

TGraph *graph5 = (TGraph*)ifilename5->Get("Graph");
graph5->SetLineColor(kBlack);//kBlack
graph5->SetFillColor(kBlack);//kBlack
graph5->SetLineWidth(1);
graph5->SetMarkerStyle(20);
graph5->SetMarkerColor(kBlack);//kBlack
graph5->SetMarkerSize(0.2);
// graph5->GetYaxis()->SetRangeUser(98.95, 101.);
// graph5->GetXaxis()->SetRangeUser(0, 60);

// Change plots from Background rejection to Background efficiency
const Int_t n5 = graph5->GetN();
Double_t dx5 = 100.;
Double_t *xs5 = graph5->GetY();
for (Int_t i=0;i<n5;i++) xs5[i] = 100 - xs5[i];
graph5->Draw("Psame");

TLegend* leg;
// leg = new TLegend(0.194842, 0.795789, 0.531519, 0.909474,NULL,"brNDC");
// leg = new TLegend(0.234336, 0.765217, 0.383459, 0.914783,NULL,"brNDC");
leg = new TLegend(0.233083, 0.717391, 0.382206, 0.868696,NULL,"brNDC");
leg->SetTextSize(0.034468);

// leg->SetHeader("Sideband Data");
// leg->AddEntry(graph1, "Run 2 BDT","f");
leg->AddEntry(graph1, "MC16a + 2016 Run 302393 Default","f");
leg->AddEntry(graph2, "MC16a + 2016 Run 302393 All Trks" ,"f");
leg->AddEntry(graph4, "MC16a + 2016 Run 302393 All Trks and PV Weights" ,"f");
// leg->AddEntry(graph1, "Run 2 BDT1","f");
// leg->AddEntry(graph2, "Run 2 BDT2" ,"f");
// leg->AddEntry(graph4, "Run 2 BDT3" ,"f");
leg->AddEntry(graph3, "Run 1 BDT on Run 1 DATA" ,"f");
leg->AddEntry(graph5, "Run 1 BDT on DATA '15/'16" ,"f");
leg->SetBorderSize(0);  // no border
leg->SetLineColor(0);
leg->SetFillColor(0);
leg->Draw();
ATLASLabel(0.259398, 0.893913,"Internal",1);


// Output plot is put in dirName1 
c2->Update();
// c2->SaveAs(dirName1+"MultiROC_wRun1_LogAccept.pdf");
// c2->SaveAs(dirName1+"MultiROC_wRun1_LogAccept2018July17.pdf");
c2->SaveAs(DirName+"MultiROC_wRun1_LogAccept2019May29.pdf");

return(0);
}