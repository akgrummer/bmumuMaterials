void loopOverEntries(TString DataORmc = ""){
    // TString DataORmc;
    // DataORmc = "Data";
    // DataORmc = "MC";
    TFile *ifile;
    if (DataORmc.EqualTo("MC")){
        // ifile = (TFile *)new TFile("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/OneTestFile_2ndRoundVal/fromBsmumu_300426_skimmed_MC/bsmumu.root", "read");
        ifile = (TFile *)new TFile("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/OneTestFile_2ndRoundVal/fromBsmumu_ct_300426_skimmed_MC/bsmumu.root", "read");
    }
    else if (DataORmc.EqualTo("Data")){  
        ifile = (TFile *)new TFile("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/OneTestFile_2ndRoundVal/fromData2018_ct_bsmumu_skimmed/bsmumu.root", "read");
    }else{
        printf("Please provide input: MC or Data?\n");
    }
    printf("looping over %s file\n", ((string)DataORmc).c_str());
    // float closeTrkDCA(0.);
    // float closeTrkDCA_T0134217728_LooSiHi1Pt05_f2dc2(0.);
    // float closeTrkDCA_T0008388608_LooSiHi1Pt05_f2dc2(0.);
    int B_cIDtrk_trkidx_T0000000035_LoosePt05_201516(0);
    int B_cIDtrk_trkidx_T0008388608_LooSiHi1Pt05_f2dc2(0);
    int B_cIDtrk_trkidx_T0134217728_LooSiHi1Pt05_f2dc2(0);
    int B_IDtrk1_trkidx(0);
    int B_IDtrk2_trkidx(0);

    TTree *itree = (TTree*)ifile->Get("T_mv");
    // itree->SetBranchAddress("closeTrkDCA",&closeTrkDCA);
    // itree->SetBranchAddress("closeTrkDCA_T0134217728_LooSiHi1Pt05_f2dc2",&closeTrkDCA_T0134217728_LooSiHi1Pt05_f2dc2);
    // itree->SetBranchAddress("closeTrkDCA_T0008388608_LooSiHi1Pt05_f2dc2",&closeTrkDCA_T0008388608_LooSiHi1Pt05_f2dc2);
    itree->SetBranchAddress("B_cIDtrk_trkidx_T0000000035_LoosePt05_201516",&B_cIDtrk_trkidx_T0000000035_LoosePt05_201516);
    itree->SetBranchAddress("B_cIDtrk_trkidx_T0008388608_LooSiHi1Pt05_f2dc2",&B_cIDtrk_trkidx_T0008388608_LooSiHi1Pt05_f2dc2);
    itree->SetBranchAddress("B_cIDtrk_trkidx_T0134217728_LooSiHi1Pt05_f2dc2",&B_cIDtrk_trkidx_T0134217728_LooSiHi1Pt05_f2dc2);
    itree->SetBranchAddress("B_IDtrk1_trkidx",&B_IDtrk1_trkidx); // indexes of muon tracks
    itree->SetBranchAddress("B_IDtrk2_trkidx",&B_IDtrk2_trkidx);

    Int_t myEntries(0);
    Int_t cnt(0);
    myEntries = itree->GetEntries();
    for (int i=0; i<myEntries; i++){
        itree->GetEntry(i);
        if (B_IDtrk1_trkidx == B_cIDtrk_trkidx_T0000000035_LoosePt05_201516){
                printf("warning track index is equal (T0000000035 and IDtrk1)\n");
                break;
            }
        if (B_IDtrk2_trkidx == B_cIDtrk_trkidx_T0000000035_LoosePt05_201516){
                printf("warning track index is equal (T0000000035 and IDtrk2)\n");
                break;
            }
        if (B_IDtrk1_trkidx == B_cIDtrk_trkidx_T0008388608_LooSiHi1Pt05_f2dc2){
                printf("warning track index is equal (T0008388608 and IDtrk1)\n");
                break;
            }
        if (B_IDtrk2_trkidx == B_cIDtrk_trkidx_T0008388608_LooSiHi1Pt05_f2dc2){
                printf("warning track index is equal (T0008388608 and IDtrk2)\n");
                break;
            }
        if (B_IDtrk1_trkidx == B_cIDtrk_trkidx_T0134217728_LooSiHi1Pt05_f2dc2){
                printf("warning track index is equal (T0134217728 and IDtrk1)\n");
                break;
            }
        if (B_IDtrk2_trkidx == B_cIDtrk_trkidx_T0134217728_LooSiHi1Pt05_f2dc2){
                printf("warning track index is equal (T0134217728 and IDtrk2)\n");
                break;
            }
        cnt++;
    }
    printf("done with entries loop - no warnings, %i entries\n", cnt);
}
void CheckTrkIdx(){
loopOverEntries("MC");
loopOverEntries("Data");
}
