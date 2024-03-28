import ROOT

import os
import glob
import re

import utils
import atlas

#-----------------------------------
def GetTime(FILE):
    ifile=open(FILE)
    l_line=ifile.read().splitlines()
    for line in l_line:
        match=re.match("DataFit\.py::Time elapsed (\d+\.?\d*)", line)
        if match:
            stime=match.group(1)
            time=float(stime)
            return time/60.

    print("Could not find time elapsed in %s" % FILE)

    return -1
#-----------------------------------
PLOTS_DIR="plots"
if not os.path.isdir(PLOTS_DIR):
    os.mkdir(PLOTS_DIR)
#-----------------------------------
h_time=utils.GetHistogram("h_time", "", 1, 30, 0, 0, title_x="time[s]", title_y = "Fits")

l_FILE=glob.glob("out/*.out")
for FILE in l_FILE:
    time=GetTime(FILE)
    if time < 0:
        continue
    h_time.Fill(time)

utils.SaveHistograms([h_time], "%s/time" % PLOTS_DIR, "Internal", "")
#-----------------------------------

