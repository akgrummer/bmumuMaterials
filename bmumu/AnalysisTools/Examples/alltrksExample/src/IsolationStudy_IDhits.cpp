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
//v3 includes Pix hits, SCT hits
//ID hits could also be constrained for chi2 cuts
//plot also all tracks for ID hits...

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
TCanvas* IsolationStudy_fileloop(TString myYear="", TString TTVA = ""){
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
    h_PIXhits_otherPV   = new TH1F("h_PIXhits_otherPV","chi2 to associated PV for selected tracks",100,0,100);
    h_SCThits_otherPV   = new TH1F("h_SCThits_otherPV","chi2 to associated PV for selected tracks",100,0,100);
    h_PIXhits_assPV     = new TH1F("h_PIXhits_assPV","chi2 to associated PV for selected tracks",100,0,100);
    h_SCThits_assPV     = new TH1F("h_SCThits_assPV","chi2 to associated PV for selected tracks",100,0,100);
    h_PIXhits_nonAss    = new TH1F("h_PIXhits_nonAss","chi2 to associated PV for selected tracks",100,0,100);
    h_SCThits_nonAss    = new TH1F("h_SCThits_nonAss","chi2 to associated PV for selected tracks",100,0,100);
    h_PIXhits_chi2_6    = new TH1F("h_PIXhits_chi2_6","chi2 to associated PV for selected tracks",100,0,100);
    h_SCThits_chi2_6    = new TH1F("h_SCThits_chi2_6","chi2 to associated PV for selected tracks",100,0,100);
    h_PIXhits_chi2_5    = new TH1F("h_PIXhits_chi2_5","chi2 to associated PV for selected tracks",100,0,100);
    h_SCThits_chi2_5    = new TH1F("h_SCThits_chi2_5","chi2 to associated PV for selected tracks",100,0,100);
    h_PIXhits_chi2_4    = new TH1F("h_PIXhits_chi2_4","chi2 to associated PV for selected tracks",100,0,100);
    h_SCThits_chi2_4    = new TH1F("h_SCThits_chi2_4","chi2 to associated PV for selected tracks",100,0,100);

Int_t totalTracks(0);
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
  v_float *B_PV_trksChi2 = 0;
  v_float *B_VTX_trksChi2=0;
  v_float *closeTrkDOCA_alltrks=0;
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

  //ts->SetBranchAddress("B_MUCALC_mass",&B_MUCALC_mass);
  ts->SetBranchAddress("event_index",  &event_index);                           // index to EventInfo tree

  // variables for the isolation studies
  //
  ts->SetBranchAddress("B_PV_idx",&B_PV_idx);                                  // index to associated PV  
  ts->SetBranchAddress("B_PV_trksChi2",&B_PV_trksChi2);                        // chi2 to associated PV, per track
  ts->SetBranchAddress("B_iso_7_Chi2_5_LoosePt05",&B_iso_7_Chi2_5_LoosePt05);  // DxAOD isoaltion variable
  ts->SetBranchAddress("B_iso_Ntracks_7_Chi2_5_LoosePt05",&B_iso_Ntracks_7_Chi2_5_LoosePt05);  // DxAOD isoaltion variable

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
                myTrkVec.Pt()>500.
                 // && ((*idtrk_nPIXhits).at(idx) - (*idtrk_NIBLayer).at(idx))>=1
                 // && (*idtrk_nSCThits).at(idx)>=2
               ){//&& myTrkVec.Eta()<2.5
              if (TTVA.EqualTo("loose")){ 
                 //associated to B PVs
                  if ( (*idtrk_pvidx_loose).at(idx) == B_PV_idx){
                      if (h_PIXhits_assPV) h_PIXhits_assPV->Fill((*idtrk_nPIXhits).at(idx));
                      if (h_SCThits_assPV) h_SCThits_assPV->Fill((*idtrk_nSCThits).at(idx));
                  }
                  //associated OTHER PVs
                  else if ( //(*idtrk_pvidx_loose).at(idx) != B_PV_idx) &&
                  (*idtrk_pvidx_loose).at(idx) != pv_type->size()-1 ) // or choose tracks ass. to other real PV's (for non-ass. tracks use '==' instead)
                  {   
                      if (h_PIXhits_otherPV) h_PIXhits_otherPV->Fill((*idtrk_nPIXhits).at(idx));
                      if (h_SCThits_otherPV) h_SCThits_otherPV->Fill((*idtrk_nSCThits).at(idx));
                  }
                  //non-associated
                  if ( (*idtrk_pvidx_loose).at(idx) == pv_type->size()-1 ) // or choose tracks ass. to other real PV's (for non-ass. tracks use '==' instead)
                  {   
                      if (h_PIXhits_nonAss) h_PIXhits_nonAss->Fill((*idtrk_nPIXhits).at(idx));
                      if (h_SCThits_nonAss) h_SCThits_nonAss->Fill((*idtrk_nSCThits).at(idx));
                  }
              }
              if (TTVA.EqualTo("nominal")){  
                  //associated to B PVs
                  if ( (*idtrk_pvidx_nominal).at(idx) == B_PV_idx){
                      if (h_PIXhits_assPV) h_PIXhits_assPV->Fill((*idtrk_nPIXhits).at(idx));
                      if (h_SCThits_assPV) h_SCThits_assPV->Fill((*idtrk_nSCThits).at(idx));
                  }
                  //associated OTHER PVs
                  else if ( (*idtrk_pvidx_nominal).at(idx) != pv_type->size()-1 ) // or choose tracks ass. to other real PV's (for non-ass. tracks use '==' instead)
                  {   
                      if (h_PIXhits_otherPV) h_PIXhits_otherPV->Fill((*idtrk_nPIXhits).at(idx));
                      if (h_SCThits_otherPV) h_SCThits_otherPV->Fill((*idtrk_nSCThits).at(idx));
                  }
                  //non-associated
                  if ( (*idtrk_pvidx_nominal).at(idx) == pv_type->size()-1 ) // or choose tracks ass. to other real PV's (for non-ass. tracks use '==' instead)
                  {   
                      if (h_PIXhits_nonAss) h_PIXhits_nonAss->Fill((*idtrk_nPIXhits).at(idx));
                      if (h_SCThits_nonAss) h_SCThits_nonAss->Fill((*idtrk_nSCThits).at(idx)); 
                  }
              }
              if (TTVA.EqualTo("tight")){  
                  //associated to B PVs
                  if ( (*idtrk_pvidx_tight).at(idx) == B_PV_idx){
                      if (h_PIXhits_assPV) h_PIXhits_assPV->Fill( (*idtrk_nPIXhits).at(idx) );
                      if (h_SCThits_assPV) h_SCThits_assPV->Fill( (*idtrk_nSCThits).at(idx) );
                  }
                  //associated OTHER PVs
                  else if ( (*idtrk_pvidx_tight).at(idx) != pv_type->size()-1 ) // or choose tracks ass. to other real PV's (for non-ass. tracks use '==' instead)
                  {   
                      if (h_PIXhits_otherPV) h_PIXhits_otherPV->Fill((*idtrk_nPIXhits).at(idx));
                      if (h_SCThits_otherPV) h_SCThits_otherPV->Fill((*idtrk_nSCThits).at(idx));
                  }
                  //non-associated
                  if ( (*idtrk_pvidx_tight).at(idx) == pv_type->size()-1 ) // or choose tracks ass. to other real PV's (for non-ass. tracks use '==' instead)
                  {   
                      if (h_PIXhits_nonAss) h_PIXhits_nonAss->Fill((*idtrk_nPIXhits).at(idx));
                      if (h_SCThits_nonAss) h_SCThits_nonAss->Fill((*idtrk_nSCThits).at(idx));
                  }
              }
              if (TTVA.EqualTo("chi2Study")){  
                  //associated to B PVs
                if ((*B_PV_trksChi2).at(idx)<6. 
                ){
                      if (h_PIXhits_chi2_6) h_PIXhits_chi2_6->Fill( (*idtrk_nPIXhits).at(idx) );
                      if (h_SCThits_chi2_6) h_SCThits_chi2_6->Fill( (*idtrk_nSCThits).at(idx) );
                  }
                  //associated OTHER PVs
                if ((*B_PV_trksChi2).at(idx)<5. 
                ){   
                      if (h_PIXhits_chi2_5) h_PIXhits_chi2_5->Fill((*idtrk_nPIXhits).at(idx));
                      if (h_SCThits_chi2_5) h_SCThits_chi2_5->Fill((*idtrk_nSCThits).at(idx));
                  }
                  //non-associated
                if ((*B_PV_trksChi2).at(idx)<4. 
                ){  
                      if (h_PIXhits_chi2_4) h_PIXhits_chi2_4->Fill((*idtrk_nPIXhits).at(idx));
                      if (h_SCThits_chi2_4) h_SCThits_chi2_4->Fill((*idtrk_nSCThits).at(idx));
                  }
              }
                        // if ((*B_VTX_trksChi2).at(idx)<=1.0) nclosetrks_all++;
                // } 
            }
        }

    }
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
    // if (h_chi2_VTX_otherPV)h_chi2_VTX_otherPV->Draw();
    // if (h_chi2_PV_otherPV)h_chi2_PV_otherPV->Draw("same");
    // if (h_chi2_VTX_assPV)h_chi2_VTX_assPV->Draw("same");
    // if (h_chi2_PV_assPV)h_chi2_PV_assPV->Draw("same");
    // if (h_chi2_VTX_nonAss)h_chi2_VTX_nonAss->Draw("same");
    // if (h_chi2_PV_nonAss)h_chi2_PV_nonAss->Draw("same");
        // if (h_ntrks_orig) h_ntrks_orig->Draw();
        // if (h_ntrks_all) h_ntrks_all->Draw("same");
        // if (h_ntrks_assPV) h_ntrks_assPV->Draw("same");
        // if (h_ntrks_otherPV) h_ntrks_otherPV->Draw("same");
        // if (h_ntrks_nonAss) h_ntrks_nonAss->Draw("same");
    if(TTVA.EqualTo("chi2Study")){
        if(h_PIXhits_chi2_6) h_PIXhits_chi2_6->Draw();
        if(h_SCThits_chi2_6) h_SCThits_chi2_6->Draw("same");
        if(h_PIXhits_chi2_5) h_PIXhits_chi2_5->Draw("same");
        if(h_SCThits_chi2_5) h_SCThits_chi2_5->Draw("same");
        if(h_PIXhits_chi2_4) h_PIXhits_chi2_4->Draw("same");
        if(h_SCThits_chi2_4) h_SCThits_chi2_4->Draw("same");
    h_PIXhits_chi2_6->GetXaxis()->SetTitle("hits");
    h_PIXhits_chi2_6->GetYaxis()->SetTitle("a.u.");
    }else{
        if (h_PIXhits_otherPV) h_PIXhits_otherPV->Draw();
        if (h_SCThits_otherPV) h_SCThits_otherPV->Draw("same");
        if (h_PIXhits_assPV) h_PIXhits_assPV->Draw("same");
        if (h_SCThits_assPV) h_SCThits_assPV->Draw("same");
        if (h_PIXhits_nonAss) h_PIXhits_nonAss->Draw("same");
        if (h_SCThits_nonAss) h_SCThits_nonAss->Draw("same");
    h_PIXhits_otherPV->GetXaxis()->SetTitle("hits");
    h_PIXhits_otherPV->GetYaxis()->SetTitle("a.u.");
    }
  }
    // TLegend* leg = new TLegend(0.4, 0.6, 0.5, 0.7,NULL,"brNDC");
  //DR
    // TLegend* leg = new TLegend(0.7, 0.7, 0.8, 0.8,NULL,"brNDC");
    //iso

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

