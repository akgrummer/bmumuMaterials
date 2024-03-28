#include<TMath.h>
#include "../AnalysisTools/Utils/AtlasStyle/AtlasLabels.C"
#include "../AnalysisTools/Utils/AtlasStyle/AtlasLabels.h"
#include "../AnalysisTools/Utils/AtlasStyle/AtlasUtils.C"
#include "../AnalysisTools/Utils/AtlasStyle/AtlasUtils.h"
#include "../AnalysisTools/Utils/AtlasStyle/AtlasStyle.C"
#include "../AnalysisTools/Utils/AtlasStyle/AtlasStyle.h"
// TString filename = "/Users/agrummer/Desktop/Bmumu/Output/Trees/LSFJOB_Trees500/bdt2016test_0.root";
// TString FilePath = "/Users/agrummer/cernbox/www/bmumu/myMVA/";
// TString ParameterName = "out2";
// TString filename = FilePath + ParameterName + "/"+"bdt2016test.root";
// TString filename = "/Users/agrummer/cernbox/www/bmumu/myMVA/out500/bdt2016test.root";
Char_t classNameTest;
TString ATestString;
Int_t classIDTest(0);
Float_t BDTvarTest(0.0);
Float_t TestWeight(0.);
vector <Float_t> bkgBDTtest;
vector <Float_t> sigBDTtest;
vector <Float_t> bkgBDTtestWeight;
vector <Float_t> sigBDTtestWeight;

Char_t classNameTrain;
TString ATrainString;
Int_t classIDTrain(0);
Float_t BDTvarTrain(0.0);
Float_t TrainWeight(0.);

vector <Float_t> bkgBDTtrain;
vector <Float_t> sigBDTtrain;
vector <Float_t> bkgBDTtrainWeight;
vector <Float_t> sigBDTtrainWeight;

Double_t BDTvarBkg(0.0);
Double_t BDTvarSig(0.0);

Double_t CombWeights(0.0);
Double_t PVWeights(0.0);
Float_t Muon1_reco_eff_sf(0.0);
Float_t Muon2_reco_eff_sf(0.0);

vector <Double_t> bkgBDT;
vector <Double_t> sigBDT;
double B_MUCALC_massBkg;
double B_MUCALC_massSig;


TMultiGraph *mg;
TGraphAsymmErrors *gr1;

// void PlotBDTvariables(Float_t bkgBDTtest,
//                       Float_t sigBDTtest,
//                       Float_t bkgBDTtrain,
//                       Float_t sigBDTtrain);


// Double_t AidansKTest(Int_t na, const Double_t *a, Int_t nb, const Double_t *b, Option_t *option);
struct VariableInfo{
  const char* name;
  Int_t nbins;
  Float_t XMin;
  Float_t XMax;
  Bool_t logScale;
  const char* axLabel;
  Bool_t usedForSystematics;
  TString ZoomName;
  Bool_t Zoom;
  Double_t ZoomVal;
  Bool_t PlotOnlyMC;
  Double_t PullYmin;
  Double_t PullYmax;
};

VariableInfo isoVar = {"B_iso_7_Chi2_5_LoosePt05",51,0.0,1.02,false,"I_{0.7}",false, "zoom", false, 0., false, 0., 3.5};
VariableInfo isoNtracks = {"B_iso_Ntracks_7_Chi2_5_LoosePt05",16,0,16,false,"Ntracks B Isolation (I^{B}_{0.7, loose, pt>0.5})",false, "zoom", false, 0., false, 0.6, 1.4};
VariableInfo closeTrkDOCA = {"closeTrkDOCA",40,0,2,true,"DOCA_{xtrk, loose, pt>0.5} [mm]",true, "zoom", false, 0., false, 0.5, 1.5};
// {"Npv-1",40,-0.5,39.5,false,"nPV",true, "zoom", false, 0., false, 0.5, 3.};
// {"B_iso_7_Chi2_5_MedPt05",51,0.0,1.02,true,"I_{0.7}",false, "zoom", false, 0., false, 0., 3.5};
// {"B_iso_Ntracks_7_Chi2_5_MedPt05",16,0,16,true,"Ntracks B Isolation (I^{B}_{0.7, loose, pt>0.5})",false, "zoom", false, 0., false, 0.75, 1.25};
// {"B_iso_7_Chi2_5_LoosePt05_AllTrks",51,0.0,1.02,true,"I_{0.7}",false, "zoom", false, 0., false, 0., 3.5};
// {"B_iso_Ntracks_7_Chi2_5_LoosePt05_AllTrks",16,0,16,true,"Ntracks B Isolation (I^{B}_{0.7, loose, pt>0.5})",false, "zoom", false, 0., false, 0.75, 1.25};
// {"closeTrkNtrksChi2_AllTrks",60,0,60,true,"N^{clos}_{trk, loose, pt>0.5}",true, "zoom", false, 0., false, 0., 3.5};//added with new MC HLT_mu6_mu4_bBmumu_Lxy0
// {"closeTrkDOCA_AllTrks2",40,0,2,true,"DOCA_{xtrk, loose, pt>0.5} [mm]",true, "zoom", false, 0., false, 0.5, 1.5};
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
const Int_t nBinsPt = 33;
Float_t xBinPt[nBinsPt]={8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 68, 70, 76, 100};
TH1F* hdummyPt = new TH1F("","" ,nBinsPt-1, xBinPt);
const Int_t nBinsEta = 51;
Float_t xBinEta[nBinsEta]={-2.5, -2.4, -2.3, -2.2, -2.1, -2, -1.9, -1.8, -1.7, -1.6, -1.5, -1.4, -1.3, -1.2, -1.1, -1, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1, 0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2, 2.1, 2.2, 2.3, 2.4, 2.5};
TH1F* hdummyEta = new TH1F("","" ,nBinsEta-1, xBinEta);

