//was used in 2020Jun12 all var new vs old ntuple comparisons:
// TCut MCweights = "PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf";
TCut MCweights = "NPVweight*PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf*Muon1_trigger_sf*Muon2_trigger_sf*CombWeights";
// TCut MCweights = "PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf*Muon1_trigger_sf*Muon2_trigger_sf*CombWeights";
TCut addCut("");
TCut testweight("testweight");



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

struct HistGraphics{
    int theLineColor;
    int theLineStyle;
    int theMarkerColor;
    int theMarkerStyle;
    int theFillColor;
    float theAlpha;
    int theFillStyle;
};
// HistGraphics hgMC1 = {2, 4, 23, 2, 0.35, 3254};//for signal
HistGraphics hgMC1 = {1, 2, 4, 23, 1, 0, 0};
HistGraphics hgMC2 = {416+1, 1, 4, 23, 416+1, 0, 0};
HistGraphics hgMC3 = {632+1, 1, 4, 23, 416+1, 0, 0};
// HistGraphics hgData1 = {1, 1, 1, 22, 22, 0, 0};
HistGraphics hgData1 = {1, 1, 1, 20, 22, 0, 0};
HistGraphics hgData2 = {432+2, 1, 432+2, 23, 2, 0, 0};
// kBlue is 600
// kRed is 632
// kGreen is 416
// kWhite  = 0,   kBlack  = 1,   kGray    = 920,  kRed    = 632,  kGreen  = 416,
// kBlue   = 600, kYellow = 400, kMagenta = 616,  kCyan   = 432,  kOrange = 800,
// kSpring = 820, kTeal   = 840, kAzure   =  860, kViolet = 880,  kPink   = 900

struct LegAndLabelPositions{
    float xLowData; float yLowData; float xHighData; float yHighData;
    float xLabelData; float yLabelData;
    float xLowMC; float yLowMC; float xHighMC; float yHighMC;
    float xLabelMC; float yLabelMC;
    float xLowbbmumuX; float yLowbbmumuX; float xHighbbmumuX; float yHighbbmumuX;
    float xLabelbbmumuX; float yLabelbbmumuX;
};
LegAndLabelPositions llPos1 = {
    //Data
    0.2, 0.78, 0.4, 0.91, 
    0.6, 0.85,
    //MC signal
    0.2, 0.78, 0.4, 0.91, 
    0.6, 0.85,
    //bbmumuX
    0.2, 0.78, 0.4, 0.91, 
    0.6, 0.85
    };

LegAndLabelPositions llPos2 = {
    //Data
    0.6, 0.74, 0.8, 0.82, 
    0.6, 0.85,
    //MC signal
    0.6, 0.74, 0.8, 0.82, 
    0.6, 0.85,
    //bbmumuX
    0.6, 0.74, 0.8, 0.82, 
    0.6, 0.85
    };

//for the residual plot:
//3 options, for different plot comparisons
struct PullParams{
    Float_t pullYMinData;//Data
    Float_t pullYMaxData;
    Float_t pullYMinMC;//Signal MC
    Float_t pullYMaxMC;
    Float_t pullYMinbbmumuX;//bbmumuX
    Float_t pullYMaxbbmumuX;
};
PullParams PullParam1 = {
    //Data
    0.97, 1.03,
    //Signal MC
    0.97, 1.03,
    //bbmumuX
    0.97, 1.03
};
PullParams PullParam2 = {
    //Data
    0.9, 1.1,
    //Signal MC
    0.9, 1.1,
    //bbmumuX
    0.9, 1.1
};

PullParams PullParam3 = {
    //Data
    0.5, 1.5,
    //Signal MC
    0.5, 1.5,
    //bbmumuX
    0.5, 1.5,
};


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
  PullParams pullLimits;
  LegAndLabelPositions legLabPos;
  TString SaveName;
};

struct CompParameters{
    TTree* tree1;
    TCut cut1;
    HistGraphics hg1;
    TString LegText1;
    TString LegOpt1;
    TString DrawOpt1;
    TTree* tree2;
    TCut cut2;
    HistGraphics hg2;
    TString LegText2;
    TString LegOpt2;
    TString DrawOpt2;
    TString plotPositions;
    TString saveTag;
    bool onlyMC;
};
// I_{0.7}
VariableInfo B_iso_7_Chi2_5_LoosePt05 = {"B_iso_7_Chi2_5_LoosePt05",
                51,0.0,1.02,
                "B Isolation", "ACH (OOO) As in Partial Run 2",
                0.0,1.02, 1E-5,1, 1,
                PullParam1,
                llPos1,
                "B_iso_7_Chi2_5_LoosePt05"
            };
VariableInfo B_iso_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127 = {"B_iso_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127",
                51,0.0,1.02,
                "B Isolation", "BDI (PVP)  As in Run 1",
                0.0,1.02, 1E-5,1, 1,
                PullParam1,
                llPos1,
                "B_iso_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127"
            };
