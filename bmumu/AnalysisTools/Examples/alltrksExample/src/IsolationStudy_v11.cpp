//
// example how to read all track ntuples
//
// iskander(dot)ibragimov(at)cern(dot)ch
// 
// setupATLAS 
// lsetup "root 6.10.06-x86_64-slc6-gcc62-opt"
//  
//v3 returns branches instead of histograms - comparison then can be made with dmcbmumuX.C code
//in previous versions comparisons are made from the saved files with histograms.

//v5 selects TTVA working points and chi2 cuts -- used
//v6 reorgaizes v5 code-- not used 
//v7 removes pixel detector hit constraints -- used

// v7 used to create new files on Jun3 and Jun5 2019
// v8 used for jun 6 2019
//v9 used jun12 - add chi2<6 cut to TTVA selections in B iso (for fun)
//   shift chi2 to SV in nclosetracks to 2

//v10 remove chi2<6
// add isTightPrimary ID hit selection in place of specific ID hits
//   shift chi2 to SV in nclosetracks from 2 to 4

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
void IsolationStudy_fileloop(TString myYear){
  SetAtlasStyle();
  // TString fsname("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/skimmed_ntup/data18/Bmumu/user.ibragimo.17073931.Bmumu._000001_skimmed.root");
  // TString fsname("/afs/cern.ch/work/a/agrummer/BsmumuData/LastSkimOne2018Run/LASTskim_2017Bmumu.root");
  // TString fsname("/afs/cern.ch/work/a/agrummer/BsmumuData/LastSkimOne2018Run/LASTskim_2018_1.root");
  // TString indir("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/skimmed_ntup/data18/Bmumu/");
  TString indir("");
  TString AllPath("");
  if (myYear.EqualTo("2017")){
        // indir = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkim2017_2019Mar7/";
        // indir = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkim_2019Mar27/2017/";
        indir = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/2017/";
        AllPath = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/2017All/";
  }else if (myYear.EqualTo("2018")){
        // indir = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkim2018_2019Mar7/";
        // indir = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkim_2019Mar27/2018/";
        indir = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/2018/";
        AllPath = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/2018All/";
  }else if (myYear.EqualTo("2016")){
        indir = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/2016/";
        AllPath = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/2016All/";
  }else if (myYear.EqualTo("MC16a")){
        // indir = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkim_2019Mar27/MC16a/";
        indir = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/MC16a/";
        AllPath = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/MC16aAll/";
  }else if (myYear.EqualTo("MC16d")){
        // indir = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkim_2019Mar27/MC16d/";
        indir = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/MC16d/";
        AllPath = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/MC16dAll/";
  }else if (myYear.EqualTo("MC16e")){
        // indir = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkim_2019Mar27/MC16e/";
        indir = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/MC16e/";
        AllPath = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/MC16eAll/";
  }
  TString finpath(indir);
  DIR *dpdf;
  struct dirent *entry;
  // const bool doIsoStudy = true; 
  // const bool doCntTrksStudy = false; 
  // const bool doChi2Study = false; 
  // const bool doNtrkStudy = false; 
  // const bool doDOCAStudy = false; 

  dpdf = opendir(finpath.Data());

Long64_t cntUpdate(0.);

Int_t totalTracks(0);
  if (dpdf != NULL){
    while (entry = readdir(dpdf)){

      printf("Filename: %s\n", entry->d_name);

      if ( !hasEnding(entry->d_name, ".root") )  continue;  // exclude non-ROOT files 
     
      std::cout << "processing file: "<< entry->d_name << std::endl;
    
      TString fintemp(finpath);
      fintemp.Append(entry->d_name);
      TFile *fin = new TFile(fintemp);
      TTree *ts = (TTree*)fin->Get("T_mv");
      TTree *tev = (TTree*)fin->Get("EventInfo");

      std::cout << "# of candidates: "<<  ts->GetEntries() << std::endl;

        // TFile *fFrame = new TFile(fintemp, "Frame");
        // TTree *tFrame = (TTree*)fFrame->Get("T_mv");

        TString newfname(fintemp);
        newfname.Remove(newfname.Index(".root"),newfname.Length());
        // newfname.Append("_2019Apr29.root");
        // newfname.Append("_2019May30.root");
        // newfname.Append("_2019Jun3.root");
        // newfname.Append("_2019Jun6.root");
        // newfname.Append("_2019Jun12.root"); // chi2<6 and TTVAs (not good for chi2<2 in NcloseTrks) 
        // newfname.Append("_2019Jun17.root");// isTightPrimary for Hit selection chi2(sv)<2 in NcloseTrks
        newfname.Append("_2019Jun17_2.root");// isTightPrimary and chi2<6 for Hit selection chi2(sv)<4 in NcloseTrks
        newfname.ReplaceAll(indir, AllPath);
        // TString fout(AllPath)
        if (newfname.Contains(indir)){
            cout<<"error: new file name contains indir!"<<endl;
            break;
        }
        TFile *fUpdate = new TFile(newfname,"recreate");
        TTree *tUpdate = ts->CloneTree(0);

        // TTree *tNew = tUpdate->CloneTree(0);
        //initialize variables:
        float B_iso_7_Chi2_5_LoosePt05_AllTrks_Chi6(0.);
        int B_iso_Ntracks_7_Chi2_5_LoosePt05_AllTrks_Chi6(0.);
        float B_iso_7_Chi2_5_LoosePt05_AllTrks_Chi5(0.);
        int B_iso_Ntracks_7_Chi2_5_LoosePt05_AllTrks_Chi5(0.);
        float B_iso_7_Chi2_5_LoosePt05_AllTrks_Chi4(0.);
        int B_iso_Ntracks_7_Chi2_5_LoosePt05_AllTrks_Chi4(0.);

        float B_iso_7_Chi2_5_LoosePt05_TTVA_loose(0.);
        int B_iso_Ntracks_7_Chi2_5_LoosePt05_TTVA_loose(0.);
        int closeTrkNtrksChi2_TTVA_loose(0);
        float closeTrkDOCA_TTVA_loose(0.);
        float B_iso_7_Chi2_5_LoosePt05_TTVA_nominal(0.);
        int B_iso_Ntracks_7_Chi2_5_LoosePt05_TTVA_nominal(0.);
        int closeTrkNtrksChi2_TTVA_nominal(0);
        float closeTrkDOCA_TTVA_nominal(0.);
        float B_iso_7_Chi2_5_LoosePt05_TTVA_tight(0.);
        int B_iso_Ntracks_7_Chi2_5_LoosePt05_TTVA_tight(0.);
        int closeTrkNtrksChi2_TTVA_tight(0);
        float closeTrkDOCA_TTVA_tight(0.);



        float closeTrkDOCA(0.);
//initialize branches:
        TBranch *iso_AllTrks_Chi6 = tUpdate->Branch("B_iso_7_Chi2_5_LoosePt05_AllTrks_Chi6",&B_iso_7_Chi2_5_LoosePt05_AllTrks_Chi6,"B_iso_7_Chi2_5_LoosePt05_AllTrks_Chi6/F");
        TBranch *isoNTrks_AllTrks_Chi6 = tUpdate->Branch("B_iso_Ntracks_7_Chi2_5_LoosePt05_AllTrks_Chi6",&B_iso_Ntracks_7_Chi2_5_LoosePt05_AllTrks_Chi6,"B_iso_Ntracks_7_Chi2_5_LoosePt05_AllTrks_Chi6/I");
        TBranch *iso_AllTrks_Chi5 = tUpdate->Branch("B_iso_7_Chi2_5_LoosePt05_AllTrks_Chi5",&B_iso_7_Chi2_5_LoosePt05_AllTrks_Chi5,"B_iso_7_Chi2_5_LoosePt05_AllTrks_Chi5/F");
        TBranch *isoNTrks_AllTrks_Chi5 = tUpdate->Branch("B_iso_Ntracks_7_Chi2_5_LoosePt05_AllTrks_Chi5",&B_iso_Ntracks_7_Chi2_5_LoosePt05_AllTrks_Chi5,"B_iso_Ntracks_7_Chi2_5_LoosePt05_AllTrks_Chi5/I");
        TBranch *iso_AllTrks_Chi4 = tUpdate->Branch("B_iso_7_Chi2_5_LoosePt05_AllTrks_Chi4",&B_iso_7_Chi2_5_LoosePt05_AllTrks_Chi4,"B_iso_7_Chi2_5_LoosePt05_AllTrks_Chi4/F");
        TBranch *isoNTrks_AllTrks_Chi4 = tUpdate->Branch("B_iso_Ntracks_7_Chi2_5_LoosePt05_AllTrks_Chi4",&B_iso_Ntracks_7_Chi2_5_LoosePt05_AllTrks_Chi4,"B_iso_Ntracks_7_Chi2_5_LoosePt05_AllTrks_Chi4/I");

        TBranch *iso_TTVA_loose = tUpdate->Branch("B_iso_7_Chi2_5_LoosePt05_TTVA_loose",&B_iso_7_Chi2_5_LoosePt05_TTVA_loose,"B_iso_7_Chi2_5_LoosePt05_TTVA_loose/F");
        TBranch *isoNTrks_TTVA_loose = tUpdate->Branch("B_iso_Ntracks_7_Chi2_5_LoosePt05_TTVA_loose",&B_iso_Ntracks_7_Chi2_5_LoosePt05_TTVA_loose,"B_iso_Ntracks_7_Chi2_5_LoosePt05_TTVA_loose/I");
        TBranch *Branch_closeTrkNtrks_TTVA_loose = tUpdate->Branch("closeTrkNtrksChi2_TTVA_loose",&closeTrkNtrksChi2_TTVA_loose,"closeTrkNtrksChi2_TTVA_loose/I");
        TBranch *Branch_closeTrkDOCA_TTVA_loose = tUpdate->Branch("closeTrkDOCA_TTVA_loose",&closeTrkDOCA_TTVA_loose,"closeTrkDOCA_TTVA_loose/F");
        TBranch *iso_TTVA_nominal = tUpdate->Branch("B_iso_7_Chi2_5_LoosePt05_TTVA_nominal",&B_iso_7_Chi2_5_LoosePt05_TTVA_nominal,"B_iso_7_Chi2_5_LoosePt05_TTVA_nominal/F");
        TBranch *isoNTrks_TTVA_nominal = tUpdate->Branch("B_iso_Ntracks_7_Chi2_5_LoosePt05_TTVA_nominal",&B_iso_Ntracks_7_Chi2_5_LoosePt05_TTVA_nominal,"B_iso_Ntracks_7_Chi2_5_LoosePt05_TTVA_nominal/I");
        TBranch *Branch_closeTrkNtrks_TTVA_nominal = tUpdate->Branch("closeTrkNtrksChi2_TTVA_nominal",&closeTrkNtrksChi2_TTVA_nominal,"closeTrkNtrksChi2_TTVA_nominal/I");
        TBranch *Branch_closeTrkDOCA_TTVA_nominal = tUpdate->Branch("closeTrkDOCA_TTVA_nominal",&closeTrkDOCA_TTVA_nominal,"closeTrkDOCA_TTVA_nominal/F");
        TBranch *iso_TTVA_tight = tUpdate->Branch("B_iso_7_Chi2_5_LoosePt05_TTVA_tight",&B_iso_7_Chi2_5_LoosePt05_TTVA_tight,"B_iso_7_Chi2_5_LoosePt05_TTVA_tight/F");
        TBranch *isoNTrks_TTVA_tight = tUpdate->Branch("B_iso_Ntracks_7_Chi2_5_LoosePt05_TTVA_tight",&B_iso_Ntracks_7_Chi2_5_LoosePt05_TTVA_tight,"B_iso_Ntracks_7_Chi2_5_LoosePt05_TTVA_tight/I");
        TBranch *Branch_closeTrkNtrks_TTVA_tight = tUpdate->Branch("closeTrkNtrksChi2_TTVA_tight",&closeTrkNtrksChi2_TTVA_tight,"closeTrkNtrksChi2_TTVA_tight/I");
        TBranch *Branch_closeTrkDOCA_TTVA_tight = tUpdate->Branch("closeTrkDOCA_TTVA_tight",&closeTrkDOCA_TTVA_tight,"closeTrkDOCA_TTVA_tight/F");

        TBranch *Branch_closeTrkDOCA = tUpdate->Branch("closeTrkDOCA",&closeTrkDOCA,"closeTrkDOCA/F");



  v_float  *pv_z        = 0;
  v_uint   *pv_type     = 0;
  v_float  *pv_sigma_z  = 0;
  v_uint    *idtrk_pvidx = 0; 
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
  double B_pT(0.);
  double B_eta(0.);
  double B_phi(0.);
  double B_IDtrk1_pT(0.);
  double B_IDtrk1_eta(0.);
  double B_IDtrk1_phi(0.);
  TVector3 myBVec;
  TVector3 myTrkVec;

  Double_t tracksPt_all_Chi6(0.);
  int tracksCnt_all_Chi6(0);
  Double_t tracksPt_all_Chi5(0.);
  int tracksCnt_all_Chi5(0);
  Double_t tracksPt_all_Chi4(0.);
  int tracksCnt_all_Chi4(0);

  Double_t tracksPt_TTVA_loose(0.);
  int nclosetrks_TTVA_loose(0);
  int tracksCnt_TTVA_loose(0);
  float docamin_TTVA_loose(999.0); 
  Double_t tracksPt_TTVA_nominal(0.);
  int nclosetrks_TTVA_nominal(0);
  int tracksCnt_TTVA_nominal(0);
  float docamin_TTVA_nominal(999.0);
  Double_t tracksPt_TTVA_tight(0.);
  int nclosetrks_TTVA_tight(0);
  int tracksCnt_TTVA_tight(0);
  float docamin_TTVA_tight(999.0);

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


for (auto ievent=0; ievent<nevents; ievent++)
    {
        cntUpdate+=1;
        // B_iso_7_Chi2_5_LoosePt05_AllTrks=-1;
        if (ievent%1000==0) cout << "Processing event "<< ievent << " -- total events: "<< cntUpdate << endl;
        // tFrame->GetEntry(cntUpdate); //for filling new branch
        ts->GetEntry(ievent);
        tev->GetEntry(event_index);

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

        //reset internal loop variables
        tracksPt_all_Chi6=0.;
        tracksCnt_all_Chi6=0;
        tracksPt_all_Chi5=0.;
        tracksCnt_all_Chi5=0;
        tracksPt_all_Chi4=0.;
        tracksCnt_all_Chi4=0;

        tracksPt_TTVA_loose=0.;
        tracksCnt_TTVA_loose=0;
        nclosetrks_TTVA_loose = 0;
        docamin_TTVA_loose=999.0;
        tracksPt_TTVA_nominal=0.;
        tracksCnt_TTVA_nominal=0;
        nclosetrks_TTVA_nominal = 0;
        docamin_TTVA_nominal=999.0;
        tracksPt_TTVA_tight=0.;
        tracksCnt_TTVA_tight=0;
        nclosetrks_TTVA_tight = 0;
        docamin_TTVA_tight=999.0;

        // float DOCA = sqrt( pow(closeTrkDCA, 2) + pow(closeTrkZCA, 2) );
        myBVec.SetPtEtaPhi(B_pT,B_eta,B_phi);
        for (unsigned int idx=0; idx<ntrks; idx++) 
        {
            // skip signal tracks (Bsmumu channel as an example, add other tracks for other signatures!)
            //
            if (idx == B_IDtrk1_trkidx || idx == B_IDtrk2_trkidx) continue; 

            myTrkVec.SetXYZ((*idtrk_px).at(idx),(*idtrk_py).at(idx),(*idtrk_pz).at(idx));
//chi^2 Isolation
            //for B Iso chi6 and B Iso number of tracks chi6
            if ((*B_PV_trksChi2).at(idx)<6. 
                 && myTrkVec.Pt()>500.
            ){
                // if (((*idtrk_nPIXhits).at(idx))>=1
                //         && (*idtrk_nSCThits).at(idx)>=2
                if((*idtrk_isTightPrimary).at(idx)==1
                ){
                    if (myTrkVec.DeltaR(myBVec) < 0.7){
                        tracksPt_all_Chi6 += myTrkVec.Pt();
                        tracksCnt_all_Chi6+=1;
                    }
                }
            }
            //for B Iso chi5 and B Iso number of tracks chi5
            if ((*B_PV_trksChi2).at(idx)<5. 
                 && myTrkVec.Pt()>500.
               ){
                    // if (((*idtrk_nPIXhits).at(idx))>=1
                    //         && (*idtrk_nSCThits).at(idx)>=2
                    if((*idtrk_isTightPrimary).at(idx)==1
                    ){
                        if (myTrkVec.DeltaR(myBVec) < 0.7){
                            tracksPt_all_Chi5 += myTrkVec.Pt();
                            tracksCnt_all_Chi5+=1;
                        }
                    }
            }
            //for B Iso chi4 and B Iso number of tracks chi4
            if ((*B_PV_trksChi2).at(idx)<4. 
                 && myTrkVec.Pt()>500.
               ){
                    // if (((*idtrk_nPIXhits).at(idx))>=1
                        // && (*idtrk_nSCThits).at(idx)>=2
                    if((*idtrk_isTightPrimary).at(idx)==1
                    ){
                        if (myTrkVec.DeltaR(myBVec) < 0.7){
                            tracksPt_all_Chi4 += myTrkVec.Pt();
                            tracksCnt_all_Chi4+=1;
                        }
                    }
            }
//TTVA working points
// TTVA loose
    if ( (*idtrk_pvidx_loose).at(idx) == B_PV_idx                 // choose tracks ass. to associated PV 
         || (*idtrk_pvidx_loose).at(idx) == pv_type->size()-1 ) // or choose tracks ass. to other real PV's (for non-ass. tracks use '==' instead)
        {            
            if (myTrkVec.Pt()>500.
               ){
                //for B Iso and B Iso number of tracks
                    // if (((*idtrk_nPIXhits).at(idx))>=1
                    //         && (*idtrk_nSCThits).at(idx)>=2
                    if((*B_PV_trksChi2).at(idx)<6. 
                         && (*idtrk_isTightPrimary).at(idx)==1
                    ){
                        if (myTrkVec.DeltaR(myBVec) < 0.7){
                            tracksPt_TTVA_loose += myTrkVec.Pt();
                            tracksCnt_TTVA_loose+=1;
                        }
                    }
                // for DOCA and NcloseTracks
                    if ((*B_VTX_trksChi2).at(idx)<=4.0) nclosetrks_TTVA_loose++;
                    if ( (*B_VTX_trksChi2).at(idx) <=7.0) {
                        if ( (*closeTrkDOCA_alltrks).at(idx) < docamin_TTVA_loose) {
                            docamin_TTVA_loose = (*closeTrkDOCA_alltrks).at(idx);
                        }
                    }            
                }
        }
// TTVA nominal
    if ( (*idtrk_pvidx_nominal).at(idx) == B_PV_idx                 // choose tracks ass. to associated PV 
         || (*idtrk_pvidx_nominal).at(idx) == pv_type->size()-1 ) // or choose tracks ass. to other real PV's (for non-ass. tracks use '==' instead)
        {            
            if (myTrkVec.Pt()>500.
               ){
                //for B Iso and B Iso number of tracks
                    // if (((*idtrk_nPIXhits).at(idx))>=1
                    //         && (*idtrk_nSCThits).at(idx)>=2
                    if((*B_PV_trksChi2).at(idx)<6. 
                         && (*idtrk_isTightPrimary).at(idx)==1
                    ){
                        if (myTrkVec.DeltaR(myBVec) < 0.7){
                            tracksPt_TTVA_nominal += myTrkVec.Pt();
                            tracksCnt_TTVA_nominal+=1;
                        }
                    }
                // for DOCA and NcloseTracks
                    if ((*B_VTX_trksChi2).at(idx)<=4.0) nclosetrks_TTVA_nominal++;
                    if ( (*B_VTX_trksChi2).at(idx) <=7.0) {
                        if ( (*closeTrkDOCA_alltrks).at(idx) < docamin_TTVA_nominal) {
                            docamin_TTVA_nominal = (*closeTrkDOCA_alltrks).at(idx);
                        }
                    }
            }
        }
// TTVA tight
    if ( (*idtrk_pvidx_tight).at(idx) == B_PV_idx                 // choose tracks ass. to associated PV 
         || (*idtrk_pvidx_tight).at(idx) == pv_type->size()-1 ) // or choose tracks ass. to other real PV's (for non-ass. tracks use '==' instead)
        {            
            if (myTrkVec.Pt()>500.
               ){
                //for B Iso and B Iso number of tracks
                    // if (((*idtrk_nPIXhits).at(idx))>=1
                    //     && (*idtrk_nSCThits).at(idx)>=2
                    if((*B_PV_trksChi2).at(idx)<6. 
                         && (*idtrk_isTightPrimary).at(idx)==1
                    ){
                        if (myTrkVec.DeltaR(myBVec) < 0.7){
                            tracksPt_TTVA_tight += myTrkVec.Pt();
                            tracksCnt_TTVA_tight+=1;
                        }
                    }
                // for DOCA and NcloseTracks
                    if ((*B_VTX_trksChi2).at(idx)<=4.0) nclosetrks_TTVA_tight++;
                    if ( (*B_VTX_trksChi2).at(idx) <=7.0) {
                        if ( (*closeTrkDOCA_alltrks).at(idx) < docamin_TTVA_tight) {
                            docamin_TTVA_tight = (*closeTrkDOCA_alltrks).at(idx);
                        }
                    } 
            }
        }

    }//end of idx for loop
            //calulate All Track Iso Variables
            B_iso_7_Chi2_5_LoosePt05_AllTrks_Chi6 = B_pT/(B_pT+tracksPt_all_Chi6);
            B_iso_Ntracks_7_Chi2_5_LoosePt05_AllTrks_Chi6 = tracksCnt_all_Chi6;            
            B_iso_7_Chi2_5_LoosePt05_AllTrks_Chi5 = B_pT/(B_pT+tracksPt_all_Chi5);
            B_iso_Ntracks_7_Chi2_5_LoosePt05_AllTrks_Chi5 = tracksCnt_all_Chi5;
            B_iso_7_Chi2_5_LoosePt05_AllTrks_Chi4 = B_pT/(B_pT+tracksPt_all_Chi4);
            B_iso_Ntracks_7_Chi2_5_LoosePt05_AllTrks_Chi4 = tracksCnt_all_Chi4;

            B_iso_7_Chi2_5_LoosePt05_TTVA_loose = B_pT/(B_pT+tracksPt_TTVA_loose);
            B_iso_Ntracks_7_Chi2_5_LoosePt05_TTVA_loose = tracksCnt_TTVA_loose;
            closeTrkNtrksChi2_TTVA_loose = nclosetrks_TTVA_loose;
            if (docamin_TTVA_loose==999.) docamin_TTVA_loose=-0.01;
            closeTrkDOCA_TTVA_loose = docamin_TTVA_loose;
            B_iso_7_Chi2_5_LoosePt05_TTVA_nominal = B_pT/(B_pT+tracksPt_TTVA_nominal);
            B_iso_Ntracks_7_Chi2_5_LoosePt05_TTVA_nominal = tracksCnt_TTVA_nominal;
            closeTrkNtrksChi2_TTVA_nominal = nclosetrks_TTVA_nominal;
            if (docamin_TTVA_nominal==999.) docamin_TTVA_nominal=-0.01;
            closeTrkDOCA_TTVA_nominal = docamin_TTVA_nominal;
            B_iso_7_Chi2_5_LoosePt05_TTVA_tight = B_pT/(B_pT+tracksPt_TTVA_tight);
            B_iso_Ntracks_7_Chi2_5_LoosePt05_TTVA_tight = tracksCnt_TTVA_tight;
            closeTrkNtrksChi2_TTVA_tight = nclosetrks_TTVA_tight;
            if (docamin_TTVA_tight==999.) docamin_TTVA_tight=-0.01;
            closeTrkDOCA_TTVA_tight = docamin_TTVA_tight;

            closeTrkDOCA = TMath::Sqrt(pow(closeTrkDCA,2)+pow(closeTrkZCA,2));
            tUpdate->Fill();

    }
cout<< "number of tracks so far: "<< totalTracks<< endl;
// cout<< "h_chi2_all entries: "<< h_chi2_all->GetEntries()<<endl;
// cout<< "h_chi2 entries: "<< h_chi2->GetEntries()<<endl;
     // fs->Close();
     // delete fs;
    fin->Close();
    fUpdate->cd();
    //  tn->Print();
    tUpdate->Write();
    fUpdate->Close();
    // fFrame->Close();
    }
  }
closedir(dpdf);
}
//end of IsolationStudy_fileloop()


int main(int argc, char* argv[])
{
  TString Dataset, pattern;
  if (argc>1) Dataset = TString(argv[1]);
  // if (argc>2) pattern = TString(argv[2]);
  // alltrksExample_fileLoop(inpath, pattern);
  // DrawMyPlots();
  IsolationStudy_fileloop(Dataset);
  return 0;
}

