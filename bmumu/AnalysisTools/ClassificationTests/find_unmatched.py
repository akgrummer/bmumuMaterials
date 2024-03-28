import ROOT

import os
import glob
import sys
import collections
import json
import array

import atlas
import utils
import settings

#******************************************
#Returns matching truth particles as the
#tuples introduced, plus one extra entry
#for the distance to the reco particle and
#the reco particle as:
# (Truth, Decay, PDGID, status, distance, Reco)
#******************************************
def TruthMatch(l_truth_particles, reco_muon1, reco_muon2, reco_kaon1=ROOT.TVector3(), reco_kaon2=ROOT.TVector3() ):
    d_muon1_particles=dict()
    d_muon2_particles=dict()
    d_kaon1_particles=dict()
    d_kaon2_particles=dict()
    
    for truth_particle in l_truth_particles:
        PDGID=truth_particle[2]
        status=truth_particle[3]

        if status != 1:
            continue

        obj=ROOT.HepPDT.ParticleID(PDGID)

        if abs(PDGID) == 13:
            DR_mu1 = reco_muon1.DeltaR(truth_particle[0])
            d_muon1_particles[DR_mu1] = truth_particle

        if abs(PDGID) == 13:
            DR_mu2 = reco_muon2.DeltaR(truth_particle[0])
            d_muon2_particles[DR_mu2] = truth_particle

        if FIRST_KAON and obj.isHadron() and not obj.hasCharm() and not obj.hasBottom():
            DR_kaon = reco_kaon1.DeltaR(truth_particle[0])
            d_kaon1_particles[DR_kaon] = truth_particle

        if BOTH_KAONS and obj.isHadron() and not obj.hasCharm() and not obj.hasBottom():
            DR_kaon = reco_kaon2.DeltaR(truth_particle[0])
            d_kaon2_particles[DR_kaon] = truth_particle

    if len(d_muon1_particles) == 0 or len(d_muon2_particles) == 0: 
        print("No Muon found for matching")
        return []

    if FIRST_KAON and len(d_kaon1_particles) == 0: 
        print("No Kaon found for matching")
        return []

    if BOTH_KAONS and len(d_kaon2_particles) == 0:
        print("No Kaon found for matching")
        return []

    od_muon1_particles=collections.OrderedDict( sorted(d_muon1_particles.items()) )
    od_muon2_particles=collections.OrderedDict( sorted(d_muon2_particles.items()) )
    od_kaon1_particles=collections.OrderedDict( sorted(d_kaon1_particles.items()) )
    od_kaon2_particles=collections.OrderedDict( sorted(d_kaon2_particles.items()) )

    t_muon1_d = od_muon1_particles.items()[0][0]
    t_muon1_p = od_muon1_particles.items()[0][1]
    t_muon1_p = t_muon1_p + (t_muon1_d, reco_muon1)

    t_muon2_d = od_muon2_particles.items()[0][0]
    t_muon2_p = od_muon2_particles.items()[0][1]
    t_muon2_p = t_muon2_p + (t_muon2_d, reco_muon2)
    
    t_kaon1_p=tuple()
    if FIRST_KAON:
        t_kaon1_d = od_kaon1_particles.items()[0][0]
        t_kaon1_p = od_kaon1_particles.items()[0][1]
        t_kaon1_p = t_kaon1_p + (t_kaon1_d, reco_kaon1)

    t_kaon2_p=tuple()
    if BOTH_KAONS:
        t_kaon2_d = od_kaon2_particles.items()[0][0]
        t_kaon2_p = od_kaon2_particles.items()[0][1]
        t_kaon2_p = t_kaon2_p + (t_kaon2_d, reco_kaon2)

    return [t_muon1_p, t_muon2_p, t_kaon1_p, t_kaon2_p]
