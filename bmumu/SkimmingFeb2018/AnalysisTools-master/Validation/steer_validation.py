import ROOT

import subprocess
import os
import sys
import shutil
import glob
import time
import json
import re

import utils

#******************************************
#Get names of branches that will be validated
#******************************************
def GetBranches(chain):
    s_branch = set()
    l_branch = chain.GetListOfBranches()
    for branch in l_branch:
        branch_name=branch.GetName()
        s_branch.add(branch_name)

    return s_branch
#******************************************
#Used to get rid of outliers in histogras
#******************************************
def TrimOutliers(hist):
    nbins = hist.GetNbinsX()
    nentries = hist.GetEntries()
    for i_bin in range(1, nbins + 1):
        bc = hist.GetBinContent(i_bin)
        if bc < 0.005 * nentries:
            hist.SetBinContent(i_bin, 0)

    return hist
#***********************************************************
#Get binning
#***********************************************************
def GetBinning(variable, chain, nentries):
    if re.search("Muon[1,2]_eLoss_.*", variable):
        return [0, 10000]

    if re.search(".*_eta$", variable):
        return [-3, 3]

    if re.search(".*_phi$", variable):
        return [-3.5, 3.5]

    if re.search("B_minChi2MuonsIPtoAnyPV", variable):
        return [-15, 15]

    if re.search("TRUTH_Jpsi_mass", variable):
        return [2500, 3500]

    if re.search("TRUTH_K_mass", variable):
        return [300, 700]


    if re.search("B_PV_Ref_cov_zz", variable):
        return [0, 0.01]

    if re.search("nphotons_*.", variable):
        return [0, 10]

    if re.search("TRUTH_B_mass", variable):
        return [5000, 6000]

    if re.search("TRUTH_MuMinus_mass", variable):
        return [50, 200]

    if re.search("TRUTH_B_vtx_[x,y]", variable):
        return [-10, 10]

    if variable == "Trigger_Matched":
        return [-0.5, 1.5]
    
    if variable == "lumi_block":
        return [0, 2000]

    if variable == "Jpsi_Lxy_err":
        return [0, 0.5]

    if variable == "Jpsi_Lxy":
        return [0, 8.0]

    if variable == "closeTrkDCA":
        return [-0.4, 0.4]

    if variable == "closeTrkDCAErr":
        return [0, 0.4]

    if variable == "closeTrkZCA":
        return [-0.4, 0.4]

    if variable == "closeTrkZCAErr":
        return [0, 0.4]

    if variable == "Muon1_matchChi2" or variable == "Muon2_matchChi2":
        return [0, 3]

    if variable == "Muon1_matchChi2OverDoF" or variable == "Muon2_matchChi2OverDoF":
        return [0, 3]

    if variable == "B_pT":
        return [7000, 40000]

    if variable == "B_IDtrks_DCA":
        return [-0.16, 0.16]

    if variable == "Bvtx3DIP":
        return [-0.02, 0.25]

    if variable == "BvtxDXSig":
        return [-2, 70]

    if variable == "chi2_PVSV_log3D":
        return [0, 10]

    if variable == "d0Max_err":
        return [0, 60e-3]

    if variable == "d0Max":
        return [-1, 1]

    if variable == "d0Min":
        return [-0.1, 0.1]
 
    if variable == "PRIVX_mu":
        return [0, 50]

    if variable == "KMinus_nTRToutliers" or variable == "KPlus_nTRToutliers":
        return [0, 10]

    if variable == "Lxy":
        return [0, 8]

    if variable == "Lxy_sig":
        return [-5, 10]

    if variable == "Lxy_err":
        return [0.02, 0.17]

    if variable == "Muon1_eLoss_mes" or variable == "Muon2_eLoss_mes":
        return [0, 0.02]

    if variable == "Muon1_trkMS_pT":
        return [0, 12000]

    if variable == "B_IDtrk1_nSCTHoles":
        return [-1, 3]

    if variable == "B_IDtrk1_nTRToutliers":
        return [-1, 5]

    if variable == "Muon1_eta":
        return [-2.5, 2.5]

    if variable == "B_MUCALC_mass" or variable == "B_VTX_mass":
        return [4500, 6000]

    if variable == "Muon1_trkComb_qoverp" or variable == "Muon1_trkMuonExtr_qoverp" or variable == "Muon1_trkMS_qoverp":
        return [0, 0.3e-3]

    if variable == "Muon2_trkComb_qoverp" or variable == "Muon2_trkMuonExtr_qoverp" or variable == "Muon2_trkMS_qoverp":
        return [-0.3e-3, 0]

    if variable == "Muon1_fitChi2" or variable == "Muon2_fitChi2":
        return [0, 200]

    if variable == "Muon1_trkComb_pT" or variable == "Muon2_trkComb_pT":
        return [3000, 14000]

    if variable == "Muon1_trkMS_pT" or variable == "Muon2_trkMS_pT":
        return [0, 10000]

    if variable == "properTime_err" or variable == "Jpsi_properTime_err":
        return [0, 0.3]

    if variable == "properTime" or variable == "Jpsi_properTime":
        return [0, 0.3]

    if variable == "MuSignedd0SigMin":
        return [-20, 20]

    if variable == "closeTrkNtrksChi2":
        return [0, 80]

    if variable == "B_pT_error":
        return [0, 5000]
    #****************************************************
    name_h = "h_temp_%s"  % variable

    h_temp = ROOT.TH1F(name_h, "", 100, 0, 0)

    chain.Draw("%s>>%s" % (variable, name_h), "", "", nentries)

    h_temp_trimmed  = TrimOutliers(h_temp)

    i_fb = h_temp_trimmed.FindFirstBinAbove(0)
    i_lb = h_temp_trimmed.FindLastBinAbove(0)

    dx = 0
    if i_fb == i_lb:
        dx = h_temp.GetBinWidth(1)

    low_edge  = h_temp.GetBinLowEdge(i_fb) - 3 * dx
    high_edge = h_temp.GetBinLowEdge(i_lb + 1) + 3 * dx

    return [low_edge, high_edge]
