// Macro for performing data/MC comparison on B+->Jpsi/K+ channel
// uses unbinned ML fit to estimate number of bkg candidates 
// under the signal peak, as well as for estimation of fraction of
// continuos bkg candidates in the left sideband etc. (N.B. in "dtbgsub_mcrew" mode)
//
// Author: Iskander Ibragimov
// 02.10.2017
//
// in the file dmcbbmumuX.h are defined:
// - input data files for MC and data (single flat ntuples are curently supported)
// - output path for the plots and other output files 
// - cuts values and some special histogram binnings 
// - discriminating variables (name, binning, axislabel)
// 
// 
// 1 . if needed change source files for MC and data in *.h file (defined by the variables fdname and fmname)
// (in principle the code should also work with group ntuples on eos
// but those are not completely flat and missing preliminary and trigger selections
//
// 2. adjust CutAdd variable (in dmcbbmumuX.h) if needed (additional cuts to be applied)
//
// 3. adjust output path for the plots, etc.
//
// 4. to exectute do (after "root -l"):
// .x dmcbbmumuX.C("B_pT","dt_mcXs") //or any other variable name from dmcbbmumuX.h file
// OR
// .x dmcbbmumuX.C("systVars","dtbgsub_mcrew") // to run on all variables used for discrimination
//.x dmcbbmumuX.C("systVars","dtbgsub_mcrew")
// OR (faster, but on some OS stops after the first step - t.b.i)
// .L dmcbbmumuX.C++
// dmcbbmumuX("systVars","dt_mcXs")
//
//Aidan
//ported from dmcbbmumuX_vBkgSig.C
// if you go back to that code, which was used to make the final plots for 15,16 analysis
// be aware that some corrections were (probably) made to start investigating 2017 and 2018

//2019 Jun 19
// This code is renamed to dmcbbmumuX_vBkgSig_IsoStudies.C
 // from dmcbbmumuX_vBkgSig_FullRun2.C
//This is to perform studies on newly created variables
//definitely used this code - not sure about dmcbbmumuX_vBkgSig_FullRun2_IsoComps.C
    // which was created and modified on June 3rd only.... (suspisiously looks unused)

#include "dmcbbmumuX_FullRun2.h"
using namespace std;


ofstream ofiletex(tabname);
TFile *fout = new TFile(ofilename,"RECREATE");

//store bkg fit data
bkg nbkgInfo;

//==========Forward declaration of functions===========

void compare(VariableInfo, TString, vector <TChain*>,vector <TString>, vector <TChain*>,vector <TString>, vector <TChain*>,vector <TString>, TString, TString, bool, bool drawResiduals=false);
TH1F* getHistoFromTree(TTree*, VariableInfo, const char*, TCut);
TLegend* defineLegendBox(TString what, TString mode, Bool_t drawinlet, int NumberOfTreesMC, Bool_t Zoom, Double_t ZoomVal);
TString getYAxisTitle(TString);
void atlasLabel(Double_t,Double_t, bool, bool ,Color_t, bool, bool, bool, TString);


// void dmcbbmumuX(TString compVar="", TString compMode="",const char period[] = "", Bool_t verbose=true)
void dmcbbmumuX_vBkgSig_FullRun2(TString compVar="", TString compMode="", Bool_t verbose=true, TString period = "")
{
//=========== Period Selection and Labeling =================================
 //select period in input, creates treename here (concatinates string using function in header file)
//   if(strcmp(period, "") == 0) { //check if period variable is empty
//     // fdtreename = treename;
//     dtlabel = "Data ALL periods 2016";
//   } else {
// // fdtreename.Append("_");
// // fdtreename.Append(period);
// dtlabel.Append(dtlabelINITIAL);
// // dtlabel.Append(period);
// }
// if (compMode.EqualTo("dt_mc_SepPeriods")) FileNames = {fdnameSP2015M, fdnameSP2016M, fdnameSP2016MWD}; //can take multiple input files
if (compMode.EqualTo("dt_mc_SepPeriods")) FileNames = {fdname}; //can take multiple input files
else if (compMode.EqualTo("dt_mcXs")) FileNames = {fdname}; //takes one file
// else if (compMode.EqualTo("dt_mcXs_Mult")) FileNames = {fdnameMain, fdnameMWD}; //takes multiple files
else if (compMode.EqualTo("dt_mcXs_Mult")) FileNames = {fdname, fdname2, fdname3, fdnameRun1, fdname4}; //takes multiple files
// else if (compMode.EqualTo("mc_mc")) FileNames = {fmname2}; //takes multiple files
// else if (compMode.EqualTo("dt_mc_OnePeriod")) FileNames = {fdnameSP2015M}; //takes only one file

TString mclabel="MC16A";//"MC 16 bb #rightarrow #mu#muX";

  //===========Make connections to tree's of two flat ntuple files=================================

// NumberOfTrees.push_back(0);//let first entry be zero for the loop below which adds the file based of tree index

if (compMode.EqualTo("dt_mc_SepPeriods")){
  for (int FileIdx=0; FileIdx<FileNames.size(); FileIdx++){

    // if (FileNames[FileIdx].Contains("2016") && FileNames[FileIdx].Contains("2015")) DataYear = "";
    // else{
    //     if (FileNames[FileIdx].Contains("2016")) DataYear = " 2016";
    //     else if (FileNames[FileIdx].Contains("2015")) DataYear = " 2015";
    //     else DataYear = "";
    //     if (FileNames[FileIdx].Contains("MainWithDelayed")) DataYear += " MWD";
    //     else if (FileNames[FileIdx].Contains("Main")) DataYear += " Main";
    // }
    ifilename = new TFile(FileNames[FileIdx],"read"); //input skimmed data file
    listofkeys = ifilename->GetListOfKeys(); //get list of keys from input file
    listofkeys->Sort();//sort the list of keys (alphabetical)
    const TObject *AnObj = listofkeys->First();//Get the first Key (for tree name) (TList* listus = ifilename->GetListOfKeys();)
    while(AnObj){//continue until "AnObj" is a null pointer - collects all the trees in the file
      TTree *ATree = (TTree*)ifilename->Get(AnObj->GetName()); //get the tree
      if(ATree->GetEntries()!=0){//ensure the tree is not empty
       treenames.push_back(AnObj->GetName());//add the tree name to vector of strings
       chains.push_back(new TChain(AnObj->GetName()));//add the tree to the vector of chains
      }
      AnObj = listofkeys->After(AnObj);//get the next tree (still in while loop)
    }//end of loop over trees
    NumberOfTrees[FileIdx+1] = treenames.size();
    for (int i=NumberOfTrees[FileIdx] ; i < NumberOfTrees[FileIdx+1]; i++) {
    treenames[i] += DataYear;
    chains[i]->Add(FileNames[FileIdx]);
    // cout<< chains[i]->GetName()<<endl;
    }
}//end of for loop over FileNames (over the input files)
//repeat commands for MC file - which really should have the same tree names as the data file
    ifilename = new TFile(fmname,"read"); //input skimmed data file
    listofkeys = ifilename->GetListOfKeys(); //get list of keys from input file
    listofkeys->Sort();//sort the list of keys (alphabetical)
    const TObject *AnObj = listofkeys->First();//Get the first Key (for tree name) (TList* listus = ifilename->GetListOfKeys();)
    while(AnObj){//continue until "AnObj" is a null pointer - collects all the trees in the file
      TTree *ATree = (TTree*)ifilename->Get(AnObj->GetName()); //get the tree
      if(ATree->GetEntries()!=0){//ensure the tree is not empty
       treenamesMC.push_back(AnObj->GetName());//add the tree name to vector of strings
       chainsMC.push_back(new TChain(AnObj->GetName()));//add the tree to the vector of chains
      }
      AnObj = listofkeys->After(AnObj);//get the next tree (still in while loop)
    }//end of loop over trees
    for (int i=0 ; i < treenamesMC.size(); i++) {
    chainsMC[i]->Add(fmname);
    }

}//end of Seperate Periods if loop
else if (compMode.EqualTo("dt_mcXs") || compMode.EqualTo("dt_mcXs_Mult") || compMode.EqualTo("mc_mc")) { 
  for (int FileIdx=0; FileIdx<FileNames.size(); FileIdx++){
      if (FileNames[FileIdx].Contains("Main_With_Delayed")) DataYear = " MWD";
      else if (FileNames[FileIdx].Contains("Main")) DataYear = " Main";
      else DataYear = "";

    ifilename = new TFile(FileNames[FileIdx],"read");
    treenames.push_back(fdtreename);
    chains.push_back(new TChain(treenames[FileIdx]));
    chains[FileIdx]->Add(FileNames[FileIdx]);
    treenames[FileIdx] += DataYear;//prepare for treenames use in legend
  }
  treenamesMC.push_back(fmtreename);
  chainsMC.push_back(new TChain(fmtreename));
  chainsMC[0]->Add(fmname);

  treenamesSigMC.push_back(fmSigtreename);
  chainsSigMC.push_back(new TChain(fmSigtreename));
  chainsSigMC[0]->Add(fmcSigName);

  treenamesSigMC.push_back(fmSigtreename);
  chainsSigMC.push_back(new TChain(fmSigtreename));
  chainsSigMC[1]->Add(fmcSigName2);

  treenamesSigMC.push_back(fmSigtreename);
  chainsSigMC.push_back(new TChain(fmSigtreename));
  chainsSigMC[2]->Add(fmcSigName3);
}
else if (compMode.EqualTo("dt_mc_OnePeriod")) { 
  if (FileNames[0].Contains("2016") && FileNames[0].Contains("2015")) DataYear = "";
  else{
    if (FileNames[0].Contains("2016")) DataYear = " 2016";
    else if (FileNames[0].Contains("2015")) DataYear = " 2015";
    else DataYear = "";
    if (FileNames[0].Contains("MainWithDelayed")) DataYear += " MWD";
    else if (FileNames[0].Contains("Main")) DataYear += " Main";
  }
  if(strcmp(period, "") == 0) {
    cout<< "Choose a period to compare. Exiting."<<endl;
    return(0);
  }

  ifilename = new TFile(FileNames[0],"read");
  fdtreename.Append("_");
  fdtreename.Append(period);//need to make sure period is in the file that you input
  treenames.push_back(fdtreename);
  chains.push_back(new TChain(treenames[0])); //treenames used to fill chain
  treenames[0] += DataYear; //prepare for treenames use in legend
  chains[0]->Add(FileNames[0]);

  treenamesMC.push_back(fmtreename);
  chainsMC.push_back(new TChain(fmtreename));
  chainsMC[0]->Add(fmname);
}
else {
  cout << "Choose a valid compMode. Exiting. "<< endl;
  return(0);
}
// TChain* td = chains[0];
  // TChain* td = new TChain(fdtreename);//TChain uses the name of the tree (same tree name in every file that is added)
  // td->Add(fdname);//Added one file that includes a tree with name in fdtreename


  // if (verbose) {
  //   if (fdname2015M) cout << "Using: "<< FileNames[0] << "<-dt file names|" << endl;//2015 main
  //   if (fdname2016M) cout << "Using: "<< FileNames[1] << "<-dt file names|" << endl;//2016 main
  //   if (fdname2016MWD) cout << "Using: "<< FileNames[2] << "<-dt file names|" << endl;//2016 main with delayed
  //   if (fdname){ cout << "Using: "<< fdname << "<-dt file name|mc file name->"<<fmname << endl;
  //   cout << "Using: "<< fdtreename << "<-dt file name|mc file name->"<<fmtreename << endl;
  //   }
  //   // cout << "TREE name used in both files: "<< treename<< endl;
  // }
  //==========================================================================================
  //===========Define different comparison modes of two files=================================
  vector<TString> Modes;
  Modes.push_back("mc_mc");
  Modes.push_back("dt_mcXs");
  Modes.push_back("dt_mcXs_Mult");
  Modes.push_back("dt_mc_SepPeriods");
  Modes.push_back("dt_mc_OnePeriod");

  //===========Output tex table with KS test results/variable=================================
  ofiletex << "\\documentclass{article}\n";
    ofiletex << "\\usepackage{graphicx}\n";
    ofiletex << "\\usepackage{longtable}\n";
    ofiletex << "\\begin{document}\n";
  
  if (compMode.EqualTo("dt_mc_SepPeriods") || compMode.EqualTo("dt_mc_OnePeriod") || compMode.EqualTo("dt_mcXs_Mult")) { 
    ofiletex << "\\begin{longtable}{c|c|c|c}\n";
    if (compMode.EqualTo("dt_mc_SepPeriods")) ofiletex << "\\caption{\\label{tab:sepVarsandSepPeriods}Data/MC agreement of separation variables per period}\\\\\n";
    else ofiletex << "\\caption{\\label{tab:sepVarsandSepPeriods}Data/MC agreement of separation variables}\\\\\n";
    if (compVar=="systVars"){
      if (compMode.EqualTo("dt_mcXs_Mult")) ofiletex << "Stream & Variable & KS test & Chi2/ndf \\\\\n\\hline\n";
      else ofiletex << "Period & Variable & KS test & Chi2/ndf \\\\\n\\hline\n";
    }else{
      if (compMode.EqualTo("dt_mcXs_Mult")) ofiletex << "Stream & Variable/Vertex type & 3-prong & 2-prong\\\\\n\\hline\n";
      else ofiletex << "Period & Variable/Vertex type & 3-prong & 2-prong\\\\\n\\hline\n";
    }
}else{
  ofiletex << "\\begin{table}[htbp]\n";
  ofiletex << "\\caption{\\label{tab:sepVars}Data/MC agreement of separation variables}\n";
  ofiletex << "\\begin{center}\n";
  if (compVar=="systVars") ofiletex << "\\begin{tabular}{c|c|c}\n";
  else ofiletex << "\\begin{tabular}{c|c|c}\n";
  if (compVar=="systVars") ofiletex << "Variable & KS test & Chi2/ndf \\\\\n\\hline\n";
  else ofiletex << "Variable/Vertex type & 3-prong & 2-prong\\\\\n\\hline\n"; 
  }
  //==========================================================================================

  //===========Loop over variables and modes and do comparison================================= 
  for (int i=0;i<nVar;i++) {
    //cout << nVar << "| "<< i << endl;
    if ((compVar!="" && compVar.CompareTo(Variables[i].name)) && !(Variables[i].usedForSystematics && compVar=="systVars")) continue;
    cout << "INFO Processing variable: " << Variables[i].name<<endl;
    for (unsigned int j=0;j<Modes.size();j++) {
      if (compMode!="" && compMode.CompareTo(Modes[j])) continue;
      cout << "INFO Processing mode: " << Modes[j]<<endl;
      compare(Variables[i], Modes[j], chains, treenames, chainsMC, treenamesMC, chainsSigMC, treenamesSigMC, dtlabel, mclabel, true, true);
    }
  }
  fout->cd();
  fout->Close();
    
  //==========================================================================================
  //===========Finish writing out table ================================= 
  
if (compMode.EqualTo("dt_mc_SepPeriods") || compMode.EqualTo("dt_mc_OnePeriod") || compMode.EqualTo("dt_mcXs_Mult")) {
  ofiletex << "\\end{longtable}\n";
}else
  {
  ofiletex << "\\end{tabular}\n";
  ofiletex << "\\end{center}\n";
  ofiletex << "\\end{table}\n";
  }
ofiletex << "\\end{document}\n";
ofiletex.close();
  //==========================================================================================
}

