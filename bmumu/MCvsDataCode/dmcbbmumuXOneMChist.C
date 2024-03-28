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
//

#include "dmcbbmumuX.h"
using namespace std;


ofstream ofiletex(tabname);
TFile *fout = new TFile(ofilename,"RECREATE");

//store bkg fit data
bkg nbkgInfo;

//==========Forward declaration of functions===========

void compare(VariableInfo, TString, vector <TChain*>,vector <TString>, TTree*, TString, TString, bool, bool drawResiduals=true);
TH1F* getHistoFromTree(TTree*, VariableInfo, const char*, TCut);
TLegend* defineLegendBox(TString what, TString mode, Bool_t drawinlet);
TString getYAxisTitle(TString);

// void dmcbbmumuX(TString compVar="", TString compMode="",const char period[] = "", Bool_t verbose=true)
void dmcbbmumuX(TString compVar="", TString compMode="", Bool_t verbose=true, TString period = "")
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
else if (compMode.EqualTo("dt_mcXs_Mult")) FileNames = {fdnameMain, fdnameMWD}; //takes multiple files
else if (compMode.EqualTo("mc_mc")) FileNames = {fmname2}; //takes multiple files
else if (compMode.EqualTo("dt_mc_OnePeriod")) FileNames = {fdnameSP2015M}; //takes only one file

TString mclabel="MC16 bb #rightarrow #mu#muX";

  //===========Make connections to tree's of two flat ntuple files=================================

// NumberOfTrees.push_back(0);//let first entry be zero for the loop below which adds the file based of tree index

if (compMode.EqualTo("dt_mc_SepPeriods")){
  for (int FileIdx=0; FileIdx<FileNames.size(); FileIdx++){

    if (FileNames[FileIdx].Contains("2016") && FileNames[FileIdx].Contains("2015")) DataYear = "";
    else{
        if (FileNames[FileIdx].Contains("2016")) DataYear = " 2016";
        else if (FileNames[FileIdx].Contains("2015")) DataYear = " 2015";
        else DataYear = "";
        if (FileNames[FileIdx].Contains("MainWithDelayed")) DataYear += " MWD";
        else if (FileNames[FileIdx].Contains("Main")) DataYear += " Main";
    }
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
}
else {
  cout << "Choose a valid compMode. Exiting. "<< endl;
  return(0);
}
// TChain* td = chains[0];
  // TChain* td = new TChain(fdtreename);//TChain uses the name of the tree (same tree name in every file that is added)
  // td->Add(fdname);//Added one file that includes a tree with name in fdtreename
  TChain* tm = new TChain(fmtreename);
  tm->Add(fmname);

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
      compare(Variables[i], Modes[j], chains, treenames, tm, dtlabel, mclabel, true, true);
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
    else if (tmpDummy.Contains("eta") || tmpDummy.Contains("Eta")) hret = new TH1F(*hdummyEta);
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
  cout << "Creating histo, title "<< hname <<", hret integral.."<< hret->Integral() <<endl; //cut out over- and unerflows
  cout << endl;
  return hret;
} // end of getHistoFromTree function

