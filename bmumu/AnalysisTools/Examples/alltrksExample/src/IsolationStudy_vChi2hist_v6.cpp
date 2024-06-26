//
// example how to read all track ntuples
//
// iskander(dot)ibragimov(at)cern(dot)ch
// 
// setupATLAS 
// lsetup "root 6.10.06-x86_64-slc6-gcc62-opt"
//  
//IsolationStudy_vChi2hist_v2.cpp is for the TTVA working points.
//
//v3 includes run number constraint (needed fro MCs) created june 10th
//chi2 distributions extending the left bin ranges to -15
//
//code updated on june 12th
//
// weights here should only be run with MC datasets!!:
// now has PVweights and muon reconstruction weights???
// prints out candidate numbers (after run cuts) and 

//v4 should be pileup chunk separated not implemented as of Jun12
// to do this perform all tight, loose, nominal hists at same time and 
// change the input option to the pileups
//
//v5 adds switch to look at pileup dependence (aimed at 2017 data and MC16d)
//
//v6 used for plotting portion of the code
// rearrange plots to compare pileups on the same figure
//
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

// int main(int argc, char* argv[]) {
TCanvas* IsolationStudy_fileloop(TString myYear="", TString TTVA = "", TString Pileup=""){
  SetAtlasStyle();
  cout<<"DEBUG 1"<<endl;
  cout<< myYear<<" "<< TTVA<< endl;
  // TString fsname("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/skimmed_ntup/data18/Bmumu/user.ibragimo.17073931.Bmumu._000001_skimmed.root");
  // TString fsname("/afs/cern.ch/work/a/agrummer/BsmumuData/LastSkimOne2018Run/LASTskim_2017Bmumu.root");
  // TString fsname("/afs/cern.ch/work/a/agrummer/BsmumuData/LastSkimOne2018Run/LASTskim_2018_1.root");
  // TString indir("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/skimmed_ntup/data18/Bmumu/");
  TString indir("");
  // int myYear(2018);
  if (myYear.EqualTo("2017")){
        // indir = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkim2017_2019Mar7/";
        // indir = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkim_2019Mar27/2017/";
        indir = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/2017/";
        // AllPath = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/2017All/";
  }else if (myYear.EqualTo("2018")){
        // indir = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkim2018_2019Mar7/";
        // indir = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkim_2019Mar27/2018/";
        indir = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/2018/";
        // AllPath = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/2018All/";
  }else if (myYear.EqualTo("2016")){
        indir = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/2016/";
        // AllPath = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/2016All/";
  }else if (myYear.EqualTo("MC16a")){
        // indir = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkim_2019Mar27/MC16a/";
        indir = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/MC16a/";
        // AllPath = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/MC16aAll/";
  }else if (myYear.EqualTo("MC16d")){
        // indir = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkim_2019Mar27/MC16d/";
        indir = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/MC16d/";
        // AllPath = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/MC16dAll/";
  }else if (myYear.EqualTo("MC16e")){
        // indir = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkim_2019Mar27/MC16e/";
        indir = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/MC16e/";
        // AllPath = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/MC16eAll/";
  }
  TString finpath(indir);
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
    h_chi2_VTX_otherPV   = new TH1F("h_chi2_VTX_otherPV","chi2 to ass. B vertex for all tracks",300,-15,15);
    h_chi2_PV_otherPV    = new TH1F("h_chi2_PV_otherPV","chi2 to associated PV for selected tracks",300,-15,15);
    h_chi2_VTX_assPV   = new TH1F("h_chi2_VTX_assPV","chi2 to ass. B vertex for all tracks",300,-15,15);
    h_chi2_PV_assPV    = new TH1F("h_chi2_PV_assPV","chi2 to associated PV for selected tracks",300,-15,15);
    h_chi2_VTX_nonAss   = new TH1F("h_chi2_VTX_nonAss","chi2 to ass. B vertex for all tracks",300,-15,15);
    h_chi2_PV_nonAss    = new TH1F("h_chi2_PV_nonAss","chi2 to associated PV for selected tracks",300,-15,15);
    h_chi2_VTX_all   = new TH1F("h_chi2_VTX_all","chi2 to ass. B vertex for all tracks",300,-15,15);
    h_chi2_PV_all    = new TH1F("h_chi2_PV_all","chi2 to associated PV for selected tracks",300,-15,15);

 
  if (h_chi2_VTX_all) h_chi2_VTX_all->SetLineColor(kBlue); 
  if (h_chi2_PV_all) h_chi2_PV_all->SetLineColor(kRed); 

Int_t totalTracks(0);
Int_t ncandidates(0);
float cntWeight(0.);
float lowPU_1(0.);
float lowPU_2(0.);
float mediumPU_1(0.);
float mediumPU_2(0.);
float highPU_1(0.);
float highPU_2(0.);
if (myYear.Contains("MC")){
    lowPU_1 = 21.;
    lowPU_2 = 32.;
    mediumPU_1 = 34.;
    mediumPU_2 = 43.;
    highPU_1 = 44.;
    highPU_2 = 55.;
}else if (myYear.Contains("2017")){
    lowPU_1 = 22.493;
    lowPU_2 = 29.0;
    mediumPU_1 = 36.352;
    mediumPU_2 = 43.;
    highPU_1 = 45.;
    highPU_2 = 55.;
}else{
    lowPU_1 = 20.;
    lowPU_2 = 30.;
    mediumPU_1 = 35.;
    mediumPU_2 = 45.;
    highPU_1 = 45.;
    highPU_2 = 55.;
}

  cout<<"DEBUG 2"<<endl;
  if (dpdf != NULL){
      cout<<"DEBUG 2"<<endl;
    while (entry = readdir(dpdf)){
  cout<<"DEBUG 2"<<endl;
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
  v_int    *idtrk_isTightPrimary = 0; 
  v_int    *idtrk_nPIXhits  = 0;
  v_int    *idtrk_NIBLayer  = 0;
  v_int    *idtrk_nSCThits  = 0;
  v_double    *idtrk_px = 0;  
  v_double    *idtrk_py = 0;  
  v_double    *idtrk_pz = 0;  
  tev->SetBranchAddress("pv_z", &pv_z);
  tev->SetBranchAddress("pv_sigma_z", &pv_sigma_z);
  tev->SetBranchAddress("pv_type", &pv_type);
  tev->SetBranchAddress("idtrk_pvidx", &idtrk_pvidx);
  tev->SetBranchAddress("idtrk_isTightPrimary", &idtrk_isTightPrimary);
  tev->SetBranchAddress("idtrk_pvidx_loose", &idtrk_pvidx_loose);     // same as above but for official loose WP
  tev->SetBranchAddress("idtrk_pvidx_nominal", &idtrk_pvidx_nominal); // same as above but for official nominal WP
  tev->SetBranchAddress("idtrk_pvidx_tight", &idtrk_pvidx_tight);     // same as above but for official tight WP
  tev->SetBranchAddress("idtrk_px", &idtrk_px);
  tev->SetBranchAddress("idtrk_py", &idtrk_py);
  tev->SetBranchAddress("idtrk_pz", &idtrk_pz);
  tev->SetBranchAddress("idtrk_nPIXhits", &idtrk_nPIXhits);    // nPIX hits
  tev->SetBranchAddress("idtrk_NIBLayer", &idtrk_NIBLayer);    // nIBL hits
  tev->SetBranchAddress("idtrk_nSCThits", &idtrk_nSCThits);    // nSCT hits

  
  
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
  v_float *closeTrkDOCA_alltrks=0;
  int closeTrkNtrksChi2(0);
  int B_iso_Ntracks_7_Chi2_5_LoosePt05(0);
  double B_minChi2MuonsIPtoAnyPV(0.);
  float closeTrkDCA(0.);
  float closeTrkZCA(0.);
  float B_iso_7_Chi2_5_LoosePt05(0.);
  double PVWeights(0.);
  float Muon1_reco_eff_sf(0.);
  float Muon2_reco_eff_sf(0.);
  double myWeight(1.);
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
  float PRIVX_mu(0.);

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
  ts->SetBranchAddress("PRIVX_mu",&PRIVX_mu);  

  ts->SetBranchAddress("PVWeights",&PVWeights);  
  ts->SetBranchAddress("Muon1_reco_eff_sf",&Muon1_reco_eff_sf);  
  ts->SetBranchAddress("Muon2_reco_eff_sf",&Muon2_reco_eff_sf);  

  // variables for the close track studies
  //
  ts->SetBranchAddress("B_VTX_trksChi2",&B_VTX_trksChi2);                // chi2 of each track to the B vertex
  ts->SetBranchAddress("closeTrkDOCA_alltrks",&closeTrkDOCA_alltrks);    // DOCA of each track to B vertex
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

  cout<<"DEBUG 3"<<endl;

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
        if (Pileup.EqualTo("low")) {
            if (PRIVX_mu < lowPU_1 || PRIVX_mu > lowPU_2) continue;
        }else if(Pileup.EqualTo("medium")) {
            if (PRIVX_mu < mediumPU_1 || PRIVX_mu > mediumPU_2) continue;
        }else if(Pileup.EqualTo("high")) {
            if (PRIVX_mu < highPU_1 || PRIVX_mu > highPU_2) continue;
        }
        if (myYear.Contains("MC")){
            myWeight = PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf;
        }else{
            myWeight=1.;
        }

        auto ntrks = B_PV_trksChi2->size();
            if ((*idtrk_pvidx).size() != ntrks) {
                cout << "FATAL: ID trk info size unequal in event and candidate trees, exiting. " << (*idtrk_pvidx).size() << " <-ev|cand-> " << ntrks << endl;
                exit(0);
            }
        ncandidates+=1;
        cntWeight+=1;
        if (myYear.Contains("MC")){
                if (cntWeight>=449) continue;
        }
        // else if (myYear.Contains("2017")){
        //         if (ncandidates>=6512) continue;
        // }

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
                myTrkVec.Pt()>500.
                 && (*idtrk_nPIXhits).at(idx)>=1
                 && (*idtrk_nSCThits).at(idx)>=2
               ){//&& myTrkVec.Eta()<2.5
              if (TTVA.EqualTo("loose")){ 
                 //associated to B PVs
                  if ( (*idtrk_pvidx_loose).at(idx) == B_PV_idx){
                      if (h_chi2_VTX_assPV) h_chi2_VTX_assPV->Fill( (*B_VTX_trksChi2).at(idx), myWeight);
                      if (h_chi2_PV_assPV) h_chi2_PV_assPV->Fill( (*B_PV_trksChi2).at(idx), myWeight );
                  }
                  //associated OTHER PVs
                  else if ( //(*idtrk_pvidx_loose).at(idx) != B_PV_idx) &&
                  (*idtrk_pvidx_loose).at(idx) != pv_type->size()-1 ) // or choose tracks ass. to other real PV's (for non-ass. tracks use '==' instead)
                  {   
                      if (h_chi2_VTX_otherPV) h_chi2_VTX_otherPV->Fill( (*B_VTX_trksChi2).at(idx), myWeight );
                      if (h_chi2_PV_otherPV) h_chi2_PV_otherPV->Fill( (*B_PV_trksChi2).at(idx), myWeight );
                  }
                  //non-associated
                  if ( (*idtrk_pvidx_loose).at(idx) == pv_type->size()-1 ) // or choose tracks ass. to other real PV's (for non-ass. tracks use '==' instead)
                  {   
                      if (h_chi2_VTX_nonAss) h_chi2_VTX_nonAss->Fill( (*B_VTX_trksChi2).at(idx), myWeight );
                      if (h_chi2_PV_nonAss) h_chi2_PV_nonAss->Fill( (*B_PV_trksChi2).at(idx), myWeight );
                  }
              }
              if (TTVA.EqualTo("nominal")){  
                  //associated to B PVs
                  if ( (*idtrk_pvidx_nominal).at(idx) == B_PV_idx){
                      if (h_chi2_VTX_assPV) h_chi2_VTX_assPV->Fill( (*B_VTX_trksChi2).at(idx), myWeight );
                      if (h_chi2_PV_assPV) h_chi2_PV_assPV->Fill( (*B_PV_trksChi2).at(idx), myWeight );
                  }
                  //associated OTHER PVs
                  else if ( (*idtrk_pvidx_nominal).at(idx) != pv_type->size()-1 ) // or choose tracks ass. to other real PV's (for non-ass. tracks use '==' instead)
                  {   
                      if (h_chi2_VTX_otherPV) h_chi2_VTX_otherPV->Fill( (*B_VTX_trksChi2).at(idx), myWeight );
                      if (h_chi2_PV_otherPV) h_chi2_PV_otherPV->Fill( (*B_PV_trksChi2).at(idx), myWeight );
                  }
                  //non-associated
                  if ( (*idtrk_pvidx_nominal).at(idx) == pv_type->size()-1 ) // or choose tracks ass. to other real PV's (for non-ass. tracks use '==' instead)
                  {   
                      if (h_chi2_VTX_nonAss) h_chi2_VTX_nonAss->Fill( (*B_VTX_trksChi2).at(idx), myWeight );
                      if (h_chi2_PV_nonAss) h_chi2_PV_nonAss->Fill( (*B_PV_trksChi2).at(idx), myWeight );
                  }
              }
              if (TTVA.EqualTo("tight")){  
                  //associated to B PVs
                  if ( (*idtrk_pvidx_tight).at(idx) == B_PV_idx){
                      if (h_chi2_VTX_assPV) h_chi2_VTX_assPV->Fill( (*B_VTX_trksChi2).at(idx), myWeight );
                      if (h_chi2_PV_assPV) h_chi2_PV_assPV->Fill( (*B_PV_trksChi2).at(idx), myWeight );
                  }
                  //associated OTHER PVs
                  else if ( (*idtrk_pvidx_tight).at(idx) != pv_type->size()-1 ) // or choose tracks ass. to other real PV's (for non-ass. tracks use '==' instead)
                  {   
                      if (h_chi2_VTX_otherPV) h_chi2_VTX_otherPV->Fill( (*B_VTX_trksChi2).at(idx), myWeight );
                      if (h_chi2_PV_otherPV) h_chi2_PV_otherPV->Fill( (*B_PV_trksChi2).at(idx), myWeight );
                  }
                  //non-associated
                  if ( (*idtrk_pvidx_tight).at(idx) == pv_type->size()-1 ) // or choose tracks ass. to other real PV's (for non-ass. tracks use '==' instead)
                  {   
                      if (h_chi2_VTX_nonAss) h_chi2_VTX_nonAss->Fill( (*B_VTX_trksChi2).at(idx), myWeight );
                      if (h_chi2_PV_nonAss) h_chi2_PV_nonAss->Fill( (*B_PV_trksChi2).at(idx), myWeight );
                  }
              }
                        // if ((*B_VTX_trksChi2).at(idx)<=1.0) nclosetrks_all++;
                // } 
            }
        }

    }
