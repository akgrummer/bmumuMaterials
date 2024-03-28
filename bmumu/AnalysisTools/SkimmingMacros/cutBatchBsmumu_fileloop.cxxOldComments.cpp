//
// example how to loop over files in a directory
// author: iskander(dot)ibragimov(at)cern(dot)ch
//
// to run:
// g++ cutBatchBsmumu_fileloop.cxx -o cutBatchBsmumu_fileloop `root-config --glibs --cflags`
// ./cutBatchBsmumu_fileloop input_folder output_folder_tag
//
// the input folder should contain the ntuple files and this code loops over multiple files
// the output_folder_tag is a data variant, ie 2017 or MC16d  and it must correspond to a  
//          pre-existing directory location that starts with "outdir" variable below
//          and ends with the data variant

//Updates 2020Feb11:
// removed the copy of the Biso, BisoNtracks, and mu iso variables with loosePt05 to medPt05 
//
// renamed these four variables: muP_iso_7_chi2_5_LoosePt05, muM_iso_7_chi2_5_LoosePt05 to
// muP_iso_7_Chi2_5_LoosePt05 muM_iso_7_Chi2_5_LoosePt05


#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TChain.h"
#include <iostream>
#include <dirent.h>
using namespace std;
typedef map<string, int>      map_str_int;

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

