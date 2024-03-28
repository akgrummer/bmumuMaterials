#!/bin/bash

#*****************************************
Set_Filename()
{
    DATASET=$1

    DSID=$(echo $DATASET | sed -r "s/.*\.([0-9]{8})\..*/\1/g")
    DSNUMBER=$((10#$DSID)) 
    STREAM=""

    if [[ $DATASET == *main*  ]] && [[ $DSNUMBER -lt $DS_RUN ]];then
        STREAM="Main"
    elif [[ $DATASET == *main*  ]] && [[ $DSNUMBER -ge $DS_RUN ]];then
        STREAM+="Main_With_Delayed"
    elif [[ $DATASET == *delayed* ]];then
        STREAM="Delayed"
    else
        echo "Unrecognized dataset $DATASET or DS number $DSNUMBER"
        kill -INT $$
    fi

    if [[ $DATASET == *Topo_Bmumu* ]];then
        TYPE="Bmumu"
    elif [[ $DATASET == *Topo_BpJpsiK* ]];then
        TYPE="Bplus"
    elif [[ $DATASET == *Topo_BsJpsiPhi* ]];then
        TYPE="BsJpsiPhi"
    elif [[ $DATASET == *.log* ]];then
        TYPE="Log"
    elif [[ $DATASET == *_hist* ]];then
        TYPE="Hist"
    else
        echo "Unrecognized dataset: $DATASET"
        kill -INT $$
    fi

    FILENAME=$STREAM"_"$TYPE".txt"
}
#*****************************************
DS_RUN=302956
RUN_2015=284484

INPUT_DIR=jobs_status
OUTPUT_DIR=Datasets_Files

mkdir -p $OUTPUT_DIR 
rm -f $OUTPUT_DIR/*

while read DATASET;do
    echo "Reading dataset $DATASET"

    Set_Filename $DATASET
    
    FILES=( $(rucio list-files $DATASET | grep user. | awk -F "|" '{print$2}') )
    for FILE in ${FILES[@]};do
        echo "$FILE         $DSID" >> $OUTPUT_DIR/$FILENAME
    done
    
    URLS=( $(rucio list-file-replicas $DATASET --pfn --protocols root) )
    for URL in ${URLS[@]};do
        if [[ $DATASET == *Bmumu* ]];then
            echo $URL  >> $OUTPUT_DIR/"URLS_Bmumu.txt"
        elif [[ $DATASET == *BpJpsiK* ]];then
            echo $URL  >> $OUTPUT_DIR/"URLS_Bplus.txt"
        elif [[ $DATASET == *BsJpsiPhi* ]];then
            echo $URL  >> $OUTPUT_DIR/"URLS_BsJpsiPhi.txt"
        fi
    done

done < $INPUT_DIR/done_output.txt
#*****************************************

