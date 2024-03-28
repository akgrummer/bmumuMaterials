import ROOT

import os
import sys
import atlas
import utils

ROOT.gROOT.SetBatch()
utils.RATIO_LOW=0.8
utils.RATIO_HIGH=1.2
#-----------------------------------------------------
#Do preliminary checks
#-----------------------------------------------------
def check():
    if not os.path.isdir(PLOTS_DIR):
        os.mkdir(PLOTS_DIR)

    if not os.path.isdir(DIRNAME):
        print("Cannot find directory \"%s\"" % DIRNAME)
        exit(1)

    if not os.path.isdir(LUMIDIR):
        print("Cannot find directory \"%s\"" % LUMIDIR)
        exit(1)
#-----------------------------------------------------
#Initialize variables
#-----------------------------------------------------
PLOTS_DIR="plots_jpsi"
LUMIDIR="/nfs/monet_3/home/campoverde/Data/Trees/Lumifiles_2015_2016/"
PROC="B^{+}#rightarrowJ/#psi+K^{+}"

#DIRNAME="/nfs/monet_3/home/campoverde/Data/Test_Rel21/user.acampove.BplusJpsiKp_undefined_BPHY8_NTUP.300404.e4862_e5984_a875_r9364_r9315_p3371_BpJpsiKp.root"
DIRNAME="/data/atlasb7/grid/BpJpsiKplus/FNTUP/mc16_13TeV.300404.Pythia8BEvtGen_A14_CTEQ6L1_Bp_Jpsi_mu3p5mu3p5_Kp_BMassFix.deriv.NTUP_SKIMMED_BPHY8.e4862_e5984_a875_r9364_r9315_p3371_BJpsiK/"

l_lumifiles_2015 = ["Lumifile_2015_HLT_mu6_mu4_bJpsimumu.root"]
l_lumifiles_2016 = ["Lumifile_2016_HLT_mu6_mu4_bJpsimumu_Lxy0.root", "Lumifile_2016_HLT_mu6_mu4_bJpsimumu_Lxy0_delayed.root"]

check()
#-----------------------------------------------------
#Open files and make histograms
#-----------------------------------------------------
chain=ROOT.TChain("T_mv")
chain.Add("%s/*.root" % DIRNAME)
chain.SetBranchStatus("*", 0)
chain.SetBranchStatus("PRIVX_mu", 1)
chain.SetBranchStatus("PVWeights", 1)
chain.SetBranchStatus("HLT_trigger", 1)
chain.SetBranchStatus("run_number", 1)
chain.SetBranchStatus("event_number", 1)