void loopFiles(TString indir, TString filter=""){

  // TString indir("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/skimmed_ntup/data18/Bmumu/");
  TString finpath(indir);
  // TString outdir("/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkimOne2018Run");
  // TString outdir("/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkim2018_2019Mar7");
  // TString outdir("/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkim_2019Mar27");
  // TString outdir("/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr");
  //renamed folder /eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr 
  //            to /eos/home-a/agrummer/BsmumuData/FinalSkim/v3
  // TString outdir("/eos/home-a/agrummer/BsmumuData/FinalSkim/v4");
  // TString outdir("/eos/home-a/agrummer/BsmumuData/FinalSkim/v5");//v5 includes isLoose, nDeadPix, nDeadSCT
  // TString outdir("/eos/home-a/agrummer/BsmumuData/FinalSkim/v6");//v6 includes updated z0 err (approx. to derivation)
  TString outdir("/eos/home-a/agrummer/BsmumuData/2020nTuples/FinalSkim/v1");//2020/v1 includes updated z0 err (approx. to derivation)
  TString foutpath(outdir);
  DIR *dpdf;
  struct dirent *entry;
  Int_t cnt(1);
  dpdf = opendir(finpath.Data());

  if (dpdf != NULL){
    while (entry = readdir(dpdf)){

      printf("Filename: %s\n", entry->d_name);

      if ( !hasEnding(entry->d_name, ".root") )  continue;  // exclude non-ROOT files 
     
      std::cout << "processing file: "<< entry->d_name << std::endl;
        foutpath = outdir;
        foutpath.Append(Form("/%s", filter.Data()));
        foutpath.Append(Form("/LASTskim_%s", filter.Data()));
        foutpath.Append(Form("_%i",cnt)); 
        foutpath.Append(".root");

      TString fintemp(finpath);
      fintemp.Append(entry->d_name);
      TFile *fin = new TFile(fintemp);
      TTree *ts = (TTree*)fin->Get("T_mv");
      TTree *tev = (TTree*)fin->Get("EventInfo");
      // TChain *tev = new TChain("EventInfo");
      // tev->Add(finpath);

      std::cout << "# of candidates: "<<  ts->GetEntries() << std::endl;
      /*
      TTree *t1 = (TTree*)fin->Get("Metadata");
      TTree *t2 = (TTree*)fin->Get("EventInfo");
      TTree *t3 = (TTree*)fin->Get("TRUTHDECAY");
      */
// cout<< "Entries in original tree: "<< ts->GetEntries() <<endl;
  auto nevents = ts->GetEntries();
  auto neventsInfo = tev->GetEntries();

  //tn->SetBranchStatus("*",0);
  double KPlus_pT, KPlus_eta, KPlus_phi, KMinus_pT, KMinus_eta, KMinus_phi, Jpsi_fitChi2;
  float B_MUCALC_mass;
  double  B_pT, B_eta, Lxy, a_2D, DR, Muon1_pT, Muon2_pT, Muon1_eta, Muon2_eta;
  double B_fitChi2NDF, Jpsi_mass, CombWeights;
  double B_iso_7_Chi2_5_MedPt05;
  double closeTrkDOCA, B_minChi2MuonsIPtoAnyPV;
  float closeTrkDCA, closeTrkZCA, B_iso_7_Chi2_5_LoosePt05, Bsmumu_minLogChi2ToAnyPV_PV_MIN_Z0_BA;
  int  B_iso_Ntracks_7_Chi2_5_MedPt05;
  int B_iso_Ntracks_7_Chi2_5_LoosePt05, nphotons_b;
  UInt_t run_number;
  int KMinus_pass,KPlus_pass,Jpsi_fitNDF, Muon1_accept, Muon2_accept, trigger_category(1);
  bool Muon1_isCombinedMuon, Muon2_isCombinedMuon, pass_grl(true), Muon1_isTight, Muon2_isTight;
  float muP_iso_7_Chi2_5_LoosePt05, muM_iso_7_Chi2_5_LoosePt05;
  double muM_iso_7_chi2_5_medPt05, muP_iso_7_chi2_5_medPt05;
  double TRUTH_MuMinus_pT, TRUTH_MuPlus_pT, TRUTH_MuMinus_eta, TRUTH_MuPlus_eta;
  int muP_iso_Ntracks_7_Chi2_5_LoosePt05, muM_iso_Ntracks_7_Chi2_5_LoosePt05;
  int muM_iso_Ntracks_7_chi2_5_medPt05, muP_iso_Ntracks_7_chi2_5_medPt05;
  map_str_int *HLT_trigger = 0;
  map_str_int *L1_trigger = 0;
  // string* decay = 0;
  bool is_2015, is_2016main, pass_trigger, Trigger_Matched;
  Float_t Muon1_trigger_sf, Muon1_trigger_sf_staterr, Muon1_trigger_sf_systerr;
  Float_t Muon2_trigger_sf, Muon2_trigger_sf_staterr, Muon2_trigger_sf_systerr;
  int event_index(0); 
  v_uint   *pv_type     = 0;
  v_float  *pv_z        = 0;
  v_float  *pv_sigma_z  = 0;
  v_int    *idtrk_pvidx = 0;


  ts->SetBranchAddress("B_MUCALC_mass",&B_MUCALC_mass);
  ts->SetBranchAddress("B_pT",&B_pT);
  ts->SetBranchAddress("B_eta",&B_eta);
  ts->SetBranchAddress("Lxy",&Lxy);
  ts->SetBranchAddress("a_2D",&a_2D);
  ts->SetBranchAddress("DR",&DR);
  ts->SetBranchAddress("Muon1_pT",&Muon1_pT);
  ts->SetBranchAddress("Muon1_eta",&Muon1_eta);
  ts->SetBranchAddress("Muon2_pT",&Muon2_pT);
  ts->SetBranchAddress("Muon2_eta",&Muon2_eta);
  ts->SetBranchAddress("B_fitChi2NDF",&B_fitChi2NDF);
  ts->SetBranchAddress("Muon1_isCombinedMuon",&Muon1_isCombinedMuon);
  ts->SetBranchAddress("Muon2_isCombinedMuon",&Muon2_isCombinedMuon);
  ts->SetBranchAddress("Muon1_accept",  &Muon1_accept);
  ts->SetBranchAddress("Muon2_accept",  &Muon2_accept);
  ts->SetBranchAddress("Muon1_isTight",  &Muon1_isTight);
  ts->SetBranchAddress("Muon2_isTight",  &Muon2_isTight);
  ts->SetBranchAddress("run_number",  &run_number);
  ts->SetBranchAddress("Trigger_Matched",  &Trigger_Matched);
  /*
  ts->SetBranchAddress("TRUTH_MuMinus_pT",  &TRUTH_MuMinus_pT);
  ts->SetBranchAddress("TRUTH_MuPlus_pT",  &TRUTH_MuPlus_pT);
  ts->SetBranchAddress("TRUTH_MuMinus_eta",  &TRUTH_MuMinus_eta);
  ts->SetBranchAddress("TRUTH_MuPlus_eta",  &TRUTH_MuPlus_eta); 
  */
  //  ts->SetBranchAddress("pass_grl",  &pass_grl); //FIXME mystyle
  ts->SetBranchAddress("HLT_trigger",&HLT_trigger);
  ts->SetBranchAddress("L1_trigger",&L1_trigger);

  ts->SetBranchAddress("B_iso_7_Chi2_5_LoosePt05",  &B_iso_7_Chi2_5_LoosePt05);
  ts->SetBranchAddress("B_iso_Ntracks_7_Chi2_5_LoosePt05",  &B_iso_Ntracks_7_Chi2_5_LoosePt05);
  ts->SetBranchAddress("muP_iso_7_Chi2_5_LoosePt05",  &muP_iso_7_Chi2_5_LoosePt05);
  ts->SetBranchAddress("muP_iso_Ntracks_7_Chi2_5_LoosePt05",  &muP_iso_Ntracks_7_Chi2_5_LoosePt05);
  ts->SetBranchAddress("muM_iso_7_Chi2_5_LoosePt05",  &muM_iso_7_Chi2_5_LoosePt05);
  ts->SetBranchAddress("muM_iso_Ntracks_7_Chi2_5_LoosePt05",  &muM_iso_Ntracks_7_Chi2_5_LoosePt05);

  ts->SetBranchAddress("closeTrkDCA",  &closeTrkDCA);
  ts->SetBranchAddress("closeTrkZCA",  &closeTrkZCA);
  //  ts->SetBranchAddress("nphotons_b", &nphotons_b);
  ts->SetBranchAddress("CombWeights", &CombWeights);
  // ts->SetBranchAddress("decay",&decay);  //NEEDED to select on combinatorics
  ts->SetBranchAddress("event_index",  &event_index);                           // index to EventInfo tree


  tev->SetBranchAddress("pv_z", &pv_z);
  tev->SetBranchAddress("pv_sigma_z", &pv_sigma_z);
  tev->SetBranchAddress("pv_type", &pv_type);
  tev->SetBranchAddress("idtrk_pvidx", &idtrk_pvidx);


      TFile *fn = new TFile(foutpath,"recreate");
      TTree *tf = ts->CloneTree(0);
  TBranch* b1 = tf->Branch("B_iso_7_Chi2_5_MedPt05",&B_iso_7_Chi2_5_MedPt05,"B_iso_7_Chi2_5_MedPt05/D");
  TBranch* b2 = tf->Branch("B_iso_Ntracks_7_Chi2_5_MedPt05",&B_iso_Ntracks_7_Chi2_5_MedPt05,"B_iso_Ntracks_7_Chi2_5_MedPt05/I");
  TBranch* b3 = tf->Branch("closeTrkDOCA",&closeTrkDOCA,"closeTrkDOCA/D");
  TBranch* b4 = tf->Branch("trigger_category",&trigger_category,"trigger_category/I");
  TBranch* b5 = tf->Branch("muM_iso_7_chi2_5_medPt05",&muM_iso_7_chi2_5_medPt05,"muM_iso_7_chi2_5_medPt05/D");
  TBranch* b6 = tf->Branch("muM_iso_Ntracks_7_chi2_5_medPt05",&muM_iso_Ntracks_7_chi2_5_medPt05,"muM_iso_Ntracks_7_chi2_5_medPt05/I");
  TBranch* b7 = tf->Branch("muP_iso_7_chi2_5_medPt05",&muP_iso_7_chi2_5_medPt05,"muP_iso_7_chi2_5_medPt05/D");
  TBranch* b8 = tf->Branch("muP_iso_Ntracks_7_chi2_5_medPt05",&muP_iso_Ntracks_7_chi2_5_medPt05,"muP_iso_Ntracks_7_chi2_5_medPt05/I");
  TBranch* b11= tf->Branch("Muon1_trigger_sf",&Muon1_trigger_sf,"Muon1_trigger_sf/F");
  TBranch* b12= tf->Branch("Muon2_trigger_sf",&Muon2_trigger_sf,"Muon2_trigger_sf/F");
  //  TBranch* b1 =tn->Branch("",&,"/D");
  // TTree *tevf = tev->CloneTree(0);
  // tevf->SetBranchStatus("*",0);//?aidan: do i need?

  int status;
  cout<< "Now loop over original tree" << endl; 
  Int_t MassWindowCut(0);
  Int_t BlindCut(0);
  Int_t sigPreCut(0);
  Int_t TriggerCut(0);
  Int_t MuonTightCut(0);
  // Int_t MuonCombinedCut(0);
  Int_t MuonKinCuts(0);
  Int_t BKinCut(0);
  Int_t B_fitChi2NDFCut(0);
  Int_t AddCuts(0);
  Int_t grlCut(0);
  for (auto ievent=0; ievent<nevents; ievent++)
    {
      if (ievent%100000==0) cout << "Processing event "<< ievent << endl;
      ts->GetEntry(ievent);
      // tev->GetEntry(event_index);//?aidan: do i need?


      if (B_MUCALC_mass<4766.0 || B_MUCALC_mass>5966.0){ 
        MassWindowCut+=1;
        continue;} 
      if(!filter.Contains("MC")){  
            if (B_MUCALC_mass>=5166.0 && B_MUCALC_mass<=5526.0){ 
              BlindCut+=1;
              continue;}
      }

      // is_2015        = (run_number <= 284484);
      // is_2016main    = (run_number > 284484 );
      // pass_trigger  = ( is_2015 && HLT_trigger->find("HLT_mu6_mu4_bBmumu") != HLT_trigger->end());
      // pass_trigger |= ( is_2016main && HLT_trigger->find("HLT_mu6_mu4_bBmumu_Lxy0") != HLT_trigger->end()); 
      //2016
      if(filter.Contains("2016") || filter.Contains("MC16a")){
      pass_trigger = ( HLT_trigger->find("HLT_mu6_mu4_bBmumu_Lxy0") != HLT_trigger->end()); 
      pass_trigger &= ( L1_trigger->find("L1_MU6_2MU4") != L1_trigger->end() );
      }
      else{
      //2017 and 2018
      pass_trigger = ( HLT_trigger->find("HLT_mu6_mu4_bBmumu_Lxy0_L1BPH-2M9-MU6MU4_BPH-0DR15-MU6MU4") != HLT_trigger->end());
      pass_trigger &= ( L1_trigger->find("L1_BPH-2M9-MU6MU4_BPH-0DR15-MU6MU4") != L1_trigger->end() );
      }
      if (!pass_trigger){
            TriggerCut+=1;
            continue;}
      if (!Trigger_Matched){
            TriggerCut+=1;
            continue;}


      if (!Muon1_isTight || !Muon2_isTight) {
        MuonTightCut+=1;
        continue;}
      if (!Muon1_accept || !Muon2_accept || 
        !Muon1_isCombinedMuon || !Muon2_isCombinedMuon) continue;
        //each muon pT must be greater than 4GeV
        //one of the muon pTs needs to be greater than 6GeV
        // ie they cannot both be less than 6GeV
      if (Muon1_pT<4000. || Muon2_pT<4000. || (Muon1_pT<6000. && Muon2_pT<6000.) || TMath::Abs(Muon1_eta)>2.5 || TMath::Abs(Muon2_eta)>2.5) {
        MuonKinCuts+=1;
        continue;}

      if (B_fitChi2NDF>6.0) {
        B_fitChi2NDFCut+=1;
        continue;}
      
      if (B_pT<8000. || TMath::Abs(B_eta)>2.5) {
        BKinCut+=1;
        continue;}

      if (Lxy<0. || TMath::Abs(a_2D)>1.0 || DR>1.5) {
        AddCuts+=1;
      continue;} 

      if (!pass_grl) {
        grlCut+=1;
        continue;}
    
      //if (nphotons_b>0) continue; //FIXME MC NORAD ONLY
      //if ((*decay) != "combinatorial") continue; //FIXME

      //FIXME blinded DATA ONLY
     
      //      if (TRUTH_MuMinus_pT<3500. || TRUTH_MuPlus_pT<3500. || fabs(TRUTH_MuPlus_eta)>3.0 || fabs(TRUTH_MuMinus_eta)>3.0) continue; //FIXME bbmumuX
  
      //FIXME MC Sigonly
      //
      /*
      double QLCval = QLC.GetWeight(TMath::Abs(B_eta), B_pT);
      double DDWval = DDW.GetWeight(B_eta, B_pT);
      CombWeights = DDWval * QLCval;
      */
      /* FIXME MC
      float pTThreshold1 = 4.0;
      float pTThreshold2 = 6.0;
      if (Muon1_pT > Muon2_pT) {
    pTThreshold1 = 6.0;
    pTThreshold2 = 4.0;
      }
      status = myWeights.GetWeight( Muon1_pT/1000., Muon1_eta,  1. ,run_number, pTThreshold1, Muon1_trigger_sf, Muon1_trigger_sf_staterr, Muon1_trigger_sf_systerr);
      //if (status<0) cout << "status " << status << " for Muon1 (mu+)" << endl;
      status = myWeights.GetWeight( Muon2_pT/1000., Muon2_eta, -1. ,run_number, pTThreshold2, Muon2_trigger_sf, Muon2_trigger_sf_staterr, Muon2_trigger_sf_systerr);
      //if (status<0) cout << "status " << status << " for Muon2 (mu-)" << endl;
      */
      B_iso_7_Chi2_5_MedPt05 = (double)B_iso_7_Chi2_5_LoosePt05;
      B_iso_Ntracks_7_Chi2_5_MedPt05 = B_iso_Ntracks_7_Chi2_5_LoosePt05;
      muM_iso_7_chi2_5_medPt05 = (double)muM_iso_7_Chi2_5_LoosePt05;
      muM_iso_Ntracks_7_chi2_5_medPt05 = muM_iso_Ntracks_7_Chi2_5_LoosePt05;
      muP_iso_7_chi2_5_medPt05 = (double)muP_iso_7_Chi2_5_LoosePt05;
      muP_iso_Ntracks_7_chi2_5_medPt05 = muP_iso_Ntracks_7_Chi2_5_LoosePt05;
      if (TMath::Abs(closeTrkDCA)==999.0) closeTrkDOCA = -0.01;  //FIXME DOCA
      else closeTrkDOCA = (double)sqrt(pow(closeTrkDCA,2)+pow(closeTrkZCA,2));
      tf->Fill();
    }

    cout<< "Entries in final tree: "<< tf->GetEntries() <<endl;

    cout<< "MassWindowCut: " << MassWindowCut<< endl;
    cout<< "BlindCut: " << BlindCut<< endl;
    cout<< "sigPreCut: " << sigPreCut<< endl;
    cout<< "TriggerCut: " << TriggerCut<< endl;
    cout<< "MuonTightCut: " << MuonTightCut<< endl;
    // cout<< MuonCombinedCut<< endl;
    cout<< "MuonKinCuts: "<<MuonKinCuts<< endl;
    cout<< "BKinCut: "<<BKinCut<< endl;
    cout<< "B_fitChi2NDFCut: "<<B_fitChi2NDFCut<< endl;
    cout<< "AddCuts: "<<AddCuts<< endl;
    cout<< "grlCut: "<<grlCut<< endl;


      fn->cd();
      // fn->Write();
      tf->Write();
      tev->CloneTree()->Write();
      // tevf->Write();
      fin->Close();
      fn->Close();
    cout<<"Wrote file: "<<foutpath<<endl; 
      cnt+=1;
    } // end of while (entry = readdir(dpdf)){ around line 53
  } //end of if (dpdf != NULL){ around line 52
  closedir(dpdf);

} //end of "loopFiles" around line 34

int main(int argc, char* argv[])
{
  TString inpath, pattern;
  if (argc>1) inpath = TString(argv[1]);
  if (argc>2) pattern = TString(argv[2]);
  loopFiles(inpath, pattern);
  return 0;
}
