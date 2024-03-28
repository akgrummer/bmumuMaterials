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

TH1F* RetrieveHist(TString tmpYear = "",  TString DataType = "", 
                    VariableInfo myVar = Bisolation, Int_t ColorIndex=0,
                    TString FileDate = "", TString Pileup= "") {
// TString DirName = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/";
TString DirName = "/eos/home-a/agrummer/BsmumuData/FinalSkim/v4/";
TString ifilename("");
TString tmp_mcName("");
TString runName("");
TCut myCut("");
TCut RunNumberCut("");
TH1F* myHist(NULL);
if (tmpYear.EqualTo("2016")){
    tmp_mcName = "MC16a";
    runName = "2016 Run 302393";
    RunNumberCut = "run_number==302393";
}else if(tmpYear.EqualTo("2017")){
    tmp_mcName = "MC16d";
    runName = "2017 Run 339849";
    RunNumberCut = "run_number==339849";
 }else if(tmpYear.EqualTo("2018")){
    tmp_mcName = "MC16e";
    runName = "2018 Run 358096";
    RunNumberCut = "run_number==358096";
 }

if (DataType.EqualTo("data")) {
    if (tmpYear.EqualTo("2016")){
        // ifilename = DirName + tmpYear+"All/LASTskim_"+tmpYear+"_All_2019Jun5.root";
        ifilename = DirName + tmpYear+"All/LASTskim_"+tmpYear+"_All_"+FileDate+".root";
    }
    else{
        // ifilename = DirName + tmpYear+"All/LASTskim_"+tmpYear+"_All_2019Jun3.root";
        ifilename = DirName + tmpYear+"All/LASTskim_"+tmpYear+"_All_"+FileDate+".root";
    }
        myCut = CutAdd;
    }
else if (DataType.EqualTo("mc")) { 
    if (tmpYear.EqualTo("2016")){
        // ifilename = DirName + tmp_mcName+"All/LASTskim_"+tmp_mcName+"_All_2019Jun5.root";
        ifilename = DirName + tmp_mcName+"All/LASTskim_"+tmp_mcName+"_All_"+FileDate+".root";
    }else{
        // ifilename = DirName + tmp_mcName+"All/LASTskim_"+tmp_mcName+"_All_2019Jun3.root";
        ifilename = DirName + tmp_mcName+"All/LASTskim_"+tmp_mcName+"_All_"+FileDate+".root";
    }
        myCut= CutAdd*RunNumberCut*"PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
    }

if (Pileup.EqualTo("lowlow")) {
myCut = myCut*("PRIVX_mu >= 12. && PRIVX_mu <= 22.");
}else if (Pileup.EqualTo("low")) {
myCut = myCut*("PRIVX_mu >= 23. && PRIVX_mu <= 33.");
}else if(Pileup.EqualTo("medium")) {
myCut = myCut*("PRIVX_mu >= 34. && PRIVX_mu <= 44.");
}else if(Pileup.EqualTo("high")) {
myCut = myCut*("PRIVX_mu >= 45. && PRIVX_mu <= 55.");
} 
    

TFile* ifile = new TFile(ifilename);
TTree *myTree = (TTree*)ifile->Get("T_mv");
cout<<tmpYear<<" "<< DataType <<" Tree Entries: "<<myTree->GetEntries()<<endl;
myHist = getHistoFromTree(myTree, myVar, myVar.name+tmpYear, myCut);

myHist->SetMarkerColor(ColorWheel[ColorIndex]);
myHist->SetLineColor(ColorWheel[ColorIndex]);
myHist->SetMarkerStyle(20);
if(DataType.EqualTo("data")) {
myHist->SetMarkerSize(0.9);
}
else{
myHist->SetMarkerSize(0);
}
myHist->SetLineWidth(2);
// myHist->SetLineStyle(ColorIndex+1);
// myHist->GetYaxis()->SetTitle("Bkg. Rejection [%]");
// myHist->GetXaxis()->SetTitle("Sig. Efficiency [%]");
// 
// myHist->GetYaxis()->SetTitle("Candidates");
myHist->Scale(1./myHist->Integral(0, myVar.nbins + 1));
myHist->GetYaxis()->SetTitle("a.u.");
return myHist;
}

