// TriggerWeights 1.5
//
// Use:
//
// 1) Create an instance with the class:
// TriggerWeights myWeights("singleMu_SF_data1516_perperiod.root");
// whenever you need a trigger weight for a given muon:
//
// status=myWeights.GetWeight(<muonpt>,<muoneta>,<muoncharge>,<runnumber>,<pt_threshold>,w,w_stat_w_syst)
//
// for a muon of (pt,eta)=(<muonpt>,<muoneta>) and charge <muoncharge> in run number <runnumber>
// this retrieves the trigger weights corresponding to trigger threshold <pt_threshold> (either 4.0 or 6.0 GeV at the moment)
// the Float_t variables w, w_stat and w_syst will return the weight, its statistical
// and systematic uncertainty.
//
// REM: pt is in GeV!
// status=-100 if the weight is outside the run range covered by the file
// status=-1 if the weight is outside the weight histograms range
// status=0 if the weight has been found in the histograms
//
// for negative status values w=1.0, w_stat=0.0 and w_syst=0.0 will be returned
// please make sure you always pass the value of eta with its sign to the class
//
/***********************************************************************************************/
/***********************************************************************************************/
//
//  for 2MU6 in BMuMu di-muon candidates we are using:
//
//                          the DEFAULT INPUT FILE: singleMu_SF_data1516_perperiod.root
//  the input file used for SYSTEMATICS VARIATIONS: singleMu_SF_data1516_etabins.root
//
// Mu1 is the muon *with the LOWEST pT of the pair*
// Mu2 is the muon *with the HIGHEST pT of the pair*
//
// status=myWeights.GetWeight(Mu1Pt,Mu1Eta,Mu1Charge,RunNumber,4.0,w1,w1_stat1_w_syst)
// status=myWeights.GetWeight(Mu2Pt,Mu2Eta,Mu2Charge,RunNumber,6.0,w2,w2_stat2_w_syst)
//
/***********************************************************************************************/
/***********************************************************************************************/
// Toy Generation
//
// a new set of toy values for all the weights loaded is generated for every call
// of GenerateWeightsToy(<TRandom3 *>,<stat>,<syst>)
// where stat and syst are two booleans choosing whether to vary the toys
// based on the statistical, systematic or combination in quadrature of the two
//

#ifndef TRIGGERWEIGHTS_CLASS_LOADED
#define TRIGGERWEIGHTS_CLASS_LOADED


#include "TMath.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TRandom3.h"

class TriggerWeights
{
 public:
  TriggerWeights(std::string inputfilename);
  Int_t GetWeight(double pt,double eta,double muoncharge,int runNumber,float pt_threshold,Float_t &w,Float_t &w_stat,Float_t &w_syst);
  void GenerateWeightsToy(TRandom3 *myRandomGenerator,bool stat,bool syst);
  std::vector<TH2F*> Weights;
  std::vector<TH2F*> originalWeights;

  std::vector<TH2F*> Weights_stat;
  std::vector<TH2F*> Weights_syst;
  std::vector<Int_t> RunMin;
  std::vector<Int_t> RunMax;
  std::vector<Float_t> PtMin;
 private:
  // DO NOT USE THE METHOD BELOW
  Int_t GetWeight(double pt,double eta,double muoncharge,int runNumber,Float_t &w,Float_t &w_stat,Float_t &w_syst);
  TFile *_file0;
  bool AddHistogramSet(std::string histogramsetlabel,double muon_pt_threshold,int startRun,int endRun);
  bool qEta,absEta;
};

