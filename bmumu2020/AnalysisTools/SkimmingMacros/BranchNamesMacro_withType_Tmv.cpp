// g++ BranchNamesMacro_withType_Tmv.cpp -o BranchNamesMacro_withType_Tmv `root-config --glibs --cflags`
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
void BranchNamesMacro(TString ifName){
// TFile* myfile = new TFile(idName+"/bsmumu.root","read");
TFile* myfile = new TFile(ifName,"read");
TTree* myTree = (TTree*) myfile->Get("T_mv");
// TTree* myTreeEV = (TTree*) myfile->Get("EventInfo");
TObjArray *mycopy = myTree->GetListOfBranches(); 
// TObjArray *mycopy = myTree->GetListOfBranches()->Clone(); 
mycopy->SetOwner(kFALSE); 
mycopy->Sort();

// TObjArray *mycopyEV = myTreeEV->GetListOfBranches(); 
// mycopyEV->SetOwner(kFALSE); 
// mycopyEV->Sort();

// for(int i = 0; i < array->GetEntries(); ++i) { cout << array->At(i)->GetName() << '\n'; }
TString ofileName("");
ofileName = ifName;
ofileName.Remove(0,ifName.Last('/')+1);
ofileName.ReplaceAll(".root","");
// ofileName.ReplaceAll(ifName, "")
// TString odName = "/afs/cern.ch/user/a/agrummer/www/bmumu/valSignOff/BranchNames/";
// TString odName = "/afs/cern.ch/user/a/agrummer/www/bmumu2020/nTupleBranchNames/v4/";
// TString odName = "/afs/cern.ch/user/a/agrummer/www/bmumu2020/nTupleBranchNames/Run1/";
TString odName = "/afs/cern.ch/user/a/agrummer/www/bmumu2020/nTupleBranchNames/partialRun2/";
ofileName = odName + ofileName;

ofstream myTextfile;
myTextfile.open (ofileName + "_T_mv.txt");
// myfile << "a  b\n";
for(int i = 0; i < mycopy->GetEntries(); ++i) { 
    myTextfile << mycopy->At(i)->GetName() << " "<< mycopy->At(i)->GetTitle() << '\n'; 
}

myTextfile.close();

// ofstream myTextfileEV;
// myTextfileEV.open (ofileName + "_EventInfo.txt");
// // myfile << "a  b\n";
// for(int i = 0; i < mycopyEV->GetEntries(); ++i) { 
//     myTextfileEV << mycopyEV->At(i)->GetName() << " "<< mycopyEV->At(i)->GetTitle() << '\n'; 
// }

// myTextfileEV.close();
// return 0;
}

int main(int argc, char* argv[])
{
  TString ifName;
  if (argc>1) ifName = TString(argv[1]);
  BranchNamesMacro(ifName);
  return 0;
}

