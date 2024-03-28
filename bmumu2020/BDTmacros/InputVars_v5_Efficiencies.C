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
//loose:
// TString iso = "B_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0008388608";
TString ctntrk = "closeTrkNtrksChi2";
//custom:
// TString ctntrk = "closeTrkNtrksChi2_T0134217728_LooSiHi1Pt05_f2dc2"
//loose:
// TString ctntrk = "closeTrkNtrksChi2_T0008388608_LooSiHi1Pt05_f2dc2"
// TString ctdoca = "TMath::Sqrt(pow(closeTrkDCA,2)+pow(closeTrkZCA,2))";
TString ctdoca = "closeTrkDOCA_3";
// TString ctdoca = "closeTrkDOCA";
//custom:
// TString ctdoca = "closeTrkDOCA_T0134217728_LooSiHi1Pt05_f2dc2";
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
    {iso     , 10 , 10 , 0.1   , 1.1    , "B Isolation (I^{B}_{0.7})" , true   , "f"}         ,
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

void mainCompare(VariableInfo, TTree*, TString, TString, TString);

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
return hret;
}

void InputVars_v5_Efficiencies( TString RunMode = ""){
clock_t start = clock();
SetAtlasStyle();

TString oDirName, filenameMC, filenameData;
TString DirNameMC = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/AnalysisNtuples2020/v4/";
TString DirNameData = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/AnalysisNtuples2020/v4/";
TString TreeName = "T_mv";
// TString filename1 = DirName + "/"+"LASTskim.mc16Bs_EVALcombo_Jun12.root";
// TString filename2 = DirNameData + "/"+"data1516Bs_EVALcombo_Jun12.root";
//for Run1privxmu_round:
// oDirName = "/afs/cern.ch/user/a/agrummer/www/bmumu2020/SavePlots/VarEfficiencies/2020July17/mu2/";
// filenameData = DirNameData + "/"+ "LASTskim.user.agrummer.Data1516.merged.2_BDT2020_out_Run1privxmu_round.root";
// filenameMC = DirNameMC + "/"+"LASTskim.user.agrummer.mcBsmumu.merged.2.NPVweight_BDT2020_out_Run1privxmu_round.root";
//for Run1nPV_npvweights: (also need to change the BDT cuts and MC weights, and for loop numbers)
// oDirName = "/afs/cern.ch/user/a/agrummer/www/bmumu2020/SavePlots/VarEfficiencies/2020July17/npv2/";
// filenameData = DirNameData + "/"+ "LASTskim.user.agrummer.Data1516.merged.2_BDT2020_out_Run1nPV_npvweights.root";
// filenameMC = DirNameMC + "/"+ "LASTskim.user.agrummer.mcBsmumu.merged.2.NPVweight_BDT2020_out_Run1nPV_npvweights.root";
//Run 1 with run 2 close track:
oDirName = "/afs/cern.ch/user/a/agrummer/www/bmumu2020/SavePlots/VarEfficiencies/2020July17/run1_axes/";
filenameData = DirNameData + "/" + "LASTskim.user.agrummer.Data1516.merged_BDT2020_out_Run1.root";
filenameMC = DirNameMC + "/"+ "LASTskim.user.agrummer.mcBsmumu.merged_BDT2020_out_Run1.root";
TFile* ifilename1;
TFile* ifilename2;

ifilename1 = new TFile(filenameMC);
ifilename2 = new TFile(filenameData);
TTree *TreeMC = (TTree*)ifilename1->Get(TreeName);
TTree *TreeData = (TTree*)ifilename2->Get(TreeName);
cout<<"TreeMC Entries: "<<TreeMC->GetEntries()<<endl;
cout<<"TreeData Entries: "<<TreeData->GetEntries()<<endl;

// TString whichBDTCut = "";
// TString whichSet="";

if (RunMode.Contains("All")) RunMode = "BkgSig183654";
int iBegin(0);
int iEnd(0);
// iBegin = 1;
// iEnd = 18;
iBegin = 15;
iEnd = 16;
if (RunMode.Contains("Bkg")){
    if (RunMode.Contains("18")){
        for(int i = iBegin; i<iEnd; i++){
            mainCompare(InputVariables[i], TreeData, "18", "Bkg", oDirName);
    }}
    if (RunMode.Contains("36")){
        for(int i = iBegin; i<iEnd; i++){
            mainCompare(InputVariables[i], TreeData, "36", "Bkg", oDirName);
    }}
    if ((RunMode.Contains("54"))){
        for(int i = iBegin; i<iEnd; i++){
            mainCompare(InputVariables[i], TreeData, "54", "Bkg", oDirName);
    }}
}

if (RunMode.Contains("Sig")){
    if (RunMode.Contains("18")){
        for(int i = iBegin; i<iEnd; i++){
            mainCompare(InputVariables[i], TreeMC, "18", "Sig", oDirName);
    }}
    if (RunMode.Contains("36")){
        for(int i = iBegin; i<iEnd; i++){
            mainCompare(InputVariables[i], TreeMC, "36", "Sig", oDirName);
    }}
    if (RunMode.Contains("54")){
        for(int i = iBegin; i<iEnd; i++){
            mainCompare(InputVariables[i], TreeMC, "54", "Sig", oDirName);
    }}
}
std::cout << "Time taken in secs: " << (clock()-start) / (double) CLOCKS_PER_SEC <<endl;
return(0);
}//end of InputVars_v5_Efficiencies

