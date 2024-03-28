void c1()
{
//=========Macro generated from canvas: c1/c1
//=========  (Wed Jun 17 09:43:48 2020) by ROOT version 6.20/04
   TCanvas *c1 = new TCanvas("c1", "c1",0,45,800,600);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c1->Range(-0.1947702,-0.1429396,0.6904913,0.7100824);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetTickx(1);
   c1->SetTicky(1);
   c1->SetLeftMargin(0.1635338);
   c1->SetRightMargin(0.04573935);
   c1->SetTopMargin(0.07043478);
   c1->SetBottomMargin(0.1382609);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   Double_t Graph0_fx24[22] = {
   0.5327,
   0.3909667,
   0.3905,
   0.3905,
   0.3905,
   0.3213,
   0.3213,
   0.3213,
   0.05768,
   0.3728,
   0.371,
   0.371,
   0.371,
   0.02572,
   0.4126,
   0.2864,
   0.02995,
   0.01149,
   0.5149,
   0.1054,
   0.1523,
   0.3623};
   Double_t Graph0_fy24[22] = {
   0.5911,
   0.3659066,
   0.3961,
   0.3929,
   0.3971,
   0.3998,
   0.404,
   0.4033,
   0.07581,
   0.381,
   0.4217,
   0.4512,
   0.4497,
   0.0227,
   0.4399,
   0.3053,
   0.02277,
   0.01244,
   0.572,
   0.1453,
   0.1714,
   0.3938};
   TGraph *graph = new TGraph(22,Graph0_fx24,Graph0_fy24);
   graph->SetName("Graph0");
   graph->SetTitle("Graph");
   graph->SetFillStyle(1000);
   graph->SetLineColor(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#cc0000");
   graph->SetMarkerColor(ci);
   graph->SetMarkerStyle(20);
   graph->SetMarkerSize(0.5);
   
   TH1F *Graph_Graph_Graph0124 = new TH1F("Graph_Graph_Graph0124","Graph",100,-0.05,0.65);
   Graph_Graph_Graph0124->SetMinimum(-0.025);
   Graph_Graph_Graph0124->SetMaximum(0.65);
   Graph_Graph_Graph0124->SetDirectory(0);
   Graph_Graph_Graph0124->SetStats(0);
   Graph_Graph_Graph0124->SetLineWidth(2);
   Graph_Graph_Graph0124->SetMarkerStyle(20);
   Graph_Graph_Graph0124->SetMarkerSize(1.2);
   Graph_Graph_Graph0124->GetXaxis()->SetTitle("Run 1 Separation");
   Graph_Graph_Graph0124->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Graph0124->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph_Graph0124->GetXaxis()->SetTitleSize(0.05);
   Graph_Graph_Graph0124->GetXaxis()->SetTitleOffset(1.4);
   Graph_Graph_Graph0124->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Graph0124->GetYaxis()->SetTitle("new Run 2 Separation");
   Graph_Graph_Graph0124->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Graph0124->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph_Graph0124->GetYaxis()->SetTitleSize(0.05);
   Graph_Graph_Graph0124->GetYaxis()->SetTitleOffset(1.4);
   Graph_Graph_Graph0124->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Graph0124->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Graph0124->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph_Graph0124->GetZaxis()->SetTitleSize(0.05);
   Graph_Graph_Graph0124->GetZaxis()->SetTitleOffset(1);
   Graph_Graph_Graph0124->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph_Graph0124);
   
   TLatex *   tex = new TLatex(0.5396197,0.6003022,"#Delta R");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.017);
   tex->SetLineWidth(2);
   tex->Draw();
   graph->GetListOfFunctions()->Add(25);
      tex = new TLatex(0.4009509,0.3659066,"B Iso ACH");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.017);
   tex->SetLineWidth(2);
   tex->Draw();
   graph->GetListOfFunctions()->Add(26);
      tex = new TLatex(0.3998415,0.4029945,"B Iso BDI As in Run 1");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.017);
   tex->SetLineWidth(2);
   tex->Draw();
   graph->GetListOfFunctions()->Add(27);
      tex = new TLatex(0.3998415,0.3881593,"B Iso BEJ Custom");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.017);
   tex->SetLineWidth(2);
   tex->Draw();
   graph->GetListOfFunctions()->Add(28);
      tex = new TLatex(0.3998415,0.4163462,"B Iso BGJ Loose");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.017);
   tex->SetLineWidth(2);
   tex->Draw();
   graph->GetListOfFunctions()->Add(29);
      tex = new TLatex(0.2611727,0.3881593,"DOCA ACK");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.017);
   tex->SetLineWidth(2);
   tex->Draw();
   graph->GetListOfFunctions()->Add(30);
      tex = new TLatex(0.2278922,0.4193132,"DOCA BEL Custom");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.017);
   tex->SetLineWidth(2);
   tex->Draw();
   graph->GetListOfFunctions()->Add(31);
      tex = new TLatex(0.2323296,0.404478,"DOCA BGL Loose");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.017);
   tex->SetLineWidth(2);
   tex->Draw();
   graph->GetListOfFunctions()->Add(32);
      tex = new TLatex(0.02030869,0.09536324,"DOCA_{#mu#mu}");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.017);
   tex->SetLineWidth(2);
   tex->Draw();
   graph->GetListOfFunctions()->Add(33);
      tex = new TLatex(0.366561,0.3748077,"L_{xy}");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.0173913);
   tex->SetLineWidth(2);
   tex->Draw();
   graph->GetListOfFunctions()->Add(34);
      tex = new TLatex(0.322187,0.4341483,"N^{clos}_{trk} ACK");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.017);
   tex->SetLineWidth(2);
   tex->Draw();
   graph->GetListOfFunctions()->Add(35);
      tex = new TLatex(0.2877971,0.4801374,"N^{clos}_{trk} BEL Custom");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.017);
   tex->SetLineWidth(2);
   tex->Draw();
   graph->GetListOfFunctions()->Add(36);
      tex = new TLatex(0.2933439,0.4593681,"N^{clos}_{trk} BGL Loose");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.017);
   tex->SetLineWidth(2);
   tex->Draw();
   graph->GetListOfFunctions()->Add(37);
      tex = new TLatex(0.00920498,0.04632637,"P^{min}_{L}");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.017);
   tex->SetLineWidth(2);
   tex->Draw();
   graph->GetListOfFunctions()->Add(38);
      tex = new TLatex(0.4042789,0.4667857,"log(#chi^{2}_{#mu,xPV})");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.017);
   tex->SetLineWidth(2);
   tex->Draw();
   graph->GetListOfFunctions()->Add(39);
      tex = new TLatex(0.2512658,0.3271739,"log(#chi^{2}_{xy})");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.017);
   tex->SetLineWidth(2);
   tex->Draw();
   graph->GetListOfFunctions()->Add(40);
      tex = new TLatex(0.03585388,0.03592461,"p^{B}_{T}");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.017);
   tex->SetLineWidth(2);
   tex->Draw();
   graph->GetListOfFunctions()->Add(41);
      tex = new TLatex(-0.0241061,0.0225509,"|#Delta #phi_{#mu#mu}|");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.017);
   tex->SetLineWidth(2);
   tex->Draw();
   graph->GetListOfFunctions()->Add(42);
      tex = new TLatex(0.52187,0.5750824,"|#alpha_{2D}|");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.017);
   tex->SetLineWidth(2);
   tex->Draw();
   graph->GetListOfFunctions()->Add(43);
      tex = new TLatex(0.07582723,0.1533159,"|IP_{B}^{3D}|");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.017);
   tex->SetLineWidth(2);
   tex->Draw();
   graph->GetListOfFunctions()->Add(44);
      tex = new TLatex(0.1035865,0.1874931,"|d_{0}|^{max} sig.");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.017);
   tex->SetLineWidth(2);
   tex->Draw();
   graph->GetListOfFunctions()->Add(45);
      tex = new TLatex(0.322187,0.3896429,"|d_{0}|^{min} sig.");
   tex->SetTextAlign(13);
   tex->SetTextFont(42);
   tex->SetTextSize(0.017);
   tex->SetLineWidth(2);
   tex->Draw();
   graph->GetListOfFunctions()->Add(46);
   graph->Draw("ap");
   TLine *line = new TLine(0.004912839,0.006153845,0.5950872,0.5951099);

   ci = 1179;
   color = new TColor(ci, 0, 0, 0.8, " ", 0.35);
   line->SetLineColor(ci);
   line->Draw();
      tex = new TLatex(0.2,0.8,"ATLAS");
tex->SetNDC();
   tex->SetTextFont(72);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.3221884,0.8,"Internal");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.05,0.48,"");
   tex->SetTextSize(0.034468);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.05,0.455,"");
   tex->SetTextSize(0.034468);
   tex->SetLineWidth(2);
   tex->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
