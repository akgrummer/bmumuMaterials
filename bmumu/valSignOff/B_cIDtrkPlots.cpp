struct VariableInfo{
  TString bname;
  Float_t nbins;
  Float_t binLow;
  Float_t binHigh;
  TCut bnameCut;
  TString xtitle;
  TString legHeader;
  Float_t XMin;
  Float_t XMax;
  Float_t YMin;
  Float_t YMax;
  int logScale;
  TString SaveName;
};

VariableInfo pT1516 = {"B_cIDtrk_pT_T0000000035_LoosePt05_201516/1000.",
        120.,0., 12., 
        "B_cIDtrk_trkidx_T0000000035_LoosePt05_201516>-1.", 
        "B_cIDtrk_pT [GeV]", "As in 201516 (T0000000035)", 0., 12., 1E-4, 3E-1, 1, "B_cIDtrk_pT_201516"};
VariableInfo pTloose = {"B_cIDtrk_pT_T0008388608_LooSiHi1Pt05_f2dc2/1000.",
        120.,0., 12., 
        "B_cIDtrk_trkidx_T0008388608_LooSiHi1Pt05_f2dc2>-1.", 
        "B_cIDtrk_pT [GeV]", "Loose TVA (T0008388608)", 0., 12., 1E-4, 3E-1, 1, "B_cIDtrk_pT_loose"};
VariableInfo pTcustom = {"B_cIDtrk_pT_T0134217728_LooSiHi1Pt05_f2dc2/1000.",
        120.,0., 12., 
        "B_cIDtrk_trkidx_T0134217728_LooSiHi1Pt05_f2dc2>-1.", 
        "B_cIDtrk_pT [GeV]", "Custom TVA (T0134217728)", 0., 12., 1E-4, 3E-1, 1, "B_cIDtrk_pT_custom"};
VariableInfo eta1516 = {"B_cIDtrk_eta_T0000000035_LoosePt05_201516",
        100.,-3., 3., 
        "B_cIDtrk_trkidx_T0000000035_LoosePt05_201516>-1.", 
        "B_cIDtrk_eta", "As in 201516 (T0000000035)", -3., -3., 1E-3, 2E-1, 1, "B_cIDtrk_eta_201516"};
VariableInfo etaloose = {"B_cIDtrk_eta_T0008388608_LooSiHi1Pt05_f2dc2",
        100.,-3., 3., 
        "B_cIDtrk_trkidx_T0008388608_LooSiHi1Pt05_f2dc2>-1.", 
        "B_cIDtrk_eta", "Loose TVA (T0008388608)", -3., -3., 1E-3, 2E-1, 1, "B_cIDtrk_eta_loose"};
VariableInfo etacustom = {"B_cIDtrk_eta_T0134217728_LooSiHi1Pt05_f2dc2",
        100.,-3., 3., 
        "B_cIDtrk_trkidx_T0134217728_LooSiHi1Pt05_f2dc2>-1.", 
        "B_cIDtrk_eta", "Custom TVA (T0134217728)", -3., -3., 1E-3, 2E-1, 1, "B_cIDtrk_eta_custom"};
VariableInfo phi1516 = {"B_cIDtrk_phi_T0000000035_LoosePt05_201516",
        106,-3.18, 3.18, 
        "B_cIDtrk_trkidx_T0000000035_LoosePt05_201516>-1.", 
        "B_cIDtrk_phi", "As in 201516 (T0000000035)", -3.2, 3.2, 1E-3, 5E-1, 1, "B_cIDtrk_phi_201516"};
VariableInfo philoose = {"B_cIDtrk_phi_T0008388608_LooSiHi1Pt05_f2dc2",
        106,-3.18, 3.18, 
        "B_cIDtrk_trkidx_T0008388608_LooSiHi1Pt05_f2dc2>-1.", 
        "B_cIDtrk_phi", "Loose TVA (T0008388608)", -3.2, 3.2, 1E-3, 5E-1, 1, "B_cIDtrk_phi_loose"};
