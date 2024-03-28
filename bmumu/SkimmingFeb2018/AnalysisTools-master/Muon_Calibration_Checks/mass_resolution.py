import ROOT
import os
import sys
import math

import atlas
import utils
import settings

#*******************************************************************************
def pass_cut(entry):
    chi2           = entry.B_fitChi2NDF
    T_mu_minus_eta = entry.TRUTH_MuMinus_eta
    T_mu_plus_eta  = entry.TRUTH_MuPlus_eta
    T_mu_minus_pT  = entry.TRUTH_MuMinus_pT
    T_mu_plus_pT   = entry.TRUTH_MuPlus_pT
    R_mu_minus_eta = entry.Muon1_eta
    R_mu_plus_eta  = entry.Muon2_eta
    R_mu_minus_pT  = entry.Muon1_pT
    R_mu_plus_pT   = entry.Muon2_pT
    R_mu_minus_isCombined  = entry.Muon1_isCombinedMuon
    R_mu_plus_isCombined  = entry.Muon2_isCombinedMuon
    isSignal       = entry.isSignal
    B_pT           = entry.B_pT
    B_eta          = entry.B_eta
    pass_truth_muon = abs( T_mu_minus_eta ) < 2.5 and abs( T_mu_plus_eta ) < 2.5 and T_mu_plus_pT > 3500 and T_mu_minus_pT > 3500
    pass_reco_muon  = abs( R_mu_minus_eta ) < 2.5 and abs( R_mu_plus_eta ) < 2.5 and R_mu_plus_pT > 4000 and R_mu_minus_pT > 4000 and R_mu_minus_isCombined and R_mu_plus_isCombined

    return pass_truth_muon and pass_reco_muon and chi2 < 6 and isSignal and B_pT > 8000 and abs(B_eta) < 2.5
#**********************************************Check number of arguments
if len(sys.argv) < 2:
    print "Argument not introduced"
    exit(1)
#**********************************************
mc_type = sys.argv[1]

OUTPUT="./Plots/"
process = ""
dirname = ""
filename = ""
ROOT.RooDataSet.setDefaultStorageType(ROOT.RooAbsData.Tree)
#**********************************************
#Make output directory
#**********************************************
if not os.path.isdir(OUTPUT):
    os.mkdir(OUTPUT)
#**********************************************
#Read files
#**********************************************
ROOT.gROOT.SetBatch()

chain_calibrated   = ROOT.TChain("T_mv")
chain_uncalibrated = ROOT.TChain("T_mv")

if mc_type == "Bsmumu":
    chain_calibrated  .Add(settings.CALI_BMUMU_DIR + settings.CALI_BMUMU_FIL)
    chain_uncalibrated.Add(settings.UCAL_BMUMU_DIR + settings.CALI_BMUMU_FIL)
    PROCESS=settings.BMUMU_PROC
elif mc_type == "Bplus":
    chain_calibrated  .Add(settings.CALI_BPLUS_DIR + settings.CALI_BPLUS_FIL)
    chain_uncalibrated.Add(settings.UCAL_BPLUS_DIR + settings.CALI_BPLUS_FIL)
    PROCESS=settings.BPLUS_PROC
else:
    exit(1)
#**********************************************
var_reco_mass  = ROOT.RooRealVar("var_reco_mass" , "Truth", 0, 10000)
var_truth_mass = ROOT.RooRealVar("var_truth_mass", "Reconstructed", 0, 10000)
var_reco_truth = ROOT.RooRealVar("var_reco_truth", "Reconstructed - Truth [MeV]", -1010, 1010)

variables = ROOT.RooArgSet(var_reco_truth, var_truth_mass, var_reco_mass)

data_calibrated   = ROOT.RooDataSet("data_calibrated"  , "", variables)
data_uncalibrated = ROOT.RooDataSet("data_uncalibrated", "", variables)
#**********************************************
#Fill dataset with (reco-truth, reco, truth)
#Calibrated
#**********************************************
for i_entry, entry in enumerate(chain_calibrated):
    if i_entry % 1000 == 0:
        print "1. Processing %d events." % i_entry

    if not pass_cut(entry):
        continue

    reco_mass  = entry.B_MUCALC_mass
    truth_mass = entry.TRUTH_B_mass

    var_reco_truth.setVal( reco_mass - truth_mass )
    var_reco_mass.setVal( reco_mass )
    var_truth_mass.setVal( truth_mass )

    data_calibrated.add(variables)
