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
TCanvas* alltrksExample_fileLoop_v2(int myYear){
  SetAtlasStyle();
  // TString fsname("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/skimmed_ntup/data18/Bmumu/user.ibragimo.17073931.Bmumu._000001_skimmed.root");
  // TString fsname("/afs/cern.ch/work/a/agrummer/BsmumuData/LastSkimOne2018Run/LASTskim_2017Bmumu.root");
  // TString fsname("/afs/cern.ch/work/a/agrummer/BsmumuData/LastSkimOne2018Run/LASTskim_2018_1.root");
  // TString indir("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/skimmed_ntup/data18/Bmumu/");
  TString indir("");
  // int myYear(2018);
  if (myYear==2017){
        // indir = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkim2017_2019Mar7/";
        indir = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkim2019Mar27/2017/";
  }else if (myYear == 2018){
        // indir = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkim2018_2019Mar7/";
        indir = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkim2019Mar27/2018";
  }
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
    TH1F* h_my_iso_assPV(NULL);
    TH1F* h_my_iso_otherPV(NULL);
    TH1F* h_my_iso_nonAss(NULL);
    TH1F* h_my_iso_myAll(NULL);
  if (doIsoStudy) {
    h_chi2_all = new TH1F("h_chi2_all","chi2 to ass. PV for all tracks",200,-5,15);
    h_chi2     = new TH1F("h_chi2","chi2 to associated PV for selected tracks",200,-5,15);
    h_myDR     = new TH1F("h_myDR","calculated DR for each track",100,0,5.8);//30,0,1.5
    h_myDR_all     = new TH1F("h_myDR_all","calculated DR for each tracks",100,0,5.8);
    h_B_pT      = new TH1F("h_B_pT","B pT",1000,0.005,1000.);
    h_trackPt      = new TH1F("h_trackPt","track pT",1000,0.005,1000.);
    h_trackPt_all      = new TH1F("h_trackPt_all","track pT all",1000,0.005,1000.);
    h_iso      = new TH1F("h_iso","B isolation",100,0.005,1.005);
    h_my_iso_assPV      = new TH1F("h_my_iso_assPV","my B isolation",100,0.005,1.005);
    h_my_iso_otherPV      = new TH1F("h_my_iso_otherPV","my B isolation",100,0.005,1.005);
    h_my_iso_nonAss      = new TH1F("h_my_iso_nonAss","my B isolation",100,0.005,1.005);
    h_my_iso_myAll      = new TH1F("h_my_iso_myAll","my B isolation",100,0.005,1.005);
    h_my_iso_all      = new TH1F("h_my_iso_all","my B isolation",100,0.005,1.005);
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
  if (h_my_iso_assPV) h_my_iso_assPV->SetLineColor(kRed);
  if (h_my_iso_otherPV) h_my_iso_otherPV->SetLineColor(kGreen+2);
  if (h_my_iso_nonAss) h_my_iso_nonAss->SetLineColor(kMagenta);
  if (h_my_iso_myAll) h_my_iso_myAll->SetLineColor(kRed-3);
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
  v_int    *idtrk_isTightPrimary = 0; 
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
  Double_t tracksPt_assPV(0.);
  Double_t tracksPt_otherPV(0.);
  Double_t tracksPt_nonAss(0.);
  Double_t tracksPt_myAll(0.);
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

            if ( (*idtrk_pvidx).at(idx) == B_PV_idx)
            {
                if (doIsoStudy) {
                    if ((*B_PV_trksChi2).at(idx)<5. && myTrkVec.DeltaR(myBVec) < 0.7 && myTrkVec.Pt()>500.){//&& myTrkVec.Eta()<2.5
                        tracksPt_assPV += myTrkVec.Pt();
                    }
                }
            }

            if ( (*idtrk_pvidx).at(idx) == B_PV_idx                // choose tracks ass. to associated PV 
                 || (*idtrk_pvidx).at(idx) != pv_type->size()-1 ) // or choose tracks ass. to other real PV's (for non-ass. tracks use '==' instead)
            { 
                if (doIsoStudy) {
                    // h_chi2->Fill( (*B_PV_trksChi2).at(idx) );
                    // h_myDR->Fill(myTrkVec.DeltaR(myBVec));
                    // h_trackPt->Fill(myTrkVec.Pt());
                    if ((*B_PV_trksChi2).at(idx)<5. && myTrkVec.DeltaR(myBVec) < 0.7 && myTrkVec.Pt()>500.){//&& myTrkVec.Eta()<2.5
                        tracksPt_otherPV += myTrkVec.Pt();
                    }
                }else {
                    h_chi2->Fill( (*B_VTX_trksChi2).at(idx) );
                    if ((*B_VTX_trksChi2).at(idx)<=1.0) nclosetrks++;
                    if ( (*B_VTX_trksChi2).at(idx) <=7.0) {
                    if ( (*closeTrkDOCA_alltrks).at(idx) < docamin) docamin = (*closeTrkDOCA_alltrks).at(idx);
                    }
                }
            }

            if ( (*idtrk_pvidx).at(idx) == B_PV_idx                // choose tracks ass. to associated PV 
                 || (*idtrk_pvidx).at(idx) == pv_type->size()-1 )  //(for non-ass. tracks use '==' instead)
            {
                if (doIsoStudy) {
                    if ((*B_PV_trksChi2).at(idx)<5. && myTrkVec.DeltaR(myBVec) < 0.7 
                            && myTrkVec.Pt()>500. && (*idtrk_isTightPrimary).at(idx) == 1 ){//&& myTrkVec.Eta()<2.5
                        tracksPt_nonAss += myTrkVec.Pt();
                    }
                }
            }

            if ( (*idtrk_pvidx).at(idx) == B_PV_idx                // choose tracks ass. to associated PV 
                 || (*idtrk_pvidx).at(idx) == pv_type->size()-1 
                 || (*idtrk_pvidx).at(idx) != pv_type->size()-1 )
            {
                if (doIsoStudy) {
                    if ((*B_PV_trksChi2).at(idx)<5. && myTrkVec.DeltaR(myBVec) < 0.7 && myTrkVec.Pt()>500.){//&& myTrkVec.Eta()<2.5
                        tracksPt_myAll += myTrkVec.Pt();
                    }
                }
            }
            if (doIsoStudy) {
                    // h_chi2_all->Fill( (*B_PV_trksChi2).at(idx) );
                    // myBVec->SetPtEtaPhi(B_pT,B_eta,B_phi);//need to be careful with the conditions
                    // h_myDR_all->Fill(myTrkVec.DeltaR(myBVec));
                    // h_trackPt_all->Fill(myTrkVec.Pt());
                    if ((*B_PV_trksChi2).at(idx)<5. && myTrkVec.DeltaR(myBVec) < 0.7 && myTrkVec.Pt()>500.){//&& myTrkVec.Eta()<2.5
                        tracksPt_all += myTrkVec.Pt();
                    }
            } else {
                    h_chi2_all->Fill( (*B_VTX_trksChi2).at(idx) );
            }
        }
// cout<<"trackPt: "<< tracksPt_all/totalTracks<<endl;
        if (doIsoStudy) {
            if (h_iso)              h_iso->Fill(B_iso_7_Chi2_5_LoosePt05);
            if (h_my_iso_assPV)     h_my_iso_assPV->Fill(B_pT/(B_pT+tracksPt_assPV));
            if (h_my_iso_otherPV)   h_my_iso_otherPV->Fill(B_pT/(B_pT+tracksPt_otherPV));
            if (h_my_iso_nonAss)    h_my_iso_nonAss->Fill(B_pT/(B_pT+tracksPt_nonAss));
            if (h_my_iso_myAll)     h_my_iso_myAll->Fill(B_pT/(B_pT+tracksPt_myAll));
            if (h_my_iso_all)       h_my_iso_all->Fill(B_pT/(B_pT+tracksPt_all));
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
    if (h_my_iso_myAll) h_my_iso_myAll->Draw("same");
    if (h_my_iso_assPV) h_my_iso_assPV->Draw("same");
    if (h_my_iso_otherPV) h_my_iso_otherPV->Draw("same");
    if (h_my_iso_nonAss) h_my_iso_nonAss->Draw("same");
    if (h_iso) h_iso->Draw("same");
  } else {
    if (h_ntrks_orig) h_ntrks_orig->Draw();
    if (h_ntrks) h_ntrks->Draw("same");
  }
    // TLegend* leg = new TLegend(0.4, 0.6, 0.5, 0.7,NULL,"brNDC");
  //DR
    // TLegend* leg = new TLegend(0.7, 0.7, 0.8, 0.8,NULL,"brNDC");
    //iso
    TLegend* leg = new TLegend(0.2, 0.6, 0.3, 0.8,NULL,"brNDC");
    leg->SetTextSize(0.034468);
    // leg->AddEntry(h_chi2, "2018 B_PV_trksChi2" ,"l");
    // leg->AddEntry(h_chi2, "2017 assoc. B_PV_trksChi2" ,"l");
    // leg->AddEntry(h_chi2_all, "2017 all B_PV_trksChi2" ,"l");
    // leg->AddEntry(h_myDR, "2018 DR tracks" ,"l");
    // leg->AddEntry(h_myDR_all, "2018 DR all tracks" ,"l");
    if (myYear==2017){
        leg->AddEntry(h_my_iso_assPV, "2017 h_my_iso_assPV" ,"l");
        leg->AddEntry(h_my_iso_otherPV, "2017 h_my_iso_otherPV" ,"l");
        leg->AddEntry(h_my_iso_nonAss, "2017 h_my_iso_nonAss" ,"l");
        leg->AddEntry(h_my_iso_myAll, "2017 h_my_iso_myAll" ,"l");
        leg->AddEntry(h_my_iso_all, "2017 myIso all tracks" ,"l");
        leg->AddEntry(h_iso, "2017 I_{0.7}" ,"l");
    }else if (myYear == 2018){
        leg->AddEntry(h_my_iso_assPV, "2018 h_my_iso_assPV" ,"l");
        leg->AddEntry(h_my_iso_otherPV, "2018 h_my_iso_otherPV" ,"l");
        leg->AddEntry(h_my_iso_nonAss, "2018 h_my_iso_nonAss" ,"l");
        leg->AddEntry(h_my_iso_myAll, "2018 h_my_iso_myAll" ,"l");
        leg->AddEntry(h_my_iso_all, "2018 myIso all tracks" ,"l");
        leg->AddEntry(h_iso, "2018 I_{0.7}" ,"l");
    }
    
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
  // c->SaveAs("myIso10.png");
  // c->SaveAs("myTrackPt.png");
    return c;
}

