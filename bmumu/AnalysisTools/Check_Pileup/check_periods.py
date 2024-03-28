import ROOT

import tools
import re
import read_json

import atlas
import utils

ROOT.gROOT.SetBatch()
#***********************************
#Fill histogram for given run
#***********************************
def fill_histogram(h_out, h_in, run_number):
    nbins=h_in.GetNbinsX()

    for i_bin in range(1, nbins + 1):
        lumi_block=h_in.GetBinLowEdge(i_bin)
        luminosity=h_in.GetBinContent(i_bin)

        mu=read_json.pileup(run_number, lumi_block)

        if mu < 0:
            continue

        #print("mu: %.3f, luminosity %.3f" % (mu, luminosity) )
        h_out.Fill(mu, luminosity)
        h_mu_total.Fill(mu, luminosity)

    return h_out 
#***********************************
#Get run number for histogram
#***********************************
def get_runnumber(hist):
    name=hist.GetName()
    match = re.match("run([0-9]{6})_peaklumiplb", name)
    #match = re.match("run([0-9]{6})_intlumi", name)
    #match = re.match("run([0-9]{6})_trigrateplb", name)
    #match = re.match("run([0-9]{6})_ntrigplb", name)

    if not match:
        return -1
    else:
        s_run_number = match.group(1)
        return int(s_run_number)
#***********************************
#Define paths
#***********************************
DATA_PATH="/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/GoodRunsLists/"

LUMI="data16_13TeV/20170720/physics_25ns_20.7.lumicalc.OflLumi-13TeV-009.root" 
#***********************************
#Fill run_number --> histogram dictionary 
#***********************************
d_hist=dict()

ifile=ROOT.TFile("%s/%s" % (DATA_PATH, LUMI) )
l_key=ifile.GetListOfKeys()

for key in l_key:
    obj=key.ReadObj()
    if obj.InheritsFrom("TH1"):
        run_number = get_runnumber(obj)
        if run_number != -1:
            obj.SetDirectory(0)
            d_hist[run_number] = obj

h_mu_def_highbin=ifile.Get("avgintperbx")
h_mu_default=h_mu_def_highbin.Rebin(10, "mu_default")
h_mu_default.SetDirectory(0)

ifile.Close()
#***********************************
#Make histograms for each period
#***********************************
if True:
    h_period_A=utils.GetHistogram("h_A", "A", 1 , 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")
    h_period_B=utils.GetHistogram("h_B", "B", 2 , 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")
    h_period_C=utils.GetHistogram("h_C", "C", 3 , 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")
    h_period_D=utils.GetHistogram("h_D", "D", 4 , 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")
    h_period_E=utils.GetHistogram("h_E", "E", 6 , 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")
    h_period_F=utils.GetHistogram("h_F", "F", 7 , 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")
    h_period_G=utils.GetHistogram("h_G", "G", 28, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")
    h_period_H=utils.GetHistogram("h_H", "H", 21, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")
    h_period_I=utils.GetHistogram("h_I", "I", 42, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")
    h_period_J=utils.GetHistogram("h_J", "J", 46, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")
    h_period_K=utils.GetHistogram("h_K", "K", 38, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")
    h_period_L=utils.GetHistogram("h_L", "L", 12, 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")

    h_mu_total=utils.GetHistogram("h_T", "T", 1 , 50, 0, 50, title_x="<#mu>", title_y = "Entries/1")
#***********************************
#Fill histograms
#***********************************
for run_number in d_hist:
    period = tools.GetPeriod(run_number)
    h_in = d_hist[run_number]

    if period == "2016_A":
        h_period_A = fill_histogram(h_period_A, h_in, run_number)
    elif period == "2016_B":
        h_period_B = fill_histogram(h_period_B, h_in, run_number)
    elif period == "2016_C":
        h_period_C = fill_histogram(h_period_C, h_in, run_number)
    elif period == "2016_D":
        h_period_D = fill_histogram(h_period_D, h_in, run_number)
    elif period == "2016_E":
        h_period_E = fill_histogram(h_period_E, h_in, run_number)
    elif period == "2016_F":
        h_period_F = fill_histogram(h_period_F, h_in, run_number)
    elif period == "2016_G":
        h_period_G = fill_histogram(h_period_G, h_in, run_number)
    elif period == "2016_H":
        h_period_H = fill_histogram(h_period_H, h_in, run_number)
    elif period == "2016_I":
        h_period_I = fill_histogram(h_period_I, h_in, run_number)
    elif period == "2016_J":
        h_period_J = fill_histogram(h_period_J, h_in, run_number)
    elif period == "2016_K":
        h_period_K = fill_histogram(h_period_K, h_in, run_number)
    elif period == "2016_L":
        h_period_L = fill_histogram(h_period_L, h_in, run_number)
    else:
        print("Unrecognized period %s, run number %d" % (period, run_number) )
        exit(1)
#***********************************
#Save histograms
#***********************************
PLOTS_DIR="plots_data"

l_hist_1=list()
l_hist_1.append(h_period_A)
l_hist_1.append(h_period_B)
l_hist_1.append(h_period_C)
l_hist_1.append(h_period_D)
l_hist_1.append(h_period_E)
l_hist_1.append(h_period_F)

l_hist_2=list()
l_hist_2.append(h_period_G)
l_hist_2.append(h_period_H)
l_hist_2.append(h_period_I)
l_hist_2.append(h_period_J)
l_hist_2.append(h_period_K)
l_hist_2.append(h_period_L)


utils.SaveHistograms(l_hist_1, "%s/period_mu_1" % PLOTS_DIR, "Data", "", legend=1)
utils.SaveHistograms(l_hist_2, "%s/period_mu_2" % PLOTS_DIR, "Data", "", legend=1)

#ofile=ROOT.TFile("%s/period_mu.root" % PLOTS_DIR, "recreate")
#for hist in l_hist:
#    hist.Write()
#ofile.Close()
#***********************************
#Compare default <mu> with ours
#***********************************
l_hist_mu_comp=[h_mu_default, h_mu_total]
utils.RATIO_LOW=0.9
utils.RATIO_HIGH=1.1

utils.SaveHistograms(l_hist_mu_comp, "%s/mu_comparison" % PLOTS_DIR, "Data", "", normalize=True, ratio=True)
#***********************************
#***********************************

