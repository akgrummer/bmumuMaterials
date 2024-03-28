#include "mvaInterface.h"

#if !defined(__CINT__)
ClassImp(mvaInterface);
#endif

mvaInterface::mvaInterface()
{
  SIG_inputFileName="";
  BKG_inputFileName="";
  SIGtrain_inputFileName="";
  BKGtrain_inputFileName="";
  SIGtest_inputFileName="";
  BKGtest_inputFileName="";
  SIG_treeName="";
  BKG_treeName="";
  valSIG_inputFileName="";
  valBKG_inputFileName="";
  valSIG_treeName="";
  valBKG_treeName="";
  WORK_DIR="";
  OUT_DIR="";
  OUT_FILE="";
  factoryName = "";
  factory_options              = "";
  factory_prepareTrainingOpt   = "";
  GradBDToptions              = "";
  AdaBDToptions              = "";
  MLPoptions              = "";
  SVMoptions              = "";
  MyCutSignal = "";
  MyCutBkgnd ="";
  MyCut ="";
  SIGweightexp  = "";
  BKGweightexp  ="";
  varVec.clear();
  varVecTitle.clear();
  varVecUnits.clear();
  varVecType.clear();
  spectVec.clear();
  spectVecTitle.clear();
  spectVecUnits.clear();
  spectVecType.clear();
}

void mvaInterface::reset()
{
  varVec.clear();
  varVecTitle.clear();
  varVecUnits.clear();
  varVecType.clear();
  spectVec.clear();
  spectVecTitle.clear();
  spectVecUnits.clear();
  spectVecType.clear();
}

