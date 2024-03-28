#!/bin/bash

#**********************************************
#Exit if dataset does not exist
#**********************************************
check_dataset()
{
    DATASET=$1
    
    rucio list-dids $DATASET | grep $DATASET &>/dev/null
    if [[ $? -ne 0 ]];then
	echo "ERROR::No $DATASET"
	kill -INT $$
    fi

    echo "OK $DATASET"
}
#**********************************************
#Setup tool if not setup
#**********************************************
setup_tool()
{
    TOOL=$1
    NAME=$2
    hash $TOOL &>/dev/null
    STATUS=$?
    if [[ $STATUS -ne 0 ]];then
	lsetup $NAME
    fi
}
#**********************************************
#Place here xAODs (NOT DxAODs).
#**********************************************
BSMUMU="mc15_13TeV.300426.Pythia8BEvtGen_A14_CTEQ6L1_Bs_mu3p5mu3p5.merge.AOD.e4889_a766_a867_r8423"
BPLUSKP="mc15_13TeV.300404.Pythia8BEvtGen_A14_CTEQ6L1_Bp_Jpsi_mu3p5mu3p5_Kp_BMassFix.merge.AOD.e4862_a766_a845_r8423"
BPLUSPI="mc15_13TeV.300406.Pythia8BEvtGen_A14_CTEQ6L1_Bp_Jpsi_mu3p5mu3p5_Pip_BMassFix.merge.AOD.e4862_a766_a845_r8423"
BDPIMUNU="mc15_13TeV.300433.Pythia8BEvtGen_A14_CTEQ6L1_Bd_pi3p5mu3p5nu.merge.AOD.e4720_a766_a845_r8423"
BSJPSIPHI="mc15_13TeV.300438.Pythia8BPhotospp_A14_CTEQ6L1_Bs_Jpsimu3p5mu3p5_phi.merge.AOD.e4922_a766_a845_r8423"
BBJPSI="mc15_13TeV.300203.Pythia8BPhotospp_A14_CTEQ6L1_bb_Jpsimu3p5mu3p5.merge.AOD.e4889_a766_a845_r8423"
LAMBDAMUNU="mc15_13TeV.300434.Pythia8BEvtGen_A14_CTEQ6L1_Lambda0b_p3p5mu3p5nu.merge.AOD.e4720_a766_a845_r8423"
BHH="mc15_13TeV.300431.Pythia8B_A14_CTEQ6L1_B_hh.merge.AOD.e4889_s2726_r8725_r8423"
BSKPMUNU="mc15_13TeV.300432.Pythia8BEvtGen_A14_CTEQ6L1_Bs_K3p5mu3p5nu.merge.AOD.e4720_a766_a845_r8423"
BPLUS_ART="mc16_13TeV.300999.Pythia8BEvtGen_A14_CTEQ6L1_Bplus_Jpsi_mu3p5mu3p5_Kplus.recon.AOD.e4397_s3126_r9703"
#**********************************************
#Setup if needed
#**********************************************
type lsetup &>/dev/null
if [[ $? -ne 0 ]];then
    setupATLASSi || setupATLAS &>/dev/null
fi

if [[ -f .asetup.save ]];then
    asetup --restore
else
    asetup AthAnalysis,21.2.34,here
fi

setup_tool pathena panda
setup_tool rucio   rucio 
#**********************************************
#Check that all datasets exist
#**********************************************
echo "Checking if datasets exist."

#check_dataset $BSMUMU
#check_dataset $BPLUSKP
#check_dataset $BPLUSPI
#check_dataset $BDPIMUNU
#check_dataset $BSJPSIPHI
#check_dataset $BBJPSI
#check_dataset $LAMBDAMUNU
#check_dataset $BHH
#check_dataset $BSKPMUNU
check_dataset $BPLUS_ART
#**********************************************
#WARNING: Replace user.acampove.* by user.YOUR_USER_NAME.*
#**********************************************
PREFIX="user.acampove."

#pathena PileupReweighting/generatePRW_jobOptions.py --forceStaged --inDS="$BSMUMU"     --outDS="$PREFIX""$BSMUMU"".prw" 
#pathena PileupReweighting/generatePRW_jobOptions.py --forceStaged --inDS="$BDPIMUNU"   --outDS="$PREFIX""$BDPIMUNU"".prw"
#pathena PileupReweighting/generatePRW_jobOptions.py --forceStaged --inDS="$BSJPSIPHI"  --outDS="$PREFIX""$BSJPSIPHI"".prw"
#pathena PileupReweighting/generatePRW_jobOptions.py --forceStaged --inDS="$BBJPSI"     --outDS="$PREFIX""$BBJPSI"".prw"
#pathena PileupReweighting/generatePRW_jobOptions.py --forceStaged --inDS="$LAMBDAMUNU" --outDS="$PREFIX""$LAMBDAMUNU"".prw"
#pathena PileupReweighting/generatePRW_jobOptions.py --forceStaged --inDS="$BHH"        --outDS="$PREFIX""$BHH"".prw"
#pathena PileupReweighting/generatePRW_jobOptions.py --forceStaged --inDS="$BSKPMUNU"   --outDS="$PREFIX""$BSKPMUNU"".prw"

#Remove mc15_13TeV from front of DS name. Otherwise cannot send job, grid does not accept output DS names with more than
#132 characters

#pathena PileupReweighting/generatePRW_jobOptions.py --forceStaged --inDS="$BPLUSKP"    --outDS="$PREFIX""${BPLUSKP#.mc15_13TeV}"".prw"
#pathena PileupReweighting/generatePRW_jobOptions.py --forceStaged --inDS="$BPLUSPI"    --outDS="$PREFIX""${BPLUSPI#.mc15_13TeV}"".prw"

pathena PileupReweighting/generatePRW_jobOptions.py --forceStaged --inDS="$BPLUS_ART"    --outDS="$PREFIX""${BPLUS_ART#mc16_13TeV.}"
#**********************************************
#**********************************************

