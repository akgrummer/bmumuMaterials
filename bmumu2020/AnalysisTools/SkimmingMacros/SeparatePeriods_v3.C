// to run Separate Periods on lxplus:
// for Coarse separation
// root -l -b -q SeparatePeriods_v3.C"(\"Coarse\")"
// for data period separation:
// root -l -b -q SeparatePeriods_v3.C

void SeparatePeriods_v3(TString SepCoarse = "") {
  if (SepCoarse.EqualTo("Coarse")) cout<<"Performing Coarse Separation" <<endl;
  else cout<<"Performing Data Period Separation" <<endl;

    // TString ifilename = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimFeb13/LASTskim.Data_2015HLTand2016HLTLxy_Main_15Feb.root";
    // TString ifilename = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimFeb13/LASTskim.bbmumuX2Bsmumu_GBRweight.root";
    // TString ifilename = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/SidebandTrained/data1516Bs.root";
    TString ifilename = "/eos/home-a/agrummer/BsmumuData/AnalysisNtuples2020/v4/LASTskim.user.agrummer.Data1516.merged.root";

    TFile *ifile;
    ifile = new TFile(ifilename);
    TTree *inputtree = (TTree*)ifile->Get("T_mv");
    Long64_t nentries = inputtree->GetEntries();
    UInt_t run_number;
    inputtree->SetBranchAddress("run_number",&run_number);
    //Create a new file + a clone of old tree in new file
    TFile *ofile;
    TString ofilename(ifilename);
    ofilename.Remove(ofilename.Index(".root"),ofilename.Length());
    if (SepCoarse.EqualTo("Coarse")) ofilename.Append("_SepCoarse.root");
    else ofilename.Append("_SepPeriods.root");
    ofile = new TFile(ofilename, "recreate");
      
    TTree *newtree2015A, *newtree2015B, *newtree2015C, *newtree2015D, 
          *newtree2015E, *newtree2015F, *newtree2015G, *newtree2015H,
          *newtree2015I, *newtree2015J, *newtree2015K, *newtree2015L;
    TTree *newtree2016A, *newtree2016B, *newtree2016C, *newtree2016D, 
          *newtree2016E, *newtree2016F, *newtree2016G, *newtree2016H,
          *newtree2016I, *newtree2016J, *newtree2016K, *newtree2016L;
    TTree *newtree2015, *newtree2016preTS1, *newtree2016TS1toMD1, 
          *newtree2016postMD1;


//The data periods:
// 15D, 15E, 15F, 15G, 15H, 15J, 
// 16A, 16B, 16C, 16D, 16E, 16F, 16G, 16I, 16K, 16L


    
    newtree2015D = inputtree->CloneTree(0); newtree2015D->SetName("T_mv_2015D");
    newtree2015E = inputtree->CloneTree(0); newtree2015E->SetName("T_mv_2015E");
    newtree2015F = inputtree->CloneTree(0); newtree2015F->SetName("T_mv_2015F");
    newtree2015G = inputtree->CloneTree(0); newtree2015G->SetName("T_mv_2015G");
    newtree2015H = inputtree->CloneTree(0); newtree2015H->SetName("T_mv_2015H");
    newtree2015J = inputtree->CloneTree(0); newtree2015J->SetName("T_mv_2015J");

    newtree2016A = inputtree->CloneTree(0); newtree2016A->SetName("T_mv_2016A");
    newtree2016B = inputtree->CloneTree(0); newtree2016B->SetName("T_mv_2016B");
    newtree2016C = inputtree->CloneTree(0); newtree2016C->SetName("T_mv_2016C");
    newtree2016D = inputtree->CloneTree(0); newtree2016D->SetName("T_mv_2016D");
    newtree2016E = inputtree->CloneTree(0); newtree2016E->SetName("T_mv_2016E");
    newtree2016F = inputtree->CloneTree(0); newtree2016F->SetName("T_mv_2016F");
    newtree2016G = inputtree->CloneTree(0); newtree2016G->SetName("T_mv_2016G");
    newtree2016I = inputtree->CloneTree(0); newtree2016I->SetName("T_mv_2016I");
    newtree2016K = inputtree->CloneTree(0); newtree2016K->SetName("T_mv_2016K");
    newtree2016L = inputtree->CloneTree(0); newtree2016L->SetName("T_mv_2016L");

    newtree2015 = inputtree->CloneTree(0); newtree2015->SetName("T_mv_2015");
    newtree2016preTS1 = inputtree->CloneTree(0); newtree2016preTS1->SetName("T_mv_2016preTS1");
    newtree2016TS1toMD1 = inputtree->CloneTree(0); newtree2016TS1toMD1->SetName("T_mv_2016TS1toMD1");
    newtree2016postMD1 = inputtree->CloneTree(0); newtree2016postMD1->SetName("T_mv_2016postMD1");

if (SepCoarse.EqualTo("Coarse")){
    for (Long64_t i=0;i<nentries; i++) {
        inputtree->GetEntry(i);
        if (run_number >= 276073 && run_number <= 284484) newtree2015->Fill();//2015 beginD to end J
        // last run before technical stop 1: 300908 (June 6, 2016)
        else if (run_number >= 266904 && run_number <= 300908) newtree2016preTS1->Fill();
        // first fun after TS: 301912 (June 11, 2016)
        // last run before Machine Developement 1:  304494 (July, 25, 2016)
        else if (run_number >= 301912 && run_number <= 304494) newtree2016TS1toMD1->Fill();
        // first run afer MD1: 305291 (Aug. 1st, 2016)
        else if (run_number >= 305291 && run_number <= 311481) newtree2016postMD1->Fill(); 

        if (i % 30000 == 0) cout << i << " of " << nentries <<endl;
    }//end of for Coarse loop
    if(newtree2015->GetEntries()!=0) newtree2015->AutoSave();
    if(newtree2016preTS1->GetEntries()!=0) newtree2016preTS1->AutoSave();
    if(newtree2016TS1toMD1->GetEntries()!=0) newtree2016TS1toMD1->AutoSave();
    if(newtree2016postMD1->GetEntries()!=0) newtree2016postMD1->AutoSave();
  }//end of if Coarse
  else{
      for (Long64_t i=0;i<nentries; i++) {
          inputtree->GetEntry(i);
          if (run_number >= 276073 && run_number <= 276954) newtree2015D->Fill(); //D
          else if (run_number >= 278727 && run_number <= 279928) newtree2015E->Fill(); //E
          else if (run_number >= 279932 && run_number <= 280422) newtree2015F->Fill(); //F
          else if (run_number >= 280423 && run_number <= 281075) newtree2015G->Fill(); //G
          else if (run_number >= 281130 && run_number <= 281411) newtree2015H->Fill(); //H
          else if (run_number >= 282625 && run_number <= 284484) newtree2015J->Fill(); //J
  
          else if (run_number >= 296939 && run_number <= 300287) newtree2016A->Fill();//A
          else if (run_number >= 300345 && run_number <= 300908) newtree2016B->Fill();//B
          else if (run_number >= 301912 && run_number <= 302393) newtree2016C->Fill(); // C
          else if (run_number >= 302737 && run_number <= 303560) newtree2016D->Fill(); // D
          else if (run_number >= 303638 && run_number <= 303892) newtree2016E->Fill(); // E
          else if (run_number >= 303943 && run_number <= 304494) newtree2016F->Fill(); // F
          else if (run_number >= 305291 && run_number <= 306714) newtree2016G->Fill(); // G
          else if (run_number >= 307124 && run_number <= 308084) newtree2016I->Fill(); // I //first run_number not 
          else if (run_number >= 309311 && run_number <= 309759) newtree2016K->Fill(); // K
          else if (run_number >= 310015 && run_number <= 311481) newtree2016L->Fill(); // L  
  //        run_number->Clear();
          if (i % 30000 == 0) cout << i << " of " << nentries <<endl;
        }//end of data period for loop
 

    if(newtree2015D->GetEntries()!=0) newtree2015D->AutoSave();
    if(newtree2015E->GetEntries()!=0) newtree2015E->AutoSave();
    if(newtree2015F->GetEntries()!=0) newtree2015F->AutoSave();
    if(newtree2015G->GetEntries()!=0) newtree2015G->AutoSave();
    if(newtree2015H->GetEntries()!=0) newtree2015H->AutoSave();
    if(newtree2015J->GetEntries()!=0) newtree2015J->AutoSave();

    if(newtree2016A->GetEntries()!=0) newtree2016A->AutoSave();
    if(newtree2016B->GetEntries()!=0) newtree2016B->AutoSave();
    if(newtree2016C->GetEntries()!=0) newtree2016C->AutoSave();
    if(newtree2016D->GetEntries()!=0) newtree2016D->AutoSave();
    if(newtree2016E->GetEntries()!=0) newtree2016E->AutoSave();
    if(newtree2016F->GetEntries()!=0) newtree2016F->AutoSave();
    if(newtree2016G->GetEntries()!=0) newtree2016G->AutoSave();
    if(newtree2016I->GetEntries()!=0) newtree2016I->AutoSave();
    if(newtree2016K->GetEntries()!=0) newtree2016K->AutoSave();
    if(newtree2016L->GetEntries()!=0) newtree2016L->AutoSave();
  }//end of else (if coarse)

    // newtreeZ->AutoSave();
    // ofile->Write();
    delete ifile;
    delete ofile;
}


