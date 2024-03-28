// macro applies Run 1 analysis cuts on BpJpsiKp channel
// using skimmed ntuples on eos 
// (tentatively here:) /eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuProd1/ntup/skimmed_201710/
// as an input
// it outputs one large file (up to 6 GByte) per dataset

// 1. specify outpath
// 2. do "make" or "make MergeNominalnTuples.exe"
// 3. ./MergeNominalnTuples.exe path/to/dataset

#include "TCut.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1.h"
#include "TH2.h"
#include "TBranch.h"
#include <iostream>
#include "TSystem.h"
#include "TLorentzVector.h"
#include "TStopwatch.h"
#include "DDWQLC.h"
#include "TriggerWeights.h"
#include <dirent.h>
#include <set>

using namespace std;
typedef std::vector<unsigned int>  v_uint;
typedef map<string, int>      map_str_int;
typedef std::vector<int>            v_int;
typedef std::vector<float>        v_float;
typedef std::vector<double>      v_double;

bool hasEnding(std::string const &fullString, std::string const &ending) {
if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}


void SaveTrees(TString workdir, TString ofile, bool isMC, bool isSignal){
    // bool isMC(true);
    // if ( !ofile.Contains("mc") ) isMC = false;
    TString idir(workdir);
    TString ifile("");
    TString dummyidir1("");
    TString dummyidir2("");
    idir+="Nominal_NTUP_data/";
    dummyidir1 = idir;
    TChain *itree = new TChain("T_mv");
    TChain *itreeEv = new TChain("EventInfo");
    TStopwatch sw;
    TStopwatch sw2;
    sw.Start();
    TString periods15main[6] = {"D", "E", "F", "G", "H", "J"};
    TString periods16main[10] = {"A", "B", "C", "D", "E", "F", "G", "I", "K", "L"};
    TString periods16delayed[7] = {"B", "D", "E", "F", "G", "I", "K"};
    int numEntries(0), numEntriesPrev(0);
    TString DataYear("");
    if (!isMC){
        DataYear = "data15main";
        if (DataYear.EqualTo("data15main")){
            idir+="data15_Main/v4/";
            dummyidir2 = idir;
                for(int i=0; i<6; i++){
                    numEntriesPrev = numEntries;
                    sw2.Start();
                    cout << DataYear<<" "<<periods15main[i]<<endl;
                    idir = dummyidir2;
                    idir.Append("user.mghneima.data15_13TeV.period"+periods15main[i]+".physics_Main.BPHY8.NTUP.grp15_v01_p4144_Bmumu/");
                    ifile = idir+"LASTskim.*.root";
                    itree->Add(ifile);
                    itreeEv->Add(ifile);
                    numEntries = itree->GetEntries();
                    cout<<"Entries added: "<<numEntries-numEntriesPrev<<endl;
                    sw2.Stop();
                    sw2.Print();
                }
        }
        idir = dummyidir1;
        DataYear = "data16main";
        if (DataYear.EqualTo("data16main")){
            idir+="data16_Main/v4/";
            dummyidir2 = idir;
                for(int i=0; i<10; i++){
                    numEntriesPrev = numEntries;
                    sw2.Start();
                    cout << DataYear<<" "<<periods16main[i]<<endl;
                    idir = dummyidir2;
                    idir.Append("user.mghneima.data16_13TeV.period"+periods16main[i]+".physics_Main.BPHY8.NTUP.grp16_v01_p4144_Bmumu/");
                    ifile = idir+"LASTskim.*.root";
                    itree->Add(ifile);
                    itreeEv->Add(ifile);
                    numEntries = itree->GetEntries();
                    cout<<"Entries added: "<<numEntries-numEntriesPrev<<endl;
                    sw2.Stop();
                    sw2.Print();
                }
        }
        // idir = dummyidir1;
        // DataYear = "data16delayed";
        // if (DataYear.EqualTo("data16delayed")){
        //     idir+="data16_BphysDelayed/v4/";
        //     dummyidir2 = idir;
        //         for(int i=0; i<7; i++){
        //             numEntriesPrev = numEntries;
        //             sw2.Start();
        //             cout << DataYear<<" "<<periods16delayed[i]<<endl;
        //             idir = dummyidir2;
        //             idir.Append("user.mghneima.data16_13TeV.period"+periods16delayed[i]+".physics_BphysDelayed.BPHY8.NTUP.grp16_v01_p4144_Bmumu/");
        //             ifile = idir+"LASTskim.*.root";
        //             itree->Add(ifile);
        //             itreeEv->Add(ifile);
        //             numEntries = itree->GetEntries();
        //             cout<<"Entries added: "<<numEntries-numEntriesPrev<<endl;
        //             sw2.Stop();
        //             sw2.Print();
        //         }
        // }
    }
    else{
        if (isSignal){
                ifile = workdir+"Nominal_NTUP_MC/";
                ifile.Append("Bsmumu/v4/user.mghneima.300426.BPHY8.NTUP.e4889_a875_r9364_p4143.Bmumu/merged/merged.root");
                itree->Add(ifile);
                itreeEv->Add(ifile);
                numEntries = itree->GetEntries();
                cout<<"Entries added: "<<numEntries-numEntriesPrev<<endl;
        }else{
            ifile = workdir+"Nominal_NTUP_MC/";
            ifile.Append("bbmumuX/v4/user.mghneima.300307.BPHY8.TNTUP.e6179_a875_r9364_p4143.Bmumu/");
            ifile.Append("LASTskim.*.root");
            itree->Add(ifile);
            itreeEv->Add(ifile);
            numEntries = itree->GetEntries();
            cout<<"Entries added: "<<numEntries-numEntriesPrev<<endl;
        }
    }

    // itree->SetBranchStatus("*",0);
    // itree->SetBranchStatus("branchname",1); //etc.
    //itree branches
    float closeTrkDCA, closeTrkZCA;
    float closeTrkDCA_T0008388608_LooSiHi1Pt05_f2dc2, closeTrkZCA_T0008388608_LooSiHi1Pt05_f2dc2;
    float closeTrkDCA_T0134217728_LooSiHi1Pt05_f2dc2, closeTrkZCA_T0134217728_LooSiHi1Pt05_f2dc2;
    itree->SetBranchAddress("closeTrkDCA",  &closeTrkDCA);
    itree->SetBranchAddress("closeTrkZCA",  &closeTrkZCA);
    itree->SetBranchAddress("closeTrkDCA_T0008388608_LooSiHi1Pt05_f2dc2",  &closeTrkDCA_T0008388608_LooSiHi1Pt05_f2dc2);
    itree->SetBranchAddress("closeTrkZCA_T0008388608_LooSiHi1Pt05_f2dc2",  &closeTrkZCA_T0008388608_LooSiHi1Pt05_f2dc2);
    itree->SetBranchAddress("closeTrkDCA_T0134217728_LooSiHi1Pt05_f2dc2",  &closeTrkDCA_T0134217728_LooSiHi1Pt05_f2dc2);
    itree->SetBranchAddress("closeTrkZCA_T0134217728_LooSiHi1Pt05_f2dc2",  &closeTrkZCA_T0134217728_LooSiHi1Pt05_f2dc2);

    // TFile *of = new TFile(ofile,"update");
    TFile *of = new TFile(ofile,"recreate");
    TTree *otree = itree->CloneTree(0);
    // otree->SetName("data15main_D");
    sw2.Start();
    TTree *otreeEv = itreeEv->CloneTree();
    sw2.Stop();
    sw2.Print();
    // otreeEv->SetName("data15mainEv_D");

    //otree branches
    double closeTrkDOCA_3(0.);
    double closeTrkDOCA_T0008388608_LooSiHi1Pt05_f2dc2(0.);
    double closeTrkDOCA_T0134217728_LooSiHi1Pt05_f2dc2(0.);
    TBranch* b_closeTrkDOCA_3 = otree->Branch("closeTrkDOCA_3",&closeTrkDOCA_3,"closeTrkDOCA_3/D");
    TBranch* b_closeTrkDOCA_T0008388608_LooSiHi1Pt05_f2dc2 = otree->Branch("closeTrkDOCA_T0008388608_LooSiHi1Pt05_f2dc2",&closeTrkDOCA_T0008388608_LooSiHi1Pt05_f2dc2,"closeTrkDOCA_T0008388608_LooSiHi1Pt05_f2dc2/D");
    TBranch* b_closeTrkDOCA_T0134217728_LooSiHi1Pt05_f2dc2 = otree->Branch("closeTrkDOCA_T0134217728_LooSiHi1Pt05_f2dc2",&closeTrkDOCA_T0134217728_LooSiHi1Pt05_f2dc2,"closeTrkDOCA_T0134217728_LooSiHi1Pt05_f2dc2/D");


    cout<< "Entries in original tree: "<< itree->GetEntries() <<endl;
    auto nevents = itree->GetEntries();
    for (auto ievent=0; ievent<nevents; ievent++)
    {
        itree->GetEntry(ievent);
        if (ievent%100000==0) cout << "Processing event "<< ievent<< " of "<< nevents << endl;
            if (TMath::Abs(closeTrkDCA)==999.0) closeTrkDOCA_3 = 3.;  //FIXME DOCA
            else closeTrkDOCA_3 = (double) TMath::Sqrt(pow(closeTrkDCA,2)+pow(closeTrkZCA,2));
            if (closeTrkDOCA_3 > 3.) closeTrkDOCA_3 = 3.;
            closeTrkDOCA_T0008388608_LooSiHi1Pt05_f2dc2 = (double) TMath::Sqrt(pow(closeTrkDCA_T0008388608_LooSiHi1Pt05_f2dc2,2)+pow(closeTrkZCA_T0008388608_LooSiHi1Pt05_f2dc2,2));
            if (closeTrkDOCA_T0008388608_LooSiHi1Pt05_f2dc2 > 3.) closeTrkDOCA_T0008388608_LooSiHi1Pt05_f2dc2 = 3.;
            closeTrkDOCA_T0134217728_LooSiHi1Pt05_f2dc2 = (double) TMath::Sqrt(pow(closeTrkDCA_T0134217728_LooSiHi1Pt05_f2dc2,2)+pow(closeTrkZCA_T0134217728_LooSiHi1Pt05_f2dc2,2));
            if (closeTrkDOCA_T0134217728_LooSiHi1Pt05_f2dc2 > 3.) closeTrkDOCA_T0134217728_LooSiHi1Pt05_f2dc2 = 3.;
        otree->Fill();
    }
    of->cd();
    otree->Write();
    otreeEv->Write();
    of->Close();
    sw.Stop();
    sw.Print();
}

