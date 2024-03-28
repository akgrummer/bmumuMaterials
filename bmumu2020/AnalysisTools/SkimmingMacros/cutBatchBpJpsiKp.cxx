// cutBatchBpJpsiKp.cxx
// producing ntuples with final analysis cuts from pre-skimmed ones, normally produced on GRID 



// takes skimmed ntuples [on eos] as an input, loops over all root file in the directory (workdir) 
// applies Run 2 analysis cuts on BpJpsiKp channel, trigger and B-kinematic weights
// computes some (BDT) variables
// outputs skimmed flat ntuples to be used e.g. in data/MC comparisons 
// path format is for input */skimmed_ntup/* , for output: */final_ntup/*, final_ntup directory needs to be created!

// new_event_index variable is not reset when moving from one file to the next, in order to make
// connection to event tree useful if merging the output files together.
// This can be changed (i.e. reset can be introduced) - see FIXME in the code

// to run
// 1. specify outpath
// 2. do "make" or "make cutBatchBpJpsiKp.exe"
// 3. ./cutBatchBpJpsiKp.exe path/to/dataset

#include "TCut.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1.h"
#include "TH2.h"
#include "TBranch.h"
#include <iostream>
#include "TSystem.h"
#include "TLorentzVector.h"
#include "TStopwatch.h"
#include "DDWQLC.h"
#include "TriggerWeights.h"
#include <dirent.h>
#include <set>

using namespace std;
typedef std::vector<unsigned int>  v_uint;
typedef map<string, int>      map_str_int;
typedef std::vector<int>            v_int;
typedef std::vector<float>        v_float;
typedef std::vector<double>      v_double;


const float closeTrkDOCAdefault = -0.01; //FIXME - value not optimal for use in BDT
const bool debug = true;

bool hasEnding(std::string const &fullString, std::string const &ending) {
  if (fullString.length() >= ending.length()) {
    return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
  } else {
    return false;
  }
}

