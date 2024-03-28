// g++ RoundFloats.cpp -o RoundFloats `root-config --glibs --cflags`
// testing script
#include "TCut.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TLegend.h"
#include "TVector3.h"
#include "TH1.h"
#include "TBranch.h"
#include "TCanvas.h"
#include <iostream>
#include <dirent.h>
#include <TChain.h>
#include <algorithm>
#include <fstream>
#include <math.h>
using namespace std;
void RoundFloats(TString ifName){
// TFile* myfile = new TFile(idName+"/bsmumu.root","read");
TFile* myfile = new TFile(ifName,"read");
TTree* myTree = (TTree*) myfile->Get("T_mv");
float PRIVX_mu(0.);
myTree->SetBranchAddress("PRIVX_mu",  &PRIVX_mu);
myTree->GetEntry(6);
float newValue(0.);
// for MC:
// newValue = ceilf(PRIVX_mu * 10) / 10;
// for data:
newValue = ceilf(PRIVX_mu) -0.5;
cout<<"PRIVX_mu = "<< PRIVX_mu <<endl;
cout<<"newValue = "<< newValue <<endl;
delete myfile;
}

int main(int argc, char* argv[])
{
  TString ifName;
  if (argc>1) ifName = TString(argv[1]);
  RoundFloats(ifName);
  return 0;
}