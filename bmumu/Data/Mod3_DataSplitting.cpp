
void Mod3_DataSplitting(TString ModSet = "2") {
    cout<<"Splitting 15/16 data in thirds number: " << ModSet << endl;

    // TString ifilename = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimFeb13/LASTskim.mc16_13TeV.300307.HLT_mu6_mu4_bBmumu_Lxy0.Feb14_testweight.root";
    // TString ifilename = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkimGBR3blinded/LASTskim.bbmumuX2Bsmumu_combinatorial_GBRweight.root";
    // TString ifilename = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkimGBR4_Mar26/LASTskim.bbmumuX2Bsmumu_combinatorial_GBRweight.root";
    // TString ifilename = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimRightSideband/LASTskim.Data_2015HLTand2016HLTLxy_RightSideband.root";
    // TString ifilename = "/afs/cern.ch/user/a/agrummer/www/bmumu/Data/LASTskim.MC16Bs_DOCAlt500.root";
    // TString ifilename = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/SignalMC/LASTskim.MC16Bs_CombWeights_DOCAlt500.root";
    // TString ifilename = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/SidebandTrained/data1516Bs.root";
    TString ifilename = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/SidebandTrained/LASTskim.mc16Bs.root";
    // TString ifilename = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/SidebandTrained/data1516Bs_RightSideband.root";

    TFile *ifile;
    ifile = new TFile(ifilename);
    TTree *inputtree = (TTree*)ifile->Get("T_mv");
    Long64_t nentries = inputtree->GetEntries();
    // string *MyDecay;
    // inputtree->SetBranchAddress("decay",&MyDecay);
    // Float_t closeTrkDCA;
    ULong64_t event_number;
    // double B_MUCALC_mass;
    // inputtree->SetBranchAddress("closeTrkDCA", &closeTrkDCA);
    inputtree->SetBranchAddress("event_number", &event_number);
    // inputtree->SetBranchAddress("B_MUCALC_mass",&B_MUCALC_mass);
    // TMath::Abs(closeTrkDCA)<500
    //Create a new file + a clone of old tree in new file
    TFile *ofile;
    TString ofilename(ifilename);
    ofilename.Remove(ofilename.Index(".root"),ofilename.Length());


    if(ModSet.Contains("1")){
        ofilename.Append("_SplitSet_1.root");
    }else if(ModSet.Contains("2")){
        ofilename.Append("_SplitSet_2.root");
    }else if(ModSet.Contains("3")){
        ofilename.Append("_SplitSet_3.root");
    }
    // ofilename.Append("_TrainTestSet.root");
    ofile = new TFile(ofilename, "recreate");

    // string CombDecay = "combinatorial";
      
    TTree *newtree;
 
    newtree = inputtree->CloneTree(0); newtree->SetName("T_mv");
      for (Long64_t i=0;i<nentries; i++) {
          inputtree->GetEntry(i);
          if(ModSet.Contains("1")){
              if (event_number%3 != 0 ) continue;
          }else if(ModSet.Contains("2")){
              if (event_number%3 != 1 ) continue;
          }else if(ModSet.Contains("3")){
              if (event_number%3 != 2 ) continue;
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

    newtree->AutoSave();

    delete ifile;
    delete ofile;
}