VariableInfo B_iso_10_noChi2_LooSiHi1Pt05_T0134217728 = {"B_iso_10_noChi2_LooSiHi1Pt05_T0134217728",
                51,0.0,1.02,
                "B Isolation", "BEJ (PPP) Custom TVA",
                0.0,1.02, 1E-5,1, 1,
                PullParam1,
                llPos1,
                "B_iso_10_noChi2_LooSiHi1Pt05_T0134217728"
            };
VariableInfo B_iso_10_noChi2_LooSiHi1Pt05_T0008388608 = {"B_iso_10_noChi2_LooSiHi1Pt05_T0008388608",
                51,0.0,1.02,
                "B Isolation", "BGJ (PPP) Loose TVA",
                0.0,1.02, 1E-5,1, 1,
                PullParam1,
                llPos1,
                "B_iso_10_noChi2_LooSiHi1Pt05_T0008388608"
            };

VariableInfo muP_iso_7_Chi2_5_LoosePt05 = {"muP_iso_7_Chi2_5_LoosePt05",
                51,0.0,1.02,
                "muP Isolation","ACH (OOO) As in Partial Run 2",
                0.0,1.02, 1E-5,1, 1,
                PullParam1,
                llPos1,
                "muP_iso_7_Chi2_5_LoosePt05"
            };
VariableInfo muP_iso_7_chi2_5_LoosePt05 = {"muP_iso_7_chi2_5_LoosePt05",
                51,0.0,1.02,
                "muP Isolation","ACH (OOO) As in Partial Run 2",
                0.0,1.02, 1E-5,1, 1,
                PullParam1,
                llPos1,
                "muP_iso_7_Chi2_5_LoosePt05"
            };
VariableInfo muP_iso_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127 = {"muP_iso_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127",
                51,0.0,1.02,
                "muP Isolation", "BDI (PVP)  As in Run 1",
                0.0,1.02, 1E-5,1, 1,
                PullParam1,
                llPos1,
                "muP_iso_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127"
            };
VariableInfo muP_iso_10_noChi2_LooSiHi1Pt05_T0134217728 = {"muP_iso_10_noChi2_LooSiHi1Pt05_T0134217728",
                51,0.0,1.02,
                "muP Isolation", "BEJ (PPP)  Custom TVA",
                0.0,1.02, 1E-5,1, 1,
                PullParam1,
                llPos1,
                "muP_iso_10_noChi2_LooSiHi1Pt05_T0134217728"
            };
VariableInfo muP_iso_10_noChi2_LooSiHi1Pt05_T0008388608 = {"muP_iso_10_noChi2_LooSiHi1Pt05_T0008388608",
                51,0.0,1.02,
                "muP Isolation", "BGJ (PPP) Loose TVA",
                0.0,1.02, 1E-5,1, 1,
                PullParam1,
                llPos1,
                "muP_iso_10_noChi2_LooSiHi1Pt05_T0008388608"
            };

VariableInfo muM_iso_7_Chi2_5_LoosePt05 = {"muM_iso_7_Chi2_5_LoosePt05",
                51,0.0,1.02,
                "muM Isolation", "ACH (OOO) As in Partial Run 2",
                0.0,1.02, 1E-5,1, 1,
                PullParam1,
                llPos1,
                "muM_iso_7_Chi2_5_LoosePt05"
            };
VariableInfo muM_iso_7_chi2_5_LoosePt05 = {"muM_iso_7_chi2_5_LoosePt05",
                51,0.0,1.02,
                "muM Isolation", "ACH (OOO) As in Partial Run 2",
                0.0,1.02, 1E-5,1, 1,
                PullParam1,
                llPos1,
                "muM_iso_7_Chi2_5_LoosePt05"
            };
VariableInfo muM_iso_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127 = {"muM_iso_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127",
                51,0.0,1.02,
                "muM Isolation", "BDI (PVP)  As in Run 1",
                0.0,1.02, 1E-5,1, 1,
                PullParam1,
                llPos1,
                "muM_iso_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127"
            };
VariableInfo muM_iso_10_noChi2_LooSiHi1Pt05_T0134217728 = {"muM_iso_10_noChi2_LooSiHi1Pt05_T0134217728",
                51,0.0,1.02,
                "muM Isolation", "BEJ (PPP) Custom TVA Trk Perigee",
                0.0,1.02, 1E-5,1, 1,
                PullParam1,
                llPos1,
                "muM_iso_10_noChi2_LooSiHi1Pt05_T0134217728"
            };
VariableInfo muM_iso_10_noChi2_LooSiHi1Pt05_T0008388608 = {"muM_iso_10_noChi2_LooSiHi1Pt05_T0008388608",
                51,0.0,1.02,
                "muM Isolation", "BGJ (PPP) Loose TVA",
                0.0,1.02, 1E-5,1, 1,
                PullParam1,
                llPos1,
                "muM_iso_10_noChi2_LooSiHi1Pt05_T0008388608"
            };
// (I^{B}_{0.7, loose, pt>0.5})
VariableInfo B_iso_Ntracks_7_Chi2_5_LoosePt05 = {"B_iso_Ntracks_7_Chi2_5_LoosePt05",
                16,0,16,
                "Ntracks B Isolation", "ACH (OOO) As in Partial Run 2",
                0.0,16, 0, 1, 0,
                PullParam1,
                llPos1,
                "B_iso_Ntracks_7_Chi2_5_LoosePt05"
                };
