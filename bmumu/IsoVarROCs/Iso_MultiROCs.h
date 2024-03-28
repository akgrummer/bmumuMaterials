// TString filename = "/Users/agrummer/Desktop/Bmumu/Output/Trees/LSFJOB_Trees500/bdt2016test_0.root";
// TString FilePath = "/Users/agrummer/cernbox/www/bmumu/myMVA/";
// TString ParameterName = "out2";
// TString filename = FilePath + ParameterName + "/"+"bdt2016test.root";
// TString filename = "/Users/agrummer/cernbox/www/bmumu/myMVA/out500/bdt2016test.root";
#include <math.h>
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

Double_t BDTvarBkg(0.0);
Double_t BDTvarSig(0.0);

Double_t CombWeights(0.0);
Double_t PVWeights(0.0);
Float_t Muon1_reco_eff_sf(0.0);
Float_t Muon2_reco_eff_sf(0.0);

vector <Double_t> bkgBDT;
vector <Double_t> sigBDT;
double B_MUCALC_massBkg;
double B_MUCALC_massSig;


TMultiGraph *mg;
TGraphAsymmErrors *gr1;

// void PlotBDTvariables(Float_t bkgBDTtest,
//                       Float_t sigBDTtest,
//                       Float_t bkgBDTtrain,
//                       Float_t sigBDTtrain);


// Double_t AidansKTest(Int_t na, const Double_t *a, Int_t nb, const Double_t *b, Option_t *option);
struct VariableInfo{
  const char* name;
  Int_t nbins;
  Float_t XMin;
  Float_t XMax;
  Bool_t logScale;
  const char* axLabel;
  Bool_t usedForSystematics;
  TString ZoomName;
  Bool_t Zoom;
  Double_t ZoomVal;
  Bool_t PlotOnlyMC;
  Double_t PullYmin;
  Double_t PullYmax;
};

VariableInfo Bisolation = {"B_iso_7_Chi2_5_LoosePt05",51,0.0,1.02,true,"I_{0.7}",false, "zoom", false, 0., false, 0., 3.5};
VariableInfo isoNtracks = {"B_iso_Ntracks_7_Chi2_5_LoosePt05",16,0,16,false,"Ntracks B Isolation (I^{B}_{0.7, loose, pt>0.5})",false, "zoom", false, 0., false, 0.6, 1.4};
// VariableInfo closeTrkDOCA = {"closeTrkDOCA",41,-0.05,2,true,"DOCA_{xtrk, loose, pt>0.5} [mm]",true, "zoom", false, 0., false, 0.5, 1.5};
VariableInfo closeTrkDOCA = {"closeTrkDOCA",63,-0.05,3.1,true,"DOCA_{xtrk, loose, pt>0.5} [mm]",true, "zoom", false, 0., false, 0.5, 1.5};
VariableInfo closeTrkNtrks = {"closeTrkNtrksChi2",60,0,60,true,"N^{clos}_{trk, loose, pt>0.5}",true, "zoom", false, 0., false, 0., 3.5};//added with new MC HLT_mu6_mu4_bBmumu_Lxy0
VariableInfo closeTrkNtrks_80 = {"closeTrkNtrksChi2",80,0,80,true,"N^{clos}_{trk, loose, pt>0.5}",true, "zoom", false, 0., false, 0., 3.5};//added with new MC HLT_mu6_mu4_bBmumu_Lxy0
VariableInfo Run1npv = {"Npv-1",40,-0.5,39.5,false,"nPV",true, "zoom", false, 0., false, 0.5, 3.};
VariableInfo Run1iso = {"B_iso_7_Chi2_5_MedPt05",51,0.0,1.02,true,"I_{0.7}",false, "zoom", false, 0., false, 0., 3.5};
VariableInfo Run1isoNTrks = {"B_iso_Ntracks_7_Chi2_5_MedPt05",16,0,16,true,"Ntracks B Isolation (I^{B}_{0.7, loose, pt>0.5})",false, "zoom", false, 0., false, 0.75, 1.25};
VariableInfo isoAlltracks = {"B_iso_7_Chi2_5_LoosePt05_AllTrks",51,0.0,1.02,true,"I_{0.7}",false, "zoom", false, 0., false, 0., 3.5};
VariableInfo isoNtrksAlltrks = {"B_iso_Ntracks_7_Chi2_5_LoosePt05_AllTrks",16,0,16,true,"Ntracks B Isolation (I^{B}_{0.7, loose, pt>0.5})",false, "zoom", false, 0., false, 0.75, 1.25};
VariableInfo closeTrkNtrks_AllTrks = {"closeTrkNtrksChi2_AllTrks",60,0,60,true,"N^{clos}_{trk, loose, pt>0.5}",true, "zoom", false, 0., false, 0., 3.5};//added with new MC HLT_mu6_mu4_bBmumu_Lxy0
VariableInfo closeTrkDOCA_AllTrks2 = {"closeTrkDOCA_AllTrks2",40,0,2,true,"DOCA_{xtrk, loose, pt>0.5} [mm]",true, "zoom", false, 0., false, 0.5, 1.5};

