import ROOT

import collections
import re

import validation
#---------------------------------
#This function will transform:
#B*->gamma + B(->X)
#into:
#B->X
#---------------------------------
def ReformatDecayString(decay):
    regex="^B.+\[gamma:(B.+\[.+\])\]$"
    obj=re.match(regex, decay)

    if obj:
        decay=obj.group(1)

    return decay
#-------------------------------------------
#Returns list of decays corresponding to
#decay matched decay products.
#-------------------------------------------
def GetDecays(l_particles):
    s_idecay=set()

    for particle in l_particles:
        if particle != ():
            s_idecay.add(particle[1])

    return list(s_idecay)
#-------------------------------------------
#Do reco particles match a suitable particle
#at truth level?
#-------------------------------------------
def Check_Matching(muon1, muon2, kaon1, kaon2):
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

    return match
#-------------------------------------------
#Returns matching truth particles as the
#tuples introduced, plus one extra entry
#for the distance to the reco particle and
#the reco particle as:
# (Truth, Decay, PDGID, status, distance, Reco)
#-------------------------------------------
def TruthMatch(l_truth_particles, reco_muon1, reco_muon2, reco_kaon1=ROOT.TVector3(), reco_kaon2=ROOT.TVector3() ):
    d_muon1_particles=dict()
    d_muon2_particles=dict()
    d_kaon1_particles=dict()
    d_kaon2_particles=dict()

    for truth_particle in l_truth_particles:
        PDGID=truth_particle[2]
        
        obj=ROOT.HepPDT.ParticleID(PDGID)

        if abs(PDGID) == 13:
            DR_mu1 = reco_muon1.DeltaR(truth_particle[0])
            d_muon1_particles[DR_mu1] = truth_particle

        if abs(PDGID) == 13:
            DR_mu2 = reco_muon2.DeltaR(truth_particle[0])
            d_muon2_particles[DR_mu2] = truth_particle
            
        if FIRST_KAON and obj.isHadron() and not obj.hasCharm() and not obj.hasBottom() and obj.threeCharge() != 0:
            DR_kaon = reco_kaon1.DeltaR(truth_particle[0])
            d_kaon1_particles[DR_kaon] = truth_particle

        if BOTH_KAONS and obj.isHadron() and not obj.hasCharm() and not obj.hasBottom() and obj.threeCharge() != 0:
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
        t_kaon1_d = od_kaon1_particles.items()[0][0]
        t_kaon1_p = od_kaon1_particles.items()[0][1]
        t_kaon1_p = t_kaon1_p + (t_kaon1_d, reco_kaon1)

        t_kaon2_d = od_kaon2_particles.items()[0][0]
        t_kaon2_p = od_kaon2_particles.items()[0][1]
        t_kaon2_p = t_kaon2_p + (t_kaon2_d, reco_kaon2)

    return [t_muon1_p, t_muon2_p, t_kaon1_p, t_kaon2_p]
#-------------------------------------------
#Return list of tuples with (particle, decay, PDGID)
#where decay is either 0 or 1
#-------------------------------------------
def GetTruthParticles():
    ndecays = chain_decay.px.size()
    l_particles = list()
    for i_decay in range(0, ndecays):
        v_pT    = chain_decay.pt[i_decay]
        v_Theta = chain_decay.theta[i_decay]
        v_Phi   = chain_decay.phi[i_decay]
        v_PDGID = chain_decay.PDGid[i_decay]
        v_status= chain_decay.status[i_decay]

        for pT, Theta, Phi, PDGID, status in zip(v_pT, v_Theta, v_Phi, v_PDGID, v_status):
            if status != 1:
                continue

            particle = ROOT.TVector3()
            particle.SetPtThetaPhi(pT, Theta, Phi)

            tuple_particle = ( particle, i_decay, PDGID, status )
            l_particles.append(tuple_particle)

    return l_particles
