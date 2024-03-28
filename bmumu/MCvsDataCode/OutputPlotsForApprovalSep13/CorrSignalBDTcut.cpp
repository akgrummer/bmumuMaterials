void atlasLabel(Double_t,Double_t, bool, bool ,Color_t, bool, bool, bool, TString);


void CorrSignalBDTcut()
{
//=========Macro generated from canvas: CorrelationMatrixS/Correlations between MVA input variables (signal)
//=========  (Thu Aug 16 23:25:58 2018) by ROOT version6.10/02
   TCanvas *CorrelationMatrixSc = new TCanvas("CorrelationMatrixS", "Correlations between MVA input variables (signal)",171,75,800,600);
   gStyle->SetOptStat(0);
   // gStyle->SetPaintTextFormat(“4.1f”);
   CorrelationMatrixSc->Range(-3.162162,-3.162162,21.16216,21.16216);
   CorrelationMatrixSc->SetFillColor(0);
   CorrelationMatrixSc->SetBorderMode(0);
   CorrelationMatrixSc->SetBorderSize(2);
   // CorrelationMatrixSc->SetGridx();
   // CorrelationMatrixSc->SetGridy();
   CorrelationMatrixSc->SetTickx(1);
   CorrelationMatrixSc->SetTicky(1);
   CorrelationMatrixSc->SetLeftMargin(0.16);
   CorrelationMatrixSc->SetRightMargin(0.13);
   CorrelationMatrixSc->SetTopMargin(0.14);
   CorrelationMatrixSc->SetBottomMargin(0.13);
   CorrelationMatrixSc->SetFrameBorderMode(0);
   CorrelationMatrixSc->SetFrameBorderMode(0);
   
   TH2F *CorrelationMatrixS = new TH2F("CorrelationMatrixS"," ",18,0,18,18,0,18);
      CorrelationMatrixS->SetBinContent(21,100.0/100.);
   CorrelationMatrixS->SetBinContent(23,1.0/100.);
   CorrelationMatrixS->SetBinContent(24,1.0/100.);
   CorrelationMatrixS->SetBinContent(26,-1.0/100.);
   CorrelationMatrixS->SetBinContent(29,1.0/100.);
   CorrelationMatrixS->SetBinContent(32,-1.0/100.);
   CorrelationMatrixS->SetBinContent(35,2.0/100.);
   CorrelationMatrixS->SetBinContent(36,1.0/100.);
   CorrelationMatrixS->SetBinContent(37,-1.0/100.);
   CorrelationMatrixS->SetBinContent(42,100.0/100.);
   CorrelationMatrixS->SetBinContent(44,1.0/100.);
   CorrelationMatrixS->SetBinContent(50,1.0/100.);
   CorrelationMatrixS->SetBinContent(61,1.0/100.);
   CorrelationMatrixS->SetBinContent(63,100.0/100.);
   CorrelationMatrixS->SetBinContent(81,1.0/100.);
   CorrelationMatrixS->SetBinContent(82,1.0/100.);
   CorrelationMatrixS->SetBinContent(84,100.0/100.);
   CorrelationMatrixS->SetBinContent(85,45.0/100.);
   CorrelationMatrixS->SetBinContent(86,11.0/100.);
   CorrelationMatrixS->SetBinContent(87,-8.0/100.);
   CorrelationMatrixS->SetBinContent(88,4.0/100.);
   CorrelationMatrixS->SetBinContent(89,15.0/100.);
   CorrelationMatrixS->SetBinContent(90,76.0/100.);
   CorrelationMatrixS->SetBinContent(91,13.0/100.);
   CorrelationMatrixS->SetBinContent(92,-27.0/100.);
   CorrelationMatrixS->SetBinContent(93,-13.0/100.);
   CorrelationMatrixS->SetBinContent(94,1.0/100.);
   CorrelationMatrixS->SetBinContent(95,-53.0/100.);
   CorrelationMatrixS->SetBinContent(96,-11.0/100.);
   CorrelationMatrixS->SetBinContent(97,-3.0/100.);
   CorrelationMatrixS->SetBinContent(98,3.0/100.);
   CorrelationMatrixS->SetBinContent(104,45.0/100.);
   CorrelationMatrixS->SetBinContent(105,100.0/100.);
   CorrelationMatrixS->SetBinContent(106,37.0/100.);
   CorrelationMatrixS->SetBinContent(107,-24.0/100.);
   CorrelationMatrixS->SetBinContent(108,65.0/100.);
   CorrelationMatrixS->SetBinContent(109,72.0/100.);
   CorrelationMatrixS->SetBinContent(110,31.0/100.);
   CorrelationMatrixS->SetBinContent(111,76.0/100.);
   CorrelationMatrixS->SetBinContent(112,-34.0/100.);
   CorrelationMatrixS->SetBinContent(113,-16.0/100.);
   CorrelationMatrixS->SetBinContent(114,-10.0/100.);
   CorrelationMatrixS->SetBinContent(115,-24.0/100.);
   CorrelationMatrixS->SetBinContent(116,-1.0/100.);
   CorrelationMatrixS->SetBinContent(117,4.0/100.);
   CorrelationMatrixS->SetBinContent(118,66.0/100.);
   CorrelationMatrixS->SetBinContent(121,-1.0/100.);
   CorrelationMatrixS->SetBinContent(124,11.0/100.);
   CorrelationMatrixS->SetBinContent(125,37.0/100.);
   CorrelationMatrixS->SetBinContent(126,100.0/100.);
   CorrelationMatrixS->SetBinContent(127,-16.0/100.);
   CorrelationMatrixS->SetBinContent(128,25.0/100.);
   CorrelationMatrixS->SetBinContent(129,26.0/100.);
   CorrelationMatrixS->SetBinContent(130,8.0/100.);
   CorrelationMatrixS->SetBinContent(131,31.0/100.);
   CorrelationMatrixS->SetBinContent(132,-10.0/100.);
   CorrelationMatrixS->SetBinContent(133,-4.0/100.);
   CorrelationMatrixS->SetBinContent(134,12.0/100.);
   CorrelationMatrixS->SetBinContent(135,-5.0/100.);
   CorrelationMatrixS->SetBinContent(136,-2.0/100.);
   CorrelationMatrixS->SetBinContent(137,6.0/100.);
   CorrelationMatrixS->SetBinContent(138,27.0/100.);
   CorrelationMatrixS->SetBinContent(144,-8.0/100.);
   CorrelationMatrixS->SetBinContent(145,-24.0/100.);
   CorrelationMatrixS->SetBinContent(146,-16.0/100.);
   CorrelationMatrixS->SetBinContent(147,100.0/100.);
   CorrelationMatrixS->SetBinContent(148,-20.0/100.);
   CorrelationMatrixS->SetBinContent(149,-21.0/100.);
   CorrelationMatrixS->SetBinContent(150,-5.0/100.);
   CorrelationMatrixS->SetBinContent(151,-35.0/100.);
   CorrelationMatrixS->SetBinContent(152,18.0/100.);
   CorrelationMatrixS->SetBinContent(153,8.0/100.);
   CorrelationMatrixS->SetBinContent(154,1.0/100.);
   CorrelationMatrixS->SetBinContent(155,8.0/100.);
   CorrelationMatrixS->SetBinContent(156,-4.0/100.);
   CorrelationMatrixS->SetBinContent(157,-3.0/100.);
   CorrelationMatrixS->SetBinContent(158,-32.0/100.);
   CorrelationMatrixS->SetBinContent(164,4.0/100.);
   CorrelationMatrixS->SetBinContent(165,65.0/100.);
   CorrelationMatrixS->SetBinContent(166,25.0/100.);
   CorrelationMatrixS->SetBinContent(167,-20.0/100.);
   CorrelationMatrixS->SetBinContent(168,100.0/100.);
   CorrelationMatrixS->SetBinContent(169,92.0/100.);
   CorrelationMatrixS->SetBinContent(170,8.0/100.);
   CorrelationMatrixS->SetBinContent(171,82.0/100.);
   CorrelationMatrixS->SetBinContent(172,-22.0/100.);
   CorrelationMatrixS->SetBinContent(173,-10.0/100.);
   CorrelationMatrixS->SetBinContent(174,-12.0/100.);
   CorrelationMatrixS->SetBinContent(175,28.0/100.);
   CorrelationMatrixS->SetBinContent(176,16.0/100.);
   CorrelationMatrixS->SetBinContent(177,7.0/100.);
   CorrelationMatrixS->SetBinContent(178,85.0/100.);
   CorrelationMatrixS->SetBinContent(181,1.0/100.);
   CorrelationMatrixS->SetBinContent(184,15.0/100.);
   CorrelationMatrixS->SetBinContent(185,72.0/100.);
   CorrelationMatrixS->SetBinContent(186,26.0/100.);
   CorrelationMatrixS->SetBinContent(187,-21.0/100.);
   CorrelationMatrixS->SetBinContent(188,92.0/100.);
   CorrelationMatrixS->SetBinContent(189,100.0/100.);
   CorrelationMatrixS->SetBinContent(190,6.0/100.);
   CorrelationMatrixS->SetBinContent(191,83.0/100.);
   CorrelationMatrixS->SetBinContent(192,-23.0/100.);
   CorrelationMatrixS->SetBinContent(193,-11.0/100.);
   CorrelationMatrixS->SetBinContent(194,-11.0/100.);
   CorrelationMatrixS->SetBinContent(195,22.0/100.);
   CorrelationMatrixS->SetBinContent(196,15.0/100.);
   CorrelationMatrixS->SetBinContent(197,6.0/100.);
   CorrelationMatrixS->SetBinContent(198,80.0/100.);
   CorrelationMatrixS->SetBinContent(202,1.0/100.);
   CorrelationMatrixS->SetBinContent(204,76.0/100.);
   CorrelationMatrixS->SetBinContent(205,31.0/100.);
   CorrelationMatrixS->SetBinContent(206,8.0/100.);
   CorrelationMatrixS->SetBinContent(207,-5.0/100.);
   CorrelationMatrixS->SetBinContent(208,8.0/100.);
   CorrelationMatrixS->SetBinContent(209,6.0/100.);
   CorrelationMatrixS->SetBinContent(210,100.0/100.);
   CorrelationMatrixS->SetBinContent(211,7.0/100.);
   CorrelationMatrixS->SetBinContent(212,-20.0/100.);
   CorrelationMatrixS->SetBinContent(213,-9.0/100.);
   CorrelationMatrixS->SetBinContent(215,-48.0/100.);
   CorrelationMatrixS->SetBinContent(216,-11.0/100.);
   CorrelationMatrixS->SetBinContent(217,-2.0/100.);
   CorrelationMatrixS->SetBinContent(218,6.0/100.);
   CorrelationMatrixS->SetBinContent(224,13.0/100.);
   CorrelationMatrixS->SetBinContent(225,76.0/100.);
   CorrelationMatrixS->SetBinContent(226,31.0/100.);
   CorrelationMatrixS->SetBinContent(227,-35.0/100.);
   CorrelationMatrixS->SetBinContent(228,82.0/100.);
   CorrelationMatrixS->SetBinContent(229,83.0/100.);
   CorrelationMatrixS->SetBinContent(230,7.0/100.);
   CorrelationMatrixS->SetBinContent(231,100.0/100.);
   CorrelationMatrixS->SetBinContent(232,-36.0/100.);
   CorrelationMatrixS->SetBinContent(233,-16.0/100.);
   CorrelationMatrixS->SetBinContent(234,-19.0/100.);
   CorrelationMatrixS->SetBinContent(235,12.0/100.);
   CorrelationMatrixS->SetBinContent(236,12.0/100.);
   CorrelationMatrixS->SetBinContent(237,7.0/100.);
   CorrelationMatrixS->SetBinContent(238,94.0/100.);
   CorrelationMatrixS->SetBinContent(241,-1.0/100.);
   CorrelationMatrixS->SetBinContent(244,-27.0/100.);
   CorrelationMatrixS->SetBinContent(245,-34.0/100.);
   CorrelationMatrixS->SetBinContent(246,-10.0/100.);
   CorrelationMatrixS->SetBinContent(247,18.0/100.);
   CorrelationMatrixS->SetBinContent(248,-22.0/100.);
   CorrelationMatrixS->SetBinContent(249,-23.0/100.);
   CorrelationMatrixS->SetBinContent(250,-20.0/100.);
   CorrelationMatrixS->SetBinContent(251,-36.0/100.);
   CorrelationMatrixS->SetBinContent(252,100.0/100.);
   CorrelationMatrixS->SetBinContent(253,16.0/100.);
   CorrelationMatrixS->SetBinContent(254,16.0/100.);
   CorrelationMatrixS->SetBinContent(255,27.0/100.);
   CorrelationMatrixS->SetBinContent(258,-30.0/100.);
   CorrelationMatrixS->SetBinContent(264,-13.0/100.);
   CorrelationMatrixS->SetBinContent(265,-16.0/100.);
   CorrelationMatrixS->SetBinContent(266,-4.0/100.);
   CorrelationMatrixS->SetBinContent(267,8.0/100.);
   CorrelationMatrixS->SetBinContent(268,-10.0/100.);
   CorrelationMatrixS->SetBinContent(269,-11.0/100.);
   CorrelationMatrixS->SetBinContent(270,-9.0/100.);
   CorrelationMatrixS->SetBinContent(271,-16.0/100.);
   CorrelationMatrixS->SetBinContent(272,16.0/100.);
   CorrelationMatrixS->SetBinContent(273,100.0/100.);
   CorrelationMatrixS->SetBinContent(274,11.0/100.);
   CorrelationMatrixS->SetBinContent(275,11.0/100.);
   CorrelationMatrixS->SetBinContent(277,73.0/100.);
   CorrelationMatrixS->SetBinContent(278,-8.0/100.);
   CorrelationMatrixS->SetBinContent(284,1.0/100.);
   CorrelationMatrixS->SetBinContent(285,-10.0/100.);
   CorrelationMatrixS->SetBinContent(286,12.0/100.);
   CorrelationMatrixS->SetBinContent(287,1.0/100.);
   CorrelationMatrixS->SetBinContent(288,-12.0/100.);
   CorrelationMatrixS->SetBinContent(289,-11.0/100.);
   CorrelationMatrixS->SetBinContent(291,-19.0/100.);
   CorrelationMatrixS->SetBinContent(292,16.0/100.);
   CorrelationMatrixS->SetBinContent(293,11.0/100.);
   CorrelationMatrixS->SetBinContent(294,100.0/100.);
   CorrelationMatrixS->SetBinContent(296,1.0/100.);
   CorrelationMatrixS->SetBinContent(297,4.0/100.);
   CorrelationMatrixS->SetBinContent(298,-19.0/100.);
   CorrelationMatrixS->SetBinContent(301,2.0/100.);
   CorrelationMatrixS->SetBinContent(304,-53.0/100.);
   CorrelationMatrixS->SetBinContent(305,-24.0/100.);
   CorrelationMatrixS->SetBinContent(306,-5.0/100.);
   CorrelationMatrixS->SetBinContent(307,8.0/100.);
   CorrelationMatrixS->SetBinContent(308,28.0/100.);
   CorrelationMatrixS->SetBinContent(309,22.0/100.);
   CorrelationMatrixS->SetBinContent(310,-48.0/100.);
   CorrelationMatrixS->SetBinContent(311,12.0/100.);
   CorrelationMatrixS->SetBinContent(312,27.0/100.);
   CorrelationMatrixS->SetBinContent(313,11.0/100.);
   CorrelationMatrixS->SetBinContent(315,100.0/100.);
   CorrelationMatrixS->SetBinContent(316,24.0/100.);
   CorrelationMatrixS->SetBinContent(317,2.0/100.);
   CorrelationMatrixS->SetBinContent(318,24.0/100.);
   CorrelationMatrixS->SetBinContent(321,1.0/100.);
   CorrelationMatrixS->SetBinContent(324,-11.0/100.);
   CorrelationMatrixS->SetBinContent(325,-1.0/100.);
   CorrelationMatrixS->SetBinContent(326,-2.0/100.);
   CorrelationMatrixS->SetBinContent(327,-4.0/100.);
   CorrelationMatrixS->SetBinContent(328,16.0/100.);
   CorrelationMatrixS->SetBinContent(329,15.0/100.);
   CorrelationMatrixS->SetBinContent(330,-11.0/100.);
   CorrelationMatrixS->SetBinContent(331,12.0/100.);
   CorrelationMatrixS->SetBinContent(334,1.0/100.);
   CorrelationMatrixS->SetBinContent(335,24.0/100.);
   CorrelationMatrixS->SetBinContent(336,100.0/100.);
   CorrelationMatrixS->SetBinContent(337,1.0/100.);
   CorrelationMatrixS->SetBinContent(338,15.0/100.);
   CorrelationMatrixS->SetBinContent(341,-1.0/100.);
   CorrelationMatrixS->SetBinContent(344,-3.0/100.);
   CorrelationMatrixS->SetBinContent(345,4.0/100.);
   CorrelationMatrixS->SetBinContent(346,6.0/100.);
   CorrelationMatrixS->SetBinContent(347,-3.0/100.);
   CorrelationMatrixS->SetBinContent(348,7.0/100.);
   CorrelationMatrixS->SetBinContent(349,6.0/100.);
   CorrelationMatrixS->SetBinContent(350,-2.0/100.);
   CorrelationMatrixS->SetBinContent(351,7.0/100.);
   CorrelationMatrixS->SetBinContent(353,73.0/100.);
   CorrelationMatrixS->SetBinContent(354,4.0/100.);
   CorrelationMatrixS->SetBinContent(355,2.0/100.);
   CorrelationMatrixS->SetBinContent(356,1.0/100.);
   CorrelationMatrixS->SetBinContent(357,100.0/100.);
   CorrelationMatrixS->SetBinContent(358,12.0/100.);
   CorrelationMatrixS->SetBinContent(364,3.0/100.);
   CorrelationMatrixS->SetBinContent(365,66.0/100.);
   CorrelationMatrixS->SetBinContent(366,27.0/100.);
   CorrelationMatrixS->SetBinContent(367,-32.0/100.);
   CorrelationMatrixS->SetBinContent(368,85.0/100.);
   CorrelationMatrixS->SetBinContent(369,80.0/100.);
   CorrelationMatrixS->SetBinContent(370,6.0/100.);
   CorrelationMatrixS->SetBinContent(371,94.0/100.);
   CorrelationMatrixS->SetBinContent(372,-30.0/100.);
   CorrelationMatrixS->SetBinContent(373,-8.0/100.);
   CorrelationMatrixS->SetBinContent(374,-19.0/100.);
   CorrelationMatrixS->SetBinContent(375,24.0/100.);
   CorrelationMatrixS->SetBinContent(376,15.0/100.);
   CorrelationMatrixS->SetBinContent(377,12.0/100.);
   CorrelationMatrixS->SetBinContent(378,100.0/100.);
      CorrelationMatrixS->SetMinimum(-1.0);
   CorrelationMatrixS->SetMaximum(1.0);
   CorrelationMatrixS->SetEntries(648);
   CorrelationMatrixS->SetStats(0);
   CorrelationMatrixS->SetContour(20);
   CorrelationMatrixS->SetContourLevel(0,-1.00);
   CorrelationMatrixS->SetContourLevel(1,-.90);
   CorrelationMatrixS->SetContourLevel(2,-.80);
   CorrelationMatrixS->SetContourLevel(3,-.70);
   CorrelationMatrixS->SetContourLevel(4,-.60);
   CorrelationMatrixS->SetContourLevel(5,-.50);
   CorrelationMatrixS->SetContourLevel(6,-.40);
   CorrelationMatrixS->SetContourLevel(7,-.30);
   CorrelationMatrixS->SetContourLevel(8,-.20);
   CorrelationMatrixS->SetContourLevel(9,-.10);
   CorrelationMatrixS->SetContourLevel(10,0.0);
   CorrelationMatrixS->SetContourLevel(11,.10);
   CorrelationMatrixS->SetContourLevel(12,.20);
   CorrelationMatrixS->SetContourLevel(13,.30);
   CorrelationMatrixS->SetContourLevel(14,.40);
   CorrelationMatrixS->SetContourLevel(15,.50);
   CorrelationMatrixS->SetContourLevel(16,.60);
   CorrelationMatrixS->SetContourLevel(17,.70);
   CorrelationMatrixS->SetContourLevel(18,.80);
   CorrelationMatrixS->SetContourLevel(19,.90);
   CorrelationMatrixS->SetLineWidth(2);
   CorrelationMatrixS->SetMarkerColor(1);
   CorrelationMatrixS->SetMarkerStyle(20);
   CorrelationMatrixS->SetMarkerSize(0.9);
   CorrelationMatrixS->GetXaxis()->SetBinLabel(1,"m_{B}");
   CorrelationMatrixS->GetXaxis()->SetBinLabel(2,"N_{PV}");
   CorrelationMatrixS->GetXaxis()->SetBinLabel(3,"#eta_{B}");
   CorrelationMatrixS->GetXaxis()->SetBinLabel(4,"p_{T}^{B}");
   CorrelationMatrixS->GetXaxis()->SetBinLabel(5,"L_{xy}");
   CorrelationMatrixS->GetXaxis()->SetBinLabel(6,"DOCA^{min}_{trk}");
   CorrelationMatrixS->GetXaxis()->SetBinLabel(7,"N^{clos}_{trk}");
   CorrelationMatrixS->GetXaxis()->SetBinLabel(8,"|d_{0}|^{min} signif.");
   CorrelationMatrixS->GetXaxis()->SetBinLabel(9,"|d_{0}|^{max} signif.");
   CorrelationMatrixS->GetXaxis()->SetBinLabel(10,"P^{min}_{L}");
   CorrelationMatrixS->GetXaxis()->SetBinLabel(11,"ln(#chi^{2}_{PV,SV,xy})");
   CorrelationMatrixS->GetXaxis()->SetBinLabel(12,"|#alpha_{2D}|");
   CorrelationMatrixS->GetXaxis()->SetBinLabel(13,"#DeltaR");
   CorrelationMatrixS->GetXaxis()->SetBinLabel(14,"B Isolation");
   CorrelationMatrixS->GetXaxis()->SetBinLabel(15,"|#phi_{1}-#phi_{2}|");
   CorrelationMatrixS->GetXaxis()->SetBinLabel(16,"DCA(#mu_{1},#mu_{2}}");
   CorrelationMatrixS->GetXaxis()->SetBinLabel(17,"|IP_{#mu#mu, 3D}|");
   CorrelationMatrixS->GetXaxis()->SetBinLabel(18,"[ln(#chi^{2}_{#mu,any PV})]^{min}_{#mu1, #mu2}");
   CorrelationMatrixS->GetXaxis()->SetBit(TAxis::kLabelsDown);
   CorrelationMatrixS->GetXaxis()->SetLabelFont(42);
   CorrelationMatrixS->GetXaxis()->SetLabelOffset(0.011);
   CorrelationMatrixS->GetXaxis()->SetTitleSize(0.05);
   CorrelationMatrixS->GetXaxis()->SetTitleOffset(1.4);
   CorrelationMatrixS->GetXaxis()->SetTitleFont(42);
   CorrelationMatrixS->GetYaxis()->SetBinLabel(1,"m_{B}");
   CorrelationMatrixS->GetYaxis()->SetBinLabel(2,"N_{PV}");
   CorrelationMatrixS->GetYaxis()->SetBinLabel(3,"#eta_{B}");
   CorrelationMatrixS->GetYaxis()->SetBinLabel(4,"p_{T}^{B}");
   CorrelationMatrixS->GetYaxis()->SetBinLabel(5,"L_{xy}");
   CorrelationMatrixS->GetYaxis()->SetBinLabel(6,"DOCA^{min}_{trk}");
   CorrelationMatrixS->GetYaxis()->SetBinLabel(7,"N^{clos}_{trk}");
   CorrelationMatrixS->GetYaxis()->SetBinLabel(8,"|d_{0}|^{min} signif.");
   CorrelationMatrixS->GetYaxis()->SetBinLabel(9,"|d_{0}|^{max} signif.");
   CorrelationMatrixS->GetYaxis()->SetBinLabel(10,"P^{min}_{L}");
   CorrelationMatrixS->GetYaxis()->SetBinLabel(11,"ln(#chi^{2}_{PV,SV,xy})");
   CorrelationMatrixS->GetYaxis()->SetBinLabel(12,"|#alpha_{2D}|");
   CorrelationMatrixS->GetYaxis()->SetBinLabel(13,"#DeltaR");
   CorrelationMatrixS->GetYaxis()->SetBinLabel(14,"B Isolation");
   CorrelationMatrixS->GetYaxis()->SetBinLabel(15,"|#phi_{1}-#phi_{2}|");
   CorrelationMatrixS->GetYaxis()->SetBinLabel(16,"DCA(#mu_{1},#mu_{2}}");
   CorrelationMatrixS->GetYaxis()->SetBinLabel(17,"|IP_{#mu#mu, 3D}|");
   CorrelationMatrixS->GetYaxis()->SetBinLabel(18,"[ln(#chi^{2}_{#mu,any PV})]^{min}_{#mu1, #mu2}");

   CorrelationMatrixS->GetYaxis()->SetLabelSize(0.03);
   CorrelationMatrixS->GetXaxis()->SetLabelSize(0.03);

   CorrelationMatrixS->GetYaxis()->SetLabelFont(42);
   CorrelationMatrixS->GetYaxis()->SetTitleSize(0.05);
   CorrelationMatrixS->GetYaxis()->SetTitleOffset(1.4);
   CorrelationMatrixS->GetYaxis()->SetTitleFont(42);
   CorrelationMatrixS->GetZaxis()->SetLabelFont(42);
   CorrelationMatrixS->GetZaxis()->SetLabelSize(0.05);
   CorrelationMatrixS->GetZaxis()->SetTitleSize(0.05);
   CorrelationMatrixS->GetZaxis()->SetTitleFont(42);
   gStyle->SetPaintTextFormat("4.2f");
   gStyle->SetHistMinimumZero(kTRUE);
   CorrelationMatrixS->Draw("text45colz");
   
   // TPaveText *pt = new TPaveText(0.01,0.9407391,0.5885284,0.995,"blNDC");
   // pt->SetName("title");
   // pt->SetBorderSize(1);

   // Int_t ci;      // for color index setting
   // TColor *color; // for color definition with alpha
   // ci = TColor::GetColor("#5d6b7d");
   // pt->SetFillColor(ci);

   // ci = TColor::GetColor("#7d8b9d");
   // pt->SetLineColor(ci);
   // pt->SetTextColor(0);
   // TText *pt_LaTex = pt->AddText("Correlation Matrix (signal)");
   // pt->Draw();
   

   TLatex *text = new TLatex(0.4,0.94,"B_{s} #rightarrow #mu^{+}#mu^{-} MC");
   text->SetNDC();
   text->SetTextFont(42);
   text->SetTextSize(0.05);
   text->Draw();
   // TText *text2 = new TText(0.489,0.87,"After continuum-BDT selection");
   TText *text2 = new TText(0.51,0.87,"After continuum-BDT selection");
   text2->SetNDC();
   text2->SetTextFont(42);
   text2->SetTextSize(0.04);
   text2->Draw();
   atlasLabel(0.17,0.87, false, true, 1, false, false, true, "");
   // TText *text = new TText(0.53,0.88,"Linear correlation coefficients in %");
   // text->SetNDC();
   // text->SetTextSize(0.026);
   // text->Draw();
   CorrelationMatrixSc->Modified();
   CorrelationMatrixSc->cd();
   CorrelationMatrixSc->SetSelected(CorrelationMatrixS);
}


void atlasLabel(Double_t x,Double_t y, bool drawRes = true, bool Preliminary=true,Color_t color=1, bool drawEnergy=false, bool drawLumi=false, bool enlarge=true, TString h1title = "")
{
  double delx = 0.115*696*gPad->GetWh()*3/(5*472*gPad->GetWw());
  double textsize;
  double dy = 0.065;
  // if (!drawRes) {
  //   delx+=0.02;
  //   textsize = 0.040;
  // } else {
    if (enlarge) {
      textsize = 0.05; 
      delx+=0.06;
      dy = 0.125;
      // dy = 0.1;
    }
    // else textsize = 0.06;
    // delx+=0.04;
  // }
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
    if (h1title.Contains("fabs_a_2D")) tex = new TLatex(0.59,0.55,"#sqrt{s} = 13 TeV, 26.2 fb^{-1}");
    else tex = new TLatex(x+0.01,y-dy,"#sqrt{s} = 13 TeV, 26.2 fb^{-1}");
    tex->SetNDC();
    tex->SetTextSize(textsize);
    tex->SetTextFont(42);
    tex->SetLineWidth(2);
    tex->SetTextColor(color);
    tex->Draw();
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

