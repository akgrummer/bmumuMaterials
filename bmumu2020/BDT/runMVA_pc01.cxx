// #include "mvaInterface.h" 
// #include "variables.h"
#include "variables_2020Mar20.h"
#include "mvaInterface.cxx"
#include "TStopwatch.h"

int runMVA_pc01(TString outdir= "", TString dynpars = "")
// int runMVA_pc01(TString dynpars = "")
// int runMVA(int argc, char** argv)
{
  TStopwatch sw;
  sw.Start();
  // cout<<"Debug: "<< argv[0] <<endl;
  // cout<<"Debug: "<< argv[1] <<endl;
  // cout<<"Debug: "<< argv[2] <<endl;
  int argc = 0;
  // TString outdir= "";
  // TString dynpars = "";
  TString cfgfilename;
  // cfgfilename="/data/ibragimov/cfgs/bdt.cfg";
  // cfgfilename="/afs/cern.ch/user/a/agrummer/www/bmumu/bsmumu-cbdt/cfg/bdt2012final.cfg";
  // cfgfilename="./bdt2012final_pc01.cfg";
  // cfgfilename="./bdt2016_sideband.cfg";
  // cfgfilename="./bdt2016_corrMatrix.cfg";
  // cfgfilename="./2019May29_IsoStudy.cfg";
  // cfgfilename="./2020Mar20_IsoStudy.cfg";
  cfgfilename="./2020Apr7_IsoStudy.cfg";
  // TString dynpars = "";
  Int_t num = 0;
  TString prepopt = "";
  TString addbkgcut = "";
  // return(0);

  // if (argc >= 2) cfgfilename = argv[1];
  // TString dynpars;
  // if (argc >= 3) dynpars = argv[2];
  // TString num;
  // if (argc >= 4) num = argv[3];
  // TString prepopt;
  // if (argc >= 5) prepopt = argv[4];
  // TString addbkgcut;
  // if (argc == 6) addbkgcut = argv[5];
  
  mvaInterface mymva;
  vector<string> varVec;	                   vector<char> varVecType;
  vector<string> varVecTitle;
  vector<string> varVecUnits;
  vector<string> spectVec;	                   vector<char> spectVecType;
  vector<string> spectVecTitle;
  vector<string> spectVecUnits;

  vector<string> varAliases;
  vector<string> spectAliases;

  if (!outdir.EqualTo("")) {
    mymva.OUT_DIR = outdir;

  }

  string ODcnf = "outdir";
  string sigData = "sigDataset";
  string bkgData = "bkgDataset";

  string sigDataTRAIN = "sigDatasetTRAIN";
  string bkgDataTRAIN = "bkgDatasetTRAIN";
  string sigDataTEST = "sigDatasetTEST";
  string bkgDataTEST = "bkgDatasetTEST";
  cout << "look at outdir: "<< outdir << endl;
  // if (outdir.Contains("2016")){
  //       sigData = "sigDatasetMC16a";
  //       bkgData = "bkgDataset2016";
  // }else if (outdir.Contains("2018_MC16a")){
  //       sigData = "sigDatasetMC16a";
  //       bkgData = "bkgDataset2018";
  // }else if (outdir.Contains("2017")){
  //       sigData = "sigDatasetMC16d";
  //       bkgData = "bkgDataset2017";
  // }else if (outdir.Contains("2018")){
  //       sigData = "sigDatasetMC16e";
  //       bkgData = "bkgDataset2018";
  // }
  string VarListcnf = "includeVarList";
  if (outdir.Contains("DOCA")){
    VarListcnf = "includeVarListDOCA";
  }else if (outdir.Contains("nCloseTracks")){
    VarListcnf = "includeVarListnCloseTracks";
  }else if (outdir.Contains("BIso")){
    VarListcnf = "includeVarListBIso";
  }else if (outdir.Contains("muM")){
    VarListcnf = "includeVarListmuM";
  }else if (outdir.Contains("muP")){
    VarListcnf = "includeVarListmuP";
  }else if (outdir.Contains("SomeVars")){
    VarListcnf = "includeVarList";
  }else if (outdir.Contains("Nom")){
    VarListcnf = "includeVarListNom";
  }else if (outdir.Contains("Run1")){
    VarListcnf = "includeVarListRun1";
  }else if (outdir.Contains("Custom")){
    VarListcnf = "includeVarListCustom";
  }else if (outdir.Contains("Loose")){
    VarListcnf = "includeVarListLoose";
  }

  if (outdir.Contains("Run1Custom")){
    VarListcnf = "includeVarListRun1Custom";
  }else if (outdir.Contains("BestSep")){
    VarListcnf = "includeVarListBestSep";
  }

  if (outdir.Contains("Run1nPV")){
    VarListcnf = "includeVarListRun1nPV";
  }else if (outdir.Contains("Run1privxmu")){
    VarListcnf = "includeVarListRun1privxmu";
  }
  if (outdir.Contains("Run1_npvweights")){
    VarListcnf = "includeVarListRun1nPVweights";
  } 
  if (outdir.Contains("ALLvars")){
    VarListcnf = "includeVarListALLvars";
  }

  if (outdir.Contains("Custom_privxmu")){
    VarListcnf = "includeVarListCustomprivxmu";
  }
  if (outdir.Contains("Custom_nPV")){
    VarListcnf = "includeVarListCustomnPV";
  } 

    if (outdir.Contains("Set1")){
        sigDataTRAIN = "sigDataset1";
        bkgDataTRAIN = "bkgDataset1";
        sigDataTEST = "sigDataset2";
        bkgDataTEST = "bkgDataset2";
    }
    else if (outdir.Contains("Set2")){
        sigDataTRAIN = "sigDataset2";
        bkgDataTRAIN = "bkgDataset2";
        sigDataTEST = "sigDataset3";
        bkgDataTEST = "bkgDataset3";
    }
    else if (outdir.Contains("Set3")){
        sigDataTRAIN = "sigDataset3";
        bkgDataTRAIN = "bkgDataset3";
        sigDataTEST = "sigDataset1";
        bkgDataTEST = "bkgDataset1";
    }
    else if (outdir.Contains("Old")){
        sigData = "sigDatasetOld";
        bkgData = "bkgDatasetOld";
    }

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
    if ( pos1 == sigData )             mymva.SIG_inputFileName = pos2;
    if ( pos1 == bkgData )             mymva.BKG_inputFileName = pos2;
    if ( pos1 == "sigTreename")             mymva.SIG_treeName = pos2;
    if ( pos1 == "bkgTreename")             mymva.BKG_treeName = pos2;
    if ( pos1 == sigDataTRAIN )             mymva.SIGtrain_inputFileName = pos2;
    if ( pos1 == bkgDataTRAIN )             mymva.BKGtrain_inputFileName = pos2;
    if ( pos1 == sigDataTEST )             mymva.SIGtest_inputFileName = pos2;
    if ( pos1 == bkgDataTEST )             mymva.BKGtest_inputFileName = pos2;
    if ( pos1 == "sigValDataset" )          mymva.valSIG_inputFileName = pos2;
    if ( pos1 == "bkgValDataset" )          mymva.valBKG_inputFileName = pos2;
    if ( pos1 == "sigValTreename")          mymva.valSIG_treeName = pos2;
    if ( pos1 == "bkgValTreename")          mymva.valBKG_treeName = pos2;
    if ( pos1 == "workdir" )                mymva.WORK_DIR = pos2;
    if ( pos1 == ODcnf    )                 mymva.OUT_DIR = pos2;
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
    if ( pos1 == "myCut")                   mymva.MyCut = (TString)pos2;
    if ( pos1 == VarListcnf)          {
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

//used for output folder with the parameter names
  // // if (argc >= 3 && !dynpars.EqualTo("")) {
  // //   mymva.AdaBDToptions.Append(dynpars);
  // // }
  // // if (!dynpars.EqualTo("")) {
  // TString dynparsDummy(dynpars);
  // if( dynparsDummy.Contains("=")) dynparsDummy.ReplaceAll("=","");
  // if( dynparsDummy.Contains(":")) dynparsDummy.ReplaceAll(":","_");
  // mymva.OUT_DIR.Append(dynparsDummy);
  // // }

// Uncomment to input from command line!!!!!!!
  if (!dynpars.EqualTo("")) {
    mymva.AdaBDToptions.Append(dynpars);
  }
  
  if (argc >= 4) {
    mymva.factoryName.Append("_");
    mymva.factoryName.Append(num);
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
  cout << "mymva.SIGtrain_inputFileName: "<< mymva.SIGtrain_inputFileName<<endl;
  cout << "mymva.BKGtrain_inputFileName: "<< mymva.BKGtrain_inputFileName<<endl;
  cout << "mymva.SIGtest_inputFileName: "<< mymva.SIGtest_inputFileName<<endl;
  cout << "mymva.BKGtest_inputFileName: "<< mymva.BKGtest_inputFileName<<endl;
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
  sw.Stop();
  sw.Print();
  return 0;
}