VariableInfo phicustom = {"B_cIDtrk_phi_T0134217728_LooSiHi1Pt05_f2dc2",
        106,-3.18, 3.18, 
        "B_cIDtrk_trkidx_T0134217728_LooSiHi1Pt05_f2dc2>-1.", 
        "B_cIDtrk_phi", "Custom TVA (T0134217728)", -3.2, 3.2, 1E-3, 5E-1, 1, "B_cIDtrk_phi_custom"};
// T_mv->Draw("Lxy", "B_cIDtrk_trkidx_T0000000035_LoosePt05_201516==-1", "egoff")
// T_mv->Draw("Lxy", "B_cIDtrk_trkidx_T0008388608_LooSiHi1Pt05_f2dc2==-1", "egoff")
// T_mv->Draw("Lxy", "B_cIDtrk_trkidx_T0134217728_LooSiHi1Pt05_f2dc2==-1", "egoff")
// T0134217728 custom
// T0008388608 loose
void makePlots(VariableInfo myVI = etacustom){
    TFile *ifileMC, *ifileData;
        // ifileMC = (TFile *)new TFile("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/OneTestFile_2ndRoundVal/fromBsmumu_ct_300426_skimmed_MC/bsmumu.root", "read");
        // ifileData = (TFile *)new TFile("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/OneTestFile_2ndRoundVal/fromData2018_ct_bsmumu_skimmed/bsmumu.root", "read");
        ifileMC = (TFile *)new TFile("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/OneTestFile_2ndRoundVal/ct_defaultLumiFiles_FixedPVWeight/fromBplusJpsiKplus_ct_300404_skimmed_MC/bpJpsiK.root", "read");
        ifileData = (TFile *)new TFile("/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/OneTestFile_2ndRoundVal/ct_defaultLumiFiles_FixedPVWeight/fromData2018_ct_BplusJpsiKplus_skimmed/bpJpsiK.root", "read");
        // VariableInfo myVI = pT1516;
        // VariableInfo myVI = pTloose;
        // VariableInfo myVI = pTcustom;
        // VariableInfo myVI = etacustom;
    // B_cIDtrk_eta_T0000000035_LoosePt05_201516
    // B_cIDtrk_eta_T0008388608_LooSiHi1Pt05_f2dc2
    // B_cIDtrk_eta_T0134217728_LooSiHi1Pt05_f2dc2
    // B_cIDtrk_pT_T0000000035_LoosePt05_201516
    // B_cIDtrk_pT_T0008388608_LooSiHi1Pt05_f2dc2
    // B_cIDtrk_pT_T0134217728_LooSiHi1Pt05_f2dc2
    // B_cIDtrk_phi_T0000000035_LoosePt05_201516
    // B_cIDtrk_phi_T0008388608_LooSiHi1Pt05_f2dc2
    // B_cIDtrk_phi_T0134217728_LooSiHi1Pt05_f2dc2
    // B_cIDtrk_trkidx_T0000000035_LoosePt05_201516
    // B_cIDtrk_trkidx_T0008388608_LooSiHi1Pt05_f2dc2
    // B_cIDtrk_trkidx_T0134217728_LooSiHi1Pt05_f2dc2
    TTree *itreeMC = (TTree*)ifileMC->Get("T_mv");
    TTree *itreeData = (TTree*)ifileData->Get("T_mv");
    TCut MCweights = "PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
    Int_t nmucalc(0), nvtx(0), nvtxSigMUCALC(0), nvtxSigVTX(0), nvtxSigBOTH(0);
    TCut addCut = myVI.bnameCut;
    TString DrawCommand1("");
    TString DrawCommand2("");
    DrawCommand1 = myVI.bname + ">>hist1";
    DrawCommand2 = myVI.bname + ">>hist2";
    if (myVI.nbins > 0 ){
        DrawCommand1+=("(");
        DrawCommand1+=myVI.nbins;
        DrawCommand1+=",";
        DrawCommand1+=myVI.binLow;
        DrawCommand1+=",";
        DrawCommand1+=myVI.binHigh;
        DrawCommand1+=")";
        DrawCommand2+=("(");
        DrawCommand2+=myVI.nbins;
        DrawCommand2+=",";
        DrawCommand2+=myVI.binLow;
        DrawCommand2+=",";
        DrawCommand2+=myVI.binHigh;
        DrawCommand2+=")";
    }
    itreeMC->Draw(DrawCommand1, MCweights*addCut, "egoff");
    itreeData->Draw(DrawCommand2, addCut, "egoff");
    TH1F* h1 = (TH1F*)gDirectory->Get("hist1");
    TH1F* h2 = (TH1F*)gDirectory->Get("hist2");
    h1->Scale(1./h1->Integral(0,myVI.nbins+1));
    h2->Scale(1./h2->Integral(0,myVI.nbins+1));
    TCanvas* c1 = new TCanvas("c1", "c1",0.,0., 800, 600);
    c1->SetLogy(myVI.logScale);
    h1->SetLineColor(4);
    h1->SetMarkerColor(4);
    h1->SetMarkerStyle(23);
    TString yAxisTitle = "Fraction of Events";
    Float_t BinWidth = (myVI.binHigh-myVI.binLow)/myVI.nbins;
    if (myVI.xtitle.Contains("GeV")){
        yAxisTitle+="/(";
        BinWidth = BinWidth*1000;
        yAxisTitle+= BinWidth;
        yAxisTitle+=" MeV)";
    }
    else{
        yAxisTitle+="/";
        yAxisTitle+= Form("%.2f", BinWidth);
    }

    h1->GetYaxis()->SetTitle(yAxisTitle);
    h1->GetXaxis()->SetTitle(myVI.xtitle);
    // if (myVI.logScale){
    //     h1->SetMinimum(600.);
    //     h1->SetMinimum(0.);
    // }
    h1->GetXaxis()->SetRangeUser(myVI.XMin,myVI.XMax);
    h1->GetYaxis()->SetRangeUser(myVI.YMin,myVI.YMax);
    h2->SetLineColor(1);
    h2->SetMarkerColor(1);
    h2->SetMarkerStyle(22);
    h1->Draw("hist");
    h2->Draw("p same");

    TLegend* leg;
    leg = new TLegend(0.7,0.75,0.9,0.9,NULL,"brNDC");
        leg->SetHeader(myVI.legHeader);
        leg->AddEntry(h1, "MC", "l");
        leg->AddEntry(h2, "Data", "p");
    leg->SetBorderSize(0);  // no border
    leg->SetLineColor(0);
    leg->SetFillColor(0);
    leg->SetTextSize(0.025);
    leg->Draw();
    Int_t dcaACK(0.), dcaBEL(0.), dcaBGL(0.), total(0.);
    // c1->SaveAs("/afs/cern.ch/user/a/agrummer/www/bmumu/valSignOff/2020Apr16/" + myVI.SaveName + ".pdf");
    c1->SaveAs("/afs/cern.ch/user/a/agrummer/www/bmumu/valSignOff/2020Apr16bplus/" + myVI.SaveName + ".pdf");
    delete c1;
return 0;
}

void B_cIDtrkPlots(){
    // VariableInfo myVI = pT1516;
    // VariableInfo myVI = pTloose;
    // VariableInfo myVI = pTcustom;
    // VariableInfo myVI = etacustom;
    makePlots(pT1516);
    makePlots(pTloose);
    makePlots(pTcustom);
    makePlots(eta1516);
    makePlots(etaloose);
    makePlots(etacustom);
    makePlots(phi1516);
    makePlots(philoose);
    makePlots(phicustom);
    }
