// Macro for performing data/MC comparison on B+->Jpsi/K+ channel
// uses unbinned ML fit to estimate number of bkg candidates 
// under the signal peak, as well as for estimation of fraction of
// continuos bkg candidates in the left sideband etc. (N.B. in "dtbgsub_mcrew" mode)
//
// Author: Iskander Ibragimov
// 02.10.2017
//
// in the file dmcbbmumuX.h are defined:
// - input data files for MC and data (single flat ntuples are curently supported)
// - output path for the plots and other output files 
// - cuts values and some special histogram binnings 
// - discriminating variables (name, binning, axislabel)
// 
// 
// 1 . if needed change source files for MC and data in *.h file (defined by the variables fdname and fmname)
// (in principle the code should also work with group ntuples on eos
// but those are not completely flat and missing preliminary and trigger selections
//
// 2. adjust CutAdd variable (in dmcbbmumuX.h) if needed (additional cuts to be applied)
//
// 3. adjust output path for the plots, etc.
//
// 4. to exectute do (after "root -l"):
// .x dmcbbmumuX.C("B_pT","dt_mcXs") //or any other variable name from dmcbbmumuX.h file
// OR
// .x dmcbbmumuX.C("systVars","dtbgsub_mcrew") // to run on all variables used for discrimination
// OR (faster, but on some OS stops after the first step - t.b.i)
// .L dmcbbmumuX.C++
// dmcbbmumuX("systVars","dt_mcXs")
//
//

#include "dmcbbmumuX.h"
using namespace std;


ofstream ofiletex(tabname);
TFile *fout = new TFile(ofilename,"RECREATE");

//store bkg fit data
bkg nbkgInfo;

//==========Forward declaration of functions===========

void compare(VariableInfo, TString, TTree*, TTree*, TString, TString, bool, bool drawResiduals=true);
TH1F* getHistoFromTree(TTree*, VariableInfo, const char*, TCut);
TLegend* defineLegendBox(TString what, Bool_t drawinlet);
TString getYAxisTitle(TString);

void dmcbbmumuX(TString compVar="", TString compMode="", TString dtlabel="2016 data run 302393", TString mclabel="MC15 bb #rightarrow #mu#muX", Bool_t verbose=true)
{
  //===========Make connections to tree's of two flat ntuple files=================================
  TChain* td = new TChain(treename);
  td->Add(fdname);
  TChain* tm = new TChain(treename);
  tm->Add(fmname);

  if (verbose) {
    cout << "Using: "<< fdname << "<-dt file name|mc file name->"<<fmname << endl;
    cout << "TREE name used in both files: "<< treename<< endl;
  }
  //==========================================================================================
  //===========Define different comparison modes of two files=================================
  vector<TString> Modes;
  Modes.push_back("mc_mc");
  Modes.push_back("dt_mcXs");

  //===========Output tex table with KS test results/variable=================================
  ofiletex << "\\begin{table}[htbp]\n";
  ofiletex << "\\caption{\\label{tab:sepVars}Data/MC agreement of separation variables}\n";
  ofiletex << "\\begin{center}\n";
  
  if (compVar=="systVars") ofiletex << "\\begin{tabular}{c|c|c}\n";
  else ofiletex << "\\begin{tabular}{c|c|c}\n";
  if (compVar=="systVars") ofiletex << "Variable & KS test & Chi2/ndf \\\\\n\\hline\n";
  else ofiletex << "Variable/Vertex type & 3-prong & 2-prong\\\\\n\\hline\n"; 
  //==========================================================================================

  //===========Loop over variables and modes and do comparison================================= 
  for (int i=0;i<nVar;i++) {
    //cout << nVar << "| "<< i << endl;
    if ((compVar!="" && compVar.CompareTo(Variables[i].name)) && !(Variables[i].usedForSystematics && compVar=="systVars")) continue;
    cout << "INFO Processing variable: " << Variables[i].name<<endl;
    for (unsigned int j=0;j<Modes.size();j++) {
      if (compMode!="" && compMode.CompareTo(Modes[j])) continue;
      cout << "INFO Processing mode: " << Modes[j]<<endl;
      compare(Variables[i], Modes[j], td, tm, dtlabel, mclabel, true, true);
    }
  }
  fout->cd();
  fout->Close();
  //==========================================================================================
  //===========Finish writing out table ================================= 
  ofiletex << "\\end{tabular}\n";
  ofiletex << "\\end{center}\n";
  ofiletex << "\\end{table}\n";
  ofiletex.close();
  //==========================================================================================
}

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
    if (tmpDummy.Contains("BvtxPt") || tmpDummy.Contains("B_pT") || tmpDummy.Contains("JPsiPt") || tmpDummy.Contains("BTruthPt")) hret = new TH1F(*hdummyPt); 
    else if (tmpDummy.Contains("eta") || tmpDummy.Contains("Eta")) hret = new TH1F(*hdummyEta);
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
  cout << "Creating histo, title "<< hname <<", hret integral.."<< hret->Integral() <<endl; //cut out over- and unerflows
  cout << endl;
  return hret;
}