void compare(VariableInfo Variable, TString mode, vector <TChain*> chains, vector <TString> treenames, TTree* tm, TString dtlabel, TString mclabel, bool normalize, bool drawResiduals)
{
  bool arbitraryUnits = true;
    // int m(1);
  int NumberOfTrees = treenames.size();
  cout<<"The number of trees to compare: "<<NumberOfTrees<<endl;
    TH1F** histogram = new TH1F*[NumberOfTrees];//vector of histograms size of number of trees
    TH1F* h2(NULL);//initialize MC historgram
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
  TString h1titledummy = h1title;

  TString h2title(h1title);
  TString htitle(h1title);
  TString hdivtitle(h1title);

  TString axLab = Variable.axLabel;
  TString yAxisTitle = getYAxisTitle(Variable.name);


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
    if(h1title.Contains("Muon1")){
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
    } 
    h2title+="_mc16_2015Trigger";
    if(h2title.Contains("Muon1")){
    h2 = getHistoFromTree(tm, Variable, h2title, CutAdd*"PVWeights*Muon1_reco_eff_sf");
    }else if (h2title.Contains("Muon2")){
    h2 = getHistoFromTree(tm, Variable, h2title, CutAdd*"PVWeights*Muon2_reco_eff_sf");
    }else if (h2title.Contains("B")){
    h2 = getHistoFromTree(tm, Variable, h2title, CutAdd*"PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf");
    }else{
    // h2 = getHistoFromTree(tm, Variable, h2title, CutAdd*"testweight");//added with addWeight.C code
    h2 = getHistoFromTree(tm, Variable, h2title, CutAdd*"PVWeights");
    }
  } else if (mode.EqualTo("dt_mcXs") ||mode.EqualTo("dt_mcXs_Mult") || mode.EqualTo("dt_mc_SepPeriods") || mode.EqualTo("dt_mc_OnePeriod")) {
    h1title+="_dt16";
    for (int i=0;i<NumberOfTrees;i++) {
    h1title+="_";
    h1title+=treenames[i];
    histogram[i] = getHistoFromTree(chains[i], Variable, h1title, CutAdd);
    h1title = h1titledummy;
    h1title+="_dt16";
    } 
    h2title+="_mcX";
    if(h2title.Contains("Muon1")){
    h2 = getHistoFromTree(tm, Variable, h2title, CutAdd*"PVWeights*Muon1_reco_eff_sf*testweight");
    }else if (h2title.Contains("Muon2")){
    h2 = getHistoFromTree(tm, Variable, h2title, CutAdd*"PVWeights*Muon2_reco_eff_sf*testweight");
    }else if (h2title.Contains("B")){
    h2 = getHistoFromTree(tm, Variable, h2title, CutAdd*"PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf*testweight");
    // }else if (h2title.Contains("closeTrkDOCA")){
    // h2 = getHistoFromTree(tm, {"closeTrkDOCA",40,0,2,true,"DOCA_{xtrk, loose, pt>0.5} [mm]",false}, h2title, CutAdd*"PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf*testweight");
    }else{
    // h2 = getHistoFromTree(tm, Variable, h2title, CutAdd*"testweight");//added with addWeight.C code
    h2 = getHistoFromTree(tm, Variable, h2title, CutAdd*"PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf*testweight");
    }
  } 
//----------------------Select Max Data histogram to normalize to and plot against----------------
vector <float> elements;
Double_t maxHisto;
int maxinteger;
if (NumberOfTrees>1){
for (int i=0;i<NumberOfTrees;i++){
  elements.push_back(histogram[i]->GetMaximum());
}
// float maxHisto;
maxHisto = *max_element(elements.begin(), elements.end());
int maxinteger;
for (int i=0;i<NumberOfTrees;i++){
  if (maxHisto == histogram[i]->GetMaximum()) maxinteger = i;
}
}//end of numberoftrees if statement
else{maxinteger = 0;}
//------------------------------------------------------------------------

  //  h2->SetFillStyle(3004);
  if (Variable.nbins>0 && Variable.XMin!= Variable.XMax) {
    histogram[maxinteger]->GetXaxis()->SetRangeUser(Variable.XMin,Variable.XMax);
    if (h2) h2->GetXaxis()->SetRangeUser(Variable.XMin,Variable.XMax);
  }
  else if (Variable.nbins!=-1) { 
    if (h2) h2->GetXaxis()->Set(histogram[maxinteger]->GetXaxis()->GetNbins(),histogram[maxinteger]->GetXaxis()->GetXmin(),histogram[maxinteger]->GetXaxis()->GetXmax());
  }
  if (normalize) {
    //typically means normalize MC(h2) to data (histogram[maxinteger])
    //
    cout << endl;
    cout << "INFO Integral of entries of each histo BEFORE normalization: " << endl;
    cout << histogram[maxinteger]->GetTitle() <<": "<< histogram[maxinteger]->Integral();
    if (h2) cout << " "<< h2->GetTitle()<< ": "<< h2->Integral();
    cout << endl;
    cout << endl;
    
  //   h2->Scale(histogram[maxinteger]->Integral()/h2->Integral()); // ATTENTION under- and over-flows not taken into account!!!  
  // for (int i=0;i<NumberOfTrees;i++) {
  //   if (i != maxinteger) histogram[i]->Scale(histogram[maxinteger]->Integral()/histogram[i]->Integral());
  // }
  if (arbitraryUnits) h2->Scale(1/h2->Integral());
  if(h1title.Contains("B") && h1title.Contains("mass") && Variable.nbins == 60){
      for (int i=0;i<NumberOfTrees;i++) {
      histogram[i]->Scale((h2->Integral()-h2->Integral(19,39))/(histogram[i]->Integral() - histogram[i]->Integral(19,39)));
      }
    }
  else{
      for (int i=0;i<NumberOfTrees;i++) {
        histogram[i]->Scale(h2->Integral()/histogram[i]->Integral());
      }//
    }

  }//end of normalize for loop

  // TString axLab = Variable.axLabel;
  histogram[maxinteger]->GetXaxis()->SetTitle(axLab);
  if (h2) {
    h2->GetXaxis()->SetTitle(axLab);
  }

  if (drawResiduals) {
    histogram[maxinteger]->GetYaxis()->SetTitleOffset(0.7); //0.57
    histogram[maxinteger]->GetYaxis()->SetTitleSize(0.08);
    if (h2) {
      h2->GetYaxis()->SetTitleOffset(0.7); //0.57
      h2->GetYaxis()->SetTitleSize(0.08);
    }
  }
  else {
    histogram[maxinteger]->GetYaxis()->SetTitleOffset(0.72);
    histogram[maxinteger]->GetYaxis()->SetTitleSize(0.07);
    if (h2) {
      h2->GetYaxis()->SetTitleOffset(0.72);
      h2->GetYaxis()->SetTitleSize(0.07);
    }
  }
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
  histogram[maxinteger]->GetYaxis()->SetTitle("a.u.");
  if (h2) h2->GetYaxis()->SetTitle("a.u.");
}
else{
  histogram[maxinteger]->GetYaxis()->SetTitle(yAxisTitle);
  if (h2) h2->GetYaxis()->SetTitle(yAxisTitle); 
}
  Double_t chi2_1(0.),ks1(0.);
  Int_t ndf_1(0), igood_1(0);
 
