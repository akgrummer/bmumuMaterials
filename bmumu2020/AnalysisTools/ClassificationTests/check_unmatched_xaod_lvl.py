import ROOT

import utils
import atlas
#**************************************************
#Open files
#**************************************************
ROOT.gROOT.SetBatch()
FILES="/nfs/monet_3/home/campoverde/Data/Trees/xAOD_Truth_Matching/*.root"

ch_match=ROOT.TChain("tree")
ch_match.Add(FILES)
#**************************************************
#Make structures
#**************************************************
map_id=ROOT.std.map("int, unsigned int")() #PDGID-frequency dictionary for truth particles when only one match is found

d_nmatch={0:0, 1:0}
#**************************************************
#Make histograms
#**************************************************
h_nmatch=utils.GetHistogram("h_nmatch", "", 4, 2, 0, 2, title_x="Number of Matches", title_y = "Entries/1")

h_dr=utils.GetHistogram("h_dr", "", 4, 100, 0, 0.01, title_x="#Delta R", title_y = "Entries/1e-4")

h_id_freq=utils.GetHistogram("h_id_freq", "", 4, 1, 0, 1, title_x="PDG ID", title_y = "Frequency")
#**************************************************
#Loop and fill histograms
#**************************************************
for entry in ch_match:
    r_pt = entry.reco_pt
    r_eta= entry.reco_eta
    r_phi= entry.reco_phi

    t_pt = entry.truth_pt
    t_eta= entry.truth_eta
    t_phi= entry.truth_phi

    t_id   = entry.truth_id
    dr     = entry.dr
    status = entry.status

    h_nmatch.Fill(status)

    if status == 0: 
        d_nmatch[1] += 1
    else:
        d_nmatch[0] += 1

    if status == 0:
        h_dr.Fill(dr)
        if t_id in map_id:
            map_id[t_id]+=1
        else:
            map_id[t_id]=1
#**************************************************
#Histogram with PDGID-frequency
#**************************************************
for entry in map_id:
    h_id_freq.Fill("%d" % entry.first, entry.second)

utils.fix_hist_errors(h_id_freq)
#**************************************************
#Save histograms
#**************************************************
utils.SaveHistograms([h_nmatch], "Plots/truth_matches", "Simulation", "")

utils.SaveHistograms([h_dr] , "Plots/dr"   , "Simulation", "")

utils.SaveHistograms([h_id_freq] , "Plots/id_freq"   , "Simulation", "")
#**************************************************
#Print information
#**************************************************
print("{0:10}{1:10}".format("n Matches", "Frequency") )
for nmatches in d_nmatch:
    frequency = d_nmatch[nmatches]
    print("{0:10}{1:10}".format(nmatches, frequency) )

print("Matched particles: %d" % map_id.size())

print("{0:10}{1:10}".format("PDG ID", "n Matches") )
for entry in map_id:
    print("{0:10}{1:10}".format(entry.first, entry.second) )
print("First match out of two--------------------------------------------")
#**************************************************
#**************************************************

