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
    if len(sys.argv) < 3:
        print("Need input file.")
        exit(1)

    IFILE_NAME=sys.argv[1]
    if not os.path.isfile(IFILE_NAME):
        print("Cannot find file %s" % IFILE_NAME)
        exit(1)

    PLOTS_DIR="plots_%s" % sys.argv[2]
    if not os.path.isdir(PLOTS_DIR):
        os.mkdir(PLOTS_DIR)
#***************************************************
check()

PLOTS_DIR="plots_%s" % sys.argv[2]

for plot in glob.glob("%s/*.pdf" % PLOTS_DIR):
    os.remove(plot)
#***************************************************
IFILE_NAME=sys.argv[1]
ifile=ROOT.TFile(IFILE_NAME)
l_key=ifile.GetListOfKeys()

for key in l_key:
    obj=key.ReadObj()
    if obj.InheritsFrom("TH1"):
        name=obj.GetName().replace("h_", "")
        utils.SaveHistograms([obj], "%s/%s" % (PLOTS_DIR, name), "Internal", "")

ifile.Close()
#***************************************************

