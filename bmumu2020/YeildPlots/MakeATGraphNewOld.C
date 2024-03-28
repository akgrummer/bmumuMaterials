//TFile* file = TFile::Open( "/Users/agrummer/Desktop/Bmumu/Output/Trees/LSFJOB_Trees500/bdt2016test_0.root" )
//file->cd("out/Method_BDT/BDT")
//TH1 *MVA_BDT_S = (TH1*) gROOT-> FindObject("MVA_BDT_S")
//TH1 *MVA_BDT_B = (TH1*) gROOT-> FindObject("MVA_BDT_B")
//TH1 *MVA_BDT_Train_S = (TH1*) gROOT-> FindObject("MVA_BDT_Train_S")
//TH1 *MVA_BDT_Train_B = (TH1*) gROOT-> FindObject("MVA_BDT_Train_B")
//Double_t kolS = MVA_BDT_S->KolmogorovTest( MVA_BDT_Train_S, "X" )
//Double_t kolB = MVA_BDT_B->KolmogorovTest( MVA_BDT_Train_B, "X" )
#include "/Users/agrummer/cernbox/www/bmumu2020/AtlasStyle/AtlasLabels.C"
#include "/Users/agrummer/cernbox/www/bmumu2020/AtlasStyle/AtlasLabels.h"
#include "/Users/agrummer/cernbox/www/bmumu2020/AtlasStyle/AtlasStyle.C"
#include "/Users/agrummer/cernbox/www/bmumu2020/AtlasStyle/AtlasStyle.h"
#include "/Users/agrummer/cernbox/www/bmumu2020/AtlasStyle/AtlasUtils.C"
#include "/Users/agrummer/cernbox/www/bmumu2020/AtlasStyle/AtlasUtils.h"

class MakeATGraph {
public:
    MakeATGraph( Double_t value = 0) {
//        kolS = value;
//        kolB = value;
    }
    void SetAtlasStyle ()
{
  static TStyle* atlasStyle = 0;
  std::cout << "\nApplying ATLAS style settings...\n" << std::endl ;
  if ( atlasStyle==0 ) atlasStyle = AtlasStyle();
  gROOT->SetStyle("ATLAS");
  gROOT->ForceStyle();
}

TStyle* AtlasStyle() 
{
  TStyle *atlasStyle = new TStyle("ATLAS","Atlas style");

  // use plain black on white colors
  Int_t icol=0; // WHITE
  atlasStyle->SetFrameBorderMode(icol);
  atlasStyle->SetFrameFillColor(icol);
  atlasStyle->SetCanvasBorderMode(icol);
  atlasStyle->SetCanvasColor(icol);
  atlasStyle->SetPadBorderMode(icol);
  atlasStyle->SetPadColor(icol);
  atlasStyle->SetStatColor(icol);
  //atlasStyle->SetFillColor(icol); // don't use: white fill color for *all* objects

  // set the paper & margin sizes
  atlasStyle->SetPaperSize(20,26);

  // set margin sizes
  atlasStyle->SetPadTopMargin(0.05);
  atlasStyle->SetPadRightMargin(0.12);
  atlasStyle->SetPadBottomMargin(0.16);
  atlasStyle->SetPadLeftMargin(0.16);
  //without residual plot:
  // atlasStyle->SetPadLeftMargin(0.16);

  // set title offsets (for axis label)
  atlasStyle->SetTitleXOffset(1.4);
  atlasStyle->SetTitleYOffset(1.4);

  // use large fonts
  //Int_t font=72; // Helvetica italics
  Int_t font=42; // Helvetica
  Double_t tsize=0.05;
  atlasStyle->SetTextFont(font);

  atlasStyle->SetTextSize(tsize);
  atlasStyle->SetLabelFont(font,"x");
  atlasStyle->SetTitleFont(font,"x");
  atlasStyle->SetLabelFont(font,"y");
  atlasStyle->SetTitleFont(font,"y");
  atlasStyle->SetLabelFont(font,"z");
  atlasStyle->SetTitleFont(font,"z");
  
  atlasStyle->SetLabelSize(tsize,"x");
  atlasStyle->SetTitleSize(tsize,"x");
  atlasStyle->SetLabelSize(tsize,"y");
  atlasStyle->SetTitleSize(tsize,"y");
  atlasStyle->SetLabelSize(tsize,"z");
  atlasStyle->SetTitleSize(tsize,"z");

  // use bold lines and markers
  atlasStyle->SetMarkerStyle(20);
  atlasStyle->SetMarkerSize(1.2);
  atlasStyle->SetHistLineWidth(2.);
  atlasStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

  // get rid of X error bars (as recommended in ATLAS figure guidelines)
  atlasStyle->SetErrorX(0.0001);
  // get rid of error bar caps
  atlasStyle->SetEndErrorSize(0.);

  // do not display any of the standard histogram decorations
  atlasStyle->SetOptTitle(0);
  //atlasStyle->SetOptStat(1111);
  atlasStyle->SetOptStat(0);
  //atlasStyle->SetOptFit(1111);
  atlasStyle->SetOptFit(0);

  // put tick marks on top and RHS of plots
  atlasStyle->SetPadTickX(1);
  atlasStyle->SetPadTickY(0);

  return atlasStyle;

}

