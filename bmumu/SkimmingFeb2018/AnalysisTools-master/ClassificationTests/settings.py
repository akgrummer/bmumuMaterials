import ROOT

#------------------------------------------
#Does this entry pass the cuts?
#------------------------------------------
def pass_cut(entry):
    trigger                = entry.HLT_trigger
    chi2                   = entry.B_fitChi2NDF

    R_mu_minus_eta         = entry.Muon1_eta
    R_mu_plus_eta          = entry.Muon2_eta
    R_mu_minus_pT          = entry.Muon1_pT
    R_mu_plus_pT           = entry.Muon2_pT

    R_kaon1_pT             = 0 
    R_kaon2_pT             = 0 

    R_kaon1_eta            = 0 
    R_kaon2_eta            = 0 

    R_kaon1_pass           = 0 
    R_kaon2_pass           = 0 

    if FIRST_KAON:
        R_kaon1_pT              = entry.K_pT
        R_kaon1_pass            = entry.K_pass
    elif BOTH_KAONS:
        R_kaon1_pT              = entry.KPlus_pT
        R_kaon1_pass            = entry.KPlus_pass

        R_kaon2_pT              = entry.KMinus_pT
        R_kaon2_pass            = entry.KMinus_pass

    R_mu_minus_isCombined  = entry.Muon1_isCombinedMuon
    R_mu_plus_isCombined   = entry.Muon2_isCombinedMuon
    R_mu_plus_accept       = entry.Muon1_accept
    R_mu_minus_accept      = entry.Muon2_accept

    B_pT                   = entry.B_pT
    B_eta                  = entry.B_eta

    pass_reco_eta          = abs( R_mu_minus_eta ) < 2.5 and abs( R_mu_plus_eta ) < 2.5 
    pass_reco_pT           = R_mu_plus_pT > 4000 and R_mu_minus_pT > 4000 
    pass_reco_qty          = R_mu_minus_isCombined and R_mu_plus_isCombined and R_mu_plus_accept and R_mu_minus_accept
    pass_reco_muon         = pass_reco_eta and pass_reco_pT and pass_reco_qty

    pass_reco_kaon=True
    if FIRST_KAON:
        pass_reco_kaon     = R_kaon1_pT > 1000 and R_kaon1_pass and abs(R_kaon1_eta) < 2.5
    elif BOTH_KAONS:
        pass_reco_kaon_1   = R_kaon1_pT > 1000 and abs(R_kaon1_eta) < 2.5 and R_kaon2_pass
        pass_reco_kaon_2   = R_kaon2_pT > 1000 and abs(R_kaon2_eta) < 2.5 and R_kaon2_pass
        pass_reco_kaon     = pass_reco_kaon_1 and pass_reco_kaon_2

    pass_B=(B_pT > 8000) and (B_eta < 2.5) and (chi2 < 6)

    return pass_reco_muon and pass_reco_kaon and pass_B 
#------------------------------------------
#------------------------------------------
FIRST_KAON=False
BOTH_KAONS=False
