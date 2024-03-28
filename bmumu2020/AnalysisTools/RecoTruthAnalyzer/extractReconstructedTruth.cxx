// ++++++++++++++++++++++++++ to do for Run 2 analysis +++++++++++++++++
// adjust truth decay variables to Run2 style (i.e. naming, [pT, eta, phi] to [px,py,pz])

// +++++++++++++++++++++ how to run the code ++++++++++++++++++++++++++++
// in root do
// .L loader.C++
// .L extractReconstructedTruth.C++
// extractReconstructedTruth()
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// ++++++++++++++++++++ how code works +++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// The code is running over the flat, candidate-wise ntuple (soft-link: MCbsmumuXntuple.root)
// which must also contain truth decay information written by TruthDecayFinder 
// (i.e. PDGid, mother, fdaughter, ldaughter, pt, eta, phi).
// For each candidate it matches truth-to-reco information
// for muons and (now commented out) the closest track to B candidate vertex.
// Then it analyses origin(s) of the OS muon pair and assignes 
// a TruthDecayCat category to each candidate.
// This category can be used to dump selected candidates into a separate file.
// which is specified (and located) as the input file appended with "_TruthDecayCat_XXX.root"
// Also, bunch of histograms is produced; some of them are dumped into the truthInfoPlots.root file
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// ++++++++++++++++++ Definition of TruthDecayCat variable +++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// TruthDecayCat==-5 Bs(bar)mumu+something (1 event there maybe 3 Gammas)
// TruthDecayCat==-4 Bs(bar)mumuGammaGamma
// TruthDecayCat==-3 Bs(bar)mumuGamma
// TruthDecayCat==-2 Bs(bar)mumu
// TruthDecayCat==-1 Bd/B+/- same vertex decays
// TruthDecayCat== 0 passed selections but uncategorized
// TruthDecayCat==+1 BB
// TruthDecayCat==+2 AB or BA
// TruthDecayCat==+3 AA
// TruthDecayCat==+4 >=1 muon mother is tau
// TruthDecayCat==+5 origin of OS muons is different than [1..4]
// TruthDecayCat==+6 (Bs+Bd) SS decays
// TruthDecayCat==+7 Bc+/- ->Jpsi mu+/- 
// TruthDecayCat==+8 ccbar

// TruthDecayCat [1,5] used for extraction of combinatorics (i.e. BDT training)
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// FIXME's
// closest-track related code is commented out as the variables are not propagated to
// flat ntuples by default
// clean-up: lot's of commented out code ("Set flags" stuff needed???)


// Date: 14.09.2017
// Comments to: Iskander(dot)Ibragimov(at)cern(dot)ch


#include "TString.h"
#include <utility>
#include <vector>
#include <iostream>
#include "TParticlePDG.h"
#include "TDatabasePDG.h"
#include "TMath.h"
#include "TH1.h"
#include "THStack.h"
#include "TFile.h"
#include "TTree.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TLorentzVector.h"

using namespace std;

// forward declarations of functions
//
TString particleNameFromPDGid(Int_t pdgid);
Double_t particleChargeFromPDGid(Int_t pdgid);
Int_t particleStabilityFromPDGid(Int_t pdgid);
bool isCompatibleQ(double q, int val);
bool matchDR(double phiT, double phiR, double etaT, double etaR, double DRcut, TH1D* hDR=NULL);
bool matchPT(double PtT, double PtR, double Ptcut, TH1D* hPt=NULL);
bool checkKaonPionMother(int  decay1, int  particle1, int  decay2, int  particle2, vector<vector<int> > *PDGid,
                         vector<vector<int> > *mother);
bool checkBMother(int  decay, int  particle, vector<vector<int> > *PDGid,
                         vector<vector<int> > *mother);
int checkCMother(int  decay, int  particle, vector<vector<int> > *PDGid,
		  vector<vector<int> > *mother);
bool checkTauMother(int  decay, int  particle, vector<vector<int> > *PDGid,
                  vector<vector<int> > *mother);
bool hasDaugthers(int  decay, int  particle,
		  vector<vector<int> > *fdaughter,
		  vector<vector<int> > *ldaughter);
void dumpDecayInfo(Int_t decay,
                   vector<vector<int> > *PDGid,
                   vector<vector<int> > *fdaughter,
                   vector<vector<int> > *ldaughter,
                   vector<vector<int> > *mother);
void drawHistos(vector <TH1*> vh);