#**********************************************
#Uncalibrated
#**********************************************
for i_entry, entry in enumerate(chain_uncalibrated):
    if i_entry % 1000 == 0:
        print "2. Processing %d events." % i_entry

    if not pass_cut(entry):
        continue

    reco_mass  = entry.B_MUCALC_mass
    truth_mass = entry.TRUTH_B_mass

    var_reco_truth.setVal( reco_mass - truth_mass )
    var_reco_mass.setVal( reco_mass )
    var_truth_mass.setVal( truth_mass )

    data_uncalibrated.add(variables)
#**********************************************
#Get Mean and RMS, with corresponding errors
#for calibrated and uncalibrated
#**********************************************
var_mean_c = data_calibrated.meanVar(var_reco_truth, "var_reco_truth > -500 && var_reco_truth < 500")
c_mean     = var_mean_c.getVal()
c_mean_e   = var_mean_c.getError()

var_rms_c  = data_calibrated.rmsVar(var_reco_truth, "var_reco_truth > -500 && var_reco_truth < 500")
c_rms      = var_rms_c.getVal()
c_rms_e    = var_rms_c.getError()
#***************
var_mean_u = data_uncalibrated.meanVar(var_reco_truth, "var_reco_truth > -500 && var_reco_truth < 500")
u_mean     = var_mean_u.getVal()
u_mean_e   = var_mean_u.getError()

var_rms_u  = data_uncalibrated.rmsVar(var_reco_truth, "var_reco_truth > -500 && var_reco_truth < 500")
u_rms      = var_rms_u.getVal()
u_rms_e    = var_rms_u.getError()
#**********************************************
#Print values
#**********************************************
print "Uncalibrated Mean %.5f+-%.5f, RMS %.5f+-%.5f" % (u_mean, u_mean_e, u_rms, u_rms_e)
print "Calibrated Mean %.5f+-%.5f, RMS %.5f+-%.5f" % (c_mean, c_mean_e, c_rms, c_rms_e)

if mc_type == "Bsmumu":
    print "$B_{s}^{0}\\rightarrow \mu^{+} \mu^{-}$ & $%.3f \pm %.3f$ & $%.3f \pm %.3f$    & $%.3f \pm %.3f$   & $%.3f \pm %.3f$" % (c_mean, c_mean_e, c_rms, c_rms_e, u_mean, u_mean_e, u_rms, u_rms_e)
elif mc_type == "Bplus":
    print "$B^{+}\\rightarrow J/\psi + K^{+}$      & $%.3f \pm %.3f$ & $%.3f \pm %.3f$    & $%.3f \pm %.3f$   & $%.3f \pm %.3f$" % (c_mean, c_mean_e, c_rms, c_rms_e, u_mean, u_mean_e, u_rms, u_rms_e)
#**********************************************
#Plot reco - truth distribution
#**********************************************
plot = var_reco_truth.frame()

data_calibrated.plotOn(plot, ROOT.RooFit.MarkerColor(2), ROOT.RooFit.LineColor(2), ROOT.RooFit.Name("data_calibrated"), ROOT.RooFit.Binning(100, -1000, 1000) )
data_uncalibrated.plotOn(plot, ROOT.RooFit.MarkerColor(4), ROOT.RooFit.LineColor(4), ROOT.RooFit.Name("data_uncalibrated"), ROOT.RooFit.Binning(100, -1000, 1000) )

d_objects = dict()
d_objects["Calibrated"]   = plot.findObject("data_calibrated")
d_objects["Uncalibrated"] = plot.findObject("data_uncalibrated")

can_resolution = ROOT.TCanvas("can_resolution", "", 800, 600)

plot.Draw()
legend = utils.GetLegend(0.6, 0.80, 0.9, 1.0, d_objects)
legend.Draw()
utils.ReformatCanvas(can_resolution)
utils.ReformatRooPlot(plot, [], ["data_calibrated", "data_uncalibrated"])
utils.ATLASLabel(0.2, 0.86, "Simulation", 1, can_resolution, process)

can_resolution.SaveAs("%s/distribution_%s.pdf" % (OUTPUT, mc_type) )
#**********************************************
