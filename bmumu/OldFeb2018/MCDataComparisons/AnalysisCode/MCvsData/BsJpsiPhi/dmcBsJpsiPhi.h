#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include "TCut.h"
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TF1.h"
#include "TFitResult.h"
#include "TFitResultPtr.h"
#include "TMath.h"
#include "Math/MinimizerOptions.h"
#include "TPad.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TInterpreter.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TCanvas.h"
#include "TMatrixDSym.h"
#include "TLine.h"
#include "TAxis.h"
#include "TROOT.h"
#include "TStyle.h"
#include "AtlasUtils.h"


// definitions used for data/MC comparison
// data period can be selected by run number in CutAdd

// DATA INPUT FILE
TString fdname = "/afs/cern.ch/user/i/ibragimo/public/forSergey/data16BsJpsiPhi_run302393.root";

// MC INPUT FILE
TString fmname = "/afs/cern.ch/user/i/ibragimo/public/forSergey/mc15BsJpsiPhi_puweight.root";

// TREE NAME in the output files above 
TString treename = "T_mv";

// OUTPUT FILES (with data/mc ratios)
TString outpath = "plots/BsJpsiPhi/";
TString ofilename = outpath+"DataMCRatioHistos.root";
TString tabname = outpath+"table_fitres.tex";

// MASS REGION USED FOR FITTING
Int_t BLowerMassCut=5166;//4966; //5266
Int_t BUpperMassCut=5566;//5766; //5466

// CUTS USED FOR Production of kinematic weights (optional)
TCut CutWeights;

// SIGNAL REGION
Double_t SRLow = 5316.0;
TCut CutSignalLow = Form("B_VTX_mass>=%f",SRLow);
Double_t SRHigh = 5416.0;
TCut CutSignalHigh = Form("B_VTX_mass<=%f",SRHigh);

TCut CutSR = CutSignalLow && CutSignalHigh;

// SIDEBANDS 

Double_t LSBLow = 5266.0;
TCut CutLSBLow = Form("B_VTX_mass>=%f",LSBLow); 
Double_t LSBHigh = 5316.0;
TCut CutLSBHigh = Form("B_VTX_mass<%f",LSBHigh);
Double_t RSBLow = 5416.0;
TCut CutRSBLow = Form("B_VTX_mass>%f",RSBLow);
Double_t RSBHigh = 5466;
TCut CutRSBHigh = Form("B_VTX_mass<=%f",RSBHigh);

TCut CutLSB = (CutLSBLow && CutLSBHigh);
TCut CutRSB = (CutRSBLow && CutRSBHigh);
TCut CutSB = CutLSB || CutRSB;

// ADDITIONAL CUTS
TCut CutAdd = "1==1";

// EXP USAGE IN BKG FIT FUNCTION
Bool_t useEXP = true;

