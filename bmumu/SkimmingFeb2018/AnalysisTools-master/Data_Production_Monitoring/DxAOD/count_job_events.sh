#!/bin/bash

#********************************************
check()
{
    hash rucio 2>/dev/null
    if [[ $? -ne 0 ]];then
        echo "You need to setup rucio."
        kill -INT $$
    fi
}
#********************************************
get_events()
{
    DATASET=$1
    REGEX_EVS="Total events : ([0-9]+)"

    rucio list-files $DATASET > tmp.txt
    tail -n 5 tmp.txt > tail_tmp.txt
    while read LINE;do
        if [[ $LINE =~ $REGEX_EVS ]];then
            NEVENTS=${BASH_REMATCH[1]}
        fi
    done < tail_tmp.txt
    rm -f tmp.txt tail_tmp.txt
}
#********************************************
get_all_events()
{
    IFILE=$1
    let "TOTAL=0"
    while read DATASET;do
        get_events $DATASET
        let "TOTAL+=$NEVENTS"
    done < $IFILE
}
#********************************************
check
for FILE in `ls datasets/split_*`;do
    get_all_events $FILE
    echo "FILE: $FILE  EVENTS: $TOTAL"
done
#********************************************
