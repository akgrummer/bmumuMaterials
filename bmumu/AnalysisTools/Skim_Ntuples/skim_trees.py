import ROOT
import os
import sys
import json
import array
import subprocess

import background_classification
import validation
#-------------------------------------------
#Should we run background classification code?
#Yes if decays tree is in input file.
#-------------------------------------------
def ClassifyTruth(l_FILES):
    ifile=ROOT.TFile(l_FILES[0])
    l_keys=ifile.GetListOfKeys()
    for key in l_keys:
        obj=key.ReadObj()
        if obj.GetName() == DECAY_TREE_NAME:
            return True

    return False
#-------------------------------------------
#Check if everything is where it should be.
#-------------------------------------------
def check():
    if not os.path.isdir(JSON_DIR):
        print("skim_trees.py::Cannot find directory %s" % JSON_DIR)
        exit(1)

    args_file="%s/arguments_%s.json" % (JSON_DIR, JOBNAME)
    if not os.path.isfile(args_file):
        print("skim_trees.py::Cannot find file with arguments, %s" % args_file)
        exit(1)

    jobs_file="%s/jobs_%s.json" % (JSON_DIR, JOBNAME)
    if not os.path.isfile(jobs_file):
        print("skim_trees.py::Cannot find file with arguments, %s" % jobs_file)
        exit(1)
#-------------------------------------------
#Applicuts for skimming
#-------------------------------------------
def pass_cut(entry):
    BMeson=True
    JPsi=True
    Phi=True
    Muon=True
    Kaon=True
    event_qual1   =entry.pass_grl and not entry.err_pixel and not entry.err_sct 
    event_qual2   =not entry.err_trt and not entry.err_lar and not entry.err_tile and not entry.err_muon and not entry.err_bitset 
    event_quality = event_qual1 and event_qual2

    if PROCESS == "BpJpsiKp" or PROCESS == "BJpsiK":
        Kaon = abs(entry.K_eta) < 2.5 and entry.K_pass == 1
        JPsi = (entry.Jpsi_fitChi2 / entry.Jpsi_fitNDF) < 13 and (entry.Jpsi_mass > 2900 and entry.Jpsi_mass < 3300) 
    elif PROCESS == "BsJpsiPhi":
        Kaon_quality = entry.KPlus_pass == 1 and entry.KMinus_pass == 1
        Kaon_eta     = abs(entry.KPlus_eta) < 2.5 and abs(entry.KMinus_eta) < 2.5 
        Kaon_pT      = entry.KPlus_pT > 800 and entry.KMinus_pT > 800
        Kaon         = Kaon_quality and Kaon_eta and Kaon_pT

        Phi  = entry.phi_mass > 959 and entry.phi_mass < 1079 
        JPsi = (entry.Jpsi_fitChi2 / entry.Jpsi_fitNDF) < 13 and (entry.Jpsi_mass > 2900 and entry.Jpsi_mass < 3300) 

    try:
        NEGATIVE_MASS  = entry.B_MUCALC_mass < 0 or entry.B_VTX_mass < 0
        IN_MASS_WINDOW = entry.B_MUCALC_mass > 4700 and entry.B_MUCALC_mass < 6000
        if PROCESS == "Bmumu" and (IN_MASS_WINDOW or NEGATIVE_MASS):
            B_mass_cut = True
        elif PROCESS != "Bmumu" and IN_MASS_WINDOW:
            B_mass_cut = True
        else:
            B_mass_cut = False
    except:
        print("skim_trees.py::pass_cut::Cannot apply mass cut at event %d" % entry.event_number)
        exit(1)

    BMeson_kinematics=entry.B_pT > 6000 and abs(entry.B_eta) < 2.5 and B_mass_cut
    BMeson_quality   =(entry.B_fitChi2 / entry.B_fitNDF) < 10
    BMeson           = BMeson_kinematics and BMeson_quality

    Muon_pT      = entry.Muon1_pT > 4000 and entry.Muon2_pT > 4000 
    Muon_eta     = abs(entry.Muon1_eta) < 2.5 and abs(entry.Muon2_eta) < 2.5 
    Muon_quality = entry.Muon1_isLoose and entry.Muon2_isLoose and entry.Muon1_accept and entry.Muon2_accept
    Muon         = Muon_pT and Muon_eta and Muon_quality

    return event_quality and BMeson and JPsi and Phi and Muon and Kaon
