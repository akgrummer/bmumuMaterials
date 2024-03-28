#!/bin/bash
LD_LIBRARY_PATH=/usr/local/lib64/:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH
shopt -s expand_aliases
export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
alias setupATLAS='source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh'
setupATLAS 
lsetup "root 6.14.04-x86_64-slc6-gcc62-opt"

infile="/afs/cern.ch/user/a/agrummer/htcondorTest/LASTskim.output_2685758.root"
outfile="/afs/cern.ch/user/a/agrummer/htcondorTest/out.root" 
export exe_path=/afs/cern.ch/user/a/agrummer/htcondorTest
${exe_path}/selectbpbkg ${infile} ${outfile}
