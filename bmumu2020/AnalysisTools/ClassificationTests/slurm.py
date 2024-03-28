import ROOT

import utils

import subprocess
import os
import sys
import shutil
import glob
import math
import time
import json
import re

import split 

args_steer = sys.argv
ROOT.gROOT.SetBatch(True)
#***********************************************************
#Makes directories and sets variables related to output and
#error files
#***********************************************************
def prepare_log_dirs(JOB_NAME):
    global LOG_DIR
    global ERR_DIR
    global SJ_NAME

    LOG_DIR="-o%s/%%j.out" % JOB_NAME
    ERR_DIR="-e%s/%%j.err" % JOB_NAME
    SJ_NAME="-J %s" % JOB_NAME
        
    if not os.path.isdir(JOB_NAME):
        os.mkdir(JOB_NAME)

    for FILE in glob.glob("%s/*" % JOB_NAME):
        os.remove(FILE) 
#***********************************************************
#Do preliminary checks
#***********************************************************
def check():
    if len(args_steer) < 2 :
        print("steer.py::Usage:") 
        print("     steer.py  setting")
        print("     steer.py  test nevents setting")
        exit(1)
    elif args_steer[1] not in l_settings:
        print("steer.py::Wrong first argument:\"%s\"." % args_steer[1])
        print("  Arguments introduced: %s" % str(args_steer) )
        exit(1)

    if args_steer[1] == "test" and len(args_steer) < 4:
        print("steer.py::Usage:")
        print("     steer.py  test nevents setting")
        exit(1)
    elif args_steer[1] == "test" and args_steer[3] not in l_settings:
        print("steer.py::Wrong setting: \"%s\"" % args_steer[3])
        exit(1)

    if args_steer[1] == "test":
        try:
            NEVENTS = int(args_steer[2])
        except Exception as e:
            print("Cannot interpret %s as a number of events." % args_steer[2])
            exit(1)

    if len( glob.glob(d_arg["FILE"]) ) <= 0:
        print("steer.py::File %s not found." % d_arg["FILE"] )
        exit(1)
#***********************************************************
#Run local test over given number of events
#***********************************************************
def RunTest():
    print("Running test.")
    subprocess.call(["python", d_arg["EXECUTABLE"], "1", "output.root", d_arg["TYPE"] ])
#***********************************************************
#Get arguments and save them in dictionary 
#***********************************************************
l_settings=["test", "bsmumu", "bplus", "bsjpsiphi"]
d_arg=dict()

if args_steer[1] == "test":
    d_arg["TEST"]   = "1"
    d_arg["NEVENTS"]= args_steer[2]
    d_arg["TYPE"]   = args_steer[3] 
else:
    d_arg["TEST"]  = "0"
    d_arg["TYPE"]  = args_steer[1]

#d_arg["EXECUTABLE"] = "find_unmatched.py"
d_arg["EXECUTABLE"] = "classify_matched.py"
d_arg["OUTPUTFILE"] = "output_%s.root" % d_arg["TYPE"] 
d_arg["CAND_TREE"]  = "T_mv"
d_arg["DECAY_TREE"] = "TRUTHDECAY"
d_arg["NJOBS"]      = 100
d_arg["JSON_DIR"]   = "Json"

JOB_NAME="%s" % (d_arg["TYPE"])
#***********************************************************
#Specify directory names
#***********************************************************
#SAMPLES_DIR="/nfs/monet_3/home/campoverde/Data/user.acampove.undefined_TruthDecay_002.300203.e4889_a766_a845_r8423_p3254/"
#BMUMU_SAMPLE="user.acampove.undefined_TruthDecay_002.300203.e4889_a766_a845_r8423_p3254_Bmumu.root"
#BPLUS_SAMPLE="user.acampove.undefined_TruthDecay_002.300203.e4889_a766_a845_r8423_p3254_BpJpsiKp.root"
#BSJPSIPHI_SAMPLE="user.acampove.undefined_TruthDecay_002.300203.e4889_a766_a845_r8423_p3254_BsJpsiPhi.root"

SAMPLES_DIR="/nfs/moroni_7/data/atlasb7/grid/BpJpsiKplus/xAOD15_ac/"
BMUMU_SAMPLE="user.acampove.undefined_TruthClasiffication_001.300306.e4911_e5984_a875_r9364_r9315_p3371_Bmumu.root"
BPLUS_SAMPLE="user.acampove.undefined_TruthClasiffication_001.300306.e4911_e5984_a875_r9364_r9315_p3371_BpJpsiKp.root"
BSJPSIPHI_SAMPLE="user.acampove.undefined_TruthClasiffication_001.300306.e4911_e5984_a875_r9364_r9315_p3371_BsJpsiPhi.root"

if d_arg["TYPE"] == "bsmumu":
    FILES_DIR="%s/%s/" % (SAMPLES_DIR, BMUMU_SAMPLE)
elif d_arg["TYPE"] == "bplus":
    FILES_DIR="%s/%s/" % (SAMPLES_DIR, BPLUS_SAMPLE)
elif d_arg["TYPE"] == "bsjpsiphi":
    FILES_DIR="%s/%s/" % (SAMPLES_DIR, BSJPSIPHI_SAMPLE)
else:
    print("Wrong type %s" % d_arg["TYPE"] )
    exit(1)

PROC_DIR=FILES_DIR.split("/")[-2]
#OUTDIR="/data/atlasb7/grid/data15a16/NTUP/No_Match/%s" % PROC_DIR 
OUTDIR="/data/atlasb7/grid/data15a16/NTUP/Classification/%s" % PROC_DIR 

print("Sending output to directory \"%s\"" % OUTDIR)
#***********************************************************
#Range of entries for each job
#***********************************************************
d_ijob_lfiles=dict()

l_FILES=glob.glob("%s/*.root*" % FILES_DIR)
d_ijob_lfiles=split.MakeGroups(l_FILES, d_arg["NJOBS"])
#***********************************************************
#Fill json object with settings and save. Saves the one
#that will be used, and the other for the record
#***********************************************************
if d_arg["TYPE"] == "bsmumu":
    d_arg["FILE"]="%s/*.root*" % FILES_DIR
elif d_arg["TYPE"]== "bplus":
    d_arg["FILE"]="%s/*.root*" % FILES_DIR
elif d_arg["TYPE"]== "bsjpsiphi":
    d_arg["FILE"]="%s/*.root*" % FILES_DIR
else:
    print("Wrong setting %s" % d_arg["TYPE"])
    exit(1)

check()

ARGS_DIR="json_args"
if not os.path.isdir(ARGS_DIR):
    os.mkdir(ARGS_DIR)

utils.dict_to_json(d_arg, "%s/arguments_%s.json" % (ARGS_DIR, JOB_NAME) )
utils.dict_to_json(d_ijob_lfiles, "%s/jobs_%s.json" % (ARGS_DIR, JOB_NAME) )
#***********************************************************
#Run test if requested 
#***********************************************************
if d_arg["TEST"] == "1": 
    RunTest()
    exit(0)
#***********************************************************
#Remove old output
#***********************************************************
for FILE in glob.glob("%s/*root" % OUTDIR):
    os.remove(FILE)
#***********************************************************
#Send job for each fragment.
#***********************************************************
prepare_log_dirs(JOB_NAME)

for i_job in d_ijob_lfiles: 
    l_call=["sbatch", SJ_NAME, LOG_DIR, ERR_DIR, "slurm.job", OUTDIR, str(i_job), d_arg["EXECUTABLE"], JOB_NAME ] 
    subprocess.call(l_call)
#***********************************************************
#***********************************************************