void mainCompare(VariableInfo Variable, TTree *Tree1, TString whichBDTCut = "", TString whichSet="", TString oDirName="./"){
 TCanvas* c1;
 TH1F *hist1Var;
 TH1F *hist1VarAllBDT;
 TH1F *hist2Var;
 TH1F *hist2VarAllBDT;
 TH1F *hist3;
 TH1F *hist4;
 Double_t yHeight;
 Double_t yHeightMin;
 Double_t yHeightMin1;
 Double_t yHeightMin2;
 Double_t yHeight1;
 Double_t yHeight2;
 TLegend* leg;
 TString histLeg;
 TString hist2Leg;
 TString hist3Leg;
 TString hist4Leg;
 Double_t sigTestCandidates;
 Double_t bkgTestCandidates;
 Double_t sigTrainCandidates;
 Double_t bkgTrainCandidates;
 Double_t kolS;
 Double_t kolB;
 TString tex3text;
 TLatex *tex3;

 cout<<Variable.Name<<endl;

if (whichBDTCut.Contains("18")){
     if (whichSet.Contains("Sig")) oDirName = oDirName + "SigBDT18/";
     if (whichSet.Contains("Bkg")) oDirName = oDirName + "BkgBDT18/";
}else if (whichBDTCut.Contains("36")){
     if (whichSet.Contains("Sig"))oDirName = oDirName + "SigBDT36/";
     if (whichSet.Contains("Bkg"))oDirName = oDirName + "BkgBDT36/";
}else if (whichBDTCut.Contains("54")){
     if (whichSet.Contains("Sig"))oDirName = oDirName + "SigBDT54/";
     if (whichSet.Contains("Bkg"))oDirName = oDirName + "BkgBDT54/";
}

 // Tree1->SetBranchAddress("BDT_bb_2016",&BDTvar1);
 
 // if (Variable.Name.Contains("TMath::Sqrt(pow(closeTrkDCA,2)+pow(closeTrkZCA,2))")){
 // Tree1->SetBranchAddress("closeTrkDCA",&myVar1f);
 // Tree1->SetBranchAddress("closeTrkZCA",&myVar1fsecond);
 // }
 // else if (Variable.dataType.Contains("f")){
 // Tree1->SetBranchAddress(Variable.Name,&myVar1f);}
 // else if(Variable.dataType.Contains("i")){
 // Tree1->SetBranchAddress(Variable.Name,&myVar1i);}
 // else{ Tree1->SetBranchAddress(Variable.Name,&myVar1);}
 
 c1 = new TCanvas("c1", "BDT Variable",0.,0., 800, 600);
 c1->cd(0);
 TPad *myPad = new TPad("pad_name","pad_name",0,0,1,1); 
        // pad1 = new TPad("pad1","pad1",0,0.33,1,1);
 myPad->Draw();
 if (Variable.logScale){
     myPad->SetLogy();
 }
 myPad->cd();
 Double_t BDTCutAll = -1;

 //June 12 new strategy
 // Double_t BDTCut18 = 0.424441;
 // Double_t BDTCut36 = 0.341969;
 // Double_t BDTCut54 = 0.258933;
 // //After addition of new data in July.
 // Double_t BDTCut18 = 0.4163;
 // Double_t BDTCut36 = 0.3312;
 // Double_t BDTCut54 = 0.2455;
// July 17, 2020:
 Double_t BDTCut18, BDTCut36, BDTCut54;
 // Run1privxmu_round:
 // BDTCut18 = 0.417643;
 // BDTCut36 = 0.346076;
 // BDTCut54 = 0.267268;
// Run1nPV_npvweights
 // BDTCut18 = 0.420502;
 // BDTCut36 = 0.348225;
 // BDTCut54 = 0.26861;
 //run1:
 // BDTCut18 = 0.429503;
 // BDTCut36 = 0.353729;
 // BDTCut54 = 0.272042;
 //run1_npvweights:
BDTCut18 = 0.428795;
BDTCut36 = 0.355033;
BDTCut54 = 0.273359;

 
 TCut BDTCut;
if (whichBDTCut.Contains("18")){
    BDTCut = Form("BDT_bb_2020>%f", BDTCut18);
}else if (whichBDTCut.Contains("36")){
    BDTCut = Form("BDT_bb_2020>%f", BDTCut36);
}else if (whichBDTCut.Contains("54")){
    BDTCut = Form("BDT_bb_2020>%f", BDTCut54);
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

TString Weights;
// TCut CutAdd = "Lxy>0.3";
TCut CutAdd = "";
if (whichSet.Contains("Sig")) Weights = "PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf*CombWeights*Muon1_trigger_sf*Muon2_trigger_sf";
// if (whichSet.Contains("Sig")) Weights = "NPVweight*PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf*CombWeights*Muon1_trigger_sf*Muon2_trigger_sf";
if (whichSet.Contains("Bkg")) Weights = "";


TCut FinalCut;
TCut FinalCutAllBDT;

if (whichSet.Contains("Sig")){
    FinalCut = BDTCut && CutAdd;
    FinalCutAllBDT = CutAdd;
}
if (whichSet.Contains("Bkg")) {
    FinalCut = BDTCut && CutAdd && CutSB;
    FinalCutAllBDT = CutAdd && CutSB;
}

TString hname = Variable.Name;
TString hnameAllBDT = Variable.Name + "FullBDT";
if (hname.Contains("(")){ 
    hname.ReplaceAll("(", "_");
    hnameAllBDT.ReplaceAll("(", "_");
    hname.ReplaceAll(")", "_");
    hnameAllBDT.ReplaceAll(")", "_");
    hname.ReplaceAll("::", "_");
    hnameAllBDT.ReplaceAll("::", "_");
}

hist1Var = getHistoFromTree(Tree1, whichSet, Variable, hname, FinalCut*Weights);
hist1VarAllBDT = getHistoFromTree(Tree1, whichSet, Variable, hnameAllBDT, FinalCutAllBDT*Weights);


 hist1Var->Sumw2();
 hist1Var->Divide(hist1VarAllBDT);
 if (whichSet.Contains("Sig")){ hist1Var->Draw("ehist");
    hist1Var->SetFillColor(632+1);
    hist1Var->SetLineColor(632+1);
}
 else if (whichSet.Contains("Bkg")){ hist1Var->Draw("ehist");
    hist1Var->SetFillColor(600+2);
    hist1Var->SetLineColor(600+2);
}
hist1Var->SetMarkerSize(0.);
hist1Var->SetMarkerStyle(21);
hist1Var->SetFillStyle(3003);

yHeight1 = hist1Var->GetMaximum();
yHeightMin1 = hist1Var->GetMinimum();

if(Variable.logScale) {
    yHeight1 = yHeight1*12.;
    // yHeight2 = yHeight2*12.;
}
else {
    yHeight1 = yHeight1*2;
    // yHeight2 = yHeight2*2;
}

if (!Variable.logScale) {
    hist1Var->GetYaxis()->SetRangeUser(yHeightMin1/1.5, yHeight1);
    // hist2Var->GetYaxis()->SetRangeUser(yHeightMin1/1.5, yHeight2);
    // hist1Var->GetYaxis()->SetRangeUser(0., 1.2);
    // hist1Var->GetYaxis()->SetRangeUser(0., 2e-3);
}
else {
    if (whichSet.Contains("Sig")){
    hist1Var->SetMaximum(5e1);
    hist1Var->SetMinimum(5e-6);
    }else{
    hist1Var->SetMaximum(5e-1);
    hist1Var->SetMinimum(5e-8);
    }
    // hist1Var->SetMaximum(yHeight1);
    // hist2Var->SetMaximum(yHeight2);
}

 if (whichSet.Contains("Sig")) {hist1Var->GetYaxis()->SetTitle("Efficiency");
     hist1Var->GetXaxis()->SetTitle(Variable.AxisName);
     histLeg = Form( "B_{s} #rightarrow #mu^{+} #mu^{-} MC");
}else{
    hist1Var->GetYaxis()->SetTitle("Efficiency");
    hist1Var->GetXaxis()->SetTitle(Variable.AxisName);
    // histLeg = Form( "2015 and 2016 sidebands");
    histLeg = Form( "Sidebands");
}

leg = new TLegend(0.265664, 0.802609, 0.466165, 0.884348, NULL,"brNDC");
leg->AddEntry(hist1Var, histLeg.Data(),"l");
leg->SetBorderSize(0);  // no border
leg->SetLineColor(0);
leg->SetFillColorAlpha(0, 0);
leg->SetTextSize(0.034468);
leg->Draw();
ATLASLabel(0.259398, 0.893913,"Internal",1);
 
TLatex *texBDT;

TString BDTLabel;
if (whichBDTCut.Contains("18"))      BDTLabel = Form( "BDT > %.4f", BDTCut18);
else if (whichBDTCut.Contains("36")) BDTLabel = Form( "BDT > %.4f", BDTCut36);
else if (whichBDTCut.Contains("54")) BDTLabel = Form( "BDT > %.4f", BDTCut54);
texBDT = new TLatex(0.67, 0.87,BDTLabel.Data());
texBDT->SetNDC();
texBDT->SetTextSize(0.06);
texBDT->SetTextFont(42);
// texNpv->SetLineWidth(2);
// texNpv->SetTextColor(color);
texBDT->Draw();

 
 
 //////////////////////////////////////////////////////////////////////
 
 if (Variable.Name.Contains("TMath::Sqrt(pow(closeTrkDCA,2)+pow(closeTrkZCA,2))")) Variable.Name.ReplaceAll("TMath::Sqrt(pow(closeTrkDCA,2)+pow(closeTrkZCA,2))","closeTrkDOCA");
 // //write:::
 c1->Update();
 // c1->SaveAs(DirName+"BkgvsSig/" + Variable.Name + ".pdf");
 
 c1->SaveAs(oDirName + Variable.Name + ".pdf");

    delete hist1VarAllBDT;
    delete hist1Var;
    delete myPad;
    delete c1;
}//end of main function




