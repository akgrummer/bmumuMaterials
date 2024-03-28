#include <TTree.h>
#include <TChain.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

void short_ex()
{
TTree *fChain;
vector <TChain*> chains;
TChain   *mainchain;


vector <string> filetreenames;
vector <string> treenames;

Double_t HT; // <- this is the variable that is loaded

filetreenames.push_back("TopViewAANtuple.root"); // <- change filename(s) here

treenames.clear();
treenames.push_back("EV0");  // <- change treename(s) here
treenames.push_back("Truth0");
treenames.push_back("CollectionTree");

 chains.push_back(new TChain(treenames[0].c_str()));
 for (int i=0; i < filetreenames.size(); i++) {
  chains[0]->Add(filetreenames[i].c_str());
  }

 mainchain = chains[0];

 for (int i=1 ; i < treenames.size(); i++) {
  cout << "new chains[" << i << "] = "<< treenames[i] << endl;
  chains.push_back( new TChain(treenames[i].c_str()));
  for (int j=0; j < filetreenames.size(); j++) {
   cout << "add filename[" << j << "]=" << filetreenames[j] << endl;
   chains[i]->Add(filetreenames[j].c_str());
   }
  cout << "Add Friend" << endl;
  mainchain->AddFriend((TTree*)chains[i],treenames[i].c_str());
  }
  
  fChain=(TTree*)mainchain;
 
// uncomment these blocks to get rid of error
//  fChain->Scan("EV0.HT"); 
//  fChain->Scan("Truth0.Truth_N");
//  fChain->Scan("CollectionTree.EventNumber");

fChain->SetBranchAddress("EV0.HT",&HT);

fChain->GetEntry(0);

cout << HT<< endl; // <- in my example the value is 324524.35
}