void cutBatchBpJpsiKp(TString workdir="") {
    if (workdir.EqualTo("")) workdir = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuRel21Prod1/ntup/skimmed_MC/BpJpsiKplus/v3/user.acampove.300404.BPHY8_FNTUP.e4862_e5984_a875_r9364_r9315_p3582_BJpsiK.root/";
  bool isMC(false);
  if ( workdir.Contains("mc16") || workdir.Contains("Loose_NTUP_MC") ) isMC = true;  // FIXME -> better


  TStopwatch sw;
  sw.Start();
  ////////////////////////////////////////////////////////
  // Reading weight files
  //
  // QLC
  TString QLCfileName = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/DDW/v6/QLCfile_BpToJpsiK.root";
  DDWQLC QLC(QLCfileName, "h_QLC_err_BpJpsiK", "h_QLC_BpJpsiK");
  // DDW
  TString DDWfileName = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/DDW/v6/DDWfile_BpToJpsiK.root";
  DDWQLC DDW(DDWfileName,  "h_covarianceDDW_even_BpJpsiK", "h_DDWpt_even_BpJpsiK", "h_DDWeta_even_BpJpsiK");
  cout << "INFO: Done reading QLC and DDW files." << endl;
  // trigger
  TriggerWeights myWeights("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/TriggerWeights/singleMu_SF_data1516_perperiod.root");
  cout << "INFO: Done reading trigger weight files." << endl;
  ////////////////////////////////////////////////////////

  int new_event_index = -1; //FIXME (needed when the output ntuples will be merged after processing, to have unique index)

  TString indir(workdir);
  TString outdir(workdir);
  outdir.ReplaceAll("Loose", "Nominal"); //only replacing the directory, the filename stays the same!

  if ( gSystem->AccessPathName(outdir) ) {
    cout << "Output folder " << outdir << " not existing, creating it." << endl;
    gSystem->Exec("mkdir " + outdir);
  }

  cout << "Looping over files in the directory: "<< indir <<endl;

  TString finpath(indir);
  DIR *dpdf;
  struct dirent *entry;

  dpdf = opendir(finpath.Data());

  if (dpdf != NULL){
    while (entry = readdir(dpdf)){

      printf("Filename: %s\n", entry->d_name);

      if ( !hasEnding(entry->d_name, ".root") )  continue;
      std::cout << "processing file: "<< entry->d_name << std::endl;

      TString fintemp(finpath);
      fintemp.Append(entry->d_name);
      TFile *fin = new TFile(fintemp);
      TTree *tin = (TTree*)fin->Get("T_mv");
      TTree *tev = (TTree*)fin->Get("EventInfo");
  
      cout<< "Entries in original tree: "<< tin->GetEntries() <<endl;
      auto nevents = tin->GetEntries();
 
      double K_pT, K_eta, K_phi, Jpsi_fitChi2;
      float B_VTX_mass;
      double B_pT, B_eta, Lxy, a_2D, DR, Muon1_pT, Muon2_pT, Muon1_eta, Muon2_eta;
      double B_fitChi2NDF, Jpsi_mass, CombWeights;
      double B_iso_7_Chi2_5_MedPt05, closeTrkDOCA, B_minChi2MuonsIPtoAnyPV;
      float closeTrkDCA, closeTrkZCA, B_iso_7_Chi2_5_LoosePt05, Bsmumu_minLogChi2ToAnyPV_PV_MIN_Z0_BA;
      int  B_iso_Ntracks_7_Chi2_5_MedPt05, B_iso_Ntracks_7_Chi2_5_LoosePt05, nphotons_b;
      UInt_t run_number=0; UInt_t previous_run_number=0;
      int K_pass(1), Jpsi_fitNDF, Muon1_accept(1), Muon2_accept(1), trigger_category(1);
      bool Muon1_isCombinedMuon, Muon2_isCombinedMuon, pass_grl(true), Muon1_isTight, Muon2_isTight;
      float muP_iso_7_Chi2_5_LoosePt05, muM_iso_7_Chi2_5_LoosePt05;
      double muM_iso_7_Chi2_5_medPt05, muP_iso_7_Chi2_5_medPt05;
      double TRUTH_MuMinus_pT, TRUTH_MuPlus_pT, TRUTH_MuMinus_eta, TRUTH_MuPlus_eta, TRUTH_K_eta, TRUTH_K_pT;
      int muP_iso_Ntracks_7_Chi2_5_LoosePt05, muM_iso_Ntracks_7_Chi2_5_LoosePt05, muM_iso_Ntracks_7_Chi2_5_medPt05, muP_iso_Ntracks_7_Chi2_5_medPt05;
      map_str_int *HLT_trigger = 0;
      map_str_int *L1_trigger = 0;
      string* decay = 0;
      bool is_2015, is_2016main, is_2016delayed, is_2017, is_2018, pass_trigger, pass_l1_trigger, Trigger_Matched;
      Float_t Muon1_trigger_sf, Muon1_trigger_sf_staterr, Muon1_trigger_sf_systerr;
      Float_t Muon2_trigger_sf, Muon2_trigger_sf_staterr, Muon2_trigger_sf_systerr; 
      int isSignal = 0; 
      int event_index = 0; //int new_event_index = -1; //FIXME
      ULong64_t event_number = 0; ULong64_t previous_event_number = 0;
      set<pair<unsigned int, unsigned long long> >evt_set;      

      // input file variables
      //
      tin->SetBranchAddress("B_VTX_mass",&B_VTX_mass);
      tin->SetBranchAddress("B_pT",&B_pT);
      tin->SetBranchAddress("B_eta",&B_eta);
      tin->SetBranchAddress("Lxy",&Lxy);
      tin->SetBranchAddress("a_2D",&a_2D);
      tin->SetBranchAddress("DR",&DR);
      tin->SetBranchAddress("Muon1_pT",&Muon1_pT);
      tin->SetBranchAddress("Muon1_eta",&Muon1_eta);
      tin->SetBranchAddress("Muon2_pT",&Muon2_pT);
      tin->SetBranchAddress("Muon2_eta",&Muon2_eta);
      tin->SetBranchAddress("B_fitChi2NDF",&B_fitChi2NDF);
      tin->SetBranchAddress("Muon1_isCombinedMuon",&Muon1_isCombinedMuon);
      tin->SetBranchAddress("Muon2_isCombinedMuon",&Muon2_isCombinedMuon);
      tin->SetBranchAddress("Muon1_accept",  &Muon1_accept);
      tin->SetBranchAddress("Muon2_accept",  &Muon2_accept);
      tin->SetBranchAddress("Muon1_isTight",  &Muon1_isTight);
      tin->SetBranchAddress("Muon2_isTight",  &Muon2_isTight);
      tin->SetBranchAddress("Jpsi_fitChi2",  &Jpsi_fitChi2);
      tin->SetBranchAddress("Jpsi_fitNDF",  &Jpsi_fitNDF);
      tin->SetBranchAddress("Jpsi_mass",  &Jpsi_mass);
      tin->SetBranchAddress("K_pass",  &K_pass);      
      tin->SetBranchAddress("run_number",  &run_number);
      tin->SetBranchAddress("event_number",  &event_number);
      tin->SetBranchAddress("Trigger_Matched",  &Trigger_Matched);
      if (isMC) {
	tin->SetBranchAddress("TRUTH_MuMinus_pT",  &TRUTH_MuMinus_pT);
	tin->SetBranchAddress("TRUTH_MuPlus_pT",  &TRUTH_MuPlus_pT);
	tin->SetBranchAddress("TRUTH_K_pT", &TRUTH_K_pT);
	tin->SetBranchAddress("TRUTH_MuMinus_eta",  &TRUTH_MuMinus_eta);
	tin->SetBranchAddress("TRUTH_MuPlus_eta",  &TRUTH_MuPlus_eta); 
	tin->SetBranchAddress("TRUTH_K_eta", &TRUTH_K_eta);
	//tin->SetBranchAddress("nphotons_b", &nphotons_b);   //select on # of photons
	tin->SetBranchAddress("CombWeights", &CombWeights);
	tin->SetBranchAddress("isSignal", &isSignal);
	//tin->SetBranchAddress("decay",&decay);              //NEEDED to select on combinatorics
      } else {
	tin->SetBranchAddress("pass_grl",  &pass_grl); 
      }

      tin->SetBranchAddress("K_pT",&K_pT);
      tin->SetBranchAddress("K_eta",&K_eta);
      tin->SetBranchAddress("K_phi",&K_phi);
      tin->SetBranchAddress("HLT_trigger",&HLT_trigger);
      tin->SetBranchAddress("L1_trigger",&L1_trigger);
      
      tin->SetBranchAddress("B_iso_7_Chi2_5_LoosePt05",  &B_iso_7_Chi2_5_LoosePt05);
      tin->SetBranchAddress("B_iso_Ntracks_7_Chi2_5_LoosePt05",  &B_iso_Ntracks_7_Chi2_5_LoosePt05);
      tin->SetBranchAddress("muP_iso_7_Chi2_5_LoosePt05",  &muP_iso_7_Chi2_5_LoosePt05);
      tin->SetBranchAddress("muP_iso_Ntracks_7_Chi2_5_LoosePt05",  &muP_iso_Ntracks_7_Chi2_5_LoosePt05);
      tin->SetBranchAddress("muM_iso_7_Chi2_5_LoosePt05",  &muM_iso_7_Chi2_5_LoosePt05);
      tin->SetBranchAddress("muM_iso_Ntracks_7_Chi2_5_LoosePt05",  &muM_iso_Ntracks_7_Chi2_5_LoosePt05);

      tin->SetBranchAddress("closeTrkDCA",  &closeTrkDCA);
      tin->SetBranchAddress("closeTrkZCA",  &closeTrkZCA);
      tin->SetBranchAddress("CombWeights",  &CombWeights);
      tin->SetBranchAddress("event_index",  &event_index);


      // preparing skimmed file
      //
      TString fouttemp(outdir);
      fouttemp.Append("LASTskim.");
      fouttemp.Append(entry->d_name);
      TFile *fout = new TFile(fouttemp, "recreate");
      TTree *tout = tin->CloneTree(0);
      TTree *tev_skimmed = tev->CloneTree(0);
      TBranch* b1 = tout->Branch("B_iso_7_Chi2_5_MedPt05",&B_iso_7_Chi2_5_MedPt05,"B_iso_7_Chi2_5_MedPt05/D");
      TBranch* b2 = tout->Branch("B_iso_Ntracks_7_Chi2_5_MedPt05",&B_iso_Ntracks_7_Chi2_5_MedPt05,"B_iso_Ntracks_7_Chi2_5_MedPt05/I");
      TBranch* b3 = tout->Branch("closeTrkDOCA",&closeTrkDOCA,"closeTrkDOCA/D");
      TBranch* b4 = tout->Branch("trigger_category",&trigger_category,"trigger_category/I");
      TBranch* b5 = tout->Branch("muM_iso_7_Chi2_5_medPt05",&muM_iso_7_Chi2_5_medPt05,"muM_iso_7_Chi2_5_medPt05/D");
      TBranch* b6 = tout->Branch("muM_iso_Ntracks_7_Chi2_5_medPt05",&muM_iso_Ntracks_7_Chi2_5_medPt05,"muM_iso_Ntracks_7_Chi2_5_medPt05/I");
      TBranch* b7 = tout->Branch("muP_iso_7_Chi2_5_medPt05",&muP_iso_7_Chi2_5_medPt05,"muP_iso_7_Chi2_5_medPt05/D");
      TBranch* b8 = tout->Branch("muP_iso_Ntracks_7_Chi2_5_medPt05",&muP_iso_Ntracks_7_Chi2_5_medPt05,"muP_iso_Ntracks_7_Chi2_5_medPt05/I");
      TBranch* b11= tout->Branch("Muon1_trigger_sf",&Muon1_trigger_sf,"Muon1_trigger_sf/F");
      TBranch* b12= tout->Branch("Muon2_trigger_sf",&Muon2_trigger_sf,"Muon2_trigger_sf/F");

      int status; 
      cout<< "Now loop over original candidate tree" << endl; 
      for (auto ievent=0; ievent<nevents; ievent++)
	{
	  if (ievent%100000==0) cout << "Processing event "<< ievent << endl;
	  tin->GetEntry(ievent);

	  //if (run_number!=XXXXXX && isMC) continue; //in case one wants to have smaller MC sample

	  if (Lxy<0. || TMath::Abs(a_2D)>1.0 || DR>1.5) continue;
	  if (B_VTX_mass<4930.0 || B_VTX_mass>5630.0) continue;
	  if (B_fitChi2NDF>6.0) continue;

	  is_2015        = (run_number <=284484);
	  is_2016main    = (run_number > 284484 && run_number < 302956);
	  is_2016delayed = (run_number >=302956 && run_number <=311481);
	  is_2017        = (run_number > 324320 && run_number <=341649);
	  is_2018        = (run_number > 348197 && run_number <=364485);
	  //
	  // 2015 HLT triggers
	  // pass_trigger = ( HLT_trigger->find("HLT_2mu4_bJpsimumu") != HLT_trigger->end() );
	  pass_trigger  = (is_2015 && HLT_trigger->find("HLT_mu6_mu4_bJpsimumu") != HLT_trigger->end() );
	  //
	  // 2016 HLT triggers
	  //
	  pass_trigger |= (is_2016main && HLT_trigger->find("HLT_mu6_mu4_bJpsimumu_Lxy0") != HLT_trigger->end() );
	  pass_trigger |= (is_2016delayed && HLT_trigger->find("HLT_mu6_mu4_bJpsimumu_Lxy0_delayed") != HLT_trigger->end() );
	  //
	  // 2017 and 2018 HLT triggers
	  //
	  // pass_trigger |= ( (is_2017 || is_2018) && HLT_trigger->find("HLT_mu6_mu4_bJpsimumu_Lxy0_L1BPH-2M9-MU6MU4_BPH-0DR15-MU6MU4") != HLT_trigger->end());
	  pass_trigger |= ( (is_2017 || is_2018) && HLT_trigger->find("HLT_2mu6_bJpsimumu_Lxy0_L1BPH-2M9-2MU6_BPH-2DR15-2MU6") != HLT_trigger->end());

	  // L1 triggers
	  // 2015 and 2016 
	  //
	  pass_l1_trigger = ( (is_2015 || is_2016main || is_2016delayed) && L1_trigger->find("L1_MU6_2MU4") != L1_trigger->end() );
	  // L1 triggers
	  // L1Topo (2017 and 2018) 
	  //
	  //pass_l1_trigger |= ( (is_2017 || is_2018) && L1_trigger->find("L1_BPH-2M9-MU6MU4_BPH-0DR15-MU6MU4") != L1_trigger->end() );
	  pass_l1_trigger |= ( (is_2017 || is_2018) && L1_trigger->find("L1_BPH-2M9-2MU6_BPH-2DR15-2MU6") != L1_trigger->end() );

	  pass_trigger    &= pass_l1_trigger;
	  if (!pass_trigger) continue;

	  if (Jpsi_fitChi2/(1.0*Jpsi_fitNDF)>10.0 || Jpsi_mass<2915.0 || Jpsi_mass>3275.0) continue;
	  if (K_pT<1000. || TMath::Abs(K_eta)>2.5 || !K_pass) continue;
	  if (B_pT<8000. || TMath::Abs(B_eta)>2.5) continue;
	  if (!Muon1_accept || !Muon2_accept || !Muon1_isCombinedMuon || !Muon2_isCombinedMuon) continue;
	  if (!Muon1_isTight || !Muon2_isTight) continue;
	  //
	  // mimicking trigger cuts in offline selections (should much the trigger selection above)
	  //
	  if (Muon1_pT<4000. || Muon2_pT<4000. || (Muon1_pT<6000. && Muon2_pT<6000.) || TMath::Abs(Muon1_eta)>2.5 || TMath::Abs(Muon2_eta)>2.5) continue;
	  //if (Muon1_pT<6000. || Muon2_pT<6000. || TMath::Abs(Muon1_eta)>2.5 || TMath::Abs(Muon2_eta)>2.5) continue;

	  if (!Trigger_Matched) continue; //implemented/works for delayed stream?
	  if (!pass_grl) continue;
    
	  
	  if (isMC) {
	    //if (nphotons_b>0) continue; //select NORAD ONLY
	    //if ((*decay) != "combinatorial") continue; //select COMBINATORIAL ONLY
	    //if (TRUTH_MuMinus_pT<3500. || TRUTH_MuPlus_pT<3500. || fabs(TRUTH_MuPlus_eta)>3.0 || fabs(TRUTH_MuMinus_eta)>3.0) continue; //mimick bbmumuX generator cuts
	    if ( isSignal!=1 ) continue;

	    if ( TRUTH_MuPlus_pT<3500. || TMath::Abs(TRUTH_MuPlus_eta)>2.6 
		 || TRUTH_MuMinus_pT<3500. || TMath::Abs(TRUTH_MuMinus_eta)>2.6
		 || TRUTH_K_pT<500. || TMath::Abs(TRUTH_K_eta)>2.5 ) continue; //mimick generation cuts

	    double QLCval = QLC.GetWeight(TMath::Abs(B_eta), B_pT);
	    double DDWval = DDW.GetWeight(TMath::Abs(B_eta), B_pT);
	    CombWeights = DDWval * QLCval;

	    float pTThreshold1 = 4.0;
	    float pTThreshold2 = 6.0;
	    if (Muon1_pT > Muon2_pT) {
	      pTThreshold1 = 6.0;
	      pTThreshold2 = 4.0;
	    }
	    status = myWeights.GetWeight( Muon1_pT/1000., Muon1_eta,  1. ,run_number, pTThreshold1, Muon1_trigger_sf, Muon1_trigger_sf_staterr, Muon1_trigger_sf_systerr);
	    if (status<0) cout << "INFO: trigger weights status " << status << " for Muon1 (mu+)" << endl;
	    status = myWeights.GetWeight( Muon2_pT/1000., Muon2_eta, -1. ,run_number, pTThreshold2, Muon2_trigger_sf, Muon2_trigger_sf_staterr, Muon2_trigger_sf_systerr);
	    if (status<0) cout << "INFO: trigger weights status " << status << " for Muon2 (mu-)" << endl;
	  }

	  B_iso_7_Chi2_5_MedPt05 = (double)B_iso_7_Chi2_5_LoosePt05;
	  B_iso_Ntracks_7_Chi2_5_MedPt05 = B_iso_Ntracks_7_Chi2_5_LoosePt05;
	  muM_iso_7_Chi2_5_medPt05 = (double)muM_iso_7_Chi2_5_LoosePt05;
	  muM_iso_Ntracks_7_Chi2_5_medPt05 = muM_iso_Ntracks_7_Chi2_5_LoosePt05;
	  muP_iso_7_Chi2_5_medPt05 = (double)muP_iso_7_Chi2_5_LoosePt05;
	  muP_iso_Ntracks_7_Chi2_5_medPt05 = muP_iso_Ntracks_7_Chi2_5_LoosePt05;

	  if (TMath::Abs(closeTrkDCA)==999.0) {
	    cout << "INFO: found invalid value for closeTrkDOCA variable, correcting it to "<<  closeTrkDOCAdefault << endl;
	    closeTrkDOCA = closeTrkDOCAdefault;
	  } else closeTrkDOCA = (double)sqrt(pow(closeTrkDCA,2)+pow(closeTrkZCA,2));

	  if (event_number != previous_event_number || run_number != previous_run_number) new_event_index++;
	  event_index = new_event_index;
	  tout->Fill();
	  evt_set.insert( make_pair(run_number, event_number) );
	  previous_event_number = event_number;
	  previous_run_number = run_number;
	}
      cout<< "Entries in final tree: "<< tout->GetEntries() <<endl;
      if (!tout->GetEntries()) {
	cout<< "No BJpsiK candidates, closing the files without writing, continuing. "<< endl;
	fout->cd();
	fout->Close();
	fin->cd();
	fin->Close();
	continue;
      }
 
      cout<< "Now loop over original event tree" << endl;
      cout<< "Entries in original event tree: "<< tev->GetEntries() <<endl;
      nevents = tev->GetEntries();
      tev->SetBranchAddress("run_number",   &run_number);
      tev->SetBranchAddress("event_number", &event_number);
      for (auto ievent=0; ievent<nevents; ievent++)
        {
          if (ievent%100000==0) cout << "Processing event "<< ievent << endl;
          tev->GetEntry(ievent);
	  //if (run_number!=XXXXXX && isMC) continue; //for smaller MC sample
	  if ( evt_set.find( make_pair(run_number, event_number) ) == evt_set.end() ) continue;
	  tev_skimmed->Fill();
	}
      cout<< "Entries in final event tree: "<< tev_skimmed->GetEntries() <<endl;

      fout->cd();
      tout->Write();
      tev_skimmed->Write();
      fout->Close();
      fin->cd();
      fin->Close();
      //break; //(to test on one file only)
    }
  }
  closedir(dpdf);

  sw.Stop();
  sw.Print();
}

int main(int argc, char* argv[])
{
  gSystem->Load("libdefinitions.so");
  TString inpath;
  if (argc>1) inpath = TString(argv[1]);
  cutBatchBpJpsiKp(inpath);
  return 0;
}
