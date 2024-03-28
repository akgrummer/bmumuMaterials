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

void EventsCutFlow(){
    // TFile *ifile = new TFile("EventCutsTotals.root");
    // TFile *ifile = new TFile("EventCuts.data15_13TeV.periodD.root");
    TFile *ifile = new TFile("EventCutsBsmumuMC.root");
    // TTree *itree = (TTree*)ifile->Get("T_mv");
//events
    TH1F *TotalEvents = (TH1F*)ifile->Get("TotalEvents");
    TH1F *BlindHist = (TH1F*)ifile->Get("BlindHist");
    TH1F *sigPreHist = (TH1F*)ifile->Get("sigPreHist");
    TH1F *TriggerHist = (TH1F*)ifile->Get("TriggerHist");
    TH1F *MuonTightHist = (TH1F*)ifile->Get("MuonTightHist");
    TH1F *MuonKinHist = (TH1F*)ifile->Get("MuonKinHist");
    TH1F *BKinHist = (TH1F*)ifile->Get("BKinHist");
    TH1F *B_fitChi2NDFHist = (TH1F*)ifile->Get("B_fitChi2NDFHist");
    TH1F *AddHist = (TH1F*)ifile->Get("AddHist");
    TH1F *EventsNotHist = (TH1F*)ifile->Get("EventsNotHist");
//candidates
    TH1F *TotalCandidates = (TH1F*)ifile->Get("TotalCandidates");
    TH1F *BlindHistCan = (TH1F*)ifile->Get("BlindHistCan");
    TH1F *sigPreHistCan = (TH1F*)ifile->Get("sigPreHistCan");
    TH1F *TriggerHistCan = (TH1F*)ifile->Get("TriggerHistCan");
    TH1F *MuonTightHistCan = (TH1F*)ifile->Get("MuonTightHistCan");
    TH1F *MuonKinHistCan = (TH1F*)ifile->Get("MuonKinHistCan");
    TH1F *BKinHistCan = (TH1F*)ifile->Get("BKinHistCan");
    TH1F *B_fitChi2NDFHistCan = (TH1F*)ifile->Get("B_fitChi2NDFHistCan");
    TH1F *AddHistCan = (TH1F*)ifile->Get("AddHistCan");
    TH1F *EventsNotHistCan = (TH1F*)ifile->Get("EventsNotHistCan");
//events
    float TotalEventsValues(0);
    float BlindValues(0);
    float sigPreValues(0);
    float TriggerValues(0);
    float MuonTightValues(0);
    float MuonKinValues(0);
    float BKinValues(0);
    float B_fitChi2NDFValues(0);
    float AddValues(0);
    float EventsNotValues(0);
//candidates
    float TotalCandidatesVal(0);
    float BlindHistCanVal(0);
    float sigPreHistCanVal(0);
    float TriggerHistCanVal(0);
    float MuonTightHistCanVal(0);
    float MuonKinHistCanVal(0);
    float BKinHistCanVal(0);
    float B_fitChi2NDFHistCanVal(0);
    float AddHistCanVal(0);
    float EventsNotHistCanVal(0);
//candidates
    TotalCandidatesVal = TotalCandidates->Integral(0,2+1);
    BlindHistCanVal = TotalCandidatesVal - BlindHistCan->Integral(0,2+1);
    sigPreHistCanVal = BlindHistCanVal - sigPreHistCan->Integral(0,2+1);
    TriggerHistCanVal = sigPreHistCanVal - TriggerHistCan->Integral(0,2+1);
    MuonTightHistCanVal = TriggerHistCanVal - MuonTightHistCan->Integral(0,2+1);
    MuonKinHistCanVal = MuonTightHistCanVal - MuonKinHistCan->Integral(0,2+1);
    BKinHistCanVal = MuonKinHistCanVal - BKinHistCan->Integral(0,2+1);
    B_fitChi2NDFHistCanVal = BKinHistCanVal - B_fitChi2NDFHistCan->Integral(0,2+1);
    AddHistCanVal = B_fitChi2NDFHistCanVal - AddHistCan->Integral(0,2+1);
    EventsNotHistCanVal = EventsNotHistCan->Integral(0,2+1);
//events
    // TotalEventsValues = TotalEvents->Integral(0,2+1);
    // BlindValues = TotalEventsValues - BlindHist->Integral(0,2+1);
    // sigPreValues = BlindValues - sigPreHist->Integral(0,2+1);
    // TriggerValues = sigPreValues - TriggerHist->Integral(0,2+1);
    // MuonTightValues = TriggerValues - MuonTightHist->Integral(0,2+1);
    // MuonKinValues = MuonTightValues -MuonKinHist->Integral(0,2+1);
    // BKinValues = MuonKinValues - BKinHist->Integral(0,2+1);
    // B_fitChi2NDFValues = BKinValues - B_fitChi2NDFHist->Integral(0,2+1);
    // AddValues = B_fitChi2NDFValues - AddHist->Integral(0,2+1);
    // EventsNotValues = EventsNotHist->Integral(0,2+1);
//
    // TotalEventsValues = TotalEvents->Integral(0,2+1);
    // BlindValues = TotalCandidatesVal - BlindHist->Integral(0,2+1);
    // sigPreValues = BlindHistCanVal - sigPreHist->Integral(0,2+1);
    // TriggerValues = sigPreHistCanVal - TriggerHist->Integral(0,2+1);
    // MuonTightValues = TriggerHistCanVal - MuonTightHist->Integral(0,2+1);
    // MuonKinValues = MuonTightHistCanVal -MuonKinHist->Integral(0,2+1);
    // BKinValues = MuonKinHistCanVal - BKinHist->Integral(0,2+1);
    // B_fitChi2NDFValues = BKinHistCanVal - B_fitChi2NDFHist->Integral(0,2+1);
    // AddValues = B_fitChi2NDFHistCanVal - AddHist->Integral(0,2+1);
    // EventsNotValues = EventsNotHist->Integral(0,2+1);

    TotalEventsValues = TotalEvents->Integral(0,2+1);
    BlindValues = BlindHist->Integral(0,2+1);
    sigPreValues = sigPreHist->Integral(0,2+1);
    TriggerValues = TriggerHist->Integral(0,2+1);
    MuonTightValues = MuonTightHist->Integral(0,2+1);
    MuonKinValues = MuonKinHist->Integral(0,2+1);
    BKinValues = BKinHist->Integral(0,2+1);
    B_fitChi2NDFValues = B_fitChi2NDFHist->Integral(0,2+1);
    AddValues = AddHist->Integral(0,2+1);
    EventsNotValues = EventsNotHist->Integral(0,2+1);

 // h1->Integral(0,100+1);
    //events
    cout<<fixed << "TotalEvents: "<<TotalEventsValues << endl;
    cout<<fixed << "BlindHist Cut: "<<BlindValues << endl;
    cout<<fixed << "sigPreHist Cut: "<<sigPreValues << endl;
    cout<<fixed << "TriggerHist Cut: "<<TriggerValues<<"   " << TriggerValues/BlindValues<< endl;
    cout<<fixed << "MuonTightHist Cut: "<<MuonTightValues<<"   " << MuonTightValues/BlindValues<< endl;
    cout<<fixed << "MuonKinHist Cut: "<<MuonKinValues<<"   " << MuonKinValues/BlindValues<< endl;
    cout<<fixed << "BKinHist Cut: "<<BKinValues<<"   " << BKinValues/BlindValues<< endl;
    cout<<fixed << "B_fitChi2NDFHist Cut: "<<B_fitChi2NDFValues<<"   " << B_fitChi2NDFValues/BlindValues<< endl;
    cout<<fixed << "AddHist Cut: "<<AddValues<<"   " << AddValues/BlindValues<< endl;
    cout<<fixed << "EventsNotHist Cut: "<<EventsNotValues << endl;
//candidate cuts
    // cout<<endl;
    // cout<<"candidates cut"<<endl;
    // cout << "TotalCandidates: "<<TotalCandidates->Integral(0,2+1)<< endl;
    // cout << "BlindHistCan Cut: "<<BlindHistCan->Integral(0,2+1)<< endl;
    // cout << "sigPreHistCan Cut: "<<sigPreHistCan->Integral(0,2+1)<< endl;
    // cout << "TriggerHistCan Cut: "<<TriggerHistCan->Integral(0,2+1)<< endl;
    // cout << "MuonTightHistCan Cut: "<<MuonTightHistCan->Integral(0,2+1)<< endl;
    // cout << "MuonKinHistCan Cut: "<<MuonKinHistCan->Integral(0,2+1)<< endl;
    // cout << "BKinHistCan Cut: "<<BKinHistCan->Integral(0,2+1)<< endl;
    // cout << "B_fitChi2NDFHistCan Cut: "<<B_fitChi2NDFHistCan->Integral(0,2+1)<< endl;
    // cout << "AddHistCan Cut: "<<AddHistCan->Integral(0,2+1)<< endl;
    // cout << "EventsNotHistCan Cut: "<<EventsNotHistCan->Integral(0,2+1)<< endl;
cout<<endl;

//candidates
    cout<<fixed << "TotalCandidatesVal: "<<TotalCandidatesVal<< endl;
    cout<<fixed << "BlindHistCanVal Entries: "<<BlindHistCanVal<< endl;
    cout<<fixed << "sigPreHistCanVal Entries: "<<sigPreHistCanVal<< endl;
    cout<<fixed << "TriggerHistCanVal Entries: "<<TriggerHistCanVal<<"   "<<TriggerHistCanVal/BlindHistCanVal<< endl;
    cout<<fixed << "MuonTightHistCanVal Entries: "<<MuonTightHistCanVal<<"   "<<MuonTightHistCanVal/BlindHistCanVal<< endl;
    cout<<fixed << "MuonKinHistCanVal Entries: "<<MuonKinHistCanVal<<"   "<<MuonKinHistCanVal/BlindHistCanVal<< endl;
    cout<<fixed << "BKinHistCanVal Entries: "<<BKinHistCanVal<<"   "<<BKinHistCanVal/BlindHistCanVal<< endl;
    cout<<fixed << "B_fitChi2NDFHistCanVal Entries: "<<B_fitChi2NDFHistCanVal<<"   "<<B_fitChi2NDFHistCanVal/BlindHistCanVal<< endl;
    cout<<fixed << "AddHistCanVal Entries: "<<AddHistCanVal<<"   "<<AddHistCanVal/BlindHistCanVal<< endl;
    cout<<fixed << "EventsNotHistCanVal Entries: "<<EventsNotHistCanVal<<"   "<<EventsNotHistCanVal/BlindHistCanVal<< endl;
cout<<endl;
//events
    // cout << "TotalEvents: "<<TotalEventsValues<< endl;
    // cout << "BlindHist Entries: "<<BlindValues<< endl;
    // cout << "sigPreHist Entries: "<<sigPreValues<< endl;
    // cout << "TriggerHist Entries: "<<TriggerValues<<"   "<<TriggerValues/BlindValues<< endl;
    // cout << "MuonTightHist Entries: "<<MuonTightValues<<"   "<<MuonTightValues/BlindValues<< endl;
    // cout << "MuonKinHist Entries: "<<MuonKinValues<<"   "<<MuonKinValues/BlindValues<< endl;
    // cout << "BKinHist Entries: "<<BKinValues<<"   "<<BKinValues/BlindValues<< endl;
    // cout << "B_fitChi2NDFHist Entries: "<<B_fitChi2NDFValues<<"   "<<B_fitChi2NDFValues/BlindValues<< endl;
    // cout << "AddHist Entries: "<<AddValues<<"   "<<AddValues/BlindValues<< endl;
    // cout << "EventsNotHist Entries: "<<EventsNotValues<<"   "<<EventsNotValues/BlindValues<< endl;

    // cout << "TriggerHist Efficiencies: "<<TriggerValues/BlindValues<< endl;
    // cout << "MuonTightHist Efficiencies: "<<MuonTightValues/BlindValues<< endl;
    // cout << "MuonKinHist Efficiencies: "<<MuonKinValues/BlindValues<< endl;
    // cout << "BKinHist Efficiencies: "<<BKinValues/BlindValues<< endl;
    // cout << "B_fitChi2NDFHist Efficiencies: "<<B_fitChi2NDFValues/BlindValues<< endl;
    // cout << "AddHist Efficiencies: "<<AddValues/BlindValues<< endl;
    // cout << "EventsNotHist Efficiencies: "<<EventsNotValues/BlindValues<< endl;

    // TCut mycut = "Lxy>0. && TMath::Abs(a_2D)<1.0 && DR<1.5";
    // TCut mycut = "";
    // TString myWeight = "PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf*CombWeights";
    // mycut = "BlindCut==0";
    // mycut = "sigPreCut==10";
    // mycut = "B_fitChi2NDFCut==10";
    // mycut = "MuonTightCut==10";

    // TString myWeight ="";
    // myWeight = "PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf*CombWeights*Muon1_trigger_sf*Muon2_trigger_sf";
// TCut mycut = "";  
// TCut mycut1 = "BlindCut==10";
// TCut mycut2 = "sigPreCut==10";
// TCut mycut3 = "TriggerCut==10";
// TCut mycut4 = "MuonTightCut==10";
// // TCut mycut5 = "MuonCombinedCut==10";
// TCut mycut6 = "MuonKinCuts==10";
// TCut mycut7 = "BKinCut==10";
// TCut mycut8 = "B_fitChi2NDFCut==10";
// TCut mycut9 = "AddCuts==10";

    // mycut = "TriggerCut==10";
    // CutValues(itree, mycut*myWeight);
    // CutValues(itree, mycut1*myWeight);
    // CutValues(itree, mycut2*myWeight);
    // CutValues(itree, mycut3*myWeight);
    // CutValues(itree, mycut4*myWeight);
    // // CutValues(itree, mycut5);
    // CutValues(itree, mycut6*myWeight);
    // CutValues(itree, mycut7*myWeight);
    // CutValues(itree, mycut8*myWeight);
    // CutValues(itree, mycut9*myWeight);
    // // itree->Draw("B_pT>>name1(100,0,3e6)",mycut,"egoff");
    // TH1F *hist1;
    // hist1 = (TH1F*)gDirectory->Get(hname);
    // cout<< hist1->Integral() << endl;
    return(0);
}

