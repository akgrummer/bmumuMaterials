import ROOT

ROOT.gROOT.SetBatch()
#*******************************************************
#Get datasets from workspace
#*******************************************************
ifile = ROOT.TFile("./Plots/workspace.root")
wks=ifile.Get("workspace")

data_calibrated = wks.data("data_calibrated")
data_uncalibrated = wks.data("data_uncalibrated")

var_resp = wks.var("var_reco_truth")
#*******************************************************
#Make PDFs
#*******************************************************
var_mean_1 = ROOT.RooRealVar("mean_1", "", 0 -1000, 1000)
var_mean_2 = ROOT.RooRealVar("mean_2", "", 0 -1000, 1000)

var_sigm_1 = ROOT.RooRealVar("sigm_1", "", 100, 500)
var_sigm_2 = ROOT.RooRealVar("sigm_2", "", 100, 500)

var_frg = ROOT.RooRealVar("frg", "", 0, 1)

pdf_gaus_1 = ROOT.RooGaussian("gaus_1", "", var_resp, var_mean_1, var_sigm_1)
pdf_gaus_2 = ROOT.RooGaussian("gaus_2", "", var_resp, var_mean_2, var_sigm_2)
pdf_comb = ROOT.RooGenericPdf("pdf", "", "@0 * @1 + (1-@0) * @2", ROOT.RooArgList(var_frg, pdf_gaus_1, pdf_gaus_2) )

pdf_comb.fitTo(data_calibrated, ROOT.RooFit.Range(-800, 800) )
#*******************************************************
#Save fits
#*******************************************************
plot = var_resp.frame()

data_calibrated.plotOn(plot)
pdf_comb.plotOn(plot, ROOT.RooFit.LineColor(4) )

can_fit = ROOT.TCanvas("can_fit", "", 800, 600)
plot.Draw()
can_fit.SaveAs("Plots/fit.pdf")
#*******************************************************
#*******************************************************

