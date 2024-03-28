#!/bin/bash

MAIN=./datasets/main_done_bphy8_output.txt
DELY=./datasets/delayed_done_bphy8_output.txt

get_sizes()
{
    DATASET=$1
    OFILE=$2
    rucio list-files $DATASET | grep ".pool.root" | awk -F "|" '{print$5}' >> $OFILE
}

TARGET="main_sizes.txt"
rm -f $TARGET
while read DATASET;do
    echo $DATASET >> $TARGET
    get_sizes $DATASET $TARGET
done < $MAIN

TARGET="dely_sizes.txt"
rm -f $TARGET
while read DATASET;do
    echo $DATASET >> $TARGET
    get_sizes $DATASET $TARGET 
done < $DELY

