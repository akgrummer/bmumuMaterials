import ROOT

import os
import glob
import sys
import collections
import operator
import json
import array

import atlas
import utils
import settings

#******************************************
#Returns list of decays corresponding to
#decay matched decay products.
#******************************************
def GetDecays(l_particles):
    s_idecay=set()

    for particle in l_particles:
        if particle != ():
            s_idecay.add(particle[1])

    return list(s_idecay)
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
            DR_kaon = reco_kaon1.DeltaR(truth_particle[0])
            d_kaon1_particles[DR_kaon] = truth_particle

            DR_kaon = reco_kaon2.DeltaR(truth_particle[0])
            d_kaon2_particles[DR_kaon] = truth_particle

    if len(d_muon1_particles) == 0 or len(d_muon2_particles) == 0: 
        print("No Muon found for matching")
        return []

    if FIRST_KAON and len(d_kaon1_particles) == 0: 
        print("No Kaon found for matching")
        return []

    if BOTH_KAONS and (len(d_kaon1_particles) == 0 and len(d_kaon2_particles) == 0):
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
        t_kaon1_d = od_kaon1_particles.items()[0][0]
        t_kaon1_p = od_kaon1_particles.items()[0][1]
        t_kaon1_p = t_kaon1_p + (t_kaon1_d, reco_kaon1)

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
        d_kaon1 = kaon1[4]
        d_kaon2 = kaon2[4]

    geo_match_muon1 = d_muon1 < MATCH_RADIUS 
    geo_match_muon2 = d_muon2 < MATCH_RADIUS 
    geo_match_kaon1 = True
    geo_match_kaon2 = True
    
    if FIRST_KAON:
        geo_match_kaon1 = d_kaon1 < MATCH_RADIUS
        
    if BOTH_KAONS:
        geo_match_kaon1 = d_kaon1 < MATCH_RADIUS
        geo_match_kaon2 = d_kaon2 < MATCH_RADIUS

    pt_match_muon1 = abs(1 - muon1[0].Pt() / muon1[5].Pt()) < PT_TOL 
    pt_match_muon2 = abs(1 - muon2[0].Pt() / muon2[5].Pt()) < PT_TOL
    pt_match_kaon1 = True
    pt_match_kaon2 = True
    
    if FIRST_KAON:
        pt_match_kaon1 = abs(1 - kaon1[0].Pt() / kaon1[5].Pt()) < PT_TOL

    if BOTH_KAONS:
        pt_match_kaon1 = abs(1 - kaon1[0].Pt() / kaon1[5].Pt()) < PT_TOL
        pt_match_kaon2 = abs(1 - kaon2[0].Pt() / kaon2[5].Pt()) < PT_TOL

    geo_match = geo_match_muon1 and geo_match_muon2 and geo_match_kaon1 and geo_match_kaon2
    pt_match  = pt_match_muon1  and pt_match_muon2  and pt_match_kaon1  and pt_match_kaon2

    match = geo_match and pt_match 
    if match: 
        return True 
    
    if not geo_match_muon1 or not pt_match_muon1:
        r_muon1 = muon1[5] 
        l_particle=[r_muon1.Pt(), r_muon1.Eta(), r_muon1.Phi(), d_muon1, 13]

    if not geo_match_muon2 or not pt_match_muon2:
        r_muon2 = muon2[5] 
        l_particle=[r_muon2.Pt(), r_muon2.Eta(), r_muon2.Phi(), d_muon2, 13]

    if not geo_match_kaon1 or not pt_match_kaon1:
        r_kaon1 = kaon1[5] 
        l_particle=[r_kaon1.Pt(), r_kaon1.Eta(), r_kaon1.Phi(), d_kaon1, 32]

    if not geo_match_kaon2 or not pt_match_kaon2:
        r_kaon2 = kaon2[5] 
        l_particle=[r_kaon2.Pt(), r_kaon2.Eta(), r_kaon2.Phi(), d_kaon2, 32]

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

json_args =utils.json_to_dict("json_args/arguments_%s.json" % JOBNAME)
json_lfile=utils.json_to_dict("json_args/jobs_%s.json" % JOBNAME)

