void Lxy_dt_mcXs()
{
//=========Macro generated from canvas: c1/c1
//=========  (Fri Sep 28 15:28:07 2018) by ROOT version6.10/04
   TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,600);
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
   pad1->Range(-0.7088607,-2.890012,3.721519,-0.09720621);
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
   
   TH1F *Lxy_dt16_SigMC__1 = new TH1F("Lxy_dt16_SigMC__1","Lxy_dt16_SigMC",35,0,3.5);
   Lxy_dt16_SigMC__1->SetBinContent(4,0.07127003);
   Lxy_dt16_SigMC__1->SetBinContent(5,0.06687914);
   Lxy_dt16_SigMC__1->SetBinContent(6,0.06137274);
   Lxy_dt16_SigMC__1->SetBinContent(7,0.05641464);
   Lxy_dt16_SigMC__1->SetBinContent(8,0.05270045);
   Lxy_dt16_SigMC__1->SetBinContent(9,0.04700361);
   Lxy_dt16_SigMC__1->SetBinContent(10,0.04402835);
   Lxy_dt16_SigMC__1->SetBinContent(11,0.04041632);
   Lxy_dt16_SigMC__1->SetBinContent(12,0.03831596);
   Lxy_dt16_SigMC__1->SetBinContent(13,0.03473065);
   Lxy_dt16_SigMC__1->SetBinContent(14,0.03139694);
   Lxy_dt16_SigMC__1->SetBinContent(15,0.03054683);
   Lxy_dt16_SigMC__1->SetBinContent(16,0.02801287);
   Lxy_dt16_SigMC__1->SetBinContent(17,0.02582413);
   Lxy_dt16_SigMC__1->SetBinContent(18,0.02353839);
   Lxy_dt16_SigMC__1->SetBinContent(19,0.02166099);
   Lxy_dt16_SigMC__1->SetBinContent(20,0.01970812);
   Lxy_dt16_SigMC__1->SetBinContent(21,0.01877734);
   Lxy_dt16_SigMC__1->SetBinContent(22,0.01800563);
   Lxy_dt16_SigMC__1->SetBinContent(23,0.01593847);
   Lxy_dt16_SigMC__1->SetBinContent(24,0.01523322);
   Lxy_dt16_SigMC__1->SetBinContent(25,0.01430715);
   Lxy_dt16_SigMC__1->SetBinContent(26,0.01264886);
   Lxy_dt16_SigMC__1->SetBinContent(27,0.0121678);
   Lxy_dt16_SigMC__1->SetBinContent(28,0.0118409);
   Lxy_dt16_SigMC__1->SetBinContent(29,0.01102156);
   Lxy_dt16_SigMC__1->SetBinContent(30,0.01016704);
   Lxy_dt16_SigMC__1->SetBinContent(31,0.009385576);
   Lxy_dt16_SigMC__1->SetBinContent(32,0.008903665);
   Lxy_dt16_SigMC__1->SetBinContent(33,0.008664158);
   Lxy_dt16_SigMC__1->SetBinContent(34,0.007485983);
   Lxy_dt16_SigMC__1->SetBinContent(35,0.007208866);
   Lxy_dt16_SigMC__1->SetBinContent(36,0.1244236);
   Lxy_dt16_SigMC__1->SetBinError(4,0.0008416806);
   Lxy_dt16_SigMC__1->SetBinError(5,0.000818869);
   Lxy_dt16_SigMC__1->SetBinError(6,0.0007856024);
   Lxy_dt16_SigMC__1->SetBinError(7,0.0007558048);
   Lxy_dt16_SigMC__1->SetBinError(8,0.0007346266);
   Lxy_dt16_SigMC__1->SetBinError(9,0.0006897612);
   Lxy_dt16_SigMC__1->SetBinError(10,0.0006690001);
   Lxy_dt16_SigMC__1->SetBinError(11,0.0006437443);
   Lxy_dt16_SigMC__1->SetBinError(12,0.0006305411);
   Lxy_dt16_SigMC__1->SetBinError(13,0.0005989079);
   Lxy_dt16_SigMC__1->SetBinError(14,0.0005675874);
   Lxy_dt16_SigMC__1->SetBinError(15,0.0005656744);
   Lxy_dt16_SigMC__1->SetBinError(16,0.0005430614);
   Lxy_dt16_SigMC__1->SetBinError(17,0.000520915);
   Lxy_dt16_SigMC__1->SetBinError(18,0.0004991391);
   Lxy_dt16_SigMC__1->SetBinError(19,0.0004787868);
   Lxy_dt16_SigMC__1->SetBinError(20,0.0004561635);
   Lxy_dt16_SigMC__1->SetBinError(21,0.0004484075);
   Lxy_dt16_SigMC__1->SetBinError(22,0.0004385947);
   Lxy_dt16_SigMC__1->SetBinError(23,0.0004169101);
   Lxy_dt16_SigMC__1->SetBinError(24,0.0004007546);
   Lxy_dt16_SigMC__1->SetBinError(25,0.0003915881);
   Lxy_dt16_SigMC__1->SetBinError(26,0.0003732205);
   Lxy_dt16_SigMC__1->SetBinError(27,0.0003671971);
   Lxy_dt16_SigMC__1->SetBinError(28,0.0003614617);
   Lxy_dt16_SigMC__1->SetBinError(29,0.0003496113);
   Lxy_dt16_SigMC__1->SetBinError(30,0.0003365507);
   Lxy_dt16_SigMC__1->SetBinError(31,0.00032458);
   Lxy_dt16_SigMC__1->SetBinError(32,0.0003193803);
   Lxy_dt16_SigMC__1->SetBinError(33,0.0003169901);
   Lxy_dt16_SigMC__1->SetBinError(34,0.0002928955);
   Lxy_dt16_SigMC__1->SetBinError(35,0.000285713);
   Lxy_dt16_SigMC__1->SetBinError(36,0.00124436);
   Lxy_dt16_SigMC__1->SetMaximum(0.4481684);
   Lxy_dt16_SigMC__1->SetEntries(134867);
   Lxy_dt16_SigMC__1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   Lxy_dt16_SigMC__1->SetFillColor(ci);
   Lxy_dt16_SigMC__1->SetFillStyle(3007);

   ci = TColor::GetColor("#ff0000");
   Lxy_dt16_SigMC__1->SetLineColor(ci);
   Lxy_dt16_SigMC__1->SetLineWidth(2);

   ci = TColor::GetColor("#ff0000");
   Lxy_dt16_SigMC__1->SetMarkerColor(ci);
   Lxy_dt16_SigMC__1->SetMarkerStyle(25);
   Lxy_dt16_SigMC__1->SetMarkerSize(0);
   Lxy_dt16_SigMC__1->GetXaxis()->SetTitle("L_{xy} [mm]");
   Lxy_dt16_SigMC__1->GetXaxis()->SetNoExponent();
   Lxy_dt16_SigMC__1->GetXaxis()->SetLabelFont(42);
   Lxy_dt16_SigMC__1->GetXaxis()->SetLabelOffset(0.028);
   Lxy_dt16_SigMC__1->GetXaxis()->SetLabelSize(0.05);
   Lxy_dt16_SigMC__1->GetXaxis()->SetTitleSize(0.05);
   Lxy_dt16_SigMC__1->GetXaxis()->SetTitleOffset(1.4);
   Lxy_dt16_SigMC__1->GetXaxis()->SetTitleFont(42);
   Lxy_dt16_SigMC__1->GetYaxis()->SetTitle("Fraction of events / 0.1 mm");
   Lxy_dt16_SigMC__1->GetYaxis()->SetLabelFont(42);
   Lxy_dt16_SigMC__1->GetYaxis()->SetLabelSize(0.05);
   Lxy_dt16_SigMC__1->GetYaxis()->SetTitleSize(0.05);
   Lxy_dt16_SigMC__1->GetYaxis()->SetTitleOffset(1.3);
   Lxy_dt16_SigMC__1->GetYaxis()->SetTitleFont(42);
   Lxy_dt16_SigMC__1->GetZaxis()->SetLabelFont(42);
   Lxy_dt16_SigMC__1->GetZaxis()->SetLabelSize(0.05);
   Lxy_dt16_SigMC__1->GetZaxis()->SetTitleSize(0.05);
   Lxy_dt16_SigMC__1->GetZaxis()->SetTitleFont(42);
   Lxy_dt16_SigMC__1->Draw("hist");
   
   TH1F *dataSR__2 = new TH1F("dataSR__2","dataSR",35,0,3.5);
   dataSR__2->SetBinContent(4,0.298779);
   dataSR__2->SetBinContent(5,0.1904674);
   dataSR__2->SetBinContent(6,0.1287037);
   dataSR__2->SetBinContent(7,0.08941598);
   dataSR__2->SetBinContent(8,0.06466229);
   dataSR__2->SetBinContent(9,0.04732433);
   dataSR__2->SetBinContent(10,0.03540057);
   dataSR__2->SetBinContent(11,0.02688185);
   dataSR__2->SetBinContent(12,0.0204379);
   dataSR__2->SetBinContent(13,0.016206);
   dataSR__2->SetBinContent(14,0.01267738);
   dataSR__2->SetBinContent(15,0.01028226);
   dataSR__2->SetBinContent(16,0.008270049);
   dataSR__2->SetBinContent(17,0.006700249);
   dataSR__2->SetBinContent(18,0.005530146);
   dataSR__2->SetBinContent(19,0.00474601);
   dataSR__2->SetBinContent(20,0.003809317);
   dataSR__2->SetBinContent(21,0.003196043);
   dataSR__2->SetBinContent(22,0.002730748);
   dataSR__2->SetBinContent(23,0.002231891);
   dataSR__2->SetBinContent(24,0.002021364);
   dataSR__2->SetBinContent(25,0.001702522);
   dataSR__2->SetBinContent(26,0.001434024);
   dataSR__2->SetBinContent(27,0.001316556);
   dataSR__2->SetBinContent(28,0.001072467);
   dataSR__2->SetBinContent(29,0.0009931381);
   dataSR__2->SetBinContent(30,0.0008894001);
   dataSR__2->SetBinContent(31,0.000741421);
   dataSR__2->SetBinContent(32,0.0006910776);
   dataSR__2->SetBinContent(33,0.0005964931);
   dataSR__2->SetBinContent(34,0.0005400474);
   dataSR__2->SetBinContent(35,0.0004652951);
   dataSR__2->SetBinContent(36,0.00908317);
   dataSR__2->SetBinError(4,0.000675133);
   dataSR__2->SetBinError(5,0.0005390445);
   dataSR__2->SetBinError(6,0.0004431082);
   dataSR__2->SetBinError(7,0.0003693362);
   dataSR__2->SetBinError(8,0.0003140797);
   dataSR__2->SetBinError(9,0.0002686931);
   dataSR__2->SetBinError(10,0.0002323911);
   dataSR__2->SetBinError(11,0.0002025088);
   dataSR__2->SetBinError(12,0.0001765763);
   dataSR__2->SetBinError(13,0.0001572361);
   dataSR__2->SetBinError(14,0.0001390686);
   dataSR__2->SetBinError(15,0.0001252445);
   dataSR__2->SetBinError(16,0.0001123229);
   dataSR__2->SetBinError(17,0.000101102);
   dataSR__2->SetBinError(18,9.185073e-05);
   dataSR__2->SetBinError(19,8.509002e-05);
   dataSR__2->SetBinError(20,7.62321e-05);
   dataSR__2->SetBinError(21,6.982656e-05);
   dataSR__2->SetBinError(22,6.454389e-05);
   dataSR__2->SetBinError(23,5.835133e-05);
   dataSR__2->SetBinError(24,5.553114e-05);
   dataSR__2->SetBinError(25,5.096367e-05);
   dataSR__2->SetBinError(26,4.677271e-05);
   dataSR__2->SetBinError(27,4.48161e-05);
   dataSR__2->SetBinError(28,4.044886e-05);
   dataSR__2->SetBinError(29,3.892415e-05);
   dataSR__2->SetBinError(30,3.683519e-05);
   dataSR__2->SetBinError(31,3.363154e-05);
   dataSR__2->SetBinError(32,3.246966e-05);
   dataSR__2->SetBinError(33,3.016595e-05);
   dataSR__2->SetBinError(34,2.87032e-05);
   dataSR__2->SetBinError(35,2.664272e-05);
   dataSR__2->SetBinError(36,0.0001177153);
   dataSR__2->SetMaximum(0.4481684);
   dataSR__2->SetEntries(655498);
   dataSR__2->SetStats(0);
   dataSR__2->SetLineWidth(2);
   dataSR__2->SetMarkerStyle(20);
   dataSR__2->SetMarkerSize(0.9);
   dataSR__2->GetXaxis()->SetTitle("L_{xy} [mm]");
   dataSR__2->GetXaxis()->SetRange(1,35);
   dataSR__2->GetXaxis()->SetNoExponent();
   dataSR__2->GetXaxis()->SetLabelFont(42);
   dataSR__2->GetXaxis()->SetLabelOffset(0.028);
   dataSR__2->GetXaxis()->SetLabelSize(0.05);
   dataSR__2->GetXaxis()->SetTitleSize(0.05);
   dataSR__2->GetXaxis()->SetTitleOffset(1.4);
   dataSR__2->GetXaxis()->SetTitleFont(42);
   dataSR__2->GetYaxis()->SetTitle("Fraction of events / 0.1 mm");
   dataSR__2->GetYaxis()->SetLabelFont(42);
   dataSR__2->GetYaxis()->SetLabelSize(0.05);
   dataSR__2->GetYaxis()->SetTitleSize(0.05);
   dataSR__2->GetYaxis()->SetTitleOffset(1.3);
   dataSR__2->GetYaxis()->SetTitleFont(42);
   dataSR__2->GetZaxis()->SetLabelFont(42);
   dataSR__2->GetZaxis()->SetLabelSize(0.05);
   dataSR__2->GetZaxis()->SetTitleSize(0.05);
   dataSR__2->GetZaxis()->SetTitleFont(42);
   dataSR__2->Draw("e0psame");
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
   TLegendEntry *entry=leg->AddEntry("dataSR","B^{0}_{s} #rightarrow #mu^{+} #mu^{-} sidebands","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(0.9);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Lxy_dt16_SigMC","B^{0}_{s} #rightarrow #mu^{+} #mu^{-} MC","fl");

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
