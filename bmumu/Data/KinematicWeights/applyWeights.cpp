//only half of data and MC are used ot calculate the DDW, this allows to choose which half
#define USE_EVEN_EVENTS_FOR_DDW

#include <iostream>
#include <vector>
#include "TFile.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TTree.h"
#include "TMath.h"
#include "TString.h"
#include "TH1D.h"
#include "TH2D.h"


using namespace std;
using namespace TMath;


double retrieveWeight(double pt, double eta, TH2D*QLC, TH1D*DDWpt, TH1D*DDWeta){
  if(pt>DDWpt->GetXaxis()->GetXmax()) pt = DDWpt->GetXaxis()->GetBinCenter( DDWpt->GetNbinsX() );
  eta = TMath::Abs(eta);

  //retrieve inverse of QLC weight
  int QLCbin = QLC->FindBin(eta,pt);
  double wQLC = QLC->GetBinContent( QLCbin );

  //retrieve pT and eta DDW
  double wDDWpt = DDWpt->GetBinContent( DDWpt->FindBin(pt) );
  double wDDWeta = DDWeta->GetBinContent( DDWeta->FindBin(eta) );

  //return the total weight
  return (wDDWpt*wDDWeta)/wQLC;
}




void applyWeights(){
  //some simple histograms
  TH1D * h_Bpt = new TH1D("h_Bpt","h_Bpt", 192,8000,200000);
  TH1D * h_Bpt_weighted = new TH1D("h_Bpt_weighted","h_Bpt_weighted", 192,8000,200000);
  TH1D * h_Beta = new TH1D("h_Beta","h_Beta", 50, 0,2.5);
  TH1D * h_Beta_weighted = new TH1D("h_Beta_weighted","h_Beta_weighted", 50, 0,2.5);

  TString kindOfDDW = "_odd";
#ifdef USE_EVEN_EVENTS_FOR_DDW
  kindOfDDW = "_even";
#endif

  TString QLCfileName = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/DDW/v1/QLCfile_BpToJpsiK.root";
  TString DDWfileName = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/DDW/v1/DDWfile_BpToJpsiK.root";
  TString MCfileName = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuRel21Prod1/ntup/skimmed_MC/BpJpsiKplus/v1.1/mc16_13TeV.300404.Pythia8BEvtGen_A14_CTEQ6L1_Bp_Jpsi_mu3p5mu3p5_Kp_BMassFix.deriv.NTUP_SKIMMED_BPHY8.e4862_e5984_a875_r9364_r9315_p3371_BJpsiK/output_1317670.root"; //run just on one file 

  ////////////////////////////////////////////////////////
  //load histograms with weights
  //load QLC
  TFile * QLCinput = new TFile(QLCfileName,"READ");
  QLCinput->cd();
  TH2D * QLC = (TH2D*)QLCinput->Get("h_QLC_BpJpsiK");
  QLC->SetDirectory(0);
  QLCinput->Close();

  //load properly calculated DDW  
  TFile * DDWinput = new TFile(DDWfileName,"READ");
  TH1D * combinedPtDDW = (TH1D*) DDWinput->Get("h_DDWpt"+kindOfDDW+"_BpJpsiK");
  TH1D * combinedEtaDDW = (TH1D*) DDWinput->Get("h_DDWeta"+kindOfDDW+"_BpJpsiK");
  combinedPtDDW->SetDirectory(0);
  combinedEtaDDW->SetDirectory(0);
  DDWinput->Close();
  ////////////////////////////////////////////////////////


  //loop over the MC
  TFile * MCinput = new TFile (MCfileName,"READ");
  TTree * ntup = (TTree*)MCinput->Get("T_mv");
  double Bpt, Beta;
  int eventNuber;
  ntup->SetBranchAddress("B_pT",&Bpt);
  ntup->SetBranchAddress("B_eta",&Beta);
  ntup->SetBranchAddress("event_number", &eventNumber);
  int nEntries = ntup->GetEntries();

  for(int iEntry = 0;iEntry<nEntries;iEntry++){
    ntup->GetEntry(iEntry);

    //use the other half of the MC
#ifdef USE_EVEN_EVENTS_FOR_DDW
    if(eventNumber%2 == 0) continue;
#else    
    if(eventNumber%2 != 0) continue;
#endif

    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    //apply cuts, here apply only B fiducial volume
    if(Bpt < 8000 || TMath::Abs(Beta) > 2.5) continue;
    

    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////

    //retrieve weight
    double W = retrieveWeight(Bpt, Beta, QLC , combinedPtDDW, combinedEtaDDW);

    //fill the plots
    h_Bpt->Fill(Bpt);
    h_Bpt_weighted->Fill(Bpt, W);
    h_Beta->Fill(Beta);
    h_Beta_weighted->Fill(Beta, W);
  }







  
  TCanvas * c1 = new TCanvas();
  c1->cd();
  QLC->Draw();


  TCanvas * c2 = new TCanvas();
  c2->cd();
  combinedPtDDW->Draw();


  TCanvas * c3 = new TCanvas();
  c3->cd();
  combinedEtaDDW->Draw();


  TCanvas * c4 = new TCanvas();
  c4->Divide(2,1);
  TPad * p1 = (TPad*)c4->cd(1);
  h_Bpt->SetLineColor(kRed);
  h_Bpt->DrawNormalized("E");
  h_Bpt_weighted->DrawNormalized("SAME");
  p1->BuildLegend();

  TPad * p2 = (TPad*)c4->cd(2);
  h_Beta->SetLineColor(kRed);
  h_Beta->DrawNormalized("E");
  h_Beta_weighted->DrawNormalized("SAME");
  p2->BuildLegend();
  

}
  
  
 