VariableInfo B_iso_Ntracks_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127 = {"B_iso_Ntracks_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127",
                16,0,16,
                "Ntracks B Isolation", "BDI (PVP)  As in Run 1",
                0.0,16, 0, 1, 0,
                PullParam1,
                llPos1,
                "B_iso_Ntracks_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127"
            };
VariableInfo B_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0134217728 = {"B_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0134217728",
                16,0,16,
                "Ntracks B Isolation",  "BEJ (PPP) Custom TVA",
                0.0,16, 0, 1, 0,
                PullParam1,
                llPos1,
                "B_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0134217728"
            };
VariableInfo B_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0008388608 = {"B_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0008388608",
                16,0,16,
                "Ntracks B Isolation", "BGJ (PPP) Loose TVA",
                0.0,16, 0, 1, 0,
                PullParam1,
                llPos1,
                "B_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0008388608"
            };

VariableInfo muP_iso_Ntracks_7_Chi2_5_LoosePt05 = {"muP_iso_Ntracks_7_Chi2_5_LoosePt05",
                16,0,16,
                "Ntracks muP Isolation", "ACH (OOO) As in Partial Run 2",
                0.0,16, 0, 1, 0,
                PullParam1,
                llPos1,
                "muP_iso_Ntracks_7_Chi2_5_LoosePt05"
            };
VariableInfo muP_iso_Ntracks_7_chi2_5_LoosePt05 = {"muP_iso_Ntracks_7_chi2_5_LoosePt05",
                16,0,16,
                "Ntracks muP Isolation", "ACH (OOO) As in Partial Run 2",
                0.0,16, 0, 1, 0,
                PullParam1,
                llPos1,
                "muP_iso_Ntracks_7_Chi2_5_LoosePt05"
            };
VariableInfo muP_iso_Ntracks_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127 = {"muP_iso_Ntracks_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127",
                16,0,16,
                "Ntracks muP Isolation", "BDI (PVP)  As in Run 1",
                0.0,16, 0, 1, 0,
                PullParam1,
                llPos1,
                "muP_iso_Ntracks_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127"
            };
VariableInfo muP_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0134217728 = {"muP_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0134217728",
                16,0,16,
                "Ntracks muP Isolation",  "BEJ (PPP) Custom TVA",
                0.0,16, 0, 1, 0,
                PullParam1,
                llPos1,
                "muP_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0134217728"
            };
VariableInfo muP_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0008388608 = {"muP_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0008388608",
                16,0,16,
                "Ntracks muP Isolation", "BGJ (PPP) Loose TVA",
                0.0,16, 0, 1, 0,
                PullParam1,
                llPos1,
                "muP_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0008388608"
            };

VariableInfo muM_iso_Ntracks_7_Chi2_5_LoosePt05 = {"muM_iso_Ntracks_7_Chi2_5_LoosePt05",
                16,0,16,
                "Ntracks muM Isolation", "ACH (OOO) As in Partial Run 2",
                0.0,16, 0, 1, 0,
                PullParam1,
                llPos1,
                "muM_iso_Ntracks_7_Chi2_5_LoosePt05"
            };
VariableInfo muM_iso_Ntracks_7_chi2_5_LoosePt05 = {"muM_iso_Ntracks_7_chi2_5_LoosePt05",
                16,0,16,
                "Ntracks muM Isolation", "ACH (OOO) As in Partial Run 2",
                0.0,16, 0, 1, 0,
                PullParam1,
                llPos1,
                "muM_iso_Ntracks_7_Chi2_5_LoosePt05"
            };
VariableInfo muM_iso_Ntracks_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127 = {"muM_iso_Ntracks_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127",
                16,0,16,
                "Ntracks muM Isolation", "BDI (PVP) As in Run 1",
                0.0,16, 0, 1, 0,
                PullParam1,
                llPos1,
                "muM_iso_Ntracks_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127"
            };
VariableInfo muM_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0134217728 = {"muM_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0134217728",
                16,0,16,
                "Ntracks muM Isolation",  "BEJ (PPP) Custom TVA",
                0.0,16, 0, 1, 0,
                PullParam1,
                llPos1,
                "muM_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0134217728"
            };
VariableInfo muM_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0008388608 = {"muM_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0008388608",
                16,0,16,
                "Ntracks muM Isolation", "BGJ (PPP) Loose TVA",
                0.0,16, 0, 1, 0,
                PullParam1,
                llPos1,
                "muM_iso_Ntracks_10_noChi2_LooSiHi1Pt05_T0008388608"
            };

VariableInfo closeTrkDOCA_3 = {"closeTrkDOCA_3",
                61,0.0,3.05,
                "DOCA_{xtrk} [mm]", "ACK (OOO) As in Partial Run 2",
                0.0,3.05, 1E-4,1, 1,
                PullParam1,
                llPos1,
                "closeTrkDOCA_3"
            };
VariableInfo closeTrkDOCA = {"closeTrkDOCA",
                61,0.0,3.05,
                "DOCA_{xtrk} [mm]", "ACK (OOO) As in Partial Run 2",
                0.0,3.05, 1E-4,1, 1,
                PullParam1,
                llPos1,
                "closeTrkDOCA_3"
            };
