TGraphErrors* Iso_logAccept_ROCs_reverse(TTree* EvalTreeSig, TTree* EvalTreeBkg, 
                VariableInfo isoVarSig, TCut CutAddSig, 
                VariableInfo isoVarBkg, TCut CutAddBkg,
                TCut theWeight, Int_t ColorIndex){

/////////////ROC

TH1F *hROCSig(NULL);
TH1F *hROCSig_w2(NULL);
TH1F *hROCBkg(NULL);
// TH1F *hROCSigNoWeight(NULL);
// TH1F *hWeight(NULL);

int NumberOfBinsROC = isoVarSig.nbins;
TString h1title = "IsolationHist";
hROCSig = getHistoFromTree(EvalTreeSig, isoVarSig, h1title, CutAddSig*theWeight);
h1title = "IsolationHist_w2";
hROCSig_w2 = getHistoFromTree(EvalTreeSig, isoVarSig, h1title, CutAddSig*theWeight*theWeight);
// h1title = "IsolationHist_noWeight";
// hROCSigNoWeight = getHistoFromTree(EvalTreeSig, isoVarSig, h1title, CutAddSig);
// hWeight = (TH1F*)hROCSig->Clone("hWeight");
// hWeight->Divide(hROCSigNoWeight);
h1title = "IsolationHist_Bkg";
hROCBkg =getHistoFromTree(EvalTreeBkg, isoVarBkg, h1title, CutAddBkg);
hROCSig->Sumw2();
hROCBkg->Sumw2();


// hROCSig->Scale(1.0/hROCSig->Integral(0, NumberOfBinsROC));
// hROCBkg->Scale(1.0/hROCBkg->Integral(0, NumberOfBinsROC));
// TCanvas* c1 = new TCanvas("c1", "var comps",0.,0., 800, 600);
// hROCSig->Draw("al");
// hROCBkg->Draw("same l");
// TString OutdirName = "/afs/cern.ch/user/a/agrummer/www/bmumu/IsoVarROCs/";
// c1->SaveAs(OutdirName + "Figures/VarCompCheck.pdf");

//////////////////////////////////////////

vector<Double_t> SigTestEff;
vector<Double_t> BkgTestRej;
vector<Double_t> BkgTestEff;
vector<Double_t> SigTestEff_err;
vector<Double_t> BkgTestEff_err;
for(int i = 1; i<NumberOfBinsROC; i++){
  // cout<<i<<endl;
  SigTestEff.push_back((hROCSig->Integral(0, i))/(hROCSig->Integral(0, NumberOfBinsROC)));
  BkgTestRej.push_back(1-(hROCBkg->Integral(0, i)/(hROCBkg->Integral(0, NumberOfBinsROC))));
  BkgTestEff.push_back((hROCBkg->Integral(0, i))/(hROCBkg->Integral(0, NumberOfBinsROC)));
  // SigTestEff_err.push_back(sqrt((SigTestEff[NumberOfBinsROC-i])*(100.-SigTestEff[NumberOfBinsROC-i])/hROCSig->GetBinContent(NumberOfBinsROC-i)));
  // BkgTestEff_err.push_back(sqrt((BkgTestEff[NumberOfBinsROC-i])*(100.-BkgTestEff[NumberOfBinsROC-i])/hROCBkg->GetBinContent(NumberOfBinsROC-i)));
}
vector<Double_t> wp;
vector<Double_t> w2p;
vector<Double_t> wm;
vector<Double_t> w2m;
vector<Double_t> w2;

for(int i = 0; i<NumberOfBinsROC-1; i++){
  BkgTestEff_err.push_back(sqrt((BkgTestEff[i]*(1-BkgTestEff[i]))/(hROCBkg->Integral(0, NumberOfBinsROC) ) ) );
 } // cout << BkgTestEff[i]<< " "<< 1-BkgTestEff[i] << " " << hROCBkg->Integral(0, NumberOfBinsROC)<<" "<< BkgTestEff_err[i]<<endl;
for(int i = 1; i<NumberOfBinsROC; i++){
  wp.push_back(hROCSig->Integral(0, i));
  w2p.push_back(hROCSig_w2->Integral(0, i));
  wm.push_back(hROCSig->Integral(i, NumberOfBinsROC));
  w2m.push_back(hROCSig_w2->Integral(i, NumberOfBinsROC));
  w2.push_back((hROCSig->Integral(0, NumberOfBinsROC))*(hROCSig->Integral(0, NumberOfBinsROC)));
}
for(int i = 0; i<NumberOfBinsROC-1; i++){
  SigTestEff_err.push_back(sqrt(w2p[i]*wm[i]*wm[i]+w2m[i]*wp[i]*wp[i])/w2[i] ) ;
  // cout <<SigTestEff[i]<<" "<<w2p[i] <<" " <<wp[i] <<" "<<w2m[i] <<" " <<wm[i] <<" " << SigTestEff_err[i]<<" "<<endl;
    }

// TGraphErrors *grROC = new TGraphErrors(NumberOfBinsROC, &SigTestEff[0], &BkgTestRej[0], &SigTestEff_err[0], &BkgTestEff_err[0]);
// TGraphErrors *grROC = new TGraphErrors(NumberOfBinsROC, &SigTestEff[0], &BkgTestRej[0], 0, &BkgTestEff_err[0]);
TGraphErrors *grROC = new TGraphErrors(NumberOfBinsROC-1, &SigTestEff[0], &BkgTestEff[0], &SigTestEff_err[0], &BkgTestEff_err[0]);
// TGraphErrors *grROC = new TGraphErrors(NumberOfBinsROC, &SigTestEff[0], &BkgTestRej[0], 0, 0);


grROC->SetMarkerColor(ColorWheel[ColorIndex]);
grROC->SetLineColor(ColorWheel[ColorIndex]);
grROC->SetMarkerStyle(20);
grROC->SetMarkerSize(1);
grROC->SetLineWidth(1);
grROC->SetLineStyle(ColorIndex+1);
grROC->SetFillColorAlpha(ColorWheel[ColorIndex], 0.4);
// grROC->SetFillColor(ColorWheel[ColorIndex]);
grROC->SetFillStyle(1001);
grROC->GetYaxis()->SetTitle("Bkg. Efficiency [%]");
grROC->GetXaxis()->SetTitle("Sig. Efficiency [%]");


Double_t sig18 = grROC->Eval(0.18);
Double_t sig36 = grROC->Eval(0.36);
Double_t sig54 = grROC->Eval(0.54);
TString ROCtext1 = "Bkg. Rej. at 18% Sig.Eff: ";
ROCtext1.Append(Form("%.6g", sig18));
TString ROCtext2 = "Bkg. Rej. at 36% Sig.Eff:";
 ROCtext2.Append(Form(" %.6g", sig36));
TString ROCtext3 = "Bkg. Rej. at 54% Sig.Eff:";
ROCtext3.Append(Form(" %.6g", sig54));
// // TString newROCtext = "#splitline{a}{#splitline{b}{c}}";
// // TString newROCtext = "#splitline{" + ROCtext1 + "}{#splitline{" + ROCtext2 + "}{"+ROCtext3+"}}";
// cout<<ROCtext1<<endl;
// cout<<ROCtext2<<endl;
// cout<<ROCtext3<<endl;
// // TLatex *ROCtex1 = new TLatex(8.60565, 70,newROCtext);
// // ROCtex1->SetTextFont(62);
// // ROCtex1->SetTextSize(0.034468);
// // ROCtex1->SetLineWidth(2);
// // ROCtex1->Draw();
// // Double_t ymin = 0.9;
// // // Double_t ymax = 10.;
// // // Double_t ymax = 25.;
// // Double_t ymax = 0.95;
// // // Double_t xmin = 0.;
// // // Double_t xmax = 0.8;
// // grROC->GetYaxis()->SetRangeUser(ymin, ymax);
// // // grROC->GetXaxis()->SetRangeUser(xmin, xmax)

// c2->Update();
return grROC;
}