TCut CutAdd = "Lxy>0.3";//"1==1";//Lxy>0.3


TH1F* getHistoFromTree(TTree* tree, VariableInfo Variable, const char* hname, TCut cut)
{
  cout << "GetHistoFromTree, getting histo "<< hname << " for variable " << Variable.name << " from tree "<< tree->GetName() << endl;
  //==================================================================================================
  //====create TString defining how the histogram will be retrieved with TTree::Draw method===========
  //================================================================================================== 
  TString tmp = Variable.name;
  TString axlab = Variable.axLabel;
  Int_t NBins = Variable.nbins;
  Float_t XMin = Variable.XMin;
  Float_t XMax = Variable.XMax;
  if (axlab.Contains("[GeV]")) tmp.Append("/1000.0");
  TString tmpDummy(tmp);
  tmp.Append(">>");
  tmp.Append(hname);
  if (NBins>0 && XMin!=XMax) {
    tmp+=("(");
    tmp+=NBins;
    tmp+=",";
    tmp+=XMin;
    tmp+=",";
    tmp+=XMax;
    tmp+=")";
  } else if (NBins == -1) { 
    tmpDummy.Append(">>+");
    tmpDummy.Append(hname);
  } else tmp.Append("(100)"); //restore default (ROOT) binning
  //==================================================================================================
  //====retrieve histo from TTree============
  //==================================================================================================
  TH1F *hret;
  int nselected(0);
  if (NBins == -1) { //variable binning for eta and pt taken from *.h file                                                                  
    if (tmpDummy.Contains("BvtxPt") || tmpDummy.Contains("B_pT") || tmpDummy.Contains("JPsiPt") || tmpDummy.Contains("BTruthPt")|| tmpDummy.Contains("Muon1_pT")|| tmpDummy.Contains("Muon2_pT")) hret = new TH1F(*hdummyPt); 
    // else if (tmpDummy.Contains("eta") || tmpDummy.Contains("Eta")) hret = new TH1F(*hdummyEta);
    else if (tmpDummy.Contains("Iso") || tmpDummy.Contains("_iso_")) hret = new TH1F(*hdummyIso);
    else if (tmpDummy.Contains("Lxy")) hret = new TH1F(*hdummyLxy);
    else if (tmpDummy.Contains("ClassBDT")) hret = new TH1F(*hdummyClassBDT);
    else {
      cout << "Unknown binning, returning zero pointer..." <<endl;
      return NULL;
    }
    hret->SetName(hname);
    hret->Reset();
    hret->Sumw2();
    nselected = tree->Draw(tmpDummy.Data(),cut,"egoff"); 
    cout << "GetHistoFromTree, creating histo:" << tmpDummy << " event survived the cut(s): " << nselected << endl;
  } else {
    nselected = tree->Draw(tmp.Data(),cut,"egoff");
    cout << "GetHistoFromTree, creating histo:" << tmp << " event survived the cut(s): " << nselected << endl;
    hret = (TH1F*)gDirectory->Get(hname);
  }
 
  hret->GetXaxis()->SetTitle(axlab);
  hret->SetTitle(hname);
  cout << "Creating histo, title "<< hname <<", hret integral.."<< hret->Integral(0, Variable.nbins + 1) <<endl; //cut out over- and unerflows
  cout << endl;
  return hret;
} // end of getHistoFromTree function

