
TFile *_file0 = TFile::Open("user.ibragimo.17073931.Bmumu._000001_skimmed.root")

TFile *_file0 = TFile::Open("user.ibragimo.20649270.Bmumu._000003.root")

typedef map<string, int>      map_str_int;
map_str_int *HLT_trigger = 0;
map_str_int *L1_trigger = 0;
T_mv->SetBranchAddress("HLT_trigger",&HLT_trigger);
T_mv->SetBranchAddress("L1_trigger",&L1_trigger);
// T_mv->GetEntry(4);

//cout<<HLT_trigger->end()<<endl;

//cout<<HLT_trigger->find("HLT_mu6_mu4_bBmumu")->second<<endl;

bool myCheckHLT;
map_str_int CountingMapHLT;
CountingMapHLT["InitialFAKE"]=1;
for (int i = 0; i<= T_mv->GetEntries(); ++i){
T_mv->GetEntry(i);
for(map<string, int >::const_iterator it = HLT_trigger->begin();it != HLT_trigger->end(); ++it){
// std::cout << it->first << " " << it->second << "\n";
//CountingMapHLT[it->first]=1;
myCheckHLT = CountingMapHLT.find(it->first) != CountingMapHLT.end();
if(myCheckHLT){CountingMapHLT[it->first]+=1;}
else{CountingMapHLT[it->first]=1;}
}
}

bool myCheckL1;
map_str_int CountingMapL1;
CountingMapL1["InitialFAKE"]=1;
for (int i = 0; i<= T_mv->GetEntries(); ++i){
T_mv->GetEntry(i);
for(map<string, int >::const_iterator it = L1_trigger->begin();it != L1_trigger->end(); ++it){
// std::cout << it->first << " " << it->second << "\n";
//CountingMapL1[it->first]=1;
myCheckL1 = CountingMapL1.find(it->first) != CountingMapL1.end();
if(myCheckL1){CountingMapL1[it->first]+=1;}
else{CountingMapL1[it->first]=1;}
}
}

for(map<string, int >::const_iterator it2 = CountingMapHLT.begin();it2 != CountingMapHLT.end(); ++it2){
std::cout << it2->first << " " << it2->second << "\n";
}
std::cout << "\n";
std::cout << "\n";
for(map<string, int >::const_iterator it2 = CountingMapL1.begin();it2 != CountingMapL1.end(); ++it2){
std::cout << it2->first << " " << it2->second << "\n";
}

//HLT_mu6_mu4_bBmumu_Lxy0_L1BPH-2M9-MU6MU4_BPH-0DR15-MU6MU4


