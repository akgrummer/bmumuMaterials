//
//
// This ROOT macro computes BDT classifier (per event) for a
// flat ntuple file specified at the beginning of the macro.
// Flat ntuple file must contain all
// BDT input variables. Variable names expected to be as in the
// official flat ntuples.
// xml BDT weight file must be also specified at the beginning
// of the macro. For the xml file name
// everything that preceeds "_ABDT.weights.xml" is interpreted
// as a BDT training method. That substring is used to append
// output file name, which is cloned from the input file name.
// The output file will contain additional variable,
// "BDT_bb_2012", which is a new classifier corresponding
// to the xml weights given.
//
// WARNING 1: not all variables are written out, only those with intree->SetBranchStatus("VARIABLE",1);
// to quickly disable this feature comment out the line:
// intree->SetBranchStatus("*",0);
//
// WARNING 2: watch for type of variables in the ntuple, cast if necessary
//
// to RUN:
// change path to the xml file
// .L addClassBDT_Run2.C++
// addClassBDT_Run2("file_BDT_weights_to_be_applied_to")
//
//or run with: 
//root -l addClassBDT_Run2.C"(\"file_BDT_weights_to_be_applied_to\")"
//root -l -q addClassBDT_Run2.C"(\"/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/SignalMC/LASTskim.MC16Bs_CombWeights_DOCAlt500_EvalSet.root\")"
//root -l -q addClassBDT_Run2.C"(\"/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimRightSideband/LASTskim.Data_2015HLTand2016HLTLxy_RightSideband_DOCAlt500.root\")"
//
//may29
//for ROC check with BDT applied to bbmumuX MC (instead of right sideband)
//root -l addClassBDT_Run2.C"(\"/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkimGBR4_Mar26/LASTskim.bbmumuX2Bsmumu_combinatorial_GBRweight_DOCAlt500_LowPileUp2.root\")"
//root -l addClassBDT_Run2.C"(\"/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkimGBR4_Mar26/LASTskim.bbmumuX2Bsmumu_combinatorial_GBRweight_DOCAlt500_MiddlePileUp2.root\")"
//root -l addClassBDT_Run2.C"(\"/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkimGBR4_Mar26/LASTskim.bbmumuX2Bsmumu_combinatorial_GBRweight_DOCAlt500_HighPileUp2.root\")"
//eval
//root -l addClassBDT_Run2.C"(\"/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/SignalMC/LASTskim.MC16Bs_CombWeights_DOCAlt500_EvalSet_LowPileUp2.root\")"
//root -l addClassBDT_Run2.C"(\"/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/SignalMC/LASTskim.MC16Bs_CombWeights_DOCAlt500_EvalSet_MiddlePileUp2.root\")"
//root -l addClassBDT_Run2.C"(\"/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/SignalMC/LASTskim.MC16Bs_CombWeights_DOCAlt500_EvalSet_HighPileUp2.root\")"
//rightsideband
//root -l addClassBDT_Run2.C"(\"/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimRightSideband/LASTskim.Data_2015HLTand2016HLTLxy_RightSideband_DOCAlt500_LowPileUp.root\")"
//root -l addClassBDT_Run2.C"(\"/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimRightSideband/LASTskim.Data_2015HLTand2016HLTLxy_RightSideband_DOCAlt500_MiddlePileUp.root\")"
//root -l addClassBDT_Run2.C"(\"/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimRightSideband/LASTskim.Data_2015HLTand2016HLTLxy_RightSideband_DOCAlt500_HighPileUp.root\")"
//
//Pileup Trained test May29
//eval
//root -l -q addClassBDT_Run2.C"(\"/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/SignalMC/LASTskim.MC16Bs_CombWeights_DOCAlt500_EvalSet_LowPileUp2.root\")"
//root -l -q addClassBDT_Run2.C"(\"/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/SignalMC/LASTskim.MC16Bs_CombWeights_DOCAlt500_EvalSet_MiddlePileUp2.root\")"
//root -l -q addClassBDT_Run2.C"(\"/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/SignalMC/LASTskim.MC16Bs_CombWeights_DOCAlt500_EvalSet_HighPileUp2.root\")"
//
//rightsideband
//root -l -q addClassBDT_Run2.C"(\"/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimRightSideband/LASTskim.Data_2015HLTand2016HLTLxy_RightSideband_DOCAlt500_LowPileUp.root\")"
//root -l -q addClassBDT_Run2.C"(\"/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimRightSideband/LASTskim.Data_2015HLTand2016HLTLxy_RightSideband_DOCAlt500_MiddlePileUp.root\")"
//root -l -q addClassBDT_Run2.C"(\"/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimRightSideband/LASTskim.Data_2015HLTand2016HLTLxy_RightSideband_DOCAlt500_HighPileUp.root\")"

