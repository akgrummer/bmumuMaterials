// macro applies Run 1 analysis cuts on BpJpsiKp channel
// using skimmed ntuples on eos 
// (tentatively here:) /eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuProd1/ntup/skimmed_201710/
// as an input
// it outputs one large file (up to 6 GByte) per dataset

// 1. specify outpath
// 2. do "make" or "make MergeNominalnTuples.exe"
// 3. ./MergeNominalnTuples.exe path/to/dataset
// g++ AddPRIVXmuRound.cpp -o AddPRIVXmuRound.exe `root-config --glibs --cflags`

// this code is used after MergeNominalnTuples (first version, v2 added PRIVX mu round to MC already)
// this code is only used for data
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
#include <math.h>

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


void SaveTrees(TString ifile, TString ofile, bool isMC, bool isSignal){
    TChain *itree = new TChain("T_mv");
    TChain *itreeEv = new TChain("EventInfo");
    TStopwatch sw;
    TStopwatch sw2;
    sw.Start();
    itree->Add(ifile);
    itreeEv->Add(ifile);

    float PRIVX_mu;
    itree->SetBranchAddress("PRIVX_mu",  &PRIVX_mu);
    TFile *of = new TFile(ofile,"recreate");
    TTree *otree = itree->CloneTree(0);
    sw2.Start();
    TTree *otreeEv = itreeEv->CloneTree();
    sw2.Stop();
    sw2.Print();

    float PRIVX_mu_round(0.);
    TBranch* b_PRIVX_mu_round = otree->Branch("PRIVX_mu_round",&PRIVX_mu_round,"PRIVX_mu_round/F");

    cout<< "Entries in original tree: "<< itree->GetEntries() <<endl;
    auto nevents = itree->GetEntries();
    for (auto ievent=0; ievent<nevents; ievent++)
    {
        itree->GetEntry(ievent);
        if (ievent%100000==0) cout << "Processing event "<< ievent<< " of "<< nevents << endl;
            if (isSignal) PRIVX_mu_round = roundf(PRIVX_mu * 10) / 10;
            else PRIVX_mu_round = ceilf(PRIVX_mu) - 0.5;
        otree->Fill();
    }
    of->cd();
    otree->Write();
    otreeEv->Write();
    of->Close();
    sw.Stop();
    sw.Print();
}

void AddPRIVXmuRound(TString whichDataSet = "") {
    // TString workdir = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/";
    // TString workdir("/eos/home-a/agrummer/BsmumuData/AnalysisNtuples2020/v4/");
    TString odir("/eos/home-a/agrummer/BsmumuData/AnalysisNtuples2020/v4/");
    TString ifile(""), ofile("");
    // bool runMC(false);
    bool isMC(false);
    bool isSignal(false);
    if (whichDataSet.EqualTo("bbmumuX")){
        isMC = true;
        isSignal=false;
        ifile=odir+"LASTskim.user.agrummer.bbmumuX.merged.root";
        ofile=odir+"LASTskim.user.agrummer.bbmumuX.merged.2.root";
    }else if (whichDataSet.EqualTo("signalMC")){
        isMC = true;
        isSignal=true;
        ifile=odir+"LASTskim.user.agrummer.mcBsmumu.merged.root";
        ofile=odir+"LASTskim.user.agrummer.mcBsmumu.merged.2.root";
    }else if (whichDataSet.EqualTo("data")){
        isMC = false;
        isSignal=false;
        ifile=odir+"LASTskim.user.agrummer.Data1516.merged.root";
        ofile=odir+"LASTskim.user.agrummer.Data1516.merged.2.root";
    }
// "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/Nominal_NTUP_MC/bbmumuX/v4/user.mghneima.300307.BPHY8.TNTUP.e6179_a875_r9364_p4143.Bmumu"
// "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/Nominal_NTUP_MC/Bsmumu/v4/user.mghneima.300426.BPHY8.NTUP.e4889_a875_r9364_p4143.Bmumu/merged/merged.root"
    SaveTrees(ifile, ofile, isMC, isSignal);
}

int main(int argc, char* argv[])
{
    // gSystem->Load("libdefinitions.so");
    TString whichDataSet("");
    // whichDataSet = "bbmumuX";
    // whichDataSet = "signalMC";
    whichDataSet = "data";
    // TString inpath, pattern;
    if (argc>1) whichDataSet = TString(argv[1]);
    AddPRIVXmuRound(whichDataSet);
    return 0;
}