cout<< "number of tracks so far: "<< totalTracks<< endl;
cout<< "number of candidates so far (after run cut): "<< ncandidates<< endl;
cout<< "totals of weights so far (after run cut): "<< cntWeight<< endl;
// cout<< "h_chi2_all entries: "<< h_chi2_all->GetEntries()<<endl;
// cout<< "h_chi2 entries: "<< h_chi2->GetEntries()<<endl;
     // fs->Close();
     // delete fs;
     fin->Close();
    }
  }
closedir(dpdf);


TCanvas* c = new TCanvas("trks chi2","trks chi2",900,600);
  if (doIsoStudy)  {
    // if (h_chi2_all) h_chi2_all->Draw();
    // if (h_chi2) h_chi2->Draw("same");
    // if (h_myDR_all) h_myDR_all->Draw();
    // if (h_myDR) h_myDR->Draw("same");
    // h_trackPt_all->Draw();
    // h_trackPt->Draw("same");
    if (h_my_iso_all) h_my_iso_all->Draw();
    // if (h_my_iso_myAll) h_my_iso_myAll->Draw("same");
    if (h_my_iso_assPV) h_my_iso_assPV->Draw("same");
    if (h_my_iso_otherPV) h_my_iso_otherPV->Draw("same");
    if (h_my_iso_nonAss) h_my_iso_nonAss->Draw("same");
    if (h_iso) h_iso->Draw("same");
  } else if (doCntTrksStudy){
        if (h_isoTrks_all_chi_5) h_isoTrks_all_chi_5->Draw();
        if (h_isoTrks_all_ID_chi_5) h_isoTrks_all_ID_chi_5->Draw("same");
        if (h_isoTrks_all_ID_chi_4) h_isoTrks_all_ID_chi_4->Draw("same");
        if (h_isoTrks_orig) h_isoTrks_orig->Draw("same");
  } else {
    // if (h_chi2_VTX_all)h_chi2_VTX_all->Draw();
    // if (h_chi2_PV_all)h_chi2_PV_all->Draw("same");
    if (h_chi2_VTX_otherPV)h_chi2_VTX_otherPV->Draw();
    if (h_chi2_PV_otherPV)h_chi2_PV_otherPV->Draw("same");
    if (h_chi2_VTX_assPV)h_chi2_VTX_assPV->Draw("same");
    if (h_chi2_PV_assPV)h_chi2_PV_assPV->Draw("same");
    if (h_chi2_VTX_nonAss)h_chi2_VTX_nonAss->Draw("same");
    if (h_chi2_PV_nonAss)h_chi2_PV_nonAss->Draw("same");
        // if (h_ntrks_orig) h_ntrks_orig->Draw();
        // if (h_ntrks_all) h_ntrks_all->Draw("same");
        // if (h_ntrks_assPV) h_ntrks_assPV->Draw("same");
        // if (h_ntrks_otherPV) h_ntrks_otherPV->Draw("same");
        // if (h_ntrks_nonAss) h_ntrks_nonAss->Draw("same");
  }
    // TLegend* leg = new TLegend(0.4, 0.6, 0.5, 0.7,NULL,"brNDC");
  //DR
    // TLegend* leg = new TLegend(0.7, 0.7, 0.8, 0.8,NULL,"brNDC");
    //iso

    h_chi2_VTX_all->GetXaxis()->SetTitle("ln(#chi^2) Track to PV");
    h_chi2_VTX_all->GetYaxis()->SetTitle("a.u.");

    // TLegend* leg = new TLegend(0.2, 0.6, 0.3, 0.8,NULL,"brNDC");
    // leg->SetTextSize(0.034468);
    // // leg->AddEntry(h_chi2, "2018 B_PV_trksChi2" ,"l");
    // // leg->AddEntry(h_chi2, "2017 assoc. B_PV_trksChi2" ,"l");
    // // leg->AddEntry(h_chi2_all, "2017 all B_PV_trksChi2" ,"l");
    // // leg->AddEntry(h_myDR, "2018 DR tracks" ,"l");
    // // leg->AddEntry(h_myDR_all, "2018 DR all tracks" ,"l");
    // if (doIsoStudy)  {
    //     if (myYear==2017){
    //         leg->AddEntry(h_my_iso_assPV, "2017 h_my_iso_assPV" ,"l");
    //         leg->AddEntry(h_my_iso_otherPV, "2017 h_my_iso_otherPV" ,"l");
    //         leg->AddEntry(h_my_iso_nonAss, "2017 h_my_iso_nonAss" ,"l");
    //         // leg->AddEntry(h_my_iso_myAll, "2017 h_my_iso_myAll" ,"l");
    //         leg->AddEntry(h_my_iso_all, "2017 myIso all tracks" ,"l");
    //         leg->AddEntry(h_iso, "2017 I_{0.7}" ,"l");
    //     }else if (myYear == 2018){
    //         leg->AddEntry(h_my_iso_assPV, "2018 h_my_iso_assPV" ,"l");
    //         leg->AddEntry(h_my_iso_otherPV, "2018 h_my_iso_otherPV" ,"l");
    //         leg->AddEntry(h_my_iso_nonAss, "2018 h_my_iso_nonAss" ,"l");
    //         // leg->AddEntry(h_my_iso_myAll, "2018 h_my_iso_myAll" ,"l");
    //         leg->AddEntry(h_my_iso_all, "2018 myIso all tracks" ,"l");
    //         leg->AddEntry(h_iso, "2018 I_{0.7}" ,"l");
    //     }
    // }else if(doCntTrksStudy){
    //     if (myYear==2017){
    //         leg->AddEntry(h_isoTrks_all_chi_5, "2017 h_isoTrks_all_chi_5" ,"l");
    //         leg->AddEntry(h_isoTrks_all_ID_chi_5, "2017 h_isoTrks_all_ID_chi_5" ,"l");
    //         leg->AddEntry(h_isoTrks_all_ID_chi_4, "2017 h_isoTrks_all_ID_chi_4" ,"l");
    //         leg->AddEntry(h_isoTrks_orig, "2017 h_isoTrks_orig" ,"l");
    //     }else if (myYear == 2018){
    //         leg->AddEntry(h_isoTrks_all_chi_5, "2018 h_isoTrks_all_chi_5" ,"l");
    //         leg->AddEntry(h_isoTrks_all_ID_chi_5, "2018 h_isoTrks_all_ID_chi_5" ,"l");
    //         leg->AddEntry(h_isoTrks_all_ID_chi_4, "2018 h_isoTrks_all_ID_chi_4" ,"l");
    //         leg->AddEntry(h_isoTrks_orig, "2018 h_isoTrks_orig" ,"l");
    //     }
    // }else{
    //       if (myYear==2017){
    //         leg->AddEntry(h_chi2_VTX_all, "2017 Decay Vertex", "l");
    //         leg->AddEntry(h_chi2_PV_all, "2017 Primary Vertex", "l");
    //         // leg->AddEntry(h_ntrks_orig, "2017 h_ntrks_orig" ,"l");
    //         // leg->AddEntry(h_ntrks_all, "2017 h_ntrks_all" ,"l");
    //         // leg->AddEntry(h_ntrks_assPV, "2017 h_ntrks_assPV" ,"l");
    //         // leg->AddEntry(h_ntrks_otherPV, "2017 h_ntrks_otherPV" ,"l");
    //         // leg->AddEntry(h_ntrks_nonAss, "2017 h_ntrks_nonAss" ,"l");
    //     }else if (myYear == 2018){
    //         leg->AddEntry(h_chi2_VTX_all, "2018 Decay Vertex", "l");
    //         leg->AddEntry(h_chi2_PV_all, "2018 Primary Vertex", "l");
    //         // leg->AddEntry(h_ntrks_orig, "2018 h_ntrks_orig" ,"l");
    //         // leg->AddEntry(h_ntrks_all, "2018 h_ntrks_all" ,"l");
    //         // leg->AddEntry(h_ntrks_assPV, "2018 h_ntrks_assPV" ,"l");
    //         // leg->AddEntry(h_ntrks_otherPV, "2018 h_ntrks_otherPV" ,"l");
    //         // leg->AddEntry(h_ntrks_nonAss, "2018 h_ntrks_nonAss" ,"l");
    //     }
    // }
    
    // leg->AddEntry(h_iso, "2017 I_{0.7}" ,"l");
    // leg->AddEntry(h_ntrks_orig, "2018 h_ntrks_orig" ,"l");
    // leg->AddEntry(h_ntrks, "2018 h_ntrks","l");
    // leg->AddEntry(h_ntrks_orig, "2017 h_ntrks_orig" ,"l");
    // leg->AddEntry(h_ntrks, "2017 h_ntrks","l");
  //   leg->SetBorderSize(0);  // no border
  //   leg->SetLineColor(0);
  //   leg->SetFillColorAlpha(0, 0.4);
  //   leg->Draw();
  // // c->SaveAs("chi2.root");
  // c->SaveAs("myDR.png");
  // c->SaveAs("myIso10.png");
  // c->SaveAs("myTrackPt.png");
    return c;
}