TH1F* RetrieveHistRun1(TString DataType = "", 
                    VariableInfo myVar = Bisolation, Int_t ColorIndex=0,
                    TString FileDate = "", TString Pileup= "") {
TString ifilename("");
TString tmp_mcName("");
TString runName("");
TCut myCut("");
TString tmpYear("Run1");
TCut RunNumberCut("");
TH1F* myHist(NULL);

if (DataType.EqualTo("data")) {
        ifilename = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun1/data/Bsmumu/data12_8TeVBsAllPeriodsUnblinded.root";
        myCut = CutRun1;
    }
else if (DataType.EqualTo("mc")) { 
        ifilename = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun1/mc12/Bsmumu/mc12_8TeV.208426.Pythia8B_AU2_CTEQ6L1_Bs_mu3p5mu3p5.r3549.172133.staco.Bs2mumu_Bs.v12.s1.wTRUTHvarsANDnoMCPcuts.root";
        myCut= CutRun1*"PVWeights";
    }

if (Pileup.EqualTo("lowlow")) {
myCut = myCut*("PRIVX_mu >= 12. && PRIVX_mu <= 22.");
}else if (Pileup.EqualTo("low")) {
myCut = myCut*("PRIVX_mu >= 23. && PRIVX_mu <= 33.");
}else if(Pileup.EqualTo("medium")) {
myCut = myCut*("PRIVX_mu >= 34. && PRIVX_mu <= 44.");
}else if(Pileup.EqualTo("high")) {
myCut = myCut*("PRIVX_mu >= 45. && PRIVX_mu <= 55.");
} 
    

TFile* ifile = new TFile(ifilename);
TTree *myTree = (TTree*)ifile->Get("T_mv");
cout<<tmpYear<<" "<< DataType <<" Tree Entries: "<<myTree->GetEntries()<<endl;
myHist = getHistoFromTree(myTree, myVar, myVar.name+tmpYear, myCut);

myHist->SetMarkerColor(ColorWheel[ColorIndex]);
myHist->SetLineColor(ColorWheel[ColorIndex]);
myHist->SetMarkerStyle(20);
if(DataType.EqualTo("data")) {
myHist->SetMarkerSize(0.9);
}
else{
myHist->SetMarkerSize(0);
}
myHist->SetLineWidth(2);
// myHist->SetLineStyle(ColorIndex+1);
// myHist->GetYaxis()->SetTitle("Bkg. Rejection [%]");
// myHist->GetXaxis()->SetTitle("Sig. Efficiency [%]");
// myHist->GetYaxis()->SetTitle("Candidates");
myHist->Scale(1./myHist->Integral(0, myVar.nbins + 1));
myHist->GetYaxis()->SetTitle("a.u.");
return myHist;
}