//Right Sideband Trained datasets
//root -l -q addClassBDT_Run2.C"(\"/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/SidebandTrained/data1516Bs_RightSideband_SplitSet_3.root\")"
//root -l -q addClassBDT_Run2.C"(\"/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/SidebandTrained/data1516Bs_SplitSet_3.root\")"
//root -l -q addClassBDT_Run2.C"(\"/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/SidebandTrained/LASTskim.mc16Bs_EvalSet.root\")"

//Right Sideband Trained datasets NEW STRATEGY

//root -l -q addClassBDT_Run2.C"(\"/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/SidebandTrained/data1516Bs_SplitSet_1.root\")"
//root -l -q addClassBDT_Run2.C"(\"/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/SidebandTrained/LASTskim.mc16Bs_SplitSet_1.root\")"

//root -l -q addClassBDT_Run2.C"(\"/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/SidebandTrained/data1516Bs_SplitSet_2.root\")"
//root -l -q addClassBDT_Run2.C"(\"/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/SidebandTrained/LASTskim.mc16Bs_SplitSet_2.root\")"

//root -l -q addClassBDT_Run2.C"(\"/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/SidebandTrained/data1516Bs_SplitSet_3.root\")"
//root -l -q addClassBDT_Run2.C"(\"/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/SidebandTrained/LASTskim.mc16Bs_SplitSet_3.root\")"


//
// Author: Iskander Ibragimov
// Date: 14.12.2014, 09.01.2018, 13.03.2018
//
// Edited by Aidan Grummer
// Date: 22.05.2018

//change input dataset, xml weights file, and output tag

#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "TFile.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"
#include "TH1.h"
#include "TH2.h"

#if not defined(__CINT__) || defined(__MAKECINT__)
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#endif

using namespace TMVA;
using namespace std;