Int_t TriggerWeights::GetWeight(double pt,double eta,double muoncharge,int runNumber,Float_t &w,Float_t &w_stat,Float_t &w_syst)
{
  if (qEta) eta=muoncharge*eta;
  if (absEta) eta=fabs(eta);
  int imatch=-1;
  double MaxPtMin=0;
  for (int iSet=0;iSet<(int)Weights.size();iSet++)
    if (runNumber>=RunMin[iSet] && runNumber<=RunMax[iSet] && pt>=PtMin[iSet])
      if (MaxPtMin<PtMin[iSet])
	{
	  MaxPtMin=PtMin[iSet];
	  imatch=iSet;
	}
  if (imatch<0)
    {
      w=1.0; w_stat=0.0; w_syst=0.0;
      return -100;
    }
  else
    {
      double ptMin =Weights[imatch]->GetXaxis()->GetXmin();
      double ptMax =Weights[imatch]->GetXaxis()->GetXmax();
      double etaMin=Weights[imatch]->GetYaxis()->GetXmin();
      double etaMax=Weights[imatch]->GetYaxis()->GetXmax();

      if (pt<ptMin || pt>ptMax || eta<etaMin || eta>etaMax)
	{
	  w=1.0; w_stat=0.0; w_syst=0.0;
	  return -1;
	}
      else
	{
	  int ibin=Weights[imatch]->FindBin(pt,eta);
	  w=Weights[imatch]->GetBinContent(ibin);
	  w_stat=Weights_stat[imatch]->GetBinContent(ibin);
	  w_syst=Weights_syst[imatch]->GetBinContent(ibin);
	  return 1;
	}
    }
  return 0;
}

Int_t TriggerWeights::GetWeight(double pt,double eta,double muoncharge,int runNumber,float pt_threshold,Float_t &w,Float_t &w_stat,Float_t &w_syst)
{
  if (qEta) eta=muoncharge*eta;
  if (absEta) eta=fabs(eta);
  int imatch=-1;
  for (int iSet=0;iSet<(int)Weights.size();iSet++)
    if (runNumber>=RunMin[iSet] && runNumber<=RunMax[iSet] && pt>=PtMin[iSet])
      if (pt_threshold==PtMin[iSet])
	  imatch=iSet;

  if (imatch<0)
    {
      w=1.0; w_stat=0.0; w_syst=0.0;
      return -100;
    }
  else
    {
      double ptMin =Weights[imatch]->GetXaxis()->GetXmin();
      double ptMax =Weights[imatch]->GetXaxis()->GetXmax();
      double etaMin=Weights[imatch]->GetYaxis()->GetXmin();
      double etaMax=Weights[imatch]->GetYaxis()->GetXmax();

      if (pt<ptMin || pt>ptMax || eta<etaMin || eta>etaMax)
	{
	  w=1.0; w_stat=0.0; w_syst=0.0;
	  return -1;
	}
      else
	{
	  int ibin=Weights[imatch]->FindBin(pt,eta);
	  w=Weights[imatch]->GetBinContent(ibin);
	  w_stat=Weights_stat[imatch]->GetBinContent(ibin);
	  w_syst=Weights_syst[imatch]->GetBinContent(ibin);
	  return 1;
	}
    }
  return 0;
}

