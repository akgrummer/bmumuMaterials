import ROOT

import sys
import os

import atlas
import utils

import os
import glob

ROOT.gROOT.SetBatch()
#***************************************************
def check():
    if len(sys.argv) < 2:
        print("Need input file.")
        exit(1)

    IFILE_NAME=sys.argv[1]
    if not os.path.isfile(IFILE_NAME):
        print("Cannot find file %s" % IFILE_NAME)
        exit(1)
#***************************************************
check()

plots_dir="plots"

if not os.path.isdir(plots_dir):
    os.mkdir(plots_dir)

for plot in glob.glob("%s/*.pdf" % plots_dir):
    os.remove(plot)

IFILE_NAME=sys.argv[1]
ifile=ROOT.TFile(IFILE_NAME)
l_key=ifile.GetListOfKeys()

l_name=list()
for key in l_key:
    name=key.GetName()
    if "_one" in name:
        name=name.replace("_one", "")
        l_name.append(name)

l_hist=list()
for name in l_name:
    hist_one=ifile.Get("%s_one" % name)
    hist_two=ifile.Get("%s_two" % name)

    l_hist.append( (hist_one, hist_two) )
#***************************************************
for h_one, h_two in l_hist:
    name=h_one.GetName().replace("_one", "").replace("h_", "")
    h_one.SetTitle("Data")
    h_two.SetTitle("MC")
    h_one.GetXaxis().SetTitle("<#mu>")
    h_two.GetXaxis().SetTitle("<#mu>")

    utils.SaveHistograms([h_one, h_two], "%s/%s" % (plots_dir, name), "Internal", "", normalize=True, legend=1)
#***************************************************
ifile.Close()
