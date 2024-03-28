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

void cutFlowValues(TString indir){
  // TString outdir("/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimFeb13_HLT_mu6_mu4_2016");

  TStopwatch sw;
  sw.Start();

  TString fspath(indir); //"specify path to dataset w/o slash at the end" 
  //fspath.Append("/user*.root");  // full flat ntuples 
  //fspath.Append("/skim*.root");  // OLD MC
  fspath.Append("/output*.root");
  cout << "Processing files: "<< fspath <<endl;
  TChain *ts = new TChain("T_mv");
  ts->Add(fspath);

  // TString fnpath(outdir);
  // fnpath.Append("/LASTskim.");
  // Int_t lsl = indir.Last('/');
  // Int_t len = indir.Length();
  // fnpath.Append(indir(lsl+1, len-lsl-1)); 
  // fnpath.Append(".root");
  
  cout<< "Entries in original tree: "<< ts->GetEntries() <<endl;
  auto nevents = ts->GetEntries();

  //tn->SetBranchStatus("*",0);
  double KPlus_pT, KPlus_eta, KPlus_phi, KMinus_pT, KMinus_eta, KMinus_phi, Jpsi_fitChi2;
  double B_MUCALC_mass, B_pT, B_eta, Lxy, a_2D, DR, Muon1_pT, Muon2_pT, Muon1_eta, Muon2_eta;
  double B_fitChi2NDF, Jpsi_mass;
  int KMinus_pass,KPlus_pass,Jpsi_fitNDF, Muon1_accept, Muon2_accept;
  bool Muon1_isCombinedMuon, Muon2_isCombinedMuon, pass_grl, Muon1_isTight, Muon2_isTight;
  map_str_int *HLT_trigger = 0;
  UInt_t run_number;
    
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
  ts->SetBranchAddress("run_number",&run_number);

  //  ts->SetBranchAddress("",  &);
  // ts->SetBranchAddress("pass_grl",  &pass_grl);//commented by Aidan on Feb. 11, 2018  reason: no grl branch in this version of files.
  ts->SetBranchAddress("HLT_trigger",&HLT_trigger);

  // TFile *fn = new TFile(fnpath,"recreate");
  TTree *tf = ts->CloneTree(0);
  cout<< "Now loop over original tree" << endl; 

  Int_t AddCuts(0);
  Int_t BlindCut(0);
  Int_t B_fitChi2NDFCut(0);
  Int_t TriggerCut(0);
  Int_t BKinCut(0);
  Int_t MuonCombinedCut(0);
  Int_t MuonTightCut(0);
  Int_t MuonKinCuts(0);
  Int_t EventsNotCut(0);
for (auto ievent=0; ievent<nevents; ievent++){
    if (ievent%100000==0) cout << "Processing event "<< ievent << endl;
    ts->GetEntry(ievent);
////////////////

////////////////[blinding]
if (!(fspath.Contains("skimmed_MC/Bsmumu") || fspath.Contains("skimmed_MC/Bmumu"))){
    // if (B_MUCALC_mass<4766.0 || B_MUCALC_mass>5966.0) continue;
    if (B_MUCALC_mass<4766.0 || B_MUCALC_mass>5966.0 || (B_MUCALC_mass>=5166.0 && B_MUCALC_mass<=5526.0)){ 
        BlindCut+=1;
        continue;} //exclude blinded region
}
////////////////

////////////////[pass triggers] 

    // if (run_number >= 276073 && run_number <= 276954) newtree2015D->Fill(); //D
    // else if (run_number >= 278727 && run_number <= 279928) newtree2015E->Fill(); //E
    // else if (run_number >= 279932 && run_number <= 280422) newtree2015F->Fill(); //F
    // else if (run_number >= 280423 && run_number <= 281075) newtree2015G->Fill(); //G
    // else if (run_number >= 281130 && run_number <= 281411) newtree2015H->Fill(); //H
    // else if (run_number >= 282625 && run_number <= 284484) newtree2015J->Fill(); //J

    // else if (run_number >= 296939 && run_number <= 300287) newtree2016A->Fill();//A
    // else if (run_number >= 300345 && run_number <= 300908) newtree2016B->Fill();//B
    // else if (run_number >= 301912 && run_number <= 302393) newtree2016C->Fill(); // C
    // else if (run_number >= 302737 && run_number <= 303560) newtree2016D->Fill(); // D
    // else if (run_number >= 303638 && run_number <= 303892) newtree2016E->Fill(); // E
    // else if (run_number >= 303943 && run_number <= 304494) newtree2016F->Fill(); // F
    // else if (run_number >= 305291 && run_number <= 306714) newtree2016G->Fill(); // G
    // else if (run_number >= 307124 && run_number <= 308084) newtree2016I->Fill(); // I //first run_number not 
    // else if (run_number >= 309311 && run_number <= 309759) newtree2016K->Fill(); // K
    // else if (run_number >= 310015 && run_number <= 311481) newtree2016L->Fill(); // L 

    bool pass_trigger;
    if (run_number >= 296939 && run_number <= 311481) pass_trigger = ( HLT_trigger->find("HLT_mu6_mu4_bBmumu_Lxy0") != HLT_trigger->end() );
    else if (run_number >= 276073 && run_number <= 284484) pass_trigger = ( HLT_trigger->find("HLT_mu6_mu4_bBmumu") != HLT_trigger->end() ); 
    // if (fspath.Contains("data15")) pass_trigger = ( HLT_trigger->find("HLT_mu6_mu4_bBmumu") != HLT_trigger->end() );
    // if (fspath.Contains("data16")) pass_trigger = ( HLT_trigger->find("HLT_mu6_mu4_bBmumu_Lxy0") != HLT_trigger->end() );
    if (!pass_trigger){
        TriggerCut+=1;
    continue;}
////////////////

////////////////[1, muon istight]
    if (!Muon1_isTight || !Muon2_isTight){ 
        MuonTightCut+=1;
        continue;}
////////////////

////////////////[muon isaccept and iscombined]
    if (!Muon1_accept || !Muon2_accept || !Muon1_isCombinedMuon || !Muon2_isCombinedMuon){ 
        MuonCombinedCut+=1;
        continue;}
////////////////

////////////////[2, muonKin]
    if (Muon1_pT<4000. || TMath::Abs(Muon1_eta)>2.5 || Muon2_pT<4000. || TMath::Abs(Muon2_eta)>2.5){ 
        MuonKinCuts+=1;
        continue;}
////////////////

////////////////[3, Bkin]
    if (B_pT<8000. || TMath::Abs(B_eta)>2.5){ 
        BKinCut+=1;
        continue;}
////////////////

////////////////[4, Chi2NDF]
    if (B_fitChi2NDF>6.0){ 
        B_fitChi2NDFCut+=1;
        continue;}
////////////////

////////////////[5, additional cuts]
    if (Lxy<0. || TMath::Abs(a_2D)>1.0 || DR>1.5){ 
        AddCuts +=1;
        continue;}
////////////////

    // if (!pass_grl) continue; //commented by Aidan on Feb. 11, 2018
    EventsNotCut+=1;
    tf->Fill();
}

  ofstream myfile;
  if (fspath.Contains("data15")) myfile.open("./CutFlow2015_2018Jul18_2.txt", std::ios_base::app);
  if (fspath.Contains("data16") && fspath.Contains("physics_BphysDelayed")) myfile.open("./CutFlow2016delayed_2018Jul18_2.txt", std::ios_base::app);
  else if (fspath.Contains("data16")) myfile.open("./CutFlow2016_2018Jul18_2.txt", std::ios_base::app);
  if (fspath.Contains("skimmed_MC/Bsmumu")) myfile.open("./CutFlowBsmumuMC_2018Jul18_2.txt", std::ios_base::app);
  else if (fspath.Contains("skimmed_MC/Bmumu")) myfile.open("./CutFlowBmumuMC_2018Jul18_2.txt", std::ios_base::app);
  else if (fspath.Contains("skimmed_MC")) myfile.open("./CutFlowbbmumuXMC_2018Jul18_2.txt", std::ios_base::app);
  myfile<< "Directory Name: "<< fspath <<endl;
  myfile<< "Entries in original tree: "<< nevents <<endl;
  myfile<< "Blind Cut not passed: "<< BlindCut <<endl;
  myfile<< "TriggerCut not passed: "<< TriggerCut <<endl;
  myfile<< "MuonTightCut not passed: "<< MuonTightCut <<endl;
  myfile<< "MuonCombinedCut not passed: "<< MuonCombinedCut <<endl;
  myfile<< "MuonKinCuts not passed: "<< MuonKinCuts <<endl;
  myfile<< "BKinCut not passed: "<< BKinCut <<endl;
  myfile<< "B_fitChi2NDFCut not passed: "<< B_fitChi2NDFCut <<endl;
  myfile<< "Additional Cut not passed: "<< AddCuts <<endl;
  myfile<< "EventsNotCut: "<< EventsNotCut <<endl;
  myfile<< "Entries in final tree: "<< tf->GetEntries() <<endl;
  myfile<< "" << endl;
  myfile.close();

  // sw.Stop();
  // sw.Print();

  // fn->cd();
  // tf->Write();
  // fn->Close();
}

// int main(int argc, char* argv[])
// {
//   gSystem->Load("libdefinitions.so");
//   TString inpath;
//   if (argc>1) inpath = TString(argv[1]);
//   cutBatchBsmumu(inpath);
//   return 0;
// }