TCanvas* Data1516(){
    TString indir("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/AnalysisNtuples/Bsmumu/data15a16/v3/data1516Bs_BDT2016_v2.root");
    TString fintemp(indir);
    TFile *fin = new TFile(fintemp);
    TTree *ts = (TTree*)fin->Get("T_mv");
    TH1F* h_iso(NULL);
    h_iso      = new TH1F("h_iso","B isolation",100,0.005,1.005);
    if (h_iso) h_iso->SetLineColor(kBlue);
    float B_iso_7_Chi2_5_LoosePt05(0.);
    // variables for the isolation studies
    //
    ts->SetBranchAddress("B_iso_7_Chi2_5_LoosePt05",&B_iso_7_Chi2_5_LoosePt05);  // DxAOD isoaltion variable
    auto nevents = ts->GetEntries();
    cout<< "Entries in 15-16 tree: "<< nevents << endl;
    for (auto ievent=0; ievent<nevents; ievent++)
    {
        if (ievent%100000==0) cout << "Processing event "<< ievent << endl;
        ts->GetEntry(ievent);
        if (h_iso) h_iso->Fill(B_iso_7_Chi2_5_LoosePt05);
    }
    TCanvas* c = new TCanvas("1516 Canvas","1516 Canvas",900,600);
    if (h_iso) h_iso->Draw("same");
    TLegend* leg = new TLegend(0.2, 0.7, 0.3, 0.8,NULL,"brNDC");
    leg->SetTextSize(0.034468);
    leg->AddEntry(h_iso, "2018 I_{0.7}" ,"l");
    leg->SetBorderSize(0);  // no border
    leg->SetLineColor(0);
    leg->SetFillColorAlpha(0, 0.4);
    leg->Draw();
    return c;
}