// main function
//
void extractReconstructedTruth(bool verbose=false)
{
  // variables from the TruthDecayFinder                                                                                                                                        
  vector<vector<int> > *PDGid     = new vector<vector<int> >;
  vector<vector<int> > *mother    = new vector<vector<int> >;
  vector<vector<int> > *fdaughter = new vector<vector<int> >;
  vector<vector<int> > *ldaughter = new vector<vector<int> >;
  vector<vector<double> > *pt     = new vector<vector<double> >;
  vector<vector<double> > *theta  = new vector<vector<double> >;
  vector<vector<double> > *phi    = new vector<vector<double> >;

  double ptMu1 = 0;
  double ptMu2 = 0;
  double etaMu1 = 0;
  double etaMu2 = 0;
  double phiMu1 = 0;
  double phiMu2 = 0;
  double qMu1 = 0;
  double qMu2 = 0;

  // dimuon mass
  double m =0;

  double eta = 0;

  // closest track info
  double clopt = 0;
  double cloeta = 0;
  double clophi = 0;
  double cloq = 0;

  int en=0;
  bool passTrkQcuts = false;
  bool saveFileWithTruthDecayInfo = true;

  int TruthDecayCat(-100);
  vector<int> evnums;
  TString finname("MCbsmumuXntuple.root");
  char buf[512];
  int count = readlink(finname, buf, sizeof(buf));
  if (count >= 0) buf[count] = '\0';

  TString foutname(buf);
  foutname.Remove(foutname.Index(".root"),foutname.Length());
  //  foutname.Append("_TruthDecayCat_ssonly_radsep.root");
  foutname.Append("_TruthDecayCat_XXX.root");
 
  TFile *fs = new TFile(finname);
  TTree *ts = (TTree*)fs->Get("T_mv");

  ts->SetBranchAddress("TRUTHDECAY_PDGid",       &PDGid);
  ts->SetBranchAddress("TRUTHDECAY_mother",      &mother);
  ts->SetBranchAddress("TRUTHDECAY_fdaughter",   &fdaughter);
  ts->SetBranchAddress("TRUTHDECAY_ldaughter",   &ldaughter);
  ts->SetBranchAddress("TRUTHDECAY_pt",          &pt);
  ts->SetBranchAddress("TRUTHDECAY_theta",       &theta);
  ts->SetBranchAddress("TRUTHDECAY_phi",         &phi);
  ts->SetBranchAddress("B_IDtrk1_pT",            &ptMu1);
  ts->SetBranchAddress("B_IDtrk2_pT",            &ptMu2);
  ts->SetBranchAddress("B_IDtrk1_eta",           &etaMu1);
  ts->SetBranchAddress("B_IDtrk2_eta",           &etaMu2);
  ts->SetBranchAddress("B_IDtrk1_phi",           &phiMu1);
  ts->SetBranchAddress("B_IDtrk2_phi",           &phiMu2);
  ts->SetBranchAddress("B_IDtrk1_QoverP",        &qMu1);
  ts->SetBranchAddress("B_IDtrk2_QoverP",        &qMu2);

  ts->SetBranchAddress("B_MUCALC_mass",        &m);

  // to find in Angel's ntuple
  // ts->SetBranchAddress("dimuonPassedIDTrackQualCuts", &passTrkQcuts);

  ts->SetBranchAddress("event_number", &en);

  // closest track info is not stored in the flat ntuples
  //
  // ts->SetBranchAddress("ClosTrackPt",  &clopt);
  // ts->SetBranchAddress("ClosTrackEta", &cloeta);
  // ts->SetBranchAddress("ClosTrackPhi", &clophi);
  // ts->SetBranchAddress("ClosTrackQ",   &cloq);

  TH1D *hMv = new TH1D("hMv", "same vtx", 100, 4500, 6200);
  TH1D *hSBs = new TH1D("hSBs", "dimuon Bs", 100, 4500, 6200);
  TH1D *hSBd = new TH1D("hSBd", "dimuon Bd", 100, 4500, 6200);
  TH1D *hSBpm = new TH1D("hSBpm", "dimuon Bpm", 100, 4500, 6200);
  TH1D *hMd = new TH1D("hMd", "same decay", 100, 4500, 6200);
  TH1D *hSSc = new TH1D("hSSc", "ss Bc", 100, 4500, 6200);
  TH1D *hSSs = new TH1D("hSSs", "ss Bs", 100, 4500, 6200);
  TH1D *hSSd = new TH1D("hSSd", "ss Bd", 100, 4500, 6200);
  TH1D *hMe = new TH1D("hMe", "same evt BCmoms", 100, 4500, 6200);
  TH1D *hMo = new TH1D("hMo", "same evt ?moms", 100, 4500, 6200);
  TH1D *hMm = new TH1D("hMm", ">2 muons", 100, 4500, 6200);
  TH1D *hMf = new TH1D("hMf", "miss muons", 100, 4500, 6200);
  TH1D *hMdf = new TH1D("hMdf", "same evt Bmoms", 100, 4500, 6200);
  TH1D *hMdc = new TH1D("hMdc", "same evt Cmoms", 100, 4500, 6200);
  TH1D *hMdt = new TH1D("hMdt", "same evt Tau mom", 100, 4500, 6200);
  TH1D *hMhh = new TH1D("hMhh", ">0 fake Kpi", 100, 4500, 6200);
  TH1D *hMmmh = new TH1D("hMmmh", "mu(mu,h)", 100, 4500, 6200);
  TH1I *hgenMp = new TH1I("hgenMp", "gen mu+ evnt", 20, 0, 20);
  TH1I *hgenMm = new TH1I("hgenMm", "gen mu- evnt", 20, 0, 20);
  TH1I *hfndMp = new TH1I("hfndMp", "fnd mu+ evnt", 20, 0, 20);
  TH1I *hfndMm = new TH1I("hfndMm", "fnd mu- evnt", 20, 0, 20);

  TH1D *hDRmuMax = new TH1D("hDRmuMax", "DRmuMax truth-reco", 1000, 0, 1);
  hDRmuMax->SetLineColor(kRed);
  TH1D *hDRmuMin = new TH1D("hDRmuMin", "DRmuMin truth-reco", 1000, 0, 1);
  hDRmuMin->SetLineColor(kBlue);
  TH1D *hDRclos = new TH1D("hDRclos", "DRclos truth-reco", 1000, 0, 1);
  hDRclos->SetLineColor(kGreen+2);

  TH1D *hPtmuMax = new TH1D("hPtmuMax", "PtmuMax truth-reco", 100, 0, 1);
  hPtmuMax->SetLineColor(kRed);
  TH1D *hPtmuMin = new TH1D("hPtmuMin", "PtmuMin truth-reco", 100, 0, 1);
  hPtmuMin->SetLineColor(kBlue);
  TH1D *hPtclos = new TH1D("hPtclos", "Ptclos truth-reco", 100, 0, 1);
  hPtclos->SetLineColor(kGreen+2);

  const Int_t nx = 7;
  char *par[nx] = {"mu+","mu-","pi-","pi+","K-","K+","other"};
  TH1I *hClosTrkID = new TH1I("hClosTrkID", "Truth-matched clos trks", nx, 0, nx);
  for (unsigned int i=1;i<=nx;i++) {
    hClosTrkID->GetXaxis()->SetBinLabel(i,par[i-1]);
  }

  bool doClosTrk             = false;
  bool dumpdecays            = false;
  bool applyIDtrkQcuts       = false;

  //================ IMPORTANT =====================
  //========= cuts for reco-truth matching =========
  //================================================
  double cutDRMu = 0.01; //0.005
  double cutRatioPtMu = 0.4;
  double cutDRclo(0.05);
  double cutPtclo(120);
  //================================================

  vector<pair<int, int> > muPList;
  vector<pair<int, int> > muMList;

  int npassed(0);
  int ndimuons(0);
  int nbc(0),nbs(0),nbd(0),nsstotal(0);
  int nbcp(0), nbcm(0);
  int nBmumuX(0),nBsmumu(0),nBsmumuX(0),nBdn3(0),nBd3(0),nBpmn3(0),nBpm3(0);
  int ncltrk(0);
  int ndb(0);
  int maxEvent(-1);
  vector<int> tdcv;

  TLorentzVector mmin, mmax;
  Int_t ncands;
  if (maxEvent>0) ncands = maxEvent; 
  else ncands = (Int_t)ts->GetEntries();

  cout << "WILL PROCESS " << ncands << " DIMUON CANDIDATES" << endl;
 
  for(int icand=0; icand<ncands; icand++) { //<====CANDIDATES
    if (verbose) cout << ">>>>>>>>>>>>>>>Next candidate"<<endl;
    if (icand%100000==0) cout << "Processing candidate "<< icand << endl;
    ts->GetEntry(icand);
    /*
    // to check if there are many candidates in one event (ntuple is by cand.)
    vector<int>::iterator it;
    for (it = evnums.begin(); it != evnums.end(); ++it)
      if (*it==en) cout << "already there!"<< endl;
    if (it == evnums.end()) evnums.push_back(en);
    */
    TruthDecayCat=-100;

    if (applyIDtrkQcuts && !passTrkQcuts){
      tdcv.push_back(TruthDecayCat);
      continue;
    }

    qMu1 = TMath::Sign(1,qMu1);
    qMu2 = TMath::Sign(1,qMu2);
    npassed++;

    if (verbose) cout << "Psel done." << endl;    
    if (dumpdecays) {
      for (int j = 0; j < (int)PDGid->size(); j++) {
	cout << "Event: " << icand << "............................................" << endl;
	cout << ">>>>>>>>>>>>>>>>>> Decay: " << j << endl;
	for (int k = 0; k < (int)PDGid->at(j).size(); k++) {
	  TString line;
	  line += Form ("indx: %5d %5d %15s %10d %10d %10d %10g %10g %10g",
			k,
			PDGid->at(j).at(k),
			particleNameFromPDGid(PDGid->at(j).at(k)).Data(),
			mother->at(j).at(k),
			fdaughter->at(j).at(k),
			ldaughter->at(j).at(k),
			pt->at(j).at(k),
			-log(tan(theta->at(j).at(k)/2)),
			phi->at(j).at(k));
	  cout << line << endl;
	}
      }
    }

    vector<pair<int, int> > indexMuPlus;
    vector<pair<int, int> > indexMuMinus;
    vector<pair<int, int> > indexKPlus;
    vector<pair<int, int> > indexKMinus;
    vector<pair<int, int> > indexPiPlus;
    vector<pair<int, int> > indexPiMinus;
    vector<pair<int, int> > indexPPlus;
    vector<pair<int, int> > indexPMinus;
    vector<pair<int, int> > indexClosest;

    int nGenMm =0 ;
    int nGenMp =0 ;

    bool foundClo =false;

    bool markEvent = false;
   
    for (int i = 0; i < (int)PDGid->size(); i++) { //<====DECAY LOOP
      for (int j = 0; j< (int)PDGid->at(i).size(); j++) { //<=== PARTICLES LOOP

	int pdgid = PDGid->at(i).at(j);
	if (pdgid == 13) nGenMm++;
	else if (pdgid == -13) nGenMp++;

	eta = -TMath::Log(TMath::Tan(theta->at(i).at(j)/2));
	//=====================================================
	//==================Match leading muon=================
	//=====================================================

	if (matchDR(phi->at(i).at(j),phiMu2,eta,etaMu2,cutDRMu,hDRmuMax) && matchPT(pt->at(i).at(j),ptMu2,cutRatioPtMu,hPtmuMax)) {
	  /*
	  if (verbose) {
	    cout << ">>>found MuMu2" << endl;
	    cout << "chargeT: " << particleChargeFromPDGid(pdgid) << endl;
	    cout << "chargeR: " << qMu2 << endl;
	    cout << isCompatibleQ(qMu2, particleChargeFromPDGid(pdgid)) << endl;
	    cout << (particleChargeFromPDGid(pdgid) == qMu2) << endl;
	  }
	  */
	  pair<int, int> temp(i, j);
	  if (pdgid == 13 && isCompatibleQ(qMu2, particleChargeFromPDGid(pdgid)) ){
	    indexMuMinus.push_back(temp);
	  }
	  if (pdgid == -13 && isCompatibleQ(qMu2, particleChargeFromPDGid(pdgid)) ){
	    indexMuPlus.push_back(temp);
	  }
	  if (pdgid == 321 && isCompatibleQ(qMu2, particleChargeFromPDGid(pdgid)) ){
            indexKPlus.push_back(temp);
          }
          if (pdgid == -321 && isCompatibleQ(qMu2, particleChargeFromPDGid(pdgid)) ){
            indexKMinus.push_back(temp);
          }
	  if (pdgid == 211 && isCompatibleQ(qMu2, particleChargeFromPDGid(pdgid)) ){
            indexPiPlus.push_back(temp);
          }
          if (pdgid == -211 && isCompatibleQ(qMu2, particleChargeFromPDGid(pdgid)) ){
            indexPiMinus.push_back(temp);
          }
	  if (pdgid == 2212 && isCompatibleQ(qMu2, particleChargeFromPDGid(pdgid)) ){
            indexPPlus.push_back(temp);
          }
          if (pdgid == -2212 && isCompatibleQ(qMu2, particleChargeFromPDGid(pdgid)) ){
            indexPMinus.push_back(temp);
          }
	}
	//=====================================================
        //==================Match trailing muon================
	//=====================================================

	if (matchDR(phi->at(i).at(j),phiMu1,eta,etaMu1,cutDRMu,hDRmuMin) && matchPT(pt->at(i).at(j),ptMu1,cutRatioPtMu,hPtmuMin)) {
	  /*
	  if (verbose) {
	    //	    cout << ">>>found MuMu1, decay: " << i <<" index: "<< j << endl;
	    cout << ">>>found MuMu1" << endl;
	    cout << "chargeT: " << particleChargeFromPDGid(pdgid) << endl;
	    cout << "chargeR: " << qMu1 << endl;
	    cout << isCompatibleQ(qMu1, particleChargeFromPDGid(pdgid)) << endl;
	    cout << (particleChargeFromPDGid(pdgid) == qMu1) << endl;
	  }
	  */
	  pair<int, int> temp(i, j);
	  if (pdgid == 13 && isCompatibleQ(qMu1, particleChargeFromPDGid(pdgid)) ){
	    indexMuMinus.push_back(temp);
	  }
	  if (pdgid == -13 && isCompatibleQ(qMu1, particleChargeFromPDGid(pdgid)) ){
	    indexMuPlus.push_back(temp);
	  }
	  if (pdgid == 321 && isCompatibleQ(qMu1, particleChargeFromPDGid(pdgid)) ){
            indexKPlus.push_back(temp);
          }
          if (pdgid == -321 && isCompatibleQ(qMu1, particleChargeFromPDGid(pdgid)) ){
            indexKMinus.push_back(temp);
          }
	  if (pdgid == 211 && isCompatibleQ(qMu1, particleChargeFromPDGid(pdgid)) ){
            indexPiPlus.push_back(temp);
          }
          if (pdgid == -211 && isCompatibleQ(qMu1, particleChargeFromPDGid(pdgid)) ){
            indexPiMinus.push_back(temp);
          }
	  if (pdgid == 2212 && isCompatibleQ(qMu1, particleChargeFromPDGid(pdgid)) ){
            indexPPlus.push_back(temp);
          }
          if (pdgid == -2212 && isCompatibleQ(qMu1, particleChargeFromPDGid(pdgid)) ){
            indexPMinus.push_back(temp);
          }
	}
	//=====================================================
        //==================Match closest track================
	//=====================================================

	/*
	//	matchPT(pt->at(i).at(j),clopt,cutPtclo, hPtclos);

	if ((matchDR(phi->at(i).at(j),clophi,eta,cloeta,cutDRclo,hDRclos))
	    //	     || matchPT(pt->at(i).at(j),clopt,cutPtclo, hPtclos))
	    && isCompatibleQ(cloq,particleChargeFromPDGid(pdgid)) 
	    && particleStabilityFromPDGid(pdgid)==1  //does not work for e.g. D*+
	    && fdaughter->at(i).at(j)==-1 && ldaughter->at(i).at(j)==-1
	    && pdgid!=12
	    && pdgid!=14
	    && pdgid!=16) {
	//pdgid!=12 => exclude neutrinos
	  //cout << ">>>found closest track, decay: " << i <<" index: "<< j << " PDG id: " << pdgid<< endl;
	  //cout << "chargeTrue: " << particleChargeFromPDGid(pdgid) << endl;
	  //cout << "chargeReco: " << cloq << endl;
	  //cout << endl;
	  pair<int, int> temp(i, j);
	  if (foundClo) {
	    //markEvent = true;
	    cout << "WARNING: more than one match found!!! evt: " << icand << " decay: " << i <<" part: "<< j  << endl;
	  } else {
	    foundClo = true;
	    ncltrk++;
	    //cout << particleNameFromPDGid(pdgid) << endl;
	    //markEvent = true;
	  }
	  indexClosest.push_back(temp);
	  switch (pdgid) {
          case  -13: hClosTrkID->Fill(par[0],1); break;
	  case   13: hClosTrkID->Fill(par[1],1); break;
          case -211: hClosTrkID->Fill(par[2],1); break;
	  case  211: hClosTrkID->Fill(par[3],1); break;
          case -321: hClosTrkID->Fill(par[4],1); break;
	  case  321: hClosTrkID->Fill(par[5],1); break;
	  default: hClosTrkID->Fill(par[6],1); break;
	  }
        }
	*/
      } // PARTICLES LOOP
    } // DECAY LOOP

    //=====================================================
    //=======Consider case when both muons are matched ====
    //=====================================================
    bool muPfromBmom                    = false;
    bool muMfromBmom                    = false;
    bool muPfromCmom                    = false;
    bool muMfromCmom                    = false;
    bool muonsFromSameDecay             = false;
    bool samemom                        = false;
    bool clossameaswell                 = false;
    bool closTrackFromDecayOfOneOfMuons = false;
    int Pdecay(-1), Ndecay(-1);
    int Ppart(-1),  Npart(-1);
    int Pmom(-1),   Nmom(-1);

    /*
    // search for exclusive semileptionic
    //
    bool mumhp = (indexMuMinus.size()==1 && (indexKPlus.size()==1 || indexPiPlus.size()==1 || indexPPlus.size()==1));
    bool muphm = (indexMuPlus.size()==1 && (indexKMinus.size()==1 || indexPiMinus.size()==1 || indexPMinus.size()==1));
    if (mumhp || muphm) {
      if (mumhp) {
	Ndecay = indexMuMinus[0].first;
	Npart  = indexMuMinus[0].second;
	if (indexKPlus.size()==1) {
	  if (verbose) cout << "Kp " << endl;
	  Pdecay = indexKPlus[0].first;
	  Ppart  = indexKPlus[0].second;
	} else if (indexPiPlus.size()==1) {
	  if (verbose) cout << "Pip " << endl;
	  Pdecay = indexPiPlus[0].first;
	  Ppart  = indexPiPlus[0].second;
	} else if (indexPPlus.size()==1) {
	  if (verbose) cout << "Pp " << endl;
	  Pdecay = indexPPlus[0].first;
          Ppart  = indexPPlus[0].second;
	}
      } else {
	Pdecay = indexMuPlus[0].first;
	Ppart  = indexMuPlus[0].second;
	if (indexKMinus.size()==1) {
	  if (verbose) cout << "Km " << endl;
	  Ndecay = indexKMinus[0].first;
	  Npart  = indexKMinus[0].second;
	} else if (indexPiMinus.size()==1) {
	  if (verbose) cout << "Pim " << endl;
	  Ndecay = indexPiMinus[0].first;
	  Npart  = indexPiMinus[0].second;
	} else if (indexPMinus.size()==1) {
	  if (verbose) cout << "Pm " << endl;
	  Ndecay = indexPMinus[0].first;
          Npart  = indexPMinus[0].second;
	}
      }
    */
    /*
    // only one muon found
    //
    if ((indexMuMinus.size() == 1 && indexMuPlus.size() == 0) || (indexMuMinus.size() == 0 && indexMuPlus.size() == 1)){
      if (indexMuMinus.size() && (indexKPlus.size()==0 && indexPiPlus.size()==0 && indexPPlus.size()==0)) {
	Ndecay = indexMuMinus[0].first;
	Npart  = indexMuMinus[0].second;
	Nmom = mother->at(Ndecay).at(Npart);
	if (PDGid->at(Ndecay).at(Nmom)==-531 || PDGid->at(Ndecay).at(Nmom)==-511) markEvent=true;
      } else if (indexMuPlus.size() && (indexKMinus.size()==0 && indexPiMinus.size()==0 && indexPMinus.size()==0)) {
	Pdecay = indexMuPlus[0].first;
	Ppart  = indexMuPlus[0].second;
	Pmom = mother->at(Pdecay).at(Ppart);
	if (PDGid->at(Pdecay).at(Pmom)==531 || PDGid->at(Pdecay).at(Pmom)==511) markEvent=true;
      }
    */

    if (indexMuMinus.size()+indexMuPlus.size()> 2) cout << "More than two reco-truth-matched muons found!!!" <<endl;

    if (indexMuMinus.size() == 1 && indexMuPlus.size() == 1) { // muons: exactly two of OS
	Ndecay = indexMuMinus[0].first;
	Npart  = indexMuMinus[0].second;
	Nmom = mother->at(Ndecay).at(Npart);
	Pdecay = indexMuPlus[0].first;
	Ppart  = indexMuPlus[0].second;
	Pmom = mother->at(Pdecay).at(Ppart);

      if (verbose) cout << Ndecay << " " << Npart << " "<< Pdecay <<" " << Ppart << endl;
    
      if (Ndecay==Pdecay && Nmom==Pmom) { //same-vertex
	nBmumuX++;
	if (fabs(PDGid->at(Pdecay).at(Pmom))==531) {
	  hSBs->Fill(m);
	  if ((ldaughter->at(Pdecay).at(Pmom)-fdaughter->at(Pdecay).at(Pmom))!=1) {
	    nBsmumuX++;
	    //markEvent = true;
	  } else nBsmumu++;  
	} else if (fabs(PDGid->at(Pdecay).at(Pmom))==511) {
	  hSBd->Fill(m);
	  if ((ldaughter->at(Pdecay).at(Pmom)-fdaughter->at(Pdecay).at(Pmom))<2 ){
	    nBdn3++;
	    cout << endl;
	    cout << "Bd->mumu ?"<< endl;
	    cout << endl;
	  } else nBd3++;
	} else if (fabs(PDGid->at(Pdecay).at(Pmom))==521) {
	  hSBpm->Fill(m);
	  if ((ldaughter->at(Pdecay).at(Pmom)-fdaughter->at(Pdecay).at(Pmom))<2 ){
	    nBpmn3++;
	    cout << endl;
	    cout << "Bpm->mumu ?"<< endl;
	    cout << endl;
	  } else nBpm3++;
	} else {
	  cout << endl;
	  cout<< "dimoun form same mom but not Bs or Bd decay."<<endl;
	  cout << endl;
	}
      }
      //=============================================
      //exclusive semi-leptonic (same decay same mom)
      //=============================================
      if (Ndecay==Pdecay && Nmom!=Pmom) { //same-side
	nsstotal++;
	int d = Ndecay; 
	if ((PDGid->at(d).at(Pmom)==541 && PDGid->at(d).at(Nmom)==443)
	    ||(PDGid->at(d).at(Nmom)==-541 && PDGid->at(d).at(Pmom)==443)) {
	  hSSc->Fill(m);
	  nbc++;
	  if (PDGid->at(d).at(Nmom)==541) nbcp++; 
	  if (PDGid->at(d).at(Pmom)==-541) nbcm++;
	  //if (markEvent) cout << "was already true!!"<< endl; 
	  //markEvent=true;
	} else if ((PDGid->at(d).at(Pmom)==531 && PDGid->at(d).at(Nmom)==-431)
		   ||(PDGid->at(d).at(Nmom)==-531 && PDGid->at(d).at(Pmom)==431)) {
	  hSSs->Fill(m);
	    nbs++;
	}  else if ((PDGid->at(d).at(Pmom)==511 && PDGid->at(d).at(Nmom)==-411)
		    ||(PDGid->at(d).at(Nmom)==-511 && PDGid->at(d).at(Pmom)==411)) {
	  hSSd->Fill(m);
	  nbd++;
	}
      } else if (Ndecay!=Pdecay) { //opposite-side

      }
    
      int Nh = indexKMinus.size()+indexPiMinus.size()+indexPMinus.size()+indexKPlus.size()+indexPiPlus.size()+indexPPlus.size();
      if (Nh==0) ndimuons++; //pure dimuons!
      //if (Nh>0) markEvent=true;

      //=====================================================
      //================== Set flags ========================
      //=====================================================
      //muMfromCmom = checkCMother(indexMuMinus[0].first,indexMuMinus[0].second, PDGid, mother);
      //muPfromCmom = checkCMother(indexMuPlus[0].first,indexMuPlus[0].second, PDGid, mother);
      //if (muMfromCmom && muPfromCmom) markEvent = true;
      /*
      muMfromBmom = checkBMother(indexMuMinus[0].first,indexMuMinus[0].second, PDGid, mother);
      muPfromBmom = checkBMother(indexMuPlus[0].first,indexMuPlus[0].second, PDGid, mother);
      muMfromCmom = checkCMother(indexMuMinus[0].first,indexMuMinus[0].second, PDGid, mother);
      muPfromCmom = checkCMother(indexMuPlus[0].first,indexMuPlus[0].second, PDGid, mother);
      if (indexMuMinus[0].first == indexMuPlus[0].first) {
	//markEvent=true;
	muonsFromSameDecay = true;
	if (mother->at(indexMuMinus[0].first).at(indexMuMinus[0].second) == mother->at(indexMuMinus[0].first).at(indexMuPlus[0].second)) samemom = true;
      }
      else if (foundClo && (indexMuMinus[0].first == indexClosest[0].first || indexMuPlus[0].first == indexClosest[0].first)) {
	closTrackFromDecayOfOneOfMuons=true;
	ndb++;
	//markEvent=true;
      } //else markEvent=true;
      if (muonsFromSameDecay && foundClo && indexMuMinus[0].first == indexClosest[0].first) clossameaswell = true;
      */
      //if (checkBMother(indexMuMinus[0].first,indexMuMinus[0].second, PDGid, mother) && checkBMother(indexMuPlus[0].first,indexMuPlus[0].second, PDGid, mother)) samemom = true;
      //=====================================================
      //      if (muMfromBmom && muPfromBmom) { //bbar
      //      if ((muMfromBmom && muPfromCmom) || (muMfromCmom && muPfromBmom)) {
      //      if (!(muMfromBmom || muMfromCmom) || !(muPfromCmom || muPfromBmom)) {
	//	if (foundClo) {
	//if (muonsFromSameDecay && !samemom) {
	  //cout << "Closest match.. " <<endl;
	//markEvent = true;
	   // }

      if (markEvent) {
	//cout << clopt << " " << cloeta << " " << clophi << " " <<cloq << endl;
	
	cout << "dimuon inv mass: " << m << endl;
	for (int j = 0; j < (int)PDGid->size(); j++) { //DECAY
	  cout << "Event: " << icand << "............................................" << endl;
	  cout << ">>>>>>>>>>>>>>>>>> Decay: " << j << endl;
	  TString cap = Form("%5s %5s %15s %10s %10s %10s %10s %10s %10s","idx","PDGid", "Name","Mother","fdaughter","ldaughter","pt","theta","phi");
	  cout<< cap << endl;
	  for (int k = 0; k < (int)PDGid->at(j).size(); k++) { //PARTICLE
	    TString line;
	    line += Form ("%5d %5d %15s %10d %10d %10d %10g %10g %10g",
			  k,
			  PDGid->at(j).at(k),
			  particleNameFromPDGid(PDGid->at(j).at(k)).Data(),
			  mother->at(j).at(k),
			  fdaughter->at(j).at(k),
			  ldaughter->at(j).at(k),
			  pt->at(j).at(k),
			  -log(tan(theta->at(j).at(k)/2)),
			  phi->at(j).at(k) );
	    if (j==Ndecay && k==Npart) {
	      TString textblue("\033[1;34m");
	      textblue+=line;
	      textblue+="\033[0m";
	      cout << textblue << endl;
	    } else if (j==Pdecay && k==Ppart) {
	      TString textred("\033[1;31m");
	      textred+=line;
	      textred+="\033[0m";
	      cout << textred << endl;
	    } /*else if ((indexKPlus.size() && j==indexKPlus[0].first && k==indexKPlus[0].second) ||
		(indexKMinus.size() && j==indexKMinus[0].first && k==indexKMinus[0].second) ||
		(indexPiPlus.size() && j==indexPiPlus[0].first && k==indexPiPlus[0].second) ||
		(indexPiMinus.size() && j==indexPiMinus[0].first && k==indexPiMinus[0].second)) {
		  TString textgreen("\033[1;32m");
		  textgreen+=line;
		  textgreen+="\033[0m";
		  cout << textgreen << endl;
		}
	      */
	    else if (indexClosest.size() && j==indexClosest[0].first && k==indexClosest[0].second) {
	      TString textgreen("\033[1;32m");
	      textgreen+=line;
	      textgreen+="\033[0m";
	      cout << textgreen << endl;
	    } else cout << line << endl;
	  } //PARTICLE
	} //DECAY
      } //markEvent
    } //muons: exactly two of OS

    hgenMp->Fill(nGenMp);
    hgenMm->Fill(nGenMm);

    //=======================================================
    //=========== analyse found mu+ and mu- ================
    //=======================================================
    TruthDecayCat = 0; //pass all selections
    if (indexMuMinus.size()>1 || indexMuPlus.size()>1) {

      if (verbose) cout << "INFO: More than one match for one of the muons found..." << endl;

      hMm->Fill(m);
    } else if (indexMuMinus.size()==0 || indexMuPlus.size()==0) {

      if (verbose) cout << "INFO: At least one muon w/o match..." << endl;

      if (indexKMinus.size()>0 || indexPiMinus.size()>0 || indexPMinus.size()>0
	|| (indexKPlus.size()>0 || indexPiPlus.size()>0) || indexPPlus.size()>0) {
	if (verbose) cout << "\t But there is a hadron..." << endl;
	hMhh->Fill(m);
      } else {
	if (verbose) cout << "\t And there is no hadron detected..." << endl;
	hMf->Fill(m);
      }
    } else if (indexMuMinus.size() == 1 && indexMuPlus.size() == 1) { //SINGLE MATCH BOTH MUONS+
      if (verbose) cout << "INFO: There is exactly one mu+ and one mu-..." << endl;
      int Nh = indexKMinus.size()+indexPiMinus.size()+indexPMinus.size()+indexKPlus.size()+indexPiPlus.size()+indexPPlus.size();
      if (Nh>0) {
	if (verbose) cout << " INFO: And there are also " << Nh << " hadron(s) on top of two muons..."<< endl;
	hMmmh->Fill(m);
      } else {

	if (indexMuMinus[0].first == indexMuPlus[0].first) { //+SAME DECAY+
	  if (verbose) cout << "\t From the same decay..." << endl;
	  int decay = indexMuMinus[0].first;
	  
	  if (mother->at(decay).at(indexMuMinus[0].second) == mother->at(decay).at(indexMuPlus[0].second)) {
	    if (verbose) cout << "\t \t And even from the same mother..." << endl;
	    //	  cout << "Muons from the same particle: "<< particleNameFromPDGid(PDGid->at(i).at(mother->at(i).at(j))) << endl;
	    int samevtxmom = mother->at(decay).at(indexMuMinus[0].second);
	    if (fabs(PDGid->at(decay).at(samevtxmom))==531) {
	      int ndau = (ldaughter->at(decay).at(samevtxmom)-fdaughter->at(decay).at(samevtxmom));
	      int ldau = ldaughter->at(decay).at(samevtxmom);
	      if (ndau==1) TruthDecayCat = -2; //Bsmumu
	      else if (ndau==2 && PDGid->at(decay).at(ldau)==22) TruthDecayCat = -3; //Bsmumugamma
	      else if (ndau==3 && PDGid->at(decay).at(ldau-1)==22 && PDGid->at(decay).at(ldau)==22) TruthDecayCat = -4; //Bsmumugaga
	      else TruthDecayCat = -5; //BsmumuX with X non-gamma or 5- and more body decays
	    } else TruthDecayCat = -1;
	    hMv->Fill(m);
	  } else {
	    if (verbose) cout << "\t \t From the different mothers..." << endl;
	    int momn = mother->at(decay).at(indexMuMinus[0].second);
	    int momp = mother->at(decay).at(indexMuPlus[0].second);
	    if ((PDGid->at(decay).at(momp)==541 && PDGid->at(decay).at(momn)==443)
		||(PDGid->at(decay).at(momn)==-541 && PDGid->at(decay).at(momp)==443)) TruthDecayCat = 7; //Bc->Jpsimunu decays
	    else TruthDecayCat = 6;
	    hMd->Fill(m);
	  }
	} else if (checkBMother(indexMuMinus[0].first,indexMuMinus[0].second, PDGid, mother) //+DIFF DECAYS BOTH WITH BMOTHER=
		   && checkBMother(indexMuPlus[0].first,indexMuPlus[0].second, PDGid, mother)) {
	  if (verbose) cout << "\t From two different B meson decays..." << endl;
	  /*if (verbose) {
	    cout << "\t From two different B meson decays..." << endl;
	    cout << "MuMinus decay: " << endl;
	    dumpDecayInfo(indexMuMinus[0].first, PDGid, fdaughter, ldaughter, mother);
	    cout <<"MuPlus decay: " << endl;
	    dumpDecayInfo(indexMuPlus[0].first, PDGid, fdaughter, ldaughter, mother);
	    }*/
	  TruthDecayCat = 1;
	  hMdf->Fill(m);
	} else if (checkCMother(indexMuMinus[0].first,indexMuMinus[0].second, PDGid, mother) //+DIFF DECAYS BOTH WITH CMOTHER=
		   && checkCMother(indexMuPlus[0].first,indexMuPlus[0].second, PDGid, mother)) {
	  if (verbose) cout << "\t From two different C meson decays..." << endl;
	  /*if (verbose) {
	    cout << "MuMinus decay: " << endl;
	    dumpDecayInfo(indexMuMinus[0].first, PDGid, fdaughter, ldaughter, mother);
	    cout <<"MuPlus decay: " << endl;
	    dumpDecayInfo(indexMuPlus[0].first, PDGid, fdaughter, ldaughter, mother);
	    }*/
	  
	  if (checkCMother(indexMuMinus[0].first,indexMuMinus[0].second, PDGid, mother)==1
	      && checkCMother(indexMuPlus[0].first,indexMuPlus[0].second, PDGid, mother)==1) { //ccbar
	    TruthDecayCat = 8;
	  } else {
	    TruthDecayCat = 3;
	    hMdc->Fill(m);
	  }
	} else if (checkTauMother(indexMuMinus[0].first,indexMuMinus[0].second, PDGid, mother)//+DIFF DECAYS ONE MOM TAU=
		   || checkTauMother(indexMuPlus[0].first,indexMuPlus[0].second, PDGid, mother)) {
	  if (verbose) cout << "\t From a tau decay (at least one muon)..." << endl;
	  /*
	    cout << "MuMinus decay: " << endl;
	    dumpDecayInfo(indexMuMinus[0].first, PDGid, fdaughter, ldaughter, mother);
	    cout <<"MuPlus decay: " << endl;
	    dumpDecayInfo(indexMuPlus[0].first, PDGid, fdaughter, ldaughter, mother);
	  */
	  TruthDecayCat = 4;
	  hMdt->Fill(m);
	} else if ((checkCMother(indexMuMinus[0].first,indexMuMinus[0].second, PDGid, mother) ||
		    checkBMother(indexMuMinus[0].first,indexMuMinus[0].second, PDGid, mother)) &&
		   (checkCMother(indexMuPlus[0].first,indexMuPlus[0].second, PDGid, mother) ||
		    checkBMother(indexMuPlus[0].first,indexMuPlus[0].second, PDGid, mother))) { //+DIFF DECAYS BC MOMS= 
	  if (verbose) cout << "\t One muon could be from B, another from C, or other way around..." << endl;
	  /*
	    cout << "MuMinus decay: " << endl;
	    dumpDecayInfo(indexMuMinus[0].first, PDGid, fdaughter, ldaughter, mother);
	    cout <<"MuPlus decay: " << endl;
	    dumpDecayInfo(indexMuPlus[0].first, PDGid, fdaughter, ldaughter, mother);
	  */
	  TruthDecayCat = 2;
	  hMe->Fill(m);
	} else { //+DIFF DECAYS SOME OTHER MOMS=
	  if (verbose) cout << "\t Muon origin is other ..." << endl;
	  TruthDecayCat = 5;
	  hMo->Fill(m);
	}
      }
    } else {
      cout << "INFO: Impossible..." << endl;
    }
    tdcv.push_back(TruthDecayCat);
  } //<====CANDIDATE

  cout << "Candidates (passed): "<< npassed << " matched dimuons (only!):  " << ndimuons << " matched clos tracks: " << ncltrk << " out of them double b-decay: " << ndb << endl;  
  cout << "Candidates with C-mother " << hMdc->GetEntries() << endl;
  cout << "SS: total: " << nsstotal << endl;
  cout << "SS: Bc decay: " << nbc << " or " << 100*(float)nbc/(float)nsstotal << " [%]"<< endl;
  cout << nbcp << " + or  - " << nbcm << endl;
  cout << "SS: Bs decay: " << nbs << " or " << 100*(float)nbs/(float)nsstotal << " [%]"<< endl;
  cout << "SS: Bd decay: " << nbd << " or " << 100*(float)nbd/(float)nsstotal << " [%]"<< endl;
  cout << endl;
  cout << "SIG decay total: " << nBmumuX << endl;
  cout << "Bsmumu: " <<  nBsmumu << endl;
  cout << "BsmumuX: " <<  nBsmumuX << endl;
  cout << "Bd->2 part (e.g. Bdmumu): " <<  nBdn3<< endl;
  cout << "Bd-> >=3 part: " <<  nBd3<< endl;
  cout << "Bpm->2 part ?: " <<  nBpmn3<< endl;
  cout << "Bpm-> >=3 part: " <<  nBpm3<< endl;

  TCanvas *c1 = new TCanvas("dimuon mass","dimuon mass",1200,600);
  c1->SetLogy(0);
  c1->SetLeftMargin(0.13);
  c1->SetRightMargin(0.10);
  c1->SetTopMargin(0.07);
  c1->SetBottomMargin(0.12);
  
  //  c1->Divide(2,2);
  //c1->cd(1);
  //==============================================
  //==== dimuon mass plot by  contibutions =======
  //==============================================
  /*
  vector <TH1*> vh;
  vh.push_back(hMdf);
  vh.push_back(hMdc);
  vh.push_back(hMdt);
  vh.push_back(hMe);
  vh.push_back(hMm);
  vh.push_back(hMhh);
  vh.push_back(hMmmh);
  vh.push_back(hMf);
  vh.push_back(hMv);
  vh.push_back(hMd);
  vh.push_back(hMo);
  drawHistos(vh);
  */
 
  hMd->SetMarkerStyle(20);
  hMd->GetXaxis()->SetTitle("m_{#mu#mu} [MeV]");
  hMd->GetYaxis()->SetTitle("B candidates / 17 MeV");
  hMd->DrawCopy("PE");
  THStack *hs = new THStack("hs", "stack - all ss contributions");
  hSSc->SetLineColor(kBlack);
  hSSc->SetFillColor(kRed);
  hs->Add(hSSc);
  hSSs->SetLineColor(kBlack);
  hSSs->SetFillColor(kGreen+2);
  hs->Add(hSSs);
  hSSd->SetLineColor(kBlack);
  hSSd->SetFillColor(kBlue);
  hs->Add(hSSd);
  hs->Draw("SAME");
  TLegend *legend3 = new TLegend(0.58, 0.60, 0.88, 0.90);
  legend3->AddEntry(hMd, "All same-side", "P");
  legend3->AddEntry(hSSc, "B_{c} decays", "F");
  legend3->AddEntry(hSSs, "B_{s} decays", "F");
  legend3->AddEntry(hSSd, "B_{d} decays", "F");
  legend3->SetFillColor(kWhite);
  legend3->SetLineColor(kWhite);
  legend3->Draw("SAME");
  c1->SaveAs("sameside.eps");
  c1->Clear();
 
  hMv->SetMarkerStyle(20);
  hMv->GetXaxis()->SetTitle("m_{#mu#mu} [MeV]");
  hMv->GetYaxis()->SetTitle("B candidates / 17 MeV");
  hMv->DrawCopy("PE");
  THStack *hsig = new THStack("hsig", "stack - all ss contributions");
 
  hSBs->SetLineColor(kBlack);
  hSBs->SetFillColor(kRed);
  hsig->Add(hSBs);
  hSBd->SetLineColor(kBlack);
  hSBd->SetFillColor(kGreen+2);
  hsig->Add(hSBd);
  hSBpm->SetLineColor(kBlack);
  hSBpm->SetFillColor(kBlue);
  hsig->Add(hSBpm);
  hsig->Draw("SAME");
  TLegend *legend4 = new TLegend(0.58, 0.60, 0.88, 0.90);
  legend4->AddEntry(hMd, "All same-vertex", "P");//B->#mu#mu(X,#gamma)", "P");
  legend4->AddEntry(hSBs, "B_{s} decays", "F");
  legend4->AddEntry(hSBd, "B_{d} decays", "F");
  legend4->AddEntry(hSBpm, "B^{#pm} decays", "F");
  legend4->SetFillColor(kWhite);
  legend4->SetLineColor(kWhite);
  legend4->Draw("SAME");
  c1->SaveAs("samevertex.eps");
 
  // some plot
  //============================================== 

  /*
  c1->cd(2);
  hgenMp->SetLineColor(kRed);
  hgenMp->GetXaxis()->SetTitle("N_{#mu}");
  hgenMp->Draw();
  hgenMm->SetLineColor(kBlue);
  hgenMm->Draw("same");
  TLegend *legGen;
  legGen = new TLegend(0.44,0.73,0.87,0.90,NULL,"brNDC");
  legGen->SetBorderSize(0);
  legGen->SetLineStyle(1);
  legGen->SetLineWidth(1);
  legGen->SetFillColor(0);
  legGen->SetFillStyle(0);
  legGen->SetTextFont(132);
  legGen->AddEntry(hgenMp,Form("%s",hgenMp->GetTitle()),"l");
  legGen->AddEntry(hgenMm,Form("%s",hgenMm->GetTitle()),"l");
  legGen->Draw();

  TPad *p3 = (TPad *)(c1->cd(3));
  p3->SetLogy();
  //==============================================
  //==== DR plots ===============
  //==============================================
  hDRmuMax->GetXaxis()->SetTitle("#DeltaR");
  hDRmuMax->Draw();
  hDRmuMin->Draw("same");
  if (doClosTrk) hDRclos->Draw("same");
  TLegend *legDR;
  legDR = new TLegend(0.44,0.73,0.87,0.90,NULL,"brNDC");
  legDR->SetBorderSize(0);
  legDR->SetLineStyle(1);
  legDR->SetLineWidth(1);
  legDR->SetFillColor(0);
  legDR->SetFillStyle(0);
  legDR->SetTextFont(132);
  legDR->AddEntry(hDRmuMax,Form("%s",hDRmuMax->GetTitle()),"l");
  legDR->AddEntry(hDRmuMin,Form("%s",hDRmuMin->GetTitle()),"l");
  if (doClosTrk) legDR->AddEntry(hDRclos,Form("%s",hDRclos->GetTitle()),"l");
  legDR->Draw();

  
  TPad *p4 = (TPad *)(c1->cd(4));
  p4->SetLogy();
  //==============================================
  //==== Pt plots ===============
  //==============================================
  hPtmuMax->GetXaxis()->SetTitle("#DeltapT/pT");
  hPtmuMax->Draw();
  hPtmuMin->Draw("same");
  if (doClosTrk) hPtclos->Draw("same");
  TLegend *legPT;
  legPT = new TLegend(0.44,0.73,0.87,0.90,NULL,"brNDC");
  legPT->SetBorderSize(0);
  legPT->SetLineStyle(1);
  legPT->SetLineWidth(1);
  legPT->SetFillColor(0);
  legPT->SetFillStyle(0);
  legPT->SetTextFont(132);
  legPT->AddEntry(hPtmuMax,Form("%s",hPtmuMax->GetTitle()),"l");
  legPT->AddEntry(hPtmuMin,Form("%s",hPtmuMin->GetTitle()),"l");
  if (doClosTrk) legPT->AddEntry(hPtclos,Form("%s",hPtclos->GetTitle()),"l");
  legPT->Draw();
  */

  TFile* fout = new TFile("truthInfoPlots.root","RECREATE");
  c1->Write();
  fout->Close();

  if (saveFileWithTruthDecayInfo) {
    //---- make skimmed ntuple --------
    //
    // it is the original file without truth decay information
    // but with additional variable - TruthDecayCat - which determines
    // the truth category of the reconstructed candidate
    // 
    ts->SetBranchStatus("PDGid",0);
    ts->SetBranchStatus("mother",0);
    ts->SetBranchStatus("fdaughter",0);
    ts->SetBranchStatus("ldaughter",0);
    ts->SetBranchStatus("pt",0);
    ts->SetBranchStatus("theta",0);
    ts->SetBranchStatus("phi",0);
    //ts->SetBranchStatus("",0);
    
    TFile *fn = new TFile(foutname,"recreate");
    TTree *tn = ts->CloneTree(0);
    TBranch *tdcat = tn->Branch("TruthDecayCat",&TruthDecayCat,"TruthDecayCat/I");
    cout << endl;
    cout << "NOW WILL SAVE SKIMMED FILE" << endl;
    cout << endl;
    for(int ii=0; ii<ncands; ii++) { 
      if (ii%100000==0) cout << "Processing event "<< ii << endl;
      ts->GetEntry(ii);
      TruthDecayCat = tdcv.at(ii);
      //if ((TruthDecayCat<0 &&TruthDecayCat!=-100) ||TruthDecayCat==6 || TruthDecayCat==7) tn->Fill();
      if (TruthDecayCat!=-100) tn->Fill();
    }
    tn->Write();
    fn->Close();
  }
}

