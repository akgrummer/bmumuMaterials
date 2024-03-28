import ROOT

import os
import sys
import glob
import collections

import utils
#------------------------------------------
#Prepare all
#------------------------------------------
ROOT.gROOT.SetBatch()
PROCESS=sys.argv[1]
DECAY_DIR="Plots/%s_decay_dist/" % PROCESS
FILENAME="Root/%s_components.root" % PROCESS

if not os.path.isdir(DECAY_DIR):
    os.mkdir(DECAY_DIR)

for FILE in glob.glob("%s/*.pdf" % DECAY_DIR):
    os.remove(FILE)
#------------------------------------------
#Make structures
#------------------------------------------
d_entries_decay_narrow=dict()
d_entries_decay_wide=dict()
#------------------------------------------
#Fill dictionaries
#------------------------------------------
ifile=ROOT.TFile(FILENAME)
l_key=ifile.GetListOfKeys()
ndecays=len(l_key) / 2 
print("Found %d decays." % ndecays)

for key in l_key:
    hist=key.ReadObj()
    nbins=hist.GetNbinsX()
    decay=hist.GetTitle()

    if "narrow" in hist.GetName():
        nentries=hist.Integral(1, nbins)
        if nentries not in d_entries_decay_narrow:
            d_entries_decay_narrow[nentries]=[decay]
        else:
            d_entries_decay_narrow[nentries].append(decay)

    if "wide" in hist.GetName():
        nentries=hist.GetEntries()
        if nentries not in d_entries_decay_wide:
            d_entries_decay_wide[nentries]=[decay]
        else:
            d_entries_decay_wide[nentries].append(decay)
#------------------------------------------
#Sort decays
#------------------------------------------
od_entries_decay_narrow=collections.OrderedDict( sorted(d_entries_decay_narrow.items(), reverse=True) )
od_entries_decay_wide  =collections.OrderedDict( sorted(d_entries_decay_wide.items(), reverse=True) )
#------------------------------------------
#Make cumulative decay entries histogram
#------------------------------------------
h_cumul_entries_narrow=utils.GetHistogram("h_cumul_entries_narrow", "M(B)#in[4.7GeV,5.7GeV]", 4, ndecays, 0.5, ndecays + 0.5, title_x="Number of Decays", title_y = "Entries/1")
h_cumul_entries_wide  =utils.GetHistogram("h_cumul_entries_wide", "M(B)#in[3GeV,5GeV]", 2, ndecays, 0.5, ndecays + 0.5, title_x="Number of Decays", title_y = "Entries/1")

cumul_nentries=0
i_decay=0.5
for entries in od_entries_decay_narrow:
    l_decay = od_entries_decay_narrow[entries]
    for decay in l_decay:
        cumul_nentries+=entries
        h_cumul_entries_narrow.Fill(i_decay, cumul_nentries)
        i_decay+=1

cumul_nentries=0
i_decay=0.5
for entries in od_entries_decay_wide:
    l_decay = od_entries_decay_wide[entries]
    for decay in l_decay:
        cumul_nentries+=entries
        h_cumul_entries_wide.Fill(i_decay, cumul_nentries)
        i_decay+=1

utils.MAX_NSCALE=1.6
utils.fix_hist_errors(h_cumul_entries_narrow)
utils.fix_hist_errors(h_cumul_entries_wide)
utils.SaveHistograms([h_cumul_entries_narrow, h_cumul_entries_wide], "%s/cumul_entries" % DECAY_DIR, "Simulation Internal", "", legend=1, logx=True)
#------------------------------------------
#------------------------------------------

