#!/bin/bash

setupATLASSi
lsetup "lcgenv -p LCG_92 x86_64-slc6-gcc62-opt HepPDT"
lsetup "gcc gcc620_x86_64_slc6"
lsetup "python 2.7.13-x86_64-slc6-gcc62"

export CPLUS_INCLUDE_PATH=:/cvmfs/sft.cern.ch/lcg/releases/LCG_92/HepPDT/2.06.01/x86_64-slc6-gcc62-opt/include/