void drawHistos(vector <TH1*> vh) {
  int maxY=-1;
  int idxMaxY = -1;
  for (unsigned int i=0;i<vh.size();i++) {
    if (maxY < vh.at(i)->GetMaximum()) {
      maxY=vh.at(i)->GetMaximum();
      idxMaxY = i;
    }
  }
  TLegend *leg;
  leg = new TLegend(0.64,0.53,0.87,0.90,NULL,"brNDC");
  leg->SetName("Compo");
  leg->SetBorderSize(0);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetTextFont(132);
 
  vh.at(idxMaxY)->SetMarkerSize(0.7);
  vh.at(idxMaxY)->GetXaxis()->SetTitle("m_{#mu#mu} [MeV]");
  vh.at(idxMaxY)->Draw();
 
  leg->AddEntry(vh.at(idxMaxY),Form("%s",vh.at(idxMaxY)->GetTitle()));
  int icolor = 2; 
  for (int i=0;i<(int)vh.size();i++) {
    if (i!=idxMaxY) {
      vh.at(i)->SetLineColor(icolor);
      vh.at(i)->SetMarkerColor(icolor);
      vh.at(i)->SetMarkerSize(0.7);
      vh.at(i)->Draw("same");
      leg->AddEntry(vh.at(i),Form("%s",vh.at(i)->GetTitle()));
      icolor++;
      if (icolor==5 || icolor==10 || icolor==19) icolor++;
    }
  }
  leg->Draw();
}

