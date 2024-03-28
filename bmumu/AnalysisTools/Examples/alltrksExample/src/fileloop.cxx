//
// example how to loop over files in a directory
// author: iskander(dot)ibragimov(at)cern(dot)ch
//
// to run:
// g++ fileloop.cxx -o fileloop `root-config --glibs --cflags`
// ./fileloop


#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include <iostream>
#include <dirent.h>


bool hasEnding(std::string const &fullString, std::string const &ending) {
  if (fullString.length() >= ending.length()) {
    return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
  } else {
    return false;
  }
}

void loopFiles(){

  TString indir("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/skimmed_ntup/data18/Bmumu/");
  TString finpath(indir);
  DIR *dpdf;
  struct dirent *entry;

  dpdf = opendir(finpath.Data());

  if (dpdf != NULL){
    while (entry = readdir(dpdf)){

      printf("Filename: %s\n", entry->d_name);

      if ( !hasEnding(entry->d_name, ".root") )  continue;  // exclude non-ROOT files 
     
      std::cout << "processing file: "<< entry->d_name << std::endl;
    
      TString fintemp(finpath);
      fintemp.Append(entry->d_name);
      TFile *fin = new TFile(fintemp);
      TTree *tin = (TTree*)fin->Get("T_mv");

      std::cout << "# of candidates: "<<  tin->GetEntries() << std::endl;
      /*
      TTree *t1 = (TTree*)fin->Get("Metadata");
      TTree *t2 = (TTree*)fin->Get("EventInfo");
      TTree *t3 = (TTree*)fin->Get("TRUTHDECAY");
      */
      fin->Close();
    }
  }
  closedir(dpdf);

}

int main(int argc, char* argv[])
{
  loopFiles();
  return 0;
}
