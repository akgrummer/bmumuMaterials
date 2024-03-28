import ROOT

import atlas
import utils

import os
import glob
#***********************************
#Return merged histogram from list
#of files
#***********************************
def GetHistograms(FILES_PATH):
    chain=ROOT.TChain("particles")
    chain.Add(FILES_PATH)

    h_pt_resp_muon =utils.GetHistogram("h_pt_resp_muon", "Muons", 4, 100, -15, 15, title_x="100 * (Truth-Reco)/Reco", title_y = "Normalized/20MeV")
    h_pt_resp_kaon =utils.GetHistogram("h_pt_resp_kaon", "Kaons", 2, 100, -15, 15, title_x="100 * (Truth-Reco)/Reco", title_y = "Normalized/20MeV")
    
    h_eta_resp_muon=utils.GetHistogram("h_eta_resp_muon", "Muons", 4, 100, -15, 15, title_x="100 * (Truth-Reco)/Reco", title_y = "Normalized/20MeV")
    h_eta_resp_kaon=utils.GetHistogram("h_eta_resp_kaon", "Kaons", 2, 100, -15, 15, title_x="100 * (Truth-Reco)/Reco", title_y = "Normalized/20MeV")
    
    h_phi_resp_muon=utils.GetHistogram("h_phi_resp_muon", "Muons", 4, 100, -15, 15, title_x="100 * (Truth-Reco)/Reco", title_y = "Normalized/20MeV")
    h_phi_resp_kaon=utils.GetHistogram("h_phi_resp_kaon", "Kaons", 2, 100, -15, 15, title_x="100 * (Truth-Reco)/Reco", title_y = "Normalized/20MeV")

    for i_entry, entry in enumerate(chain):
        if i_entry % 10000 == 0:
            print("Processing entry %d" % i_entry)

        pt_resp  = 100. * (entry.truth_pt  - entry.reco_pt)  / entry.reco_pt
        eta_resp = 100. * (entry.truth_eta - entry.reco_eta) / entry.reco_eta
        phi_resp = 100. * (entry.truth_phi - entry.reco_phi) / entry.reco_phi

        if entry.truth_ID == 13:
            h_pt_resp_muon .Fill(pt_resp)
            h_eta_resp_muon.Fill(eta_resp)
            h_phi_resp_muon.Fill(phi_resp)
        else:
            h_pt_resp_kaon .Fill(pt_resp)
            h_eta_resp_kaon.Fill(eta_resp)
            h_phi_resp_kaon.Fill(phi_resp)

    return [(h_pt_resp_muon, h_pt_resp_kaon), (h_eta_resp_muon, h_eta_resp_kaon), (h_phi_resp_muon, h_phi_resp_kaon)]
#***********************************
#Save Histograms
#***********************************
def SaveHistograms(process):
    if process=="bsmumu":
        FILES_PATH="%s/%s/output*.root" % (PATH_DIR, BSMUMU_DIR)
    elif process == "bplus":
        FILES_PATH="%s/%s/output*.root" % (PATH_DIR, BPLUS_DIR)
    elif process == "bsjpsiphi":
        FILES_PATH="%s/%s/output*.root" % (PATH_DIR, BSJPSIPHI_DIR)

    l_hist=GetHistograms(FILES_PATH)

    if process == "bsmumu":
        utils.SaveHistograms([ l_hist[0][0] ], "Plots/%s_pt_resp"  % process, "Simulation Internal", "", normalize=True, log=True)
        utils.SaveHistograms([ l_hist[1][0] ], "Plots/%s_eta_resp" % process, "Simulation Internal", "", normalize=True, log=True)
        utils.SaveHistograms([ l_hist[2][0] ], "Plots/%s_phi_resp" % process, "Simulation Internal", "", normalize=True, log=True)
    else:
        utils.SaveHistograms([ l_hist[0][0] , l_hist[0][1] ], "Plots/%s_pt_resp"  % process, "Simulation Internal", "", normalize=True, log=True, legend=1)
        utils.SaveHistograms([ l_hist[1][0] , l_hist[1][1] ], "Plots/%s_eta_resp" % process, "Simulation Internal", "", normalize=True, log=True, legend=1)
        utils.SaveHistograms([ l_hist[2][0] , l_hist[2][1] ], "Plots/%s_phi_resp" % process, "Simulation Internal", "", normalize=True, log=True, legend=1)
#***********************************
#Define paths
#***********************************
PATH_DIR="/data/atlasb7/grid/data15a16/NTUP/No_Match/"

#BSMUMU_DIR="user.acampove.undefined_TruthDecay_002.300203.e4889_a766_a845_r8423_p3254_Bmumu.root"
#BPLUS_DIR="user.acampove.undefined_TruthDecay_002.300203.e4889_a766_a845_r8423_p3254_BpJpsiKp.root"
#BSJPSIPHI_DIR="user.acampove.undefined_TruthDecay_002.300203.e4889_a766_a845_r8423_p3254_BsJpsiPhi.root"

BSMUMU_DIR="user.acampove.undefined_TruthClasiffication_001.300306.e4911_e5984_a875_r9364_r9315_p3371_Bmumu.root"
BPLUS_DIR="user.acampove.undefined_TruthClasiffication_001.300306.e4911_e5984_a875_r9364_r9315_p3371_BpJpsiKp.root"
BSJPSIPHI_DIR="user.acampove.undefined_TruthClasiffication_001.300306.e4911_e5984_a875_r9364_r9315_p3371_BsJpsiPhi.root"

if not os.path.isdir(PATH_DIR):
    print("Cannot find directory %s" % PATH_DIR)
    exit(1)

if not os.path.isdir("%s/%s" % (PATH_DIR, BSMUMU_DIR) ):
    print("Cannot find directory %s" % (PATH_DIR, BSMUMU_DIR) )
    exit(1)

if not os.path.isdir("%s/%s" % (PATH_DIR, BPLUS_DIR) ):
    print("Cannot find directory %s" % (PATH_DIR, BPLUS_DIR) )
    exit(1)

if not os.path.isdir("%s/%s" % (PATH_DIR, BSJPSIPHI_DIR) ):
    print("Cannot find directory %s" % (PATH_DIR, BSJPSIPHI_DIR) )
    exit(1)
#***********************************
#Make histograms
#***********************************
ROOT.gROOT.SetBatch()

SaveHistograms("bsmumu")
SaveHistograms("bplus")
SaveHistograms("bsjpsiphi")
#***********************************
#***********************************