void atlasLabel(Double_t x,Double_t y, bool drawRes = true, bool Preliminary=true,Color_t color=1, bool drawEnergy=true, bool drawLumi=false, bool enlarge=true, TString h1title = "")
{
  double delx = 0.115*696*gPad->GetWh()*3/(5*472*gPad->GetWw());
  double textsize;
  double dy = 0.065;
  if (!drawRes) {
    if (enlarge) {
      textsize = 0.055; 
      delx+=0.03;
      dy = 0.065;
      // dy = 0.1;
    }
    else textsize = 0.06;
    delx+=0.04;
  }
  TLatex *tex = new TLatex(x,y,"ATLAS");
  tex->SetNDC();
  tex->SetTextSize(textsize);
  tex->SetTextFont(72);
  tex->SetLineWidth(2);
  tex->SetTextColor(color);
  tex->Draw();
  if (Preliminary) {
    tex = new TLatex(x+delx,y,"Internal"); //Preliminary
    // tex = new TLatex(x+delx,y,"Preliminary"); //Preliminary
    tex->SetNDC();
    tex->SetTextSize(textsize);
    tex->SetTextFont(42); //42
    tex->SetLineWidth(2);
    tex->SetTextColor(color);
    tex->Draw();
  }
  if (drawEnergy) {
    if (h1title.Contains("fabs_a_2D")) tex = new TLatex(0.5,0.55,"#sqrt{s} = 13 TeV, 26.3 fb^{-1}");
    else if (h1title.Contains("B_IDtrks_DCA")) tex = new TLatex(0.58,0.66,"#sqrt{s} = 13 TeV, 26.3 fb^{-1}");
    else if (h1title.Contains("chi2_PVSV_log2D")) tex = new TLatex(0.56,0.77,"#sqrt{s} = 13 TeV, 26.3 fb^{-1}");
    else if (h1title.Contains("B_iso_7_Chi2_5_LoosePt05")) tex = new TLatex(0.2,0.68,"#sqrt{s} = 13 TeV, 26.3 fb^{-1}");
    else tex = new TLatex(x+0.01,y-dy,"#sqrt{s} = 13 TeV, 26.3 fb^{-1}");
    tex->SetNDC();
    tex->SetTextSize(textsize);
    tex->SetTextFont(42);
    tex->SetLineWidth(2);
    tex->SetTextColor(color);
    // tex->Draw();
  }
  if (drawLumi) {
    tex = new TLatex(x-0.01,y-2*dy,"#int Ldt = 4.9 fb^{-1}");
    tex->SetNDC();
    tex->SetTextSize(textsize);
    tex->SetTextFont(42);
    tex->SetLineWidth(2);
    tex->SetTextColor(color);
    tex->Draw();
  }
}