// VARIABLES
struct VariableInfo{
  const char* name;
  Int_t nbins;
  Float_t XMin;
  Float_t XMax;
  Bool_t logScale;
  const char* axLabel;
  Bool_t usedForSystematics;
}Variables[]= {
  {"TMath::Abs(a_2D)",50,0,1.0,true,"|#alpha_{2D}| [rad]",true},
  //  {"TMath::Abs(a_3D)",60,0,1.5,true,"|#alpha_{3D}| [rad]",true},
  {"DR",30,0,1.5,true,"#DeltaR",true},
  {"Lxy",40,-0.5,3.5,false,"L_{xy} [mm]",true},
  {"chi2_PVSV_log2D",60,-6,12,false,"Log(#chi^{2}_{xy})",true},  
  {"TMath::Abs(d0Min_sig)",40,0.0,40.0,false,"|d_{0}|^{min} sig.",true},
  {"TMath::Abs(d0Max_sig)",50,0.0,50.0,false,"|d_{0}|^{max} sig.",true},
  {"B_iso_7_Chi2_5_LoosePt05",60,0.0,1.05,true,"B Isolation (I^{B}_{0.7, loose, pt>0.5})",true},
  {"B_iso_Ntracks_7_Chi2_5_LoosePt05",16,0,16,true,"Ntracks B Isolation (I^{B}_{0.7, loose, pt>0.5})",true},

  {"B_pT",-1,10000,100000,false,"p_{T}^{B} [GeV]",true},
  {"PlngMin2D",25,0,25,false,"P^{min}_{L} [GeV]",true},
  {"closeTrkNtrksChi2LoosePt05",60,0,60,true,"N^{clos}_{trk, loose, pt>0.5}",true},


  {"TMath::Abs(B_IDtrks_DCA)",80,0,0.4,true,"DOCA_{#mu#mu} [mm]",true}, 
  {"TMath::Abs(B_IDtrks_deltaPhi)",50,0.0,1.0,true,"|#Delta#phi_{#mu#mu}|",true},

  {"closeTrkDOCALoosePt05",40,0,2,true,"DOCA_{xtrk, loose, pt>0.5} [mm]",true},

  {"Bvtx3DIP",60,0,2.0,true,"|IP_{B}^{3D}|",true}, //0.6
  //  {"B_minChi2MuonsIPtoAnyPV",80,-10,10,false,"Log(#chi^{2}_{#mu,xPV})",true}, //n.y. implemented


  {"B_eta",-1,-3.0,3.0,false,"#eta^{B}",true},
  {"B_fitChi2NDF",24,0,6,false,"#chi^{2}_{B}/NDF",true},
  {"Npv",30,-0.5,29.5,false,"nPV",true},
  {"Lxy_sig",60,0,60,false,"BvtxLxy signif.",true},
  {"B_VTX_massErr",30,0,90,false,"#delta m_{J/#psi K} [MeV]",true},
  {"properTime_sig",65,-10,120,false,"ct significance",false}, //t_{prop} /#sigma_{tprop}"},

  {"B_VTX_mass",40,5080,5480,false,"m_{#mu#muK} [MeV]",false},
  {"B_VTX_mass/B_VTX_mass_err",100,0,600,false,"m_{J/#psi K} /#Deltam_{J/#psi K}",false},

  {"chi2_PVSV_log1Dz",52,-14,12,false,"Log(#chi^{2}_{z})",false},// (PV-BVtx)in z)"}, //40,-8,12,
  {"TMath::Abs(d0Min)",40,0.0,2.0,false,"|d_{0}|^{min} [mm]",false},
  {"TMath::Abs(d0Max)",60,0,3.0,true,"|d_{0}|^{max} [mm]",false},
  {"TMath::Abs(closeTrkDCA)",100,0,0.5,true,"|D_{xy}|^{min} [mm]",false}, //Distance in xy to the closest approach track [mm]"},
  {"PlngMax2D",40,0,40,false,"P^{max}_{L} [GeV]",false}, //not from full 2011 analysis!
  {"TMath::Abs(closeTrkZCA)",100,0,0.5,true,"|D_{z}|^{min} [mm]",false},



  {"B_iso_Ntracks_7_Chi2_5_MedPt05",25,0,25,false,"number of tracks in iso cone",false},
  {"B_pT_error",100,0,3000,false,"#delta p_{T}^{B} [MeV]",false},
 
  {"Lxy_err",60,0,0.6,false,"BvtxLxyErr",false},
  {"TMath::Abs(B_IDtrks_deltaEta)",28,0.0,1.4,true,"|#eta_{#mu1}-#eta_{#mu2}|",false},

  {"B_pT_sig",70,0,840,false,"p_{T}^{B} sig.",false}, //140
  {"BDT_bb_2012",80,-0.8,0.8,false,"BDT output",false}, //32,-0.8,0.8 //60,0.15,0.7

  {"UpdatedClassBDT",32,-0.8,0.8,false,"BDT output",false},

  {"muP_iso_Ntracks_7_chi2_5_medPt05",25,0,25,false,"N^{Iso 0.7, #mu+}_{trk}",false},
  {"muM_iso_Ntracks_7_chi2_5_medPt05",25,0,25,false,"N^{Iso 0.7, #mu-}_{trk}",false},
  {"muP_iso_7_chi2_5_medPt05",-1,0.0,1.1,false,"#mu+ Isolation (I^{#mu+}_{0.7})",false},
  {"muM_iso_7_chi2_5_medPt05",-1,0.0,1.1,false,"#mu- Isolation (I^{#mu-}_{0.7})",false}
};

Int_t nVar = sizeof(Variables)/sizeof(Variables[0]);

// RESULTS OF UBL FIT
struct bkg{
  double nTotBkgSR;
  double nTotBkgSRErr;
  double nPartBkgSR;
  double nPartBkgSRErr;
  double nContBkgSR;
  double nContBkgSRErr;
  double nContBkgLSB;
  double nContBkgLSBErr;
  double nContBkgRSB;
  double nContBkgRSBErr;
  double LowPt;
  double UpPt; 
};

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