TH1F* getHistoFromTree(TTree* tree, VariableInfo Variable, const char* hname, TCut cut)
{
  cout << "GetHistoFromTree, getting histo "<< hname << " for variable " << Variable.name << " from tree "<< tree->GetName() << endl;
  //==================================================================================================
  //====create TString defining how the histogram will be retrieved with TTree::Draw method===========
  //================================================================================================== 
  TString tmp = Variable.name;
  TString axlab = Variable.axLabel;
  Int_t NBins = Variable.nbins;
  Float_t XMin = Variable.XMin;
  Float_t XMax = Variable.XMax;
  if (axlab.Contains("[GeV]")) tmp.Append("/1000.0");
  TString tmpDummy(tmp);
  tmp.Append(">>");
  tmp.Append(hname);
  if (NBins>0 && XMin!=XMax) {
    tmp+=("(");
    tmp+=NBins;
    tmp+=",";
    tmp+=XMin;
    tmp+=",";
    tmp+=XMax;
    tmp+=")";
  } else if (NBins == -1) { 
    tmpDummy.Append(">>+");
    tmpDummy.Append(hname);
  } else tmp.Append("(100)"); //restore default (ROOT) binning
  //==================================================================================================
  //====retrieve histo from TTree============
  //==================================================================================================
  TH1F *hret;
  int nselected(0);
  if (NBins == -1) { //variable binning for eta and pt taken from *.h file                                                                  
    if (tmpDummy.Contains("BvtxPt") || tmpDummy.Contains("B_pT") || tmpDummy.Contains("JPsiPt") || tmpDummy.Contains("BTruthPt")|| tmpDummy.Contains("Muon1_pT")|| tmpDummy.Contains("Muon2_pT")) hret = new TH1F(*hdummyPt); 
    // else if (tmpDummy.Contains("eta") || tmpDummy.Contains("Eta")) hret = new TH1F(*hdummyEta);
    else if (tmpDummy.Contains("Iso") || tmpDummy.Contains("_iso_")) hret = new TH1F(*hdummyIso);
    else if (tmpDummy.Contains("Lxy")) hret = new TH1F(*hdummyLxy);
    else if (tmpDummy.Contains("ClassBDT")) hret = new TH1F(*hdummyClassBDT);
    else {
      cout << "Unknown binning, returning zero pointer..." <<endl;
      return NULL;
    }
    hret->SetName(hname);
    hret->Reset();
    hret->Sumw2();
    nselected = tree->Draw(tmpDummy.Data(),cut,"egoff"); 
    cout << "GetHistoFromTree, creating histo:" << tmpDummy << " event survived the cut(s): " << nselected << endl;
  } else {
    nselected = tree->Draw(tmp.Data(),cut,"egoff");
    cout << "GetHistoFromTree, creating histo:" << tmp << " event survived the cut(s): " << nselected << endl;
    hret = (TH1F*)gDirectory->Get(hname);
  }
 
  hret->GetXaxis()->SetTitle(axlab);
  hret->SetTitle(hname);
  cout << "Creating histo, title "<< hname <<", hret integral.."<< hret->Integral(0, Variable.nbins + 1) <<endl; //cut out over- and unerflows
  cout << endl;
  return hret;
} // end of getHistoFromTree function