void addClassBDT_Run2(TString fname = ""){
  //=============================================
  //====== flat ntuple input file  ==============
  //=============================================

  if (fname == "") {
    cout << "specify file name! Exiting..." << endl;
    return;
  }
  cout << "Will apply BDT weights to file: "<< fname << endl;  
  // TString newfnameTag = "_BDT2016_Jun7_train1_test2";//ww - with weights
  // TString newfnameTag = "_BDT2016_Jun7_train2_test1";//ww - with weights
  // TString newfnameTag = "_BDT2016_Jun11_train1_test2";//ww - with weights
  // TString newfnameTag = "_BDT2016_Jun11_train2_test3";//ww - with weights
  // TString newfnameTag = "_BDT2016_Jun11_train3_test1";//ww - with weights

  // TString newfnameTag = "_BDT2016_Jun12_train2_test3";//ww - with weights
  // TString newfnameTag = "_BDT2016_Jun12_train3_test1";//ww - with weights
  // TString newfnameTag = "_BDT2016_Jun12_train1_test2";//ww - with weights
  TString newfnameTag = "_BDT2016_Jun13MuIso_train1_test2";//ww - with weights

  // TString newfnameTag = "_BDT2016_Jun7_RS_train1_test2";//ww - with weights
  // TString newfnameTag = "_BDT2016_Jun7_RS_train2_test1";//ww - with weights
  // TString newfnameTag = "_BDT2016_May24_ww";//ww - with weights
  // TString newfnameTag = "_BDT2016_May24npv";//Tag to be added to the end of the output file.
  // TString newfnameTag = "_BDT2016_May29_wQLCDDW";//Tag to be added to the end of the output file.
  // TString newfnameTag = "_BDT2016_May31_noPVweights";//Tag to be added to the end of the output file.
  // TString newfnameTag = "_BDT2016_May31_noPVweightsBkg";//Tag to be added to the end of the output file.
  // TString newfnameTag = "_BDT2016_May29_trainPVstudy";//Tag to be added to the end of the output file.
  //=============================================
  //=========== xml file with BDT weights =======
  //=============================================

// change xmlname for a different set of weights
    // May15/ changes to TrainedMVAs/
// TString xmlname("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BDT/bdt2016.weights.xml");
  // TString xmlFolder = "/afs/cern.ch/user/a/agrummer/www/bmumu/Data/TrainedMVAs/Jun7_train1_test2/";//Official 15 vars with QLC and DDW
  // TString xmlFolder = "/afs/cern.ch/user/a/agrummer/www/bmumu/Data/TrainedMVAs/Jun7_train2_test1/";//Official 15 vars with QLC and DDW
  // TString xmlFolder = "/afs/cern.ch/user/a/agrummer/www/bmumu/Data/TrainedMVAs/Jun7_RS_train1_test2/";//Official 15 vars with QLC and DDW
  // TString xmlFolder = "/afs/cern.ch/user/a/agrummer/www/bmumu/Data/TrainedMVAs/Jun7_RS_train2_test1/";//Official 15 vars with QLC and DDW
  // TString xmlFolder = "/afs/cern.ch/user/a/agrummer/www/bmumu/Data/TrainedMVAs/Jun7_train2_test1/";//Official 15 vars with QLC and DDW
  // TString xmlFolder = "/afs/cern.ch/user/a/agrummer/www/bmumu/Data/TrainedMVAs/May24/";//Official 15 vars with QLC and DDW
  // TString xmlFolder = "/afs/cern.ch/user/a/agrummer/www/bmumu/Data/TrainedMVAs/May31_noPVweights/";//Official 15 vars with QLC and DDW
  // TString xmlFolder = "/afs/cern.ch/user/a/agrummer/www/bmumu/Data/TrainedMVAs/May31_noPVweightsBkg/";//Official 15 vars with QLC and DDW
  // TString xmlFolder = "/afs/cern.ch/user/a/agrummer/www/bmumu/Data/TrainedMVAs/OutMVA_PileupTrained/May29_LowPileup/";
  // TString xmlFolder = "/afs/cern.ch/user/a/agrummer/www/bmumu/Data/TrainedMVAs/OutMVA_PileupTrained/May29_MiddlePileup/";
  // TString xmlFolder = "/afs/cern.ch/user/a/agrummer/www/bmumu/Data/TrainedMVAs/OutMVA_PileupTrained/May29_HighPileup/";

  // TString xmlFolder = "/afs/cern.ch/user/a/agrummer/www/bmumu/Data/TrainedMVAs/Jun11/train1_test2/";//Official 15 vars with QLC and DDW
  // TString xmlFolder = "/afs/cern.ch/user/a/agrummer/www/bmumu/Data/TrainedMVAs/Jun11/train2_test3/";//Official 15 vars with QLC and DDW
  // TString xmlFolder = "/afs/cern.ch/user/a/agrummer/www/bmumu/Data/TrainedMVAs/Jun11/train3_test1/";//Official 15 vars with QLC and DDW
  // TString xmlname(xmlFolder + "out_MaxDepth4_MinNodeSize0.2_AdaBoostBeta0.5_NTrees500/weights/bdt2016_BDT.weights.xml");


  // TString xmlFolder = "/afs/cern.ch/user/a/agrummer/www/bmumu/Data/TrainedMVAs/Jun12/train2_test3/";//Official 15 vars with QLC and DDW
  // TString xmlFolder = "/afs/cern.ch/user/a/agrummer/www/bmumu/Data/TrainedMVAs/Jun12/train3_test1/";//Official 15 vars with QLC and DDW
  // TString xmlFolder = "/afs/cern.ch/user/a/agrummer/www/bmumu/Data/TrainedMVAs/Jun12/train1_test2/";
  TString xmlFolder = "/afs/cern.ch/user/a/agrummer/OutMVA/Jun13_muIso/train1_test2/";
  TString xmlname(xmlFolder + "out_MaxDepth4_MinNodeSize0.2_AdaBoostBeta0.5_NTrees500/weights/bdt2016_BDT.weights.xml");

  TString bdtMethod(xmlname);
  bdtMethod.Remove(0,bdtMethod.Last('/')+1);
    // for Run 1 bdts (but also need different variable names below...):
  // bdtMethod.Remove(bdtMethod.Index("_ABDT.weights.xml"),bdtMethod.Length());
  // for Run 2 bdts:
  bdtMethod.Remove(bdtMethod.Index(".weights.xml"),bdtMethod.Length());

  cout << "Use BDT weight file: "<< xmlname << " with training method: " << bdtMethod << endl;


  // tree name in official ntuples 
  //
  TString tname("T_mv");
  
#ifdef __CINT__
  gROOT->ProcessLine( ".O0" ); // turn off optimization in CINT
#endif
  
  //---------------------------------------------------------------
    
  // This loads the library
  TMVA::Tools::Instance();
  
  // Default MVA methods to be trained + tested
  std::map<std::string,int> Use;
  
  cout << endl;
  cout << "==> Start TMVAClassificationApplication" << endl;
  
  
  // --------------------------------------------------------------------------------------------------
  
  // --- Create the Reader object
  // --- this part is not to be changed
  
  cout << "--- Create the Reader object" << endl;
  
  TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );    
  
  // Create a set of variables and declare them to the reader
  // - the variable names MUST corresponds in name and type to those given in the weight file(s) used
  Float_t pT_reader, pTSign_reader, BrefTrPlngMin2D_reader, closeDOCA_reader, closeDOCASign_reader, chi2PVSVLog1Dz_reader, chi2PVSVLog2D_reader;
  Float_t d0MinSign_reader, d0Max_reader, d0MaxSign_reader, properTime_sig_reader, a_2D_reader, iso7Chi26MedPt05_reader, Lxy_reader, DR_reader;
  Float_t ClosNTracksChi2_reader, DPhi_reader, DEta_reader, MuonsDCA_reader, Chi2ByNDF_reader, Chi2Muons2AnyPV_reader, MuonsIso_reader;
  Float_t MuonPIso_reader, MuonMIso_reader, DecayCopl_reader, LxySig_reader;
  Float_t MuonPNtrk_reader,MuonMNtrk_reader,a_3D_reader,DXSign_reader,DXSign2D_reader,IP3D_reader, Musd0S_reader, CoplwithZ_reader;
  Float_t Npv;
  Float_t MuPiso;
  Float_t MuMiso;
