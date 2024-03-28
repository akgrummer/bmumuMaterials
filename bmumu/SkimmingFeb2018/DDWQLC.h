
#ifndef DDWQLC_CLASS_LOADED
#define DDWQLC_CLASS_LOADED

/*********************************************************************************************************************************/
/*                                                                                                                               */
/* Version 1.0                                                                                                                   */
/*                                                                                                                               */
/* This class provides the following functionalities:                                                                            */
/* each class instance allows to access one set of DDW or QLC                                                                    */
/*                                                                                                                               */
/* Instantiate the class as:                                                                                                     */
/*  DDWQLC myDDW("<root file name>","<covariance histogram name>","<pt weights histogram name>","<eta weights histogram name>"); */
/*  for DDW, and as:                                                                                                             */
/*  DDWQLC myQLC("<root file name>","<errors histogram name>","<2D pt-eta weights histogram name>");                             */
/*  for QLC                                                                                                                      */
/*    (in the typical case where you want to access QLC and DDW weights, you will need two separate instance of this class       */
/*                                                                                                                               */
/* given a candidate's eta and pt, the corresponding (eta*pt) weight is retrieved as:                                            */
/* myDDW.GetWeight(<candidate eta>,<candidate pt>)                                                                               */
/*                                                                                                                               */
/* by default GetWeight(...) accesses the weights provided in the input file, which are also always accessible through the       */
/* myDDW.GetOriginalWeight(...)                                                                                                  */
/*                                                                                                                               */
/* After a call to GenerateToy(<random seed value>) GetWeight will return weights generated randomly on the basis of the input   */
/* file covariance matrix. The same set of 'toy' weights is accessed through GetWeight until GenerateToy is called again         */
/*                                                                                                                               */
/*********************************************************************************************************************************/

#include "TH2D.h"
#include "TH1D.h"
#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TRandom3.h"
#include "TMatrixD.h"
#include "TMatrixDEigen.h"
#include "TF2.h"
#include "TMath.h"

class DDWQLC
{
 public:
  DDWQLC(TString inputfilename, TString covarianceHName, TString ptHName, TString etaHName);
  /* "DDWfile_BpToJpsiK.root","h_covarianceDDW_odd_BpJpsiK","h_DDWpt_o	dd_BpJpsiK","h_DDWeta_odd_BpJpsiK" */
  
  DDWQLC(TString inputfilename, TString errorHName, TString ptetaHName);
  /* "QLCfile_BpToJpsiK.root","h_QLC_err_BpJpsiK","h_QLC_BpJpsiK" */
  void GenerateToy(int seed=0); /* generate toy set of weights which will be accessible through GetWeight */
  void UseOriginalWeights();    /* reset GetWeight internal structures and make sure GetWeight points back at the original input weights */
  
  double GetWeight(double eta,double pt); /* access either default input weights or toy generated set, depending on whether 'GenerateToy() was called */
  double GetOriginalWeight(double eta,double pt); /* access original input weights no matter whether a toy set of weights was generated or not */

    
  /* test classes used in development/check of input by developer */
  void TestSubMatrixRandomGeneration(int ii,int jj,int ntrials=10000);
  void TestSingleWeightRandomGeneration(int ii,int ntrials);
 private:
  TH2D *weights_cv;
  TRandom3 *myRandom;
    
  TMatrixD *cv;
  TMatrixD *cvEigenVectors;
  TVectorD *cvEigenValues;
  TVectorD *GeneratedDeltaW;
  
  TH1D *eta_weights;
  TH1D *pt_weights;
  TH2D *eta_pt_weights;
  TH2D *err_eta_pt_weights;
    
  TH1D *ref_eta_weights;
  TH1D *ref_pt_weights;
  TH2D *ref_eta_pt_weights;
  bool is_toy;
  int toy_seed;
};