VariableInfo closeTrkDOCA_T0134217728_LooSiHi1Pt05_f2dc2 = {"closeTrkDOCA_T0134217728_LooSiHi1Pt05_f2dc2",
                61,0.0,3.05,
                "DOCA_{xtrk} [mm]", "BEL (PPP) Custom TVA",
                0.0,3.05, 1E-4,1, 1,
                PullParam1,
                llPos1,
                "closeTrkDOCA_T0134217728_LooSiHi1Pt05_f2dc2"
            };
VariableInfo closeTrkDOCA_T0008388608_LooSiHi1Pt05_f2dc2 = {"closeTrkDOCA_T0008388608_LooSiHi1Pt05_f2dc2",
                61,0.0,3.05,
                "DOCA_{xtrk} [mm]", "BGL (PPP) Loose TVA",
                0.0,3.05, 1E-4,1, 1,
                PullParam1,
                llPos1,
                "closeTrkDOCA_T0008388608_LooSiHi1Pt05_f2dc2"
            };

VariableInfo closeTrkNtrksChi2 = {"closeTrkNtrksChi2",
                80,0,80,
                "N^{clos}_{trk}", "ACK (OOO) As in Partial Run 2",
                0.0,80.0, 1E-4,1, 1,
                PullParam1,
                llPos1,
                "closeTrkNtrksChi2"
            };
VariableInfo closeTrkNtrksChi2_T0134217728_LooSiHi1Pt05_f2dc2 = {"closeTrkNtrksChi2_T0134217728_LooSiHi1Pt05_f2dc2",
                80,0,80,
                "N^{clos}_{trk}", "BEL (PPP) Custom TVA",
                0.0,80.0, 1E-4,1, 1,
                PullParam1,
                llPos1,
                "closeTrkNtrksChi2_T0134217728_LooSiHi1Pt05_f2dc2"
            };
VariableInfo closeTrkNtrksChi2_T0008388608_LooSiHi1Pt05_f2dc2 = {"closeTrkNtrksChi2_T0008388608_LooSiHi1Pt05_f2dc2",
                80,0,80,
                "N^{clos}_{trk}", "BGL (PPP) Loose TVA",
                0.0,80.0, 1E-4,1, 1,
                PullParam1,
                llPos1,
                "closeTrkNtrksChi2_T0008388608_LooSiHi1Pt05_f2dc2"
            };