TriggerWeights::TriggerWeights(std::string inputfilename)
{
  _file0 = TFile::Open(inputfilename.c_str(),"read");
  if (_file0==NULL)
    {
      printf("DDWQLC Class ERROR: Cannot find file %s, abort!\n",inputfilename.c_str());
    }
  else
    {
      bool status=false;

      // Run Ranges
      // 2017 pp  5 TeV 340634-341184
      // 2017 pp 13 TeV 323427-341649
      // 2016 HI        312649-314199
      // 2016 pp        296939-311563
      // 2015 HI        286665-287931
      // 2015 pp  5 TeV 286282-286474
      // 2015 pp 13 TeV 266904-284484
      if (inputfilename.find("singleMu_SF_data1516.root")!=std::string::npos)
	{
	  qEta=false;
	  absEta=true;
	  status=AddHistogramSet("periodData15AllYear_mu4",4.0,266904,287931);
	  status=AddHistogramSet("periodData15AllYear_mu6",6.0,266904,287931);
	  status=AddHistogramSet("periodData16AllYear_mu4",4.0,296939,314199);
	  status=AddHistogramSet("periodData16AllYear_mu6",6.0,296939,314199);
	}
      else if (inputfilename.find("singleMu_SF_2016_etabins.root")!=std::string::npos)
	{
	  qEta=true;
	  absEta=false;
	  status=AddHistogramSet("periodData16AllYear_mu4",4.0,296939,314199);
	  status=AddHistogramSet("periodData16AllYear_mu6",6.0,296939,314199);
	}
      else if (inputfilename.find("singleMu_SF_data1516_etabins.root")!=std::string::npos)
	{
	  qEta=true;
	  absEta=false;
	  status=AddHistogramSet("periodData15AllYear_mu4",4.0,266904,287931);
	  status=AddHistogramSet("periodData15AllYear_mu6",6.0,266904,287931);
	  status=AddHistogramSet("periodData16AllYear_mu4",4.0,296939,314199);
	  status=AddHistogramSet("periodData16AllYear_mu6",6.0,296939,314199);
	}
      else if (inputfilename.find("singleMu_SF_data1516_perperiod.root")!=std::string::npos)
	{
	  qEta=false;
	  absEta=true;
	  status=AddHistogramSet("periodData15D_mu4",4.0,276073,276954);
	  status=AddHistogramSet("periodData15D_mu6",6.0,276073,276954);
	  status=AddHistogramSet("periodData15E_mu4",4.0,278727,279928);
	  status=AddHistogramSet("periodData15E_mu6",6.0,278727,279928);
	  status=AddHistogramSet("periodData15F_mu4",4.0,279932,280422);
	  status=AddHistogramSet("periodData15F_mu6",6.0,279932,280422);
	  status=AddHistogramSet("periodData15G_mu4",4.0,280423,281075);
	  status=AddHistogramSet("periodData15G_mu6",6.0,280423,281075);
	  status=AddHistogramSet("periodData15H_mu4",4.0,281130,281411);
	  status=AddHistogramSet("periodData15H_mu6",6.0,281130,281411);
	  status=AddHistogramSet("periodData15J_mu4",4.0,282625,284484);
	  status=AddHistogramSet("periodData15J_mu6",6.0,282625,284484);


	  status=AddHistogramSet("periodData16A_mu4",4.0,296939,300287);
	  status=AddHistogramSet("periodData16A_mu6",6.0,296939,300287);
	  status=AddHistogramSet("periodData16B_mu4",4.0,300345,300908);
	  status=AddHistogramSet("periodData16B_mu6",6.0,300345,300908);
	  status=AddHistogramSet("periodData16C_mu4",4.0,301912,302393);
	  status=AddHistogramSet("periodData16C_mu6",6.0,301912,302393);
	  status=AddHistogramSet("periodData16D_mu4",4.0,302737,303560);
	  status=AddHistogramSet("periodData16D_mu6",6.0,302737,303560);
	  status=AddHistogramSet("periodData16E_mu4",4.0,303638,303892);
	  status=AddHistogramSet("periodData16E_mu6",6.0,303638,303892);
	  status=AddHistogramSet("periodData16F_mu4",4.0,303943,304494);
	  status=AddHistogramSet("periodData16F_mu6",6.0,303943,304494);
	  status=AddHistogramSet("periodData16G_mu4",4.0,305291,306714);
	  status=AddHistogramSet("periodData16G_mu6",6.0,305291,306714);
	  status=AddHistogramSet("periodData16I_mu4",4.0,307124,308084);
	  status=AddHistogramSet("periodData16I_mu6",6.0,307124,308084);
	  status=AddHistogramSet("periodData16K_mu4",4.0,309311,309759);
	  status=AddHistogramSet("periodData16K_mu6",6.0,309311,309759);
	  status=AddHistogramSet("periodData16L_mu4",4.0,310015,311481);
	  status=AddHistogramSet("periodData16L_mu6",6.0,310015,311481);
	}
      else if (inputfilename.find("singleMu_SF_data1516_perperiod_useAllYear.root")!=std::string::npos)
	{
	  qEta=false;
	  absEta=true;
	  status=AddHistogramSet("periodData15AllYear_mu4",4.0,266904,287931);
	  status=AddHistogramSet("periodData15AllYear_mu6",6.0,266904,287931);
	  status=AddHistogramSet("periodData16AllYear_mu4",4.0,296939,314199);
	  status=AddHistogramSet("periodData16AllYear_mu6",6.0,296939,314199);
	}
    }
}