void compare(VariableInfo Variable, TString mode, vector <TChain*> chains, vector <TString> treenames, vector <TChain*> chainsMC, vector <TString> treenamesMC, vector <TChain*> chainsSigMC, vector <TString> treenamesSigMC, TString dtlabel, TString mclabel, bool normalize, bool drawResiduals)
{
  bool arbitraryUnits = true;
    // int m(1);
  int NumberOfTrees = treenames.size();
  int NumberOfTreesMC = treenamesMC.size();
  int NumberOfTreesSigMC = treenamesSigMC.size();
  cout<<"The number of trees to compare, data: "<<NumberOfTrees<<", MC: "<<NumberOfTreesMC<<", SigMC: "<<NumberOfTreesSigMC<<endl;
  // if (NumberOfTrees == 4 && treenames[0].Contains("2015")&& treenames[3].Contains("2016preTS1")&& treenames[1].Contains("2016TS1toMD1")&& treenames[2].Contains("2016postMD1")){
  //   cout<<"DEBUG I'm inside"<<endl;
  //     swap(treenames[2], treenames[3]);
  //     swap(treenames[1], treenames[2]);
  //     swap(treenamesMC[2], treenamesMC[3]);
  //     swap(treenamesMC[1], treenamesMC[2]);
  //     swap(chains[2], chains[3]);
  //     swap(chains[1], chains[2]);
  //     swap(chainsMC[2], chainsMC[3]);
  //     swap(chainsMC[1], chainsMC[2]);
  // }


    TH1F** histogram = new TH1F*[NumberOfTrees];//vector of histograms size of number of trees
    TH1F** h2 = new TH1F*[NumberOfTreesMC];//initialize MC historgram
    TH1F** h3 = new TH1F*[NumberOfTreesSigMC];//initialize MC historgram
  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");

// string input = "";
//  gPad->Modified(); gPad->Update();
//  // How to get a string/sentence with spaces
// cout << "Please enter a valid sentence (with spaces):\n>";
//  getline(cin, input);
//  cout << "You entered: " << input << endl << endl;

  if (c1) c1->Clear();
  else c1 = new TCanvas("c1","c1",0,45,800,600);
  c1->SetLogy(0);
  c1->SetLeftMargin(0.13);
  c1->SetRightMargin(0.10); //0.07
  c1->SetTopMargin(0.07);
  c1->SetBottomMargin(0.12);
  
  TString h1title = Variable.name;
  if (h1title.Contains("TMath::Abs")) h1title.ReplaceAll("TMath::Abs","fabs");
  if (h1title.Contains("TMath::")) h1title.ReplaceAll("TMath::","");
  if (h1title.Contains('(')) h1title.ReplaceAll('(','_');
  if (h1title.Contains(')')) h1title.ReplaceAll(')','_');
  if (h1title.Contains('/')) h1title.ReplaceAll('/','_');
  if (h1title.Contains(" +")) h1title.ReplaceAll(" +","plus");
  if (h1title.Contains("+")) h1title.ReplaceAll("+","plus");
  if (h1title.Contains(", ")) h1title.ReplaceAll(", ","_");
  if (h1title.Contains(",")) h1title.ReplaceAll(",","_");
  if (h1title.Contains(" pow")) h1title.ReplaceAll(" pow","pow");
  TString h1titledummy = h1title;

  TString h2title(h1title);
  TString htitle(h1title);
  TString hdivtitle(h1title);

  TString axLab = Variable.axLabel;
  TString yAxisTitle = getYAxisTitle(Variable.name);

  TString h3title(h1title);
VariableInfo Run1npv = {"Npv-1",40,-0.5,39.5,false,"nPV",true, "zoom", false, 0., false, 0.5, 3.};
VariableInfo Run1iso = {"B_iso_7_Chi2_5_MedPt05",51,0.0,1.02,true,"I_{0.7}",false, "zoom", false, 0., false, 0., 3.5};
VariableInfo Run1isoNTrks = {"B_iso_Ntracks_7_Chi2_5_MedPt05",16,0,16,true,"Ntracks B Isolation (I^{B}_{0.7, loose, pt>0.5})",false, "zoom", false, 0., false, 0.75, 1.25};
VariableInfo isoAlltracks = {"B_iso_7_Chi2_5_LoosePt05_AllTrks",51,0.0,1.02,true,"I_{0.7}",false, "zoom", false, 0., false, 0., 3.5};
VariableInfo isoNtrksAlltrks = {"B_iso_Ntracks_7_Chi2_5_LoosePt05_AllTrks",16,0,16,true,"Ntracks B Isolation (I^{B}_{0.7, loose, pt>0.5})",false, "zoom", false, 0., false, 0.75, 1.25};
VariableInfo closeTrkNtrks_AllTrks = {"closeTrkNtrksChi2_AllTrks",60,0,60,true,"N^{clos}_{trk, loose, pt>0.5}",true, "zoom", false, 0., false, 0., 3.5};//added with new MC HLT_mu6_mu4_bBmumu_Lxy0
VariableInfo closeTrkDOCA_AllTrks2 = {"closeTrkDOCA_AllTrks2",40,0,2,true,"DOCA_{xtrk, loose, pt>0.5} [mm]",true, "zoom", false, 0., false, 0.5, 1.5};
// VariableInfo isoAlltracks = {"B_iso_7_Chi2_5_LoosePt05_Aidan",51,0.0,1.02,true,"I_{0.7}",false, "zoom", false, 0., false, 0., 3.5};
// VariableInfo isoNtrksAlltrks = {"B_iso_Ntracks_7_Chi2_5_LoosePt05_Aidan",16,0,16,true,"Ntracks B Isolation (I^{B}_{0.7, loose, pt>0.5})",false, "zoom", false, 0., false, 0.75, 1.25};
// VariableInfo closeTrkNtrks_AllTrks = {"closeTrkNtrksChi2_Aidan",60,0,60,true,"N^{clos}_{trk, loose, pt>0.5}",true, "zoom", false, 0., false, 0., 3.5};//added with new MC HLT_mu6_mu4_bBmumu_Lxy0
// VariableInfo closeTrkDOCA_AllTrks2 = {"closeTrkDOCA_Aidan",40,0,2,true,"DOCA_{xtrk, loose, pt>0.5} [mm]",true, "zoom", false, 0., false, 0.5, 1.5};
if (mode.EqualTo("mc_mc")) {
    // h1title+="_mc12";
    // for (int i=0;i<NumberOfTrees;i++) {
    // histogram[i] = getHistoFromTree(chains[i], Variable, h1title, CutBase && CutLSBLow && CutRSBHigh && "CombWeights*PVWeights*CatN1Weights*CatN2Weights*CatN3Weights*isSignal");
    // }
    // h2title+="_mc15";
    // h2 = getHistoFromTree(tm, Variable, h2title, CutBase && CutLSBLow && CutRSBHigh && "(nphotons==0)*CombWeights*PVWeights*CatN1Weights*CatN2Weights*CatN3Weights*isSignal");
    // h1title+="_mc12";
    // for (int i=0;i<NumberOfTrees;i++) {
    // histogram[i] = getHistoFromTree(chains[i], Variable, h1title, CutBase && CutLSBLow && CutRSBHigh && "PVWeights");
    // }
    // h2title+="_mc15";
    // h2 = getHistoFromTree(tm, Variable, h2title, CutBase && CutLSBLow && CutRSBHigh && "PVWeights");
    h1title+="_mc16_2016Trigger";
    for (int i=0;i<NumberOfTrees;i++) {
    h1title+="_";
    h1title+=treenames[i];
    if(i==3){
    histogram[i] = getHistoFromTree(chains[i], Variable, h1title, CutRun1);
    }
    else if(h1title.Contains("Muon1")){
    histogram[i] = getHistoFromTree(chains[i], Variable, h1title, CutAdd*"PVWeights*Muon1_reco_eff_sf");
    }else if (h1title.Contains("Muon2")){
    histogram[i] = getHistoFromTree(chains[i], Variable, h1title, CutAdd*"PVWeights*Muon2_reco_eff_sf");
    }else if (h1title.Contains("B")){
    histogram[i] = getHistoFromTree(chains[i], Variable, h1title, CutAdd*"PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf");
    }else{
    // h2 = getHistoFromTree(tm, Variable, h2title, CutAdd*"testweight");//added with addWeight.C code
    // h2 = getHistoFromTree(tm, Variable, h2title, CutAdd*"PVWeights");
    histogram[i] = getHistoFromTree(chains[i], Variable, h1title, CutAdd*"PVWeights");
    }
    h1title = h1titledummy;
    h1title+="";
    }//End of number of trees for loop 
    h2title+="_bkgMC";
    if(h2title.Contains("Muon1")){
    h2[0] = getHistoFromTree(chainsMC[0], Variable, h2title, CutAdd*"PVWeights*Muon1_reco_eff_sf");
    }else if (h2title.Contains("Muon2")){
    h2[0] = getHistoFromTree(chainsMC[0], Variable, h2title, CutAdd*"PVWeights*Muon2_reco_eff_sf");
    }else if (h2title.Contains("B")){
    h2[0] = getHistoFromTree(chainsMC[0], Variable, h2title, CutAdd*"PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf");
    }else{
    // h2 = getHistoFromTree(tm, Variable, h2title, CutAdd*"testweight");//added with addWeight.C code
    h2[0] = getHistoFromTree(chainsMC[0], Variable, h2title, CutAdd*"PVWeights");
    }
  }//end of mc_mc mode
   else if (mode.EqualTo("dt_mcXs") ||mode.EqualTo("dt_mcXs_Mult") || mode.EqualTo("dt_mc_SepPeriods") || mode.EqualTo("dt_mc_OnePeriod")) {
    h1title+="Data";
    for (int i=0;i<NumberOfTrees;i++) {
    h1title+="_";
    h1title+=treenames[i];
    h1title+="_";
    h1title+=to_string(i);
    if (i == 3) {
        if (TString(Variable.name).EqualTo("Npv")){
            histogram[i] = getHistoFromTree(chains[i], Run1npv, h1title, CutRun1);
        }else if (TString(Variable.name).EqualTo("B_iso_7_Chi2_5_LoosePt05")){
            histogram[i] = getHistoFromTree(chains[i], Run1iso, h1title, CutRun1);
        }else if (TString(Variable.name).EqualTo("B_iso_Ntracks_7_Chi2_5_LoosePt05")){
            histogram[i] = getHistoFromTree(chains[i], Run1isoNTrks, h1title, CutRun1);
        }else{
            histogram[i] = getHistoFromTree(chains[i], Variable, h1title, CutRun1);
        }
    }else if(i ==0){
        if (TString(Variable.name).EqualTo("B_iso_7_Chi2_5_LoosePt05")){
            // histogram[i] = getHistoFromTree(chains[i], isoAlltracks, h1title, CutAdd2017run);
            histogram[i] = getHistoFromTree(chains[i], isoAlltracks, h1title, CutAdd*"testweight");
            // histogram[i] = getHistoFromTree(chains[i], Variable, h1title, CutAdd);
        }else if (TString(Variable.name).EqualTo("B_iso_Ntracks_7_Chi2_5_LoosePt05")){
            // histogram[i] = getHistoFromTree(chains[i], isoNtrksAlltrks, h1title, CutAdd*"PVWeights*testweight");
            histogram[i] = getHistoFromTree(chains[i], isoNtrksAlltrks, h1title, CutAdd*"testweight");
            // histogram[i] = getHistoFromTree(chains[i], Variable, h1title, CutAdd);
        }else if (TString(Variable.name).EqualTo("closeTrkNtrksChi2")){
            histogram[i] = getHistoFromTree(chains[i], closeTrkNtrks_AllTrks, h1title, CutAdd*"testweight");
            // histogram[i] = getHistoFromTree(chains[i], Variable, h1title, CutAdd);
        }else if (TString(Variable.name).EqualTo("closeTrkDOCA")){
            histogram[i] = getHistoFromTree(chains[i], closeTrkDOCA_AllTrks2, h1title, CutAdd*"testweight");
            // histogram[i] = getHistoFromTree(chains[i], Variable, h1title, CutAdd);
        }else{
            histogram[i] = getHistoFromTree(chains[i], Variable, h1title, CutAdd*"PVWeights");
        }
    // histogram[i] = getHistoFromTree(chains[i], Variable, h1title, CutAdd);
    }else if(i ==1||i==4){
        if (TString(Variable.name).EqualTo("B_iso_7_Chi2_5_LoosePt05")){
            histogram[i] = getHistoFromTree(chains[i], isoAlltracks, h1title, CutAdd*"testweight");
            // histogram[i] = getHistoFromTree(chains[i], Variable, h1title, CutAdd);
        }else if (TString(Variable.name).EqualTo("B_iso_Ntracks_7_Chi2_5_LoosePt05")){
            // histogram[i] = getHistoFromTree(chains[i], isoNtrksAlltrks, h1title, CutAdd*"PVWeights*testweight");
            histogram[i] = getHistoFromTree(chains[i], isoNtrksAlltrks, h1title, CutAdd*"testweight");
            // histogram[i] = getHistoFromTree(chains[i], Variable, h1title, CutAdd);
        }else if (TString(Variable.name).EqualTo("closeTrkNtrksChi2")){
            histogram[i] = getHistoFromTree(chains[i], closeTrkNtrks_AllTrks, h1title, CutAdd*"testweight");
            // histogram[i] = getHistoFromTree(chains[i], Variable, h1title, CutAdd);
        }else if (TString(Variable.name).EqualTo("closeTrkDOCA")){
            histogram[i] = getHistoFromTree(chains[i], closeTrkDOCA_AllTrks2, h1title, CutAdd*"testweight");
            // histogram[i] = getHistoFromTree(chains[i], Variable, h1title, CutAdd);
        }else{
            histogram[i] = getHistoFromTree(chains[i], Variable, h1title, CutAdd*"PVWeights");
        }
    // histogram[i] = getHistoFromTree(chains[i], Variable, h1title, CutAdd*"PVWeights*testweight");
    }
    else histogram[i] = getHistoFromTree(chains[i], Variable, h1title, (CutAdd && CutSB));
    h1title = h1titledummy;
    h1title+="_Data";
    } 
    h2title+="_mcX";
  for (int i=0;i<NumberOfTreesMC;i++) {
    h2title+="_";
    h2title+=treenamesMC[i];
    if(h2title.Contains("Muon1")){
    // h2[i] = getHistoFromTree(chainsMC[i], Variable, h2title, CutAdd*"PVWeights*Muon1_reco_eff_sf*testweight");
    // h2[i] = getHistoFromTree(chainsMC[i], Variable, h2title, (CutAdd && CutSB)*"PVWeights*Muon1_reco_eff_sf*testweight");
    h2[i] = getHistoFromTree(chainsMC[i], Variable, h2title, (CutAdd && CutSB));
    }else if (h2title.Contains("Muon2")){
    // h2[i] = getHistoFromTree(chainsMC[i], Variable, h2title, CutAdd*"PVWeights*Muon2_reco_eff_sf*testweight");
    // h2[i] = getHistoFromTree(chainsMC[i], Variable, h2title, (CutAdd && CutSB)*"PVWeights*Muon2_reco_eff_sf*testweight");
    h2[i] = getHistoFromTree(chainsMC[i], Variable, h2title, (CutAdd && CutSB));
    // }else if (h2title.Contains("B")){
    // h2[i] = getHistoFromTree(chainsMC[i], Variable, h2title, CutAdd*"PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf*testweight");
    // }else if (h2title.Contains("closeTrkDOCA")){
    // h2 = getHistoFromTree(tm, {"closeTrkDOCA",40,0,2,true,"DOCA_{xtrk, loose, pt>0.5} [mm]",false}, h2title, CutAdd*"PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf*testweight");
    }else{
    // h2 = getHistoFromTree(tm, Variable, h2title, CutAdd*"testweight");//added with addWeight.C code
    // h2[i] = getHistoFromTree(chainsMC[i], Variable, h2title, CutAdd*"PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf*testweight");
    // h2[i] = getHistoFromTree(chainsMC[i], Variable, h2title, (CutAdd && CutSB)*"PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf*testweight");
    h2[i] = getHistoFromTree(chainsMC[i], Variable, h2title, (CutAdd && CutSB));
    }
  }//end of MC for loop
  h3title = h1titledummy;
  h3title+="_SigMC";
  for (int i=0;i<NumberOfTreesSigMC;i++) {
    h3title+="_";
    h3title+=to_string(i);
  if(h3title.Contains("Muon1")){
    // h3[i] = getHistoFromTree(chainsSigMC[i], Variable, h3title, CutAdd*"PVWeights*Muon1_reco_eff_sf*CombWeights*Muon1_trigger_sf");
    h3[i] = getHistoFromTree(chainsSigMC[i], Variable, h3title, CutAdd*"PVWeights*Muon1_reco_eff_sf");
    // h3[i] = getHistoFromTree(chainsSigMC[i], Variable, h3title, CutAdd);
    }else if (h3title.Contains("Muon2")){
    // h3[i] = getHistoFromTree(chainsSigMC[i], Variable, h3title, CutAdd*"PVWeights*Muon2_reco_eff_sf*CombWeights*Muon2_trigger_sf");
    h3[i] = getHistoFromTree(chainsSigMC[i], Variable, h3title, CutAdd*"PVWeights*Muon2_reco_eff_sf");
    // h3[i] = getHistoFromTree(chainsSigMC[i], Variable, h3title, CutAdd);
    }else{
    // h3[i] = getHistoFromTree(chainsSigMC[i], Variable, h3title, CutAdd*"PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf*CombWeights*Muon1_trigger_sf*Muon2_trigger_sf");
    h3[i] = getHistoFromTree(chainsSigMC[i], Variable, h3title, CutAdd*"PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf");
    // h3[i] = getHistoFromTree(chainsSigMC[i], Variable, h3title, CutAdd);
   }//
    h3title = h1titledummy;
    h3title+="_SigMC";
   }//end of h3 loop
  }//end of else if modes 
//----------------------Select Max Data histogram to normalize to and plot against----------------
vector <float> elements;
vector <float> elementsMC;
vector <float> elementsSigMC;
float maxHisto;
float maxHistoMC;
int maxinteger(0);
int maxintegerMC(0);
int maxintegerSigMC(0);

if (NumberOfTrees>1){
for (int i=0;i<NumberOfTrees;i++){
  elements.push_back(histogram[i]->GetMaximum());
}
maxinteger = distance(elements.begin(), max_element(elements.begin(), elements.end()));
}//end of numberoftrees if statement
else{maxinteger = 0;}
// cout<<"DEBUG: "<<elements[0]<<" "<<elements[1]<<" "<<elements[2]<<" "<<elements[3]<<" "<<endl;
// cout<<"DEBUG: "<<elements[maxinteger]<<endl;


cout<<"Debug here"<<endl;

//------------------------------------------------------------------------
//repeat for MC
if (NumberOfTreesMC>1){
  for (int i=0;i<NumberOfTreesMC;i++){
  elementsMC.push_back(h2[i]->GetMaximum());
}
maxintegerMC = distance(elementsMC.begin(), max_element(elementsMC.begin(), elementsMC.end()));
}//end of numberoftrees if statement
else{maxintegerMC = 0;}

if (NumberOfTreesSigMC>1){
  for (int i=0;i<NumberOfTreesSigMC;i++){
  elementsSigMC.push_back(h3[i]->GetMaximum());
}
maxintegerSigMC = distance(elementsSigMC.begin(), max_element(elementsSigMC.begin(), elementsSigMC.end()));
}//end of numberoftrees if statement
else{maxintegerSigMC = 0;}
// cout<<"DEBUG: "<<elementsMC[0]<<" "<<elementsMC[1]<<" "<<elementsMC[2]<<" "<<elementsMC[3]<<" "<<endl;
// cout<<"DEBUG: "<<elementsMC[maxintegerMC]<<endl;

// //Normalization doesn't work properly for PRIVX_mu for COARSE PERIOD separation
// //so manually correct it here:
// if (h1title.Contains("PRIVX_mu") && NumberOfTreesMC <5){
//   maxintegerMC = 0;
//   maxintegerSigMC = 0;
//   maxinteger = 0;
// }
//------------------------------------------------------------------------

  //  h2->SetFillStyle(3004);
  if (Variable.nbins>0 && Variable.XMin!= Variable.XMax) {
    histogram[maxinteger]->GetXaxis()->SetRangeUser(Variable.XMin,Variable.XMax);
    if (h2[maxintegerMC]) h2[maxintegerMC]->GetXaxis()->SetRangeUser(Variable.XMin,Variable.XMax);
    if (h3[maxintegerSigMC]) h3[maxintegerSigMC]->GetXaxis()->SetRangeUser(Variable.XMin,Variable.XMax);
  }
  else if (Variable.nbins!=-1) { 
    if (h2[maxintegerMC]) h2[maxintegerMC]->GetXaxis()->Set(histogram[maxinteger]->GetXaxis()->GetNbins(),histogram[maxinteger]->GetXaxis()->GetXmin(),histogram[maxinteger]->GetXaxis()->GetXmax());
    if (h2[maxintegerSigMC]) h2[maxintegerSigMC]->GetXaxis()->Set(histogram[maxinteger]->GetXaxis()->GetNbins(),histogram[maxinteger]->GetXaxis()->GetXmin(),histogram[maxinteger]->GetXaxis()->GetXmax());
  }
  if (normalize) {
    //typically means normalize MC(h2) to data (histogram[maxinteger])
    //
    cout << endl;
    cout << "INFO Integral of entries of each histo BEFORE normalization: " << endl;
    cout << histogram[maxinteger]->GetTitle() <<": "<< histogram[maxinteger]->Integral(0, Variable.nbins + 1);
    if (h2[maxintegerMC]) cout << "Bkg MC: "<< h2[maxintegerMC]->GetTitle()<< ": "<< h2[maxintegerMC]->Integral(0, Variable.nbins + 1);
    if (h3[maxintegerSigMC]) cout << " Signal MC:  "<< h3[maxintegerSigMC]->GetTitle()<< ": "<< h3[maxintegerSigMC]->Integral(0, Variable.nbins + 1);
    cout << endl;
    cout << endl;
    
    // for (int i=0; i< NumberOfTreesMC; i++){
    //     cout << "DEBUG: "<< h2[i]->GetTitle()<< ": int.:"<< h2[i]->Integral()<< " entries: "<< chainsMC[i]->GetEntries()<< endl;
    // }

  //   h2->Scale(histogram[maxinteger]->Integral()/h2->Integral()); // ATTENTION under- and over-flows not taken into account!!!  
  // for (int i=0;i<NumberOfTrees;i++) {
  //   if (i != maxinteger) histogram[i]->Scale(histogram[maxinteger]->Integral()/histogram[i]->Integral());
  // }
  if (arbitraryUnits){ 
    histogram[maxinteger]->Scale(1./histogram[maxinteger]->Integral(0, Variable.nbins + 1));
    if(h1title.Contains("B") && h1title.Contains("mass") && Variable.nbins == 60){
      for (int i=0;i<NumberOfTreesMC;i++) {
        h2[i]->Scale((histogram[maxinteger]->Integral(0, Variable.nbins + 1) - histogram[maxinteger]->Integral(19,39))/(h2[i]->Integral(0, Variable.nbins + 1) - h2[i]->Integral(19,39)));
      }
      for (int i=0;i<NumberOfTreesSigMC;i++) {
        h3[i]->Scale(1./(h3[i]->Integral(0, Variable.nbins + 1)));
      }
    }
    else{
      for (int i=0;i<NumberOfTreesMC;i++) {
        h2[i]->Scale(histogram[maxinteger]->Integral(0, Variable.nbins + 1)/h2[i]->Integral(0, Variable.nbins + 1));
        // h2[i]->Scale(1./h2[i]->Integral(0, Variable.nbins + 1));
      }
      for (int i=0;i<NumberOfTreesSigMC;i++) {
        h3[i]->Scale(histogram[maxinteger]->Integral(0, Variable.nbins + 1)/h3[i]->Integral(0, Variable.nbins + 1));
        // h3[i]->Scale(1./h3[i]->Integral(0, Variable.nbins + 1));
        }
      }
    for (int i=0;i<NumberOfTrees;i++) {
         
    //this is scaled to one, but kept for other data periods.
      histogram[i]->Scale(histogram[maxinteger]->Integral(0, Variable.nbins + 1)/histogram[i]->Integral(0, Variable.nbins + 1));
      // histogram[i]->Scale(1./histogram[i]->Integral(0, Variable.nbins + 1));
    }//
  }// ifarbitraryUnits
  }//end of normalize for loop

  // TString axLab = Variable.axLabel;
  histogram[maxinteger]->GetXaxis()->SetTitle(axLab);
  if (h2[maxintegerMC]) {
    h2[maxintegerMC]->GetXaxis()->SetTitle(axLab);
  }
  if (h3[maxintegerSigMC]) {
    h3[maxintegerSigMC]->GetXaxis()->SetTitle(axLab);
  }

  if (drawResiduals) {
    // histogram[maxinteger]->GetYaxis()->SetTitleOffset(0.7); //0.57
    histogram[maxinteger]->GetYaxis()->SetTitleOffset(1.); //0.57
    histogram[maxinteger]->GetYaxis()->SetTitleSize(0.08);
    if (h2[maxintegerMC]) {
      // h2[maxintegerMC]->GetYaxis()->SetTitleOffset(0.7); //0.57
      h2[maxintegerMC]->GetYaxis()->SetTitleOffset(1.); //0.57
      h2[maxintegerMC]->GetYaxis()->SetTitleSize(0.08);
    }
    if (h3[maxintegerSigMC]) {
      // h3[maxintegerSigMC]->GetYaxis()->SetTitleOffset(0.7); //0.57
      h3[maxintegerSigMC]->GetYaxis()->SetTitleOffset(1.); //0.57
      h3[maxintegerSigMC]->GetYaxis()->SetTitleSize(0.08);
    }

  }
  else {
    histogram[maxinteger]->GetYaxis()->SetTitleOffset(1.3);
    histogram[maxinteger]->GetYaxis()->SetTitleSize(0.05);
    if (h2[maxintegerMC]) {
      h2[maxintegerMC]->GetYaxis()->SetTitleOffset(1.3);
      h2[maxintegerMC]->GetYaxis()->SetTitleSize(0.05);
    }
    if (h3[maxintegerSigMC]) {
      h3[maxintegerSigMC]->GetYaxis()->SetTitleOffset(1.3);
      h3[maxintegerSigMC]->GetYaxis()->SetTitleSize(0.05);
    }
  }//end of if (drawResiduals)
 // }//end histo for loop 1
  // TString yAxisTitle = getYAxisTitle(Variable.name);
  if (Variable.nbins>0 && Variable.XMin!= Variable.XMax) {
    yAxisTitle +=" / ";
    char buf[20];
    sprintf(buf,"%3.2f",(Variable.XMax-Variable.XMin)/(double)Variable.nbins);
    yAxisTitle+=buf;
    yAxisTitle += " "; //FMPLOT
    TString dummyStr(axLab);
    dummyStr.Remove(0,dummyStr.Index('[')+1);
    dummyStr.Remove(dummyStr.Index(']'),dummyStr.Length());
    if (axLab.Contains("[")) yAxisTitle += dummyStr;
  }
// for (int i=0;i<NumberOfTrees;i++) { 
if (arbitraryUnits){
    if (h1title.Contains("B_minChi2MuonsIPtoAnyPV")){
        histogram[maxinteger]->GetYaxis()->SetTitle("1/N dn/d#chi^{2}");
        if (h2[maxintegerMC]) h2[maxintegerMC]->GetYaxis()->SetTitle("1/N dn/d#chi^{2}");
        if (h3[maxintegerSigMC]) h3[maxintegerSigMC]->GetYaxis()->SetTitle("1/N dn/d#chi^{2}");
    }
    else if (h1title.Contains("fabs_a_2D")){
        histogram[maxinteger]->GetYaxis()->SetTitle("1/N dn/d|#alpha_{2D}|");
        if (h2[maxintegerMC]) h2[maxintegerMC]->GetYaxis()->SetTitle("1/N dn/d|#alpha_{2D}|");
        if (h3[maxintegerSigMC]) h3[maxintegerSigMC]->GetYaxis()->SetTitle("1/N dn/d|#alpha_{2D}|");
    }else if (h1title.Contains("Lxy")){
        histogram[maxinteger]->GetYaxis()->SetTitle("Fraction of events / 0.1 mm");
        if (h2[maxintegerMC]) h2[maxintegerMC]->GetYaxis()->SetTitle("Fraction of events / 0.1 mm");
        if (h3[maxintegerSigMC]) h3[maxintegerSigMC]->GetYaxis()->SetTitle("Fraction of events / 0.1 mm");
    }else if (h1title.Contains("B_iso_7_Chi2_5_LoosePt05")){
        histogram[maxinteger]->GetYaxis()->SetTitle("Fraction of events / 0.02");
        if (h2[maxintegerMC]) h2[maxintegerMC]->GetYaxis()->SetTitle("Fraction of events / 0.02");
        if (h3[maxintegerSigMC]) h3[maxintegerSigMC]->GetYaxis()->SetTitle("Fraction of events / 0.02");
    }else if (h1title.Contains("DR")){
        histogram[maxinteger]->GetYaxis()->SetTitle("1/N dn/d#DeltaR");
        if (h2[maxintegerMC]) h2[maxintegerMC]->GetYaxis()->SetTitle("1/N dn/d#DeltaR");
        if (h3[maxintegerSigMC]) h3[maxintegerSigMC]->GetYaxis()->SetTitle("1/N dn/d#DeltaR");
    }else if (h1title.Contains("chi2_PVSV_log2D")){
        histogram[maxinteger]->GetYaxis()->SetTitle("Fraction of events / 0.25");
        if (h2[maxintegerMC]) h2[maxintegerMC]->GetYaxis()->SetTitle("Fraction of events / 0.25");
        if (h3[maxintegerSigMC]) h3[maxintegerSigMC]->GetYaxis()->SetTitle("Fraction of events / 0.25");
    }else if (h1title.Contains("B_IDtrks_DCA")){
        histogram[maxinteger]->GetYaxis()->SetTitle("Fraction of events / 0.01 mm");
        if (h2[maxintegerMC]) h2[maxintegerMC]->GetYaxis()->SetTitle("Fraction of events / 0.01 mm");
        if (h3[maxintegerSigMC]) h3[maxintegerSigMC]->GetYaxis()->SetTitle("Fraction of events / 0.01 mm");
    }
    else{
        histogram[maxinteger]->GetYaxis()->SetTitle("a.u.");
        if (h2[maxintegerMC]) h2[maxintegerMC]->GetYaxis()->SetTitle("a.u.");
        if (h3[maxintegerSigMC]) h3[maxintegerSigMC]->GetYaxis()->SetTitle("a.u.");
    }
}
else{
  histogram[maxinteger]->GetYaxis()->SetTitle(yAxisTitle);
  if (h2[maxintegerMC]) h2[maxintegerMC]->GetYaxis()->SetTitle(yAxisTitle); 
  if (h3[maxintegerSigMC]) h3[maxintegerSigMC]->GetYaxis()->SetTitle(yAxisTitle); 
}
  Double_t chi2_1(0.),ks1(0.);
  Int_t ndf_1(0), igood_1(0);
// cout<<"Debug here2"<<endl; 
//Add to Latex Table to include ks1 and chi2/ndf 
  // if (h2[maxintegerMC]) {
  //   for (int i=0;i<NumberOfTrees;i++){
  //       histogram[i]->Chi2TestX(h2[i],chi2_1,ndf_1,igood_1,"WW P"); //Weighted Weighted Print
  //       ks1 = histogram[i]->KolmogorovTest(h2[i]);
  //       TString tabentry(Variable.axLabel);
  //       if (tabentry.Contains("DeltaR")) tabentry.ReplaceAll("DeltaR","Delta~R");
  //       char buf[20];
  //       sprintf(buf,"%5.1f/%3d",chi2_1,ndf_1);
  //       tabentry.ReplaceAll('#','\\');
  //       // tabentry.Append(' Period');
  //       TString treenamesdummy = treenames[i];
  //       if (treenamesdummy.Contains("T_mv_")) treenamesdummy.ReplaceAll("T_mv_"," Period ");
  //       else if(treenamesdummy.Contains("T_mv"))  treenamesdummy.ReplaceAll("T_mv","");
  //      if (mode.EqualTo("dt_mc_SepPeriods") || mode.EqualTo("dt_mcXs_Mult")) ofiletex << treenamesdummy << " & " << "$"<< tabentry <<"$" << " & "<< ks1 << " & "<< buf << "\\\\\n\\hline\n";
  //      else ofiletex << "$"<< tabentry <<"$" << " & "<< ks1 << " & "<< buf << "\\\\\n\\hline\n";
  //    }
  // }

// }//end histo for loop 2
  TPad *pad1, *pad2;

  if (drawResiduals) {
  pad1 = new TPad("pad1","pad1",0,0.33,1,1); //xlow ylow xup yup
  pad2 = new TPad("pad2","pad2",0,0,1,0.33); //0.3
    pad1->SetMargin(0.16,0.05,0.028,0.09);//left, right, bottom, top
    // pad1->SetMargin(0.12,0.05,0.028,0.09);
    pad1->SetBorderMode(0);
    if (Variable.logScale) pad1->SetLogy();
    if (h2[maxintegerMC]) {
        pad2->SetMargin(0.16,0.05,0.38,0.04);
      // pad2->SetMargin(0.12,0.05,0.38,0.06);
      pad2->SetBorderMode(0);
      pad1->Draw();
      pad2->Draw();
      pad1->cd();
    }
  }//end of  if (drawResiduals)
  else{
    pad1 = new TPad("pad1","pad1",0,0,1,1); //xlow ylow xup yup
    pad2 = new TPad("pad2","pad2",0,0,0,0); //0.3
    if (Variable.logScale) pad1->SetLogy();
    pad1->SetMargin(0.16,0.05,0.16,0.09);
    pad1->Draw();
    pad1->cd();
  }//end of  if else (drawResiduals)

// gStyle->SetPalette(77);

for (int i=0;i<NumberOfTrees;i++) {
// for (int i=0;i<NumberOfTrees;i++) {
  // histogram[i]->SetLineWidth(2);        
  //histogram[0]->SetFillColor(0);        
  //histogram[0]->SetLineColor(kBlack);  
  histogram[i]->SetLineStyle(1);        
  histogram[i]->SetMarkerSize(0.9);     
  // histogram[i]->SetMarkerStyle(20 + i); //different marker style for each histogram
  // histogram[i]->SetMarkerStyle(20);
  histogram[i]->SetMarkerColor(1); 
  }    
  // histogram[0]->SetMarkerColor(kBlack);
  // if (h2[maxintegerMC]) h2[maxintegerMC]->SetLineWidth(2);
  if (h2[maxintegerMC]){ 
     h2[maxintegerMC]->SetFillColor(0);//kRed);/*30*/
     h2[maxintegerMC]->SetFillColor(0);//kRed);/*30*/
     h2[maxintegerMC]->SetFillColor(0);//kRed);/*30*/ 
     h2[maxintegerMC]->SetLineColor(kGreen+2);   
     h2[maxintegerMC]->SetLineStyle(1);/*22*/
     h2[maxintegerMC]->SetMarkerSize(0.);
     h2[maxintegerMC]->SetMarkerStyle(25);   
     h2[maxintegerMC]->SetMarkerColor(kGreen+2);
     h2[maxintegerMC]->SetFillStyle(3002);
 }
   if (h3[maxintegerSigMC]){ 
       h3[maxintegerSigMC]->SetFillColor(0);//kRed);/*30*/
       h3[maxintegerSigMC]->SetLineColor(kRed+2);   
       h3[maxintegerSigMC]->SetLineStyle(1);/*22*/
       h3[maxintegerSigMC]->SetMarkerSize(0.);
       h3[maxintegerSigMC]->SetMarkerStyle(25);   
       h3[maxintegerSigMC]->SetMarkerColor(kRed+2);
       h3[maxintegerSigMC]->SetFillStyle(3002);
 }
  //if (h2[0]) h2->SetMarkerSize(0);

// auto elements = { histogram[0]->GetMaximum(), number4, number5, number6 };



//---------------------Draw the Histograms: --------------------
  if (h2[maxintegerMC] && h2[maxintegerMC]->GetMean()!=0 && h2[maxintegerMC]->GetRMS()!=0) {

    if (drawResiduals){
        histogram[maxinteger]->GetYaxis()->SetLabelSize(0.08);
        histogram[maxinteger]->GetXaxis()->SetNoExponent();
        histogram[maxinteger]->GetXaxis()->SetLabelOffset(0.028); //0.07
        histogram[maxinteger]->GetXaxis()->SetTitle("");
        h2[maxintegerMC]->GetYaxis()->SetLabelSize(0.08);
        h2[maxintegerMC]->GetXaxis()->SetNoExponent();
        h2[maxintegerMC]->GetXaxis()->SetLabelOffset(0.028); //0.07
        h2[maxintegerMC]->GetXaxis()->SetTitle("");
        if (h3[maxintegerSigMC]){
            h3[maxintegerSigMC]->GetYaxis()->SetLabelSize(0.08);
            h3[maxintegerSigMC]->GetXaxis()->SetNoExponent();
            h3[maxintegerSigMC]->GetXaxis()->SetLabelOffset(0.028); //0.07
            h3[maxintegerSigMC]->GetXaxis()->SetTitle("");}
        cout << histogram[maxinteger]->GetMaximum() <<" <=h1max|h2max-> "<<h2[maxintegerMC]->GetMaximum()<< endl;
    }else{
        histogram[maxinteger]->GetYaxis()->SetLabelSize(0.05);
        histogram[maxinteger]->GetXaxis()->SetNoExponent();
        histogram[maxinteger]->GetXaxis()->SetLabelOffset(0.028); //0.07
        // histogram[maxinteger]->GetXaxis()->SetTitle("");
        h2[maxintegerMC]->GetYaxis()->SetLabelSize(0.05);
        h2[maxintegerMC]->GetXaxis()->SetNoExponent();
        h2[maxintegerMC]->GetXaxis()->SetLabelOffset(0.028); //0.07
        // h2[maxintegerMC]->GetXaxis()->SetTitle("");
        if (h3[maxintegerSigMC]){
            h3[maxintegerSigMC]->GetYaxis()->SetLabelSize(0.05);
            h3[maxintegerSigMC]->GetXaxis()->SetNoExponent();
            h3[maxintegerSigMC]->GetXaxis()->SetLabelOffset(0.028); //0.07
            // h3[maxintegerSigMC]->GetXaxis()->SetTitle("");}
        cout << histogram[maxinteger]->GetMaximum() <<" <=h1max|h2max-> "<<h2[maxintegerMC]->GetMaximum()<< endl;
        }   
    }   


  //   if (histogram[maxinteger]->GetMaximum()>h2[maxintegerMC]->GetMaximum()) {
  //     histogram[maxinteger]->SetMaximum(histogram[maxinteger]->GetMaximum()*1.5);
  //     histogram[maxinteger]->Draw("ep PLC PMC"); //PFC
  //     // histogram[maxinteger]->Draw("epsame");
  //     h2[maxintegerMC]->Draw("histsame");
  //     // if(!histogram[maxinteger]->GetFillColor()) histogram[maxinteger]->Draw("epsame");
  //   } else {
  //     h2[maxintegerMC]->SetMaximum(h2[maxintegerMC]->GetMaximum()*1.5);
  //     h2[maxintegerMC]->Draw("hist");
  //     // h2[maxintegerMC]->Draw("histsame");
  //     histogram[maxinteger]->Draw("epsame PLC PMC"); //PFC
  //   }
  // } else {
  //   histogram[maxinteger]->Draw("ep PLC PMC"); //PFC
  // }
if (NumberOfTrees>1){
  for (int i=0;i<NumberOfTrees;i++) {
    histogram[i]->SetMarkerColor(ColorWheel[i]);
    histogram[i]->SetLineColor(ColorWheel[i]);
    histogram[i]->SetLineWidth(1);
  }
}else{
  histogram[0]->SetMarkerColor(1);
  histogram[0]->SetLineColor(1);
  histogram[0]->SetLineWidth(2);
  histogram[0]->SetMarkerStyle(20);

}

if (NumberOfTreesMC>1){
  for (int i=0;i<NumberOfTreesMC;i++) {
    h2[i]->SetMarkerColor(ColorWheel[i]);
    h2[i]->SetMarkerSize(0);
    h2[i]->SetLineColor(ColorWheel[i]);
    h2[i]->SetLineWidth(1);
  }
}else{
  h2[0]->SetMarkerColor(ColorWheel[0]);
  h2[0]->SetLineColor(ColorWheel[0]);
  h2[0]->SetLineWidth(2);
}

if (maxintegerSigMC>1){
for (int i=0;i<NumberOfTreesSigMC;i++) {
  h3[i]->SetMarkerColor(ColorWheel[i]);
  h3[i]->SetMarkerSize(0);
  h3[i]->SetLineColor(ColorWheel[i]);
  h3[i]->SetLineWidth(2);
  // h3[i]->SetFillColor(ColorWheel[1]);
  h3[i]->SetFillColor(0);
  // h3[i]->SetFillStyle(3007);
  // h3[i]->SetFillStyle(3003);
    }   
}else{
  h3[0]->SetMarkerColor(ColorWheel[1]);
  h3[0]->SetLineColor(ColorWheel[1]);
  h3[0]->SetLineWidth(2);
  // h3[i]->SetFillColor(ColorWheel[1]);
  h3[0]->SetFillColor(0);
  // h3[i]->SetFillStyle(3007);
  // h3[i]->SetFillStyle(3003);
}
// h2[maxintegerMC]->SetLineColor(ColorWheel[0]);

// h2[maxintegerMC]->Draw("hist");
// h2[maxintegerMC]->Draw("ehist");//not plotted to just have sigMC v bkg
// for (int i=0;i<NumberOfTreesMC;i++) {
//   if (i != maxintegerMC){
//    // h2[i]->SetLineColor(ColorWheel[i+1]);
//    h2[i]->Draw("histsame");
//   }
// }
// if(h3[maxintegerSigMC]){
h3[maxintegerSigMC]->Draw("ehistsame");
for (int i=0;i<NumberOfTreesSigMC;i++) {
   // h2[i]->SetLineColor(ColorWheel[i+1]);
   // h3[i]->Draw("ehistsame");
   if (i!=maxintegerSigMC)h3[i]->Draw("ehistsame");
}
// }
// histogram[maxinteger]->SetMarkerColor(ColorWheel[0]);
// histogram[maxinteger]->SetLineColor(ColorWheel[0]);
if(!Variable.PlotOnlyMC){
cout<<"Debug here2"<<endl; 

// histogram[maxinteger]->Draw("epsame");//PLC PMC
histogram[maxinteger]->Draw("e0psame");//PLC PMC
for (int i=0;i<NumberOfTrees;i++) {
  if (i != maxinteger){
    // histogram[i]->SetMarkerColor(ColorWheel[i+1]);
    // histogram[i]->SetLineColor(ColorWheel[i+1]);
    histogram[i]->Draw("e0psame");
    cout<<"Debug here2.5"<<endl; 
    } //PLC PMC PFC

}
}
cout<<"Debug here3"<<endl; 


// EColor myColor = kBlue;
// vector <EColor> myColor;
// myColor.push_back(kBlue);
Double_t YminVal(0.), YmaxVal(0.);
YminVal = histogram[maxinteger]->GetMinimum();
YmaxVal = histogram[maxinteger]->GetMaximum();
// YmaxVal = h3[maxintegerSigMC]->GetMaximum();
// if (histogram[maxinteger]->GetMinimum() < h2[maxintegerMC]->GetMinimum() && histogram[maxinteger]->GetMinimum() < h3[maxintegerMC]->GetMinimum()){
//     YminVal = histogram[maxinteger]->GetMinimum();
// }
// else if(h3[maxinteger]->GetMinimum() < h2[maxintegerMC]->GetMinimum() && h3[maxinteger]->GetMinimum() < histogram[maxintegerMC]->GetMinimum()){
// YminVal=h3[maxinteger]->GetMinimum();
// }else{
//     YminVal = h2[maxinteger]->GetMinimum();
// }
// if (histogram[maxinteger]->GetMaximum() > h2[maxintegerMC]->GetMaximum() && histogram[maxinteger]->GetMaximum() > h3[maxintegerMC]->GetMaximum()){
//     YmaxVal = histogram[maxinteger]->GetMaximum();
// }
// else if(h3[maxinteger]->GetMaximum() > h2[maxintegerMC]->GetMaximum() && h3[maxinteger]->GetMaximum() > histogram[maxintegerMC]->GetMaximum()){
//     YmaxVal=h3[maxinteger]->GetMaximum();
// }else{
//     YmaxVal = h2[maxinteger]->GetMaximum();
// }
cout<<"Debug here4"<<endl; 

// TString VarName = (TString)Variable.name;
// if(Variable.logScale) YmaxVal = YmaxVal*12;
// if(VarName.Contains("pow(closeTrkDCA,2)+pow(closeTrkZCA,2)")
//  || VarName.Contains("B_iso_7_Chi2_5_LoosePt05")
//  || VarName.Contains("B_IDtrks_deltaPhi")
//  || VarName.Contains("B_IDtrks_deltaEta")
//  || VarName.EqualTo("TMath::Abs(d0Min)")
//  || VarName.Contains("pow(B_IDtrks_deltaEta, 2) + pow(B_IDtrks_deltaPhi, 2)")
//  || VarName.EqualTo("d0Max")
//  || VarName.EqualTo("d0Min")
//  || VarName.Contains("chi2_PVSV_log2D")
//  // || VarName.Contains("")
//  // || VarName.Contains("")
//     ){
//     YmaxVal = YmaxVal*12;
// }
// if(VarName.Contains("PRIVX_mu")
//  || VarName.Contains("B_minChi2MuonsIPtoAnyPV")
//  || VarName.EqualTo("B_eta")
//  // || VarName.Contains("")
//  // || VarName.Contains("")
//  // || VarName.Contains("")
//     ){
//     YmaxVal = YmaxVal/1.5*2;
// }
if(Variable.logScale) YmaxVal = YmaxVal*12;
else YmaxVal = YmaxVal*2;


if (!Variable.logScale){
  // if(h1titledummy.EqualTo("Npv")){
  //   histogram[maxinteger]->GetYaxis()->SetRangeUser(0, 0.16);
  //   h2[maxintegerMC]->GetYaxis()->SetRangeUser(0, 0.16);
  //   h3[maxintegerSigMC]->GetYaxis()->SetRangeUser(0, 0.16);
  // }else{
    histogram[maxinteger]->GetYaxis()->SetRangeUser(YminVal/1.5, YmaxVal);
    h2[maxintegerMC]->GetYaxis()->SetRangeUser(YminVal/1.5, YmaxVal);
    h3[maxintegerSigMC]->GetYaxis()->SetRangeUser(YminVal/1.5, YmaxVal);
    if (h1title.Contains("B_minChi2MuonsIPtoAnyPV")) {
        histogram[maxinteger]->GetYaxis()->SetRangeUser(YminVal/1.5, YmaxVal/2*1.5);
        h2[maxintegerMC]->GetYaxis()->SetRangeUser(YminVal/1.5, YmaxVal/2*1.5);
        h3[maxintegerSigMC]->GetYaxis()->SetRangeUser(YminVal/1.5, YmaxVal/2*1.5);
    }else if (h1title.Contains("chi2_PVSV_log2D")|| h1title.Contains("B_iso_7_Chi2_5_LoosePt05")) {
        histogram[maxinteger]->GetYaxis()->SetRangeUser(0., YmaxVal/2*1.5);
          h2[maxintegerMC]->GetYaxis()->SetRangeUser(0., YmaxVal/2*1.5);
          h3[maxintegerSigMC]->GetYaxis()->SetRangeUser(0., YmaxVal/2*1.5);
      }else if (h1title.Contains("B_eta")) {
        histogram[maxinteger]->GetYaxis()->SetRangeUser(YminVal/1.5, YmaxVal);
        // histogram[maxinteger]->GetYaxis()->SetRangeUser(0, 0.5);
          h2[maxintegerMC]->GetYaxis()->SetRangeUser(YminVal/1.5, YmaxVal);
          h3[maxintegerSigMC]->GetYaxis()->SetRangeUser(YminVal/1.5, YmaxVal);
          cout<<"HELLLOO!!! "<<YmaxVal<< endl;
      }
  // }
}else {
  histogram[maxinteger]->SetMaximum(YmaxVal/12*15);
  h2[maxintegerMC]->SetMaximum(YmaxVal/12*15);
  h3[maxintegerSigMC]->SetMaximum(YmaxVal/12*15);
if (h1title.Contains("fabs_a_2D")) {
        histogram[maxinteger]->SetMaximum(YmaxVal/12*1.5);
        h2[maxintegerMC]->SetMaximum(YmaxVal/12*1.5);
        h3[maxintegerSigMC]->SetMaximum(YmaxVal/12*1.5);
    }else if (h1title.Contains("chi2_PVSV_log2D")|| h1title.Contains("B_iso_7_Chi2_5_LoosePt05")) {
        histogram[maxinteger]->SetMaximum(YmaxVal/12*25);
          h2[maxintegerMC]->SetMaximum(YmaxVal/12*25);
          h3[maxintegerSigMC]->SetMaximum(YmaxVal/12*25);
    }else if (h1title.Contains("Lxy")) {
        histogram[maxinteger]->SetMaximum(YmaxVal/12*1.5);
          h2[maxintegerMC]->SetMaximum(YmaxVal/12*1.5);
          h3[maxintegerSigMC]->SetMaximum(YmaxVal/12*1.5);
    }
  // histogram[maxinteger]->SetMinimum(YminVal);
  // h2[maxintegerMC]->SetMinimum(YminVal);
  // h3[maxintegerSigMC]->SetMinimum(YminVal);
    // histogram[maxinteger]->GetYaxis()->SetRangeUser(YminVal/10, YmaxVal*10);
    // h2[maxintegerMC]->GetYaxis()->SetRangeUser(YminVal/10, YmaxVal*10);
    // h3[maxintegerMC]->GetYaxis()->SetRangeUser(YminVal/10, YmaxVal*10);
}

//d0Max and d0Min zoom
if (h1titledummy.EqualTo("d0Max") && Variable.Zoom){
histogram[maxinteger]->GetXaxis()->SetRangeUser(-Variable.ZoomVal,Variable.ZoomVal);
h2[maxintegerMC]->GetXaxis()->SetRangeUser(-Variable.ZoomVal,Variable.ZoomVal);
}
if (h1titledummy.EqualTo("d0Min") && Variable.Zoom){
histogram[maxinteger]->GetXaxis()->SetRangeUser(-Variable.ZoomVal,Variable.ZoomVal);
h2[maxintegerMC]->GetXaxis()->SetRangeUser(-Variable.ZoomVal,Variable.ZoomVal);
}
}//if loop at start of draw histograms
//---------------------//---------------------//---------------------

  htitle+="_";
  htitle+=mode;

  TLegend *leg = defineLegendBox(Variable.name, mode,  drawResiduals, NumberOfTreesMC, Variable.Zoom, Variable.ZoomVal);
  leg->SetBorderSize(0);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  // leg->SetTextFont(132);
  leg->SetTextFont(42);
  // if (h1title.Contains("B_minChi2MuonsIPtoAnyPV") || h1title.Contains("fabs_a_2D")) leg->SetTextSize(0.067);
  // // else leg->SetTextSize(0.057);
  // // else leg->SetTextSize(0.045);
  // else 
    leg->SetTextSize(0.02);

//    leg->SetMargin(0.2);//Aidan
TString dtlabeldummy = dtlabel;
TString mclabeldummy = mclabel;

if (h1title.Contains("B_minChi2MuonsIPtoAnyPV")) atlasLabel(0.2, 0.54, false, true, 1, true, false, true, h1title);
else if (h1title.Contains("fabs_a_2D")) {
    atlasLabel(0.23, 0.73, false, true, 1, true, false, true, h1title);
}else if (h1title.Contains("B_IDtrks_DCA")) {
    atlasLabel(0.2, 0.81, false, true, 1, true, false, true, h1title);
}else if (h1title.Contains("chi2_PVSV_log2D")) {
    atlasLabel(0.58, 0.83, false, true, 1, true, false, true, h1title);
}else if (h1title.Contains("B_iso_7_Chi2_5_LoosePt05")) {
    atlasLabel(0.6, 0.8, false, true, 1, true, false, true, h1title);
}else if (h1title.Contains("Lxy") || h1title.Contains("B_iso_7_Chi2_5_LoosePt05")|| h1title.Contains("DR")) {
    atlasLabel(0.55, 0.67, false, true, 1, true, false, true, h1title);
}
else atlasLabel(0.62, 0.83, false, true, 1, true, false, true, h1title);

  if (h2[maxintegerMC]) {
    if (mode.Contains("dtbgsub_mcrew")) {
      leg->AddEntry(histogram[maxinteger],"Background-subtracted data run 302393","p"); //FIXMELEGEND
      leg->AddEntry(h2[maxintegerMC],"B^{+}#rightarrow J/#psi K^{+} MC15","l"); 
    } else {
      // dtlabel+=treenames[maxinteger];
      // if (dtlabel.Contains("T_mv_")) dtlabel.ReplaceAll("T_mv_"," Period ");
      // dtlabel+=" (A)";
      // leg->AddEntry(histogram[maxinteger],dtlabel,"elp");
        //
        //
        //
      leg->AddEntry(histogram[4],"2016 Run 302393","p");
      leg->AddEntry(histogram[0],"2017 Run 339849","p");
      leg->AddEntry(histogram[1],"2018 Run 358096","p");
      leg->AddEntry(histogram[3],"Run 1 Dataset","p");
      leg->AddEntry(histogram[2],"15+16 Dataset","p");
      // for (int i=0;i<NumberOfTrees;i++) {
      //   dtlabel = dtlabeldummy;
      //   dtlabel+=treenames[i];
      //   // dtlabel+=DataYear;
      //   if (dtlabel.Contains("T_mv_")) dtlabel.ReplaceAll("T_mv_"," Period ");
      //   else if(dtlabel.Contains("T_mv"))  dtlabel.ReplaceAll("T_mv"," ALL Periods");
      //   if (dtlabel.Contains("preTS1")) dtlabel.ReplaceAll("preTS1"," pre-TS1");
      //   else if (dtlabel.Contains("TS1toMD1")) dtlabel.ReplaceAll("TS1toMD1"," TS1-to-MD1");
      //   else if (dtlabel.Contains("postMD1")) dtlabel.ReplaceAll("postMD1"," post-MD1");
      //   // if (i != maxinteger) leg->AddEntry(histogram[i],dtlabel,"elp");
      //   // if (i == maxinteger) dtlabel+=" (A)";
      //   if(mode.Contains("mc_mc")){
      //     mclabeldummy+="2015 Trigger";
      //     mclabel+="2016 Trigger";
      //   leg->AddEntry(histogram[i],mclabeldummy,"elp");
      //   }else{
      //    // if(!Variable.PlotOnlyMC) leg->AddEntry(histogram[i],dtlabel,"elp");
      //    // if(!Variable.PlotOnlyMC) leg->AddEntry(histogram[i],"B^{0}_{s} #rightarrow #mu^{+} #mu^{-} sidebands","p");
      //   if(!Variable.PlotOnlyMC) {
      //       if(i ==4) leg->AddEntry(histogram[i],"2016 Run 302393","p");
      //       if(i ==0) leg->AddEntry(histogram[i],"2017 Run 339849","p");
      //       if(i ==1) leg->AddEntry(histogram[i],"2018 Run 358096","p");
      //       if(i ==3) leg->AddEntry(histogram[i],"Run 1","p");
      //       if(i ==2) leg->AddEntry(histogram[i],"2015 and 2016 Dataset","p");
      //   }
      //   if (NumberOfTreesMC>1){ 
      //     mclabel = mclabeldummy;
      //     mclabel+=treenames[i];
      //     if (mclabel.Contains("T_mv_")) mclabel.ReplaceAll("T_mv_"," Period ");
      //     if (mclabel.Contains("preTS1")) mclabel.ReplaceAll("preTS1"," pre-TS1");
      //     else if (mclabel.Contains("TS1toMD1")) mclabel.ReplaceAll("TS1toMD1"," TS1-to-MD1");
      //     else if (mclabel.Contains("postMD1")) mclabel.ReplaceAll("postMD1"," post-MD1");
      //     leg->AddEntry(h2[i],mclabel,"le");}
      //   }
      // }
       if (NumberOfTreesSigMC==1){ 
      // mclabel+=" (B)";
      // for (int i=0;i<NumberOfTreesMC;i++) {
      // mclabel = mclabeldummy;
      // mclabel+=treenames[i];
      // leg->AddEntry(h2[0],"b#bar{b} #rightarrow #mu^{+}#mu^{-}X MC","l");
        
      // leg->AddEntry(h2[0],"Continuum bkg MC","l");
      // leg->AddEntry(h3[0],"B^{0}_{s} #rightarrow #mu^{+} #mu^{-} MC","fl");
      leg->AddEntry(h3[0],"MC16a","l");
    }else{
      leg->AddEntry(h3[0],"MC16a","l");
      leg->AddEntry(h3[1],"MC16d","l");
      leg->AddEntry(h3[2],"MC16e","l");
    }
    }
  }

  // if (treenames[i].Contains("T_mv_")) treenames[i].ReplaceAll("T_mv_","Period_");
 
  leg->Draw();
  TLatex *texNpv;
if (CutAddString.Contains("Npv")){
  if (h1title.Contains("chi2_PVSV_log2D") || h1title.Contains("B_minChi2MuonsIPtoAnyPV")) texNpv = new TLatex(0.7, 0.75,"11 < nPV #leq 15");
  else if (CutAddString.Contains("Npv<=11") && CutAddString.Contains("11")) texNpv = new TLatex(0.2, 0.8,"nPV #leq 11");
  else if (CutAddString.Contains("Npv>11 && Npv<=15")) texNpv = new TLatex(0.2, 0.8,"11 < nPV #leq 15");
  else if (CutAddString.Contains("Npv>15")) texNpv = new TLatex(0.2, 0.8,"nPV > 15");
  texNpv->SetNDC();
  texNpv->SetTextSize(0.06);
  texNpv->SetTextFont(42);
  // texNpv->SetLineWidth(2);
  // texNpv->SetTextColor(color);
  texNpv->Draw();
}


TH1F** hres = new TH1F*[NumberOfTrees];

  bool drawResError = true;
  if (drawResiduals) {
    for (int i=0;i<NumberOfTrees;i++) {
    if(i == 3) continue; //dont include run 1/run1 ratio ha!
    pad2->cd();
    hres[i] = (TH1F*)histogram[i]->Clone("hres");
    cout << "Before plotting" << endl;
    hres[i]->SetMarkerSize(0.7);
    hres[i]->GetXaxis()->SetTitleOffset(1.0); //0.95
    hres[i]->GetXaxis()->SetTitle(axLab);
    hres[i]->GetXaxis()->SetTitleSize(0.17);
    hres[i]->GetXaxis()->SetLabelSize(0.15); //0.17 0.1
    hres[i]->GetXaxis()->SetRangeUser(Variable.XMin,Variable.XMax);
    
    // hres[i]->GetYaxis()->SetTitleSize(0.10);
    hres[i]->GetYaxis()->SetTitleSize(0.17);
    hres[i]->GetYaxis()->SetTitleOffset(0.32); //0.26
    // hres[i]->GetYaxis()->SetTitleOffset(0.6); //0.26
    // if (mode.Contains("dtbgsub_mcrew")) hres->GetYaxis()->SetTitle("Data/MC"); //FIXMELEGEND
    // else hres->GetYaxis()->SetTitle("A/B");
    // hres[i]->GetYaxis()->SetTitle("Data/MC");
    hres[i]->GetYaxis()->SetTitle("Run2/Run1");
    // hres[i]->GetYaxis()->SetTitle("Data / bb #rightarrow#mu^{+}#mu^{-}X MC");
    hres[i]->GetYaxis()->SetLabelSize(0.12);//0.17 //0.08
    hres[i]->GetYaxis()->SetNdivisions(4,3,0); //4,5,0
    
    // cout << "DEBUG " << " bin2 content: "<<histogram[maxinteger]->GetBinContent(2) << " error: "<< histogram[maxinteger]->GetBinError(2) << endl;
    // if (h2[0]) cout << "DEBUG " << " bin2 content: "<<h2->GetBinContent(2) << " error: "<< h2->GetBinError(2) << endl;
    // cout << "DEBUG " << " bin4 content: "<<histogram[maxinteger]->GetBinContent(4) << " error: "<< histogram[maxinteger]->GetBinError(4) << endl;
    // if (h2[0]) cout << "DEBUG " << " bin4 content: "<<h2->GetBinContent(4) << " error: "<< h2->GetBinError(4) << endl;
    
    hres[i]->Sumw2();
    
    // hres[i]->Divide(histogram[i],h2[i],1.0,1.0); //RATIO
    hres[i]->Divide(histogram[i],histogram[3],1.0,1.0); //RATIO
    // if(htitle.Contains("B_MUCALC_mass") || htitle.Contains("d0Min") || htitle.Contains("d0Max")){
    // if(htitle.Contains("B_MUCALC_mass"|| "Lxy")){
      // cout<<"DEBUG"<<" Aidan"<<endl;
    // hres[i]->GetYaxis()->SetRangeUser(0.85,1.15);
    // hres[i]->GetYaxis()->SetRangeUser(Variable.PullYmin,Variable.PullYmax);
    // }else{
    hres[i]->GetYaxis()->SetRangeUser(Variable.PullYmin,Variable.PullYmax);//0,2);//0.55,1.75); //
    // }

    hres[i]->SetMarkerColor(ColorWheel[i]);
    hres[i]->SetLineColor(ColorWheel[i]);
    // hres[i]->SetMarkerColor(1);
    // hres[i]->SetLineColor(1);
    // if (i == 0) hres[0]->Draw("");
    hres[i]->Draw("epsame");

    //d0Max and d0Min zoom
    // if (h1titledummy.EqualTo("d0Max") && Variable.Zoom){
    // hres[i]->GetXaxis()->SetRangeUser(-Variable.ZoomVal,Variable.ZoomVal);
    // }
    // if (h1titledummy.EqualTo("d0Min") && Variable.Zoom){
    // hres[i]->GetXaxis()->SetRangeUser(-Variable.ZoomVal,Variable.ZoomVal);
    // }
  }
    
    //Dotted line on lower pad at ratio = 1
    TLine *l;
    // if (h1titledummy.EqualTo("d0Max") && Variable.Zoom){
    // l = new TLine(-Variable.ZoomVal,1,Variable.ZoomVal,1);
    // }
    // else if (h1titledummy.EqualTo("d0Min") && Variable.Zoom){
    // l = new TLine(-Variable.ZoomVal,1,Variable.ZoomVal,1);
    // }else{
    l = new TLine(histogram[maxinteger]->GetXaxis()->GetXmin(),1,histogram[maxinteger]->GetXaxis()->GetXmax(),1);
    // }
    l->SetLineColor(kBlack);
    l->SetLineStyle(2);
    l->SetLineWidth(3);
    l->Draw();
    
    // TPaveText *chi2res = new TPaveText(0.72,0.76,0.98,0.95,"brNDC"); //0.62,0.56,0.88,0.75
    // chi2res->SetName("chi2res");
    // chi2res->SetFillStyle(0);
    // chi2res->SetTextAlign(12);
    // chi2res->SetTextSize(0.1);
    // chi2res->SetBorderSize(0);
    // char buf[20];
    // sprintf(buf,"#chi^{2}/ndf = %5.1f/%3d",chi2_1,ndf_1);
    // chi2res->AddText(buf);
    // sprintf(buf,"KS test = %1.6f",ks1);
    // chi2res->AddText(buf);
    // chi2res->Draw();  //FIXME KSSTAT
  }//end of if drawResiduals

  fout->cd();
  
  histogram[maxinteger]->SetTitle("dataSR");
  histogram[maxinteger]->SetName("dataSR");


//Not sure what hdiv->Write() is used for - did not correct for seperate periods
  if (h2[maxintegerMC]) {
    // create histogram with data/MC ratios
    //
    h2[maxintegerMC]->SetName("dataSB");
    h2[maxintegerMC]->SetTitle("dataSB");
  
    TH1F* hdiv =(TH1F*)histogram[maxinteger]->Clone("hdiv");
    hdivtitle  = Variable.name;
    hdivtitle+="_div_data_by_mc";
    hdiv->Sumw2();
    hdiv->Divide(histogram[maxinteger],h2[maxintegerMC],1.0/histogram[maxinteger]->Integral(0, Variable.nbins + 1),1.0/h2[maxintegerMC]->Integral(0, Variable.nbins + 1));//this = c1*h1/(c2*h2), Divide(h1,h2,c1,c2)
    for (Int_t i=1;i<=hdiv->GetNbinsX();i++) {
      if (hdiv->GetBinContent(i) < 0) {
    hdiv->SetBinContent(i, 1.0);
    hdiv->SetBinError(i, 0.);
      }
    }
    hdiv->SetTitle(hdivtitle);
    hdiv->SetName(hdivtitle);
    hdiv->Write();
  }//end of h2 if statement
// }//end of historam for loop

c1->Update();
c1->Write(htitle);

  c1->cd();
  c1->Update();
  if (Variable.Zoom){
    htitle+=Variable.ZoomName;
  }
    c1->SaveAs(outpath+htitle+".pdf");
    // c1->SaveAs(outpath+htitle+".png");
  // c1->SaveAs(outpath+htitle+".eps");
  //
  //
  // c1->SaveAs(outpath+htitle+".C");
  /*
  c1->SaveAs(outpath+htitle+".root");
  c1->SaveAs(outpath+htitle+".gif");
  */
    // for (int i=0;i<NumberOfTrees;i++) {histogram[i]->Write();}
  

  // c1->Write();
  // c1->Write(htitle);


  // delete histogram[0];

//Comment when working on legend placements
if (mode.EqualTo("systVars")) {
  for (int i=0;i<NumberOfTrees;i++) { delete histogram[i];}
  for (int i=0;i<NumberOfTreesMC;i++) { delete h2[i];}
  // delete h2;

  delete pad2;
  delete pad1;
  delete c1;
}
} //end of compare function

