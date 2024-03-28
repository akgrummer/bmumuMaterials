import collections

VariableInfo = collections.namedtuple('VariableInfo', 'name, \
  nbins, XMin, XMax, logScale, axLabel, usedForSystematics, LatexName')

Variables = [VariableInfo("TMath_Abs(a_2D)", 50, 0, 1.0, True, "|#alpha_{2D}| [rad]", True, r'$|\alpha_{2D}|$'),
    #   VariableInfo("TMath_Abs(a_3D)",60,0,1.5,True,"|#alpha_{3D}| [rad]",True, ""),
    VariableInfo("DR",30,0,1.5,True,"#DeltaR",True, "$\Delta R$"),
    VariableInfo("Lxy",40,-0.5,3.5,False,"L_{xy} [mm]",True, "$L_{xy}$"),
    VariableInfo("chi2_PVSV_log2D",60,-6,12,False,"Log(#chi^{2}_{xy})",True, "$ln(\chi^{2}_{xy})$"),  
    VariableInfo("TMath_Abs(d0Min_sig)",40,0.0,40.0,False,"|d_{0}|^{min}sig.",True, "$d^0_{min, sig}$"),
    VariableInfo("TMath_Abs(d0Max_sig)",50,0.0,50.0,False,"|d_{0}|^{max}sig.",True, "$d^0_{max, sig}$"),
    # VariableInfo("B_iso_7_Chi2_5_LoosePt05",60,0.0,1.05,True,"BIsolation(I^{B}_{0.7})",True, "B Isolation $(I^{B}_{0.7})$"),
    VariableInfo("B_iso_7_Chi2_5_LoosePt05_AllTrks",60,0.0,1.05,True,"I_{0.7}",True, "B Isolation $(I^{B}_{0.7})$ (All Trks)"),
    VariableInfo("B_iso_Ntracks_7_Chi2_5_LoosePt05",16,0,16,True,"Ntracks B Isolation (I^{B}_{0.7, loose, pt>0.5})",True, ""),

    #   VariableInfo("B_pT",-1,10000,100000,True,"p_{T}^{B} [GeV]",True, ""),
    VariableInfo("B_pT",70,5,40,True,"p_{T}^{B} [GeV]",True, "$p^B_{T}$"),
    VariableInfo("PlngMin2D",25,0,25,False,"P^{min}_{L} [GeV]",True, "$P^{min}_{L}$"),
    VariableInfo("closeTrkNtrksChi2LoosePt05",60,0,60,True,"N^{clos}_{trk, loose, pt>0.5}",False, ""), # Aidan set to False - not in data files
    # VariableInfo("closeTrkNtrksChi2",60,0,60,True,"N^{clos}_{trk, loose, pt>0.5}",True, "Log(\chi^{2}_{xy})"),# added with new MC HLT_mu6_mu4_bBmumu_Lxy0
    # VariableInfo("closeTrkNtrksChi2",60,0,60,True,"N^{clos}_{trk,loose,pt>0.5}",True, "$N^{clos}_{trk}$"),# added with new MC HLT_mu6_mu4_bBmumu_Lxy0
    # VariableInfo("closeTrkNtrksChi2",60,0,60,True,"N^{clos}_{trk}",True, "$N^{clos}_{trk}$"),# added with new MC HLT_mu6_mu4_bBmumu_Lxy0
    # VariableInfo("closeTrkNtrksChi2_AllTrks",60,0,60,True,"N^{clos}_{trk,loose,pt>0.5}",True, "$N^{clos}_{trk}$ (All Trks)"),# added with new MC HLT_mu6_mu4_bBmumu_Lxy0


    VariableInfo("TMath_Abs(B_IDtrks_DCA)",80,0,0.4,True,"DOCA_{#mu#mu} [mm]",True, "$DOCA_{\mu\mu}$"), 
    VariableInfo("TMath_Abs(B_IDtrks_deltaPhi)",70,0.0,1.4,True,"|#Delta#phi_{#mu#mu}|",True, "$|\Delta \phi_{\mu\mu}|$"),
    # VariableInfo("closeTrkDOCALoosePt05",40,0,2,True,"DOCA_{xtrk, loose, pt>0.5} [mm]",False, ""), # Aidan set to False - not in data files
    VariableInfo("TMath_Sqrt(pow(closeTrkDCA,2)+pow(closeTrkZCA,2))",40,0,2,True,"DOCA_{xtrk,loose,pt>0.5}[mm]",False, "$DOCA_{xtrk,loose,pt>0.5}$"), # Aidan set to False - not in data files
    # VariableInfo("closeTrkDOCA",40,0,2,True,"DOCA_{xtrk,loose,pt>0.5}[mm]",False, "$DOCA_{xtrk,loose,pt>0.5}$"), # Aidan set to False - not in data files
    # VariableInfo("closeTrkDOCA_AllTrks2",40,0,2,True,"$DOCA_{xtrk,loose,pt>0.5}$",False, "$DOCA_{xtrk,loose,pt>0.5}$ (All Trks)"), # Aidan set to False - not in data files

    VariableInfo("Bvtx3DIP",60,0,2.0,True,"|IP_{B}^{3D}|",True, "$|IP_{B}^{3D}|$"), # 0.6
    VariableInfo("B_minChi2MuonsIPtoAnyPV",80,-10,10,False,"Log(#chi^{2}_{#mu,xPV})",True, "$log(\chi^{2}_{\mu,xPV})$"), # n.y implemented


    VariableInfo("B_eta",-1,-3.0,3.0,False,"#eta^{B}",True, ""),
    VariableInfo("B_fitChi2NDF",24,0,6,False,"#chi^{2}_{B}/NDF",True, ""),
    # VariableInfo("Npv",30,-0.5,29.5,False,"PVmultiplicity",True, "PV multiplicity"),
    VariableInfo("Lxy_sig",80,0,80,False,"BvtxLxy signif.",True, ""),
    VariableInfo("B_MUCALC_massErr",40,30,430,False,"#delta m_{#mu#mu} [MeV]",True, ""),
    #   VariableInfo("properTime_sig",65,-10,120,False,"ct significance",True, ""),

    VariableInfo("B_MUCALC_mass",60,4766,5966,False,"m_{#mu#mu} [MeV]",True, ""),
    VariableInfo("B_MUCALC_mass/B_MUCALC_massErr",100,0,600,False,"m_{#mu#mu} /#Deltam_{#mu#mu}",False, ""),


    VariableInfo("Muon1_etcone30",220,-20000,200000,True,"Muon1_etcone30",True, ""),
    VariableInfo("Muon2_etcone30",220,-20000,200000,True,"Muon2_etcone30",True, ""),
    VariableInfo("Muon1_etcone40",220,-20000,200000,True,"Muon1_etcone40",True, ""),
    VariableInfo("Muon2_etcone40",220,-20000,200000,True,"Muon2_etcone40",True, ""),
    VariableInfo("Muon1_nucone30",200,0,200,True,"Muon1_nucone30",False, ""),
    VariableInfo("Muon2_nucone30",200,0,200,True,"Muon2_nucone30",False, ""),
    VariableInfo("Muon1_nucone40",200,0,200,True,"Muon1_nucone40",False, ""),
    VariableInfo("Muon2_nucone40",200,0,200,True,"Muon2_nucone40",False, ""),


    VariableInfo("B_PV_Ref_z",40,-200,200,False,"B_PV_ref_z",True, ""),

    VariableInfo("chi2_PVSV_log1Dz",52,-14,12,False,"Log(#chi^{2}_{z})",False, ""),
    VariableInfo("DecayCoplanarity",120,0,12000,True,"coplan._{#Deltax,#mu1,#mu2}",False, ""),
    VariableInfo("MuSignedd0SigMin",200,-50,150,False,"sd_{0}^{min} signif.",False, ""),
    VariableInfo("CoplanaritywithZ",180,0,18000,True,"coplan._{#Deltax,#mu#mu,z}",False, ""),
    VariableInfo("BvtxDXSig",70,0,140,False,"|#Deltax_{3D}| signif.",False, ""),
    VariableInfo("BvtxDXSig2D",70,0,140,False,"|#Deltax_{2D}| signif.",False, ""),
    VariableInfo("PlngMax2D",40,0,40,False,"P^{max}_{L} [GeV]",False, ""),
    VariableInfo("B_iso_Ntracks_7_Chi2_5_MedPt05",25,0,25,False,"number of tracks in iso cone",False, ""),
    VariableInfo("BDT_bb_2012",80,-0.8,0.8,False,"BDT output",False, ""),



    VariableInfo("B_iso_Ntracks_7_Chi2_5_MedPt05",25,0,25,False,"number of tracks in iso cone",False, ""),
    VariableInfo("B_pT_error",100,0,3000,False,"#delta p_{T}^{B} [MeV]",False, ""),

    VariableInfo("Lxy_err",60,0,0.6,False,"BvtxLxyErr",False, ""),

    VariableInfo("TMath_Abs(d0Min)",40,0.0,2.0,True,"|d_{0}|^{min} [mm]",False, ""),
    VariableInfo("TMath_Abs(d0Max)",60,0,3.0,True,"|d_{0}|^{max} [mm]",False, ""),
    VariableInfo("d0Min_err",40,0.0,0.1,True,"d_{0}^{min} err. [mm]",False, ""),
    VariableInfo("d0Max_err",60,0.0,0.15,True,"d_{0}^{max} err. [mm]",False, ""),
    #  VariableInfo("TMath_Abs(closeTrkDCA)",100,0,0.5,True,"|D_{xy}|^{min} [mm]",False, ""),
    #  VariableInfo("TMath_Abs(closeTrkZCA)",100,0,0.5,True,"|D_{z}|^{min} [mm]",False, ""),
    #  VariableInfo("TMath_Abs(closeTrkDCA)",100,0,0.5,True,"|D_{xy}|^{min} [mm]",True, ""),# added with new MC HLT_mu6_mu4_bBmumu_Lxy0
    #  VariableInfo("TMath_Abs(closeTrkZCA)",100,0,0.5,True,"|D_{z}|^{min} [mm]",True, ""),# added with new MC HLT_mu6_mu4_bBmumu_Lxy0


    VariableInfo("TMath_Abs(B_IDtrks_deltaEta)",28,0.0,1.4,True,"|#eta_{#mu1}-#eta_{#mu2}|",False, ""),
    VariableInfo("B_pT_sig",70,0,840,False,"p_{T}^{B} sig.",False, ""), # 140
    VariableInfo("BDT_bb_2012",80,-0.8,0.8,False,"BDT output",False, ""), # 32,-0.8,0.8 # 60,0.15,0.7

    VariableInfo("UpdatedClassBDT",32,-0.8,0.8,False,"BDT output",False, ""),

    VariableInfo("muP_iso_Ntracks_7_chi2_5_medPt05",25,0,25,False,"N^{Iso 0.7, #mu+}_{trk}",False, ""),
    VariableInfo("muM_iso_Ntracks_7_chi2_5_medPt05",25,0,25,False,"N^{Iso 0.7, #mu-}_{trk}",False, ""),
    # VariableInfo("muP_iso_7_chi2_5_medPt05",-1,0.0,1.1,False,"#mu+ Isolation (I^{#mu+}_{0.7})",False, ""),
    # VariableInfo("muM_iso_7_chi2_5_medPt05",-1,0.0,1.1,False,"#mu- Isolation (I^{#mu-}_{0.7})",False, "")
    # VariableInfo("muP_iso_7_chi2_5_LoosePt05",-1,0.0,1.1,False,"#mu+Isolation(I^{#mu+}_{0.7})",False, "$\mu^+$ Isolation $(I^{\mu^+}_{0.7})$"),
    # VariableInfo("muM_iso_7_chi2_5_LoosePt05",-1,0.0,1.1,False,"#mu-Isolation(I^{#mu-}_{0.7})",False, "$\mu^-$ Isolation $(I^{\mu^-}_{0.7})$"), 

    VariableInfo("closeTrkDOCA_3",61,0.,3.05,True, "DOCAACK(OOO)",True,  "DOCA ACK (OOO)"),
    # VariableInfo("closeTrkDOCA_LooSiHi1Pt05_corc2cnt",61,0.,3.05,True, "DOCABCM(POV)",True, "DOCA BCM (POV)"),
    # VariableInfo("closeTrkDOCA_LooSiHi1Pt05_corc2cnt_custom",61,0.,3.05,True, "DOCABFM(PVV)CustomTVAApprox.",True, "DOCA BFM (PVV) Custom TVA Approx."),
    VariableInfo("closeTrkDOCA_T0134217728_LooSiHi1Pt05_f2dc2",61,0.,3.05,True, "DOCABEL(PPP)CustomTVATrkPerigee",True, "DOCA BEL (PPP) Custom TVA Trk Perigee"),
    # VariableInfo("closeTrkDOCA_LooSiHi1Pt05_corc2cnt_loose",61,0.,3.05,True, "DOCABGM(PPV)LooseTVAApprox.",True, "DOCA BGM (PPV) Loose TVA Approx."),
    VariableInfo("closeTrkDOCA_T0008388608_LooSiHi1Pt05_f2dc2",61,0.,3.05,True, "DOCABGL(PPP)LooseTVA",True, "DOCA BGL (PPP) Loose TVA"),

    VariableInfo("closeTrkNtrksChi2",80,0,80,True, "nCloseTracksACK(OOO)",True, "nCloseTracks ACK (OOO)"),
    # VariableInfo("closeTrkNtrksChi2_T0000000035_LooSiHi1Pt05_corc2cnt",80,0,80,True, "nCloseTracksBCM(POV)",True, "nCloseTracks BCM (POV)"),
    # VariableInfo("closeTrkNtrksChi2_T0004194304_LooSiHi1Pt05_corc2cnt",80,0,80,True, "nCloseTracksBFM(PVV)CustomTVAApprox.",True, "nCloseTracks BFM (PVV) Custom TVA Approx."),
    VariableInfo("closeTrkNtrksChi2_T0134217728_LooSiHi1Pt05_f2dc2",80,0,80,True, "nCloseTracksBEL(PPP)CustomTVATrkPerigee",True, "nCloseTracks BEL (PPP) Custom TVA Trk Perigee"),
    # VariableInfo("closeTrkNtrksChi2_T0008388608_LooSiHi1Pt05_corc2cnt",80,0,80,True, "nCloseTracksBGM(PPV)LooseTVAApprox.",True, "nCloseTracks BGM (PPV) Loose TVA Approx."),
    VariableInfo("closeTrkNtrksChi2_T0008388608_LooSiHi1Pt05_f2dc2",80,0,80,True, "nCloseTracksBGL(PPP)LooseTVA",True, "nCloseTracks BGL (PPP) Loose TVA"),

    VariableInfo("B_iso_7_Chi2_5_LoosePt05",51,0.0,1.02,True, "BIsoACH(OOO)", True, "B Iso ACH (OOO)"),
    VariableInfo("B_iso_7_Chi2_5_noAbs_LooSiHi1Pt05",51,0.0,1.02,True, "BIsoBCI(POP)", True, "B Iso BCI (POP)"),
    VariableInfo("B_iso_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127",51,0.0,1.02,True, "BIsoBDI(PVP)AsinRun1", True, "B Iso BDI (PVP) As in Run 1"),
    VariableInfo("B_iso_10_noChi2_LooSiHi1Pt05_T0004194304",51,0.0,1.02,True, "BIsoBFJ(PVP)CustomTVAApprox", True, "B Iso BFJ (PVP) Custom TVA Approx"),
    VariableInfo("B_iso_10_noChi2_LooSiHi1Pt05_T0134217728",51,0.0,1.02,True, "BIsoBEJ(PPP)CustomTVATrkPerigee", True, "B Iso BEJ (PPP) Custom TVA Trk Perigee"),
    VariableInfo("B_iso_10_noChi2_LooSiHi1Pt05_T0008388608",51,0.0,1.02,True, "BIsoBGJ(PPP)LooseTVA", True, "B Iso BGJ (PPP) Loose TVA"),

    VariableInfo("muM_iso_7_Chi2_5_LoosePt05",51,0.0,1.02,True, "muMIsoACH(OOO)", True, "muM Iso ACH (OOO)"),
    VariableInfo("muM_iso_7_Chi2_5_noAbs_LooSiHi1Pt05",51,0.0,1.02,True, "muMIsoBCI(POP)", True, "muM Iso BCI (POP)"),
    VariableInfo("muM_iso_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127",51,0.0,1.02,True, "muMIsoBDI(PVP)AsinRun1", True, "muM Iso BDI (PVP) As in Run 1"),
    VariableInfo("muM_iso_10_noChi2_LooSiHi1Pt05_T0004194304",51,0.0,1.02,True, "muMIsoBFJ(PVP)CustomTVAApprox", True, "muM Iso BFJ (PVP) Custom TVA Approx"),
    VariableInfo("muM_iso_10_noChi2_LooSiHi1Pt05_T0134217728",51,0.0,1.02,True, "muMIsoBEJ(PPP)CustomTVATrkPerigee", True, "muM Iso BEJ (PPP) Custom TVA Trk Perigee"),
    VariableInfo("muM_iso_10_noChi2_LooSiHi1Pt05_T0008388608",51,0.0,1.02,True, "muMIsoBGJ(PPP)LooseTVA", True, "muM Iso BGJ (PPP) Loose TVA"),

    VariableInfo("muP_iso_7_Chi2_5_LoosePt05",51,0.0,1.02,True, "muPIsoACH(OOO)", True, "muP Iso ACH (OOO)"),
    VariableInfo("muP_iso_7_Chi2_5_noAbs_LooSiHi1Pt05",51,0.0,1.02,True, "muPIsoBCI(POP)", True, "muP Iso BCI (POP)"),
    VariableInfo("muP_iso_7_Chi2_5_noAbs_LooSiHi1Pt05_T0000000127",51,0.0,1.02,True, "muPIsoBDI(PVP)AsinRun1", True, "muP Iso BDI (PVP) As in Run 1"),
    VariableInfo("muP_iso_10_noChi2_LooSiHi1Pt05_T0004194304",51,0.0,1.02,True, "muPIsoBFJ(PVP)CustomTVAApprox", True, "muP Iso BFJ (PVP) Custom TVA Approx"),
    VariableInfo("muP_iso_10_noChi2_LooSiHi1Pt05_T0134217728",51,0.0,1.02,True, "muPIsoBEJ(PPP)CustomTVATrkPerigee", True, "muP Iso BEJ (PPP) Custom TVA Trk Perigee"),
    VariableInfo("muP_iso_10_noChi2_LooSiHi1Pt05_T0008388608",51,0.0,1.02,True, "muPIsoBGJ(PPP)LooseTVA", True, "muP Iso BGJ (PPP) Loose TVA"),

    VariableInfo("PRIVX_mu",1,0.0,1.0,True, "#muPRIVX", True, "$PRIVX\mu$"),
    VariableInfo("PRIVX_mu_round",1,0.0,1.0,True, "#muPRIVX", True, "$PRIVX\mu$"),
    VariableInfo("Npv",1,0.0,1.0,True, "PVmultiplicity", True, "nPV")

  ]
# for i in range(10):
#   print(Variables[i].name, " ", Variables[i].axLabel)

# import collections

# VariableInfo = collections.namedtuple('VariableInfo', 'a b')

# Variables = [VariableInfo('lame', False), VariableInfo(4,True)]
# Variables['lame'].a