void TriggerWeights::GenerateWeightsToy(TRandom3 *myRandomGenerator,bool stat,bool syst)
{
  if (!stat && !syst) return;
  for (int iSet=0;iSet<(int)Weights.size();iSet++)
    for (int iBinx=0;iBinx<Weights[iSet]->GetXaxis()->GetNbins();iBinx++)
      for (int iBiny=0;iBiny<Weights[iSet]->GetYaxis()->GetNbins();iBiny++)
	{
	  double mu=originalWeights[iSet]->GetBinContent(iBinx,iBiny);
	  double s_stat=Weights_stat[iSet]->GetBinContent(iBinx,iBiny);
	  double s_syst=Weights_syst[iSet]->GetBinContent(iBinx,iBiny);
	  double s;
	  if (stat) s=s_stat;
	  if (syst) s=s_syst;
	  if (stat && syst) s=TMath::Sqrt(s_stat*s_stat+s_syst*s_syst);
	  double v=myRandomGenerator->Gaus(mu,s);
	  Weights[iSet]->SetBinContent(iBinx,iBiny,v);
	}
}

void PlotWeightsPull(int nloops=1000)
{
  TRandom3 *myRandom=new TRandom3();
  TriggerWeights a("singleMu_SF_data1516_perperiod.root");
  TH1F *pullPlot=new TH1F("pullPlot","Toys Test: Pull",50,-5,5);
  for (int i=0;i<nloops;i++)
    {
      a.GenerateWeightsToy(myRandom,true,false);
      for (int iSet=0;iSet<(int)a.Weights.size();iSet++)
	for (int iBinx=0;iBinx<a.Weights[iSet]->GetXaxis()->GetNbins();iBinx++)
	  for (int iBiny=0;iBiny<a.Weights[iSet]->GetYaxis()->GetNbins();iBiny++)
	    {
	      double delta=a.Weights[iSet]->GetBinContent(iBinx,iBiny)-a.originalWeights[iSet]->GetBinContent(iBinx,iBiny);
	      double sigma=a.Weights_stat[iSet]->GetBinContent(iBinx,iBiny);
	      double pull=delta/sigma;
	      pullPlot->Fill(pull);
	    }
      
    }
  pullPlot->Draw();
}

bool TriggerWeights::AddHistogramSet(std::string histogramsetlabel,double muon_pt_threshold,int startRun,int endRun)
{
  std::string hname;

  hname="SF_"+histogramsetlabel;
  TH2F *weightHisto=(TH2F*) _file0->FindObjectAny(hname.c_str());

  hname="SF_"+histogramsetlabel+"_stat";
  TH2F *weightHisto_stat=(TH2F*) _file0->FindObjectAny(hname.c_str());

  hname="SF_"+histogramsetlabel+"_syst";
  TH2F *weightHisto_syst=(TH2F*) _file0->FindObjectAny(hname.c_str());

  if (weightHisto==NULL || weightHisto_stat==NULL || weightHisto_syst==NULL)
    {
      printf("Could not find Trigger weight histograms corresponding to %s\n",histogramsetlabel.c_str());
      return false;
    }
  else
    {
      weightHisto->SetDirectory(0);
      weightHisto_stat->SetDirectory(0);
      weightHisto_syst->SetDirectory(0);
      
      originalWeights.push_back(weightHisto);
      hname="Original_"+hname;
      Weights.push_back((TH2F*)weightHisto->Clone(hname.c_str()));
      Weights_stat.push_back(weightHisto_stat);
      Weights_syst.push_back(weightHisto_syst);
      RunMin.push_back(startRun);
      RunMax.push_back(endRun);
      PtMin.push_back(muon_pt_threshold);
    }
  return true;
}



#endif
