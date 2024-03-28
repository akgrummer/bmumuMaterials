// g++ ScanTree.cpp -o ScanTree `root-config --glibs --cflags`
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
using namespace std;
void ScanTree(TString ifName){
// TFile* myfile = new TFile(idName+"/bsmumu.root","read");
TFile* myfile = new TFile(ifName,"read");
TTree* myTree = (TTree*) myfile->Get("T_mv");
myTree->SetScanField(50);//max rows
// myTree->Scan("PRIVX_mu");
myTree->Scan("PRIVX_mu:PRIVX_mu_round");
// this command does not save the scan output:
// myTree->SaveAs("/afs/cern.ch/user/a/agrummer/www/bmumu2020/nTupleBranchNames/v4/dump_MCsignal.xml");
//need to use command line instead - see BranchNamesReadMe.txt for example command:
//[>>>]./ScanTree /eos/home-a/agrummer/BsmumuData/AnalysisNtuples2020/v4/LASTskim.user.agrummer.mcBsmumu.merged.root > /afs/cern.ch/user/a/agrummer/www/bmumu2020/nTupleBranchNames/v4/dump_MCsignal.txt
delete myfile;
}

int main(int argc, char* argv[])
{
  TString ifName;
  if (argc>1) ifName = TString(argv[1]);
  ScanTree(ifName);
  return 0;
}