void atlasLabel(Double_t x,Double_t y, bool drawRes = true, bool Preliminary=true,Color_t color=1, bool drawEnergy=true, bool drawLumi=false, bool enlarge=true, TString h1title = "")
{
  double delx = 0.115*696*gPad->GetWh()*3/(5*472*gPad->GetWw());
  double textsize;
  double dy = 0.065;
  if (!drawRes) {
    if (enlarge) {
      textsize = 0.055; 
      delx+=0.03;
      dy = 0.065;
      // dy = 0.1;
    }
    else textsize = 0.06;
    delx+=0.04;
  }
  TLatex *tex = new TLatex(x,y,"ATLAS");
  tex->SetNDC();
  tex->SetTextSize(textsize);
  tex->SetTextFont(72);
  tex->SetLineWidth(2);
  tex->SetTextColor(color);
  tex->Draw();
  if (Preliminary) {
    tex = new TLatex(x+delx,y,"Internal"); //Preliminary
    // tex = new TLatex(x+delx,y,"Preliminary"); //Preliminary
    tex->SetNDC();
    tex->SetTextSize(textsize);
    tex->SetTextFont(42); //42
    tex->SetLineWidth(2);
    tex->SetTextColor(color);
    tex->Draw();
  }
  if (drawEnergy) {
    if (h1title.Contains("fabs_a_2D")) tex = new TLatex(0.5,0.55,"#sqrt{s} = 13 TeV, 26.3 fb^{-1}");
    else if (h1title.Contains("B_IDtrks_DCA")) tex = new TLatex(0.58,0.66,"#sqrt{s} = 13 TeV, 26.3 fb^{-1}");
    else if (h1title.Contains("chi2_PVSV_log2D")) tex = new TLatex(0.56,0.77,"#sqrt{s} = 13 TeV, 26.3 fb^{-1}");
    else if (h1title.Contains("B_iso_7_Chi2_5_LoosePt05")) tex = new TLatex(0.2,0.68,"#sqrt{s} = 13 TeV, 26.3 fb^{-1}");
    else tex = new TLatex(x+0.01,y-dy,"#sqrt{s} = 13 TeV, 26.3 fb^{-1}");
    tex->SetNDC();
    tex->SetTextSize(textsize);
    tex->SetTextFont(42);
    tex->SetLineWidth(2);
    tex->SetTextColor(color);
    // tex->Draw();
  }
  if (drawLumi) {
    tex = new TLatex(x-0.01,y-2*dy,"#int Ldt = 4.9 fb^{-1}");
    tex->SetNDC();
    tex->SetTextSize(textsize);
    tex->SetTextFont(42);
    tex->SetLineWidth(2);
    tex->SetTextColor(color);
    tex->Draw();
  }
}

