import math

import ROOT

import atlas
import utils
import settings

ROOT.gROOT.SetBatch()
PI=math.pi
utils.RATIO_LOW=0.5
utils.RATIO_HIGH=1.5
#*********************************
#Calculate cali-orig difference
#*********************************
def deviation(entry):
    dev = max(entry.pt_dev, entry.eta_dev, entry.phi_dev)

    return dev
#*********************************
#Apply cuts
#*********************************
def pass_cuts(entry):
    return (entry.pt_orig > 4000) and (abs(entry.eta_orig) < 2.5)
#*********************************
#Define variables
#*********************************
FILES="/nfs/monet_3/home/campoverde/Data/Trees/Muon_Calibration_Tests/*.root"
TOLERANCE=0.05
#PREFIX="large_dev"
PREFIX="small_dev"
#*********************************
#Open files
#*********************************
ch_calibration=ROOT.TChain("tree", "")
ch_calibration.Add("%s/%s" % (settings.KIN_DIRNAME, settings.KIN_FILENAME) )
#*********************************
#Make histograms
#*********************************
h_pt_orig =utils.GetHistogram("h_pt_orig", "Original p_{T}"  , 4, 100, 3000, 40000, title_x="p_{T}", title_y = "Entries/0.05")
h_pt_cali =utils.GetHistogram("h_pt_cali", "Calibrated p_{T}", 2, 100, 3000, 40000, title_x="p_{T}", title_y = "Entries/0.05")

h_eta_orig=utils.GetHistogram("h_eta_orig", "Original #eta"  , 4, 100, -2.5, +2.5, title_x="#eta", title_y = "Entries/0.05")
h_eta_cali=utils.GetHistogram("h_eta_cali", "Calibrated #eta", 2, 100, -2.5, +2.5, title_x="#eta", title_y = "Entries/0.05")

h_phi_orig=utils.GetHistogram("h_phi_orig", "Original #phi"  , 4, 100, -PI, +PI, title_x="#phi", title_y = "Entries/0.05")
h_phi_cali=utils.GetHistogram("h_phi_cali", "Calibrated #phi", 2, 100, -PI, +PI, title_x="#phi", title_y = "Entries/0.05")

h_deviation  =utils.GetHistogram("h_deviation"  , "Deviation"  , 4, 100, 0, 500, title_x="Dev", title_y = "Entries/0.2")
#*********************************
#Fill histograms
#*********************************
for i_entry, entry in enumerate(ch_calibration):
    dev = deviation(entry)

    h_deviation.Fill(dev)

    if not pass_cuts(entry):
        continue

    if   PREFIX == "large_dev" and (deviation(entry) < TOLERANCE):
        continue
    elif PREFIX == "small_dev" and (deviation(entry) > TOLERANCE):
        continue

    h_pt_orig.Fill(entry.pt_orig)
    h_pt_cali.Fill(entry.pt_cali)

    h_eta_orig.Fill(entry.eta_orig)
    h_eta_cali.Fill(entry.eta_cali)

    h_phi_orig.Fill(entry.phi_orig)
    h_phi_cali.Fill(entry.phi_cali)
#*********************************
#Fill Q-deviation
#*********************************
h_deviation.Scale(1./h_deviation.Integral())

h_q_deviation=h_deviation.GetCumulative(False)
h_q_deviation.SetTitle("Q-Deviation")
h_q_deviation.SetLineColor(2)
h_q_deviation.SetMarkerColor(2)

h_deviation.GetXaxis().SetRangeUser(0, 100)
h_deviation.GetXaxis().SetRangeUser(0, 100)
#*********************************
#Save plots
#*********************************
utils.SaveHistograms([h_pt_orig, h_pt_cali],   "kinematics/%s_muon_pt"  % PREFIX, "Simulation", "Tol=%.3f" % TOLERANCE, log=True, legend=1, ratio=True)
utils.SaveHistograms([h_eta_orig, h_eta_cali], "kinematics/%s_muon_eta" % PREFIX, "Simulation", "Tol=%.3f" % TOLERANCE, legend=1, ratio=True)
utils.SaveHistograms([h_phi_orig, h_phi_cali], "kinematics/%s_muon_phi" % PREFIX, "Simulation", "Tol=%.3f" % TOLERANCE, legend=1, ratio=True)

utils.SaveHistograms([h_deviation, h_q_deviation], "kinematics/deviation", "Simulation", "", log=True, legend=1)
#*********************************
#*********************************

