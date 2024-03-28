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
void alltrksExample_fileLoop(){
    SetAtlasStyle();
  // TString fsname("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/skimmed_ntup/data18/Bmumu/user.ibragimo.17073931.Bmumu._000001_skimmed.root");
  // TString fsname("/afs/cern.ch/work/a/agrummer/BsmumuData/LastSkimOne2018Run/LASTskim_2017Bmumu.root");
  // TString fsname("/afs/cern.ch/work/a/agrummer/BsmumuData/LastSkimOne2018Run/LASTskim_2018_1.root");
  // TString indir("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/skimmed_ntup/data18/Bmumu/");
  TString indir("/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkim2018_2019Mar7/");
  TString finpath(indir);
  DIR *dpdf;
  struct dirent *entry;
  const bool doIsoStudy = true; 

  dpdf = opendir(finpath.Data());


  TH1F* h_chi2_all(NULL); TH1F* h_chi2(NULL); TH1I* h_ntrks(NULL); 
  TH1I* h_ntrks_orig(NULL); TH1F* h_iso(NULL); TH1F* h_myDR(NULL); TH1F* h_myDR_all(NULL);
  TH1F* h_my_iso(NULL); TH1F* h_my_iso_all(NULL);
  TH1F* h_trackPt(NULL); TH1F* h_trackPt_all(NULL);
  TH1F* h_B_pT(NULL);
  if (doIsoStudy) {
    h_chi2_all = new TH1F("h_chi2_all","chi2 to ass. PV for all tracks",200,-5,15);
    h_chi2     = new TH1F("h_chi2","chi2 to associated PV for selected tracks",200,-5,15);
    h_myDR     = new TH1F("h_myDR","calculated DR for each track",100,0,5.8);//30,0,1.5
    h_myDR_all     = new TH1F("h_myDR_all","calculated DR for each tracks",100,0,5.8);
    h_B_pT      = new TH1F("h_B_pT","B pT",1000,0.005,1000.);
    h_trackPt      = new TH1F("h_trackPt","track pT",1000,0.005,1000.);
    h_trackPt_all      = new TH1F("h_trackPt_all","track pT all",1000,0.005,1000.);
    h_iso      = new TH1F("h_iso","B isolation",100,0.005,1.005);
    h_my_iso      = new TH1F("h_my_iso","my B isolation",100,0.005,1.005);
    h_my_iso_all      = new TH1F("h_my_iso","my B isolation",100,0.005,1.005);
  } else {
    h_chi2_all   = new TH1F("h_chi2_all","chi2 to ass. B vertex for all tracks",200,-5,15);
    h_chi2       = new TH1F("h_chi2","chi2 to B vertex for selected tracks",200,-5,15);
    h_ntrks      = new TH1I("h_ntrks","h_ntrks",100,0,100);  
    h_ntrks->SetLineColor(kRed);
    h_ntrks_orig = new TH1I("h_ntrks_orig","h_ntrks_orig",100,0,100); 
    h_ntrks_orig->SetLineColor(kBlack);
  }
  if (h_chi2_all) h_chi2_all->SetLineColor(kBlack);
  if (h_chi2) h_chi2->SetLineColor(kRed);
  if (h_myDR_all) h_myDR_all->SetLineColor(kBlack);
  if (h_myDR) h_myDR->SetLineColor(kRed);
  if (h_iso) h_iso->SetLineColor(kBlue);
  if (h_my_iso_all) h_my_iso_all->SetLineColor(kBlack);
  if (h_my_iso) h_my_iso->SetLineColor(kRed);
  if (h_trackPt_all) h_trackPt_all->SetLineColor(kBlack);
  if (h_trackPt) h_trackPt->SetLineColor(kRed);

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

  v_uint   *pv_type     = 0;
  v_float  *pv_z        = 0;
  v_float  *pv_sigma_z  = 0;
  v_int    *idtrk_pvidx = 0;  
  v_double    *idtrk_px = 0;  
  v_double    *idtrk_py = 0;  
  v_double    *idtrk_pz = 0;  
  tev->SetBranchAddress("pv_z", &pv_z);
  tev->SetBranchAddress("pv_sigma_z", &pv_sigma_z);
  tev->SetBranchAddress("pv_type", &pv_type);
  tev->SetBranchAddress("idtrk_pvidx", &idtrk_pvidx);
  tev->SetBranchAddress("idtrk_px", &idtrk_px);
  tev->SetBranchAddress("idtrk_py", &idtrk_py);
  tev->SetBranchAddress("idtrk_pz", &idtrk_pz);
  
  
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
  Double_t tracksPt(0.);
  Double_t tracksPt_all(0.);

  //ts->SetBranchAddress("B_MUCALC_mass",&B_MUCALC_mass);
  ts->SetBranchAddress("event_index",  &event_index);                           // index to EventInfo tree

  // variables for the isolation studies
  //
  ts->SetBranchAddress("B_PV_idx",&B_PV_idx);                                  // index to associated PV  
  ts->SetBranchAddress("B_PV_trksChi2",&B_PV_trksChi2);                        // chi2 to associated PV, per track
  ts->SetBranchAddress("B_iso_7_Chi2_5_LoosePt05",&B_iso_7_Chi2_5_LoosePt05);  // DxAOD isoaltion variable

  // variables for the close track studies
  //
  ts->SetBranchAddress("B_VTX_trksChi2",&B_VTX_trksChi2);                // chi2 of each track to the B vertex
  ts->SetBranchAddress("closeTrkDOCA_alltrks",&closeTrkDOCA_alltrks);    // DOCA of each track to B vertex
  ts->SetBranchAddress("closeTrkNtrksChi2",&closeTrkNtrksChi2);          // DxAOD closeTrkNtrksChi2 variable
  ts->SetBranchAddress("closeTrkDCA",&closeTrkDCA);                      // DxAOD closeTrkDCA variable 
  ts->SetBranchAddress("closeTrkZCA",&closeTrkZCA);                      // DxAOD closeTrkZCA variable

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
        if (ievent%100000==0) cout << "Processing event "<< ievent << endl;
        ts->GetEntry(ievent);
        tev->GetEntry(event_index);
        tracksPt=0.;
        tracksPt_all=0.;

        auto ntrks = B_PV_trksChi2->size();
            if ((*idtrk_pvidx).size() != ntrks) {
                cout << "FATAL: ID trk info size unequal in event and candidate trees, exiting. " << (*idtrk_pvidx).size() << " <-ev|cand-> " << ntrks << endl;
                exit(0);
            }
        totalTracks+=ntrks;
        int nclosetrks(0);
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
            if ( (*idtrk_pvidx).at(idx) == B_PV_idx                // choose tracks ass. to associated PV 
                 || (*idtrk_pvidx).at(idx) != pv_type->size()-1 ) // or choose tracks ass. to other real PV's (for non-ass. tracks use '==' instead)
            { 
                if (doIsoStudy) {
                    h_chi2->Fill( (*B_PV_trksChi2).at(idx) );
                    h_myDR->Fill(myTrkVec.DeltaR(myBVec));
                    h_trackPt->Fill(myTrkVec.Pt());
                    if ((*B_PV_trksChi2).at(idx)<5. && myTrkVec.DeltaR(myBVec) < 0.7 && myTrkVec.Pt()>500.){//&& myTrkVec.Eta()<2.5
                        tracksPt += myTrkVec.Pt();
                    }
                }else {
                    h_chi2->Fill( (*B_VTX_trksChi2).at(idx) );
                    if ((*B_VTX_trksChi2).at(idx)<=1.0) nclosetrks++;
                    if ( (*B_VTX_trksChi2).at(idx) <=7.0) {
                    if ( (*closeTrkDOCA_alltrks).at(idx) < docamin) docamin = (*closeTrkDOCA_alltrks).at(idx);
                    }
                }
            }
            if (doIsoStudy) {
                    h_chi2_all->Fill( (*B_PV_trksChi2).at(idx) );
                    // myBVec->SetPtEtaPhi(B_pT,B_eta,B_phi);//need to be careful with the conditions
                    h_myDR_all->Fill(myTrkVec.DeltaR(myBVec));
                    h_trackPt_all->Fill(myTrkVec.Pt());
                    if ((*B_PV_trksChi2).at(idx)<5. && myTrkVec.DeltaR(myBVec) < 0.7 && myTrkVec.Pt()>500.){//&& myTrkVec.Eta()<2.5
                        tracksPt_all += myTrkVec.Pt();
                    }
            } else {
                    h_chi2_all->Fill( (*B_VTX_trksChi2).at(idx) );
            }
        }
