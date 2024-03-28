TCut MCweights = "PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
TCut addCut("");

struct VariableInfo{
  TString bname;
  Float_t nbins;
  Float_t binLow;
  Float_t binHigh;
  TString xtitle;
  TString legHeader;
  Float_t XMin;
  Float_t XMax;
  Float_t YMin;
  Float_t YMax;
  int logScale;
  TString SaveName;
};

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


// I_{0.7}
VariableInfo B_iso_7_Chi2_5_LoosePt05 = {"B_iso_7_Chi2_5_LoosePt05",
                51,0.0,1.02,
                "B Isolation", "ACH (OOO) As in Partial Run 2",
                0.0,1.02, 1E-5,1, 1,
                "B_iso_7_Chi2_5_LoosePt05"
            };
VariableInfo B_iso_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127 = {"B_iso_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127",
                51,0.0,1.02,
                "B Isolation", "BDI (PVP)  As in Run 1",
                0.0,1.02, 1E-5,1, 1,
                "B_iso_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127"
            };
VariableInfo B_iso_10_noChi2_LooSiHi1Pt05_T0134217728 = {"B_iso_10_noChi2_LooSiHi1Pt05_T0134217728",
                51,0.0,1.02,
                "B Isolation", "BEJ (PPP) Custom TVA",
                0.0,1.02, 1E-5,1, 1,
                "B_iso_10_noChi2_LooSiHi1Pt05_T0134217728"
            };
VariableInfo B_iso_10_noChi2_LooSiHi1Pt05_T0008388608 = {"B_iso_10_noChi2_LooSiHi1Pt05_T0008388608",
                51,0.0,1.02,
                "B Isolation", "BGJ (PPP) Loose TVA",
                0.0,1.02, 1E-5,1, 1,
                "B_iso_10_noChi2_LooSiHi1Pt05_T0008388608"
            };

VariableInfo muP_iso_7_Chi2_5_LoosePt05 = {"muP_iso_7_Chi2_5_LoosePt05",
                51,0.0,1.02,
                "muP Isolation","ACH (OOO) As in Partial Run 2",
                0.0,1.02, 1E-5,1, 1,
                "muP_iso_7_Chi2_5_LoosePt05"
            };
VariableInfo muP_iso_7_chi2_5_LoosePt05 = {"muP_iso_7_chi2_5_LoosePt05",
                51,0.0,1.02,
                "muP Isolation","ACH (OOO) As in Partial Run 2",
                0.0,1.02, 1E-5,1, 1,
                "muP_iso_7_Chi2_5_LoosePt05"
            };
VariableInfo muP_iso_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127 = {"muP_iso_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127",
                51,0.0,1.02,
                "muP Isolation", "BDI (PVP)  As in Run 1",
                0.0,1.02, 1E-5,1, 1,
                "muP_iso_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127"
            };
VariableInfo muP_iso_10_noChi2_LooSiHi1Pt05_T0134217728 = {"muP_iso_10_noChi2_LooSiHi1Pt05_T0134217728",
                51,0.0,1.02,
                "muP Isolation", "BEJ (PPP)  Custom TVA",
                0.0,1.02, 1E-5,1, 1,
                "muP_iso_10_noChi2_LooSiHi1Pt05_T0134217728"
            };
VariableInfo muP_iso_10_noChi2_LooSiHi1Pt05_T0008388608 = {"muP_iso_10_noChi2_LooSiHi1Pt05_T0008388608",
                51,0.0,1.02,
                "muP Isolation", "BGJ (PPP) Loose TVA",
                0.0,1.02, 1E-5,1, 1,
                "muP_iso_10_noChi2_LooSiHi1Pt05_T0008388608"
            };

VariableInfo muM_iso_7_Chi2_5_LoosePt05 = {"muM_iso_7_Chi2_5_LoosePt05",
                51,0.0,1.02,
                "muM Isolation", "ACH (OOO) As in Partial Run 2",
                0.0,1.02, 1E-5,1, 1,
                "muM_iso_7_Chi2_5_LoosePt05"
            };
VariableInfo muM_iso_7_chi2_5_LoosePt05 = {"muM_iso_7_chi2_5_LoosePt05",
                51,0.0,1.02,
                "muM Isolation", "ACH (OOO) As in Partial Run 2",
                0.0,1.02, 1E-5,1, 1,
                "muM_iso_7_Chi2_5_LoosePt05"
            };
