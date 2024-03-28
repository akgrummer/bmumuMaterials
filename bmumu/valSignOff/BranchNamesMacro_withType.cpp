// g++ BranchNamesMacro.cpp -o BranchNamesMacro `root-config --glibs --cflags`
//this codes was not tested - the type information is included in the GetTitle call
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
void BranchNamesMacro(TString idName, TString ifName){
// TFile* myfile = new TFile(idName+"/bsmumu.root","read");
TFile* myfile = new TFile(idName+"/"+ifName,"read");
TTree* myTree = (TTree*) myfile->Get("T_mv");
TTree* myTreeEV = (TTree*) myfile->Get("EventInfo");
TObjArray *mycopy = myTree->GetListOfBranches(); 
// TObjArray *mycopy = myTree->GetListOfBranches()->Clone(); 
mycopy->SetOwner(kFALSE); 
mycopy->Sort();

TObjArray *mycopyEV = myTreeEV->GetListOfBranches(); 
mycopyEV->SetOwner(kFALSE); 
mycopyEV->Sort();

// for(int i = 0; i < array->GetEntries(); ++i) { cout << array->At(i)->GetName() << '\n'; }
TString ofileName("");
ofileName = idName;
ofileName.Remove(0,idName.Last('/')+1);
// ofileName.ReplaceAll(idName, "")
// TString odName = "/afs/cern.ch/user/a/agrummer/www/bmumu/valSignOff/BranchNames/";
TString odName = "/afs/cern.ch/user/a/agrummer/www/bmumu/valSignOff/";
ofileName = odName + ofileName;

ofstream myTextfile;
myTextfile.open (ofileName + "_T_mv.txt");
// myfile << "a  b\n";
for(int i = 0; i < mycopy->GetEntries(); ++i) { 
    myTextfile << mycopy->At(i)->GetName() << " "<< mycopy->At(i)->GetTitle() << '\n'; 
}

myTextfile.close();

ofstream myTextfileEV;
myTextfileEV.open (ofileName + "_EventInfo.txt");
// myfile << "a  b\n";
for(int i = 0; i < mycopyEV->GetEntries(); ++i) { 
    myTextfileEV << mycopyEV->At(i)->GetName() << " "<< mycopyEV->At(i)->GetTitle() << '\n'; 
}

myTextfileEV.close();
// return 0;
}

int main(int argc, char* argv[])
{
  TString idName, ifName;
  if (argc>1) idName = TString(argv[1]);
  if (argc>2) ifName = TString(argv[2]);
  BranchNamesMacro(idName, ifName);
  return 0;
}

