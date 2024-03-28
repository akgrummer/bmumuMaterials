import ROOT

import json
import os

#*******************************************************
#Add files to chain, turn off all branches, except the
#ones needed.
#*******************************************************
FILES="/nfs/monet_3/home/campoverde/Data/Production_MC_Ntuple/Bmumu/*.root"

chain=ROOT.TChain("T_mv")
chain.Add(FILES)

chain.SetBranchStatus("*", 0)
chain.SetBranchStatus("PRIVX_mu", 1)
chain.SetBranchStatus("PVWeights", 1)
#*******************************************************
#Fill dictionary
#*******************************************************
d_mu_wt=dict()

for i_entry, entry in enumerate(chain):
    if i_entry % 10000 == 0:
        print("Processing event %d." % i_entry)

    pileup=entry.PRIVX_mu
    weight=entry.PVWeights

    d_mu_wt[int(pileup)]=weight
#*******************************************************
#Save as JSON
#*******************************************************
JSON_DIR="json"
if not os.path.isdir(JSON_DIR):
    os.mkdir(JSON_DIR)

ofile=open("%s/mu_wgt.json" % JSON_DIR, "w")
json.dump(d_mu_wt, ofile)
ofile.close()
#*******************************************************
#*******************************************************