h_mu_cw          =utils.GetHistogram("h_mu_cw"          , "Reweighted mc 2015 + 2016"  , 2, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")
h_mu_cw_2015     =utils.GetHistogram("h_mu_cw_2015"     , "Reweighted mc 2015"         , 2, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")
h_mu_cw_2016     =utils.GetHistogram("h_mu_cw_2016"     , "Reweighted mc 2016"         , 2, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")
h_mu_cw_2016_main=utils.GetHistogram("h_mu_cw_2016_main", "Reweighted mc 2016, Main"   , 2, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")
h_mu_cw_2016_dely=utils.GetHistogram("h_mu_cw_2016_dely", "Reweighted mc 2016, Delayed", 2, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")

h_mu_nw          =utils.GetHistogram("h_mu_nw"          , "Original mc 2015 + 2016"  , 4, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")
h_mu_nw_2015     =utils.GetHistogram("h_mu_nw_2015"     , "Original mc 2015"         , 4, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")
h_mu_nw_2016     =utils.GetHistogram("h_mu_nw_2016"     , "Original mc 2016"         , 4, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")
h_mu_nw_2016_main=utils.GetHistogram("h_mu_nw_2016_main", "Original mc 2016, Main"   , 4, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")
h_mu_nw_2016_dely=utils.GetHistogram("h_mu_nw_2016_dely", "Original mc 2016, Delayed", 4, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")
#-----------------------------------------------------
TRIG_2015_MAIN="HLT_mu6_mu4_bJpsimumu"
TRIG_2016_MAIN="HLT_mu6_mu4_bJpsimumu_Lxy0"
TRIG_2016_DELY="HLT_mu6_mu4_bJpsimumu_Lxy0_delayed"
SF=1./1.03
#-----------------------------------------------------
for i_entry, entry in enumerate(chain):
    if i_entry % 100000 == 0:
        print("Processing %d entries" % i_entry)

    pass_main_trigger_2015= TRIG_2015_MAIN in entry.HLT_trigger
    pass_main_trigger_2016= TRIG_2016_MAIN in entry.HLT_trigger
    pass_dely_trigger_2016= TRIG_2016_DELY in entry.HLT_trigger

    if pass_main_trigger_2015 and entry.run_number <= 284484:
        h_mu_cw_2015.Fill(entry.PRIVX_mu, entry.PVWeights)
        h_mu_nw_2015.Fill(entry.PRIVX_mu, 1)

    if pass_main_trigger_2016 and entry.run_number >  284484 and entry.run_number < 302956:
        h_mu_cw_2016_main.Fill(entry.PRIVX_mu, entry.PVWeights)
        h_mu_nw_2016_main.Fill(entry.PRIVX_mu, 1)

    if pass_dely_trigger_2016 and entry.run_number >= 302956:
        h_mu_cw_2016_dely.Fill(entry.PRIVX_mu, entry.PVWeights)
        h_mu_nw_2016_dely.Fill(entry.PRIVX_mu, 1)
#-----------------------------------------------------
#Get single year histograms for MC
#-----------------------------------------------------
h_mu_nw_2016.Add(h_mu_nw_2016_main, h_mu_nw_2016_dely)
h_mu_nw.Add(h_mu_nw_2015, h_mu_nw_2016)

h_mu_cw_2016.Add(h_mu_cw_2016_main, h_mu_cw_2016_dely)
h_mu_cw.Add(h_mu_cw_2015, h_mu_cw_2016)

mc_entries=chain.GetEntries()
print("MC entries %d" % mc_entries)
#-----------------------------------------------------
#Fill data histograms
#-----------------------------------------------------
h_mu_dt_2015=utils.GetHistogram("h_mu_dt_2015", "Data 2015", 1, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")

chain_dt_2015=ROOT.TChain("LumiMetaData")
for FILE in l_lumifiles_2015:
    chain_dt_2015.Add("%s/%s" % (LUMIDIR, FILE) )

for entry in chain_dt_2015:
    h_mu_dt_2015.Fill(SF * entry.AvergeInteractionPerXing, entry.IntLumi)
#------------
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
        h_mu_dt_2016_main.Fill(SF * entry.AvergeInteractionPerXing, entry.IntLumi)
    else:
        h_mu_dt_2016_dely.Fill(SF * entry.AvergeInteractionPerXing, entry.IntLumi)
#-----------------------------------------------------
#Get single year histograms for data
#-----------------------------------------------------
h_mu_dt_2016.Add(h_mu_dt_2016_main, h_mu_dt_2016_dely)
h_mu_dt.Add(h_mu_dt_2015, h_mu_dt_2016)
#-----------------------------------------------------
#Save DATA/MC comparisons
#-----------------------------------------------------
h_mu_dt_2015.GetXaxis().SetRangeUser(7, 20)
h_mu_cw_2015.GetXaxis().SetRangeUser(7, 20)

utils.SaveHistograms([h_mu_dt_2015, h_mu_cw_2015, h_mu_nw_2015], "./%s/mcrw_dt_2015" % PLOTS_DIR, "Internal", PROC, legend=1, normalize=True, ratio=True)

utils.SaveHistograms([h_mu_dt_2016_main, h_mu_cw_2016_main, h_mu_nw_2016_main], "./%s/mcrw_dt_2016_main" % PLOTS_DIR, "Internal", PROC, legend=1, normalize=True, ratio=True)
utils.SaveHistograms([h_mu_dt_2016_dely, h_mu_cw_2016_dely, h_mu_nw_2016_dely], "./%s/mcrw_dt_2016_dely" % PLOTS_DIR, "Internal", PROC, legend=1, normalize=True, ratio=True)
utils.SaveHistograms([h_mu_dt_2016     , h_mu_cw_2016     , h_mu_nw_2016     ], "./%s/mcrw_dt_2016" % PLOTS_DIR, "Internal", PROC, legend=1, normalize=True, ratio=True)
utils.SaveHistograms([h_mu_dt_2015     , h_mu_cw_2015     , h_mu_nw_2015     ], "./%s/mcrw_dt_2015" % PLOTS_DIR, "Internal", PROC, legend=1, normalize=True, ratio=True)
utils.SaveHistograms([h_mu_dt          , h_mu_cw          , h_mu_nw          ], "./%s/mcrw_dt"      % PLOTS_DIR, "Internal", PROC, legend=1, normalize=True, ratio=True)
#-----------------------------------------------------
#Save MC overlays
#-----------------------------------------------------
h_mu_cw_2015.SetLineColor(2)
h_mu_cw_2015.SetMarkerColor(2)

h_mu_cw_2016.SetLineColor(4)
h_mu_cw_2016.SetMarkerColor(4)

h_mu_cw.SetLineColor(1)
h_mu_cw.SetMarkerColor(1)

utils.SaveHistograms([h_mu_cw, h_mu_cw_2015, h_mu_cw_2016], "./%s/mcrw" % PLOTS_DIR, "Internal", PROC, legend=1)
#-----------------------------------------------------
#Save Data overlays
#-----------------------------------------------------
h_mu_dt_2015.SetLineColor(2)
h_mu_dt_2015.SetMarkerColor(2)

h_mu_dt_2016.SetLineColor(4)
h_mu_dt_2016.SetMarkerColor(4)

utils.SaveHistograms([h_mu_dt, h_mu_dt_2015, h_mu_dt_2016], "./%s/data" % PLOTS_DIR, "Internal", PROC, legend=1)
#-----------------------------------------------------
#Save histograms
#-----------------------------------------------------
ofile=ROOT.TFile("./%s/hist_mu.root" % PLOTS_DIR, "recreate")
h_mu_cw_2015.Write()
h_mu_cw_2016.Write()
h_mu_cw.Write()
h_mu_dt_2015.Write()
h_mu_dt_2016.Write()
h_mu_dt.Write()
ofile.Close()
#-----------------------------------------------------
#-----------------------------------------------------