#-------------------------------------------
def print_arguments():
    print("Job index: %s" % IJOB)
    print("Output file: %s" % OUTPUT)
#-------------------------------------------
#Initialize
#-------------------------------------------
ROOT.gROOT.SetBatch()
set_event_number=ROOT.std.set("long long unsigned")()
JSON_DIR="json_args"
DECAY_TREE_NAME="TRUTHDECAY"
validation.VALIDATE=False
#-------------------------------------------
#Get arguments
#-------------------------------------------
args_validate=sys.argv
IJOB=args_validate[1]
OUTPUT=args_validate[2]
JOBNAME=args_validate[3]

check()

ifile_arg=open("%s/arguments_%s.json" % (JSON_DIR, JOBNAME) )
json_arg=json.load(ifile_arg)
ifile_arg.close()

ifile_jobs=open("%s/jobs_%s.json" % (JSON_DIR, JOBNAME) )
json_jobs =json.load(ifile_jobs)
ifile_jobs.close()

l_FILE=json_jobs[str(IJOB)]
if len(l_FILE) == 0:
    print("No files available for job %d" % IJOB)
    exit(1)

print_arguments()

PROCESS=json_arg["PROCESS"]
#-------------------------------------------
#Load trees
#-------------------------------------------
print("Loading chains")

chain_OLD_cand=ROOT.TChain("T_mv")
chain_OLD_evnt=ROOT.TChain("EventInfo")
chain_OLD_meta=ROOT.TChain("Metadata")

print("Working with:")
for FILE in l_FILE:
    chain_OLD_cand.Add(FILE)
    chain_OLD_evnt.Add(FILE)
    chain_OLD_meta.Add(FILE)
    print("  %s" % FILE)
#-------------------------------------------
#Should we do truth classification?
#If so, initialize variables.
#-------------------------------------------
chain_decay=ROOT.TChain(DECAY_TREE_NAME)
classify_truth=ClassifyTruth(l_FILE)

if classify_truth:
    print("Decay tree found, will do truth classification.")
    for FILE in l_FILE:
        chain_decay.Add(FILE)

    background_classification.chain_decay=chain_decay
    background_classification.PROCESS=PROCESS
    background_classification.FillEntryDictionary()
else:
    print("Could not find decay tree. Will not do truth classification.")
#-------------------------------------------
#Turn off branches that wont be needed
#clone and turn branches back on
#-------------------------------------------
print("Clone trees.")

chain_OLD_cand.SetBranchStatus("err_pixel", 0)
chain_OLD_cand.SetBranchStatus("err_sct", 0)
chain_OLD_cand.SetBranchStatus("err_trt", 0)
chain_OLD_cand.SetBranchStatus("err_lar", 0)
chain_OLD_cand.SetBranchStatus("err_tile", 0)
chain_OLD_cand.SetBranchStatus("err_muon", 0)
chain_OLD_cand.SetBranchStatus("err_bitset", 0)
chain_OLD_cand.SetBranchStatus("pass_grl", 0)

skim_file=ROOT.TFile(OUTPUT, "RECREATE")

chain_NEW_cand=None  
chain_NEW_evnt=None
chain_NEW_meta=None

while chain_NEW_cand==None:
    chain_NEW_cand=chain_OLD_cand.CloneTree(0)

while chain_NEW_evnt==None:
    chain_NEW_evnt=chain_OLD_evnt.CloneTree(0)

while chain_NEW_meta==None:
    chain_NEW_meta=chain_OLD_meta.CloneTree(0)


