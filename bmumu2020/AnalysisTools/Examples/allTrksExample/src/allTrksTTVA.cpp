//
// plot TTVA assiciation pie charts for associated to B-PV, pile-up and unassociated tracks if any
// plot log(chi2), |d0|, |dz0sin(theta)| for these 3 categories
//
// MISSING BSz for |dz0sin(theta)| calculation
// TODO: do the same with track eta (to see phase space where we are working)
//
// iskander(dot)ibragimov(at)cern(dot)ch
// 
// 
//  

#include "TPie.h"
#include "TCut.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "THStack.h"
#include "TLegend.h"
#include "TBranch.h"
#include "TCanvas.h"
#include "TVector3.h"
#include <iostream>
#include <dirent.h>

using namespace std;
typedef std::vector<unsigned int>  v_uint;
typedef std::vector<int>           v_int;
typedef std::vector<float>         v_float;
typedef std::vector<double>        v_double;

int main(int argc, char* argv[]) {

  TString suf, fsname;
  if (argc > 0) suf = argv[1];
  if (suf.Contains("data17")) {
    fsname = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/final_ntup/data17/Bmumu/v4/LASTskim.data17_run339849.Bmumu.Allv4.root";
  } else if (suf.Contains("dtwpverr")) {
    fsname = "/afs/cern.ch/user/i/ibragimo/skimmed_ntup_dt/dt_bsmumu_wpverr.root";
  } else if (suf.Contains("dtnopverr")) {
    fsname = "/afs/cern.ch/user/i/ibragimo/skimmed_ntup_dt/dt_bsmumu_nopverr.root";
  } else if (suf.Contains("mcwpverr")) {
    fsname = "/afs/cern.ch/user/i/ibragimo/skimmed_ntup/mc_bsmumu_wpverr.root";
  } else if (suf.Contains("mcnopverr")) {
    fsname = "/afs/cern.ch/user/i/ibragimo/skimmed_ntup/mc_bsmumu_nopverr.root";
  } else if (suf.Contains("mc16d")) {
    fsname = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/final_ntup/user.ibragimo.mc16d_13TeV.300426.Bs_mu3p5mu3p5.DAOD_BPHY8.e4889_s3126_r10201_p3793_NTUP_atrkwhits/v4/LASTskim.mc16d_run339849.Bs_mu3p5mu3p5.Bmumu.Allv4.root";
  } else {
    cout << "input unknown, exiting" << endl;
    exit(1);
  }
  TFile *fs  = new TFile(fsname);
  TTree *ts  = (TTree*)fs->Get("T_mv");
  TTree *tev = (TTree*)fs->Get("EventInfo");
  
  // variables related to PV container
  //
  v_uint   *pv_type = 0;
  v_float  *pv_z    = 0;
  tev->SetBranchAddress("pv_type", &pv_type);         // type of primary vertices (1,3 or 0 - the last one in the container)
  tev->SetBranchAddress("pv_z", &pv_z);

  // variables related to ID track container
  //
  v_uint   *idtrk_pvidx_lastround = 0;
  v_uint   *idtrk_pvidx_custom    = 0;
  v_uint   *idtrk_pvidx_loose     = 0;
  v_uint   *idtrk_pvidx_nominal   = 0;
  v_uint   *idtrk_pvidx_tight     = 0;

  v_int    *idtrk_nPIXhits  = 0;
  v_int    *idtrk_nSCThits  = 0;
  v_int    *idtrk_nPIXDead  = 0;
  v_int    *idtrk_nSCTDead  = 0;
  v_double *idtrk_px    = 0;
  v_double *idtrk_py    = 0;
  v_double *idtrk_pz    = 0;
  v_double *idtrk_d0    = 0;
  v_double *idtrk_z0    = 0;
  v_float  *idtrk_mintrksChi2 = 0;
  tev->SetBranchAddress("idtrk_pvidx", &idtrk_pvidx_lastround); // index of association of ID track to PV,
                                                      // i.e. the position of the corresponding PV in the vertex contaner
                                                      // if the position is the last position in the containter (PV type 0),
                                                      // that means that the track has not been associated to any PV.
                                                      // ( currently filled with info whether the track has been used in PV fit,  
                                                      // which is not recommended to be used by the vertex group )
  tev->SetBranchAddress("idtrk_pvidx_custom", &idtrk_pvidx_custom);     // same as above but for official custom WP
  tev->SetBranchAddress("idtrk_pvidx_loose", &idtrk_pvidx_loose);     // same as above but for official loose WP
  tev->SetBranchAddress("idtrk_pvidx_nominal", &idtrk_pvidx_nominal);     // same as above but for official nominal WP
  tev->SetBranchAddress("idtrk_pvidx_tight", &idtrk_pvidx_tight);     // same as above but for official tight WP
  tev->SetBranchAddress("idtrk_px", &idtrk_px);       // momenta of all ID tracks
  tev->SetBranchAddress("idtrk_py", &idtrk_py);
  tev->SetBranchAddress("idtrk_pz", &idtrk_pz);
  tev->SetBranchAddress("idtrk_d0", &idtrk_d0);
  tev->SetBranchAddress("idtrk_z0", &idtrk_z0);

  tev->SetBranchAddress("idtrk_nPIXhits", &idtrk_nPIXhits);    // nPIX hits
  tev->SetBranchAddress("idtrk_nSCThits", &idtrk_nSCThits);    // nSCT hits
  tev->SetBranchAddress("idtrk_nDeadPixels", &idtrk_nPIXDead); // nPIX Dead
  tev->SetBranchAddress("idtrk_nDeadSCT", &idtrk_nSCTDead);    // nSCT Dead

  tev->SetBranchAddress("idtrk_mintrksChi2", &idtrk_mintrksChi2);

  auto nevents = ts->GetEntries();
  cout<< "Entries in original tree: "<< nevents << endl;
  
  float B_MUCALC_mass(0.);
  int event_index(0);
  int B_PV_idx(0);
  int B_IDtrk1_trkidx(0);
  int B_IDtrk2_trkidx(0);
  v_float *B_PV_trksChi2 = 0;
  v_float *B_VTX_trksChi2=0;
  v_float *B_VTX_trksChi2trkspart=0;
  v_float *closeTrkDOCA_alltrks=0;
  int closeTrkNtrksChi2(0);
  float closeTrkDCA(0.);
  float closeTrkZCA(0.);
  float closeTrkDCAErr(0.);
  float closeTrkZCAErr(0.);
  float B_iso_7_Chi2_5_LoosePt05(0.), B_iso_7_Chi2_lastround_TTVA, B_iso_10_Chi2_custom_TTVA, B_iso_7_Chi2_alaRun1_TTVA;
  int Npv(0);
  float PRIVX_mu(0.);
  float Muon1_reco_eff_sf(0.);
  float Muon2_reco_eff_sf(0.);
  double PVWeights(0.), ew(0), B_pT(0), B_eta(0), B_phi(0), Lxy(0), a_2D(0);

  ts->SetBranchAddress("B_MUCALC_mass",&B_MUCALC_mass);
  ts->SetBranchAddress("event_index",  &event_index);                           // index to EventInfo tree

  // variables for the isolation studies
  //
  ts->SetBranchAddress("B_PV_idx",&B_PV_idx);                                  // index to associated PV  
  ts->SetBranchAddress("B_PV_trksChi2",&B_PV_trksChi2);                        // chi2 to associated PV, per track
  ts->SetBranchAddress("B_iso_7_Chi2_5_LoosePt05",&B_iso_7_Chi2_5_LoosePt05);  // DxAOD isoaltion variable
  ts->SetBranchAddress("B_pT",&B_pT);
  ts->SetBranchAddress("B_eta",&B_eta);
  ts->SetBranchAddress("B_phi",&B_phi);
  ts->SetBranchAddress("Lxy",&Lxy);
  ts->SetBranchAddress("a_2D",&a_2D);

  // variables for the close track studies
  //
  ts->SetBranchAddress("B_VTX_trksChi2",&B_VTX_trksChi2);                // chi2 of each track to the B vertex
  ts->SetBranchAddress("B_VTX_trksChi2trkspart",&B_VTX_trksChi2trkspart);// chi2 of each track to the B vertex using only errors from track parameters
  ts->SetBranchAddress("closeTrkDOCA_alltrks",&closeTrkDOCA_alltrks);    // DOCA of each track to B vertex

  ts->SetBranchAddress("closeTrkNtrksChi2",&closeTrkNtrksChi2);          // DxAOD closeTrkNtrksChi2 variable
  ts->SetBranchAddress("closeTrkDCA",&closeTrkDCA);                      // DxAOD closeTrkDCA variable 
  ts->SetBranchAddress("closeTrkZCA",&closeTrkZCA);                      // DxAOD closeTrkZCA variable
  ts->SetBranchAddress("closeTrkDCAErr",&closeTrkDCAErr);                      // DxAOD closeTrkDCAErr variable 
  ts->SetBranchAddress("closeTrkZCAErr",&closeTrkZCAErr);                      // DxAOD closeTrkZCAErr variable

  // variables to identify signal tracks
  //
  ts->SetBranchAddress("B_IDtrk1_trkidx",&B_IDtrk1_trkidx); // indexes of muon tracks
  ts->SetBranchAddress("B_IDtrk2_trkidx",&B_IDtrk2_trkidx);

  ts->SetBranchAddress("Npv",  &Npv);
  ts->SetBranchAddress("PRIVX_mu",  &PRIVX_mu);

  ts->SetBranchAddress("Muon1_reco_eff_sf", &Muon1_reco_eff_sf);
  ts->SetBranchAddress("Muon2_reco_eff_sf", &Muon2_reco_eff_sf);
  ts->SetBranchAddress("PVWeights", &PVWeights);


  THStack *hchi2_ass = new THStack("hchi2_ass","log(chi2) of associated PVs");
  THStack *hchi2_una = new THStack("hchi2_una","log(chi2) of unassociated PVs");
  THStack *hchi2_pu = new THStack("hchi2_pu","log(chi2) of pileup PVs");

  TH1F*h_chi2_runone_ass = new TH1F("h_chi2_runone_ass","log(chi2) to ass. PV, Run 1 TTVA",200,-10,15);
  h_chi2_runone_ass->SetLineColor(kBlack);
  TH1F*h_chi2_runone_pu = new TH1F("h_chi2_runone_pu","log(chi2) to pileup PV, Run 1 TTVA",200,-10,15);
  h_chi2_runone_pu->SetLineColor(kBlack);

  TH1F*h_chi2_custom_ass = new TH1F("h_chi2_custom_ass","log(chi2) to ass. PV, custom TTVA",200,-10,15);
  h_chi2_custom_ass->SetLineColor(kCyan);
  TH1F*h_chi2_custom_pu = new TH1F("h_chi2_custom_pu","log(chi2) to pileup PV, custom TTVA",200,-10,15);
  h_chi2_custom_pu->SetLineColor(kCyan);

  TH1F*h_chi2_loose_ass = new TH1F("h_chi2_loose_ass","log(chi2) to ass. PV, loose TTVA",200,-10,15);
  h_chi2_loose_ass->SetLineColor(kRed);
  TH1F*h_chi2_loose_pu = new TH1F("h_chi2_loose_pu","log(chi2) to pileup PV, loose TTVA",200,-10,15);
  h_chi2_loose_pu->SetLineColor(kRed);
  TH1F*h_chi2_loose_una = new TH1F("h_chi2_loose_una","log(chi2) to unass. PV, loose TTVA",200,-10,15);
  h_chi2_loose_una->SetLineColor(kRed);

  TH1F*h_chi2_nominal_ass = new TH1F("h_chi2_nominal_ass","log(chi2) to ass. PV, nominal TTVA",200,-10,15);
  h_chi2_nominal_ass->SetLineColor(kGreen+2);
  TH1F*h_chi2_nominal_pu = new TH1F("h_chi2_nominal_pu","log(chi2) to pileup PV, nominal TTVA",200,-10,15);
  h_chi2_nominal_pu->SetLineColor(kGreen+2);
  TH1F*h_chi2_nominal_una = new TH1F("h_chi2_nominal_una","log(chi2) to unass. PV, nominal TTVA",200,-10,15);
  h_chi2_nominal_una->SetLineColor(kGreen+2);

  TH1F*h_chi2_tight_ass = new TH1F("h_chi2_tight_ass","log(chi2) to ass. PV, tight TTVA",200,-10,15);
  h_chi2_tight_ass->SetLineColor(kBlue);
  TH1F*h_chi2_tight_pu = new TH1F("h_chi2_tight_pu","log(chi2) to pileup PV, tight TTVA",200,-10,15);
  h_chi2_tight_pu->SetLineColor(kBlue);
  TH1F*h_chi2_tight_una = new TH1F("h_chi2_tight_una","log(chi2) to unass. PV, tight TTVA",200,-10,15);
  h_chi2_tight_una->SetLineColor(kBlue);


  THStack *heta_ass = new THStack("heta_ass","track #eta for associated PVs");
  THStack *heta_una = new THStack("heta_una","track #eta for unassociated PVs");
  THStack *heta_pu = new THStack("heta_pu","track #eta for pileup PVs");

  TH1F*h_eta_runone_ass = new TH1F("h_eta_runone_ass","track #eta, Run 1 TTVA",55,-2.75,2.75);
  h_eta_runone_ass->SetLineColor(kBlack);
  TH1F*h_eta_runone_pu = new TH1F("h_eta_runone_pu","track #eta, Run 1 TTVA",55,-2.75,2.75);
  h_eta_runone_pu->SetLineColor(kBlack);

  TH1F*h_eta_custom_ass = new TH1F("h_eta_custom_ass","track #eta, custom TTVA",55,-2.75,2.75);
  h_eta_custom_ass->SetLineColor(kCyan);
  TH1F*h_eta_custom_pu = new TH1F("h_eta_custom_pu","track #eta, custom TTVA",55,-2.75,2.75);
  h_eta_custom_pu->SetLineColor(kCyan);

  TH1F*h_eta_loose_ass = new TH1F("h_eta_loose_ass","track #eta, loose TTVA",55,-2.75,2.75);
  h_eta_loose_ass->SetLineColor(kRed);
  TH1F*h_eta_loose_pu = new TH1F("h_eta_loose_pu","track #eta, loose TTVA",55,-2.75,2.75);
  h_eta_loose_pu->SetLineColor(kRed);
  TH1F*h_eta_loose_una = new TH1F("h_eta_loose_una","track #eta, loose TTVA",55,-2.75,2.75);
  h_eta_loose_una->SetLineColor(kRed);

  TH1F*h_eta_nominal_ass = new TH1F("h_eta_nominal_ass","track #eta, nominal TTVA",55,-2.75,2.75);
  h_eta_nominal_ass->SetLineColor(kGreen+2);
  TH1F*h_eta_nominal_pu = new TH1F("h_eta_nominal_pu","track #eta, nominal TTVA",55,-2.75,2.75);
  h_eta_nominal_pu->SetLineColor(kGreen+2);
  TH1F*h_eta_nominal_una = new TH1F("h_eta_nominal_una","track #eta, nominal TTVA",55,-2.75,2.75);
  h_eta_nominal_una->SetLineColor(kGreen+2);

  TH1F*h_eta_tight_ass = new TH1F("h_eta_tight_ass","track #eta, tight TTVA",55,-2.75,2.75);
  h_eta_tight_ass->SetLineColor(kBlue);
  TH1F*h_eta_tight_pu = new TH1F("h_eta_tight_pu","track #eta, tight TTVA",55,-2.75,2.75);
  h_eta_tight_pu->SetLineColor(kBlue);
  TH1F*h_eta_tight_una = new TH1F("h_eta_tight_una","track #eta, tight TTVA",55,-2.75,2.75);
  h_eta_tight_una->SetLineColor(kBlue);

  THStack *had0_ass = new THStack("had0_ass","|d0| of associated PVs");
  THStack *had0_una = new THStack("had0_una","|d0| of unassociated PVs");
  THStack *had0_pu = new THStack("had0_pu","|d0| of pileup PVs");

  TH1F*h_ad0_runone_ass = new TH1F("h_ad0_runone_ass","|d0|, Run 1 TTVA",100,-0.1,9.9);
  h_ad0_runone_ass->SetLineColor(kBlack);
  TH1F*h_ad0_runone_pu = new TH1F("h_ad0_runone_pu","|d0|, Run 1 TTVA",100,-0.1,9.9);
  h_ad0_runone_pu->SetLineColor(kBlack);

  TH1F*h_ad0_custom_ass = new TH1F("h_ad0_custom_ass","|d0|, custom TTVA",100,-0.1,9.9);
  h_ad0_custom_ass->SetLineColor(kCyan);
  TH1F*h_ad0_custom_pu = new TH1F("h_ad0_custom_pu","|d0|, custom TTVA",100,-0.1,9.9);
  h_ad0_custom_pu->SetLineColor(kCyan);

  TH1F*h_ad0_loose_ass = new TH1F("h_ad0_loose_ass","|d0|, loose TTVA",100,-0.1,9.9);
  h_ad0_loose_ass->SetLineColor(kRed);
  TH1F*h_ad0_loose_pu = new TH1F("h_ad0_loose_pu","|d0|, loose TTVA",100,-0.1,9.9);
  h_ad0_loose_pu->SetLineColor(kRed);
  TH1F*h_ad0_loose_una = new TH1F("h_ad0_loose_una","|d0|, loose TTVA",100,-0.1,9.9);
  h_ad0_loose_una->SetLineColor(kRed);

  TH1F*h_ad0_nominal_ass = new TH1F("h_ad0_nominal_ass","|d0|, nominal TTVA",100,-0.1,9.9);
  h_ad0_nominal_ass->SetLineColor(kGreen+2);
  TH1F*h_ad0_nominal_pu = new TH1F("h_ad0_nominal_pu","|d0|, nominal TTVA",100,-0.1,9.9);
  h_ad0_nominal_pu->SetLineColor(kGreen+2);
  TH1F*h_ad0_nominal_una = new TH1F("h_ad0_nominal_una","|d0|, nominal TTVA",100,-0.1,9.9);
  h_ad0_nominal_una->SetLineColor(kGreen+2);

  TH1F*h_ad0_tight_ass = new TH1F("h_ad0_tight_ass","|d0|, tight TTVA",100,-0.1,9.9);
  h_ad0_tight_ass->SetLineColor(kBlue);
  TH1F*h_ad0_tight_pu = new TH1F("h_ad0_tight_pu","|d0|, tight TTVA",100,-0.1,9.9);
  h_ad0_tight_pu->SetLineColor(kBlue);
  TH1F*h_ad0_tight_una = new TH1F("h_ad0_tight_una","|d0|, tight TTVA",100,-0.1,9.9);
  h_ad0_tight_una->SetLineColor(kBlue);


  THStack *hdz0sint_ass = new THStack("hdz0sint_ass","|#Deltaz0sin#theta| of associated PVs");
  THStack *hdz0sint_una = new THStack("hdz0sint_una","|#Deltaz0sin#theta| of unassociated PVs");
  THStack *hdz0sint_pu = new THStack("hdz0sint_pu","|#Deltaz0sin#theta| of pileup PVs");

  TH1F*h_dz0sint_runone_ass = new TH1F("h_dz0sint_runone_ass","|#Deltaz0sin#theta|, Run 1 TTVA",100,-0.1,9.9);
  h_dz0sint_runone_ass->SetLineColor(kBlack);
  TH1F*h_dz0sint_runone_pu = new TH1F("h_dz0sint_runone_pu","|#Deltaz0sin#theta|, Run 1 TTVA",100,-0.1,9.9);
  h_dz0sint_runone_pu->SetLineColor(kBlack);

  TH1F*h_dz0sint_custom_ass = new TH1F("h_dz0sint_custom_ass","|#Deltaz0sin#theta|, custom TTVA",100,-0.1,9.9);
  h_dz0sint_custom_ass->SetLineColor(kCyan);
  TH1F*h_dz0sint_custom_pu = new TH1F("h_dz0sint_custom_pu","|#Deltaz0sin#theta|, custom TTVA",100,-0.1,9.9);
  h_dz0sint_custom_pu->SetLineColor(kCyan);

  TH1F*h_dz0sint_loose_ass = new TH1F("h_dz0sint_loose_ass","|#Deltaz0sin#theta|, loose TTVA",100,-0.1,9.9);
  h_dz0sint_loose_ass->SetLineColor(kRed);
  TH1F*h_dz0sint_loose_pu = new TH1F("h_dz0sint_loose_pu","|#Deltaz0sin#theta|, loose TTVA",100,-0.1,9.9);
  h_dz0sint_loose_pu->SetLineColor(kRed);
  TH1F*h_dz0sint_loose_una = new TH1F("h_dz0sint_loose_una","|#Deltaz0sin#theta|, loose TTVA",100,-0.1,9.9);
  h_dz0sint_loose_una->SetLineColor(kRed);

  TH1F*h_dz0sint_nominal_ass = new TH1F("h_dz0sint_nominal_ass","|#Deltaz0sin#theta|, nominal TTVA",100,-0.1,9.9);
  h_dz0sint_nominal_ass->SetLineColor(kGreen+2);
  TH1F*h_dz0sint_nominal_pu = new TH1F("h_dz0sint_nominal_pu","|#Deltaz0sin#theta|, nominal TTVA",100,-0.1,9.9);
  h_dz0sint_nominal_pu->SetLineColor(kGreen+2);
  TH1F*h_dz0sint_nominal_una = new TH1F("h_dz0sint_nominal_una","|#Deltaz0sin#theta|, nominal TTVA",100,-0.1,9.9);
  h_dz0sint_nominal_una->SetLineColor(kGreen+2);

  TH1F*h_dz0sint_tight_ass = new TH1F("h_dz0sint_tight_ass","|#Deltaz0sin#theta|, tight TTVA",100,-0.1,9.9);
  h_dz0sint_tight_ass->SetLineColor(kBlue);
  TH1F*h_dz0sint_tight_pu = new TH1F("h_dz0sint_tight_pu","|#Deltaz0sin#theta|, tight TTVA",100,-0.1,9.9);
  h_dz0sint_tight_pu->SetLineColor(kBlue);
  TH1F*h_dz0sint_tight_una = new TH1F("h_dz0sint_tight_una","|#Deltaz0sin#theta|, tight TTVA",100,-0.1,9.9);
  h_dz0sint_tight_una->SetLineColor(kBlue);



  map<string, int> associated;
  map<string, int> pileup;
  map<string, int> unassociated;
  associated.insert(pair<string, int>("loose", 0));
  associated.insert(pair<string, int>("nominal", 0));
  associated.insert(pair<string, int>("tight", 0));
  associated.insert(pair<string, int>("runone", 0));
  associated.insert(pair<string, int>("custom", 0));
  unassociated.insert(pair<string, int>("loose", 0));
  unassociated.insert(pair<string, int>("nominal", 0));
  unassociated.insert(pair<string, int>("tight", 0));
  unassociated.insert(pair<string, int>("runone", 0));
  unassociated.insert(pair<string, int>("custom", 0));
  pileup.insert(pair<string, int>("loose", 0));
  pileup.insert(pair<string, int>("nominal", 0));
  pileup.insert(pair<string, int>("tight", 0));
  pileup.insert(pair<string, int>("runone", 0));
  pileup.insert(pair<string, int>("custom", 0));


  int ntrkstotal(0);

  for (auto ievent=0; ievent<nevents; ievent++)
    {
      if (ievent%100000==0) cout << "Processing event "<< ievent << endl;
      ts->GetEntry(ievent);

      // do not run on blinded events
      if (!fsname.Contains("mc16") && (B_MUCALC_mass<0.) ) continue; 

      // event weight
      ew = Muon1_reco_eff_sf*Muon2_reco_eff_sf*PVWeights; 

      TVector3 B_p;
      B_p.SetPtEtaPhi(B_pT, B_eta, B_phi);
    
      tev->GetEntry(event_index);

      // cross-check on the ntuple structure     
      auto ntrks = B_PV_trksChi2->size();
      if ((*idtrk_pvidx_lastround).size() != ntrks) {
	cout << "FATAL: ID trk info size unequal in event and candidate trees, exiting. " << (*idtrk_pvidx_lastround).size() << " <-ev|cand-> " << ntrks << " event: "<< ievent << endl;
	exit(0);
      }
      // another cross-check on the ntuple structure     
      if ( Npv != pv_type->size()-1 ) {
	cout << "WARNING: smth is wrong with Npv, continuing. " << pv_type->size()-1 << " <-ev|cand-> " << Npv << " event: "<< ievent << endl;
      }
      // yet another cross-check on the ntuple structure    
      if ( (*idtrk_mintrksChi2).size() != (*B_PV_trksChi2).size() ) {
	cout << "smth is wrong now: "<< (*idtrk_mintrksChi2).size() << " vs " << (*B_PV_trksChi2).size() << endl;  
      }


      for (unsigned int idx=0; idx<ntrks; idx++) {

	// skip signal tracks (Bsmumu channel as an example, add other tracks for other signatures!)
	//
	if ( (idx == B_IDtrk1_trkidx || idx == B_IDtrk2_trkidx) ) continue;
	if ( ( (*idtrk_nPIXhits).at(idx) + (*idtrk_nPIXDead).at(idx) )<1 || ( (*idtrk_nSCThits).at(idx) + (*idtrk_nSCTDead).at(idx) )<2 ) continue;
	TVector3 idtrk_p( (*idtrk_px).at(idx), (*idtrk_py).at(idx), (*idtrk_pz).at(idx) );
 	float track_eta = (float)idtrk_p.Eta(); 
	if ( fabs(track_eta) >=2.5 || idtrk_p.Pt()<=500. ) continue;
	ntrkstotal++;

	double deltaR = B_p.DeltaR(idtrk_p);

	// select tracks by vertex association
	// 
	float logchi2PV = (*B_PV_trksChi2).at(idx);
	float d0abs     = (float)fabs( (*idtrk_d0).at(idx) ); 
	float adz0sint  = fabs( ( (float)(*idtrk_z0).at(idx) /*+ BSz*/ - (*pv_z).at(B_PV_idx) ) * sin( idtrk_p.Theta() ) );

	if ( (*B_PV_trksChi2).at(idx) < 5.0 ) {
	  associated["runone"]++;
	  h_chi2_runone_ass->Fill( logchi2PV );
	  if (deltaR < 1.0) h_eta_runone_ass->Fill( track_eta );
	  h_ad0_runone_ass->Fill( d0abs );
	  h_dz0sint_runone_ass->Fill( adz0sint );
	} else {
	  pileup["runone"]++;
	  h_chi2_runone_pu->Fill( logchi2PV );
	  if (deltaR < 1.0) h_eta_runone_pu->Fill( track_eta );
	  h_ad0_runone_pu->Fill( d0abs );
	  h_dz0sint_runone_pu->Fill( adz0sint );
	}
	
	if ( (*idtrk_pvidx_custom).at(idx) == B_PV_idx ) {
	  associated["custom"]++;
	  h_chi2_custom_ass->Fill( logchi2PV );
	  if (deltaR < 1.0) h_eta_custom_ass->Fill( track_eta );
	  h_ad0_custom_ass->Fill( d0abs );
	  h_dz0sint_custom_ass->Fill( adz0sint );
	} else if ( (*idtrk_pvidx_custom).at(idx) == pv_type->size()-1 ) {
	  unassociated["custom"]++;
	  cout << "Unassociated custom WP track - it can't happen!!!" << endl;
	} else {
	  pileup["custom"]++;
	  h_chi2_custom_pu->Fill( logchi2PV );
	  if (deltaR < 1.0) h_eta_custom_pu->Fill( track_eta );
	  h_ad0_custom_pu->Fill( d0abs );
	  h_dz0sint_custom_pu->Fill( adz0sint );
	}

	
	if ( (*idtrk_pvidx_loose).at(idx) == B_PV_idx ) {
	  associated["loose"]++;
	  h_chi2_loose_ass->Fill( logchi2PV );
	  if (deltaR < 1.0) h_eta_loose_ass->Fill( track_eta );
	  h_ad0_loose_ass->Fill( d0abs );
	  h_dz0sint_loose_ass->Fill( adz0sint );
	} else if ( (*idtrk_pvidx_loose).at(idx) == pv_type->size()-1 ) {
	  unassociated["loose"]++;
	  h_chi2_loose_una->Fill( logchi2PV );
	  if (deltaR < 1.0) h_eta_loose_una->Fill( track_eta );
	  h_ad0_loose_una->Fill( d0abs );
	  h_dz0sint_loose_una->Fill( adz0sint );
	} else {
	  pileup["loose"]++;
	  h_chi2_loose_pu->Fill( logchi2PV );
	  if (deltaR < 1.0) h_eta_loose_pu->Fill( track_eta );
	  h_ad0_loose_pu->Fill( d0abs );
	  h_dz0sint_loose_pu->Fill( adz0sint );
	}

	
	if ( (*idtrk_pvidx_nominal).at(idx) == B_PV_idx ) {
	  associated["nominal"]++;
	  h_chi2_nominal_ass->Fill( logchi2PV );
	  if (deltaR < 1.0) h_eta_nominal_ass->Fill( track_eta );
	  h_ad0_nominal_ass->Fill( d0abs );
	  h_dz0sint_nominal_ass->Fill( adz0sint );
	} else if ( (*idtrk_pvidx_nominal).at(idx) == pv_type->size()-1 ) {
	  unassociated["nominal"]++;
	  h_chi2_nominal_una->Fill( logchi2PV );
	  if (deltaR < 1.0) h_eta_nominal_una->Fill( track_eta );
	  h_ad0_nominal_una->Fill( d0abs );
	  h_dz0sint_nominal_una->Fill( adz0sint );
	} else {
	  pileup["nominal"]++;
	  h_chi2_nominal_pu->Fill( logchi2PV );
	  if (deltaR < 1.0) h_eta_nominal_pu->Fill( track_eta );
	  h_ad0_nominal_pu->Fill( d0abs );
	  h_dz0sint_nominal_pu->Fill( adz0sint );
	}

	
	if ( (*idtrk_pvidx_tight).at(idx) == B_PV_idx ) {
	  associated["tight"]++;
	  h_chi2_tight_ass->Fill( logchi2PV );
	  if (deltaR < 1.0) h_eta_tight_ass->Fill( track_eta );
	  h_ad0_tight_ass->Fill( d0abs );
	  h_dz0sint_tight_ass->Fill( adz0sint );
	} else if ( (*idtrk_pvidx_tight).at(idx) == pv_type->size()-1 ) {
	  unassociated["tight"]++;
	  h_chi2_tight_una->Fill( logchi2PV );
	  if (deltaR < 1.0) h_eta_tight_una->Fill( track_eta );
	  h_ad0_tight_una->Fill( d0abs );
	  h_dz0sint_tight_una->Fill( adz0sint );
	} else {
	  pileup["tight"]++;
	  h_chi2_tight_pu->Fill( logchi2PV );
	  if (deltaR < 1.0) h_eta_tight_pu->Fill( track_eta );
	  h_ad0_tight_pu->Fill( d0abs );
	  h_dz0sint_tight_pu->Fill( adz0sint );
	}
	  
      } // tracks
    } // events

  cout << "done w loops, ntrkstotal: "<< ntrkstotal << endl;

  Float_t vals[3] = {.2, 1.1, .6};
  Int_t colors[3] = {2, 3, 4};
  const char* pielabels[3] = {"associated", "unsassociated", "pileup"};

  TCanvas* c = new TCanvas("DoStats","Pie charts with track fractions",900,600);
  c->Divide(3,2);
  
  c->cd(1);
  vals[0] = associated["loose"];
  vals[1] = unassociated["loose"];
  vals[2] = pileup["loose"];
  TPie *pie3 = new TPie("pie3", "#it{loose} association", 3, vals, colors);
  pie3->SetRadius(.2);
  pie3->SetLabelsOffset(.01);
  pie3->SetLabelFormat("%perc");
  pie3->SetLabels(pielabels);
  pie3->Draw("nol <");
  TLegend *pieleg = pie3->MakeLegend();
  pieleg->SetY1(.56); pieleg->SetY2(.86);
  
  c->cd(2);
  vals[0] = associated["nominal"];
  vals[1] = unassociated["nominal"];
  vals[2] = pileup["nominal"];
  TPie *pie4 = new TPie("pie4", "#it{nominal} association", 3, vals, colors);
  pie4->SetRadius(.2);
  pie4->SetLabelsOffset(.01);
  pie4->SetLabelFormat("%perc");
  pie4->SetLabels(pielabels);
  pie4->Draw("nol <");
  
  c->cd(3);
  vals[0] = associated["tight"];
  vals[1] = unassociated["tight"];
  vals[2] = pileup["tight"];
  TPie *pie5 = new TPie("pie5", "#it{tight} association", 3, vals, colors);
  pie5->SetRadius(.2);
  pie5->SetLabelsOffset(.01);
  pie5->SetLabelFormat("%perc");
  pie5->SetLabels(pielabels);
  pie5->Draw("nol <");
  
  c->cd(4);
  vals[0] = associated["runone"];
  vals[1] = unassociated["runone"];
  vals[2] = pileup["runone"];
  TPie *pie1 = new TPie("pie1", "#it{runone} association", 3, vals, colors);
  pie1->SetRadius(.2);
  pie1->SetLabelsOffset(.01);
  pie1->SetLabelFormat("%perc");
  pie1->SetLabels(pielabels);
  pie1->Draw("nol <");
  c->cd(5);
  vals[0] = associated["custom"];
  vals[1] = unassociated["custom"];
  vals[2] = pileup["custom"];
  TPie *pie2 = new TPie("pie2", "#it{custom} association", 3, vals, colors);
  pie2->SetRadius(.2);
  pie2->SetLabelsOffset(.01);
  pie2->SetLabelFormat("%perc");
  pie2->SetLabels(pielabels);
  pie2->Draw("nol <");
  
  //c->SaveAs("pie_"+suf+".root");
  c->SaveAs("pie_"+suf+".eps");  
  
  TLegend* leg0;
  TLegend* leg1;
  TLegend* leg2;
  TCanvas* c1 = new TCanvas("DoChi2","log(Chi2)_{PV} for different trk associations",900,600);
  c1->Divide(2,2);
  c1->cd(1);
  gPad->SetLogy();gPad->SetTicky(1);
  hchi2_ass->Add(h_chi2_runone_ass);
  hchi2_ass->Add(h_chi2_custom_ass);
  hchi2_ass->Add(h_chi2_loose_ass);
  hchi2_ass->Add(h_chi2_nominal_ass);
  hchi2_ass->Add(h_chi2_tight_ass);
  hchi2_ass->Draw("nostack");
  hchi2_ass->GetXaxis()->SetTitle("log(chi2) to B-PV, associated tracks");
  leg0 = new TLegend(0.05,0.78,0.35,0.94);
  leg0->AddEntry(h_chi2_loose_ass,"loose","l");
  leg0->AddEntry(h_chi2_nominal_ass,"nominal","l");
  leg0->AddEntry(h_chi2_tight_ass,"tight","l");
  leg0->AddEntry(h_chi2_runone_ass,"runone","l");
  leg0->AddEntry(h_chi2_custom_ass,"custom","l");
  leg0->Draw();
  c1->cd(2);
  gPad->SetLogy();gPad->SetTicky(1);
  hchi2_pu->Add(h_chi2_runone_pu);
  hchi2_pu->Add(h_chi2_custom_pu);
  hchi2_pu->Add(h_chi2_loose_pu);
  hchi2_pu->Add(h_chi2_nominal_pu);
  hchi2_pu->Add(h_chi2_tight_pu);
  hchi2_pu->Draw("nostack");
  hchi2_pu->GetXaxis()->SetTitle("log(chi2) to B-PV, pileup tracks");
  leg1 = new TLegend(0.05,0.78,0.35,0.94);
  leg1->AddEntry(h_chi2_loose_pu,"loose","l");
  leg1->AddEntry(h_chi2_nominal_pu,"nominal","l");
  leg1->AddEntry(h_chi2_tight_pu,"tight","l");
  leg1->AddEntry(h_chi2_runone_pu,"runone","l");
  leg1->AddEntry(h_chi2_custom_pu,"custom","l");
  leg1->Draw();
  c1->cd(3);
  gPad->SetLogy();gPad->SetTicky(1);
  hchi2_una->Add(h_chi2_loose_una);
  hchi2_una->Add(h_chi2_nominal_una);
  hchi2_una->Add(h_chi2_tight_una);
  hchi2_una->Draw("nostack");
  hchi2_una->GetXaxis()->SetTitle("log(chi2) to B-PV, unassociated tracks");
  leg2 = new TLegend(0.05,0.78,0.35,0.94);
  leg2->AddEntry(h_chi2_loose_una,"loose","l");
  leg2->AddEntry(h_chi2_nominal_una,"nominal","l");
  leg2->AddEntry(h_chi2_tight_una,"tight","l");
  leg2->Draw();
  //  c1->SaveAs("chi2all_"+suf+".root");
  c1->SaveAs("chi2all_"+suf+".eps");  


  TCanvas* c2 = new TCanvas("Absd0","|d0| for different trk associations",900,600);
  c2->Divide(2,2);
  c2->cd(1);
  gPad->SetLogy();gPad->SetTicky(1);
  had0_ass->Add(h_ad0_runone_ass);
  had0_ass->Add(h_ad0_custom_ass);
  had0_ass->Add(h_ad0_loose_ass);
  had0_ass->Add(h_ad0_nominal_ass);
  had0_ass->Add(h_ad0_tight_ass);
  had0_ass->Draw("nostack");
  had0_ass->GetXaxis()->SetTitle("|d0|, associated tracks [mm]");
  leg0 = new TLegend(0.65,0.78,0.95,0.94);
  leg0->AddEntry(h_ad0_loose_ass,"loose","l");
  leg0->AddEntry(h_ad0_nominal_ass,"nominal","l");
  leg0->AddEntry(h_ad0_tight_ass,"tight","l");
  leg0->AddEntry(h_ad0_runone_ass,"runone","l");
  leg0->AddEntry(h_ad0_custom_ass,"custom","l");
  leg0->Draw();
  c2->cd(2);
  gPad->SetLogy();gPad->SetTicky(1);
  had0_pu->Add(h_ad0_runone_pu);
  had0_pu->Add(h_ad0_custom_pu);
  had0_pu->Add(h_ad0_loose_pu);
  had0_pu->Add(h_ad0_nominal_pu);
  had0_pu->Add(h_ad0_tight_pu);
  had0_pu->Draw("nostack");
  had0_pu->GetXaxis()->SetTitle("|d0|, pileup tracks [mm]");
  leg1 = new TLegend(0.65,0.78,0.95,0.94);
  leg1->AddEntry(h_ad0_loose_pu,"loose","l");
  leg1->AddEntry(h_ad0_nominal_pu,"nominal","l");
  leg1->AddEntry(h_ad0_tight_pu,"tight","l");
  leg1->AddEntry(h_ad0_runone_pu,"runone","l");
  leg1->AddEntry(h_ad0_custom_pu,"custom","l");
  leg1->Draw();
  c2->cd(3);
  gPad->SetLogy();gPad->SetTicky(1);
  had0_una->Add(h_ad0_loose_una);
  had0_una->Add(h_ad0_nominal_una);
  had0_una->Add(h_ad0_tight_una);
  had0_una->Draw("nostack");
  had0_una->GetXaxis()->SetTitle("|d0|, unassociated tracks [mm]");
  leg2 = new TLegend(0.65,0.78,0.95,0.94);
  leg2->AddEntry(h_ad0_loose_una,"loose","l");
  leg2->AddEntry(h_ad0_nominal_una,"nominal","l");
  leg2->AddEntry(h_ad0_tight_una,"tight","l");
  leg2->Draw();
  //  c2->SaveAs("absad0all_"+suf+".root");
  c2->SaveAs("absd0all_"+suf+".eps");  

  TCanvas* c3 = new TCanvas("Absdz0sint","|#Deltaz0sin#theta| for different trk associations",900,600);
  c3->Divide(2,2);
  c3->cd(1);
  gPad->SetLogy();gPad->SetTicky(1);
  hdz0sint_ass->Add(h_dz0sint_runone_ass);
  hdz0sint_ass->Add(h_dz0sint_custom_ass);
  hdz0sint_ass->Add(h_dz0sint_loose_ass);
  hdz0sint_ass->Add(h_dz0sint_nominal_ass);
  hdz0sint_ass->Add(h_dz0sint_tight_ass);
  hdz0sint_ass->Draw("nostack");
  hdz0sint_ass->GetXaxis()->SetTitle("|#Deltaz0sin#theta| wrt B_PVz, associated tracks [mm]");
  leg0 = new TLegend(0.65,0.78,0.95,0.94);
  leg0->AddEntry(h_dz0sint_loose_ass,"loose","l");
  leg0->AddEntry(h_dz0sint_nominal_ass,"nominal","l");
  leg0->AddEntry(h_dz0sint_tight_ass,"tight","l");
  leg0->AddEntry(h_dz0sint_runone_ass,"runone","l");
  leg0->AddEntry(h_dz0sint_custom_ass,"custom","l");
  leg0->Draw();
  c3->cd(2);
  gPad->SetLogy();gPad->SetTicky(1);
  hdz0sint_pu->Add(h_dz0sint_runone_pu);
  hdz0sint_pu->Add(h_dz0sint_custom_pu);
  hdz0sint_pu->Add(h_dz0sint_loose_pu);
  hdz0sint_pu->Add(h_dz0sint_nominal_pu);
  hdz0sint_pu->Add(h_dz0sint_tight_pu);
  hdz0sint_pu->Draw("nostack");
  hdz0sint_pu->GetXaxis()->SetTitle("|#Deltaz0sin#theta| wrt B_PVz, pileup tracks [mm]");
  leg1 = new TLegend(0.65,0.78,0.95,0.94);
  leg1->AddEntry(h_dz0sint_loose_pu,"loose","l");
  leg1->AddEntry(h_dz0sint_nominal_pu,"nominal","l");
  leg1->AddEntry(h_dz0sint_tight_pu,"tight","l");
  leg1->AddEntry(h_dz0sint_runone_pu,"runone","l");
  leg1->AddEntry(h_dz0sint_custom_pu,"custom","l");
  leg1->Draw();
  c3->cd(3);
  gPad->SetLogy();gPad->SetTicky(1);
  hdz0sint_una->Add(h_dz0sint_loose_una);
  hdz0sint_una->Add(h_dz0sint_nominal_una);
  hdz0sint_una->Add(h_dz0sint_tight_una);
  hdz0sint_una->Draw("nostack");
  hdz0sint_una->GetXaxis()->SetTitle("|#Deltaz0sin#theta| wrt B_PVz, unassociated tracks [mm]");
  leg2 = new TLegend(0.65,0.78,0.95,0.94);
  leg2->AddEntry(h_dz0sint_loose_una,"loose","l");
  leg2->AddEntry(h_dz0sint_nominal_una,"nominal","l");
  leg2->AddEntry(h_dz0sint_tight_una,"tight","l");
  leg2->Draw();
  //  c3->SaveAs("absdz0sintall_"+suf+".root");
  c3->SaveAs("absdz0sintall_"+suf+".eps");  


  TCanvas* c4 = new TCanvas("trketa","track #eta for different trk associations",900,600);
  c4->Divide(2,2);
  c4->cd(1);
  gPad->SetLogy();gPad->SetTicky(1);
  heta_ass->Add(h_eta_runone_ass);
  heta_ass->Add(h_eta_custom_ass);
  heta_ass->Add(h_eta_loose_ass);
  heta_ass->Add(h_eta_nominal_ass);
  heta_ass->Add(h_eta_tight_ass);
  heta_ass->Draw("nostack");
  heta_ass->GetXaxis()->SetTitle("track #eta, associated tracks");
  leg0 = new TLegend(0.65,0.78,0.95,0.94);
  leg0->AddEntry(h_eta_loose_ass,"loose","l");
  leg0->AddEntry(h_eta_nominal_ass,"nominal","l");
  leg0->AddEntry(h_eta_tight_ass,"tight","l");
  leg0->AddEntry(h_eta_runone_ass,"runone","l");
  leg0->AddEntry(h_eta_custom_ass,"custom","l");
  leg0->Draw();
  c4->cd(2);
  gPad->SetLogy();gPad->SetTicky(1);
  heta_pu->Add(h_eta_runone_pu);
  heta_pu->Add(h_eta_custom_pu);
  heta_pu->Add(h_eta_loose_pu);
  heta_pu->Add(h_eta_nominal_pu);
  heta_pu->Add(h_eta_tight_pu);
  heta_pu->Draw("nostack");
  heta_pu->GetXaxis()->SetTitle("track #eta, pileup tracks");
  leg1 = new TLegend(0.65,0.78,0.95,0.94);
  leg1->AddEntry(h_eta_loose_pu,"loose","l");
  leg1->AddEntry(h_eta_nominal_pu,"nominal","l");
  leg1->AddEntry(h_eta_tight_pu,"tight","l");
  leg1->AddEntry(h_eta_runone_pu,"runone","l");
  leg1->AddEntry(h_eta_custom_pu,"custom","l");
  leg1->Draw();
  c4->cd(3);
  gPad->SetLogy();gPad->SetTicky(1);
  heta_una->Add(h_eta_loose_una);
  heta_una->Add(h_eta_nominal_una);
  heta_una->Add(h_eta_tight_una);
  heta_una->Draw("nostack");
  heta_una->GetXaxis()->SetTitle("track #eta, unassociated tracks");
  leg2 = new TLegend(0.65,0.78,0.95,0.94);
  leg2->AddEntry(h_eta_loose_una,"loose","l");
  leg2->AddEntry(h_eta_nominal_una,"nominal","l");
  leg2->AddEntry(h_eta_tight_una,"tight","l");
  leg2->Draw();
  c4->SaveAs("trketaall_"+suf+".eps");  

  
  fs->Close();
  delete fs;
}
