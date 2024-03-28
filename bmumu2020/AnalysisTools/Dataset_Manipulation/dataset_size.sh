#!/bin/bash

#***********************************
#Do checks
#***********************************
check()
{
    if [[ -z $DATASETS ]];then
	echo "Datasets not specified"
	kill -INT $$
    fi

    if [[ ! -f $SAMPLES ]];then
	echo "Cannot find $SAMPLES"
	kill -INT $$
    fi
}
#***********************************
#Setup everything
#***********************************
source ../Utils/setup_atlas.sh

setup_tool rucio rucio
setup_tool ami   pyami 
#***********************************
#Get samples information
#***********************************
DATASETS=$1
L_NAME="logicalDatasetName"
L_EVTS="totalEvents"
SAMPLES="$(pwd)/text/$DATASETS"

check

while read DATASET;do
    echo "#######################"
    echo "Sample $DATASET"
    echo "#######################"
    ami show dataset info $DATASET | grep "$L_NAME""\|""$L_EVTS"
    rucio list-files $DATASET | grep "Total size"
done < $SAMPLES 
#***********************************
#***********************************