//Add to Latex Table to include ks1 and chi2/ndf 
  if (h2) {
    for (int i=0;i<NumberOfTrees;i++){
        histogram[i]->Chi2TestX(h2,chi2_1,ndf_1,igood_1,"WW P"); //Weighted Weighted Print
        ks1 = histogram[i]->KolmogorovTest(h2);
        TString tabentry(Variable.axLabel);
        if (tabentry.Contains("DeltaR")) tabentry.ReplaceAll("DeltaR","Delta~R");
        char buf[20];
        sprintf(buf,"%5.1f/%3d",chi2_1,ndf_1);
        tabentry.ReplaceAll('#','\\');
        // tabentry.Append(' Period');
        TString treenamesdummy = treenames[i];
        if (treenamesdummy.Contains("T_mv_")) treenamesdummy.ReplaceAll("T_mv_"," Period ");
        else if(treenamesdummy.Contains("T_mv"))  treenamesdummy.ReplaceAll("T_mv","");
       if (mode.EqualTo("dt_mc_SepPeriods") || mode.EqualTo("dt_mcXs_Mult")) ofiletex << treenamesdummy << " & " << "$"<< tabentry <<"$" << " & "<< ks1 << " & "<< buf << "\\\\\n\\hline\n";
       else ofiletex << "$"<< tabentry <<"$" << " & "<< ks1 << " & "<< buf << "\\\\\n\\hline\n";
     }
  }
// }//end histo for loop 2
  TPad *pad1, *pad2;
  pad1 = new TPad("pad1","pad1",0,0.33,1,1); //xlow ylow xup yup
  pad2 = new TPad("pad2","pad2",0,0,1,0.33); //0.3

  if (drawResiduals) {
    pad1->SetMargin(0.12,0.05,0.028,0.09);
    pad1->SetBorderMode(0);
    if (Variable.logScale) pad1->SetLogy();
    if (h2) {
      pad2->SetMargin(0.12,0.05,0.38,0.06);
      pad2->SetBorderMode(0);
      pad1->Draw();
      pad2->Draw();
      pad1->cd();
    }
  }
gStyle->SetPalette(77);

