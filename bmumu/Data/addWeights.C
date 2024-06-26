//
// macro reads two ntuples, typically a data and a mc ntuple 
// for variable of interest additional weight per event is calulated and 
// added to one of the ntuples (where applicable)
// 
// adjust computation of "testweight" variable
//
// .L addWeights.C++
// addWeights(fdataname, fmcname);
// output file with name fmcname_testweight.root will be produced

// author Iskander(dot)Ibragimov(at)cern(dot)ch
// 09.11.2017
//
//

#include "TCut.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TBranch.h"
#include <iostream>

// number of primary vertices
//
TH1D* hrewnpv      = new TH1D("hrewnpv","hrewnpv",30,0.,30.);

// B isolation (number of tracks)
//
TH1D* hrewbisontrk = new TH1D("hrewbisontrk","hrewbisontrk",16,0,16);

// B_PV_z (z-position of PV associated with B meson)
//
TH1D* hrewbpvrz    = new TH1D("hrewbpvrz","hrewbpvrz",40,-200,200);

// variable binning for pT(B) and eta(B) re-weighting histogram
//
const Int_t nBinsPt = 33;
Float_t xBinPt[nBinsPt]={8000, 10000, 12000, 14000, 16000, 18000, 20000, 22000, 24000, 26000, 28000, 30000, 32000, 34000, 36000, 38000, 40000, 42000, 44000, 
			 46000, 48000, 50000, 52000, 54000, 56000, 58000, 60000, 62000, 64000, 68000, 70000, 76000, 100000};
TH1D* hrewbpt = new TH1D("hrewbpt","hrewbpt" ,nBinsPt-1, xBinPt);
const Int_t nBinsEta = 26;
Float_t xBinEta[nBinsEta]={-2.5, -2.3, -2.1, -1.9, -1.7, -1.5, -1.3, -1.1, -0.9, -0.7, -0.5, 
			   -0.3, -0.1, 0.1, 0.3, 0.5, 0.7, 0.9, 1.1, 1.3, 1.5, 1.7, 1.9, 2.1, 2.3, 2.5};
TH1D* hrewbeta = new TH1D("hrewbeta","hrewbeta" ,nBinsEta-1, xBinEta);

//
//

using namespace std;

// reweighting method based on a histogram
//
double getWeight(double, TH1D*);

