import ROOT

import utils
import atlas

import sys
import re
import os
#--------------------------------------
#Reformat decay string so that it does
#not contain radiation stuff.
#--------------------------------------
def clean_decay(process):
    reg_one="Jpsi\[mu\+:mu\+:mu-:mu-(:gamma)+\]"
    reg_two="B.*\[gamma:(B.*)\]"
    org_jps="Jpsi[mu+:mu-]"
    bplus_rad="[gamma:K+:K+:Jpsi[mu+:mu-]Jpsi]"
                 
    match_one=re.search(reg_one, process)
    if match_one:
        sub_proc=match_one.group(0)
        process=process.replace(sub_proc, org_jps)

    match_two=re.search(reg_two, process)
    if match_two:
        process=match_two.group(1)

    if bplus_rad in process:
        process=process.replace(bplus_rad, "[K+:Jpsi[mu+:mu-]]")

    return process 
#--------------------------------------
#Setup/Initialize eveything
#--------------------------------------
print("Setting up variables.")

ROOT.gROOT.SetBatch()
d_decay_lmass=dict()
d_decay_hmass=dict()
ndecays=0.
#--------------------------------------
#Open files (ADJUST INPUT FILES HERE)
#--------------------------------------
print("Opening files")

FILES_DIR="/data/atlasb7/grid/data15a16/NTUP/Classification/"

#BSMUMU_DIR="user.acampove.undefined_TruthDecay_002.300203.e4889_a766_a845_r8423_p3254_Bmumu.root"
#BPLUS_DIR="user.acampove.undefined_TruthDecay_002.300203.e4889_a766_a845_r8423_p3254_BpJpsiKp.root"
#BSJPSIPHI_DIR="user.acampove.undefined_TruthDecay_002.300203.e4889_a766_a845_r8423_p3254_BsJpsiPhi.root"

BSMUMU_DIR="user.acampove.undefined_TruthClasiffication_001.300306.e4911_e5984_a875_r9364_r9315_p3371_Bmumu.root"
BPLUS_DIR="user.acampove.undefined_TruthClasiffication_001.300306.e4911_e5984_a875_r9364_r9315_p3371_BpJpsiKp.root"
BSJPSIPHI_DIR="user.acampove.undefined_TruthClasiffication_001.300306.e4911_e5984_a875_r9364_r9315_p3371_BsJpsiPhi.root"

FILES=""
PROCESS=sys.argv[1]

if PROCESS == "bsmumu":
    FILES="%s/%s/output*.root" % (FILES_DIR, BSMUMU_DIR)
elif PROCESS == "bplus":
    FILES="%s/%s/output*.root" % (FILES_DIR, BPLUS_DIR)
elif PROCESS == "bsjpsiphi":
    FILES="%s/%s/output*.root" % (FILES_DIR, BSJPSIPHI_DIR)
else:
    print("Wrong process.")
    exit(1)

chain_decays=ROOT.TChain("decays")
chain_decays.Add(FILES)
#--------------------------------------
#Prepare output directory
#--------------------------------------
print("Preparing output directory.")

ROOT_DIR="Root"
if not os.path.isdir(ROOT_DIR):
    os.mkdir(ROOT_DIR)
#--------------------------------------
#Fill structure with decays
#--------------------------------------
print("Looping over %d entries." % chain_decays.GetEntries() )

for i_entry, entry in enumerate(chain_decays):
    if i_entry % 100000 == 0:
        print("Processing entry %d" % i_entry)

    decay=str(entry.decay).replace("/", "")
    decay=clean_decay(decay)

    if "[gamma:K+:K+:Jpsi[mu+:mu-]Jpsi]" in decay:
        print("Found %s" % decay)
        exit(1)

    Bmass=entry.Bmass

    if decay not in d_decay_lmass:
        d_decay_lmass[decay]=[Bmass]
        ndecays+=1
    else:
        d_decay_lmass[decay].append(Bmass)
#--------------------------------------
#Make histogram per decay
#--------------------------------------
print("Making histograms.")

idecay=0
for decay in d_decay_lmass:
    idecay+=1

    #print("Making histogram for: %s" % decay)
    
    h_mass_narrow = utils.GetHistogram("h_decay_%d_narrow" % idecay, decay, 4, 50, 4700, 5700, title_x="B Mass", title_y = "Entries/10MeV")
    h_mass_wide   = utils.GetHistogram("h_decay_%d_wide"   % idecay, decay, 4, 50, 3000, 5000, title_x="B Mass", title_y = "Entries/20MeV")
    d_decay_hmass[decay]=(h_mass_narrow, h_mass_wide)
#--------------------------------------
#Fill histograms
#--------------------------------------
print("Filling histograms.")

for decay in d_decay_lmass:
    idecay+=1

    if decay not in d_decay_hmass:
        continue

    l_mass=d_decay_lmass[decay] 
    for mass in l_mass:
        d_decay_hmass[decay][0].Fill(mass)
        d_decay_hmass[decay][1].Fill(mass)
#--------------------------------------
#Save histograms
#--------------------------------------
print("Saving histograms.")

ofile_hist=ROOT.TFile("%s/%s_components.root" % (ROOT_DIR, PROCESS), "recreate")

for decay in d_decay_hmass:
    hmass_narrow=d_decay_hmass[decay][0]
    hmass_wide  =d_decay_hmass[decay][1]
    
    hmass_narrow.Write()
    hmass_wide  .Write()

ofile_hist.Close()
#--------------------------------------
#--------------------------------------