#******************************************
#Do tests for result of matching
#******************************************
def Check_Matching(muon1, muon2, kaon1, kaon2, event_number):
    d_muon1 = muon1[4]
    d_muon2 = muon2[4]
    d_kaon1 = 0
    d_kaon2 = 0

    if FIRST_KAON:
        d_kaon1 = kaon1[4]

    if BOTH_KAONS:
        d_kaon2 = kaon2[4]

    geo_match_muon1 = d_muon1 < MATCH_RADIUS 
    geo_match_muon2 = d_muon2 < MATCH_RADIUS 
    geo_match_kaon1 = True
    geo_match_kaon2 = True
    
    if FIRST_KAON:
        geo_match_kaon1 = d_kaon1 < MATCH_RADIUS
        
    if BOTH_KAONS:
        geo_match_kaon2 = d_kaon2 < MATCH_RADIUS

    pt_match_muon1 = abs(1 - muon1[0].Pt() / muon1[5].Pt()) < PT_TOL 
    pt_match_muon2 = abs(1 - muon2[0].Pt() / muon2[5].Pt()) < PT_TOL
    pt_match_kaon1 = True
    pt_match_kaon2 = True
    
    if FIRST_KAON:
        pt_match_kaon1 = abs(1 - kaon1[0].Pt() / kaon1[5].Pt()) < PT_TOL

    if BOTH_KAONS:
        pt_match_kaon2 = abs(1 - kaon2[0].Pt() / kaon2[5].Pt()) < PT_TOL

    geo_match = geo_match_muon1 and geo_match_muon2 and geo_match_kaon1 and geo_match_kaon2
    pt_match  = pt_match_muon1  and pt_match_muon2  and pt_match_kaon1  and pt_match_kaon2

    match = geo_match and pt_match 
    if match: 
        return True 
    
    d_evnt_kin[event_number]=[]
    
    if not geo_match_muon1 or not pt_match_muon1:
        r_muon1 = muon1[5] 
        l_particle=[r_muon1.Pt(), r_muon1.Eta(), r_muon1.Phi(), d_muon1, 13]
        d_evnt_kin[event_number].append(l_particle)

    if not geo_match_muon2 or not pt_match_muon2:
        r_muon2 = muon2[5] 
        l_particle=[r_muon2.Pt(), r_muon2.Eta(), r_muon2.Phi(), d_muon2, 13]
        d_evnt_kin[event_number].append(l_particle)

    if not geo_match_kaon1 or not pt_match_kaon1:
        r_kaon1 = kaon1[5] 
        l_particle=[r_kaon1.Pt(), r_kaon1.Eta(), r_kaon1.Phi(), d_kaon1, 32]
        d_evnt_kin[event_number].append(l_particle)

    if not geo_match_kaon2 or not pt_match_kaon2:
        r_kaon2 = kaon2[5] 
        l_particle=[r_kaon2.Pt(), r_kaon2.Eta(), r_kaon2.Phi(), d_kaon2, 32]
        d_evnt_kin[event_number].append(l_particle)

    if len(d_evnt_kin[event_number]) == 0:
        print("NO PARTICLES SAVED FOR EVENT: %d" % event_number)

    return match 
#******************************************
#Return list of tuples with (particle, decay, PDGID)
#where decay is either 0 or 1
#******************************************
def GetTruthParticles(truth_entry):
    ndecays = truth_entry.px.size()
    l_particles = list()
    for i_decay in range(0, ndecays):
        v_pT    = truth_entry.pt[i_decay]
        v_Theta = truth_entry.theta[i_decay]
        v_Phi   = truth_entry.phi[i_decay]
        v_PDGID = truth_entry.PDGid[i_decay]
        v_status= truth_entry.status[i_decay]
        
        for pT, Theta, Phi, PDGID, status in zip(v_pT, v_Theta, v_Phi, v_PDGID, v_status):
            particle = ROOT.TVector3()
            particle.SetPtThetaPhi(pT, Theta, Phi)

            tuple_particle = ( particle, i_decay, PDGID, status )
            
            l_particles.append(tuple_particle)

    return l_particles
#******************************************
#Load HepPDT libraries, etc.
#******************************************
print("Loading HepPDT libraries")

ROOT.gSystem.Load("libHepPID.so")
ROOT.gSystem.Load("libHepPDT.so")
ROOT.gROOT.ProcessLine('#include "HepPDT/ParticleID.hh"')
#******************************************
#Pick JSON file and initialize variables
#******************************************
print("Opening JSON files and initializing variables")

