//Author: Aidan Grummer, Aug 2018
//run with root -l -q InputVars_v3.cpp"(13)"
// or RunInputVars_v2.sh

// Run with 
/*
root -l -q -b InputVars_v5_Efficiencies.C"(\"Bkg36\")"
root -l -q -b InputVars_v5_Efficiencies.C"(\"Sig36\")"
root -l -q -b InputVars_v5_Efficiencies.C"(\"Bkg18\")"
root -l -q -b InputVars_v5_Efficiencies.C"(\"Bkg54\")"
root -l -q -b InputVars_v5_Efficiencies.C"(\"Sig18\")"
root -l -q -b InputVars_v5_Efficiencies.C"(\"Sig54\")"
*/


#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasLabels.C"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasLabels.h"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasStyle.C"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasStyle.h"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasUtils.C"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasUtils.h"
#include<TMath.h>
#include <ctime>

// Char_t classNameTest;
// TString ATestString;
// Int_t classIDTest(0);
// Float_t BDTvarTest(0.0);
// Float_t TestWeight(0.);

// Float_t BptvarTest(0.0);

// Char_t classNameTrain;
// TString ATrainString;
// Int_t classIDTrain(0);
// Float_t BDTvarTrain(0.0);
// Float_t TrainWeight(0.);

// Double_t BDTvar1(0.0);
// Double_t myVar1(0.0);
// Double_t myVar1second(0.0);
// Double_t BDTvar2(0.0);
// Double_t myVar2(0.0);
// Double_t myVar2second(0.0);

// Float_t BDTvar1f(0.0);
// Float_t myVar1f(0.0);
// Float_t myVar1fsecond(0.0);
// Float_t BDTvar2f(0.0);
// Float_t myVar2f(0.0);
// Float_t myVar2fsecond(0.0);

// Int_t BDTvar1i(0.0);
// Int_t myVar1i(0.0);
// Int_t BDTvar2i(0.0);
// Int_t myVar2i(0.0);

// Float_t BptvarTrain(0.0);

// Float_t myVar = (0.0);

// TString iso = "B_iso_7_Chi2_5_LoosePt05";
//as in run1:
//this is wrong though! iso should be Biso not Biso NTracks
// TString iso = "B_iso_Ntracks_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127";
//custom:
// TString iso = "B_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0134217728";
TString iso = "B_iso_10_noChi2_LooSiHi1Pt05_T0134217728";
//loose:
//CAREFUL - should by BISO not BISO ntracks
// TString iso = "B_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0008388608";
// TString ctntrk = "closeTrkNtrksChi2";
//custom:
TString ctntrk = "closeTrkNtrksChi2_T0134217728_LooSiHi1Pt05_f2dc2";
//loose:
// TString ctntrk = "closeTrkNtrksChi2_T0008388608_LooSiHi1Pt05_f2dc2"
// TString ctdoca = "TMath::Sqrt(pow(closeTrkDCA,2)+pow(closeTrkZCA,2))";
//as in run1:
// TString ctdoca = "closeTrkDOCA_3";
// TString ctdoca = "closeTrkDOCA";
//custom:
TString ctdoca = "closeTrkDOCA_T0134217728_LooSiHi1Pt05_f2dc2";
//loose:
// TString ctdoca = "closeTrkDOCA_T0008388608_LooSiHi1Pt05_f2dc2";
TString pa = "a_2D";
TString dr = "DR";
TString bpt = "B_pT";
TString mchi2pv = "chi2_PVSV_log2D";
TString ch2pvsv = "B_minChi2MuonsIPtoAnyPV";
TString bip = "Bvtx3DIP";
TString d0maxs = "d0Max_sig";
TString d0mins = "d0Min_sig";
TString dphi = "B_IDtrks_deltaPhi";
TString mdca = "B_IDtrks_DCA";
TString blxy = "Lxy";
TString plng = "PlngMin2D";
TString Npv = "Npv";
TString mu = "PRIVX_mu_round";
// TString BDT = "BDT_bb_2016";
TString BDT = "BDT_bb_2020";

struct Open2Trees{
TTree *Tree1;
TTree *Tree2;
};
struct BDTcuts{
    Double_t cut18;
    Double_t cut36;
    Double_t cut54;
};
struct ConfigStruct{
    TString ifile1;
    TString ifile2;
    TString odir;
    BDTcuts BDTcuts1;
    BDTcuts BDTcuts2;
    TCut AddCut;
    TCut weights;
};

