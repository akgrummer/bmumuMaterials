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

// 534572

int CutValues(TTree *itree, TCut mycut){
    TString hname = "name1";
    // nentries=itree->GetEntries();
    // set< pair<UInt_t,ULong64_t> > TotalEventsSet;
    // for (auto ievent=0; ievent<nentries; ievent++){
    //     if (ievent%100000==0) cout << "Processing event "<< ievent << endl;
    //     ts->GetEntry(ievent);
    //     TotalEventsSet.insert(make_pair(run_number,event_number));
    // }
    itree->Draw("B_pT>>name1(100,0,3e6)",mycut,"egoff");
    // itree->Draw("Npv>>name1(100,0,100)",mycut,"egoff");
    TH1F *hist1;
    hist1 = (TH1F*)gDirectory->Get(hname);
    //oraganize output
    TString mycutString = (TString) mycut;
    Int_t outlsl = mycutString.First("==");
    Int_t outlen = mycutString.Length();
    if (outlsl!=-1) mycutString.Remove(outlsl+1, outlen);
    ////
    if (mycutString.EqualTo("")){
    cout<< "AllCandidates" << ": " << hist1->Integral(0,3e6+1) << endl;
    }else cout<< mycutString << ": " << hist1->Integral(0,3e6+1) << endl;
    return(0);
}

void WeightedEfficiencies(){
    TFile *ifile = new TFile("AidanOutput.root");
    TTree *itree = (TTree*)ifile->Get("T_mv");
    UInt_t run_number;
    ULong64_t event_number;
    itree->SetBranchAddress("run_number",&run_number);
    itree->SetBranchAddress("event_number",&event_number);
    // TCut mycut = "Lxy>0. && TMath::Abs(a_2D)<1.0 && DR<1.5";
    // TCut mycut = "";
    TString myWeight ="";
    myWeight = "PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf*CombWeights*Muon1_trigger_sf*Muon2_trigger_sf";
    // TString myWeight = "PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf*CombWeights";
    // mycut = "BlindCut==0";
    // mycut = "sigPreCut==10";
    // mycut = "B_fitChi2NDFCut==10";
    // mycut = "MuonTightCut==10";
TCut mycut = "";  
// TCut mycut1 = "BlindCut==10";
// TCut mycut2 = "sigPreCut==10";
// TCut mycut3 = "TriggerCut==10";
// TCut mycut4 = "MuonTightCut==10";
// // TCut mycut5 = "MuonCombinedCut==10";
// TCut mycut6 = "MuonKinCuts==10";
// TCut mycut7 = "BKinCut==10";
// TCut mycut8 = "B_fitChi2NDFCut==10";
// TCut mycut9 = "AddCuts==10";

TCut mycut1 = "BlindCut==0";
TCut mycut2 = "sigPreCut==0&&BlindCut==0";
TCut mycut3 = "TriggerCut==0&&sigPreCut==0&&BlindCut==0";
TCut mycut4 = "MuonTightCut==0&&TriggerCut==0&&sigPreCut==0&&BlindCut==0";
// TCut mycut5 = "MuonCombinedCut==0";
TCut mycut6 = "MuonKinCuts==0&&MuonTightCut==0&&TriggerCut==0&&sigPreCut==0&&BlindCut==0";
TCut mycut7 = "BKinCut==0&&MuonKinCuts==0&&MuonTightCut==0&&TriggerCut==0&&sigPreCut==0&&BlindCut==0";
TCut mycut8 = "B_fitChi2NDFCut==0&&BKinCut==0&&MuonKinCuts==0&&MuonTightCut==0&&TriggerCut==0&&sigPreCut==0&&BlindCut==0";
TCut mycut9 = "AddCuts==0&&B_fitChi2NDFCut==0&&BKinCut==0&&MuonKinCuts==0&&MuonTightCut==0&&TriggerCut==0&&sigPreCut==0&&BlindCut==0";

    // mycut = "TriggerCut==10";
    CutValues(itree, mycut*myWeight);
    CutValues(itree, mycut1*myWeight);
    CutValues(itree, mycut2*myWeight);
    CutValues(itree, mycut3*myWeight);
    CutValues(itree, mycut4*myWeight);
    // CutValues(itree, mycut5);
    CutValues(itree, mycut6*myWeight);
    CutValues(itree, mycut7*myWeight);
    CutValues(itree, mycut8*myWeight);
    CutValues(itree, mycut9*myWeight);
    // itree->Draw("B_pT>>name1(100,0,3e6)",mycut,"egoff");
    // TH1F *hist1;
    // hist1 = (TH1F*)gDirectory->Get(hname);
    // cout<< hist1->Integral() << endl;
    return(0);
}