args=sys.argv
if len(args) < 3:
    print("Arguments introduced: %s" % args)
    exit(1)

IJOB=args[1]
OUTPUT=args[2]
JOBNAME=args[3]

json_file_args=open("json_args/arguments_%s.json" % JOBNAME)
json_args=json.load(json_file_args)
json_file_args.close()

ifile_json_lfile=open("json_args/jobs_%s.json" % JOBNAME)
json_lfile=json.load(ifile_json_lfile)
ifile_json_lfile.close()

l_FILE=json_lfile[IJOB]

FIRST_KAON = json_args["TYPE"] == "bplus"
BOTH_KAONS = json_args["TYPE"] == "bsjpsiphi"
JSON_DIR   = json_args["JSON_DIR"]

settings.FIRST_KAON = json_args["TYPE"] == "bplus"
settings.BOTH_KAONS = json_args["TYPE"] == "bsjpsiphi"
#******************************************
#Initialize variables, etc
#******************************************
print("Initializing remaining variables")

ROOT.gROOT.SetBatch()
MATCH_RADIUS=0.05
PT_TOL=0.15

if not os.path.isdir(JSON_DIR):
    os.mkdir(JSON_DIR)
#******************************************
#Open file and get trees
#******************************************
print("Opening files.")

cand_chain = ROOT.TChain(json_args["CAND_TREE"])
truth_chain= ROOT.TChain(json_args["DECAY_TREE"])

for FILE in l_FILE:
    cand_chain.Add(FILE)
    truth_chain.Add(FILE)
#******************************************
#Create objects/variables
#******************************************
print("Creating structures/containers.")

d_evnt_kin=dict()

matched_cand=0
unmatched_cand=0

s_events_nocuts=set()
s_events_cuts=set()
s_unmatch_events=set()

l_truth_reco_particle = list()

#Get dictionary between event number and
#entry index for decays tree.
d_event_number_index=utils.GetIndexes(truth_chain)
#******************************************
#Decide for how many entries will run.
#******************************************
HIGH_ENTRY=0
if json_args["TEST"] == "0":
    HIGH_ENTRY= cand_chain.GetEntries()
else:
    HIGH_ENTRY= int( json_args["NEVENTS"] )
#******************************************
#Fill structures
#******************************************
print("Looping over trees")

for i_entry in range(0, HIGH_ENTRY + 1):
    cand_chain.GetEntry(i_entry)
    reco_entry = cand_chain

    if i_entry % 10000 == 0:
        print("Processing entry %d" % i_entry)

    reco_event=reco_entry.event_number
    #*************************************
    #Apply cuts
    #*************************************
    s_events_nocuts.add(reco_event)

    if not settings.pass_cut(reco_entry):
        continue

    s_events_cuts.add(reco_entry.event_number)
    #*************************************
    #Test index consistency
    #*************************************
    if reco_event not in d_event_number_index:
        print("Truth event not found")
        continue

    index=d_event_number_index[reco_event]
    truth_chain.GetEntry(index)
    truth_event=truth_chain.event_number

    if reco_event != truth_event:
        print("Failing for candidate %d, event %d" % (reco_event, truth_event) )
        continue

    truth_entry = truth_chain 
    #*************************************
    #Match
    #*************************************
    reco_kaon1 = ROOT.TVector3()
    reco_kaon2 = ROOT.TVector3()
    reco_muon1 = ROOT.TVector3()
    reco_muon2 = ROOT.TVector3()

    reco_muon1.SetPtEtaPhi( reco_entry.Muon1_pT_orig, reco_entry.Muon1_eta_orig, reco_entry.Muon1_phi_orig)
    reco_muon2.SetPtEtaPhi( reco_entry.Muon2_pT_orig, reco_entry.Muon2_eta_orig, reco_entry.Muon2_phi_orig)

    l_truth_particles  = GetTruthParticles(truth_entry)
    if json_args["TYPE"] == "bsmumu":
        l_matched_particle = TruthMatch(l_truth_particles, reco_muon1, reco_muon2) 
    elif json_args["TYPE"] == "bplus":    
        reco_kaon1.SetPtEtaPhi( reco_entry.K_pT, reco_entry.K_eta, reco_entry.K_phi )
        l_matched_particle = TruthMatch(l_truth_particles, reco_muon1, reco_muon2, reco_kaon1) 
    elif json_args["TYPE"] == "bsjpsiphi":
        reco_kaon1.SetPtEtaPhi( reco_entry.KPlus_pT , reco_entry.KPlus_eta , reco_entry.KPlus_phi )
        reco_kaon2.SetPtEtaPhi( reco_entry.KMinus_pT, reco_entry.KMinus_eta, reco_entry.KMinus_phi)

        l_matched_particle = TruthMatch(l_truth_particles, reco_muon1, reco_muon2, reco_kaon1, reco_kaon2) 
    #*************************************
    #Test matches
    #*************************************
    match=False
    if len(l_matched_particle) == 0:
        print("Insuficient particles for event %d" % reco_entry.event_number)
    else:
        match=Check_Matching(l_matched_particle[0], l_matched_particle[1], l_matched_particle[2], l_matched_particle[3], reco_event)

    if match:
        matched_cand+=1
        for matched_particle in l_matched_particle:
            if matched_particle != ():
                l_truth_reco_particle.append(matched_particle)
    else:
        s_unmatch_events.add(reco_entry.event_number)
        unmatched_cand+=1