for (int i=0;i<NumberOfTrees;i++) {
// for (int i=0;i<NumberOfTrees;i++) {
  histogram[i]->SetLineWidth(2);        
  //histogram[0]->SetFillColor(0);        
  //histogram[0]->SetLineColor(kBlack);  
  histogram[i]->SetLineStyle(1);        
  histogram[i]->SetMarkerSize(0.8);     
  histogram[i]->SetMarkerStyle(20 + i); //different marker style for each histogram
  }    
  // histogram[0]->SetMarkerColor(kBlack);
  if (h2) h2->SetLineWidth(2);
  if (h2) h2->SetFillColor(0);//kRed);/*30*/
  if (h2) h2->SetFillColor(0);//kRed);/*30*/
  if (h2) h2->SetFillColor(0);//kRed);/*30*/ 
 if (h2) h2->SetLineColor(kGreen+2);   
if (h2) h2->SetLineStyle(1);/*22*/
 if (h2) h2->SetMarkerSize(0.8);
  if (h2) h2->SetMarkerStyle(25);   
  if (h2) h2->SetMarkerColor(kGreen+2);
  if (h2) h2->SetFillStyle(3002);
  //if (h2) h2->SetMarkerSize(0);

// auto elements = { histogram[0]->GetMaximum(), number4, number5, number6 };


//---------------------Draw the Histograms: --------------------
  if (h2 && h2->GetMean()!=0 && h2->GetRMS()!=0) {
    histogram[maxinteger]->GetYaxis()->SetLabelSize(0.08);
    histogram[maxinteger]->GetXaxis()->SetNoExponent();
    h2->GetYaxis()->SetLabelSize(0.08);
    h2->GetXaxis()->SetNoExponent();
    histogram[maxinteger]->GetXaxis()->SetLabelOffset(0.028); //0.07
    h2->GetXaxis()->SetLabelOffset(0.028); //0.07
    histogram[maxinteger]->GetXaxis()->SetTitle("");
    h2->GetXaxis()->SetTitle("");
    cout << histogram[maxinteger]->GetMaximum() <<" <=h1max|h2max-> "<<h2->GetMaximum()<< endl;
    if (histogram[maxinteger]->GetMaximum()>h2->GetMaximum()) {
      histogram[maxinteger]->SetMaximum(histogram[maxinteger]->GetMaximum()*1.5);
      histogram[maxinteger]->Draw("ep PLC PMC PFC");
      // histogram[maxinteger]->Draw("epsame");
      h2->Draw("histsame");
      // if(!histogram[maxinteger]->GetFillColor()) histogram[maxinteger]->Draw("epsame");
    } else {
      h2->SetMaximum(h2->GetMaximum()*1.5);
      h2->Draw("hist");
      // h2->Draw("histsame");
      histogram[maxinteger]->Draw("epsame PLC PMC PFC");
    }
  } else {
    histogram[maxinteger]->Draw("ep PLC PMC PFC");
  }

for (int i=0;i<NumberOfTrees;i++) {
  if (i != maxinteger) histogram[i]->Draw("epsame PLC PMC PFC");
}
//---------------------//---------------------//---------------------

  htitle+="_";
  htitle+=mode;

  TLegend *leg = defineLegendBox(Variable.name, mode,  drawResiduals);
  leg->SetBorderSize(0);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetTextFont(132);
//    leg->SetMargin(0.2);//Aidan
TString dtlabeldummy = dtlabel;
TString mclabeldummy = mclabel;

  if (h2) {
    if (mode.Contains("dtbgsub_mcrew")) {
      leg->AddEntry(histogram[maxinteger],"Background-subtracted data run 302393","p"); //FIXMELEGEND
      leg->AddEntry(h2,"B^{+}#rightarrow J/#psi K^{+} MC15","l"); 
    } else {
      // dtlabel+=treenames[maxinteger];
      // if (dtlabel.Contains("T_mv_")) dtlabel.ReplaceAll("T_mv_"," Period ");
      // dtlabel+=" (A)";
      // leg->AddEntry(histogram[maxinteger],dtlabel,"elp");
      for (int i=0;i<NumberOfTrees;i++) {
        dtlabel = dtlabeldummy;
        dtlabel+=treenames[i];
        // dtlabel+=DataYear;
        if (dtlabel.Contains("T_mv_")) dtlabel.ReplaceAll("T_mv_"," Period ");
        else if(dtlabel.Contains("T_mv"))  dtlabel.ReplaceAll("T_mv"," ALL Periods");
        // if (i != maxinteger) leg->AddEntry(histogram[i],dtlabel,"elp");
        // if (i == maxinteger) dtlabel+=" (A)";
        if(mode.Contains("mc_mc")){
          mclabeldummy+="2015 Trigger";
          mclabel+="2016 Trigger";
        leg->AddEntry(histogram[i],mclabeldummy,"elp");
        }else{
        leg->AddEntry(histogram[i],dtlabel,"elp");
        }
      }
      // mclabel+=" (B)";
      leg->AddEntry(h2,mclabel,"elp");
    }
  }

  // if (treenames[i].Contains("T_mv_")) treenames[i].ReplaceAll("T_mv_","Period_");
 
  leg->Draw();