void makePlots(TString DataType ="", 
                TString theVar="", TString FileDate = "",
                VariableInfo myVar = closeTrkDOCA, bool Run1set=false){
    SetAtlasStyle();

///////////////////
// TString theYear="2018";
// TString DataType = "data";
// TString DataType = "mc";
// TString theRunNumber("");
// TString mcName("");
// if (theYear.EqualTo("2016")){
//     theRunNumber = " Run 302393";
//     mcName = "MC16a";
// }
// else if (theYear.EqualTo("2017")){
//     theRunNumber = " Run 339849";
//     mcName = "MC16d";
// }
// else if (theYear.EqualTo("2018")){
//     theRunNumber = " Run 358096";
//     mcName = "MC16e";
// }
//
// TH1F* h2016data_Default(NULL);
// TH1F* h2016data_TTVA_custom_c1(NULL);
// TH1F* h2016data_TTVA_custom_c2(NULL);
// TH1F* h2016data_all_c1(NULL);
Int_t ColorIndex = 0;
//
// closeTrkNtrks_TTVA_custom_c1
// closeTrkNtrks_TTVA_custom_c2
// closeTrkNtrks_all_c1
// closeTrkNtrks_all_c2
TH1F* h_lowlow(NULL);
TH1F* h_low(NULL);
TH1F* h_medium(NULL);
TH1F* h_high(NULL);
if (!Run1set){
ColorIndex = 0;
h_lowlow = RetrieveHist("2018", DataType, myVar, ColorIndex, FileDate, "lowlow");
ColorIndex = 1;
h_low = RetrieveHist("2017", DataType, myVar, ColorIndex, FileDate, "low");
ColorIndex = 2;
h_medium = RetrieveHist("2017", DataType, myVar, ColorIndex, FileDate, "medium");
ColorIndex = 3;
h_high = RetrieveHist("2017", DataType, myVar, ColorIndex, FileDate, "high");
}else{
h_lowlow = RetrieveHistRun1(DataType, myVar, ColorIndex, FileDate, "lowlow");
ColorIndex = 1;
h_low = RetrieveHistRun1(DataType, myVar, ColorIndex, FileDate, "low");
ColorIndex = 2;
h_medium = RetrieveHistRun1(DataType, myVar, ColorIndex, FileDate, "medium");  
}


TCanvas* c2 = new TCanvas("c2", "Var Comps",0.,0., 800, 600);
    TPad *pad1, *pad2;
    pad1 = new TPad("pad1","pad1",0.,0.33,1.,1.); //xlow ylow xup yup
    pad2 = new TPad("pad2","pad2",0.,0.,1.,0.33); //0.3
    pad1->SetLogy();
    pad1->SetMargin(0.16,0.05,0.05,0.09);//left, right, bottom, top
    pad1->SetBorderMode(0);
    pad2->SetMargin(0.16,0.05,0.38,0.05);//left, right, bottom, top
    pad2->SetBorderMode(0);
    pad2->Draw();
    pad1->Draw();
    pad1->cd();

    Double_t ymin;
    Double_t ymax;
    Double_t xmin;
    Double_t xmax;
    if(DataType.EqualTo("data")){
        // h2016data->Draw("e0psame");
        if(theVar.EqualTo("DOCA")){
            ymin = 1e-5;
            ymax = 5e0;
            xmin = -0.1;
            xmax = 3.2;
            // xmax = 5.0;
        }else{
            ymin = 1e-4;
            ymax = 5e-1;
            xmin = 0;
            xmax = 60;
        }
        //Don't use SetLimits for Histograms!!!
        // h_lowlow->GetXaxis()->SetLimits(xmin, xmax);// along X
        // h_low->GetXaxis()->SetLimits(xmin, xmax);// along X
        // h_medium->GetXaxis()->SetLimits(xmin, xmax);// along X
        // if (!Run1set) h_high->GetXaxis()->SetLimits(xmin, xmax);// along X
        h_lowlow->GetXaxis()->SetRangeUser(xmin, xmax);// along X
        h_low->GetXaxis()->SetRangeUser(xmin, xmax);// along X
        h_medium->GetXaxis()->SetRangeUser(xmin, xmax);// along X
        if (!Run1set) h_high->GetXaxis()->SetRangeUser(xmin, xmax);// along X
        cout<<"Integral of lowlow data: "<<h_lowlow->Integral(0, myVar.nbins + 1)<<endl;
        cout<<"Integral of low data: "<<h_low->Integral(0, myVar.nbins + 1)<<endl;
        cout<<"Integral of medium data: "<<h_medium->Integral(0, myVar.nbins + 1)<<endl;
        h_lowlow->SetMaximum(ymax);   // along          
        h_lowlow->SetMinimum(ymin);  //   Y  
        h_low->SetMaximum(ymax);   // along          
        h_low->SetMinimum(ymin);  //   Y  
        h_medium->SetMaximum(ymax);   // along          
        h_medium->SetMinimum(ymin);  //   Y  
        if (!Run1set) h_high->SetMaximum(ymax);   // along          
        if (!Run1set) h_high->SetMinimum(ymin);  //   Y  
        h_lowlow->Draw("e0p");
        h_low->Draw("e0psame");
        h_medium->Draw("e0psame");
        if (!Run1set) h_high->Draw("e0psame");
    }
    else if(DataType.EqualTo("mc")){
        if(theVar.EqualTo("DOCA")){
            ymin = 1e-5;
            ymax = 1e1;
            xmin = -0.1;
            xmax = 3.2;
            // xmax = 5.0;
        }
        else{
            ymin = 1e-5;
            ymax = 1e1;
            xmin = 0;
            xmax = 60;
        }
        //dont use SetLimits for histograms!!!
        // h_lowlow->GetXaxis()->SetLimits(xmin, xmax);// along X
        // h_low->GetXaxis()->SetLimits(xmin, xmax);// along X
        // h_medium->GetXaxis()->SetLimits(xmin, xmax);// along X
        // if (!Run1set) h_high->GetXaxis()->SetLimits(xmin, xmax);// along X        
        h_lowlow->GetXaxis()->SetRangeUser(xmin, xmax);// along X
        h_low->GetXaxis()->SetRangeUser(xmin, xmax);// along X
        h_medium->GetXaxis()->SetRangeUser(xmin, xmax);// along X
        if (!Run1set) h_high->GetXaxis()->SetRangeUser(xmin, xmax);// along X        
        cout<<"Integral of lowlow mc: "<<h_lowlow->Integral(0, myVar.nbins + 1)<<endl;
        cout<<"Integral of low mc: "<<h_low->Integral(0, myVar.nbins + 1)<<endl;
        cout<<"Integral of medium mc: "<<h_medium->Integral(0, myVar.nbins + 1)<<endl;

        h_lowlow->SetMaximum(ymax);   // along          
        h_lowlow->SetMinimum(ymin);  //   Y  
        h_low->SetMaximum(ymax);   // along          
        h_low->SetMinimum(ymin);  //   Y  
        h_medium->SetMaximum(ymax);   // along          
        h_medium->SetMinimum(ymin);  //   Y  
        if (!Run1set) h_high->SetMaximum(ymax);   // along          
        if (!Run1set) h_high->SetMinimum(ymin);  //   Y  
        h_lowlow->Draw("hist e0");
        h_low->Draw("hist e0 same");
        h_medium->Draw("hist e0 same");
        if (!Run1set) h_high->Draw("hist e0 same");
        // h2016data_Chi6->Draw("hist e0 same");
        // h2016data_Chi5->Draw("hist e0 same");
        // h2016data_Chi4->Draw("hist e0 same");
    }


TLegend* leg2(NULL);
// leg2 = new TLegend(1, 0.06, 5, 0.08,NULL,"brNDC");
// leg2 = new TLegend(0.218045, 0.721739, 0.418546, 0.770435,NULL,"brNDC");
TString theTracks="";

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

// leg2 = new TLegend(0.218045, 0.2, 0.418546, 0.4,NULL,"brNDC");
if (DataType.EqualTo("data")) {
    atlasLabel(0.62, 0.8, false, true, 1, true, false, true);
    if (theVar.EqualTo("nCloseTrks")){
        leg2 = new TLegend(0.23, 0.2, 0.43, 0.45,NULL,"brNDC");
        }
    else{
        leg2 = new TLegend(0.61, 0.55, 0.81, 0.8,NULL,"brNDC");
        }
}
else if (DataType.EqualTo("mc")) {
    atlasLabel(0.62, 0.85, false, true, 1, true, false, true);
    // atlasLabel(0.2, 0.83, false, true, 1, true, false, true);
    leg2 = new TLegend(0.61, 0.6, 0.81, 0.85,NULL,"brNDC");
    // leg2 = new TLegend(0.22, 0.57, 0.42, 0.8,NULL,"brNDC");
}
if (dummyVarName.EqualTo("closeTrkNtrksChi2")){
   if (!Run1set) leg2->SetHeader("2015+2016 Computation");
   else leg2->SetHeader("Run 1");
}else if (dummyVarName.EqualTo("closeTrkNtrks_TTVA_custom_c1")){
   leg2->SetHeader("Custom TTVA WP and #chi^{2}_{SV} #leq 1");
}else if (dummyVarName.EqualTo("closeTrkNtrks_TTVA_custom_c2")){
   leg2->SetHeader("Custom TTVA WP and #chi^{2}_{SV} #leq 2");
}else if (dummyVarName.EqualTo("closeTrkNtrks_all_c1")){
   leg2->SetHeader("Old Assoc., #chi^{2}_{SV} #leq 1");
}else if (dummyVarName.EqualTo("closeTrkNtrks_all_c2")){
   leg2->SetHeader("Old Assoc., #chi^{2}_{PV} #leq 2");
}

if (dummyVarName.EqualTo("closeTrkDOCA")){
   if (!Run1set) leg2->SetHeader("2015+2016 Computation");
   else leg2->SetHeader("Run 1");
}else if (dummyVarName.EqualTo("closeTrkDOCA_TTVA_custom_c7")){
   leg2->SetHeader("Custom TTVA WP, #chi^{2}_{SV} #leq 7");
}else if (dummyVarName.EqualTo("closeTrkDOCA_TTVA_custom_c2")){
   leg2->SetHeader("Custom TTVA WP, #chi^{2}_{SV} #leq 2");
}else if (dummyVarName.EqualTo("closeTrkDOCA_all_c7")){
   leg2->SetHeader("Old Assoc., #chi^{2}_{SV} #leq 7");
}else if (dummyVarName.EqualTo("closeTrkDOCA_all_c2")){
   leg2->SetHeader("Old Assoc., #chi^{2}_{PV} #leq 2");
}
// leg2->SetHeader(mcName);
if(DataType.EqualTo("data")){
// leg2->AddEntry(hRun1, ,"pe");
leg2->AddEntry(h_lowlow, PileupHeader_lowlow,"pe");
leg2->AddEntry(h_low, PileupHeader_low,"pe");
leg2->AddEntry(h_medium, PileupHeader_medium,"pe");
if (!Run1set) leg2->AddEntry(h_high, PileupHeader_high,"pe");
}else if(DataType.EqualTo("mc")){
// leg2->AddEntry(hRun1, ,"l");
leg2->AddEntry(h_lowlow, PileupHeader_lowlow,"l");
leg2->AddEntry(h_low, PileupHeader_low,"l");
leg2->AddEntry(h_medium, PileupHeader_medium,"l");
if (!Run1set) leg2->AddEntry(h_high, PileupHeader_high,"l");
    }

leg2->SetBorderSize(0);  // no border
leg2->SetLineColor(0);
leg2->SetFillColor(0);
leg2->SetTextSize(0.025);
leg2->Draw();

pad2->cd();

TH1F* h_lowlow_Res(NULL);
TH1F* h_low_Res(NULL);
TH1F* h_medium_Res(NULL);
TH1F* h_high_Res(NULL);

h_lowlow_Res = (TH1F*)h_lowlow->Clone("h_lowlow_Res");
h_low_Res = (TH1F*)h_low->Clone("h_low_Res");
h_medium_Res = (TH1F*)h_medium->Clone("h_medium_Res");
if (!Run1set) h_high_Res = (TH1F*)h_high->Clone("h_high_Res");

h_low_Res->Sumw2();
h_medium_Res->Sumw2();
if (!Run1set) h_high_Res->Sumw2();

h_low_Res->Divide(h_low_Res,h_lowlow_Res,1.0,1.0);
h_medium_Res->Divide(h_medium_Res,h_lowlow_Res,1.0,1.0);
if (!Run1set) h_high_Res->Divide(h_high_Res,h_lowlow_Res,1.0,1.0);


h_low_Res->SetMaximum(1.9);   // along          
h_low_Res->SetMinimum(0.1);  //   Y  
h_low_Res->GetYaxis()->SetLabelSize(0.11);//0.17 //0.08
h_low_Res->GetYaxis()->SetNdivisions(4,3,0); //4,5,0
h_low_Res->GetYaxis()->SetTitle("Ratio to Low Pileup");
h_low_Res->GetYaxis()->SetTitleSize(0.10);
h_low_Res->GetYaxis()->SetTitleOffset(0.38); //0.26
h_low_Res->GetXaxis()->SetTitleOffset(0.95); //0.95
h_low_Res->GetXaxis()->SetTitleSize(0.15);
h_low_Res->GetXaxis()->SetLabelSize(0.13); //0.17 0.1
if(DataType.EqualTo("data")){
// h_low_Res->SetRangeUser(0.1,1.9);
h_low_Res->Draw("e0p");
h_medium_Res->Draw("e0p same");
if (!Run1set) h_high_Res->Draw("e0p same");
}else if(DataType.EqualTo("mc")){
h_low_Res->Draw("hist e0");
h_medium_Res->Draw("hist e0 same");
if (!Run1set) h_high_Res->Draw("hist e0 same");
}

TString OutdirName = "/afs/cern.ch/user/a/agrummer/www/bmumu/IsoVarROCs/";
// TString Tag = "Tracks_2016";
// TString Tag = theYear;
TString Tag("");
if (DataType.EqualTo("data")) {
    if (theVar.EqualTo("nCloseTrks")) Tag = "CloseTrks_TTVA";
    else Tag =  "DOCA_TTVA";
}
else if (DataType.EqualTo("mc")) {
    if (theVar.EqualTo("nCloseTrks")) Tag = "CloseTrks_TTVA";
    else Tag = "DOCA_TTVA";
}
// Tag+="_2019Jun12_chi2_2";
// Tag+="_2019Jun13_chi2_2";
Tag+="_";
// Tag+=FileDate;
// Tag+="2019July30_";
Tag+="2019Aug13_";
TString varDir="";
if (theVar.EqualTo("nCloseTrks")){
    varDir = "NcloseTracks";
}else{
    varDir = "DOCA";
}
Tag+=DataType;
Tag+="_";
if (Run1set){
    Tag+="Run1";   
}else{ 
    Tag+=dummyVarName;
}
TString typeDir="";
if (DataType.EqualTo("data")){
    typeDir = "Data";
}else{
    typeDir = "MC";
}
// Tag+="_lowPU";
// Tag+=myPileup;
// Tag+="_medPU";
// Tag+="_highPU";
// c2->SaveAs(OutdirName + "Figures/VarComps/VarComp_"+Tag+".pdf");
// c2->SaveAs(OutdirName + "Figures/VarComps2019Jun27/VarComp_"+Tag+".pdf");
// c2->SaveAs(OutdirName + "Figures/VarComps2019July30_PU/VarComp_"+Tag+".pdf");
// c2->SaveAs(OutdirName + "Figures/VarComps2019Aug13_PU/"+varDir+"/"+typeDir+"/VarComp_"+Tag+".pdf");
//need to repeat without SetLimits (Sep 3):
// c2->SaveAs(OutdirName + "Figures/VarComps2019Sep3_PU/"+varDir+"/"+typeDir+"/VarComp_"+Tag+".pdf");
//look at doca overflow bin (Sep 4):
c2->SaveAs(OutdirName + "Figures/VarComps2019Sep5_PU_2018/"+varDir+"/"+typeDir+"/VarComp_"+Tag+".pdf");
delete c2;
delete h_lowlow;
delete h_low;
delete h_medium;
delete h_high;
return 0;
}

