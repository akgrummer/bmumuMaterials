import ROOT

import glob
import os
import re

import atlas
import utils

#***********************************
#Make bin errors zero
#***********************************
def zero_errors(hist):
    nbins=hist.GetNbinsX()
    for i_bin in range(1, nbins + 1):
        hist.SetBinError(i_bin, 0)
#***********************************
#Retrieve title based on name
#***********************************
d_mc_proc={"300406":"B^{+} #rightarrow J/#psi#pi^{+}", "300404":"B^{+} #rightarrow J/#psiK^{+}", "300432":"B_{s} #rightarrow K#mu#nu", "300431":"B #rightarrow hh", "300434":"#Lambda_{b}^{0} #rightarrow #mu#nu", "300203":"bb #rightarrow J/#psiX", "300438":"B_{s} #rightarrow J/#psi#phi", "300433":"B_{d} #rightarrow #pi #mu #nu", "300426":"B_{s} #rightarrow #mu#mu"}

def get_title(hist):
    name=hist.GetName()

    if name == "pileup_chan3_run284500":
        return "Not Recomended"

    pattern="pileup_chan([0-9]{6})_run[0-9]{6}"
    match = re.match(pattern, name)
    if not match:
        print("Cannot find DSID for histogram %s" % name)
        return "None"
    else:
        DSID=match.group(1)
        if DSID in d_mc_proc:
            return d_mc_proc[DSID]
        else:
            print("DSID %s not found in %s" % (DSID, name) )
            return "Not Found"
#***********************************
#Gets histogram from PRW file
#***********************************
def get_histogram(filename):
    l_hist=list()

    if "NotRecommended" in filename:
        ifile=ROOT.TFile(filename)
        hist=ifile.Get("pileup_chan3_run284500")
        hist.SetDirectory(0)
        zero_errors(hist)
        ifile.Close()

        return hist

    ifile=ROOT.TFile(filename)

    directory=ifile.Get("PileupReweighting")
    l_key=directory.GetListOfKeys()
    for key in l_key:
        obj=key.ReadObj()
        if obj.InheritsFrom("TH1D"):
            l_hist.append(obj)

    if len(l_hist) != 1:
        print("Found %d histograms." % len(l_hist) )
        print(l_hist)
        exit(1)

    l_hist[0].SetDirectory(0)
    ifile.Close()

    return l_hist[0]
#***********************************
#Make directories, etc
#***********************************
ROOT.gROOT.SetBatch()

PLOT_DIR="plots_mc"
HIST_DIR="hist"

if not os.path.isdir(PLOT_DIR):
    os.mkdir(PLOT_DIR)

if not os.path.isdir(HIST_DIR):
    os.mkdir(HIST_DIR)
#***********************************
#Gets all histograms
#***********************************
PRW_DIR="prw_files"

l_hist=list()
for FILE in glob.glob("%s/*.root" % PRW_DIR):
    hist=get_histogram(FILE) 
    l_hist.append(hist)
#***********************************
#Reformat histograms
#***********************************
l_color=[1,2,3,4,6,7,28,21,42,8]
l_c_hist=list()

for i_hist, hist in enumerate(l_hist):
    color=l_color[i_hist]
    c_hist=hist.Clone()
    title=get_title(hist)
    c_hist.SetTitle(title)
    c_hist.SetLineColor(color)
    c_hist.SetMarkerColor(color)
    c_hist.GetXaxis().SetRangeUser(0, 50)
    c_hist.GetXaxis().SetTitle("<#mu>")
    
    l_c_hist.append(c_hist)
#***********************************
#Save histograms
#***********************************
#***********************************
utils.RATIO_LOW=0.9
utils.RATIO_HIGH=1.1

utils.LEG_DY=0.6

utils.SaveHistograms(l_c_hist, "%s/pileup_mc" % PLOT_DIR, "Simulation", "mc15c", normalize=True, legend=1, ratio=True)
#***********************************
#Save histograms as ROOT
#***********************************
ofile=ROOT.TFile("%s/hist_mc.root" % HIST_DIR, "recreate")

for hist in l_c_hist:
    hist.Write()

ofile.Close()
#***********************************
#***********************************

