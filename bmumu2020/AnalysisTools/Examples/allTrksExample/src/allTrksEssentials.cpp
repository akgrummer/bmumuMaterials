//
// plot isolation variables from ntuples w/ all track informaion
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

  TString fsname("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/skimmed_ntup/data17/Bmumu/v5/user.ibragimo.19794075.Bmumu._000021.root");

  TFile *fs  = new TFile(fsname);
  TTree *ts  = (TTree*)fs->Get("T_mv");
  TTree *tev = (TTree*)fs->Get("EventInfo");
  
  // variables related to PV container
  //
  v_uint   *pv_type               = 0;
  tev->SetBranchAddress("pv_type", &pv_type);         // type of primary vertices (1,3 or 0 - the last one in the container)

  // variables related to ID track container
  //
  v_uint   *idtrk_pvidx_lastround = 0;
  v_uint   *idtrk_pvidx_custom    = 0;

  v_int    *idtrk_isLoose   = 0;
  v_int    *idtrk_nPIXhits  = 0;
  v_int    *idtrk_nSCThits  = 0;
  v_int    *idtrk_nPIXDead  = 0;
  v_int    *idtrk_nSCTDead  = 0;
  v_double *idtrk_px    = 0;
  v_double *idtrk_py    = 0;
  v_double *idtrk_pz    = 0;
  v_float  *idtrk_mintrksChi2 = 0;
  tev->SetBranchAddress("idtrk_pvidx", &idtrk_pvidx_lastround); // index of association of ID track to PV,
                                                      // i.e. the position of the corresponding PV in the vertex contaner
                                                      // if the position is the last position in the containter (PV type 0),
                                                      // that means that the track has not been associated to any PV.
                                                      // ( currently filled with info whether the track has been used in PV fit,  
                                                      // which is not recommended to be used by the vertex group )
  tev->SetBranchAddress("idtrk_pvidx_custom", &idtrk_pvidx_custom);     // same as above but for official custom WP
  tev->SetBranchAddress("idtrk_isLoose", &idtrk_isLoose);             // ensure loose track selection
  tev->SetBranchAddress("idtrk_px", &idtrk_px);       // momenta of all ID tracks
  tev->SetBranchAddress("idtrk_py", &idtrk_py);
  tev->SetBranchAddress("idtrk_pz", &idtrk_pz);

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
  v_float *closeTrkDCA_alltrks=0;
  v_float *closeTrkZCA_alltrks=0; 
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
  ts->SetBranchAddress("closeTrkDCA_alltrks",&closeTrkDCA_alltrks);    // DCA of each track to B vertex
  ts->SetBranchAddress("closeTrkZCA_alltrks",&closeTrkZCA_alltrks);    // ZCA of each track to B vertex
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



  THStack *hisoAll = new THStack("hisoAll","B isolation, data18"); 
  TH1F* h_iso_def(NULL); TH1F* h_iso_0p7(NULL); TH1F* h_iso_1p0(NULL); TH1F* h_iso_alar1(NULL); 

  THStack *hntrksAll = new THStack("hntrksAll","Nclosetracks, data18");
  TH1I* h_ntrksCustom(NULL); TH1I* h_ntrksDxAOD(NULL); TH1I* h_ntrksNtuple(NULL); 

  THStack *hdocaAll = new THStack("hdocaAll","DOCA, data18");
  TH1F* h_docaCustom(NULL); TH1F* h_docaDxAOD(NULL); TH1F* h_docaNtuple(NULL); 

  h_iso_def      = new TH1F("h_iso_def","B isolation def",50,0.01,1.01);
  h_iso_def->SetLineColor(kBlack);
  h_iso_0p7      = new TH1F("h_iso_0p7","B isolation 0p7",50,0.01,1.01);
  h_iso_0p7->SetLineColor(kRed);
  h_iso_1p0      = new TH1F("h_iso_1p0","B isolation 1p0",50,0.01,1.01);
  h_iso_1p0->SetLineColor(kBlue);
  h_iso_alar1    = new TH1F("h_iso_alar1","B isolation alar1",50,0.01,1.01);
  h_iso_alar1->SetLineColor(kCyan);

  h_ntrksDxAOD   = new TH1I("h_ntrksDxAOD","h_ntrksDxAOD",100,0,100); 
  h_ntrksDxAOD->SetLineColor(kBlack);
  h_ntrksNtuple  = new TH1I("h_ntrksNtuple","h_ntrksNtuple",100,0,100);  
  h_ntrksNtuple->SetLineColor(kRed);
  h_ntrksCustom  = new TH1I("h_ntrksCustom","h_ntrksCustom",100,0,100);  
  h_ntrksCustom->SetLineColor(kBlue);


  h_docaDxAOD   = new TH1F("h_docaDxAOD","h_docaDxAOD",100,-0.02,0.48); 
  h_docaDxAOD->SetLineColor(kBlack);
  h_docaNtuple  = new TH1F("h_docaNtuple","h_docaNtuple",100,-0.02,0.48);  
  h_docaNtuple->SetLineColor(kRed);
  h_docaCustom  = new TH1F("h_docaCustom","h_docaCustom",100,-0.02,0.48);  
  h_docaCustom->SetLineColor(kBlue);

   
  TFile *fout = new TFile("fout.root","recreate");
  TTree *tout = new TTree("T_mv","official name of the tree");
  TBranch *b1 = tout->Branch("Lxy",  &Lxy,  "Lxy/D");
  TBranch *b2 = tout->Branch("a_2D", &a_2D, "a_2D/D");
  TBranch *b3 = tout->Branch("ew",  &ew,  "ew/D");

  TBranch *b4 = tout->Branch("B_iso_7_Chi2_lastround_TTVA",  &B_iso_7_Chi2_lastround_TTVA,  "B_iso_7_Chi2_lastround_TTVA/F");
  TBranch *b5 = tout->Branch("B_iso_10_Chi2_custom_TTVA",  &B_iso_10_Chi2_custom_TTVA,  "B_iso_10_Chi2_custom_TTVA/F");
  TBranch *b7 = tout->Branch("B_iso_7_Chi2_alaRun1_TTVA",  &B_iso_7_Chi2_alaRun1_TTVA,  "B_iso_7_Chi2_alaRun1_TTVA/F"); //isolation calculation in run1
  TBranch *b8 = tout->Branch("B_iso_7_Chi2_5_LoosePt05",  &B_iso_7_Chi2_5_LoosePt05,  "B_iso_7_Chi2_5_LoosePt05/F"); //default isolation

  TBranch *b9 = tout->Branch("B_MUCALC_mass",  &B_MUCALC_mass,  "B_MUCALC_mass/F");
  TBranch *b10 = tout->Branch("B_pT",  &B_pT,  "B_pT/D");
  TBranch *b11 = tout->Branch("B_eta",  &B_eta,  "B_eta/D");
  //  TBranch *b = tout->Branch("",  &,  "/F");


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

      float dca(999.0); float zca(999.0); float dcaerr(999.0); float zcaerr(999.0);
      int nclosetrksCustom(0); int nclosetrksNtuple(0);
      float docaNtuple(999.0); float docaCustom(999.0); 
      float docaDxAOD = sqrt( pow(closeTrkDCA, 2) + pow(closeTrkZCA, 2) );
      map<string, bool> associated;
      map<string, bool> pileup;
      map<string, bool> unassociated;
      associated.insert(pair<string, bool>("lastround", false));
      associated.insert(pair<string, bool>("custom", false));
      unassociated.insert(pair<string, bool>("lastround", false));
      pileup.insert(pair<string, bool>("lastround", false));
      pileup.insert(pair<string, bool>("custom", false));

      double ptsum_0p7(0.), ptsum_1p0(0.), ptsum_alar1(0.);

      for (unsigned int idx=0; idx<ntrks; idx++) {

	// skip signal tracks (Bsmumu channel as an example, add other tracks for other signatures!)
	//
	if ( (idx == B_IDtrk1_trkidx || idx == B_IDtrk2_trkidx) ) continue;

	// track quality cuts
	//
	TVector3 idtrk_p;
	idtrk_p.SetXYZ( (*idtrk_px).at(idx), (*idtrk_py).at(idx), (*idtrk_pz).at(idx) );
	if ( ( (*idtrk_nPIXhits).at(idx) + (*idtrk_nPIXDead).at(idx) )<1 || ( (*idtrk_nSCThits).at(idx) + (*idtrk_nSCTDead).at(idx) )<2 || (*idtrk_isLoose).at(idx)==0 || idtrk_p.Pt()<500 ) continue;

	// classify tracks by vertex association
	// 
	if ( (*idtrk_pvidx_lastround).at(idx) == B_PV_idx ) {
	  associated["lastround"]    = true;
	  pileup["lastround"]        = false;
	  unassociated["lastround"] = false;
	} else if ( (*idtrk_pvidx_lastround).at(idx) == pv_type->size()-1 ) {
	  associated["lastround"]    = false;
	  pileup["lastround"]        = false;
	  unassociated["lastround"] = true;
	} else {
	  associated["lastround"]    = false;
	  pileup["lastround"]        = true;
	  unassociated["lastround"] = false;
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
	  
	double deltaR = B_p.DeltaR(idtrk_p);
	
	if ( associated["custom"] ) {
	  if (deltaR < 1.0) ptsum_1p0 += idtrk_p.Pt();
	  if ((*B_VTX_trksChi2).at(idx)< 2.0) nclosetrksCustom++;
	  if ( (*B_VTX_trksChi2).at(idx) < 7.0) {
	    float DOCAtrk = sqrt( pow( (*closeTrkDCA_alltrks).at(idx), 2) + pow( (*closeTrkZCA_alltrks).at(idx), 2) );
	    if ( DOCAtrk < docaCustom) {
	      docaCustom = DOCAtrk;
	    }
	  }
	}
	
	if ( associated["lastround"] ) {
	  if (deltaR < 0.7) ptsum_0p7 += idtrk_p.Pt();
	  if ( (*B_VTX_trksChi2).at(idx) < 1.0) nclosetrksNtuple++;
	  if ( (*B_VTX_trksChi2).at(idx) < 7.0) {
	    float DOCAtrk = sqrt( pow( (*closeTrkDCA_alltrks).at(idx), 2) + pow( (*closeTrkZCA_alltrks).at(idx), 2) );
	    if ( DOCAtrk < docaNtuple) {
	      docaNtuple = DOCAtrk;
	    }
	  }
	}
	
	if ( (*B_PV_trksChi2).at(idx) < 5.0 && deltaR<0.7 ) {
	  ptsum_alar1 += idtrk_p.Pt();
	}

      } // tracks

    
      // isolation variable
      //
      if (h_iso_def) h_iso_def->Fill( B_iso_7_Chi2_5_LoosePt05,  ew );
      
      B_iso_7_Chi2_lastround_TTVA  = B_pT / (B_pT + ptsum_0p7);
      if (h_iso_0p7) h_iso_0p7->Fill( B_iso_7_Chi2_lastround_TTVA, ew );
      
      B_iso_10_Chi2_custom_TTVA = B_pT / (B_pT + ptsum_1p0);
      if (h_iso_1p0) h_iso_1p0->Fill( B_iso_10_Chi2_custom_TTVA, ew );
      
      B_iso_7_Chi2_alaRun1_TTVA = B_pT / (B_pT + ptsum_alar1);
      if (h_iso_alar1) h_iso_alar1->Fill( B_iso_7_Chi2_alaRun1_TTVA, ew );
      
      tout->Fill();

      // DOCA
      //

      if (h_docaDxAOD)  h_docaDxAOD->Fill(docaDxAOD);
      if (h_docaNtuple) h_docaNtuple->Fill(docaNtuple);
      if (h_docaCustom) h_docaCustom->Fill(docaCustom);
     
      // cout << "DOCA: " << docaDxAOD << " <-AOD|ntup-> "<< docamin << endl; //" DCA: "<< closeTrkDCA << " ZCA: "<< closeTrkZCA << endl; 

      // n close tracks
      //
      if (h_ntrksDxAOD)  h_ntrksDxAOD->Fill(closeTrkNtrksChi2);
      if (h_ntrksNtuple) h_ntrksNtuple->Fill(nclosetrksNtuple);
      if (h_ntrksCustom) h_ntrksCustom->Fill(nclosetrksCustom);
      // cout << "Ntrk: "<< closeTrkNtrksChi2 << " <-AOD|ntup-> "<< nclosetrksNtuple << endl;	    

    } // events

  cout << "done w loops" << endl;

  TCanvas* c = new TCanvas("alltrks","alltrks",900,600);
  c->Divide(2,2);
  c->cd(1);
  gPad->SetLogy();
  //gPad->SetPadTicksy(1);
  h_iso_def->Scale( 1./h_iso_def->Integral() );
  h_iso_0p7->Scale( 1./h_iso_0p7->Integral() );
  h_iso_1p0->Scale( 1./h_iso_1p0->Integral() );
  h_iso_alar1->Scale( 1./h_iso_alar1->Integral() );
  
  if (h_iso_def) hisoAll->Add(h_iso_def);
  if (h_iso_0p7) hisoAll->Add(h_iso_0p7);
  if (h_iso_1p0) hisoAll->Add(h_iso_1p0);
  if (h_iso_alar1) hisoAll->Add(h_iso_alar1);
  //    hisoAll->Draw("nostackY+");
  hisoAll->Draw("nostack");
  hisoAll->GetXaxis()->SetTitle("B iso");
  TLegend *leg1 = new TLegend(0.05,0.78,0.35,0.94);
  leg1->AddEntry(h_iso_def,"lastround DxAOD","l");
  leg1->AddEntry(h_iso_0p7,"lastround ntuple","l");
  leg1->AddEntry(h_iso_1p0,"min #chi^2 TTVA, cone 1.0","l");
  leg1->AddEntry(h_iso_alar1,"as in run 1","l");
  leg1->Draw();
  fout->cd();
  tout->Write();
  fout->Close();

  c->cd(2);
  if (h_ntrksDxAOD) hntrksAll->Add(h_ntrksDxAOD);
  if (h_ntrksNtuple) hntrksAll->Add(h_ntrksNtuple);
  if (h_ntrksCustom) hntrksAll->Add(h_ntrksCustom);
  hntrksAll->Draw("nostack");
  hntrksAll->GetXaxis()->SetTitle("Nclose trks");

  TLegend *leg2 = new TLegend(0.58,0.78,0.95,0.94);
  leg2->AddEntry(h_ntrksDxAOD,"from DxAOD","l");
  leg2->AddEntry(h_ntrksNtuple,"from ntuple","l");
  leg2->AddEntry(h_ntrksCustom,"custom from ntuple","l");
  leg2->Draw();

  c->cd(3);
  gPad->SetLogy();
  if (h_docaDxAOD) hdocaAll->Add(h_docaDxAOD);
  if (h_docaNtuple) hdocaAll->Add(h_docaNtuple);
  if (h_docaCustom) hdocaAll->Add(h_docaCustom);
  hdocaAll->Draw("nostack");
  hdocaAll->GetXaxis()->SetTitle("DOCA [mm]");

  TLegend *leg3 = new TLegend(0.58,0.78,0.95,0.94);
  leg3->AddEntry(h_docaDxAOD,"from DxAOD","l");
  leg3->AddEntry(h_docaNtuple,"from ntuple","l");
  leg3->AddEntry(h_docaCustom,"custom from ntuple","l");
  leg3->Draw();
  
 
  c->SaveAs("chi2.root");
  c->SaveAs("chi2.eps");  
  fs->Close();
  delete fs;
}
