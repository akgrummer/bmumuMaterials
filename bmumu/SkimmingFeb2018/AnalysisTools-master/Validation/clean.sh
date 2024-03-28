#!/bin/bash

rm -f err/*.err
rm -f out/*.out
rm -rf Output*/*
rm -f *.pyc
rm -f *.root
rm -f *.json

WHAT_TO_CLEAN=$1
if [[ $WHAT_TO_CLEAN == "ALL" ]];then
    rm -rf json_*
    rm -rf Output_*
    rm -rf plots_*
fi

if [[ $WHAT_TO_CLEAN == "PLOTS" ]];then
    rm -rf plots_*/*.pdf
fi