#******************************************
#Save matching information
#******************************************
print("Saving unmatched particles information")

ofile_match=open("%s/unmatched_%s.json" % (JSON_DIR, IJOB), "w")
json.dump(d_evnt_kin, ofile_match)
ofile_match.close()
#******************************************
#Plot quantities associated to matched pairs
#******************************************
print("Making Tree")

a_reco_pt=array.array('f', [0])
a_reco_eta=array.array('f', [0])
a_reco_phi=array.array('f', [0])
a_truth_pt=array.array('f', [0])
a_truth_eta=array.array('f', [0])
a_truth_phi=array.array('f', [0])
a_truth_ID=array.array('i', [0])

particles=ROOT.TTree("particles", "")
particles.Branch("reco_pt", a_reco_pt, "a_reco_pt/F")
particles.Branch("reco_eta", a_reco_eta, "a_reco_eta/F")
particles.Branch("reco_phi", a_reco_phi, "a_reco_phi/F")
particles.Branch("truth_pt", a_truth_pt, "a_truth_pt/F")
particles.Branch("truth_eta", a_truth_eta, "a_truth_eta/F")
particles.Branch("truth_phi", a_truth_phi, "a_truth_phi/F")
particles.Branch("truth_ID", a_truth_ID, "a_truth_ID/I")

for truth_reco_particle in l_truth_reco_particle:
    ID             = truth_reco_particle[2]
    truth_particle = truth_reco_particle[0]
    reco_particle  = truth_reco_particle[5]

    a_reco_pt[0]   = reco_particle.Pt()
    a_reco_eta[0]  = reco_particle.Eta()
    a_reco_phi[0]  = reco_particle.Phi()

    a_truth_pt[0]  = truth_particle.Pt()
    a_truth_eta[0] = truth_particle.Eta()
    a_truth_phi[0] = truth_particle.Phi()

    a_truth_ID[0]  = ID 

    particles.Fill()
#******************************************
#Save everything 
#******************************************
print("Saving tree.")

ofile_hist=ROOT.TFile(OUTPUT, "recreate")
particles.Write()
ofile_hist.Write()
#******************************************
#Print information
#******************************************
print("Candidates before cuts:%d" % cand_chain.GetEntries())
print("")
print("Matched candidates:%d" % matched_cand)
print("Unmatched candidates:%d" % unmatched_cand)
print("")
print("Number of events before cuts:%d" % len(s_events_nocuts) )
print("Number of events after cuts:%d" % len(s_events_cuts) )
print("Number of events after cuts and with matched candidates:%d" % len(s_events_cuts.difference(s_unmatch_events)) )
print("Number of events after cuts and without matched candidates:%d" % len(s_unmatch_events) )
print("Entries in JSON file: %d" % len(d_evnt_kin) )
#******************************************
#******************************************