VariableInfo iso_AllTrks_Chi6 = {"B_iso_7_Chi2_5_LoosePt05_AllTrks_Chi6",51,0.0,1.02,true,"I_{0.7}",false, "zoom", false, 0., false, 0., 3.5};
VariableInfo isoNTrks_AllTrks_Chi6 = {"B_iso_Ntracks_7_Chi2_5_LoosePt05_AllTrks_Chi6",16,0,16,true,"Ntracks B Isolation (I^{B}_{0.7, loose, pt>0.5})",false, "zoom", false, 0., false, 0.75, 1.25};
VariableInfo iso_AllTrks_Chi5 = {"B_iso_7_Chi2_5_LoosePt05_AllTrks_Chi5",51,0.0,1.02,true,"I_{0.7}",false, "zoom", false, 0., false, 0., 3.5};
VariableInfo isoNTrks_AllTrks_Chi5 = {"B_iso_Ntracks_7_Chi2_5_LoosePt05_AllTrks_Chi5",16,0,16,true,"Ntracks B Isolation (I^{B}_{0.7, loose, pt>0.5})",false, "zoom", false, 0., false, 0.75, 1.25};
VariableInfo iso_AllTrks_Chi4 = {"B_iso_7_Chi2_5_LoosePt05_AllTrks_Chi4",51,0.0,1.02,true,"I_{0.7}",false, "zoom", false, 0., false, 0., 3.5};
VariableInfo isoNTrks_AllTrks_Chi4 = {"B_iso_Ntracks_7_Chi2_5_LoosePt05_AllTrks_Chi4",16,0,16,true,"Ntracks B Isolation (I^{B}_{0.7, loose, pt>0.5})",false, "zoom", false, 0., false, 0.75, 1.25};