struct VariableInfo{
  // const char * Name;
  TString Name;
  int SigBins;
  int BkgBins;
  Float_t XMin;
  Float_t XMax;
  const char * AxisName;
  bool logScale;
  TString dataType;
}InputVariables[]= {

//for sig:
    // {pa, 100, 0.0, 1., "|#alpha_{2D}| [rad]", true, "d"},
    // {iso, 100, 0.1, 1.1, "B Isolation (I^{B}_{0.7})", true, "f"},
    // {dr, 100, 0.0, 1.5, "#Delta R", true, "d"},
    // {bpt, 100, 9000., 36000., "p_{T}^{B} [MeV]", false, "d"},
    // {mchi2pv, 100, -5.0, 10., "Log(#chi^{2}_{xy})", false, "d"},
    // {ch2pvsv,80,-10,10,"Log(#chi^{2}_{#mu,xPV})", false, "d"},
    // {bip, 100, 0.0, 1., "|IP_{B}^{3D}|", false, "d"},
    // {d0maxs, 200, 0.0, 50., "|d_{0}|^{max} sig.", true, "d"},
    // {d0mins, 200, 0.0, 40., "|d_{0}|^{min} sig.", true, "d"},
    // {dphi, 100, 0.0, 1.3, "|#Delta#phi_{#mu#mu}|", false, "d"},
    // {mdca, 100, 0.0, 1., "DOCA_{#mu#mu} [mm]", false, "d"},
    // {ctdoca, 100, 0.0, 1., "DOCA_{xtrk,loose,pt>0.5}[mm]", false},
    // {ctntrk, 50, 0., 50., "N^{clos}_{trk, loose, pt>0.5}", false, "i"},
    // {blxy, 100, 0.0, 5., "L_{xy} [mm]", true, "d"},
    // {plng, 40, 0., 40000., "P^{min}_{L} [MeV]", false, "d"},
    // {Npv, 25, 0., 25., "nPV", false, "i"},
    // {BDT, 100, -0.8, 0.8, "BDT Variable", false, "d"}
//For Bkg:
    {iso     , 51  ,51  , 0.0    , 1.02 , "B Isolation" , true   , "f"}         ,
    {pa      , 100 , 100 , 0.0   , 1.     , "|#alpha_{2D}| [rad]"       , true   , "d"}         ,
    {dr      , 25 , 10 , 0.0   , 1.5    , "#Delta R"                  , true   , "d"}         ,
    {bpt     , 50 , 10 , 9000. , 36000. , "p_{T}^{B} [MeV]"           , false  , "d"}         ,
    {mchi2pv , 50 , 25 , -5.0  , 10.    , "Log(#chi^{2}_{xy})"        , false  , "d"}         ,
    {ch2pvsv , 80  , 25 , -10   , 10     , "Log(#chi^{2}_{#mu, xPV})"  , false  , "d"}   ,
    {bip     , 15 , 15 , 0.0   , 1.     , "|IP_{B}^{3D}|"             , false  , "d"}         ,
    {d0maxs  , 30 , 15 , 0.0   , 50.    , "|d_{0}|^{max} sig."        , true   , "d"}         ,
    {d0mins  , 30 , 15 , 0.0   , 40.    , "|d_{0}|^{min} sig."        , true   , "d"}         ,
    {dphi    , 50 , 10 , 0.0   , 1.3    , "|#Delta#phi_{#mu#mu}|"     , false  , "d"}         ,
    {mdca    , 50 , 25 , 0.0   , 1.     , "DOCA_{#mu#mu} [mm]"        , false  , "d"}         ,
    {ctdoca  , 50 , 10 , 0.0   , 1.     , "DOCA_{xtrk, loose, pt>0.5}[mm]" , false} ,
    {ctntrk  , 50  , 50  , 0.    , 50.    , "N^{clos}_{trk, loose, pt>0.5}", false  , "i"}      ,
    {blxy    , 50 , 15   , 0.0   , 5.     , "L_{xy} [mm]"               , true   , "d"}         ,
    {plng    , 25  , 10  , 0.    , 40000. , "P^{min}_{L} [MeV]"         , false  , "d"}         ,
    {Npv     , 30  , 30  , 0.    ,30.    , "nPV"                       , false  , "i"}         ,
    {mu      , 45  , 45  , 0.    ,45.    , "<mu>"                       , false  , "i"}         ,
    {BDT     , 50 , 25 , -0.8  , 0.8    , "BDT Variable"              , false  , "d"}
//used before rebinning request:
    // {pa, 100, 0.0, 1., "|#alpha_{2D}| [rad]", true, "d"},
    // {iso, 100, 0.1, 1.1, "B Isolation (I^{B}_{0.7})", true, "f"},
    // {dr, 100, 0.0, 1.5, "#Delta R", true, "d"},
    // {bpt, 100, 9000., 36000., "p_{T}^{B} [MeV]", false, "d"},
    // {mchi2pv, 100, -5.0, 10., "Log(#chi^{2}_{xy})", false, "d"},
    // {ch2pvsv,80,-10,10,"Log(#chi^{2}_{#mu,xPV})", false, "d"},
    // {bip, 100, 0.0, 1., "|IP_{B}^{3D}|", false, "d"},
    // {d0maxs, 200, 0.0, 50., "|d_{0}|^{max} sig.", true, "d"},
    // {d0mins, 200, 0.0, 40., "|d_{0}|^{min} sig.", true, "d"},
    // {dphi, 100, 0.0, 1.3, "|#Delta#phi_{#mu#mu}|", false, "d"},
    // {mdca, 100, 0.0, 1., "DOCA_{#mu#mu} [mm]", false, "d"},
    // {ctdoca, 100, 0.0, 1., "DOCA_{xtrk,loose,pt>0.5}[mm]", false},
    // {ctntrk, 50, 0., 50., "N^{clos}_{trk, loose, pt>0.5}", false, "i"},
    // {blxy, 100, 0.0, 5., "L_{xy} [mm]", true, "d"},
    // {plng, 40, 0., 40000., "P^{min}_{L} [MeV]", false, "d"},
    // {Npv, 25, 0., 25., "nPV", false, "i"},
    // {BDT, 100, -0.8, 0.8, "BDT Variable", false, "d"}

    // {"TMath_Abs_B_IDtrks_deltaEta_", 100, 0.0, 1., "|#eta_{#mu1}-#eta_{#mu2}|", true},
    // {"muP_iso_7_chi2_5_LoosePt05",100,0.0,1.1,"#mu+ Isolation (I^{#mu+}_{0.7})", true},
    // {"muM_iso_7_chi2_5_LoosePt05",100,0.0,1.1,"#mu- Isolation (I^{#mu-}_{0.7})", true}




    // {pa, 100, 0.0, 1., "|#alpha_{2D}| [rad]", true, "d"},
    // {"B_iso_7_Chi2_5_LoosePt05", 100, 0.1, 1.1, "B Isolation (I^{B}_{0.7})", true, "f"},
    // {"DR", 100, 0.0, 1.5, "#Delta R", true, "d"},
    // {"B_pT", 100, 9000., 36000., "p_{T}^{B} [GeV]", false, "d"},
    // {"chi2_PVSV_log2D", 100, 0.0, 10., "Log(#chi^{2}_{xy})", false, "d"},
    // {"B_minChi2MuonsIPtoAnyPV",80,-10,10,"Log(#chi^{2}_{#mu,xPV})", false, "d"},
    // {"Bvtx3DIP", 100, 0.0, 1., "|IP_{B}^{3D}|", false, "d"},
    // {"d0Max_sig", 200, 0.0, 100., "|d_{0}|^{max} sig.", false, "d"},
    // {"d0Min_sig", 200, 0.0, 100., "|d_{0}|^{min} sig.", false, "d"},
    // {"B_IDtrks_deltaPhi", 100, 0.0, 1.3, "|#Delta#phi_{#mu#mu}|", false, "d"},
    // {"B_IDtrks_DCA", 100, 0.0, 1., "DOCA_{xtrk,loose,pt>0.5}[mm]", false, "d"},
    // {"TMath::Sqrt(pow(closeTrkDCA,2)+pow(closeTrkZCA,2))", 100, 0.0, 1., "DOCA_{xtrk,loose,pt>0.5}[mm]", false},
    // {"closeTrkNtrksChi2", 50, 0., 50., "N^{clos}_{trk, loose, pt>0.5}", false, "i"},
    // {"Lxy", 100, 0.0, 5., "L_{xy} [mm]", true, "d"},
    // {"PlngMin2D", 40, 0., 40000., "P^{min}_{L} [GeV]", false, "d"}
};