#***********************************************************
#Save binning
#***********************************************************
def SaveBinning(outputfile):
    print("Saving Binning")

    chain=ROOT.TChain(d_arg["TREENAME"])

    for FILE in glob.glob(d_arg["FILE"]):
        chain.Add(FILE)

    s_branches = GetBranches(chain)
    s_vetoed   = utils.txt_to_set("./Info/Vetoed.txt")
    s_variable = s_branches.difference(s_vetoed)

    d_binning = dict()
    for variable in s_variable:
        l_binning = GetBinning(variable, chain, 10000)
        d_binning[variable] = (l_binning[0], l_binning[1])

    utils.dict_to_json(d_binning, outputfile)
#***********************************************************
#Returns list of fragments for a given file
#***********************************************************
def GetFragments(FILENAME):
    chain = ROOT.TChain(d_arg["TREENAME"])
    for FILE in glob.glob(FILENAME):
        chain.Add(FILE)

    NENTRIES = chain.GetEntries()

    NFRAGMENTS=int(d_arg["NFRAGMENTS"])

    print("Found %d entries for %d fragments." % (NENTRIES, NFRAGMENTS) )

    D_ENTRIES = NENTRIES/float(NFRAGMENTS)
    MINENTRY = 0
    MAXENTRY = int(D_ENTRIES)

    l_fragments=list()
    for i_fragment in range(0, NFRAGMENTS):
        if i_fragment == NFRAGMENTS - 1:
            l_fragments.append( (MINENTRY, NENTRIES) )
            continue

        l_fragments.append( (MINENTRY, MAXENTRY) )

        MINENTRY=MAXENTRY+1
        MAXENTRY+=int(D_ENTRIES)

    return l_fragments
#***********************************************************
#Print variables
#***********************************************************
def print_variables():
    for SETTING, VALUE in d_arg.iteritems():
        print("%s   %s" % (SETTING, VALUE) )
#***********************************************************
#Do preliminary checks
#***********************************************************
def check():
    if len(args_steer) < 3 :
        print("steer.py::Usage:") 
        print("     steer.py  MC_SPECIFIER PROCESS_SPECIFIER")
        print("or to run tests:")
        print("     steer.py  test NEVENTS MC_SPECIFIER")
        exit(1)

    #Check for non-test
    if args_steer[1] != "test" and (args_steer[1] not in l_setting):
        print("steer.py::Wrong first argument:\"%s\"." % args_steer[1])
        print("  Arguments introduced: %s" % str(args_steer) )
        exit(1)
    elif args_steer[1] != "test" and (args_steer[2] not in l_process):
        print("steer.py::Wrong second argument:\"%s\"." % args_steer[2])
        print("  Arguments introduced: %s" % str(args_steer) )
        exit(1)

    #Checks when running test
    if args_steer[1] == "test" and len(args_steer) < 5:
        print("steer.py::Usage:")
        print("     steer.py test NEVENTS MC_SPECIFIER PROCESS_SPECIFIER")
        exit(1)
    elif args_steer[1] == "test" and (args_steer[3] not in l_setting):
        print("steer.py::Wrong setting: \"%s\"" % args_steer[3])
        exit(1)
    elif args_steer[1] == "test" and (args_steer[4] not in l_process):
        print("steer.py::Wrong setting: \"%s\"" % args_steer[4])
        exit(1)

    #Check if NEVENTS is really a number
    if args_steer[1] == "test":
        try:
            NEVENTS = int(args_steer[2])
        except Exception as e:
            print("Cannot interpret %s as a number of events." % args_steer[2])
            exit(1)

    if not os.path.isfile("clean.sh"):
       print("clean.sh script not found")
       exit(1)
#***********************************************************
#Run local test over given number of events
#***********************************************************
def RunTest():
    print("Running test.")
    subprocess.call(["python", d_arg["EXECUTABLE"] ])
#***********************************************************
#Clean previous output if any
#***********************************************************
subprocess.call(["./clean.sh"])
#***********************************************************
#Get arguments and save them as arguments.json
#***********************************************************
args_steer = sys.argv
ROOT.gROOT.SetBatch(True)