// TLegend* defineLegendBox(TString what, Bool_t drawinlet){
//   TLegend* leg;
//   if (drawinlet){
//     if (what.Contains("Iso") || what.Contains("_iso_7") || what.Contains("_iso_5")) leg = new TLegend(0.14,0.74,0.64,0.94,NULL,"brNDC"); //xbl,ybl,xur,yur
//     else if (what.Contains("_iso_Ntracks")) leg = new TLegend(0.43,0.74-0.2,0.93,0.94,NULL,"brNDC");
//     else if (what.Contains("DR")) leg = new TLegend(0.39,0.72-0.2,0.89,0.92,NULL,"brNDC");
//     else if (what.Contains("Eta") || what.Contains("eta") || what.Contains("deltaPhi")) leg = new TLegend(0.12,0.22-0.2,0.62,0.42,NULL,"brNDC");
//     else if (what.Contains("lnChi2") || what.Contains("Chi2Muons") || what.Contains("chi2_PVSV") || what.Contains("SumMuTrackPixHits")) leg = new TLegend(0.17,0.74,0.67,0.94,NULL,"brNDC");
//     else if (what.Contains("BDT")) leg = new TLegend(0.12,0.66-0.2,0.85,0.82,NULL,"brNDC");
//     // else leg = new TLegend(0.45,0.74,0.95,0.94,NULL,"brNDC"); //xbl(0.71),ybl(0.62),xur(0.98),yur(0.98)
//     else leg = new TLegend(0.497494,0.514601, 0.997494, 0.919533,NULL,"brNDC");
//   } else {
//     if (what.Contains("Iso") || what.Contains("d0") || what.Contains("Eta") || what.Contains("eta") || what.Contains("DCA") || what.Contains("BDT")) leg = new TLegend(0.15,0.64,0.68,0.92,NULL,"brNDC"); //xbl,ybl,xur,yur //0.09
//     else if (what.Contains("DR")) leg = new TLegend(0.45,0.74,0.68,0.92,NULL,"brNDC");
//     else leg = new TLegend(0.74,0.75,0.95,0.93,NULL,"brNDC"); //xbl(0.71,0.68),ybl(0.62),xur(0.98),yur(0.98)
//   }
//   return leg;
// }