TCanvas* Run1data(){
    TString indir("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun1/data/Bsmumu/data12_8TeVBsAllPeriodsUnblinded.root");
    TString fintemp(indir);
    TFile *fin = new TFile(fintemp);
    TTree *ts = (TTree*)fin->Get("T_mv");
    TH1F* h_isoAll(NULL); TH1F* h_isoBlinded(NULL); TH1F* h_isoRun2Cuts(NULL); TH1F* h_isoMuonDRcut(NULL);
    h_isoAll          = new TH1F("h_isoAll","h_isoAll",100,0.005,1.005);
    h_isoBlinded      = new TH1F("h_isoBlinded","h_isoBlinded",100,0.005,1.005);
    h_isoRun2Cuts     = new TH1F("h_isoRun2Cuts","h_isoRun2Cuts",100,0.005,1.005);
    h_isoMuonDRcut    = new TH1F("h_isoMuonDRcut","h_isoMuonDRcut",100,0.005,1.005);
    if (h_isoAll) h_isoAll->SetLineColor(kBlue);
    if (h_isoBlinded) h_isoBlinded->SetLineColor(kBlack);
    if (h_isoRun2Cuts) h_isoRun2Cuts->SetLineColor(kRed);
    if (h_isoMuonDRcut) h_isoMuonDRcut->SetLineColor(kGreen+2);
    double B_iso_7_Chi2_5_MedPt05(0.);
    double dr(0.), lxy(0.), pa(0.);
    double B_MUCALC_mass, B_VTX_mass;
    double Muon1_pT, Muon1_eta, Muon1_phi;
    double Muon2_pT, Muon2_eta, Muon2_phi;
    bool cat3;
    double fmu1, fmu2;
    TVector3 Muon1vec;
    TVector3 Muon2vec;

    // count the cut flow
    int MassWindowCut(0), BlindCut(0), Run2Cuts(0), DeltaRCut(0); 
    // variables for the isolation studies

    ts->SetBranchAddress("B_MUCALC_mass",&B_MUCALC_mass); 
    ts->SetBranchAddress("B_VTX_mass",&B_VTX_mass); 

    ts->SetBranchAddress("Lxy",&lxy);   // needed to implement additional cuts
    ts->SetBranchAddress("a_2D",&pa);   // which weren't applied in Run 1 ntuples
    ts->SetBranchAddress("DR",&dr);     // by default
    ts->SetBranchAddress("BDT_fakeMuon_1",&fmu1); // fake muon BDT, a cut below should
    ts->SetBranchAddress("BDT_fakeMuon_2",&fmu2); // be equivalent to our isTight requirement
    ts->SetBranchAddress("isCatN3",&cat3); //cat3 is triggered by mu4mu6 trigger

    ts->SetBranchAddress("Muon1_pT",&Muon1_pT); 
    ts->SetBranchAddress("Muon1_eta",&Muon1_eta); 
    ts->SetBranchAddress("Muon1_phi",&Muon1_phi); 
    ts->SetBranchAddress("Muon2_pT",&Muon2_pT); 
    ts->SetBranchAddress("Muon2_eta",&Muon2_eta); 
    ts->SetBranchAddress("Muon2_phi",&Muon2_phi); 
    //
    ts->SetBranchAddress("B_iso_7_Chi2_5_MedPt05",&B_iso_7_Chi2_5_MedPt05);  // DxAOD isoaltion variable

    auto nevents = ts->GetEntries();
    cout<< "Entries in 15-16 tree: "<< nevents << endl;
    for (auto ievent=0; ievent<nevents; ievent++)
    {
        if (ievent%100000==0) cout << "Processing event "<< ievent << endl;
        ts->GetEntry(ievent);
        if (h_isoAll) h_isoAll->Fill(B_iso_7_Chi2_5_MedPt05);

        if (B_MUCALC_mass<4766.0 || B_MUCALC_mass>5966.0){ MassWindowCut+=1; continue;} 
        if (B_MUCALC_mass>=5166.0 && B_MUCALC_mass<=5526.0){ BlindCut+=1; continue;}
        if (h_isoBlinded) h_isoBlinded->Fill(B_iso_7_Chi2_5_MedPt05);

        if (!(lxy>0. && TMath::Abs(pa)<1.0 && dr<1.5) || !(fmu1>-0.458 && fmu2>-0.458) || !cat3) {Run2Cuts+=1; continue;}
        if (h_isoRun2Cuts) h_isoRun2Cuts->Fill(B_iso_7_Chi2_5_MedPt05);

        Muon1vec.SetPtEtaPhi(Muon1_pT,Muon1_eta,Muon1_phi);
        Muon2vec.SetPtEtaPhi(Muon2_pT,Muon2_eta,Muon2_phi);
        if(!(Muon1vec.DeltaR(Muon2vec)<1.5)){DeltaRCut+=1; continue; }
        if (h_isoMuonDRcut) h_isoMuonDRcut->Fill(B_iso_7_Chi2_5_MedPt05);
    }
    cout<<"NumberOfEntries: "<< nevents<<endl;
    cout<<"NumberOfEntries after cuts: "<< h_isoMuonDRcut->GetEntries()<<endl;
    cout<<"MassWindowCut cut : "<< MassWindowCut<< 
    " Entries Remaining: "<<nevents-MassWindowCut <<endl;
    cout<<"BlindCut cut : "<< BlindCut<< 
    " Entries Remaining: "<<nevents-BlindCut-MassWindowCut <<endl;
    cout<<"Run2Cuts cut : "<< Run2Cuts<< 
    " Entries Remaining: "<<nevents-BlindCut-MassWindowCut-Run2Cuts <<endl;
    cout<<"DeltaRCut cut : "<< DeltaRCut<< 
    " Entries Remaining: "<<nevents-BlindCut-MassWindowCut-Run2Cuts-DeltaRCut <<endl;
    TCanvas* c = new TCanvas("1516 Canvas","1516 Canvas",900,600);
    if (h_isoAll) h_isoAll->Draw();
    if (h_isoBlinded) h_isoBlinded->Draw("same");
    if (h_isoRun2Cuts) h_isoRun2Cuts->Draw("same");
    if (h_isoMuonDRcut) h_isoMuonDRcut->Draw("same");
    TLegend* leg = new TLegend(0.2, 0.7, 0.3, 0.8,NULL,"brNDC");
    leg->SetTextSize(0.034468);
    leg->AddEntry(h_isoAll, "h_isoAll" ,"l");
    leg->AddEntry(h_isoBlinded, "h_isoBlinded" ,"l");
    leg->AddEntry(h_isoRun2Cuts, "h_isoRun2Cuts" ,"l");
    leg->AddEntry(h_isoMuonDRcut, "h_isoMuonDRcut" ,"l");
    leg->SetBorderSize(0);  // no border
    leg->SetLineColor(0);
    leg->SetFillColorAlpha(0, 0.4);
    leg->Draw();
    return c;
}