TH1F* getHistoFromTree(TTree* tree, TString whichSet, VariableInfo Variable, const char* hname, TCut cut)
{
TH1F *hret;
TString tmp = Variable.Name;
tmp.Append(">>");
tmp.Append(hname); // histogram name
tmp+=("(");
if (whichSet.Contains("Sig")) tmp+=Variable.SigBins;
else if (whichSet.Contains("Bkg")) tmp+=Variable.BkgBins;
tmp+=",";
tmp+=Variable.XMin;
tmp+=",";
tmp+=Variable.XMax;
tmp+=")";

int nselected(0);

nselected = tree->Draw(tmp.Data(),cut,"egoff");
cout << "creating histo:" << tmp << " event survived the cut(s): " << nselected << endl;
hret = (TH1F*)gDirectory->Get(hname);
if (whichSet.Contains("Sig")) cout << "integral of: " << hname<< " " << hret->Integral(0, Variable.SigBins+1) << endl;
else if (whichSet.Contains("Bkg")) cout << "integral of: " <<hname<<" " << hret->Integral(0, Variable.BkgBins+1) << endl;
return hret;
}

TH1F* makeRatioHists(TTree *aTree, ConfigStruct theCS, TString whichSet, TString whichBDTCut, TString whichBDT, VariableInfo Variable, TString hnameRet, TCut Weights){
    TH1F* hist1Var(NULL);
    TH1F* hist1VarAllBDT(NULL);
    TString hname = Variable.Name;
    TString hnameAllBDT = Variable.Name + "FullBDT";
    // if (hname.Contains("(")){ 
    //     hname.ReplaceAll("(", "_");
    //     hnameAllBDT.ReplaceAll("(", "_");
    //     hname.ReplaceAll(")", "_");
    //     hnameAllBDT.ReplaceAll(")", "_");
    //     hname.ReplaceAll("::", "_");
    //     hnameAllBDT.ReplaceAll("::", "_");
    // }
    Double_t BDTCutAll = -1;

    TCut BDTCut;
    if (whichBDTCut.Contains("18")){
        if (whichBDT.EqualTo("withoutPU")) BDTCut = Form("BDT_bb_2020>%f", theCS.BDTcuts1.cut18);
        if (whichBDT.EqualTo("withPU")) BDTCut = Form("BDT_bb_2020>%f", theCS.BDTcuts2.cut18);
    }else if (whichBDTCut.Contains("36")){
        if (whichBDT.EqualTo("withoutPU")) BDTCut = Form("BDT_bb_2020>%f", theCS.BDTcuts1.cut36);
        if (whichBDT.EqualTo("withPU")) BDTCut = Form("BDT_bb_2020>%f", theCS.BDTcuts2.cut36);
    }else if (whichBDTCut.Contains("54")){
        if (whichBDT.EqualTo("withoutPU")) BDTCut = Form("BDT_bb_2020>%f", theCS.BDTcuts1.cut54);
        if (whichBDT.EqualTo("withPU")) BDTCut = Form("BDT_bb_2020>%f", theCS.BDTcuts2.cut54);
    }

    Double_t LSBLow = 4766.0;
    TCut CutLSBLow = Form("B_MUCALC_mass>=%f",LSBLow); 
    Double_t LSBHigh = 5166.0;
    TCut CutLSBHigh = Form("B_MUCALC_mass<%f",LSBHigh);
    Double_t RSBLow = 5526.0;
    TCut CutRSBLow = Form("B_MUCALC_mass>%f",RSBLow);
    Double_t RSBHigh = 5966.0;
    TCut CutRSBHigh = Form("B_MUCALC_mass<=%f",RSBHigh);

    TCut CutLSB = (CutLSBLow && CutLSBHigh);
    TCut CutRSB = (CutRSBLow && CutRSBHigh);
    TCut CutSB = CutLSB || CutRSB;
    TCut AddCut = theCS.AddCut;


    TCut FinalCut;
    TCut FinalCutAllBDT;

    if (whichSet.Contains("Sig")){
        FinalCut = BDTCut && AddCut;
        FinalCutAllBDT = AddCut;
    }
    if (whichSet.Contains("Bkg")) {
        FinalCut = BDTCut && AddCut && CutSB;
        FinalCutAllBDT = AddCut && CutSB;
    }


    hist1Var = getHistoFromTree(aTree, whichSet, Variable, hname+hnameRet, FinalCut*Weights);
    hist1VarAllBDT = getHistoFromTree(aTree, whichSet, Variable, hnameAllBDT+hnameRet, FinalCutAllBDT*Weights);


    hist1Var->Sumw2();
    hist1Var->Divide(hist1VarAllBDT);
    hist1Var->SetName(hnameRet);
    return hist1Var;
}



