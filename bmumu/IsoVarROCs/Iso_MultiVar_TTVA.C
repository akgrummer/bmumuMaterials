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
                    TString FileDate=""){
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
        cout<< "ifilename "<< ifilename<<endl;
        // ifilename = DirName + tmpYear+"All/LASTskim_"+tmpYear+"_All_2019Jun12.root";
    }
    else{
        // ifilename = DirName + tmpYear+"All/LASTskim_"+tmpYear+"_All_2019Jun3.root";
        ifilename = DirName + tmpYear+"All/LASTskim_"+tmpYear+"_All_"+FileDate+".root";
        cout<< "ifilename "<< ifilename<<endl;
        // ifilename = DirName + tmpYear+"All/LASTskim_"+tmpYear+"_All_2019Jun12.root";
    }
        myCut = CutAdd;
    }
else if (DataType.EqualTo("mc")) { 
    if (tmpYear.EqualTo("2016")){
        // ifilename = DirName + tmp_mcName+"All/LASTskim_"+tmp_mcName+"_All_2019Jun5.root";
        ifilename = DirName + tmp_mcName+"All/LASTskim_"+tmp_mcName+"_All_"+FileDate+".root";
        cout<< "ifilename "<< ifilename<<endl;
        // ifilename = DirName + tmp_mcName+"All/LASTskim_"+tmp_mcName+"_All_2019Jun12.root";
    }else{
        // ifilename = DirName + tmp_mcName+"All/LASTskim_"+tmp_mcName+"_All_2019Jun3.root";
        ifilename = DirName + tmp_mcName+"All/LASTskim_"+tmp_mcName+"_All_"+FileDate+".root";
        cout<< "ifilename "<< ifilename<<endl;
        // ifilename = DirName + tmp_mcName+"All/LASTskim_"+tmp_mcName+"_All_2019Jun12.root";
    }
        // myCut= CutAdd*RunNumberCut*"PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
        myCut= CutAdd*RunNumberCut;
    }
    

TFile* ifile = new TFile(ifilename);
TTree *myTree = (TTree*)ifile->Get("T_mv");
cout<<tmpYear <<" Tree Entries: "<<myTree->GetEntries()<<endl;
myHist = getHistoFromTree(myTree, myVar, myVar.name, myCut);

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
                TString FileDate = ""){
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
Int_t ColorIndex = 0;
TH1F* h2016data_Default = RetrieveHist(theYear, DataType, Bisolation, ColorIndex, FileDate);
ColorIndex = 1;
TH1F* h2016data_TTVA_loose = RetrieveHist(theYear, DataType, iso_TTVA_loose, ColorIndex, FileDate);
ColorIndex = 2;
TH1F* h2016data_TTVA_nominal = RetrieveHist(theYear, DataType, iso_TTVA_nominal, ColorIndex, FileDate);
ColorIndex = 3;
TH1F* h2016data_TTVA_tight = RetrieveHist(theYear, DataType, iso_TTVA_tight, ColorIndex, FileDate);
ColorIndex = 4;
TH1F* h2016data_Chi6 = RetrieveHist(theYear, DataType, iso_AllTrks_Chi6, ColorIndex, FileDate);
ColorIndex = 5;
TH1F* h2016data_Chi5 = RetrieveHist(theYear, DataType, iso_AllTrks_Chi5, ColorIndex, FileDate);
ColorIndex = 6;
TH1F* h2016data_Chi4 = RetrieveHist(theYear, DataType, iso_AllTrks_Chi4, ColorIndex, FileDate);

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
        h2016data_Chi6->Draw("e0psame");
        h2016data_Chi5->Draw("e0psame");
        h2016data_Chi4->Draw("e0psame");
    }
    else if(DataType.EqualTo("mc")){
        h2016data_Default->SetMaximum(5.);
        h2016data_Default->Draw("hist e0");
        h2016data_TTVA_loose->Draw("hist e0 same");
        h2016data_TTVA_nominal->Draw("hist e0 same");
        h2016data_TTVA_tight->Draw("hist e0 same");
        h2016data_Chi6->Draw("hist e0 same");
        h2016data_Chi5->Draw("hist e0 same");
        h2016data_Chi4->Draw("hist e0 same");
    }


TLegend* leg2(NULL);
// leg2 = new TLegend(1, 0.06, 5, 0.08,NULL,"brNDC");
// leg2 = new TLegend(0.218045, 0.721739, 0.418546, 0.770435,NULL,"brNDC");

