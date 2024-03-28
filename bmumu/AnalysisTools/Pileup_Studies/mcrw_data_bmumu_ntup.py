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
PLOTS_DIR="plots_bmumu"
PROC_BSMUMU="B_{s}^{0}#rightarrow#mu^{+}#mu^{-}"
LUMIDIR="/nfs/monet_3/home/campoverde/Data/Trees/Lumifiles_2015_2016/"

#DIRNAME="/nfs/monet_3/home/campoverde/Data/MC_Rel21/mc16_13TeV.300426.Pythia8BEvtGen_A14_CTEQ6L1_Bs_mu3p5mu3p5.deriv.NTUP_BPHY8.e4889_e5984_a875_r9364_r9315_p3371_Bmumu/"
#DIRNAME="/nfs/monet_3/home/campoverde/Data/Tests/Test_Rel21/data-Bmumu/"
DIRNAME="/data/atlasb7/grid/Bsmumu/FNTUP/mc16_13TeV.300426.Pythia8BEvtGen_A14_CTEQ6L1_Bs_mu3p5mu3p5.deriv.NTUP_SKIMMED_BPHY8.e4889_e5984_a875_r9364_r9315_p3371_Bmumu/"

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

h_mu_nw_2015=utils.GetHistogram("h_mu_nw_2015", "Original mc 2015", 4, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")
h_mu_nw_2016=utils.GetHistogram("h_mu_nw_2016", "Original mc 2016", 4, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")

h_mu_cw_2015=utils.GetHistogram("h_mu_cw_2015", "Reweighted mc 2015", 2, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")
h_mu_cw_2016=utils.GetHistogram("h_mu_cw_2016", "Reweighted mc 2016", 2, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")
#-----------------------------------------------------
#Initialize more variables
#-----------------------------------------------------
TRIG_2015="HLT_mu6_mu4_bBmumu"
TRIG_2016="HLT_mu6_mu4_bBmumu_Lxy0"
SF=1/1.03
s_event_number=set()
#-----------------------------------------------------
#Fill reweighted and original MC histograms
#-----------------------------------------------------
for i_entry, entry in enumerate(chain):
    if i_entry % 100000 == 0:
        print("Processing %d entries" % i_entry)

    event_number=entry.event_number
    if event_number in s_event_number:
        continue
    else:
        s_event_number.add(event_number)

    pass_trigger_2015= TRIG_2015 in entry.HLT_trigger
    pass_trigger_2016= TRIG_2016 in entry.HLT_trigger

    mu = entry.PRIVX_mu
    wgt= entry.PVWeights

    if pass_trigger_2015 and entry.run_number <= 284484:
        h_mu_cw_2015.Fill(mu, wgt)
        h_mu_nw_2015.Fill(mu, 1)

    if pass_trigger_2016 and entry.run_number >  284484:
        h_mu_cw_2016.Fill(mu, wgt)
        h_mu_nw_2016.Fill(mu, 1)

print("Entries for <mu> 2015:%d" % h_mu_cw_2015.GetEntries())
print("Entries for <mu> 2016:%d" % h_mu_cw_2016.GetEntries())
#-----------------------------------------------------
#
#-----------------------------------------------------
h_mu_nw=h_mu_nw_2016.Clone("h_mu_nw")
h_mu_nw.SetTitle("Original mc 2015+2016")
h_mu_nw.Add(h_mu_nw_2015, h_mu_nw_2016)

h_mu_cw=h_mu_cw_2016.Clone("h_mu_cw")
h_mu_cw.SetTitle("Reweighted mc 2015+2016")
h_mu_cw.Add(h_mu_cw_2015, h_mu_cw_2016)

mc_entries=chain.GetEntries()
print("MC entries %d" % mc_entries)
#-----------------------------------------------------
#Make data histograms and fill them
#-----------------------------------------------------
h_mu_dt_2015=utils.GetHistogram("h_mu_dt_2015", "Data 2015", 1, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")

ifile_2015=ROOT.TFile("%s/Lumifile_2015_HLT_mu6_mu4_bBmumu.root" % LUMIDIR)
tree_dt_2015=ifile_2015.Get("LumiMetaData")
for entry in tree_dt_2015:
    h_mu_dt_2015.Fill(SF * entry.AvergeInteractionPerXing, entry.IntLumi)

ifile_2015.Close()
#------------
h_mu_dt_2016=utils.GetHistogram("h_mu_dt_2016", "Data 2016", 1, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")

ifile_2016=ROOT.TFile("%s/Lumifile_2016_HLT_mu6_mu4_bBmumu_Lxy0.root" % LUMIDIR)
tree_dt_2016=ifile_2016.Get("LumiMetaData")
for entry in tree_dt_2016:
    h_mu_dt_2016.Fill(SF * entry.AvergeInteractionPerXing, entry.IntLumi)

ifile_2016.Close()
#------------
h_mu_dt = h_mu_dt_2016.Clone("h_mu_dt")
h_mu_dt.SetTitle("Data 2015+2016")
h_mu_dt.Add(h_mu_dt_2015, h_mu_dt_2016, 1, 1)
#-----------------------------------------------------
#Save single year plots
#-----------------------------------------------------
h_mu_dt_2015.GetXaxis().SetRangeUser(7, 20)
h_mu_cw_2015.GetXaxis().SetRangeUser(7, 20)
h_mu_nw_2015.GetXaxis().SetRangeUser(7, 20)

utils.SaveHistograms([h_mu_dt_2015, h_mu_cw_2015, h_mu_nw_2015], "./%s/mcrw_dt_2015" % PLOTS_DIR, "Internal", PROC_BSMUMU, legend=1, normalize=True, ratio=True)
utils.SaveHistograms([h_mu_dt_2016, h_mu_cw_2016, h_mu_nw_2016], "./%s/mcrw_dt_2016" % PLOTS_DIR, "Internal", PROC_BSMUMU, legend=1, normalize=True, ratio=True)
utils.SaveHistograms([h_mu_dt     , h_mu_cw     , h_mu_nw     ], "./%s/mcrw_dt"      % PLOTS_DIR, "Internal", PROC_BSMUMU, legend=1, normalize=True, ratio=True)
#-----------------------------------------------------
#Save added plots
#-----------------------------------------------------
h_mu_cw_2015.SetLineColor(2)
h_mu_cw_2015.SetMarkerColor(2)

h_mu_cw_2016.SetLineColor(4)
h_mu_cw_2016.SetMarkerColor(4)

h_mu_cw.SetLineColor(1)
h_mu_cw.SetMarkerColor(1)

utils.SaveHistograms([h_mu_cw, h_mu_cw_2015, h_mu_cw_2016], "./%s/mcrw" % PLOTS_DIR, "Internal", PROC_BSMUMU, legend=1)
#--------------
h_mu_dt_2015.SetLineColor(2)
h_mu_dt_2015.SetMarkerColor(2)

h_mu_dt_2016.SetLineColor(4)
h_mu_dt_2016.SetMarkerColor(4)

utils.SaveHistograms([h_mu_dt, h_mu_dt_2015, h_mu_dt_2016], "./%s/data" % PLOTS_DIR, "Internal", PROC_BSMUMU, legend=1)
#-----------------------------------------------------
#Save histograms
#-----------------------------------------------------
ofile=ROOT.TFile("./%s/hist_mu.root" % PLOTS_DIR, "recreate")
h_mu_cw_2015.Write()
h_mu_cw_2016.Write()
h_mu_cw.Write()

h_mu_nw_2015.Write()
h_mu_nw_2016.Write()
h_mu_nw.Write()

h_mu_dt_2015.Write()
h_mu_dt_2016.Write()
h_mu_dt.Write()
ofile.Close()
#-----------------------------------------------------
#-----------------------------------------------------

