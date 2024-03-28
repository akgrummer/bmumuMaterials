import collections

VariableInfo = collections.namedtuple('VariableInfo', 'name, \
  nbins, XMin, XMax, logScale, axLabel, usedForSystematics')

Variables = [VariableInfo("TMath::Abs(a_2D)",50,0,1.0,True,"|#alpha_{2D}| [rad]",True),
  #   VariableInfo("TMath::Abs(a_3D)",60,0,1.5,True,"|#alpha_{3D}| [rad]",True),
  VariableInfo("DR",30,0,1.5,True,"#DeltaR",True),
  VariableInfo("Lxy",40,-0.5,3.5,False,"L_{xy} [mm]",True),
  VariableInfo("chi2_PVSV_log2D",60,-6,12,False,"Log(#chi^{2}_{xy})",True),  
  VariableInfo("TMath::Abs(d0Min_sig)",40,0.0,40.0,False,"|d_{0}|^{min} sig.",True),
  VariableInfo("TMath::Abs(d0Max_sig)",50,0.0,50.0,False,"|d_{0}|^{max} sig.",True),
  VariableInfo("B_iso_7_Chi2_5_LoosePt05",60,0.0,1.05,True,"B Isolation (I^{B}_{0.7, loose, pt>0.5})",True),
  VariableInfo("B_iso_Ntracks_7_Chi2_5_LoosePt05",16,0,16,True,"Ntracks B Isolation (I^{B}_{0.7, loose, pt>0.5})",True),

  #   VariableInfo("B_pT",-1,10000,100000,True,"p_{T}^{B} [GeV]",True),
  VariableInfo("B_pT",70,5,40,True,"p_{T}^{B} [GeV]",True),
  VariableInfo("PlngMin2D",25,0,25,False,"P^{min}_{L} [GeV]",True),
  #  VariableInfo("closeTrkNtrksChi2LoosePt05",60,0,60,True,"N^{clos}_{trk, loose, pt>0.5}",False), # Aidan set to False - not in data files
  VariableInfo("closeTrkNtrksChi2",60,0,60,True,"N^{clos}_{trk, loose, pt>0.5}",True),# added with new MC HLT_mu6_mu4_bBmumu_Lxy0

  VariableInfo("TMath::Abs(B_IDtrks_DCA)",80,0,0.4,True,"DOCA_{#mu#mu} [mm]",True), 
  VariableInfo("TMath::Abs(B_IDtrks_deltaPhi)",70,0.0,1.4,True,"|#Delta#phi_{#mu#mu}|",True),
  VariableInfo("closeTrkDOCALoosePt05",40,0,2,True,"DOCA_{xtrk, loose, pt>0.5} [mm]",False), # Aidan set to False - not in data files

  VariableInfo("Bvtx3DIP",60,0,2.0,True,"|IP_{B}^{3D}|",True), # 0.6
  #   VariableInfo("B_minChi2MuonsIPtoAnyPV",80,-10,10,False,"Log(#chi^{2}_{#mu,xPV})",True), # n.y implemented


  VariableInfo("B_eta",-1,-3.0,3.0,False,"#eta^{B}",True),
  VariableInfo("B_fitChi2NDF",24,0,6,False,"#chi^{2}_{B}/NDF",True),
  VariableInfo("Npv",30,-0.5,29.5,False,"nPV",True),
  VariableInfo("Lxy_sig",80,0,80,False,"BvtxLxy signif.",True),
  VariableInfo("B_MUCALC_massErr",40,30,430,False,"#delta m_{#mu#mu} [MeV]",True),
  #   VariableInfo("properTime_sig",65,-10,120,False,"ct significance",True),

  VariableInfo("B_MUCALC_mass",60,4766,5966,False,"m_{#mu#mu} [MeV]",True),
  VariableInfo("B_MUCALC_mass/B_MUCALC_massErr",100,0,600,False,"m_{#mu#mu} /#Deltam_{#mu#mu}",False),


  VariableInfo("Muon1_etcone30",220,-20000,200000,True,"Muon1_etcone30",True),
  VariableInfo("Muon2_etcone30",220,-20000,200000,True,"Muon2_etcone30",True),
  VariableInfo("Muon1_etcone40",220,-20000,200000,True,"Muon1_etcone40",True),
  VariableInfo("Muon2_etcone40",220,-20000,200000,True,"Muon2_etcone40",True),
  VariableInfo("Muon1_nucone30",200,0,200,True,"Muon1_nucone30",False),
  VariableInfo("Muon2_nucone30",200,0,200,True,"Muon2_nucone30",False),
  VariableInfo("Muon1_nucone40",200,0,200,True,"Muon1_nucone40",False),
  VariableInfo("Muon2_nucone40",200,0,200,True,"Muon2_nucone40",False),


  VariableInfo("B_PV_Ref_z",40,-200,200,False,"B_PV_ref_z",True),

  VariableInfo("chi2_PVSV_log1Dz",52,-14,12,False,"Log(#chi^{2}_{z})",False),
  VariableInfo("DecayCoplanarity",120,0,12000,True,"coplan._{#Deltax,#mu1,#mu2}",False),
  VariableInfo("MuSignedd0SigMin",200,-50,150,False,"sd_{0}^{min} signif.",False),
  VariableInfo("CoplanaritywithZ",180,0,18000,True,"coplan._{#Deltax,#mu#mu,z}",False),
  VariableInfo("BvtxDXSig",70,0,140,False,"|#Deltax_{3D}| signif.",False),
  VariableInfo("BvtxDXSig2D",70,0,140,False,"|#Deltax_{2D}| signif.",False),
  VariableInfo("PlngMax2D",40,0,40,False,"P^{max}_{L} [GeV]",False),
  VariableInfo("B_iso_Ntracks_7_Chi2_5_MedPt05",25,0,25,False,"number of tracks in iso cone",False),
  VariableInfo("BDT_bb_2012",80,-0.8,0.8,False,"BDT output",False),



  VariableInfo("B_iso_Ntracks_7_Chi2_5_MedPt05",25,0,25,False,"number of tracks in iso cone",False),
  VariableInfo("B_pT_error",100,0,3000,False,"#delta p_{T}^{B} [MeV]",False),
 
  VariableInfo("Lxy_err",60,0,0.6,False,"BvtxLxyErr",False),

  VariableInfo("TMath::Abs(d0Min)",40,0.0,2.0,True,"|d_{0}|^{min} [mm]",False),
  VariableInfo("TMath::Abs(d0Max)",60,0,3.0,True,"|d_{0}|^{max} [mm]",False),
  VariableInfo("d0Min_err",40,0.0,0.1,True,"d_{0}^{min} err. [mm]",False),
  VariableInfo("d0Max_err",60,0.0,0.15,True,"d_{0}^{max} err. [mm]",False),
  #  VariableInfo("TMath::Abs(closeTrkDCA)",100,0,0.5,True,"|D_{xy}|^{min} [mm]",False),
  #  VariableInfo("TMath::Abs(closeTrkZCA)",100,0,0.5,True,"|D_{z}|^{min} [mm]",False),
  #  VariableInfo("TMath::Abs(closeTrkDCA)",100,0,0.5,True,"|D_{xy}|^{min} [mm]",True),# added with new MC HLT_mu6_mu4_bBmumu_Lxy0
  #  VariableInfo("TMath::Abs(closeTrkZCA)",100,0,0.5,True,"|D_{z}|^{min} [mm]",True),# added with new MC HLT_mu6_mu4_bBmumu_Lxy0


  VariableInfo("TMath::Abs(B_IDtrks_deltaEta)",28,0.0,1.4,True,"|#eta_{#mu1}-#eta_{#mu2}|",False),
  VariableInfo("B_pT_sig",70,0,840,False,"p_{T}^{B} sig.",False), # 140
  VariableInfo("BDT_bb_2012",80,-0.8,0.8,False,"BDT output",False), # 32,-0.8,0.8 # 60,0.15,0.7

  VariableInfo("UpdatedClassBDT",32,-0.8,0.8,False,"BDT output",False),

  VariableInfo("muP_iso_Ntracks_7_chi2_5_medPt05",25,0,25,False,"N^{Iso 0.7, #mu+}_{trk}",False),
  VariableInfo("muM_iso_Ntracks_7_chi2_5_medPt05",25,0,25,False,"N^{Iso 0.7, #mu-}_{trk}",False),
  VariableInfo("muP_iso_7_chi2_5_medPt05",-1,0.0,1.1,False,"#mu+ Isolation (I^{#mu+}_{0.7})",False),
  VariableInfo("muM_iso_7_chi2_5_medPt05",-1,0.0,1.1,False,"#mu- Isolation (I^{#mu-}_{0.7})",False)
  ]
# for i in range(10):
#   print(Variables[i].name, " ", Variables[i].axLabel)

# import collections

# VariableInfo = collections.namedtuple('VariableInfo', 'a b')

# Variables = [VariableInfo('lame', False), VariableInfo(4,True)]
# Variables['lame'].a
