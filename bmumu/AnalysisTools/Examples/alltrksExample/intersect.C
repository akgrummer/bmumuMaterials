#include <iostream>
#include <algorithm>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>

using namespace std;
set<ULong64_t> intersection(TString myFile1 = "", TString myFile2 = "") {

  ULong64_t en1, en2;
  set<ULong64_t> ens1;
  set<ULong64_t> ens2;

  // TFile* file1 = new TFile(myFile1);
  // TTree* tr1 = (TTree*)file1->Get("T_mv");
  TChain* tr1 = new TChain("T_mv");
  tr1->Add(myFile1);
  cout<< "Entries in original tree of file 1: "<< tr1->GetEntries() <<endl;
  tr1->SetBranchStatus("*", 0);
  tr1->SetBranchStatus("event_number", 1);
  tr1->SetBranchAddress("event_number", &en1);
  for (int ii = 0; ii < tr1->GetEntries(); ++ii)
    {
      tr1->GetEntry(ii);
      ens1.insert(en1);
    }
  // file1->Close();

  TChain* tr2 = new TChain("T_mv");
  tr2->Add(myFile2);
  cout<< "Entries in original tree of file 2: "<< tr2->GetEntries() <<endl;
  tr2->SetBranchStatus("*", 0);
  tr2->SetBranchStatus("event_number", 1);
  tr2->SetBranchAddress("event_number", &en2);
  for (int ii = 0; ii < tr2->GetEntries(); ++ii)
    {
      tr2->GetEntry(ii);
      ens2.insert(en2);
    }
    // tr2->Close();

  set<ULong64_t> intersect;
  set_intersection(ens1.begin(), ens1.end(), ens2.begin(), ens2.end(),
		   std::inserter(intersect, intersect.begin()));
  cout << "# of unique events in file 1: "<< ens1.size() << endl
  << "# of unique events in file 2: "<< ens2.size() << endl
  << "intersection of both: "<< intersect.size() << endl;  
  
  set<ULong64_t> uni;
  set_union(ens1.begin(), ens1.end(), ens2.begin(), ens2.end(), std::inserter(uni, uni.begin()));
  cout << "Union of both: "<< uni.size() << endl;

  set<ULong64_t> dif1;
  set_difference(ens1.begin(), ens1.end(), ens2.begin(), ens2.end(), std::inserter(dif1, dif1.begin()));
  set<ULong64_t> dif2;
  set_difference(ens2.begin(), ens2.end(), ens1.begin(), ens1.end(), std::inserter(dif2, dif2.begin()));
  cout << "Only in first: "<< dif1.size() << endl
  << " only in second: "<< dif2.size() << endl
  << " sum of both: " << dif1.size() + dif2.size() << endl;

 return  intersect;
}
void intersect(){
  // number of 
  // const bool is_in = ens1.find(1451998596) != ens1.end();
  // if (ens1.find(1451998596) != ens1.end()){
  //   cout<< "1451998596 is in ens1 (bool2)"<<endl;
  // }

  // cout<<"first event number in ens1 "<< ens1.begin() <<endl;
    // TString myFile1 = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal1/final_ntup/data17/Bmumu/v5/LASTskim.data17_run339849.Bmumu.Allv5.root";
    // TString myFile2 = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/final_ntup/data17_00339849/Bmumu/v1/*.root";
    TString indir1 = "/eos/home-a/agrummer/BsmumuData/2020nTuples/FinalSkim/v1/";
    TString indir2 = "/eos/home-a/agrummer/BsmumuData/FinalSkim/v6/";
    TString myYear = "2017";
    TString myFile1 = indir1+myYear+"/*.root";
    // myFile1 += myYear;
    // myFile1 +="/*_2020Feb11.root";
    TString myFile2 = indir2+myYear+"/*.root";
    set<ULong64_t> intersect;
  intersect = intersection(myFile1, myFile2);
  ULong64_t en1, en2;
  set<ULong64_t> ens1;
  set<ULong64_t> ens2;
  TChain* tr2 = new TChain("T_mv");
  tr2->Add(myFile2);
  cout<< " Entries in original tree of file 2 (again): "<< tr2->GetEntries() <<endl;
  tr2->SetBranchStatus("*", 0);
  tr2->SetBranchStatus("event_number", 1);
  tr2->SetBranchAddress("event_number", &en2);
  for (int ii = 0; ii < tr2->GetEntries(); ++ii)
    {
      tr2->GetEntry(ii);
      ens2.insert(en2);
    }
    // tr2->Close();

  Int_t cnt(0);
  for (int ii = 0; ii < tr2->GetEntries(); ++ii)
    {
      tr2->GetEntry(ii);
        // if (ens1.find(en2) != ens1.end()){
        if (intersect.count(en2)){
            // cout<< "1451998596 is in ens1 (bool2)"<<endl;
            cnt++;
        }
        // if (ii ==2) cout<<"3rd en2: "<<en2<<endl;
      // ens2.insert(en2);
    }
cout<< "number of en2 in the intersect set: "<< cnt<<endl;
// cout<< "number of en2 in the ens1 set: "<< cnt<<endl;


  // set<ULong64_t> uni;
  // set_union(ens1.begin(), ens1.end(), ens2.begin(), ens2.end(), std::inserter(uni, uni.begin()));
  // cout << "Union of both: "<< uni.size() << endl;

  // set<ULong64_t> dif1;
  // set_difference(ens1.begin(), ens1.end(), ens2.begin(), ens2.end(), std::inserter(dif1, dif1.begin()));
  // set<ULong64_t> dif2;
  // set_difference(ens2.begin(), ens2.end(), ens1.begin(), ens1.end(), std::inserter(dif2, dif2.begin()));
  // cout << "Only in first: "<< dif1.size() << " only in second: "<< dif2.size() << " sum of both: " << dif1.size() + dif2.size() << endl;

}