VariableInfo muM_iso_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127 = {"muM_iso_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127",
                51,0.0,1.02,
                "muM Isolation", "BDI (PVP)  As in Run 1",
                0.0,1.02, 1E-5,1, 1,
                "muM_iso_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127"
            };
VariableInfo muM_iso_10_noChi2_LooSiHi1Pt05_T0134217728 = {"muM_iso_10_noChi2_LooSiHi1Pt05_T0134217728",
                51,0.0,1.02,
                "muM Isolation", "BEJ (PPP) Custom TVA Trk Perigee",
                0.0,1.02, 1E-5,1, 1,
                "muM_iso_10_noChi2_LooSiHi1Pt05_T0134217728"
            };
VariableInfo muM_iso_10_noChi2_LooSiHi1Pt05_T0008388608 = {"muM_iso_10_noChi2_LooSiHi1Pt05_T0008388608",
                51,0.0,1.02,
                "muM Isolation", "BGJ (PPP) Loose TVA",
                0.0,1.02, 1E-5,1, 1,
                "muM_iso_10_noChi2_LooSiHi1Pt05_T0008388608"
            };
// (I^{B}_{0.7, loose, pt>0.5})
VariableInfo B_iso_Ntracks_7_Chi2_5_LoosePt05 = {"B_iso_Ntracks_7_Chi2_5_LoosePt05",
                16,0,16,
                "Ntracks B Isolation", "ACH (OOO) As in Partial Run 2",
                0.0,16, 0, 1, 0,
                "B_iso_Ntracks_7_Chi2_5_LoosePt05"
                };
VariableInfo B_iso_Ntracks_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127 = {"B_iso_Ntracks_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127",
                16,0,16,
                "Ntracks B Isolation", "BDI (PVP)  As in Run 1",
                0.0,16, 0, 1, 0,
                "B_iso_Ntracks_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127"
            };
VariableInfo B_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0134217728 = {"B_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0134217728",
                16,0,16,
                "Ntracks B Isolation",  "BEJ (PPP) Custom TVA",
                0.0,16, 0, 1, 0,
                "B_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0134217728"
            };
VariableInfo B_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0008388608 = {"B_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0008388608",
                16,0,16,
                "Ntracks B Isolation", "BGJ (PPP) Loose TVA",
                0.0,16, 0, 1, 0,
                "B_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0008388608"
            };

VariableInfo muP_iso_Ntracks_7_Chi2_5_LoosePt05 = {"muP_iso_Ntracks_7_Chi2_5_LoosePt05",
                16,0,16,
                "Ntracks muP Isolation", "ACH (OOO) As in Partial Run 2",
                0.0,16, 0, 1, 0,
                "muP_iso_Ntracks_7_Chi2_5_LoosePt05"
            };
VariableInfo muP_iso_Ntracks_7_chi2_5_LoosePt05 = {"muP_iso_Ntracks_7_chi2_5_LoosePt05",
                16,0,16,
                "Ntracks muP Isolation", "ACH (OOO) As in Partial Run 2",
                0.0,16, 0, 1, 0,
                "muP_iso_Ntracks_7_Chi2_5_LoosePt05"
            };
VariableInfo muP_iso_Ntracks_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127 = {"muP_iso_Ntracks_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127",
                16,0,16,
                "Ntracks muP Isolation", "BDI (PVP)  As in Run 1",
                0.0,16, 0, 1, 0,
                "muP_iso_Ntracks_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127"
            };
VariableInfo muP_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0134217728 = {"muP_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0134217728",
                16,0,16,
                "Ntracks muP Isolation",  "BEJ (PPP) Custom TVA",
                0.0,16, 0, 1, 0,
                "muP_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0134217728"
            };
VariableInfo muP_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0008388608 = {"muP_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0008388608",
                16,0,16,
                "Ntracks muP Isolation", "BGJ (PPP) Loose TVA",
                0.0,16, 0, 1, 0,
                "muP_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0008388608"
            };

VariableInfo muM_iso_Ntracks_7_Chi2_5_LoosePt05 = {"muM_iso_Ntracks_7_Chi2_5_LoosePt05",
                16,0,16,
                "Ntracks muM Isolation", "ACH (OOO) As in Partial Run 2",
                0.0,16, 0, 1, 0,
                "muM_iso_Ntracks_7_Chi2_5_LoosePt05"
            };