void compare(VariableInfo Variable, TString mode, TTree* td, TTree* tm, TString dtlabel, TString mclabel, bool normalize, bool drawResiduals)
{
  TH1F* h1(NULL);
  TH1F* h2(NULL);
  TString h1title = Variable.name;
  if (h1title.Contains("TMath::Abs")) h1title.ReplaceAll("TMath::Abs","fabs");
  if (h1title.Contains('(')) h1title.ReplaceAll('(','_');
  if (h1title.Contains(')')) h1title.ReplaceAll(')','_');
  if (h1title.Contains('/')) h1title.ReplaceAll('/','_');

  TString h2title(h1title);
  TString htitle(h1title);
  TString hdivtitle(h1title);

 if (mode.EqualTo("mc_mc")) {
    h1title+="_mc12";
    h1 = getHistoFromTree(td, Variable, h1title, CutBase && CutLSBLow && CutRSBHigh && "CombWeights*PVWeights*CatN1Weights*CatN2Weights*CatN3Weights*isSignal");
    h2title+="_mc15";
    h2 = getHistoFromTree(tm, Variable, h2title, CutBase && CutLSBLow && CutRSBHigh && "(nphotons==0)*CombWeights*PVWeights*CatN1Weights*CatN2Weights*CatN3Weights*isSignal");
  } else if (mode.EqualTo("dt_mcXs")) {
    h1title+="_dt16";
    h1 = getHistoFromTree(td, Variable, h1title, CutAdd);
    h2title+="_mcX";
    h2 = getHistoFromTree(tm, Variable, h2title, CutAdd*"CombWeights");
  } 

  TCanvas *c1 = (TCanvas*)gROOT->FindObject("c1");
  if (c1) c1->Clear();
  else c1 = new TCanvas("c1","c1",0,45,800,600);
  c1->SetLogy(0);
  c1->SetLeftMargin(0.13);
  c1->SetRightMargin(0.10); //0.07
  c1->SetTopMargin(0.07);
  c1->SetBottomMargin(0.12);
  h1->SetLineWidth(2);        if (h2) h2->SetLineWidth(2); 
  h1->SetFillColor(0);        if (h2) h2->SetFillColor(0);//kRed);/*30*/
  h1->SetLineColor(kBlack);   if (h2) h2->SetLineColor(kGreen+2); 
  h1->SetLineStyle(1);        if (h2) h2->SetLineStyle(1);/*22*/
  h1->SetMarkerSize(0.8);     if (h2) h2->SetMarkerSize(0.8);
  h1->SetMarkerStyle(20);     if (h2) h2->SetMarkerStyle(25);   
  h1->SetMarkerColor(kBlack); if (h2) h2->SetMarkerColor(kGreen+2);
  if (h2) h2->SetFillStyle(3002);
  //if (h2) h2->SetMarkerSize(0);


  //  h2->SetFillStyle(3004);
  if (Variable.nbins>0 && Variable.XMin!= Variable.XMax) {
    h1->GetXaxis()->SetRangeUser(Variable.XMin,Variable.XMax);
    if (h2) h2->GetXaxis()->SetRangeUser(Variable.XMin,Variable.XMax);
  }
  else if (Variable.nbins!=-1) { 
    if (h2) h2->GetXaxis()->Set(h1->GetXaxis()->GetNbins(),h1->GetXaxis()->GetXmin(),h1->GetXaxis()->GetXmax());
  }
  if (normalize) {
    //typically means normalize MC(h2) to data (h1)
    //
    cout << endl;
    cout << "INFO Integral of entries of each histo BEFORE normalization: " << endl;
    cout << h1->GetTitle() <<": "<< h1->Integral();
    if (h2) cout << " "<< h2->GetTitle()<< ": "<< h2->Integral();
    cout << endl;
    cout << endl;
    
    h2->Scale(h1->Integral()/h2->Integral()); // ATTENTION under- and over-flows not taken into account!!!  
  }
  TString axLab = Variable.axLabel;
  h1->GetXaxis()->SetTitle(axLab);
  if (h2) {
    h2->GetXaxis()->SetTitle(axLab);
  }

  if (drawResiduals) {
    h1->GetYaxis()->SetTitleOffset(0.7); //0.57
    h1->GetYaxis()->SetTitleSize(0.08);
    if (h2) {
      h2->GetYaxis()->SetTitleOffset(0.7); //0.57
      h2->GetYaxis()->SetTitleSize(0.08);
    }
  }
  else {
    h1->GetYaxis()->SetTitleOffset(0.72);
    h1->GetYaxis()->SetTitleSize(0.07);
    if (h2) {
      h2->GetYaxis()->SetTitleOffset(0.72);
      h2->GetYaxis()->SetTitleSize(0.07);
    }
  }
 
  TString yAxisTitle = getYAxisTitle(Variable.name);
  if (Variable.nbins>0 && Variable.XMin!= Variable.XMax) {
    yAxisTitle +=" / ";
    char buf[20];
    sprintf(buf,"%3.2f",(Variable.XMax-Variable.XMin)/(double)Variable.nbins);
    yAxisTitle+=buf;
    yAxisTitle += " "; //FMPLOT
    TString dummyStr(axLab);
    dummyStr.Remove(0,dummyStr.Index('[')+1);
    dummyStr.Remove(dummyStr.Index(']'),dummyStr.Length());
    if (axLab.Contains("[")) yAxisTitle += dummyStr;
  }
  h1->GetYaxis()->SetTitle(yAxisTitle);
  if (h2) h2->GetYaxis()->SetTitle(yAxisTitle); 

  Double_t chi2_1(0.),ks1(0.);
  Int_t ndf_1(0), igood_1(0);
 
  if (h2) {
    h1->Chi2TestX(h2,chi2_1,ndf_1,igood_1,"WW P"); //Weighted Weighted Print
    ks1 = h1->KolmogorovTest(h2);
    TString tabentry(Variable.axLabel);
    if (tabentry.Contains("DeltaR")) tabentry.ReplaceAll("DeltaR","Delta~R");
    char buf[20];
    sprintf(buf,"%5.1f/%3d",chi2_1,ndf_1);
    ofiletex << "$"<< tabentry.ReplaceAll('#','\\') <<"$" << " & "<< ks1 << " & "<< buf << "\\\\\n\\hline\n";
  }

  TPad *pad1, *pad2;
  pad1 = new TPad("pad1","pad1",0,0.33,1,1); //xlow ylow xup yup
  pad2 = new TPad("pad2","pad2",0,0,1,0.33); //0.3

  if (drawResiduals) {
    pad1->SetMargin(0.12,0.05,0.028,0.09);
    pad1->SetBorderMode(0);
    if (Variable.logScale) pad1->SetLogy();
    if (h2) {
      pad2->SetMargin(0.12,0.05,0.38,0.06);
      pad2->SetBorderMode(0);
      pad1->Draw();
      pad2->Draw();
      pad1->cd();
    }
  }

  if (h2 && h2->GetMean()!=0 && h2->GetRMS()!=0) {
    h1->GetYaxis()->SetLabelSize(0.08);
    h1->GetXaxis()->SetNoExponent();
    h2->GetYaxis()->SetLabelSize(0.08);
    h2->GetXaxis()->SetNoExponent();
    h1->GetXaxis()->SetLabelOffset(0.028); //0.07
    h2->GetXaxis()->SetLabelOffset(0.028); //0.07
    h1->GetXaxis()->SetTitle("");
    h2->GetXaxis()->SetTitle("");
    cout << h1->GetMaximum() <<" <=h1max|h2max-> "<<h2->GetMaximum()<< endl;
    if (h1->GetMaximum()>h2->GetMaximum()) {
      h1->SetMaximum(h1->GetMaximum()*1.5);
      h1->Draw("");
      h1->Draw("epsame");
      h2->Draw("histsame");
      if(!h1->GetFillColor()) h1->Draw("epsame");
    } else {
      h2->SetMaximum(h2->GetMaximum()*1.5);
      h2->Draw("");
      h2->Draw("histsame");
      h1->Draw("epsame");
    }
  } else {
    h1->Draw("ep");
  }

  htitle+="_";
  htitle+=mode;

  TLegend *leg = defineLegendBox(Variable.name, drawResiduals);
  leg->SetBorderSize(0);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetTextFont(132);
  if (h2) {
    if (mode.Contains("dtbgsub_mcrew")) {
      leg->AddEntry(h1,"Background-subtracted data run 302393","p"); //FIXMELEGEND
      leg->AddEntry(h2,"B^{+}#rightarrow J/#psi K^{+} MC15","l"); 
    } else {
      dtlabel+=" (A)";
      mclabel+=" (B)";
      leg->AddEntry(h1,dtlabel,"elp");
      leg->AddEntry(h2,mclabel,"elp");
    }
  }
 
  leg->Draw();

  bool drawResError = true;
  if (drawResiduals) {
    pad2->cd();
    TH1F *hres = (TH1F*)h1->Clone("hres");
    cout << "Before plotting" << endl;
    hres->SetMarkerSize(0.7);
    hres->GetXaxis()->SetTitleOffset(1.0); //0.95
    hres->GetXaxis()->SetTitle(axLab);
    hres->GetXaxis()->SetTitleSize(0.17);
    hres->GetXaxis()->SetLabelSize(0.15); //0.17 0.1
    
    hres->GetYaxis()->SetTitleSize(0.17);
    hres->GetYaxis()->SetTitleOffset(0.32); //0.26
    if (mode.Contains("dtbgsub_mcrew")) hres->GetYaxis()->SetTitle("Data/MC"); //FIXMELEGEND
    else hres->GetYaxis()->SetTitle("A/B");
    hres->GetYaxis()->SetLabelSize(0.12);//0.17 //0.08
    hres->GetYaxis()->SetNdivisions(4,3,0); //4,5,0
    
    cout << "DEBUG " << " bin2 content: "<<h1->GetBinContent(2) << " error: "<< h1->GetBinError(2) << endl;
    if (h2) cout << "DEBUG " << " bin2 content: "<<h2->GetBinContent(2) << " error: "<< h2->GetBinError(2) << endl;
    cout << "DEBUG " << " bin4 content: "<<h1->GetBinContent(4) << " error: "<< h1->GetBinError(4) << endl;
    if (h2) cout << "DEBUG " << " bin4 content: "<<h2->GetBinContent(4) << " error: "<< h2->GetBinError(4) << endl;
    
    hres->Sumw2();
    
    hres->Divide(h1,h2,1.0,1.0); //RATIO
    hres->GetYaxis()->SetRangeUser(0.,3.5);//0,2);//0.55,1.75);

    hres->Draw("");
    hres->Draw("epsame");
    
    TLine *l = new TLine(h1->GetXaxis()->GetXmin(),1,h1->GetXaxis()->GetXmax(),1);
    l->SetLineColor(kBlack);
    l->SetLineStyle(2);
    l->SetLineWidth(3);
    l->Draw();
    
    TPaveText *chi2res = new TPaveText(0.72,0.76,0.98,0.95,"brNDC"); //0.62,0.56,0.88,0.75
    chi2res->SetName("chi2res");
    chi2res->SetFillStyle(0);
    chi2res->SetTextAlign(12);
    chi2res->SetTextSize(0.1);
    chi2res->SetBorderSize(0);
    char buf[20];
    sprintf(buf,"#chi^{2}/ndf = %5.1f/%3d",chi2_1,ndf_1);
    chi2res->AddText(buf);
    sprintf(buf,"KS test = %1.6f",ks1);
    chi2res->AddText(buf);
    chi2res->Draw();  //FIXME KSSTAT
  }

  fout->cd();
  
  h1->SetTitle("dataSR");
  h1->SetName("dataSR");

  if (h2) {
    // create histogram with data/MC ratios
    //
    h2->SetName("dataSB");
    h2->SetTitle("dataSB");
  
    TH1F* hdiv =(TH1F*)h1->Clone("hdiv");
    hdivtitle  = Variable.name;
    hdivtitle+="_div_data_by_mc";
    hdiv->Sumw2();
    hdiv->Divide(h1,h2,1.0/h1->Integral(),1.0/h2->Integral());
    for (Int_t i=1;i<=hdiv->GetNbinsX();i++) {
      if (hdiv->GetBinContent(i) < 0) {
	hdiv->SetBinContent(i, 1.0);
	hdiv->SetBinError(i, 0.);
      }
    }
    hdiv->SetTitle(hdivtitle);
    hdiv->SetName(hdivtitle);
    hdiv->Write();
  }

  c1->cd();
  c1->Update();
  c1->SaveAs(outpath+htitle+".eps");
  //
  //
  /*
  c1->SaveAs(outpath+htitle+".C");
  c1->SaveAs(outpath+htitle+".root");
  c1->SaveAs(outpath+htitle+".gif");
  */
  

  c1->Write(htitle);
  delete h1;
  delete h2;
  delete pad2;
  delete pad1;
  delete c1;
}