VariableInfo iso_TTVA_loose = {"B_iso_7_Chi2_5_LoosePt05_TTVA_loose",51,0.0,1.02,true,"I_{0.7}",false, "zoom", false, 0., false, 0., 3.5};
VariableInfo isoNTrks_TTVA_loose = {"B_iso_Ntracks_7_Chi2_5_LoosePt05_TTVA_loose",16,0,16,true,"Ntracks B Isolation (I^{B}_{0.7, loose, pt>0.5})",false, "zoom", false, 0., false, 0.75, 1.25};
VariableInfo var_closeTrkNtrks_TTVA_loose = {"closeTrkNtrksChi2_TTVA_loose",60,0,60,true,"N^{clos}_{trk, loose, pt>0.5}",true, "zoom", false, 0., false, 0., 3.5};//added with new MC HLT_mu6_mu4_bBmumu_Lxy0
VariableInfo var_closeTrkDOCA_TTVA_loose = {"closeTrkDOCA_TTVA_loose",40,0,2,true,"DOCA_{xtrk, loose, pt>0.5} [mm]",true, "zoom", false, 0., false, 0.5, 1.5};
VariableInfo iso_TTVA_nominal = {"B_iso_7_Chi2_5_LoosePt05_TTVA_nominal",51,0.0,1.02,true,"I_{0.7}",false, "zoom", false, 0., false, 0., 3.5};
VariableInfo isoNTrks_TTVA_nominal = {"B_iso_Ntracks_7_Chi2_5_LoosePt05_TTVA_nominal",16,0,16,true,"Ntracks B Isolation (I^{B}_{0.7, loose, pt>0.5})",false, "zoom", false, 0., false, 0.75, 1.25};
VariableInfo var_closeTrkNtrks_TTVA_nominal = {"closeTrkNtrksChi2_TTVA_nominal",60,0,60,true,"N^{clos}_{trk, loose, pt>0.5}",true, "zoom", false, 0., false, 0., 3.5};//added with new MC HLT_mu6_mu4_bBmumu_Lxy0
VariableInfo var_closeTrkDOCA_TTVA_nominal = {"closeTrkDOCA_TTVA_nominal",40,0,2,true,"DOCA_{xtrk, loose, pt>0.5} [mm]",true, "zoom", false, 0., false, 0.5, 1.5};
VariableInfo iso_TTVA_tight = {"B_iso_7_Chi2_5_LoosePt05_TTVA_tight",51,0.0,1.02,true,"I_{0.7}",false, "zoom", false, 0., false, 0., 3.5};
VariableInfo isoNTrks_TTVA_tight = {"B_iso_Ntracks_7_Chi2_5_LoosePt05_TTVA_tight",16,0,16,true,"Ntracks B Isolation (I^{B}_{0.7, loose, pt>0.5})",false, "zoom", false, 0., false, 0.75, 1.25};
VariableInfo var_closeTrkNtrks_TTVA_tight = {"closeTrkNtrksChi2_TTVA_tight",60,0,60,true,"N^{clos}_{trk, loose, pt>0.5}",true, "zoom", false, 0., false, 0., 3.5};//added with new MC HLT_mu6_mu4_bBmumu_Lxy0
VariableInfo var_closeTrkDOCA_TTVA_tight = {"closeTrkDOCA_TTVA_tight",40,0,2,true,"DOCA_{xtrk, loose, pt>0.5} [mm]",true, "zoom", false, 0., false, 0.5, 1.5};
//
//Variables for June 27 studies 
VariableInfo B_Iso_TTVA_tight_c2 = {"B_Iso_TTVA_tight_c2",51,0.0,1.02,true,"I_{0.7}",false, "zoom", false, 0., false, 0., 3.5};
VariableInfo B_Iso_Ntracks_TTVA_tight_c2 = {"B_Iso_Ntracks_TTVA_tight_c2",16,0,16,true,"Ntracks B Isolation (I^{B}_{0.7, loose, pt>0.5})",false, "zoom", false, 0., false, 0.75, 1.25};
VariableInfo closeTrkNtrks_TTVA_tight_c1 = {"closeTrkNtrks_TTVA_tight_c1",60,0,60,true,"N^{clos}_{trk, loose, pt>0.5}",true, "zoom", false, 0., false, 0., 3.5};
VariableInfo closeTrkNtrks_TTVA_tight_c2 = {"closeTrkNtrks_TTVA_tight_c2",60,0,60,true,"N^{clos}_{trk, loose, pt>0.5}",true, "zoom", false, 0., false, 0., 3.5};
VariableInfo closeTrkDOCA_TTVA_tight_c7 = {"closeTrkDOCA_TTVA_tight_c7",41,-0.05,2,true,"DOCA_{xtrk, loose, pt>0.5} [mm]",true, "zoom", false, 0., false, 0.5, 1.5};
VariableInfo closeTrkDOCA_TTVA_tight_c2 = {"closeTrkDOCA_TTVA_tight_c2",41,-0.05,2,true,"DOCA_{xtrk, loose, pt>0.5} [mm]",true, "zoom", false, 0., false, 0.5, 1.5};
VariableInfo B_Iso_all_c5 = {"B_Iso_all_c5",51,0.0,1.02,true,"I_{0.7}",false, "zoom", false, 0., false, 0., 3.5};
VariableInfo B_Iso_Ntracks_all_c5 = {"B_Iso_Ntracks_all_c5",16,0,16,true,"Ntracks B Isolation (I^{B}_{0.7, loose, pt>0.5})",false, "zoom", false, 0., false, 0.75, 1.25};
VariableInfo B_Iso_all_c6 = {"B_Iso_all_c6",51,0.0,1.02,true,"I_{0.7}",false, "zoom", false, 0., false, 0., 3.5};
VariableInfo B_Iso_Ntracks_all_c6 = {"B_Iso_Ntracks_all_c6",16,0,16,true,"Ntracks B Isolation (I^{B}_{0.7, loose, pt>0.5})",false, "zoom", false, 0., false, 0.75, 1.25};
VariableInfo closeTrkNtrks_all_c1 = {"closeTrkNtrks_all_c1",60,0,60,true,"N^{clos}_{trk, loose, pt>0.5}",true, "zoom", false, 0., false, 0., 3.5};
VariableInfo closeTrkNtrks_all_c1_80 = {"closeTrkNtrks_all_c1",80,0,80,true,"N^{clos}_{trk, loose, pt>0.5}",true, "zoom", false, 0., false, 0., 3.5};
VariableInfo closeTrkNtrks_all_c2 = {"closeTrkNtrks_all_c2",60,0,60,true,"N^{clos}_{trk, loose, pt>0.5}",true, "zoom", false, 0., false, 0., 3.5};
VariableInfo closeTrkNtrks_all_c2_80 = {"closeTrkNtrks_all_c2",80,0,80,true,"N^{clos}_{trk, loose, pt>0.5}",true, "zoom", false, 0., false, 0., 3.5};
// VariableInfo closeTrkDOCA_all_c7 = {"closeTrkDOCA_all_c7",41,-0.05,2,true,"DOCA_{xtrk, loose, pt>0.5} [mm]",true, "zoom", false, 0., false, 0.5, 1.5};
VariableInfo closeTrkDOCA_all_c7 = {"closeTrkDOCA_all_c7",63,-0.05,3.1,true,"DOCA_{xtrk, loose, pt>0.5} [mm]",true, "zoom", false, 0., false, 0.5, 1.5};
// VariableInfo closeTrkDOCA_all_c2 = {"closeTrkDOCA_all_c2",41,-0.05,2,true,"DOCA_{xtrk, loose, pt>0.5} [mm]",true, "zoom", false, 0., false, 0.5, 1.5};
VariableInfo closeTrkDOCA_all_c2 = {"closeTrkDOCA_all_c2",63,-0.05,3.1,true,"DOCA_{xtrk, loose, pt>0.5} [mm]",true, "zoom", false, 0., false, 0.5, 1.5};
//July18:
VariableInfo B_Iso_TTVA_custom = {"B_Iso_TTVA_custom",51,0.0,1.02,true,"I_{0.7}",false, "zoom", false, 0., false, 0., 3.5};
VariableInfo B_Iso_TTVA_custom_dr = {"B_Iso_TTVA_custom_dr",51,0.0,1.02,true,"I_{0.7}",false, "zoom", false, 0., false, 0., 3.5};
VariableInfo B_Iso_TTVA_loose_dr = {"B_Iso_TTVA_loose_dr",51,0.0,1.02,true,"I_{0.7}",false, "zoom", false, 0., false, 0., 3.5};
VariableInfo closeTrkNtrks_TTVA_custom_c1 = {"closeTrkNtrks_TTVA_custom_c1",60,0,60,true,"N^{clos}_{trk, loose, pt>0.5}",true, "zoom", false, 0., false, 0., 3.5};
VariableInfo closeTrkNtrks_TTVA_custom_c1_80 = {"closeTrkNtrks_TTVA_custom_c1",80,0,80,true,"N^{clos}_{trk, loose, pt>0.5}",true, "zoom", false, 0., false, 0., 3.5};
VariableInfo closeTrkNtrks_TTVA_custom_c2 = {"closeTrkNtrks_TTVA_custom_c2",60,0,60,true,"N^{clos}_{trk, loose, pt>0.5}",true, "zoom", false, 0., false, 0., 3.5};
VariableInfo closeTrkNtrks_TTVA_custom_c2_80 = {"closeTrkNtrks_TTVA_custom_c2",80,0,80,true,"N^{clos}_{trk, loose, pt>0.5}",true, "zoom", false, 0., false, 0., 3.5};
VariableInfo closeTrkNtrks_TTVA_loose_c2 = {"closeTrkNtrks_TTVA_loose_c2",60,0,60,true,"N^{clos}_{trk, loose, pt>0.5}",true, "zoom", false, 0., false, 0., 3.5};
VariableInfo closeTrkNtrks_TTVA_loose_c2_80 = {"closeTrkNtrks_TTVA_loose_c2",80,0,80,true,"N^{clos}_{trk, loose, pt>0.5}",true, "zoom", false, 0., false, 0., 3.5};
// VariableInfo closeTrkDOCA_TTVA_custom_c7 = {"closeTrkDOCA_TTVA_custom_c7",41,-0.05,2,true,"DOCA_{xtrk, loose, pt>0.5} [mm]",true, "zoom", false, 0., false, 0.5, 1.5};
VariableInfo closeTrkDOCA_TTVA_custom_c7 = {"closeTrkDOCA_TTVA_custom_c7",63,-0.05,3.1,true,"DOCA_{xtrk, loose, pt>0.5} [mm]",true, "zoom", false, 0., false, 0.5, 1.5};
VariableInfo closeTrkDOCA_TTVA_loose_c7 = {"closeTrkDOCA_TTVA_loose_c7",63,-0.05,3.1,true,"DOCA_{xtrk, loose, pt>0.5} [mm]",true, "zoom", false, 0., false, 0.5, 1.5};
// VariableInfo closeTrkDOCA_TTVA_custom_c2 = {"closeTrkDOCA_TTVA_custom_c2",41,-0.05,2,true,"DOCA_{xtrk, loose, pt>0.5} [mm]",true, "zoom", false, 0., false, 0.5, 1.5};
VariableInfo closeTrkDOCA_TTVA_custom_c2 = {"closeTrkDOCA_TTVA_custom_c2",63,-0.05,3.1,true,"DOCA_{xtrk, loose, pt>0.5} [mm]",true, "zoom", false, 0., false, 0.5, 1.5};


