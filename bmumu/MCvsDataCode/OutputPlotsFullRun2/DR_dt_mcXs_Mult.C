void DR_dt_mcXs_Mult()
{
//=========Macro generated from canvas: c1/c1
//=========  (Thu Apr 11 07:34:44 2019) by ROOT version6.10/06
   TCanvas *c1 = new TCanvas("c1", "c1",1,1,800,576);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetTickx(1);
   c1->SetTicky(1);
   c1->SetLeftMargin(0.13);
   c1->SetTopMargin(0.07);
   c1->SetBottomMargin(0.12);
   c1->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: pad1
   TPad *pad1 = new TPad("pad1", "pad1",0,0,1,1);
   pad1->Draw();
   pad1->cd();
   pad1->Range(-0.3037975,-4.491722,1.594937,0.7035039);
   pad1->SetFillColor(0);
   pad1->SetBorderMode(0);
   pad1->SetBorderSize(2);
   pad1->SetLogy();
   pad1->SetTickx(1);
   pad1->SetTicky(1);
   pad1->SetLeftMargin(0.16);
   pad1->SetRightMargin(0.05);
   pad1->SetBottomMargin(0.16);
   pad1->SetFrameBorderMode(0);
   pad1->SetFrameBorderMode(0);
   
   TH1F *DR_Data_SigMC__4 = new TH1F("DR_Data_SigMC__4","DR_Data_SigMC",30,0,1.5);
   DR_Data_SigMC__4->SetBinContent(1,0.6905594);
   DR_Data_SigMC__4->SetBinContent(2,0.1778846);
   DR_Data_SigMC__4->SetBinContent(3,0.0673077);
   DR_Data_SigMC__4->SetBinContent(4,0.01879371);
   DR_Data_SigMC__4->SetBinContent(5,0.01748252);
   DR_Data_SigMC__4->SetBinContent(6,0.006993007);
   DR_Data_SigMC__4->SetBinContent(7,0.003059441);
   DR_Data_SigMC__4->SetBinContent(8,0.003933567);
   DR_Data_SigMC__4->SetBinContent(9,0.001748252);
   DR_Data_SigMC__4->SetBinContent(10,0.002622378);
   DR_Data_SigMC__4->SetBinContent(11,0.0004370629);
   DR_Data_SigMC__4->SetBinContent(12,0.001311189);
   DR_Data_SigMC__4->SetBinContent(13,0.001311189);
   DR_Data_SigMC__4->SetBinContent(15,0.0004370629);
   DR_Data_SigMC__4->SetBinContent(16,0.001311189);
   DR_Data_SigMC__4->SetBinContent(17,0.0004370629);
   DR_Data_SigMC__4->SetBinContent(19,0.0008741259);
   DR_Data_SigMC__4->SetBinContent(20,0.0008741259);
   DR_Data_SigMC__4->SetBinContent(22,0.0008741259);
   DR_Data_SigMC__4->SetBinContent(25,0.0008741259);
   DR_Data_SigMC__4->SetBinContent(27,0.0004370629);
   DR_Data_SigMC__4->SetBinContent(30,0.0004370629);
   DR_Data_SigMC__4->SetBinError(1,0.01737291);
   DR_Data_SigMC__4->SetBinError(2,0.008817413);
   DR_Data_SigMC__4->SetBinError(3,0.005423808);
   DR_Data_SigMC__4->SetBinError(4,0.002866013);
   DR_Data_SigMC__4->SetBinError(5,0.002764229);
   DR_Data_SigMC__4->SetBinError(6,0.001748252);
   DR_Data_SigMC__4->SetBinError(7,0.00115636);
   DR_Data_SigMC__4->SetBinError(8,0.001311189);
   DR_Data_SigMC__4->SetBinError(9,0.0008741259);
   DR_Data_SigMC__4->SetBinError(10,0.001070581);
   DR_Data_SigMC__4->SetBinError(11,0.0004370629);
   DR_Data_SigMC__4->SetBinError(12,0.0007570152);
   DR_Data_SigMC__4->SetBinError(13,0.0007570152);
   DR_Data_SigMC__4->SetBinError(15,0.0004370629);
   DR_Data_SigMC__4->SetBinError(16,0.0007570152);
   DR_Data_SigMC__4->SetBinError(17,0.0004370629);
   DR_Data_SigMC__4->SetBinError(19,0.0006181003);
   DR_Data_SigMC__4->SetBinError(20,0.0006181003);
   DR_Data_SigMC__4->SetBinError(22,0.0006181003);
   DR_Data_SigMC__4->SetBinError(25,0.0006181003);
   DR_Data_SigMC__4->SetBinError(27,0.0004370629);
   DR_Data_SigMC__4->SetBinError(30,0.0004370629);
   DR_Data_SigMC__4->SetMaximum(1.721605);
   DR_Data_SigMC__4->SetEntries(2288);
   DR_Data_SigMC__4->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   DR_Data_SigMC__4->SetFillColor(ci);
   DR_Data_SigMC__4->SetFillStyle(3007);

   ci = TColor::GetColor("#ff0000");
   DR_Data_SigMC__4->SetLineColor(ci);
   DR_Data_SigMC__4->SetLineWidth(2);

   ci = TColor::GetColor("#ff0000");
   DR_Data_SigMC__4->SetMarkerColor(ci);
   DR_Data_SigMC__4->SetMarkerStyle(25);
   DR_Data_SigMC__4->SetMarkerSize(0);
   DR_Data_SigMC__4->GetXaxis()->SetTitle("#DeltaR");
   DR_Data_SigMC__4->GetXaxis()->SetNoExponent();
   DR_Data_SigMC__4->GetXaxis()->SetLabelFont(42);
   DR_Data_SigMC__4->GetXaxis()->SetLabelOffset(0.028);
   DR_Data_SigMC__4->GetXaxis()->SetLabelSize(0.05);
   DR_Data_SigMC__4->GetXaxis()->SetTitleSize(0.05);
   DR_Data_SigMC__4->GetXaxis()->SetTitleOffset(1.4);
   DR_Data_SigMC__4->GetXaxis()->SetTitleFont(42);
   DR_Data_SigMC__4->GetYaxis()->SetTitle("1/N dn/d#DeltaR");
   DR_Data_SigMC__4->GetYaxis()->SetLabelFont(42);
   DR_Data_SigMC__4->GetYaxis()->SetLabelSize(0.05);
   DR_Data_SigMC__4->GetYaxis()->SetTitleSize(0.05);
   DR_Data_SigMC__4->GetYaxis()->SetTitleOffset(1.3);
   DR_Data_SigMC__4->GetYaxis()->SetTitleFont(42);
   DR_Data_SigMC__4->GetZaxis()->SetLabelFont(42);
   DR_Data_SigMC__4->GetZaxis()->SetLabelSize(0.05);
   DR_Data_SigMC__4->GetZaxis()->SetTitleSize(0.05);
   DR_Data_SigMC__4->GetZaxis()->SetTitleFont(42);
   DR_Data_SigMC__4->Draw("hist");
   
   TH1F *dataSR__5 = new TH1F("dataSR__5","dataSR",30,0,1.5);
   dataSR__5->SetBinContent(1,0.02603607);
   dataSR__5->SetBinContent(2,0.05852144);
   dataSR__5->SetBinContent(3,0.08754329);
   dataSR__5->SetBinContent(4,0.09841156);
   dataSR__5->SetBinContent(5,0.1103547);
   dataSR__5->SetBinContent(6,0.1147737);
   dataSR__5->SetBinContent(7,0.09602293);
   dataSR__5->SetBinContent(8,0.09160396);
   dataSR__5->SetBinContent(9,0.07273379);
   dataSR__5->SetBinContent(10,0.06234325);
   dataSR__5->SetBinContent(11,0.04753374);
   dataSR__5->SetBinContent(12,0.03762092);
   dataSR__5->SetBinContent(13,0.02866356);
   dataSR__5->SetBinContent(14,0.02042279);
   dataSR__5->SetBinContent(15,0.01528723);
   dataSR__5->SetBinContent(16,0.009435089);
   dataSR__5->SetBinContent(17,0.005971575);
   dataSR__5->SetBinContent(18,0.00477726);
   dataSR__5->SetBinContent(19,0.003821808);
   dataSR__5->SetBinContent(20,0.002985788);
   dataSR__5->SetBinContent(21,0.001313747);
   dataSR__5->SetBinContent(22,0.001194315);
   dataSR__5->SetBinContent(23,0.000477726);
   dataSR__5->SetBinContent(24,0.0008360206);
   dataSR__5->SetBinContent(25,0.0003582945);
   dataSR__5->SetBinContent(27,0.0003582945);
   dataSR__5->SetBinContent(28,0.0001194315);
   dataSR__5->SetBinContent(29,0.0003582945);
   dataSR__5->SetBinContent(30,0.0001194315);
   dataSR__5->SetBinError(1,0.001763385);
   dataSR__5->SetBinError(2,0.002643729);
   dataSR__5->SetBinError(3,0.003233485);
   dataSR__5->SetBinError(4,0.003428329);
   dataSR__5->SetBinError(5,0.003630403);
   dataSR__5->SetBinError(6,0.003702377);
   dataSR__5->SetBinError(7,0.003386468);
   dataSR__5->SetBinError(8,0.003307627);
   dataSR__5->SetBinError(9,0.002947322);
   dataSR__5->SetBinError(10,0.00272869);
   dataSR__5->SetBinError(11,0.002382651);
   dataSR__5->SetBinError(12,0.002119699);
   dataSR__5->SetBinError(13,0.001850225);
   dataSR__5->SetBinError(14,0.00156177);
   dataSR__5->SetBinError(15,0.001351213);
   dataSR__5->SetBinError(16,0.00106153);
   dataSR__5->SetBinError(17,0.0008445083);
   dataSR__5->SetBinError(18,0.0007553512);
   dataSR__5->SetBinError(19,0.0006756066);
   dataSR__5->SetBinError(20,0.0005971575);
   dataSR__5->SetBinError(21,0.0003961095);
   dataSR__5->SetBinError(22,0.0003776756);
   dataSR__5->SetBinError(23,0.000238863);
   dataSR__5->SetBinError(24,0.0003159861);
   dataSR__5->SetBinError(25,0.0002068614);
   dataSR__5->SetBinError(27,0.0002068614);
   dataSR__5->SetBinError(28,0.0001194315);
   dataSR__5->SetBinError(29,0.0002068614);
   dataSR__5->SetBinError(30,0.0001194315);
   dataSR__5->SetMaximum(1.721605);
   dataSR__5->SetEntries(8373);
   dataSR__5->SetStats(0);

   ci = TColor::GetColor("#00cc00");
   dataSR__5->SetLineColor(ci);

   ci = TColor::GetColor("#00cc00");
   dataSR__5->SetMarkerColor(ci);
   dataSR__5->SetMarkerStyle(20);
   dataSR__5->SetMarkerSize(0.9);
   dataSR__5->GetXaxis()->SetTitle("#DeltaR");
   dataSR__5->GetXaxis()->SetRange(1,30);
   dataSR__5->GetXaxis()->SetNoExponent();
   dataSR__5->GetXaxis()->SetLabelFont(42);
   dataSR__5->GetXaxis()->SetLabelOffset(0.028);
   dataSR__5->GetXaxis()->SetLabelSize(0.05);
   dataSR__5->GetXaxis()->SetTitleSize(0.05);
   dataSR__5->GetXaxis()->SetTitleOffset(1.4);
   dataSR__5->GetXaxis()->SetTitleFont(42);
   dataSR__5->GetYaxis()->SetTitle("1/N dn/d#DeltaR");
   dataSR__5->GetYaxis()->SetLabelFont(42);
   dataSR__5->GetYaxis()->SetLabelSize(0.05);
   dataSR__5->GetYaxis()->SetTitleSize(0.05);
   dataSR__5->GetYaxis()->SetTitleOffset(1.3);
   dataSR__5->GetYaxis()->SetTitleFont(42);
   dataSR__5->GetZaxis()->SetLabelFont(42);
   dataSR__5->GetZaxis()->SetLabelSize(0.05);
   dataSR__5->GetZaxis()->SetTitleSize(0.05);
   dataSR__5->GetZaxis()->SetTitleFont(42);
   dataSR__5->Draw("e0psame");
   
   TH1F *DR_Data_T_mv_1__6 = new TH1F("DR_Data_T_mv_1__6","DR_Data_T_mv_1",30,0,1.5);
   DR_Data_T_mv_1__6->SetBinContent(1,0.02261666);
   DR_Data_T_mv_1__6->SetBinContent(2,0.0632694);
   DR_Data_T_mv_1__6->SetBinContent(3,0.08860578);
   DR_Data_T_mv_1__6->SetBinContent(4,0.1014887);
   DR_Data_T_mv_1__6->SetBinContent(5,0.1105067);
   DR_Data_T_mv_1__6->SetBinContent(6,0.1125107);
   DR_Data_T_mv_1__6->SetBinContent(7,0.1012024);
   DR_Data_T_mv_1__6->SetBinContent(8,0.09132551);
   DR_Data_T_mv_1__6->SetBinContent(9,0.07443459);
   DR_Data_T_mv_1__6->SetBinContent(10,0.06155168);
   DR_Data_T_mv_1__6->SetBinContent(11,0.04738048);
   DR_Data_T_mv_1__6->SetBinContent(12,0.03406814);
   DR_Data_T_mv_1__6->SetBinContent(13,0.02347552);
   DR_Data_T_mv_1__6->SetBinContent(14,0.02018322);
   DR_Data_T_mv_1__6->SetBinContent(15,0.0131692);
   DR_Data_T_mv_1__6->SetBinContent(16,0.008445462);
   DR_Data_T_mv_1__6->SetBinContent(17,0.006584598);
   DR_Data_T_mv_1__6->SetBinContent(18,0.004437446);
   DR_Data_T_mv_1__6->SetBinContent(19,0.003721729);
   DR_Data_T_mv_1__6->SetBinContent(20,0.003292299);
   DR_Data_T_mv_1__6->SetBinContent(21,0.001860865);
   DR_Data_T_mv_1__6->SetBinContent(22,0.001288291);
   DR_Data_T_mv_1__6->SetBinContent(23,0.0005725737);
   DR_Data_T_mv_1__6->SetBinContent(24,0.0007157171);
   DR_Data_T_mv_1__6->SetBinContent(25,0.001002004);
   DR_Data_T_mv_1__6->SetBinContent(26,0.0005725737);
   DR_Data_T_mv_1__6->SetBinContent(27,0.0005725737);
   DR_Data_T_mv_1__6->SetBinContent(28,0.0004294303);
   DR_Data_T_mv_1__6->SetBinContent(29,0.0001431434);
   DR_Data_T_mv_1__6->SetBinContent(30,0.0005725737);
   DR_Data_T_mv_1__6->SetBinError(1,0.001799285);
   DR_Data_T_mv_1__6->SetBinError(2,0.003009418);
   DR_Data_T_mv_1__6->SetBinError(3,0.003561367);
   DR_Data_T_mv_1__6->SetBinError(4,0.003811488);
   DR_Data_T_mv_1__6->SetBinError(5,0.003977224);
   DR_Data_T_mv_1__6->SetBinError(6,0.004013125);
   DR_Data_T_mv_1__6->SetBinError(7,0.003806108);
   DR_Data_T_mv_1__6->SetBinError(8,0.003615612);
   DR_Data_T_mv_1__6->SetBinError(9,0.003264172);
   DR_Data_T_mv_1__6->SetBinError(10,0.002968285);
   DR_Data_T_mv_1__6->SetBinError(11,0.002604266);
   DR_Data_T_mv_1__6->SetBinError(12,0.002208309);
   DR_Data_T_mv_1__6->SetBinError(13,0.00183313);
   DR_Data_T_mv_1__6->SetBinError(14,0.001699734);
   DR_Data_T_mv_1__6->SetBinError(15,0.001372984);
   DR_Data_T_mv_1__6->SetBinError(16,0.001099506);
   DR_Data_T_mv_1__6->SetBinError(17,0.000970846);
   DR_Data_T_mv_1__6->SetBinError(18,0.0007969889);
   DR_Data_T_mv_1__6->SetBinError(19,0.0007298911);
   DR_Data_T_mv_1__6->SetBinError(20,0.0006864918);
   DR_Data_T_mv_1__6->SetBinError(21,0.000516111);
   DR_Data_T_mv_1__6->SetBinError(22,0.0004294303);
   DR_Data_T_mv_1__6->SetBinError(23,0.0002862869);
   DR_Data_T_mv_1__6->SetBinError(24,0.0003200784);
   DR_Data_T_mv_1__6->SetBinError(25,0.0003787219);
   DR_Data_T_mv_1__6->SetBinError(26,0.0002862869);
   DR_Data_T_mv_1__6->SetBinError(27,0.0002862869);
   DR_Data_T_mv_1__6->SetBinError(28,0.0002479317);
   DR_Data_T_mv_1__6->SetBinError(29,0.0001431434);
   DR_Data_T_mv_1__6->SetBinError(30,0.0002862869);
   DR_Data_T_mv_1__6->SetEntries(6986);
   DR_Data_T_mv_1__6->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   DR_Data_T_mv_1__6->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   DR_Data_T_mv_1__6->SetMarkerColor(ci);
   DR_Data_T_mv_1__6->SetMarkerStyle(20);
   DR_Data_T_mv_1__6->SetMarkerSize(0.9);
   DR_Data_T_mv_1__6->GetXaxis()->SetTitle("#DeltaR");
   DR_Data_T_mv_1__6->GetXaxis()->SetLabelFont(42);
   DR_Data_T_mv_1__6->GetXaxis()->SetLabelSize(0.05);
   DR_Data_T_mv_1__6->GetXaxis()->SetTitleSize(0.05);
   DR_Data_T_mv_1__6->GetXaxis()->SetTitleOffset(1.4);
   DR_Data_T_mv_1__6->GetXaxis()->SetTitleFont(42);
   DR_Data_T_mv_1__6->GetYaxis()->SetLabelFont(42);
   DR_Data_T_mv_1__6->GetYaxis()->SetLabelSize(0.05);
   DR_Data_T_mv_1__6->GetYaxis()->SetTitleSize(0.05);
   DR_Data_T_mv_1__6->GetYaxis()->SetTitleOffset(1.4);
   DR_Data_T_mv_1__6->GetYaxis()->SetTitleFont(42);
   DR_Data_T_mv_1__6->GetZaxis()->SetLabelFont(42);
   DR_Data_T_mv_1__6->GetZaxis()->SetLabelSize(0.05);
   DR_Data_T_mv_1__6->GetZaxis()->SetTitleSize(0.05);
   DR_Data_T_mv_1__6->GetZaxis()->SetTitleFont(42);
   DR_Data_T_mv_1__6->Draw("e0psame");
   TLatex *   tex = new TLatex(0.55,0.67,"ATLAS");
tex->SetNDC();
   tex->SetTextFont(72);
   tex->SetTextSize(0.055);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.6931138,0.67,"Internal");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.055);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.56,0.605,"#sqrt{s} = 13 TeV, 26.3 fb^{-1}");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.055);
   tex->SetLineWidth(2);
   tex->Draw();
   
   TLegend *leg = new TLegend(0.526316,0.750871,0.85213,0.869338,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.045);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("dataSR","2017","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#00cc00");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(0.9);
   entry->SetTextFont(42);
   entry=leg->AddEntry("DR_Data_T_mv_1","2018","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ff0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(0.9);
   entry->SetTextFont(42);
   entry=leg->AddEntry("DR_Data_SigMC","MC16a","fl");

   ci = TColor::GetColor("#ff0000");
   entry->SetFillColor(ci);
   entry->SetFillStyle(3007);

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   pad1->Modified();
   c1->cd();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