void RunOverData(TString inYear ="", TString inTTVA=""){
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
    TCanvas* myC = IsolationStudy_fileloop(inYear, inTTVA);
    myC->GetListOfPrimitives()->Print();
    myC->SaveAs(myDir+"data/"+inYear+"_"+inTTVA+"_IDhits_2019Jun10.root");
    myC->SaveAs(myDir+"figures/"+inYear+"_"+inTTVA+"_IDhits_2019Jun10.png");

}

void RunOverSavedFiles_Chi2(TString theYear="", TString Association="", TString Detector=""){
    SetAtlasStyle();

      TString myDir = "/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/data/";
    //chi2 files
    int numberOfBinsChi2 = 200;

    TFile* ifile_chi2_loose = new TFile(myDir+theYear+"_loose_IDhits_2019Jun10.root");
    TCanvas *Canvas_chi2_loose = (TCanvas*)ifile_chi2_loose->Get("trks chi2");


    TH1F *h_PIXhits_otherPV_loose = (TH1F*)Canvas_chi2_loose->GetListOfPrimitives()->FindObject("h_PIXhits_otherPV");
    TH1F *h_SCThits_otherPV_loose = (TH1F*)Canvas_chi2_loose->GetListOfPrimitives()->FindObject("h_SCThits_otherPV");
    // h_chi2_PV_otherPV_loose->Scale(1./(h_chi2_PV_otherPV_loose->Integral(0, numberOfBinsChi2 + 1)));
    TH1F *h_PIXhits_assPV_loose = (TH1F*)Canvas_chi2_loose->GetListOfPrimitives()->FindObject("h_PIXhits_assPV");
    TH1F *h_SCThits_assPV_loose = (TH1F*)Canvas_chi2_loose->GetListOfPrimitives()->FindObject("h_SCThits_assPV");
    // h_chi2_PV_nonAss_loose->Scale(1./(h_chi2_PV_nonAss_loose->Integral(0, numberOfBinsChi2 + 1)));
    TH1F *h_PIXhits_nonAss_loose = (TH1F*)Canvas_chi2_loose->GetListOfPrimitives()->FindObject("h_PIXhits_nonAss");
    TH1F *h_SCThits_nonAss_loose = (TH1F*)Canvas_chi2_loose->GetListOfPrimitives()->FindObject("h_SCThits_nonAss");
    // h_chi2_PV_assPV_loose->Scale(1./(h_chi2_PV_assPV_loose->Integral(0, numberOfBinsChi2 + 1)));
    ifile_chi2_loose->Close();

    ////
    TFile* ifile_chi2_nominal = new TFile(myDir+theYear+"_nominal_IDhits_2019Jun10.root");
    TCanvas *Canvas_chi2_nominal = (TCanvas*)ifile_chi2_nominal->Get("trks chi2");
    
    TH1F *h_PIXhits_otherPV_nominal = (TH1F*)Canvas_chi2_nominal->GetListOfPrimitives()->FindObject("h_PIXhits_otherPV");
    TH1F *h_SCThits_otherPV_nominal = (TH1F*)Canvas_chi2_nominal->GetListOfPrimitives()->FindObject("h_SCThits_otherPV");
    TH1F *h_PIXhits_assPV_nominal = (TH1F*)Canvas_chi2_nominal->GetListOfPrimitives()->FindObject("h_PIXhits_assPV");
    TH1F *h_SCThits_assPV_nominal = (TH1F*)Canvas_chi2_nominal->GetListOfPrimitives()->FindObject("h_SCThits_assPV");
    TH1F *h_PIXhits_nonAss_nominal = (TH1F*)Canvas_chi2_nominal->GetListOfPrimitives()->FindObject("h_PIXhits_nonAss");
    TH1F *h_SCThits_nonAss_nominal = (TH1F*)Canvas_chi2_nominal->GetListOfPrimitives()->FindObject("h_SCThits_nonAss");
    ifile_chi2_nominal->Close();
////
    TFile* ifile_chi2_tight = new TFile(myDir+theYear+"_tight_IDhits_2019Jun10.root");
    TCanvas *Canvas_chi2_tight = (TCanvas*)ifile_chi2_tight->Get("trks chi2");
    
    TH1F *h_PIXhits_otherPV_tight = (TH1F*)Canvas_chi2_tight->GetListOfPrimitives()->FindObject("h_PIXhits_otherPV");
    TH1F *h_SCThits_otherPV_tight = (TH1F*)Canvas_chi2_tight->GetListOfPrimitives()->FindObject("h_SCThits_otherPV");
    TH1F *h_PIXhits_assPV_tight = (TH1F*)Canvas_chi2_tight->GetListOfPrimitives()->FindObject("h_PIXhits_assPV");
    TH1F *h_SCThits_assPV_tight = (TH1F*)Canvas_chi2_tight->GetListOfPrimitives()->FindObject("h_SCThits_assPV");
    TH1F *h_PIXhits_nonAss_tight = (TH1F*)Canvas_chi2_tight->GetListOfPrimitives()->FindObject("h_PIXhits_nonAss");
    TH1F *h_SCThits_nonAss_tight = (TH1F*)Canvas_chi2_tight->GetListOfPrimitives()->FindObject("h_SCThits_nonAss");
    
    ifile_chi2_tight->Close();
////
        cout<<"DEBUG 2019Jun5 1"<<endl;
    TFile* ifile_chi2Study = new TFile(myDir+theYear+"_chi2Study_IDhits_2019Jun10.root");
    TCanvas *Canvas_chi2Study = (TCanvas*)ifile_chi2Study->Get("trks chi2");
        cout<<"DEBUG 2019Jun5 2"<<endl;
    TH1F *h_Chi2Study_PIXhits_chi2_6 = (TH1F*)Canvas_chi2Study->GetListOfPrimitives()->FindObject("h_PIXhits_chi2_6");
    TH1F *h_Chi2Study_SCThits_chi2_6 = (TH1F*)Canvas_chi2Study->GetListOfPrimitives()->FindObject("h_SCThits_chi2_6");
    TH1F *h_Chi2Study_PIXhits_chi2_5 = (TH1F*)Canvas_chi2Study->GetListOfPrimitives()->FindObject("h_PIXhits_chi2_5");
    TH1F *h_Chi2Study_SCThits_chi2_5 = (TH1F*)Canvas_chi2Study->GetListOfPrimitives()->FindObject("h_SCThits_chi2_5");
    TH1F *h_Chi2Study_PIXhits_chi2_4 = (TH1F*)Canvas_chi2Study->GetListOfPrimitives()->FindObject("h_PIXhits_chi2_4");
    TH1F *h_Chi2Study_SCThits_chi2_4 = (TH1F*)Canvas_chi2Study->GetListOfPrimitives()->FindObject("h_SCThits_chi2_4");
    
    ifile_chi2Study->Close();
    cout<<"DEBUG 2019Jun5 4"<<endl;

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

    h_PIXhits_otherPV_loose->SetLineColor(kBlue); 
    h_PIXhits_otherPV_loose->SetMarkerSize(0.);
    h_SCThits_otherPV_loose->SetLineColor(kBlue);
    h_SCThits_otherPV_loose->SetMarkerSize(0.);
    h_PIXhits_assPV_loose->SetLineColor(kBlue); 
    h_PIXhits_assPV_loose->SetMarkerSize(0.);
    h_SCThits_assPV_loose->SetLineColor(kBlue);
    h_SCThits_assPV_loose->SetMarkerSize(0.);
    h_PIXhits_nonAss_loose->SetLineColor(kBlue); 
    h_PIXhits_nonAss_loose->SetMarkerSize(0.);
    h_SCThits_nonAss_loose->SetLineColor(kBlue);
    h_SCThits_nonAss_loose->SetMarkerSize(0.);
    h_PIXhits_otherPV_nominal->SetLineColor(kRed); 
    h_PIXhits_otherPV_nominal->SetMarkerSize(0.);
    h_SCThits_otherPV_nominal->SetLineColor(kRed);
    h_SCThits_otherPV_nominal->SetMarkerSize(0.);
    h_PIXhits_assPV_nominal->SetLineColor(kRed); 
    h_PIXhits_assPV_nominal->SetMarkerSize(0.);
    h_SCThits_assPV_nominal->SetLineColor(kRed);
    h_SCThits_assPV_nominal->SetMarkerSize(0.);
    h_PIXhits_nonAss_nominal->SetLineColor(kRed); 
    h_PIXhits_nonAss_nominal->SetMarkerSize(0.);
    h_SCThits_nonAss_nominal->SetLineColor(kRed);
    h_SCThits_nonAss_nominal->SetMarkerSize(0.);
    h_PIXhits_otherPV_tight->SetLineColor(kGreen+2); 
    h_PIXhits_otherPV_tight->SetMarkerSize(0.);
    h_SCThits_otherPV_tight->SetLineColor(kGreen+2);
    h_SCThits_otherPV_tight->SetMarkerSize(0.);
    h_PIXhits_assPV_tight->SetLineColor(kGreen+2); 
    h_PIXhits_assPV_tight->SetMarkerSize(0.);
    h_SCThits_assPV_tight->SetLineColor(kGreen+2);
    h_SCThits_assPV_tight->SetMarkerSize(0.);
    h_PIXhits_nonAss_tight->SetLineColor(kGreen+2); 
    h_PIXhits_nonAss_tight->SetMarkerSize(0.);
    h_SCThits_nonAss_tight->SetLineColor(kGreen+2);
    h_SCThits_nonAss_tight->SetMarkerSize(0.);

    h_Chi2Study_PIXhits_chi2_6->SetLineColor(kBlue); 
    h_Chi2Study_PIXhits_chi2_6->SetMarkerSize(0.);
    h_Chi2Study_SCThits_chi2_6->SetLineColor(kBlue); 
    h_Chi2Study_SCThits_chi2_6->SetMarkerSize(0.);
    h_Chi2Study_PIXhits_chi2_5->SetLineColor(kRed); 
    h_Chi2Study_PIXhits_chi2_5->SetMarkerSize(0.);
    h_Chi2Study_SCThits_chi2_5->SetLineColor(kRed); 
    h_Chi2Study_SCThits_chi2_5->SetMarkerSize(0.);
    h_Chi2Study_PIXhits_chi2_4->SetLineColor(kGreen+2); 
    h_Chi2Study_PIXhits_chi2_4->SetMarkerSize(0.);
    h_Chi2Study_SCThits_chi2_4->SetLineColor(kGreen+2); 
    h_Chi2Study_SCThits_chi2_4->SetMarkerSize(0.);


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
    TLegend* legAll(NULL);
if(Association.EqualTo("otherPV") && Detector.EqualTo("PIX")) {
    if (h_PIXhits_otherPV_loose) h_PIXhits_otherPV_loose->GetXaxis()->SetRangeUser(0, 15);
    if (h_PIXhits_otherPV_loose) h_PIXhits_otherPV_loose->Draw("e0 hist");
    if (h_PIXhits_otherPV_nominal) h_PIXhits_otherPV_nominal->Draw("e0 hist same");
    if (h_PIXhits_otherPV_tight) h_PIXhits_otherPV_tight->Draw("e0 hist same");
    h_PIXhits_otherPV_loose->GetXaxis()->SetTitle("PIX Hits");
    h_PIXhits_otherPV_loose->GetYaxis()->SetTitle("Candidates * Num. of Trks per cand.");
    legAll = new TLegend(0.62, 0.7, 0.8, 0.9);
}
if(Association.EqualTo("nonAss") && Detector.EqualTo("PIX")) {
    if (h_PIXhits_nonAss_loose) h_PIXhits_nonAss_loose->GetXaxis()->SetRangeUser(0, 15);
    if (h_PIXhits_nonAss_loose) h_PIXhits_nonAss_loose->Draw("e0 hist");
    if (h_PIXhits_nonAss_nominal) h_PIXhits_nonAss_nominal->Draw("e0 hist same");
    if (h_PIXhits_nonAss_tight) h_PIXhits_nonAss_tight->Draw("e0 hist same");
    h_PIXhits_nonAss_loose->GetXaxis()->SetTitle("PIX Hits");
    h_PIXhits_nonAss_loose->GetYaxis()->SetTitle("Candidates * Num. of Trks per cand.");
    legAll = new TLegend(0.62, 0.7, 0.8, 0.9);
}   
if(Association.EqualTo("assPV") && Detector.EqualTo("PIX")) {
    if (h_PIXhits_assPV_loose) h_PIXhits_assPV_loose->GetXaxis()->SetRangeUser(0, 15);
    if (h_PIXhits_assPV_loose) h_PIXhits_assPV_loose->Draw("e0 hist");
    if (h_PIXhits_assPV_nominal) h_PIXhits_assPV_nominal->Draw("e0 hist same");
    if (h_PIXhits_assPV_tight) h_PIXhits_assPV_tight->Draw("e0 hist same");
    h_PIXhits_assPV_loose->GetXaxis()->SetTitle("PIX Hits");
    h_PIXhits_assPV_loose->GetYaxis()->SetTitle("Candidates * Num. of Trks per cand.");
    legAll = new TLegend(0.62, 0.7, 0.8, 0.9);
}

if(Association.EqualTo("otherPV") && Detector.EqualTo("SCT")) {
    if (h_SCThits_otherPV_loose) h_SCThits_otherPV_loose->GetXaxis()->SetRangeUser(0, 15);
    if (h_SCThits_otherPV_loose) h_SCThits_otherPV_loose->Draw("e0 hist");
    if (h_SCThits_otherPV_nominal) h_SCThits_otherPV_nominal->Draw("e0 hist same");
    if (h_SCThits_otherPV_tight) h_SCThits_otherPV_tight->Draw("e0 hist same");
    h_SCThits_otherPV_loose->GetXaxis()->SetTitle("SCT Hits");
    h_SCThits_otherPV_loose->GetYaxis()->SetTitle("Candidates * Num. of Trks per cand.");
    legAll = new TLegend(0.3, 0.2, 0.4, 0.35);
}
if(Association.EqualTo("nonAss") && Detector.EqualTo("SCT")) {
    if (h_SCThits_nonAss_loose) h_SCThits_nonAss_loose->GetXaxis()->SetRangeUser(0, 15);
    if (h_SCThits_nonAss_loose) h_SCThits_nonAss_loose->Draw("e0 hist");
    if (h_SCThits_nonAss_nominal) h_SCThits_nonAss_nominal->Draw("e0 hist same");
    if (h_SCThits_nonAss_tight) h_SCThits_nonAss_tight->Draw("e0 hist same");
    h_SCThits_nonAss_loose->GetXaxis()->SetTitle("SCT Hits");
    h_SCThits_nonAss_loose->GetYaxis()->SetTitle("Candidates * Num. of Trks per cand.");
    legAll = new TLegend(0.3, 0.2, 0.4, 0.35);
}   
if(Association.EqualTo("assPV") && Detector.EqualTo("SCT")) {
    if (h_SCThits_assPV_loose) h_SCThits_assPV_loose->GetXaxis()->SetRangeUser(0, 15);
    if (h_SCThits_assPV_loose) h_SCThits_assPV_loose->Draw("e0 hist");
    if (h_SCThits_assPV_nominal) h_SCThits_assPV_nominal->Draw("e0 hist same");
    if (h_SCThits_assPV_tight) h_SCThits_assPV_tight->Draw("e0 hist same");
    h_SCThits_assPV_loose->GetXaxis()->SetTitle("SCT Hits");
    h_SCThits_assPV_loose->GetYaxis()->SetTitle("Candidates * Num. of Trks per cand.");
    legAll = new TLegend(0.3, 0.2, 0.4, 0.35);
}
if(Association.EqualTo("chi2Study") && Detector.EqualTo("PIX")) {
    if (h_Chi2Study_PIXhits_chi2_6) h_Chi2Study_PIXhits_chi2_6->GetXaxis()->SetRangeUser(0, 15);
    if (h_Chi2Study_PIXhits_chi2_6) h_Chi2Study_PIXhits_chi2_6->Draw("e0 hist");
    if (h_Chi2Study_PIXhits_chi2_5) h_Chi2Study_PIXhits_chi2_5->Draw("e0 hist same");
    if (h_Chi2Study_PIXhits_chi2_4) h_Chi2Study_PIXhits_chi2_4->Draw("e0 hist same");
    h_Chi2Study_PIXhits_chi2_6->GetXaxis()->SetTitle("PIX Hits");
    h_Chi2Study_PIXhits_chi2_6->GetYaxis()->SetTitle("Candidates * Num. of Trks per cand.");
    legAll = new TLegend(0.62, 0.7, 0.8, 0.9);
}

if(Association.EqualTo("chi2Study") && Detector.EqualTo("SCT")) {
    if (h_Chi2Study_SCThits_chi2_6) h_Chi2Study_SCThits_chi2_6->GetXaxis()->SetRangeUser(0, 15);
    if (h_Chi2Study_SCThits_chi2_6) h_Chi2Study_SCThits_chi2_6->Draw("e0 hist");
    if (h_Chi2Study_SCThits_chi2_5) h_Chi2Study_SCThits_chi2_5->Draw("e0 hist same");
    if (h_Chi2Study_SCThits_chi2_4) h_Chi2Study_SCThits_chi2_4->Draw("e0 hist same");
    h_Chi2Study_SCThits_chi2_6->GetXaxis()->SetTitle("SCT Hits");
    h_Chi2Study_SCThits_chi2_6->GetYaxis()->SetTitle("Candidates * Num. of Trks per cand.");
    legAll = new TLegend(0.3, 0.2, 0.4, 0.35);
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
    if(Association.EqualTo("chi2Study")){
        legAll->SetHeader(theYear + " All Tracks");
    legAll->AddEntry(h_Chi2Study_PIXhits_chi2_6, "#chi^{2}<6" ,"l");
    legAll->AddEntry(h_Chi2Study_PIXhits_chi2_5, "#chi^{2}<5" ,"l");
    legAll->AddEntry(h_Chi2Study_PIXhits_chi2_4, "#chi^{2}<4" ,"l");
    }else{
        legAll->AddEntry(h_SCThits_nonAss_loose, "TTVA Loose WP" ,"l");
        legAll->AddEntry(h_SCThits_nonAss_nominal, "TTVA Nominal WP" ,"l");
        legAll->AddEntry(h_SCThits_nonAss_tight, "TTVA Tight WP" ,"l");
    }
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
    allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/IDhits/"+theYear+"_"+Association+"_"+Detector+"_2019Jun10.png");
}

void RunOverSavedFiles_Ntrks(){
// void IsolationStudy(){
    SetAtlasStyle();
    // cout<<"DEbug"<<endl;
    //pull from saved histos
    // //
      TString myDir = "/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/data/";
      int numberOfBins = 60;
      //run1
    TFile* run1File = new TFile(myDir+"myNtrksRun1_2019Apr1.root");
    TCanvas *Run1Canvas = (TCanvas*)run1File->Get("Run1 Canvas");
    TH1F *h_ntrksAll_Run1 = (TH1F*)Run1Canvas->GetListOfPrimitives()->FindObject("h_NtrkAll");
    h_ntrksAll_Run1->Scale(1./(h_ntrksAll_Run1->Integral(0, numberOfBins + 1)));
    TH1F *h_ntrksBlinded_Run1 = (TH1F*)Run1Canvas->GetListOfPrimitives()->FindObject("h_NtrkBlinded");
    h_ntrksBlinded_Run1->Scale(1./(h_ntrksBlinded_Run1->Integral(0, numberOfBins + 1)));
    TH1F *h_ntrksRun2Cuts_Run1 = (TH1F*)Run1Canvas->GetListOfPrimitives()->FindObject("h_NtrkRun2Cuts");
    h_ntrksRun2Cuts_Run1->Scale(1./(h_ntrksRun2Cuts_Run1->Integral(0, numberOfBins + 1)));
    run1File->Close();
    //1516
    TFile* ifile1516 = new TFile(myDir+"myNtrks1516_2019Apr1.root");
    TCanvas *Canvas1516 = (TCanvas*)ifile1516->Get("1516 Canvas");
    TH1F *h_ntrks_1516 = (TH1F*)Canvas1516->GetListOfPrimitives()->FindObject("h_ntrks_orig");
    h_ntrks_1516->Scale(1./(h_ntrks_1516->Integral(0, numberOfBins + 1)));
    // cout<"15 16 integral: "<< (h_ntrks_1516->Integral(0, numberOfBins + 1)<< endl;
    ifile1516->Close();
    //2017 (includes ID requirements)
    TFile* ifile2017 = new TFile(myDir+"myNtrks2017_2019Apr3.root");
    TCanvas *Canvas2017 = (TCanvas*)ifile2017->Get("trks chi2");
    TH1F *h_ntrks_assPV_2017 = (TH1F*)Canvas2017->GetListOfPrimitives()->FindObject("h_ntrks_assPV");
    h_ntrks_assPV_2017->Scale(1./(h_ntrks_assPV_2017->Integral(0, numberOfBins + 1)));
    TH1F *h_ntrks_otherPV_2017 = (TH1F*)Canvas2017->GetListOfPrimitives()->FindObject("h_ntrks_otherPV");
    h_ntrks_otherPV_2017->Scale(1./(h_ntrks_otherPV_2017->Integral(0, numberOfBins + 1)));
    TH1F *h_ntrks_nonAss_2017 = (TH1F*)Canvas2017->GetListOfPrimitives()->FindObject("h_ntrks_nonAss");
    h_ntrks_nonAss_2017->Scale(1./(h_ntrks_nonAss_2017->Integral(0, numberOfBins + 1)));
    // TH1F *h_ntrksAll_2017 = (TH1F*)Canvas2017->GetListOfPrimitives()->FindObject("h_ntrksAll");
    // h_ntrksAll_2017->Scale(1./(h_ntrksAll_2017->Integral(0, numberOfBins + 1)));
    TH1F *h_ntrks_all_2017 = (TH1F*)Canvas2017->GetListOfPrimitives()->FindObject("h_ntrks_all");
    h_ntrks_all_2017->Scale(1./(h_ntrks_all_2017->Integral(0, numberOfBins + 1)));
    TH1F *h_ntrks_2017 = (TH1F*)Canvas2017->GetListOfPrimitives()->FindObject("h_ntrks_orig");
    h_ntrks_2017->Scale(1./(h_ntrks_2017->Integral(0, numberOfBins + 1)));
    ifile2017->Close();
    //2018 (includes ID requirements)
    TFile* ifile2018 = new TFile(myDir+"myNtrks2018_2019Apr3.root");
    TCanvas *Canvas2018 = (TCanvas*)ifile2018->Get("trks chi2");
    TH1F *h_ntrks_assPV_2018 = (TH1F*)Canvas2018->GetListOfPrimitives()->FindObject("h_ntrks_assPV");
    h_ntrks_assPV_2018->Scale(1./(h_ntrks_assPV_2018->Integral(0, numberOfBins + 1)));
    TH1F *h_ntrks_otherPV_2018 = (TH1F*)Canvas2018->GetListOfPrimitives()->FindObject("h_ntrks_otherPV");
    h_ntrks_otherPV_2018->Scale(1./(h_ntrks_otherPV_2018->Integral(0, numberOfBins + 1)));
    TH1F *h_ntrks_nonAss_2018 = (TH1F*)Canvas2018->GetListOfPrimitives()->FindObject("h_ntrks_nonAss");
    h_ntrks_nonAss_2018->Scale(1./(h_ntrks_nonAss_2018->Integral(0, numberOfBins + 1)));
    // TH1F *h_ntrksAll_2018 = (TH1F*)Canvas2018->GetListOfPrimitives()->FindObject("h_ntrksAll");
    // h_ntrksAll_2018->Scale(1./(h_ntrksAll_2018->Integral(0, numberOfBins + 1)));
    TH1F *h_ntrks_all_2018 = (TH1F*)Canvas2018->GetListOfPrimitives()->FindObject("h_ntrks_all");
    h_ntrks_all_2018->Scale(1./(h_ntrks_all_2018->Integral(0, numberOfBins + 1)));
    TH1F *h_ntrks_2018 = (TH1F*)Canvas2018->GetListOfPrimitives()->FindObject("h_ntrks_orig");
    h_ntrks_2018->Scale(1./(h_ntrks_2018->Integral(0, numberOfBins + 1)));
    ifile2018->Close();
    // //////2017_isTightPrimary
    // TFile* ifile2017_isTightPrimary = new TFile(myDir+"myntrks2017_isTightPrimary.root");
    // TCanvas *Canvas2017_isTightPrimary = (TCanvas*)ifile2017_isTightPrimary->Get("trks chi2");
    // TH1F *h_ntrks_assPV_2017_isTightPrimary = (TH1F*)Canvas2017_isTightPrimary->GetListOfPrimitives()->FindObject("h_ntrks_assPV");
    // h_ntrks_assPV_2017_isTightPrimary->Scale(1./(h_ntrks_assPV_2017_isTightPrimary->Integral(0, numberOfBins + 1)));
    // TH1F *h_ntrks_otherPV_2017_isTightPrimary = (TH1F*)Canvas2017_isTightPrimary->GetListOfPrimitives()->FindObject("h_ntrks_otherPV");
    // h_ntrks_otherPV_2017_isTightPrimary->Scale(1./(h_ntrks_otherPV_2017_isTightPrimary->Integral(0, numberOfBins + 1)));
    // TH1F *h_ntrks_nonAss_2017_isTightPrimary = (TH1F*)Canvas2017_isTightPrimary->GetListOfPrimitives()->FindObject("h_ntrks_nonAss");
    // h_ntrks_nonAss_2017_isTightPrimary->Scale(1./(h_ntrks_nonAss_2017_isTightPrimary->Integral(0, numberOfBins + 1)));
    // // TH1F *h_ntrksAll_2017_isTightPrimary = (TH1F*)Canvas2017_isTightPrimary->GetListOfPrimitives()->FindObject("h_ntrksAll");
    // // h_ntrksAll_2017_isTightPrimary->Scale(1./(h_ntrksAll_2017_isTightPrimary->Integral(0, numberOfBins + 1)));
    // TH1F *h_ntrks_all_2017_isTightPrimary = (TH1F*)Canvas2017_isTightPrimary->GetListOfPrimitives()->FindObject("h_ntrks_all");
    // h_ntrks_all_2017_isTightPrimary->Scale(1./(h_ntrks_all_2017_isTightPrimary->Integral(0, numberOfBins + 1)));
    // TH1F *h_ntrks_2017_isTightPrimary = (TH1F*)Canvas2017_isTightPrimary->GetListOfPrimitives()->FindObject("h_ntrks");
    // h_ntrks_2017_isTightPrimary->Scale(1./(h_ntrks_2017_isTightPrimary->Integral(0, numberOfBins + 1)));
    // ifile2017_isTightPrimary->Close();
    // //2018_isTightPrimary
    // TFile* ifile2018_isTightPrimary = new TFile(myDir+"myntrks2018_isTightPrimary.root");
    // TCanvas *Canvas2018_isTightPrimary = (TCanvas*)ifile2018_isTightPrimary->Get("trks chi2");
    // TH1F *h_ntrks_assPV_2018_isTightPrimary = (TH1F*)Canvas2018_isTightPrimary->GetListOfPrimitives()->FindObject("h_ntrks_assPV");
    // h_ntrks_assPV_2018_isTightPrimary->Scale(1./(h_ntrks_assPV_2018_isTightPrimary->Integral(0, numberOfBins + 1)));
    // TH1F *h_ntrks_otherPV_2018_isTightPrimary = (TH1F*)Canvas2018_isTightPrimary->GetListOfPrimitives()->FindObject("h_ntrks_otherPV");
    // h_ntrks_otherPV_2018_isTightPrimary->Scale(1./(h_ntrks_otherPV_2018_isTightPrimary->Integral(0, numberOfBins + 1)));
    // TH1F *h_ntrks_nonAss_2018_isTightPrimary = (TH1F*)Canvas2018_isTightPrimary->GetListOfPrimitives()->FindObject("h_ntrks_nonAss");
    // h_ntrks_nonAss_2018_isTightPrimary->Scale(1./(h_ntrks_nonAss_2018_isTightPrimary->Integral(0, numberOfBins + 1)));
    // // TH1F *h_ntrksAll_2018_isTightPrimary = (TH1F*)Canvas2018_isTightPrimary->GetListOfPrimitives()->FindObject("h_ntrksAll");
    // // h_ntrksAll_2018_isTightPrimary->Scale(1./(h_ntrksAll_2018_isTightPrimary->Integral(0, numberOfBins + 1)));
    // TH1F *h_ntrks_all_2018_isTightPrimary = (TH1F*)Canvas2018_isTightPrimary->GetListOfPrimitives()->FindObject("h_ntrks_all");
    // h_ntrks_all_2018_isTightPrimary->Scale(1./(h_ntrks_all_2018_isTightPrimary->Integral(0, numberOfBins + 1)));
    // TH1F *h_ntrks_2018_isTightPrimary = (TH1F*)Canvas2018_isTightPrimary->GetListOfPrimitives()->FindObject("h_ntrks");
    // h_ntrks_2018_isTightPrimary->Scale(1./(h_ntrks_2018_isTightPrimary->Integral(0, numberOfBins + 1)));
    // ifile2018_isTightPrimary->Close();
    ////
    // //////2017 pixel sct hit requirements
    TFile* ifile2017_IdHits = new TFile(myDir+"myNtrks2017_2019Apr3.root");
    TCanvas *Canvas2017_IdHits = (TCanvas*)ifile2017_IdHits->Get("trks chi2");
    TH1F *h_ntrks_assPV_2017_IdHits = (TH1F*)Canvas2017_IdHits->GetListOfPrimitives()->FindObject("h_ntrks_assPV");
    h_ntrks_assPV_2017_IdHits->Scale(1./(h_ntrks_assPV_2017_IdHits->Integral(0, numberOfBins + 1)));
    TH1F *h_ntrks_otherPV_2017_IdHits = (TH1F*)Canvas2017_IdHits->GetListOfPrimitives()->FindObject("h_ntrks_otherPV");
    h_ntrks_otherPV_2017_IdHits->Scale(1./(h_ntrks_otherPV_2017_IdHits->Integral(0, numberOfBins + 1)));
    TH1F *h_ntrks_nonAss_2017_IdHits = (TH1F*)Canvas2017_IdHits->GetListOfPrimitives()->FindObject("h_ntrks_nonAss");
    h_ntrks_nonAss_2017_IdHits->Scale(1./(h_ntrks_nonAss_2017_IdHits->Integral(0, numberOfBins + 1)));
    // TH1F *h_ntrksAll_2017_IdHits = (TH1F*)Canvas2017_IdHits->GetListOfPrimitives()->FindObject("h_ntrksAll");
    // h_ntrksAll_2017_IdHits->Scale(1./(h_ntrksAll_2017_IdHits->Integral(0, numberOfBins + 1)));
    TH1F *h_ntrks_all_2017_IdHits = (TH1F*)Canvas2017_IdHits->GetListOfPrimitives()->FindObject("h_ntrks_all");
    h_ntrks_all_2017_IdHits->Scale(1./(h_ntrks_all_2017_IdHits->Integral(0, numberOfBins + 1)));
    TH1F *h_ntrks_2017_IdHits = (TH1F*)Canvas2017_IdHits->GetListOfPrimitives()->FindObject("h_ntrks_orig");
    h_ntrks_2017_IdHits->Scale(1./(h_ntrks_2017_IdHits->Integral(0, numberOfBins + 1)));
    ifile2017_IdHits->Close();
    // //2018  pixel sct hit requirements
    TFile* ifile2018_IdHits = new TFile(myDir+"myNtrks2018_2019Apr3.root");
    TCanvas *Canvas2018_IdHits = (TCanvas*)ifile2018_IdHits->Get("trks chi2");
    TH1F *h_ntrks_assPV_2018_IdHits = (TH1F*)Canvas2018_IdHits->GetListOfPrimitives()->FindObject("h_ntrks_assPV");
    h_ntrks_assPV_2018_IdHits->Scale(1./(h_ntrks_assPV_2018_IdHits->Integral(0, numberOfBins + 1)));
    TH1F *h_ntrks_otherPV_2018_IdHits = (TH1F*)Canvas2018_IdHits->GetListOfPrimitives()->FindObject("h_ntrks_otherPV");
    h_ntrks_otherPV_2018_IdHits->Scale(1./(h_ntrks_otherPV_2018_IdHits->Integral(0, numberOfBins + 1)));
    TH1F *h_ntrks_nonAss_2018_IdHits = (TH1F*)Canvas2018_IdHits->GetListOfPrimitives()->FindObject("h_ntrks_nonAss");
    h_ntrks_nonAss_2018_IdHits->Scale(1./(h_ntrks_nonAss_2018_IdHits->Integral(0, numberOfBins + 1)));
    // TH1F *h_ntrksAll_2018_IdHits = (TH1F*)Canvas2018_IdHits->GetListOfPrimitives()->FindObject("h_ntrksAll");
    // h_ntrksAll_2018_IdHits->Scale(1./(h_ntrksAll_2018_IdHits->Integral(0, numberOfBins + 1)));
    TH1F *h_ntrks_all_2018_IdHits = (TH1F*)Canvas2018_IdHits->GetListOfPrimitives()->FindObject("h_ntrks_all");
    h_ntrks_all_2018_IdHits->Scale(1./(h_ntrks_all_2018_IdHits->Integral(0, numberOfBins + 1)));
    TH1F *h_ntrks_2018_IdHits = (TH1F*)Canvas2018_IdHits->GetListOfPrimitives()->FindObject("h_ntrks_orig");
    h_ntrks_2018_IdHits->Scale(1./(h_ntrks_2018_IdHits->Integral(0, numberOfBins + 1)));
    ifile2018_IdHits->Close();
    // ////
    //
    // h_ntrksRun2Cuts_Run1->Scale(h_ntrks_2017->Integral(0, numberOfBins + 1)/(h_ntrksRun2Cuts_Run1->Integral(0, numberOfBins + 1)));
    // h_ntrks_1516->Scale(h_ntrks_2017->Integral(0, numberOfBins + 1)/(h_ntrks_1516->Integral(0, numberOfBins + 1)));
    ///
    TCanvas* allC = new TCanvas("allC","allC",900,600);
    // if (h_ntrksAll_Run1) h_ntrksAll_Run1->Draw();
    // if (h_ntrksBlinded_Run1) h_ntrksBlinded_Run1->Draw("same");
    h_ntrksRun2Cuts_Run1->SetLineColor(kRed);
    h_ntrksRun2Cuts_Run1->SetMarkerSize(0.);

    h_ntrks_1516->SetLineColor(kBlack);
    h_ntrks_1516->SetMarkerSize(0.);
    h_ntrks_2017->SetLineColor(kBlue);

    h_ntrks_2017->SetMarkerSize(0.);
    h_ntrks_2017_IdHits->SetLineColor(kBlue);
    h_ntrks_2017_IdHits->SetMarkerSize(0.);;
    // h_ntrks_nonAss_2017_isTightPrimary->SetLineColor(kBlue);
    h_ntrks_nonAss_2017_IdHits->SetLineColor(kBlue);
    h_ntrks_nonAss_2017_IdHits->SetMarkerSize(0.);
    h_ntrks_all_2017_IdHits->SetLineColor(kBlue);
    h_ntrks_all_2017_IdHits->SetMarkerSize(0.);

    h_ntrks_2018->SetLineColor(kGreen+1);
    h_ntrks_2018->SetMarkerSize(0.);
    h_ntrks_2018_IdHits->SetLineColor(kGreen+1);
    h_ntrks_2018_IdHits->SetMarkerSize(0.);
    h_ntrks_all_2018_IdHits->SetLineColor(kGreen+1);
    h_ntrks_all_2018_IdHits->SetMarkerSize(0.);
    // h_ntrks_nonAss_2018_isTightPrimary->SetLineColor(kGreen+1);
    h_ntrks_nonAss_2018_IdHits->SetLineColor(kGreen+1);
    h_ntrks_nonAss_2018_IdHits->SetMarkerSize(0.);


    h_ntrks_1516->Draw("e0 hist");
    h_ntrksRun2Cuts_Run1->Draw("e0 hist same");
    // if (h_ntrks_nonAss_2017) h_ntrks_nonAss_2017->Draw("e0 hist ");
    // if (h_ntrks_2017_IdHits) h_ntrks_2017_IdHits->Draw("e0 hist");
    // if (h_ntrks_2018_IdHits) h_ntrks_2018_IdHits->Draw("e0 hist");
    // if (h_ntrks_2017) h_ntrks_2017->Draw("e0 hist same");
    // if (h_ntrks_nonAss_2017) h_ntrks_nonAss_2017_isTightPrimary->Draw("hist same");
    // if (h_ntrks_nonAss_2017_IdHits) h_ntrks_nonAss_2017_IdHits->Draw("e0 hist same");
    if (h_ntrks_all_2017_IdHits) h_ntrks_all_2017_IdHits->Draw("e0 hist same");
    // if (h_ntrks_2018) h_ntrks_2018->Draw("e0 hist same");
    // if (h_ntrks_nonAss_2018) h_ntrks_nonAss_2018_isTightPrimary->Draw("hist same");
    // if (h_ntrks_nonAss_2018_IdHits) h_ntrks_nonAss_2018_IdHits->Draw("e0 hist same");
    if (h_ntrks_all_2018_IdHits) h_ntrks_all_2018_IdHits->Draw(" e0 hist same");
    //for logy scale
    // gPad->SetLogy();
    // h_ntrks_1516->SetMaximum(1.);
    // else:
    // h_ntrksRun2Cuts_Run1->GetYaxis()->SetRangeUser(0,0.08);

    h_ntrks_1516->GetXaxis()->SetTitle("N^{clos}_{xtrk}");
    h_ntrks_1516->GetYaxis()->SetTitle("a.u.");

    TLegend* legAll = new TLegend(0.4, 0.75, 0.5, 0.9);
    legAll->SetTextSize(0.034468);
    // legAll->AddEntry(h_ntrksAll_Run1, "h_ntrksAll_Run1" ,"l");
    // legAll->AddEntry(h_ntrksBlinded_Run1, "h_ntrksBlinded_Run1" ,"l");
    legAll->AddEntry(h_ntrksRun2Cuts_Run1, "Run1 w/Run 2 cuts" ,"l");
    legAll->AddEntry(h_ntrks_1516, "2015 and 2016 data" ,"l");
    // legAll->AddEntry(h_ntrks_nonAss_2017, "2017 run (with Non-Assoc. Tracks)" ,"l");
    // legAll->AddEntry(h_ntrks_nonAss_2018, "2018 run (with Non-Assoc. Tracks)" ,"l");
    // legAll->AddEntry(h_ntrks_nonAss_2017_IdHits, "2017 run (with Non-Assoc. Tracks and spec ID hits)" ,"l");
    // legAll->AddEntry(h_ntrks_nonAss_2018_IdHits, "2018 run (with Non-Assoc. Tracks and spec ID hits)" ,"l");
    legAll->AddEntry(h_ntrks_nonAss_2017_IdHits, "2017 run (with all Trks)" ,"l");
    legAll->AddEntry(h_ntrks_nonAss_2018_IdHits, "2018 run (with all Trks)" ,"l");
    // legAll->AddEntry(h_ntrks_nonAss_2017_IdHits, "2017 run (default calculation)" ,"l");
    // legAll->AddEntry(h_ntrks_nonAss_2018_IdHits, "2018 run (default calculation)" ,"l");
    legAll->SetBorderSize(0);  // no border
    legAll->SetLineColor(0);
    legAll->SetFillColorAlpha(0, 0.4);
    legAll->Draw();


    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/Ntrks/NtrksComp.png");
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/Ntrks/NtrksComp_orig_linear.png");
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/Ntrks/NtrksComparison_wNonAssoc.png");
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/Ntrks/NtrksComp_wNonAssoc_linear.png");
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/Ntrks/NtrksComparison_wNonAssoc_isTightPrimary.png");
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/Ntrks/NtrksComparison_wNonAssoc_isTightPrimary_linear.png");
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/Ntrks/NtrksComp_wNonAssoc_IdHits.png");
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/Ntrks/NtrksComp_orig_IdHits_linear.png");
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/Ntrks/NtrksComp_wNonAssoc_IdHits_linear.png");
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/Ntrks/NtrksComp_allTrks.png");
    allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/Ntrks/NtrksComp_allTrks_linear.png");
    // cout<<h_isoRun2Cuts_Run1->GetEntries()<<endl;
}

void RunOverSavedFiles_IsoTrks(){
    SetAtlasStyle();
    TString myDir = "/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/data/";
    int numberOfBins = 25;
    TFile* ifile2017 = new TFile(myDir+"isoNtrks2017_2019Apr3.root");
        TCanvas *Canvas2017 = (TCanvas*)ifile2017->Get("trks chi2");
            TH1F *h_isoTrks_all_chi_5_2017 = (TH1F*)Canvas2017->GetListOfPrimitives()->FindObject("h_isoTrks_all_chi_5");
            h_isoTrks_all_chi_5_2017->Scale(1./(h_isoTrks_all_chi_5_2017->Integral(0, numberOfBins + 1)));
            TH1F *h_isoTrks_all_ID_chi_5_2017 = (TH1F*)Canvas2017->GetListOfPrimitives()->FindObject("h_isoTrks_all_ID_chi_5");
            h_isoTrks_all_ID_chi_5_2017->Scale(1./(h_isoTrks_all_ID_chi_5_2017->Integral(0, numberOfBins + 1)));
            TH1F *h_isoTrks_all_ID_chi_4_2017 = (TH1F*)Canvas2017->GetListOfPrimitives()->FindObject("h_isoTrks_all_ID_chi_4");
            h_isoTrks_all_ID_chi_4_2017->Scale(1./(h_isoTrks_all_ID_chi_4_2017->Integral(0, numberOfBins + 1)));
            TH1F *h_isoTrks_orig_2017 = (TH1F*)Canvas2017->GetListOfPrimitives()->FindObject("h_isoTrks_orig");
            h_isoTrks_orig_2017->Scale(1./(h_isoTrks_orig_2017->Integral(0, numberOfBins + 1)));
    TFile* ifile2018 = new TFile(myDir+"isoNtrks2018_2019Apr3.root");
        TCanvas *Canvas2018 = (TCanvas*)ifile2018->Get("trks chi2");
            TH1F *h_isoTrks_all_chi_5_2018 = (TH1F*)Canvas2018->GetListOfPrimitives()->FindObject("h_isoTrks_all_chi_5");
            h_isoTrks_all_chi_5_2018->Scale(1./(h_isoTrks_all_chi_5_2018->Integral(0, numberOfBins + 1)));
            TH1F *h_isoTrks_all_ID_chi_5_2018 = (TH1F*)Canvas2018->GetListOfPrimitives()->FindObject("h_isoTrks_all_ID_chi_5");
            h_isoTrks_all_ID_chi_5_2018->Scale(1./(h_isoTrks_all_ID_chi_5_2018->Integral(0, numberOfBins + 1)));
            TH1F *h_isoTrks_all_ID_chi_4_2018 = (TH1F*)Canvas2018->GetListOfPrimitives()->FindObject("h_isoTrks_all_ID_chi_4");
            h_isoTrks_all_ID_chi_4_2018->Scale(1./(h_isoTrks_all_ID_chi_4_2018->Integral(0, numberOfBins + 1)));
            TH1F *h_isoTrks_orig_2018 = (TH1F*)Canvas2018->GetListOfPrimitives()->FindObject("h_isoTrks_orig");
            h_isoTrks_orig_2018->Scale(1./(h_isoTrks_orig_2018->Integral(0, numberOfBins + 1)));
 //run1
    TFile* run1File = new TFile(myDir+"isoNtrksRun1_2019Apr4.root");
        TCanvas *Run1Canvas = (TCanvas*)run1File->Get("Run1 Canvas");//was saved as 1516 but is really run1
            TH1F *h_iso_ntrk_Run1 = (TH1F*)Run1Canvas->GetListOfPrimitives()->FindObject("h_iso_ntrk");
            h_iso_ntrk_Run1->Scale(1./(h_iso_ntrk_Run1->Integral(0, numberOfBins + 1)));
            // TH1F *h_isoBlinded_Run1 = (TH1F*)Run1Canvas->GetListOfPrimitives()->FindObject("h_isoBlinded");
            // h_isoBlinded_Run1->Scale(1./(h_isoBlinded_Run1->Integral(0, numberOfBins + 1)));
            // TH1F *h_isoRun2Cuts_Run1 = (TH1F*)Run1Canvas->GetListOfPrimitives()->FindObject("h_isoRun2Cuts");
            // h_isoRun2Cuts_Run1->Scale(1./(h_isoRun2Cuts_Run1->Integral(0, numberOfBins + 1)));
            run1File->Close();
    //1516
    TFile* ifile1516 = new TFile(myDir+"isoNtrks1516_2019Apr4.root");
        TCanvas *Canvas1516 = (TCanvas*)ifile1516->Get("1516 Canvas");
            TH1F *h_iso_ntrk_med_1516 = (TH1F*)Canvas1516->GetListOfPrimitives()->FindObject("h_iso_ntrk_med");
            h_iso_ntrk_med_1516->Scale(1./(h_iso_ntrk_med_1516->Integral(0, numberOfBins + 1)));
            TH1F *h_iso_ntrk_loose_1516 = (TH1F*)Canvas1516->GetListOfPrimitives()->FindObject("h_iso_ntrk_loose");
            h_iso_ntrk_loose_1516->Scale(1./(h_iso_ntrk_loose_1516->Integral(0, numberOfBins + 1)));
            ifile1516->Close();

    TCanvas* allC = new TCanvas("allC","allC",900,600);
h_isoTrks_all_chi_5_2017->SetLineColor(kBlue);
h_isoTrks_all_chi_5_2017->SetMarkerSize(0.);
h_isoTrks_all_ID_chi_5_2017->SetLineColor(kBlue);
h_isoTrks_all_ID_chi_5_2017->SetMarkerSize(0.);
h_isoTrks_all_ID_chi_4_2017->SetLineColor(kBlue);
h_isoTrks_all_ID_chi_4_2017->SetMarkerSize(0.);
h_isoTrks_orig_2017->SetLineColor(kBlue);
h_isoTrks_orig_2017->SetMarkerSize(0.);

h_isoTrks_all_chi_5_2018->SetLineColor(kGreen+1);
h_isoTrks_all_chi_5_2018->SetMarkerSize(0.);
h_isoTrks_all_ID_chi_5_2018->SetLineColor(kGreen+1);
h_isoTrks_all_ID_chi_5_2018->SetMarkerSize(0.);
h_isoTrks_all_ID_chi_4_2018->SetLineColor(kGreen+1);
h_isoTrks_all_ID_chi_4_2018->SetMarkerSize(0.);
h_isoTrks_orig_2018->SetLineColor(kGreen+1);
h_isoTrks_orig_2018->SetMarkerSize(0.);

h_iso_ntrk_Run1->SetLineColor(kRed);
h_iso_ntrk_Run1->SetMarkerSize(0.);

h_iso_ntrk_med_1516->SetLineColor(kBlack);
h_iso_ntrk_med_1516->SetMarkerSize(0.);
h_iso_ntrk_loose_1516->SetLineColor(kBlack);
h_iso_ntrk_loose_1516->SetMarkerSize(0.);

h_iso_ntrk_med_1516->Draw("e0 hist");
h_iso_ntrk_Run1->Draw("e0 hist same");
// h_isoTrks_orig_2017->Draw("e0 hist same");
// h_isoTrks_orig_2018->Draw("e0 hist same");
// h_isoTrks_all_chi_5_2017->Draw("e0 hist same");
// h_isoTrks_all_chi_5_2018->Draw("e0 hist same");
h_isoTrks_all_ID_chi_5_2017->Draw("e0 hist same");
h_isoTrks_all_ID_chi_5_2018->Draw("e0 hist same");
// h_isoTrks_all_ID_chi_4_2017->Draw("e0 hist same");
// h_isoTrks_all_ID_chi_4_2018->Draw("e0 hist same");

h_iso_ntrk_med_1516->GetXaxis()->SetTitle("N_{trks} B Isolation");
h_iso_ntrk_med_1516->GetYaxis()->SetTitle("a.u.");

TLegend* legAll = new TLegend(0.6, 0.75, 0.7, 0.9);
legAll->SetTextSize(0.034468);

legAll->AddEntry(h_iso_ntrk_Run1, "Run 1 (w/Run 2 cuts)" ,"l");
legAll->AddEntry(h_iso_ntrk_med_1516, "2015 and 2016" ,"l");
// legAll->AddEntry(h_isoTrks_orig_2017, "2017 default" ,"l");
// legAll->AddEntry(h_isoTrks_orig_2018, "2018 default" ,"l");
// legAll->AddEntry(h_isoTrks_orig_2017, "2017 (all trks, #chi^{2}<5)" ,"l");
// legAll->AddEntry(h_isoTrks_orig_2018, "2018 (all trks, #chi^{2}<5)" ,"l");
legAll->AddEntry(h_isoTrks_all_ID_chi_5_2017, "2017 (all trks, IDhits, #chi^{2}<5)" ,"l");
legAll->AddEntry(h_isoTrks_all_ID_chi_5_2018, "2018 (all trks, IDhits, #chi^{2}<5)" ,"l");
// legAll->AddEntry(h_isoTrks_all_ID_chi_4_2017, "2017 (all trks, IDhits, #chi^{2}<4)" ,"l");
// legAll->AddEntry(h_isoTrks_all_ID_chi_4_2018, "2018 (all trks, IDhits, #chi^{2}<4)" ,"l");
legAll->SetBorderSize(0);  // no border
legAll->SetLineColor(0);
legAll->SetFillColorAlpha(0, 0.4);
legAll->Draw();
// allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/IsoNtrks/IsoNtrks_orig_linear.png");
// allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/IsoNtrks/IsoNtrks_all_chi2_5.png");
allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/IsoNtrks/IsoNtrks_all_ID_chi2_5.png");
// allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/IsoNtrks/IsoNtrks_all_ID_chi2_4.png");


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

