void ExamplePlot(){
    TString DataORmc;
    // DataORmc = "Data";
    DataORmc = "MC";
    TFile *ifile;
    if (DataORmc.EqualTo("MC")){
        // ifile = (TFile *)new TFile("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/OneTestFile_2ndRoundVal/fromBsmumu_300426_skimmed_MC/bsmumu.root", "read");
        // ifile = (TFile *)new TFile("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/OneTestFile_2ndRoundVal/fromBsmumu_ct_300426_skimmed_MC/bsmumu.root", "read");
        ifile = (TFile *)new TFile("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/OneTestFile_2ndRoundVal/ct_defaultLumiFiles_FixedPVWeight/fromBplusJpsiKplus_ct_300404_skimmed_MC/bpJpsiK.root", "read");
    }
    else{  
        // ifile = (TFile *)new TFile("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/OneTestFile_2ndRoundVal/fromData2018_ct_bsmumu_skimmed/bsmumu.root", "read");
        ifile = (TFile *)new TFile("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/OneTestFile_2ndRoundVal/ct_defaultLumiFiles_FixedPVWeight/fromData2018_ct_BplusJpsiKplus_skimmed/bpJpsiK.root", "read");
    }
    TTree *itree = (TTree*)ifile->Get("T_mv");
    Double_t LSBLow = 4766.0;
    TCut CutLSBLow = Form("B_MUCALC_mass>=%f",LSBLow); 
    Double_t LSBHigh = 5166.0;
    TCut CutLSBHigh = Form("B_MUCALC_mass<%f",LSBHigh);
    Double_t RSBLow = 5526.0;
    TCut CutRSBLow = Form("B_MUCALC_mass>%f",RSBLow);
    Double_t RSBHigh = 5966.0;
    TCut CutRSBHigh = Form("B_MUCALC_mass<=%f",RSBHigh);

    TCut CutLSB = (CutLSBLow && CutLSBHigh);
    TCut CutRSB = (CutRSBLow && CutRSBHigh);
    TCut CutSB = CutLSB || CutRSB;
    TCut MCweights = "PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
    Int_t nmucalc(0), nvtx(0), nvtxSigMUCALC(0), nvtxSigVTX(0), nvtxSigBOTH(0);
    if (DataORmc.EqualTo("MC")){
        // nmucalc = itree->Draw("B_MUCALC_mass>>hist1(60,4766,5966)",MCweights,"egoff");
        nmucalc = itree->Draw("B_MUCALC_mass>>hist1(90,4466,6266)",MCweights,"egoff");
        // nvtx = itree->Draw("B_VTX_mass>>hist2(60,4766,5966)",MCweights,"egoff");
        nvtx = itree->Draw("B_VTX_mass>>hist2(90,4466,6266)",MCweights,"egoff");
    }
    else{
        // nmucalc = itree->Draw("B_MUCALC_mass>>hist1(60,4766,5966)","B_MUCALC_mass>0","egoff");
        nmucalc = itree->Draw("B_MUCALC_mass>>hist1(90,4466,6266)","B_MUCALC_mass>0","egoff");
        // nvtx = itree->Draw("B_VTX_mass>>hist2(60,4766,5966)","B_MUCALC_mass>0","egoff");
        nvtx = itree->Draw("B_VTX_mass>>hist2(90,4466,6266)","B_MUCALC_mass>0","egoff");
    }
    nvtxSigMUCALC = itree->Draw("B_VTX_mass","(B_MUCALC_mass>5166.0)&&(B_MUCALC_mass<5526.0)","egoff");
    nvtxSigVTX = itree->Draw("B_VTX_mass","(B_VTX_mass>5166.0)&&(B_VTX_mass<5526.0)","egoff");
    nvtxSigBOTH = itree->Draw("B_VTX_mass","(B_MUCALC_mass>5166.0)&&(B_MUCALC_mass<5526.0)&&(B_VTX_mass>5166.0)&&(B_VTX_mass<5526.0)","egoff");
    printf("nmucalc: %i nvtx: %i\n", nmucalc, nvtx);
    printf("nvtxSigMUCALC: %i nvtxSigVTX: %i nvtxSigBOTH: %i\n", nvtxSigMUCALC, nvtxSigVTX, nvtxSigBOTH);
    TH1F* h1 = (TH1F*)gDirectory->Get("hist1");
    TH1F* h2 = (TH1F*)gDirectory->Get("hist2");
      // {"B_MUCALC_mass",60,4766,5966,false,"m_{#mu#mu} [MeV]",true, "zoom", false, 0., false, 0.85, 1.15},
    h1->Scale(1./h1->Integral(0,61));
    h2->Scale(1./h2->Integral(0,61));
    TCanvas* c1 = new TCanvas("c1", "c1",0.,0., 800, 600);
    h1->SetLineColor(4);
    h1->SetMarkerColor(4);
    h1->SetMarkerStyle(23);
    h1->GetYaxis()->SetTitle("Fraction of Events/(20 MeV)");
    h1->GetXaxis()->SetTitle("B Mass [MeV]");
    // h1->GetYaxis()->SetRangeUser(0.,500.);
    // h1->GetXaxis()->SetRangeUser(4500., 6300.);
    // h1->GetXaxis()->SetRangeUser(4000., 7000.);
    // h1->SetMinimum(600.);
    // h1->SetMinimum(0.);
    h2->SetLineColor(1);
    h2->SetMarkerColor(1);
    h2->SetMarkerStyle(22);
    if (DataORmc.EqualTo("MC")){
        h1->GetYaxis()->SetRangeUser(0.,0.2);
        h1->Draw("hist");
        h2->Draw("hist same");
    }else{
        h1->GetYaxis()->SetRangeUser(0.,0.08);
        h1->Draw("p");
        h2->Draw("p same");}

    TLegend* leg;
    leg = new TLegend(0.7,0.75,0.9,0.9,NULL,"brNDC");
    if (DataORmc.EqualTo("MC")){
        leg->SetHeader("MC Sample");
        leg->AddEntry(h1, "B_MUCALC_mass", "l");
        leg->AddEntry(h2, "B_VTX_mass", "l");
    }
    else{
        leg->SetHeader("Data Sample");
        leg->AddEntry(h1, "B_MUCALC_mass", "lp");
        leg->AddEntry(h2, "B_VTX_mass", "lp");
    }
    leg->SetBorderSize(0);  // no border
    leg->SetLineColor(0);
    leg->SetFillColor(0);
    leg->SetTextSize(0.025);
    leg->Draw();
    Int_t dcaACK(0.), dcaBEL(0.), dcaBGL(0.), total(0.);
    if (DataORmc.EqualTo("MC")){
    dcaACK = itree->Draw("Lxy",MCweights*"closeTrkDCA==-999","egoff");
    dcaBEL = itree->Draw("Lxy",MCweights*"closeTrkDCA_T0134217728_LooSiHi1Pt05_f2dc2==-999","egoff");
    dcaBGL = itree->Draw("Lxy",MCweights*"closeTrkDCA_T0008388608_LooSiHi1Pt05_f2dc2==-999","egoff");
    total = itree->Draw("Lxy",MCweights,"egoff");
    }
    else{
    dcaACK = itree->Draw("Lxy","closeTrkDCA==-999","egoff");
    dcaBEL = itree->Draw("Lxy","closeTrkDCA_T0134217728_LooSiHi1Pt05_f2dc2==-999","egoff");
    dcaBGL = itree->Draw("Lxy","closeTrkDCA_T0008388608_LooSiHi1Pt05_f2dc2==-999","egoff");
    total = itree->Draw("Lxy","","egoff");
    }
    printf("dcaACK: %i dcaBEL: %i dcaBGL: %i \n", dcaACK, dcaBEL, dcaBGL);
    printf("Total: %i\n", total);
    if (DataORmc.EqualTo("MC")){
        c1->SaveAs("/afs/cern.ch/user/a/agrummer/www/bmumu/valSignOff/2020Apr16bplus/MC.pdf");
    }else {c1->SaveAs("/afs/cern.ch/user/a/agrummer/www/bmumu/valSignOff/2020Apr16bplus/Data.pdf");}
return 0;
}