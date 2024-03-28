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


void MergeFiles(){
TString finpath(indir);
  DIR *dpdf;
  struct dirent *entry;
  dpdf = opendir(finpath.Data());
}