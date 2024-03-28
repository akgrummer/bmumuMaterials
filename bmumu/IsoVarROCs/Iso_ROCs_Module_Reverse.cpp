TGraph* Iso_ROCs(TTree* EvalTreeSig, TTree* EvalTreeBkg, 
                VariableInfo isoVarSig, TCut CutAddSig, 
                VariableInfo isoVarBkg, TCut CutAddBkg,
                Int_t ColorIndex){

/////////////ROC

TH1F *hROCSig(NULL);
TH1F *hROCBkg(NULL);

int NumberOfBinsROC = isoVarSig.nbins;
TString h1title = "IsolationHist";
hROCSig = getHistoFromTree(EvalTreeSig, isoVarSig, h1title, CutAddSig);
h1title += "_Bkg";
hROCBkg =getHistoFromTree(EvalTreeBkg, isoVarBkg, h1title, CutAddBkg);
hROCSig->Sumw2();
hROCBkg->Sumw2();


// hROCSig->Scale(1.0/hROCSig->Integral(1, NumberOfBinsROC-1));
// hROCBkg->Scale(1.0/hROCBkg->Integral(1, NumberOfBinsROC-1));
hROCSig->Scale(1.0/hROCSig->Integral(0, NumberOfBinsROC));
hROCBkg->Scale(1.0/hROCBkg->Integral(0, NumberOfBinsROC));
// TCanvas* c1 = new TCanvas("c1", "var comps",0.,0., 800, 600);
// hROCSig->Draw("al");
// hROCBkg->Draw("same l");
// TString OutdirName = "/afs/cern.ch/user/a/agrummer/www/bmumu/IsoVarROCs/";
// c1->SaveAs(OutdirName + "Figures/VarCompCheck.pdf");

//////////////////////////////////////////

vector<Double_t> SigTestEff;
vector<Double_t> BkgTestRej;
for(int i = 1; i<NumberOfBinsROC; i++){
  // cout<<i<<endl;
  SigTestEff.push_back((hROCSig->Integral(0, i))/(hROCSig->Integral(0, NumberOfBinsROC))*100);
  BkgTestRej.push_back((1-(hROCBkg->Integral(0, i))/(hROCBkg->Integral(0, NumberOfBinsROC)))*100);
}


TGraph *grROC = new TGraph(NumberOfBinsROC-1, &SigTestEff[0], &BkgTestRej[0]);


grROC->SetMarkerColor(ColorWheel[ColorIndex]);
grROC->SetLineColor(ColorWheel[ColorIndex]);
grROC->SetMarkerStyle(20);
grROC->SetMarkerSize(2);
grROC->SetLineWidth(2);
grROC->SetLineStyle(ColorIndex+1);
grROC->GetYaxis()->SetTitle("Bkg. Rejection [%]");
grROC->GetXaxis()->SetTitle("Sig. Efficiency [%]");


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
// TString newROCtext = "#splitline{" + ROCtext1 + "}{#splitline{" + ROCtext2 + "}{"+ROCtext3+"}}";
cout<<ROCtext1<<endl;
cout<<ROCtext2<<endl;
cout<<ROCtext3<<endl;
// TLatex *ROCtex1 = new TLatex(8.60565, 70,newROCtext);
// ROCtex1->SetTextFont(62);
// ROCtex1->SetTextSize(0.034468);
// ROCtex1->SetLineWidth(2);
// ROCtex1->Draw();


// c2->Update();
return grROC;
}