// leg2 = new TLegend(0.218045, 0.2, 0.418546, 0.4,NULL,"brNDC");
TString theIDHits="";
if (FileDate.EqualTo("2019May30")){
    theIDHits = " ID Hits like Run 1";
}
if (FileDate.EqualTo("2019Jun6")){
    theIDHits = " ID Hits with IBL";
}
if (FileDate.EqualTo("2019Jun12")){
    theIDHits = " ID Hits with IBL + #chi^{2}<6";
}
if (FileDate.EqualTo("2019Jun17")){
    theIDHits = " isTightPrimary";
}
if (FileDate.EqualTo("2019Jun17_2")){
    theIDHits = " isTightPrimary + #chi^{2}<6";
}
if (DataType.EqualTo("data")) {
    atlasLabel(0.4, 0.47, false, true, 1, true, false, true);
    leg2 = new TLegend(0.42, 0.2, 0.62, 0.43,NULL,"brNDC");
    leg2->SetHeader(theYear + theRunNumber+theIDHits);
}
else if (DataType.EqualTo("mc")) {
    atlasLabel(0.5, 0.83, false, true, 1, true, false, true);
    leg2 = new TLegend(0.22, 0.67, 0.42, 0.9,NULL,"brNDC");
    leg2->SetHeader(mcName + theRunNumber+theIDHits);
}
// leg2->SetHeader(mcName);
if(DataType.EqualTo("data")){
leg2->AddEntry(h2016data_Default, "Default","pe");
leg2->AddEntry(h2016data_TTVA_loose, "TTVA Loose WP","pe");
leg2->AddEntry(h2016data_TTVA_nominal, "TTVA Nominal WP","pe");
leg2->AddEntry(h2016data_TTVA_tight, "TTVA Tight WP","pe");
leg2->AddEntry(h2016data_Chi6, "All Tracks #chi^{2}<6","pe");
leg2->AddEntry(h2016data_Chi5, "All Tracks #chi^{2}<5","pe");
leg2->AddEntry(h2016data_Chi4, "All Tracks #chi^{2}<4","pe");
}else if(DataType.EqualTo("mc")){
leg2->AddEntry(h2016data_Default, "Default","l");
leg2->AddEntry(h2016data_TTVA_loose, "TTVA Loose WP","l");
leg2->AddEntry(h2016data_TTVA_nominal, "TTVA Nominal WP","l");
leg2->AddEntry(h2016data_TTVA_tight, "TTVA Tight WP","l");
leg2->AddEntry(h2016data_Chi6, "All Tracks #chi^{2}<6","l");
leg2->AddEntry(h2016data_Chi5, "All Tracks #chi^{2}<5","l");
leg2->AddEntry(h2016data_Chi4, "All Tracks #chi^{2}<4","l");
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
Tag = theYear + "TTVA_chi2";
}
else if (DataType.EqualTo("mc")) {
// Tag = mcName + "TTVA_chi2_2019Jun6";
Tag = mcName + "TTVA_chi2";
}
// Tag+="_2019Jun12_chi2_6"
// Tag+="_2019Jun13_chi2_6"
Tag+="_";
// Tag+="_2019Jun17";
Tag+=FileDate;
// c2->SaveAs(OutdirName + "Figures/VarComps/VarComp_"+Tag+".pdf");
c2->SaveAs(OutdirName + "Figures/VarComps2019Jun17/"+FileDate+"/VarComp_"+Tag+".pdf");

return 0;
}

void Iso_MultiVar_TTVA(){
    TString FileDate = ""; //no ID hits
    // TString FileDate = "2019Jun3"; //no ID hits
    // TString FileDate = "2019Jun5"; //no ID hits for 2016
    // TString FileDate = "2019May30"; //ID hits like run 1 without IBL included //bad triggers 2016+MC16a
    // TString FileDate = "2019Jun6"; //ID hits revised run 1 with IBL included
// TString FileDate = "2019Jun12"; //ID hits revised run 1 with IBL included and chi2<6
// TString FileDate = "2019Jun17"; //ID hits isTightPrimary
// TString FileDate = "2019Jun17_2"; //ID hits isTightPrimary and chi2<6
    // makePlots("2016", "data", FileDate);
    // makePlots("2017", "data", FileDate);
    // makePlots("2018", "data", FileDate);
    // makePlots("2016", "mc", FileDate);
    // makePlots("2017", "mc", FileDate);
    // makePlots("2018", "mc", FileDate);

// FileDate = "2019May30";
//     makePlots("2016", "data", FileDate);
//     makePlots("2017", "data", FileDate);
//     makePlots("2018", "data", FileDate);
//     makePlots("2016", "mc", FileDate);
//     makePlots("2017", "mc", FileDate);
//     makePlots("2018", "mc", FileDate);
FileDate = "2019Jun5";
    makePlots("2016", "data", FileDate);
    makePlots("2016", "mc", FileDate);
FileDate = "2019Jun3";
    makePlots("2017", "data", FileDate);
    makePlots("2018", "data", FileDate);
    makePlots("2017", "mc", FileDate);
    makePlots("2018", "mc", FileDate);
FileDate = "2019Jun6";
    makePlots("2016", "data", FileDate);
    makePlots("2017", "data", FileDate);
    makePlots("2018", "data", FileDate);
    makePlots("2016", "mc", FileDate);
    makePlots("2017", "mc", FileDate);
    makePlots("2018", "mc", FileDate);
FileDate = "2019Jun12";
    makePlots("2016", "data", FileDate);
    makePlots("2017", "data", FileDate);
    makePlots("2018", "data", FileDate);
    makePlots("2016", "mc", FileDate);
    makePlots("2017", "mc", FileDate);
    makePlots("2018", "mc", FileDate);
FileDate = "2019Jun17";
    makePlots("2016", "data", FileDate);
    makePlots("2017", "data", FileDate);
    makePlots("2018", "data", FileDate);
    makePlots("2016", "mc", FileDate);
    makePlots("2017", "mc", FileDate);
    makePlots("2018", "mc", FileDate);
FileDate = "2019Jun17_2";
    makePlots("2016", "data", FileDate);
    makePlots("2017", "data", FileDate);
    makePlots("2018", "data", FileDate);
    makePlots("2016", "mc", FileDate);
    makePlots("2017", "mc", FileDate);
    makePlots("2018", "mc", FileDate);

}

