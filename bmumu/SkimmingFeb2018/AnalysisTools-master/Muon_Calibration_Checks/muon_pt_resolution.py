#!/usr/bin/python

import ROOT
import sys
import os

import utils
import atlas
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

ROOT.gROOT.SetBatch()
OUTPUT="./Plots/"
ROOT.RooDataSet.setDefaultStorageType(ROOT.RooAbsData.Tree)
#**********************************************
#Make output directory
#**********************************************
if not os.path.isdir(OUTPUT):
    os.mkdir(OUTPUT)
#**********************************************
#Read files
#**********************************************
chain   = ROOT.TChain("T_mv")

if mc_type == "Bsmumu":
    chain.Add(settings.CALI_BMUMU_DIR + settings.CALI_BMUMU_FIL)
    PROCESS=settings.BMUMU_PROC
elif mc_type == "Bplus":
    chain.Add(settings.CALI_BPLUS_DIR + settings.CALI_BPLUS_FIL)
    PROCESS=settings.BPLUS_PROC
else:
    exit(1)
#**********************************************
#Make dataset
#**********************************************
var_reco_pt    = ROOT.RooRealVar("var_reco_pt" , "Truth", 4000, 40000)
var_truth_pt   = ROOT.RooRealVar("var_truth_pt", "Reconstructed", 4000, 40000)
var_reco_truth = ROOT.RooRealVar("var_reco_truth", "Reconstructed - Truth [MeV]", -1010, 1010)

variables = ROOT.RooArgSet(var_reco_truth, var_truth_pt, var_reco_pt)

data_calibrated   = ROOT.RooDataSet("data_calibrated"  , "", variables)
data_uncalibrated = ROOT.RooDataSet("data_uncalibrated", "", variables)
#**********************************************
# upper_bound = 10000
#**********************************************
for i_entry, entry in enumerate(chain):
    if i_entry % 1000 == 0:
        print "Processing %d events." % i_entry

    if not pass_cut(entry):
        continue
    #*****************************************
    Muon1_pT         = entry.Muon1_pT
    Muon2_pT         = entry.Muon2_pT
    TRUTH_MuPlus_pT  = entry.TRUTH_MuPlus_pT
    TRUTH_MuMinus_pT = entry.TRUTH_MuMinus_pT
    Muon1_pT_orig    = entry.Muon1_pT_orig
    Muon2_pT_orig    = entry.Muon2_pT_orig
    #*****************************************
    var_reco_truth.setVal( Muon1_pT - TRUTH_MuPlus_pT )
    var_reco_pt.setVal( Muon1_pT )
    var_truth_pt.setVal( TRUTH_MuPlus_pT )

    data_calibrated.add(variables)
    #*****************************************
    var_reco_truth.setVal( Muon2_pT - TRUTH_MuMinus_pT )
    var_reco_pt.setVal( Muon2_pT )
    var_truth_pt.setVal( TRUTH_MuMinus_pT )

    data_calibrated.add(variables)
    #*****************************************
    #*****************************************
    var_reco_truth.setVal( Muon1_pT_orig - TRUTH_MuPlus_pT )
    var_reco_pt.setVal( Muon1_pT_orig )
    var_truth_pt.setVal( TRUTH_MuPlus_pT )

    data_uncalibrated.add(variables)
    #*****************************************
    var_reco_truth.setVal( Muon2_pT_orig - TRUTH_MuMinus_pT )
    var_reco_pt.setVal( Muon2_pT_orig )
    var_truth_pt.setVal( TRUTH_MuMinus_pT )

    data_uncalibrated.add(variables)
#**********************************************
#Get mean and RMS (also errors) for reco-truth pt
#**********************************************
var_mean_c = data_calibrated.meanVar(var_reco_truth, "var_reco_truth > -1000 && var_reco_truth < 1000")
c_mean     = var_mean_c.getVal()
c_mean_e   = var_mean_c.getError()

var_rms_c  = data_calibrated.rmsVar(var_reco_truth, "var_reco_truth > -1000 && var_reco_truth < 1000")
c_rms      = var_rms_c.getVal()
c_rms_e    = var_rms_c.getError()
#******
var_mean_u = data_uncalibrated.meanVar(var_reco_truth, "var_reco_truth > -1000 && var_reco_truth < 1000")
u_mean     = var_mean_u.getVal()
u_mean_e   = var_mean_u.getError()

var_rms_u  = data_uncalibrated.rmsVar(var_reco_truth, "var_reco_truth > -1000 && var_reco_truth < 1000")
u_rms      = var_rms_u.getVal()
u_rms_e    = var_rms_u.getError()
#**********************************************
if mc_type == "Bsmumu":
    print "$B_{s}^{0}\\rightarrow \mu^{+} \mu^{-}$ & $%.3f \pm %.3f$ & $%.3f \pm %.3f$    & $%.3f \pm %.3f$   & $%.3f \pm %.3f$" % (c_mean, c_mean_e, c_rms, c_rms_e, u_mean, u_mean_e, u_rms, u_rms_e)
elif mc_type == "Bplus":
    print "$B^{+}\\rightarrow J/\psi + K^{+}$      & $%.3f \pm %.3f$ & $%.3f \pm %.3f$    & $%.3f \pm %.3f$   & $%.3f \pm %.3f$" % (c_mean, c_mean_e, c_rms, c_rms_e, u_mean, u_mean_e, u_rms, u_rms_e)
#**********************************************
#Save workspace
#**********************************************
ofile = ROOT.TFile("%s/workspace.root" % OUTPUT, "recreate")

workspace = ROOT.RooWorkspace("workspace")
getattr(workspace,'import')(data_calibrated)
getattr(workspace,'import')(data_uncalibrated)

workspace.Write()

ofile.Close()
#**********************************************
#Save plots
#**********************************************
plot = var_reco_truth.frame()
data_uncalibrated.plotOn(plot, ROOT.RooFit.MarkerColor(4), ROOT.RooFit.LineColor(4), ROOT.RooFit.Name("data_uncalibrated") )
data_calibrated  .plotOn(plot, ROOT.RooFit.MarkerColor(2), ROOT.RooFit.LineColor(2), ROOT.RooFit.Name("data_calibrated") )

d_objects = dict()
d_objects["Calibrated"]   = plot.findObject("data_calibrated")
d_objects["Uncalibrated"] = plot.findObject("data_uncalibrated")

can_ptresp = ROOT.TCanvas("can_ptresp", "", 800, 600)
plot.Draw()
legend = utils.GetLegend(0.6, 0.80, 0.9, 1.0, d_objects)
legend.Draw()
utils.ReformatCanvas(can_ptresp)
utils.ReformatRooPlot(plot, [], ["data_calibrated", "data_uncalibrated"])
utils.ATLASLabel(0.2, 0.86, "Simulation", 1, can_ptresp, PROCESS)

can_ptresp.SaveAs("%s/ptresp_%s.pdf"  % (OUTPUT, mc_type) )
can_ptresp.SaveAs("%s/ptresp_%s.root" % (OUTPUT, mc_type) )
#**********************************************