//XML variable names:
  //These Variables have to be in the order of the xml weights file (order that were submitted to the training)
  reader->AddVariable( "B_pT", &pT_reader );
  reader->AddVariable( "Lxy", &Lxy_reader );
  // reader->AddVariable( "TMath::Sqrt(pow(closeTrkDCA,2)+pow(closeTrkZCA,2))", &closeDOCA_reader );
  reader->AddVariable( "closeTrkDOCA", &closeDOCA_reader );
  reader->AddVariable( "closeTrkNtrksChi2", &ClosNTracksChi2_reader );
  reader->AddVariable( "TMath::Abs(d0Min_sig)", &d0MinSign_reader );

  reader->AddVariable( "TMath::Abs(d0Max_sig)", &d0MaxSign_reader );
  reader->AddVariable( "PlngMin2D", &BrefTrPlngMin2D_reader );
  reader->AddVariable( "chi2_PVSV_log2D", &chi2PVSVLog2D_reader );
  reader->AddVariable( "TMath::Abs(a_2D)", &a_2D_reader );
  reader->AddVariable( "DR", &DR_reader );

  reader->AddVariable( "B_iso_7_Chi2_5_LoosePt05", &iso7Chi26MedPt05_reader );
  reader->AddVariable( "TMath::Abs(B_IDtrks_deltaPhi)", &DPhi_reader );
  reader->AddVariable( "TMath::Abs(B_IDtrks_DCA)", &MuonsDCA_reader );
  reader->AddVariable( "Bvtx3DIP", &IP3D_reader );
  reader->AddVariable( "B_minChi2MuonsIPtoAnyPV", &Chi2Muons2AnyPV_reader );
  // reader->AddVariable( "Npv", &Npv );
  reader->AddVariable( "muP_iso_7_chi2_5_LoosePt05", &MuPiso );
  reader->AddVariable( "muM_iso_7_chi2_5_LoosePt05", &MuMiso );
  
  reader->BookMVA(bdtMethod, xmlname);

  //---------------------------------------------------------------------------------------------------

  // Prepare input tree (this must be replaced by your data source)
  // in this example, there is a toy tree with signal and one with background events
  // we'll later on use only the "signal" events for the test in this example.
  // 
  
  TFile *ifile = TFile::Open( fname );
  TTree *intree = (TTree*)ifile->Get(tname);
  
  cout << "--- TMVAClassificationApp    : Using input file: " << ifile->GetName() << endl;
  
  // --- Event loop
  
  // Prepare the event tree
  // - here the variable names have to corresponds to your tree
  // - you can use the same variables as above which is slightly faster,
  //   but of course you can use different ones and copy the values inside the event loop
  //
  
  Double_t BvtxEta, BvtxPt, BvtxPtSign, BvtxLxy,  ClosTrackDOCASign, d0MinSign, d0Max, d0MaxSign;
  Float_t ClosTrackDCA,  ClosTrackZCA, BvtxIsolation;
  Float_t muPiso,  muMiso;
  Double_t ClosTrackDOCA;
  Double_t minChi2MuonsIP2AnyPV;
  Double_t BvtxPlngMin2D,lnChi2PVtxBVtx1D, lnChi2PVtxBVtx2D, BvtxPointingAngle2D, BvtxDR, BvtxLxySign, closeTrkDOCA;
  Double_t MuonsRefTrksDPhi, MuonsRefTrksDEta, MuonsDCA, BvtxChi2byNDF, MUpIsolation, MUmIsolation;
  Double_t MuSignedd0SignMin, CoplwithZ, DecayCoplanarity;
  Double_t BvtxPointingAngle3D, BvtxDXSign,BvtxDXSign2D,Bvtx3DIP;
  Int_t MUpNTracksIsolation,MUmNTracksIsolation;
  Int_t ClosTrackNTracksChi2(0);
  Double_t UpdatedClassBDT(0);
  Int_t OddEvent, ResCategory, PassBDTPresel;
  Bool_t passTriggerScheme2a,passTriggerScheme2b,passTriggerScheme2c;
  cout << "--- Select signal sample" << endl;

  if (tname.EqualTo("T_mv")) {
    // =======================
    // == Official ntuples ===
    // =======================
    intree->SetBranchStatus("*",0);
    intree->SetBranchStatus("B_pT",1);
    intree->SetBranchAddress( "B_pT", &BvtxPt );
    intree->SetBranchStatus("Lxy",1);
    intree->SetBranchAddress( "Lxy", &BvtxLxy );
    intree->SetBranchStatus("closeTrkDCA",1);
    intree->SetBranchAddress( "closeTrkDCA", &ClosTrackDCA );
    intree->SetBranchStatus("closeTrkZCA",1);
    intree->SetBranchAddress( "closeTrkZCA", &ClosTrackZCA );
    intree->SetBranchStatus("closeTrkDOCA",1);
    intree->SetBranchAddress( "closeTrkDOCA", &ClosTrackDOCA );

    intree->SetBranchStatus("closeTrkNtrksChi2",1);
    intree->SetBranchAddress( "closeTrkNtrksChi2", &ClosTrackNTracksChi2 );

    intree->SetBranchStatus("d0Min_sig",1);
    intree->SetBranchAddress( "d0Min_sig", &d0MinSign );
    intree->SetBranchStatus("d0Max_sig",1);
    intree->SetBranchAddress( "d0Max_sig", &d0MaxSign );
    intree->SetBranchStatus("PlngMin2D",1);
    intree->SetBranchAddress( "PlngMin2D", &BvtxPlngMin2D );
    intree->SetBranchStatus("chi2_PVSV_log2D",1);
    intree->SetBranchAddress( "chi2_PVSV_log2D", &lnChi2PVtxBVtx2D );
    intree->SetBranchStatus("a_2D",1);
    intree->SetBranchAddress( "a_2D", &BvtxPointingAngle2D );
    
    intree->SetBranchStatus("DR",1);
    intree->SetBranchAddress( "DR", &BvtxDR );
    intree->SetBranchStatus("B_iso_7_Chi2_5_LoosePt05",1);
    intree->SetBranchAddress( "B_iso_7_Chi2_5_LoosePt05", &BvtxIsolation );

    intree->SetBranchStatus("B_IDtrks_deltaPhi",1);
    intree->SetBranchAddress( "B_IDtrks_deltaPhi", &MuonsRefTrksDPhi );
    intree->SetBranchStatus("B_IDtrks_DCA",1);
    intree->SetBranchAddress( "B_IDtrks_DCA", &MuonsDCA );

    intree->SetBranchStatus("B_minChi2MuonsIPtoAnyPV",1);
    intree->SetBranchAddress( "B_minChi2MuonsIPtoAnyPV", &minChi2MuonsIP2AnyPV );

    intree->SetBranchStatus("B_MUCALC_mass",1);
    intree->SetBranchStatus("B_MUCALC_massErr",1);
    /*    
    // for BpJpsiKp and BsJpsiPhi
    intree->SetBranchStatus("B_VTX_mass",1);
    intree->SetBranchStatus("B_VTX_massErr",1);
    */

    intree->SetBranchStatus("Bvtx3DIP",1);
    intree->SetBranchAddress("Bvtx3DIP", &Bvtx3DIP );
    
    intree->SetBranchStatus("B_eta",1); 
    intree->SetBranchStatus("event_number",1); 
    intree->SetBranchStatus("run_number",1);
    intree->SetBranchStatus("Npv",1);
    intree->SetBranchStatus("Lxy_sig",1);
    //    intree->SetBranchStatus("properTime",1);
    intree->SetBranchStatus("properTime_sig",1);

    intree->SetBranchStatus("CombWeights",1);
    intree->SetBranchStatus("B_iso_Ntracks_7_Chi2_5_LoosePt05",1);
    intree->SetBranchStatus("B_fitChi2NDF",1);

    //weights 
    intree->SetBranchStatus("CombWeights",1);//Kinematic Weights 
    intree->SetBranchStatus("PVWeights",1); //Pileup weights
    intree->SetBranchStatus("Muon1_reco_eff_sf",1); //muon reconstruction factors
    intree->SetBranchStatus("Muon2_reco_eff_sf",1); //muon reconstruction factors

    // intree->SetBranchStatus("testweight",1); 

    intree->SetBranchStatus("muP_iso_7_chi2_5_LoosePt05",1); //muon reconstruction factors
    intree->SetBranchAddress( "muP_iso_7_chi2_5_LoosePt05", &muPiso );
    intree->SetBranchStatus("muM_iso_7_chi2_5_LoosePt05",1); //muon reconstruction factors
    intree->SetBranchAddress( "muM_iso_7_chi2_5_LoosePt05", &muMiso );
    //intree->SetBranchStatus("testweight",1); //FIXMEMC
    //intree->SetBranchStatus("isSignal",1); //FIXMEMC

    //    intree->SetBranchStatus("",1);
  } else {
    cout << "Unknown flat ntuple tree name, exiting..."  <<endl;
    return;
  }
  //   intree->SetBranchAddress("",&);
  //--------create new file with new class branch---------------


  TString newfname(fname);
  //newfname.Remove(0,newfname.Last('/')+1); //get rid of path
  newfname.Remove(newfname.Index(".root"),newfname.Length());
  // newfname+=Form("_%s", newfnameTag);
  newfname.Append(newfnameTag + ".root");
  TFile *ofile = new TFile(newfname,"recreate");

  TTree *tn = intree->CloneTree(0);
  TBranch *bcla = tn->Branch("BDT_bb_2016",&UpdatedClassBDT,"BDT_bb_2016/D");
  // the variable below can be added to be compatible w/ Run 1 ntuples
  //  TBranch *bcat = tn->Branch("closeTrkDOCA",&closeTrkDOCA,"closeTrkDOCA/D"); //FIXME 
  //------------------------------------------------------------
  
  cout << "--- Processing: " << intree->GetEntries() << " events" << endl;
  TStopwatch sw;
  sw.Start();
  
  for (Long64_t ievt=0; ievt<intree->GetEntries();ievt++) {
    
    if (ievt%50000 == 0) cout << "--- ... Processing event: " << ievt << endl;
    
    intree->GetEntry(ievt);
    //    if (!(BvtxLxy>0.0 && TMath::Abs(BvtxPointingAngle2D)<1.0 && BvtxDR<1.5)) continue;
    
    pT_reader=BvtxPt;
    Lxy_reader=BvtxLxy;
    // closeDOCA_reader = sqrt(pow(ClosTrackDCA,2)+pow(ClosTrackZCA,2));
    closeDOCA_reader = (float) ClosTrackDOCA;
    ClosNTracksChi2_reader=ClosTrackNTracksChi2;
    d0MinSign_reader=TMath::Abs(d0MinSign);

    d0MaxSign_reader=TMath::Abs(d0MaxSign);
    BrefTrPlngMin2D_reader=BvtxPlngMin2D;
    chi2PVSVLog2D_reader=lnChi2PVtxBVtx2D;
    a_2D_reader=TMath::Abs(BvtxPointingAngle2D);
    DR_reader=BvtxDR;

    iso7Chi26MedPt05_reader=BvtxIsolation;
    DPhi_reader=MuonsRefTrksDPhi;
    MuonsDCA_reader=TMath::Abs(MuonsDCA);
    Chi2Muons2AnyPV_reader=minChi2MuonsIP2AnyPV;
    IP3D_reader=Bvtx3DIP;

    //MuonsIso_reader=MUpIsolation+MUmIsolation;
    MuonPIso_reader=MUpIsolation;
    MuonMIso_reader=MUmIsolation;
    MuonPNtrk_reader=MUpNTracksIsolation;
    MuonMNtrk_reader=MUmNTracksIsolation;
    a_3D_reader=BvtxPointingAngle3D;

    MuPiso=muPiso;
    MuMiso=muMiso;

    //DecayCopl_reader=DecayCoplanarity;
    //Musd0S_reader=MuSignedd0SignMin;
    //CoplwithZ_reader=CoplwithZ;
    UpdatedClassBDT = reader->EvaluateMVA(bdtMethod);
    // closeTrkDOCA = (double)closeDOCA_reader; //FIXME    
    tn->Fill();     
  }
  ofile->cd();
  tn->Write();
  ifile->Close();
  ofile->Close();
  // Get elapsed time
  sw.Stop();
  cout << "--- End of event loop: "; sw.Print();
  delete reader;
  
  cout << "==> TMVAClassificationApplication for the file "<< fname <<" is done!" << endl;

}