void mainCompare(VariableInfo Variable, ConfigStruct theCS, Open2Trees theTrees, TString whichBDTCut="", TString whichSet=""){
TCanvas* c1;
TH1F *h1(NULL);
TH1F *h2(NULL);
TH1F *hratio(NULL);
TLegend* leg;
TString histLeg;
TString h1Leg;
TString h2Leg;
Double_t sigTestCandidates;
Double_t bkgTestCandidates;
Double_t sigTrainCandidates;
Double_t bkgTrainCandidates;
Double_t kolS;
Double_t kolB;
TString tex3text;
TLatex *tex3;

Double_t yHeight;
Double_t yHeightMin;
Double_t yHeightMin1;
Double_t yHeightMin2;
Double_t yHeight1;
Double_t yHeight2;

cout<<Variable.Name<<endl;

TString outdir = theCS.odir;

if (whichBDTCut.Contains("18")){
     if (whichSet.Contains("Sig")) outdir = outdir + "SigBDT18/";
     if (whichSet.Contains("Bkg")) outdir = outdir + "BkgBDT18/";
}else if (whichBDTCut.Contains("36")){
     if (whichSet.Contains("Sig")) outdir = outdir + "SigBDT36/";
     if (whichSet.Contains("Bkg")) outdir = outdir + "BkgBDT36/";
}else if (whichBDTCut.Contains("54")){
     if (whichSet.Contains("Sig")) outdir = outdir + "SigBDT54/";
     if (whichSet.Contains("Bkg")) outdir = outdir + "BkgBDT54/";
}
 
c1 = new TCanvas("c1", "BDT Variable",0.,0., 800, 600);
c1->cd(0);
    TPad *pad1, *pad2, *pad3;
    pad1 = new TPad("pad1","pad1",0,0.33,1,1); //xlow ylow xup yup
    pad2 = new TPad("pad2","pad2",0,0,1,0.31); //0.3
    pad3 = new TPad("pad3","pad3",0,0,1,1); //0.3        // pad1 = new TPad("pad1","pad1",0,0.33,1,1);

    pad1->SetMargin(0.16,0.05,0.032,0.09);//left, right, bottom, top
    // pad1->SetBorderMode(0);
    pad1->SetLogy(Variable.logScale);
    pad2->SetMargin(0.16,0.05,0.38,0.05);
    pad2->SetBorderMode(0);
    pad3->SetBorderMode(0);
    pad3->SetMargin(0.16,0.05,0.16,0.05);
    pad3->SetFillStyle(4000);
    pad1->Draw();
    pad2->Draw();
    pad3->Draw();
    pad1->cd();
TString whichBDT("");
whichBDT = "withoutPU";
h1 = makeRatioHists(theTrees.Tree1, theCS, whichSet, whichBDTCut, whichBDT, Variable, "h1", theCS.weights);
whichBDT = "withPU";
h2 = makeRatioHists(theTrees.Tree2, theCS, whichSet, whichBDTCut, whichBDT, Variable, "h2", theCS.weights);
yHeight1 = h1->GetMaximum();
yHeightMin1 = h1->GetMinimum();
    if(Variable.logScale) {
        yHeight1 = yHeight1*12.;
    }
    else {
        yHeight1 = yHeight1*2;
    }

    if (!Variable.logScale) {
        h1->GetYaxis()->SetRangeUser(yHeightMin1/1.5, yHeight1);
        h2->GetYaxis()->SetRangeUser(yHeightMin1/1.5, yHeight1);
    }
    else {
        if (whichSet.Contains("Sig")){
            if (whichBDTCut.Contains("18")){
                h1->SetMaximum(5e1);
                h1->SetMinimum(1e-4);
                h2->SetMaximum(5e1);
                h2->SetMinimum(1e-4);
            }
            if (whichBDTCut.Contains("36")){
                h1->SetMaximum(5e1);
                h1->SetMinimum(5e-4);
                h2->SetMaximum(5e1);
                h2->SetMinimum(5e-4);
            }
            if (whichBDTCut.Contains("54")){
                h1->SetMaximum(5e1);
                h1->SetMinimum(1e-3);
                h2->SetMaximum(5e1);
                h2->SetMinimum(1e-3);
            }

        }else{
            if (whichBDTCut.Contains("18")){
                h1->SetMaximum(1e-3);
                h1->SetMinimum(1e-8);
                h2->SetMaximum(1e-3);
                h2->SetMinimum(1e-8);
            }
            if (whichBDTCut.Contains("36")){
                h1->SetMaximum(1e-2);
                h1->SetMinimum(5e-6);
                h2->SetMaximum(1e-2);
                h2->SetMinimum(5e-6);
            }
            if (whichBDTCut.Contains("54")){
                h1->SetMaximum(2e-2);
                h1->SetMinimum(1e-6);
                h2->SetMaximum(2e-2);
                h2->SetMinimum(1e-6);
            }
        }
    }
hratio = (TH1F*) h1->Clone("hratio");
hratio->Divide(h1,h2,1.0,1.0);

if (whichSet.Contains("Sig")) {
    histLeg = Form( "B_{s} #rightarrow #mu^{+} #mu^{-} MC");
}else{
    // histLeg = Form( "2015 and 2016 sidebands");
    histLeg = Form( "Sidebands");
}
h2->Draw("ehist");
    if (whichSet.Contains("Sig")){ 
        h2->SetLineColor(kBlack);
        h2->SetMarkerSize(0.);
    }
     else if (whichSet.Contains("Bkg")){
        h2->SetLineColor(kBlack);
        h2->SetMarkerSize(0.);
    }
h1->Draw("ehist same");
    if (whichSet.Contains("Sig")){ 
        h1->SetFillColor(632+1);
        h1->SetLineColor(632+1);
        h1->SetMarkerSize(0.);
        h1->SetFillStyle(3003);
    }
     else if (whichSet.Contains("Bkg")){
        h1->SetFillColor(600+2);
        h1->SetLineColor(600+2);
        h1->SetMarkerSize(0.);
        h1->SetFillStyle(3003);
    }
h2->GetXaxis()->SetLabelSize(0);
h2->GetYaxis()->SetTitle("Efficiency");
h2->GetXaxis()->SetTitle(Variable.AxisName);

    TLine *myLineEff;
    if (whichBDTCut.Contains("18")) myLineEff  = new TLine(Variable.XMin, 0.18, Variable.XMax, 0.18);
    if (whichBDTCut.Contains("36")) myLineEff  = new TLine(Variable.XMin, 0.36, Variable.XMax, 0.36);
    if (whichBDTCut.Contains("54")) myLineEff  = new TLine(Variable.XMin, 0.54, Variable.XMax, 0.54);
    // myLineEff  = new TLine(pad2->GetUxmin(), 1., pad2->GetUxmax(), 1.);
    myLineEff->SetLineStyle(1);
    myLineEff->SetLineWidth(1);
    myLineEff->SetLineColorAlpha(kBlack, 0.5);
    if (whichSet.Contains("Sig")) myLineEff->Draw();
    if (whichSet.Contains("Sig")){
    }

pad3->cd();
    leg = new TLegend(0.265664, 0.802609, 0.466165, 0.884348, NULL,"brNDC");
    leg->AddEntry(h1, histLeg + " trained w/o PU var","l");
    leg->AddEntry(h2, histLeg + " trained w/ PU var","l");
    leg->SetBorderSize(0);  // no border
    leg->SetLineColor(0);
    leg->SetFillColorAlpha(0, 0);
    leg->SetTextSize(0.034468);
    leg->Draw();
    ATLASLabel(0.259398, 0.893913,"Internal",1);
     
    TLatex *texBDT, *texBDT2;

    TString BDTLabel,BDTLabel2;
    if (whichBDTCut.Contains("18"))      BDTLabel = Form( "BDT > %.4f", theCS.BDTcuts1.cut18);
    else if (whichBDTCut.Contains("36")) BDTLabel = Form( "BDT > %.4f", theCS.BDTcuts1.cut36);
    else if (whichBDTCut.Contains("54")) BDTLabel = Form( "BDT > %.4f", theCS.BDTcuts1.cut54);

    texBDT = new TLatex(0.72, 0.87,BDTLabel.Data());
    texBDT->SetNDC();
    texBDT->SetTextSize(0.04);
    texBDT->SetTextFont(42);
    if (whichSet.Contains("Sig")) texBDT->SetTextColor(kRed+2);
    if (whichSet.Contains("Bkg")) texBDT->SetTextColor(kBlue+2);
    texBDT->Draw();


    if (whichBDTCut.Contains("18"))      BDTLabel2 = Form( "BDT > %.4f", theCS.BDTcuts2.cut18);
    else if (whichBDTCut.Contains("36")) BDTLabel2 = Form( "BDT > %.4f", theCS.BDTcuts2.cut36);
    else if (whichBDTCut.Contains("54")) BDTLabel2 = Form( "BDT > %.4f", theCS.BDTcuts2.cut54);

    texBDT2 = new TLatex(0.72, 0.82,BDTLabel2.Data());
    texBDT2->SetNDC();
    texBDT2->SetTextSize(0.04);
    texBDT2->SetTextFont(42);
    // texNpv->SetLineWidth(2);
    texBDT2->SetTextColor(kBlack);
    texBDT2->Draw();
    TLatex *texAdd;
    TString AddCutText = (TString)theCS.AddCut;
    TString AddCutTextDummy = AddCutText;
    cout<<"Add Cut: " << AddCutText<<endl;
    if (!AddCutText.EqualTo("")){
        AddCutText = "mu > 25";
        texAdd = new TLatex(0.3, 0.77, AddCutText.Data());
        texAdd->SetNDC();
        texAdd->SetTextSize(0.04);
        texAdd->SetTextFont(42);
        // texNpv->SetLineWidth(2);
        texAdd->SetTextColor(kBlack);
        texAdd->Draw();
    }
pad2->cd();
        hratio = (TH1F*)h1->Clone("hratio");
        // hratio->Sumw2(); //this is already present
        hratio->Divide(h1,h2,1.0,1.0);
        // hratio->GetXaxis()->SetRangeUser(xmin, xmax);
        // hratio->SetMaximum(myVI.pullYMax);   // along          
        // hratio->SetMinimum(myVI.pullYMin);  //   Y 
        hratio->GetYaxis()->SetRangeUser(.5, 1.5);
        hratio->SetMarkerSize(0.7);
        hratio->SetLineStyle(1);
        hratio->GetXaxis()->SetTitleOffset(1.0); //0.95
        hratio->GetXaxis()->SetTitleSize(0.17);
        hratio->GetXaxis()->SetLabelSize(0.14); //0.17 0.1
        hratio->GetXaxis()->SetTitle(Variable.AxisName);
        hratio->GetYaxis()->SetTitleSize(0.12);
        hratio->GetYaxis()->SetTitleOffset(0.47); //0.26
        hratio->GetYaxis()->SetLabelSize(0.1);//0.17 //0.08
        hratio->GetYaxis()->SetNdivisions(4,3,0); //4,5,0
        
        hratio->GetYaxis()->SetTitle("no PU / PU");
        // hratio->GetXaxis()->SetTitle(Xtitle);
        hratio->SetMarkerColor(1);
        hratio->SetLineColor(1);
        hratio->Draw("e0p same");
        TLine *myLine;
        myLine  = new TLine(Variable.XMin, 1., Variable.XMax, 1.);
        // myLine  = new TLine(pad2->GetUxmin(), 1., pad2->GetUxmax(), 1.);
        myLine->SetLineStyle(1);
        myLine->SetLineWidth(1);
        myLine->SetLineColorAlpha(600+1, 0.5);
        myLine->Draw();
// c1-Update();

 
 //////////////////////////////////////////////////////////////////////
 c1->Update();
 // c1->SaveAs(DirName+"BkgvsSig/" + Variable.Name + ".pdf");
 TString ofile("");
    if (AddCutTextDummy.EqualTo("")){
        ofile = outdir + Variable.Name + ".pdf";
    }
    else {
        ofile = outdir + Variable.Name + "AddCut.pdf";
    }
if (!ofile.EqualTo("")){
 c1->SaveAs(ofile);}

    delete h1;
    delete h2;
    delete hratio;
    delete pad1;
    delete pad2;
    delete pad3;
    delete c1;
}//end of main function