void mvaInterface::runMVAtraining() {
  TFile* SIG_file(NULL); if (!SIG_inputFileName.EqualTo(""))  SIG_file = new TFile(SIG_inputFileName);
  TFile* BKG_file(NULL); if (!BKG_inputFileName.EqualTo(""))  BKG_file = new TFile(BKG_inputFileName);

  TFile* SIGtrain_file(NULL); if (!SIGtrain_inputFileName.EqualTo(""))  SIGtrain_file = new TFile(SIGtrain_inputFileName);
  TFile* BKGtrain_file(NULL); if (!BKGtrain_inputFileName.EqualTo(""))  BKGtrain_file = new TFile(BKGtrain_inputFileName);
  TFile* SIGtest_file(NULL); if (!SIGtest_inputFileName.EqualTo(""))  SIGtest_file = new TFile(SIGtest_inputFileName);
  TFile* BKGtest_file(NULL); if (!BKGtest_inputFileName.EqualTo(""))  BKGtest_file = new TFile(BKGtest_inputFileName);
cout<< "SIGtrain_inputFileName: "<< SIGtrain_inputFileName <<endl;


  TFile* valSIG_file(NULL); if (!valSIG_inputFileName.EqualTo("")) valSIG_file = new TFile(valSIG_inputFileName);
  TFile* valBKG_file(NULL); if (!valBKG_inputFileName.EqualTo("")) valBKG_file = new TFile(valBKG_inputFileName);

  cout << "Retrieving tree branches ... " << endl;
  TTree* SIG_tree(NULL); if (!SIG_treeName.EqualTo("") && SIG_file!=NULL) SIG_tree = (TTree*)SIG_file->Get(SIG_treeName);
  TTree* BKG_tree(NULL); if (!BKG_treeName.EqualTo("") && BKG_file!=NULL) BKG_tree = (TTree*)BKG_file->Get(BKG_treeName);

  TTree* SIGtrain_tree(NULL); if (!SIG_treeName.EqualTo("")) SIGtrain_tree = (TTree*)SIGtrain_file->Get(SIG_treeName);
  TTree* BKGtrain_tree(NULL); if (!BKG_treeName.EqualTo("")) BKGtrain_tree = (TTree*)BKGtrain_file->Get(BKG_treeName);
  TTree* SIGtest_tree(NULL); if (!SIG_treeName.EqualTo("")) SIGtest_tree = (TTree*)SIGtest_file->Get(SIG_treeName);
  TTree* BKGtest_tree(NULL); if (!BKG_treeName.EqualTo("")) BKGtest_tree = (TTree*)BKGtest_file->Get(BKG_treeName);

  TTree* valSIG_tree(NULL); if (!valSIG_treeName.EqualTo("") && valSIG_file!=NULL) valSIG_tree = (TTree*)valSIG_file->Get(valSIG_treeName);
  TTree* valBKG_tree(NULL); if (!valBKG_treeName.EqualTo("") && valBKG_file!=NULL) valBKG_tree = (TTree*)valBKG_file->Get(valBKG_treeName);
  
  //create factory
  cout << " * Initialise TMVA..." << endl;
  // create factory

  TFile* outputFile = TFile::Open(WORK_DIR+"/"+OUT_DIR+"/"+OUT_FILE, "RECREATE" );

  
  TMVA::Factory* factory = new TMVA::Factory(factoryName, outputFile, factory_options);


  TMVA::DataLoader *dataloader=new TMVA::DataLoader(OUT_DIR.Data());

  //dataloader->GetDataSetInfo().AddClass("Background"); // adds class 0
  //dataloader->GetDataSetInfo().AddClass("Signal"); // adds class 1

  (TMVA::gConfig().GetIONames()).fWeightFileDir = "weights";
  // (TMVA::gConfig().GetIONames()).fWeightFileDir = WORK_DIR+"/"+OUT_DIR+"/"+"weights";
  (TMVA::gConfig().GetVariablePlotting()).fMaxNumOfAllowedVariablesForScatterPlots = 25;

  //add variables
  for (unsigned int ii=0;ii<varVec.size();ii++) {
    dataloader->AddVariable(varVec[ii],varVecTitle[ii],varVecUnits[ii],varVecType[ii]);
  }
  //add spectators
  for (unsigned int ii=0;ii<spectVec.size();ii++) {
    dataloader->AddSpectator(spectVec[ii],spectVecTitle[ii],spectVecUnits[ii],spectVecType[ii]);
  }

  //add trees
  if (valSIG_tree!=NULL && valBKG_tree!=NULL) {
    dataloader->AddSignalTree(SIG_tree, 1.0, TMVA::Types::kTraining);
    dataloader->AddBackgroundTree(BKG_tree, 1.0, TMVA::Types::kTraining);
    dataloader->AddSignalTree(valSIG_tree, 1.0, TMVA::Types::kTesting);
    dataloader->AddBackgroundTree(valBKG_tree, 1.0, TMVA::Types::kTesting);
  } else if (SIGtrain_tree!=NULL && BKGtrain_tree!=NULL && SIGtest_tree!=NULL && BKGtest_tree!=NULL){
    dataloader->AddSignalTree(SIGtrain_tree, 1.0, "Training");
    dataloader->AddBackgroundTree(BKGtrain_tree, 1.0, "Training");
    dataloader->AddSignalTree(SIGtest_tree, 1.0,  "Test");
    dataloader->AddBackgroundTree(BKGtest_tree, 1.0,  "Test");
  } else if (SIG_tree!=NULL && BKG_tree!=NULL){
    dataloader->AddSignalTree(SIG_tree, 1.0);
    dataloader->AddBackgroundTree(BKG_tree, 1.0);
  } else{
    cout<<"Error in mvaInterface.cxx: trees are empty"<<endl;
    return 0;
  }

  //add weights
  if (!SIGweightexp.EqualTo("")) dataloader->SetSignalWeightExpression(SIGweightexp);
  if (!BKGweightexp.EqualTo("")) dataloader->SetBackgroundWeightExpression(BKGweightexp);
  
 
  // prepare and test tree
  cout << " * Prepare Training and Test Tree..." << endl;
  // if (SIG_file!=NULL) 
    dataloader->PrepareTrainingAndTestTree(MyCutSignal,MyCutBkgnd,factory_prepareTrainingOpt);
  // else if (SIGtrain_tree!=NULL && BKGtrain_tree!=NULL && SIGtest_tree!=NULL && BKGtest_tree!=NULL){
  //   dataloader->PrepareTrainingAndTestTree(MyCut,SIGtrain_tree,BKGtrain_tree,SIGtest_tree,BKGtest_tree);
  // }

  //book methods
  if (!AdaBDToptions.EqualTo("")) {
    cout << " * Book AdaBDT Training Method..." << endl;
    factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDT", AdaBDToptions);
  }

  if (!GradBDToptions.EqualTo("")) {
    cout << " * Book GradBDT Training Method..." << endl;
    factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDT", GradBDToptions);
  } 
  
  if (!MLPoptions.EqualTo("")) {
    cout << " * Book MLP Training Method..." << endl;
    factory->BookMethod( dataloader, TMVA::Types::kMLP, "MLP", MLPoptions);
  } 

  if (!SVMoptions.EqualTo("")) {
    cout << " * Book SVM Training Method..." << endl;
    factory->BookMethod( dataloader, TMVA::Types::kSVM, "SVM", SVMoptions);
  }
  
  if (GradBDToptions.EqualTo("") && AdaBDToptions.EqualTo("") && MLPoptions.EqualTo("") && SVMoptions.EqualTo("")){
    cout << " * Neither BDT nor MLP nor SVM Training Method defined, only correlations of the input variables will be provided..." << endl;
  } 
  // ---- optimize the setting (configuration) of the MVAs using the set of training events
  // ==== EXPERIMENTAL !!!!
  // 
  //factory->OptimizeAllMethods("ROCIntegral","Scan");

  // ---- Train MVAs using the set of training events
  factory->TrainAllMethodsForClassification();
  
  // ---- Evaluate all MVAs using the set of test events
  factory->TestAllMethods();    
 
  // ----- Evaluate and compare performance of all configured MVAs
  // if (!(factory_prepareTrainingOpt.Contains("nTest_Signal=1") || factory_prepareTrainingOpt.Contains("nTest_Background=1")))
  factory->EvaluateAllMethods();    
   
  //close file  
  outputFile->Close();
  
  // Clean up
  delete factory;
  delete dataloader;
}

