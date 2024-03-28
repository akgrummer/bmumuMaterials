#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TChain.h"
#include <iostream>
#include <dirent.h>
using namespace std;

void Run1docaMacro(TString indir="", TString DataType=""){
  TString finpath(indir);
  TString outdir("");
  outdir = "/eos/home-a/agrummer/BsmumuData/Run1";

  TChain *ts = new TChain("T_mv");
  ts->Add(finpath);

  TString foutpath(outdir);
  if(DataType.EqualTo("MC")){
      foutpath.Append("/MC");} 
  else if(DataType.EqualTo("Data")){
      foutpath.Append("/Data");}
  foutpath.Append("/");
  Int_t lsl = indir.Last('/');
  Int_t len = indir.Length();
  foutpath.Append(indir(lsl+1, len-lsl-1)); 
  foutpath.Append("_doca3.root");
  
  cout<< "Entries in original tree: "<< ts->GetEntries() <<endl;
  auto nevents = ts->GetEntries();

  double closeTrkDCA, closeTrkZCA;
  ts->SetBranchAddress("closeTrkDCA",  &closeTrkDCA);
  ts->SetBranchAddress("closeTrkZCA",  &closeTrkZCA);

  double closeTrkDOCA_3;

  TFile *fn = new TFile(foutpath,"recreate");
  TTree *tf = ts->CloneTree(0);
  TBranch* b3 = tf->Branch("closeTrkDOCA_3",&closeTrkDOCA_3,"closeTrkDOCA_3/D");
  cout<< "Now loop over original tree" << endl; 
  for (auto ievent=0; ievent<nevents; ievent++)
    {
      if (ievent%100000==0) cout << "Processing event "<< ievent << endl;
      ts->GetEntry(ievent);

      closeTrkDOCA_3 = (double) sqrt(pow(closeTrkDCA,2)+pow(closeTrkZCA,2));
      if (closeTrkDOCA_3 > 3.) closeTrkDOCA_3 = 3.;
      tf->Fill();
    }
  cout<< "Entries in final tree: "<< tf->GetEntries() <<endl;
  fn->cd();
  tf->Write();
  fn->Close();
}

int main(int argc, char* argv[])
{
  TString inpath, DataType;
  if (argc>1) inpath = TString(argv[1]);
  if (argc>2) DataType = TString(argv[2]);
  Run1docaMacro(inpath, DataType);
  return 0;
}