void OtherIso_MultiVar_TTVA_v6_PU() {
// ////TString FileDate = "2019Jun12"; //not good!! included chi2 PV cut
    TString FileDate = ""; 
    TString myPileup = "";
    // myPileup = "low";
    // myPileup = "medium";
    // myPileup = "high";
    // FileDate = "2019Jun6"; //NcloseTrks chi2SV <=1
// TString FileDate = "2019Jun17"; //NcloseTrks chi2SV <=2
// TString FileDate = "2019Jun17_2"; //NcloseTrks chi2SV <=4
    // makePlots("2016", "data", myVar, FileDate);
    // makePlots("2017", "data", myVar, FileDate);
    // makePlots("2018", "data", myVar, FileDate);
    // makePlots("2016", "mc", myVar, FileDate);
    // makePlots("2017", "mc", myVar, FileDate);
    // makePlots("2018", "mc", myVar, FileDate);
TString whichVar = "";
whichVar = "nCloseTrks";
// FileDate = "2019Jun27";
// FileDate = "2019July1";
FileDate = "2019July30";
    // makePlots("2016", "data", myVar, FileDate, myPileup);
    // makePlots("2017", "data", myVar, FileDate, myPileup);
    // makePlots("2018", "data", myVar, FileDate, myPileup);
    // makePlots("2016", "mc", myVar, FileDate, myPileup);
    // makePlots("2017", "mc", myVar, FileDate, myPileup);
    // makePlots("2018", "mc", myVar, FileDate, myPileup);
    // myPileup = "lowlow";
    // makePlots("2018", "data", myVar, FileDate, myPileup);
    // makePlots("2018", "mc", myVar, FileDate, myPileup);
    // myPileup = "low";
    // makePlots("2017", "data", myVar, FileDate, myPileup);
    // makePlots("2017", "mc", myVar, FileDate, myPileup);
    // myPileup = "medium";
    // makePlots("2017", "data", myVar, FileDate, myPileup);
    // makePlots("2017", "mc", myVar, FileDate, myPileup);
    // myPileup = "high";
    // makePlots("2017", "data", myVar, FileDate, myPileup);
    // makePlots("2017", "mc", myVar, FileDate, myPileup);
//commented sept 5
    bool Run1set = false;
    VariableInfo myVar;

    Run1set = true;
    myVar = closeTrkNtrks_80;
    makePlots("data", whichVar, FileDate, myVar, Run1set);
    makePlots("mc", whichVar, FileDate, myVar, Run1set);
    Run1set = false;

    myVar = closeTrkNtrks_80;
    makePlots("data", whichVar, FileDate, myVar, Run1set);
    makePlots("mc", whichVar, FileDate, myVar, Run1set);
    myVar = closeTrkNtrks_TTVA_custom_c1_80;
    makePlots("data", whichVar, FileDate, myVar, Run1set);
    makePlots("mc", whichVar, FileDate, myVar, Run1set);
    myVar = closeTrkNtrks_TTVA_custom_c2_80;
    makePlots("data", whichVar, FileDate, myVar, Run1set);
    makePlots("mc", whichVar, FileDate, myVar, Run1set);
    myVar = closeTrkNtrks_all_c1_80;
    makePlots("data", whichVar, FileDate, myVar, Run1set);
    makePlots("mc", whichVar, FileDate, myVar, Run1set);
    myVar = closeTrkNtrks_all_c2_80;
    makePlots("data", whichVar, FileDate, myVar, Run1set);
    makePlots("mc", whichVar, FileDate, myVar, Run1set);

whichVar = "DOCA";
// FileDate = "2019Jun27";
// FileDate = "2019July1";
FileDate = "2019July30";
    // makePlots("2016", "data", myVar, FileDate, myPileup);
    // makePlots("2017", "data", myVar, FileDate, myPileup);
    // makePlots("2018", "data", myVar, FileDate, myPileup);
    // makePlots("2016", "mc", myVar, FileDate, myPileup);
    // makePlots("2017", "mc", myVar, FileDate, myPileup);
    // makePlots("2018", "mc", myVar, FileDate, myPileup);
    // myPileup = "lowlow";
    // makePlots("2018", "data", myVar, FileDate, myPileup);
    // makePlots("2018", "mc", myVar, FileDate, myPileup);
    // myPileup = "low";
    // makePlots("2018", "data", myVar, FileDate, myPileup);
    // makePlots("2018", "mc", myVar, FileDate, myPileup);
    // makePlots("2017", "data", myVar, FileDate, myPileup);
    // makePlots("2017", "mc", myVar, FileDate, myPileup);
    // myPileup = "medium";
    // makePlots("2017", "data", myVar, FileDate, myPileup);
    // makePlots("2017", "mc", myVar, FileDate, myPileup);
    // myPileup = "high";
    // makePlots("2017", "data", myVar, FileDate, myPileup);
    // makePlots("2017", "mc", myVar, FileDate, myPileup);

    Run1set = true;
    myVar = closeTrkDOCA;
    makePlots("data", whichVar, FileDate, myVar, Run1set);
    makePlots("mc", whichVar, FileDate, myVar, Run1set);
    Run1set = false;

    myVar = closeTrkDOCA;
    makePlots("data", whichVar, FileDate, myVar, Run1set);
    makePlots("mc", whichVar, FileDate, myVar, Run1set);
    // commented Sept 5
    myVar = closeTrkDOCA_TTVA_custom_c7;
    makePlots("data", whichVar, FileDate, myVar, Run1set);
    makePlots("mc", whichVar, FileDate, myVar, Run1set);
    myVar = closeTrkDOCA_TTVA_custom_c2;
    makePlots("data", whichVar, FileDate, myVar, Run1set);
    makePlots("mc", whichVar, FileDate, myVar, Run1set);
    myVar = closeTrkDOCA_all_c7;
    makePlots("data", whichVar, FileDate, myVar, Run1set);
    makePlots("mc", whichVar, FileDate, myVar, Run1set);
    myVar = closeTrkDOCA_all_c2;
    makePlots("data", whichVar, FileDate, myVar, Run1set);
    makePlots("mc", whichVar, FileDate, myVar, Run1set);


}

