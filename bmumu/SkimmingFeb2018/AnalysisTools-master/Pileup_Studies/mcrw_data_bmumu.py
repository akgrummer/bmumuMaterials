import ROOT

import os
import sys
import atlas
import utils

ROOT.gROOT.SetBatch()
utils.RATIO_LOW=0.8
utils.RATIO_HIGH=1.2
l_TYPE=["xaod_fixed", "xaod", "xaod_same_trigger", "xaod_2015", "xaod_2016", "dxaod", "dxaod_same_trigger", "dxaod_2015", "dxaod_2016"]
#*****************************************************
def precheck():
    if len(sys.argv) < 2:
        print("Usage:")
        print("       mcrw_data.py TYPE")
        exit(1)

    TYPE=sys.argv[1]
    if TYPE not in l_TYPE:
        print("Wrong type, use %s" % l_TYPE)
        exit(1)
#*****************************************************
def check():
    if not os.path.isdir(PLOTS_DIR):
        os.mkdir(PLOTS_DIR)

    if not os.path.isdir(DIRNAME):
        print("Cannot find directory \"%s\"" % DIRNAME)
        exit(1)

    if not os.path.isdir(LUMIDIR):
        print("Cannot find directory \"%s\"" % LUMIDIR)
        exit(1)
#*****************************************************
precheck()
TYPE=sys.argv[1]

PLOTS_DIR="plots_%s" % TYPE
PROC_BSMUMU="B_{s}^{0}#rightarrow#mu^{+}#mu^{-}"
LUMIDIR="/nfs/monet_3/home/campoverde/Data/Trees/Lumifiles_2015_2016/"

if TYPE == "xaod_fixed":
    DIRNAME="/nfs/monet_3/home/campoverde/Data/Pileup_Tester_300307_xAOD/fetch/"

check()
#*****************************************************
chain=ROOT.TChain("tree")
chain.Add("%s/hist-*.root" % DIRNAME)

h_mu_cw_2015=utils.GetHistogram("h_mu_cw_2015", "MC 2015", 2, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")
h_mu_cw_2016=utils.GetHistogram("h_mu_cw_2016", "MC 2016", 2, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")

chain.Draw("mu >> h_mu_cw_2015", "cwt*trigger*(RunNumber <= 284484)")
chain.Draw("mu >> h_mu_cw_2016", "cwt*trigger*(RunNumber >  284484)")

h_mu_cw=h_mu_cw_2016.Clone("h_mu_cw")
h_mu_cw.SetTitle("MC 2015+2016")
h_mu_cw.Add(h_mu_cw_2015, h_mu_cw_2016)
h_mu_cw.SetLineColor(2)

mc_entries=chain.GetEntries()
print("MC entries %d" % mc_entries)
#*****************************************************
h_mu_dt_2015=utils.GetHistogram("h_mu_dt_2015", "Data 2015", 1, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")

ifile_2015=ROOT.TFile("%s/Lumifile_2015_HLT_mu6_mu4_bBmumu.root" % LUMIDIR)
tree_dt_2015=ifile_2015.Get("LumiMetaData")
for entry in tree_dt_2015:
    h_mu_dt_2015.Fill(entry.AvergeInteractionPerXing, entry.IntLumi)

ifile_2015.Close()
#************
h_mu_dt_2016=utils.GetHistogram("h_mu_dt_2016", "Data 2016", 1, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")

if "same_trigger" in TYPE:
    LUMIFILE="%s/Lumifile_2016_HLT_mu6_mu4_bBmumu.root" % LUMIDIR
else:
    LUMIFILE="%s/Lumifile_2016_HLT_mu6_mu4_bBmumu_Lxy0.root" % LUMIDIR

ifile_2016=ROOT.TFile(LUMIFILE)
tree_dt_2016=ifile_2016.Get("LumiMetaData")
for entry in tree_dt_2016:
    h_mu_dt_2016.Fill(entry.AvergeInteractionPerXing, entry.IntLumi)

ifile_2016.Close()

h_mu_dt = h_mu_dt_2016.Clone("h_mu_dt")
h_mu_dt.SetTitle("Data 2015+2016")
h_mu_dt.Add(h_mu_dt_2015, h_mu_dt_2016, 1, 1)
#*****************************************************
h_mu_dt_2015.GetXaxis().SetRangeUser(7, 20)
h_mu_cw_2015.GetXaxis().SetRangeUser(7, 20)

utils.SaveHistograms([h_mu_dt_2015, h_mu_cw_2015], "./%s/mcrw_dt_2015" % PLOTS_DIR, "Internal", PROC_BSMUMU, legend=1, normalize=True, ratio=True)
utils.SaveHistograms([h_mu_dt_2016, h_mu_cw_2016], "./%s/mcrw_dt_2016" % PLOTS_DIR, "Internal", PROC_BSMUMU, legend=1, normalize=True, ratio=True)
utils.SaveHistograms([h_mu_dt     , h_mu_cw     ], "./%s/mcrw_dt"      % PLOTS_DIR, "Internal", PROC_BSMUMU, legend=1, normalize=True, ratio=True)
#*****************************************************
h_mu_cw_2015.SetLineColor(2)
h_mu_cw_2015.SetMarkerColor(2)

h_mu_cw_2016.SetLineColor(4)
h_mu_cw_2016.SetMarkerColor(4)

h_mu_cw.SetLineColor(1)
h_mu_cw.SetMarkerColor(1)

utils.SaveHistograms([h_mu_cw, h_mu_cw_2015, h_mu_cw_2016], "./%s/mcrw" % PLOTS_DIR, "Internal", PROC_BSMUMU, legend=1)
#*****************************************************
h_mu_dt_2015.SetLineColor(2)
h_mu_dt_2015.SetMarkerColor(2)

h_mu_dt_2016.SetLineColor(4)
h_mu_dt_2016.SetMarkerColor(4)

utils.SaveHistograms([h_mu_dt, h_mu_dt_2015, h_mu_dt_2016], "./%s/data" % PLOTS_DIR, "Internal", PROC_BSMUMU, legend=1)
#*****************************************************

