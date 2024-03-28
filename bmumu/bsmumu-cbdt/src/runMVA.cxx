#include "mvaInterface.h" 
#include <variables.h>

int main(int argc, char* argv[])
{
  TString cfgfilename;
  // cfgfilename="/data/ibragimov/cfgs/bdt.cfg";
  cfgfilename="/afs/cern.ch/user/a/agrummer/www/bmumu/bsmumu-cbdt/cfg/bdt2012final.cfg";
  if (argc >= 2) cfgfilename = argv[1];
  TString dynpars;
  if (argc >= 3) dynpars = argv[2];
  TString num;
  if (argc >= 4) num = argv[3];
  TString prepopt;
  if (argc >= 5) prepopt = argv[4];
  TString addbkgcut;
  if (argc == 6) addbkgcut = argv[5];
  
  mvaInterface mymva;
  vector<string> varVec;	                   vector<char> varVecType;
  vector<string> varVecTitle;
  vector<string> varVecUnits;
  vector<string> spectVec;	                   vector<char> spectVecType;
  vector<string> spectVecTitle;
  vector<string> spectVecUnits;

  vector<string> varAliases;
  vector<string> spectAliases;

  fstream fcfg;
  char carray[256];
  fcfg.open(cfgfilename, ios::in);
  if (fcfg.is_open()) cout << "Opening the cfg file "<< cfgfilename << endl;
  else {
    cout << "could not open the cfg file, exiting... "<< cfgfilename << endl;
    exit(0);
  }
 
  while (!fcfg.eof()) {
    fcfg.getline(carray, sizeof(carray));
    stringstream line;
    string pos1;
    string pos2;
    line << carray;
    line >> pos1;
    line >> pos2;
    if ( pos1 == "sigDataset" )             mymva.SIG_inputFileName = pos2;
    if ( pos1 == "bkgDataset" )             mymva.BKG_inputFileName = pos2;
    if ( pos1 == "sigTreename")             mymva.SIG_treeName = pos2;
    if ( pos1 == "bkgTreename")             mymva.BKG_treeName = pos2;
    if ( pos1 == "sigValDataset" )          mymva.valSIG_inputFileName = pos2;
    if ( pos1 == "bkgValDataset" )          mymva.valBKG_inputFileName = pos2;
    if ( pos1 == "sigValTreename")          mymva.valSIG_treeName = pos2;
    if ( pos1 == "bkgValTreename")          mymva.valBKG_treeName = pos2;
    if ( pos1 == "workdir" )                mymva.WORK_DIR = pos2;
    if ( pos1 == "outdir" )                 mymva.OUT_DIR = pos2;
    if ( pos1 == "factoryname")             mymva.factoryName = pos2;
    if ( pos1 == "prepareTrainingOpt")      mymva.factory_prepareTrainingOpt = pos2;
    if ( pos1 == "sigWeightExp")            mymva.SIGweightexp = pos2;
    if ( pos1 == "bkgWeightExp")            mymva.BKGweightexp = pos2;
    if ( pos1 == "gradBdtOptions")          mymva.GradBDToptions = pos2;
    if ( pos1 == "adaBdtOptions")           mymva.AdaBDToptions = pos2;
    if ( pos1 == "mlpOptions")              mymva.MLPoptions = pos2;
    if ( pos1 == "svmOptions")              mymva.SVMoptions = pos2;
    if ( pos1 == "sigCut")                  mymva.MyCutSignal = (TString)pos2;
    if ( pos1 == "bkgCut")                  mymva.MyCutBkgnd = (TString)pos2;
    if ( pos1 == "includeVarList")          {
      stringstream invarlist((string)pos2);
      string token;
      while (getline(invarlist, token, ',')) {
	varAliases.push_back(token);
	cout << "INFO: including variable: " << token << endl;
      }
    }
    if ( pos1 == "includeSpectList")          {
      stringstream inspectlist((string)pos2);
      string token;
      while (getline(inspectlist, token, ',')) {
	spectAliases.push_back(token);
	cout << "INFO: including spectator: " << token << endl;
      }
    }
  }
  fcfg.close();
  
  for (unsigned int ii=0;ii<varAliases.size();ii++) {
    for (int ivar=0;ivar<nVar;ivar++) {
      if (varAliases[ii].compare(Variables[ivar].alias)) continue;
      cout << "INFO adding input variable: " << Variables[ivar].name << " "<< Variables[ivar].axName << " "<< Variables[ivar].units<< " "<< Variables[ivar].type << endl; 
      varVec.push_back(Variables[ivar].name);varVecTitle.push_back(Variables[ivar].axName);varVecUnits.push_back(Variables[ivar].units);varVecType.push_back(Variables[ivar].type);
    }
  }

  for (unsigned int ii=0;ii<spectAliases.size();ii++) {
    for (int ivar=0;ivar<nVar;ivar++) {
      if (spectAliases[ii].compare(Variables[ivar].alias)) continue;
      cout << "INFO adding spectator variable: " << Variables[ivar].name << " "<< Variables[ivar].axName << " "<< Variables[ivar].units<< " "<< Variables[ivar].type << endl; 
      spectVec.push_back(Variables[ivar].name);spectVecTitle.push_back(Variables[ivar].axName);spectVecUnits.push_back(Variables[ivar].units);spectVecType.push_back(Variables[ivar].type);
    }
  }

  
  if (argc >= 3 && !dynpars.EqualTo("")) {
    mymva.AdaBDToptions.Append(dynpars);
    cout<<"Debug: "<< "AdaBDToptions  " << dynpars<<endl;
  }
  
  if (argc >= 4) {
    mymva.factoryName.Append("_");
    mymva.factoryName.Append(num);
    cout<<"Debug: "<< "factoryName  " << num <<endl;
  }
  
  if (argc >= 5 && !prepopt.EqualTo("")) mymva.factory_prepareTrainingOpt.Append(prepopt);

  if (argc == 6 && !addbkgcut.EqualTo("")) {
    mymva.MyCutBkgnd+=addbkgcut;
  }
  
  mymva.OUT_FILE=mymva.factoryName;
  mymva.OUT_FILE.Append(".root");
  
  cout << endl;
  cout << "SET FOLLOWING MVA TRAINING OPTIONS:  "<<endl;
  cout << "mymva.SIG_inputFileName: "<< mymva.SIG_inputFileName << endl;
  cout << "mymva.BKG_inputFileName: "<< mymva.BKG_inputFileName<<endl;
  cout << "mymva.SIG_treeName: "<< mymva.SIG_treeName<<endl;
  cout << "mymva.BKG_treeName: "<< mymva.BKG_treeName<<endl;
  cout << "mymva.valSIG_inputFileName: "<< mymva.valSIG_inputFileName << endl;
  cout << "mymva.valBKG_inputFileName: "<< mymva.valBKG_inputFileName<<endl;
  cout << "mymva.valSIG_treeName: "<< mymva.valSIG_treeName<<endl;
  cout << "mymva.valBKG_treeName: "<< mymva.valBKG_treeName<<endl;
  cout << "mymva.OUT_DIR: "<< mymva.OUT_DIR<<endl;
  cout << "mymva.OUT_FILE: "<< mymva.OUT_FILE<<endl;
  cout << "mymva.factoryName: "<< mymva.factoryName<<endl;
  cout << "mymva.factory_prepareTrainingOpt: "<< mymva.factory_prepareTrainingOpt<<endl;
  cout << "mymva.SIGweightexp: "<< mymva.SIGweightexp<<endl;
  cout << "mymva.BKGweightexp: "<< mymva.BKGweightexp<<endl;
  cout << "mymva.GradBDToptions: "<< mymva.GradBDToptions<<endl;
  cout << "mymva.AdaBDToptions: "<< mymva.AdaBDToptions<<endl;
  cout << "mymva.MLPoptions: "<< mymva.MLPoptions<<endl;
  cout << "mymva.SVMoptions: "<< mymva.SVMoptions<<endl;
  cout << "mymva.MyCutSignal: "<< mymva.MyCutSignal<<endl;
  cout << "mymva.MyCutBkgnd: "<< mymva.MyCutBkgnd<<endl;
  cout << endl;

  //use all remaining events in the trees after training for testing:
  mymva.factory_options = "Color:DrawProgressBar";

  //in MVA options H - Print method-specific help message, V - verbose output

  mymva.varVec          =  varVec;
  mymva.varVecTitle      =  varVecTitle;
  mymva.varVecUnits      =  varVecUnits;
  mymva.varVecType      =  varVecType;
  mymva.spectVec          =  spectVec;
  mymva.spectVecTitle      =  spectVecTitle;
  mymva.spectVecUnits      =  spectVecUnits;
  mymva.spectVecType      =  spectVecType;
  mymva.runMVAtraining();

  return 0;
}

