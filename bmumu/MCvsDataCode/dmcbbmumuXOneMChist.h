#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include "TCut.h"
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
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

// definitions used for data/MC comparison
// data period can be selected by run number in CutAdd

// DATA INPUT FILE
//TString fdname = "user.agrummer.12302533._000001.Topo_BsJpsiPhi.root"; //"data16Bs_Lxy0.root";//"v_dt.root"; //data
//TString fdname = "user.agrummer.12302533._000001.Topo_Bmumu.root"; //"data16Bs_Lxy0.root";//"v_dt.root"; //data
//TString fdname = "skim.Data";
//TString fdname = "output_829096.root";

//Two datasets "Main" and "Main with delayed"
TString fdnameMain = "/Users/agrummer/Desktop/Bmumu/dataMCcomparisons/AnalysisCode/MCvsData/bbmumuX/LASTskim.user.acampove.BPHY8_201709.NTUP.Data_Main_001_Bmumu_Blinded.root";
// TString fdname = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimFeb11/LASTskim.Data_ALLMain_11Feb.root";
// TString fdname = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskim.Data_2016Main_11Feb.root";
// TString fdname = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskim.Data_2016Main_11Feb_toomany.root";
// TString fdname = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimFeb13/LASTskim.mc16_13TeV.300307.HLT_mu6_mu4_bBmumu.Feb14.root";
//B_VTX_mass // // TString fdname = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimB_VTX_mass/LASTskim.Data_2015HLTand2016HLTLxy_Main_B_VTX_mass.root";

// TString fdname = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimFeb13/LASTskim.Data_2015HLTand2016HLTLxy_Main_15Feb.root";
TString fdname = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimFeb13/LASTskim.Data_2015HLTand2016HLTLxy_Main_15Feb_SepCoarse.root";
// TString fdname = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimFeb13/LASTskim.Data_2015HLTand2016HLTLxy_Main_15Feb_SepPeriods.root";

TString fdnameMWD = "LASTskim.user.acampove.BPHY8_201709.NTUP.Data_Main_With_Delayed_Available_001_Bmumu_Blinded.root";
// TString fdname = "~/Desktop/Bmumu/dataMCcomparisons/SeparatePeriods/small.root";
// TString fdname;

TString fdnameSP2016MWD = "~/Desktop/Bmumu/dataMCcomparisons/SeparatePeriods/MainWithDelayedPeriods2016_Blinded.root";
TString fdnameSP2016M = "~/Desktop/Bmumu/dataMCcomparisons/SeparatePeriods/MainPeriods2016_Blinded.root";
TString fdnameSP2015M = "~/Desktop/Bmumu/dataMCcomparisons/SeparatePeriods/MainPeriods2015_Blinded.root";

TString DataYear;

TFile *ifilename;
TList* listofkeys;
vector <TString> treenames;//initialize vector for inserting treenames (corresponds to periods in file - if separated)
vector <TChain*> chains;//initialize a vector of TChains
vector <TString> FileNames;
vector <int> NumberOfTrees ={0};//let first entry be zero for the loop which adds the correct file based of tree index


//TString fdname = "user.agrummer.12302533._000002.Topo_Bmumu.root";

// MC INPUT FILE
// TString fmname = "bmumuxBs.root";//"v_mc.root";// bmumuxBs.root is a background MC
// TString fmname = "bmumuxBs_w_HLT_mu6_mu4_bBmumu_Lxy0.root";
//last one, feb 11:
// TString fmname = "bmumuxBs_w_HLT_mu6_mu4_bBmumu_Lxy0_testweight2.root";
//updated to: (feb 11)
// TString fmname = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskim.MC16_bbmumuX2Bsmumu.root";
// TString fmname = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimFeb11/LASTskim.mc16_13TeV.300307.Pythia8B_A14_CTEQ6L1_bb_mu3p5mu3p5_Py8RepDec_4to6p5GeV.deriv.NTUP_SKIMMED_BPHY8.e6179_e5984_a875_r9364_r9315_p3371_Bmumu.root";
//B_VTX_mass // // TString fmname = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimB_VTX_mass/LASTskim.mc16_13TeV.300307.HLT_mu6_mu4_bBmumu_Lxy0.Feb15_B_VTX_mass.root";
// TString fmname = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimFeb13/LASTskim.mc16_13TeV.300307.HLT_mu6_mu4_bBmumu_Lxy0.Feb14_testweight.root";
TString fmname = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimFeb13/LASTskim.bbmumuX2Bsmumu_GBRweight.root";
TString fmname2 = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimFeb13/LASTskim.mc16_13TeV.300307.HLT_mu6_mu4_bBmumu.Feb15.root";
// TString fmname = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimFeb11/LASTskim.mc16_13TeV.300307_Bmumu_Blinded_Feb12.root";
// TREE NAME in the output files above 
// char treename[] = "T_mv";
// char *periodSelect;
// char *fdtreename;
// char dtlabelINITIAL[] ="2016 data period ";
// const char *dtlabel = "";