TH1F** hres = new TH1F*[NumberOfTrees];

  bool drawResError = true;
  if (drawResiduals) {
    for (int i=0;i<NumberOfTrees;i++) {
    pad2->cd();
    hres[i] = (TH1F*)histogram[i]->Clone("hres");
    cout << "Before plotting" << endl;
    hres[i]->SetMarkerSize(0.7);
    hres[i]->GetXaxis()->SetTitleOffset(1.0); //0.95
    hres[i]->GetXaxis()->SetTitle(axLab);
    hres[i]->GetXaxis()->SetTitleSize(0.17);
    hres[i]->GetXaxis()->SetLabelSize(0.15); //0.17 0.1
    hres[i]->GetXaxis()->SetRangeUser(Variable.XMin,Variable.XMax);
    
    hres[i]->GetYaxis()->SetTitleSize(0.17);
    hres[i]->GetYaxis()->SetTitleOffset(0.32); //0.26
    // if (mode.Contains("dtbgsub_mcrew")) hres->GetYaxis()->SetTitle("Data/MC"); //FIXMELEGEND
    // else hres->GetYaxis()->SetTitle("A/B");
    hres[i]->GetYaxis()->SetTitle("Data/MC");
    hres[i]->GetYaxis()->SetLabelSize(0.12);//0.17 //0.08
    hres[i]->GetYaxis()->SetNdivisions(4,3,0); //4,5,0
    
    // cout << "DEBUG " << " bin2 content: "<<histogram[maxinteger]->GetBinContent(2) << " error: "<< histogram[maxinteger]->GetBinError(2) << endl;
    // if (h2) cout << "DEBUG " << " bin2 content: "<<h2->GetBinContent(2) << " error: "<< h2->GetBinError(2) << endl;
    // cout << "DEBUG " << " bin4 content: "<<histogram[maxinteger]->GetBinContent(4) << " error: "<< histogram[maxinteger]->GetBinError(4) << endl;
    // if (h2) cout << "DEBUG " << " bin4 content: "<<h2->GetBinContent(4) << " error: "<< h2->GetBinError(4) << endl;
    
    hres[i]->Sumw2();
    
    hres[i]->Divide(histogram[i],h2,1.0,1.0); //RATIO
    // if(htitle.Contains("B_MUCALC_mass") || htitle.Contains("d0Min") || htitle.Contains("d0Max")){
    if(htitle.Contains("B_MUCALC_mass")){
      cout<<"DEBUG"<<" Aidan"<<endl;
    hres[i]->GetYaxis()->SetRangeUser(0.85,1.15);
    }else{
    hres[i]->GetYaxis()->SetRangeUser(0., 3.5);//0,2);//0.55,1.75); //
    }

    // if (i == 0) hres[0]->Draw("");
    hres[i]->Draw("epsame PLC PMC PFC");
  }
    
    //Dotted line on lower pad at ratio = 1
    TLine *l = new TLine(histogram[maxinteger]->GetXaxis()->GetXmin(),1,histogram[maxinteger]->GetXaxis()->GetXmax(),1);
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
  }

  fout->cd();
  
  histogram[maxinteger]->SetTitle("dataSR");
  histogram[maxinteger]->SetName("dataSR");


