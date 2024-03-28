#!/bin/bash

#***************************************************
#Setup everything
#***************************************************
source ../Utils/setup_atlas.sh

setup_tool rucio rucio
#***************************************************
#Set name of merged PRW file
#***************************************************
set_filename()
{
    DSNAME=$1
    REGEX_DSID=".*\.([0-9]{6})\..*"

    if [[ $DSNAME =~ $REGEX_DSID ]];then
	DSID=${BASH_REMATCH[1]}
	echo "Found DSID $DSID in $DSNAME"
    fi

    if [[ $DSID -eq 300203 ]];then
	FILENAME="bbjpsix_prw.root"
    elif [[ $DSID -eq 300306 ]];then
	FILENAME="bbmumux_prw.root"
    elif [[ $DSID -eq 300404 ]];then
	FILENAME="bpjpsikp_prw.root"
    elif [[ $DSID -eq 300406 ]];then
	FILENAME="bpjpsipi_prw.root"
    elif [[ $DSID -eq 300426 ]];then
	FILENAME="bsmumu_prw.root"
    elif [[ $DSID -eq 300431 ]];then
	FILENAME="bhh_prw.root"
    elif [[ $DSID -eq 300432 ]];then
	FILENAME="bskpmunu_prw.root"
    elif [[ $DSID -eq 300433 ]];then
	FILENAME="bdpimunu_prw.root"
    elif [[ $DSID -eq 300434 ]];then
	FILENAME="lambmunu_prw.root"
    elif [[ $DSID -eq 300438 ]];then
	FILENAME="bsjpsiphi_prw.root"
    else
	echo "Unrecognized DSID=$DSID"
    fi
}
#***************************************************
#Download and merge PRW files
#***************************************************
get_files()
{
    DSNAME=$1
    rucio download $DSNAME

    set_filename $DSNAME

    mkdir -p PRW

    cd $DSNAME
    group_files 100000
    merge_files
    cd -

    mv $DSNAME/Merged_1.root PRW/$FILENAME
    rm -rf $DSNAME 
}
#***************************************************
#Loop over files
#***************************************************
while read DATASET;do
    echo "Downloading $DATASET"
    get_files $DATASET 
done < prw_datasets.txt
#***************************************************
#***************************************************