    // called GainsCalc.py
    void MakeTheGraph( const Int_t cnt, Double_t* xvals, Double_t* yvals, Double_t *yvals2, Double_t* yError, Double_t *yvals3, Double_t* yvals2020) {
      // const Int_t cnt2 = 5;
      //there must be some type errors passing python arrays to root. I DON"T GET IT!
      // Double_t xvals2[18] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
      // Double_t yvals2[5] = {2.,3.,5.,6.,7.};
      // TString Periods[bins] = {"D", "E", "F", "G", "H", "J", "A", "B", "C", "D", "D", "E", "F", "G", "H", "I", "K", "L"};
      const Int_t bins = 16; //should be same as cnt...
      TString Periods[bins] = {"D", "E", "F", "G", "H", "J", "A", "B", "C", "D", "E", "F", "G", "I", "K", "L"};
      
      // TMultiGraph  *mg  = new TMultiGraph();
      // TMultiGraph  *mg2  = new TMultiGraph();
      TCanvas* c1 = new TCanvas("c1", "A TGraph",0.,0., 800, 600);
      TPad *pad1 = new TPad("pad1","",0,0.3,1,1);
      pad1->SetTitle("pad1");
      // pad1->SetMargin(0.16,0.12,0.038,0.06);//left, right, bottom, top
      // pad1->SetBorderMode(0);
      TPad *pad2 = new TPad("pad2","",0,0.3,1,1);
        pad2->SetFillStyle(4000);
        pad2->SetTitle("pad2");
        // Makes pad2
        // pad2->SetMargin(0.16,0.12,0.38,0.06);//left, right, bottom, top
        // pad2->SetBorderMode(0);
        pad2->SetFrameFillStyle(0);
      TPad *pad3 = new TPad("pad3","",0,0,1,0.3);
        pad3->SetTitle("pad3");
    pad1->SetMargin(0.16,0.12,0.05,0.05);//left, right, bottom, top
    pad2->SetMargin(0.16,0.12,0.05,0.05);//left, right, bottom, top
    pad3->SetMargin(0.16,0.12,0.4,0.09);//left, right, bottom, top
        pad1->Draw();
         pad2->Draw();
         pad3->Draw();

        //
      // TPad *pad3 = new TPad("pad3","",0,0,1,1);
      //   pad3->SetFillStyle(4000);
      //   pad3->SetTitle("");
      //   // Makes pad3
      //   pad3->SetFrameFillStyle(0);
        //

        // transparent.
        const Double_t * myZero(0);
      TGraphAsymmErrors* gr1 = new TGraphAsymmErrors(cnt, xvals, yvals, myZero, myZero, yError, yError);
        gr1->SetMarkerStyle(21);
        gr1->SetMarkerColor(kRed+2);
        gr1->SetFillColor(kRed+2);
        gr1->SetMarkerSize(0.8);
        gr1->SetLineColor(kRed+2);
        gr1->SetLineWidth(2);
      TGraphAsymmErrors* gr3;
      gr3 = new TGraphAsymmErrors(cnt, xvals, yvals2020, myZero, myZero, yError, yError);
        gr3->SetMarkerStyle(23);
        gr3->SetMarkerColor(kGreen+2);
        gr3->SetFillColor(kGreen+2);
        gr3->SetMarkerSize(0.8);
        gr3->SetLineColor(kGreen+2);
        gr3->SetLineWidth(2);
      TGraphAsymmErrors* gr2 = new TGraphAsymmErrors(cnt, xvals, yvals2);
        gr2->SetMarkerStyle(21);
        gr2->SetMarkerColor(kBlue+2);
        // gr2->SetFillColor(kBlue+2);
        gr2->SetFillColorAlpha(kBlue+2, 0.35);
        gr2->SetMarkerSize(0.5);
        gr2->SetLineColor(kBlue+2);
        gr2->SetLineWidth(2);



        auto nPoints = gr2->GetN(); // number of points in your TGraph
       TH1D* h = new TH1D("h", "h title", nPoints, 0, nPoints-1);
        // TH1 *h; // the histogram (you should set the number of bins, the title etc)
        double x,y, yerr;
        for(int i=0; i < nPoints; ++i) {
            gr2->GetPoint(i, x, y);
            cout<<y<<endl;
            // h->Fill(y,1); // ?
            h->SetBinContent(i+1,y); // ?
        }
        h->SetMarkerStyle(21);
        h->SetMarkerColor(kBlue+2);
        // h->SetFillColor(kBlue+2);
        // h->SetFillColorAlpha(kBlue+2, 0.35);
        h->SetMarkerSize(0.5);
        h->SetLineColor(kBlue+2);
        h->SetLineWidth(2);

       auto nPoints1 = gr1->GetN(); // number of points in your TGraph
       TH1D* h1 = new TH1D("h1", "h1 title", nPoints1, 0, nPoints1-1);
        // TH1 *h; // the histogram (you should set the number of bins, the title etc)
        for(int i=0; i < nPoints1; ++i) {
            // double x,y;
            gr1->GetPoint(i, x, y);
            yerr = gr1->GetErrorYhigh(i);
            // cout<<y<<endl;
            // h->Fill(y,1); // ?
            h1->SetBinContent(i+1,y); // ?
            h1->SetBinError(i+1,yerr); // ?
        }
       auto nPoints3 = gr3->GetN(); // number of points in your TGraph
       TH1D* h3 = new TH1D("h2", "h2 title", nPoints3, 0, nPoints3-1);
        // TH1 *h; // the histogram (you should set the number of bins, the title etc)
        for(int i=0; i < nPoints3; ++i) {
            // double x,y;
            gr3->GetPoint(i, x, y);
            yerr = gr3->GetErrorYhigh(i);
            // cout<<y<<endl;
            // h->Fill(y,1); // ?
            h3->SetBinContent(i+1,y);
            h3->SetBinError(i+1,yerr); 
        }
        h1->Sumw2();
        h3->Sumw2();
        TH1D* hres = (TH1D*)h1->Clone("hres");
        hres->Sumw2();
        hres->Divide(h3,h1,1.0,1.0);
        hres->SetMarkerSize(0.7);
        hres->SetLineStyle(1);
        hres->GetYaxis()->SetRangeUser(0.95, 1.05);
        hres->GetXaxis()->SetTitleOffset(1.0); //0.95
        hres->GetXaxis()->SetTitleSize(0.17);
        hres->GetXaxis()->SetLabelSize(0.14); //0.17 0.1
        hres->GetXaxis()->SetTitle("Data Period");
        hres->GetYaxis()->SetTitle("New/Old");
        hres->GetYaxis()->SetTitleSize(0.12);
        hres->GetYaxis()->SetTitleOffset(0.47); //0.26
        hres->GetYaxis()->SetLabelSize(0.1);//0.17 //0.08
        hres->GetYaxis()->SetNdivisions(4,3,0); //4,5,0
        hres->GetXaxis()->Set(bins, 0.5, bins+0.5);
        hres->GetYaxis()->SetTickLength(0.02);
        hres->GetXaxis()->SetTickLength(0.04);
        hres->GetXaxis()->SetLabelOffset(0.03);
        for(int i = 0; i < bins; i++){
            hres->GetXaxis()->SetBinLabel(i+1,Periods[i]);
          }
        //
      // TGraphAsymmErrors* gr3 = new TGraphAsymmErrors(cnt, xvals, yvals3);
      //   gr3->SetMarkerStyle(21);
      //   gr3->SetMarkerColor(kBlue);
      //   gr3->SetFillColor(kBlue);
      //   gr3->SetMarkerSize(0.5);
      //   gr3->SetLineColor(kGreen +2);
      //   gr3->SetLineWidth(2);
        //

        // pad1->Draw();
        // gPad->Update();
        pad1->cd();
        // gr2->Draw("ABY+");
        h->Draw("histY+");
        // mg->Add(gr2, "L");
        // mg->Draw("ALP");
        // gr2->GetXaxis()->Set(bins, 0.5, bins+0.5);
        // for(int i = 0; i < bins; i++){
        //     gr2->GetXaxis()->SetBinLabel(i+1,Periods[i]);
        //   }
        // // gr2->GetYaxis()->SetRangeUser(0.,0.05);
        // gr2->GetYaxis()->SetTitle("Integrated Luminosity [fb^{-1}]");
        // gr2->GetYaxis()->SetTitleOffset(1.);
        // gr2->GetYaxis()->SetRangeUser(0.,30.);
        // gr2->GetYaxis()->SetAxisColor(kBlue+2);
        // gr2->GetYaxis()->SetLabelColor(kBlue+2);
        // gr2->GetYaxis()->SetTitleColor(kBlue+2);

        h->GetXaxis()->Set(bins, 0.5, bins+0.5);
        for(int i = 0; i < bins; i++){
            h->GetXaxis()->SetBinLabel(i+1,Periods[i]);
          }
        // h->GetYaxis()->SetRangeUser(0.,0.05);
        h->GetYaxis()->SetTitle("Integrated Luminosity [fb^{-1}]");
        h->GetYaxis()->SetTitleOffset(1.);
        h->GetYaxis()->SetRangeUser(0.,30.);
        h->GetYaxis()->SetAxisColor(kBlue+2);
        h->GetYaxis()->SetLabelColor(kBlue+2);
        h->GetYaxis()->SetTitleColor(kBlue+2);
        h->GetXaxis()->SetLabelSize(0);


        //
        // pad3->Draw();
        // gPad->Update();
        // pad3->cd();
        // gr3->Draw("ALY+");
        // // mg->Add(gr2, "L");
        // // mg->Draw("ALP");
        // gr3->GetXaxis()->Set(bins, 0.5, bins+0.5);
        // for(int i = 0; i < bins; i++){
        //     gr3->GetXaxis()->SetBinLabel(i+1,Periods[i]);
        //   }
        // gr3->GetYaxis()->SetRangeUser(0.,40.);
        //


        // pad2->Draw();
        // pad2->SetPadRightMargin(0.16);
        pad2->cd();
        gr1->Draw("aepz");
        // gr3->Draw("aepz");
        gr3->Draw("same epz");
        // mg2->Add(gr1, "P");
        // mg2->Draw("ALP");

        gr1->GetXaxis()->Set(bins, 0.5, bins+0.5);
        for(int i = 0; i < bins; i++){
               gr1->GetXaxis()->SetBinLabel(i+1,Periods[i]);
             }
        gr3->GetXaxis()->Set(bins, 0.5, bins+0.5);
        for(int i = 0; i < bins; i++){
               gr3->GetXaxis()->SetBinLabel(i+1,Periods[i]);
             }
        // Double_t yHeight = 0.04;
        // Double_t yHeight = 200*1000;
        Double_t yHeight = 200;
        // gr1->GetYaxis()->SetRangeUser(0.,yHeight);
        Double_t Ymin = 60.;
        Double_t Ymax = 140.;
        // Double_t Ymin = 60000.;
        // Double_t Ymax = 140000.;
        // Double_t Ymin = 0.;
        // Double_t Ymax = 200000.;

        //for events error only:
        // Double_t Ymin = 80000.;
        // Double_t Ymax = 110000.;

        gr1->GetYaxis()->SetRangeUser(Ymin,Ymax);
        // gr1->GetXaxis()->SetRangeUser(0.,bins+1);
        // gr1->GetXaxis()->SetRangeUser(-1, 120);
        gr1->GetYaxis()->SetTitle("Candidates/fb^{-1} [#times 10^{3}]");
        gr1->GetXaxis()->SetLabelSize(0);
        // gr1->GetXaxis()->SetTitle("Data Period");

        gr3->GetYaxis()->SetRangeUser(Ymin,Ymax);
        gr3->GetYaxis()->SetTitle("Candidates/fb^{-1} [#times 10^{3}]");
        gr3->GetXaxis()->SetLabelSize(0);
        // gr3->GetXaxis()->SetTitle("Data Period");

        // TLine *line = new TLine(6.5,0,6.5,yHeight);
        TLine *line = new TLine(6.5,Ymin,6.5,Ymax);
        line->SetLineColorAlpha(kBlack, 0.4);
        line->Draw();

//95 reference line
        // TLine *lineHoriz = new TLine(0.5,95.*1000,bins+0.5,95.*1000);
        // lineHoriz->SetLineColorAlpha(kRed, 0.4);
        // lineHoriz->SetLineStyle(2);
        // lineHoriz->Draw();

        // TLine *line5 = new TLine(10.5,0., 10.5, yHeight);
        // line5->SetLineColorAlpha(kBlack, 0.4);
        // line5->Draw();
            // TLatex *tex3 = new TLatex(4.46049, 0.225*yHeight,"2015");
            TLatex *tex3 = new TLatex(4.46049, 0.52*yHeight,"2015");
            tex3->SetTextFont(62);
            tex3->SetTextSize(0.038);
            tex3->SetLineWidth(2);
            tex3->Draw();            
            // TLatex *tex4 = new TLatex(7.10474, 0.52*yHeight,"2016 Main");
            // tex4->SetTextFont(62);
            // tex4->SetTextSize(0.038);
            // tex4->SetLineWidth(2);
            // tex4->Draw();            
            // TLatex *tex5 = new TLatex(7.23212, 0.225*yHeight,"2016");
            TLatex *tex5 = new TLatex(7.23212, 0.52*yHeight,"2016");
            tex5->SetTextFont(62);
            tex5->SetTextSize(0.038);
            tex5->SetLineWidth(2);
            tex5->Draw();
        TLegend* leg;
        // leg = new TLegend(1, 0.06, 5, 0.08,NULL,"brNDC");
        // leg = new TLegend(0.219298, 0.796522, 0.409774, 0.909565,NULL,"brNDC");
        // leg = new TLegend(0.224, 0.774, 0.415, 0.864,NULL,"brNDC");
        leg = new TLegend(0.224, 0.75, 0.415, 0.864,NULL,"brNDC");
        
        leg->SetBorderSize(0);  // no border
        leg->SetLineColor(0);
        leg->SetFillColor(0);
        leg->SetTextSize(0.038);



        // leg->AddEntry(gr1, "Yield Old nTuples","epl");
        // leg->AddEntry(gr3, "Yield 2020 nTuples","epl");
        leg->AddEntry(gr3, "Sideband Data (New nTuples)","epl");
        leg->AddEntry(gr1, "Sideband Data (Old nTuples)","epl");
        // leg->AddEntry(lineHoriz, "Reference Gain = 95","l");
        TString LumiLeg = Form("Int. Luminosity (Total = %.1f fb^{-1})", yvals2[cnt-1]);
        leg->AddEntry(gr2, LumiLeg,"l");
        leg->Draw();
        ATLASLabel(0.255639, 0.876522,"Internal",1);

        pad3->cd();
        hres->Draw("pe");
        TLine *myLine  = new TLine(0.5, 1., 16.5, 1.);
        // myLine  = new TLine(pad2->GetUxmin(), 1., pad2->GetUxmax(), 1.);
        myLine->SetLineStyle(1);
        myLine->SetLineWidth(1);
        myLine->SetLineColorAlpha(600+1, 0.5);
        myLine->Draw();

        c1->Update();
        // c1->SaveAs("./GainPlot.eps");
        // c1->SaveAs("./GainPlot.pdf");
        c1->SaveAs("./GainPlotwithOldnTuples.pdf");
    }
    
    Double_t GetValue_S() {
//        file->cd("out/Method_BDT/BDT");
//        TH1 *MVA_BDT_S = (TH1*) gROOT-> FindObject("MVA_BDT_S");
//        TH1 *MVA_BDT_Train_S = (TH1*) gROOT-> FindObject("MVA_BDT_Train_S");
//        Double_t kolS = MVA_BDT_S->KolmogorovTest( MVA_BDT_Train_S, "X" );
        return kolS;
    }
    
    Double_t GetValue_B() {
//        file->cd("out/Method_BDT/BDT");
//        TH1 *MVA_BDT_B = (TH1*) gROOT-> FindObject("MVA_BDT_B");
//        TH1 *MVA_BDT_Train_B = (TH1*) gROOT-> FindObject("MVA_BDT_Train_B");
//        Double_t kolB = MVA_BDT_B->KolmogorovTest( MVA_BDT_Train_B, "X" );
        return kolB;
    }
    
private:
    Double_t kolS;
    Double_t kolB;
};