void addWeights(TString fdataname, TString fmcname){

  Double_t testweight(0), CombWeights(0);
  Int_t Npv(0),B_iso_Ntracks_7_Chi2_5_LoosePt05(0);
  Double_t B_pT(0), B_eta(0), B_PV_Ref_z(0);

  TH1D* hdivnpv, *hdivbpt, *hdivbeta, *hdivbpvrz, *hdivbisontrk; 

  //-------REF (DATA) FILE (NUMERATOR) --------
  //
  TFile *fd = new TFile(fdataname);
  TTree *td = (TTree*)fd->Get("T_mv");

  td->SetBranchAddress("Npv",&Npv);
  td->SetBranchAddress("B_pT",&B_pT);
  td->SetBranchAddress("B_eta",&B_eta);
  //  td->SetBranchAddress("B_PV_Ref_z",&B_PV_Ref_z);
  td->SetBranchAddress("B_iso_Ntracks_7_Chi2_5_LoosePt05",&B_iso_Ntracks_7_Chi2_5_LoosePt05);

  //-------SOURCE (MC) FILE (DENOMINATOR) --------
  //
  TFile *fm = new TFile(fmcname);
  TTree *tm = (TTree*)fm->Get("T_mv");
  tm->SetBranchAddress("Npv",&Npv);
  tm->SetBranchAddress("B_pT",&B_pT);
  tm->SetBranchAddress("B_eta",&B_eta);
  //tm->SetBranchAddress("B_PV_Ref_z",&B_PV_Ref_z);
  //  tm->SetBranchAddress("CombWeights",&CombWeights);
  tm->SetBranchAddress("B_iso_Ntracks_7_Chi2_5_LoosePt05",&B_iso_Ntracks_7_Chi2_5_LoosePt05);

  //-------GET REWEITHING HISTOGRAMS---------

  TCut someCuts = "1==1";

  //htgtnpv - target, hsrcnpv - source

  // ------ Npv -----------------------------
  hdivnpv =(TH1D*)hrewnpv->Clone("hdivnpv");
  
  TH1D* htgtnpv = new TH1D(*hrewnpv); htgtnpv->SetName("htgtnpv");
  htgtnpv->Reset(); htgtnpv->Sumw2();
  td->Draw("Npv>>htgtnpv",someCuts,"egoff");
  htgtnpv = (TH1D*)gDirectory->Get("htgtnpv");
  
  
  TH1D* hsrcnpv = new TH1D(*hrewnpv); hsrcnpv->SetName("hsrcnpv");
  hsrcnpv->Reset();hsrcnpv->Sumw2();
  tm->Draw("Npv>>hsrcnpv",someCuts,"egoff");
  hsrcnpv = (TH1D*)gDirectory->Get("hsrcnpv");
  
  hdivnpv->Reset();
  hdivnpv->Divide(htgtnpv,hsrcnpv,1./htgtnpv->Integral(),1./hsrcnpv->Integral());

  // ------ BpT -----------------------------
  hdivbpt =(TH1D*)hrewbpt->Clone("hdivbpt");
  
  TH1D* htgtbpt = new TH1D(*hrewbpt); htgtbpt->SetName("htgtbpt");
  htgtbpt->Reset(); htgtbpt->Sumw2();
  td->Draw("B_pT>>htgtbpt",someCuts,"egoff");
  htgtbpt = (TH1D*)gDirectory->Get("htgtbpt");
  
  
  TH1D* hsrcbpt = new TH1D(*hrewbpt); hsrcbpt->SetName("hsrcbpt");
  hsrcbpt->Reset();hsrcbpt->Sumw2();
  tm->Draw("B_pT>>hsrcbpt",someCuts,"egoff");
  hsrcbpt = (TH1D*)gDirectory->Get("hsrcbpt");
  
  hdivbpt->Reset();
  hdivbpt->Divide(htgtbpt,hsrcbpt,1./htgtbpt->Integral(),1./hsrcbpt->Integral());

  // ------ Beta ----------------------------  
  hdivbeta =(TH1D*)hrewbeta->Clone("hdivbeta");
  
  TH1D* htgtbeta = new TH1D(*hrewbeta); htgtbeta->SetName("htgtbeta");
  htgtbeta->Reset(); htgtbeta->Sumw2();
  td->Draw("B_eta>>htgtbeta",someCuts,"egoff");
  htgtbeta = (TH1D*)gDirectory->Get("htgtbeta");
  
  
  TH1D* hsrcbeta = new TH1D(*hrewbeta); hsrcbeta->SetName("hsrcbeta");
  hsrcbeta->Reset();hsrcbeta->Sumw2();
  tm->Draw("B_eta>>hsrcbeta",someCuts,"egoff");
  hsrcbeta = (TH1D*)gDirectory->Get("hsrcbeta");
  
  hdivbeta->Reset();
  hdivbeta->Divide(htgtbeta,hsrcbeta,1./htgtbeta->Integral(),1./hsrcbeta->Integral());

  // ------ B_PV_z ----------------------------
  /*
  hdivbpvrz =(TH1D*)hrewbpvrz->Clone("hdivbpvrz");
  
  TH1D* htgtbpvrz = new TH1D(*hrewbpvrz); htgtbpvrz->SetName("htgtbpvrz");
  htgtbpvrz->Reset(); htgtbpvrz->Sumw2();
  td->Draw("B_PV_Ref_z>>htgtbpvrz",someCuts,"egoff");
  htgtbpvrz = (TH1D*)gDirectory->Get("htgtbpvrz");
  
  
  TH1D* hsrcbpvrz = new TH1D(*hrewbpvrz); hsrcbpvrz->SetName("hsrcbpvrz");
  hsrcbpvrz->Reset();hsrcbpvrz->Sumw2();
  tm->Draw("B_PV_Ref_z>>hsrcbpvrz",someCuts,"egoff");
  hsrcbpvrz = (TH1D*)gDirectory->Get("hsrcbpvrz");
  
  hdivbpvrz->Reset();
  hdivbpvrz->Divide(htgtbpvrz,hsrcbpvrz,1./htgtbpvrz->Integral(),1./hsrcbpvrz->Integral());
  */
  // ------ B_iso_Ntracks_7_Chi2_5_LoosePt05 ----------------------------
  hdivbisontrk =(TH1D*)hrewbisontrk->Clone("hdivbisontrk");
  
  TH1D* htgtbisontrk = new TH1D(*hrewbisontrk); htgtbisontrk->SetName("htgtbisontrk");
  htgtbisontrk->Reset(); htgtbisontrk->Sumw2();
  td->Draw("B_iso_Ntracks_7_Chi2_5_LoosePt05>>htgtbisontrk",someCuts,"egoff");
  htgtbisontrk = (TH1D*)gDirectory->Get("htgtbisontrk");
  
  
  TH1D* hsrcbisontrk = new TH1D(*hrewbisontrk); hsrcbisontrk->SetName("hsrcbisontrk");
  hsrcbisontrk->Reset();hsrcbisontrk->Sumw2();
  tm->Draw("B_iso_Ntracks_7_Chi2_5_LoosePt05>>hsrcbisontrk",someCuts,"egoff");
  hsrcbisontrk = (TH1D*)gDirectory->Get("hsrcbisontrk");
  
  hdivbisontrk->Reset();
  int nbins = htgtbisontrk->GetNbinsX();
  hdivbisontrk->Divide(htgtbisontrk,hsrcbisontrk,1./htgtbisontrk->Integral(0,nbins+1),1./hsrcbisontrk->Integral(0,nbins+1));



  //-------WRITE REWEITED FILE OUT---------
  //
  TString newfname(fmcname);
  newfname.Remove(newfname.Index(".root"),newfname.Length());
  newfname.Append("_testweight.root");
  TFile *fn = new TFile(newfname,"recreate");
  TTree *tn = tm->CloneTree(0);
  TBranch *mwa = tn->Branch("testweight",&testweight,"testweight/D");
 
  Int_t N=tm->GetEntries();
  Int_t isel(0);
  Double_t w1(1.),w2(1.),w3(1.),w4(1.),w5(1.0);
  cout << "Processing entries: "<< N <<endl;
  for(int ie=0;ie<N;ie++) {
    tm->GetEntry(ie);
    isel++;
    w1 = getWeight((double)Npv,  hdivnpv);
    w2 = getWeight(B_pT,  hdivbpt);
    w3 = getWeight(B_eta, hdivbeta);
    //    w4 = getWeight(B_PV_Ref_z, hdivbpvrz);
    //w5 = getWeight(B_iso_Ntracks_7_Chi2_5_LoosePt05, hdivbisontrk);
 
    testweight = w1*w2*w3*w4*w5; //ADJUST

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
