//
// macro reads two ntuples, typically a data and a mc ntuple 
// for variable of interest additional weight per event is calculated and
// added to one of the ntuples (where applicable)
// 
// adjust computation of "NPVweight" variable
//
// .L addWeights.C++
// addWeights(ifileData, ifileMC);
// output file with name ifileMC_NPVweight.root will be produced

//based on www/bmumu/MCvsDataCode/addWeights.C:
// authored by Iskander(dot)Ibragimov(at)cern(dot)ch
// 09.11.2017
//
//Edited for NPV weights by Aidan
//this script does not save event info tree

#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasLabels.C"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasLabels.h"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasStyle.C"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasStyle.h"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasUtils.C"
#include "/afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle/AtlasUtils.h"

#include "TCut.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TBranch.h"
#include <iostream>


// number of primary vertices
//
TH1D* hnpv      = new TH1D("hnpv","hnpv",30,0.,30.);
//

using namespace std;

// reweighting method based on a histogram
//
double getWeight(double, TH1D*);

//void addWeights(TString ifileData, TString ifileMC){
void addWeightsNPV(){

TString ifileData = "/eos/home-a/agrummer/BsmumuData/AnalysisNtuples2020/v4/LASTskim.user.agrummer.Data1516.merged.2.root";
TString ifileMC =  "/eos/home-a/agrummer/BsmumuData/AnalysisNtuples2020/v4/LASTskim.user.agrummer.mcBsmumu.merged.2.root";

  Double_t NPVweight(0), CombWeights(0);
  Int_t Npv(0),B_iso_Ntracks_7_Chi2_5_LoosePt05(0);
  Double_t B_pT(0), B_eta(0), B_PV_Ref_z(0);

  TH1D* hdivnpv, *hdivbpt, *hdivbeta, *hdivbpvrz, *hdivbisontrk; 

  //-------REF (DATA) FILE (NUMERATOR) --------
  //
  TFile *fd = new TFile(ifileData);
  TTree *td = (TTree*)fd->Get("T_mv");
  // TTree *td = (TTree*)fd->Get("T_mv_H");//for MainWDelayed
  // TTree *td = (TTree*)fd->Get("T_mv_C"); //for Main periods


  td->SetBranchAddress("Npv",&Npv);

  //-------SOURCE (MC) FILE (DENOMINATOR) --------
  //
  TFile *fm = new TFile(ifileMC);
  TTree *tm = (TTree*)fm->Get("T_mv");
  tm->SetBranchAddress("Npv",&Npv);

  //-------GET REWEIGHTING HISTOGRAMS---------

  // TCut someCuts = "Lxy>0.3";
  // TCut MCweights = someCuts*"Muon1_reco_eff_sf*Muon2_reco_eff_sf*PVWeights";
  TCut someCuts = "";
  TCut MCweights = someCuts*"PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf*Muon1_trigger_sf*Muon2_trigger_sf*CombWeights";

  //htgtnpv - target, hsrcnpv - source

  // ------ Npv -----------------------------
  hdivnpv =(TH1D*)hnpv->Clone("hdivnpv");
  
  TH1D* htgtnpv = new TH1D(*hnpv); htgtnpv->SetName("htgtnpv");
  htgtnpv->Reset(); htgtnpv->Sumw2();
  td->Draw("Npv>>htgtnpv(30,0.,30.)",someCuts,"egoff");
  htgtnpv = (TH1D*)gDirectory->Get("htgtnpv");
  
  
  TH1D* hsrcnpv = new TH1D(*hnpv); hsrcnpv->SetName("hsrcnpv");
  hsrcnpv->Reset();hsrcnpv->Sumw2();
  tm->Draw("Npv>>hsrcnpv(30,0.,30.)",MCweights,"egoff");
  hsrcnpv = (TH1D*)gDirectory->Get("hsrcnpv");
  
  hdivnpv->Reset();
  hdivnpv->Divide(htgtnpv,hsrcnpv,1./htgtnpv->Integral(),1./hsrcnpv->Integral());

  //-------WRITE REWEITED FILE OUT---------
  //
  TString newfname(ifileMC);
  newfname.Remove(newfname.Index(".root"),newfname.Length());
  newfname.Append(".NPVweight.root");
  TFile *fn = new TFile(newfname,"recreate");
  TTree *tn = tm->CloneTree(0);
  TBranch *mwa = tn->Branch("NPVweight",&NPVweight,"NPVweight/D");
 
  Int_t N=tm->GetEntries();
  Int_t isel(0);
  Double_t w1(1.),w2(1.),w3(1.),w4(1.),w5(1.0);
  cout << "Processing entries: "<< N <<endl;
  for(int ie=0;ie<N;ie++) {
    tm->GetEntry(ie);
    isel++;
    w1 = getWeight((double)Npv,  hdivnpv);
    // w2 = getWeight(B_pT,  hdivbpt);
    // w3 = getWeight(B_eta, hdivbeta);
    // //    w4 = getWeight(B_PV_Ref_z, hdivbpvrz);
    // w5 = getWeight(B_iso_Ntracks_7_Chi2_5_LoosePt05, hdivbisontrk);
 
    // NPVweight = w1*w2*w3*w4*w5; //ADJUST
    NPVweight = w1; //ADJUST

    tn->Fill();
  }
  cout << "Selected entries: "<< isel <<endl;
  fn->cd();
  //  tn->Print();
  tn->Write();
  fn->Close();
}

double getWeight(double pVal, TH1D* hw){
  Double_t theWeight(1.0);
  int binPt=0;
  Int_t NbinPt=hw->GetNbinsX();
  for (int p=1; p<=NbinPt;++p){
    if ((pVal>=hw->GetXaxis()->GetBinLowEdge(p)) && (pVal<hw->GetXaxis()->GetBinUpEdge(p)) ){
      binPt=p;
      break;
    }
  }
  theWeight = hw->GetBinContent(binPt);
  return theWeight;
}