void Iso_ROCs(){
    SetAtlasStyle();
// TString DirName = "/Users/agrummer/cernbox/www/bmumu/Data/";
TString DirName = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/";
// TString DirName = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimRightSideband/";
// TString DirName = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LastSkimGBR4_Mar26/";
// TString DirName2 = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/EvalSetMC/";
// TString DirName2 = "/eos/home-a/agrummer/BsmumuData/LastSkim_2019Apr/";

TString Tag = "2016";

TString vBDT = "";
// TString filenameBkg = DirName + "data1516Bs"+vBDT+Tag+".root";
TString filenameBkg = DirName + "2016All/LASTskim_2016_All_2019Apr29_testweight.root";
// TString filenameSig = DirName2 + "LASTskim.mc16Bs"+vBDT+Tag+".root";
TString filenameSig = DirName + "MC16aAll/LASTskim_MC16a_All_Studies_2019Apr24.root";

TFile* ifilenameBkg = new TFile(filenameBkg);
TFile* ifilenameSig = new TFile(filenameSig);

TTree *EvalTreeBkg = (TTree*)ifilenameBkg->Get("T_mv");
// EvalTreeBkg->SetBranchAddress("B_iso_7_Chi2_5_LoosePt05",&B_iso_7_Chi2_5_LoosePt05);
// EvalTreeBkg->SetBranchAddress("B_MUCALC_mass",&B_MUCALC_massBkg);


TTree *EvalTreeSig = (TTree*)ifilenameSig->Get("T_mv");
// EvalTreeSig->SetBranchAddress("BDT_bb_2016",&BDTvarSig);

// EvalTreeSig->SetBranchAddress("CombWeights",&CombWeights);
// EvalTreeSig->SetBranchAddress("PVWeights",&PVWeights);
// EvalTreeSig->SetBranchAddress("Muon1_reco_eff_sf",&Muon1_reco_eff_sf);
// EvalTreeSig->SetBranchAddress("Muon2_reco_eff_sf",&Muon2_reco_eff_sf);

// EvalTreeSig->SetBranchAddress("B_MUCALC_mass",&B_MUCALC_massSig);

cout<<"EvalTreeBkg Entries: "<<EvalTreeBkg->GetEntries()<<endl;
cout<<"EvalTreeSig Entries: "<<EvalTreeSig->GetEntries()<<endl;


// for(int i=0; i < EvalTreeBkg->GetEntries(); i++){
//     EvalTreeBkg->GetEntry(i);
//     // if (B_MUCALC_massBkg <=5526.0) continue;
//     bkgBDT.push_back(BDTvarBkg);
//       }

// for(int i=0; i < EvalTreeSig->GetEntries(); i++){
//     EvalTreeSig->GetEntry(i);
//     sigBDT.push_back(BDTvarSig);
//       }

// cout<<"bkg vector size: "<<bkgBDT.size()<<endl;
// cout<<"sig vector size: "<<sigBDT.size()<<endl;
// cout<<"bkg+sig vector size: "<<bkgBDT.size() + sigBDT.size()<<endl;


// sort(sigBDT.begin(), sigBDT.end());
// sort(bkgBDT.begin(), bkgBDT.end());

// vector<Double_t> vec = sigBDT;
// vec.insert( vec.end(), bkgBDT.begin(), bkgBDT.end() );//merge sig and bkg vectors
// sort(vec.begin(), vec.end());
// vec.erase( unique( vec.begin(), vec.end() ), vec.end() );//select unique values in full vector for hist bins
// // cout<<vec.back()<<endl;
// // cout<<vec[vec.size()]<<endl;
// cout<<" vec size (sig+bkg)  "<<vec.size()<<endl;
// vec.push_back(vec.back()+ 0.01);
// cout<<" vec size + 1 "<<vec.size()<<endl;
// Double_t* b = &vec[0];// the array that the vector points to!!!
// sort(b, b + vec.size());


////////PLOTTING
TCanvas* c1;
TH1F *hret;
TH1F *hretSig;
TH1F *hretBkg;
TH1F *hret2;
TH1F *hret3;
TH1F *hret4;
Double_t yHeight;
TLegend* leg;
TString hretLeg;
TString hret2Leg;
TString hret3Leg;
TString hret4Leg;
Double_t sigTestCandidates;
Double_t bkgTestCandidates;
Double_t sigTrainCandidates;
Double_t bkgTrainCandidates;
Double_t kolS;
Double_t kolB;
TString tex3text;
TLatex *tex3;
// int NumberOfBins;


// NumberOfBins = 100;

/////////////ROC

TH1F *hROCSig(NULL);
TH1F *hROCBkg(NULL);

int NumberOfBinsROC = isoVar.nbins+100;
// hROCSig = new TH1F("NameROC", "titleROC", NumberOfBinsROC, vec[0], vec.back());
// hROCBkg = new TH1F("NameROC2", "titleROC2", NumberOfBinsROC, vec[0], vec.back());
// hROC3 = new TH1F("NameROC3", "titleROC3", NumberOfBinsROC, vec[0], vec.back());
// hROC4 = new TH1F("NameROC4", "titleROC4", NumberOfBinsROC, vec[0], vec.back());

TString h1title = "IsolationHist";
hROCSig = getHistoFromTree(EvalTreeSig, isoVar, h1title, CutAdd*"PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf");
// for(int i = 0; i<EvalTreeSig->GetEntries(); i++){
//     EvalTreeSig->GetEntry(i);
//     hROCSig->Fill(BDTvarSig, CombWeights*PVWeights*Muon1_reco_eff_sf*Muon2_reco_eff_sf);
// }
h1title += "_Bkg";
hROCBkg =getHistoFromTree(EvalTreeBkg, isoVar, h1title, CutAdd*"testweight");
hROCSig->Sumw2();
hROCBkg->Sumw2();
// for(int i = 0; i<EvalTreeBkg->GetEntries(); i++){
//     EvalTreeBkg->GetEntry(i);
//     if (B_MUCALC_massBkg <=5526.0) continue;
//     hROCBkg->Fill(BDTvarBkg);
// }

hROCSig->Scale(1.0/hROCSig->Integral(0, NumberOfBinsROC));
hROCBkg->Scale(1.0/hROCBkg->Integral(0, NumberOfBinsROC));


//////////////////////////////////////////

vector<Double_t> SigTestEff;
vector<Double_t> BkgTestRej;
for(int i = 0; i<NumberOfBinsROC; i++){
  // cout<<i<<endl;
  SigTestEff.push_back((hROCSig->Integral(NumberOfBinsROC-i, NumberOfBinsROC))/(hROCSig->Integral(0, NumberOfBinsROC))*100);
  BkgTestRej.push_back((1-(hROCBkg->Integral(NumberOfBinsROC-i, NumberOfBinsROC))/(hROCBkg->Integral(0, NumberOfBinsROC)))*100);

  // if ((SigTestEff[i] > 17.95 && SigTestEff[i] < 18.05) || (SigTestEff[i] > 35.95 && SigTestEff[i] < 36.05) || (SigTestEff[i] > 53.95 && SigTestEff[i] < 54.05)){
  //     cout<<"Bkg Rej= "<< BkgTestRej[i]<< " at a signal efficiency: " << SigTestEff[i] 
  //     << " BDT value: "<< hROCSig->GetXaxis()->GetBinCenter(NumberOfBinsROC-i)
  //     <<" bkg: "<<hROCBkg->GetXaxis()->GetBinCenter(NumberOfBinsROC-i) << endl;
  //     }
}

TCanvas* c2 = new TCanvas("c2", "ROC curve",0.,0., 800, 600);
TGraph *grROC = new TGraph(NumberOfBinsROC, &SigTestEff[0], &BkgTestRej[0]);

grROC->Draw("al");
grROC->SetMarkerColor(4);
grROC->SetLineColor(4);
grROC->SetMarkerStyle(20);
grROC->SetMarkerSize(1);
grROC->SetLineWidth(1);
grROC->GetYaxis()->SetTitle("Bkg. Rejection [%]");
grROC->GetXaxis()->SetTitle("Sig. Efficiency [%]");

atlasLabel(0.45, 0.2, false, true, 1, true, false, true, h1title);

TLegend* leg2;
// leg2 = new TLegend(1, 0.06, 5, 0.08,NULL,"brNDC");
// leg2 = new TLegend(0.218045, 0.721739, 0.418546, 0.770435,NULL,"brNDC");
leg2 = new TLegend(0.218045, 0.32, 0.418546, 0.37,NULL,"brNDC");
leg2->AddEntry(grROC, "MC16a + 2016 Run 302393","l");
leg2->SetBorderSize(0);  // no border
leg2->SetLineColor(0);
leg2->SetFillColor(0);
leg2->SetTextSize(0.034468);
leg2->Draw();


Double_t sig18 = grROC->Eval(18);
Double_t sig36 = grROC->Eval(36);
Double_t sig54 = grROC->Eval(54);
TString ROCtext1 = "Bkg. Rej. at 18% Sig.Eff: ";
ROCtext1.Append(Form("%.6g", sig18));
TString ROCtext2 = "Bkg. Rej. at 36% Sig.Eff:";
 ROCtext2.Append(Form(" %.6g", sig36));
TString ROCtext3 = "Bkg. Rej. at 54% Sig.Eff:";
ROCtext3.Append(Form(" %.6g", sig54));
// TString newROCtext = "#splitline{a}{#splitline{b}{c}}";
TString newROCtext = "#splitline{" + ROCtext1 + "}{#splitline{" + ROCtext2 + "}{"+ROCtext3+"}}";
cout<<newROCtext<<endl;
// TLatex *ROCtex1 = new TLatex(8.60565, 70,newROCtext);
// ROCtex1->SetTextFont(62);
// ROCtex1->SetTextSize(0.034468);
// ROCtex1->SetLineWidth(2);
// ROCtex1->Draw();


c2->Update();
// TString ofilenames = "Jun13MuIso_SidebandTrained/BDT1";//train3
TString OutdirName = "/afs/cern.ch/user/a/agrummer/www/bmumu/IsoVarROCs/";

c2->SaveAs(OutdirName + "Figures/ROC"+Tag+".pdf");
TFile ofile(OutdirName + "RootFiles/ROC"+Tag+".root", "recreate");
grROC->Write();


return 0;
}
