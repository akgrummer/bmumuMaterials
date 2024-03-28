#!/bin/bash

setupATLAS
#Code will break with later versions of ROOT
lsetup "root 6.12.06-x86_64-slc6-gcc62-opt"
#Setup HepPDT
lsetup "lcgenv -p LCG_92 x86_64-slc6-gcc62-opt HepPDT"
#lsetup "gcc gcc620_x86_64_slc6"
#lsetup "python 2.7.13-x86_64-slc6-gcc62"

#Include path is not set when setting up HepPDF => set it here.
export CPLUS_INCLUDE_PATH=:/cvmfs/sft.cern.ch/lcg/releases/LCG_92/HepPDT/2.06.01/x86_64-slc6-gcc62-opt/include/

#----------------------------------------------
#Build dictionary library
#----------------------------------------------
#DICT_DIRECTORY=../RootDictionary/
#export DICT_LIBRARY=$DICT_DIRECTORY/libgeneric.so
#if [[ ! -d $DICT_DIRECTORY ]];then
#    echo "Cannot find directory with dictionary code \"$DICT_DIRECTORY\""
#    kill -INT $$
#fi
#
#cd $DICT_DIRECTORY
#make
#cd -
#
#if [[ ! -f $DICT_LIBRARY ]];then
#    echo "Cannot find library \"$DICT_LIBRARY\"."
#    kill -INT $$
#fi
#----------------------------------------------
#----------------------------------------------