VariableInfo a_2D = {
    "TMath::Abs(a_2D)",
    50,0.0,1.0,
    "|#alpha_{2D}| [rad]", "",
    0.0,1.0,1E-4,1, 1,
    PullParam1,
    llPos1,
    "a_2D_abs"
};
VariableInfo DR = {
    "DR",
    30,0.0,1.5,
    "#DeltaR", "",
    0.0,1.5,1E-4,1,1,
    PullParam1,
    llPos2,
    "DR"
};
VariableInfo Lxy = {
    "Lxy",
    35,0.0,3.5,
    "L_{xy} [mm]", "",
    0.0,3.5,1E-4,1,1,
    PullParam1,
    llPos2,
    "Lxy"
};
VariableInfo chi2_PVSV_log2D = {
    "chi2_PVSV_log2D",
    72,-2,16,
    "ln(#chi^{2}_{PV,DV xy})", "",
    -2,16,1E-4,1,1,
    PullParam1,
    llPos1,
    "chi2_PVSV_log2D"
};
VariableInfo d0Min_sig = {
    "TMath::Abs(d0Min_sig)",
    40,0.0,40.0,
    "|d_{0}|^{min} sig.", "",
    0.0,40.0,0,0.3,0,
    PullParam2,
    llPos2,
    "d0Min_sig_abs"
};
VariableInfo d0Max_sig = {
    "TMath::Abs(d0Max_sig)",
    50,0.0,50.0,
    "|d_{0}|^{max} sig.", "",
    0.0,50.0,0,0.3,0,
    PullParam2,
    llPos2,
    "d0Max_sig_abs"
};
VariableInfo B_pT = {
    "B_pT",
    70,5,40,
    "p_{T}^{B} [GeV]", "",
    5,40,1E-4,1,1,
    PullParam1,
    llPos2,
    "B_pT"
};
VariableInfo PlngMin2D = {
    "PlngMin2D",
    25,0,25,
    "P^{min}_{L} [GeV]", "",
    0,25,0,0.4,0,
    PullParam1,
    llPos2,
    "PlngMin2D"
};
VariableInfo B_IDtrks_DCA = {
    "TMath::Abs(B_IDtrks_DCA)",
    40,0,0.4,
    "DOCA_{#mu#mu} [mm]", "",
    0,0.4,1E-4,1,1,
    PullParam2,
    llPos2,
    "B_IDtrks_DCA_abs"
}; 
VariableInfo B_IDtrks_deltaPhi = {
    "TMath::Abs(B_IDtrks_deltaPhi)",
    70,0.0,1.4,
    "|#Delta#phi_{#mu#mu}|", "",
    0.0,1.4,1E-4,1,1,
    PullParam1,
    llPos1,
    "B_IDtrks_deltaPhi_abs"
};
VariableInfo Bvtx3DIP = {
    "Bvtx3DIP",
    60,0.0,2.0,
    "|IP_{B}^{3D}|", "",
    0.0,2.0,1E-4,1,1,
    PullParam2,
    llPos2,
    "Bvtx3DIP"
};
VariableInfo B_eta = {
    "B_eta",
    60,-3.0,3.0,
    "#eta^{B}", "",
    -3.0,3.0,0,0.05,0,
    PullParam1,
    llPos1,
    "B_eta"
};
// VariableInfo = {"B_eta",50,-2.,2.,false,"#eta^{B}",false, "zoom", true, 0.0, true, 0.0, 3.5},
VariableInfo B_fitChi2NDF = {
    "B_fitChi2NDF",
    24,0,6,
    "#chi^{2}_{B}/NDF", "",
    0,6,0,0.5,0,
    PullParam2,
    llPos1,
    "B_fitChi2NDF"
};
VariableInfo Npv = {
    "Npv",
    // 30,-0.5,29.5,
    30,0.,30.,
    "nPV", "",
    -0.5,30.5,0,0.25,0,
    // PullParam1, //used for new/old ntuple comps
    PullParam3,
    llPos1,
    "Npv"
};
VariableInfo Lxy_sig = {
    "Lxy_sig",
    80,0,80,
    "BvtxLxy signif.", "",
    0,80,0,0.3,0,
    PullParam2,
    llPos2,
    "Lxy_sig"
};
VariableInfo B_MUCALC_massErr = {
    "B_MUCALC_massErr",
    40,30,130,
    "#delta m_{#mu#mu} [MeV]", "",
    30,130,0,0.15,0,
    PullParam1,
    llPos1,
    "B_MUCALC_massErr"
};
VariableInfo properTime_sig = {
    "properTime_sig",
    65,-10,120,
    "ct significance", "",
    -10,120,1E-4,1,1,
    PullParam1,
    llPos2,
    "properTime_sig"
};
VariableInfo properTime = {
    "properTime",
    90,0,15,
    "ct", "",
    0,15,1E-4,1,1,
    PullParam1,
    llPos2,
    "properTime"
};
// VariableInfo = {"properTime",30,6,14,true,"ct",true, "zoom", true, 0.0, false, 0.0, 3.5},
VariableInfo PRIVX_mu = {
    "PRIVX_mu",
    // 35,0,35,
    // 41,-1.,45.33,
    40,0.,45.2,//number 7
    // 41,0.,46.33, //number 8
    // 31,0.,35.03,//number 6
    "#mu PRIVX", "",
    // -1,45,0,0.2,0,
    0,45,0,0.2,0,//number 7
    // 0,46,0,0.2,0,//number 8
    // 0,35,0,0.2,0,//number 6
    PullParam2,//was PullParam1 for new/old nTuple comps
    llPos1,
    "PRIVX_mu"
};
VariableInfo PRIVX_mu_round = {
    "PRIVX_mu_round",
    // 35,0,35,
    // 41,-1.,45.33,
    40,0.,45.2,//number 7
    // 41,0.,46.33, //number 8
    // 31,0.,35.03,//number 6
    "#mu PRIVX", "",
    // -1,45,0,0.2,0,
    0,45,0,0.2,0,//number 7
    // 0,46,0,0.2,0,//number 8
    // 0,35,0,0.2,0,//number 6
    PullParam2,//was PullParam1 for new/old nTuple comps
    llPos1,
    "PRIVX_mu"
};
VariableInfo B_MUCALC_mass = {
    "B_MUCALC_mass",
    60,4766,5966,
    "m_{#mu#mu} [MeV]", "",
    4766,5966,0,0.1,0,
    PullParam1,
    llPos1,
    "B_MUCALC_mass"
};
VariableInfo B_MUCALCovermassErr= {
    "B_MUCALC_mass/B_MUCALC_massErr",
    30,0,180,
    // 100,0,600,
    "m_{#mu#mu} /#Deltam_{#mu#mu}", "",
    0,180,0,0.25,0,
    PullParam1,
    llPos1,
    "B_MUCALC_massovermassErr"
};
VariableInfo Muon1_etcone30 = {
    "Muon1_etcone30",
    220,-20000,200000,
    "Muon1_etcone30", "",
    -20000,200000,1E-4,1,1,
    PullParam2,
    llPos1,
    "Muon1_etcone30"
};
VariableInfo Muon2_etcone30 = {
    "Muon2_etcone30",
    220,-20000,200000,
    "Muon2_etcone30", "",
    -20000,200000,1E-4,1,1,
    PullParam2,
    llPos1,
    "Muon2_etcone30"
};
VariableInfo Muon1_etcone40 = {
    "Muon1_etcone40",
    220,-20000,200000,
    "Muon1_etcone40", "",
    -20000,200000,1E-4,1,1,
    PullParam2,
    llPos1,
    "Muon1_etcone40"
};
VariableInfo Muon2_etcone40 = {
    "Muon2_etcone40",
    220,-20000,200000,
    "Muon2_etcone40", "",
    -20000,200000,1E-4,1,1,
    PullParam2,
    llPos1,
    "Muon2_etcone40"
};
VariableInfo Muon1_nucone30 = {
    "Muon1_nucone30",
    200,0,200,
    "Muon1_nucone30", "",
    0,200,1E-4,1,1,
    PullParam2,
    llPos1,
    "Muon1_nucone30"
};
VariableInfo Muon2_nucone30 = {
    "Muon2_nucone30",
    200,0,200,
    "Muon2_nucone30", "",
    0,200,1E-4,1,1,
    PullParam2,
    llPos1,
    "Muon2_nucone30"
};
VariableInfo Muon1_nucone40 = {
    "Muon1_nucone40",
    200,0,200,
    "Muon1_nucone40", "",
    0,200,1E-4,1,1,
    PullParam2,
    llPos1,
    "Muon1_nucone40"
};
VariableInfo Muon2_nucone40 = {
    "Muon2_nucone40",
    200,0,200,
    "Muon2_nucone40", "",
    0,200,1E-4,1,1,
    PullParam2,
    llPos1,
    "Muon2_nucone40"
};
VariableInfo B_PV_Ref_z = {
    "B_PV_Ref_z",
    40,-200,200,
    "B_PV_ref_z", "",
    -200,200,0,0.25,0,
    PullParam1,
    llPos1,
    "B_PV_Ref_z"
};
VariableInfo chi2_PVSV_log1Dz = {
    "chi2_PVSV_log1Dz",
    52,-14,12,
    "Log(#chi^{2}_{z})", "",
    -14,12,0,0.3,0,
    PullParam2,
    llPos1,
    "chi2_PVSV_log1Dz"
};
VariableInfo DecayCoplanarity = {
    "DecayCoplanarity",
    120,0,12000,
    "coplan._{#Deltax,#mu1,#mu2}", "",
    0,12000,1E-4,1,1,
    PullParam2,
    llPos1,
    "DecayCoplanarity"
};
VariableInfo MuSignedd0SigMin = {
    "MuSignedd0SigMin",
    200,-50,150,
    "sd_{0}^{min} signif.", "",
    -50,150,0,0.4,0,
    PullParam2,
    llPos1,
    "MuSignedd0SigMin"
};
VariableInfo CoplanaritywithZ = {
    "CoplanaritywithZ",
    180,0,18000,
    "coplan._{#Deltax,#mu#mu,z}", "",
    0,18000,1E-4,1,1,
    PullParam2,
    llPos1,
    "CoplanaritywithZ"
};
VariableInfo BvtxDXSig = {
    "BvtxDXSig",
    70,0,140,
    "|#Deltax_{3D}| signif.", "",
    0,140,0,0.5,0,
    PullParam2,
    llPos2,
    "BvtxDXSig"
};
VariableInfo BvtxDXSig2D = {
    "BvtxDXSig2D",
    70,0,140,
    "|#Deltax_{2D}| signif.", "",
    0,140,0,0.5,0,
    PullParam2,
    llPos2,
    "BvtxDXSig2D"
};
VariableInfo PlngMax2D = {
    "PlngMax2D",
    40,0,40,
    "P^{max}_{L} [GeV]", "",
    0,40,0,0.4,0,
    PullParam1,
    llPos2,
    "PlngMax2D"
};
// VariableInfo = {"B_iso_Ntracks_7_Chi2_5_MedPt05",25,0,25,false,"number of tracks in iso cone",false, "zoom", false, 0.0, false, 0.0, 3.5},
// VariableInfo = {"BDT_bb_2012",80,-0.8,0.8,false,"BDT output",false, "zoom", false, 0.0, false, 0.0, 3.5},
// VariableInfo = {"BDT_bb_2012",80,-0.8,0.8,false,"BDT output",false, "zoom", false, 0.0, false, 0.0, 3.5},
// VariableInfo = {"UpdatedClassBDT",32,-0.8,0.8,false,"BDT output",false, "zoom", false, 0.0, false, 0.0, 3.5},
// VariableInfo = {"B_iso_Ntracks_7_Chi2_5_MedPt05",25,0,25,false,"number of tracks in iso cone",false, "zoom", false, 0.0, false, 0.0, 3.5},
VariableInfo B_pT_error = {
    "B_pT_error",
    100,0,3000,
    "#delta p_{T}^{B} [MeV]", "",
    0,3000,0,0.15,0,
    PullParam2,
    llPos2,
    "B_pT_error"
};
VariableInfo Lxy_err = {
    "Lxy_err",
    60,0.0,0.6,
    "BvtxLxyErr", "",
    0.0,0.6,1E-4,1,1,
    PullParam2,
    llPos2,
    "Lxy_err"
};
VariableInfo d0Min = {
    "TMath::Abs(d0Min)",
    40,0.0,2.0,
    "|d_{0}|^{min} [mm]", "",
    0.0,2.0,1E-4,1,1,
    PullParam2,
    llPos2,
    "d0Min_abs"
};
VariableInfo d0Max = {
    "TMath::Abs(d0Max)",
    60,0.0,3.0,
    "|d_{0}|^{max} [mm]", "",
    0.0,3.0,1E-4,1,1,
    PullParam2,
    llPos2,
    "d0Max_abs"
};
// VariableInfo = {"d0Min",80,-2.0,2.0,true,"d_{0}^{min} [mm]",true, "zoom", false, 0.0, false, 0.0, 3.5},
// VariableInfo = {"d0Min",50,-0.4,0.4,true,"d_{0}^{min} [mm]",true, "zoom1", true, 0.4, false, 0.75, 1.25},
// VariableInfo = {"d0Min",50,-0.2,0.2,true,"d_{0}^{min} [mm]",true, "zoom2", true, 0.2, false, 0.75, 1.25},
// VariableInfo = {"d0Min",50,-0.07,0.07,true,"d_{0}^{min} [mm]",true, "zoom3", true, 0.07, false, 0.75, 1.25},
// VariableInfo = {"d0Max",120,-3.0,3.0,true,"d_{0}^{max} [mm]",true, "zoom", false, 0.0, false, 0.75, 3.5},
// VariableInfo = {"d0Max",50,-0.6,0.6,true,"d_{0}^{max} [mm]",true, "zoom1", true, 0.6, false, 0.75, 2.0},
// VariableInfo = {"d0Max",50,-0.3,0.3,true,"d_{0}^{max} [mm]",true, "zoom2", true, 0.3, false, 0.75, 2.0},
VariableInfo d0Min_err = {
    "d0Min_err",
    40,0.0,0.1,
    "d_{0}^{min} err. [mm]", "",
    0.0,0.1,1E-4,1,1,
    PullParam2,
    llPos2,
    "d0Min_err"
};
VariableInfo d0Max_err = {
    "d0Max_err",
    60,0.0,0.15,
    "d_{0}^{max} err. [mm]", "",
    0.0,0.15,1E-4,1,1,
    PullParam2,
    llPos2,
    "d0Max_err"
};
VariableInfo B_IDtrks_deltaEta = {
    "TMath::Abs(B_IDtrks_deltaEta)",
    28,0.0,1.4,
    "|#eta_{#mu1}-#eta_{#mu2}|", "",
    0.0,1.4,1E-4,1,1,
    PullParam1,
    llPos1,
    "B_IDtrks_deltaEta_abs"
};
VariableInfo B_IDtrks_deltaR = {
    "TMath::Sqrt(pow(B_IDtrks_deltaEta, 2) + pow(B_IDtrks_deltaPhi, 2))", 
    28,0.0,1.4,
    "|#Delta R_{#mu #mu}|", "",
    0.0,1.4,1E-4,1,1,
    PullParam1,
    llPos1,
    "B_IDtrks_deltaR"
};
VariableInfo B_pT_sig = {
    "B_pT_sig",
    // 70,0,840,
    10,0,120,
    "p_{T}^{B} sig.", "",
    0,120,0,0.4,0,
    PullParam1,
    llPos1,
    "B_pT_sig"
};
// VariableInfo = {"muP_iso_Ntracks_7_chi2_5_medPt05",25,0,25,false,"N^{Iso 0.7, #mu+}_{trk}",false, "zoom", false, 0.0, false, 0.0, 3.5},
// VariableInfo = {"muM_iso_Ntracks_7_chi2_5_medPt05",25,0,25,false,"N^{Iso 0.7, #mu-}_{trk}",false, "zoom", false, 0.0, false, 0.0, 3.5},
// VariableInfo = {"muP_iso_7_chi2_5_medPt05",-1,0.0,1.1,false,"#mu+ Isolation (I^{#mu+}_{0.7})",false, "zoom", false, 0.0, false, 0.0, 3.5},
// VariableInfo = {"muM_iso_7_chi2_5_medPt05",-1,0.0,1.1,false,"#mu- Isolation (I^{#mu-}_{0.7})",false, "zoom", false, 0.0, false, 0.0, 3.5},
VariableInfo Muon1_eta = {
    "Muon1_eta",
    60,-3.0,3.0,
    "#eta_{#mu_{1}}", "",
    -3.0,3.0,0,0.07,0,
    PullParam1,
    llPos1,
    "Muon1_eta"
};
VariableInfo Muon1_pT = {
    "Muon1_pT",
    100,0,50,
    "p_{T}^{#mu_{1}} [GeV]", "",
    0,50,1E-4,1,1,
    PullParam2,
    llPos2,
    "Muon1_pT"
};
VariableInfo Muon2_eta = {
    "Muon2_eta",
    60,-3.0,3.0,
    "#eta_{#mu_{2}}", "",
    -3.0,3.0,0,0.07,0,
    PullParam1,
    llPos1,
    "Muon2_eta"
};
VariableInfo Muon2_pT = {
    "Muon2_pT",
    100,0,50,
    "p_{T}^{#mu_{2}} [GeV]", "",
    0,50,1E-4,1,1,
    PullParam2,
    llPos2,
    "Muon2_pT"
};
VariableInfo B_minChi2MuonsIPtoAnyPV = {
    "B_minChi2MuonsIPtoAnyPV",
    80,-10,10,
    "#chi^{2}_{#mu,xPV}", "",
    -10,10,0,0.22,0,
    PullParam2,
    llPos1,
    "B_minChi2MuonsIPtoAnyPV"
};
VariableInfo varMCweightsAll = {
    "PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf*CombWeights*Muon1_trigger_sf*Muon2_trigger_sf",
    60,-0.04,2.56,
    "MC Weights (PV*reco*trig*QLC*DDW)", "",
    -0.04,2.56,1E-4,1,1,
    PullParam3,
    llPos2,
    "MCWeightsAll"
};
VariableInfo varMCweights = {
    "PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf",
    60,-0.04,2.56,
    "PV Weights * Muon Reco Eff SFs", "",
    -0.04,2.56,1E-4,1,1,
    PullParam3,
    llPos2,
    "PVWeightsMuonReco"
};
VariableInfo varPVWeights = {
    "PVWeights",
    60,-0.04,2.56,
    "PV Weights", "",
    -0.04,2.56,1E-4,1,1,
    PullParam3,
    llPos2,
    "PVWeights"
};
VariableInfo varMuon1_reco_eff_sf = {
    "Muon1_reco_eff_sf",
    200,0.8,1.2,
    "#mu_{1} Reco Eff SF", "",
    0.8,1.2,1E-4,1,1,
    PullParam3,
    llPos1,
    "mu1RecoEffSF"
};
VariableInfo varMuon2_reco_eff_sf = {
    "Muon2_reco_eff_sf",
    200,0.8,1.2,
    "#mu_{2} Reco Eff SF", "",
    0.8,1.2,1E-4,1,1,
    PullParam3,
    llPos1,
    "mu2RecoEffSF"
};
VariableInfo varMuon1_trigger_sf = {
    "Muon1_trigger_sf",
    200,0.8,1.2,
    "#mu_{1} Trigger SF", "",
    0.8,1.2,1E-4,1,1,
    PullParam2,
    llPos1,
    "mu1TriggerSF"
};
VariableInfo varMuon2_trigger_sf = {
    "Muon2_trigger_sf",
    200,0.8,1.2,
    "#mu_{2} Trigger SF", "",
    0.8,1.2,1E-4,1,1,
    PullParam2,
    llPos1,
    "mu2TriggerSF"
};
VariableInfo varCombWeights = {
    "CombWeights",
    200,0.5,2.5,
    "QLC*DDW", "",
    0.5,2.5,1E-4,1,1,
    PullParam2,
    llPos2,
    "CombWeights"
};
VariableInfo NPVweight = {
    "NPVweight",
    50, 0.5, 1.5,
    "NPV weight", "",
    0.5,1.5,0.,0.3,0,
    PullParam2,
    llPos2,
    "NPVweight"
};
VariableInfo NPVweightdata = {//this is a way to trick root because npvweights is not in data.
    "Muon1_trigger_sf",
    25, 0.5, 1.5,
    "NPV weight", "",
    0.5,1.5,0.,0.3,0,
    PullParam2,
    llPos2,
    "NPVweight"
};
VariableInfo varMCweightsAllnpv = {
    "NPVweight*PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf*CombWeights*Muon1_trigger_sf*Muon2_trigger_sf",
    60,-0.04,2.56,
    "MC Weights (PV*reco*trig*QLC*DDW*nPV)", "",
    -0.04,2.56,1E-4,1,1,
    PullParam3,
    llPos2,
    "MCWeightsAllnpv"
};


