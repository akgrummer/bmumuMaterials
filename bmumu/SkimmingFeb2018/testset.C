float testset()
{
 TString outdir("./AidanTest.root");
   TString indir("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuRel21Prod1/ntup/skimmed_data/v3/user.acampove.data15_13TeV.periodD.physics_Main.BPHY8_FNTUP.grp16_v01_p3583_retry_001_Bmumu.root");
   
    TString fnpath(outdir);
    // fnpath.Append("/LASTskim.");
    Int_t lsl = indir.Index("acampove");
    Int_t lsp = indir.Index(".period");
    Int_t len = indir.Length();

    Int_t outlsl = outdir.Index(".root");
    // Int_t outlsp = indir.Last(".period");
    Int_t outlen = outdir.Length();

    cout<<" lsl "<< lsl <<" lsp "<< lsp <<" len "<< len <<" outlsl "<< outlsl <<" outlen "<< outlen <<endl;
    if (outlsl!=-1) fnpath.Remove(outlsl+1, outlen); 
    // fnpath.Remove(".root"); 
    // fnpath.Append(indir(lsl+1, len-lsl-1)); 
    if (lsl!=-1 && lsp!=-1) fnpath.Append(indir(lsl+9, lsp-lsl-1)); 
    fnpath.Append(".root"); //if getting ..root check lsl and lsp
    cout<<"writing histograms to fnpath: " <<fnpath<<endl;

   // TString fnpath(outdir);
   TFile *fn = new TFile(fnpath,"recreate");
  //declaration
  set< pair<float,float> > eventSet;
  set<float> runSet;
  cout<<"hello" << endl;
  
  //read 4 values from user
  float x,y;
  for(float i=0; i<4; i++)
    {
      cin>>x>>y;
      eventSet.insert(make_pair(x,y));
      runSet.insert(x);
    }
  //then you have a set of values of non-duplicate x,y
  cout<<"hello" << endl;
  cout << endl;  
  //Access the elements
  // set< pair<float,float> >::iterator it;
  // for(it=eventSet.begin(); it!=eventSet.end(); ++it)
  //   {
  //     //first is x, y is the second element
  //     cout<<it->first<<" "<<it->second<<endl;
  //   }
  cout<<"size: "<< eventSet.size()<<endl;
  cout<<"run size: "<< runSet.size()<<endl;

  TH1F *h1 = new TH1F("h1", "h1 title", 2, 0, 2);
  h1->SetBinContent(1, eventSet.size());
  h1->Integral(0,100+1);
  cout << "hist int: "<<h1->Integral(0,2+1)<< endl;
  
  // h1->Fill(x, w); //fill with weight

  fn->cd();
  h1->Write();
  fn->Close();

  return 0;
}
