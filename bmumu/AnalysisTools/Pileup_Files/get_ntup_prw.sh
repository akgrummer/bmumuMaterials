#!/bin/bash

#-------------------------------------------------
#Copy renamed files
#-------------------------------------------------
doRename()
{
    DIRNAME=$1
    TARGET=$2

    if [[ ! -d $DIRNAME ]];then
        echo "Directory $DIRNAME not found"
        kill -INT $$
    fi

    if [[ ! -f $DIRNAME/"Merged_1.root" ]];then
        echo "File $DIRNAME/Merged_1.root does not exist."
        kill -INT $$
    fi

    mkdir -p $TARGET
    if [[ ! -d $TARGET ]];then
        echo "Directory $TARGET not found"
        kill -INT $$
    fi

    if [[ $DIRNAME == *300203* ]];then
        FILENAME="bbjpsix_prw.root"
    elif [[ $DIRNAME == *300306* ]];then
        FILENAME="bmumux_prw.root"
    elif [[ $DIRNAME == *300307* ]];then
        FILENAME="bbmumux_prw.root"
    elif [[ $DIRNAME == *300404* ]];then
        FILENAME="bpjpsikp_prw.root"
    elif [[ $DIRNAME == *300405* ]];then
        FILENAME="bmjpsikm_prw.root"
    elif [[ $DIRNAME == *300406* ]];then
        FILENAME="bpjpsipip_prw.root"
    elif [[ $DIRNAME == *300426* ]];then
        FILENAME="bsmumu_prw.root"
    elif [[ $DIRNAME == *300430* ]];then
        FILENAME="bdmumu_prw.root"
    elif [[ $DIRNAME == *300431* ]];then
        FILENAME="bhh_prw.root"
    elif [[ $DIRNAME == *300432* ]];then
        FILENAME="bskpmunu_prw.root"
    elif [[ $DIRNAME == *300433* ]];then
        FILENAME="bdpimunu_prw.root"
    elif [[ $DIRNAME == *300434* ]];then
        FILENAME="lambmunu_prw.root"
    elif [[ $DIRNAME == *300437* ]];then
        FILENAME="bmjpsipim_prw.root"
    elif [[ $DIRNAME == *300438* ]];then
        FILENAME="bsjpsiphi_prw.root"
    fi

    echo "Copying in $DIRNAME"
    echo "Merged_1.root ----> $FILENAME"
    echo ""

    cp $DIRNAME/"Merged_1.root" $TARGET/$FILENAME
}
#-------------------------------------------------
#Removes what is already there
#-------------------------------------------------
doRemove()
{
    echo "Removing everything in $PRW_DIR"
    rm -rf $PRW_DIR
}
#-------------------------------------------------
#Make output directory and put NTUP datasets there
#-------------------------------------------------
doDownload()
{
    mkdir -p $PRW_DIR
    cd $PRW_DIR

    rucio download mc16_13TeV.300*.Pythia8B*_CTEQ6L1_*.deriv.NTUP_PILEUP.*_r9364_r9315_p3384
    rucio download mc16_13TeV.300*.Pythia8B*_CTEQ6L1_*.deriv.NTUP_PILEUP.*_r9364_r9315_p3288

    cd $CURRENT
}
#-------------------------------------------------
#Merge files in given directory
#-------------------------------------------------
doMerge()
{
    DIR=$1
    MERGED="Merged_1.root"

    echo "Merging files in $DIR"

    if [[ ! -d $DIR ]];then
        echo "$DIR directory does not exist."
        kill -INT $$
    fi
    cd $DIR

    group_files 1000
    merge_files

    if [[ ! -f $MERGED ]];then
        echo "$MERGED file does not exist."
        cd $CURRENT

        kill $INT $$
    fi

    cd $CURRENT
}
#-------------------------------------------------
#Load, setup everything
#-------------------------------------------------
CURRENT=$(pwd)
SETUP_ATLAS=$CURRENT/../Utils/setup_atlas.sh

if [[ ! -f $SETUP_ATLAS ]];then
    echo "Cannot find file $SETUP_ATLAS"
    kill -INT $$
fi

source $SETUP_ATLAS 

PRW_DIR=/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/PRW/v_03
TARGET=$PRW_DIR/PRW_FILES
#-------------------------------------------------
#Setup everything
#-------------------------------------------------
setup_tool root  root
setup_tool rucio rucio
#-------------------------------------------------
#Loop over all the directories
#-------------------------------------------------
#doRemove
#doDownload
#
#for TARGET in `find $PRW_DIR -type d -name mc*`;do
#    doMerge $TARGET 
#done
#
for SOURCE in `find $PRW_DIR -type d -name mc*`;do
    doRename $SOURCE $TARGET 
done
#-------------------------------------------------
#-------------------------------------------------

