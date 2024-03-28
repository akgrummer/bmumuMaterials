//Run with 
//for low pile up region:
// root -l SeparatePileUpSets.C"(\"1\")" 
//for middle pile up region:
// root -l SeparatePileUpSets.C"(\"2\")"
//for high pile up region:
// root -l SeparatePileUpSets.C"(\"3\")"

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


// TString ifilename = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/EvalSetMC/LASTskim.MC16Bs_DOCAlt500_EvalSet.root"
void applyKinematicWeights(TString ifilename = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/SignalMC/LASTskim.MC16Bs.root") {
    cout<<"Applying Kinematic Weights to Signal MC" <<endl;


      //some simple histograms
  TH1D * h_Bpt = new TH1D("h_Bpt","h_Bpt", 192,8000,200000);
  TH1D * h_Bpt_weighted = new TH1D("h_Bpt_weighted","h_Bpt_weighted", 192,8000,200000);
  TH1D * h_Beta = new TH1D("h_Beta","h_Beta", 50, 0,2.5);
  TH1D * h_Beta_weighted = new TH1D("h_Beta_weighted","h_Beta_weighted", 50, 0,2.5);

  TString kindOfDDW = "_odd";
#ifdef USE_EVEN_EVENTS_FOR_DDW
  kindOfDDW = "_even";
#endif

  // TString QLCfileName = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/DDW/v1/QLCfile_BsToMuMu_preliminary.root";
  // TString DDWfileName = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/DDW/v1/DDWfile_BpToJpsiK.root";
  TString QLCfileName = "/afs/cern.ch/user/a/agrummer/www/bmumu/Data/KinematicWeights/QLCfile_BsToMuMu_preliminary.root";
  TString DDWfileName = "/afs/cern.ch/user/a/agrummer/www/bmumu/Data/KinematicWeights/DDWfile_BpToJpsiK.root";


  ////////////////////////////////////////////////////////
  //load histograms with weights
  //load QLC
  TFile * QLCinput = new TFile(QLCfileName,"READ");
  QLCinput->cd();
  TH2D * QLC = (TH2D*)QLCinput->Get("h_QLC_BsMuMu");
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


  Double_t testweight(0), CombWeights(0);
  Int_t Npv(0),B_iso_Ntracks_7_Chi2_5_LoosePt05(0); 
  ULong64_t eventNumber(0);
  Double_t B_pT(0), B_eta(0), B_PV_Ref_z(0);

    // TString ifilename = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimFeb13/LASTskim.mc16_13TeV.300307.HLT_mu6_mu4_bBmumu_Lxy0.Feb14_testweight.root";
    // TString ifilename = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkimGBR3blinded/LASTskim.bbmumuX2Bsmumu_combinatorial_GBRweight.root";
    // TString ifilename = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkimGBR4_Mar26/LASTskim.bbmumuX2Bsmumu_combinatorial_GBRweight.root";
    // TString ifilename = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimRightSideband/LASTskim.Data_2015HLTand2016HLTLxy_RightSideband_DOCAlt500.root";
    // TString ifilename = "/afs/cern.ch/user/a/agrummer/www/bmumu/Data/LASTskim.MC16Bs_DOCAlt500_EvalSet.root";
    // TString ifilename = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/EvalSetMC/LASTskim.MC16Bs_DOCAlt500_EvalSet.root";
    // TString ifilename = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskim.MC16Bs.root";

    TFile *ifile;
    ifile = new TFile(ifilename, "READ");
    TTree *inputtree = (TTree*)ifile->Get("T_mv");
    Long64_t nentries = inputtree->GetEntries();

    inputtree->SetBranchAddress("Npv",&Npv);
    inputtree->SetBranchAddress("B_pT",&B_pT);
    inputtree->SetBranchAddress("B_eta",&B_eta);
    //inputtree->SetBranchAddress("B_PV_Ref_z",&B_PV_Ref_z);
    inputtree->SetBranchAddress("CombWeights",&CombWeights);
    inputtree->SetBranchAddress("B_iso_Ntracks_7_Chi2_5_LoosePt05",&B_iso_Ntracks_7_Chi2_5_LoosePt05);
    inputtree->SetBranchAddress("event_number", &eventNumber);


    //Create a new file + a clone of old tree in new file
    TFile *ofile;
    TString ofilename(ifilename);
    ofilename.Remove(ofilename.Index(".root"),ofilename.Length());

    ofilename.Append("_CombWeights.root");
    ofile = new TFile(ofilename, "recreate");

    // string CombDecay = "combinatorial";
      
    TTree *newtree;
 
    newtree = inputtree->CloneTree(0); newtree->SetName("T_mv");
      for (Long64_t i=0;i<nentries; i++) {
          inputtree->GetEntry(i);


            if(B_pT < 8000 || TMath::Abs(B_eta) > 2.5) continue;
            //use the other half of the MC
            #ifdef USE_EVEN_EVENTS_FOR_DDW
                if(eventNumber%2 == 0){
                CombWeights = retrieveWeight(B_pT, B_eta, QLC , combinedPtDDW, combinedEtaDDW);
                }
            #else    
                if(eventNumber%2 != 0){
                CombWeights = retrieveWeight(B_pT, B_eta, QLC , combinedPtDDW, combinedEtaDDW);
                }
            #endif


          newtree->Fill();
          if (i % 30000 == 0) cout << i << " of " << nentries <<endl;
        }//end of data period for loop
    Long64_t nentriesNewTree = newtree->GetEntries();
    Long64_t entriesCut;
    entriesCut = nentries - nentriesNewTree;
    cout<<"Entries in input tree: "<<nentries<<endl;
    cout<<"Entries in new tree: "<<nentriesNewTree<<endl;
    cout<<"Entries Cut: "<<entriesCut<<endl;

    // newtree->AutoSave();
    ofile->cd();
    //  tn->Print();
    newtree->Write();
    ofile->Close();

    // delete ifile;
    // delete ofile;
}


