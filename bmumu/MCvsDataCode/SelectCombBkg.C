
void SelectCombBkg() {
    cout<<"Performing Combinatorial Bkg Selection" <<endl;

    // TString ifilename = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimFeb13/LASTskim.mc16_13TeV.300307.HLT_mu6_mu4_bBmumu_Lxy0.Feb14_testweight.root";
    TString ifilename = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimFeb13/LASTskim.bbmumuX2Bsmumu_GBRweight.root";

    TFile *ifile;
    ifile = new TFile(ifilename);
    TTree *inputtree = (TTree*)ifile->Get("T_mv");
    Long64_t nentries = inputtree->GetEntries();
    string *MyDecay;
    inputtree->SetBranchAddress("decay",&MyDecay);
    //Create a new file + a clone of old tree in new file
    TFile *ofile;
    TString ofilename(ifilename);
    ofilename.Remove(ofilename.Index(".root"),ofilename.Length());
    ofilename.Append("_CombBkg.root");
    ofile = new TFile(ofilename, "recreate");

    string CombDecay = "combinatorial";
      
    TTree *newtree;
 
    newtree = inputtree->CloneTree(0); newtree->SetName("T_mv");
      for (Long64_t i=0;i<nentries; i++) {
          inputtree->GetEntry(i);
          if (CombDecay.compare(*MyDecay) == 0) newtree->Fill();
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


