import ROOT

import os
import json

import atlas
import utils
#******************************************
#Return histogram with 50 bins, from 0 to 50
#******************************************
def get_rebinned_hist(hist, name, title):
    nbins=hist.GetNbinsX()

    if nbins < 50:
        print("Insuficient number of bins: %d" % nbins)
        exit(1)

    h_rebinned=ROOT.TH1F(name, title, 50, 0, 50)

    for i_bin in range(1, 51):
        bc=hist.GetBinContent(i_bin)
        be=hist.GetBinError(i_bin)
        
        h_rebinned.SetBinContent(i_bin, bc)
        h_rebinned.SetBinError(i_bin, be)

    return h_rebinned
#******************************************
#Do preliminary checks
#******************************************
def check():
    if not os.path.isdir(JSON_DIR):
        print("Cannot find directory %s." % JSON_DIR)
        exit(1)

    if not os.path.isfile("%s/%s" % (JSON_DIR, IWEIGHT_FILE) ):
        print("Cannot find %s/%s." % (JSON_DIR, IWEIGHT_FILE) )
        exit(1)

    if not os.path.isdir(HIST_DIR):
        print("Cannot find directory %s." % HIST_DIR)
        exit(1)

    if not os.path.isfile("%s/%s" % (HIST_DIR, HIST_DATA) ):
        print("Cannot find %s/%s." % (HIST_DIR, HIST_DATA) )
        exit(1)

    if not os.path.isfile("%s/%s" % (HIST_DIR, HIST_MC) ):
        print("Cannot find %s/%s." % (HIST_DIR, HIST_MC) )
        exit(1)
        
    if not os.path.isdir(REWEIGHT_DIR):
        os.mkdir(REWEIGHT_DIR)
#******************************************
#Set variables
#******************************************
ROOT.gROOT.SetBatch()

JSON_DIR="json"
IWEIGHT_FILE="mu_wgt.json"
OWEIGHT_FILE="mu_wgt_last.json"
HIST_DIR="hist"
HIST_DATA="hist_data.root"
HIST_MC="hist_mc.root"
REWEIGHT_DIR="reweight"

check()
#******************************************
#Read histograms
#******************************************
ifile_data=ROOT.TFile("%s/%s" % (HIST_DIR, HIST_DATA) )
h_mu_data_org=ifile_data.Get("h_2015_2016")
h_mu_data=h_mu_data_org.Rebin(10, "h_2015_2016_rebinned")
h_mu_data.SetTitle("Data, 2015+2016")
h_mu_data.SetDirectory(0)
ifile_data.Close()

ifile_mc=ROOT.TFile("%s/%s" % (HIST_DIR, HIST_MC) )
h_mu_mc_orig=ifile_mc.Get("pileup_chan300426_run284500")
h_mu_mc=get_rebinned_hist(h_mu_mc_orig, "h_mu_mc", "B_{s}#rightarrow#mu#mu")
h_mu_mc.SetDirectory(0)
ifile_mc.Close()
#******************************************
#Read JSON weights file
#******************************************
ifile=open("%s/%s" % (JSON_DIR, IWEIGHT_FILE))
d_mu_wgt=json.load(ifile)
ifile.close()
#******************************************
#Reweight
#******************************************
nbins=h_mu_mc.GetNbinsX()
h_mu_mc_reweighted=h_mu_mc.Clone("mu_mc_reweighted")
h_mu_mc_reweighted.SetTitle("B_{s}#rightarrow#mu#mu Reweighted")

for i_bin in range(1, 40):
    bin_content = h_mu_mc.GetBinContent(i_bin)
    mu=int(h_mu_mc.GetBinLowEdge(i_bin))
    weight=d_mu_wgt[str(mu)]

    h_mu_mc_reweighted.SetBinContent(i_bin, bin_content * weight)
#******************************************
#Save plots
#******************************************
h_mu_data.SetLineColor(1)
h_mu_mc.SetLineColor(2)
h_mu_mc_reweighted.SetLineColor(4)

h_mu_data.SetMarkerColor(1)
h_mu_mc.SetMarkerColor(2)
h_mu_mc_reweighted.SetMarkerColor(4)

h_mu_data.GetXaxis().SetRangeUser(0, 45)
h_mu_mc.GetXaxis().SetRangeUser(0, 45)
h_mu_mc_reweighted.GetXaxis().SetRangeUser(0, 45)

l_hist=[h_mu_data, h_mu_mc, h_mu_mc_reweighted]

utils.SaveHistograms(l_hist, "%s/reweight" % REWEIGHT_DIR, "Internal", "", normalize=True, legend=1, ratio=True)
#******************************************
#Calculate weights
#******************************************
d_imu_wgt=dict()

for i_bin in range(1, 51):
    bc_data = h_mu_data.GetBinContent(i_bin)
    bc_mc   = h_mu_mc.GetBinContent(i_bin)

    if bc_mc <= 0:
        print("Bin content %.3f for MC at bin %d, skipping." % (bc_mc, i_bin) )
        continue

    weight=bc_data/bc_mc
    i_mu  = i_bin - 1
    d_imu_wgt[i_mu]=weight
    
ofile=open("%s/%s" % (JSON_DIR, OWEIGHT_FILE), "w")
json.dump(d_imu_wgt, ofile)
ofile.close()
#******************************************
#******************************************

