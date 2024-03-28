// macro applies Run 1 analysis cuts on BpJpsiKp channel
// using skimmed ntuples on eos 
// (tentatively here:) /eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuProd1/ntup/skimmed_201710/
// as an input
// it outputs one large file (up to 6 GByte) per dataset

// 1. specify outpath
// 2. do "make" or "make cutBatchBpJpsiKp.exe"
// 3. ./cutBatchBpJpsiKp path/to/dataset

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

void cutBatchBpJpsiKp(TString indir){
  TString outdir("path/to/your/output/dir");

  TStopwatch sw;
  sw.Start();

  TString fspath(indir); //"specify path to dataset w/o slash at the end" 
  //fspath.Append("/user*.root");  // full flat ntuples 
  //fspath.Append("/skim*.root");  // OLD MC
  fspath.Append("/output*.root");
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
  double K_pT, K_eta, K_phi, Jpsi_fitChi2;
  double B_VTX_mass, B_pT, B_eta, Lxy, a_2D, DR, Muon1_pT, Muon2_pT, Muon1_eta, Muon2_eta;
  double B_fitChi2NDF, Jpsi_mass, Phi_mass;
  int K_pass(1),Jpsi_fitNDF, Muon1_accept(1), Muon2_accept(1);
  bool Muon1_isCombinedMuon, Muon2_isCombinedMuon, pass_grl, Muon1_isTight, Muon2_isTight;
  map_str_int *HLT_trigger = 0;

  ts->SetBranchAddress("B_VTX_mass",&B_VTX_mass);
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
  ts->SetBranchAddress("Jpsi_fitChi2",  &Jpsi_fitChi2);
  ts->SetBranchAddress("Jpsi_fitNDF",  &Jpsi_fitNDF);
  ts->SetBranchAddress("Jpsi_mass",  &Jpsi_mass);
  ts->SetBranchAddress("K_pass",  &K_pass);

  //  ts->SetBranchAddress("",  &);
  ts->SetBranchAddress("pass_grl",  &pass_grl);
  ts->SetBranchAddress("K_pT",&K_pT);
  ts->SetBranchAddress("K_eta",&K_eta);
  ts->SetBranchAddress("K_phi",&K_phi);
    ts->SetBranchAddress("HLT_trigger",&HLT_trigger);

  TFile *fn = new TFile(fnpath,"recreate");
  TTree *tf = ts->CloneTree(0);
  cout<< "Now loop over original tree" << endl;
    Int_t AddCuts(0);
    Int_t vtxMassWindowCut(0);
    Int_t B_fitChi2NDFCut(0);
    Int_t TriggerCut(0);

    Int_t JpsiFitCut(0);
    Int_t JpsiBlindCut(0);
    Int_t KaonKinCuts(0);
    Int_t BKinCut(0);
    Int_t MuonFlagCut(0);
    Int_t MuonTightCut(0);
    Int_t MuonKinCuts(0);
    Int_t grlCut(0); 
  for (auto ievent=0; ievent<nevents; ievent++)
    {
      if (ievent%100000==0) cout << "Processing event "<< ievent << endl;
      ts->GetEntry(ievent);

      if (Lxy<0. || TMath::Abs(a_2D)>1.0 || DR>1.5){AddCuts+=1; continue;}
      if (B_VTX_mass<4930.0 || B_VTX_mass>5630.0){vtxMassWindowCut+=1; continue;}
      if (B_fitChi2NDF>6.0){B_fitChi2NDFCut+=1; continue;}

      // trigger cut has been already applied in the skimmed ntuples 
      //
      bool pass_trigger = ( HLT_trigger->find("HLT_mu6_mu4_bJpsimumu_Lxy0_L1BPH-2M9-MU6MU4_BPH-0DR15-MU6MU4") != HLT_trigger->end() );  //FIXME
      if (!pass_trigger){TriggerCut+=1; continue;}


      if (Jpsi_fitChi2/(1.0*Jpsi_fitNDF)>10.0){JpsiFitCut+=1; continue;}
      if (Jpsi_mass<2915.0 || Jpsi_mass>3275.0){JpsiBlindCut+=1; continue;}
      if (K_pT<1000. || TMath::Abs(K_eta)>2.5 || !K_pass){KaonKinCuts+=1; continue;}
      if (B_pT<8000. || TMath::Abs(B_eta)>2.5){BKinCut+=1; continue;}
      if (!Muon1_accept || !Muon2_accept || !Muon1_isCombinedMuon || !Muon2_isCombinedMuon){MuonFlagCut+=1; continue;}
      if (!Muon1_isTight || !Muon2_isTight){MuonTightCut+=1; continue;}
      if (Muon1_pT<4000. || TMath::Abs(Muon1_eta)>2.5 || Muon2_pT<4000. || TMath::Abs(Muon2_eta)>2.5){MuonKinCuts+=1; continue;}
      if (!pass_grl){grlCut+=l; continue;}


      tf->Fill();
    }
  cout<< "Entries in final tree: "<< tf->GetEntries() <<endl;
    cout<< "AddCuts: "<< AddCuts << endl;
    cout<< "vtxMassWindowCut: "<< vtxMassWindowCut << endl;
    cout<< "B_fitChi2NDFCut: "<< B_fitChi2NDFCut << endl;
    cout<< "TriggerCut: "<< TriggerCut << endl;

    cout<< "JpsiFitCut: "<< JpsiFitCut << endl;
    cout<< "JpsiBlindCut: "<< JpsiBlindCut << endl;
    cout<< "KaonKinCuts: "<< KaonKinCuts << endl;
    cout<< "BKinCut: "<< BKinCut << endl;
    cout<< "MuonFlagCut: "<< MuonFlagCut << endl;
    cout<< "MuonTightCut: "<< MuonTightCut << endl;
    cout<< "MuonKinCuts: "<< MuonKinCuts << endl;
    cout<< "grlCut: "<< grlCut << endl;

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
  cutBatchBpJpsiKp(inpath);
  return 0;
}
