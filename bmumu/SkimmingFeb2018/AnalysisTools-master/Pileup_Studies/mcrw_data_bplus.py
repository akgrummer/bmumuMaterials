import ROOT

import os
import sys
import atlas
import utils

ROOT.gROOT.SetBatch()
utils.RATIO_LOW=0.8
utils.RATIO_HIGH=1.2
l_TYPE=["xaod_bp_fixed"]
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
LUMIDIR="/nfs/monet_3/home/campoverde/Data/Trees/Lumifiles_2015_2016/"
PROC="B^{+}#rightarrowJ/#psi+K^{+}"
DIRNAME=""

l_lumifiles_2015=list()
l_lumifiles_2016=list()

if TYPE == "xaod_bp_fixed":
    DIRNAME="/nfs/monet_3/home/campoverde/Data/user.acampove.data_pileup_test_004.merge.AOD_hist/"
    l_lumifiles_2015 = ["Lumifile_2015_HLT_mu6_mu4_bJpsimumu.root"]
    l_lumifiles_2016 = ["Lumifile_2016_HLT_mu6_mu4_bJpsimumu_Lxy0.root"]
    l_lumifiles_2016 = ["Lumifile_2016_HLT_mu6_mu4_bJpsimumu_Lxy0.root", "Lumifile_2016_HLT_mu6_mu4_bJpsimumu_Lxy0_delayed.root"]

check()
#*****************************************************
#Fill MC histograms
#*****************************************************
chain=ROOT.TChain("tree")
chain.Add("%s/*.root" % DIRNAME)

h_mu_cw          =utils.GetHistogram("h_mu_cw"          , "MC 2015 + 2016"  , 2, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")
h_mu_cw_2015     =utils.GetHistogram("h_mu_cw_2015"     , "MC 2015"         , 2, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")
h_mu_cw_2016     =utils.GetHistogram("h_mu_cw_2016"     , "MC 2016"         , 2, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")
h_mu_cw_2016_main=utils.GetHistogram("h_mu_cw_2016_main", "MC 2016, Main"   , 2, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")
h_mu_cw_2016_dely=utils.GetHistogram("h_mu_cw_2016_dely", "MC 2016, Delayed", 2, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")

chain.Draw("mu >> h_mu_cw_2015"     , "cwt*trigger*(RunNumber <= 284484)")
chain.Draw("mu >> h_mu_cw_2016_main", "cwt*trigger*(RunNumber >  284484 && RunNumber < 302956)")
chain.Draw("mu >> h_mu_cw_2016_dely", "cwt*trigger*(RunNumber >= 302956)")

h_mu_cw_2016.Add(h_mu_cw_2016_main, h_mu_cw_2016_dely)
h_mu_cw.Add(h_mu_cw_2015, h_mu_cw_2016)

mc_entries=chain.GetEntries()
print("MC entries %d" % mc_entries)
#*****************************************************
#Fill data histograms
#*****************************************************
h_mu_dt_2015=utils.GetHistogram("h_mu_dt_2015", "Data 2015", 1, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")

chain_dt_2015=ROOT.TChain("LumiMetaData")
for FILE in l_lumifiles_2015:
    chain_dt_2015.Add("%s/%s" % (LUMIDIR, FILE) )

for entry in chain_dt_2015:
    h_mu_dt_2015.Fill(entry.AvergeInteractionPerXing, entry.IntLumi)
#************
h_mu_dt          =utils.GetHistogram("h_mu_dt"          , "Data 2015 + 2016"   , 1, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")
h_mu_dt_2016     =utils.GetHistogram("h_mu_dt_2016"     , "Data 2016"          , 1, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")
h_mu_dt_2016_main=utils.GetHistogram("h_mu_dt_2016_main", "Data 2016, Main"    , 1, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")
h_mu_dt_2016_dely=utils.GetHistogram("h_mu_dt_2016_dely", "Data 2016, Delayed" , 1, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")

chain_dt_2016=ROOT.TChain("LumiMetaData")
for FILE in l_lumifiles_2016:
    chain_dt_2016.Add("%s/%s" % (LUMIDIR, FILE) )

for entry in chain_dt_2016:
    run_number=entry.RunNbr

    if run_number < 302956:
        h_mu_dt_2016_main.Fill(entry.AvergeInteractionPerXing, entry.IntLumi)
    else:
        h_mu_dt_2016_dely.Fill(entry.AvergeInteractionPerXing, entry.IntLumi)
#************
h_mu_dt_2016.Add(h_mu_dt_2016_main, h_mu_dt_2016_dely)
h_mu_dt.Add(h_mu_dt_2015, h_mu_dt_2016)
#*****************************************************
#Save DATA/MC comparisons
#*****************************************************
h_mu_dt_2015.GetXaxis().SetRangeUser(7, 20)
h_mu_cw_2015.GetXaxis().SetRangeUser(7, 20)

utils.SaveHistograms([h_mu_dt_2015, h_mu_cw_2015], "./%s/mcrw_dt_2015" % PLOTS_DIR, "Internal", PROC, legend=1, normalize=True, ratio=True)

utils.SaveHistograms([h_mu_dt_2016_main, h_mu_cw_2016_main], "./%s/mcrw_dt_2016_main" % PLOTS_DIR, "Internal", PROC, legend=1, normalize=True, ratio=True)
utils.SaveHistograms([h_mu_dt_2016_dely, h_mu_cw_2016_dely], "./%s/mcrw_dt_2016_dely" % PLOTS_DIR, "Internal", PROC, legend=1, normalize=True, ratio=True)
utils.SaveHistograms([h_mu_dt_2016     , h_mu_cw_2016     ], "./%s/mcrw_dt_2016" % PLOTS_DIR, "Internal", PROC, legend=1, normalize=True, ratio=True)
utils.SaveHistograms([h_mu_dt_2015     , h_mu_cw_2015     ], "./%s/mcrw_dt_2015" % PLOTS_DIR, "Internal", PROC, legend=1, normalize=True, ratio=True)
utils.SaveHistograms([h_mu_dt          , h_mu_cw          ], "./%s/mcrw_dt"      % PLOTS_DIR, "Internal", PROC, legend=1, normalize=True, ratio=True)
#*****************************************************
#Save MC overlays
#*****************************************************
h_mu_cw_2015.SetLineColor(2)
h_mu_cw_2015.SetMarkerColor(2)

h_mu_cw_2016.SetLineColor(4)
h_mu_cw_2016.SetMarkerColor(4)

h_mu_cw.SetLineColor(1)
h_mu_cw.SetMarkerColor(1)

utils.SaveHistograms([h_mu_cw, h_mu_cw_2015, h_mu_cw_2016], "./%s/mcrw" % PLOTS_DIR, "Internal", PROC, legend=1)
#*****************************************************
#Save Data overlays
#*****************************************************
h_mu_dt_2015.SetLineColor(2)
h_mu_dt_2015.SetMarkerColor(2)

h_mu_dt_2016.SetLineColor(4)
h_mu_dt_2016.SetMarkerColor(4)

utils.SaveHistograms([h_mu_dt, h_mu_dt_2015, h_mu_dt_2016], "./%s/data" % PLOTS_DIR, "Internal", PROC, legend=1)
#*****************************************************
#*****************************************************

