import ROOT

import collections
#---------------------------------------------
#Load files
#---------------------------------------------
FILESDIR="/data/atlasb7/grid/data15a16/NTUP/Classification/"
PROC_DIR="user.acampove.undefined_TruthDecay_002.300203.e4889_a766_a845_r8423_p3254_BsJpsiPhi.root"

chain=ROOT.TChain("decays")
chain.Add("%s/%s/output*.root" % (FILESDIR, PROC_DIR) )

chain.SetBranchStatus("*", 0)
chain.SetBranchStatus("decay", 1)

d_decay_nentries=dict()
d_nentries_decay=dict()
#---------------------------------------------
#Fill dictionary with decay multiplicity
#---------------------------------------------
chain_size=chain.GetEntries()
for i_entry, entry in enumerate(chain):
    if i_entry % 100000 == 0:
        print("Processing %d/%d." % (i_entry, chain_size) )

    #if i_entry > 1000:
    #    break

    decay=str(entry.decay)
    if decay not in d_decay_nentries:
        d_decay_nentries[decay]=1
    else:
        d_decay_nentries[decay]+=1
#---------------------------------------------

#---------------------------------------------
for decay in d_decay_nentries:
    nentries=d_decay_nentries[decay]
    if nentries not in d_nentries_decay:
        d_nentries_decay[nentries]=[decay]
    else:
        d_nentries_decay[nentries].append(decay)
#---------------------------------------------
#Dump decays in textfile
#---------------------------------------------
od_nentries_decay=collections.OrderedDict( sorted(d_nentries_decay.items(), reverse=True) )

ofile=open("decays.txt", "w")
for nentries in od_nentries_decay:
    l_decay=od_nentries_decay[nentries]
    for decay in l_decay:
        ofile.write("{0:<80}{1:>15}\n".format(decay, nentries) )
        
ofile.close()
#---------------------------------------------
#---------------------------------------------