//Not sure what hdiv->Write() is used for - did not correct for seperate periods
  if (h2) {
    // create histogram with data/MC ratios
    //
    h2->SetName("dataSB");
    h2->SetTitle("dataSB");
  
    TH1F* hdiv =(TH1F*)histogram[maxinteger]->Clone("hdiv");
    hdivtitle  = Variable.name;
    hdivtitle+="_div_data_by_mc";
    hdiv->Sumw2();
    hdiv->Divide(histogram[maxinteger],h2,1.0/histogram[maxinteger]->Integral(),1.0/h2->Integral());//this = c1*h1/(c2*h2), Divide(h1,h2,c1,c2)
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
    c1->SaveAs(outpath+htitle+".pdf");
  //c1->SaveAs(outpath+htitle+".eps");
  //
  //
  /*
  c1->SaveAs(outpath+htitle+".C");
  c1->SaveAs(outpath+htitle+".root");
  c1->SaveAs(outpath+htitle+".gif");
  */
    // for (int i=0;i<NumberOfTrees;i++) {histogram[i]->Write();}
  

  // c1->Write();
  // c1->Write(htitle);


  // delete histogram[0];
  for (int i=0;i<NumberOfTrees;i++) { delete histogram[i];}
  delete h2;
  delete pad2;
  delete pad1;
  delete c1;

} //end of compare function

