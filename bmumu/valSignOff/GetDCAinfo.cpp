void GetDCAinfo(){
    TString DataORmc;
    DataORmc = "Data";
    // DataORmc = "MC";
    TFile *ifile;
    if (DataORmc.EqualTo("MC")){
        // ifile = (TFile *)new TFile("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/OneTestFile_2ndRoundVal/fromBsmumu_300426_skimmed_MC/bsmumu.root", "read");
        ifile = (TFile *)new TFile("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/OneTestFile_2ndRoundVal/fromBsmumu_ct_300426_skimmed_MC/bsmumu.root", "read");
    }
    else{  
        ifile = (TFile *)new TFile("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/OneTestFile_2ndRoundVal/fromData2018_ct_bsmumu_skimmed/bsmumu.root", "read");
    }
    TTree *itree = (TTree*)ifile->Get("T_mv");
}