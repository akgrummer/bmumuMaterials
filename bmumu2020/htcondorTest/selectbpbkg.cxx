// takes bbJpsiX nominal ntuple as the input
// vetoes B+JPsiK(pi)+(gamma) events
// keepeng the rest in a new ntuple
#include "TCut.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1.h"
#include "TH2.h"
#include "TBranch.h"
#include <iostream>

using namespace std;
void selectbpbkg(TString finname, TString foutname) {
  string* decay = 0;
  TFile *fin = new TFile(finname);
  TTree *tin = (TTree*)fin->Get("T_mv");
  tin->SetBranchAddress("decay", &decay);

  TFile *fout = new TFile(foutname, "recreate");
  TTree *tout = tin->CloneTree(0);
  int category(-1);
  TBranch* b1 = tout->Branch("category",&category,"category/I");
  Long64_t nevents = tin->GetEntries();
  cout<< "Entries in input tree: "<< tin->GetEntries() <<endl;
  for (auto ievent=0; ievent<nevents; ievent++)
    {
      if (ievent%100000==0) cout << "Processing event "<< ievent << endl;
      tin->GetEntry(ievent);
      if ( ((TString)*decay).Contains("B+[K+:J/psi[mu+:mu-") ||
	   ((TString)*decay).Contains("B+[gamma:K+:J/psi[mu+:mu-") ||
	   ((TString)*decay).Contains("B+[gamma:gamma:K+:J/psi[mu+:mu-") ||
	   ((TString)*decay).Contains("B+[gamma:gamma:gamma:K+:J/psi[mu+:mu-") ||
	   ((TString)*decay).Contains("B-[K-:J/psi[mu+:mu-") ||
	   ((TString)*decay).Contains("B-[gamma:K-:J/psi[mu+:mu-") ||
	   ((TString)*decay).Contains("B-[gamma:gamma:K-:J/psi[mu+:mu-") ||
	   ((TString)*decay).Contains("B-[gamma:gamma:gamma:K-:J/psi[mu+:mu-") ) category = 0; //signal
      else if (
	   ((TString)*decay).Contains("B+[pi+:J/psi[mu+:mu-") ||
	   ((TString)*decay).Contains("B+[gamma:pi+:J/psi[mu+:mu-") ||
	   ((TString)*decay).Contains("B+[gamma:gamma:pi+:J/psi[mu+:mu-") ||
	   ((TString)*decay).Contains("B+[gamma:gamma:gamma:pi+:J/psi[mu+:mu-") ||
	   ((TString)*decay).Contains("B-[pi-:J/psi[mu+:mu-") ||
	   ((TString)*decay).Contains("B-[gamma:pi-:J/psi[mu+:mu-") ||
	   ((TString)*decay).Contains("B-[gamma:gamma:pi-:J/psi[mu+:mu-") ||
	   ((TString)*decay).Contains("B-[gamma:gamma:gamma:pi-:J/psi[mu+:mu-") ) category = 1; //Cabibbo
      else if ( (*decay)=="combinatorial" || (*decay)=="unmatched") category = 2;
      else category = 3;
      tout->Fill(); 
    }
  cout<< "Entries in final tree: "<< tout->GetEntries() <<endl;
  fout->cd();
  if (!tout->GetEntries()) {
    cout<< "Only vetoed BJpsiK(pi)[gamma] candidates found, closing the files without writing, continuing. "<< endl;
  } else {
    fout->Write();
  }
  fout->Close();
  fin->cd();
  fin->Close();
}

int main(int argc, char* argv[])
{
  TString fin, fout;
  if (argc!=3) {
    cout << "Exiting: Input and output files to be provided, i.e. selectbpbkg fin fout"<< endl;
    exit(0);
  }
  fin = TString(argv[1]);
  fout = TString(argv[2]);
  selectbpbkg(fin, fout);
  return 0;
}
