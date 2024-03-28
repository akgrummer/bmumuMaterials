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
                    TString FileDate = "") {
TString DirName = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/";
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
myHist->Scale(1./myHist->Integral(0, myVar.nbins + 1));
myHist->GetYaxis()->SetTitle("a.u.");
return myHist;
}

void makePlots(TString theYear="", TString DataType ="", 
                TString theVar="", TString FileDate = ""){
    SetAtlasStyle();

///////////////////
// TString theYear="2018";
// TString DataType = "data";
// TString DataType = "mc";
TString theRunNumber("");
TString mcName("");
if (theYear.EqualTo("2016")){
    theRunNumber = " Run 302393";
    mcName = "MC16a";
}
else if (theYear.EqualTo("2017")){
    theRunNumber = " Run 339849";
    mcName = "MC16d";
}
else if (theYear.EqualTo("2018")){
    theRunNumber = " Run 358096";
    mcName = "MC16e";
}
//
TH1F* h2016data_Default(NULL);
TH1F* h2016data_TTVA_loose(NULL);
TH1F* h2016data_TTVA_nominal(NULL);
TH1F* h2016data_TTVA_tight(NULL);
Int_t ColorIndex = 0;
if (theVar.EqualTo("nCloseTrks")){
h2016data_Default = RetrieveHist(theYear, DataType, closeTrkNtrks, ColorIndex, FileDate);
ColorIndex = 1;
h2016data_TTVA_loose = RetrieveHist(theYear, DataType, var_closeTrkNtrks_TTVA_loose, ColorIndex, FileDate);
ColorIndex = 2;
h2016data_TTVA_nominal = RetrieveHist(theYear, DataType, var_closeTrkNtrks_TTVA_nominal, ColorIndex, FileDate);
ColorIndex = 3;
h2016data_TTVA_tight = RetrieveHist(theYear, DataType, var_closeTrkNtrks_TTVA_tight, ColorIndex, FileDate);
}//
// Int_t ColorIndex = 0;
else{
h2016data_Default = RetrieveHist(theYear, DataType, closeTrkDOCA, ColorIndex, FileDate);
ColorIndex = 1;
h2016data_TTVA_loose = RetrieveHist(theYear, DataType, var_closeTrkDOCA_TTVA_loose, ColorIndex, FileDate);
ColorIndex = 2;
h2016data_TTVA_nominal = RetrieveHist(theYear, DataType, var_closeTrkDOCA_TTVA_nominal, ColorIndex, FileDate);
ColorIndex = 3;
h2016data_TTVA_tight = RetrieveHist(theYear, DataType, var_closeTrkDOCA_TTVA_tight, ColorIndex, FileDate);
}
//
// ColorIndex = 4;
// TH1F* h2016data_Chi6 = RetrieveHist(theYear, DataType, iso_AllTrks_Chi6, ColorIndex);
// ColorIndex = 5;
// TH1F* h2016data_Chi5 = RetrieveHist(theYear, DataType, iso_AllTrks_Chi5, ColorIndex);
// ColorIndex = 6;
// TH1F* h2016data_Chi4 = RetrieveHist(theYear, DataType, iso_AllTrks_Chi4, ColorIndex);

TCanvas* c2 = new TCanvas("c2", "Var Comps",0.,0., 800, 600);
    TPad *pad1, *pad2;
    pad1 = new TPad("pad1","pad1",0,0,1,1); //xlow ylow xup yup
    // pad2 = new TPad("pad2","pad2",0,0,0,0); //0.3
    pad1->SetLogy();
    pad1->SetMargin(0.16,0.05,0.16,0.09);
    pad1->Draw();
    pad1->cd();
    if(DataType.EqualTo("data")){
        // h2016data->Draw("e0psame");
        h2016data_Default->Draw("e0p");
        h2016data_TTVA_loose->Draw("e0psame");
        h2016data_TTVA_nominal->Draw("e0psame");
        h2016data_TTVA_tight->Draw("e0psame");
        // h2016data_Chi6->Draw("e0psame");
        // h2016data_Chi5->Draw("e0psame");
        // h2016data_Chi4->Draw("e0psame");
    }
    else if(DataType.EqualTo("mc")){
        h2016data_Default->Draw("hist e0");
        h2016data_TTVA_loose->Draw("hist e0 same");
        h2016data_TTVA_nominal->Draw("hist e0 same");
        h2016data_TTVA_tight->Draw("hist e0 same");
        // h2016data_Chi6->Draw("hist e0 same");
        // h2016data_Chi5->Draw("hist e0 same");
        // h2016data_Chi4->Draw("hist e0 same");
    }


TLegend* leg2(NULL);
// leg2 = new TLegend(1, 0.06, 5, 0.08,NULL,"brNDC");
// leg2 = new TLegend(0.218045, 0.721739, 0.418546, 0.770435,NULL,"brNDC");
TString theTracks="";
if (FileDate.EqualTo("2019Jun6")){
    theTracks = " #chi^{2}_{SV}<=1";
}
if (FileDate.EqualTo("2019Jun17")){
    theTracks = " #chi^{2}_{SV}<=1";
}
if (FileDate.EqualTo("2019Jun17_2")) {
    theTracks = " #chi^{2}_{SV}<=1";
}
// leg2 = new TLegend(0.218045, 0.2, 0.418546, 0.4,NULL,"brNDC");
if (DataType.EqualTo("data")) {
    atlasLabel(0.62, 0.8, false, true, 1, true, false, true);
    leg2 = new TLegend(0.63, 0.65, 0.83, 0.77,NULL,"brNDC");
    leg2->SetHeader(theYear + theRunNumber+theTracks);
}
else if (DataType.EqualTo("mc")) {
    atlasLabel(0.62, 0.8, false, true, 1, true, false, true);
    // atlasLabel(0.2, 0.83, false, true, 1, true, false, true);
    leg2 = new TLegend(0.63, 0.65, 0.83, 0.77,NULL,"brNDC");
    // leg2 = new TLegend(0.22, 0.57, 0.42, 0.8,NULL,"brNDC");
    leg2->SetHeader(mcName + theRunNumber+theTracks);
}
// leg2->SetHeader(mcName);
if(DataType.EqualTo("data")){
leg2->AddEntry(h2016data_Default, "Default","pe");
leg2->AddEntry(h2016data_TTVA_loose, "TTVA Loose WP","pe");
leg2->AddEntry(h2016data_TTVA_nominal, "TTVA Nominal WP","pe");
leg2->AddEntry(h2016data_TTVA_tight, "TTVA Tight WP","pe");
// leg2->AddEntry(h2016data_Chi6, "All Tracks #chi^{2}<6","pe");
// leg2->AddEntry(h2016data_Chi5, "All Tracks #chi^{2}<5","pe");
// leg2->AddEntry(h2016data_Chi4, "All Tracks #chi^{2}<4","pe");
}else if(DataType.EqualTo("mc")){
leg2->AddEntry(h2016data_Default, "Default","l");
leg2->AddEntry(h2016data_TTVA_loose, "TTVA Loose WP","l");
leg2->AddEntry(h2016data_TTVA_nominal, "TTVA Nominal WP","l");
leg2->AddEntry(h2016data_TTVA_tight, "TTVA Tight WP","l");
// leg2->AddEntry(h2016data_Chi6, "All Tracks #chi^{2}<6","l");
// leg2->AddEntry(h2016data_Chi5, "All Tracks #chi^{2}<5","l");
// leg2->AddEntry(h2016data_Chi4, "All Tracks #chi^{2}<4","l");
    }

leg2->SetBorderSize(0);  // no border
leg2->SetLineColor(0);
leg2->SetFillColor(0);
leg2->SetTextSize(0.025);
leg2->Draw();

TString OutdirName = "/afs/cern.ch/user/a/agrummer/www/bmumu/IsoVarROCs/";
// TString Tag = "Tracks_2016";
// TString Tag = theYear;
TString Tag("");
if (DataType.EqualTo("data")) {
    if (theVar.EqualTo("nCloseTrks")) Tag = theYear + "CloseTrks_TTVA";
    else Tag = theYear + "DOCA_TTVA";
}
else if (DataType.EqualTo("mc")) {
    if (theVar.EqualTo("nCloseTrks")) Tag = mcName + "CloseTrks_TTVA";
    else Tag = mcName + "DOCA_TTVA";
}
// Tag+="_2019Jun12_chi2_2";
// Tag+="_2019Jun13_chi2_2";
Tag+="_";
Tag+=FileDate;
// c2->SaveAs(OutdirName + "Figures/VarComps/VarComp_"+Tag+".pdf");
c2->SaveAs(OutdirName + "Figures/VarComps2019Jun17/"+FileDate+"/VarComp_"+Tag+".pdf");
delete c2;
delete h2016data_Default;
delete h2016data_TTVA_loose;
delete h2016data_TTVA_nominal;
delete h2016data_TTVA_tight;
return 0;
}