void RunOverData(){
    SetAtlasStyle();
    TString myDir = "/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/";
    // TCanvas* myC = alltrksExample_fileLoop_v2(2018);
    TCanvas* myC = alltrksExample_fileLoop_v2(2017);
    myC->GetListOfPrimitives()->Print();
    myC->SaveAs(myDir+"data/"+"myIso2017_isTightPrimary.root");
    myC->SaveAs(myDir+"figures/"+"myIso2017_isTightPrimary.png");

}

void RunOverSavedFiles(){
    SetAtlasStyle();
    //pull from saved histos
    // //
      TString myDir = "/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/data/";
      int numberOfBins = 100;
      //run1
    TFile* run1File = new TFile(myDir+"myIsoRun1.root");
    TCanvas *Run1Canvas = (TCanvas*)run1File->Get("1516 Canvas");
    TH1F *h_isoAll_Run1 = (TH1F*)Run1Canvas->GetListOfPrimitives()->FindObject("h_isoAll");
    h_isoAll_Run1->Scale(1./(h_isoAll_Run1->Integral(0, numberOfBins + 1)));
    TH1F *h_isoBlinded_Run1 = (TH1F*)Run1Canvas->GetListOfPrimitives()->FindObject("h_isoBlinded");
    h_isoBlinded_Run1->Scale(1./(h_isoBlinded_Run1->Integral(0, numberOfBins + 1)));
    TH1F *h_isoRun2Cuts_Run1 = (TH1F*)Run1Canvas->GetListOfPrimitives()->FindObject("h_isoRun2Cuts");
    h_isoRun2Cuts_Run1->Scale(1./(h_isoRun2Cuts_Run1->Integral(0, numberOfBins + 1)));
    run1File->Close();
    //1516
    TFile* ifile1516 = new TFile(myDir+"myIso1516.root");
    TCanvas *Canvas1516 = (TCanvas*)ifile1516->Get("1516 Canvas");
    TH1F *h_iso_1516 = (TH1F*)Canvas1516->GetListOfPrimitives()->FindObject("h_iso");
    h_iso_1516->Scale(1./(h_iso_1516->Integral(0, numberOfBins + 1)));
    ifile1516->Close();
    //2017
    TFile* ifile2017 = new TFile(myDir+"myIso2017.root");
    TCanvas *Canvas2017 = (TCanvas*)ifile2017->Get("trks chi2");
    TH1F *h_my_iso_assPV_2017 = (TH1F*)Canvas2017->GetListOfPrimitives()->FindObject("h_my_iso_assPV");
    h_my_iso_assPV_2017->Scale(1./(h_my_iso_assPV_2017->Integral(0, numberOfBins + 1)));
    TH1F *h_my_iso_otherPV_2017 = (TH1F*)Canvas2017->GetListOfPrimitives()->FindObject("h_my_iso_otherPV");
    h_my_iso_otherPV_2017->Scale(1./(h_my_iso_otherPV_2017->Integral(0, numberOfBins + 1)));
    TH1F *h_my_iso_nonAss_2017 = (TH1F*)Canvas2017->GetListOfPrimitives()->FindObject("h_my_iso_nonAss");
    h_my_iso_nonAss_2017->Scale(1./(h_my_iso_nonAss_2017->Integral(0, numberOfBins + 1)));
    TH1F *h_my_iso_myAll_2017 = (TH1F*)Canvas2017->GetListOfPrimitives()->FindObject("h_my_iso_myAll");
    h_my_iso_myAll_2017->Scale(1./(h_my_iso_myAll_2017->Integral(0, numberOfBins + 1)));
    TH1F *h_my_iso_all_2017 = (TH1F*)Canvas2017->GetListOfPrimitives()->FindObject("h_my_iso_all");
    h_my_iso_all_2017->Scale(1./(h_my_iso_all_2017->Integral(0, numberOfBins + 1)));
    TH1F *h_iso_2017 = (TH1F*)Canvas2017->GetListOfPrimitives()->FindObject("h_iso");
    h_iso_2017->Scale(1./(h_iso_2017->Integral(0, numberOfBins + 1)));
    ifile2017->Close();
    //2018
    TFile* ifile2018 = new TFile(myDir+"myIso2018.root");
    TCanvas *Canvas2018 = (TCanvas*)ifile2018->Get("trks chi2");
    TH1F *h_my_iso_assPV_2018 = (TH1F*)Canvas2018->GetListOfPrimitives()->FindObject("h_my_iso_assPV");
    h_my_iso_assPV_2018->Scale(1./(h_my_iso_assPV_2018->Integral(0, numberOfBins + 1)));
    TH1F *h_my_iso_otherPV_2018 = (TH1F*)Canvas2018->GetListOfPrimitives()->FindObject("h_my_iso_otherPV");
    h_my_iso_otherPV_2018->Scale(1./(h_my_iso_otherPV_2018->Integral(0, numberOfBins + 1)));
    TH1F *h_my_iso_nonAss_2018 = (TH1F*)Canvas2018->GetListOfPrimitives()->FindObject("h_my_iso_nonAss");
    h_my_iso_nonAss_2018->Scale(1./(h_my_iso_nonAss_2018->Integral(0, numberOfBins + 1)));
    TH1F *h_my_iso_myAll_2018 = (TH1F*)Canvas2018->GetListOfPrimitives()->FindObject("h_my_iso_myAll");
    h_my_iso_myAll_2018->Scale(1./(h_my_iso_myAll_2018->Integral(0, numberOfBins + 1)));
    TH1F *h_my_iso_all_2018 = (TH1F*)Canvas2018->GetListOfPrimitives()->FindObject("h_my_iso_all");
    h_my_iso_all_2018->Scale(1./(h_my_iso_all_2018->Integral(0, numberOfBins + 1)));
    TH1F *h_iso_2018 = (TH1F*)Canvas2018->GetListOfPrimitives()->FindObject("h_iso");
    h_iso_2018->Scale(1./(h_iso_2018->Integral(0, numberOfBins + 1)));
    ifile2018->Close();
    //////2017_isTightPrimary
    TFile* ifile2017_isTightPrimary = new TFile(myDir+"myIso2017_isTightPrimary.root");
    TCanvas *Canvas2017_isTightPrimary = (TCanvas*)ifile2017_isTightPrimary->Get("trks chi2");
    TH1F *h_my_iso_assPV_2017_isTightPrimary = (TH1F*)Canvas2017_isTightPrimary->GetListOfPrimitives()->FindObject("h_my_iso_assPV");
    h_my_iso_assPV_2017_isTightPrimary->Scale(1./(h_my_iso_assPV_2017_isTightPrimary->Integral(0, numberOfBins + 1)));
    TH1F *h_my_iso_otherPV_2017_isTightPrimary = (TH1F*)Canvas2017_isTightPrimary->GetListOfPrimitives()->FindObject("h_my_iso_otherPV");
    h_my_iso_otherPV_2017_isTightPrimary->Scale(1./(h_my_iso_otherPV_2017_isTightPrimary->Integral(0, numberOfBins + 1)));
    TH1F *h_my_iso_nonAss_2017_isTightPrimary = (TH1F*)Canvas2017_isTightPrimary->GetListOfPrimitives()->FindObject("h_my_iso_nonAss");
    h_my_iso_nonAss_2017_isTightPrimary->Scale(1./(h_my_iso_nonAss_2017_isTightPrimary->Integral(0, numberOfBins + 1)));
    TH1F *h_my_iso_myAll_2017_isTightPrimary = (TH1F*)Canvas2017_isTightPrimary->GetListOfPrimitives()->FindObject("h_my_iso_myAll");
    h_my_iso_myAll_2017_isTightPrimary->Scale(1./(h_my_iso_myAll_2017_isTightPrimary->Integral(0, numberOfBins + 1)));
    TH1F *h_my_iso_all_2017_isTightPrimary = (TH1F*)Canvas2017_isTightPrimary->GetListOfPrimitives()->FindObject("h_my_iso_all");
    h_my_iso_all_2017_isTightPrimary->Scale(1./(h_my_iso_all_2017_isTightPrimary->Integral(0, numberOfBins + 1)));
    TH1F *h_iso_2017_isTightPrimary = (TH1F*)Canvas2017_isTightPrimary->GetListOfPrimitives()->FindObject("h_iso");
    h_iso_2017_isTightPrimary->Scale(1./(h_iso_2017_isTightPrimary->Integral(0, numberOfBins + 1)));
    ifile2017_isTightPrimary->Close();
    //2018_isTightPrimary
    TFile* ifile2018_isTightPrimary = new TFile(myDir+"myIso2018_isTightPrimary.root");
    TCanvas *Canvas2018_isTightPrimary = (TCanvas*)ifile2018_isTightPrimary->Get("trks chi2");
    TH1F *h_my_iso_assPV_2018_isTightPrimary = (TH1F*)Canvas2018_isTightPrimary->GetListOfPrimitives()->FindObject("h_my_iso_assPV");
    h_my_iso_assPV_2018_isTightPrimary->Scale(1./(h_my_iso_assPV_2018_isTightPrimary->Integral(0, numberOfBins + 1)));
    TH1F *h_my_iso_otherPV_2018_isTightPrimary = (TH1F*)Canvas2018_isTightPrimary->GetListOfPrimitives()->FindObject("h_my_iso_otherPV");
    h_my_iso_otherPV_2018_isTightPrimary->Scale(1./(h_my_iso_otherPV_2018_isTightPrimary->Integral(0, numberOfBins + 1)));
    TH1F *h_my_iso_nonAss_2018_isTightPrimary = (TH1F*)Canvas2018_isTightPrimary->GetListOfPrimitives()->FindObject("h_my_iso_nonAss");
    h_my_iso_nonAss_2018_isTightPrimary->Scale(1./(h_my_iso_nonAss_2018_isTightPrimary->Integral(0, numberOfBins + 1)));
    TH1F *h_my_iso_myAll_2018_isTightPrimary = (TH1F*)Canvas2018_isTightPrimary->GetListOfPrimitives()->FindObject("h_my_iso_myAll");
    h_my_iso_myAll_2018_isTightPrimary->Scale(1./(h_my_iso_myAll_2018_isTightPrimary->Integral(0, numberOfBins + 1)));
    TH1F *h_my_iso_all_2018_isTightPrimary = (TH1F*)Canvas2018_isTightPrimary->GetListOfPrimitives()->FindObject("h_my_iso_all");
    h_my_iso_all_2018_isTightPrimary->Scale(1./(h_my_iso_all_2018_isTightPrimary->Integral(0, numberOfBins + 1)));
    TH1F *h_iso_2018_isTightPrimary = (TH1F*)Canvas2018_isTightPrimary->GetListOfPrimitives()->FindObject("h_iso");
    h_iso_2018_isTightPrimary->Scale(1./(h_iso_2018_isTightPrimary->Integral(0, numberOfBins + 1)));
    ifile2018_isTightPrimary->Close();
    ////
    TCanvas* allC = new TCanvas("allC","allC",900,600);
    // if (h_isoAll_Run1) h_isoAll_Run1->Draw();
    // if (h_isoBlinded_Run1) h_isoBlinded_Run1->Draw("same");
    h_isoRun2Cuts_Run1->SetLineColor(kRed);
    h_iso_1516->SetLineColor(kBlack);
    h_iso_2017->SetLineColor(kBlue);
    h_my_iso_nonAss_2017->SetLineColor(kBlue);
    h_my_iso_nonAss_2017_isTightPrimary->SetLineColor(kBlue);
    h_iso_2018->SetLineColor(kGreen+1);
    h_my_iso_nonAss_2018->SetLineColor(kGreen+1);
    h_my_iso_nonAss_2018_isTightPrimary->SetLineColor(kGreen+1);
    if (h_isoRun2Cuts_Run1) h_isoRun2Cuts_Run1->Draw("hist");
    if (h_iso_1516) h_iso_1516->Draw("hist same");
    // if (h_iso_2017) h_iso_2017->Draw("hist same");
    // if (h_my_iso_nonAss_2017) h_my_iso_nonAss_2017->Draw("hist same");
    if (h_my_iso_nonAss_2017) h_my_iso_nonAss_2017_isTightPrimary->Draw("hist same");
    // if (h_iso_2018) h_iso_2018->Draw("hist same");
    // if (h_my_iso_nonAss_2018) h_my_iso_nonAss_2018->Draw("hist same");
    if (h_my_iso_nonAss_2018) h_my_iso_nonAss_2018_isTightPrimary->Draw("hist same");
    //for logy scale
    gPad->SetLogy();
    h_isoRun2Cuts_Run1->SetMaximum(1.);
    // else:
    // h_isoRun2Cuts_Run1->GetYaxis()->SetRangeUser(0,0.08);

    h_isoRun2Cuts_Run1->GetXaxis()->SetTitle("B Isolation");
    h_isoRun2Cuts_Run1->GetYaxis()->SetTitle("a.u.");

    TLegend* legAll = new TLegend(0.2, 0.75, 0.3, 0.9);
    legAll->SetTextSize(0.034468);
    // legAll->AddEntry(h_isoAll_Run1, "h_isoAll_Run1" ,"l");
    // legAll->AddEntry(h_isoBlinded_Run1, "h_isoBlinded_Run1" ,"l");
    legAll->AddEntry(h_isoRun2Cuts_Run1, "Run1 w/Run 2 cuts" ,"l");
    legAll->AddEntry(h_iso_1516, "2015 and 2016 data" ,"l");
    legAll->AddEntry(h_my_iso_nonAss_2017, "2017 run (with Non-Assoc. Tracks and IBL hit)" ,"l");
    legAll->AddEntry(h_my_iso_nonAss_2018, "2018 run (with Non-Assoc. Tracks and IBL hit)" ,"l");
    legAll->SetBorderSize(0);  // no border
    legAll->SetLineColor(0);
    legAll->SetFillColorAlpha(0, 0.4);
    legAll->Draw();

    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/IsoComparison.png");
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/IsoComparison_linear.png");
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/IsoComparison_wNonAssoc.png");
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/IsoComparison_wNonAssoc_linear.png");
    allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/IsoComparison_wNonAssoc_isTightPrimary.png");
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/IsoComparison_wNonAssoc_isTightPrimary_linear.png");
    // cout<<h_isoRun2Cuts_Run1->GetEntries()<<endl;
}


