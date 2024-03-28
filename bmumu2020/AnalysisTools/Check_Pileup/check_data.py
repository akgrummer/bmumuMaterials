import os
import sys

import ROOT

import atlas
import utils
import tools

#***********************************
#Returns histogram with pileup
#***********************************
def get_pileup_hist(year):
    color=1
    title=""
    if year == 2015:
        filename = "%s/%s" % (DATA_PATH, LUMI_2015)
        color=4
        title="2015"
    else:
        filename = "%s/%s" % (DATA_PATH, LUMI_2016)
        color=2
        title="2016"

    ifile = ROOT.TFile("%s" % filename)

    h_mu=ifile.Get(mu_hist)
    h_mu.SetLineColor(color)
    h_mu.SetMarkerColor(color)
    h_mu.SetTitle(title)
    h_mu.SetName("h_%s" % title)
    h_mu.SetFillColor(0)
    h_mu.SetDirectory(0)

    ifile.Close()

    return h_mu
#***********************************
#Set paths
#***********************************
DATA_PATH="/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/GoodRunsLists/"

LUMI_2015="data15_13TeV/20160720/physics_25ns_20.7.lumicalc.OflLumi-13TeV-005.root" 
LUMI_2016="data16_13TeV/20170720/physics_25ns_20.7.lumicalc.OflLumi-13TeV-009.root" 

mu_hist="avgintperbx"
#***********************************
#Make plots/hist directory
#***********************************
PLOT_DIR="plots_data"
HIST_DIR="hist"

if not os.path.isdir(PLOT_DIR):
    os.mkdir(PLOT_DIR)

if not os.path.isdir(HIST_DIR):
    os.mkdir(HIST_DIR)
#***********************************
#Plot histograms
#***********************************
ROOT.gROOT.SetBatch()

h_mu_2015=get_pileup_hist(2015)
h_mu_2015.Rebin(10)
print("2015 bin width %.3f" % h_mu_2015.GetBinWidth(1) )
print("2015 area %.3f" % h_mu_2015.Integral() )

h_mu_2016=get_pileup_hist(2016)
h_mu_2016.Rebin(10)
print("2016 bin width %.3f" % h_mu_2016.GetBinWidth(1) )
print("2016 area %.3f" % h_mu_2016.Integral() )

utils.SaveHistograms([h_mu_2015], "%s/mu_2015" % PLOT_DIR, "", "")
utils.SaveHistograms([h_mu_2016], "%s/mu_2016" % PLOT_DIR, "", "")
utils.SaveHistograms([h_mu_2015, h_mu_2016], "%s/mu_2015_2016" % PLOT_DIR, "", "", legend=1)

h_mu_2015_2016=h_mu_2015.Clone()
h_mu_2015_2016.SetTitle("2015+2016")
h_mu_2015_2016.Add(h_mu_2015, h_mu_2016)
h_mu_2015_2016.SetName("h_2015_2016")
h_mu_2015_2016.SetLineColor(1)

utils.MAX_NSCALE=0.8
utils.SaveHistograms([h_mu_2015, h_mu_2016, h_mu_2015_2016], "%s/mu_2015_plus_2016" % PLOT_DIR, "Internal", "Data", legend=1)
#***********************************
#Save as ROOT
#***********************************
ofile=ROOT.TFile("%s/hist_data.root" % HIST_DIR, "recreate")
h_mu_2015.Write()
h_mu_2016.Write()
h_mu_2015_2016.Write()
ofile.Close()
#***********************************
#***********************************
