import ROOT

import re
import sys

import tools
import read_json
import atlas
import utils

ROOT.gROOT.SetBatch()
#***********************************
#Get run number for histogram
#***********************************
def get_runnumber(hist):
    name=hist.GetName()
    match = re.match("run([0-9]{6})_peaklumiplb", name)

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
            #print("Found run %d." % run_number)
            d_hist[run_number] = obj
#***********************************
#Print luminosity
#***********************************
run_number=int(sys.argv[1])

hist=d_hist[run_number]

nbins=hist.GetNbinsX()
for i_bin in range(1, nbins + 1):
    lumi_block=hist.GetBinLowEdge(i_bin)
    luminosity=hist.GetBinContent(i_bin)

    print("Lumiblock:%d    Luminosity:%.3f" % (lumi_block, luminosity) )
#***********************************
#***********************************