DDWQLC::DDWQLC(TString inputfilename, TString errorHName, TString ptetaHName)
{
  err_eta_pt_weights=eta_pt_weights=ref_eta_pt_weights=NULL;
  weights_cv=NULL;
  eta_weights=pt_weights=ref_eta_weights=ref_pt_weights=NULL;
  TFile *_file0 = TFile::Open(inputfilename ,"read");
  if (_file0==NULL)
    {
      std::cout << Form("DDWQLC Class ERROR: Cannot find file %s, abort!\n", inputfilename.Data()) << std::endl;
    }
  else
    {
      eta_pt_weights    = (TH2D*)_file0->Get(ptetaHName.Data()); 
      err_eta_pt_weights= (TH2D*)_file0->Get(errorHName.Data());
      if (eta_pt_weights==NULL || err_eta_pt_weights==NULL)
	{
	  printf("Couldnt find one of the required histograms (eta_pt ptr=%p,err_eta_pt_ptr=%p)\n",eta_pt_weights,err_eta_pt_weights);
	  exit(0);
	}
      
      eta_pt_weights->SetDirectory(0);
      err_eta_pt_weights->SetDirectory(0);
      ref_eta_pt_weights=(TH2D*)eta_pt_weights->Clone("ref_eta_pt_weights");
      ref_eta_pt_weights->Copy(*eta_pt_weights); ref_eta_pt_weights->SetDirectory(0);
    }
  myRandom=new TRandom3();
  printf("Input histograms loaded\n");
}

DDWQLC::DDWQLC(TString inputfilename, TString covarianceHName, TString ptHName, TString etaHName)
{
  err_eta_pt_weights=eta_pt_weights=ref_eta_pt_weights=NULL;
  weights_cv=NULL;
  eta_weights=pt_weights=ref_eta_weights=ref_pt_weights=NULL;
  TFile *_file0 = TFile::Open(inputfilename ,"read");
  if (_file0==NULL)
    {
      std::cout << Form("DDWQLC Class ERROR: Cannot find file %s, abort!\n", inputfilename.Data()) << std::endl;
    }
  else
    {
      TH2D *in_weights_cv  = (TH2D*)_file0->Get(covarianceHName.Data());
      TH1D *in_eta_weights = (TH1D*)_file0->Get(etaHName.Data());
      TH1D *in_pt_weights  = (TH1D*)_file0->Get(ptHName.Data());

      if (in_weights_cv==NULL || in_eta_weights==NULL || in_pt_weights==NULL)
	{
	  printf("Couldnt find one of the required histograms (covariance ptr=%p,eta ptr=%p,pt ptr=%p)\n",in_weights_cv,in_eta_weights,in_pt_weights);
	  exit(0);
	}

      weights_cv=(TH2D*)in_weights_cv->Clone("weights_cv"); weights_cv->SetDirectory(0);
      int nx=weights_cv->GetNbinsX();
      int ny=weights_cv->GetNbinsY();
      cv=new TMatrixD(nx,ny);
      for (int ii=1;ii<=weights_cv->GetNbinsX();ii++)
	for (int jj=1;jj<=weights_cv->GetNbinsY();jj++)
	  {
	    (*cv)(nx-ii,jj-1)=weights_cv->GetBinContent(ii,jj);
	  }

      TMatrixDEigen Eigen(*cv);
      cvEigenValues=new TVectorD(cv->GetNrows());
      cvEigenVectors=new TMatrixD(cv->GetNrows(),cv->GetNcols());

      (*cvEigenValues) =Eigen.GetEigenValuesRe();
      (*cvEigenVectors)=Eigen.GetEigenVectors();

      // cvEigenValues->Print();
      // cvEigenVectors->Print();
      
      eta_weights=(TH1D*)in_eta_weights->Clone("eta_weights"); eta_weights->SetDirectory(0);
      pt_weights =(TH1D*)in_pt_weights ->Clone( "pt_weights");  pt_weights->SetDirectory(0);

      ref_eta_weights=(TH1D*)in_eta_weights->Clone("ref_eta_weights"); ref_eta_weights->SetDirectory(0);
      ref_pt_weights =(TH1D*)in_pt_weights ->Clone( "ref_pt_weights");  ref_pt_weights->SetDirectory(0);
      is_toy=false;
      toy_seed=-1;
      myRandom=new TRandom3();
    }
  printf("Input histograms loaded\n");
}

void DDWQLC::UseOriginalWeights()
{
  is_toy=false;
  if (eta_pt_weights)
    {
      eta_pt_weights->Copy(*ref_eta_pt_weights);
    }
  else
    {
      eta_weights->Copy(*ref_eta_weights);
      pt_weights->Copy(*ref_pt_weights);
    }
}

