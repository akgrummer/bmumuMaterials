#include "TCut.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TLegend.h"
#include "TVector3.h"
#include "TH1.h"
#include "TBranch.h"
#include "TCanvas.h"
#include <iostream>
#include <dirent.h>
#include <TChain.h>
#include <algorithm>
#include "TMultiGraph.h"
#include "/afs/cern.ch/user/a/agrummer/AtlasStyle/AtlasLabels.C"
#include "/afs/cern.ch/user/a/agrummer/AtlasStyle/AtlasLabels.h"
#include "/afs/cern.ch/user/a/agrummer/AtlasStyle/AtlasUtils.C"
#include "/afs/cern.ch/user/a/agrummer/AtlasStyle/AtlasUtils.h"
#include "/afs/cern.ch/user/a/agrummer/AtlasStyle/AtlasStyle.C"
#include "/afs/cern.ch/user/a/agrummer/AtlasStyle/AtlasStyle.h"
using namespace std;
#include "/afs/cern.ch/user/a/agrummer/www/bmumu/IsoVarROCs/v8IsoScripts/PlottingScript.h"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu/IsoVarROCs/v8IsoScripts/getHistoPlottingScript.C"

TH1F* SetAxes(TH1F* hist1 = NULL, AxesStruct axesInfo = axesPVWeights,
              TString Ytitle = "", TString Xtitle = "", bool drawResiduals = false){
        hist1->GetXaxis()->SetRangeUser(axesInfo.XLow, axesInfo.Xhigh);
            hist1->SetMaximum(axesInfo.Yhigh);   // along          
            hist1->SetMinimum(axesInfo.YLow);  //   Y 
        if (drawResiduals){
            hist1->GetYaxis()->SetNdivisions(4,5,0); //4,5,0
            hist1->GetXaxis()->SetLabelOffset(0.028);
        }

        if (!Ytitle.EqualTo("")) hist1->GetYaxis()->SetTitle(Ytitle);
        if (!Xtitle.EqualTo("")) hist1->GetXaxis()->SetTitle(Xtitle);
        // cout<< "xl, xu, yl, yu"<< axesInfo.XLow<<" "<<axesInfo.Xhigh<<" "<< axesInfo.YLow<<" "<<axesInfo.Yhigh<<endl;
        return hist1;
    }

TH1F* SetAxesRes(TH1F* hres = NULL, AxesStruct axesInfo = axesPVWeights,
        TString Ytitle = "", TString Xtitle = ""){
        hres->GetXaxis()->SetRangeUser(axesInfo.XLow, axesInfo.Xhigh);
        hres->SetMaximum(axesInfo.resYhigh);   // along          
        hres->SetMinimum(axesInfo.resYLow);  //   Y 
        // hres->SetMarkerSize(0.7);
        // hres->SetMarkerSize(1);
        hres->GetXaxis()->SetTitleOffset(1.0); //0.95
        hres->GetXaxis()->SetTitleSize(0.17);
        hres->GetXaxis()->SetLabelSize(0.15); //0.17 0.1
        hres->GetYaxis()->SetTitleSize(0.17);
        hres->GetYaxis()->SetTitleOffset(0.47); //0.26
        hres->GetYaxis()->SetLabelSize(0.12);//0.17 //0.08
        hres->GetYaxis()->SetNdivisions(4,3,0); //4,5,0

        if (!Ytitle.EqualTo("")) hres->GetYaxis()->SetTitle(Ytitle);
        if (!Xtitle.EqualTo("")) hres->GetXaxis()->SetTitle(Xtitle);
        // cout<< "xl, xu, yl, yu"<< axesInfo.XLow<<" "<<axesInfo.Xhigh<<" "<< axesInfo.YLow<<" "<<axesInfo.Yhigh<<endl;
        return hres;
    }

TLegend *GetLegend(TH1F* hist1 = NULL, TString leg1 = "legend name 1", TString Descript1 = "l",
                    TH1F* hist2 = NULL, TString leg2 = "legend name 2", TString Descript2 = "l",
                    TString legHeader = "", LegStruct PlaceLeg = legPVWeights){
    TLegend* leg;
    leg = new TLegend(PlaceLeg.XLow, PlaceLeg.YLow, PlaceLeg.Xhigh, PlaceLeg.Yhigh ,NULL,"brNDC");
    leg->SetHeader(legHeader);
    leg->AddEntry(hist1, leg1, Descript1);
    leg->AddEntry(hist2, leg2, Descript2);
    leg->SetBorderSize(0);  // no border
    leg->SetLineColor(0);
    leg->SetFillColor(0);
    leg->SetTextSize(0.025);
    return leg;
}

