//
// example how to read all track ntuples
//
// iskander(dot)ibragimov(at)cern(dot)ch
// 
// setupATLAS 
// lsetup "root 6.10.06-x86_64-slc6-gcc62-opt"
//  
//This script ported from IsolationStudy_vChi2hist_v2
//
//ID hits v2 compares 
// all trks, is tight primary, run1 id constaints, run1 id constraints but with IBL
// not been implemented by jun12
//
//v3 is for the new 2020 nTuples
//
//v4 includes an intersect requirement - only events that are in both new and old ntuples are considered.
#include "TCut.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TLegend.h"
#include "TVector3.h"
#include "TH1.h"
#include "TBranch.h"
#include "TCanvas.h"
#include <iostream>
#include <dirent.h>
#include <TChain.h>
#include <algorithm>
#include "../../../Utils/AtlasStyle/AtlasLabels.C"
#include "../../../Utils/AtlasStyle/AtlasLabels.h"
#include "../../../Utils/AtlasStyle/AtlasUtils.C"
#include "../../../Utils/AtlasStyle/AtlasUtils.h"
#include "../../../Utils/AtlasStyle/AtlasStyle.C"
#include "../../../Utils/AtlasStyle/AtlasStyle.h"

using namespace std;
typedef std::vector<unsigned int>  v_uint;
typedef std::vector<int>           v_int;
typedef std::vector<float>         v_float;
typedef std::vector<double>        v_double;


bool hasEnding(std::string const &fullString, std::string const &ending) {
  if (fullString.length() >= ending.length()) {
    return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
  } else {
    return false;
  }
}

set<ULong64_t> intersection(TString myFile1 = "", TString myFile2 = "") {

  ULong64_t en1, en2;
  set<ULong64_t> ens1;
  set<ULong64_t> ens2;

  // TFile* file1 = new TFile(myFile1);
  // TTree* tr1 = (TTree*)file1->Get("T_mv");
  TChain* tr1 = new TChain("T_mv");
  tr1->Add(myFile1);
  cout<< "Entries in original tree of file 1: "<< tr1->GetEntries() <<endl;
  tr1->SetBranchStatus("*", 0);
  tr1->SetBranchStatus("event_number", 1);
  tr1->SetBranchAddress("event_number", &en1);
  for (int ii = 0; ii < tr1->GetEntries(); ++ii)
    {
      tr1->GetEntry(ii);
      ens1.insert(en1);
    }
  // file1->Close();

  TChain* tr2 = new TChain("T_mv");
  tr2->Add(myFile2);
  cout<< "Entries in original tree of file 2: "<< tr2->GetEntries() <<endl;
  tr2->SetBranchStatus("*", 0);
  tr2->SetBranchStatus("event_number", 1);
  tr2->SetBranchAddress("event_number", &en2);
  for (int ii = 0; ii < tr2->GetEntries(); ++ii)
    {
      tr2->GetEntry(ii);
      ens2.insert(en2);
    }
    // tr2->Close();

  set<ULong64_t> intersect;
  set_intersection(ens1.begin(), ens1.end(), ens2.begin(), ens2.end(),
           std::inserter(intersect, intersect.begin()));
  cout << "# of unique events in file 1: "<< ens1.size() << endl
  << "# of unique events in file 2: "<< ens2.size() << endl
  << "intersection of both: "<< intersect.size() << endl;  
  
  set<ULong64_t> uni;
  set_union(ens1.begin(), ens1.end(), ens2.begin(), ens2.end(), std::inserter(uni, uni.begin()));
  cout << "Union of both: "<< uni.size() << endl;

  set<ULong64_t> dif1;
  set_difference(ens1.begin(), ens1.end(), ens2.begin(), ens2.end(), std::inserter(dif1, dif1.begin()));
  set<ULong64_t> dif2;
  set_difference(ens2.begin(), ens2.end(), ens1.begin(), ens1.end(), std::inserter(dif2, dif2.begin()));
  cout << "Only in first: "<< dif1.size() << endl
  << " only in second: "<< dif2.size() << endl
  << " sum of both: " << dif1.size() + dif2.size() << endl;

 return  intersect;
}

