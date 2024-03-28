#include<TMath.h>
#include "/afs/cern.ch/user/a/agrummer/www/bmumu/AnalysisTools/Utils/AtlasStyle/AtlasLabels.C"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu/AnalysisTools/Utils/AtlasStyle/AtlasLabels.h"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu/AnalysisTools/Utils/AtlasStyle/AtlasUtils.C"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu/AnalysisTools/Utils/AtlasStyle/AtlasUtils.h"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu/AnalysisTools/Utils/AtlasStyle/AtlasStyle.C"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu/AnalysisTools/Utils/AtlasStyle/AtlasStyle.h"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu/IsoVarROCs/v8IsoScripts/Iso_MultiROCs.h"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu/IsoVarROCs/v8IsoScripts/getHistoFromTree.C"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu/IsoVarROCs/atlasLabel.C"
// #include "Iso_ROCs_Module.C"

TH1F* RetrieveHist(TString tmpYear = "",  TString DataType = "", 
                    VariableInfo myVar = Bisolation, Int_t ColorIndex=0,
                    TString FileDate = "", TString Pileup= "") {
// TString DirName = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/";
// TString DirName = "/eos/home-a/agrummer/BsmumuData/FinalSkim/v5/";
TString DirName = "/eos/home-a/agrummer/BsmumuData/FinalSkim/v6/";
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
}if (Pileup.EqualTo("low")) {
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
                    VariableInfo myVar = Bisolation, Int_t ColorIndex=0, TString Pileup= "") {
TString ifilename("");
TString tmp_mcName("");
TString runName("");
TCut myCut("");
TString tmpYear("Run1");
TCut RunNumberCut("");
TH1F* myHist(NULL);

if (DataType.EqualTo("data")) {
        ifilename = "/eos/home-a/agrummer/BsmumuData/Run1/Data/data12_8TeVBsAllPeriodsUnblinded_doca3.root";

        myCut = CutRun1;
    }
else if (DataType.EqualTo("mc")) { 
        ifilename = "/eos/home-a/agrummer/BsmumuData/Run1/MC/mc12_8TeV.208426.Pythia8B_AU2_CTEQ6L1_Bs_mu3p5mu3p5.r3549.172133.staco.Bs2mumu_Bs.v12.s1.wTRUTHvarsANDnoMCPcuts_doca3.root";

        myCut= CutRun1*"PVWeights";
    }

if (Pileup.EqualTo("lowlow")) {
myCut = myCut*("PRIVX_mu >= 12. && PRIVX_mu <= 22.");
}if (Pileup.EqualTo("low")) {
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

void makePlots(TString theYear="", TString DataType ="", 
                TString theVar="", TString FileDate = "", TString myPileup= ""){
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
TH1F* hdata_TTVA_loose(NULL);
TH1F* hdata_TTVA_custom(NULL);
// TH1F* h2016data_all_c1(NULL);
// TH1F* h2016data_all_c2(NULL);
TH1F* hRun1(NULL);
Int_t ColorIndex = 0;
//
// closeTrkNtrks_TTVA_custom_c1
// closeTrkNtrks_TTVA_custom_c2
// closeTrkNtrks_all_c1
// closeTrkNtrks_all_c2

if (theVar.EqualTo("nCloseTrks")){
    //the 80 is to ensure proper nomalization of the histograms in nClose tracks (80 bins instead of the original 60)
ColorIndex = 3;
hRun1 = RetrieveHistRun1(DataType, closeTrkNtrks_80, ColorIndex, myPileup);
ColorIndex = 0;
h2016data_Default = RetrieveHist(theYear, DataType, closeTrkNtrks_80, ColorIndex, FileDate, myPileup);
ColorIndex = 1;
hdata_TTVA_loose = RetrieveHist(theYear, DataType, closeTrkNtrks_TTVA_loose_c2_80, ColorIndex, FileDate, myPileup);
ColorIndex = 2;
hdata_TTVA_custom = RetrieveHist(theYear, DataType, closeTrkNtrks_TTVA_custom_c2_80, ColorIndex, FileDate, myPileup);
// ColorIndex = 4;
// h2016data_all_c1 = RetrieveHist(theYear, DataType, closeTrkNtrks_all_c1_80, ColorIndex, FileDate, myPileup);
// ColorIndex = 5;
// h2016data_all_c2 = RetrieveHist(theYear, DataType, closeTrkNtrks_all_c2_80, ColorIndex, FileDate, myPileup);
}//
// Int_t ColorIndex = 0;
//
// closeTrkDOCA_TTVA_custom_c7
// closeTrkDOCA_TTVA_custom_c2
// closeTrkDOCA_all_c7
// closeTrkDOCA_all_c2
else{
ColorIndex = 3;
hRun1 = RetrieveHistRun1(DataType, closeTrkDOCA_3, ColorIndex, myPileup);
ColorIndex = 0;
h2016data_Default = RetrieveHist(theYear, DataType, closeTrkDOCA_comp, ColorIndex, FileDate, myPileup);
ColorIndex = 1;
hdata_TTVA_loose = RetrieveHist(theYear, DataType, closeTrkDOCA_TTVA_loose_c7, ColorIndex, FileDate, myPileup);
ColorIndex = 2;
hdata_TTVA_custom = RetrieveHist(theYear, DataType, closeTrkDOCA_TTVA_custom_c7, ColorIndex, FileDate, myPileup);
// ColorIndex = 4;
// h2016data_all_c1 = RetrieveHist(theYear, DataType, closeTrkDOCA_all_c7, ColorIndex, FileDate, myPileup);
// ColorIndex = 5;
// h2016data_all_c2 = RetrieveHist(theYear, DataType, closeTrkDOCA_all_c2, ColorIndex, FileDate, myPileup);
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
    Double_t ymin;
    Double_t ymax;
    Double_t xmin;
    Double_t xmax;
    if(DataType.EqualTo("data")){
        // h2016data->Draw("e0psame");
        if(theVar.EqualTo("DOCA")){
            ymin = 1e-5;
            ymax = 5e0;
            xmin = 0;
            xmax = 3.2;
        }else{
            ymin = 1e-4;
            ymax = 5e-1;
            xmin = 0;
            xmax = 60;
        }
        //don't use SetLimits for Histograms!!
            // h2016data_Default->GetXaxis()->SetLimits(xmin, xmax);// along X
            h2016data_Default->GetXaxis()->SetRangeUser(xmin, xmax);// along X
            h2016data_Default->SetMaximum(ymax);   // along          
            h2016data_Default->SetMinimum(ymin);  //   Y  
        h2016data_Default->Draw("e0p");
        hdata_TTVA_loose->Draw("e0psame");
        hdata_TTVA_custom->Draw("e0psame");
        // h2016data_all_c1->Draw("e0psame");
        // h2016data_all_c2->Draw("e0psame");
        if (!myPileup.EqualTo("high")){hRun1->Draw("e0psame");}
        // h2016data_Chi6->Draw("e0psame");
        // h2016data_Chi5->Draw("e0psame");
        // h2016data_Chi4->Draw("e0psame");
    }
    else if(DataType.EqualTo("mc")){
        if(theVar.EqualTo("DOCA")){
            ymin = 1e-5;
            ymax = 1e1;
            xmin = 0;
            xmax = 3.2;
        }
        else{
            ymin = 1e-5;
            ymax = 1e1;
            xmin = 0;
            xmax = 60;
        }
        //don't use setLimits for histograms!
            // h2016data_Default->GetXaxis()->SetLimits(xmin, xmax);// along X
            h2016data_Default->GetXaxis()->SetRangeUser(xmin, xmax);// along X
            h2016data_Default->SetMaximum(ymax);   // along          
            h2016data_Default->SetMinimum(ymin);  //   Y  
        h2016data_Default->Draw("hist e0");
        hdata_TTVA_loose->Draw("hist e0 same");
        hdata_TTVA_custom->Draw("hist e0 same");
        // h2016data_all_c2->Draw("hist e0 same");
        if (!myPileup.EqualTo("high")){hRun1->Draw("hist e0 same");}
        // h2016data_all_c1->Draw("hist e0 same");
        // h2016data_Chi6->Draw("hist e0 same");
        // h2016data_Chi5->Draw("hist e0 same");
        // h2016data_Chi4->Draw("hist e0 same");
    }


TLegend* leg2(NULL);
// leg2 = new TLegend(1, 0.06, 5, 0.08,NULL,"brNDC");
// leg2 = new TLegend(0.218045, 0.721739, 0.418546, 0.770435,NULL,"brNDC");
TString theTracks="";

TString PileupHeader;
if (myPileup.EqualTo("lowlow")) {
    PileupHeader = ", 12. #leq PRIVX_mu #leq 22.";
}if (myPileup.EqualTo("low")) {
    PileupHeader = ", 23. #leq PRIVX_mu #leq 33.";
}else if(myPileup.EqualTo("medium")) {
    PileupHeader = ", 34. #leq PRIVX_mu #leq 44.";
}else if(myPileup.EqualTo("high")) {
    PileupHeader = ", 45. #leq PRIVX_mu #leq 55.";
}

// leg2 = new TLegend(0.218045, 0.2, 0.418546, 0.4,NULL,"brNDC");
if (DataType.EqualTo("data")) {
    atlasLabel(0.62, 0.8, false, true, 1, true, false, true);
    if (theVar.EqualTo("nCloseTrks")){
        leg2 = new TLegend(0.23, 0.2, 0.43, 0.45,NULL,"brNDC");
        }
    else{
        leg2 = new TLegend(0.61, 0.55, 0.81, 0.8,NULL,"brNDC");
        }
    leg2->SetHeader(theYear + theRunNumber + PileupHeader);
}
else if (DataType.EqualTo("mc")) {
    atlasLabel(0.62, 0.85, false, true, 1, true, false, true);
    // atlasLabel(0.2, 0.83, false, true, 1, true, false, true);
    leg2 = new TLegend(0.61, 0.6, 0.81, 0.85,NULL,"brNDC");
    // leg2 = new TLegend(0.22, 0.57, 0.42, 0.8,NULL,"brNDC");
    leg2->SetHeader(mcName + theRunNumber + PileupHeader);
}
// leg2->SetHeader(mcName);
if(DataType.EqualTo("data")){
    if (!myPileup.EqualTo("high")){leg2->AddEntry(hRun1, "Run 1","pe");}
    leg2->AddEntry(h2016data_Default, "Default","pe");
    if (theVar.EqualTo("DOCA")){
        leg2->AddEntry(hdata_TTVA_loose, "Loose TTVA WP and #chi^{2}_{SV} #leq 7","pe");
        leg2->AddEntry(hdata_TTVA_custom, "Custom TTVA WP and #chi^{2}_{SV} #leq 7","pe");
    }else{
        leg2->AddEntry(hdata_TTVA_loose, "Loose TTVA WP and #chi^{2}_{SV} #leq 2","pe");
        leg2->AddEntry(hdata_TTVA_custom, "Custom TTVA WP and #chi^{2}_{SV} #leq 2","pe");
    }
    // if (theVar.EqualTo("DOCA")){
    //     leg2->AddEntry(h2016data_all_c1, "All Tracks and #chi^{2}_{SV} #leq 7","pe");
    // }else{
    //     leg2->AddEntry(h2016data_all_c1, "All Tracks and #chi^{2}_{SV} #leq 1","pe");
    // }
    // leg2->AddEntry(h2016data_all_c2, "All Tracks and #chi^{2}_{SV} #leq 2","pe");
}else if(DataType.EqualTo("mc")){
    if (!myPileup.EqualTo("high")){leg2->AddEntry(hRun1, "Run 1","l");}
    leg2->AddEntry(h2016data_Default, "Default","l");
    if (theVar.EqualTo("DOCA")){
        leg2->AddEntry(hdata_TTVA_loose, "Loose TTVA WP and #chi^{2}_{SV} #leq 7","l");
        leg2->AddEntry(hdata_TTVA_custom, "Custom TTVA WP and #chi^{2}_{SV} #leq 7","l");
    }else{
        leg2->AddEntry(hdata_TTVA_loose, "Loose TTVA WP and #chi^{2}_{SV} #leq 2","l");
        leg2->AddEntry(hdata_TTVA_custom, "Custom TTVA WP and #chi^{2}_{SV} #leq 2","l");
    }
    // if (theVar.EqualTo("DOCA")){
    //     leg2->AddEntry(h2016data_all_c1, "All Tracks and #chi^{2}_{SV} #leq 7","l");
    // }else{
    //     leg2->AddEntry(h2016data_all_c1, "All Tracks and #chi^{2}_{SV} #leq 1","l");
    // }
    // leg2->AddEntry(h2016data_all_c2, "All Tracks and #chi^{2}_{SV} #leq 2","l");
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
Tag+="_";
// Tag+="2019July30_";
// Tag+="_lowPU";
// Tag+=myPileup;
TString varDir="";
if (theVar.EqualTo("nCloseTrks")){
    varDir = "NcloseTracks";
}else{
    varDir = "DOCA";
}
Tag+=DataType;
Tag+="_";
Tag+=myPileup;
// if (Run1set){
//     Tag+="Run1";   
// }else{ 
//     Tag+=dummyVarName;
// }
TString typeDir="";
if (DataType.EqualTo("data")){
    typeDir = "Data";
}else{
    typeDir = "MC";
}
// Tag+="_medPU";
// Tag+="_highPU";
// c2->SaveAs(OutdirName + "Figures/VarComps/VarComp_"+Tag+".pdf");
// c2->SaveAs(OutdirName + "Figures/VarComps2019Jun27/VarComp_"+Tag+".pdf");
// c2->SaveAs(OutdirName + "Figures/VarComps2019July30_PU/VarComp_"+Tag+".pdf");
//need to repeat without SetLimits:
// c2->SaveAs(OutdirName + "Figures/VarComps2019Sep3_VarBinned/"+varDir+"/"+typeDir+"/VarComp_"+Tag+".pdf");
// c2->SaveAs(OutdirName + "Figures/VarComps2019Sep5_VarBinned/"+varDir+"/"+typeDir+"/VarComp_"+Tag+".pdf");
// c2->SaveAs(OutdirName + "Figures/VarComps2019Nov21_VarBinned_v7/"+varDir+"/"+typeDir+"/VarComp_"+Tag+".pdf");
c2->SaveAs(OutdirName + "Figures/VarComps2020Mar24_VarBinned_v7_repeat/"+varDir+"/"+typeDir+"/VarComp_"+Tag+".pdf");
delete c2;
delete h2016data_Default;
delete hdata_TTVA_loose;
delete hdata_TTVA_custom;
// delete h2016data_all_c1;
// delete h2016data_all_c2;
delete hRun1;
return 0;
}

void OtherIso_MultiVar_TTVA_v7_PU_2() {
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
TString myVar = "";
myVar = "nCloseTrks";
// FileDate = "2019Jun27";
// FileDate = "2019July1";
// FileDate = "2019July30";
// FileDate = "2019Nov21";
FileDate = "2019Dec5";
    // makePlots("2016", "data", myVar, FileDate, myPileup);
    // makePlots("2017", "data", myVar, FileDate, myPileup);
    // makePlots("2018", "data", myVar, FileDate, myPileup);
    // makePlots("2016", "mc", myVar, FileDate, myPileup);
    // makePlots("2017", "mc", myVar, FileDate, myPileup);
    // makePlots("2018", "mc", myVar, FileDate, myPileup);
    myPileup = "lowlow";
    makePlots("2018", "data", myVar, FileDate, myPileup);
    makePlots("2018", "mc", myVar, FileDate, myPileup);
    myPileup = "low";
    makePlots("2017", "data", myVar, FileDate, myPileup);
    makePlots("2017", "mc", myVar, FileDate, myPileup);
    myPileup = "medium";
    makePlots("2017", "data", myVar, FileDate, myPileup);
    makePlots("2017", "mc", myVar, FileDate, myPileup);
    myPileup = "high";
    makePlots("2017", "data", myVar, FileDate, myPileup);
    makePlots("2017", "mc", myVar, FileDate, myPileup);
myVar = "DOCA";
// FileDate = "2019Jun27";
// FileDate = "2019July1";
// FileDate = "2019July30";
// FileDate = "2019Nov21";
FileDate = "2019Dec5";
    // makePlots("2016", "data", myVar, FileDate, myPileup);
    // makePlots("2017", "data", myVar, FileDate, myPileup);
    // makePlots("2018", "data", myVar, FileDate, myPileup);
    // makePlots("2016", "mc", myVar, FileDate, myPileup);
    // makePlots("2017", "mc", myVar, FileDate, myPileup);
    // makePlots("2018", "mc", myVar, FileDate, myPileup);
    myPileup = "lowlow";
    makePlots("2018", "data", myVar, FileDate, myPileup);
    makePlots("2018", "mc", myVar, FileDate, myPileup);
    myPileup = "low";
    // makePlots("2018", "data", myVar, FileDate, myPileup);
    // makePlots("2018", "mc", myVar, FileDate, myPileup);
    makePlots("2017", "data", myVar, FileDate, myPileup);
    makePlots("2017", "mc", myVar, FileDate, myPileup);
    myPileup = "medium";
    makePlots("2017", "data", myVar, FileDate, myPileup);
    makePlots("2017", "mc", myVar, FileDate, myPileup);
    myPileup = "high";
    makePlots("2017", "data", myVar, FileDate, myPileup);
    makePlots("2017", "mc", myVar, FileDate, myPileup);

}