TString SetDataTypeText(TString DataType = ""){
    TString theRunNumber("");
    if (DataType.EqualTo("2016main") || DataType.EqualTo("MC16a")){
    theRunNumber = " Run 302393";
    }
    else if (DataType.EqualTo("2016main303846") || DataType.EqualTo("MC16a303846")){
        theRunNumber = " Run 303846";
    }
    else if (DataType.EqualTo("2017") || DataType.EqualTo("MC16d")){
        theRunNumber = " Run 339849";
    }
    else if (DataType.EqualTo("2018") || DataType.EqualTo("MC16e")){
        theRunNumber = " Run 358096";
    }
    TString DataTypeText("");
    DataTypeText = theRunNumber;
    return DataTypeText;
}

VariableInfo in2vexp(TString inPattern){
    VariableInfo vexp;
if (inPattern.EqualTo("varPVWeights")) vexp = varPVWeights;
else if (inPattern.EqualTo("varMuon1_reco_eff_sf")) vexp = varMuon1_reco_eff_sf;
else if (inPattern.EqualTo("varMuon2_reco_eff_sf")) vexp = varMuon2_reco_eff_sf;
else if (inPattern.EqualTo("varMuon1_reco_eff_sf*")) vexp = varMuon1_reco_eff_sf;
else if (inPattern.EqualTo("MCWeights")) vexp = MCWeights;
else if (inPattern.EqualTo("MuonRecoWeights")) vexp = MuonRecoWeights;
else if (inPattern.EqualTo("PRIVX_mu")) vexp = PRIVX_mu;
else if (inPattern.EqualTo("BIsoACH")) vexp = BisolationACH;
else if (inPattern.EqualTo("BIsoBEJ")) vexp = BisolationBEJ;
else if (inPattern.EqualTo("BIsoBGJ")) vexp = BisolationBGJ;
else if (inPattern.EqualTo("ct")) vexp = ct;
return vexp;
}

TH1F* RetrieveHist(TString ifilename = "", TString DataType = "", 
                    VariableInfo myVar = BisolationACH, TString wt = "", 
                    Int_t ColorIndex=0, TString Pileup="",  TString Norm = "", HistStruct hs = hist1StructData){
TCut myCut("1==1");
TH1F *myHist(NULL);
if (Pileup.EqualTo("lowlow")) {
myCut = myCut*("PRIVX_mu >= 12. && PRIVX_mu <= 22.");
}if (Pileup.EqualTo("low")) {
myCut = myCut*("PRIVX_mu >= 23. && PRIVX_mu <= 33.");
}else if(Pileup.EqualTo("medium")) {
myCut = myCut*("PRIVX_mu >= 34. && PRIVX_mu <= 44.");
}else if(Pileup.EqualTo("high")) {
myCut = myCut*("PRIVX_mu >= 45. && PRIVX_mu <= 55.");
}else if(Pileup.EqualTo("all")) {
myCut = myCut;
} 
if (!wt.EqualTo("")){
    myCut=myCut*wt;
}
// myCut = "Muon1_reco_eff_sf*Muon2_reco_eff_sf";

// TFile* ifile = new TFile(ifilename);
// TTree *myTree = (TTree*)ifile->Get("T_mv");
// cout<<" Tree Entries: "<<myTree->GetEntries()<<endl;
// myHist = getHistoFromTree(myTree, myVar, myVar.name, myCut);
TChain* myTree = new TChain("T_mv");
myTree->Add(ifilename);
// TFile* ifile = new TFile(ifilename);
// TTree *myTree = (TTree*)ifile->Get("T_mv");
cout<<" Tree Entries: "<<myTree->GetEntries()<<endl;
TString myVarname = myVar.name;
TString histName("");
histName = TString(myVar.name);
if (!ColorIndex==0) histName.Form(histName+"%d", ColorIndex);
// TString histName = TString(ColorIndex);
myHist = getHistoFromTree(myTree, myVar, histName, myCut);
// myHist = getHistoFromTChain(myTree, myVar, histName, myCut);
// myHist->Sumw2();
myHist->SetMarkerColor(ColorWheel[ColorIndex]);
myHist->SetLineColor(ColorWheel[ColorIndex]);
myHist->SetMarkerStyle(20);
// if(DataType.Contains("2016")||DataType.Contains("2017")||DataType.Contains("2018")) {
// myHist->SetMarkerSize(0.9);
myHist->SetMarkerStyle(hs.MarkerStyle);
myHist->SetMarkerSize(hs.MarkerSize);
myHist->SetLineWidth(2);
// myHist->SetLineStyle(ColorIndex+1);
// myHist->SetLineStyle(ColorIndex+1);
// myHist->GetYaxis()->SetTitle("Bkg. Rejection [%]");
// myHist->GetXaxis()->SetTitle("Sig. Efficiency [%]");
if (Norm.EqualTo("norm")){
    myHist->Scale(1./myHist->Integral(0, myVar.nbins + 1));
    myHist->GetYaxis()->SetTitle("a.u.");
}
// Double_t binSize = myVar.XMax/myVar.nbins;
// TString binName = TString(binSize)
// binName += myVar.
else{
    myHist->GetYaxis()->SetTitle("Candidates");
}
return myHist;
}