void OtherIso_MultiVar_TTVA() {
// ////TString FileDate = "2019Jun12"; //not good!! included chi2 PV cut
    TString FileDate = ""; 
    // FileDate = "2019Jun6"; //NcloseTrks chi2SV <=1
// TString FileDate = "2019Jun17"; //NcloseTrks chi2SV <=2
// TString FileDate = "2019Jun17_2"; //NcloseTrks chi2SV <=4
    // makePlots("2016", "data", myVar, FileDate);
    // makePlots("2017", "data", myVar, FileDate);
    // makePlots("2018", "data", myVar, FileDate);
    // makePlots("2016", "mc", myVar, FileDate);
    // makePlots("2017", "mc", myVar, FileDate);
    // makePlots("2018", "mc", myVar, FileDate);
TString myVar = "nCloseTrks";
FileDate = "2019Jun6";
    makePlots("2016", "data", myVar, FileDate);
    makePlots("2017", "data", myVar, FileDate);
    makePlots("2018", "data", myVar, FileDate);
    makePlots("2016", "mc", myVar, FileDate);
    makePlots("2017", "mc", myVar, FileDate);
    makePlots("2018", "mc", myVar, FileDate);
FileDate = "2019Jun17";
    makePlots("2016", "data", myVar, FileDate);
    makePlots("2017", "data", myVar, FileDate);
    makePlots("2018", "data", myVar, FileDate);
    makePlots("2016", "mc", myVar, FileDate);
    makePlots("2017", "mc", myVar, FileDate);
    makePlots("2018", "mc", myVar, FileDate);
FileDate = "2019Jun17_2";
    makePlots("2016", "data", myVar, FileDate);
    makePlots("2017", "data", myVar, FileDate);
    makePlots("2018", "data", myVar, FileDate);
    makePlots("2016", "mc", myVar, FileDate);
    makePlots("2017", "mc", myVar, FileDate);
    makePlots("2018", "mc", myVar, FileDate);
myVar = "DOCA";
FileDate = "2019Jun6";
    makePlots("2016", "data", myVar, FileDate);
    makePlots("2017", "data", myVar, FileDate);
    makePlots("2018", "data", myVar, FileDate);
    makePlots("2016", "mc", myVar, FileDate);
    makePlots("2017", "mc", myVar, FileDate);
    makePlots("2018", "mc", myVar, FileDate);
FileDate = "2019Jun17";
    makePlots("2016", "data", myVar, FileDate);
    makePlots("2017", "data", myVar, FileDate);
    makePlots("2018", "data", myVar, FileDate);
    makePlots("2016", "mc", myVar, FileDate);
    makePlots("2017", "mc", myVar, FileDate);
    makePlots("2018", "mc", myVar, FileDate);
FileDate = "2019Jun17_2";
    makePlots("2016", "data", myVar, FileDate);
    makePlots("2017", "data", myVar, FileDate);
    makePlots("2018", "data", myVar, FileDate);
    makePlots("2016", "mc", myVar, FileDate);
    makePlots("2017", "mc", myVar, FileDate);
    makePlots("2018", "mc", myVar, FileDate);
}

