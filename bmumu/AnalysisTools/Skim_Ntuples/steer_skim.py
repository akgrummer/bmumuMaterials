import ROOT

import subprocess
import os
import sys
import shutil
import glob
import time
import json
import re

#-----------------------------------------------------------
#Saves dictionary as JSON file
#-----------------------------------------------------------
def save_as_json(dictionary, filename):
    ofile=open(filename, "w")
    json.dump(dictionary, ofile)
    ofile.close()
#-----------------------------------------------------------
#Makes directories and sets variables related to output and
#error files
#-----------------------------------------------------------
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
#-----------------------------------------------------------
#Do preliminary checks
#-----------------------------------------------------------
def check():
    if len(args_steer) < 2:
        print("No arguments introduced")
        print("python steer_skim_slurm.py test Nevents Process DSID")
        print("python steer_skim_slurm.py Process DSID")
        exit(1)

    if args_steer[1] == "test":
        if len(args_steer) < 5:
            print("Not enough arguments introduced")
            print("python steer_skim_slurm.py test Nevents Process DSID")
            exit(1)

        if args_steer[4] not in l_process:
            print("Process introduced %s, not recognized" % args_steer[4])
            print("Processes: %s" % l_process)
            exit(1)
    elif args_steer[2] not in l_process:
        print("Process introduced %s, not recognized" % args_steer[1])
        print("Processes: %s" % l_process)
        exit(1)
#-----------------------------------------------------------
#Initialize
#-----------------------------------------------------------

args_steer = sys.argv
ROOT.gROOT.SetBatch()

l_dsid=list()

l_process=["Bmumu", "BpJpsiKp", "BsJpsiPhi", "BJpsiK", "BJpsiPi", "Bhh", "Bhmunu"]

#List of DSIDs for MC.
l_dsid1=["300426", "300430", "300404", "300405", "300438", "300406", "300437"]
l_dsid2=["300431", "300432", "300433", "300434", "300306", "300203", "300307"]

#List of starting strings for data.
if True:
    l_dsid.append("data15_13TeV.periodD.physics_Main")
    l_dsid.append("data15_13TeV.periodE.physics_Main")
    l_dsid.append("data15_13TeV.periodF.physics_Main")
    l_dsid.append("data15_13TeV.periodG.physics_Main")
    l_dsid.append("data15_13TeV.periodH.physics_Main")
    l_dsid.append("data15_13TeV.periodJ.physics_Main")

    l_dsid.append("data16_13TeV.periodA.physics_Main")
    l_dsid.append("data16_13TeV.periodB.physics_Main")
    l_dsid.append("data16_13TeV.periodC.physics_Main")


    l_dsid.append("data16_13TeV.periodD.BPHY8_NTUP")
    l_dsid.append("data16_13TeV.periodD.physics_Main.BPHY8_NTUP")

    l_dsid.append("data16_13TeV.periodE.BPHY8_NTUP")
    l_dsid.append("data16_13TeV.periodE.physics_Main.BPHY8_NTUP")

    l_dsid.append("data16_13TeV.periodF.BPHY8_NTUP")
    l_dsid.append("data16_13TeV.periodF.physics_Main.BPHY8_NTUP")

    l_dsid.append("data16_13TeV.periodG.BPHY8_NTUP")
    l_dsid.append("data16_13TeV.periodG.physics_Main.BPHY8_NTUP")

    l_dsid.append("data16_13TeV.periodI.BPHY8_NTUP")
    l_dsid.append("data16_13TeV.periodI.physics_Main.BPHY8_NTUP")

    l_dsid.append("data16_13TeV.periodK.BPHY8_NTUP")
    l_dsid.append("data16_13TeV.periodK.physics_Main.BPHY8_NTUP")

    l_dsid.append("data16_13TeV.periodL.BPHY8_NTUP")
    l_dsid.append("data16_13TeV.periodL.physics_Main.BPHY8_NTUP")

l_dsid=l_dsid + l_dsid1 + l_dsid2

check()
#-----------------------------------------------------------
#Get arguments and save them in dictionary 
#-----------------------------------------------------------
d_arg=dict()

if args_steer[1] == "test":
    d_arg["TEST"]   = "1"
    d_arg["NEVENTS"]= args_steer[2]
    d_arg["DSID"]   = args_steer[3]
    d_arg["PROCESS"]= args_steer[4] 