void DrawMyPlots(){
      // SetAtlasStyle();
      // RunOverData();
      RunOverSavedFiles();
    // // //run overdata
    // // //
    // TCanvas* myC = alltrksExample_fileLoop_v2();
    // // TCanvas* myC = Run1data();
    // myC->GetListOfPrimitives()->Print();
    // // // TFile* ifile2018iso = new TFile("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/myIso2018.root");
    // // // TCanvas *myC = (TCanvas*)ifile2018iso->Get("allC");
    // // // TH1F *h_my_iso_2018 = (TH1F*)myC->GetListOfPrimitives()->FindObject("h_my_iso");
    // // // TH1F *h_my_iso_all_2018 = (TH1F*)myC->GetListOfPrimitives()->FindObject("h_my_iso_all");
    // // // TH1F *h_iso_2018 = (TH1F*)myC->GetListOfPrimitives()->FindObject("h_iso");
    // // // TCanvas* allC = new TCanvas("allC","allC",900,600);
    // // // if (h_my_iso_2018) h_my_iso_2018->Draw();
    // // // if (h_my_iso_all_2018) h_my_iso_all_2018->Draw();
    // // // if (h_iso_2018) h_iso_2018->Draw();
    // // // TLegend* legAll = new TLegend(0.2, 0.7, 0.3, 0.8);
    // // // legAll->SetTextSize(0.034468);
    // // // legAll->AddEntry(h_my_iso_2018, "2018 my Iso" ,"l");
    // // // legAll->AddEntry(h_my_iso_all_2018, "2018 myIso all tracks" ,"l");
    // // // legAll->AddEntry(h_iso_2018, "2018 I_{0.7}" ,"l");
    // // // legAll->Draw();
    // // // allC->SaveAs("myIsoTest4.png");
    // // // // myC->GetListOfPrimitives()->Print();
    // // // myC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/data/myIso1516.root");
    // // // myC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/myIso1516.png");
    // // myC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/data/myIsoRun1.root");
    // // myC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/myIsoRun1.png");
    // myC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/data/myIso2018.root");
    // myC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/myIso2018.png");
    // //
    //pull from saved histos
    // //
    //   TString myDir = "/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/data/";
    //   int numberOfBins = 100;
    //   //run1
    // TFile* run1File = new TFile(myDir+"myIsoRun1.root");
    // TCanvas *Run1Canvas = (TCanvas*)run1File->Get("1516 Canvas");
    // TH1F *h_isoAll_Run1 = (TH1F*)Run1Canvas->GetListOfPrimitives()->FindObject("h_isoAll");
    // h_isoAll_Run1->Scale(1./(h_isoAll_Run1->Integral(0, numberOfBins + 1)));
    // TH1F *h_isoBlinded_Run1 = (TH1F*)Run1Canvas->GetListOfPrimitives()->FindObject("h_isoBlinded");
    // h_isoBlinded_Run1->Scale(1./(h_isoBlinded_Run1->Integral(0, numberOfBins + 1)));
    // TH1F *h_isoRun2Cuts_Run1 = (TH1F*)Run1Canvas->GetListOfPrimitives()->FindObject("h_isoRun2Cuts");
    // h_isoRun2Cuts_Run1->Scale(1./(h_isoRun2Cuts_Run1->Integral(0, numberOfBins + 1)));
    // run1File->Close();
    // //1516
    // TFile* ifile1516 = new TFile(myDir+"myIso1516.root");
    // TCanvas *Canvas1516 = (TCanvas*)ifile1516->Get("1516 Canvas");
    // TH1F *h_iso_1516 = (TH1F*)Canvas1516->GetListOfPrimitives()->FindObject("h_iso");
    // h_iso_1516->Scale(1./(h_iso_1516->Integral(0, numberOfBins + 1)));
    // ifile1516->Close();
    // //2017
    // TFile* ifile2017 = new TFile(myDir+"myIso2017.root");
    // TCanvas *Canvas2017 = (TCanvas*)ifile2017->Get("trks chi2");
    // TH1F *h_my_iso_assPV_2017 = (TH1F*)Canvas2017->GetListOfPrimitives()->FindObject("h_my_iso_assPV");
    // h_my_iso_assPV_2017->Scale(1./(h_my_iso_assPV_2017->Integral(0, numberOfBins + 1)));
    // TH1F *h_my_iso_otherPV_2017 = (TH1F*)Canvas2017->GetListOfPrimitives()->FindObject("h_my_iso_otherPV");
    // h_my_iso_otherPV_2017->Scale(1./(h_my_iso_otherPV_2017->Integral(0, numberOfBins + 1)));
    // TH1F *h_my_iso_nonAss_2017 = (TH1F*)Canvas2017->GetListOfPrimitives()->FindObject("h_my_iso_nonAss");
    // h_my_iso_nonAss_2017->Scale(1./(h_my_iso_nonAss_2017->Integral(0, numberOfBins + 1)));
    // TH1F *h_my_iso_myAll_2017 = (TH1F*)Canvas2017->GetListOfPrimitives()->FindObject("h_my_iso_myAll");
    // h_my_iso_myAll_2017->Scale(1./(h_my_iso_myAll_2017->Integral(0, numberOfBins + 1)));
    // TH1F *h_my_iso_all_2017 = (TH1F*)Canvas2017->GetListOfPrimitives()->FindObject("h_my_iso_all");
    // h_my_iso_all_2017->Scale(1./(h_my_iso_all_2017->Integral(0, numberOfBins + 1)));
    // TH1F *h_iso_2017 = (TH1F*)Canvas2017->GetListOfPrimitives()->FindObject("h_iso");
    // h_iso_2017->Scale(1./(h_iso_2017->Integral(0, numberOfBins + 1)));
    // ifile2017->Close();
    // //2018
    // TFile* ifile2018 = new TFile(myDir+"myIso2018.root");
    // TCanvas *Canvas2018 = (TCanvas*)ifile2018->Get("trks chi2");
    // TH1F *h_my_iso_assPV_2018 = (TH1F*)Canvas2018->GetListOfPrimitives()->FindObject("h_my_iso_assPV");
    // h_my_iso_assPV_2018->Scale(1./(h_my_iso_assPV_2018->Integral(0, numberOfBins + 1)));
    // TH1F *h_my_iso_otherPV_2018 = (TH1F*)Canvas2018->GetListOfPrimitives()->FindObject("h_my_iso_otherPV");
    // h_my_iso_otherPV_2018->Scale(1./(h_my_iso_otherPV_2018->Integral(0, numberOfBins + 1)));
    // TH1F *h_my_iso_nonAss_2018 = (TH1F*)Canvas2018->GetListOfPrimitives()->FindObject("h_my_iso_nonAss");
    // h_my_iso_nonAss_2018->Scale(1./(h_my_iso_nonAss_2018->Integral(0, numberOfBins + 1)));
    // TH1F *h_my_iso_myAll_2018 = (TH1F*)Canvas2018->GetListOfPrimitives()->FindObject("h_my_iso_myAll");
    // h_my_iso_myAll_2018->Scale(1./(h_my_iso_myAll_2018->Integral(0, numberOfBins + 1)));
    // TH1F *h_my_iso_all_2018 = (TH1F*)Canvas2018->GetListOfPrimitives()->FindObject("h_my_iso_all");
    // h_my_iso_all_2018->Scale(1./(h_my_iso_all_2018->Integral(0, numberOfBins + 1)));
    // TH1F *h_iso_2018 = (TH1F*)Canvas2018->GetListOfPrimitives()->FindObject("h_iso");
    // h_iso_2018->Scale(1./(h_iso_2018->Integral(0, numberOfBins + 1)));
    // ifile2018->Close();
    // ////
    // TCanvas* allC = new TCanvas("allC","allC",900,600);
    // // if (h_isoAll_Run1) h_isoAll_Run1->Draw();
    // // if (h_isoBlinded_Run1) h_isoBlinded_Run1->Draw("same");
    // h_isoRun2Cuts_Run1->SetLineColor(kRed);
    // h_iso_1516->SetLineColor(kBlack);
    // h_iso_2017->SetLineColor(kBlue);
    // h_my_iso_nonAss_2017->SetLineColor(kBlue);
    // h_iso_2018->SetLineColor(kGreen+1);
    // h_my_iso_nonAss_2018->SetLineColor(kGreen+1);
    // if (h_isoRun2Cuts_Run1) h_isoRun2Cuts_Run1->Draw("hist");
    // if (h_iso_1516) h_iso_1516->Draw("hist same");
    // // if (h_iso_2017) h_iso_2017->Draw("hist same");
    // if (h_my_iso_nonAss_2017) h_my_iso_nonAss_2017->Draw("hist same");
    // // if (h_iso_2018) h_iso_2018->Draw("hist same");
    // if (h_my_iso_nonAss_2018) h_my_iso_nonAss_2018->Draw("hist same");
    // //for logy scale
    // // gPad->SetLogy();
    // // h_isoRun2Cuts_Run1->SetMaximum(1.);
    // // else:
    // h_isoRun2Cuts_Run1->GetYaxis()->SetRangeUser(0,0.08);

    // h_isoRun2Cuts_Run1->GetXaxis()->SetTitle("B Isolation");
    // h_isoRun2Cuts_Run1->GetYaxis()->SetTitle("a.u.");

    // TLegend* legAll = new TLegend(0.2, 0.75, 0.3, 0.9);
    // legAll->SetTextSize(0.034468);
    // // legAll->AddEntry(h_isoAll_Run1, "h_isoAll_Run1" ,"l");
    // // legAll->AddEntry(h_isoBlinded_Run1, "h_isoBlinded_Run1" ,"l");
    // legAll->AddEntry(h_isoRun2Cuts_Run1, "Run1 w/Run 2 cuts" ,"l");
    // legAll->AddEntry(h_iso_1516, "2015 and 2016 data" ,"l");
    // legAll->AddEntry(h_my_iso_nonAss_2017, "2017 run (with Non-Assoc. Tracks)" ,"l");
    // legAll->AddEntry(h_my_iso_nonAss_2018, "2018 run (with Non-Assoc. Tracks)" ,"l");
    // legAll->SetBorderSize(0);  // no border
    // legAll->SetLineColor(0);
    // legAll->SetFillColorAlpha(0, 0.4);
    // legAll->Draw();

    // // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/IsoComparison.png");
    // // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/IsoComparison_linear.png");
    // // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/IsoComparison_wNonAssoc.png");
    // allC->SaveAs("/eos/home-a/agrummer/www/bmumu/AnalysisTools/Examples/alltrksExample/figures/IsoComparison_wNonAssoc_linear.png");
    // // cout<<h_isoRun2Cuts_Run1->GetEntries()<<endl;
}


int main(int argc, char* argv[])
{
  TString inpath, pattern;
  if (argc>1) inpath = TString(argv[1]);
  if (argc>2) pattern = TString(argv[2]);
  // alltrksExample_fileLoop(inpath, pattern);
  DrawMyPlots();
  return 0;
}