// int main(int argc, char* argv[]) {
TCanvas* IsolationStudy_fileloop(TString myYear="", TString nTupleVer = ""){
  SetAtlasStyle();
  cout<<"DEBUG 1"<<endl;
  cout<< myYear<<" "<< endl;
  // TString fsname("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/skimmed_ntup/data18/Bmumu/user.ibragimo.17073931.Bmumu._000001_skimmed.root");
  // TString fsname("/afs/cern.ch/work/a/agrummer/BsmumuData/LastSkimOne2018Run/LASTskim_2017Bmumu.root");
  // TString fsname("/afs/cern.ch/work/a/agrummer/BsmumuData/LastSkimOne2018Run/LASTskim_2018_1.root");
  // TString indir("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/skimmed_ntup/data18/Bmumu/");
  TString indir("");
  TString indir1 = "/eos/home-a/agrummer/BsmumuData/2020nTuples/FinalSkim/v1/";
  TString indir2 = "/eos/home-a/agrummer/BsmumuData/FinalSkim/v6/";
    if (nTupleVer.EqualTo("new")){
        indir = indir1;}
    else{
        indir = indir2;}
  // int myYear(2018);
  if (myYear.EqualTo("2017")){
        // indir = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkim2017_2019Mar7/";
        // indir = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkim_2019Mar27/2017/";
        // indir = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/2017/";
        // indir = "/eos/home-a/agrummer/BsmumuData/FinalSkim/v6/2017/";
        indir = indir + "2017/";
        // AllPath = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/2017All/";
  }else if (myYear.EqualTo("2018")){
        // indir = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkim2018_2019Mar7/";
        // indir = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkim_2019Mar27/2018/";
        // indir = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/2018/";
        // indir = "/eos/home-a/agrummer/BsmumuData/FinalSkim/v6/2018/";
        indir = indir + "2018/";
        // AllPath = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/2018All/";
  }else if (myYear.EqualTo("2016")){
        // indir = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/2016/";
        // indir = "/eos/home-a/agrummer/BsmumuData/FinalSkim/v6/2016/";
      if (nTupleVer.EqualTo("new")){
            indir =  indir + "2016main/";}
      else{
            indir =  indir + "2016/";}
        // AllPath = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/2016All/";
  }else if (myYear.EqualTo("MC16a")){
        // indir = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkim_2019Mar27/MC16a/";
        // indir = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/MC16a/";
        // indir = "/eos/home-a/agrummer/BsmumuData/FinalSkim/v6/MC16a/";
        indir =  indir + "MC16a/";
        // AllPath = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/MC16aAll/";
  }else if (myYear.EqualTo("MC16d")){
        // indir = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkim_2019Mar27/MC16d/";
        // indir = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/MC16d/";
        // indir = "/eos/home-a/agrummer/BsmumuData/FinalSkim/v6/MC16d/";
        indir =  indir + "MC16d/";
        // AllPath = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/MC16dAll/";
  }else if (myYear.EqualTo("MC16e")){
        // indir = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkim_2019Mar27/MC16e/";
        // indir = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/MC16e/";
        // indir = "/eos/home-a/agrummer/BsmumuData/FinalSkim/v6/MC16e/";
        indir =  indir + "MC16e/";
        // AllPath = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/MC16eAll/";
  }
  TString finpath(indir);
    TString myFile1 = "";
    TString myFile2 = "";
    if (myYear.EqualTo("2016")){
       myFile1 = indir1+myYear+"main/*.root";}
    else{
       myFile1 = indir1+myYear+"/*.root";}
    myFile2 = indir2+myYear+"/*.root";

    set<ULong64_t> intersect;
    cout<< myFile1<<endl;
    intersect = intersection(myFile1, myFile2);
 

  DIR *dpdf;
  struct dirent *entry;
  const bool doIsoStudy = false; 
  const bool doCntTrksStudy = false; 
  const bool doChi2Study = false; 
  const bool doNtrkStudy = false; 
  const bool doDOCAStudy = false; 

  dpdf = opendir(finpath.Data());


    TH1F* h_chi2(NULL); TH1F* h_ntrks(NULL);
    TH1F* h_ntrks_all(NULL);
    TH1F* h_ntrks_assPV(NULL);
    TH1F* h_ntrks_otherPV(NULL);
    TH1F* h_ntrks_nonAss(NULL);
    TH1F* h_ntrks_orig(NULL); TH1F* h_iso(NULL); TH1F* h_myDR(NULL); TH1F* h_myDR_all(NULL);
    TH1F* h_my_iso(NULL); TH1F* h_my_iso_all(NULL);
    TH1F* h_trackPt(NULL); TH1F* h_trackPt_all(NULL);
    TH1F* h_B_pT(NULL);
    TH1F* h_my_iso_assPV(NULL);
    TH1F* h_my_iso_otherPV(NULL);
    TH1F* h_my_iso_nonAss(NULL);
    TH1F* h_chi2_all(NULL);
    TH1F* h_chi2_VTX_otherPV(NULL);
    TH1F* h_chi2_PV_otherPV(NULL);
    TH1F* h_chi2_VTX_nonAss(NULL);
    TH1F* h_chi2_PV_nonAss(NULL);
    TH1F* h_chi2_VTX_assPV(NULL);
    TH1F* h_chi2_PV_assPV(NULL);
    TH1F* h_chi2_VTX_all(NULL);
    TH1F* h_chi2_PV_all(NULL);
    TH1F* h_PIXhits_otherPV(NULL);
    TH1F* h_SCThits_otherPV(NULL);
    TH1F* h_PIXhits_assPV(NULL);
    TH1F* h_SCThits_assPV(NULL);
    TH1F* h_PIXhits_nonAss(NULL);
    TH1F* h_SCThits_nonAss(NULL);
    TH1F* h_PIXhits_chi2_6(NULL);
    TH1F* h_SCThits_chi2_6(NULL);
    TH1F* h_PIXhits_chi2_5(NULL);
    TH1F* h_SCThits_chi2_5(NULL);
    TH1F* h_PIXhits_chi2_4(NULL);
    TH1F* h_SCThits_chi2_4(NULL);
    //
    TH1F* h_chi2_orig(NULL);
    //
    TH1F* h_doca(NULL);
    TH1F* h_doca_orig(NULL);
    //
    TH1F* h_isoTrks_all_chi_5(NULL);
    TH1F* h_isoTrks_all_ID_chi_5(NULL);
    TH1F* h_isoTrks_all_ID_chi_4(NULL);
    TH1F* h_isoTrks_orig(NULL);

    TH1F* h_PIXhits_Loose(NULL);
    TH1F* h_SCThits_Loose(NULL);
    TH1F* h_IBLhits_Loose(NULL);
    TH1F* h_PIXhits_isTight(NULL);
    TH1F* h_SCThits_isTight(NULL);
    TH1F* h_IBLhits_isTight(NULL);
    TH1F* h_PIXhits_Run1(NULL);
    TH1F* h_SCThits_Run1(NULL);
    TH1F* h_IBLhits_Run1(NULL);
    TH1F* h_PIXhits_Run2(NULL);
    TH1F* h_SCThits_Run2(NULL);
    TH1F* h_IBLhits_Run2(NULL);
    // h_PIXhits_Loose   = new TH1F("h_PIXhits_Loose","chi2 to associated PV for selected tracks",100,0,100);
    // h_SCThits_Loose   = new TH1F("h_SCThits_Loose","chi2 to associated PV for selected tracks",100,0,100);
    // h_IBLhits_Loose   = new TH1F("h_IBLhits_Loose","chi2 to associated PV for selected tracks",100,0,100);
    // h_PIXhits_isTight   = new TH1F("h_PIXhits_isTight","chi2 to associated PV for selected tracks",100,0,100);
    // h_SCThits_isTight   = new TH1F("h_SCThits_isTight","chi2 to associated PV for selected tracks",100,0,100);
    // h_IBLhits_isTight   = new TH1F("h_IBLhits_isTight","chi2 to associated PV for selected tracks",100,0,100);
    // h_PIXhits_Run1   = new TH1F("h_PIXhits_Run1","chi2 to associated PV for selected tracks",100,0,100);
    // h_SCThits_Run1   = new TH1F("h_SCThits_Run1","chi2 to associated PV for selected tracks",100,0,100);
    // h_IBLhits_Run1   = new TH1F("h_IBLhits_Run1","chi2 to associated PV for selected tracks",100,0,100);
    h_PIXhits_Run2   = new TH1F("h_PIXhits_Run2","chi2 to associated PV for selected tracks",100,0,100);
    h_SCThits_Run2   = new TH1F("h_SCThits_Run2","chi2 to associated PV for selected tracks",100,0,100);
    // h_IBLhits_Run2   = new TH1F("h_IBLhits_Run2","chi2 to associated PV for selected tracks",100,0,100);

Int_t totalTracks(0);
Int_t totalEvCnt(0);
  // cout<<"DEBUG 2"<<endl;
  if (dpdf != NULL){
      // cout<<"DEBUG 2"<<endl;
    while (entry = readdir(dpdf)){
  // cout<<"DEBUG 2"<<endl;
      printf("Filename: %s\n", entry->d_name);

      if ( !hasEnding(entry->d_name, ".root") )  continue;  // exclude non-ROOT files 
     
      std::cout << "processing file: "<< entry->d_name << std::endl;
    
      TString fintemp(finpath);
      fintemp.Append(entry->d_name);
      TFile *fin = new TFile(fintemp);
      TTree *ts = (TTree*)fin->Get("T_mv");
      TTree *tev = (TTree*)fin->Get("EventInfo");

      std::cout << "# of candidates: "<<  ts->GetEntries() << std::endl;

  v_uint   *pv_type     = 0;
  v_float  *pv_z        = 0;
  v_float  *pv_sigma_z  = 0;
  v_int    *idtrk_pvidx = 0; 
  v_uint   *idtrk_pvidx_loose     = 0;
  v_uint   *idtrk_pvidx_nominal   = 0;
  v_uint   *idtrk_pvidx_tight     = 0;
  // v_int    *idtrk_isTightPrimary = 0; 
  v_int    *idtrk_nPIXhits  = 0;
  v_int    *idtrk_NIBLayer  = 0;
  v_int    *idtrk_nSCThits  = 0;
  v_int    *idtrk_nPIXDead  = 0;
  v_int    *idtrk_nSCTDead  = 0;
  v_int    *idtrk_isLoose   = 0;  //N.B. idtrk_isTightPrimary is not in nTuple anymore
  v_double    *idtrk_px = 0;  
  v_double    *idtrk_py = 0;  
  v_double    *idtrk_pz = 0;  
  tev->SetBranchAddress("pv_z", &pv_z);
  tev->SetBranchAddress("pv_sigma_z", &pv_sigma_z);
  tev->SetBranchAddress("pv_type", &pv_type);
  tev->SetBranchAddress("idtrk_pvidx", &idtrk_pvidx);
  // tev->SetBranchAddress("idtrk_isTightPrimary", &idtrk_isTightPrimary);
  tev->SetBranchAddress("idtrk_pvidx_loose", &idtrk_pvidx_loose);     // same as above but for official loose WP
  tev->SetBranchAddress("idtrk_pvidx_nominal", &idtrk_pvidx_nominal); // same as above but for official nominal WP
  tev->SetBranchAddress("idtrk_pvidx_tight", &idtrk_pvidx_tight);     // same as above but for official tight WP
  tev->SetBranchAddress("idtrk_px", &idtrk_px);
  tev->SetBranchAddress("idtrk_py", &idtrk_py);
  tev->SetBranchAddress("idtrk_pz", &idtrk_pz);
  tev->SetBranchAddress("idtrk_nPIXhits", &idtrk_nPIXhits);    // nPIX hits
  tev->SetBranchAddress("idtrk_NIBLayer", &idtrk_NIBLayer);    // nIBL hits
  tev->SetBranchAddress("idtrk_nSCThits", &idtrk_nSCThits);    // nSCT hits
  tev->SetBranchAddress("idtrk_nDeadPixels", &idtrk_nPIXDead); // nPIX Dead
  tev->SetBranchAddress("idtrk_nDeadSCT", &idtrk_nSCTDead); // nSCT Dead
  tev->SetBranchAddress("idtrk_isLoose", &idtrk_isLoose);             // loose track selection: 0 -fail, 1- pass

  
  
  auto nevents = ts->GetEntries();
  cout<< "Entries in original tree: "<< nevents << endl;
  
  //float B_MUCALC_mass(0.);
  int event_index(0);
  int B_PV_idx(0);
  int B_IDtrk1_trkidx(0);
  int B_IDtrk2_trkidx(0);
    UInt_t run_number(0);
      bool Trigger_Matched(false);
  v_float *B_PV_trksChi2 = 0;
  v_float *B_VTX_trksChi2=0;
  // v_float *closeTrkDOCA_alltrks=0;
  int closeTrkNtrksChi2(0);
  int B_iso_Ntracks_7_Chi2_5_LoosePt05(0);
  double B_minChi2MuonsIPtoAnyPV(0.);
  float closeTrkDCA(0.);
  float closeTrkZCA(0.);
  float B_iso_7_Chi2_5_LoosePt05(0.);
  double B_pT(0.);
  double B_eta(0.);
  double B_phi(0.);
  double B_IDtrk1_pT(0.);
  double B_IDtrk1_eta(0.);
  double B_IDtrk1_phi(0.);
  TVector3 myBVec;
  TVector3 myTrkVec;
  Double_t tracksPt_assPV(0.);
  Double_t tracksPt_otherPV(0.);
  Double_t tracksPt_nonAss(0.);
  Double_t tracksPt_myAll(0.);
  Double_t tracksPt_all(0.);
  ULong64_t event_number;

  //ts->SetBranchAddress("B_MUCALC_mass",&B_MUCALC_mass);
  ts->SetBranchAddress("event_index",  &event_index);                           // index to EventInfo tree

  // variables for the isolation studies
  //
  ts->SetBranchAddress("B_PV_idx",&B_PV_idx);                                  // index to associated PV  
  ts->SetBranchAddress("B_PV_trksChi2",&B_PV_trksChi2);                        // chi2 to associated PV, per track
  ts->SetBranchAddress("B_iso_7_Chi2_5_LoosePt05",&B_iso_7_Chi2_5_LoosePt05);  // DxAOD isoaltion variable
  ts->SetBranchAddress("B_iso_Ntracks_7_Chi2_5_LoosePt05",&B_iso_Ntracks_7_Chi2_5_LoosePt05);  // DxAOD isoaltion variable
  ts->SetBranchAddress("run_number",&run_number);
  ts->SetBranchAddress("Trigger_Matched",&Trigger_Matched);  

  // variables for the close track studies
  //
  ts->SetBranchAddress("B_VTX_trksChi2",&B_VTX_trksChi2);                // chi2 of each track to the B vertex
  // ts->SetBranchAddress("closeTrkDOCA_alltrks",&closeTrkDOCA_alltrks);    // DOCA of each track to B vertex
  ts->SetBranchAddress("closeTrkNtrksChi2",&closeTrkNtrksChi2);          // DxAOD closeTrkNtrksChi2 variable
  ts->SetBranchAddress("closeTrkDCA",&closeTrkDCA);                      // DxAOD closeTrkDCA variable 
  ts->SetBranchAddress("closeTrkZCA",&closeTrkZCA);                      // DxAOD closeTrkZCA variable
  // TMath::Sqrt(pow(closeTrkDCA,2)+pow(closeTrkZCA,2))
  //closeTrkDOCALoosePt05
  ts->SetBranchAddress("B_minChi2MuonsIPtoAnyPV",&B_minChi2MuonsIPtoAnyPV); 
  //B_minChi2MuonsIPtoAnyPV

  // variables to identify signal tracks
  //
  ts->SetBranchAddress("B_IDtrk1_trkidx",&B_IDtrk1_trkidx); // indexes of muon tracks
  ts->SetBranchAddress("B_IDtrk2_trkidx",&B_IDtrk2_trkidx);
  ts->SetBranchAddress("B_pT",&B_pT);
  ts->SetBranchAddress("B_eta",&B_eta);
  ts->SetBranchAddress("B_phi",&B_phi);
  ts->SetBranchAddress("B_IDtrk1_pT",&B_IDtrk1_pT);
  ts->SetBranchAddress("B_IDtrk1_eta",&B_IDtrk1_eta);
  ts->SetBranchAddress("B_IDtrk1_phi",&B_IDtrk1_phi);

  ts->SetBranchAddress("event_number", &event_number);
  // cout<<"DEBUG 3"<<endl;
Int_t EvCnt(0);
for (auto ievent=0; ievent<nevents; ievent++)
    {
        if (ievent%100000==0) cout << "Processing event "<< ievent << endl;
        ts->GetEntry(ievent);
        tev->GetEntry(event_index);
        tracksPt_assPV=0.;
        tracksPt_otherPV=0.;
        tracksPt_nonAss=0.;
        tracksPt_myAll=0.;
        tracksPt_all=0.;
        if (!intersect.count(event_number)) continue; //count is a function of set 
        EvCnt++;
        if (myYear.EqualTo("MC16a")){
            if (run_number != 302393) continue;
        }
        if (myYear.EqualTo("MC16d")){
            if (run_number != 339849) continue;
        }
        if (myYear.EqualTo("MC16e")){
            if (run_number != 358096) continue;
        }
        if (!Trigger_Matched) continue;

        auto ntrks = B_PV_trksChi2->size();
            if ((*idtrk_pvidx).size() != ntrks) {
                cout << "FATAL: ID trk info size unequal in event and candidate trees, exiting. " << (*idtrk_pvidx).size() << " <-ev|cand-> " << ntrks << endl;
                exit(0);
            }
        totalTracks+=ntrks;
        int nclosetrks_all(0);
        int nclosetrks_assPV(0);
        int nclosetrks_otherPV(0);
        int nclosetrks_nonAss(0);
        int tracksCnt_all_chi_5(0);
        int tracksCnt_all_ID_chi_5(0);
        int tracksCnt_all_ID_chi_4(0);
        float docamin(999.0);
        float DOCA = sqrt( pow(closeTrkDCA, 2) + pow(closeTrkZCA, 2) );
        myBVec.SetPtEtaPhi(B_pT,B_eta,B_phi);
        for (unsigned int idx=0; idx<ntrks; idx++) 
        {
            // skip signal tracks (Bsmumu channel as an example, add other tracks for other signatures!)
            //
            if (idx == B_IDtrk1_trkidx || idx == B_IDtrk2_trkidx) continue; 
            // select tracks by vertex association and fill chi2 histogram
            // 
            myTrkVec.SetXYZ((*idtrk_px).at(idx),(*idtrk_py).at(idx),(*idtrk_pz).at(idx));
            
            if (
                // (*B_PV_trksChi2).at(idx)<5. 
                myTrkVec.Pt()>500. && myTrkVec.Eta()<2.5
                 // && ((*idtrk_nPIXhits).at(idx) - (*idtrk_NIBLayer).at(idx))>=1
                 // && (*idtrk_nSCThits).at(idx)>=2
                 // (*idtrk_isTightPrimary).at(idx)==1
               ){ 
                    if  ( ( (*idtrk_nPIXhits).at(idx) + (*idtrk_nPIXDead).at(idx) )>=1 
                        && ( (*idtrk_nSCThits).at(idx) + (*idtrk_nSCTDead).at(idx) ) >= 2 
                        && (*idtrk_isLoose).at(idx) == 1 
                    ){
                    if (h_PIXhits_Run2) h_PIXhits_Run2->Fill((*idtrk_nPIXhits).at(idx));
                    if (h_SCThits_Run2) h_SCThits_Run2->Fill((*idtrk_nSCThits).at(idx));
                    } 
                }
        }

    }
    totalEvCnt+=EvCnt;

cout<< "number of intersect events so far: "<< totalEvCnt<< endl;
cout<< "number of tracks so far: "<< totalTracks<< endl;

// cout<< "h_chi2_all entries: "<< h_chi2_all->GetEntries()<<endl;
// cout<< "h_chi2 entries: "<< h_chi2->GetEntries()<<endl;
     // fs->Close();
     // delete fs;
     fin->Close();
    }
  }
closedir(dpdf);


TCanvas* c = new TCanvas("trks chi2","trks chi2",900,600);
  // if (doIsoStudy)  {
  //   // if (h_chi2_all) h_chi2_all->Draw();
  //   // if (h_chi2) h_chi2->Draw("same");
  //   // if (h_myDR_all) h_myDR_all->Draw();
  //   // if (h_myDR) h_myDR->Draw("same");
  //   // h_trackPt_all->Draw();
  //   // h_trackPt->Draw("same");
  //   if (h_my_iso_all) h_my_iso_all->Draw();
  //   // if (h_my_iso_myAll) h_my_iso_myAll->Draw("same");
  //   if (h_my_iso_assPV) h_my_iso_assPV->Draw("same");
  //   if (h_my_iso_otherPV) h_my_iso_otherPV->Draw("same");
  //   if (h_my_iso_nonAss) h_my_iso_nonAss->Draw("same");
  //   if (h_iso) h_iso->Draw("same");
  // } else if (doCntTrksStudy){
  //       if (h_isoTrks_all_chi_5) h_isoTrks_all_chi_5->Draw();
  //       if (h_isoTrks_all_ID_chi_5) h_isoTrks_all_ID_chi_5->Draw("same");
  //       if (h_isoTrks_all_ID_chi_4) h_isoTrks_all_ID_chi_4->Draw("same");
  //       if (h_isoTrks_orig) h_isoTrks_orig->Draw("same");
  // } else {
// if(h_PIXhits_Loose) h_PIXhits_Loose->Draw();
// if(h_SCThits_Loose) h_SCThits_Loose->Draw("same");
// if(h_IBLhits_Loose) h_IBLhits_Loose->Draw("same");
// if(h_PIXhits_isTight) h_PIXhits_isTight->Draw("same");
// if(h_SCThits_isTight) h_SCThits_isTight->Draw("same");
// if(h_IBLhits_isTight) h_IBLhits_isTight->Draw("same");
// if(h_PIXhits_Run1) h_PIXhits_Run1->Draw("same");
// if(h_SCThits_Run1) h_SCThits_Run1->Draw("same");
// if(h_IBLhits_Run1) h_IBLhits_Run1->Draw("same");
if(h_PIXhits_Run2) h_PIXhits_Run2->Draw();
if(h_SCThits_Run2) h_SCThits_Run2->Draw("same");
// if(h_IBLhits_Run2) h_IBLhits_Run2->Draw("same");
  // }

    return c;
}

