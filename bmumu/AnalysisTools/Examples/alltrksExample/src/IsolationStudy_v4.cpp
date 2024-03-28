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
        indir = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkim_2019Mar27/2017/";
        AllPath = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/2017All/";
  }else if (myYear.EqualTo("2018")){
        // indir = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkim2018_2019Mar7/";
        indir = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkim_2019Mar27/2018/";
        AllPath = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/2018All/";
  }else if (myYear.EqualTo("2016")){
        indir = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/2016/";
        AllPath = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/2016All/";
  }else if (myYear.EqualTo("MC16a")){
        indir = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkim_2019Mar27/MC16a/";
        AllPath = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/MC16aAll/";
  }else if (myYear.EqualTo("MC16d")){
        indir = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkim_2019Mar27/MC16d/";
        AllPath = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/MC16dAll/";
  }else if (myYear.EqualTo("MC16e")){
        indir = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkim_2019Mar27/MC16e/";
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
        newfname.Append("_2019Apr29.root");
        newfname.ReplaceAll(indir, AllPath);
        // TString fout(AllPath)
        if (newfname.Contains(indir)){
            cout<<"error: new file name contains indir!"<<endl;
            break;
        }
        TFile *fUpdate = new TFile(newfname,"recreate");
        TTree *tUpdate = ts->CloneTree(0);

        // TTree *tNew = tUpdate->CloneTree(0);
        float B_iso_7_Chi2_5_LoosePt05_AllTrks(0.);
        float B_iso_7_Chi2_5_LoosePt05_Aidan(0.);
        int B_iso_Ntracks_7_Chi2_5_LoosePt05_AllTrks(0.);
        int B_iso_Ntracks_7_Chi2_5_LoosePt05_Aidan(0.);
        int closeTrkNtrksChi2_AllTrks(0);
        int closeTrkNtrksChi2_Aidan(0);
        float closeTrkDOCA(0.);
        float closeTrkDOCA_AllTrks2(0.);
        float closeTrkDOCA_Aidan(0.);
        // double B_minChi2MuonsIPtoAnyPV_AllTrks(0.);

        TBranch *iso_AllTrks = tUpdate->Branch("B_iso_7_Chi2_5_LoosePt05_AllTrks",&B_iso_7_Chi2_5_LoosePt05_AllTrks,"B_iso_7_Chi2_5_LoosePt05_AllTrks/F");
        TBranch *iso_Aidan = tUpdate->Branch("B_iso_7_Chi2_5_LoosePt05_Aidan",&B_iso_7_Chi2_5_LoosePt05_Aidan,"B_iso_7_Chi2_5_LoosePt05_Aidan/F");
        TBranch *isoNTrks_AllTrks = tUpdate->Branch("B_iso_Ntracks_7_Chi2_5_LoosePt05_AllTrks",&B_iso_Ntracks_7_Chi2_5_LoosePt05_AllTrks,"B_iso_Ntracks_7_Chi2_5_LoosePt05_AllTrks/I");
        TBranch *isoNTrks_Aidan = tUpdate->Branch("B_iso_Ntracks_7_Chi2_5_LoosePt05_Aidan",&B_iso_Ntracks_7_Chi2_5_LoosePt05_Aidan,"B_iso_Ntracks_7_Chi2_5_LoosePt05_Aidan/I");
        TBranch *Branch_closeTrkNtrks_AllTrks = tUpdate->Branch("closeTrkNtrksChi2_AllTrks",&closeTrkNtrksChi2_AllTrks,"closeTrkNtrksChi2_AllTrks/I");
        TBranch *Branch_closeTrkNtrks_Aidan = tUpdate->Branch("closeTrkNtrksChi2_Aidan",&closeTrkNtrksChi2_Aidan,"closeTrkNtrksChi2_Aidan/I");
        TBranch *Branch_closeTrkDOCA = tUpdate->Branch("closeTrkDOCA",&closeTrkDOCA,"closeTrkDOCA/F");
        TBranch *Branch_closeTrkDOCA_AllTrks2 = tUpdate->Branch("closeTrkDOCA_AllTrks2",&closeTrkDOCA_AllTrks2,"closeTrkDOCA_AllTrks2/F");
        TBranch *Branch_closeTrkDOCA_Aidan = tUpdate->Branch("closeTrkDOCA_Aidan",&closeTrkDOCA_Aidan,"closeTrkDOCA_Aidan/F");
        // TBranch *Branch_B_minChi2MuonsIPtoAnyPV_AllTrks = tUpdate->Branch("B_minChi2MuonsIPtoAnyPV_AllTrks",&B_minChi2MuonsIPtoAnyPV_AllTrks,"B_minChi2MuonsIPtoAnyPV_AllTrks/D");




  v_uint   *pv_type     = 0;
  v_float  *pv_z        = 0;
  v_float  *pv_sigma_z  = 0;
  v_int    *idtrk_pvidx = 0; 
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

  Double_t tracksPt_aidan(0.);

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


for (auto ievent=0; ievent<nevents; ievent++)
    {
        cntUpdate+=1;
        B_iso_7_Chi2_5_LoosePt05_AllTrks=-1;
        if (ievent%1000==0) cout << "Processing event "<< ievent << " -- total events: "<< cntUpdate << endl;
        // tFrame->GetEntry(cntUpdate); //for filling new branch
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
        //Default calculation repeats!
        int tracksCnt_aidan_ID_chi_5(0);
        int nclosetrks_aidan(0);
        tracksPt_aidan=0.;
        float docamin_aidan(999.0);



        // float DOCA = sqrt( pow(closeTrkDCA, 2) + pow(closeTrkZCA, 2) );
        myBVec.SetPtEtaPhi(B_pT,B_eta,B_phi);
        for (unsigned int idx=0; idx<ntrks; idx++) 
        {
            // skip signal tracks (Bsmumu channel as an example, add other tracks for other signatures!)
            //
            if (idx == B_IDtrk1_trkidx || idx == B_IDtrk2_trkidx) continue; 

            myTrkVec.SetXYZ((*idtrk_px).at(idx),(*idtrk_py).at(idx),(*idtrk_pz).at(idx));
            //for B Iso
            if ((*B_PV_trksChi2).at(idx)<5. 
                 && myTrkVec.Pt()>500.
               ){
                    if (((*idtrk_nPIXhits).at(idx) - (*idtrk_NIBLayer).at(idx))>=1
                        && (*idtrk_nSCThits).at(idx)>=2
                    ){
                        if (myTrkVec.DeltaR(myBVec) < 0.7){
                            tracksPt_all += myTrkVec.Pt();
                        }
                    }
                // } 
            }
            // for DOCA
            if (myTrkVec.Pt()>500.
               ){
                        if ((*B_VTX_trksChi2).at(idx)<=1.0) nclosetrks_all++;
                        if ( (*B_VTX_trksChi2).at(idx) <=7.0) {
                            if ( (*closeTrkDOCA_alltrks).at(idx) < docamin) {
                                docamin = (*closeTrkDOCA_alltrks).at(idx);
                            }
                        }
            }
            // for B Iso number of tracks:
            if (myTrkVec.DeltaR(myBVec) < 0.7 
                && myTrkVec.Pt()>500.
            ){
                if ((*B_PV_trksChi2).at(idx)<5.){
                    if (((*idtrk_nPIXhits).at(idx) - (*idtrk_NIBLayer).at(idx))>=1
                        && (*idtrk_nSCThits).at(idx)>=2
                    ){
                        tracksCnt_all_ID_chi_5+=1;
                    }
                }
            }

    //////////////////////REPEAT THE Default calculations!
            //for B Iso
            if ((*idtrk_pvidx).at(idx) == B_PV_idx
                && (*B_PV_trksChi2).at(idx)<5. 
                 && myTrkVec.Pt()>500.
               ){
                    if (((*idtrk_nPIXhits).at(idx) - (*idtrk_NIBLayer).at(idx))>=1
                        && (*idtrk_nSCThits).at(idx)>=2
                    ){
                        if (myTrkVec.DeltaR(myBVec) < 0.7){
                            tracksPt_aidan += myTrkVec.Pt();
                        }
                    }
            }
            //for DOCA
            if ((*idtrk_pvidx).at(idx) == B_PV_idx
                && myTrkVec.Pt()>500.
               ){
                        if ((*B_VTX_trksChi2).at(idx)<=1.0) nclosetrks_aidan++;
                        if ( (*B_VTX_trksChi2).at(idx) <=7.0) {
                            if ( (*closeTrkDOCA_alltrks).at(idx) < docamin_aidan) {
                                docamin_aidan = (*closeTrkDOCA_alltrks).at(idx);
                            }
                        }
            }
            //for Biso number of tracks
            if ((*idtrk_pvidx).at(idx) == B_PV_idx
                && myTrkVec.DeltaR(myBVec) < 0.7 
                && myTrkVec.Pt()>500.
            ){
                if ((*B_PV_trksChi2).at(idx)<5.){
                        tracksCnt_aidan_ID_chi_5+=1;
                }
            }
        }
            //calulate All Track Iso Variables
            B_iso_7_Chi2_5_LoosePt05_AllTrks = B_pT/(B_pT+tracksPt_all);
            B_iso_Ntracks_7_Chi2_5_LoosePt05_AllTrks = tracksCnt_all_ID_chi_5;
            closeTrkNtrksChi2_AllTrks = nclosetrks_all;
            if (docamin==999.) docamin=-0.1;
            closeTrkDOCA_AllTrks2 = docamin;
            closeTrkDOCA = TMath::Sqrt(pow(closeTrkDCA,2)+pow(closeTrkZCA,2));
            //repeat default...:
            B_iso_7_Chi2_5_LoosePt05_Aidan = B_pT/(B_pT+tracksPt_aidan);
            B_iso_Ntracks_7_Chi2_5_LoosePt05_Aidan = tracksCnt_aidan_ID_chi_5;
            closeTrkNtrksChi2_Aidan = nclosetrks_aidan;
            if (docamin_aidan==999.) docamin_aidan=-0.1;
            closeTrkDOCA_Aidan = docamin_aidan;
            // B_minChi2MuonsIPtoAnyPV_AllTrks = 0.; //fix me!!
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

