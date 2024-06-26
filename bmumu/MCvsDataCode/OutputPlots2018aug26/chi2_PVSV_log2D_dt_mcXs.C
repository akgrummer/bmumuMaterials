void chi2_PVSV_log2D_dt_mcXs()
{
//=========Macro generated from canvas: c1/c1
//=========  (Sun Aug 26 22:05:56 2018) by ROOT version6.10/04
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
   pad1->Range(-4.835443,-7.464943,12.88608,1.06807);
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
   
   TH1F *chi2_PVSV_log2D_dt16_SigMC__1 = new TH1F("chi2_PVSV_log2D_dt16_SigMC__1","chi2_PVSV_log2D_dt16_SigMC",60,-2,12);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(9,1.580268e-05);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(11,4.179881e-06);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(12,1.589898e-06);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(13,2.336069e-05);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(14,0.0001053184);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(15,0.00024737);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(16,0.0004844042);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(17,0.0007683489);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(18,0.001401153);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(19,0.002179457);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(20,0.003703035);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(21,0.006346487);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(22,0.01023111);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(23,0.01376543);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(24,0.01861214);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(25,0.02485012);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(26,0.02903187);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(27,0.03549631);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(28,0.03874015);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(29,0.04143632);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(30,0.04311098);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(31,0.04605665);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(32,0.04826606);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(33,0.04776029);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(34,0.04829343);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(35,0.04896289);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(36,0.05001475);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(37,0.05032595);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(38,0.04802377);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(39,0.0460751);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(40,0.04220022);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(41,0.04027684);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(42,0.03720404);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(43,0.03259961);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(44,0.02867597);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(45,0.02484385);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(46,0.02057931);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(47,0.01745182);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(48,0.01353754);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(49,0.01088892);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(50,0.008414231);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(51,0.00616038);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(52,0.00434145);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(53,0.002866392);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(54,0.001933427);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(55,0.00145474);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(56,0.0008089719);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(57,0.0006348809);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(58,0.0003303581);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(59,0.000288489);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(60,0.0001747213);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinContent(61,0.0002476829);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(9,1.580268e-05);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(11,4.179881e-06);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(12,1.589898e-06);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(13,1.830314e-05);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(14,3.681792e-05);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(15,5.571049e-05);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(16,7.976917e-05);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(17,0.0001029738);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(18,0.0001328796);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(19,0.0001575048);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(20,0.0002103689);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(21,0.0002685948);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(22,0.0003419938);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(23,0.0003896403);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(24,0.0004477988);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(25,0.0005156912);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(26,0.0005502536);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(27,0.000607345);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(28,0.0006361136);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(29,0.0006542448);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(30,0.0006693535);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(31,0.0006873693);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(32,0.000708831);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(33,0.0007009217);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(34,0.0007071052);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(35,0.0007136029);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(36,0.0007240091);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(37,0.0007266286);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(38,0.0007090062);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(39,0.0006986454);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(40,0.0006685237);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(41,0.0006571815);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(42,0.0006356214);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(43,0.000592961);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(44,0.0005582647);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(45,0.0005231835);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(46,0.000476312);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(47,0.0004461502);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(48,0.0003889833);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(49,0.0003571849);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(50,0.0003133042);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(51,0.0002691379);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(52,0.0002287558);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(53,0.0001892571);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(54,0.0001529665);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(55,0.0001342529);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(56,0.0001025818);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(57,9.390668e-05);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(58,6.81774e-05);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(59,6.730313e-05);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(60,4.937626e-05);
   chi2_PVSV_log2D_dt16_SigMC__1->SetBinError(61,6.115244e-05);
   chi2_PVSV_log2D_dt16_SigMC__1->SetMaximum(1.995715);
   chi2_PVSV_log2D_dt16_SigMC__1->SetEntries(134867);
   chi2_PVSV_log2D_dt16_SigMC__1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   chi2_PVSV_log2D_dt16_SigMC__1->SetFillColor(ci);
   chi2_PVSV_log2D_dt16_SigMC__1->SetFillStyle(3007);

   ci = TColor::GetColor("#ff0000");
   chi2_PVSV_log2D_dt16_SigMC__1->SetLineColor(ci);
   chi2_PVSV_log2D_dt16_SigMC__1->SetLineWidth(2);

   ci = TColor::GetColor("#ff0000");
   chi2_PVSV_log2D_dt16_SigMC__1->SetMarkerColor(ci);
   chi2_PVSV_log2D_dt16_SigMC__1->SetMarkerStyle(25);
   chi2_PVSV_log2D_dt16_SigMC__1->SetMarkerSize(0);
   chi2_PVSV_log2D_dt16_SigMC__1->GetXaxis()->SetTitle("ln[#chi^{2} (PV-DV)] x-y plane");
   chi2_PVSV_log2D_dt16_SigMC__1->GetXaxis()->SetNoExponent();
   chi2_PVSV_log2D_dt16_SigMC__1->GetXaxis()->SetLabelFont(42);
   chi2_PVSV_log2D_dt16_SigMC__1->GetXaxis()->SetLabelOffset(0.028);
   chi2_PVSV_log2D_dt16_SigMC__1->GetXaxis()->SetLabelSize(0.05);
   chi2_PVSV_log2D_dt16_SigMC__1->GetXaxis()->SetTitleSize(0.05);
   chi2_PVSV_log2D_dt16_SigMC__1->GetXaxis()->SetTitleOffset(1.4);
   chi2_PVSV_log2D_dt16_SigMC__1->GetXaxis()->SetTitleFont(42);
   chi2_PVSV_log2D_dt16_SigMC__1->GetYaxis()->SetTitle("1/N dn/dln(#chi^{2})");
   chi2_PVSV_log2D_dt16_SigMC__1->GetYaxis()->SetLabelFont(42);
   chi2_PVSV_log2D_dt16_SigMC__1->GetYaxis()->SetLabelSize(0.05);
   chi2_PVSV_log2D_dt16_SigMC__1->GetYaxis()->SetTitleSize(0.05);
   chi2_PVSV_log2D_dt16_SigMC__1->GetYaxis()->SetTitleOffset(1.3);
   chi2_PVSV_log2D_dt16_SigMC__1->GetYaxis()->SetTitleFont(42);
   chi2_PVSV_log2D_dt16_SigMC__1->GetZaxis()->SetLabelFont(42);
   chi2_PVSV_log2D_dt16_SigMC__1->GetZaxis()->SetLabelSize(0.05);
   chi2_PVSV_log2D_dt16_SigMC__1->GetZaxis()->SetTitleSize(0.05);
   chi2_PVSV_log2D_dt16_SigMC__1->GetZaxis()->SetTitleFont(42);
   chi2_PVSV_log2D_dt16_SigMC__1->Draw("hist");
   
   TH1F *dataSR__2 = new TH1F("dataSR__2","dataSR",60,-2,12);
   dataSR__2->SetBinContent(3,1.52662e-06);
   dataSR__2->SetBinContent(4,3.053239e-06);
   dataSR__2->SetBinContent(6,4.579859e-06);
   dataSR__2->SetBinContent(7,2.28993e-05);
   dataSR__2->SetBinContent(8,2.900577e-05);
   dataSR__2->SetBinContent(9,3.511225e-05);
   dataSR__2->SetBinContent(10,0.0001160231);
   dataSR__2->SetBinContent(11,0.0001755613);
   dataSR__2->SetBinContent(12,0.000312957);
   dataSR__2->SetBinContent(13,0.0004228737);
   dataSR__2->SetBinContent(14,0.00075873);
   dataSR__2->SetBinContent(15,0.001082373);
   dataSR__2->SetBinContent(16,0.001648749);
   dataSR__2->SetBinContent(17,0.002470071);
   dataSR__2->SetBinContent(18,0.003653201);
   dataSR__2->SetBinContent(19,0.005538576);
   dataSR__2->SetBinContent(20,0.008503271);
   dataSR__2->SetBinContent(21,0.01340983);
   dataSR__2->SetBinContent(22,0.02031015);
   dataSR__2->SetBinContent(23,0.02881037);
   dataSR__2->SetBinContent(24,0.03903872);
   dataSR__2->SetBinContent(25,0.04996473);
   dataSR__2->SetBinContent(26,0.06058237);
   dataSR__2->SetBinContent(27,0.06984895);
   dataSR__2->SetBinContent(28,0.07608367);
   dataSR__2->SetBinContent(29,0.0779034);
   dataSR__2->SetBinContent(30,0.07774922);
   dataSR__2->SetBinContent(31,0.07321668);
   dataSR__2->SetBinContent(32,0.06834523);
   dataSR__2->SetBinContent(33,0.06049689);
   dataSR__2->SetBinContent(34,0.05272792);
   dataSR__2->SetBinContent(35,0.04444906);
   dataSR__2->SetBinContent(36,0.03712892);
   dataSR__2->SetBinContent(37,0.03006983);
   dataSR__2->SetBinContent(38,0.02358017);
   dataSR__2->SetBinContent(39,0.01841409);
   dataSR__2->SetBinContent(40,0.01434412);
   dataSR__2->SetBinContent(41,0.01056573);
   dataSR__2->SetBinContent(42,0.00790789);
   dataSR__2->SetBinContent(43,0.005662232);
   dataSR__2->SetBinContent(44,0.004047069);
   dataSR__2->SetBinContent(45,0.002859359);
   dataSR__2->SetBinContent(46,0.002031931);
   dataSR__2->SetBinContent(47,0.001428916);
   dataSR__2->SetBinContent(48,0.0008884926);
   dataSR__2->SetBinContent(49,0.0007755228);
   dataSR__2->SetBinContent(50,0.0005327903);
   dataSR__2->SetBinContent(51,0.0003923413);
   dataSR__2->SetBinContent(52,0.0003434894);
   dataSR__2->SetBinContent(53,0.0002442591);
   dataSR__2->SetBinContent(54,0.0002228865);
   dataSR__2->SetBinContent(55,0.0001954073);
   dataSR__2->SetBinContent(56,0.000184721);
   dataSR__2->SetBinContent(57,0.0001221296);
   dataSR__2->SetBinContent(58,0.0001297627);
   dataSR__2->SetBinContent(59,0.0001129699);
   dataSR__2->SetBinContent(60,9.923028e-05);
   dataSR__2->SetBinContent(61,0.0006961386);
   dataSR__2->SetBinError(3,1.52662e-06);
   dataSR__2->SetBinError(4,2.158966e-06);
   dataSR__2->SetBinError(6,2.644183e-06);
   dataSR__2->SetBinError(7,5.912573e-06);
   dataSR__2->SetBinError(8,6.654381e-06);
   dataSR__2->SetBinError(9,7.321411e-06);
   dataSR__2->SetBinError(10,1.330876e-05);
   dataSR__2->SetBinError(11,1.637117e-05);
   dataSR__2->SetBinError(12,2.185787e-05);
   dataSR__2->SetBinError(13,2.540802e-05);
   dataSR__2->SetBinError(14,3.403369e-05);
   dataSR__2->SetBinError(15,4.064938e-05);
   dataSR__2->SetBinError(16,5.016984e-05);
   dataSR__2->SetBinError(17,6.140732e-05);
   dataSR__2->SetBinError(18,7.467964e-05);
   dataSR__2->SetBinError(19,9.19527e-05);
   dataSR__2->SetBinError(20,0.0001139353);
   dataSR__2->SetBinError(21,0.0001430794);
   dataSR__2->SetBinError(22,0.0001760848);
   dataSR__2->SetBinError(23,0.00020972);
   dataSR__2->SetBinError(24,0.0002441255);
   dataSR__2->SetBinError(25,0.0002761832);
   dataSR__2->SetBinError(26,0.0003041155);
   dataSR__2->SetBinError(27,0.0003265468);
   dataSR__2->SetBinError(28,0.0003408091);
   dataSR__2->SetBinError(29,0.0003448606);
   dataSR__2->SetBinError(30,0.0003445192);
   dataSR__2->SetBinError(31,0.0003343262);
   dataSR__2->SetBinError(32,0.0003230127);
   dataSR__2->SetBinError(33,0.0003039009);
   dataSR__2->SetBinError(34,0.0002837172);
   dataSR__2->SetBinError(35,0.0002604934);
   dataSR__2->SetBinError(36,0.0002380793);
   dataSR__2->SetBinError(37,0.000214255);
   dataSR__2->SetBinError(38,0.0001897313);
   dataSR__2->SetBinError(39,0.0001676643);
   dataSR__2->SetBinError(40,0.0001479798);
   dataSR__2->SetBinError(41,0.0001270034);
   dataSR__2->SetBinError(42,0.0001098742);
   dataSR__2->SetBinError(43,9.297352e-05);
   dataSR__2->SetBinError(44,7.860238e-05);
   dataSR__2->SetBinError(45,6.606931e-05);
   dataSR__2->SetBinError(46,5.569547e-05);
   dataSR__2->SetBinError(47,4.670558e-05);
   dataSR__2->SetBinError(48,3.682921e-05);
   dataSR__2->SetBinError(49,3.440826e-05);
   dataSR__2->SetBinError(50,2.851961e-05);
   dataSR__2->SetBinError(51,2.447358e-05);
   dataSR__2->SetBinError(52,2.28993e-05);
   dataSR__2->SetBinError(53,1.931038e-05);
   dataSR__2->SetBinError(54,1.844622e-05);
   dataSR__2->SetBinError(55,1.727173e-05);
   dataSR__2->SetBinError(56,1.679282e-05);
   dataSR__2->SetBinError(57,1.36545e-05);
   dataSR__2->SetBinError(58,1.407474e-05);
   dataSR__2->SetBinError(59,1.313248e-05);
   dataSR__2->SetBinError(60,1.2308e-05);
   dataSR__2->SetBinError(61,3.259968e-05);
   dataSR__2->SetMaximum(1.995715);
   dataSR__2->SetEntries(655498);
   dataSR__2->SetStats(0);
   dataSR__2->SetLineWidth(2);
   dataSR__2->SetMarkerStyle(20);
   dataSR__2->SetMarkerSize(0.9);
   dataSR__2->GetXaxis()->SetTitle("ln[#chi^{2} (PV-DV)] x-y plane");
   dataSR__2->GetXaxis()->SetRange(1,60);
   dataSR__2->GetXaxis()->SetNoExponent();
   dataSR__2->GetXaxis()->SetLabelFont(42);
   dataSR__2->GetXaxis()->SetLabelOffset(0.028);
   dataSR__2->GetXaxis()->SetLabelSize(0.05);
   dataSR__2->GetXaxis()->SetTitleSize(0.05);
   dataSR__2->GetXaxis()->SetTitleOffset(1.4);
   dataSR__2->GetXaxis()->SetTitleFont(42);
   dataSR__2->GetYaxis()->SetTitle("1/N dn/dln(#chi^{2})");
   dataSR__2->GetYaxis()->SetLabelFont(42);
   dataSR__2->GetYaxis()->SetLabelSize(0.05);
   dataSR__2->GetYaxis()->SetTitleSize(0.05);
   dataSR__2->GetYaxis()->SetTitleOffset(1.3);
   dataSR__2->GetYaxis()->SetTitleFont(42);
   dataSR__2->GetZaxis()->SetLabelFont(42);
   dataSR__2->GetZaxis()->SetLabelSize(0.05);
   dataSR__2->GetZaxis()->SetTitleSize(0.05);
   dataSR__2->GetZaxis()->SetTitleFont(42);
   dataSR__2->Draw("psame");
   TLatex *   tex = new TLatex(0.62,0.83,"ATLAS");
tex->SetNDC();
   tex->SetTextFont(72);
   tex->SetTextSize(0.055);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.7631138,0.83,"Internal");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.055);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.58,0.77,"#sqrt{s} = 13 TeV, 36.2 fb^{-1}");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.055);
   tex->SetLineWidth(2);
   tex->Draw();
   
   TLegend *leg = new TLegend(0.179198,0.756098,0.502506,0.879791,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(132);
   leg->SetTextSize(0.045);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("dataSR","2015 and 2016 sidebands","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(0.9);
   entry->SetTextFont(132);
   entry=leg->AddEntry("chi2_PVSV_log2D_dt16_SigMC","B_{s} #rightarrow #mu^{+} #mu^{-} MC","fl");

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
   entry->SetTextFont(132);
   leg->Draw();
   pad1->Modified();
   c1->cd();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
