///Aidan
//notes: This version is used on the MC cuts (see SkimmingCommandLine.txt 2018 Aug 16)
// outputs candidate  numbers after subsequent cuts to a root file then WeightedEfficiencies.cpp is used locally to apply the cuts to the histograms.
//version 3 will apply cuts to events instead of candidates



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
#include "DDWQLC.h"
#include "TriggerWeights.h"

using namespace std;
typedef map<string, int>      map_str_int;

void cutFlowValues_v2Weights(TString indir){
  // TString outdir("/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimFeb13_HLT_mu6_mu4_2016");
  TString outdir("/afs/cern.ch/user/a/agrummer/www/bmumu/SkimmingFeb2018/AidanOutput.root");

  TStopwatch sw;
  sw.Start();

  ////////////////////////////////////////////////////////
  TString QLCfileName = "/afs/cern.ch/user/a/agrummer/www/bmumu/SkimmingFeb2018/QLCfile_BsToMuMu.root";
  DDWQLC QLC(QLCfileName, "h_QLC_err_BsMuMu", "h_QLC_BsMuMu");

  TString DDWfileName = "/afs/cern.ch/user/a/agrummer/www/bmumu/SkimmingFeb2018/DDWfile_BpToJpsiK.root";
  DDWQLC DDW(DDWfileName,  "h_covarianceDDW_even_BpJpsiK", "h_DDWpt_even_BpJpsiK", "h_DDWeta_even_BpJpsiK");

  cout << "Done reading QLC and DDW files." << endl;

  TriggerWeights myWeights("singleMu_SF_data1516_perperiod.root");

  cout << "Done reading trigger weight files." << endl;
  ////////////////////////////////////////////////////////

  TString fspath(indir); //"specify path to dataset w/o slash at the end" 
  //fspath.Append("/user*.root");  // full flat ntuples 
  //fspath.Append("/skim*.root");  // OLD MC
  fspath.Append("/output*.root");
  cout << "Processing files: "<< fspath <<endl;
  TChain *ts = new TChain("T_mv");
  ts->Add(fspath);

  TString fnpath(outdir);
  // fnpath.Append("/LASTskim.");
  // Int_t lsl = indir.Last('/');
  // Int_t len = indir.Length();
  // fnpath.Append(indir(lsl+1, len-lsl-1)); 
  // fnpath.Append(".root");
  
  cout<< "Entries in original tree: "<< ts->GetEntries() <<endl;
  auto nevents = ts->GetEntries();

  //tn->SetBranchStatus("*",0);
  double KPlus_pT, KPlus_eta, KPlus_phi, KMinus_pT, KMinus_eta, KMinus_phi, Jpsi_fitChi2;
  double B_pT, B_eta, Lxy, a_2D, DR, Muon1_pT, Muon2_pT, Muon1_eta, Muon2_eta;
  float B_MUCALC_mass;
  double B_fitChi2NDF, Jpsi_mass, CombWeights;
  int KMinus_pass,KPlus_pass,Jpsi_fitNDF, Muon1_accept, Muon2_accept;
  double TRUTH_MuMinus_pT, TRUTH_MuPlus_pT, TRUTH_MuMinus_eta, TRUTH_MuPlus_eta;
  int isSignal;
  bool Muon1_isCombinedMuon, Muon2_isCombinedMuon, pass_grl, Muon1_isTight, Muon2_isTight;
  bool is_2015, is_2016main, pass_trigger, Trigger_Matched;
  map_str_int *HLT_trigger = 0;
  // map_str_int *HLT_trigger = 0;
  map_str_int *L1_trigger = 0;
  UInt_t run_number;
  Float_t Muon1_trigger_sf, Muon1_trigger_sf_staterr, Muon1_trigger_sf_systerr;
  Float_t Muon2_trigger_sf, Muon2_trigger_sf_staterr, Muon2_trigger_sf_systerr;
  int status;  

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
  ts->SetBranchAddress("Trigger_Matched",  &Trigger_Matched);
  ts->SetBranchAddress("CombWeights", &CombWeights);
  
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
 

  Int_t AddCuts(0);
  Int_t BlindCut(0);
  Int_t sigPreCut(0);
  Int_t B_fitChi2NDFCut(0);
  Int_t TriggerCut(0);
  Int_t BKinCut(0);
  Int_t MuonCombinedCut(0);
  Int_t MuonTightCut(0);
  Int_t MuonKinCuts(0);
  Int_t EventsNotCut(0);

tf->Branch("AddCuts", &AddCuts, "AddCuts/I");
tf->Branch("BlindCut", &BlindCut, "BlindCut/I");
tf->Branch("sigPreCut", &sigPreCut, "sigPreCut/I");
tf->Branch("B_fitChi2NDFCut", &B_fitChi2NDFCut, "B_fitChi2NDFCut/I");
tf->Branch("TriggerCut", &TriggerCut, "TriggerCut/I");
tf->Branch("BKinCut", &BKinCut, "BKinCut/I");
tf->Branch("MuonCombinedCut", &MuonCombinedCut, "MuonCombinedCut/I");
tf->Branch("MuonTightCut", &MuonTightCut, "MuonTightCut/I");
tf->Branch("MuonKinCuts", &MuonKinCuts, "MuonKinCuts/I");
tf->Branch("EventsNotCut", &EventsNotCut, "EventsNotCut/I");
  TBranch* b11= tf->Branch("Muon1_trigger_sf",&Muon1_trigger_sf,"Muon1_trigger_sf/F");
  TBranch* b12= tf->Branch("Muon2_trigger_sf",&Muon2_trigger_sf,"Muon2_trigger_sf/F");

for (auto ievent=0; ievent<nevents; ievent++){
    if (ievent%100000==0) cout << "Processing event "<< ievent << endl;
    ts->GetEntry(ievent);

AddCuts = 0;
BlindCut = 0;
sigPreCut = 0;
B_fitChi2NDFCut = 0;
TriggerCut = 0;
BKinCut = 0;
MuonCombinedCut = 0;
MuonTightCut = 0;
MuonKinCuts = 0;
EventsNotCut = 0;
////////////////

    
      double QLCval = QLC.GetWeight(TMath::Abs(B_eta), B_pT);
      double DDWval = DDW.GetWeight(B_eta, B_pT);
      CombWeights = DDWval * QLCval;

      //should I really just set negative values to 1 by hand?
      if (CombWeights < 0.){
        CombWeights = 1.;
      }
      
       //FIXME MC
      float pTThreshold1 = 4.0;
      float pTThreshold2 = 6.0;
      if (Muon1_pT > Muon2_pT) {
      pTThreshold1 = 6.0;
      pTThreshold2 = 4.0;
      }
      status = myWeights.GetWeight( Muon1_pT/1000., Muon1_eta,  1. ,run_number, pTThreshold1, Muon1_trigger_sf, Muon1_trigger_sf_staterr, Muon1_trigger_sf_systerr);
      // if (status<0) cout << "status " << status << " for Muon1 (mu+)" << endl;
      status = myWeights.GetWeight( Muon2_pT/1000., Muon2_eta, -1. ,run_number, pTThreshold2, Muon2_trigger_sf, Muon2_trigger_sf_staterr, Muon2_trigger_sf_systerr);
      // if (status<0) cout << "status " << status << " for Muon2 (mu-)" << endl;


////////////////[blinding]
    //IF NOT signal
    if (!(fspath.Contains("skimmed_MC/Bsmumu") || fspath.Contains("skimmed_MC/Bmumu"))){

    // if (B_MUCALC_mass<4766.0 || B_MUCALC_mass>5966.0) continue;
    if (B_MUCALC_mass<4766.0 || B_MUCALC_mass>5966.0 || (B_MUCALC_mass>=5166.0 && B_MUCALC_mass<=5526.0)){ 
        BlindCut=10;
            tf->Fill();
    continue;
       } //exclude blinded region
    } else{
    if (TRUTH_MuMinus_pT<3500. || TRUTH_MuPlus_pT<3500. || fabs(TRUTH_MuPlus_eta)>2.6 || fabs(TRUTH_MuMinus_eta)>2.6 || isSignal == 0){
        sigPreCut=10;
            tf->Fill();
    continue;
       } //FIXME bbmumuX
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

    // bool pass_trigger;
    // if (run_number >= 296939 && run_number <= 311481) pass_trigger = ( HLT_trigger->find("HLT_mu6_mu4_bBmumu_Lxy0") != HLT_trigger->end() );
    // else if (run_number >= 276073 && run_number <= 284484) pass_trigger = ( HLT_trigger->find("HLT_mu6_mu4_bBmumu") != HLT_trigger->end() ); 
    // // if (fspath.Contains("data15")) pass_trigger = ( HLT_trigger->find("HLT_mu6_mu4_bBmumu") != HLT_trigger->end() );
    // // if (fspath.Contains("data16")) pass_trigger = ( HLT_trigger->find("HLT_mu6_mu4_bBmumu_Lxy0") != HLT_trigger->end() );
    // if (!pass_trigger){
    //     TriggerCut=1;
    //}

      is_2015        = (run_number <= 284484);
      is_2016main    = (run_number > 284484 );
      pass_trigger  = ( is_2015 && HLT_trigger->find("HLT_mu6_mu4_bBmumu") != HLT_trigger->end());
      pass_trigger |= ( is_2016main && HLT_trigger->find("HLT_mu6_mu4_bBmumu_Lxy0") != HLT_trigger->end()); 
      pass_trigger &= ( L1_trigger->find("L1_MU6_2MU4") != L1_trigger->end() );
      if (!pass_trigger){
            TriggerCut=10;
                tf->Fill();
    continue;
           }
      if (!Trigger_Matched){
            TriggerCut=10;
                tf->Fill();
    continue;
           }

////////////////

////////////////[1, muon istight]
    if (!Muon1_isTight || !Muon2_isTight || !Muon1_accept || !Muon2_accept){ 
        MuonTightCut=10;
            tf->Fill();
    continue;
       }
////////////////

////////////////[2, muonKin]
    if (!Muon1_isCombinedMuon || !Muon2_isCombinedMuon){ 
        MuonKinCuts=10;
            tf->Fill();
    continue;
       }
    // if (Muon1_pT<4000. || TMath::Abs(Muon1_eta)>2.5 || Muon2_pT<4000. || TMath::Abs(Muon2_eta)>2.5){ 
    if (Muon1_pT<4000. || Muon2_pT<4000. || (Muon1_pT<6000. && Muon2_pT<6000.) || TMath::Abs(Muon1_eta)>2.5 || TMath::Abs(Muon2_eta)>2.5){ 
        MuonKinCuts=10;
            tf->Fill();
    continue;
       }
////////////////

////////////////[3, Bkin]
    if (B_pT<8000. || TMath::Abs(B_eta)>2.5){ 
        BKinCut=10;
            tf->Fill();
    continue;
       }
////////////////

////////////////[4, Chi2NDF]
    if (B_fitChi2NDF>6.0){ 
        B_fitChi2NDFCut=10;
            tf->Fill();
    continue;
       }
////////////////

////////////////[5, additional cuts]
    if (Lxy<0. || TMath::Abs(a_2D)>1.0 || DR>1.5){ 
        AddCuts =10;
            tf->Fill();
    continue;
       }
////////////////

    // if (!pass_grl) //commented by Aidan on Feb. 11, 2018
    // EventsNotCut=10;
    tf->Fill();
}

  // ofstream myfile;
  // TString DataName = "2018aug16";
  // if (fspath.Contains("data15")) myfile.open("./CutFlow2015_"+DataName+".txt", std::ios_base::app);
  // if (fspath.Contains("data16") && fspath.Contains("physics_BphysDelayed")) myfile.open("./CutFlow2016delayed_"+DataName+".txt", std::ios_base::app);
  // else if (fspath.Contains("data16")) myfile.open("./CutFlow2016_"+DataName+".txt", std::ios_base::app);
  // if (fspath.Contains("skimmed_MC/Bsmumu")) myfile.open("./CutFlowBsmumuMC_"+DataName+".txt", std::ios_base::app);
  // else if (fspath.Contains("skimmed_MC/Bmumu")) myfile.open("./CutFlowBmumuMC_"+DataName+".txt", std::ios_base::app);
  // else if (fspath.Contains("skimmed_MC")) myfile.open("./CutFlowbbmumuXMC_"+DataName+".txt", std::ios_base::app);
  // myfile<< "Directory Name: "<< fspath <<endl;
  // myfile<< "Entries in original tree: "<< nevents <<endl;
  // myfile<< "Blind Cut not passed: "<< BlindCut <<endl;
  // myfile<< "sigPre Cut not passed: "<< sigPreCut <<endl;
  // myfile<< "TriggerCut not passed: "<< TriggerCut <<endl;
  // myfile<< "MuonTightCut not passed: "<< MuonTightCut <<endl;
  // myfile<< "MuonCombinedCut not passed: "<< MuonCombinedCut <<endl;
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

  fn->cd();
  tf->Write();
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