void ComparisonPlot(VariableInfo vexp, TString wt = "",
                    TString version="", TString DataType=""){
    SetAtlasStyle();
    TString p1(""), p2(""), d1(""), d2(""), ft(""), ftstar(""), fin1p(""), fin2p("");
    TString Xtitle("");
    TH1F *hist1(NULL), *hist2(NULL), *hres(NULL);
    if (version.EqualTo("v1")){
          p1 = "/eos/home-a/agrummer/BsmumuData/2020nTuples/FinalSkim/v1/";} //path1
    else if (version.EqualTo("v2")){
          p1 = "/eos/home-a/agrummer/BsmumuData/2020nTuples/FinalSkim/v2/";} //path1
          // p1 = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/skimmed_MC/Bsmumu/v2/";} //path1
    // else {p1 = "/eos/home-a/agrummer/BsmumuData/2020nTuples/FinalSkim/v3/";}
    // else {p1 = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/skimmed_MC/Bsmumu/v3/";}
    else {p1 = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/OneTestFile_2ndRoundVal/fromBsmumu_ct_300426_skimmed_MC/bsmumu.root";}
    p2 = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/OneTestFile_2ndRoundVal/fromBsmumu_300426_skimmed_MC/bsmumu.root";//path2
    // p2 =  "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/skimmed_ntup/";
    // p2 = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/skimmed_MC/Bsmumu/v2/";//path2
    d1  = "2020Feb11";//date1
    d2  = "2019Dec5";//date2
    // ft = "MC16e";//file type
    ft = DataType;//file type
    // if (DataType.Contains("16a")){
    // ftstar = "user.ibragimo.mc16a_13TeV.300426.Bs_mu3p5mu3p5.DAOD_BPHY8.e4889_s3126_r9364_p3793_NTUP_atrkwhits/v6";

    // }
    // else if (DataType.Contains("16d")){
    // ftstar = "user.ibragimo.mc16d_13TeV.300426.Bs_mu3p5mu3p5.DAOD_BPHY8.e4889_s3126_r10201_p3793_NTUP_atrkwhits/v6";

    // }else if (DataType.Contains("16e")){
    // ftstar = "user.ibragimo.mc16e_13TeV.300426.Bs_mu3p5mu3p5.DAOD_BPHY8.e4889_s3126_r10724_p3793_NTUP_atrkwhits/v6";

    // }
    // if(DataType.EqualTo("2016main")){
    //     fin1p = p1 + ft + "/" + "*.root";
    //     fin2p = p2 + "2016" + "/" + "*.root";
    // }else{
    //     fin1p = p1 + ft + "/" + "*.root";
    //     // if (DataType.Contains("mc")){
    //     //     ftstar.ReplaceAll("mc","MC");
    //     // }
    //     // fin2p = p2 + ftstar + "/" + "*.root";
    //     fin2p = p2 + ft + "/" + "*.root";
    // }
        // fin1p = p1 + ft + "/" + "*.root";
    //     fin1p = p1 + ft + "All/" + "LASTskim_"+DataType+"_All_2020Feb11.root";
    // if(DataType.EqualTo("2016main")){
    //     fin2p = p1 + "2016" + "All/" + "LASTskim_2016_All_2020Feb11.root";
    // }else{
    //     fin2p = p1 + ft + "All/" + "LASTskim_"+DataType+"_All_2020Feb11.root";
    // }
    if (DataType.EqualTo("MC16e")){
            fin1p = p1 + ft + "All/" + "LASTskim_"+DataType+"_All_2020Feb11.root";
            fin2p = p1 + "2018" + "All/" + "LASTskim_"+"2018"+"_All_2020Feb11.root";}
    else if (DataType.EqualTo("MC16d")){
            fin1p = p1 + ft + "All/" + "LASTskim_"+DataType+"_All_2020Feb11.root";
            fin2p = p1 + "2017" + "All/" + "LASTskim_"+"2017"+"_All_2020Feb11.root";}
    else{
        fin1p = p1;
        fin2p = p2;
    }

    // fin1p = p1 + ft + "All/LASTskim_" + ft + "_All_" + d1 + ".root";
    // fin2p = p2 + ft + "All/LASTskim_" + ft + "_All_" + d2 + ".root";
    // TFile *fin1 = new TFile(fin1p);
    // TTree *tin1 = (TTree*)fin1->Get("T_mv");
    // TH1F* getHistoFromTree(TTree* tree, VariableInfo Variable, const char* hname, TCut cut)
    // TCut aCut = "1==1";
    HistStruct h1s;
    HistStruct h2s;
    // if (DataType.Contains("MC")){
    h1s = hist1StructMC;
    // h2s = hist2StructData;
    h2s = hist2StructMC;
    // }else{
    // h1s = hist1StructData;
    // h2s = hist2StructData;
    // }
    hist1 = RetrieveHist(fin1p, DataType, vexp, wt, 0, "all", "norm", h1s);
    hist2 = RetrieveHist(fin2p, DataType, vexp, "", 1, "all", "norm", h2s);
    //note - this should go into the hist structure!
    hist2->SetLineStyle(2);
    // fin1->Close();
    // TFile *fin2 = new TFile(fin2p);
    // TTree *tin2 = (TTree*)fin2->Get("T_mv");
    // hist2 = getHistoFromTree(tin2, vexp, "hist2", aCut);
    // fin2->Close();

    // TChain* ch = new TChain("T_mv")
    // ch->Add("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/final_MC/Bmumu/v1/mc16e/*.root")
    // /eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/skimmed_MC/Bsmumu/v2/mc16e/
    TCanvas* c2 = new TCanvas("c2", "ROC curve",0.,0., 800, 600);
    TPad *pad1, *pad2;
    pad1 = new TPad("pad1","pad1",0,0.33,1,1); //xlow ylow xup yup
    pad2 = new TPad("pad2","pad2",0,0,1,0.33); //0.3
    bool drawResiduals(true);
    if (drawResiduals) {
        pad1->SetMargin(0.16,0.05,0.028,0.09);//left, right, bottom, top
        // pad1->SetMargin(0.12,0.05,0.028,0.09);
        pad1->SetBorderMode(0);
        if (vexp.logScale) pad1->SetLogy(1);
        pad2->SetMargin(0.16,0.05,0.38,0.04);
        // pad2->SetMargin(0.12,0.05,0.38,0.06);
        pad2->SetBorderMode(0);
        pad1->Draw();
        pad2->Draw();
        pad1->cd();
    }
    // hist1->Scale(1./hist1->Integral(0, vexp.nbins + 1));
    // if (iinfo.EqualTo("varMuon2*")) Xtitle = "#mu_{1} Reco Eff SF * #mu_{2} Reco Eff SF";
    TString varnameDummy = vexp.name;
    if(varnameDummy.EqualTo("PRIVX_mu")){
        if (DataType.Contains("2016")){
            vexp.AxesInfo = axesPRIVX_mu2016;
        }else if(DataType.Contains("MC16e") || DataType.Contains("MC16a")){
            vexp.AxesInfo = axesPRIVX_muMC16star;
        }
    }
    hist1 = SetAxes(hist1, vexp.AxesInfo, "", Xtitle, drawResiduals);
    hist2 = SetAxes(hist2, vexp.AxesInfo, "", Xtitle, drawResiduals);
    hist1->Draw(h1s.DrawCommands);
    hist2->Draw(h2s.DrawCommands);
    // hist2->SetLineStyle(2);

    // TString legName1 = DataType + ", New nTuple ("+version+")";
    TString legName1 = "new validation file";
    // TString legName2 = DataType + ", v2 nTuple";
    TString legName2("");
    if (DataType.EqualTo("MC16e")){
        legName2 = "2018 , New nTuple ("+version+")";}
    if (DataType.EqualTo("MC16d")){
        legName2 = "2017 , New nTuple ("+version+")";}
    legName2 = "old validation file";
    // TString legName2 = DataType + ", New nTuple (v2)";

    TString legHeader("");
    legHeader = SetDataTypeText(DataType);
    TLegend* leg = GetLegend(hist1, legName1, h1s.LegCommand, 
                              hist2, legName2, h2s.LegCommand, 
                              legHeader, vexp.LegInfo);
    leg->Draw();
    TString Ytitle("");
    // Ytitle = version+"/old";
    Ytitle = "new/old";
    if (drawResiduals) {
        pad2->cd();
        hres = (TH1F*)hist1->Clone("hres");
        hres->Sumw2();
        hres->Divide(hist1,hist2,1.0,1.0);

        hres = SetAxesRes(hres, vexp.AxesInfo, Ytitle, Xtitle);
        hres->SetMarkerColor(1);
        hres->SetMarkerStyle(20);
        hres->SetMarkerSize(0.7);
        hres->SetLineColor(1);
        hres->Draw("e0p same");
    }

    /////// SAVE OPTIONS ////////////////
    TString op(""), vd("");
    // op = "/afs/cern.ch/user/a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/vars2020Mar/";
    // vd = version;
    // op += vd;
    // op += "/";
    // op += DataType;
    // op += "/";
    // TString on = vexp.name;
    // if(!(wt.EqualTo("")||wt.EqualTo("1"))) on += wt;
    // on+=DataType;
    op = "/afs/cern.ch/user/a/agrummer/www/bmumu/valSignOff/2020Apr16/";
    op += vexp.name;
    op += ".pdf";
    c2->SaveAs(op);
    delete c2;
    // TChain* ch0 = new TChain("T_mv")
    // ch0->Add("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/final_ntup/user.ibragimo.mc16e_13TeV.300426.Bs_mu3p5mu3p5.DAOD_BPHY8.e4889_s3126_r10724_p3793_NTUP_atrkwhits/v6/*.root");
}

int main(int argc, char* argv[])
{
    // VariableInfo pattern;
      TString  pattern1, pattern2, version, DataType;
  // if (argc>1) inpath = TString(argv[1]);
  if (argc>1) pattern1 = TString(argv[1]);
  // if (argc>2) pattern2 = TString(argv[2]);
  if (argc>2) version = TString(argv[2]);
  if (argc>3) DataType = TString(argv[3]);

    VariableInfo vexp;
    vexp = in2vexp(pattern1);
    cout<<vexp.name <<endl;

    if (DataType.EqualTo("data")){
        ComparisonPlot(vexp, "", version, "2016main");
        ComparisonPlot(vexp, "", version, "2017");
        ComparisonPlot(vexp, "", version, "2018");
    }else if (DataType.EqualTo("MC")){
        // ComparisonPlot(vexp, "(run_number==302393)*PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf", version, "MC16a");
        ComparisonPlot(vexp, "(run_number==339849)*PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf", version, "MC16d");
        ComparisonPlot(vexp, "(run_number==358096)*PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf", version, "MC16e");
    }else if (DataType.Contains("weights")){
        // ComparisonPlot(vexp, "(run_number==302393)", version, "MC16a");
        // ComparisonPlot(vexp, "(run_number==339849)", version, "MC16d");
        // ComparisonPlot(vexp, "(run_number==358096)", version, "MC16e");
        ComparisonPlot(vexp, "", version, "weights");
    }
    else{ComparisonPlot(vexp, "", version, DataType);}

return 0;
}