void MergeNominalnTuples(TString whichDataSet = "") {
    TString workdir = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/";
    TString odir("/eos/home-a/agrummer/BsmumuData/AnalysisNtuples2020/v4/");
    TString ofile("");
    // bool runMC(false);
    bool isMC(false);
    bool isSignal(false);
    if (whichDataSet.EqualTo("bbmumuX")){
        isMC = true;
        isSignal=false;
        ofile=odir+"LASTskim.user.agrummer.bbmumuX.merged.root";
    }else if (whichDataSet.EqualTo("signalMC")){
        isMC = true;
        isSignal=true;
        ofile=odir+"LASTskim.user.agrummer.mcBsmumu.merged.root";
    }else if (whichDataSet.EqualTo("data")){
        isMC = false;
        isSignal=false;
        ofile=odir+"LASTskim.user.agrummer.Data1516.merged.root";
    }
// "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/Nominal_NTUP_MC/bbmumuX/v4/user.mghneima.300307.BPHY8.TNTUP.e6179_a875_r9364_p4143.Bmumu"
// "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/Nominal_NTUP_MC/Bsmumu/v4/user.mghneima.300426.BPHY8.NTUP.e4889_a875_r9364_p4143.Bmumu/merged/merged.root"
    SaveTrees(workdir, ofile, isMC, isSignal);
}

int main(int argc, char* argv[])
{
    // gSystem->Load("libdefinitions.so");
    TString whichDataSet("");
    whichDataSet = "bbmumuX";
    // TString inpath, pattern;
    if (argc>1) whichDataSet = TString(argv[1]);
    MergeNominalnTuples(whichDataSet);
    return 0;
}
