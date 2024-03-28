#ifndef MVAINTERFACE_H
#define MVAINTERFACE_H

#include "iostream"
#include <stdlib.h>
#include "TFile.h"
#include "Riostream.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TH1F.h"
#include <string>
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#include "TMVA/Config.h"
#include "TMVA/DataLoader.h"

#include <algorithm>
#include <sstream>
#include <iterator>

using namespace std;

class mvaInterface
{
	
private:
	
	
public:
  TString BKG_inputFileName;
  TString SIG_inputFileName;

  TString BKG_treeName;
  TString SIG_treeName;  

  TString valBKG_inputFileName;
  TString valSIG_inputFileName;

  TString valBKG_treeName;
  TString valSIG_treeName;  
  
  TString WORK_DIR;
  TString OUT_DIR;
  TString OUT_FILE; 
  
  TString factoryName;
  TString factory_options;
  TString factory_prepareTrainingOpt;

  TCut MyCutSignal;
  TCut MyCutBkgnd;

  TString SIGweightexp;
  TString BKGweightexp;

  TString GradBDToptions;
  TString AdaBDToptions;
  TString MLPoptions;
  TString SVMoptions;

  vector<string> varVec;
  vector<string> varVecTitle;
  vector<string> varVecUnits;
  vector<char> varVecType;
  vector<string> spectVec;
  vector<string> spectVecTitle;
  vector<string> spectVecUnits;
  vector<char> spectVecType;
  
  mvaInterface();
  
  void reset();
  void runMVAtraining();
};

#endif