void RunOverData(TString inYear ="", TString inTTVA="", TString Pileup = ""){
    SetAtlasStyle();
    cout<<"debug hello"<<endl;
    cout<<inYear<<inTTVA<<endl;
    TString myDir = "/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/";
    // TCanvas* myC = alltrksExample_fileLoop_v2(2018);
    // TString inYear = "2016";
    // TString inTTVA = "loose";

    // TString inYear = "2017";
    // TString inYear = "2018";
    // TString inYear = "MC16a";
    // TString inYear = "MC16d";
    // TString inYear = "MC16e";
    TCanvas* myC = IsolationStudy_fileloop(inYear, inTTVA, Pileup);
    myC->GetListOfPrimitives()->Print();
    // myC->SaveAs(myDir+"data/"+inYear+"_"+inTTVA+"chi2_2019Jun6.root");
    // myC->SaveAs(myDir+"figures/"+inYear+"_"+inTTVA+"chi2_2019Jun6.png");
    // myC->SaveAs(myDir+"data/"+inYear+"_"+inTTVA+"chi2_2019Jun10.root");
    // myC->SaveAs(myDir+"figures/"+inYear+"_"+inTTVA+"chi2_2019Jun10.png");
    // myC->SaveAs(myDir+"data/"+inYear+"_"+inTTVA+"chi2_2019Jun12.root");
    // myC->SaveAs(myDir+"figures/"+inYear+"_"+inTTVA+"chi2_2019Jun12.png");
    // myC->SaveAs(myDir+"data/"+inYear+"_"+inTTVA+"_"+Pileup+"_"+"chi2_2019Jun19.root");
    // myC->SaveAs(myDir+"figures/"+inYear+"_"+inTTVA+"_"+Pileup+"_"+"chi2_2019Jun19.png");
    // myC->SaveAs(myDir+"data/"+inYear+"_"+inTTVA+"_"+Pileup+"_"+"chi2_2019Jun25.root");
    // myC->SaveAs(myDir+"figures/"+inYear+"_"+inTTVA+"_"+Pileup+"_"+"chi2_2019Jun25.png");
    myC->SaveAs(myDir+"data/"+inYear+"_"+inTTVA+"_"+Pileup+"_"+"chi2_2019Jun26.root");
    myC->SaveAs(myDir+"figures/"+inYear+"_"+inTTVA+"_"+Pileup+"_"+"chi2_2019Jun26.png");

}

