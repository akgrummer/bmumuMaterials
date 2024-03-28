import ROOT
import glob
import os
import subprocess
import math
import shutil
import sys
import json
import re
import array

import read_json
import atlas
import utils

ROOT.gROOT.SetBatch(True)
#******************************************
#Read pileup weight from JSON file
#******************************************
def get_pileup_weights():
    ifile=open(PILEUP_JSON)
    d_mu_wgt=json.load(ifile)
    ifile.close()

    return d_mu_wgt
#******************************************
def save_histograms(p_histograms):
    scale_1 = p_histograms[0].Integral()
    scale_2 = p_histograms[1].Integral()

    name_h_1 = p_histograms[0].GetName()
    name_h_2 = p_histograms[1].GetName()
    
    if scale_1 == 0 or scale_2 == 0:
        print "Cannot normalize either %s or %s." % (name_h_1, name_h_2)
        return 

    p_histograms[0].Write()
    p_histograms[1].Write()
#******************************************
def check():
    if not os.path.isfile("arguments.json"):
        print("Validate.py::Cannot find file with arguments, arguments.json")
        exit(1)
#******************************************
def pass_trigger(entry):
    BJPSI_2015_M="HLT_mu6_mu4_bJpsimumu"
    BJPSI_2016_M="HLT_mu6_mu4_bJpsimumu_Lxy0"
    BJPSI_2016_D="HLT_mu6_mu4_bJpsimumu_Lxy0_delayed"

    #BMUMU_2015_M="HLT_mu6_mu4_bBmumu"
    #BMUMU_2016_M="HLT_mu6_mu4_bBmumu_Lxy0"

    BMUMU_2015_M="HLT_2mu6_bBmumu"
    BMUMU_2016_M="HLT_2mu6_bBmumu"

    is_2015 = entry.run_number <= 284484 #Smaller or equal is 2015
    has_DELY= entry.run_number >= 302956 #Bigger or equal contains delayed stream

    TRIGGER_NAME=""
    if PROCESS == "bsmumu" and is_2015:
        TRIGGER_NAME=BMUMU_2015_M
    elif PROCESS == "bsmumu" and (not is_2015):
        TRIGGER_NAME=BMUMU_2016_M
    elif (PROCESS == "bplus" or PROCESS == "bsjpsiphi") and is_2015:
        TRIGGER_NAME=BJPSI_2015_M
    elif (PROCESS == "bplus" or PROCESS == "bsjpsiphi") and is_2016 and (not has_DELY):
        TRIGGER_NAME=BJPSI_2016_M
    elif (PROCESS == "bplus" or PROCESS == "bsjpsiphi") and is_2016 and has_DELY:
        TRIGGER_NAME=BJPSI_2016_D

    found = entry.HLT_trigger.find(TRIGGER_NAME) != entry.HLT_trigger.end()

    return found
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
def MakeHistograms(variable, nbins, xmin, xmax):
    dx = "%.3f" % ( (xmax - xmin) / 100.)

    h_one = ROOT.TH1F( "h_" + variable + "_one", "Latest Version", nbins, xmin, xmax)
    h_one.SetLineColor(4)
    h_one.SetMarkerColor(4)
    h_one.SetMarkerStyle(22)
    h_one.GetYaxis().SetTitle("Normalized/" + str(dx) )
    h_one.GetXaxis().SetTitle(variable)
    h_one.Sumw2()

    h_two = ROOT.TH1F( "h_" + variable + "_two", "Old Version", nbins, xmin, xmax)
    h_two.SetLineColor(2)
    h_two.SetMarkerColor(2)
    h_two.GetYaxis().SetTitle("Normalized/" + str(dx) )
    h_two.GetXaxis().SetTitle(variable)
    h_two.Sumw2()

    return [h_one, h_two]
#******************************************
def print_arguments():
    print("File 1, first event: %d" % MIN_ONE)
    print("File 2, first event: %d" % MIN_TWO)
    print("File 1, last event: %d" % MAX_ONE)
    print("File 2, last event: %d" % MAX_TWO)
    print("Output file: %s" % OUTPUT)
#******************************************
#Get arguments
#******************************************
check()

ifile_arg=open("arguments.json")
json_arg=json.load(ifile_arg)
ifile_arg.close()

MIN_ONE=0
MAX_ONE=0
MIN_TWO=0
MAX_TWO=0
OUTPUT =""
PILEUP_JSON="json/mu_wgt.json"

d_mu_wgt=get_pileup_weights()

