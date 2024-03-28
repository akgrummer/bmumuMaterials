#include "TH1F.h"
#include "TCut.h"

// ODD/EVEN EVENTS
TCut CutOdd = "(event_number%2)==0";

// ADDITIONAL CUTS
TCut CutAdd = "(isCatN1 || isCatN2 || isCatN3) && (Lxy>0. && TMath::Abs(a_2D)<1.0 && DR<1.5) && BDT_fakeMuon_1>-0.458 && BDT_fakeMuon_2>-0.458";
//TCut CutAdd =  "EF_trigger_name == \"EF_2mu6_Jpsimumu_L2StarB\" && B_IDtrk1_nPIXhits>0 && B_IDtrk2_nPIXhits>0 && B_IDtrk1_nTRThits>0 && B_IDtrk2_nTRThits>0 && Lxy>0.3";

// VARIABLES
struct VariableInfo{
  string alias;
  string name;
  Int_t nbins;
  Float_t XMin;
  Float_t XMax;
  Bool_t logScale;
  string axName;
  string units;
  char type;
}Variables[]= {
  {"pa","TMath::Abs(a_2D)",50,0,1.0,true,"|#alpha_{2D}|","rad",'F'},
  {"pa3D","TMath::Abs(a_3D)",60,0,1.5,true,"|#alpha_{3D}|","rad",'F'},
  {"dr","DR",30,0,1.5,true,"#DeltaR","",'F'},
  {"blxy","Lxy",-1,-2,15,false,"L_{xy}","mm",'F'},
  {"ch2pvsv","chi2_PVSV_log2D",60,-6,12,false,"Log(#chi^{2}_{xy})","",'F'},
  {"d0mins","TMath::Abs(d0Min_sig)",40,0.0,40.0,false,"|d_{0}|^{min} sig.","",'F'},
  {"d0maxs","TMath::Abs(d0Max_sig)",50,0.0,50.0,false,"|d_{0}|^{max} sig.","",'F'},
  {"iso","B_iso_7_Chi2_5_LoosePt05",-1,0.0,1.1,false,"B Isolation (I^{B}_{0.7})","",'F'}, //with #chi^{2} cut"},
  {"bpt","B_pT",-1,10000,100000,false,"p_{T}^{B}","MeV",'F'},
  {"plng","PlngMin2D",25,0,25,false,"P^{min}_{L}","MeV",'F'},

  {"beta","B_eta",-1,-3.0,3.0,false,"#eta^{B}","",'F'},

  {"","B_fitChi2NDF",24,0,6,false,"#chi^{2}_{B}/NDF","",'F'},
  {"mchi2pv","B_minChi2MuonsIPtoAnyPV",80,-10,10,true,"Log(#chi^{2}_{#mu,xPV})","",'F'},

  {"evnum", "event_number",-1,1,10000000,false,"evt number","",'I'},
  {"mass","B_MUCALC_mass",30,4766,5966,false,"m_{#mu#mu}","MeV",'F'},
  {"maerr","B_MUCALC_mass_err",30,0,90,false,"#delta m_{#mu#mu}","MeV",'F'},
  {"masig","B_MUCALC_mass/B_MUCALC_mass_err",100,0,600,false,"m_{#mu#mu} /#Deltam_{#mu#mu}","",'F'},
  {"","properTime_sig",65,-10,120,false,"ct significance","",'F'},
  {"","chi2_PVSV_log1Dz",52,-14,12,false,"Log(#chi^{2}_{z})","",'F'},
  {"","TMath::Abs(d0Min)",40,0.0,2.0,false,"|d_{0}|^{min}","mm",'F'},
  {"","TMath::Abs(d0Max)",60,0,3.0,true,"|d_{0}|^{max}","mm",'F'},
  {"","TMath::Abs(closeTrkDCA)",100,0,0.5,true,"|D_{xy}|^{min}","mm",'F'}, //Distance in xy to the closest approach track [mm]"},
  {"","PlngMax2D",40,0,40,false,"P^{max}_{L}","MeV",'F'},
  {"","TMath::Abs(closeTrkZCA)",100,0,0.5,true,"|D_{z}|^{min}","mm",'F'},



  {"","B_iso_Ntracks_7_Chi2_5_MedPt05",25,0,25,false,"number of tracks in iso cone","",'I'},
  {"","B_pT_error",100,0,3000,false,"#delta p_{T}^{B}","MeV",'F'},
  {"ctntrk","closeTrkNtrksChi2LoosePt05",60,0,60,false,"N^{clos}_{trk}","",'I'},
  {"","Lxy_err",60,0,0.6,false,"BvtxLxyErr","",'F'},
  {"","Lxy_sig",60,0,60,false,"BvtxLxy signif.","",'F'},

  {"mdca","TMath::Abs(B_IDtrks_DCA)",80,0,0.4,true,"DOCA_{#mu#mu}","mm",'F'}, 
  {"deta","TMath::Abs(B_IDtrks_deltaEta)",28,0.0,1.4,true,"|#eta_{#mu1}-#eta_{#mu2}|","",'F'},
  {"dphi","TMath::Abs(B_IDtrks_deltaPhi)",50,0.0,1.0,true,"|#Delta#phi_{#mu#mu}|","",'F'},

  {"ctdoca","closeTrkDOCALoosePt05",20,0,2,false,"DOCA_{xtrk}","mm",'F'},
  {"","B_pT_sig",70,0,840,false,"p_{T}^{B} sig.","",'F'}, //140
  {"bip","Bvtx3DIP",60,0,2.0,true,"|IP_{B}^{3D}|","",'F'}, //0.6
  {"","BDT_bb_2012",32,-0.8,0.8,false,"BDT_bb_2012","",'F'}, //32,-0.8,0.8 //60,0.15,0.7
  {"","UpdatedClassBDT",32,-0.8,0.8,false,"BDT output","",'F'},

  {"npv","nPV",20,2.5,22.5,false,"PV multiplicity","",'F'},
  
  {"","muP_iso_Ntracks_7_chi2_5_medPt05",25,0,25,false,"N^{Iso 0.7, #mu+}_{trk}","",'I'},
  {"","muM_iso_Ntracks_7_chi2_5_medPt05",25,0,25,false,"N^{Iso 0.7, #mu-}_{trk}","",'I'},
  {"","muP_iso_7_chi2_5_medPt05",-1,0.0,1.1,false,"#mu+ Isolation (I^{#mu+}_{0.7})","",'F'},
  {"","muM_iso_7_chi2_5_medPt05",-1,0.0,1.1,false,"#mu- Isolation (I^{#mu-}_{0.7})","",'F'}

  /* 
  {"","SumMuTrackPixHits",11,1,12,false,"SumMuTrackPixHits","",'F'},
  {"","PVtxType",4,0,4,false,"PV type","",'F'},
  {"","EventMu",40,0.5,40.5,false,"Event mu","",'F'},
  */
};