TLegend* defineLegendBox(TString what, TString mode, Bool_t drawinlet, int NumberOfTreesMC, Bool_t Zoom, Double_t ZoomVal){
int NumberOfColumns(2);
  TLegend* leg;
  if (mode.EqualTo("dt_mcXs") || mode.EqualTo("dt_mcXs_Mult") || mode.EqualTo("dt_mc_OnePeriod")){
    if (drawinlet){
        // if (what.Contains("B_iso_7_Chi2_5_LoosePt05")) leg = new TLegend(0.517544, 0.291369 , 0.829574, 0.58209,NULL,"brNDC");
        // else if (what.Contains("B_iso_Ntracks_7_Chi2_5_LoosePt05")) leg = new TLegend(0.281955, 0.260221, 0.537594, 0.504218 ,NULL,"brNDC");
        // else if (what.Contains("B_IDtrks_deltaPhi")) leg = new TLegend(0.281955, 0.257625, 0.537594, 0.504218,NULL,"brNDC");
        // else if (what.Contains("B_eta_dt_mcXs")) leg = new TLegend(0.686717, 0.67294, 0.942356, 0.901363,NULL,"brNDC");
        // else    
        if (what.Contains("chi2_PVSV_log2D")) {
            leg = new TLegend(0.192982, 0.666961, 0.551378, 0.856779, NULL,"brNDC");}
        else if (what.Contains("B_minChi2MuonsIPtoAnyPV")) {
            leg = new TLegend(0.192982,   0.648968,  0.551378,   0.867388, NULL,"brNDC");}
        else if (what.Contains("TMath::Abs(a_2D)")) {
            leg = new TLegend(0.7, 0.65, 0.85, 0.9, NULL,"brNDC");}
        // else leg = new TLegend(0.577694, 0.604764, 0.93609, 0.797181, NULL,"brNDC"); //xbl(0.71),ybl(0.62),xur(0.98),yur(0.98)
        else if (what.Contains("B_iso_7_Chi2_5_LoosePt05")) {
        leg = new TLegend(0.2, 0.65, 0.5, 0.85, NULL,"brNDC"); //xbl(0.71),ybl(0.62),xur(0.98),yur(0.98)
            }
        else leg = new TLegend(0.8, 0.55, 0.95, 0.75, NULL,"brNDC"); //xbl(0.71),ybl(0.62),xur(0.98),yur(0.98)


  } else{
        // if (what.Contains("Iso") || what.Contains("d0") || what.Contains("Eta") || what.Contains("eta") || what.Contains("DCA") || what.Contains("BDT")) leg = new TLegend(0.15,0.64,0.68,0.92,NULL,"brNDC"); //xbl,ybl,xur,yur //0.09
        // else if (what.Contains("DR")) leg = new TLegend(0.45,0.74,0.68,0.92,NULL,"brNDC");
        // // else leg = new TLegend(0.74,0.75,0.95,0.93,NULL,"brNDC"); //xbl(0.71,0.68),ybl(0.62),xur(0.98),yur(0.98)
        // else
        if (what.Contains("B_iso_7_Chi2_5_LoosePt05")) leg = new TLegend(0.179198, 0.756098, 0.502506, 0.879791,NULL,"brNDC"); //xbl(0.71,0.68),ybl(0.62),xur(0.98),yur(0.98)
        else if (what.Contains("Lxy")) leg = new TLegend(0.526316, 0.750871, 0.85213, 0.869338,NULL,"brNDC"); //xbl(0.71,0.68),ybl(0.62),xur(0.98),yur(0.98)
        else if (what.Contains("DR")) leg = new TLegend(0.526316, 0.750871, 0.85213, 0.869338,NULL,"brNDC"); //xbl(0.71,0.68),ybl(0.62),xur(0.98),yur(0.98)
        else if (what.Contains("chi2_PVSV_log2D")) leg = new TLegend(0.179198, 0.756098, 0.502506, 0.879791,NULL,"brNDC"); //xbl(0.71,0.68),ybl(0.62),xur(0.98),yur(0.98)
        else if (what.Contains("TMath::Abs(B_IDtrks_DCA)")) leg = new TLegend(0.530075, 0.756098, 0.857143, 0.867596,NULL,"brNDC"); //xbl(0.71,0.68),ybl(0.62),xur(0.98),yur(0.98)
        else leg = new TLegend(0.56015, 0.623693, 0.883459, 0.78223,NULL,"brNDC"); //xbl(0.71,0.68),ybl(0.62),xur(0.98),yur(0.98)
  }
  }else if (mode.EqualTo("mc_mc")){
    if (drawinlet){
    if (what.Contains("B_iso_7_Chi2_5_LoosePt05")) leg = new TLegend(0.517544, 0.291369 , 0.829574, 0.58209,NULL,"brNDC");
    else if (what.Contains("B_iso_Ntracks_7_Chi2_5_LoosePt05")) leg = new TLegend(0.281955, 0.260221, 0.537594, 0.504218 ,NULL,"brNDC");
    else if (what.Contains("B_IDtrks_deltaPhi")) leg = new TLegend(0.281955, 0.257625, 0.537594, 0.504218,NULL,"brNDC");
    // else if (what.Contains("B_eta_dt_mcXs")) leg = new TLegend(0.686717, 0.67294, 0.942356, 0.901363,NULL,"brNDC");
    else leg = new TLegend(0.672932, 0.579494, 0.928571, 0.89098, NULL,"brNDC"); //xbl(0.71),ybl(0.62),xur(0.98),yur(0.98)
  } else {
    if (what.Contains("Iso") || what.Contains("d0") || what.Contains("Eta") || what.Contains("eta") || what.Contains("DCA") || what.Contains("BDT")) leg = new TLegend(0.15,0.64,0.68,0.92,NULL,"brNDC"); //xbl,ybl,xur,yur //0.09
    else if (what.Contains("DR")) leg = new TLegend(0.45,0.74,0.68,0.92,NULL,"brNDC");
    else leg = new TLegend(0.547619, 0.54575, 0.880952, 0.85464,NULL,"brNDC"); //xbl(0.71,0.68),ybl(0.62),xur(0.98),yur(0.98)
  }

  }else {
  if (drawinlet && NumberOfTreesMC>1 && NumberOfTreesMC<5){
    if (what.Contains("Sqrt_pow_B_IDtrks_deltaEta_2_plus") || what.Contains("B_IDtrks_deltaEta") || what.Contains("B_IDtrks_DCA")|| what.Contains("d0Min_err")){
    leg = new TLegend(0.241855, 0.123719, 0.557644, 0.531957);
    NumberOfColumns = 1;
    }
    else if (what.Contains("chi2_PVSV_log2D") ){
        leg = new TLegend(0.209273, 0.435748, 0.52381, 0.843986);
        NumberOfColumns = 1;
      }
    else if (what.Contains("d0Min")) {
            NumberOfColumns = 1;
            if(ZoomVal == 0.2 && Zoom) leg = new TLegend(0.716792, 0.56316, 0.968672, 0.882989);
            else if(ZoomVal < 0.1 && Zoom) {
              leg = new TLegend(0.369674, 0.0899163, 0.81203, 0.329138);
              NumberOfColumns = 2;
            }
            else leg = new TLegend(0.719298, 0.529357, 0.969925, 0.851786);
      }
    else if (what.EqualTo("d0Max") ) {
      if((ZoomVal == 0.6 || ZoomVal == 0.3)  && Zoom) leg = new TLegend(0.241855, 0.0665141, 0.556391, 0.474752);//zoom legend
      else leg = new TLegend(0.373434, 0.0847158, 0.625313, 0.422747);
            NumberOfColumns = 1;
      }
    else if (what.Contains("B_iso_7_Chi2_5_LoosePt05")) leg = new TLegend(0.37594, 0.212128, 0.860902, 0.417546,NULL,"brNDC");
    else if (what.Contains("B_iso_Ntracks_7_Chi2_5_LoosePt05")  || what.Contains("B_IDtrks_deltaPhi") || what.Contains("a_2D")|| what.Contains("chi2_PVSV_log2D") || what.Contains("DR")) leg = new TLegend(0.226817, 0.152322, 0.677945, 0.362941 ,NULL,"brNDC");
    // else if (what.Contains("B_IDtrks_deltaPhi") ) leg = new TLegend(0.295739, 0.091499, 0.551378, 0.61843,NULL,"brNDC");
    // else if (what.Contains("B_pT")) leg = new TLegend(0.706767, 0.576898-0.05, 0.962406, 0.924724-0.03,NULL,"brNDC");
    // else if (what.Contains("a_2D") || what.Contains("chi2_PVSV_log2D") || what.Contains("DR")) leg = new TLegend(0.195489, 0.109669, 0.451128, 0.639195, NULL,"brNDC");
    // else if (what.Contains("Muon1_etcone30")) leg = new TLegend(0.706767, 0.576898-0.05, 0.962406, 0.924724-0.03,NULL,"brNDC");
    // else if (what.Contains("B_eta_dt_mcXs")) leg = new TLegend(0.176692, 0.595068, 0.676692, 0.911746 ,NULL,"brNDC");
    // else if (what.EqualTo("B_MUCALC_mass") || what.EqualTo("PRIVX_mu")){
    //   leg = new TLegend(0.406015, 0.659369, 0.932331, 0.877789, NULL,"brNDC");
    // }
    // else if (what.EqualTo("B_eta")){
    //   leg = new TLegend(0.362155, 0.722258, 0.968672, 0.878001, NULL,"brNDC");
    // }
    else if(Zoom && what.Contains("B_pT")){
        leg = new TLegend(0.659148, 0.555359, 0.942356, 0.882989);
        NumberOfColumns = 1;
      }
    else if (what.Contains("Muon1_etcone30")){
      leg = new TLegend(0.501253, 0.634004, 0.997494, 0.878001, NULL,"brNDC");
    }else if (what.Contains("B_PV_Ref_z") || what.Contains("B_pT") || what.Contains("Npv")) {
      leg = new TLegend(0.659148, 0.482552, 0.942356, 0.882989);
      NumberOfColumns = 1;
    }
        // 0.706767, 0.576898-0.05, 0.962406, 0.924724-0.03
    // else leg = new TLegend(0.695489, 0.26087, 0.997494, 0.850097, NULL,"brNDC"); //xbl(0.71),ybl(0.62),xur(0.98),yur(0.98)
    else leg = new TLegend(0.362155, 0.722258, 0.968672, 0.878001, NULL,"brNDC"); //xbl(0.71),ybl(0.62),xur(0.98),yur(0.98)
    leg->SetNColumns(NumberOfColumns);
  } 

  else if (drawinlet){
    if (what.Contains("B_iso_7_Chi2_5_LoosePt05")) leg = new TLegend(0.575188, 0.166775, 0.887218, 0.67294,NULL,"brNDC");
    else if (what.Contains("B_iso_Ntracks_7_Chi2_5_LoosePt05")) leg = new TLegend(0.281955, 0.125243, 0.537594, 0.610642 ,NULL,"brNDC");
    else if (what.Contains("B_IDtrks_deltaPhi") ) leg = new TLegend(0.295739, 0.091499, 0.551378, 0.61843,NULL,"brNDC");
    else if (what.Contains("B_pT")) leg = new TLegend(0.706767, 0.576898-0.05, 0.962406, 0.924724-0.03,NULL,"brNDC");
    else if (what.Contains("a_2D") || what.Contains("chi2_PVSV_log2D") || what.Contains("DR")) leg = new TLegend(0.195489, 0.109669, 0.451128, 0.639195, NULL,"brNDC");
    // else if (what.Contains("Muon1_etcone30")) leg = new TLegend(0.706767, 0.576898-0.05, 0.962406, 0.924724-0.03,NULL,"brNDC");
    // else if (what.Contains("B_eta_dt_mcXs")) leg = new TLegend(0.176692, 0.595068, 0.676692, 0.911746 ,NULL,"brNDC");
    else if (what.EqualTo("B_MUCALC_mass")){
      leg = new TLegend(0.404762, 0.641791, 0.931078, 0.903958, NULL,"brNDC");
      leg->SetNColumns(3);
      NumberOfColumns = 3;
    }
    // else if (what.EqualTo("B_eta")){
    //   leg = new TLegend(0.362155, 0.722258, 0.968672, 0.878001, NULL,"brNDC");
    //   leg->SetNColumns(3);
    //   NumberOfColumns = 3;
    // }
    else if (what.Contains("Muon1_etcone30")){
      leg = new TLegend(0.501253, 0.634004, 0.997494, 0.878001, NULL,"brNDC");
      leg->SetNColumns(2);
      NumberOfColumns = 2;
    }
        // 0.706767, 0.576898-0.05, 0.962406, 0.924724-0.03
    else leg = new TLegend(0.695489, 0.26087, 0.997494, 0.850097, NULL,"brNDC"); //xbl(0.71),ybl(0.62),xur(0.98),yur(0.98)
    leg->SetNColumns(NumberOfColumns*2);
  } 

  else {
    // if (what.Contains("Iso") || what.Contains("d0") || what.Contains("Eta") || what.Contains("eta") || what.Contains("DCA") || what.Contains("BDT")) leg = new TLegend(0.15,0.64,0.68,0.92,NULL,"brNDC"); //xbl,ybl,xur,yur //0.09
    // else if (what.Contains("DR")) leg = new TLegend(0.45,0.74,0.68,0.92,NULL,"brNDC");
    // else 
    leg = new TLegend(0.56015, 0.623693, 0.883459, 0.78223,NULL,"brNDC"); //xbl(0.71,0.68),ybl(0.62),xur(0.98),yur(0.98)
  }
}
  return leg;

}