void atlasLabel(Double_t x,Double_t y, bool drawRes = true, bool Preliminary=true,Color_t color=1, bool drawLumi=false, bool enlarge=false)
{
  double delx = 0.115*696*gPad->GetWh()*3/(5*472*gPad->GetWw());
  double textsize;
  double dy = 0.065;
  if (!drawRes) {
    delx+=0.02;
    textsize = 0.040;
  } else {
    if (enlarge) {
      textsize = 0.075; 
      delx+=0.04;
      dy = 0.125;
    }
    else textsize = 0.045;
  }
  TLatex *tex = new TLatex(x,y,"ATLAS");
  tex->SetNDC();
  tex->SetTextSize(textsize);
  tex->SetTextFont(72);
  tex->SetLineWidth(2);
  tex->SetTextColor(color);
  tex->Draw();
  if (Preliminary) {
    tex = new TLatex(x+delx,y,"for approval"); //Preliminary
    tex->SetNDC();
    tex->SetTextSize(textsize);
    tex->SetTextFont(42); //42
    tex->SetLineWidth(2);
    tex->SetTextColor(color);
    tex->Draw();
  }
  tex = new TLatex(x+0.02,y-dy,"#sqrt{s} = 7 TeV");
  tex->SetNDC();
  tex->SetTextSize(textsize);
  tex->SetTextFont(42);
  tex->SetLineWidth(2);
  tex->SetTextColor(color);
  tex->Draw();
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

TLegend* defineLegendBox(TString what, Bool_t drawinlet){
  TLegend* leg;
  if (drawinlet){
    if (what.Contains("Iso") || what.Contains("_iso_7") || what.Contains("_iso_5")) leg = new TLegend(0.14,0.74,0.64,0.94,NULL,"brNDC"); //xbl,ybl,xur,yur
    else if (what.Contains("_iso_Ntracks")) leg = new TLegend(0.43,0.74,0.93,0.94,NULL,"brNDC");
    else if (what.Contains("DR")) leg = new TLegend(0.39,0.72,0.89,0.92,NULL,"brNDC");
    else if (what.Contains("Eta") || what.Contains("eta") || what.Contains("deltaPhi")) leg = new TLegend(0.12,0.22,0.62,0.42,NULL,"brNDC");
    else if (what.Contains("lnChi2") || what.Contains("Chi2Muons") || what.Contains("chi2_PVSV") || what.Contains("SumMuTrackPixHits")) leg = new TLegend(0.17,0.74,0.67,0.94,NULL,"brNDC");
    else if (what.Contains("BDT")) leg = new TLegend(0.12,0.66,0.85,0.82,NULL,"brNDC");
    else leg = new TLegend(0.45,0.74,0.95,0.94,NULL,"brNDC"); //xbl(0.71),ybl(0.62),xur(0.98),yur(0.98)
  } else {
    if (what.Contains("Iso") || what.Contains("d0") || what.Contains("Eta") || what.Contains("eta") || what.Contains("DCA") || what.Contains("BDT")) leg = new TLegend(0.15,0.64,0.68,0.92,NULL,"brNDC"); //xbl,ybl,xur,yur //0.09
    else if (what.Contains("DR")) leg = new TLegend(0.45,0.74,0.68,0.92,NULL,"brNDC");
    else leg = new TLegend(0.74,0.75,0.95,0.93,NULL,"brNDC"); //xbl(0.71,0.68),ybl(0.62),xur(0.98),yur(0.98)
  }
  return leg;
}

TString getYAxisTitle(TString what) {
  TString yAxisTitle;
  if (what.Contains("JPsi")) {
    yAxisTitle = "J/#psi candidates";
  } else if (what.Contains("Mu") && !what.Contains("Mult")) {
    yAxisTitle = "#mu candidates";
  } else if (what.Contains("Kaon")) {
    yAxisTitle = "Kaon candidates";
  }  else if (what.Contains("d0")) {
    yAxisTitle = "#mu tracks";
  }
  else {
    yAxisTitle = "Events";
    //yAxisTitle = "B^{#pm} candidates"; 
    //yAxisTitle = "B_{s} candidates";
  }
  return yAxisTitle;
}