// VariableInfo = {"TMath::Sqrt(pow(closeTrkDCA,2)+pow(closeTrkZCA,2))",40,0,2,true,"DOCA_{xtrk, loose, pt>0.5} [mm]",true, "zoom", false, 0.0, false, 0.5, 1.5},

VariableInfo AllVarsArray[43] = {
    a_2D,
    DR,
    Lxy,
    chi2_PVSV_log2D,
    d0Min_sig,
    d0Max_sig,
    B_pT,
    PlngMin2D,
    B_IDtrks_DCA,
    B_IDtrks_deltaPhi,
    Bvtx3DIP,
    B_eta,
    B_fitChi2NDF,
    Npv,
    Lxy_sig,
    B_MUCALC_massErr,
    properTime_sig,
    properTime,
    PRIVX_mu,
    PRIVX_mu_round,
    B_MUCALC_mass,
    B_MUCALCovermassErr,
    // Muon1_etcone30,
    // Muon2_etcone30,
    // Muon1_etcone40,
    // Muon2_etcone40,
    // Muon1_nucone30,
    // Muon2_nucone30,
    // Muon1_nucone40,
    // Muon2_nucone40,
    B_PV_Ref_z,
    chi2_PVSV_log1Dz,
    DecayCoplanarity,
    MuSignedd0SigMin,
    CoplanaritywithZ,
    BvtxDXSig,
    BvtxDXSig2D,
    PlngMax2D,
    B_pT_error,
    Lxy_err,
    d0Min,
    d0Max,
    d0Min_err,
    d0Max_err,
    B_IDtrks_deltaEta,
    B_IDtrks_deltaR,
    // B_pT_sig,
    Muon1_eta,
    Muon1_pT,
    Muon2_eta,
    Muon2_pT,
    B_minChi2MuonsIPtoAnyPV
};