chain_OLD_cand.SetBranchStatus("err_pixel", 1)
chain_OLD_cand.SetBranchStatus("err_sct", 1)
chain_OLD_cand.SetBranchStatus("err_trt", 1)
chain_OLD_cand.SetBranchStatus("err_lar", 1)
chain_OLD_cand.SetBranchStatus("err_tile", 1)
chain_OLD_cand.SetBranchStatus("err_muon", 1)
chain_OLD_cand.SetBranchStatus("err_bitset", 1)
chain_OLD_cand.SetBranchStatus("pass_grl", 1)
#-------------------------------------------
#Set branch address for variables that need
#to be added/modified.
#-------------------------------------------
print("Add extra branches.")
#-------
print("   Commit branch.")
commit=subprocess.check_output(["git", "log", "--pretty=format:\"%H\"", "-1"])
str_skim_commit=ROOT.std.string(commit)
chain_NEW_meta.Branch("skim_commit", str_skim_commit)
#-------
print("   Candidate ---> Event index.")

event_index=array.array('i', [0])
chain_NEW_cand.Branch("event_index", event_index, "event_index/I")
#-------------------
str_decay=ROOT.std.string()
if classify_truth:
    chain_NEW_cand.Branch("decay", str_decay)
#-------------------------------------------
#Fill candidate tree 
#-------------------------------------------
print("Filling candidate tree.")

MAX_EVT=0
MAX_CHAIN=chain_OLD_cand.GetEntries()
if json_arg["TEST"] == "1":
    nevs=int(json_arg["NEVENTS"])
    MAX_EVT=nevs if nevs >= 0 and nevs <= MAX_CHAIN else MAX_CHAIN 
else:
    MAX_EVT=MAX_CHAIN

print("Looping over %d entries." % MAX_EVT)
for i_entry in range(0, MAX_EVT):
    chain_OLD_cand.GetEntry(i_entry)

    if i_entry % 1000 == 0:
        print("First chain::Processing %d entries." % i_entry)
        
    if not pass_cut(chain_OLD_cand):
        continue

    if classify_truth:
        decay=background_classification.GetDecayString(chain_OLD_cand)
        str_decay.erase()
        str_decay.append(decay)

    set_event_number.insert(chain_OLD_cand.event_number)
    event_index[0]=len(set_event_number) - 1

    skim_file.cd()
    chain_NEW_cand.Fill()

background_classification.Finalize()
#-------------------------------------------
#Fill event tree
#-------------------------------------------
print("Filling event tree.")

for i_entry, entry in enumerate(chain_OLD_evnt):
    if i_entry % 100000 == 0:
        print("Processing %d entries of event tree." % i_entry)

    if set_event_number.find(entry.event_number) == set_event_number.end():
        continue

    chain_NEW_evnt.Fill()
#-------------------------------------------
#Fill metadata tree
#-------------------------------------------
#print("Filling metadata tree.")

#for i_entry, entry in enumerate(chain_OLD_meta):
#    if i_entry % 10 == 0:
#        print("Processing %d entries of metadata tree." % i_entry)
#
#    chain_NEW_meta.Fill()
#-------------------------------------------
#Check candidate ---> Event index
#-------------------------------------------
print("Checking candidate-event tree event  numbers.")

for i_entry, entry in enumerate(chain_NEW_cand):
    index=entry.event_index
    chain_NEW_evnt.GetEntry(index)
    event_evt_num=chain_NEW_evnt.event_number
    candt_evt_num=chain_NEW_cand.event_number 

    if event_evt_num != candt_evt_num:
        print("Index between candidate and event trees is broken at entry %d" % i_entry)
        print("   Candidate event number %d" % event_evt_num)
        print("   Event event number %d" % candt_evt_num)
        exit(1)

print("Candidate ---> Event indexes OK")
#-------------------------------------------
#Save trees
#-------------------------------------------
print("Saving trees.")

skim_file.cd()

chain_NEW_cand.Write("", ROOT.TObject.kOverwrite)
chain_NEW_evnt.Write("", ROOT.TObject.kOverwrite)
chain_NEW_meta.Write("", ROOT.TObject.kOverwrite)

skim_file.Close()
#-------------------------------------------
#-------------------------------------------

