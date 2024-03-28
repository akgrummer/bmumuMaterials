void atlasLabel(Double_t,Double_t, bool, bool ,Color_t, bool, bool, bool, TString);


void CorrBkgBDTcut()
{
//=========Macro generated from canvas: CorrelationMatrixB/Correlations between MVA input variables (signal)
//=========  (Thu Aug 16 23:25:58 2018) by ROOT version6.10/02
   TCanvas *CorrelationMatrixBc = new TCanvas("CorrelationMatrixB", "Correlations between MVA input variables (signal)",171,75,800,600);
   gStyle->SetOptStat(0);
   // gStyle->SetPaintTextFormat(“4.1f”);
   CorrelationMatrixBc->Range(-3.162162,-3.162162,21.16216,21.16216);
   CorrelationMatrixBc->SetFillColor(0);
   CorrelationMatrixBc->SetBorderMode(0);
   CorrelationMatrixBc->SetBorderSize(2);
   // CorrelationMatrixBc->SetGridx();
   // CorrelationMatrixBc->SetGridy();
   CorrelationMatrixBc->SetTickx(1);
   CorrelationMatrixBc->SetTicky(1);
   CorrelationMatrixBc->SetLeftMargin(0.16);
   CorrelationMatrixBc->SetRightMargin(0.13);
   CorrelationMatrixBc->SetTopMargin(0.14);
   CorrelationMatrixBc->SetBottomMargin(0.13);
   CorrelationMatrixBc->SetFrameBorderMode(0);
   CorrelationMatrixBc->SetFrameBorderMode(0);
   
   TH2F *CorrelationMatrixB = new TH2F("CorrelationMatrixB"," ",18,0,18,18,0,18);
   CorrelationMatrixB->SetBinContent(21,100.0/100.);
   CorrelationMatrixB->SetBinContent(22,-1.0/100.);
   CorrelationMatrixB->SetBinContent(23,-2.0/100.);
   CorrelationMatrixB->SetBinContent(24,-2.0/100.);
   CorrelationMatrixB->SetBinContent(25,-13.0/100.);
   CorrelationMatrixB->SetBinContent(27,5.0/100.);
   CorrelationMatrixB->SetBinContent(28,-6.0/100.);
   CorrelationMatrixB->SetBinContent(29,-6.0/100.);
   CorrelationMatrixB->SetBinContent(30,-3.0/100.);
   CorrelationMatrixB->SetBinContent(31,-12.0/100.);
   CorrelationMatrixB->SetBinContent(32,1.0/100.);
   CorrelationMatrixB->SetBinContent(33,5.0/100.);
   CorrelationMatrixB->SetBinContent(34,2.0/100.);
   CorrelationMatrixB->SetBinContent(35,19.0/100.);
   CorrelationMatrixB->SetBinContent(37,-1.0/100.);
   CorrelationMatrixB->SetBinContent(38,-12.0/100.);
   CorrelationMatrixB->SetBinContent(41,-1.0/100.);
   CorrelationMatrixB->SetBinContent(42,100.0/100.);
   CorrelationMatrixB->SetBinContent(43,3.0/100.);
   CorrelationMatrixB->SetBinContent(44,-5.0/100.);
   CorrelationMatrixB->SetBinContent(45,-6.0/100.);
   CorrelationMatrixB->SetBinContent(46,1.0/100.);
   CorrelationMatrixB->SetBinContent(47,-7.0/100.);
   CorrelationMatrixB->SetBinContent(48,-4.0/100.);
   CorrelationMatrixB->SetBinContent(49,-6.0/100.);
   CorrelationMatrixB->SetBinContent(50,-4.0/100.);
   CorrelationMatrixB->SetBinContent(51,-3.0/100.);
   CorrelationMatrixB->SetBinContent(52,2.0/100.);
   CorrelationMatrixB->SetBinContent(54,1.0/100.);
   CorrelationMatrixB->SetBinContent(55,4.0/100.);
   CorrelationMatrixB->SetBinContent(57,-1.0/100.);
   CorrelationMatrixB->SetBinContent(58,-2.0/100.);
   CorrelationMatrixB->SetBinContent(61,-2.0/100.);
   CorrelationMatrixB->SetBinContent(62,3.0/100.);
   CorrelationMatrixB->SetBinContent(63,100.0/100.);
   CorrelationMatrixB->SetBinContent(64,-1.0/100.);
   CorrelationMatrixB->SetBinContent(65,-2.0/100.);
   CorrelationMatrixB->SetBinContent(66,-1.0/100.);
   CorrelationMatrixB->SetBinContent(68,-2.0/100.);
   CorrelationMatrixB->SetBinContent(69,-1.0/100.);
   CorrelationMatrixB->SetBinContent(72,-4.0/100.);
   CorrelationMatrixB->SetBinContent(73,4.0/100.);
   CorrelationMatrixB->SetBinContent(75,-2.0/100.);
   CorrelationMatrixB->SetBinContent(76,3.0/100.);
   CorrelationMatrixB->SetBinContent(77,3.0/100.);
   CorrelationMatrixB->SetBinContent(81,-2.0/100.);
   CorrelationMatrixB->SetBinContent(82,-5.0/100.);
   CorrelationMatrixB->SetBinContent(83,-1.0/100.);
   CorrelationMatrixB->SetBinContent(84,100.0/100.);
   CorrelationMatrixB->SetBinContent(85,35.0/100.);
   CorrelationMatrixB->SetBinContent(86,2.0/100.);
   CorrelationMatrixB->SetBinContent(87,-7.0/100.);
   CorrelationMatrixB->SetBinContent(88,8.0/100.);
   CorrelationMatrixB->SetBinContent(89,16.0/100.);
   CorrelationMatrixB->SetBinContent(90,75.0/100.);
   CorrelationMatrixB->SetBinContent(91,15.0/100.);
   CorrelationMatrixB->SetBinContent(92,-25.0/100.);
   CorrelationMatrixB->SetBinContent(93,-12.0/100.);
   CorrelationMatrixB->SetBinContent(94,-1.0/100.);
   CorrelationMatrixB->SetBinContent(95,-54.0/100.);
   CorrelationMatrixB->SetBinContent(96,-12.0/100.);
   CorrelationMatrixB->SetBinContent(97,-1.0/100.);
   CorrelationMatrixB->SetBinContent(98,5.0/100.);
   CorrelationMatrixB->SetBinContent(101,-13.0/100.);
   CorrelationMatrixB->SetBinContent(102,-6.0/100.);
   CorrelationMatrixB->SetBinContent(103,-2.0/100.);
   CorrelationMatrixB->SetBinContent(104,35.0/100.);
   CorrelationMatrixB->SetBinContent(105,100.0/100.);
   CorrelationMatrixB->SetBinContent(106,24.0/100.);
   CorrelationMatrixB->SetBinContent(107,-21.0/100.);
   CorrelationMatrixB->SetBinContent(108,71.0/100.);
   CorrelationMatrixB->SetBinContent(109,75.0/100.);
   CorrelationMatrixB->SetBinContent(110,31.0/100.);
   CorrelationMatrixB->SetBinContent(111,73.0/100.);
   CorrelationMatrixB->SetBinContent(112,-17.0/100.);
   CorrelationMatrixB->SetBinContent(113,-11.0/100.);
   CorrelationMatrixB->SetBinContent(114,-8.0/100.);
   CorrelationMatrixB->SetBinContent(115,-25.0/100.);
   CorrelationMatrixB->SetBinContent(116,-1.0/100.);
   CorrelationMatrixB->SetBinContent(117,26.0/100.);
   CorrelationMatrixB->SetBinContent(118,59.0/100.);
   CorrelationMatrixB->SetBinContent(122,1.0/100.);
   CorrelationMatrixB->SetBinContent(123,-1.0/100.);
   CorrelationMatrixB->SetBinContent(124,2.0/100.);
   CorrelationMatrixB->SetBinContent(125,24.0/100.);
   CorrelationMatrixB->SetBinContent(126,100.0/100.);
   CorrelationMatrixB->SetBinContent(127,-13.0/100.);
   CorrelationMatrixB->SetBinContent(128,7.0/100.);
   CorrelationMatrixB->SetBinContent(129,9.0/100.);
   CorrelationMatrixB->SetBinContent(130,2.0/100.);
   CorrelationMatrixB->SetBinContent(131,20.0/100.);
   CorrelationMatrixB->SetBinContent(132,-1.0/100.);
   CorrelationMatrixB->SetBinContent(134,12.0/100.);
   CorrelationMatrixB->SetBinContent(135,-8.0/100.);
   CorrelationMatrixB->SetBinContent(137,8.0/100.);
   CorrelationMatrixB->SetBinContent(138,11.0/100.);
   CorrelationMatrixB->SetBinContent(141,5.0/100.);
   CorrelationMatrixB->SetBinContent(142,-7.0/100.);
   CorrelationMatrixB->SetBinContent(144,-7.0/100.);
   CorrelationMatrixB->SetBinContent(145,-21.0/100.);
   CorrelationMatrixB->SetBinContent(146,-13.0/100.);
   CorrelationMatrixB->SetBinContent(147,100.0/100.);
   CorrelationMatrixB->SetBinContent(148,-18.0/100.);
   CorrelationMatrixB->SetBinContent(149,-19.0/100.);
   CorrelationMatrixB->SetBinContent(150,-4.0/100.);
   CorrelationMatrixB->SetBinContent(151,-36.0/100.);
   CorrelationMatrixB->SetBinContent(153,10.0/100.);
   CorrelationMatrixB->SetBinContent(154,3.0/100.);
   CorrelationMatrixB->SetBinContent(155,4.0/100.);
   CorrelationMatrixB->SetBinContent(156,-9.0/100.);
   CorrelationMatrixB->SetBinContent(157,-9.0/100.);
   CorrelationMatrixB->SetBinContent(158,-33.0/100.);
   CorrelationMatrixB->SetBinContent(161,-6.0/100.);
   CorrelationMatrixB->SetBinContent(162,-4.0/100.);
   CorrelationMatrixB->SetBinContent(163,-2.0/100.);
   CorrelationMatrixB->SetBinContent(164,8.0/100.);
   CorrelationMatrixB->SetBinContent(165,71.0/100.);
   CorrelationMatrixB->SetBinContent(166,7.0/100.);
   CorrelationMatrixB->SetBinContent(167,-18.0/100.);
   CorrelationMatrixB->SetBinContent(168,100.0/100.);
   CorrelationMatrixB->SetBinContent(169,93.0/100.);
   CorrelationMatrixB->SetBinContent(170,13.0/100.);
   CorrelationMatrixB->SetBinContent(171,74.0/100.);
   CorrelationMatrixB->SetBinContent(172,-10.0/100.);
   CorrelationMatrixB->SetBinContent(173,-8.0/100.);
   CorrelationMatrixB->SetBinContent(174,-15.0/100.);
   CorrelationMatrixB->SetBinContent(175,15.0/100.);
   CorrelationMatrixB->SetBinContent(176,11.0/100.);
   CorrelationMatrixB->SetBinContent(177,29.0/100.);
   CorrelationMatrixB->SetBinContent(178,76.0/100.);
   CorrelationMatrixB->SetBinContent(181,-6.0/100.);
   CorrelationMatrixB->SetBinContent(182,-6.0/100.);
   CorrelationMatrixB->SetBinContent(183,-1.0/100.);
   CorrelationMatrixB->SetBinContent(184,16.0/100.);
   CorrelationMatrixB->SetBinContent(185,75.0/100.);
   CorrelationMatrixB->SetBinContent(186,9.0/100.);
   CorrelationMatrixB->SetBinContent(187,-19.0/100.);
   CorrelationMatrixB->SetBinContent(188,93.0/100.);
   CorrelationMatrixB->SetBinContent(189,100.0/100.);
   CorrelationMatrixB->SetBinContent(190,13.0/100.);
   CorrelationMatrixB->SetBinContent(191,76.0/100.);
   CorrelationMatrixB->SetBinContent(192,-12.0/100.);
   CorrelationMatrixB->SetBinContent(193,-9.0/100.);
   CorrelationMatrixB->SetBinContent(194,-16.0/100.);
   CorrelationMatrixB->SetBinContent(195,10.0/100.);
   CorrelationMatrixB->SetBinContent(196,10.0/100.);
   CorrelationMatrixB->SetBinContent(197,26.0/100.);
   CorrelationMatrixB->SetBinContent(198,74.0/100.);
   CorrelationMatrixB->SetBinContent(201,-3.0/100.);
   CorrelationMatrixB->SetBinContent(202,-4.0/100.);
   CorrelationMatrixB->SetBinContent(204,75.0/100.);
   CorrelationMatrixB->SetBinContent(205,31.0/100.);
   CorrelationMatrixB->SetBinContent(206,2.0/100.);
   CorrelationMatrixB->SetBinContent(207,-4.0/100.);
   CorrelationMatrixB->SetBinContent(208,13.0/100.);
   CorrelationMatrixB->SetBinContent(209,13.0/100.);
   CorrelationMatrixB->SetBinContent(210,100.0/100.);
   CorrelationMatrixB->SetBinContent(211,11.0/100.);
   CorrelationMatrixB->SetBinContent(212,-20.0/100.);
   CorrelationMatrixB->SetBinContent(213,-10.0/100.);
   CorrelationMatrixB->SetBinContent(215,-52.0/100.);
   CorrelationMatrixB->SetBinContent(216,-10.0/100.);
   CorrelationMatrixB->SetBinContent(218,9.0/100.);
   CorrelationMatrixB->SetBinContent(221,-12.0/100.);
   CorrelationMatrixB->SetBinContent(222,-3.0/100.);
   CorrelationMatrixB->SetBinContent(224,15.0/100.);
   CorrelationMatrixB->SetBinContent(225,73.0/100.);
   CorrelationMatrixB->SetBinContent(226,20.0/100.);
   CorrelationMatrixB->SetBinContent(227,-36.0/100.);
   CorrelationMatrixB->SetBinContent(228,74.0/100.);
   CorrelationMatrixB->SetBinContent(229,76.0/100.);
   CorrelationMatrixB->SetBinContent(230,11.0/100.);
   CorrelationMatrixB->SetBinContent(231,100.0/100.);
   CorrelationMatrixB->SetBinContent(232,-17.0/100.);
   CorrelationMatrixB->SetBinContent(233,-14.0/100.);
   CorrelationMatrixB->SetBinContent(234,-28.0/100.);
   CorrelationMatrixB->SetBinContent(235,4.0/100.);
   CorrelationMatrixB->SetBinContent(236,13.0/100.);
   CorrelationMatrixB->SetBinContent(237,24.0/100.);
   CorrelationMatrixB->SetBinContent(238,92.0/100.);
   CorrelationMatrixB->SetBinContent(241,1.0/100.);
   CorrelationMatrixB->SetBinContent(242,2.0/100.);
   CorrelationMatrixB->SetBinContent(243,-4.0/100.);
   CorrelationMatrixB->SetBinContent(244,-25.0/100.);
   CorrelationMatrixB->SetBinContent(245,-17.0/100.);
   CorrelationMatrixB->SetBinContent(246,-1.0/100.);
   CorrelationMatrixB->SetBinContent(248,-10.0/100.);
   CorrelationMatrixB->SetBinContent(249,-12.0/100.);
   CorrelationMatrixB->SetBinContent(250,-20.0/100.);
   CorrelationMatrixB->SetBinContent(251,-17.0/100.);
   CorrelationMatrixB->SetBinContent(252,100.0/100.);
   CorrelationMatrixB->SetBinContent(253,6.0/100.);
   CorrelationMatrixB->SetBinContent(254,29.0/100.);
   CorrelationMatrixB->SetBinContent(255,24.0/100.);
   CorrelationMatrixB->SetBinContent(257,-3.0/100.);
   CorrelationMatrixB->SetBinContent(258,-11.0/100.);
   CorrelationMatrixB->SetBinContent(261,5.0/100.);
   CorrelationMatrixB->SetBinContent(263,4.0/100.);
   CorrelationMatrixB->SetBinContent(264,-12.0/100.);
   CorrelationMatrixB->SetBinContent(265,-11.0/100.);
   CorrelationMatrixB->SetBinContent(267,10.0/100.);
   CorrelationMatrixB->SetBinContent(268,-8.0/100.);
   CorrelationMatrixB->SetBinContent(269,-9.0/100.);
   CorrelationMatrixB->SetBinContent(270,-10.0/100.);
   CorrelationMatrixB->SetBinContent(271,-14.0/100.);
   CorrelationMatrixB->SetBinContent(272,6.0/100.);
   CorrelationMatrixB->SetBinContent(273,100.0/100.);
   CorrelationMatrixB->SetBinContent(274,19.0/100.);
   CorrelationMatrixB->SetBinContent(275,9.0/100.);
   CorrelationMatrixB->SetBinContent(276,-3.0/100.);
   CorrelationMatrixB->SetBinContent(277,78.0/100.);
   CorrelationMatrixB->SetBinContent(278,-2.0/100.);
   CorrelationMatrixB->SetBinContent(281,2.0/100.);
   CorrelationMatrixB->SetBinContent(282,1.0/100.);
   CorrelationMatrixB->SetBinContent(284,-1.0/100.);
   CorrelationMatrixB->SetBinContent(285,-8.0/100.);
   CorrelationMatrixB->SetBinContent(286,12.0/100.);
   CorrelationMatrixB->SetBinContent(287,3.0/100.);
   CorrelationMatrixB->SetBinContent(288,-15.0/100.);
   CorrelationMatrixB->SetBinContent(289,-16.0/100.);
   CorrelationMatrixB->SetBinContent(291,-28.0/100.);
   CorrelationMatrixB->SetBinContent(292,29.0/100.);
   CorrelationMatrixB->SetBinContent(293,19.0/100.);
   CorrelationMatrixB->SetBinContent(294,100.0/100.);
   CorrelationMatrixB->SetBinContent(295,-2.0/100.);
   CorrelationMatrixB->SetBinContent(296,4.0/100.);
   CorrelationMatrixB->SetBinContent(297,13.0/100.);
   CorrelationMatrixB->SetBinContent(298,-30.0/100.);
   CorrelationMatrixB->SetBinContent(301,19.0/100.);
   CorrelationMatrixB->SetBinContent(302,4.0/100.);
   CorrelationMatrixB->SetBinContent(303,-2.0/100.);
   CorrelationMatrixB->SetBinContent(304,-54.0/100.);
   CorrelationMatrixB->SetBinContent(305,-25.0/100.);
   CorrelationMatrixB->SetBinContent(306,-8.0/100.);
   CorrelationMatrixB->SetBinContent(307,4.0/100.);
   CorrelationMatrixB->SetBinContent(308,15.0/100.);
   CorrelationMatrixB->SetBinContent(309,10.0/100.);
   CorrelationMatrixB->SetBinContent(310,-52.0/100.);
   CorrelationMatrixB->SetBinContent(311,4.0/100.);
   CorrelationMatrixB->SetBinContent(312,24.0/100.);
   CorrelationMatrixB->SetBinContent(313,9.0/100.);
   CorrelationMatrixB->SetBinContent(314,-2.0/100.);
   CorrelationMatrixB->SetBinContent(315,100.0/100.);
   CorrelationMatrixB->SetBinContent(316,24.0/100.);
   CorrelationMatrixB->SetBinContent(317,-1.0/100.);
   CorrelationMatrixB->SetBinContent(318,18.0/100.);
   CorrelationMatrixB->SetBinContent(323,3.0/100.);
   CorrelationMatrixB->SetBinContent(324,-12.0/100.);
   CorrelationMatrixB->SetBinContent(325,-1.0/100.);
   CorrelationMatrixB->SetBinContent(327,-9.0/100.);
   CorrelationMatrixB->SetBinContent(328,11.0/100.);
   CorrelationMatrixB->SetBinContent(329,10.0/100.);
   CorrelationMatrixB->SetBinContent(330,-10.0/100.);
   CorrelationMatrixB->SetBinContent(331,13.0/100.);
   CorrelationMatrixB->SetBinContent(333,-3.0/100.);
   CorrelationMatrixB->SetBinContent(334,4.0/100.);
   CorrelationMatrixB->SetBinContent(335,24.0/100.);
   CorrelationMatrixB->SetBinContent(336,100.0/100.);
   CorrelationMatrixB->SetBinContent(337,-5.0/100.);
   CorrelationMatrixB->SetBinContent(338,17.0/100.);
   CorrelationMatrixB->SetBinContent(341,-1.0/100.);
   CorrelationMatrixB->SetBinContent(342,-1.0/100.);
   CorrelationMatrixB->SetBinContent(343,3.0/100.);
   CorrelationMatrixB->SetBinContent(344,-1.0/100.);
   CorrelationMatrixB->SetBinContent(345,26.0/100.);
   CorrelationMatrixB->SetBinContent(346,8.0/100.);
   CorrelationMatrixB->SetBinContent(347,-9.0/100.);
   CorrelationMatrixB->SetBinContent(348,29.0/100.);
   CorrelationMatrixB->SetBinContent(349,26.0/100.);
   CorrelationMatrixB->SetBinContent(351,24.0/100.);
   CorrelationMatrixB->SetBinContent(352,-3.0/100.);
   CorrelationMatrixB->SetBinContent(353,78.0/100.);
   CorrelationMatrixB->SetBinContent(354,13.0/100.);
   CorrelationMatrixB->SetBinContent(355,-1.0/100.);
   CorrelationMatrixB->SetBinContent(356,-5.0/100.);
   CorrelationMatrixB->SetBinContent(357,100.0/100.);
   CorrelationMatrixB->SetBinContent(358,32.0/100.);
   CorrelationMatrixB->SetBinContent(361,-12.0/100.);
   CorrelationMatrixB->SetBinContent(362,-2.0/100.);
   CorrelationMatrixB->SetBinContent(364,5.0/100.);
   CorrelationMatrixB->SetBinContent(365,59.0/100.);
   CorrelationMatrixB->SetBinContent(366,11.0/100.);
   CorrelationMatrixB->SetBinContent(367,-33.0/100.);
   CorrelationMatrixB->SetBinContent(368,76.0/100.);
   CorrelationMatrixB->SetBinContent(369,74.0/100.);
   CorrelationMatrixB->SetBinContent(370,9.0/100.);
   CorrelationMatrixB->SetBinContent(371,92.0/100.);
   CorrelationMatrixB->SetBinContent(372,-11.0/100.);
   CorrelationMatrixB->SetBinContent(373,-2.0/100.);
   CorrelationMatrixB->SetBinContent(374,-30.0/100.);
   CorrelationMatrixB->SetBinContent(375,18.0/100.);
   CorrelationMatrixB->SetBinContent(376,17.0/100.);
   CorrelationMatrixB->SetBinContent(377,32.0/100.);
   CorrelationMatrixB->SetBinContent(378,100.0/100.);
      CorrelationMatrixB->SetMinimum(-1.0);
   CorrelationMatrixB->SetMaximum(1.0);
   CorrelationMatrixB->SetEntries(648);
   CorrelationMatrixB->SetStats(0);
   CorrelationMatrixB->SetContour(20);
   CorrelationMatrixB->SetContourLevel(0,-1.00);
   CorrelationMatrixB->SetContourLevel(1,-.90);
   CorrelationMatrixB->SetContourLevel(2,-.80);
   CorrelationMatrixB->SetContourLevel(3,-.70);
   CorrelationMatrixB->SetContourLevel(4,-.60);
   CorrelationMatrixB->SetContourLevel(5,-.50);
   CorrelationMatrixB->SetContourLevel(6,-.40);
   CorrelationMatrixB->SetContourLevel(7,-.30);
   CorrelationMatrixB->SetContourLevel(8,-.20);
   CorrelationMatrixB->SetContourLevel(9,-.10);
   CorrelationMatrixB->SetContourLevel(10,0.0);
   CorrelationMatrixB->SetContourLevel(11,.10);
   CorrelationMatrixB->SetContourLevel(12,.20);
   CorrelationMatrixB->SetContourLevel(13,.30);
   CorrelationMatrixB->SetContourLevel(14,.40);
   CorrelationMatrixB->SetContourLevel(15,.50);
   CorrelationMatrixB->SetContourLevel(16,.60);
   CorrelationMatrixB->SetContourLevel(17,.70);
   CorrelationMatrixB->SetContourLevel(18,.80);
   CorrelationMatrixB->SetContourLevel(19,.90);
   CorrelationMatrixB->SetLineWidth(2);
   CorrelationMatrixB->SetMarkerColor(1);
   CorrelationMatrixB->SetMarkerStyle(20);
   CorrelationMatrixB->SetMarkerSize(0.9);
   CorrelationMatrixB->GetXaxis()->SetBinLabel(1,"m_{B}");
   CorrelationMatrixB->GetXaxis()->SetBinLabel(2,"N_{PV}");
   CorrelationMatrixB->GetXaxis()->SetBinLabel(3,"#eta_{B}");
   CorrelationMatrixB->GetXaxis()->SetBinLabel(4,"p_{T}^{B}");
   CorrelationMatrixB->GetXaxis()->SetBinLabel(5,"L_{xy}");
   CorrelationMatrixB->GetXaxis()->SetBinLabel(6,"DOCA^{min}_{trk}");
   CorrelationMatrixB->GetXaxis()->SetBinLabel(7,"N^{clos}_{trk}");
   CorrelationMatrixB->GetXaxis()->SetBinLabel(8,"|d_{0}|^{min} signif.");
   CorrelationMatrixB->GetXaxis()->SetBinLabel(9,"|d_{0}|^{max} signif.");
   CorrelationMatrixB->GetXaxis()->SetBinLabel(10,"P^{min}_{L}");
   CorrelationMatrixB->GetXaxis()->SetBinLabel(11,"ln(#chi^{2}_{PV,SV,xy})");
   CorrelationMatrixB->GetXaxis()->SetBinLabel(12,"|#alpha_{2D}|");
   CorrelationMatrixB->GetXaxis()->SetBinLabel(13,"#DeltaR");
   CorrelationMatrixB->GetXaxis()->SetBinLabel(14,"B Isolation");
   CorrelationMatrixB->GetXaxis()->SetBinLabel(15,"|#phi_{1}-#phi_{2}|");
   CorrelationMatrixB->GetXaxis()->SetBinLabel(16,"DCA(#mu_{1},#mu_{2}}");
   CorrelationMatrixB->GetXaxis()->SetBinLabel(17,"|IP_{#mu#mu, 3D}|");
   CorrelationMatrixB->GetXaxis()->SetBinLabel(18,"[ln(#chi^{2}_{#mu,any PV})]^{min}_{#mu1, #mu2}");
   CorrelationMatrixB->GetXaxis()->SetBit(TAxis::kLabelsDown);
   CorrelationMatrixB->GetXaxis()->SetLabelFont(42);
   CorrelationMatrixB->GetXaxis()->SetLabelOffset(0.011);
   CorrelationMatrixB->GetXaxis()->SetTitleSize(0.05);
   CorrelationMatrixB->GetXaxis()->SetTitleOffset(1.4);
   CorrelationMatrixB->GetXaxis()->SetTitleFont(42);
   CorrelationMatrixB->GetYaxis()->SetBinLabel(1,"m_{B}");
   CorrelationMatrixB->GetYaxis()->SetBinLabel(2,"N_{PV}");
   CorrelationMatrixB->GetYaxis()->SetBinLabel(3,"#eta_{B}");
   CorrelationMatrixB->GetYaxis()->SetBinLabel(4,"p_{T}^{B}");
   CorrelationMatrixB->GetYaxis()->SetBinLabel(5,"L_{xy}");
   CorrelationMatrixB->GetYaxis()->SetBinLabel(6,"DOCA^{min}_{trk}");
   CorrelationMatrixB->GetYaxis()->SetBinLabel(7,"N^{clos}_{trk}");
   CorrelationMatrixB->GetYaxis()->SetBinLabel(8,"|d_{0}|^{min} signif.");
   CorrelationMatrixB->GetYaxis()->SetBinLabel(9,"|d_{0}|^{max} signif.");
   CorrelationMatrixB->GetYaxis()->SetBinLabel(10,"P^{min}_{L}");
   CorrelationMatrixB->GetYaxis()->SetBinLabel(11,"ln(#chi^{2}_{PV,SV,xy})");
   CorrelationMatrixB->GetYaxis()->SetBinLabel(12,"|#alpha_{2D}|");
   CorrelationMatrixB->GetYaxis()->SetBinLabel(13,"#DeltaR");
   CorrelationMatrixB->GetYaxis()->SetBinLabel(14,"B Isolation");
   CorrelationMatrixB->GetYaxis()->SetBinLabel(15,"|#phi_{1}-#phi_{2}|");
   CorrelationMatrixB->GetYaxis()->SetBinLabel(16,"DCA(#mu_{1},#mu_{2}}");
   CorrelationMatrixB->GetYaxis()->SetBinLabel(17,"|IP_{#mu#mu, 3D}|");
   CorrelationMatrixB->GetYaxis()->SetBinLabel(18,"[ln(#chi^{2}_{#mu,any PV})]^{min}_{#mu1, #mu2}");

   CorrelationMatrixB->GetYaxis()->SetLabelSize(0.03);
   CorrelationMatrixB->GetXaxis()->SetLabelSize(0.03);

   CorrelationMatrixB->GetYaxis()->SetLabelFont(42);
   CorrelationMatrixB->GetYaxis()->SetTitleSize(0.05);
   CorrelationMatrixB->GetYaxis()->SetTitleOffset(1.4);
   CorrelationMatrixB->GetYaxis()->SetTitleFont(42);
   CorrelationMatrixB->GetZaxis()->SetLabelFont(42);
   CorrelationMatrixB->GetZaxis()->SetLabelSize(0.05);
   CorrelationMatrixB->GetZaxis()->SetTitleSize(0.05);
   CorrelationMatrixB->GetZaxis()->SetTitleFont(42);
   gStyle->SetPaintTextFormat("4.2f");
   gStyle->SetHistMinimumZero(kTRUE);
   CorrelationMatrixB->Draw("text45colz");
   
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
   

   // TLatex *text = new TLatex(0.4,0.94,"B_{s} #rightarrow #mu^{+}#mu^{-} MC");
   TText *text = new TText(0.305,0.94,"2015 and 2016 sidebands");
   text->SetNDC();
   text->SetTextFont(42);
   text->SetTextSize(0.05);
   text->Draw();
   // TText *text2 = new TText(0.489,0.87,"Before continuum-BDT selection");
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
   CorrelationMatrixBc->Modified();
   CorrelationMatrixBc->cd();
   CorrelationMatrixBc->SetSelected(CorrelationMatrixB);
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