// TString treename = "T_mv";
// TString periodSelect;
TString fdtreename = "T_mv";
TString dtlabelINITIAL ="Data";
TString dtlabel="Data";

// std::string fdtreename;
//  fdtreename = "T_mv"+"_A";
// fdtreename += "_A";
TString fmtreename = "T_mv";


// OUTPUT FILES (with data/mc ratios)
TString outpath = "./OutputPlots/";//"plots/bbmumuX/";
TString ofilename = outpath+"DataMCRatioHistos.root";
TString tabname = outpath+"table_fitres_Full.tex";

// MASS REGION USED FOR FITTING
Int_t BLowerMassCut=4766.0;
Int_t BUpperMassCut=5966.0;

// CUTS USED FOR Production of kinematic weights (optional)
TCut CutWeights;

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

// ADDITIONAL CUTS
TCut CutBKin = "B_pT>8000. && TMath::Abs(B_eta)<2.5";
TCut CutMuKin = "B_IDtrk1_pT>4000. && TMath::Abs(B_IDtrk1_eta)<2.5 && B_IDtrk2_pT>4000. && TMath::Abs(B_IDtrk2_eta)<2.5 && Muon1_isCombinedMuon==1 && Muon2_isCombinedMuon==1";
TCut CutTruthMuKin = "TRUTH_MuPlus_pT>3500. && TMath::Abs(TRUTH_MuPlus_eta)<2.5 && TRUTH_MuMinus_pT>3500. && TMath::Abs(TRUTH_MuMinus_eta)<2.5";
TCut CutBase =  CutBKin && CutMuKin && CutTruthMuKin && "B_fitChi2NDF<6.0";

// TCut CutAdd = "Lxy>0.3 && TMath::Abs(Muon1_eta) < 1.05 && TMath::Abs(Muon2_eta) < 1.05";//"1==1";//Lxy>0.3
// TCut CutAdd = "Lxy>0.3 && TMath::Abs(Muon1_eta) > 1.05 && TMath::Abs(Muon1_eta) < 2.4 && TMath::Abs(Muon2_eta) > 1.05 && TMath::Abs(Muon2_eta) < 2.4";//"1==1";//Lxy>0.3
TCut CutAdd = "Lxy>0.3";//"1==1";//Lxy>0.3