bool checkKaonPionMother(int  decay1, int  particle1, int  decay2, int  particle2, vector<vector<int> > *PDGid,
			 vector<vector<int> > *mother) {
  int mom1Id = TMath::Abs(PDGid->at(decay1).at(mother->at(decay1).at(particle1)));
  int mom2Id = TMath::Abs(PDGid->at(decay2).at(mother->at(decay2).at(particle2)));
  if (mom1Id==321 || mom1Id==211 || mom2Id==321 || mom2Id==211) {
    cout << "Decay in flight found" << endl;
    return true;
  } 
  else 
    {
      return false;
    }
}

bool checkBMother(int  decay, int  particle, vector<vector<int> > *PDGid, vector<vector<int> > *mother) {
  int moMuId = TMath::Abs(PDGid->at(decay).at(mother->at(decay).at(particle)));

  if ((moMuId > 500 && moMuId < 600) ||
      (moMuId > 10500 && moMuId < 10600) ||
      (moMuId > 20500 && moMuId < 20600) || 
      (moMuId > 5000 && moMuId < 6000))
    {
      return true;
    } 
  else 
    {
      return false;
    }
}

int checkCMother(int  decay, int  particle, vector<vector<int> > *PDGid, vector<vector<int> > *mother) {
  int moMuId = TMath::Abs(PDGid->at(decay).at(mother->at(decay).at(particle)));
  int    mo0 = TMath::Abs(PDGid->at(decay).at(0));
  bool origC = false;
  if ((mo0 > 400 && mo0 < 500) ||
      (mo0 > 10400 && mo0 < 10500) ||
      (mo0 > 20400 && mo0 < 20500) ||
      (mo0 > 4000 && mo0 < 5000))  origC = true;
  if ((moMuId > 400 && moMuId < 500) ||
      (moMuId > 10400 && moMuId < 10500) ||
      (moMuId > 20400 && moMuId < 20500) ||
      (moMuId > 4000 && moMuId < 5000))
    {
      // to detect ccbar origin
      if (mother->at(decay).at(particle)==0) return 1;               // prompt
      else if (mother->at(decay).at(particle)==1 && origC) return 1; // catch up excited
      else return 2;                                                 // could be A chain
    } 
  else
    { 
      return 0;
    }
}

