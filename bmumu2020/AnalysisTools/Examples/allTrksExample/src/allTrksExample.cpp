//
// example how to read all track ntuples
//
// iskander(dot)ibragimov(at)cern(dot)ch
// 
// 
//  

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

  TString fsname("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/skimmed_ntup/data17/Bmumu/v4/user.ibragimo.18611470.Bmumu._000018.root");
  //  TString fsname("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/skimmed_ntup/user.ibragimo.mc16d_13TeV.300426.Bs_mu3p5mu3p5.DAOD_BPHY8.e4889_s3126_r10201_p3793_NTUP_atrkwhits/v3/user.ibragimo.17799416.Bmumu._000002.root");
  //  TString fsname("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/final_ntup/user.ibragimo.mc16a_13TeV.300426.Bs_mu3p5mu3p5.DAOD_BPHY8.e4889_s3126_r9364_p3793_NTUP_atrkwhits/v3/LASTskim.user.ibragimo.17799339.Bmumu._000002.root");
  //  TString fsname("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/final_ntup/data17/Bmumu/v3/LASTskim.user.ibragimo.17799201.Bmumu._000020.root");


  //TString fsname("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/final_ntup/data17/Bmumu/v3/LASTskim.data17_run339849.Bmumu.All.root");
  //TString fsname("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/final_ntup/user.ibragimo.mc16d_13TeV.300426.Bs_mu3p5mu3p5.DAOD_BPHY8.e4889_s3126_r10201_p3793_NTUP_atrkwhits/v3/LASTskim.mc16d_run339849.Bs_mu3p5mu3p5.Bmumu.All.root");



  //TString fsname("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/skimmed_ntup/user.ibragimo.mc16a_13TeV.300426.Bs_mu3p5mu3p5.DAOD_BPHY8.e4889_s3126_r9364_p3793_NTUP_atrkwhits/v3/user.ibragimo.17799339.Bmumu._000005.root");
  //TString fsname("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/skimmed_ntup/data16/Bmumu/v3/user.ibragimo.17799287.Bmumu._000011.root");

  //TString fsname("/afs/cern.ch/user/i/ibragimo/AnalysisCode/build/x86_64-slc6-gcc62-opt/jobOptions/BsmumuNtupleMaker/bsmumu_mc.root");
  //TString fsname("/afs/cern.ch/user/i/ibragimo/AnalysisCode/build/x86_64-centos7-gcc62-opt/jobOptions/BsmumuNtupleMaker/bpJpsiK.root");
  //TString fsname("/afs/cern.ch/user/i/ibragimo/AnalysisCode/build/x86_64-centos7-gcc62-opt/jobOptions/BsmumuNtupleMaker/bsjpsiphi.root");
  const bool doIsoStudy  = false; 
  const bool doPUStudy   = false;
  const bool doHitsStudy = false;
  const bool doChi2Study = true;

  TFile *fs  = new TFile(fsname);
  TTree *ts  = (TTree*)fs->Get("T_mv");
  TTree *tev = (TTree*)fs->Get("EventInfo");
  
  // variables related to PV container
  //
  v_uint   *pv_type               = 0;
  v_float  *pv_z                  = 0;
  v_float  *pv_sigma_z            = 0;
  tev->SetBranchAddress("pv_z", &pv_z);               // z position of primary vertices
  tev->SetBranchAddress("pv_sigma_z", &pv_sigma_z);   // sigma_z of primary vertices
  tev->SetBranchAddress("pv_type", &pv_type);         // type of primary vertices (1,3 or 0 - the last one in the container)

  // variables related to ID track container
  //
  v_uint   *idtrk_pvidx           = 0;
  v_uint   *idtrk_pvidx_loose     = 0;
  v_uint   *idtrk_pvidx_nominal   = 0;
  v_uint   *idtrk_pvidx_tight     = 0;
  v_uint   *idtrk_pvidx_custom    = 0;
  v_uint   *idtrk_pvtype          = 0;
  v_int    *idtrk_isTightPrimary  = 0;
  v_int    *idtrk_nPIXhits  = 0;
  v_int    *idtrk_NIBLayer  = 0;
  v_int    *idtrk_nSCThits  = 0;
  v_int    *idtrk_nPIXDead  = 0;
  v_int    *idtrk_nSCTDead  = 0;
  v_double *idtrk_px    = 0;
  v_double *idtrk_py    = 0;
  v_double *idtrk_pz    = 0;
  v_double *idtrk_d0    = 0;
  v_float  *idtrk_mintrksChi2 = 0;
  tev->SetBranchAddress("idtrk_pvidx", &idtrk_pvidx); // index of association of ID track to PV,
                                                      // i.e. the position of the corresponding PV in the vertex contaner
                                                      // if the position is the last position in the containter (PV type 0),
                                                      // that means that the track has not been associated to any PV.
                                                      // ( currently filled with info whether the track has been used in PV fit,  
                                                      // which is not recommended to be used by the vertex group )
  tev->SetBranchAddress("idtrk_pvidx_loose", &idtrk_pvidx_loose);     // same as above but for official loose WP
  tev->SetBranchAddress("idtrk_pvidx_nominal", &idtrk_pvidx_nominal); // same as above but for official nominal WP
  tev->SetBranchAddress("idtrk_pvidx_tight", &idtrk_pvidx_tight);     // same as above but for official tight WP
  tev->SetBranchAddress("idtrk_pvidx_custom", &idtrk_pvidx_custom);     // same as above but for official custom WP
  tev->SetBranchAddress("idtrk_px", &idtrk_px);       // momenta of all ID tracks
  tev->SetBranchAddress("idtrk_py", &idtrk_py);
  tev->SetBranchAddress("idtrk_pz", &idtrk_pz);

  tev->SetBranchAddress("idtrk_d0", &idtrk_d0);

  tev->SetBranchAddress("idtrk_pvtype", &idtrk_pvtype);                  // type of the associated PV (to ID track)
  tev->SetBranchAddress("idtrk_isTightPrimary", &idtrk_isTightPrimary);  // flag if ID track passes isTightPrimary selection criteria
  tev->SetBranchAddress("idtrk_nPIXhits", &idtrk_nPIXhits);    // nPIX hits
  tev->SetBranchAddress("idtrk_NIBLayer", &idtrk_NIBLayer);    // nIBL hits
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
  v_float *B_PV_trksd0ErrPV = 0;
  v_float *B_PV_trksz0ErrPV = 0;
  v_float *B_VTX_trksChi2=0;
  v_float *B_VTX_trksChi2trkspart=0;
  v_float *closeTrkDOCA_alltrks=0;
  v_float *closeTrkDCA_alltrks=0;
  v_float *closeTrkZCA_alltrks=0;
  v_float *closeTrkDCAErr_alltrks=0;
  v_float *closeTrkDCAErr1_alltrks=0;
  v_float *closeTrkDCAErr2_alltrks=0;
  v_float *closeTrkZCAErr_alltrks=0;
  v_float *closeTrkZCAErr1_alltrks=0;
  v_float *closeTrkZCAErr2_alltrks=0;
  v_float *closeTrkZCAErr3_alltrks=0;
  int closeTrkNtrksChi2(0);
  float closeTrkDCA(0.);
  float closeTrkZCA(0.);
  float closeTrkDCAErr(0.);
  float closeTrkZCAErr(0.);
  float B_iso_7_Chi2_5_LoosePt05(0.), B_iso_7_Chi2_2_TTVA_trkR1, B_iso_10_Chi2_2_TTVA_trkR1, B_iso_varcone_Chi2_2_TTVA_trkR1, B_iso_alaR1;
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
  //  ts->SetBranchAddress("B_PV_trksd0ErrPV",&B_PV_trksd0ErrPV);
  //ts->SetBranchAddress("B_PV_trksz0ErrPV",&B_PV_trksz0ErrPV);

  // variables for the close track studies
  //
  ts->SetBranchAddress("B_VTX_trksChi2",&B_VTX_trksChi2);                // chi2 of each track to the B vertex
  //ts->SetBranchAddress("B_VTX_trksChi2trkspart",&B_VTX_trksChi2trkspart);// chi2 of each track to the B vertex using only errors from track parameters
  ts->SetBranchAddress("closeTrkDOCA_alltrks",&closeTrkDOCA_alltrks);    // DOCA of each track to B vertex
  /*
  ts->SetBranchAddress("closeTrkDCA_alltrks",&closeTrkDCA_alltrks);
  ts->SetBranchAddress("closeTrkZCA_alltrks",&closeTrkZCA_alltrks);
  ts->SetBranchAddress("closeTrkDCAErr_alltrks",&closeTrkDCAErr_alltrks);
  ts->SetBranchAddress("closeTrkDCAErr1_alltrks",&closeTrkDCAErr1_alltrks);
  ts->SetBranchAddress("closeTrkDCAErr2_alltrks",&closeTrkDCAErr2_alltrks);
  ts->SetBranchAddress("closeTrkZCAErr_alltrks",&closeTrkZCAErr_alltrks);
  ts->SetBranchAddress("closeTrkZCAErr1_alltrks",&closeTrkZCAErr1_alltrks);
  ts->SetBranchAddress("closeTrkZCAErr2_alltrks",&closeTrkZCAErr2_alltrks);
  ts->SetBranchAddress("closeTrkZCAErr3_alltrks",&closeTrkZCAErr3_alltrks);
  */
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


  TH1F* h_chi2_all(NULL); TH1F* h_chi2(NULL); TH1I* h_ntrks(NULL); TH1I* h_ntrks_orig(NULL); TH1I* h_ntrksDxAOD(NULL);
  TH1F* h_chi2_loose(NULL); TH1F* h_chi2_nominal(NULL); TH1F* h_chi2_tight(NULL); TH1F* h_chi2_custom(NULL);
  TH1F* h_chi2_1(NULL); TH1F* h_chi2_2(NULL); TH1F* h_chi2_3(NULL);
  TH1F* h_iso_def(NULL); TH1F* h_iso_0p7(NULL); TH1F* h_iso_1p0(NULL); TH1F* h_iso_dyn(NULL); TH1F* h_iso_alar1(NULL); 
  TH1F* h_d0(NULL);
  TH1F* h_dca(NULL); TH1F* h_zca(NULL); TH1F* h_dcaerr(NULL); TH1F* h_zcaerr(NULL);
  TH1F* h_dca_orig(NULL); TH1F* h_zca_orig(NULL); TH1F* h_dcaerr_orig(NULL); TH1F* h_zcaerr_orig(NULL);
  TH1F* h_dcaerr1(NULL); TH1F* h_dcaerr2(NULL); TH1F* h_zcaerr1(NULL); TH1F* h_zcaerr2(NULL); TH1F* h_zcaerr3(NULL);
  TH1F* h_PVxyErr(NULL); TH1F* h_PVzErr(NULL);
  TH1F* h_ph_loose(NULL); TH1F* h_ph_tight(NULL); TH1F* h_ih_loose(NULL); TH1F* h_ih_tight(NULL); TH1F* h_sh_loose(NULL); TH1F* h_sh_tight(NULL);
  TH1F* h_ph_r1(NULL); TH1F* h_ph_r2(NULL); TH1F* h_ih_r1(NULL); TH1F* h_ih_r2(NULL); TH1F* h_sh_r1(NULL); TH1F* h_sh_r2(NULL);
  THStack *hderr = new THStack("hderr","DCA errors");
  THStack *hzerr = new THStack("hzerr","ZCA errors");
  THStack *hchi2PV = new THStack("hchi2PV","unassociated PVs, mc16d");
  THStack *hisoAll = new THStack("hisoAll","B isolation, data17");
  THStack *hPIX = new THStack("hPIX","pix hits, dt17"); 
  THStack *hIBL = new THStack("hIBL","ibl hits, dt17");
  THStack *hSCT = new THStack("hSCT","sct hits, dt17");
  if (doIsoStudy) {
    h_iso_def      = new TH1F("h_iso_def","B isolation def",50,0.01,1.01);
    h_iso_def->SetLineColor(kBlack);
    h_iso_0p7      = new TH1F("h_iso_0p7","B isolation 0p7",50,0.01,1.01);
    h_iso_0p7->SetLineColor(kRed);
    h_iso_1p0      = new TH1F("h_iso_1p0","B isolation 1p0",50,0.01,1.01);
    h_iso_1p0->SetLineColor(kBlue);
    h_iso_dyn      = new TH1F("h_iso_dyn","B isolation dyn",50,0.01,1.01);
    h_iso_dyn->SetLineColor(kGreen+2);
    h_iso_alar1    = new TH1F("h_iso_alar1","B isolation alar1",50,0.01,1.01);
    h_iso_alar1->SetLineColor(kCyan);
    //h_d0       = new TH1F("h_d0","d0 of tracks",200,-10,10);
  } else if (doChi2Study) {
    h_chi2_all = new TH1F("h_chi2_all","chi2 to ass. PV for all tracks",200,-10,15);
    h_chi2     = new TH1F("h_chi2","min chi2 to associated PV for selected tracks",200,-10,15);
    h_chi2_loose = new TH1F("h_chi2_loose","chi2 to ass. PV for all tracks, loose TTVA",200,-10,15);
    h_chi2_loose->SetLineColor(kRed);
    h_chi2_nominal = new TH1F("h_chi2_nominal","chi2 to ass. PV for all tracks, nominal TTVA",200,-10,15);
    h_chi2_nominal->SetLineColor(kGreen+2);
    h_chi2_tight = new TH1F("h_chi2_tight","chi2 to ass. PV for all tracks, tight TTVA",200,-10,15);
    h_chi2_tight->SetLineColor(kBlue);
    h_chi2_custom = new TH1F("h_chi2_custom","chi2 to ass. PV for all tracks, custom TTVA",200,-10,15);
    h_chi2_custom->SetLineColor(kCyan);
  } else if (doHitsStudy) {
    h_ph_loose = new TH1F("h_ph_loose","pixel hits loose tracks",10,-0.5,9.5);
    h_ph_loose->SetLineColor(kRed);
    h_ph_tight = new TH1F("h_ph_tight","pixel hits tight tracks",10,-0.5,9.5);
    h_ph_tight->SetLineColor(kBlue);
    h_ph_r1 = new TH1F("h_ph_r1","pixel hits r1 tracks",10,-0.5,9.5);
    h_ph_r1->SetLineColor(kGreen+2);
    h_ph_r2 = new TH1F("h_ph_r2","pixel hits r2 tracks",10,-0.5,9.5);
    h_ph_r2->SetLineColor(kBlack);

    h_ih_loose = new TH1F("h_ih_loose","ibl hits loose tracks",5,-0.5,4.5);
    h_ih_loose->SetLineColor(kRed);
    h_ih_tight = new TH1F("h_ih_tight","ibl hits tight tracks",5,-0.5,4.5);
    h_ih_tight->SetLineColor(kBlue);
    h_ih_r1 = new TH1F("h_ih_r1","ibl hits r1 tracks",5,-0.5,4.5);
    h_ih_r1->SetLineColor(kGreen+2);
    h_ih_r2 = new TH1F("h_ih_r2","ibl hits r2 tracks",5,-0.5,4.5);
    h_ih_r2->SetLineColor(kBlack);


    h_sh_loose = new TH1F("h_sh_loose","sct hits loose tracks",15,-0.5,14.5);
    h_sh_loose->SetLineColor(kRed);
    h_sh_tight = new TH1F("h_sh_tight","sct hits tight tracks",15,-0.5,14.5);
    h_sh_tight->SetLineColor(kBlue);
    h_sh_r1 = new TH1F("h_sh_r1","sct hits r1 tracks",15,-0.5,14.5);
    h_sh_r1->SetLineColor(kGreen+2);
    h_sh_r2 = new TH1F("h_sh_r2","sct hits r2 tracks",15,-0.5,14.5);
    h_sh_r2->SetLineColor(kBlack);
  } else if (doPUStudy) {

    h_chi2_1 = new TH1F("h_chi2_1","chi2 to ass. PV for all tracks, low pu",200,-10,15);
    h_chi2_1->SetLineColor(kRed);
    h_chi2_2 = new TH1F("h_chi2_2","chi2 to ass. PV for all tracks, middle pu",200,-10,15);
    h_chi2_2->SetLineColor(kGreen+2);
    h_chi2_3 = new TH1F("h_chi2_3","chi2 to ass. PV for all tracks, high pu",200,-10,15);
    h_chi2_3->SetLineColor(kBlue);


  } else {
    h_chi2_all   = new TH1F("h_chi2_all","chi2 to ass. B vertex for all tracks",200,-5,15);
    h_chi2       = new TH1F("h_chi2","chi2 to B vertex for selected tracks",200,-5,15);
    h_ntrks      = new TH1I("h_ntrks","h_ntrks",100,0,100);  
    h_ntrks->SetLineColor(kRed);
    h_ntrks_orig = new TH1I("h_ntrks_orig","h_ntrks_orig",100,0,100); 
    h_ntrks_orig->SetLineColor(kBlack);
    h_ntrksDxAOD = new TH1I("h_ntrks_ala_DxAOD","h_ntrks_ala_DxAOD",100,0,100);  
    h_ntrksDxAOD->SetLineColor(kBlue);

    h_dca = new TH1F("h_dca","dca for closest tracks",200,-1,1);
    h_dca->SetLineColor(kRed);
    h_zca = new TH1F("h_zca","zca for closest tracks",200,-3,3);
    h_zca->SetLineColor(kRed);
    h_dcaerr = new TH1F("h_dcaerr","dcaerr for closest tracks",100,0,0.5);
    h_dcaerr->SetLineColor(kRed);
    h_dcaerr1 = new TH1F("h_dcaerr1","dcaerr1 for closest tracks",100,0,0.5);
    h_dcaerr1->SetLineColor(kGreen+2);
    h_dcaerr2 = new TH1F("h_dcaerr2","dcaerr2 for closest tracks",100,0,0.5);
    h_dcaerr2->SetLineColor(kBlue);
    h_PVxyErr = new TH1F("h_PVxyErr","h_PVxyErr for ass PV",100,0,0.5);
    h_PVxyErr->SetLineColor(kMagenta);

    h_zcaerr = new TH1F("h_zcaerr","zcaerr for closest tracks",100,0,2.5);
    h_zcaerr->SetLineColor(kRed);
    h_zcaerr1 = new TH1F("h_zcaerr1","zcaerr1 for closest tracks",100,0,2.5);
    h_zcaerr1->SetLineColor(kOrange+1);
    h_zcaerr2 = new TH1F("h_zcaerr2","zcaerr2 for closest tracks",100,0,2.5);
    h_zcaerr2->SetLineColor(kGreen+2);
    h_zcaerr3 = new TH1F("h_zcaerr3","zcaerr3 for closest tracks",100,0,2.5);
    h_zcaerr3->SetLineColor(kBlue);
    h_PVzErr = new TH1F("h_PVzErr","h_PVzErr for ass PV",100,0,2.5);
    h_PVzErr->SetLineColor(kMagenta);

    h_dca_orig = new TH1F("h_dca_orig","DCA for closest tracks",200,-1,1);
    h_dca_orig->SetLineColor(kBlack);
    h_zca_orig = new TH1F("h_zca_orig","ZCA for closest tracks",200,-3,3);
    h_zca_orig->SetLineColor(kBlack);
    h_dcaerr_orig = new TH1F("h_dcaerr_orig","dcaerr_orig for closest tracks",100,0,0.5);
    h_dcaerr_orig->SetLineColor(kBlack);
    h_zcaerr_orig = new TH1F("h_zcaerr_orig","zcaerr_orig for closest tracks",100,0,2.5);
    h_zcaerr_orig->SetLineColor(kBlack);

  }
  if (h_chi2_all) h_chi2_all->SetLineColor(kBlack);
  if (h_chi2) h_chi2->SetLineColor(kOrange);

  TFile *fout = new TFile("fout.root","recreate");
  TTree *tout = new TTree("T_mv","official name of the tree");
  TBranch *b1 = tout->Branch("Lxy",  &Lxy,  "Lxy/D");
  TBranch *b2 = tout->Branch("a_2D", &a_2D, "a_2D/D");
  TBranch *b3 = tout->Branch("ew",  &ew,  "ew/D");

  TBranch *b4 = tout->Branch("B_iso_7_Chi2_2_TTVA_trkR1",  &B_iso_7_Chi2_2_TTVA_trkR1,  "B_iso_7_Chi2_2_TTVA_trkR1/F");
  TBranch *b5 = tout->Branch("B_iso_10_Chi2_2_TTVA_trkR1",  &B_iso_10_Chi2_2_TTVA_trkR1,  "B_iso_10_Chi2_2_TTVA_trkR1/F");
  TBranch *b6 = tout->Branch("B_iso_varcone_Chi2_2_TTVA_trkR1",  &B_iso_varcone_Chi2_2_TTVA_trkR1,  "B_iso_varcone_Chi2_2_TTVA_trkR1/F");
  TBranch *b7 = tout->Branch("B_iso_alaR1",  &B_iso_alaR1,  "B_iso_alaR1/F");
  TBranch *b8 = tout->Branch("B_iso_7_Chi2_5_LoosePt05",  &B_iso_7_Chi2_5_LoosePt05,  "B_iso_7_Chi2_5_LoosePt05/F");

  TBranch *b9 = tout->Branch("B_MUCALC_mass",  &B_MUCALC_mass,  "B_MUCALC_mass/F");
  TBranch *b10 = tout->Branch("B_pT",  &B_pT,  "B_pT/D");
  TBranch *b11 = tout->Branch("B_eta",  &B_eta,  "B_eta/D");
  //  TBranch *b = tout->Branch("",  &,  "/F");


  double npu_cand[3] = {0, 0, 0};
  const double npu_cand_max = 1895.;//3400.;

  for (auto ievent=0; ievent<nevents; ievent++)
    {
      if (ievent%100000==0) cout << "Processing event "<< ievent << endl;
      ts->GetEntry(ievent);

      if (!fsname.Contains("mc16") && (B_MUCALC_mass<0) ) continue;

				       //B_MUCALC_mass>5166.0
      ew = Muon1_reco_eff_sf*Muon2_reco_eff_sf*PVWeights;


      int b1r = 31; //30;  
      int b2l = 31; //35;
      int b2r = 42; //45;
      int b3l = 42; //50;
      if (doPUStudy) { //comment out if you do
	if ( PRIVX_mu<=b1r && npu_cand[0]>=npu_cand_max )                 continue;
	if ( PRIVX_mu>b2l  && PRIVX_mu<=b2r && npu_cand[1]>=npu_cand_max ) continue;
	if ( PRIVX_mu>b3l  && npu_cand[2]>=npu_cand_max )                 continue;
	if ( (PRIVX_mu>b1r && PRIVX_mu<=b2l) || (PRIVX_mu>b2r && PRIVX_mu<=b3l)) continue;
	
	if ( PRIVX_mu<=b1r ) { //30
	  npu_cand[0] += ew;
	} else if ( PRIVX_mu>b2l && PRIVX_mu<=b2r ) { //35-45 FIXME
	  npu_cand[1] += ew;
	} else if ( PRIVX_mu>b3l ) { //50 FIXME
	  npu_cand[2] += ew;
	}
      }

      TVector3 B_p;
      B_p.SetPtEtaPhi(B_pT, B_eta, B_phi);
    
      tev->GetEntry(event_index);
     
      auto ntrks = B_PV_trksChi2->size();
      if ((*idtrk_pvidx).size() != ntrks) {
	cout << "FATAL: ID trk info size unequal in event and candidate trees, exiting. " << (*idtrk_pvidx).size() << " <-ev|cand-> " << ntrks << " event: "<< ievent << endl;
	exit(0);
      }

      if ( Npv != pv_type->size()-1 ) {
	cout << "WARNING: smth is wrong with Npv, continuing. " << pv_type->size()-1 << " <-ev|cand-> " << Npv << " event: "<< ievent << endl;
      }

      if ( (*idtrk_mintrksChi2).size() != (*B_PV_trksChi2).size() ) {
	cout << "smth is wrong now: "<< (*idtrk_mintrksChi2).size() << " vs " << (*B_PV_trksChi2).size() << endl;  
      }

      int nclosetrks(0); int nclosetrksDxAOD(0);
      float docamin(999.0); float dca(999.0); float zca(999.0); float dcaerr(999.0); float zcaerr(999.0);
      float dcaerr1(999.0); float dcaerr2(999.0); float zcaerr1(999.0); float zcaerr2(999.0); float zcaerr3(999.0);
      float PVxyErr(999.0); float PVzErr(999.0);
      float DOCA = sqrt( pow(closeTrkDCA, 2) + pow(closeTrkZCA, 2) );
      map<string, bool> associated;
      map<string, bool> pileup;
      map<string, bool> unassociated;
      associated.insert(pair<string, bool>("loose", false));
      associated.insert(pair<string, bool>("nominal", false));
      associated.insert(pair<string, bool>("tight", false));
      associated.insert(pair<string, bool>("custom", false));
      unassociated.insert(pair<string, bool>("loose", false));
      unassociated.insert(pair<string, bool>("nominal", false));
      unassociated.insert(pair<string, bool>("tight", false));
      pileup.insert(pair<string, bool>("loose", false));
      pileup.insert(pair<string, bool>("nominal", false));
      pileup.insert(pair<string, bool>("tight", false));
      pileup.insert(pair<string, bool>("custom", false));

      double ptsum_0p7(0.), ptsum_1p0(0.), ptsum_dyn(0.), ptsum_alar1(0.);

      for (unsigned int idx=0; idx<ntrks; idx++) {

	// skip signal tracks (Bsmumu channel as an example, add other tracks for other signatures!)
	//
	if ( (idx == B_IDtrk1_trkidx || idx == B_IDtrk2_trkidx) ) continue;

	// select tracks by vertex association
	// 
	if ( (*idtrk_pvidx_loose).at(idx) == B_PV_idx ) {
	  associated["loose"]    = true;
	  pileup["loose"]        = false;
	  unassociated["loose"] = false;
	} else if ( (*idtrk_pvidx_loose).at(idx) == pv_type->size()-1 ) {
	  associated["loose"]    = false;
	  pileup["loose"]        = false;
	  unassociated["loose"] = true;
	} else {
	  associated["loose"]    = false;
	  pileup["loose"]        = true;
	  unassociated["loose"] = false;
	}
	
	if ( (*idtrk_pvidx_nominal).at(idx) == B_PV_idx ) {
	  associated["nominal"]    = true;
	  pileup["nominal"]        = false;
	  unassociated["nominal"] = false;
	} else if ( (*idtrk_pvidx_nominal).at(idx) == pv_type->size()-1 ) {
	  associated["nominal"]    = false;
	  pileup["nominal"]        = false;
	  unassociated["nominal"] = true;
	} else {
	  associated["nominal"]    = false;
	  pileup["nominal"]        = true;
	  unassociated["nominal"] = false;
	}
	
	if ( (*idtrk_pvidx_tight).at(idx) == B_PV_idx ) {
	  associated["tight"]    = true;
	  pileup["tight"]        = false;
	  unassociated["tight"] = false;
	} else if ( (*idtrk_pvidx_tight).at(idx) == pv_type->size()-1 ) {
	  associated["tight"]    = false;
	  pileup["tight"]        = false;
	  unassociated["tight"] = true;
	} else {
	  associated["tight"]    = false;
	  pileup["tight"]        = true;
	  unassociated["tight"] = false;
	}

	if ( (*idtrk_pvidx_custom).at(idx) == B_PV_idx ) {
	  associated["custom"]    = true;
	  pileup["custom"]        = false;
	  unassociated["custom"]  = false;
	} else if ( (*idtrk_pvidx_custom).at(idx) == pv_type->size()-1 ) {
	  associated["custom"]    = false;
	  pileup["custom"]        = false;
	  unassociated["custom"]  = true;
	} else {
	  associated["custom"]    = false;
	  pileup["custom"]        = true;
	  unassociated["custom"]  = false;
	}
	  

	if (doIsoStudy) {
	  if ( ( (*idtrk_nPIXhits).at(idx) + (*idtrk_nPIXDead).at(idx) )>=1 && ( (*idtrk_nSCThits).at(idx) + (*idtrk_nSCTDead).at(idx) )>=2 ) { // trk quality a la Run 1
	    TVector3 idtrk_p;
	    idtrk_p.SetXYZ( (*idtrk_px).at(idx), (*idtrk_py).at(idx), (*idtrk_pz).at(idx) );
	    double deltaR = B_p.DeltaR(idtrk_p);
	    double dynsize = min(10000./B_pT, 1.0);

	    if ( associated["tight"] || (unassociated["tight"] && (*B_VTX_trksChi2).at(idx) < 2.0) ) {
	      if (deltaR<0.7)     ptsum_0p7 += idtrk_p.Pt();
	      if (deltaR<1.0)     ptsum_1p0 += idtrk_p.Pt();
	      if (deltaR<dynsize) ptsum_dyn += idtrk_p.Pt();
	    }
	    if ( (*B_PV_trksChi2).at(idx) < 5.0 && deltaR<0.7) {
	      ptsum_alar1 += idtrk_p.Pt();
	    }
	  }

	} else if (doChi2Study) { 	// fill chi2 histogram
	  if (unassociated["loose"]) {
	    h_chi2_loose->Fill( (*B_PV_trksChi2).at(idx) );
	  } 
	  if (unassociated["nominal"]) {
	    h_chi2_nominal->Fill( (*B_PV_trksChi2).at(idx) );
	  } 
	  if (unassociated["tight"]) {
	    h_chi2_tight->Fill( (*B_PV_trksChi2).at(idx) );
	  }
	  if (unassociated["custom"]) {
	    h_chi2_custom->Fill( (*B_PV_trksChi2).at(idx) );
	  }
	  h_chi2->Fill( (*idtrk_mintrksChi2).at(idx) );
	  /*
	  if ( (*idtrk_pvidx).at(idx) != B_PV_idx && (*idtrk_pvidx).at(idx) != pv_type->size()-1 ) {
	    h_chi2->Fill( (*B_PV_trksChi2).at(idx) );
	  }
	  */
	} else if (doHitsStudy) {
	  h_ph_loose->Fill( (*idtrk_nPIXhits).at(idx) );
	  h_ih_loose->Fill( (*idtrk_NIBLayer).at(idx) );
	  h_sh_loose->Fill( (*idtrk_nSCThits).at(idx) );
	  if ( (*idtrk_isTightPrimary).at(idx) ) {
	    h_ph_tight->Fill( (*idtrk_nPIXhits).at(idx) );
	    h_ih_tight->Fill( (*idtrk_NIBLayer).at(idx) );
	    h_sh_tight->Fill( (*idtrk_nSCThits).at(idx) );
	  }
	  if ( ((*idtrk_nPIXhits).at(idx) + (*idtrk_nPIXDead).at(idx) - (*idtrk_NIBLayer).at(idx))>=1 && ( (*idtrk_nSCThits).at(idx) + (*idtrk_nSCTDead).at(idx) )>=2 ) { //FIXME subtract dead IBL if exists
	    h_ph_r1->Fill( (*idtrk_nPIXhits).at(idx) );
	    h_ih_r1->Fill( (*idtrk_NIBLayer).at(idx) );
	    h_sh_r1->Fill( (*idtrk_nSCThits).at(idx) );
	  }

	  if ( ( (*idtrk_nPIXhits).at(idx) + (*idtrk_nPIXDead).at(idx) )>=1 && ( (*idtrk_nSCThits).at(idx) + (*idtrk_nSCTDead).at(idx) )>=2 ) {
	    h_ph_r2->Fill( (*idtrk_nPIXhits).at(idx) );
	    h_ih_r2->Fill( (*idtrk_NIBLayer).at(idx) );
	    h_sh_r2->Fill( (*idtrk_nSCThits).at(idx) );
	  }
	} else if (doPUStudy) {
	  if ( ( (*idtrk_nPIXhits).at(idx) + (*idtrk_nPIXDead).at(idx) )>=1 && ( (*idtrk_nSCThits).at(idx) + (*idtrk_nSCTDead).at(idx) )>=2 ) {
	    TVector3 idtrk_p;
	    idtrk_p.SetXYZ( (*idtrk_px).at(idx), (*idtrk_py).at(idx), (*idtrk_pz).at(idx) );
	    double deltaR = B_p.DeltaR(idtrk_p);
	    if (unassociated["tight"]){ //&& deltaR<0.7){ //&& (*idtrk_isTightPrimary).at(idx) ) {
	      if ( PRIVX_mu<=b1r )                     h_chi2_1->Fill( (*B_VTX_trksChi2).at(idx), ew ); 
	      else if ( PRIVX_mu>b2l && PRIVX_mu<=b2r ) h_chi2_2->Fill( (*B_VTX_trksChi2).at(idx), ew );
	      else if ( PRIVX_mu>b3l )                 h_chi2_3->Fill( (*B_VTX_trksChi2).at(idx), ew );
	    }
	  }
	}
	/*
	if ( (*idtrk_pvidx).at(idx) == B_PV_idx ) {                 // choose tracks ass. to associated PV 
	  //	     || (*idtrk_pvidx).at(idx) == pv_type->size()-1 ) { // or choose tracks ass. to other real PV's (for non-ass. tracks use '==' instead)
	 
	  if (doIsoStudy) {
	    h_chi2->Fill( (*B_PV_trksChi2).at(idx) );
	    h_d0->Fill( (*idtrk_d0).at(idx) );
	  } else {
	    h_chi2->Fill( (*B_VTX_trksChi2).at(idx) );
	  
	    if ((*B_VTX_trksChi2).at(idx)< 1.0) nclosetrks++;
	    if ((*B_VTX_trksChi2trkspart).at(idx)< 1.0) nclosetrksDxAOD++;

	    if ( (*B_VTX_trksChi2).at(idx) < 7.0) {
	      if ( (*closeTrkDOCA_alltrks).at(idx) < docamin) {
		docamin = (*closeTrkDOCA_alltrks).at(idx);
		dca = (*closeTrkDCA_alltrks).at(idx);
		zca = (*closeTrkZCA_alltrks).at(idx);
		dcaerr = (*closeTrkDCAErr_alltrks).at(idx);
		dcaerr1 = (*closeTrkDCAErr1_alltrks).at(idx);
		dcaerr2 = (*closeTrkDCAErr2_alltrks).at(idx);
		zcaerr = (*closeTrkZCAErr_alltrks).at(idx);
		zcaerr1 = (*closeTrkZCAErr1_alltrks).at(idx);
		zcaerr2 = (*closeTrkZCAErr2_alltrks).at(idx);
		zcaerr3 = (*closeTrkZCAErr3_alltrks).at(idx);
		PVxyErr = (*B_PV_trksd0ErrPV).at(idx);
		PVzErr  = (*B_PV_trksz0ErrPV).at(idx);
	      }
	    }
	  }
	}
	if (doIsoStudy) {
	  h_chi2_all->Fill( (*B_PV_trksChi2).at(idx) );
	} else {
	  h_chi2_all->Fill( (*B_VTX_trksChi2).at(idx) );
	}
	*/
      } // tracks

      if (doIsoStudy) {
	if (h_iso_def) h_iso_def->Fill( B_iso_7_Chi2_5_LoosePt05,  ew );

	B_iso_7_Chi2_2_TTVA_trkR1  = B_pT / (B_pT + ptsum_0p7);
	if (h_iso_0p7) h_iso_0p7->Fill( B_iso_7_Chi2_2_TTVA_trkR1, ew );

	B_iso_10_Chi2_2_TTVA_trkR1 = B_pT / (B_pT + ptsum_1p0);
	if (h_iso_1p0) h_iso_1p0->Fill( B_iso_10_Chi2_2_TTVA_trkR1, ew );

	B_iso_varcone_Chi2_2_TTVA_trkR1 = B_pT / (B_pT + ptsum_dyn); 
	if (h_iso_dyn) h_iso_dyn->Fill( B_iso_varcone_Chi2_2_TTVA_trkR1, ew );

	B_iso_alaR1 = B_pT / (B_pT + ptsum_alar1);
	if (h_iso_alar1) h_iso_alar1->Fill( B_iso_alaR1, ew );
	tout->Fill();


      } else if (doChi2Study) {
      } else if (doHitsStudy) {
      } else if (doPUStudy) {
      } else {
	// cout << "DOCA: " << DOCA << " <-AOD|ntup-> "<< docamin << endl; //" DCA: "<< closeTrkDCA << " ZCA: "<< closeTrkZCA << endl; 
	if (h_ntrks) h_ntrks->Fill(nclosetrks);
	if (h_ntrks_orig) h_ntrks_orig->Fill(closeTrkNtrksChi2);
	if (h_ntrksDxAOD) h_ntrksDxAOD->Fill(nclosetrksDxAOD);
	//	cout << "Ntrk: "<< closeTrkNtrksChi2 << " <-AOD|ntup-> "<< nclosetrks << endl;	 
	if (h_dca) h_dca->Fill(dca);
	if (h_zca) h_zca->Fill(zca);
	if (h_dcaerr) h_dcaerr->Fill(dcaerr);
	if (h_dcaerr1) h_dcaerr1->Fill(dcaerr1);
	if (h_dcaerr2) h_dcaerr2->Fill(dcaerr2);
	if (h_zcaerr) h_zcaerr->Fill(zcaerr);
	if (h_zcaerr1) h_zcaerr1->Fill(zcaerr1);
	if (h_zcaerr2) h_zcaerr2->Fill(zcaerr2);
	if (h_zcaerr3) h_zcaerr3->Fill(zcaerr3);
	if (h_dca_orig) h_dca_orig->Fill(closeTrkDCA);
	if (h_zca_orig) h_zca_orig->Fill(closeTrkZCA);
	if (h_dcaerr_orig) h_dcaerr_orig->Fill(closeTrkDCAErr);
	if (h_zcaerr_orig) h_zcaerr_orig->Fill(closeTrkZCAErr);
	if (h_PVxyErr) h_PVxyErr->Fill(PVxyErr);
	if (h_PVzErr) h_PVzErr->Fill(PVzErr);
      }

    } // events

  cout << "done w loops" << endl;
  cout << "control check, # of cand in pu bins: "<< endl; 
  cout << "0: " << npu_cand[0] << " 1: " << npu_cand[1] <<  " 2: " << npu_cand[2] << endl;
  TCanvas* c = new TCanvas("alltrks","alltrks",900,600);
 
  if (doIsoStudy)  {
    c->SetLogy();
    //gPad->SetPadTicksy(1);
    h_iso_def->Scale( 1./h_iso_def->Integral() );
    h_iso_0p7->Scale( 1./h_iso_0p7->Integral() );
    h_iso_1p0->Scale( 1./h_iso_1p0->Integral() );
    h_iso_dyn->Scale( 1./h_iso_dyn->Integral() );
    h_iso_alar1->Scale( 1./h_iso_alar1->Integral() );

    if (h_iso_def) hisoAll->Add(h_iso_def);
    if (h_iso_0p7) hisoAll->Add(h_iso_0p7);
    if (h_iso_1p0) hisoAll->Add(h_iso_1p0);
    if (h_iso_dyn) hisoAll->Add(h_iso_dyn);
    if (h_iso_alar1) hisoAll->Add(h_iso_alar1);
    //    hisoAll->Draw("nostackY+");
    hisoAll->Draw("nostack");
    hisoAll->GetXaxis()->SetTitle("B iso");
    TLegend *leg0 = new TLegend(0.05,0.78,0.35,0.94);
    leg0->AddEntry(h_iso_def,"default","l");
    leg0->AddEntry(h_iso_0p7,"cone 0.7","l");
    leg0->AddEntry(h_iso_1p0,"cone 1.0","l");
    leg0->AddEntry(h_iso_dyn,"dyn cone","l");
    leg0->AddEntry(h_iso_alar1,"a la r1","l");
    leg0->Draw();
    fout->cd();
    tout->Write();
    fout->Close();
  } else if (doChi2Study)  {
    c->SetLogy();
    /*
    if (h_chi2_all) h_chi2_all->Draw();
    if (h_chi2) h_chi2->Draw("same");
    */
    //if (h_d0) h_d0->Draw();
    if (h_chi2_loose) hchi2PV->Add(h_chi2_loose);
    if (h_chi2_nominal) hchi2PV->Add(h_chi2_nominal);
    if (h_chi2_tight) hchi2PV->Add(h_chi2_tight);
    if (h_chi2) hchi2PV->Add(h_chi2);
    if (h_chi2_custom) hchi2PV->Add(h_chi2_custom);
    hchi2PV->Draw("nostack");
    hchi2PV->GetXaxis()->SetTitle("chi2 to PV");
    TLegend *leg0 = new TLegend(0.05,0.78,0.35,0.94);
    leg0->AddEntry(h_chi2_loose,"loose","l");
    leg0->AddEntry(h_chi2_nominal,"nominal","l");
    leg0->AddEntry(h_chi2_tight,"tight","l");
    leg0->AddEntry(h_chi2,"minimum","l");//"not recommended","l");
    leg0->AddEntry(h_chi2_custom,"custom","l");
    leg0->Draw();
  } else if (doPUStudy) {
    c->SetLogy();
    //h_chi2_1->Scale(1./h_chi2_1->Integral() );
    //h_chi2_2->Scale(1./h_chi2_2->Integral() );
    //h_chi2_3->Scale(1./h_chi2_3->Integral() );
    if (h_chi2_1) hchi2PV->Add(h_chi2_1);
    if (h_chi2_2) hchi2PV->Add(h_chi2_2);
    if (h_chi2_3) hchi2PV->Add(h_chi2_3);
    hchi2PV->Draw("nostack");
    hchi2PV->GetXaxis()->SetTitle("chi2 to SV");
    TLegend *leg0 = new TLegend(0.05,0.78,0.35,0.94);
    leg0->AddEntry(h_chi2_1,"low pu","l");
    leg0->AddEntry(h_chi2_2,"mid pu","l");
    leg0->AddEntry(h_chi2_3,"high pu","l");
    leg0->Draw();
  } else if (doHitsStudy) {
    c->Divide(2,2);
    c->cd(1);
    gPad->SetLogy();
    if (h_ph_loose) hPIX->Add(h_ph_loose);
    if (h_ph_tight) hPIX->Add(h_ph_tight);
    if (h_ph_r1) hPIX->Add(h_ph_r1);
    if (h_ph_r2) hPIX->Add(h_ph_r2);
    hPIX->Draw("nostack");
    hPIX->GetXaxis()->SetTitle("# pix hits");
    TLegend *leg0 = new TLegend(0.05,0.78,0.35,0.94);
    leg0->AddEntry(h_ph_loose,"loose","l");
    leg0->AddEntry(h_ph_tight,"tight","l");
    leg0->AddEntry(h_ph_r1,"run 1 sel.","l");
    leg0->AddEntry(h_ph_r2,"run 2 sel.","l");
    leg0->Draw();
    c->cd(2);
    gPad->SetLogy();
    if (h_ih_loose) hIBL->Add(h_ih_loose);
    if (h_ih_tight) hIBL->Add(h_ih_tight);
    if (h_ih_r1) hIBL->Add(h_ih_r1);
    if (h_ih_r2) hIBL->Add(h_ih_r2);
    hIBL->Draw("nostack");
    hIBL->GetXaxis()->SetTitle("# ibl hits");
    c->cd(3);
    gPad->SetLogy();
    if (h_sh_loose) hSCT->Add(h_sh_loose);
    if (h_sh_tight) hSCT->Add(h_sh_tight);
    if (h_sh_r1) hSCT->Add(h_sh_r1);
    if (h_sh_r2) hSCT->Add(h_sh_r2);
    hSCT->Draw("nostack");
    hSCT->GetXaxis()->SetTitle("# sct hits");

  } else {
    if (h_ntrks_orig) h_ntrks_orig->Draw();
    if (h_ntrks) h_ntrks->Draw("same");
    if (h_ntrksDxAOD) h_ntrksDxAOD->Draw("same");
    TLegend *leg0 = new TLegend(0.58,0.78,0.95,0.94);
    leg0->AddEntry(h_ntrks_orig,"from DxAOD","l");
    leg0->AddEntry(h_ntrks,"from ntuple","l");
    leg0->AddEntry(h_ntrksDxAOD,"from ntuple, using only trk errors","l");
    leg0->Draw();
    /*
    c->cd(1);
    gPad->SetLogy();
    if (h_dca_orig) h_dca_orig->Draw();
    if (h_dca) h_dca->Draw("same");
    TLegend *leg1 = new TLegend(0.58,0.78,0.95,0.94);
    leg1->AddEntry(h_dca_orig,"from DxAOD","l");
    leg1->AddEntry(h_dca,"from ntuple","l");
    leg1->Draw();
    c->cd(2);
    gPad->SetLogy();
    if (h_zca_orig) h_zca_orig->Draw();
    if (h_zca) h_zca->Draw("same");
    TLegend *leg2 = new TLegend(0.58,0.78,0.95,0.94);
    leg2->AddEntry(h_zca_orig,"from DxAOD","l");
    leg2->AddEntry(h_zca,"from ntuple","l");
    leg2->Draw();
    c->cd(3);
    gPad->SetLogy();
    if (h_dcaerr_orig) hderr->Add(h_dcaerr_orig);
    if (h_dcaerr) hderr->Add(h_dcaerr);
    if (h_dcaerr1) hderr->Add(h_dcaerr1);
    if (h_dcaerr2) hderr->Add(h_dcaerr2);
    if (h_PVxyErr) hderr->Add(h_PVxyErr);
    hderr->Draw("nostack");
    TLegend *leg3 = new TLegend(0.58,0.65,0.95,0.94);
    leg3->AddEntry(h_dcaerr_orig,"from DxAOD","l");
    leg3->AddEntry(h_dcaerr,"from ntuple","l");
    leg3->AddEntry(h_dcaerr1,"BS->SV part","l");
    leg3->AddEntry(h_dcaerr2,"trk_d0 part","l");
    leg3->AddEntry(h_PVxyErr,"PVxyErr","l");
    leg3->Draw();
    c->cd(4);
    gPad->SetLogy();
    if (h_zcaerr_orig) hzerr->Add(h_zcaerr_orig);
    if (h_zcaerr) hzerr->Add(h_zcaerr);
    if (h_zcaerr1) hzerr->Add(h_zcaerr1);
    if (h_zcaerr2) hzerr->Add(h_zcaerr2);
    if (h_zcaerr3) hzerr->Add(h_zcaerr3);
    if (h_PVzErr) hzerr->Add(h_PVzErr);
    hzerr->Draw("nostack");
    TLegend *leg4 = new TLegend(0.58,0.65,0.95,0.94);
    leg4->AddEntry(h_zcaerr_orig,"from DxAOD","l");
    leg4->AddEntry(h_zcaerr,"from ntuple","l");
    leg4->AddEntry(h_zcaerr1,"SVz part","l");
    leg4->AddEntry(h_zcaerr2,"BS->SV part","l");
    leg4->AddEntry(h_zcaerr3,"trk_z0 part","l");
    leg4->AddEntry(h_PVzErr,"PVzErr","l");
    leg4->Draw();
    */
  }

  c->SaveAs("chi2.root");
  c->SaveAs("chi2.eps");  
  fs->Close();
  delete fs;
}
