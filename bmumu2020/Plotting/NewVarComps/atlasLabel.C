void atlasLabel(Double_t x,Double_t y, bool drawRes = true, bool Preliminary=true,Color_t color=1, bool drawEnergy=true, bool drawLumi=false, bool enlarge=true, TString h1title = "")
{
  double delx = 0.115*696*gPad->GetWh()*3/(5*472*gPad->GetWw());
  double textsize;
  double dy = 0.065;
  if (!drawRes) {
    if (enlarge) {
      textsize = 0.055; 
      delx+=0.03;
      dy = 0.065;
      // dy = 0.1;
    }
    else textsize = 0.06;
    delx+=0.04;
  }
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
    if (h1title.Contains("fabs_a_2D")) tex = new TLatex(0.5,0.55,"#sqrt{s} = 13 TeV, 26.3 fb^{-1}");
    else if (h1title.Contains("B_IDtrks_DCA")) tex = new TLatex(0.58,0.66,"#sqrt{s} = 13 TeV, 26.3 fb^{-1}");
    else if (h1title.Contains("chi2_PVSV_log2D")) tex = new TLatex(0.56,0.77,"#sqrt{s} = 13 TeV, 26.3 fb^{-1}");
    else if (h1title.Contains("B_iso_7_Chi2_5_LoosePt05")) tex = new TLatex(0.2,0.68,"#sqrt{s} = 13 TeV, 26.3 fb^{-1}");
    else tex = new TLatex(x+0.01,y-dy,"#sqrt{s} = 13 TeV, 26.3 fb^{-1}");
    tex->SetNDC();
    tex->SetTextSize(textsize);
    tex->SetTextFont(42);
    tex->SetLineWidth(2);
    tex->SetTextColor(color);
    // tex->Draw();
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