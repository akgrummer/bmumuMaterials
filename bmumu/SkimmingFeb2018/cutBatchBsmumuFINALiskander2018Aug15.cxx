// macro applies Run 1 analysis cuts on BpJpsiKp channel
// using skimmed ntuples on eos 
// (tentatively here:) /eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuProd1/ntup/skimmed_201710/
// as an input
// it outputs one large file (up to 6 GByte) per dataset

// 1. specify outpath
// 2. do "make" or "make cutBatchBsmumu.exe"
// 3. ./cutBatchBsmumu path/to/dataset

#include "TCut.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1.h"
#include "TH2.h"
#include "TBranch.h"
#include <iostream>
#include "TSystem.h"
#include "TLorentzVector.h"
#include "TStopwatch.h"
#include "DDWQLC.h"
#include "TriggerWeights.h"

using namespace std;
typedef map<string, int>      map_str_int;

void cutBatchBsmumu(TString indir="", TString filter=""){
  if (indir.EqualTo("")) indir = "/afs/cern.ch/work/i/ibragimo/mc15Bs";
  TString outdir(indir);

  TStopwatch sw;
  sw.Start();

  ////////////////////////////////////////////////////////
  TString QLCfileName = "/afs/cern.ch/user/i/ibragimo/test/QLCfile_BsToMuMu.root";
  DDWQLC QLC(QLCfileName, "h_QLC_err_BsMuMu", "h_QLC_BsMuMu");

  TString DDWfileName = "/afs/cern.ch/user/i/ibragimo/test/DDWfile_BpToJpsiK.root";
  DDWQLC DDW(DDWfileName,  "h_covarianceDDW_even_BpJpsiK", "h_DDWpt_even_BpJpsiK", "h_DDWeta_even_BpJpsiK");

  cout << "Done reading QLC and DDW files." << endl;

  TriggerWeights myWeights("singleMu_SF_data1516_perperiod.root");

  cout << "Done reading trigger weight files." << endl;
  ////////////////////////////////////////////////////////


  TString fspath(indir); //"specify path to dataset w/o slash at the end" 
  //fspath.Append("/user*.root");  // full flat ntuples 
  if (filter=="") fspath.Append("/skim/skim");
  else fspath.Append(Form("/skim/skim.output_%s", filter.Data()));
  fspath.Append("*.root");
  //fspath.Append("/output*.root");
  cout << "Processing files: "<< fspath <<endl;
  TChain *ts = new TChain("T_mv");
  ts->Add(fspath);

  TString fnpath(outdir);
  fnpath.Append("/LASTskim.");
  Int_t lsl = indir.Last('/');
  Int_t len = indir.Length();
  fnpath.Append(indir(lsl+1, len-lsl-1)); 
  if (filter=="") fnpath.Append(".root");
  else fnpath.Append(Form("%s.root", filter.Data()));
  
  cout<< "Entries in original tree: "<< ts->GetEntries() <<endl;
  auto nevents = ts->GetEntries();

  //tn->SetBranchStatus("*",0);
  double KPlus_pT, KPlus_eta, KPlus_phi, KMinus_pT, KMinus_eta, KMinus_phi, Jpsi_fitChi2;
  float B_MUCALC_mass;
  double  B_pT, B_eta, Lxy, a_2D, DR, Muon1_pT, Muon2_pT, Muon1_eta, Muon2_eta;
  double B_fitChi2NDF, Jpsi_mass, CombWeights;
  double B_iso_7_Chi2_5_MedPt05, closeTrkDOCA, B_minChi2MuonsIPtoAnyPV;
  float closeTrkDCA, closeTrkZCA, B_iso_7_Chi2_5_LoosePt05, Bsmumu_minLogChi2ToAnyPV_PV_MIN_Z0_BA;
  int  B_iso_Ntracks_7_Chi2_5_MedPt05, B_iso_Ntracks_7_Chi2_5_LoosePt05, nphotons_b;
  UInt_t run_number;
  int KMinus_pass,KPlus_pass,Jpsi_fitNDF, Muon1_accept, Muon2_accept, trigger_category(1);
  bool Muon1_isCombinedMuon, Muon2_isCombinedMuon, pass_grl(true), Muon1_isTight, Muon2_isTight;
  float muP_iso_7_chi2_5_LoosePt05, muM_iso_7_chi2_5_LoosePt05;
  double muM_iso_7_chi2_5_medPt05, muP_iso_7_chi2_5_medPt05;
  double TRUTH_MuMinus_pT, TRUTH_MuPlus_pT, TRUTH_MuMinus_eta, TRUTH_MuPlus_eta;
  int muP_iso_Ntracks_7_chi2_5_LoosePt05, muM_iso_Ntracks_7_chi2_5_LoosePt05, muM_iso_Ntracks_7_chi2_5_medPt05, muP_iso_Ntracks_7_chi2_5_medPt05;
  map_str_int *HLT_trigger = 0;
  map_str_int *L1_trigger = 0;
  string* decay = 0;
  bool is_2015, is_2016main, pass_trigger, Trigger_Matched;
  Float_t Muon1_trigger_sf, Muon1_trigger_sf_staterr, Muon1_trigger_sf_systerr;
  Float_t Muon2_trigger_sf, Muon2_trigger_sf_staterr, Muon2_trigger_sf_systerr; 


  ts->SetBranchAddress("B_MUCALC_mass",&B_MUCALC_mass);
  ts->SetBranchAddress("B_pT",&B_pT);
  ts->SetBranchAddress("B_eta",&B_eta);
  ts->SetBranchAddress("Lxy",&Lxy);
  ts->SetBranchAddress("a_2D",&a_2D);
  ts->SetBranchAddress("DR",&DR);
  ts->SetBranchAddress("Muon1_pT",&Muon1_pT);
  ts->SetBranchAddress("Muon1_eta",&Muon1_eta);
  ts->SetBranchAddress("Muon2_pT",&Muon2_pT);
  ts->SetBranchAddress("Muon2_eta",&Muon2_eta);
  ts->SetBranchAddress("B_fitChi2NDF",&B_fitChi2NDF);
  ts->SetBranchAddress("Muon1_isCombinedMuon",&Muon1_isCombinedMuon);
  ts->SetBranchAddress("Muon2_isCombinedMuon",&Muon2_isCombinedMuon);
  ts->SetBranchAddress("Muon1_accept",  &Muon1_accept);
  ts->SetBranchAddress("Muon2_accept",  &Muon2_accept);
  ts->SetBranchAddress("Muon1_isTight",  &Muon1_isTight);
  ts->SetBranchAddress("Muon2_isTight",  &Muon2_isTight);
  ts->SetBranchAddress("run_number",  &run_number);
  ts->SetBranchAddress("Trigger_Matched",  &Trigger_Matched);
  /*
  ts->SetBranchAddress("TRUTH_MuMinus_pT",  &TRUTH_MuMinus_pT);
  ts->SetBranchAddress("TRUTH_MuPlus_pT",  &TRUTH_MuPlus_pT);
  ts->SetBranchAddress("TRUTH_MuMinus_eta",  &TRUTH_MuMinus_eta);
  ts->SetBranchAddress("TRUTH_MuPlus_eta",  &TRUTH_MuPlus_eta); 
  */
  //  ts->SetBranchAddress("pass_grl",  &pass_grl); //FIXME mystyle
  ts->SetBranchAddress("HLT_trigger",&HLT_trigger);
  ts->SetBranchAddress("L1_trigger",&L1_trigger);

  ts->SetBranchAddress("B_iso_7_Chi2_5_LoosePt05",  &B_iso_7_Chi2_5_LoosePt05);
  ts->SetBranchAddress("B_iso_Ntracks_7_Chi2_5_LoosePt05",  &B_iso_Ntracks_7_Chi2_5_LoosePt05);
  ts->SetBranchAddress("muP_iso_7_chi2_5_LoosePt05",  &muP_iso_7_chi2_5_LoosePt05);
  ts->SetBranchAddress("muP_iso_Ntracks_7_chi2_5_LoosePt05",  &muP_iso_Ntracks_7_chi2_5_LoosePt05);
  ts->SetBranchAddress("muM_iso_7_chi2_5_LoosePt05",  &muM_iso_7_chi2_5_LoosePt05);
  ts->SetBranchAddress("muM_iso_Ntracks_7_chi2_5_LoosePt05",  &muM_iso_Ntracks_7_chi2_5_LoosePt05);

  ts->SetBranchAddress("closeTrkDCA",  &closeTrkDCA);
  ts->SetBranchAddress("closeTrkZCA",  &closeTrkZCA);
  //  ts->SetBranchAddress("nphotons_b", &nphotons_b);
  ts->SetBranchAddress("CombWeights", &CombWeights);
  ts->SetBranchAddress("decay",&decay);  //NEEDED to select on combinatorics

  TFile *fn = new TFile(fnpath,"recreate");
  TTree *tf = ts->CloneTree(0);
  TBranch* b1 = tf->Branch("B_iso_7_Chi2_5_MedPt05",&B_iso_7_Chi2_5_MedPt05,"B_iso_7_Chi2_5_MedPt05/D");
  TBranch* b2 = tf->Branch("B_iso_Ntracks_7_Chi2_5_MedPt05",&B_iso_Ntracks_7_Chi2_5_MedPt05,"B_iso_Ntracks_7_Chi2_5_MedPt05/I");
  TBranch* b3 = tf->Branch("closeTrkDOCA",&closeTrkDOCA,"closeTrkDOCA/D");
  TBranch* b4 = tf->Branch("trigger_category",&trigger_category,"trigger_category/I");
  TBranch* b5 = tf->Branch("muM_iso_7_chi2_5_medPt05",&muM_iso_7_chi2_5_medPt05,"muM_iso_7_chi2_5_medPt05/D");
  TBranch* b6 = tf->Branch("muM_iso_Ntracks_7_chi2_5_medPt05",&muM_iso_Ntracks_7_chi2_5_medPt05,"muM_iso_Ntracks_7_chi2_5_medPt05/I");
  TBranch* b7 = tf->Branch("muP_iso_7_chi2_5_medPt05",&muP_iso_7_chi2_5_medPt05,"muP_iso_7_chi2_5_medPt05/D");
  TBranch* b8 = tf->Branch("muP_iso_Ntracks_7_chi2_5_medPt05",&muP_iso_Ntracks_7_chi2_5_medPt05,"muP_iso_Ntracks_7_chi2_5_medPt05/I");
  TBranch* b11= tf->Branch("Muon1_trigger_sf",&Muon1_trigger_sf,"Muon1_trigger_sf/F");
  TBranch* b12= tf->Branch("Muon2_trigger_sf",&Muon2_trigger_sf,"Muon2_trigger_sf/F");
  //  TBranch* b1 =tn->Branch("",&,"/D");

  int status;
  cout<< "Now loop over original tree" << endl; 
  for (auto ievent=0; ievent<nevents; ievent++)
    {
      if (ievent%100000==0) cout << "Processing event "<< ievent << endl;
      ts->GetEntry(ievent);


      if (B_MUCALC_mass<4766.0 || B_MUCALC_mass>5966.0) continue; 
      if (B_MUCALC_mass>=5166.0 && B_MUCALC_mass<=5526.0) continue; 


      is_2015        = (run_number <= 284484);
      is_2016main    = (run_number > 284484 );
      pass_trigger  = ( is_2015 && HLT_trigger->find("HLT_mu6_mu4_bBmumu") != HLT_trigger->end());
      pass_trigger |= ( is_2016main && HLT_trigger->find("HLT_mu6_mu4_bBmumu_Lxy0") != HLT_trigger->end()); 
      pass_trigger &= ( L1_trigger->find("L1_MU6_2MU4") != L1_trigger->end() );
      if (!pass_trigger) continue;
      if (!Trigger_Matched) continue;


      if (!Muon1_isTight || !Muon2_isTight) continue;
      if (!Muon1_accept || !Muon2_accept || 

        !Muon1_isCombinedMuon || !Muon2_isCombinedMuon) continue;
      if (Muon1_pT<4000. || Muon2_pT<4000. || (Muon1_pT<6000. && Muon2_pT<6000.) || TMath::Abs(Muon1_eta)>2.5 || TMath::Abs(Muon2_eta)>2.5) continue;

      if (B_fitChi2NDF>6.0) continue;
      
      if (B_pT<8000. || TMath::Abs(B_eta)>2.5) continue;

      if (Lxy<0. || TMath::Abs(a_2D)>1.0 || DR>1.5) continue; //FIXMETEST

      if (!pass_grl) continue;
    
      //if (nphotons_b>0) continue; //FIXME MC NORAD ONLY
      //if ((*decay) != "combinatorial") continue; //FIXME

      //FIXME blinded DATA ONLY
     
      //      if (TRUTH_MuMinus_pT<3500. || TRUTH_MuPlus_pT<3500. || fabs(TRUTH_MuPlus_eta)>3.0 || fabs(TRUTH_MuMinus_eta)>3.0) continue; //FIXME bbmumuX
  
      //FIXME MC Sigonly
      //
      /*
      double QLCval = QLC.GetWeight(TMath::Abs(B_eta), B_pT);
      double DDWval = DDW.GetWeight(B_eta, B_pT);
      CombWeights = DDWval * QLCval;
      */
      /* FIXME MC
      float pTThreshold1 = 4.0;
      float pTThreshold2 = 6.0;
      if (Muon1_pT > Muon2_pT) {
	pTThreshold1 = 6.0;
	pTThreshold2 = 4.0;
      }
      status = myWeights.GetWeight( Muon1_pT/1000., Muon1_eta,  1. ,run_number, pTThreshold1, Muon1_trigger_sf, Muon1_trigger_sf_staterr, Muon1_trigger_sf_systerr);
      //if (status<0) cout << "status " << status << " for Muon1 (mu+)" << endl;
      status = myWeights.GetWeight( Muon2_pT/1000., Muon2_eta, -1. ,run_number, pTThreshold2, Muon2_trigger_sf, Muon2_trigger_sf_staterr, Muon2_trigger_sf_systerr);
      //if (status<0) cout << "status " << status << " for Muon2 (mu-)" << endl;
      */
      B_iso_7_Chi2_5_MedPt05 = (double)B_iso_7_Chi2_5_LoosePt05;
      B_iso_Ntracks_7_Chi2_5_MedPt05 = B_iso_Ntracks_7_Chi2_5_LoosePt05;
      muM_iso_7_chi2_5_medPt05 = (double)muM_iso_7_chi2_5_LoosePt05;
      muM_iso_Ntracks_7_chi2_5_medPt05 = muM_iso_Ntracks_7_chi2_5_LoosePt05;
      muP_iso_7_chi2_5_medPt05 = (double)muP_iso_7_chi2_5_LoosePt05;
      muP_iso_Ntracks_7_chi2_5_medPt05 = muP_iso_Ntracks_7_chi2_5_LoosePt05;
      if (TMath::Abs(closeTrkDCA)==999.0) closeTrkDOCA = -0.01;  //FIXME DOCA
      else closeTrkDOCA = (double)sqrt(pow(closeTrkDCA,2)+pow(closeTrkZCA,2));
      tf->Fill();
    }
  cout<< "Entries in final tree: "<< tf->GetEntries() <<endl;
  sw.Stop();
  sw.Print();

  fn->cd();
  tf->Write();
  fn->Close();
}

int main(int argc, char* argv[])
{
  gSystem->Load("libdefinitions.so");
  TString inpath, pattern;
  if (argc>1) inpath = TString(argv[1]);
  if (argc>2) pattern = TString(argv[2]);
  cutBatchBsmumu(inpath, pattern);
  return 0;
}
