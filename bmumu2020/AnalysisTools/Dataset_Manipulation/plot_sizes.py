import ROOT

import fnmatch
import os
import operator

#---------------------------------
ROOT.gROOT.SetBatch()
h_size=ROOT.TH1F("h_size", "", 100, 0, 0)
h_size.GetXaxis().SetTitle("MB")
h_size.GetYaxis().SetTitle("Entries")
TOTALSIZE=0.
NFILES=0
d_FILE=dict()
#---------------------------------
for root, dirnames, filenames in os.walk('.'):
    for filename in fnmatch.filter(filenames, '*.root'):
        FILEPATH="%s/%s" % (root, filename)
        SIZE=os.path.getsize(FILEPATH)/(1000. * 1000.)
        TOTALSIZE+=SIZE
        h_size.Fill(SIZE)
        NFILES+=1
        d_FILE[FILEPATH] = SIZE
#---------------------------------
c_size=ROOT.TCanvas("c_size", "", 600, 600)
h_size.Draw()
c_size.SaveAs("size.pdf")
#---------------------------------
ofile=open("size.txt", "w")

l_tp_FILE=sorted(d_FILE.items(), key=operator.itemgetter(1))
for FILE, SIZE in l_tp_FILE:
    ofile.write("{0:60}{1:10.0f}\n".format(FILE,SIZE) )
ofile.close()
#---------------------------------
print("Total size: %d MB" % TOTALSIZE)
print("Total files: %d" % NFILES)
#---------------------------------