else:
    d_arg["TEST"]   = "0"
    d_arg["DSID"]   = args_steer[1]
    d_arg["PROCESS"]= args_steer[2]

d_arg["EXECUTABLE"] = "skim_trees.py"
d_arg["OUTPUTFILE"] = "output_%s_%s.root" % (d_arg["DSID"], d_arg["PROCESS"])
d_arg["TREENAME"]   = "T_mv"
d_arg["NFILES"]     = "1" 
#-----------------------------------------------------------
#Specify directory names
#-----------------------------------------------------------
#PATH="/data/atlasb9/local/AC/MC16_v3/"
PATH="/nfs/monet_3/home/campoverde/Test/Test_001/build/x86_64-debian8-gcc62-opt/jobOptions/BsmumuNtupleMaker/"

DIR_PATH="%s/*%s*%s" % (PATH, d_arg["DSID"], d_arg["PROCESS"])
l_input_dir=glob.glob(DIR_PATH)

if len(l_input_dir) != 1 and args_steer[1] != "test":
    print("Did not find one and only one input directory in \"%s\"." % DIR_PATH)
    print(l_input_dir)
    exit(1)

INPUT_DIR=l_input_dir[0]
if "NTUP" in INPUT_DIR:
    OUTPUT_DIR=INPUT_DIR.replace("NTUP", "FNTUP")
else:
    OUTPUT_DIR=INPUT_DIR + "_skimmed"

JOB_NAME="%s_%s_skimming" % (d_arg["DSID"], d_arg["PROCESS"])

d_arg["FILE"]="%s/*.root*" % INPUT_DIR 

print("Sending output to directory \"%s\"" % OUTPUT_DIR)
#-----------------------------------------------------------
#Make lists with files
#-----------------------------------------------------------
d_jobs=dict()
l_FILE=glob.glob("%s/*.root*" % INPUT_DIR)
i_job = -1 
nfiles= 0
for i_FILE, FILE in enumerate(l_FILE):
    if i_FILE % int(d_arg["NFILES"]) == 0:
        i_job+=1
        d_jobs[i_job]=list()

    d_jobs[i_job].append(FILE)
    nfiles+=1

if nfiles == 0:
    print("No files found in %s." % INPUT_DIR)
    exit(1)

print("Found %d files." % nfiles)
print("Files in list: %d" % len(l_FILE) )
#-----------------------------------------------------------
#Fill json object with settings and save. Saves the one
#that will be used, and the other for the record
#-----------------------------------------------------------
ARGS_DIR="json_args"
if not os.path.isdir(ARGS_DIR):
    os.mkdir(ARGS_DIR)

save_as_json(d_arg, "%s/arguments_%s.json" % (ARGS_DIR, JOB_NAME) )
save_as_json(d_jobs, "%s/jobs_%s.json" % (ARGS_DIR, JOB_NAME) )
#-----------------------------------------------------------
#Run test if requested 
#-----------------------------------------------------------
if d_arg["TEST"] == "1": 
    print("Running test.")
    subprocess.call(["python", d_arg["EXECUTABLE"], "0", "output_test.root", JOB_NAME])
    OUTPUT_PATH="%s_skimmed/" % INPUT_DIR
    if not os.path.isdir(OUTPUT_PATH):
        os.mkdir(OUTPUT_PATH)

    TARGET_PATH="%s/output_test.root" % OUTPUT_PATH
    if os.path.isfile(TARGET_PATH):
        os.remove(TARGET_PATH)

    shutil.move("output_test.root", OUTPUT_PATH)
    
    exit(0)
#-----------------------------------------------------------
#Remove old output
#-----------------------------------------------------------
for FILE in glob.glob("%s/*.root*" % OUTPUT_DIR):
    if os.path.isfile(FILE):
        os.remove(FILE)
#-----------------------------------------------------------
#Send job for each fragment.
#-----------------------------------------------------------
prepare_log_dirs(JOB_NAME)

for i_job in d_jobs: 
    l_call=["sbatch", SJ_NAME, LOG_DIR, ERR_DIR, "split.job", OUTPUT_DIR, str(i_job), d_arg["EXECUTABLE"], JOB_NAME ] 
    subprocess.call(l_call)
#-----------------------------------------------------------
#-----------------------------------------------------------