#-------------------------------------------
#Return a list of matching particles each
#element is a tuple:
#(Truth, Decay, PDGID, status, distance, Reco)
#-------------------------------------------
def Match(reco_entry):
    reco_kaon1 = ROOT.TVector3()
    reco_kaon2 = ROOT.TVector3()
    reco_muon1 = ROOT.TVector3()
    reco_muon2 = ROOT.TVector3()
    
    reco_muon1.SetPtEtaPhi( reco_entry.Muon1_pT_orig, reco_entry.Muon1_eta_orig, reco_entry.Muon1_phi_orig)
    reco_muon2.SetPtEtaPhi( reco_entry.Muon2_pT_orig, reco_entry.Muon2_eta_orig, reco_entry.Muon2_phi_orig)
    
    l_truth_particles  = GetTruthParticles()
    if PROCESS == "Bmumu":
        l_matched_particle = TruthMatch(l_truth_particles, reco_muon1, reco_muon2) 
    elif PROCESS == "BpJpsiKp" or PROCESS == "BJpsiK":    
        reco_kaon1.SetPtEtaPhi( reco_entry.K_pT, reco_entry.K_eta, reco_entry.K_phi )
        l_matched_particle = TruthMatch(l_truth_particles, reco_muon1, reco_muon2, reco_kaon1) 
    elif PROCESS == "BsJpsiPhi":
        reco_kaon1.SetPtEtaPhi( reco_entry.KPlus_pT , reco_entry.KPlus_eta , reco_entry.KPlus_phi )
        reco_kaon2.SetPtEtaPhi( reco_entry.KMinus_pT, reco_entry.KMinus_eta, reco_entry.KMinus_phi)
        l_matched_particle = TruthMatch(l_truth_particles, reco_muon1, reco_muon2, reco_kaon1, reco_kaon2) 
    else:
        print("Unrecognized process: %s" % PROCESS)
        exit(1)

    return l_matched_particle
#-------------------------------------------
#Set truth_entry to event corresponding to
#reco_entry
#-------------------------------------------
def SetTruthEntry(reco_entry):
    event_number=reco_entry.event_number

    if event_number in d_event_number_index:
        truth_index=d_event_number_index[event_number]
    else:
        print("Match::Event number %d not found in TRUTHDECAY tree." % event_number)
        return False 

    chain_decay.GetEntry(truth_index)

    if chain_decay.event_number != reco_entry.event_number:
        print("Candidate and Decay trees are not sycronized.")
        return False
    
    return True 
#-------------------------------------------
#Returns decay string
#-------------------------------------------
def GetDecayString(reco_entry):
    global FIRST_KAON
    global BOTH_KAONS 

    if not SetTruthEntry(reco_entry):
        return "Missing event %d in TRUTHDECAYS" % reco_entry.event_number

    FIRST_KAON = PROCESS == "BpJpsiKp" or PROCESS == "BJpsiK"
    BOTH_KAONS = PROCESS == "BsJpsiPhi"
    validation.FIRST_KAON=FIRST_KAON
    validation.BOTH_KAONS=BOTH_KAONS

    match=False
    l_matched_particle=Match(reco_entry)
    if len(l_matched_particle) == 0:
        return "missing particles"
    else:
        muon1=l_matched_particle[0]
        muon2=l_matched_particle[1]
        kaon1=l_matched_particle[2]
        kaon2=l_matched_particle[3]
        match=Check_Matching(muon1, muon2, kaon1, kaon2)

    if match:
        l_decays=GetDecays(l_matched_particle)

        ndecays=len(l_decays)
        if ndecays == 2:
            decay="combinatorial"
        elif ndecays == 1:
            i_decay=l_decays[0]
            decay = chain_decay.decay[i_decay]
            decay = ReformatDecayString(decay)
        else:
            decay = "Found %d decays at event %d" % (ndecays, reco_entry.event_number)
    else:
        decay="unmatched"
    #--------------------------------
    #Save validation information
    #--------------------------------
    l_distance=list()
    for particle in l_matched_particle:
        if particle == ():
            continue

        distance=particle[4]
        l_distance.append(distance)

    validation.Initialize()
    validation.Execute(l_distance, match)
    #--------------------------------
    #--------------------------------
    return decay
#-------------------------------------------
#Fill dictionary
#-------------------------------------------
def FillEntryDictionary():
    nentries=chain_decay.GetEntries()
    print("Making dictionary for %d entries." % nentries )
    for i_entry in range(0, nentries):
        chain_decay.GetEntry(i_entry)
        d_event_number_index[chain_decay.event_number] = i_entry
#-------------------------------------------
#Finalize all
#-------------------------------------------
def Finalize():
    validation.Finalize()
#-------------------------------------------
#Initialize everything
#-------------------------------------------
ROOT.gROOT.SetBatch()

chain_decay=ROOT.TChain()
d_event_number_index=dict()
PROCESS=""
FIRST_KAON=False
BOTH_KAONS=False
MATCH_RADIUS=0.05
PT_TOL=0.15
#-------------------------------------------
#Load HepPDT libraries, etc.
#-------------------------------------------
print("Loading HepPDT libraries")

ROOT.gSystem.Load("libHepPID.so")
ROOT.gSystem.Load("libHepPDT.so")
ROOT.gROOT.ProcessLine('#include "HepPDT/ParticleID.hh"')
#-------------------------------------------
#-------------------------------------------