// EXP USAGE IN BKG FIT FUNCTION
Bool_t useEXP = false;

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
  // {"d0Min_sig",80,-40.,40.0,false,"d_{0}^{min} sig.",true},//data in root file is already abs for d0 sig
  // {"d0Max_sig",100,-50.,50.0,false,"d_{0}^{max} sig.",true},
  {"B_iso_7_Chi2_5_LoosePt05",60,0.0,1.05,true,"B Isolation (I^{B}_{0.7, loose, pt>0.5})",true},
  {"B_iso_Ntracks_7_Chi2_5_LoosePt05",16,0,16,true,"Ntracks B Isolation (I^{B}_{0.7, loose, pt>0.5})",true},

  //  {"B_pT",-1,10000,100000,true,"p_{T}^{B} [GeV]",true},
  {"B_pT",70,5,40,true,"p_{T}^{B} [GeV]",true},
  {"PlngMin2D",25,0,25,false,"P^{min}_{L} [GeV]",true},
  // {"closeTrkNtrksChi2LoosePt05",60,0,60,true,"N^{clos}_{trk, loose, pt>0.5}",false}, //Aidan set to false - not in data files
  {"closeTrkNtrksChi2",60,0,60,true,"N^{clos}_{trk, loose, pt>0.5}",true},//added with new MC HLT_mu6_mu4_bBmumu_Lxy0




  {"TMath::Abs(B_IDtrks_DCA)",80,0,0.4,true,"DOCA_{#mu#mu} [mm]",true}, 
  {"TMath::Abs(B_IDtrks_deltaPhi)",70,0.0,1.4,true,"|#Delta#phi_{#mu#mu}|",true},
  {"closeTrkDOCALoosePt05",40,0,2,true,"DOCA_{xtrk, loose, pt>0.5} [mm]",false}, //Aidan set to false - not in data files

  {"Bvtx3DIP",60,0,2.0,true,"|IP_{B}^{3D}|",true}, //0.6
  //  {"B_minChi2MuonsIPtoAnyPV",80,-10,10,false,"Log(#chi^{2}_{#mu,xPV})",true}, //n.y implemented


  {"B_eta",-1,-3.0,3.0,false,"#eta^{B}",true},
  {"B_fitChi2NDF",24,0,6,false,"#chi^{2}_{B}/NDF",true},
  {"Npv",30,-0.5,29.5,false,"nPV",true},
  {"Lxy_sig",80,0,80,false,"BvtxLxy signif.",true},
  {"B_MUCALC_massErr",40,30,130,false,"#delta m_{#mu#mu} [MeV]",true},
  {"properTime_sig",65,-10,120,true,"ct significance",true},
  {"properTime",90,0,15,true,"ct",true},
  {"PRIVX_mu",35,0,35,false,"#mu PRIVX",true},

  {"B_MUCALC_mass",60,4766,5966,false,"m_{#mu#mu} [MeV]",true},
  {"B_MUCALC_mass/B_MUCALC_massErr",100,0,600,false,"m_{#mu#mu} /#Deltam_{#mu#mu}",false},


  {"Muon1_etcone30",220,-20000,200000,true,"Muon1_etcone30",false},
  {"Muon2_etcone30",220,-20000,200000,true,"Muon2_etcone30",false},
  {"Muon1_etcone40",220,-20000,200000,true,"Muon1_etcone40",false},
  {"Muon2_etcone40",220,-20000,200000,true,"Muon2_etcone40",false},
  {"Muon1_nucone30",200,0,200,true,"Muon1_nucone30",false},
  {"Muon2_nucone30",200,0,200,true,"Muon2_nucone30",false},
  {"Muon1_nucone40",200,0,200,true,"Muon1_nucone40",false},
  {"Muon2_nucone40",200,0,200,true,"Muon2_nucone40",false},


  {"B_PV_Ref_z",40,-200,200,false,"B_PV_ref_z",true},

  {"chi2_PVSV_log1Dz",52,-14,12,false,"Log(#chi^{2}_{z})",false},
  {"DecayCoplanarity",120,0,12000,true,"coplan._{#Deltax,#mu1,#mu2}",false},
  {"MuSignedd0SigMin",200,-50,150,false,"sd_{0}^{min} signif.",false},
  {"CoplanaritywithZ",180,0,18000,true,"coplan._{#Deltax,#mu#mu,z}",false},
  {"BvtxDXSig",70,0,140,false,"|#Deltax_{3D}| signif.",false},
  {"BvtxDXSig2D",70,0,140,false,"|#Deltax_{2D}| signif.",false},
  {"PlngMax2D",40,0,40,false,"P^{max}_{L} [GeV]",false},
  {"B_iso_Ntracks_7_Chi2_5_MedPt05",25,0,25,false,"number of tracks in iso cone",false},
  {"BDT_bb_2012",80,-0.8,0.8,false,"BDT output",false},



  {"B_iso_Ntracks_7_Chi2_5_MedPt05",25,0,25,false,"number of tracks in iso cone",false},
  {"B_pT_error",100,0,3000,false,"#delta p_{T}^{B} [MeV]",false},
 
  {"Lxy_err",60,0,0.6,true,"BvtxLxyErr",true},

  {"TMath::Abs(d0Min)",40,0.0,2.0,true,"|d_{0}|^{min} [mm]",true},
  {"TMath::Abs(d0Max)",60,0,3.0,true,"|d_{0}|^{max} [mm]",true},
  // {"d0Min",80,-1.0,1.0,true,"d_{0}^{min} [mm]",true},
  // {"d0Max",120,-3.0,3.0,true,"d_{0}^{max} [mm]",true},
  {"d0Min",80,-.4,.4,true,"d_{0}^{min} [mm]",true},
  {"d0Max",120,-.6,.6,true,"d_{0}^{max} [mm]",true},
  // {"d0Min",80,-.2,.2,true,"d_{0}^{min} [mm]",true},
  // {"d0Max",120,-.3,.3,true,"d_{0}^{max} [mm]",true},
  {"d0Min_err",40,0.0,0.1,true,"d_{0}^{min} err. [mm]",true},
  {"d0Max_err",60,0.0,0.15,true,"d_{0}^{max} err. [mm]",true},
  // {"TMath::Abs(closeTrkDCA)",100,0,0.5,true,"|D_{xy}|^{min} [mm]",false},
  // {"TMath::Abs(closeTrkZCA)",100,0,0.5,true,"|D_{z}|^{min} [mm]",false},
  // {"TMath::Abs(closeTrkDCA)",100,0,0.5,true,"|D_{xy}|^{min} [mm]",true},//added with new MC HLT_mu6_mu4_bBmumu_Lxy0
  // {"TMath::Abs(closeTrkZCA)",100,0,0.5,true,"|D_{z}|^{min} [mm]",true},//added with new MC HLT_mu6_mu4_bBmumu_Lxy0


  {"TMath::Abs(B_IDtrks_deltaEta)",28,0.0,1.4,true,"|#eta_{#mu1}-#eta_{#mu2}|",true},
  {"TMath::Sqrt(pow(B_IDtrks_deltaEta, 2) + pow(B_IDtrks_deltaPhi, 2))", 28,0.0,1.4,true,"|#Delta R_{#mu #mu}|",true},
  {"B_pT_sig",70,0,840,false,"p_{T}^{B} sig.",false}, //140
  {"BDT_bb_2012",80,-0.8,0.8,false,"BDT output",false}, //32,-0.8,0.8 //60,0.15,0.7

  {"UpdatedClassBDT",32,-0.8,0.8,false,"BDT output",false},

  {"muP_iso_Ntracks_7_chi2_5_medPt05",25,0,25,false,"N^{Iso 0.7, #mu+}_{trk}",false},
  {"muM_iso_Ntracks_7_chi2_5_medPt05",25,0,25,false,"N^{Iso 0.7, #mu-}_{trk}",false},
  {"muP_iso_7_chi2_5_medPt05",-1,0.0,1.1,false,"#mu+ Isolation (I^{#mu+}_{0.7})",false},
  {"muM_iso_7_chi2_5_medPt05",-1,0.0,1.1,false,"#mu- Isolation (I^{#mu-}_{0.7})",false},