VariableInfo muM_iso_Ntracks_7_chi2_5_LoosePt05 = {"muM_iso_Ntracks_7_chi2_5_LoosePt05",
                16,0,16,
                "Ntracks muM Isolation", "ACH (OOO) As in Partial Run 2",
                0.0,16, 0, 1, 0,
                "muM_iso_Ntracks_7_Chi2_5_LoosePt05"
            };
VariableInfo muM_iso_Ntracks_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127 = {"muM_iso_Ntracks_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127",
                16,0,16,
                "Ntracks muM Isolation", "BDI (PVP) As in Run 1",
                0.0,16, 0, 1, 0,
                "muM_iso_Ntracks_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127"
            };
VariableInfo muM_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0134217728 = {"muM_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0134217728",
                16,0,16,
                "Ntracks muM Isolation",  "BEJ (PPP) Custom TVA",
                0.0,16, 0, 1, 0,
                "muM_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0134217728"
            };
VariableInfo muM_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0008388608 = {"muM_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0008388608",
                16,0,16,
                "Ntracks muM Isolation", "BGJ (PPP) Loose TVA",
                0.0,16, 0, 1, 0,
                "muM_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0008388608"
            };

VariableInfo closeTrkDOCA_3 = {"closeTrkDOCA_3",
                61,0.,3.05,
                "DOCA_{xtrk} [mm]", "ACK (OOO) As in Partial Run 2",
                0.,3.05, 1E-4,1, 1,
                "closeTrkDOCA_3"
            };
VariableInfo closeTrkDOCA = {"closeTrkDOCA",
                61,0.,3.05,
                "DOCA_{xtrk} [mm]", "ACK (OOO) As in Partial Run 2",
                0.,3.05, 1E-4,1, 1,
                "closeTrkDOCA_3"
            };
VariableInfo closeTrkDOCA_T0134217728_LooSiHi1Pt05_f2dc2 = {"closeTrkDOCA_T0134217728_LooSiHi1Pt05_f2dc2",
                61,0.,3.05,
                "DOCA_{xtrk} [mm]", "BEL (PPP) Custom TVA",
                0.,3.05, 1E-4,1, 1,
                "closeTrkDOCA_T0134217728_LooSiHi1Pt05_f2dc2"
            };
VariableInfo closeTrkDOCA_T0008388608_LooSiHi1Pt05_f2dc2 = {"closeTrkDOCA_T0008388608_LooSiHi1Pt05_f2dc2",
                61,0.,3.05,
                "DOCA_{xtrk} [mm]", "BGL (PPP) Loose TVA",
                0.,3.05, 1E-4,1, 1,
                "closeTrkDOCA_T0008388608_LooSiHi1Pt05_f2dc2"
            };

VariableInfo closeTrkNtrksChi2 = {"closeTrkNtrksChi2",
                80,0,80,
                "N^{clos}_{trk}", "ACK (OOO) As in Partial Run 2",
                0.,80., 1E-4,1, 1,
                "closeTrkNtrksChi2"
            };
VariableInfo closeTrkNtrksChi2_T0134217728_LooSiHi1Pt05_f2dc2 = {"closeTrkNtrksChi2_T0134217728_LooSiHi1Pt05_f2dc2",
                80,0,80,
                "N^{clos}_{trk}", "BEL (PPP) Custom TVA",
                0.,80., 1E-4,1, 1,
                "closeTrkNtrksChi2_T0134217728_LooSiHi1Pt05_f2dc2"
            };
VariableInfo closeTrkNtrksChi2_T0008388608_LooSiHi1Pt05_f2dc2 = {"closeTrkNtrksChi2_T0008388608_LooSiHi1Pt05_f2dc2",
                80,0,80,
                "N^{clos}_{trk}", "BGL (PPP) Loose TVA",
                0.,80., 1E-4,1, 1,
                "closeTrkNtrksChi2_T0008388608_LooSiHi1Pt05_f2dc2"
            };