if json_arg["TEST"] == "1":
    MIN_ONE=0
    MAX_ONE=int(json_arg["NEVENTS"])
    MIN_TWO=0
    MAX_TWO=int(json_arg["NEVENTS"])
    OUTPUT =json_arg["OUTPUTFILE"]
else:
    args_validate=sys.argv
    MIN_ONE=int(args_validate[1])
    MAX_ONE=int(args_validate[2])
    MIN_TWO=int(args_validate[3])
    MAX_TWO=int(args_validate[4])
    OUTPUT =args_validate[5]

print_arguments()

PROCESS_DESC="Process description"
PROCESS=json_arg["TYPE"] #bsmumu/bplus/bsjpsiphi
#******************************************
chain_ONE=ROOT.TChain(json_arg["TREENAME"])
chain_TWO=ROOT.TChain(json_arg["TREENAME"])

chain_ONE.Add(json_arg["FILE_ONE"])
chain_TWO.Add(json_arg["FILE_TWO"])
#******************************************
#Turn on only neede branches
#******************************************
if True:
    chain_ONE.SetBranchStatus("*", 0)
    chain_TWO.SetBranchStatus("*", 0)
    
    chain_ONE.SetBranchStatus("HLT_trigger", 1)
    chain_TWO.SetBranchStatus("HLT_trigger" , 1)
    
    chain_ONE.SetBranchStatus("PRIVX_mu", 1)
    chain_TWO.SetBranchStatus("PRIVX_mu" , 1)
    
    chain_ONE.SetBranchStatus("PVWeights", 1)
    chain_TWO.SetBranchStatus("PVWeights" , 1)
    
    chain_ONE.SetBranchStatus("combined_wt", 1)
    chain_TWO.SetBranchStatus("combined_wt" , 1)
    
    chain_ONE.SetBranchStatus("run_number", 1)
    chain_TWO.SetBranchStatus("run_number" , 1)

    chain_ONE.SetBranchStatus("pass_grl", 1)
    chain_TWO.SetBranchStatus("pass_grl" , 1)

    chain_ONE.SetBranchStatus("lumi_block", 1)
    chain_TWO.SetBranchStatus("lumi_block" , 1)
#******************************************
#Make histograms and lists
#******************************************
hists_nowt = MakeHistograms("h_nowt", 50, 0, 50)
hists_pvwt = MakeHistograms("h_pvwt", 50, 0, 50)
hists_cbwt = MakeHistograms("h_cbwt", 50, 0, 50)

hists_pgrl = MakeHistograms("h_pgrl", 2, 0, 2)
hists_trig = MakeHistograms("h_trig", 2, 0, 2)
#******************************************
#Fill histograms, first file
#******************************************
for i_entry in range(MIN_ONE, MAX_ONE + 1):
    chain_ONE.GetEntry(i_entry)

    run_number=chain_ONE.run_number
    lumi_block=chain_ONE.lumi_block
    pileup = read_json.pileup(run_number, lumi_block)
    pass_grl = read_json.pass_grl(run_number, lumi_block)

    if i_entry % 100000 == 0:
        print "First chain::Processing " + str(i_entry)

    hists_nowt[0].Fill(pileup) 
    hists_pvwt[0].Fill(pileup) 

    hists_pgrl[0].Fill(pass_grl) 

    pass_hlt = pass_trigger(chain_ONE)
    hists_trig[0].Fill(pass_hlt)
    if pass_hlt:
        hists_cbwt[0].Fill(pileup) 
#******************************************
#Fill histograms, second file
#******************************************
for i_entry in range(MIN_TWO, MAX_TWO + 1):
    chain_TWO.GetEntry(i_entry)

    if i_entry % 100000 == 0:
        print "First chain::Processing " + str(i_entry)

    pileup       =chain_TWO.PRIVX_mu
    pileup_weight=chain_TWO.PVWeights
    #pileup_weight = d_mu_wgt(int(pileup))

    hists_nowt[1].Fill(pileup, 1) 
    hists_pvwt[1].Fill(pileup, pileup_weight) 

    hists_pgrl[1].Fill(chain_TWO.pass_grl) 

    pass_hlt = pass_trigger(chain_TWO)
    hists_trig[1].Fill(pass_hlt)
    if pass_hlt:
        hists_cbwt[1].Fill(pileup, chain_TWO.combined_wt) 
#******************************************
#Save histograms
#******************************************
ofile=ROOT.TFile(OUTPUT, "RECREATE")
save_histograms(hists_nowt)
save_histograms(hists_pvwt)
save_histograms(hists_cbwt)
save_histograms(hists_pgrl)
save_histograms(hists_trig)
ofile.Close()
#******************************************
#******************************************