FIRST_KAON = json_args["TYPE"] == "bplus"
BOTH_KAONS = json_args["TYPE"] == "bsjpsiphi"

settings.FIRST_KAON = json_args["TYPE"] == "bplus"
settings.BOTH_KAONS = json_args["TYPE"] == "bsjpsiphi"
#******************************************
#Initialize variables, etc
#******************************************
print("Initializing remaining variables")

ROOT.gROOT.SetBatch()
MATCH_RADIUS=0.05
PT_TOL=0.15
JSON_DIR="Json"
#******************************************
#Open file and get trees
#******************************************
print("Opening files.")

cand_chain = ROOT.TChain(json_args["CAND_TREE"])
truth_chain= ROOT.TChain(json_args["DECAY_TREE"])

l_FILES=json_lfile[IJOB]
for FILE in l_FILES:
    cand_chain.Add(FILE)
    truth_chain.Add(FILE)
#******************************************
#Set range of entries
#******************************************
HIGH_ENTRY=0
if json_args["TEST"] == "0":
    HIGH_ENTRY=cand_chain.GetEntries()
else:
    HIGH_ENTRY= int( json_args["NEVENTS"] )
#******************************************
#Create objects/variables
#******************************************
print("Creating structures/containers.")

matched_cand  =0
unmatched_cand=0

s_events_nocuts =set()
s_events_cuts   =set()
s_unmatch_events=set()

d_decay_freq    =dict()
#******************************************
#Make output tree
#******************************************
decay=ROOT.std.string()
a_Bmass=array.array('f', [0.])
a_event_number=array.array('i', [0])

ofile=ROOT.TFile(OUTPUT, "recreate")
decays=ROOT.TTree("decays", "")
decays.Branch("decay", decay)
decays.Branch("Bmass", a_Bmass, "Bmass/F")
decays.Branch("event_number", a_event_number, "event_number/I")

#Get dictionary between event number and
#entry index for decays tree.
d_event_number_index=utils.GetIndexes(truth_chain, branch_name="event_number")
#******************************************
#Fill structures
#******************************************
print("Looping over trees")

for i_entry in range(0, HIGH_ENTRY + 1):
    cand_chain.GetEntry(i_entry)
    reco_entry = cand_chain

    if i_entry % 10000 == 0:
        print("Processing entry %d" % i_entry)

    r_event_number=reco_entry.event_number
    #*************************************
    #Apply cuts
    #*************************************
    s_events_nocuts.add(r_event_number)

    if not settings.pass_cut(reco_entry):
        continue

    s_events_cuts.add(r_event_number)
    
    a_event_number[0]=reco_entry.event_number 
    #*************************************
    #Test index consistency
    #*************************************
    if r_event_number not in d_event_number_index:
        print("Truth event not found")
        continue

    index=d_event_number_index[r_event_number]
    truth_chain.GetEntry(index)
    t_event_number=truth_chain.event_number

    if r_event_number != t_event_number:
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
        match=Check_Matching(l_matched_particle[0], l_matched_particle[1], l_matched_particle[2], l_matched_particle[3], r_event_number)
    #*************************************
    #Assign values to entry and fill
    #*************************************
    if match:
        matched_cand+=1
        l_decays=GetDecays(l_matched_particle)

        ndecays=len(l_decays)
        if ndecays == 2:
            decay.erase()
            decay.append("comb")
        elif ndecays == 1:
            idecay=l_decays[0]
            decay.erase()
            decay.append(truth_entry.decay[idecay])
        else:
            print("Found %d decays at event %d" % (ndecays, r_event_number) )
            decay.erase()
            decay.append("none")

        pystr_decay=decay.c_str()
        if pystr_decay not in d_decay_freq:
            d_decay_freq[pystr_decay] = 1
        else:
            d_decay_freq[pystr_decay]+= 1
            
        a_Bmass[0]=reco_entry.B_VTX_mass
        decays.Fill()
    else:
        a_Bmass[0]=reco_entry.B_VTX_mass
        decay.erase()
        decay.append("unmatched")
        decays.Fill()

        s_unmatch_events.add(r_event_number)
        unmatched_cand+=1
#******************************************
#Save everything 
#******************************************
print("Saving tree.")
decays.Write()
ofile.Close()
#******************************************
#******************************************