void RunOverData(TString inYear ="", TString nTupleVer = ""){
    SetAtlasStyle();
    cout<<"debug hello"<<endl;
    cout<<inYear<<endl;
    TString myDir = "/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/";
    // TCanvas* myC = alltrksExample_fileLoop_v2(2018);
    // TString inYear = "2016";
    // TString  = "loose";

    // TString inYear = "2017";
    // TString inYear = "2018";
    // TString inYear = "MC16a";
    // TString inYear = "MC16d";
    // TString inYear = "MC16e";
    TCanvas* myC = IsolationStudy_fileloop(inYear, nTupleVer);
    myC->GetListOfPrimitives()->Print();
    myC->SaveAs(myDir+"data/"+inYear+"_IDhits_2020Mar3_Intersect_"+nTupleVer+".root");
    myC->SaveAs(myDir+"figures/"+inYear+"_IDhits_2020Mar3_Intersect_"+nTupleVer+".png");

}

void RunOverSavedFiles_Chi2(TString theYear="", TString Detector=""){
    SetAtlasStyle();

      TString myDir = "/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/data/";
    //chi2 files
    int numberOfBinsChi2 = 200;

    TFile* ifile_IDhits_new = new TFile(myDir+theYear+"_IDhits_2020Mar3_Intersect_new.root");
    TCanvas *Canvas_IDhits_new = (TCanvas*)ifile_IDhits_new->Get("trks chi2");

    TH1F *h_PIXhits_Run2_new = (TH1F*)Canvas_IDhits_new->GetListOfPrimitives()->FindObject("h_PIXhits_Run2");
    TH1F *h_SCThits_Run2_new = (TH1F*)Canvas_IDhits_new->GetListOfPrimitives()->FindObject("h_SCThits_Run2");

    ifile_IDhits_new->Close();

    TFile* ifile_IDhits_old = new TFile(myDir+theYear+"_IDhits_2020Mar3_Intersect_old.root");
    TCanvas *Canvas_IDhits_old = (TCanvas*)ifile_IDhits_old->Get("trks chi2");

    TH1F *h_PIXhits_Run2_old = (TH1F*)Canvas_IDhits_old->GetListOfPrimitives()->FindObject("h_PIXhits_Run2");
    TH1F *h_SCThits_Run2_old = (TH1F*)Canvas_IDhits_old->GetListOfPrimitives()->FindObject("h_SCThits_Run2");

    ifile_IDhits_old->Close();

    ////


    TCanvas* allC = new TCanvas("allC","allC",900,600);
    allC->SetLogy();

// h_PIXhits_Loose->SetLineColor(kBlue);
// h_PIXhits_Loose->SetMarkerSize(0.);
// h_SCThits_Loose->SetLineColor(kBlue);
// h_SCThits_Loose->SetMarkerSize(0.);
// h_IBLhits_Loose->SetLineColor(kBlue);
// h_IBLhits_Loose->SetMarkerSize(0.);
h_PIXhits_Run2_new->SetLineColor(kRed);
h_PIXhits_Run2_new->SetLineStyle(2);
h_PIXhits_Run2_new->SetMarkerSize(0.);
// h_PIXhits_Run2_new->SetMarkerStyle(22.);
// h_PIXhits_Run2_new->SetMarkerColor(kRed);
h_SCThits_Run2_new->SetLineColor(kRed);
h_SCThits_Run2_new->SetMarkerSize(0.);
h_SCThits_Run2_new->SetLineStyle(2.);
// h_SCThits_Run2_new->SetMarkerStyle(22.);
// h_SCThits_Run2_new->SetMarkerColor(kRed);
// h_IBLhits_isTight->SetLineColor(kRed);
// h_IBLhits_isTight->SetMarkerSize(0.);
// h_PIXhits_Run1->SetLineColor(kMagenta+2);
// h_PIXhits_Run1->SetMarkerSize(0.);
// h_SCThits_Run1->SetLineColor(kMagenta+2);
// h_SCThits_Run1->SetMarkerSize(0.);
// h_IBLhits_Run1->SetLineColor(kMagenta+2);
// h_IBLhits_Run1->SetMarkerSize(0.);
h_PIXhits_Run2_old->SetLineColor(kGreen+2);
h_PIXhits_Run2_old->SetMarkerSize(0.);
h_PIXhits_Run2_old->SetLineStyle(3.);
// h_PIXhits_Run2_old->SetMarkerStyle(23.);
// h_PIXhits_Run2_old->SetMarkerColor(kGreen+2);
h_SCThits_Run2_old->SetLineColor(kGreen+2);
h_SCThits_Run2_old->SetMarkerSize(0.);
h_SCThits_Run2_old->SetLineStyle(3.);
// h_IBLhits_Run2->SetLineColor(kGreen+2);
// h_IBLhits_Run2->SetMarkerSize(0.);


    // if (h_isoRun2Cuts_Run1) h_isoRun2Cuts_Run1->Draw("e0 hist");
    // if (h_iso_1516) h_iso_1516->Draw("e0 hist same");
    // // if (h_iso_2017) h_iso_2017->Draw("e0 hist same");
    // // if (h_my_iso_nonAss_2017) h_my_iso_nonAss_2017->Draw("e0 hist same");
    // // if (h_my_iso_nonAss_2017) h_my_iso_nonAss_2017_isTightPrimary->Draw("hist same");
    // // if (h_my_iso_nonAss_2017_IdHits) h_my_iso_nonAss_2017_IdHits->Draw("e0 hist same");
    // if (h_my_iso_all_2017_IdHits) h_my_iso_all_2017_IdHits->Draw("e0 hist same");
    // // if (h_iso_2018) h_iso_2018->Draw("e0 hist same");
    // // if (h_my_iso_nonAss_2018) h_my_iso_nonAss_2018->Draw("e0 hist same");
    // // if (h_my_iso_nonAss_2018) h_my_iso_nonAss_2018_isTightPrimary->Draw("hist same");
    // // if (h_my_iso_nonAss_2018_IdHits) h_my_iso_nonAss_2018_IdHits->Draw("e0 hist same");
    // if (h_my_iso_all_2018_IdHits) h_my_iso_all_2018_IdHits->Draw(" e0 hist same");
    // //for logy scale
    // gPad->SetLogy();
    // h_isoRun2Cuts_Run1->SetMaximum(1.);
    // else:
    // h_isoRun2Cuts_Run1->GetYaxis()->SetRangeUser(0,0.08);
    
    // if (h_chi2_VTX_all) h_chi2_VTX_all->Draw("e0 hist");
    // if (h_chi2_VTX_all) h_chi2_VTX_assPV->Draw("e0 hist same");
    // if (h_chi2_VTX_all) h_chi2_VTX_otherPV->Draw("e0 hist same");
    // if (h_chi2_VTX_all) h_chi2_VTX_nonAss->Draw("e0 hist same");
    // h_chi2_VTX_all->GetXaxis()->SetTitle("#chi^{2}");
    // // h_chi2_VTX_all->GetYaxis()->SetTitle("a.u.");
    // h_chi2_VTX_all->GetYaxis()->SetTitle("Candidates * Num. of Trks per cand.");

    // if (h_chi2_PV_all) h_chi2_PV_all->Draw("e0 hist");
    Double_t ymin;
    Double_t ymax;
    // Double_t xmin;
    // Double_t xmax;
    TLegend* legAll(NULL);
if(Detector.EqualTo("PIX")) {
    h_PIXhits_Run2_old->GetXaxis()->SetRangeUser(0, 16);
    ymin = 1e-1;
    ymax = 1e7;
    h_PIXhits_Run2_old->SetMaximum(ymax);   // along          
    h_PIXhits_Run2_old->SetMinimum(ymin);  //   Y  
    // if (h_PIXhits_Loose) h_PIXhits_Loose->Draw("e0 hist");
    // if (h_PIXhits_isTight) h_PIXhits_isTight->Draw("e0 hist same");
    // if (h_PIXhits_Run1) h_PIXhits_Run1->Draw("e0 hist same");
    h_PIXhits_Run2_old->Draw("e0 hist");
    h_PIXhits_Run2_new->Draw("e0 hist same");
    h_PIXhits_Run2_old->GetXaxis()->SetTitle("Num. of PIX Hits");
    h_PIXhits_Run2_old->GetYaxis()->SetTitle("Candidates #times Num. of Trks per cand.");
    legAll = new TLegend(0.62, 0.7, 0.8, 0.9);
}
if(Detector.EqualTo("SCT")) {
    h_SCThits_Run2_old->GetXaxis()->SetRangeUser(0, 25);
    ymin = 1e-1;
    ymax = 1e7;
    h_SCThits_Run2_old->SetMaximum(ymax);   // along          
    h_SCThits_Run2_old->SetMinimum(ymin);  //   Y  
    // if (h_SCThits_Loose) h_SCThits_Loose->Draw("e0 hist");
    // if (h_SCThits_isTight) h_SCThits_isTight->Draw("e0 hist same");
    // if (h_SCThits_Run1) h_SCThits_Run1->Draw("e0 hist same");
    h_SCThits_Run2_old->Draw("e0 hist");
    h_SCThits_Run2_new->Draw("e0 hist same");
    h_SCThits_Run2_old->GetXaxis()->SetTitle("Num. of SCT Hits");
    h_SCThits_Run2_old->GetYaxis()->SetTitle("Candidates #times Num. of Trks per cand.");
    legAll = new TLegend(0.62, 0.7, 0.8, 0.9);
}   
// if(Detector.EqualTo("IBL")) {
//     if (h_IBLhits_Loose) h_IBLhits_Loose->GetXaxis()->SetRangeUser(0, 6);
//     if (h_IBLhits_Loose) h_IBLhits_Loose->Draw("e0 hist");
//     if (h_IBLhits_isTight) h_IBLhits_isTight->Draw("e0 hist same");
//     if (h_IBLhits_Run1) h_IBLhits_Run1->Draw("e0 hist same");
//     if (h_IBLhits_Run2) h_IBLhits_Run2->Draw("e0 hist same");
//     h_IBLhits_Loose->GetXaxis()->SetTitle("Num. of IBL Hits");
//     h_IBLhits_Loose->GetYaxis()->SetTitle("Candidates #times Num. of Trks per cand.");
//     legAll = new TLegend(0.62, 0.7, 0.8, 0.9);
// }
    // h_chi2_PV_all->GetYaxis()->SetTitle("a.u.");
    
    
    // legAll->SetTextSize(0.034468);
    legAll->SetTextSize(0.03);
    // legAll->SetHeader("2017 Decay Vertex");
    // legAll->AddEntry(h_chi2_VTX_all, "All Tracks" ,"l");
    // legAll->AddEntry(h_chi2_VTX_assPV, "Tracks Associated to B PV" ,"l");
    // legAll->AddEntry(h_chi2_VTX_otherPV, "Tracks Assoc. to B PV and other PVs" ,"l");
    // legAll->AddEntry(h_chi2_VTX_nonAss, "Tracks Assoc. to B PV and not Assoc. to any PV" ,"l");


    legAll->SetHeader(theYear );
//tight label doesn't matter here as long as the line colors don't change

        // legAll->AddEntry(h_IBLhits_Loose, "Loose Hit Selection" ,"l");
        // legAll->AddEntry(h_IBLhits_isTight, "Tight Hit Selection" ,"l");
        // legAll->AddEntry(h_IBLhits_Run1, "Like Run 1 ID Selection" ,"l");
        legAll->AddEntry(h_SCThits_Run2_new, "New nTuple" ,"l");
        legAll->AddEntry(h_SCThits_Run2_old, "Old nTuple" ,"l");

    legAll->SetBorderSize(0);  // no border
    legAll->SetLineColor(0);
    legAll->SetFillColorAlpha(0, 0.4);
    legAll->Draw();
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/Iso/IsoComp.png");
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/Iso/IsoComp_orig_linear.png");
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/Iso/IsoComparntrksn_wNonAssoc.png");
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/Iso/IsoComp_wNonAssoc_linear.png");
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/Iso/IsoComparntrksn_wNonAssoc_isTightPrimary.png");
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/Iso/IsoComparntrksn_wNonAssoc_isTightPrimary_linear.png");
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/Iso/IsoComp_wNonAssoc_IdHits.png");
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/Iso/IsoComp_wNonAssoc_IdHits_linear.png");
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/Iso/IsoComp_allTrks_Chi2_5.png");
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/Iso/IsoComp_allTrks_IDhits_Chi2_5.png");
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/Iso/IsoComp_allTrks_IDhits_Chi2_4.png");
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/Iso/IsoComp_allTrks_linear.png");
    // cout<<h_ntrksRun2Cuts_Run1->GetEntries()<<endl;
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/Chi2/2017chi2_VTXcomp_2019May7.png");
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/Chi2/2017chi2_PVcomp_2019May7.png");
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/IDhits/"+theYear+"_"+Detector+"_2019Jun13.png");
    allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/IDhits/"+theYear+"_"+Detector+"_2020Mar3_Intersect.png");
}

// void DrawMyPlots(){
//       // SetAtlasStyle();
//       // RunOverData();
//       // RunOverSavedFiles_Iso();
//       // RunOverSavedFiles_Ntrks();
//       // RunOverSavedFiles_IsoTrks();
//     RunOverSavedFiles_Chi2();
//     // cout<<""<<endl;
// }


int main(int argc, char* argv[])
{
  TString  pattern, pattern2;
  // if (argc>1) inpath = TString(argv[1]);
  if (argc>1) pattern = TString(argv[1]);
  if (argc>2) pattern2 = TString(argv[2]);
  // alltrksExample_fileLoop(inpath, pattern);
  // DrawMyPlots();

//One configuration:
  // //pattern -> year
  // //pattern2 -> IDselection
  // RunOverData(pattern, pattern2);
//Second configuration:
   // //pattern -> year
   // //pattern2 -> track association:
   // // otherPV
   // // nonAss
   // // assPV
  RunOverSavedFiles_Chi2(pattern, pattern2);
  return 0;
}