// TLegend* defineLegendBox(TString what, Bool_t drawinlet){
//   TLegend* leg;
//   if (drawinlet){
//     if (what.Contains("Iso") || what.Contains("_iso_7") || what.Contains("_iso_5")) leg = new TLegend(0.14,0.74,0.64,0.94,NULL,"brNDC"); //xbl,ybl,xur,yur
//     else if (what.Contains("_iso_Ntracks")) leg = new TLegend(0.43,0.74,0.93,0.94,NULL,"brNDC");
//     else if (what.Contains("DR")) leg = new TLegend(0.39,0.72,0.89,0.92,NULL,"brNDC");
//     else if (what.Contains("Eta") || what.Contains("eta") || what.Contains("deltaPhi")) leg = new TLegend(0.12,0.22,0.62,0.42,NULL,"brNDC");
//     else if (what.Contains("lnChi2") || what.Contains("Chi2Muons") || what.Contains("chi2_PVSV") || what.Contains("SumMuTrackPixHits")) leg = new TLegend(0.17,0.74,0.67,0.94,NULL,"brNDC");
//     else if (what.Contains("BDT")) leg = new TLegend(0.12,0.66,0.85,0.82,NULL,"brNDC");
//     else leg = new TLegend(0.706767, 0.576898-0.05, 0.962406, 0.924724-0.03,NULL,"brNDC"); //xbl(0.71),ybl(0.62),xur(0.98),yur(0.98)
//     // else leg = new TLegend(0.45,0.74,0.95,0.94,NULL,"brNDC"); //xbl(0.71),ybl(0.62),xur(0.98),yur(0.98)
//     // else leg = new TLegend(0.497494,0.514601, 0.997494, 0.919533,NULL,"brNDC");
//   } else {
//     if (what.Contains("Iso") || what.Contains("d0") || what.Contains("Eta") || what.Contains("eta") || what.Contains("DCA") || what.Contains("BDT")) leg = new TLegend(0.15,0.64,0.68,0.92,NULL,"brNDC"); //xbl,ybl,xur,yur //0.09
//     else if (what.Contains("DR")) leg = new TLegend(0.45,0.74,0.68,0.92,NULL,"brNDC");
//     else leg = new TLegend(0.74,0.75,0.95,0.93,NULL,"brNDC"); //xbl(0.71,0.68),ybl(0.62),xur(0.98),yur(0.98)
//   }
//   return leg;
// }


TString getYAxisTitle(TString what) {
  TString yAxisTitle;
  if (what.Contains("JPsi")) {
    yAxisTitle = "J/#psi candidates";
  } else if (what.Contains("Mu") && !what.Contains("Mult")) {
    yAxisTitle = "#mu candidates";
  } else if (what.Contains("Kaon")) {
    yAxisTitle = "Kaon candidates";
  }  else if (what.Contains("d0")) {
    yAxisTitle = "#mu tracks";
  }
  else {
    yAxisTitle = "Events";
    //yAxisTitle = "B^{#pm} candidates"; 
    //yAxisTitle = "B_{s} candidates";
  }
  return yAxisTitle;
}
