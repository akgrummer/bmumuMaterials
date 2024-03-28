import ROOT

import utils
import atlas

import collections
import sys
import os
import glob

#--------------------------------------
#Setup/Initialize eveything
#--------------------------------------
ROOT.gROOT.SetBatch()

d_process_hist_narrow=dict()
d_process_hist_wide  =dict()

d_nentries_hist=dict()

ROOT_DIR="Root"
PROCESS=sys.argv[1]
#**************************************
#Open file and get histograms
#**************************************
ifile_hist=ROOT.TFile("%s/%s_components.root" % (ROOT_DIR, PROCESS) )
keys=ifile_hist.GetListOfKeys()
for key in keys:
    obj=key.ReadObj()
    histname=obj.GetName()
    process=obj.GetTitle()

    if "narrow" in histname:
        d_process_hist_narrow[process]=obj

    if "wide" in histname:
        d_process_hist_wide[process]=obj
#**************************************
#Make histograms
#**************************************
h_nentries=utils.GetHistogram("h_nentries", "", 4, 100, 0, 0, title_x="Number of candidates", title_y = "Entries")
#**************************************
#Remove old plots
#**************************************
for FILE in glob.glob("Plots/%s_components/*.pdf" % PROCESS):
    os.remove(FILE)
#**************************************
#Pair wide-narrow histograms with number
#of entries in signal region as key
#**************************************
tot_nentries=0
for process in d_process_hist_wide:
    hist_wide  =d_process_hist_wide[process]
    hist_narrow=d_process_hist_narrow[process]

    nbins=hist_narrow.GetNbinsX()
    nentries=hist_narrow.Integral(1, nbins)
    tot_nentries+=nentries

    d_nentries_hist[nentries] = (hist_wide, hist_narrow)
#**************************************
#Sort pairs of histograms
#**************************************
od_nentries_hist=collections.OrderedDict( sorted(d_nentries_hist.items()) )

for nentries in od_nentries_hist:
    h_nentries.Fill(nentries)

    if nentries < 0.001 * tot_nentries:
        continue

    hist_wide, hist_narrow = od_nentries_hist[nentries]

    process=hist_wide.GetTitle()
    nentries_wide=hist_wide.GetEntries()

    utils.SaveHistograms([hist_wide]  , "Plots/%s_components/wide__%d__%s"   % (PROCESS, nentries, process), "Simulation Internal", "Entries %d" % nentries_wide)
    utils.SaveHistograms([hist_narrow], "Plots/%s_components/narrow__%d__%s" % (PROCESS, nentries, process), "Simulation Internal", "Entries %d" % nentries)
#**************************************
#Save histograms
#**************************************
utils.SaveHistograms([h_nentries], "Plots/%s_nentries" % PROCESS, "Simulation Internal", "", logx=True)
#**************************************
#Print useful information
#**************************************
print("Number of histograms %d." % h_nentries.Integral() )
#**************************************
#**************************************
ifile_hist.Close()

