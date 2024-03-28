#!/bin/bash

#**********************************
#Do checks
#**********************************
check()
{
    if [[ ! -d samples_status ]];then
        echo "Input directory \"samples_status\" does not exist."
        kill -INT $$
    fi

    if [[ ! -f $INPUT ]];then
        echo "File \"$INPUT\" not found."
        kill -INT $$
    fi

    which rucio 2&> /dev/null

    #if [[ "$?" -ne "0" ]];then
    #    echo "You need to setup rucio."
    #    kill -INT $$
    #fi
}
#**********************************
INPUT="samples_status/done_bphy8.txt"

check
#**********************************
mkdir -p rucio

INPUT_DS_MAIN="./rucio/input_main_run_event.txt"
OUTPUT_DS_MAIN="./rucio/output_main_run_event.txt"

INPUT_DS_DELAYED="./rucio/input_delayed_run_event.txt"
OUTPUT_DS_DELAYED="./rucio/output_delayed_run_event.txt"

rm -f $INPUT_DS_MAIN
rm -f $OUTPUT_DS_MAIN

rm -f $INPUT_DS_DELAYED
rm -f $OUTPUT_DS_DELAYED

while read LINE;do
    REGEX_INPUT_MAIN="Input:.*:(.*Main.*),\sOutput:.*"
    REGEX_OUTPUT_MAIN="Output:(.*Main.*),\sTaskID:.*"

    REGEX_INPUT_DELAYED="Input:.*:(.*Delayed.*),\sOutput:.*"
    REGEX_OUTPUT_DELAYED="Output:(.*Delayed.*),\sTaskID:.*"

    REGEX_NUMBER="^[0-9]+$"

    if [[ $LINE =~ $REGEX_INPUT_MAIN ]];then
        IN_DATASET=${BASH_REMATCH[1]}

        IN_NEVENTS=$(rucio list-files $IN_DATASET | grep "Total events" |  sed -E "s|Total events : ([0-9]+)|\1|g")
        RUNNUMBER=$(echo $IN_DATASET | sed -E "s|.*_13TeV\.([0-9]+)\.physics.*|\1|g")

        if ! [[ $IN_NEVENTS =~ $REGEX_NUMBER ]];then
            IN_NEVENTS=0
        fi

        echo "Input Main: $RUNNUMBER   $IN_NEVENTS"
        echo "$RUNNUMBER   $IN_NEVENTS" >> $INPUT_DS_MAIN
    fi

    if [[ $LINE =~ $REGEX_OUTPUT_MAIN ]];then
        OT_DATASET=${BASH_REMATCH[1]}

        OT_NEVENTS=$(rucio list-files $OT_DATASET | grep "Total events" |  sed -E "s|Total events : ([0-9]+)|\1|g")
        RUNNUMBER=$(echo $OT_DATASET | sed -E "s|.*_13TeV\.([0-9]+)\.physics.*|\1|g")

        if ! [[ $OT_NEVENTS =~ $REGEX_NUMBER ]];then
            OT_NEVENTS=0
        fi

        echo "Output Main: $RUNNUMBER   $OT_NEVENTS"
        echo "$RUNNUMBER   $OT_NEVENTS" >> $OUTPUT_DS_MAIN
    fi 

    if [[ $LINE =~ $REGEX_INPUT_DELAYED ]];then
        IN_DATASET=${BASH_REMATCH[1]}

        IN_NEVENTS=$(rucio list-files $IN_DATASET | grep "Total events" |  sed -E "s|Total events : ([0-9]+)|\1|g")
        RUNNUMBER=$(echo $IN_DATASET | sed -E "s|.*_13TeV\.([0-9]+)\.physics.*|\1|g")

        if ! [[ $IN_NEVENTS =~ $REGEX_NUMBER ]];then
            IN_NEVENTS=0
            fi

        echo "Input Delayed: $RUNNUMBER   $IN_NEVENTS"
        echo "$RUNNUMBER   $IN_NEVENTS" >> $INPUT_DS_DELAYED
    fi

    if [[ $LINE =~ $REGEX_OUTPUT_DELAYED ]];then
        OT_DATASET=${BASH_REMATCH[1]}

        OT_NEVENTS=$(rucio list-files $OT_DATASET | grep "Total events" |  sed -E "s|Total events : ([0-9]+)|\1|g")
        RUNNUMBER=$(echo $OT_DATASET | sed -E "s|.*_13TeV\.([0-9]+)\.physics.*|\1|g")

        if ! [[ $OT_NEVENTS =~ $REGEX_NUMBER ]];then
            OT_NEVENTS=0
        fi

        echo "Output Delayed: $RUNNUMBER   $OT_NEVENTS"
        echo "$RUNNUMBER   $OT_NEVENTS" >> $OUTPUT_DS_DELAYED
    fi 
done < $INPUT 
