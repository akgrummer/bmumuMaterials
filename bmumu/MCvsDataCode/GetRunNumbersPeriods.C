#include <iostream>
#include <fstream>

void GetRunNumbersPeriods(TString Year = "16", TString Period = "K"){
// TString ifilename = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimFeb13/LASTskim.Data_2015HLTand2016HLTLxy_Main_15Feb.root";

// root -l -q GetRunNumbersPeriods.C"(\"15\",\"D\" )"
// root -l -q GetRunNumbersPeriods.C"(\"15\",\"E\" )"
// root -l -q GetRunNumbersPeriods.C"(\"15\",\"F\" )"
// root -l -q GetRunNumbersPeriods.C"(\"15\",\"G\" )"
// root -l -q GetRunNumbersPeriods.C"(\"15\",\"H\" )"
// root -l -q GetRunNumbersPeriods.C"(\"15\",\"J\" )"
// root -l -q GetRunNumbersPeriods.C"(\"16\",\"A\" )"
// root -l -q GetRunNumbersPeriods.C"(\"16\",\"B\" )"
// root -l -q GetRunNumbersPeriods.C"(\"16\",\"C\" )"
// root -l -q GetRunNumbersPeriods.C"(\"16\",\"D\" )"
// root -l -q GetRunNumbersPeriods.C"(\"16\",\"E\" )"
// root -l -q GetRunNumbersPeriods.C"(\"16\",\"F\" )"
// root -l -q GetRunNumbersPeriods.C"(\"16\",\"G\" )"
// root -l -q GetRunNumbersPeriods.C"(\"16\",\"I\" )"
// root -l -q GetRunNumbersPeriods.C"(\"16\",\"K\" )"
// root -l -q GetRunNumbersPeriods.C"(\"16\",\"L\" )"

// LASTskim.user.acampove.data15D_undefined_BPHY8_NTUP_SKIMMED.periodD.grp15_v01_p3372_Bmumu.root.root
// LASTskim.user.acampove.data15E_undefined_BPHY8_NTUP_SKIMMED.periodE.grp15_v01_p3372_Bmumu.root.root
// LASTskim.user.acampove.data15F_undefined_BPHY8_NTUP_SKIMMED.periodF.grp15_v01_p3372_Bmumu.root.root
// LASTskim.user.acampove.data15G_undefined_BPHY8_NTUP_SKIMMED.periodG.grp15_v01_p3372_Bmumu.root.root
// LASTskim.user.acampove.data15H_undefined_BPHY8_NTUP_SKIMMED.periodH.grp15_v01_p3372_Bmumu.root.root
// LASTskim.user.acampove.data15J_undefined_BPHY8_NTUP_SKIMMED.periodJ.grp15_v01_p3372_Bmumu.root.root

// LASTskim.user.acampove.data16A_undefined_BPHY8_NTUP_SKIMMED.periodA.grp16_v01_p3372_Bmumu.root.root
// LASTskim.user.acampove.data16B_undefined_BPHY8_NTUP_SKIMMED.periodB.grp16_v01_p3372_Bmumu.root.root
// LASTskim.user.acampove.data16C_undefined_BPHY8_NTUP_SKIMMED.periodC.grp16_v01_p3372_Bmumu.root.root
// LASTskim.user.acampove.data16D_undefined_BPHY8_NTUP_SKIMMED.periodD.grp16_v01_p3372_Bmumu.root.root
// LASTskim.user.acampove.data16E_undefined_BPHY8_NTUP_SKIMMED.periodE.grp16_v01_p3372_Bmumu.root.root
// LASTskim.user.acampove.data16F_undefined_BPHY8_NTUP_SKIMMED.periodF.grp16_v01_p3372_Bmumu.root.root
// LASTskim.user.acampove.data16G_undefined_BPHY8_NTUP_SKIMMED.periodG.grp16_v01_p3372_Bmumu.root.root
// LASTskim.user.acampove.data16I_undefined_BPHY8_NTUP_SKIMMED.periodI.grp16_v01_p3372_Bmumu.root.root
// LASTskim.user.acampove.data16K_undefined_BPHY8_NTUP_SKIMMED.periodK.grp16_v01_p3372_Bmumu.root.root
// LASTskim.user.acampove.data16L_undefined_BPHY8_NTUP_SKIMMED.periodL.grp16_v01_p3372_Bmumu.root.root

TString ifilename = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimFeb11/LASTskim.user.acampove.data"+Year+Period+"_undefined_BPHY8_NTUP_SKIMMED.period"+Period+".grp"+Year+"_v01_p3372_Bmumu.root.root";
TString ifilename2 = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimFeb13/LASTskim.Data_2015HLTand2016HLTLxy_Main_15Feb_SepCoarse.root";
TFile *ifile;
TFile *ifile2;
ifile = new TFile(ifilename);
ifile2 = new TFile(ifilename2);
vector<UInt_t> RunNumbers = {};
vector<UInt_t> RunNumbers2015 = {};
vector<UInt_t> RunNumbers2016preTS1 = {};
vector<UInt_t> RunNumbers2016TS1toMD1 = {};
vector<UInt_t> RunNumbers2016postMD1 = {};



TTree *myTree = (TTree*)ifile->Get("T_mv");
UInt_t runNumber(0);//UInt_t
myTree->SetBranchAddress("run_number",&runNumber);
for(int i; i < myTree->GetEntries(); i++){
    myTree->GetEntry(i);
    RunNumbers.push_back(runNumber);
}
// TTree *myTree2 = (TTree*)ifile2->Get("T_mv_2015");
// UInt_t runNumber2(0);//UInt_t
// myTree2->SetBranchAddress("run_number",&runNumber2);
// for(int i; i < myTree2->GetEntries(); i++){
//     myTree2->GetEntry(i);
//     RunNumbers2015.push_back(runNumber2);
// }
// TTree *myTree3 = (TTree*)ifile2->Get("T_mv_2016preTS1");
// UInt_t runNumber3(0);//UInt_t
// myTree3->SetBranchAddress("run_number",&runNumber3);
// for(int i; i < myTree3->GetEntries(); i++){
//     myTree3->GetEntry(i);
//     RunNumbers2016preTS1.push_back(runNumber3);
// }
// TTree *myTree4 = (TTree*)ifile2->Get("T_mv_2016TS1toMD1");
// UInt_t runNumber4(0);//UInt_t
// myTree4->SetBranchAddress("run_number",&runNumber4);
// for(int i; i < myTree4->GetEntries(); i++){
//     myTree4->GetEntry(i);
//     RunNumbers2016TS1toMD1.push_back(runNumber4);
// }
// TTree *myTree5 = (TTree*)ifile2->Get("T_mv_2016postMD1");
// UInt_t runNumber5(0);//UInt_t
// myTree5->SetBranchAddress("run_number",&runNumber5);
// for(int i; i < myTree5->GetEntries(); i++){
//     myTree5->GetEntry(i);
//     RunNumbers2016postMD1.push_back(runNumber5);
// }


sort( RunNumbers.begin(), RunNumbers.end() );
RunNumbers.erase( unique( RunNumbers.begin(), RunNumbers.end() ), RunNumbers.end() );
// sort( RunNumbers2015.begin(), RunNumbers2015.end() );
// RunNumbers2015.erase( unique( RunNumbers2015.begin(), RunNumbers2015.end() ), RunNumbers2015.end() );
// sort( RunNumbers2016preTS1.begin(), RunNumbers2016preTS1.end() );
// RunNumbers2016preTS1.erase( unique( RunNumbers2016preTS1.begin(), RunNumbers2016preTS1.end() ), RunNumbers2016preTS1.end() );
// sort( RunNumbers2016TS1toMD1.begin(), RunNumbers2016TS1toMD1.end() );
// RunNumbers2016TS1toMD1.erase( unique( RunNumbers2016TS1toMD1.begin(), RunNumbers2016TS1toMD1.end() ), RunNumbers2016TS1toMD1.end() );
// sort( RunNumbers2016postMD1.begin(), RunNumbers2016postMD1.end() );
// RunNumbers2016postMD1.erase( unique( RunNumbers2016postMD1.begin(), RunNumbers2016postMD1.end() ), RunNumbers2016postMD1.end() );

ofstream myfile;
myfile.open ("./RunNumbers/RunNumbersPeriod"+Year+Period+".csv");
cout<<RunNumbers.size()<<endl;
for (int i = 0; i< RunNumbers.size(); i++){
myfile<<RunNumbers[i]<<endl;
}
myfile<<""<<endl;

// cout<<RunNumbers2015.size()<<endl;
// for (int i = 0; i< RunNumbers2015.size(); i++){
// myfile<<RunNumbers2015[i]<<endl;
// }
// myfile<<""<<endl;

// cout<<RunNumbers2016preTS1.size()<<endl;
// for (int i = 0; i< RunNumbers2016preTS1.size(); i++){
// myfile<<RunNumbers2016preTS1[i]<<endl;
// }
// myfile<<""<<endl;

// cout<<RunNumbers2016TS1toMD1.size()<<endl;
// for (int i = 0; i< RunNumbers2016TS1toMD1.size(); i++){
// myfile<<RunNumbers2016TS1toMD1[i]<<endl;
// }
// myfile<<""<<endl;

// cout<<RunNumbers2016postMD1.size()<<endl;
// for (int i = 0; i< RunNumbers2016postMD1.size(); i++){
// myfile<<RunNumbers2016postMD1[i]<<endl;
// }

myfile.close();

// cout<<RunNumbers.size()<<endl;
return 0;

}