Open2Trees GetTrees(TString ifile1, TString ifile2){
    TFile* ifilename1;
    TFile* ifilename2;

    ifilename1 = new TFile(ifile1);
    ifilename2 = new TFile(ifile2);
    TTree *Tree1 = (TTree*)ifilename1->Get("T_mv");
    TTree *Tree2 = (TTree*)ifilename2->Get("T_mv");
    cout<<" Tree Entries: "<<Tree1->GetEntries()<<" " 
        << "from file"<< ifile1 <<endl;
    cout<<" Tree Entries: "<<Tree2->GetEntries()<<" " 
        << "from file"<< ifile2 <<endl;
    Open2Trees myTrees = {Tree1, Tree2};
return myTrees;
}

void VarEfficiencyRatios( TString RunMode = "", TString whichVar = ""){
clock_t start = clock();
SetAtlasStyle();

TString oDirName;
TString ifileMC_Run1, ifileData_Run1;
TString ifileMC_Run1privxmu, ifileData_Run1privxmu;
TString ifileMC_Run1_npvweights, ifileData_Run1_npvweights;
TString ifileMC_Run1nPV_npvweights, ifileData_Run1nPV_npvweights;
TString ifileMC_Custom, ifileData_Custom, ifileMC_Custom_mu, ifileData_Custom_mu;
TString idir = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/AnalysisNtuples2020/v4";
// oDirName = "/afs/cern.ch/user/a/agrummer/www/bmumu2020/SavePlots/VarEfficiencies/PUcomps2020July30/";
oDirName = "/afs/cern.ch/user/a/agrummer/www/bmumu2020/SavePlots/VarEfficiencies/PUcomps2020Aug7/";
TString TreeName = "T_mv";
//for Run1privxmu_round:
//Run 1 with run 2 close track:
ifileMC_Run1 = idir + "/"+ "LASTskim.user.agrummer.mcBsmumu.merged.2.NPVweight_BDT2020_out_Run1.root";
ifileData_Run1 = idir + "/" + "LASTskim.user.agrummer.Data1516.merged.2_BDT2020_out_Run1.root";
// oDirName = "/afs/cern.ch/user/a/agrummer/www/bmumu2020/SavePlots/VarEfficiencies/2020July17/mu2/";
ifileMC_Run1privxmu = idir + "/"+"LASTskim.user.agrummer.mcBsmumu.merged.2.NPVweight_BDT2020_out_Run1privxmu_round.root";
ifileData_Run1privxmu = idir + "/"+ "LASTskim.user.agrummer.Data1516.merged.2_BDT2020_out_Run1privxmu_round.root";
//isolation Custom
ifileMC_Custom = idir + "/"+"LASTskim.user.agrummer.mcBsmumu.merged.2.NPVweight_BDT2020_out_Custom.root";
ifileData_Custom = idir + "/"+ "LASTskim.user.agrummer.Data1516.merged.2_BDT2020_out_Custom.root";
//isolation Custom mu
ifileMC_Custom_mu = idir + "/"+"LASTskim.user.agrummer.mcBsmumu.merged.2.NPVweight_BDT2020_Custom_privxmu.root";
ifileData_Custom_mu = idir + "/"+ "LASTskim.user.agrummer.Data1516.merged.2_BDT2020_Custom_privxmu.root";
//for Run1nPV_npvweights: (also need to change the BDT cuts and MC weights, and for loop numbers)
// oDirName = "/afs/cern.ch/user/a/agrummer/www/bmumu2020/SavePlots/VarEfficiencies/2020July17/npv2/";
ifileMC_Run1nPV_npvweights = idir + "/"+ "LASTskim.user.agrummer.mcBsmumu.merged.2.NPVweight_BDT2020_out_Run1nPV_npvweights.root";
ifileData_Run1nPV_npvweights = idir + "/"+ "LASTskim.user.agrummer.Data1516.merged.2_BDT2020_out_Run1nPV_npvweights.root";
//Run with npv weights applied:
ifileMC_Run1_npvweights = idir + "/"+ "LASTskim.user.agrummer.mcBsmumu.merged.2.NPVweight_BDT2020_out_Run1_npvweights.root";
ifileData_Run1_npvweights = idir + "/" + "LASTskim.user.agrummer.Data1516.merged.2_BDT2020_out_Run1_npvweights.root";

BDTcuts Run1privxmu_roundCuts ={ 
    0.417643, // BDTCut18
    0.346076, // BDTCut36
    0.267268  // BDTCut54
};
BDTcuts CustomCuts={
    0.4418,
    0.3662,
    0.2774
};
BDTcuts Custom_mu_Cuts={
    0.4297,
    0.3562,
    0.2705
};
BDTcuts Run1nPV_npvweightsCuts = {
    0.420502, // BDTCut18
    0.348225, // BDTCut36
    0.26861   // BDTCut54
 };
BDTcuts run1Cuts = {
    0.429503, //BDTCut18
    0.353729, //BDTCut36
    0.272042  //BDTCut54
};
BDTcuts run1_npvweightsCuts = {
    0.428795, // BDTCut18
    0.355033, // BDTCut36
    0.273359  // BDTCut54
};
TCut MCweights = "PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf*CombWeights*Muon1_trigger_sf*Muon2_trigger_sf";
TCut MCweightsNPVweight = "NPVweight*PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf*CombWeights*Muon1_trigger_sf*Muon2_trigger_sf";
TCut noWeight = "";
TCut AddCut = "";
// TCut AddCut = "PRIVX_mu_round>25";
// TString whichVar("");
//without PU variable in training goes first:
ConfigStruct csMCmu = {ifileMC_Run1, ifileMC_Run1privxmu, oDirName, 
                        run1Cuts, Run1privxmu_roundCuts, AddCut, MCweights};
ConfigStruct csDatamu = {ifileData_Run1, ifileData_Run1privxmu, oDirName, 
                        run1Cuts, Run1privxmu_roundCuts, AddCut, noWeight};

ConfigStruct csMCcustom_mu = {ifileMC_Custom, ifileMC_Custom_mu, oDirName, 
                        CustomCuts, Custom_mu_Cuts, AddCut, MCweights};
ConfigStruct csDatacustom_mu = {ifileData_Custom, ifileData_Custom_mu, oDirName, 
                        CustomCuts, Custom_mu_Cuts, AddCut, noWeight};

ConfigStruct csMCcustom_mu_iso = {ifileMC_Custom, ifileMC_Custom_mu, oDirName, 
                        CustomCuts, Custom_mu_Cuts, AddCut, MCweights};
ConfigStruct csDatacustom_mu_iso = {ifileData_Custom, ifileData_Custom_mu, oDirName, 
                        CustomCuts, Custom_mu_Cuts, AddCut, noWeight};

ConfigStruct csMCnpv = {ifileMC_Run1_npvweights, ifileMC_Run1nPV_npvweights, oDirName, 
                        run1_npvweightsCuts, Run1nPV_npvweightsCuts, AddCut, MCweightsNPVweight};
ConfigStruct csDatanpv = {ifileData_Run1_npvweights, ifileData_Run1nPV_npvweights, oDirName, 
                        run1_npvweightsCuts, Run1nPV_npvweightsCuts, AddCut, noWeight};
ConfigStruct SetCS;
Open2Trees theTrees;
// TString whichBDTCut = "";
// TString whichSet="";

if (RunMode.Contains("All")) RunMode = "BkgSig183654";
int iBegin(0);
int iEnd(0);
// iBegin = 1;
// iEnd = 18;
if (whichVar.EqualTo("iso")){
iBegin = 0;
iEnd = 1;}
if (whichVar.EqualTo("npv")){
iBegin = 15;
iEnd = 16;}
if (whichVar.EqualTo("mu")){
iBegin = 16;
iEnd = 17;}
if (whichVar.EqualTo("muCustom")){
iBegin = 16;
iEnd = 17;}
if (RunMode.Contains("Bkg")){
    if (whichVar.EqualTo("mu")) SetCS = csDatamu;
    if (whichVar.EqualTo("npv")) SetCS = csDatanpv;
    if (whichVar.EqualTo("muCustom")) SetCS = csDatacustom_mu;
    if (whichVar.EqualTo("iso")) SetCS = csDatacustom_mu_iso;
    theTrees = GetTrees(SetCS.ifile1, SetCS.ifile2);
    if (RunMode.Contains("18")){
        for(int i = iBegin; i<iEnd; i++){
            mainCompare(InputVariables[i], SetCS, theTrees, "18", "Bkg");
    }}
    if (RunMode.Contains("36")){
        for(int i = iBegin; i<iEnd; i++){
            mainCompare(InputVariables[i], SetCS, theTrees, "36", "Bkg");
    }}
    if ((RunMode.Contains("54"))){
        for(int i = iBegin; i<iEnd; i++){
            mainCompare(InputVariables[i], SetCS, theTrees, "54", "Bkg");
    }}
}

if (RunMode.Contains("Sig")){
    if (whichVar.EqualTo("mu")) SetCS = csMCmu;
    if (whichVar.EqualTo("npv")) SetCS = csMCnpv;
    if (whichVar.EqualTo("muCustom")) SetCS = csMCcustom_mu;
    if (whichVar.EqualTo("iso")) SetCS = csMCcustom_mu_iso;
    theTrees = GetTrees(SetCS.ifile1, SetCS.ifile2);
    if (RunMode.Contains("18")){
        for(int i = iBegin; i<iEnd; i++){
            mainCompare(InputVariables[i], SetCS, theTrees, "18", "Sig");
    }}
    if (RunMode.Contains("36")){
        for(int i = iBegin; i<iEnd; i++){
            mainCompare(InputVariables[i], SetCS, theTrees, "36", "Sig");
    }}
    if (RunMode.Contains("54")){
        for(int i = iBegin; i<iEnd; i++){
            mainCompare(InputVariables[i], SetCS, theTrees, "54", "Sig");
    }}
}
std::cout << "Time taken in secs: " << (clock()-start) / (double) CLOCKS_PER_SEC <<endl;
return(0);
}//end of InputVars_v5_Efficiencies