double DDWQLC::GetWeight(double eta,double pt)
{
  if (eta_pt_weights)
    {
      int ixbin=eta_pt_weights->GetXaxis()->FindBin(eta);
      ixbin=(ixbin>eta_pt_weights->GetXaxis()->GetNbins())?eta_pt_weights->GetXaxis()->GetNbins():ixbin;
      int iybin=eta_pt_weights->GetYaxis()->FindBin(pt);
      iybin=(iybin>eta_pt_weights->GetYaxis()->GetNbins())?eta_pt_weights->GetYaxis()->GetNbins():iybin;
      if (ixbin>0 && iybin>0)
	return 1.0/eta_pt_weights->GetBinContent(ixbin,iybin);
      else
	{
	  printf("QLC bin not found for eta:%f pt:%f\n",eta,pt);
	  return -1;
	}
    }
  else
    {
      int ieta=eta_weights->FindBin(eta);
      ieta=(ieta>eta_weights->GetNbinsX())?eta_weights->GetNbinsX():ieta;
      if (ieta<=0) printf("Eta value %f nod found in histogram bounds (%f,%f)\n",eta,
			  eta_weights->GetXaxis()->GetXmin(),
			  eta_weights->GetXaxis()->GetXmax());
      int  ipt= pt_weights->FindBin(pt);
      ipt=(ipt>pt_weights->GetNbinsX())?pt_weights->GetNbinsX():ipt;
      if (ipt<=0) printf("pT value %f nod found in histogram bounds (%f,%f)\n",pt,
			 pt_weights->GetXaxis()->GetXmin(),
			 pt_weights->GetXaxis()->GetXmax());

      
      if ((ieta>0)&&(ipt>0))
	{
	  double etaw=eta_weights->GetBinContent(ieta);
	  double ptw =pt_weights->GetBinContent(ipt);
	  // printf("%f %f\n",etaw,ptw);
	  return etaw*ptw;
	}
      else
	return -1;
    }
}

double DDWQLC::GetOriginalWeight(double eta,double pt)
{
  if (eta_pt_weights)
    {
      int ibin=ref_eta_pt_weights->FindBin(eta,pt);
      if (ibin>0)
	return 1.0/ref_eta_pt_weights->GetBinContent(ibin);
      else
	{
	  printf("QLC bin not found for eta:%f pt:%f\n",eta,pt);
	  return -1;
	}
    }
  else
    {
      int ieta=ref_eta_weights->FindBin(eta);
      int  ipt=ref_pt_weights->FindBin(pt);
      if ((ieta>0)&&(ipt>0))
	return ref_eta_weights->GetBinContent(ieta)*ref_pt_weights->GetBinContent(ipt);
      else
	return -1;
    }
}

void DDWQLC::GenerateToy(int seed)
{
  myRandom->SetSeed(seed);

  if (eta_pt_weights)
    {
      int nx=eta_pt_weights->GetNbinsX();
      int ny=eta_pt_weights->GetNbinsY();
      for (int ii=1;ii<=nx;ii++)
	for (int jj=1;jj<=ny;jj++)
	  {
	    double mu   =ref_eta_pt_weights->GetBinContent(ii,jj);
	    double sigma=err_eta_pt_weights->GetBinContent(ii,jj);
	    double newvalue=myRandom->Gaus(mu,sigma);
	    eta_pt_weights->SetBinContent(ii,jj,newvalue);
	  }
    }
  else
    {
      int n=weights_cv->GetNbinsX();
      TVectorD win(n);
      TVectorD Sig(n);
      
      for (int i=0;i<n;i++)
	{
	  double sigma=TMath::Sqrt((*cvEigenValues)(i));
	  double r=myRandom->Gaus(0.0,sigma);
	  win(i)=r;
	  //    printf("%f\n",r);
	}
      
      GeneratedDeltaW=new TVectorD(n);
      (*GeneratedDeltaW)=(*cvEigenVectors)*win;
      int ibin=0;
      for (int i=0;i<pt_weights->GetNbinsX();i++)
	{
	  double w=ref_pt_weights->GetBinContent(i+1)+(*GeneratedDeltaW)(ibin);
	  pt_weights->SetBinContent(i+1,w);
	  ibin++;
	}
      for (int i=0;i<eta_weights->GetNbinsX();i++)
	{
	  double w=ref_eta_weights->GetBinContent(i+1)+(*GeneratedDeltaW)(ibin);
	  eta_weights->SetBinContent(i+1,w);
	  ibin++;
	}
    }
}