bool checkTauMother(int  decay, int  particle, vector<vector<int> > *PDGid, vector<vector<int> > *mother) {
  int moMuId = TMath::Abs(PDGid->at(decay).at(mother->at(decay).at(particle)));
  if (moMuId == 15)
    {
      return true;
    } 
  else 
    {
    return false;
    }
}


bool hasDaugthers(int  decay, int  particle,
                  vector<vector<int> > *fdaughter,
                  vector<vector<int> > *ldaughter) {
  if (fdaughter->at(decay).at(particle)==-1 && ldaughter->at(decay).at(particle)==-1) return false;
  else return true;
}

TString particleNameFromPDGid(Int_t pdgid) {
  TString name;
  TParticlePDG* p = TDatabasePDG::Instance()->GetParticle(pdgid);
  if ( p != NULL ) {
    name = p->GetName();
  } else {
    name = Form("Unknown(%d)", pdgid);
  }
  return name;
}

Double_t particleChargeFromPDGid(Int_t pdgid) {
  TParticlePDG* p = TDatabasePDG::Instance()->GetParticle(pdgid);
  if ( p != NULL ) {
    return p->Charge()/3;
  } else {
    return TMath::Pi();
  }
}

Int_t particleStabilityFromPDGid(Int_t pdgid) {
  TParticlePDG* p = TDatabasePDG::Instance()->GetParticle(pdgid);
  if ( p != NULL ) {
    return p->Stable();
  } else {
    return -1;
  }
}

