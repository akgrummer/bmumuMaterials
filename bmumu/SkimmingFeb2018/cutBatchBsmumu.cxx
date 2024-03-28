// macro applies Run 1 analysis cuts on BpJpsiKp channel
// using skimmed ntuples on eos 
// (tentatively here:) /eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuProd1/ntup/slimmed_201710/
// as an input
// it outputs one large file (up to 6 GByte) per dataset

// 1. specify outpath
// 2. do "make" or "make cutBatchBsmumu.exe"
// 3. ./cutBatchBsmumu("path/to/dataset")

#include "TCut.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1.h"
#include "TBranch.h"
#include <iostream>
#include "TSystem.h"
#include "TLorentzVector.h"
#include "TStopwatch.h"

using namespace std;
typedef map<string, int>      map_str_int;

void cutBatchBsmumu(TString indir){
  TString outdir("/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimFeb13_HLT_mu6_mu4_2016");

  TStopwatch sw;
  sw.Start();

  TString fspath(indir); //"specify path to dataset w/o slash at the end" 
  //fspath.Append("/user*.root");  // full flat ntuples 
  //fspath.Append("/skim*.root");  // OLD MC
  fspath.Append("/output*.root");
  cout << "Processing files: "<< fspath <<endl;
  TChain *ts = new TChain("T_mv");
  ts->Add(fspath);

  TString fnpath(outdir);
  fnpath.Append("/LASTskim.");
  Int_t lsl = indir.Last('/');
  Int_t len = indir.Length();
  fnpath.Append(indir(lsl+1, len-lsl-1)); 
  fnpath.Append(".root");
  
  cout<< "Entries in original tree: "<< ts->GetEntries() <<endl;
  auto nevents = ts->GetEntries();

  //tn->SetBranchStatus("*",0);
  double KPlus_pT, KPlus_eta, KPlus_phi, KMinus_pT, KMinus_eta, KMinus_phi, Jpsi_fitChi2;
  double B_MUCALC_mass, B_pT, B_eta, Lxy, a_2D, DR, Muon1_pT, Muon2_pT, Muon1_eta, Muon2_eta;
  double B_fitChi2NDF, Jpsi_mass;
  int KMinus_pass,KPlus_pass,Jpsi_fitNDF, Muon1_accept, Muon2_accept;
  bool Muon1_isCombinedMuon, Muon2_isCombinedMuon, pass_grl, Muon1_isTight, Muon2_isTight;
  map_str_int *HLT_trigger = 0;

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
  //  ts->SetBranchAddress("",  &);
  // ts->SetBranchAddress("pass_grl",  &pass_grl);//commented by Aidan on Feb. 11, 2018  reason: no grl branch in this version of files.
  ts->SetBranchAddress("HLT_trigger",&HLT_trigger);

  TFile *fn = new TFile(fnpath,"recreate");
  TTree *tf = ts->CloneTree(0);
  cout<< "Now loop over original tree" << endl; 
  for (auto ievent=0; ievent<nevents; ievent++)
    {
      if (ievent%100000==0) cout << "Processing event "<< ievent << endl;
      ts->GetEntry(ievent);

      if (Lxy<0. || TMath::Abs(a_2D)>1.0 || DR>1.5) continue;
      // if (B_MUCALC_mass<4766.0 || B_MUCALC_mass>5966.0) continue;
      if (B_MUCALC_mass<4766.0 || B_MUCALC_mass>5966.0 || (B_MUCALC_mass>=5166.0 && B_MUCALC_mass<=5526.0)) continue; //exclude blinded region
      if (B_fitChi2NDF>6.0) continue;

      bool pass_trigger = ( HLT_trigger->find("HLT_mu6_mu4_bBmumu") != HLT_trigger->end() );
      if (!pass_trigger) continue;

      if (B_pT<8000. || TMath::Abs(B_eta)>2.5) continue;
      if (!Muon1_accept || !Muon2_accept || !Muon1_isCombinedMuon || !Muon2_isCombinedMuon) continue;
      if (!Muon1_isTight || !Muon2_isTight) continue;
      if (Muon1_pT<4000. || TMath::Abs(Muon1_eta)>2.5 || Muon2_pT<4000. || TMath::Abs(Muon2_eta)>2.5) continue;
      // if (!pass_grl) continue; //commented by Aidan on Feb. 11, 2018


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
  TString inpath;
  if (argc>1) inpath = TString(argv[1]);
  cutBatchBsmumu(inpath);
  return 0;
}