// VariableInfo a_2D = {"TMath::Abs(a_2D)",50,0,1.0,true,"|#alpha_{2D}| [rad]",true, "zoom", false, 0., false, 0.4, 1.5},
// VariableInfo DR = {"DR",30,0,1.5,true,"#DeltaR",true, "zoom", false, 0., false, 0.75, 1.25},
// VariableInfo Lxy = {"Lxy",35,0.,3.5,true,"L_{xy} [mm]",true, "zoom", false, 0., false, 0.5, 1.5},
// VariableInfo chi2_PVSV_log2D = {"chi2_PVSV_log2D",72,-2,16,true,"ln(#chi^{2}_{PV,DV xy})",true, "zoom", false, 0., false, 0., 3.5},  
// VariableInfo d0Min_sig = {"TMath::Abs(d0Min_sig)",40,0.0,40.0,false,"|d_{0}|^{min} sig.",true, "zoom", false, 0., false, 0.25, 1.5},
// VariableInfo d0Max_sig = {"TMath::Abs(d0Max_sig)",50,0.0,50.0,false,"|d_{0}|^{max} sig.",true, "zoom", false, 0., false, 0.25, 2.5},
// VariableInfo B_pT = {"B_pT",70,5,40,true,"p_{T}^{B} [GeV]",true, "zoom", false, 0., false, 0., 1.3},
// VariableInfo PlngMin2D = {"PlngMin2D",25,0,25,false,"P^{min}_{L} [GeV]",true, "zoom", false, 0., false, 0.75, 1.5},
// VariableInfo B_IDtrks_DCA = {"TMath::Abs(B_IDtrks_DCA)",40,0,0.4,true,"DOCA_{#mu#mu} [mm]",true, "zoom", false, 0., false, 0.9, 3.}, 
// VariableInfo B_IDtrks_deltaPhi = {"TMath::Abs(B_IDtrks_deltaPhi)",70,0.0,1.4,true,"|#Delta#phi_{#mu#mu}|",true, "zoom", false, 0., false, 0., 2.},
// VariableInfo Bvtx3DIP = {"Bvtx3DIP",60,0,2.0,true,"|IP_{B}^{3D}|",true, "zoom", false, 0., false, 0., 3.5}, //0.6
// VariableInfo B_eta = {"B_eta",-1,-3.0,3.0,false,"#eta^{B}",true, "zoom", false, 0., false, 0.75, 1.25},
// // VariableInfo = {"B_eta",50,-2.,2.,false,"#eta^{B}",false, "zoom", true, 0., true, 0., 3.5},
// VariableInfo B_fitChi2NDF = {"B_fitChi2NDF",24,0,6,false,"#chi^{2}_{B}/NDF",true, "zoom", false, 0., false, 0.75, 1.25},
// VariableInfo Npv = {"Npv",30,-0.5,29.5,false,"nPV",true, "zoom", false, 0., false, 0.5, 3.},
// VariableInfo Lxy_sig = {"Lxy_sig",80,0,80,false,"BvtxLxy signif.",true, "zoom", false, 0., false, 0.25, 2.5},
// VariableInfo B_MUCALC_massErr = {"B_MUCALC_massErr",40,30,130,false,"#delta m_{#mu#mu} [MeV]",true, "zoom", false, 0., false, 0.5, 2.},
// VariableInfo properTime_sig = {"properTime_sig",65,-10,120,true,"ct significance",true, "zoom", false, 0., false, 0., 3.5},
// VariableInfo properTime = {"properTime",90,0,15,true,"ct",true, "zoom", false, 0., false, 0., 3.5},
// // VariableInfo = {"properTime",30,6,14,true,"ct",true, "zoom", true, 0., false, 0., 3.5},
// VariableInfo PRIVX_mu = {"PRIVX_mu",35,0,35,false,"#mu PRIVX",true, "zoom", false, 0., false, 0., 3.5},
// VariableInfo B_MUCALC_mass = {"B_MUCALC_mass",60,4766,5966,false,"m_{#mu#mu} [MeV]",true, "zoom", false, 0., false, 0.85, 1.15},
// VariableInfo B_MUCALCovermassErr= {"B_MUCALC_mass/B_MUCALC_massErr",100,0,600,false,"m_{#mu#mu} /#Deltam_{#mu#mu}",false, "zoom", false, 0., false, 0., 3.5},
// VariableInfo Muon1_etcone30 = {"Muon1_etcone30",220,-20000,200000,true,"Muon1_etcone30",false, "zoom", false, 0., false, 0., 3.5},
// VariableInfo Muon2_etcone30 = {"Muon2_etcone30",220,-20000,200000,true,"Muon2_etcone30",false, "zoom", false, 0., false, 0., 3.5},
// VariableInfo Muon1_etcone40 = {"Muon1_etcone40",220,-20000,200000,true,"Muon1_etcone40",false, "zoom", false, 0., false, 0., 3.5},
// VariableInfo Muon2_etcone40 = {"Muon2_etcone40",220,-20000,200000,true,"Muon2_etcone40",false, "zoom", false, 0., false, 0., 3.5},
// VariableInfo Muon1_nucone30 = {"Muon1_nucone30",200,0,200,true,"Muon1_nucone30",false, "zoom", false, 0., false, 0., 3.5},
// VariableInfo Muon2_nucone30 = {"Muon2_nucone30",200,0,200,true,"Muon2_nucone30",false, "zoom", false, 0., false, 0., 3.5},
// VariableInfo Muon1_nucone40 = {"Muon1_nucone40",200,0,200,true,"Muon1_nucone40",false, "zoom", false, 0., false, 0., 3.5},
// VariableInfo Muon2_nucone40 = {"Muon2_nucone40",200,0,200,true,"Muon2_nucone40",false, "zoom", false, 0., false, 0., 3.5},
// VariableInfo B_PV_Ref_z = {"B_PV_Ref_z",40,-200,200,false,"B_PV_ref_z",true, "zoom", false, 0., false, 0., 3.5},
// VariableInfo chi2_PVSV_log1Dz = {"chi2_PVSV_log1Dz",52,-14,12,false,"Log(#chi^{2}_{z})",false, "zoom", false, 0., false, 0., 3.5},
// VariableInfo DecayCoplanarity = {"DecayCoplanarity",120,0,12000,true,"coplan._{#Deltax,#mu1,#mu2}",false, "zoom", false, 0., false, 0., 3.5},
// VariableInfo MuSignedd0SigMin = {"MuSignedd0SigMin",200,-50,150,false,"sd_{0}^{min} signif.",false, "zoom", false, 0., false, 0., 3.5},
// VariableInfo CoplanaritywithZ = {"CoplanaritywithZ",180,0,18000,true,"coplan._{#Deltax,#mu#mu,z}",false, "zoom", false, 0., false, 0., 3.5},
// VariableInfo BvtxDXSig = {"BvtxDXSig",70,0,140,false,"|#Deltax_{3D}| signif.",false, "zoom", false, 0., false, 0., 3.5},
// VariableInfo BvtxDXSig2D = {"BvtxDXSig2D",70,0,140,false,"|#Deltax_{2D}| signif.",false, "zoom", false, 0., false, 0., 3.5},
// VariableInfo PlngMax2D = {"PlngMax2D",40,0,40,false,"P^{max}_{L} [GeV]",false, "zoom", false, 0., false, 0., 3.5},
// // VariableInfo = {"B_iso_Ntracks_7_Chi2_5_MedPt05",25,0,25,false,"number of tracks in iso cone",false, "zoom", false, 0., false, 0., 3.5},
// // VariableInfo = {"BDT_bb_2012",80,-0.8,0.8,false,"BDT output",false, "zoom", false, 0., false, 0., 3.5},
// // VariableInfo = {"BDT_bb_2012",80,-0.8,0.8,false,"BDT output",false, "zoom", false, 0., false, 0., 3.5}, //32,-0.8,0.8 //60,0.15,0.7
// // VariableInfo = {"UpdatedClassBDT",32,-0.8,0.8,false,"BDT output",false, "zoom", false, 0., false, 0., 3.5},
// // VariableInfo = {"B_iso_Ntracks_7_Chi2_5_MedPt05",25,0,25,false,"number of tracks in iso cone",false, "zoom", false, 0., false, 0., 3.5},
// VariableInfo B_pT_error = {"B_pT_error",100,0,3000,false,"#delta p_{T}^{B} [MeV]",false, "zoom", false, 0., false, 0., 3.5},
// VariableInfo Lxy_err = {"Lxy_err",60,0,0.6,true,"BvtxLxyErr",true, "zoom", false, 0., false, 0., 3.5},
// VariableInfo d0Min = {"TMath::Abs(d0Min)",40,0.0,2.0,true,"|d_{0}|^{min} [mm]",true, "zoom", false, 0., false, 0., 2.5},
// VariableInfo d0Max = {"TMath::Abs(d0Max)",60,0,3.0,true,"|d_{0}|^{max} [mm]",true, "zoom", false, 0., false, 0.25, 3.},
// // VariableInfo = {"d0Min",80,-2.0,2.0,true,"d_{0}^{min} [mm]",true, "zoom", false, 0., false, 0., 3.5},
// // VariableInfo = {"d0Min",50,-0.4,0.4,true,"d_{0}^{min} [mm]",true, "zoom1", true, 0.4, false, 0.75, 1.25},//200
// // VariableInfo = {"d0Min",50,-0.2,0.2,true,"d_{0}^{min} [mm]",true, "zoom2", true, 0.2, false, 0.75, 1.25},//400
// // VariableInfo = {"d0Min",50,-0.07,0.07,true,"d_{0}^{min} [mm]",true, "zoom3", true, 0.07, false, 0.75, 1.25},//400
// // VariableInfo = {"d0Max",120,-3.0,3.0,true,"d_{0}^{max} [mm]",true, "zoom", false, 0., false, 0.75, 3.5},
// // VariableInfo = {"d0Max",50,-0.6,0.6,true,"d_{0}^{max} [mm]",true, "zoom1", true, 0.6, false, 0.75, 2.},
// // VariableInfo = {"d0Max",50,-0.3,0.3,true,"d_{0}^{max} [mm]",true, "zoom2", true, 0.3, false, 0.75, 2.},
// VariableInfo d0Min_err = {"d0Min_err",40,0.0,0.1,true,"d_{0}^{min} err. [mm]",true, "zoom", false, 0., false, 0.5, 3.5},
// VariableInfo d0Max_err = {"d0Max_err",60,0.0,0.15,true,"d_{0}^{max} err. [mm]",true, "zoom", false, 0., false, 0.5, 3.5},
// VariableInfo B_IDtrks_deltaEta = {"TMath::Abs(B_IDtrks_deltaEta)",28,0.0,1.4,true,"|#eta_{#mu1}-#eta_{#mu2}|",true, "zoom", false, 0., false, 0.5, 3.},
// VariableInfo B_IDtrks_deltaR = {"TMath::Sqrt(pow(B_IDtrks_deltaEta, 2) + pow(B_IDtrks_deltaPhi, 2))", 28,0.0,1.4,true,"|#Delta R_{#mu #mu}|",true, "zoom", false, 0., false, 0., 3.5},
// VariableInfo B_pT_sig = {"B_pT_sig",70,0,840,false,"p_{T}^{B} sig.",false, "zoom", false, 0., false, 0., 3.5}, //140
// // VariableInfo = {"muP_iso_Ntracks_7_chi2_5_medPt05",25,0,25,false,"N^{Iso 0.7, #mu+}_{trk}",false, "zoom", false, 0., false, 0., 3.5},
// // VariableInfo = {"muM_iso_Ntracks_7_chi2_5_medPt05",25,0,25,false,"N^{Iso 0.7, #mu-}_{trk}",false, "zoom", false, 0., false, 0., 3.5},
// // VariableInfo = {"muP_iso_7_chi2_5_medPt05",-1,0.0,1.1,false,"#mu+ Isolation (I^{#mu+}_{0.7})",false, "zoom", false, 0., false, 0., 3.5},
// // VariableInfo = {"muM_iso_7_chi2_5_medPt05",-1,0.0,1.1,false,"#mu- Isolation (I^{#mu-}_{0.7})",false, "zoom", false, 0., false, 0., 3.5},
// VariableInfo Muon1_eta = {"Muon1_eta",-1,-3.0,3.0,false, "#eta_{#mu_{1}}", true, "zoom", false, 0., false, 0.5, 1.5},
// VariableInfo Muon1_pT = {"Muon1_pT",100,0,50,true,"p_{T}^{#mu_{1}} [GeV]", true, "zoom", false, 0., false, 0.5, 2.5},
// VariableInfo Muon2_eta = {"Muon2_eta",-1,-3.0,3.0,false, "#eta_{#mu_{2}}", true, "zoom", false, 0., false, 0.5, 1.5},
// VariableInfo Muon2_pT = {"Muon2_pT",100,0,50,true,"p_{T}^{#mu_{2}} [GeV]", true, "zoom", false, 0., false, 0.5, 2.5},
// VariableInfo B_minChi2MuonsIPtoAnyPV = {"B_minChi2MuonsIPtoAnyPV",80,-10,10,false,"#chi^{2}_{#mu,xPV}",true, "zoom", false, 0., false, 0., 3.5},
// // VariableInfo = {"TMath::Sqrt(pow(closeTrkDCA,2)+pow(closeTrkZCA,2))",40,0,2,true,"DOCA_{xtrk, loose, pt>0.5} [mm]",true, "zoom", false, 0., false, 0.5, 1.5}