void RunOverSavedFiles_Chi2(TString theYear="", TString Association="", TString TTVA=""){
    SetAtlasStyle();
    // TString Vertex = "PV";
    TString Vertex = "VTX";
    // TString FileDate = "2019Jun25";
    TString FileDate = "2019Jun26";
    //pull from saved histos
    // //
    // TString Association ="nonAss";
    // TString theYear="2017";
    // TString Association ="otherPV";
    // TString Association ="assPV";

      TString myDir = "/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/data/";
    //chi2 files
    int numberOfBinsChi2 = 200;
    // TFile* ifile_chi2_loose = new TFile(myDir+theYear+"_loosechi2_2019Jun6.root");
    // TFile* ifile_chi2_loose = new TFile(myDir+theYear+"_loosechi2_2019Jun12.root");
    // TFile* ifile_chi2_lowPU = new TFile(myDir+theYear+"_"+TTVA+"_low_chi2_2019Jun19.root");
    TFile* ifile_chi2_lowPU = new TFile(myDir+theYear+"_"+TTVA+"_low_chi2_"+FileDate+".root");
    TCanvas *Canvas_chi2_lowPU = (TCanvas*)ifile_chi2_lowPU->Get("trks chi2");

    // TH1F *h_chi2_VTX_all = (TH1F*)Canvas_chi2->GetListOfPrimitives()->FindObject("h_chi2_VTX_all");
    // h_chi2_VTX_all->Scale(1./(h_chi2_VTX_all->Integral(0, numberOfBinsChi2 + 1)));
    // TH1F *h_chi2_VTX_otherPV = (TH1F*)Canvas_chi2->GetListOfPrimitives()->FindObject("h_chi2_VTX_otherPV");
    // h_chi2_VTX_otherPV->Scale(1./(h_chi2_VTX_otherPV->Integral(0, numberOfBinsChi2 + 1)));
    // TH1F *h_chi2_VTX_nonAss = (TH1F*)Canvas_chi2->GetListOfPrimitives()->FindObject("h_chi2_VTX_nonAss");
    // h_chi2_VTX_nonAss->Scale(1./(h_chi2_VTX_nonAss->Integral(0, numberOfBinsChi2 + 1)));
    // TH1F *h_chi2_VTX_assPV = (TH1F*)Canvas_chi2->GetListOfPrimitives()->FindObject("h_chi2_VTX_assPV");
    // h_chi2_VTX_assPV->Scale(1./(h_chi2_VTX_assPV->Integral(0, numberOfBinsChi2 + 1)));

    TH1F *h_chi2_PV_otherPV_lowPU = (TH1F*)Canvas_chi2_lowPU->GetListOfPrimitives()->FindObject("h_chi2_"+Vertex+"_otherPV");
    // h_chi2_PV_otherPV_lowPU->Scale(1./(h_chi2_PV_otherPV_lowPU->Integral(0, numberOfBinsChi2 + 1)));
    TH1F *h_chi2_PV_nonAss_lowPU = (TH1F*)Canvas_chi2_lowPU->GetListOfPrimitives()->FindObject("h_chi2_"+Vertex+"_nonAss");
    // h_chi2_PV_nonAss_lowPU->Scale(1./(h_chi2_PV_nonAss_lowPU->Integral(0, numberOfBinsChi2 + 1)));
    TH1F *h_chi2_PV_assPV_lowPU = (TH1F*)Canvas_chi2_lowPU->GetListOfPrimitives()->FindObject("h_chi2_"+Vertex+"_assPV");
    // h_chi2_PV_assPV_lowPU->Scale(1./(h_chi2_PV_assPV_lowPU->Integral(0, numberOfBinsChi2 + 1)));
    ifile_chi2_lowPU->Close();
    // cout<<"DEBUG 2019Jun5 4"<<endl;
    // cout<<"Loose otherPV: "<< h_chi2_PV_otherPV_loose->GetEntries() <<endl;
    // cout<<"Loose nonAss: "<< h_chi2_PV_nonAss_loose->GetEntries() <<endl;
    // cout<<"Loose assPV: "<< h_chi2_PV_assPV_loose->GetEntries() <<endl;
    ////
    // TFile* ifile_chi2_nominal = new TFile(myDir+theYear+"_nominalchi2_2019Jun6.root");
    // TFile* ifile_chi2_nominal = new TFile(myDir+theYear+"_nominalchi2_2019Jun10.root");
    // TFile* ifile_chi2_nominal = new TFile(myDir+theYear+"_nominalchi2_2019Jun12.root");
    // TFile* ifile_chi2_mediumPU = new TFile(myDir+theYear+"_"+TTVA+"_medium_chi2_2019Jun19.root");
    TFile* ifile_chi2_mediumPU = new TFile(myDir+theYear+"_"+TTVA+"_medium_chi2_"+FileDate+".root");
    TCanvas *Canvas_chi2_mediumPU = (TCanvas*)ifile_chi2_mediumPU->Get("trks chi2");
    
    TH1F *h_chi2_PV_otherPV_mediumPU = (TH1F*)Canvas_chi2_mediumPU->GetListOfPrimitives()->FindObject("h_chi2_"+Vertex+"_otherPV");
    // h_chi2_PV_otherPV_mediumPU->Scale(1./(h_chi2_PV_otherPV_mediumPU->Integral(0, numberOfBinsChi2 + 1)));
    TH1F *h_chi2_PV_nonAss_mediumPU = (TH1F*)Canvas_chi2_mediumPU->GetListOfPrimitives()->FindObject("h_chi2_"+Vertex+"_nonAss");
    // h_chi2_PV_nonAss_mediumPU->Scale(1./(h_chi2_PV_nonAss_mediumPU->Integral(0, numberOfBinsChi2 + 1)));
    TH1F *h_chi2_PV_assPV_mediumPU = (TH1F*)Canvas_chi2_mediumPU->GetListOfPrimitives()->FindObject("h_chi2_"+Vertex+"_assPV");
    // h_chi2_PV_assPV_mediumPU->Scale(1./(h_chi2_PV_assPV_mediumPU->Integral(0, numberOfBinsChi2 + 1)));
    
    ifile_chi2_mediumPU->Close();
    // cout<<"nominal otherPV: "<< h_chi2_PV_otherPV_nominal->GetEntries() <<endl;
    // cout<<"nominal nonAss: "<< h_chi2_PV_nonAss_nominal->GetEntries() <<endl;
    // cout<<"nominal assPV: "<< h_chi2_PV_assPV_nominal->GetEntries() <<endl;
////
    // TFile* ifile_chi2_tight = new TFile(myDir+theYear+"_tightchi2_2019Jun6.root");
    // TFile* ifile_chi2_tight = new TFile(myDir+theYear+"_tightchi2_2019Jun10.root");
    // TFile* ifile_chi2_tight = new TFile(myDir+theYear+"_tightchi2_2019Jun12.root");
    // TFile* ifile_chi2_highPU = new TFile(myDir+theYear+"_"+TTVA+"_high_chi2_2019Jun19.root");
    TFile* ifile_chi2_highPU = new TFile(myDir+theYear+"_"+TTVA+"_high_chi2_"+FileDate+".root");
    TCanvas *Canvas_chi2_highPU = (TCanvas*)ifile_chi2_highPU->Get("trks chi2");
    
    TH1F *h_chi2_PV_otherPV_highPU = (TH1F*)Canvas_chi2_highPU->GetListOfPrimitives()->FindObject("h_chi2_"+Vertex+"_otherPV");
    // h_chi2_PV_otherPV_highPU->Scale(1./(h_chi2_PV_otherPV_highPU->Integral(0, numberOfBinsChi2 + 1)));
    TH1F *h_chi2_PV_nonAss_highPU = (TH1F*)Canvas_chi2_highPU->GetListOfPrimitives()->FindObject("h_chi2_"+Vertex+"_nonAss");
    // h_chi2_PV_nonAss_highPU->Scale(1./(h_chi2_PV_nonAss_highPU->Integral(0, numberOfBinsChi2 + 1)));
    TH1F *h_chi2_PV_assPV_highPU = (TH1F*)Canvas_chi2_highPU->GetListOfPrimitives()->FindObject("h_chi2_"+Vertex+"_assPV");
    // h_chi2_PV_assPV_highPU->Scale(1./(h_chi2_PV_assPV_highPU->Integral(0, numberOfBinsChi2 + 1)));
    
    ifile_chi2_highPU->Close();
    // cout<<"tight otherPV: "<< h_chi2_PV_otherPV_tight->GetEntries() <<endl;
    // cout<<"tight nonAss: "<< h_chi2_PV_nonAss_tight->GetEntries() <<endl;
    // cout<<"tight assPV: "<< h_chi2_PV_assPV_tight->GetEntries() <<endl;

    ////


    TCanvas* allC = new TCanvas("allC","allC",900,600);
    allC->SetLogy();
    // // if (h_isoAll_Run1) h_isoAll_Run1->Draw();
    // // if (h_isoBlinded_Run1) h_isoBlinded_Run1->Draw("same");
    // h_isoRun2Cuts_Run1->SetLineColor(kRed);
    // h_isoRun2Cuts_Run1->SetMarkerSize(0.);

    // h_iso_1516->SetLineColor(kBlack);
    // h_iso_1516->SetMarkerSize(0.);
    // h_iso_2017->SetLineColor(kBlue);

    // h_iso_2017->SetMarkerSize(0.);
    // h_my_iso_nonAss_2017->SetLineColor(kBlue);
    // h_my_iso_nonAss_2017->SetMarkerSize(0.);;
    // // h_my_iso_nonAss_2017_isTightPrimary->SetLineColor(kBlue);
    // h_my_iso_nonAss_2017_IdHits->SetLineColor(kBlue);
    // h_my_iso_nonAss_2017_IdHits->SetMarkerSize(0.);
    // h_my_iso_all_2017_IdHits->SetLineColor(kBlue);
    // h_my_iso_all_2017_IdHits->SetMarkerSize(0.);

    // h_iso_2018->SetLineColor(kGreen+1);
    // h_iso_2018->SetMarkerSize(0.);
    // h_my_iso_nonAss_2018->SetLineColor(kGreen+1);
    // h_my_iso_nonAss_2018->SetMarkerSize(0.);
    // h_my_iso_all_2018_IdHits->SetLineColor(kGreen+1);
    // h_my_iso_all_2018_IdHits->SetMarkerSize(0.);
    // // h_my_iso_nonAss_2018_isTightPrimary->SetLineColor(kGreen+1);
    // h_my_iso_nonAss_2018_IdHits->SetLineColor(kGreen+1);
    // h_my_iso_nonAss_2018_IdHits->SetMarkerSize(0.);
    // h_chi2_VTX_all->SetLineColor(kRed);
    // h_chi2_VTX_all->SetMarkerSize(0.);
    // h_chi2_VTX_assPV->SetLineColor(kBlue);
    // h_chi2_VTX_assPV->SetMarkerSize(0.);
    // h_chi2_VTX_otherPV->SetLineColor(kGreen+2);
    // h_chi2_VTX_otherPV->SetMarkerSize(0.);
    // h_chi2_VTX_nonAss->SetLineColor(kMagenta+2);
    // h_chi2_VTX_nonAss->SetMarkerSize(0.);

    // h_chi2_PV_assPV->SetLineColor(kBlue);
    // h_chi2_PV_assPV->SetMarkerSize(0.);
    // h_chi2_PV_otherPV->SetLineColor(kGreen+2);
    // h_chi2_PV_otherPV->SetMarkerSize(0.);
    // h_chi2_PV_nonAss->SetLineColor(kMagenta+2);
    // h_chi2_PV_nonAss->SetMarkerSize(0.);

    h_chi2_PV_otherPV_lowPU->SetLineColor(kBlue); 
    h_chi2_PV_otherPV_lowPU->SetMarkerSize(0.);
    h_chi2_PV_nonAss_lowPU->SetLineColor(kBlue); 
    h_chi2_PV_nonAss_lowPU->SetMarkerSize(0.);
    h_chi2_PV_assPV_lowPU->SetLineColor(kBlue); 
    h_chi2_PV_assPV_lowPU->SetMarkerSize(0.);
    h_chi2_PV_otherPV_mediumPU->SetLineColor(kRed); 
    h_chi2_PV_otherPV_mediumPU->SetMarkerSize(0.);
    h_chi2_PV_nonAss_mediumPU->SetLineColor(kRed); 
    h_chi2_PV_nonAss_mediumPU->SetMarkerSize(0.);
    h_chi2_PV_assPV_mediumPU->SetLineColor(kRed); 
    h_chi2_PV_assPV_mediumPU->SetMarkerSize(0.);
    h_chi2_PV_otherPV_highPU->SetLineColor(kGreen+2); 
    h_chi2_PV_otherPV_highPU->SetMarkerSize(0.);
    h_chi2_PV_nonAss_highPU->SetLineColor(kGreen+2); 
    h_chi2_PV_nonAss_highPU->SetMarkerSize(0.);
    h_chi2_PV_assPV_highPU->SetLineColor(kGreen+2); 
    h_chi2_PV_assPV_highPU->SetMarkerSize(0.);

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
    TString XaxisTitle("");
if (Vertex.EqualTo("PV")){
    XaxisTitle = "ln(#chi^{2}) Track to PV";
}else if (Vertex.EqualTo("VTX")){
    XaxisTitle = "ln(#chi^{2}) Track to SV";
}
    // if (h_chi2_PV_all) h_chi2_PV_all->Draw("e0 hist");
    TLegend* legAll(NULL);
if(Association.EqualTo("otherPV")){
    if (h_chi2_PV_otherPV_lowPU) h_chi2_PV_otherPV_lowPU->GetXaxis()->SetLimits(-15,15);
    if (h_chi2_PV_otherPV_lowPU) h_chi2_PV_otherPV_lowPU->Draw("e0 hist");
    if (h_chi2_PV_otherPV_mediumPU) h_chi2_PV_otherPV_mediumPU->Draw("e0 hist same");
    if (h_chi2_PV_otherPV_highPU) h_chi2_PV_otherPV_highPU->Draw("e0 hist same");
    h_chi2_PV_otherPV_lowPU->GetXaxis()->SetTitle(XaxisTitle);
    h_chi2_PV_otherPV_lowPU->GetYaxis()->SetTitle("Candidates * Num. of Trks per cand.");
    if(theYear.Contains("MC")) h_chi2_PV_otherPV_lowPU->SetMaximum(1e4);
    if(theYear.Contains("2017")) h_chi2_PV_otherPV_lowPU->SetMaximum(1e5);
    h_chi2_PV_otherPV_lowPU->SetMinimum(5e-2);
    legAll = new TLegend(0.2, 0.75, 0.3, 0.9);
}

if(Association.EqualTo("nonAss")){
     if (h_chi2_PV_nonAss_lowPU) h_chi2_PV_nonAss_lowPU->GetXaxis()->SetLimits(-15,15);
    if (h_chi2_PV_nonAss_lowPU) h_chi2_PV_nonAss_lowPU->Draw("e0 hist");
    if (h_chi2_PV_nonAss_mediumPU) h_chi2_PV_nonAss_mediumPU->Draw("e0 hist same");
    if (h_chi2_PV_nonAss_highPU) h_chi2_PV_nonAss_highPU->Draw("e0 hist same");
    h_chi2_PV_nonAss_lowPU->GetXaxis()->SetTitle(XaxisTitle);
    h_chi2_PV_nonAss_lowPU->GetYaxis()->SetTitle("Candidates * Num. of Trks per cand.");
    if(theYear.Contains("MC")) h_chi2_PV_nonAss_lowPU->SetMaximum(1e4);
    if(theYear.Contains("2017")) h_chi2_PV_nonAss_lowPU->SetMaximum(1e5);
    h_chi2_PV_nonAss_lowPU->SetMinimum(5e-2);
    legAll = new TLegend(0.2, 0.75, 0.3, 0.9);
}    
if(Association.EqualTo("assPV")){
    if (h_chi2_PV_assPV_lowPU) h_chi2_PV_assPV_lowPU->GetXaxis()->SetLimits(-15,15);
    if (h_chi2_PV_assPV_lowPU) h_chi2_PV_assPV_lowPU->Draw("e0 hist");
    if (h_chi2_PV_assPV_mediumPU) h_chi2_PV_assPV_mediumPU->Draw("e0 hist same");
    if (h_chi2_PV_assPV_highPU) h_chi2_PV_assPV_highPU->Draw("e0 hist same");
    h_chi2_PV_assPV_lowPU->GetXaxis()->SetTitle(XaxisTitle);
    h_chi2_PV_assPV_lowPU->GetYaxis()->SetTitle("Candidates * Num. of Trks per cand.");
    if(theYear.Contains("MC")) h_chi2_PV_assPV_lowPU->SetMaximum(1e4);
    if(theYear.Contains("2017")) h_chi2_PV_assPV_lowPU->SetMaximum(1e5);
    h_chi2_PV_assPV_lowPU->SetMinimum(5e-2);
    legAll = new TLegend(0.2, 0.75, 0.3, 0.9);
}
    // h_chi2_PV_all->GetYaxis()->SetTitle("a.u.");

    
    
    // legAll->SetTextSize(0.034468);
    legAll->SetTextSize(0.03);
    // legAll->SetHeader("2017 Decay Vertex");
    // legAll->AddEntry(h_chi2_VTX_all, "All Tracks" ,"l");
    // legAll->AddEntry(h_chi2_VTX_assPV, "Tracks Associated to B PV" ,"l");
    // legAll->AddEntry(h_chi2_VTX_otherPV, "Tracks Assoc. to B PV and other PVs" ,"l");
    // legAll->AddEntry(h_chi2_VTX_nonAss, "Tracks Assoc. to B PV and not Assoc. to any PV" ,"l");

    // legAll->SetHeader("2017 Primary Vertex");
            // cout<<"DEBUG 2019Jun17 1"<<endl;
    TString TTVAtext="";
        if (TTVA.EqualTo("loose")) {
            TTVAtext = "TTVA Loose WP";
        }else if(TTVA.EqualTo("nominal")) {
            TTVAtext = "TTVA Nominal WP";
        }else if(TTVA.EqualTo("tight")) {
            TTVAtext = "TTVA Tight WP";
        }
    TLatex texMessage;
    //     // texMessage = new TLatex(, , TTVAtext);
    //     // texMessage->SetTextFont(62);
    //     // texMessage->SetTextSize(0.025);
    //     // texMessage->SetTextColorAlpha(1,0.4);
    //     // texMessage->SetLineWidth(2);
    //     // texMessage->SetTextAngle(90);
    texMessage.SetTextSize(0.03);
    texMessage.SetTextFont(42);
    texMessage.DrawLatexNDC(0.23, 0.67, TTVAtext);

    if(Association.EqualTo("otherPV")){
        legAll->SetHeader(theYear + " Tracks Assoc. other PVs");
    }
    if(Association.EqualTo("nonAss")){
        legAll->SetHeader(theYear + " Tracks not Assoc. to any PV");
    }
    if(Association.EqualTo("assPV")){
        legAll->SetHeader(theYear + " Tracks Associated to B PV");
    }
//tight label doesn't matter here as long as the line colors don't change
    // legAll->AddEntry(h_chi2_PV_assPV_loose, "TTVA Loose WP" ,"l");
    // legAll->AddEntry(h_chi2_PV_otherPV_nominal, "TTVA Nominal WP" ,"l");
    // legAll->AddEntry(h_chi2_PV_nonAss_tight, "TTVA Tight WP" ,"l");
    if (theYear.Contains("MC")){
        legAll->AddEntry(h_chi2_PV_assPV_lowPU, "21<PRIVX_{#mu}<32" ,"l");
        legAll->AddEntry(h_chi2_PV_otherPV_mediumPU, "34<PRIVX_{#mu}<43" ,"l");
        legAll->AddEntry(h_chi2_PV_nonAss_highPU, "44<PRIVX_{#mu}<55" ,"l");
        }
    else{
        legAll->AddEntry(h_chi2_PV_assPV_lowPU, "22.493<PRIVX_{#mu}<29.0" ,"l");
        legAll->AddEntry(h_chi2_PV_otherPV_mediumPU, "36.352<PRIVX_{#mu}<43.0" ,"l");
        legAll->AddEntry(h_chi2_PV_nonAss_highPU, "45.0<PRIVX_{#mu}<55.0" ,"l");
    }
    // cout<<"DEBUG 2019Jun17 2"<<endl;

    // legAll->AddEntry(h_isoBlinded_Run1, "h_isoBlinded_Run1" ,"l");
    // legAll->AddEntry(h_isoRun2Cuts_Run1, "Run1 w/Run 2 cuts" ,"l");
    // legAll->AddEntry(h_iso_1516, "2015 and 2016 data" ,"l");
    // legAll->AddEntry(h_my_iso_nonAss_2017_IdHits, "2017 run (with Non-Assoc. Tracks and spec ID hits)" ,"l");
    // legAll->AddEntry(h_my_iso_nonAss_2018_IdHits, "2018 run (with Non-Assoc. Tracks and spec ID hits)" ,"l");
    // legAll->AddEntry(h_my_iso_nonAss_2017_IdHits, "2017 run (with Non-Assoc. Tracks)" ,"l");
    // legAll->AddEntry(h_my_iso_nonAss_2018_IdHits, "2018 run (with Non-Assoc. Tracks)" ,"l");
    // legAll->AddEntry(h_my_iso_all_2017_IdHits, "2017 run (with all Trks, ntrks #chi^{2} < 5)" ,"l");
    // legAll->AddEntry(h_my_iso_all_2018_IdHits, "2018 run (with all Trks, ntrks #chi^{2} < 5)" ,"l");
    // legAll->AddEntry(h_my_iso_all_2017_IdHits, "2017 run (with all Trks, spec ID hits, ntrks #chi^{2} < 5)" ,"l");
    // legAll->AddEntry(h_my_iso_all_2018_IdHits, "2018 run (with all Trks, spec ID hits, ntrks #chi^{2} < 5)" ,"l");
    // legAll->AddEntry(h_my_iso_all_2017_IdHits, "2017 run (with all Trks, spec ID hits, ntrks #chi^{2} < 4)" ,"l");
    // legAll->AddEntry(h_my_iso_all_2018_IdHits, "2018 run (with all Trks, spec ID hits, ntrks #chi^{2} < 4)" ,"l");
    // legAll->AddEntry(h_my_iso_nonAss_2017_IdHits, "2017 run (default calculation)" ,"l");
    // legAll->AddEntry(h_my_iso_nonAss_2018_IdHits, "2018 run (default calculation)" ,"l");
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
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/Chi2/"+theYear+Association+"_2019Jun6.png");
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/Chi2/"+theYear+Association+"_2019Jun10.png");
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/Chi2/"+theYear+Association+"_combo_2019Jun12.png");
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/Chi2/"+theYear+Association+"_combo_2019Jun17.png");
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/Chi2/"+theYear+Association+"_"+Pileup+"_"+Vertex+"_2019Jun19.png");
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/Chi2/"+theYear+Association+"_"+Pileup+"_"+Vertex+"_2019Jun20.png");
    allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/Chi2/"+theYear+Association+"_"+TTVA+"_"+Vertex+"_"+FileDate+".png");
        // cout<<"DEBUG 2019Jun17 3"<<endl;

}


void DrawMyPlots(){
      // SetAtlasStyle();
      // RunOverData();
      // RunOverSavedFiles_Iso();
      // RunOverSavedFiles_Ntrks();
      // RunOverSavedFiles_IsoTrks();
    RunOverSavedFiles_Chi2();
    // cout<<""<<endl;
}


int main(int argc, char* argv[])
{
  TString  pattern, pattern2, pattern3;
  // if (argc>1) inpath = TString(argv[1]);
  if (argc>1) pattern = TString(argv[1]);
  if (argc>2) pattern2 = TString(argv[2]);
  if (argc>3) pattern3 = TString(argv[3]);
  // alltrksExample_fileLoop(inpath, pattern);
  // DrawMyPlots();

//One configuration:
  // //pattern -> year
  // //pattern2 -> ttva
  // RunOverData(pattern, pattern2, pattern3);
  // RunOverData(pattern, pattern2);
//Second configuration:
   // //pattern -> year
   // //pattern2 -> track association:
   // // otherPV
   // // nonAss
   // // assPV
  // RunOverSavedFiles_Chi2(pattern, pattern2);
  RunOverSavedFiles_Chi2(pattern, pattern2, pattern3);
  return 0;
}

