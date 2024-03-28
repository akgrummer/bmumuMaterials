//Run with 
//for low pile up region:
// root -l -q SeparatePileUpSets.C"(\"1\")" 
//for middle pile up region:
// root -l -q SeparatePileUpSets.C"(\"2\")"
//for high pile up region:
// root -l -q SeparatePileUpSets.C"(\"3\")"

void SeparatePileUpSets(TString PileUpBin = "1") {
    cout<<"Splitting Data on Pile Up" <<endl;

    // TString ifilename = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimFeb13/LASTskim.mc16_13TeV.300307.HLT_mu6_mu4_bBmumu_Lxy0.Feb14_testweight.root";
    // TString ifilename = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkimGBR3blinded/LASTskim.bbmumuX2Bsmumu_combinatorial_GBRweight.root";
    // TString ifilename = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkimGBR4_Mar26/LASTskim.bbmumuX2Bsmumu_combinatorial_GBRweight.root";
    // TString ifilename = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimRightSideband/LASTskim.Data_2015HLTand2016HLTLxy_RightSideband_DOCAlt500.root";
    // TString ifilename = "/afs/cern.ch/user/a/agrummer/www/bmumu/Data/LASTskim.MC16Bs_DOCAlt500_EvalSet.root";
    // TString ifilename = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/EvalSetMC/LASTskim.MC16Bs_DOCAlt500_EvalSet.root";
    // TString ifilename = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskim.MC16Bs.root";
    //for pile up split training and then eval with DDW+QLC
    // TString ifilename = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/SignalMC/LASTskim.MC16Bs_CombWeights_DOCAlt500_EvalSet.root";
    // TString ifilename = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/SignalMC/LASTskim.MC16Bs_CombWeights_DOCAlt500_TrainTestSet.root";
    TString ifilename = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkimGBR4_Mar26/LASTskim.bbmumuX2Bsmumu_combinatorial_GBRweight_DOCAlt500.root";

//eval samples (right sidebanc)
// LASTskimRightSideband/LASTskim.Data_2015HLTand2016HLTLxy_RightSideband_DOCAlt500.root";
// LASTskimRightSideband/LASTskim.Data_2015HLTand2016HLTLxy_RightSideband_DOCAlt500_MiddlePileUp.root
// LASTskimRightSideband/LASTskim.Data_2015HLTand2016HLTLxy_RightSideband_DOCAlt500_LowPileUp.root
// LASTskimRightSideband/LASTskim.Data_2015HLTand2016HLTLxy_RightSideband_DOCAlt500_HighPileUp.root

    //training sample (bbmumuX MC)
    // LASTskim.bbmumuX2Bsmumu_combinatorial_GBRweight_DOCAlt500.root

    TFile *ifile;
    ifile = new TFile(ifilename, "READ");
    TTree *inputtree = (TTree*)ifile->Get("T_mv");
    Long64_t nentries = inputtree->GetEntries();
    // string *MyDecay;
    // inputtree->SetBranchAddress("decay",&MyDecay);
    // Float_t closeTrkDCA;
    // ULong64_t event_number;
    Int_t Npv;
    // inputtree->SetBranchAddress("closeTrkDCA", &closeTrkDCA);
    // inputtree->SetBranchAddress("event_number", &event_number);
    inputtree->SetBranchAddress("Npv", &Npv);
    // TMath::Abs(closeTrkDCA)<500
    //Create a new file + a clone of old tree in new file
    TFile *ofile;
    TString ofilename(ifilename);
    ofilename.Remove(ofilename.Index(".root"),ofilename.Length());
    if(PileUpBin.EqualTo("1")){
        ofilename.Append("_LowPileUp2.root");
    }else if(PileUpBin.EqualTo("2")){
        ofilename.Append("_MiddlePileUp2.root");
    }else if(PileUpBin.EqualTo("3")){
        ofilename.Append("_HighPileUp2.root");
    }
    // ofilename.Append("_TrainTestSet.root");
    ofile = new TFile(ofilename, "recreate");

    // string CombDecay = "combinatorial";
      
    TTree *newtree;
 
    newtree = inputtree->CloneTree(0); newtree->SetName("T_mv");
      for (Long64_t i=0;i<nentries; i++) {
          inputtree->GetEntry(i);
          if(PileUpBin.EqualTo("1")){
              if ( Npv > 11 ) continue;
          }else if (PileUpBin.EqualTo("2")){
              if ( Npv <= 11 || Npv > 15) continue;
          }else if (PileUpBin.EqualTo("3")){
              if ( Npv <= 15) continue;
          }
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


