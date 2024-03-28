#!/bin/bash

#**************************************
#Check if histograms are there, etc.
#**************************************
check()
{
    HIST_DIR="hist"
    if [[ ! -d $HIST_DIR ]];then
	echo "Cannot find $HIST_DIR directory"
	kill -INT $$
    fi

    HIST_FILE=hist/output_$PROCESS".root"
    
    STATUS=0
    if [[ ! -f $HIST_FILE ]];then
	echo "Cannot find $HIST_FILE"
	STATUS=1
    fi
}
#**************************************
#**************************************
#PROCESSES=(bpluskp_BpJpsiKp bsmumu_Bmumu bskmunu_Bhmunu bpluspi_BpJpsiPi bpluspi_BpJpsiKp lambmunu_Bhmunu bdpimunu_Bhmunu)
#PROCESSES=(bsmumu_Bmumu bsmumu_BpJpsiK bsmumu_BsJpsiPhi)
PROCESSES=(bsmumu_Bmumu bpluskp_BpJpsiK bsjpsiphi_BsJpsiPhi)

MERGED_PLOTS_DIR=$(pwd)"/plots_merged/"
mkdir -p $MERGED_PLOTS_DIR
rm -f $MERGED_PLOTS_DIR/*

for PROCESS in ${PROCESSES[@]};do
    check
    if [[ $STATUS -ne 0 ]];then
	continue
    fi

    PLOTS_DIR=$(pwd)"/plots_"$PROCESS
    MERGED_FILE=$PROCESS".pdf" 
    INPUT_HIST="$(pwd)/hist/output_"$PROCESS".root"

    echo "Making plots from $INPUT_HIST"

    rm -f $PLOTS_DIR/*

    python plotter.py $INPUT_HIST $PROCESS

    echo "Merging for process $PROCESS"

    cd $PLOTS_DIR
    rm -f $MERGED_FILE
    echo "Merging in $(pwd)"
    pdfunite *.pdf $MERGED_FILE 
    mv $MERGED_FILE $MERGED_PLOTS_DIR
    cd -
done
#**************************************
#**************************************

