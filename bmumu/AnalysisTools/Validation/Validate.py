import ROOT
import glob
import os
import subprocess
import math
import atlas
import utils
import shutil
import sys
import json
import re
import array

ROOT.gROOT.SetBatch(True)
#******************************************
#Do preliminary checks
#******************************************
def check():
    if not os.path.isfile("arguments.json"):
        print("Validate.py::Cannot find file with arguments, arguments.json")
        exit(1)
#******************************************
#Should this variable's histogram be in log scale?
#******************************************
def uselog(variable):
    s_variables = utils.txt_to_set("./Info/use_log.txt")

    return variable in s_variables 
#******************************************
#Does this entry pass the cuts?
#******************************************
def pass_cut(entry):
    chi2                   = entry.B_fitChi2NDF
    R_mu_minus_eta         = entry.Muon1_eta
    R_mu_plus_eta          = entry.Muon2_eta
    R_mu_minus_pT          = entry.Muon1_pT
    R_mu_plus_pT           = entry.Muon2_pT
    R_mu_minus_isCombined  = entry.Muon1_isCombinedMuon
    R_mu_plus_isCombined   = entry.Muon2_isCombinedMuon
    B_pT                   = entry.B_pT
    B_eta                  = entry.B_eta
    pass_reco_muon         = abs( R_mu_minus_eta ) < 2.5 and abs( R_mu_plus_eta ) < 2.5 and R_mu_plus_pT > 4000 and R_mu_minus_pT > 4000 and R_mu_minus_isCombined and R_mu_plus_isCombined

    return pass_reco_muon and chi2 < 6 and B_pT > 8000 and abs(B_eta) < 2.5 
#******************************************
#Returns histogram
#******************************************
def MakeHistogram(variable, xmin, xmax):
    nbins=100
    dx = "%.3f" % ( (xmax - xmin) / nbins)

    hist = ROOT.TH1F( "h_" + variable, "", nbins, xmin, xmax)
    hist.SetLineColor(4)
    hist.SetMarkerColor(4)
    hist.SetMarkerStyle(22)
    hist.GetYaxis().SetTitle("Entries/" + str(dx) )
    hist.GetXaxis().SetTitle(variable)
    hist.Sumw2()

    return hist 
#******************************************
#Prints arguments that will be used
#******************************************
def print_arguments():
    print("File, first event: %d" % MIN)
    print("File, last event: %d" % MAX)
    print("Output file: %s" % OUTPUT)
#******************************************
#Get arguments
#******************************************
json_arg=utils.json_to_dict("arguments.json")

MIN=0
MAX=0
OUTPUT =""

if json_arg["TEST"] == "1":
    MIN=0
    MAX=int(json_arg["NEVENTS"])
    OUTPUT =json_arg["OUTPUTFILE"]
else:
    args_validate=sys.argv
    MIN=int(args_validate[1])
    MAX=int(args_validate[2])
    OUTPUT =args_validate[3]

check()
print_arguments()
#******************************************
#Make histograms
#******************************************
d_histograms = dict()

json_bin=utils.json_to_dict("binning.json")

for VARIABLE in json_bin:
    tupl = json_bin[VARIABLE]
    minx = tupl[0]
    maxx = tupl[1]

    hists = MakeHistogram(VARIABLE, minx, maxx)
    d_histograms[VARIABLE] = hists
#******************************************
#Make chain and turn on only variables wanted
#******************************************
chain=ROOT.TChain(json_arg["TREENAME"])

for FILE in glob.glob(json_arg["FILE"]):
    chain.Add(FILE)

chain.SetBranchStatus("*", 0)

for VARIABLE in json_bin:
    chain.SetBranchStatus(VARIABLE, 1)
#******************************************
#Fill histograms
#******************************************
if MAX == -1:
    MAX=chain.GetEntries()
    print("Running over %d entries." % MAX)

for i_entry in range(MIN, MAX + 1):
    chain.GetEntry(i_entry)
    #************************
    if i_entry % 1000 == 0:
        print "First chain::Processing " + str(i_entry)

    #if ( not pass_cut(chain) ):
    #    continue
    
    for variable in d_histograms:
        hist = d_histograms[variable]

        leaf = chain.GetLeaf(variable)

        value = leaf.GetValue()

        hist.Fill(value)
#******************************************
#Save histograms
#******************************************
ofile=ROOT.TFile(OUTPUT, "RECREATE")

for variable in d_histograms:
    d_histograms[variable].Write()
ofile.Close()
#******************************************
#******************************************

