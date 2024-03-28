import ROOT

import subprocess
import os
import sys
import shutil
import glob
import time
import json
import re

args_steer = sys.argv
ROOT.gROOT.SetBatch(True)
#***********************************************************
#Returns list of fragments for a given file
#***********************************************************
def GetFragments(FILENAME):
    chain = ROOT.TChain(d_arg["TREENAME"])
    chain.Add(FILENAME)
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

    if len( glob.glob(d_arg["FILE_ONE"]) ) <= 0:
        print("steer.py::File %s not found." % d_arg["FILE_ONE"] )
        exit(1)

    if len( glob.glob(d_arg["FILE_TWO"]) ) <= 0:
        print("steer.py::File %s not found." % d_arg["FILE_TWO"] )
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
print("Cleaning current directory.")

if not os.path.isfile("clean.sh"):
    print("clean.sh script not found")
    exit(1)

subprocess.call(["./clean.sh"])
#***********************************************************
#Get arguments and save them as arguments.json
#***********************************************************
print("Picking up arguments")

l_settings=["test", "bsmumu", "bplus", "bsjpsiphi"]
d_arg=dict()

if args_steer[1] == "test":
    d_arg["NEVENTS"] = args_steer[2]
    d_arg["TYPE"] = args_steer[3] 
    d_arg["TEST"] = "1"
else:
    d_arg["TYPE"] = args_steer[1]
    d_arg["TEST"] = "0"

#d_arg["EXECUTABLE"] = "pileup.py"
d_arg["EXECUTABLE"] = "trig_eff.py"
d_arg["OUTPUTFILE"] = "output_%s.root" % d_arg["TYPE"] 
d_arg["TREENAME"]   = "T_mv"
d_arg["NFRAGMENTS"] = "30"

FILES_DIR_ONE="/nfs/monet_3/home/campoverde/Data/Data_Ntup_001/"
FILES_DIR_TWO="/nfs/monet_3/home/campoverde/Data/Production_MC_Ntuple/"

JSON_DIR="%s_json" % d_arg["TYPE"]

if d_arg["TYPE"] == "bsmumu":
    d_arg["FILE_ONE"]="%s/Bmumu/*.root" % FILES_DIR_ONE
    d_arg["FILE_TWO"]="%s/Bmumu_HLT_2mu6_bBmumu/*.root" % FILES_DIR_TWO
elif d_arg["TYPE"]== "bplus":
    d_arg["FILE_ONE"]="%s/BJpsiK/*.root" % FILES_DIR_ONE
    d_arg["FILE_TWO"]="%s/BJpsiK/*.root" % FILES_DIR_TWO
elif d_arg["TYPE"]== "bsjpsiphi":
    d_arg["FILE_ONE"]="%s/BsJpsiPhi/*.root" % FILES_DIR_ONE
    d_arg["FILE_TWO"]="%s/BJpsiPhi/*.root" % FILES_DIR_TWO
else:
    print("Wrong setting %s" % d_arg["TYPE"])
    exit(1)

check()

ofile=open("arguments.json", "w")
json.dump(d_arg, ofile)
ofile.close()
#***********************************************************
#Run test if needed
#***********************************************************
if d_arg["TEST"] == "1": 
    RunTest()
    exit(0)
#***********************************************************
#Make out and err directories
#***********************************************************
if not os.path.isdir("out"):
    os.mkdir("out")

if not os.path.isdir("err"):
    os.mkdir("err")
#***********************************************************
#Send job for each fragment.
#***********************************************************
print("Getting fragments.")

l_fragments_one = GetFragments(d_arg["FILE_ONE"])
l_fragments_two = GetFragments(d_arg["FILE_TWO"])

print("Submitting jobs.")
for fragment_one, fragment_two in zip(l_fragments_one, l_fragments_two):
    MINEVNT_ONE=str(fragment_one[0])
    MAXEVNT_ONE=str(fragment_one[1])

    MINEVNT_TWO=str(fragment_two[0])
    MAXEVNT_TWO=str(fragment_two[1])
    
    l_call=["sbatch", "split.job", MINEVNT_ONE, MAXEVNT_ONE, MINEVNT_TWO, MAXEVNT_TWO, d_arg["EXECUTABLE"]] 
    subprocess.call(l_call)
#***********************************************************
#Wait untill all files are received
#***********************************************************
print("Finished submission, checking jobs.")

nfiles=0
while nfiles < int(d_arg["NFRAGMENTS"]):
    time.sleep(1)

    l_files=glob.glob("./Output/*.root")
    if nfiles != len(l_files):
        print("Received %d files." % len(l_files))

    nfiles=len(l_files)
#***********************************************************
#Merge rename and save
#***********************************************************
subprocess.call(["group_files", str(d_arg["NFRAGMENTS"] )], cwd="./Output")
subprocess.call(["merge_files"], cwd="./Output")

OUTPUT_DIR="output_%s" % d_arg["TYPE"]
if not os.path.isdir(OUTPUT_DIR):
    os.mkdir(OUTPUT_DIR)

shutil.move("./Output/Merged_1.root", "%s/%s" % (OUTPUT_DIR, d_arg["OUTPUTFILE"]) )
#***********************************************************
#Save JSON files
#***********************************************************
if not os.path.isdir(JSON_DIR):
    os.mkdir(JSON_DIR)

l_json_files=glob.glob("*.json")
for json_file in l_json_files:
    os.rename(json_file, "./%s/%s" % (JSON_DIR, json_file) )
#***********************************************************
#***********************************************************