void atlasLabel(Double_t x,Double_t y, bool drawRes = true, bool Preliminary=true,Color_t color=1, bool drawLumi=false, bool enlarge=false)
{
  double delx = 0.115*696*gPad->GetWh()*3/(5*472*gPad->GetWw());
  double textsize;
  double dy = 0.065;
  if (!drawRes) {
    delx+=0.02;
    textsize = 0.040;
  } else {
    if (enlarge) {
      textsize = 0.075; 
      delx+=0.04;
      dy = 0.125;
    }
    else textsize = 0.045;
  }
  TLatex *tex = new TLatex(x,y,"ATLAS");
  tex->SetNDC();
  tex->SetTextSize(textsize);
  tex->SetTextFont(72);
  tex->SetLineWidth(2);
  tex->SetTextColor(color);
  tex->Draw();
  if (Preliminary) {
    tex = new TLatex(x+delx,y,"for approval"); //Preliminary
    tex->SetNDC();
    tex->SetTextSize(textsize);
    tex->SetTextFont(42); //42
    tex->SetLineWidth(2);
    tex->SetTextColor(color);
    tex->Draw();
  }
  tex = new TLatex(x+0.02,y-dy,"#sqrt{s} = 7 TeV");
  tex->SetNDC();
  tex->SetTextSize(textsize);
  tex->SetTextFont(42);
  tex->SetLineWidth(2);
  tex->SetTextColor(color);
  tex->Draw();
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

TLegend* defineLegendBox(TString what, TString mode, Bool_t drawinlet){

  TLegend* leg;
  if (mode.EqualTo("dt_mcXs") || mode.EqualTo("dt_mcXs_Mult") || mode.EqualTo("dt_mc_OnePeriod")){
    if (drawinlet){
    if (what.Contains("B_iso_7_Chi2_5_LoosePt05")) leg = new TLegend(0.517544, 0.291369 , 0.829574, 0.58209,NULL,"brNDC");
    else if (what.Contains("B_iso_Ntracks_7_Chi2_5_LoosePt05")) leg = new TLegend(0.281955, 0.260221, 0.537594, 0.504218 ,NULL,"brNDC");
    else if (what.Contains("B_IDtrks_deltaPhi")) leg = new TLegend(0.281955, 0.257625, 0.537594, 0.504218,NULL,"brNDC");
    else if (what.Contains("B_eta_dt_mcXs")) leg = new TLegend(0.686717, 0.67294, 0.942356, 0.901363,NULL,"brNDC");
    else leg = new TLegend(0.672932, 0.579494, 0.928571, 0.89098, NULL,"brNDC"); //xbl(0.71),ybl(0.62),xur(0.98),yur(0.98)
  } else {
    if (what.Contains("Iso") || what.Contains("d0") || what.Contains("Eta") || what.Contains("eta") || what.Contains("DCA") || what.Contains("BDT")) leg = new TLegend(0.15,0.64,0.68,0.92,NULL,"brNDC"); //xbl,ybl,xur,yur //0.09
    else if (what.Contains("DR")) leg = new TLegend(0.45,0.74,0.68,0.92,NULL,"brNDC");
    else leg = new TLegend(0.74,0.75,0.95,0.93,NULL,"brNDC"); //xbl(0.71,0.68),ybl(0.62),xur(0.98),yur(0.98)
  }

  }else if (mode.EqualTo("mc_mc")){
    if (drawinlet){
    if (what.Contains("B_iso_7_Chi2_5_LoosePt05")) leg = new TLegend(0.517544, 0.291369 , 0.829574, 0.58209,NULL,"brNDC");
    else if (what.Contains("B_iso_Ntracks_7_Chi2_5_LoosePt05")) leg = new TLegend(0.281955, 0.260221, 0.537594, 0.504218 ,NULL,"brNDC");
    else if (what.Contains("B_IDtrks_deltaPhi")) leg = new TLegend(0.281955, 0.257625, 0.537594, 0.504218,NULL,"brNDC");
    else if (what.Contains("B_eta_dt_mcXs")) leg = new TLegend(0.686717, 0.67294, 0.942356, 0.901363,NULL,"brNDC");
    else leg = new TLegend(0.672932, 0.579494, 0.928571, 0.89098, NULL,"brNDC"); //xbl(0.71),ybl(0.62),xur(0.98),yur(0.98)
  } else {
    if (what.Contains("Iso") || what.Contains("d0") || what.Contains("Eta") || what.Contains("eta") || what.Contains("DCA") || what.Contains("BDT")) leg = new TLegend(0.15,0.64,0.68,0.92,NULL,"brNDC"); //xbl,ybl,xur,yur //0.09
    else if (what.Contains("DR")) leg = new TLegend(0.45,0.74,0.68,0.92,NULL,"brNDC");
    else leg = new TLegend(0.547619, 0.54575, 0.880952, 0.85464,NULL,"brNDC"); //xbl(0.71,0.68),ybl(0.62),xur(0.98),yur(0.98)
  }

  }else{
  if (drawinlet){
    if (what.Contains("B_iso_7_Chi2_5_LoosePt05")) leg = new TLegend(0.575188, 0.166775, 0.887218, 0.67294,NULL,"brNDC");
    else if (what.Contains("B_iso_Ntracks_7_Chi2_5_LoosePt05")) leg = new TLegend(0.281955, 0.125243, 0.537594, 0.610642 ,NULL,"brNDC");
    else if (what.Contains("B_IDtrks_deltaPhi") ) leg = new TLegend(0.295739, 0.091499, 0.551378, 0.61843,NULL,"brNDC");
    else if (what.Contains("B_pT")) leg = new TLegend(0.706767, 0.576898-0.05, 0.962406, 0.924724-0.03,NULL,"brNDC");
    else if (what.Contains("a_2D") || what.Contains("chi2_PVSV_log2D") || what.Contains("DR")) leg = new TLegend(0.195489, 0.109669, 0.451128, 0.639195, NULL,"brNDC");
    // else if (what.Contains("Muon1_etcone30")) leg = new TLegend(0.706767, 0.576898-0.05, 0.962406, 0.924724-0.03,NULL,"brNDC");
    else if (what.Contains("B_eta_dt_mcXs")) leg = new TLegend(0.176692, 0.595068, 0.676692, 0.911746 ,NULL,"brNDC");
    else if (what.EqualTo("B_MUCALC_mass")){
      leg = new TLegend(0.404762, 0.641791, 0.931078, 0.903958, NULL,"brNDC");
      leg->SetNColumns(3);
    }
    else if (what.EqualTo("B_eta")){
      leg = new TLegend(0.362155, 0.722258, 0.968672, 0.878001, NULL,"brNDC");
      leg->SetNColumns(3);
    }
    else if (what.Contains("Muon1_etcone30")){
      leg = new TLegend(0.501253, 0.634004, 0.997494, 0.878001, NULL,"brNDC");
      leg->SetNColumns(2);
    }


        // 0.706767, 0.576898-0.05, 0.962406, 0.924724-0.03
    else leg = new TLegend(0.695489, 0.26087, 0.997494, 0.850097, NULL,"brNDC"); //xbl(0.71),ybl(0.62),xur(0.98),yur(0.98)
  } else {
    if (what.Contains("Iso") || what.Contains("d0") || what.Contains("Eta") || what.Contains("eta") || what.Contains("DCA") || what.Contains("BDT")) leg = new TLegend(0.15,0.64,0.68,0.92,NULL,"brNDC"); //xbl,ybl,xur,yur //0.09
    else if (what.Contains("DR")) leg = new TLegend(0.45,0.74,0.68,0.92,NULL,"brNDC");
    else leg = new TLegend(0.74,0.75,0.95,0.93,NULL,"brNDC"); //xbl(0.71,0.68),ybl(0.62),xur(0.98),yur(0.98)
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
