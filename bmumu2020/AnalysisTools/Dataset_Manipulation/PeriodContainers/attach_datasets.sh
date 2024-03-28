#!/bin/bash

#----------------------------------------
#Attach datasets to containers
#----------------------------------------
#PATTERN="data15_13TeV.%.physics_Main.deriv.DAOD_BPHY8.%p3583"
PATTERN="data16_13TeV.%.physics_Main.deriv.DAOD_BPHY8.%p3583"
DATASETS=$(ami list datasets $PATTERN)

REGEX="^data([0-9]+)_.*"
if [[ $PATTERN =~ $REGEX ]];then
    YEAR=${BASH_REMATCH[1]}
else
    echo "Year not found in $PATTERN"
    kill -INT $$
fi

SKIP_FILE="Skipped_"$YEAR".txt"
ATCH_FILE="Attached_"$YEAR".txt"
SUCC_FILE="Success_"$YEAR".txt"

rm -f $SKIP_FILE
rm -f $ATCH_FILE 
for DATASET in ${DATASETS[@]};do
    LINE=$(ami show dataset info $DATASET | grep period)
    STATUS=$(ami show dataset info $DATASET | grep prodsysStatus)
    #----------------------------
    #Checking for DS status
    #----------------------------
    REGEX="^prodsysStatus\s+:\s+([A-Z].*[A-Z])$"
    if [[ $STATUS =~ $REGEX ]];then
	STAT=${BASH_REMATCH[1]}
    else
	echo "Cannot get events status for $DATASET with line $STATUS"
	kill -INT $$
    fi

    if [[ $STAT != "ALL EVENTS AVAILABLE" ]];then
	echo "Skipping DS $DATASET, has:" 
	echo "   Event status: $STAT"
	echo ""

	echo "Skipping DS $DATASET, has:" >> $SKIP_FILE  
	echo "   Event status: $STAT"     >> $SKIP_FILE 
	echo ""                           >> $SKIP_FILE 

	continue
    fi
    #----------------------------
    #Attaching good DS
    #----------------------------
    REGEX="^period\s+:\s+([A-Z])[0-9]+$"
    if [[ $LINE =~ $REGEX ]];then
	PERIOD=${BASH_REMATCH[1]}
	CONTAINER="user.acampove.data"$YEAR"_13TeV.period"$PERIOD".physics_Main.PhysCont.DAOD_BPHY8.grp16_v01_p3583"
	echo "Attaching"
	echo "$DATASET ----> $CONTAINER"
	echo ""

	echo "Attaching"                  >> $ATCH_FILE 
	echo "$DATASET ----> $CONTAINER"  >> $ATCH_FILE 
	echo ""                           >> $ATCH_FILE 

	rucio attach $CONTAINER $DATASET

	if [[ $? -eq 0 ]];then
	    echo "Attaching"                  >> $SUCC_FILE 
	    echo "$DATASET ----> $CONTAINER"  >> $SUCC_FILE 
	    echo ""                           >> $SUCC_FILE 
	fi

    else
	echo "Cannot extract period for $LINE"
	kill -INT $$
    fi
done
#----------------------------------------
#----------------------------------------












