#!/bin/bash

#-----------------------
#Used to rename produced lumifiles
#-----------------------
rename_move()
{
    for FILE in `ls *.root`;do
	mv $FILE ./Lumifiles/"Lumifile_"$1_$2".root"
	mv *.xml ./Lumifiles/
	mv *.tmp ./Lumifiles/
    done
}
#-----------------------
#Set trigger names
#-----------------------
TRIGGER_2015_MUMU=HLT_mu6_mu4_bBmumu    #Lxy0 not available
TRIGGER_2015_JPSI=HLT_mu6_mu4_bJpsimumu #Lxy0 not available

TRIGGER_2016_MUMU=HLT_mu6_mu4_bBmumu_Lxy0
TRIGGER_2016_JPSI_MAIN=HLT_mu6_mu4_bJpsimumu_Lxy0 #for 2016, all runs
TRIGGER_2016_JPSI_DELY=HLT_mu6_mu4_bJpsimumu_Lxy0_delayed #for 302956 and after

#Others have 2-9 GeV window and get prescaled more often.
TRIGGER_2017_MUMU=HLT_mu6_mu4_bBmumu_Lxy0_L1BPH-2M9-MU6MU4_BPH-0DR15-MU6MU4
TRIGGER_2017_JPSI=HLT_mu6_mu4_bJpsimumu_Lxy0_L1BPH-2M9-MU6MU4_BPH-0DR15-MU6MU4 

LUMITAG_2015=OflLumi-13TeV-008
LUMITAG_2016=OflLumi-13TeV-009
LUMITAG_2017=OflLumi-13TeV-010
#-----------------------
#Setup ATHENA release
#-----------------------
hash lsetup &>/dev/null
if [[ $? != 0 ]]; then
    setupATLASSi || setupATLAS
    lsetup 'asetup AtlasProduction,20.7.9.9,here'
fi
#-----------------------
#Checkout and build LumiCalc
#-----------------------
if [[ ! -d LumiBlock ]]; then
    cmt co -r LumiCalc-00-04-30 LumiBlock/LumiCalc #adjust version to latest at the bottom of https://atlas-lumicalc.cern.ch/
    cd LumiBlock/LumiCalc/cmt/
    gmake
    cd -
fi
#-----------------------
#Make output directory
#-----------------------
mkdir -p Lumifiles
#-----------------------
#Check if LumiCalc is available
#-----------------------
hash iLumiCalc.exe
if [[ $? != 0 ]]; then
    echo "make_lumi_files.sh::LumiCalc is not available, package was not build successfully?"
    kill -INT $$
fi
#-----------------------
#Produce Lumi files.
#WARNING:Make sure you are using the LATEST GRLs.
#-----------------------
DATA_PATH="/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/GoodRunsLists/"
GRL_2015=$DATA_PATH"/data15_13TeV/20170619/data15_13TeV.periodAllYear_DetStatus-v89-pro21-02_Unknown_PHYS_StandardGRL_All_Good_25ns.xml"
GRL_2016=$DATA_PATH"/data16_13TeV/20180129/data16_13TeV.periodAllYear_DetStatus-v89-pro21-01_DQDefects-00-02-04_PHYS_StandardGRL_All_Good_25ns.xml"
GRL_2017=$DATA_PATH"/data17_13TeV/20180309/data17_13TeV.periodAllYear_DetStatus-v97-pro21-13_Unknown_PHYS_StandardGRL_All_Good_25ns_Triggerno17e33prim.xml"
#----------
#2015
#----------
iLumiCalc.exe --lumitag=$LUMITAG_2015 --livetrigger=L1_EM12 --trigger=$TRIGGER_2015_MUMU --xml=$GRL_2015 --lar --lartag=LARBadChannelsOflEventVeto-RUN2-UPD4-04 --plots
rename_move 2015 $TRIGGER_2015_MUMU

iLumiCalc.exe --lumitag=$LUMITAG_2015 --livetrigger=L1_EM12 --trigger=$TRIGGER_2015_JPSI --xml=$GRL_2015 --lar --lartag=LARBadChannelsOflEventVeto-RUN2-UPD4-04 --plots
rename_move 2015 $TRIGGER_2015_JPSI
#----------
#2016
#----------
iLumiCalc.exe --lumitag=$LUMITAG_2016 --livetrigger=L1_EM12 --trigger=$TRIGGER_2016_MUMU --xml=$GRL_2016 --lar --lartag=LARBadChannelsOflEventVeto-RUN2-UPD4-04 --plots
rename_move 2016 $TRIGGER_2016_MUMU

iLumiCalc.exe --lumitag=$LUMITAG_2016 --livetrigger=L1_EM12 --trigger=$TRIGGER_2016_JPSI_MAIN --xml=$GRL_2016 --lar --lartag=LARBadChannelsOflEventVeto-RUN2-UPD4-04 --plots --run=-302925
rename_move 2016 $TRIGGER_2016_JPSI_MAIN

iLumiCalc.exe --lumitag=$LUMITAG_2016 --livetrigger=L1_EM12 --trigger=$TRIGGER_2016_JPSI_DELY --xml=$GRL_2016 --lar --lartag=LARBadChannelsOflEventVeto-RUN2-UPD4-04 --plots --run=302956-
rename_move 2016 $TRIGGER_2016_JPSI_DELY
#----------
#2017
#----------
iLumiCalc.exe --lumitag=$LUMITAG_2017 --livetrigger=L1_EM12 --trigger=$TRIGGER_2017_JPSI --xml=$GRL_2017 --lar --lartag=LARBadChannelsOflEventVeto-RUN2-UPD4-04 --plots 
rename_move 2017 $TRIGGER_2017_JPSI