{"Muon1_eta",-1,-3.0,3.0,false, "#eta_{#mu_{1}}", true},
{"Muon1_pT",100,0,50,true,"p_{T}^{#mu_{1}} [GeV]", true},
// {"Muon1_pT",-1,10000,100000,true,"p_{T}^{#mu_{1}} [GeV]",true},
{"Muon2_eta",-1,-3.0,3.0,false, "#eta_{#mu_{2}}", true},
{"Muon2_pT",100,0,50,true,"p_{T}^{#mu_{2}} [GeV]", true},
{"B_VTX_mass",60,4766,5966,false,"m_{#mu#mu} [MeV]",true},
{"B_VTX_massErr",40,30,430,false,"#delta m_{#mu#mu} [MeV]",true},
{"B_minChi2MuonsIPtoAnyPV",80,-10,10,false,"Log(#chi^{2}_{#mu,xPV})",true},
{"TMath::Sqrt(pow(closeTrkDCA,2)+pow(closeTrkZCA,2))",40,0,2,true,"DOCA_{xtrk, loose, pt>0.5} [mm]",true}
// {"closeTrkDOCA",40,0,2,true,"DOCA_{xtrk, loose, pt>0.5} [mm]",false}
// {"Muon2_pT",70,0,35,true, "#p_{T}^{#mu_{2}}", true}
// {"Muon2_pT",-1,10000,100000,true,"#p_{T}^{#mu_{2}}", true}

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