l_setting=["bsmumu", "bpluspi", "bsjpsiphi", "bpluskp", "bdpimunu", "bskmunu", "lambmunu"]
#l_process=["BpJpsiKp", "BpJpsiPi", "Bmumu", "Bmumu", "Bhh", "Bhmunu", "Bhmunu", "Bhmunu", "BsJpsiPhi"]
l_process=["BpJpsiK", "BpJpsiPi", "Bmumu", "Bmumu", "Bhh", "Bhmunu", "Bhmunu", "Bhmunu", "BsJpsiPhi"]

check()

d_arg=dict()

if args_steer[1] == "test":
    d_arg["TEST"] = "1"
    d_arg["NEVENTS"] = args_steer[2]
    d_arg["TYPE"] = args_steer[3] 
    d_arg["PROCESS"] = args_steer[4]
else:
    d_arg["TEST"] = "0"
    d_arg["TYPE"] = args_steer[1]
    d_arg["PROCESS"] = args_steer[2]

d_arg["EXECUTABLE"] = "Validate.py"
d_arg["OUTPUTFILE"] = "output_%s_%s.root" % (d_arg["TYPE"], d_arg["PROCESS"]) 
d_arg["TREENAME"]   = "T_mv"
d_arg["NFRAGMENTS"] = "30"

#---------------------------------
NTUP_DIR="/nfs/monet_3/home/campoverde/Data/Ntup_Validation_16_04_2018/"
if d_arg["TYPE"] == "bsmumu" and d_arg["PROCESS"] == "Bmumu":
    d_arg["FILE"]="%s/user.acampove.300426.BPHY8_NTUP_test2_04_26_18.e4889_e5984_a875_r9364_r9315_p3371_Bmumu.root/*.root" % NTUP_DIR
elif d_arg["TYPE"] == "bpluskp" and d_arg["PROCESS"] == "BpJpsiK":
    d_arg["FILE"]="%s/user.acampove.300404.BPHY8_NTUP_test2_04_26_18.e4862_e5984_a875_r9364_r9315_p3371_BJpsiK.root/*.root" % NTUP_DIR
elif d_arg["TYPE"] == "bsjpsiphi" and d_arg["PROCESS"] == "BsJpsiPhi":
    d_arg["FILE"]="%s/user.acampove.300438.BPHY8_NTUP_test2_04_25_18.e4922_e5984_a875_r9364_r9315_p3371_BsJpsiPhi.root/*.root" % NTUP_DIR
else:
    print("Wrong process/type.")
    exit(1)
#---------------------------------
if len(glob.glob(d_arg["FILE"])) <= 0:
    print("Cannot find any file in %s" % d_arg["FILE"])
    exit(1)

print_variables()

utils.dict_to_json(d_arg, "arguments.json")

SaveBinning("binning.json")
#***********************************************************
#Run test if needed
#***********************************************************
if d_arg["TEST"] == "1": 
    RunTest()
    exit(0)
#***********************************************************
#Create output directories
#***********************************************************
OUTP_DIR="Output_%s_%s" % (d_arg["TYPE"], d_arg["PROCESS"])
HIST_DIR="hist"
PLOT_DIR="plots_%s_%s" % (d_arg["TYPE"], d_arg["PROCESS"])
JSON_DIR="json_%s_%s" % (d_arg["TYPE"], d_arg["PROCESS"])

if not os.path.isdir(HIST_DIR):
    os.mkdir(HIST_DIR)

if not os.path.isdir(PLOT_DIR):
    os.mkdir(PLOT_DIR)

if not os.path.isdir(JSON_DIR):
    os.mkdir(JSON_DIR)
#***********************************************************
#Send job for each fragment.
#***********************************************************
l_fragment = GetFragments(d_arg["FILE"])

for fragment in l_fragment:
    MINEVNT=str(fragment[0])
    MAXEVNT=str(fragment[1])
    
    l_call=["sbatch", "split_validation.job", MINEVNT, MAXEVNT, d_arg["EXECUTABLE"], d_arg["TYPE"], d_arg["PROCESS"] ]
    subprocess.call(l_call)
#***********************************************************
#Wait untill all files are received
#***********************************************************
nfiles=0
while nfiles < int(d_arg["NFRAGMENTS"]):
    time.sleep(1)

    l_files=glob.glob("./%s/*.root" % OUTP_DIR)
    if nfiles != len(l_files):
        print("Received %d files." % len(l_files))

    nfiles=len(l_files)
#***********************************************************
#Merge and clean
#***********************************************************
subprocess.call(["group_files", str(d_arg["NFRAGMENTS"] )], cwd=OUTP_DIR)
subprocess.call(["merge_files"], cwd=OUTP_DIR)

HIST_TARGET="%s/%s" % (HIST_DIR, d_arg["OUTPUTFILE"] )
shutil.move("./%s/Merged_1.root" % (OUTP_DIR), HIST_TARGET )

l_json_files=glob.glob("*.json")
for json_file in l_json_files:
    os.rename(json_file, "%s/%s" % (JSON_DIR, json_file) )
#***********************************************************
#***********************************************************