bool isCompatibleQ(double q, int val)
 {
   double range = 0.01;
   double diff = TMath::Abs(q-val);
   return diff < range;
 }

void dumpDecayInfo(Int_t decay, 
		   vector<vector<int> > *PDGid,
		   vector<vector<int> > *fdaughter,
		   vector<vector<int> > *ldaughter,
		   vector<vector<int> > *mother) {
  
  int j = decay;
  
  for (int k = 0; k < (int)PDGid->at(j).size(); k++) {
    TString line;
    line += Form ("indx: %5d %5d %15s %10d %10d %10d",
		  k,
		  PDGid->at(j).at(k),
		  particleNameFromPDGid(PDGid->at(j).at(k)).Data(),
		  mother->at(j).at(k),
			  fdaughter->at(j).at(k),
		  ldaughter->at(j).at(k));
    cout << line << endl;
  }
}

bool matchDR(double phiT, double phiR, double etaT, double etaR, double DRcut, TH1D* hDR) {
  double deltaPhi = phiT-phiR;
  if (deltaPhi  > TMath::Pi()) deltaPhi = 2*TMath::Pi()-deltaPhi;
  else if (deltaPhi <= -TMath::Pi()) deltaPhi = 2*TMath::Pi()+deltaPhi;
  double deltaEta = etaT-etaR;
  double deltaR = TMath::Sqrt(deltaEta*deltaEta + deltaPhi*deltaPhi);
  if (hDR!=NULL) hDR->Fill(deltaR);
  if (deltaR < DRcut) return true;
  else return false;
}

bool matchPT(double ptTrue, double ptReco, double ratioPtcut, TH1D* hPt) {
  double ratioPt = TMath::Abs(ptTrue-ptReco)/ptTrue;
  if (hPt!=NULL) hPt->Fill(ratioPt);
  if (ratioPt < ratioPtcut) return true;
  else return false;
}
