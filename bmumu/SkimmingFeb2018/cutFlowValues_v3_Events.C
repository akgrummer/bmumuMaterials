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

void cutFlowValues_v3_Events(TString indir){
  // TString outdir("/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimFeb13_HLT_mu6_mu4_2016");
TString outdir("/afs/cern.ch/user/a/agrummer/www/bmumu/SkimmingFeb2018/EventCuts.root");
  TStopwatch sw;
  sw.Start();

  TString fspath(indir); //"specify path to dataset w/o slash at the end" 
  //fspath.Append("/user*.root");  // full flat ntuples 
  //fspath.Append("/skim*.root");  // OLD MC
  fspath.Append("/output*.root");
  cout << "Processing files: "<< fspath <<endl;
  TChain *ts = new TChain("T_mv");
  ts->Add(fspath);
////
  TString fnpath(outdir);
    // fnpath.Append("/LASTskim.");
  if (indir.Contains("skimmed_MC/Bsmumu")){
        if(fnpath.Contains(".root")) fnpath.ReplaceAll(".root", "");
        fnpath.Append("BsmumuMC");
  }else{
      Int_t lsl = indir.Index("acampove");
      Int_t lsp = indir.Index(".period");
      Int_t len = indir.Length();
  
      Int_t outlsl = outdir.Index(".root");
      // Int_t outlsp = indir.Last(".period");
      Int_t outlen = outdir.Length();
  
      // cout<<" lsl "<< lsl <<" lsp "<< lsp <<" len "<< len <<" outlsl "<< outlsl <<" outlen "<< outlen <<endl;
      if (outlsl!=-1) fnpath.Remove(outlsl+1, outlen); 
      // fnpath.Remove(".root"); 
      // fnpath.Append(indir(lsl+1, len-lsl-1)); 
      if (lsl!=-1 && lsp!=-1) fnpath.Append(indir(lsl+9, lsp-lsl-1));} 
    fnpath.Append(".root"); //if getting ..root check lsl and lsp
////  

  
  cout<< "Entries in original tree: "<< ts->GetEntries() <<endl;
  auto nentries = ts->GetEntries();

  //tn->SetBranchStatus("*",0);
  double KPlus_pT, KPlus_eta, KPlus_phi, KMinus_pT, KMinus_eta, KMinus_phi, Jpsi_fitChi2;
  double B_pT, B_eta, Lxy, a_2D, DR, Muon1_pT, Muon2_pT, Muon1_eta, Muon2_eta;
  float B_MUCALC_mass;
  double B_fitChi2NDF, Jpsi_mass;
  int KMinus_pass,KPlus_pass,Jpsi_fitNDF, Muon1_accept, Muon2_accept;
  double TRUTH_MuMinus_pT, TRUTH_MuPlus_pT, TRUTH_MuMinus_eta, TRUTH_MuPlus_eta;
  int isSignal;
  bool Muon1_isCombinedMuon, Muon2_isCombinedMuon, pass_grl, Muon1_isTight, Muon2_isTight;
  bool is_2015, is_2016main, pass_trigger, Trigger_Matched;
  map_str_int *HLT_trigger = 0;
  // map_str_int *HLT_trigger = 0;
  map_str_int *L1_trigger = 0;
  UInt_t run_number;
  ULong64_t event_number;
    
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
  ts->SetBranchAddress("event_number",&event_number);
  ts->SetBranchAddress("Trigger_Matched",  &Trigger_Matched);

if (fspath.Contains("skimmed_MC/Bsmumu")){
  ts->SetBranchAddress("isSignal",  &isSignal);
  ts->SetBranchAddress("TRUTH_MuMinus_pT",  &TRUTH_MuMinus_pT);
  ts->SetBranchAddress("TRUTH_MuPlus_pT",  &TRUTH_MuPlus_pT);
  ts->SetBranchAddress("TRUTH_MuMinus_eta",  &TRUTH_MuMinus_eta);
  ts->SetBranchAddress("TRUTH_MuPlus_eta",  &TRUTH_MuPlus_eta); 
}

  //  ts->SetBranchAddress("",  &);
  // ts->SetBranchAddress("pass_grl",  &pass_grl);//commented by Aidan on Feb. 11, 2018  reason: no grl branch in this version of files.
  ts->SetBranchAddress("HLT_trigger",&HLT_trigger);
  ts->SetBranchAddress("L1_trigger",&L1_trigger);

  TFile *fn = new TFile(fnpath,"recreate");
  TTree *tf = ts->CloneTree(0);
  cout<< "Now loop over original tree" << endl; 

  Int_t BlindCut(0);
  Int_t sigPreCut(0);
  Int_t TriggerCut(0);
  Int_t MuonTightCut(0);
  // Int_t MuonCombinedCut(0);
  Int_t MuonKinCuts(0);
  Int_t BKinCut(0);
  Int_t B_fitChi2NDFCut(0);
  Int_t AddCuts(0);
  Int_t EventsNotCut(0);

set< pair<UInt_t,ULong64_t> > TotalEventsSet;
set< pair<UInt_t,ULong64_t> > BlindSet;
set< pair<UInt_t,ULong64_t> > sigPreSet;
set< pair<UInt_t,ULong64_t> > TriggerSet;
set< pair<UInt_t,ULong64_t> > MuonTightSet;
set< pair<UInt_t,ULong64_t> > MuonKinSet;
set< pair<UInt_t,ULong64_t> > BKinSet;
set< pair<UInt_t,ULong64_t> > B_fitChi2NDFSet;
set< pair<UInt_t,ULong64_t> > AddSet;
set< pair<UInt_t,ULong64_t> > EventsNotSet;
Int_t dummy1(0);
Int_t dummy2(0);

//Event histograms
TH1F *TotalEvents = new TH1F("TotalEvents", "TotalEvents", 2, 0, 2);
TH1F *BlindHist = new TH1F("BlindHist", "BlindHistTitle", 2, 0, 2);
TH1F *sigPreHist = new TH1F("sigPreHist", "sigPreHistTitle", 2, 0, 2);
TH1F *TriggerHist = new TH1F("TriggerHist", "TriggerHistTitle", 2, 0, 2);
TH1F *MuonTightHist = new TH1F("MuonTightHist", "MuonTightHistTitle", 2, 0, 2);
TH1F *MuonKinHist = new TH1F("MuonKinHist", "MuonKinHistTitle", 2, 0, 2);
TH1F *BKinHist = new TH1F("BKinHist", "BKinHistTitle", 2, 0, 2);
TH1F *B_fitChi2NDFHist = new TH1F("B_fitChi2NDFHist", "B_fitChi2NDFHistTitle", 2, 0, 2);
TH1F *AddHist = new TH1F("AddHist", "AddHistTitle", 2, 0, 2);
TH1F *EventsNotHist = new TH1F("EventsNotHist", "EventsNotHistTitle", 2, 0, 2);

//Candidate Histograms
TH1F *TotalCandidates = new TH1F("TotalCandidates", "TotalCandidates", 2, 0, 2);
TH1F *BlindHistCan = new TH1F("BlindHistCan", "BlindHistCanTitle", 2, 0, 2);
TH1F *sigPreHistCan = new TH1F("sigPreHistCan", "sigPreHistCanTitle", 2, 0, 2);
TH1F *TriggerHistCan = new TH1F("TriggerHistCan", "TriggerHistCanTitle", 2, 0, 2);
TH1F *MuonTightHistCan = new TH1F("MuonTightHistCan", "MuonTightHistCanTitle", 2, 0, 2);
TH1F *MuonKinHistCan = new TH1F("MuonKinHistCan", "MuonKinHistCanTitle", 2, 0, 2);
TH1F *BKinHistCan = new TH1F("BKinHistCan", "BKinHistCanTitle", 2, 0, 2);
TH1F *B_fitChi2NDFHistCan = new TH1F("B_fitChi2NDFHistCan", "B_fitChi2NDFHistCanTitle", 2, 0, 2);
TH1F *AddHistCan = new TH1F("AddHistCan", "AddHistCanTitle", 2, 0, 2);
TH1F *EventsNotHistCan = new TH1F("EventsNotHistCan", "EventsNotHistCanTitle", 2, 0, 2);


for (auto ievent=0; ievent<nentries; ievent++){
    if (ievent%100000==0) cout << "Processing event "<< ievent << endl;
    ts->GetEntry(ievent);
////////////////
    // dummy1 = TotalEventsSet.size();
    TotalEventsSet.insert(make_pair(run_number,event_number));
    // dummy2 = TotalEventsSet.size();
    // if(dummy1 == dummy2) continue;
////////////////[blinding]
    //IF NOT signal
if (!(fspath.Contains("skimmed_MC/Bsmumu") || fspath.Contains("skimmed_MC/Bmumu"))){
    // if (B_MUCALC_mass<4766.0 || B_MUCALC_mass>5966.0) continue;
    // if (B_MUCALC_mass<4766.0 || B_MUCALC_mass>5966.0){
    if (B_MUCALC_mass>0){
        // if (B_MUCALC_mass<4766.0 || B_MUCALC_mass>5966.0 || (B_MUCALC_mass>=5166.0 && B_MUCALC_mass<=5526.0)){ 
        if (B_MUCALC_mass<4766.0 || B_MUCALC_mass>5966.0){ 
        BlindCut+=1;
        continue;}
    }
} else{
    if (TRUTH_MuMinus_pT<3500. || TRUTH_MuPlus_pT<3500. || fabs(TRUTH_MuPlus_eta)>2.6 || fabs(TRUTH_MuMinus_eta)>2.6 || isSignal == 0){
        sigPreCut+=1;
        continue;} //FIXME bbmumuX
        sigPreSet.insert(make_pair(run_number,event_number));//just a check now.
}
if (!(fspath.Contains("skimmed_MC/Bsmumu") || fspath.Contains("skimmed_MC/Bmumu"))) BlindSet.insert(make_pair(run_number,event_number));

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

    // bool pass_trigger;
    // if (run_number >= 296939 && run_number <= 311481) pass_trigger = ( HLT_trigger->find("HLT_mu6_mu4_bBmumu_Lxy0") != HLT_trigger->end() );
    // else if (run_number >= 276073 && run_number <= 284484) pass_trigger = ( HLT_trigger->find("HLT_mu6_mu4_bBmumu") != HLT_trigger->end() ); 
    // // if (fspath.Contains("data15")) pass_trigger = ( HLT_trigger->find("HLT_mu6_mu4_bBmumu") != HLT_trigger->end() );
    // // if (fspath.Contains("data16")) pass_trigger = ( HLT_trigger->find("HLT_mu6_mu4_bBmumu_Lxy0") != HLT_trigger->end() );
    // if (!pass_trigger){
    //     TriggerCut+=1;
    // continue;}

      is_2015        = (run_number <= 284484);
      is_2016main    = (run_number > 284484 );
      pass_trigger  = ( is_2015 && HLT_trigger->find("HLT_mu6_mu4_bBmumu") != HLT_trigger->end());
      pass_trigger |= ( is_2016main && HLT_trigger->find("HLT_mu6_mu4_bBmumu_Lxy0") != HLT_trigger->end()); 
      pass_trigger &= ( L1_trigger->find("L1_MU6_2MU4") != L1_trigger->end() );
      if (!pass_trigger){
            TriggerCut+=1;
            continue;}
            // TriggerSet.insert(make_pair(run_number,event_number));
      if (!Trigger_Matched){
            TriggerCut+=1;
            continue;}
            TriggerSet.insert(make_pair(run_number,event_number));

////////////////

////////////////[1, muon istight]
    if (!Muon1_isTight || !Muon2_isTight || !Muon1_accept || !Muon2_accept){ 
        MuonTightCut+=1;
        continue;}
        MuonTightSet.insert(make_pair(run_number,event_number));
////////////////

////////////////[2, muonKin]
    if (!Muon1_isCombinedMuon || !Muon2_isCombinedMuon){ 
        MuonKinCuts+=1;
        continue;}
        // MuonKinSet.insert(make_pair(run_number,event_number));
    // if (Muon1_pT<4000. || TMath::Abs(Muon1_eta)>2.5 || Muon2_pT<4000. || TMath::Abs(Muon2_eta)>2.5){ 
    if (Muon1_pT<4000. || Muon2_pT<4000. || (Muon1_pT<6000. && Muon2_pT<6000.) || TMath::Abs(Muon1_eta)>2.5 || TMath::Abs(Muon2_eta)>2.5){ 
        MuonKinCuts+=1;
        continue;}
        MuonKinSet.insert(make_pair(run_number,event_number));
        // if (true){
        // w1 += weight;
        // }
////////////////

////////////////[3, Bkin]
    if (B_pT<8000. || TMath::Abs(B_eta)>2.5){ 
        BKinCut+=1;
        continue;}
        BKinSet.insert(make_pair(run_number,event_number));
        // w2 += weight;
////////////////

////////////////[4, Chi2NDF]
    if (B_fitChi2NDF>6.0){ 
        B_fitChi2NDFCut+=1;
        continue;}
        B_fitChi2NDFSet.insert(make_pair(run_number,event_number));
////////////////

////////////////[5, additional cuts]
    if (Lxy<0. || TMath::Abs(a_2D)>1.0 || DR>1.5){ 
        AddCuts +=1;
        continue;}
        AddSet.insert(make_pair(run_number,event_number));
////////////////

    // if (!pass_grl) continue; //commented by Aidan on Feb. 11, 2018
    EventsNotCut+=1;
    EventsNotSet.insert(make_pair(run_number,event_number));
    // tf->Fill();
}
//Events
TotalEvents->SetBinContent(1, TotalEventsSet.size());
BlindHist->SetBinContent(1, BlindSet.size());
sigPreHist->SetBinContent(1, sigPreSet.size());
TriggerHist->SetBinContent(1, TriggerSet.size());
MuonTightHist->SetBinContent(1, MuonTightSet.size());
MuonKinHist->SetBinContent(1, MuonKinSet.size());
BKinHist->SetBinContent(1, BKinSet.size());
B_fitChi2NDFHist->SetBinContent(1, B_fitChi2NDFSet.size());
AddHist->SetBinContent(1, AddSet.size());
EventsNotHist->SetBinContent(1, EventsNotSet.size());
//Candidates
TotalCandidates->SetBinContent(1, nentries);
BlindHistCan->SetBinContent(1, BlindCut);
sigPreHistCan->SetBinContent(1, sigPreCut);
TriggerHistCan->SetBinContent(1, TriggerCut);
MuonTightHistCan->SetBinContent(1, MuonTightCut);
MuonKinHistCan->SetBinContent(1, MuonKinCuts);
BKinHistCan->SetBinContent(1, BKinCut);
B_fitChi2NDFHistCan->SetBinContent(1, B_fitChi2NDFCut);
AddHistCan->SetBinContent(1, AddCuts);
EventsNotHistCan->SetBinContent(1, EventsNotCut);

  // ofstream myfile;
  // TString DataName = "2018aug17";
  // if (fspath.Contains("data15")) myfile.open("./CutFlow2015_"+DataName+".txt", std::ios_base::app);
  // if (fspath.Contains("data16") && fspath.Contains("physics_BphysDelayed")) myfile.open("./CutFlow2016delayed_"+DataName+".txt", std::ios_base::app);
  // else if (fspath.Contains("data16")) myfile.open("./CutFlow2016_"+DataName+".txt", std::ios_base::app);
  // if (fspath.Contains("skimmed_MC/Bsmumu")) myfile.open("./CutFlowBsmumuMC_"+DataName+".txt", std::ios_base::app);
  // else if (fspath.Contains("skimmed_MC/Bmumu")) myfile.open("./CutFlowBmumuMC_"+DataName+".txt", std::ios_base::app);
  // else if (fspath.Contains("skimmed_MC")) myfile.open("./CutFlowbbmumuXMC_"+DataName+".txt", std::ios_base::app);
  // myfile<< "Directory Name: "<< fspath <<endl;
  // myfile<< "Entries in original tree: "<< nentries <<endl;
  // myfile<< "Blind Cut not passed: "<< BlindCut <<endl;
  // myfile<< "sigPre Cut not passed: "<< sigPreCut <<endl;
  // myfile<< "TriggerCut not passed: "<< TriggerCut <<endl;
  // myfile<< "MuonTightCut not passed: "<< MuonTightCut <<endl;
  // // myfile<< "MuonCombinedCut not passed: "<< MuonCombinedCut <<endl;
  // myfile<< "MuonKinCuts not passed: "<< MuonKinCuts <<endl;
  // myfile<< "BKinCut not passed: "<< BKinCut <<endl;
  // myfile<< "B_fitChi2NDFCut not passed: "<< B_fitChi2NDFCut <<endl;
  // myfile<< "Additional Cut not passed: "<< AddCuts <<endl;
  // myfile<< "EventsNotCut: "<< EventsNotCut <<endl;
  // myfile<< "Entries in final tree: "<< tf->GetEntries() <<endl;
  // myfile<< "" << endl;
  // myfile.close();

  // sw.Stop();
  // sw.Print();
cout<<"writing histograms to fnpath: " <<fnpath<<endl;
fn->cd();
TotalEvents->Write();
TotalCandidates->Write();
BlindHist->Write();
BlindHistCan->Write();
sigPreHist->Write();
sigPreHistCan->Write();
TriggerHist->Write();
TriggerHistCan->Write();
MuonTightHist->Write();
MuonTightHistCan->Write();
MuonKinHist->Write();
MuonKinHistCan->Write();
BKinHist->Write();
BKinHistCan->Write();
B_fitChi2NDFHist->Write();
B_fitChi2NDFHistCan->Write();
AddHist->Write();
AddHistCan->Write();
EventsNotHist->Write();
EventsNotHistCan->Write();
  // tf->Write();
fn->Close();
}

// int main(int argc, char* argv[])
// {
//   gSystem->Load("libdefinitions.so");
//   TString inpath;
//   if (argc>1) inpath = TString(argv[1]);
//   cutBatchBsmumu(inpath);
//   return 0;
// }