// VariableInfo isoAlltracks = {"B_iso_7_Chi2_5_LoosePt05_Aidan",51,0.0,1.02,true,"I_{0.7}",false, "zoom", false, 0., false, 0., 3.5};
// VariableInfo isoNtrksAlltrks = {"B_iso_Ntracks_7_Chi2_5_LoosePt05_Aidan",16,0,16,true,"Ntracks B Isolation (I^{B}_{0.7, loose, pt>0.5})",false, "zoom", false, 0., false, 0.75, 1.25};
// VariableInfo closeTrkNtrks_AllTrks = {"closeTrkNtrksChi2_Aidan",60,0,60,true,"N^{clos}_{trk, loose, pt>0.5}",true, "zoom", false, 0., false, 0., 3.5};//added with new MC HLT_mu6_mu4_bBmumu_Lxy0
// VariableInfo closeTrkDOCA_AllTrks2 = {"closeTrkDOCA_Aidan",40,0,2,true,"DOCA_{xtrk, loose, pt>0.5} [mm]",true, "zoom", false, 0., false, 0.5, 1.5};
// SPECIAL HISTOGRAMS WITH VARIABLE BINNING FOR SOME VARIABLES
const Int_t nBinsIso = 16;
Float_t xBinIso[nBinsIso]={0.0,0.3,0.45,0.55,0.625,0.7,0.75,0.8,0.84,0.88,0.92,0.95,0.975,0.99,1.01,1.05};
TH1F* hdummyIso = new TH1F("","" ,nBinsIso-1, xBinIso);
const Int_t nBinsLxy = 18;
Float_t xBinLxy[nBinsLxy]={-3.0,0.0,0.3,0.8,1.3,1.8,2.3,2.8,3.3,3.9,4.6,5.4,6.2,7.2,8.8,11.0,14.0,18.0}; //-0.5
TH1F* hdummyLxy = new TH1F("","" ,nBinsLxy-1, xBinLxy);
const Int_t nBinsClassBDT = 18;
Float_t xBinClassBDT[nBinsClassBDT]={-0.6,-0.3,-0.2,-0.1,-0.05,0.0,0.05,0.1007,0.1050,0.1135,0.115,0.1220,0.1262,0.1347,0.15,0.2,0.3,0.4};
TH1F* hdummyClassBDT = new TH1F("","" ,nBinsClassBDT-1, xBinClassBDT);
const Int_t nBinsPt = 33;
Float_t xBinPt[nBinsPt]={8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 68, 70, 76, 100};
TH1F* hdummyPt = new TH1F("","" ,nBinsPt-1, xBinPt);
const Int_t nBinsEta = 51;
Float_t xBinEta[nBinsEta]={-2.5, -2.4, -2.3, -2.2, -2.1, -2, -1.9, -1.8, -1.7, -1.6, -1.5, -1.4, -1.3, -1.2, -1.1, -1, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1, 0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2, 2.1, 2.2, 2.3, 2.4, 2.5};
TH1F* hdummyEta = new TH1F("","" ,nBinsEta-1, xBinEta);

// TCut CutAdd = "Trigger_Matched";//"1==1";//Lxy>0.3
//trigger_matched is included in the final skim code
TCut CutAdd = "";//"1==1";//Lxy>0.3

// SIGNAL REGION
Double_t SRLow = 5066.0;
TCut CutSignalLow = Form("B_MUCALC_mass>=%f",SRLow);
Double_t SRHigh = 5666.0;
TCut CutSignalHigh = Form("B_MUCALC_mass<=%f",SRHigh);

TCut CutSR = CutSignalLow && CutSignalHigh;

// SIDEBANDS 
//with a gap//w/o gap
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
TCut CutRun1 = CutSB && "Lxy>0. && a_2D<1.0 && DR<1.5 &&BDT_fakeMuon_1>-0.458 && BDT_fakeMuon_2>-0.458 && isCatN3";
TCut CutRun1dummy = CutRun1;

vector<int>  ColorWheel = {632, 600+2, 400+2, 432+2, 616+2,
  632-3, 416-3, 600-3, 400-3, 616-3, 432-3, 800+2, 820+2, 840+2, 860+2, 880+2, 900+2};
