// macro applies Run 1 analysis cuts on BpJpsiKp channel
// using skimmed ntuples on eos 
// (tentatively here:) /eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuProd1/ntup/skimmed_201710/
// as an input
// it outputs one large file (up to 6 GByte) per dataset

// 1. specify outpath
// 2. do "make" or "make cutBatchBsmumu.exe"
// 3. ./cutBatchBsmumu path/to/dataset

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

void MergeNominalnTuples(TString workdir = "") {
    if (workdir.EqualTo("")) workdir = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/";
    bool isMC(true);
    if ( !workdir.Contains("mc16") ) isMC = false;
    // "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/Nominal_NTUP_MC/Bsmumu/v4/user.mghneima.300426.BPHY8.NTUP.e4889_a875_r9364_p4143.Bmumu/merged/merged.root"
    TString idir(workdir);
    TString odir("/eos/home-a/agrummer/BsmumuData/AnalysisNtuples2020/v4/");
    TString ifile("");
    TString ofile("");
    TString dummyidir("");
    idir+="Nominal_NTUP_data/";
    TString DataYear = "data15main";
    TChain *itree = new TChain("T_mv");
    TChain *itreeEv = new TChain("EventInfo");
    TStopwatch sw;
    sw.Start();
    if (DataYear.EqualTo("data15main")){
        idir+="data15_Main/v4/";
        dummyidir = idir;
        TString periods15main[6] = {"D", "E", "F", "G", "H", "J"};
            idir = dummyidir;
            idir.Append("user.mghneima.data15_13TeV.period"+periods15main[0]+".physics_Main.BPHY8.NTUP.grp15_v01_p4144_Bmumu/");
            ifile = idir+"LASTskim.*.root";
            itree->Add(ifile);
            itreeEv->Add(ifile);
    }
    ofile=odir+"data15main.root";
    TFile *of = new TFile(ofile,"recreate");
    TTree *otree = itree->CloneTree(0);
    TTree *otreeEv = itreeEv->CloneTree(0);
    // data16main
    // "data16_Main/v4/"
    // TString  periods16main[10] = {"A", "B", "C", "D", "E", "F", "G", "I", "K", "L"};
    // "user.mghneima.data16_13TeV.period"+periods16main[i]+".physics_Main.BPHY8.NTUP.grp16_v01_p4144_Bmumu/";

    // data16delayed
    // "data16_BphysDelayed/v4/"
    // TString periods16delayed[7] = {"B", "D", "E", "F", "G", "I", "K"};
    // "user.mghneima.data16_13TeV.period"+periods16delayed[i]+".physics_BphysDelayed.BPHY8.NTUP.grp16_v01_p4144_Bmumu/";

    of->cd();
    otree->Write();
    otreeEv->Write();
    of->Close();
    sw.Stop();
    sw.Print();
}

int main(int argc, char* argv[])
{
    gSystem->Load("libdefinitions.so");
    TString inpath, pattern;
    if (argc>1) inpath = TString(argv[1]);
    MergeNominalnTuples();
    return 0;
}
