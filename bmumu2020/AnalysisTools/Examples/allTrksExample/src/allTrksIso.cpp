//
// produce small flat ntuples
// with isolation variables computed
// from ntuples w/ all track informaion
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
  if (suf.Contains("data17Bsv5")) {
    fsname = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/final_ntup/data17/Bmumu/v5/LASTskim.data17_run339849.Bmumu.Allv5.root";
  } else if (suf.Contains("data17Bp")) {
    fsname = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/final_ntup/data17/BJpsiK/v3/LASTskim.data17_run339849.BJpsiK.Allmu6mu4.root";
  } else if (suf.Contains("data16Bs")) {
    fsname = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/final_ntup/data16/Bmumu/v4/LASTskim.data16_run302393.Bmumu.Allmu6mu4_v4.root";
  } else if (suf.Contains("data16Bj")) {
    fsname = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/final_ntup/data16/BsJpsiPhi/v4/LASTskim.data16_run302393.BsJpsiPhi.Allmu6mu4_v4.root";
  } else if (suf.Contains("data16Bp")) {
    fsname = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/final_ntup/data16/BJpsiK/v4/LASTskim.data16_run302393.BJpsiK.Allmu6mu4_v4.root";
  } else if (suf.Contains("dtwpverr")) {
    fsname = "/afs/cern.ch/user/i/ibragimo/skimmed_ntup_dt/dt_bsmumu_wpverr.root";
  } else if (suf.Contains("dtnopverr")) {
    fsname = "/afs/cern.ch/user/i/ibragimo/skimmed_ntup_dt/dt_bsmumu_nopverr.root";
  } else if (suf.Contains("mcwpverr")) {
    fsname = "/afs/cern.ch/user/i/ibragimo/skimmed_ntup/mc_bsmumu_wpverr.root";
  } else if (suf.Contains("mcnopverr")) {
    fsname = "/afs/cern.ch/user/i/ibragimo/skimmed_ntup/mc_bsmumu_nopverr.root";
  } else if (suf.Contains("mc16a")) {
    fsname = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/final_ntup/user.ibragimo.mc16a_13TeV.300426.Bs_mu3p5mu3p5.DAOD_BPHY8.e4889_s3126_r9364_p3793_NTUP_atrkwhits/v4/LASTskim.mc16a.Bs_mu3p5mu3p5.Bmumu.Allv4.root";
  } else if (suf.Contains("mc16dv5")) {
    fsname = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/final_ntup/user.ibragimo.mc16d_13TeV.300426.Bs_mu3p5mu3p5.DAOD_BPHY8.e4889_s3126_r10201_p3793_NTUP_atrkwhits/v5/LASTskim.mc16d_run339849.Bs_mu3p5mu3p5.Bmumu.Allv5.root";
  } else if (suf.Contains("mc16e")) {
    fsname = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/final_ntup/user.ibragimo.mc16e_13TeV.300426.Bs_mu3p5mu3p5.DAOD_BPHY8.e4889_s3126_r10724_p3793_NTUP_atrkwhits/v4/LASTskim.mc16e.Bs_mu3p5mu3p5.Bmumu.Allv4.root";
  } else if (suf.Contains("bbmumuX16a")) {
    fsname = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/final_ntup/bbmumuX16a/v4/LASTskim.bbmumuX.Bmumu.Allmu6mu4_v5.root";
  } else {
    cout << "input unknown, exiting" << endl;
    exit(1);
  }
  TFile *fs  = new TFile(fsname);
  TTree *ts  = (TTree*)fs->Get("T_mv");
  bool isMC(false);
  if (ts->GetBranch("TRUTH_B_pT")) isMC=true;
  cout << "INFO: isMC flat set to " << isMC << endl;  
  TTree *tev = (TTree*)fs->Get("EventInfo");
  
  // variables related to PV container
  //
  v_uint   *pv_type               = 0;
  tev->SetBranchAddress("pv_type", &pv_type);         // type of primary vertices (1,3 or 0 - the last one in the container)

  // variables related to ID track container
  //
  v_uint   *idtrk_pvidx_lastround = 0;
  v_uint   *idtrk_pvidx_custom    = 0;
  v_uint   *idtrk_pvidx_loose     = 0;
  v_uint   *idtrk_pvidx_nominal   = 0;
  v_uint   *idtrk_pvidx_tight     = 0;

  v_int    *idtrk_isLoose   = 0;
  v_int    *idtrk_nPIXhits  = 0;
  v_int    *idtrk_nSCThits  = 0;
  v_int    *idtrk_nPIXDead  = 0;
  v_int    *idtrk_nSCTDead  = 0;
  v_int    *idtrk_nPIXHoles = 0;
  v_int    *idtrk_nSCTHoles = 0;
  v_float  *idtrk_px    = 0;
  v_float  *idtrk_py    = 0;
  v_float  *idtrk_pz    = 0;
  v_float  *idtrk_mintrksChi2 = 0;
  tev->SetBranchAddress("idtrk_pvidx", &idtrk_pvidx_lastround); // index of association of ID track to PV,
                                                      // i.e. the position of the corresponding PV in the vertex contaner
                                                      // if the position is the last position in the containter (PV type 0),
                                                      // that means that the track has not been associated to any PV.
                                                      // ( currently filled with info whether the track has been used in PV fit,  
                                                      // which is not recommended to be used by the vertex group )
  tev->SetBranchAddress("idtrk_pvidx_custom", &idtrk_pvidx_custom);   // same as above but for official custom WP
  tev->SetBranchAddress("idtrk_pvidx_loose", &idtrk_pvidx_loose);     // same as above but for official loose WP
  tev->SetBranchAddress("idtrk_pvidx_nominal", &idtrk_pvidx_nominal); // same as above but for official nominal WP
  tev->SetBranchAddress("idtrk_pvidx_tight", &idtrk_pvidx_tight);     // same as above but for official tight WP
  tev->SetBranchAddress("idtrk_isLoose", &idtrk_isLoose);             // ensure loose track selection
  tev->SetBranchAddress("idtrk_px", &idtrk_px);                       // momenta of all ID tracks
  tev->SetBranchAddress("idtrk_py", &idtrk_py);
  tev->SetBranchAddress("idtrk_pz", &idtrk_pz);


  tev->SetBranchAddress("idtrk_nPIXhits", &idtrk_nPIXhits);    // nPIX hits
  tev->SetBranchAddress("idtrk_nSCThits", &idtrk_nSCThits);    // nSCT hits
  tev->SetBranchAddress("idtrk_nDeadPixels", &idtrk_nPIXDead); // nPIX Dead
  tev->SetBranchAddress("idtrk_nDeadSCT", &idtrk_nSCTDead);    // nSCT Dead
  tev->SetBranchAddress("idtrk_nPIXHoles", &idtrk_nPIXHoles);    // nPIX Holes
  tev->SetBranchAddress("idtrk_nSCTHoles", &idtrk_nSCTHoles);    // nSCT Holes

  tev->SetBranchAddress("idtrk_mintrksChi2", &idtrk_mintrksChi2);

  auto ncands = ts->GetEntries();
  cout<< "Entries in original tree: "<< ncands << endl;
  
  float B_MUCALC_mass(0.), B_VTX_mass(0);
  int event_index(0);
  int B_PV_idx(0), PV_Type1_idx(0);
  int B_IDtrk1_trkidx(0);
  int B_IDtrk2_trkidx(0);
  int K_trkidx(0);
  v_float *B_PV_trksChi2 = 0;
  v_float *B_VTX_trksChi2=0;
  int closeTrkNtrksChi2(0);
  float closeTrkDCA(0.);
  float closeTrkZCA(0.);
  float closeTrkDCAErr(0.);
  float closeTrkZCAErr(0.);

  float B_iso_10_Chi2_runone_TTVA, B_iso_10_Chi2_custom_TTVA, B_iso_10_Chi2_loose_TTVA, B_iso_10_Chi2_nominal_TTVA, B_iso_10_Chi2_tight_TTVA, B_iso_10_Chi2_cutcustom_TTVA;
  int B_isoNtrks_10_Chi2_runone_TTVA, B_isoNtrks_10_Chi2_custom_TTVA, B_isoNtrks_10_Chi2_loose_TTVA, B_isoNtrks_10_Chi2_nominal_TTVA, B_isoNtrks_10_Chi2_tight_TTVA, B_isoNtrks_10_Chi2_cutcustom_TTVA;

  int Npv(0), B_PV_type(0), pvtx_match(1);
  float PRIVX_mu(0.);
  float Muon1_reco_eff_sf(0.);
  float Muon2_reco_eff_sf(0.);
  double PVWeights(0.), ew(0), B_pT(0), B_eta(0), B_phi(0), Lxy(0), a_2D(0), Pt2SumType1(0);

  if ( suf.Contains("Bs") ) ts->SetBranchAddress("B_MUCALC_mass",&B_MUCALC_mass);
  else ts->SetBranchAddress("B_VTX_mass",&B_VTX_mass);
  ts->SetBranchAddress("event_index",  &event_index);                           // index to EventInfo tree

  // variables for the isolation studies
  //
  ts->SetBranchAddress("B_PV_idx",&B_PV_idx);                                  // index to associated PV  
  ts->SetBranchAddress("B_PV_trksChi2",&B_PV_trksChi2);                        // chi2 to associated PV, per track
  ts->SetBranchAddress("B_pT",&B_pT);
  ts->SetBranchAddress("B_eta",&B_eta);
  ts->SetBranchAddress("B_phi",&B_phi);
  ts->SetBranchAddress("Lxy",&Lxy);
  ts->SetBranchAddress("a_2D",&a_2D);

  // variables for the close track studies
  //
  ts->SetBranchAddress("B_VTX_trksChi2",&B_VTX_trksChi2);                // chi2 of each track to the B vertex

  ts->SetBranchAddress("closeTrkNtrksChi2",&closeTrkNtrksChi2);          // DxAOD closeTrkNtrksChi2 variable
  ts->SetBranchAddress("closeTrkDCA",&closeTrkDCA);                      // DxAOD closeTrkDCA variable 
  ts->SetBranchAddress("closeTrkZCA",&closeTrkZCA);                      // DxAOD closeTrkZCA variable
  ts->SetBranchAddress("closeTrkDCAErr",&closeTrkDCAErr);                      // DxAOD closeTrkDCAErr variable 
  ts->SetBranchAddress("closeTrkZCAErr",&closeTrkZCAErr);                      // DxAOD closeTrkZCAErr variable

  // variables to identify signal tracks
  //
  ts->SetBranchAddress("B_IDtrk1_trkidx",&B_IDtrk1_trkidx); // indexes of muon tracks
  ts->SetBranchAddress("B_IDtrk2_trkidx",&B_IDtrk2_trkidx);
  if ( suf.Contains("Bp") ) ts->SetBranchAddress("K_trkidx",&K_trkidx);

  ts->SetBranchAddress("Npv",  &Npv);
  ts->SetBranchAddress("PRIVX_mu",  &PRIVX_mu);

  if (isMC) {
    ts->SetBranchAddress("pvtx_match",&pvtx_match);
    
    ts->SetBranchAddress("Muon1_reco_eff_sf", &Muon1_reco_eff_sf);
    ts->SetBranchAddress("Muon2_reco_eff_sf", &Muon2_reco_eff_sf);
    ts->SetBranchAddress("PVWeights", &PVWeights);
  }

  TString foutname(fsname);
  if (!fsname.Contains("/eos/atlas/atlascerngroupdisk")) foutname.ReplaceAll("bsmumu", "bsmumu_iso");
  else {
    if (isMC) foutname = "/afs/cern.ch/user/i/ibragimo/skimmed_ntup_mc/" + suf + "_iso.root";
    else foutname = "/afs/cern.ch/user/i/ibragimo/skimmed_ntup_dt/" + suf + "_iso.root";
  }
  TFile *fout = new TFile(foutname, "recreate");
  TTree *tout = new TTree("T_mv","official name of the tree");
  TBranch *b0(NULL);
  if ( suf.Contains("Bs")  ) b0 = tout->Branch("B_MUCALC_mass",  &B_MUCALC_mass,  "B_MUCALC_mass/F");
  else b0 = tout->Branch("B_VTX_mass",  &B_VTX_mass,  "B_VTX_mass/F");
  TBranch *b1 = tout->Branch("Lxy",  &Lxy,  "Lxy/D");
  TBranch *b2 = tout->Branch("a_2D", &a_2D, "a_2D/D");
  TBranch *b3 = tout->Branch("ew",  &ew,  "ew/D");
  TBranch *b4 = tout->Branch("B_iso_10_Chi2_runone_TTVA",  &B_iso_10_Chi2_runone_TTVA,  "B_iso_10_Chi2_runone_TTVA/F");
  TBranch *b5 = tout->Branch("B_iso_10_Chi2_custom_TTVA",  &B_iso_10_Chi2_custom_TTVA,  "B_iso_10_Chi2_custom_TTVA/F");
  TBranch *b6 = tout->Branch("B_iso_10_Chi2_loose_TTVA",  &B_iso_10_Chi2_loose_TTVA,  "B_iso_10_Chi2_loose_TTVA/F");
  TBranch *b7 = tout->Branch("B_iso_10_Chi2_nominal_TTVA",  &B_iso_10_Chi2_nominal_TTVA,  "B_iso_10_Chi2_nominal_TTVA/F");
  TBranch *b8 = tout->Branch("B_iso_10_Chi2_tight_TTVA",  &B_iso_10_Chi2_tight_TTVA,  "B_iso_10_Chi2_tight_TTVA/F");
  TBranch *b9 = tout->Branch("B_iso_10_Chi2_cutcustom_TTVA",  &B_iso_10_Chi2_cutcustom_TTVA,  "B_iso_10_Chi2_cutcustom_TTVA/F");
  TBranch *b10 = tout->Branch("B_pT",  &B_pT,  "B_pT/D");
  TBranch *b11 = tout->Branch("B_eta",  &B_eta,  "B_eta/D");
  TBranch *b12 = tout->Branch("Npv",  &Npv,  "Npv/I");
  TBranch *b13 = tout->Branch("PRIVX_mu",  &PRIVX_mu,  "PRIVX_mu/F");
  TBranch *b14 = tout->Branch("B_isoNtrks_10_Chi2_runone_TTVA",  &B_isoNtrks_10_Chi2_runone_TTVA,  "B_isoNtrks_10_Chi2_runone_TTVA/I");
  TBranch *b15 = tout->Branch("B_isoNtrks_10_Chi2_custom_TTVA",  &B_isoNtrks_10_Chi2_custom_TTVA,  "B_isoNtrks_10_Chi2_custom_TTVA/I");
  TBranch *b16 = tout->Branch("B_isoNtrks_10_Chi2_loose_TTVA",  &B_isoNtrks_10_Chi2_loose_TTVA,  "B_isoNtrks_10_Chi2_loose_TTVA/I");
  TBranch *b17 = tout->Branch("B_isoNtrks_10_Chi2_nominal_TTVA",  &B_isoNtrks_10_Chi2_nominal_TTVA,  "B_isoNtrks_10_Chi2_nominal_TTVA/I");
  TBranch *b18 = tout->Branch("B_isoNtrks_10_Chi2_tight_TTVA",  &B_isoNtrks_10_Chi2_tight_TTVA,  "B_isoNtrks_10_Chi2_tight_TTVA/I");
  TBranch *b19 = tout->Branch("B_isoNtrks_10_Chi2_cutcustom_TTVA",  &B_isoNtrks_10_Chi2_cutcustom_TTVA,  "B_isoNtrks_10_Chi2_cutcustom_TTVA/I");
  TBranch *b20 = tout->Branch("B_PV_type",  &B_PV_type,  "B_PV_type/I");
  TBranch *b21 = tout->Branch("pvtx_match",  &pvtx_match,  "pvtx_match/I");
  TBranch *b22 = tout->Branch("Pt2SumType1",  &Pt2SumType1,  "Pt2SumType1/D");

  int ntrkstotal(0);
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
  PV_Type1_idx = 0;  
  for (auto icand=0; icand<ncands; icand++)
    {
      if (icand%100000==0) cout << "Processing candidate: "<< icand << endl;
      ts->GetEntry(icand);

      // do not run on blinded candidates
      if (!fsname.Contains("mc16") && (B_MUCALC_mass<0.) ) continue; 

      // candidate weight
      ew = 1.0;
      if (isMC) ew = Muon1_reco_eff_sf*Muon2_reco_eff_sf*PVWeights;

      TVector3 B_p;
      B_p.SetPtEtaPhi(B_pT, B_eta, B_phi);
    
      tev->GetEntry(event_index);

      B_PV_type = (*pv_type).at(B_PV_idx);

      auto it = std::find(pv_type->begin(), pv_type->end(), 1);
      if (it == pv_type->end())
	{
	  cout << "WARNING: could not find PV type 1, taking the first element of the vertex array." << endl;
	}
      else
	{
	  PV_Type1_idx  = std::distance(pv_type->begin(), it);
	}

      // cross-check on the ntuple structure     
      auto ntrks = B_PV_trksChi2->size();
      if ((*idtrk_pvidx_lastround).size() != ntrks) {
	cout << "FATAL: ID trk info size unequal in event and candidate trees, exiting. " << (*idtrk_pvidx_lastround).size() << " <-ev|cand-> " << ntrks << " candidate: "<< icand << endl;
	exit(0);
      }
      // another cross-check on the ntuple structure     
      if ( Npv != pv_type->size()-1 ) {
	cout << "WARNING: smth is wrong with Npv, continuing. " << pv_type->size()-1 << " <-ev|cand-> " << Npv << " candidate: "<< icand << endl;
      }
      // yet another cross-check on the ntuple structure    
      if ( (*idtrk_mintrksChi2).size() != (*B_PV_trksChi2).size() ) {
	cout << "smth is wrong now: "<< (*idtrk_mintrksChi2).size() << " vs " << (*B_PV_trksChi2).size() << endl;  
      }

      for ( auto it = associated.begin(); it != associated.end(); it++ ) it->second=0;
      for ( auto it = pileup.begin(); it != pileup.end(); it++ ) it->second=0;
      for ( auto it = unassociated.begin(); it != unassociated.end(); it++ ) it->second=0;
      double ptsum_1p0_runone(0.), ptsum_1p0_custom(0.), ptsum_1p0_loose(0.), ptsum_1p0_nominal(0.), ptsum_1p0_tight(0.), ptsum_1p0_cutcustom(0.);
      Pt2SumType1 = 0.;

      for (unsigned int idx=0; idx<ntrks; idx++) {

	// skip signal tracks (Bsmumu channel as an example, add other tracks for other signatures!)
	//
	if ( (idx == B_IDtrk1_trkidx || idx == B_IDtrk2_trkidx) ) continue;
	if ( suf.Contains("Bp") && idx == K_trkidx ) continue;

	TVector3 idtrk_p;
	idtrk_p.SetXYZ( (*idtrk_px).at(idx), (*idtrk_py).at(idx), (*idtrk_pz).at(idx) );

	//if ( (*idtrk_nPIXhits).at(idx)<1 || (*idtrk_nSCThits).at(idx)<2 || (*idtrk_isLoose).at(idx)==0 ) continue;
	if ( ( (*idtrk_nPIXhits).at(idx) + (*idtrk_nPIXDead).at(idx) )<1 || ( (*idtrk_nSCThits).at(idx) + (*idtrk_nSCTDead).at(idx) )<2 || (*idtrk_isLoose).at(idx)==0 || idtrk_p.Pt()<500 ) continue;
	if ( fabs(idtrk_p.Eta())>2.5 || idtrk_p.Pt()<500 ) {
	  cout << "tracks out of isolation variables acceptance cuts, track (pT, eta): " << idtrk_p.Pt() << ", "<< idtrk_p.Eta() << endl;
	  continue;
	}
	if ( ( (*idtrk_nPIXhits).at(idx) + (*idtrk_nPIXDead).at(idx) + (*idtrk_nSCThits).at(idx) + (*idtrk_nSCTDead).at(idx) ) < 7 ) {
	  cout << "smth is wrong w Loose track selections, Nhits_si < 7" << endl; 
	}
	if ( ( (*idtrk_nPIXHoles).at(idx) + (*idtrk_nSCTHoles).at(idx) ) > 2 ) {
	  cout << "smth is wrong w Loose track selections, Nhole_SI > 2" << endl; 
	}


	ntrkstotal++;

	double deltaR = B_p.DeltaR(idtrk_p);
	
	// select tracks by vertex association
	// 
	if ( (*B_PV_trksChi2).at(idx) < 5.0 ) {
	  if (deltaR < 1.0) {
	    ptsum_1p0_runone += idtrk_p.Pt();
	    associated["runone"]++;
	  }
	} else {
	  pileup["runone"]++;
	}
	
	if ( (*idtrk_pvidx_custom).at(idx) == B_PV_idx ) {
	  if (deltaR < 1.0) {
	    ptsum_1p0_custom += idtrk_p.Pt();
	    if ( (*B_PV_trksChi2).at(idx) < 9.0) ptsum_1p0_cutcustom += idtrk_p.Pt();
	    associated["custom"]++;
	  }
	} else if ( (*idtrk_pvidx_custom).at(idx) == pv_type->size()-1 ) {
	  unassociated["custom"]++;
	  cout << "ERROR: found unassociated custom TTVA track. Something is wrong." << endl;
	} else {
	  pileup["custom"]++;
	}

	
	if ( (*idtrk_pvidx_loose).at(idx) == B_PV_idx ) {
	  if (deltaR < 1.0) {
	    ptsum_1p0_loose += idtrk_p.Pt();
	    associated["loose"]++;
	  }
	} else if ( (*idtrk_pvidx_loose).at(idx) == pv_type->size()-1 ) {
	  unassociated["loose"]++;
	} else {
	  pileup["loose"]++;
	}

	if ( (*idtrk_pvidx_nominal).at(idx) == B_PV_idx ) {
	  if (deltaR < 1.0) {
	    ptsum_1p0_nominal += idtrk_p.Pt();
	    associated["nominal"]++;
	  }
	} else if ( (*idtrk_pvidx_nominal).at(idx) == pv_type->size()-1 ) {
	  unassociated["nominal"]++;
	} else {
	  pileup["nominal"]++;
	}
	
	if ( (*idtrk_pvidx_nominal).at(idx) == PV_Type1_idx ) {
	  Pt2SumType1 += pow(idtrk_p.Pt(), 2);
	}

	if ( (*idtrk_pvidx_tight).at(idx) == B_PV_idx ) {
	  if (deltaR < 1.0) {
	    ptsum_1p0_tight += idtrk_p.Pt();
	    associated["tight"]++;
	  }
	} else if ( (*idtrk_pvidx_tight).at(idx) == pv_type->size()-1 ) {
	  unassociated["tight"]++;
	} else {
	  pileup["tight"]++;
	}
	  
      } // tracks
      
      Pt2SumType1 = sqrt(Pt2SumType1);

      B_isoNtrks_10_Chi2_runone_TTVA  = associated["runone"]; 
      B_isoNtrks_10_Chi2_custom_TTVA  = associated["custom"];
      B_isoNtrks_10_Chi2_loose_TTVA   = associated["loose"];
      B_isoNtrks_10_Chi2_nominal_TTVA = associated["nominal"];
      B_isoNtrks_10_Chi2_tight_TTVA   = associated["tight"];
      B_iso_10_Chi2_runone_TTVA       = B_pT / (B_pT + ptsum_1p0_runone);      
      B_iso_10_Chi2_custom_TTVA       = B_pT / (B_pT + ptsum_1p0_custom);
      B_iso_10_Chi2_loose_TTVA        = B_pT / (B_pT + ptsum_1p0_loose);
      B_iso_10_Chi2_nominal_TTVA      = B_pT / (B_pT + ptsum_1p0_nominal);
      B_iso_10_Chi2_tight_TTVA        = B_pT / (B_pT + ptsum_1p0_tight);
      B_iso_10_Chi2_cutcustom_TTVA    = B_pT / (B_pT + ptsum_1p0_cutcustom);
      
      tout->Fill();

    } // candidates

  cout << "done w loops, ntrkstotal: "<< ntrkstotal << endl;

  fout->cd();
  tout->Write();
  fout->Close();
  
  fs->Close();
  delete fs;
}
