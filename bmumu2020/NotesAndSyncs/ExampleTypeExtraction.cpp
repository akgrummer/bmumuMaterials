//run in the root environment on lxplus
//use these set up commands:
// setupATLAS
// lsetup "root 6.20.06-x86_64-centos7-gcc8-opt"

TString ifName = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/Nominal_OneFileData2018_FinalIso/LASTskim.bsmumu.root";
TFile* myfile = new TFile(ifName,"read");
TTree* myTree = (TTree*) myfile->Get("T_mv");
TObjArray *mycopy = myTree->GetListOfBranches(); 
mycopy->SetOwner(kFALSE); 
mycopy->Sort();
cout << mycopy->At(90)->GetTitle() << endl;
cout << mycopy->At(91)->GetTitle() << endl;

// to print all branches, titles and branch data types:
// for(int i = 0; i < mycopy->GetEntries(); ++i) { 
//     cout << mycopy->At(i)->GetName() << " "<< mycopy->At(i)->GetTitle() << endl; 
// }