// cout<<"trackPt: "<< tracksPt_all/totalTracks<<endl;
        if (doIsoStudy) {
            if (h_iso) h_iso->Fill(B_iso_7_Chi2_5_LoosePt05);
            if (h_my_iso) h_my_iso->Fill(B_pT/(B_pT+tracksPt));
            if (h_my_iso_all) h_my_iso_all->Fill(B_pT/(B_pT+tracksPt_all));
        }else {
            cout << DOCA << " <-AOD|ntup-> "<< docamin << endl; //" DCA: "<< closeTrkDCA << " ZCA: "<< closeTrkZCA << endl; 
            if (h_ntrks) h_ntrks->Fill(nclosetrks);
            if (h_ntrks_orig) h_ntrks_orig->Fill(closeTrkNtrksChi2);     
        }
    }
cout<< "number of tracks so far: "<< totalTracks<< endl;
cout<< "h_chi2_all entries: "<< h_chi2_all->GetEntries()<<endl;
cout<< "h_chi2 entries: "<< h_chi2->GetEntries()<<endl;
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
    if (h_my_iso) h_my_iso->Draw("same");
    if (h_iso) h_iso->Draw("same");
  } else {
    if (h_ntrks_orig) h_ntrks_orig->Draw();
    if (h_ntrks) h_ntrks->Draw("same");
  }
    // TLegend* leg = new TLegend(0.4, 0.6, 0.5, 0.7,NULL,"brNDC");
  //DR
    // TLegend* leg = new TLegend(0.7, 0.7, 0.8, 0.8,NULL,"brNDC");
    //iso
    TLegend* leg = new TLegend(0.2, 0.7, 0.3, 0.8,NULL,"brNDC");
    leg->SetTextSize(0.034468);
    // leg->AddEntry(h_chi2, "2018 B_PV_trksChi2" ,"l");
    // leg->AddEntry(h_chi2, "2017 assoc. B_PV_trksChi2" ,"l");
    // leg->AddEntry(h_chi2_all, "2017 all B_PV_trksChi2" ,"l");
    // leg->AddEntry(h_myDR, "2018 DR tracks" ,"l");
    // leg->AddEntry(h_myDR_all, "2018 DR all tracks" ,"l");
    leg->AddEntry(h_my_iso, "2018 my Iso" ,"l");
    leg->AddEntry(h_my_iso_all, "2018 myIso all tracks" ,"l");
    leg->AddEntry(h_iso, "2018 I_{0.7}" ,"l");
    // leg->AddEntry(h_iso, "2017 I_{0.7}" ,"l");
    // leg->AddEntry(h_ntrks_orig, "2018 h_ntrks_orig" ,"l");
    // leg->AddEntry(h_ntrks, "2018 h_ntrks","l");
    // leg->AddEntry(h_ntrks_orig, "2017 h_ntrks_orig" ,"l");
    // leg->AddEntry(h_ntrks, "2017 h_ntrks","l");
    leg->SetBorderSize(0);  // no border
    leg->SetLineColor(0);
    leg->SetFillColorAlpha(0, 0.4);
    leg->Draw();
  // c->SaveAs("chi2.root");
  // c->SaveAs("myDR.png");
  c->SaveAs("myIso10.png");
  // c->SaveAs("myTrackPt.png");
  

}

int main(int argc, char* argv[])
{
  TString inpath, pattern;
  if (argc>1) inpath = TString(argv[1]);
  if (argc>2) pattern = TString(argv[2]);
  // alltrksExample_fileLoop(inpath, pattern);
  alltrksExample_fileLoop();
  return 0;
}