Int_t nVar = sizeof(Variables)/sizeof(Variables[0]);

// SPECIAL HISTOGRAMS WITH VARIABLE BINNING FOR SOME VARIABLES
const Int_t nBinsIso = 16;
Float_t xBinIso[nBinsIso]={0.0,0.3,0.45,0.55,0.625,0.7,0.75,0.8,0.84,0.88,0.92,0.95,0.975,0.99,1.01,1.05};
TH1F* hdummyIso = new TH1F("","" ,nBinsIso-1, xBinIso);
const Int_t nBinsLxy = 18;
Float_t xBinLxy[nBinsLxy]={-3.0,0.0,0.3,0.8,1.3,1.8,2.3,2.8,3.3,3.9,4.6,5.4,6.2,7.2,8.8,11.0,14.0,18.0}; //-0.5
TH1F* hdummyLxy = new TH1F("","" ,nBinsLxy-1, xBinLxy);
const Int_t nBinsClassBDT = 18;
Float_t xBinClassBDT[nBinsClassBDT]={-0.6,-0.3,-0.2,-0.1,-0.05,0.0,0.05,0.1007,0.1050,0.1135,0.115,0.1220,0.1262,0.1347,0.15,0.2,0.3,0.4};
TH1F* hdummyClassBDT = new TH1F("","" ,nBinsClassBDT-1, xBinClassBDT);

