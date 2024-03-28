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


void SaveTrees(TString ifile, TString ofile, bool isData){

    TChain *itree = new TChain("T_mv");
    TStopwatch sw;
    TStopwatch sw2;
    sw.Start();
    itree->Add(ifile);
    int numEntries(0), numEntriesPrev(0);
    numEntries = itree->GetEntries();
    cout<<"Entries added: "<<numEntries-numEntriesPrev<<endl;
    float closeTrkDCA, closeTrkZCA;
    float B_MUCALC_mass;
    itree->SetBranchAddress("closeTrkDCA",  &closeTrkDCA);
    itree->SetBranchAddress("closeTrkZCA",  &closeTrkZCA);
    itree->SetBranchAddress("B_MUCALC_mass",&B_MUCALC_mass);
    TFile *of = new TFile(ofile,"recreate");
    TTree *otree = itree->CloneTree(0);
    double closeTrkDOCA_3(0.);
    TBranch* b_closeTrkDOCA_3 = otree->Branch("closeTrkDOCA_3",&closeTrkDOCA_3,"closeTrkDOCA_3/D");

    cout<< "Entries in original tree: "<< itree->GetEntries() <<endl;
    auto nevents = itree->GetEntries();
    for (auto ievent=0; ievent<nevents; ievent++)
    {
        itree->GetEntry(ievent);
        if (ievent%100000==0) cout << "Processing event "<< ievent<< " of "<< nevents << endl;
        if(isData){
            if (B_MUCALC_mass<4766.0 || B_MUCALC_mass>5966.0 || (B_MUCALC_mass>=5166.0 && B_MUCALC_mass<=5526.0)) continue; //exclude blinded region
        }
            if (TMath::Abs(closeTrkDCA)==999.0) closeTrkDOCA_3 = 3.;  //FIXME DOCA
            else closeTrkDOCA_3 = (double) TMath::Sqrt(pow(closeTrkDCA,2)+pow(closeTrkZCA,2));
            if (closeTrkDOCA_3 > 3.) closeTrkDOCA_3 = 3.;
        otree->Fill();
    }
    of->cd();
    otree->Write();
    of->Close();
    sw.Stop();
    sw.Print();
}

void MergeNominalnTuples(TString whichDataSet = "") {
    TString idir = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/AnalysisNtuples/";
    // ifileMCPartial = (TFile *)new TFile(idirPartial+"Bsmumu/mc16a/v3/LASTskim.mc16Bs_BDT2016_v2.root", "read");
    // ifileDataPartial = (TFile *)new TFile(idirPartial+"Bsmumu/data15a16/v3/data1516Bs_BDT2016_v2.root", "read");
    TString workdir = "/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/";
    TString odir("/eos/home-a/agrummer/BsmumuData/partialRun2/");
    TString ifile(""), ofile("");
    bool isData(false);
    if (whichDataSet.EqualTo("signalMC")){
        ifile=idir+"Bsmumu/mc16a/v3/LASTskim.mc16Bs_BDT2016_v2.root";
        ofile=odir+"LASTskim.mc16Bs_BDT2016_v2_doca3.root";
    }else if (whichDataSet.EqualTo("data")){
        isData = true;
        ifile=idir+"Bsmumu/data15a16/v3/data1516Bs_BDT2016_v2.root";
        ofile=odir+"data1516Bs_BDT2016_v2_doca3_blind.root";
    }
    SaveTrees(ifile, ofile, isData);
}

int main(int argc, char* argv[])
{
    // gSystem->Load("libdefinitions.so");
    TString whichDataSet("");
    // whichDataSet = "bbmumuX";
    // TString inpath, pattern;
    if (argc>1) whichDataSet = TString(argv[1]);
    MergeNominalnTuples(whichDataSet);
    return 0;
}