void DDWQLC::TestSingleWeightRandomGeneration(int ii,int ntrials)
{
  TCanvas *tst=new TCanvas();
  tst->Divide(2,2);

  if (eta_pt_weights)
    {
      tst->cd(1); eta_pt_weights->Draw("colz"); tst->cd(2); err_eta_pt_weights->Draw("colz");
    }
  else
    {
      tst->cd(1); pt_weights->Draw(); tst->cd(2); eta_weights->Draw();
    }

  double mux=0.0;
  TH1D *theh;
  int ix,iy,theidx;
  double xx=0.0;
  if (eta_pt_weights)
    {
      int nx=eta_pt_weights->GetNbinsX();
      ix=ii%nx;
      iy=(ii-ix)/nx;
      printf("%i %i\n",ix,iy);
      mux=eta_pt_weights->GetBinContent(ix,iy);
      xx=5*err_eta_pt_weights->GetBinContent(ix,iy);
    }
  else
    {
      xx=5*TMath::Sqrt((*cv)(ii,ii));
      int npx=pt_weights->GetNbinsX();
      //      int nex=eta_weights->GetNbinsX();
      
      if (ii<npx)
	{
	  theh=pt_weights;
	  theidx=ii+1;
	}
      else
	{
	  theh=eta_weights;
	  theidx=ii-npx;
	}
      mux=theh->GetBinContent(theidx);
    }


  int nbins=50;
  TH1F *hx=new TH1F("hx","X projection",nbins,mux-xx,mux+xx);

  for (int i=0;i<ntrials;i++)
    {
      GenerateToy();
      double v=0.0;
      if (eta_pt_weights)
	{
	  v=eta_pt_weights->GetBinContent(ix,iy);
	}
      else
	{
	  v=theh->GetBinContent(theidx);
	}
      hx->Fill(v);
    }  
  tst->cd(3); hx->Fit("gaus");
}

void DDWQLC::TestSubMatrixRandomGeneration(int ii,int jj,int ntrials)
{
  TCanvas *tst=new TCanvas();
  tst->Divide(2,2);

  printf("The Submatrix being tested:\n");
  printf("\t %f \t %f\n",(*cv)(ii,ii),(*cv)(ii,jj));
  printf("\t %f \t %f\n",(*cv)(jj,ii),(*cv)(jj,jj));
  
  double xx=5*TMath::Sqrt((*cv)(ii,ii));
  double yy=5*TMath::Sqrt((*cv)(jj,jj));
  int nbins=50;
  TH2F *scatter=new TH2F("scatter","Scatter Test",nbins,-xx,+xx,nbins,-yy,+yy);
  TH1F *hx=new TH1F("hx","X projection",nbins,-xx,xx);
  TH1F *hy=new TH1F("hy","Y projection",nbins,-yy,yy);
  
  for (int i=0;i<ntrials;i++)
    {
      GenerateToy();
      scatter->Fill((*GeneratedDeltaW)(ii),(*GeneratedDeltaW)(jj));
      hx->Fill((*GeneratedDeltaW)(ii));
      hy->Fill((*GeneratedDeltaW)(jj));
    }

  tst->cd(1); hx->Fit("gaus");
  tst->cd(2); hy->Fit("gaus");
  tst->cd(3); scatter->Draw("colz");

  TF2 *f3=new TF2("f3","(([0]/2/3.1415/sqrt([1]*[3]-[2]*[2]))*exp(-([3]*x*x-2*[2]*x*y+[1]*y*y)/2.0/([1]*[3]-[2]*[2])))",-xx,xx,-yy,yy);

  f3->SetParameters(ntrials/nbins/nbins,(*cv)(ii,ii),((*cv)(ii,jj)),(*cv)(jj,jj));
  double f3int=f3->Integral(-xx,xx,-yy,yy);
  printf("%f\n",f3int);
  tst->cd(3); scatter->Fit(f3);

  printf("These two matrices should be very similar:\n");
  printf("\t %f \t %f\t\t %f \t %f \n",(*cv)(ii,ii),(*cv)(ii,jj),f3->GetParameter(1),f3->GetParameter(2));
  printf("\t %f \t %f\t\t %f \t %f \n",(*cv)(jj,ii),(*cv)(jj,jj),f3->GetParameter(2),f3->GetParameter(3));
}

#endif


