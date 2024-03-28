#!/bin/bash 
#########script for creating MVA training jobs on the lxplus batch
#. /afs/cern.ch/sw/lcg/external/gcc/4.9/x86_64-slc6-gcc49-opt/setup.sh
#lsetup "root 6.08.06-x86_64-slc6-gcc49-opt"

# . /afs/cern.ch/sw/lcg/external/gcc/6.2/x86_64-slc6-gcc62-opt/setup.sh 
# lsetup "root 6.10.02-x86_64-slc6-gcc62-opt"

# setupATLAS
# lsetup root

#export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH                                                                                                                                                               
#export LD_LIBRARY_PATH=./lib:$LD_LIBRARY_PATH
#bin/runMVA cfg/bdt2012final.cfg :MaxDepth=2:MinNodeSize=0.5:AdaBoostBeta=0.5:NTrees=500 2
#cd /afs/cern.ch/sw/lcg/app/releases/ROOT/6.06.06/x86_64-slc6-gcc49-opt/root
#. bin/thisroot.sh
#cd -

# queue=1nh
### all available: bqueues -u <username>

# export WORK_DIR=${HOME}/cernbox/www/bmumu/bsmumu-cbdt
# for aidans mac
# export WORK_DIR=/Users/agrummer/cernbox/www/bmumu/myMVA
# mkdir -p ${WORK_DIR}/OutputMVAMar14
# export Output_DIR=${WORK_DIR}/OutputMVAMar14
# export MacrosDir=/Users/agrummer/Desktop/Bmumu/Macros
# export ImportanceDir=${MacrosDir}/PythonImportance

#for pcatlunm01
# export HOME_DIR=/home/agrummer
#for lxplus
export HOME_DIR=/home/agrummer/bmumu2020
# export WORK_DIR=${HOME_DIR}/www/bmumu/myMVA
export WORK_DIR=${HOME_DIR}/BDT
# export WORK_DIR=/home/agrummer/myTraining
export OUTMVA=BDToutput
# export OUTMVA=${HOME_DIR}/BDToutput
# mkdir -p ${OUTMVA}/2019May29
# mkdir -p ${OUTMVA}/2020Mar20
# mkdir -p ${OUTMVA}/2020May20
# mkdir -p ${OUTMVA}/2020May29
# mkdir -p ${OUTMVA}/2020Jun16
# mkdir -p ${OUTMVA}/2020Jun26
# mkdir -p ${OUTMVA}/2020July3
# mkdir -p ${OUTMVA}/2020July16
# mkdir -p ${OUTMVA}/2020July22
mkdir -p ${OUTMVA}/2020Aug6
# mkdir -p ${OUTMVA}/Aug16
# mkdir -p ${OUTMVA}/2019May29/test
# mkdir -p ${OUTMVA}/2020May20/test
# mkdir -p ${OUTMVA}/Aug16/test3
# export Output_DIR=${OUTMVA}/Aug16/test3
# export Output_DIR=${OUTMVA}/2019May29/test
# export Output_DIR=${OUTMVA}/2020May29
# export Output_DIR=${OUTMVA}/2020Jun16
# export Output_DIR=${OUTMVA}/2020Jun26
# export Output_DIR=${OUTMVA}/2020July3
# export Output_DIR=${OUTMVA}/2020July16
# export Output_DIR=${OUTMVA}/2020July22
export Output_DIR=${OUTMVA}/2020Aug6
export MacrosDir=${WORK_DIR}/Macros
export ImportanceDir=${MacrosDir}/PythonImportance

# export EXE_PATH=${WORK_DIR}/bin


# mdval=( 2 3 4 5 6 )
#mdval=( 2 3 4 5 6 7 8 9 10 11 12 13 14 15 )
# mdval=( 2 )
# source SubmitmyMVA_pc01input.sh "(1)"
# mdval="${1[@]}"
mdval=($1)
# echo "${mdval[0]}"
# echo "${mdval[1]}"
#mdval=(2 3 4 5 6)
# mdval=( 7 8 9 10 11 )
# mdval=( 12 13 14 15 16 )

# ndsize=( 0.1 0.2 0.5 1.0 2.0 5.0 10.0 )
# ndsize=( 0.1 0.2 0.5 1.0 2.0)
# ndsize=( 3.0 4.0 5.0 7.0 10.0 )
ndsize=( $2 )
# ndsize="$2"
# ndsize=( 1.0 2.0 5.0 10.0 )
# ndsize=(0.5)
# ndsize=(0.2)
# bbeta=( 0.1 0.2 0.4 0.5 0.6 )
# bbeta=(0.1 0.2)
bbeta=( $3 )
# bbeta="$3"
# ntrees=(200 400 500)
ntrees=( $4 )
# ntrees="$4"
#ntrees=(600)
#ncuts=(100)
outdnamelist=( $5 )
outdnamelistSets=( $6 )
TNUM=0

# outdnamelist=(out_BIso_2018_MC16e out_nCloseTracks_2018_MC16e\
#               out_DOCA_2018_MC16e out_muM_2018_MC16e out_muP_2018_MC16e\
#               out_BIso_2017_MC16d out_nCloseTracks_2017_MC16d\
#               out_DOCA_2017_MC16d out_muM_2017_MC16d out_muP_2017_MC16d\
#               out_BIso_2016_MC16a out_nCloseTracks_2016_MC16a\
#               out_DOCA_2016_MC16a out_muM_2016_MC16a out_muP_2016_MC16a\
#               )
#for final validation before production:

# outdnamelist=(
#     out_BIso
#     # out_BIso_2018_MC16a out_nCloseTracks_2018_MC16a\
#               # out_DOCA_2018_MC16a\
#               # out_SomeVars_2018_MC16a\
#               # out_muM_2018_MC16a out_muP_2018_MC16a\
#               )
# outdnamelist=(out_nCloseTracks_2018_MC16e\
#               out_nCloseTracks_2017_MC16d\
#               out_nCloseTracks_2016_MC16a\
#               )
# outdnamelist=(out_BIso_2016_MC16a out_nCloseTracks_2016_MC16a\
#               out_DOCA_2016_MC16a out_muM_2016_MC16a out_muP_2016_MC16a\
#               )

for outdname in "${outdnamelist[@]}"
    do
    for outdset in "${outdnamelistSets[@]}"
        do 
        for NTrees in "${ntrees[@]}"
            do
            for AdaBoostBeta in "${bbeta[@]}"
                do
                for MinNodeSize in "${ndsize[@]}"
                     do
                    for MaxDepth in "${mdval[@]}"
                        do
#   cd ${OUTDIR}
# mkdir -p ${WORK_DIR}/out_MaxDepth${MaxDepth}_MinNodeSize${MinNodeSize}_AdaBoostBeta${AdaBoostBeta}_NTrees${NTrees}
# export OUTDIR=${WORK_DIR}/out_MaxDepth${MaxDepth}_MinNodeSize${MinNodeSize}_AdaBoostBeta${AdaBoostBeta}_NTrees${NTrees}
# export outdname=out_DOCA_2018_MC16e
# mkdir -p ${WORK_DIR}/${outdname}
mkdir -p ${WORK_DIR}/${Output_DIR}/${outdname}
mkdir -p ${WORK_DIR}/${Output_DIR}/${outdname}/${outdset}
export OUTDIR=${Output_DIR}/${outdname}/${outdset}
# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH${WORK_DIR}:${WORK_DIR}/src:${WORK_DIR}/lib
# args="\(\":MaxDepth=2:MinNodeSize=0.2:AdaBoostBeta=0.5:NTrees=50\"\)"
# root -l -q ${WORK_DIR}/runMVA.cxx "${args}" | tee output.txt 

echo ${outdname}
myArgs=\":MaxDepth=${MaxDepth}:MinNodeSize=${MinNodeSize}:AdaBoostBeta=${AdaBoostBeta}:NTrees=${NTrees}\"
echo ${myArgs}
root -l -q ''${WORK_DIR}'/runMVA_pc01.cxx('\"${OUTDIR}\"', '${myArgs}')' >> ${WORK_DIR}/${OUTDIR}/output.txt 2>>${WORK_DIR}/${OUTDIR}/err.txt
# root -l -q ''${WORK_DIR}'/runMVA_pc01.cxx('${myArgs}')'| tee ${OUTDIR}/output.txt 
#
# 'root -l -q ${WORK_DIR}/runMVA.cxx "(\":MaxDepth='${MaxDepth}':MinNodeSize='${MinNodeSize}':AdaBoostBeta='${AdaBoostBeta}':NTrees='${NTrees}'\")"' | tee output.txt 
# ${EXE_PATH}/runMVA ${WORK_DIR}/cfg/bdt2012final.cfg :MaxDepth=${MaxDepth}:MinNodeSize=${MinNodeSize}:AdaBoostBeta=${AdaBoostBeta}:NTrees=${NTrees} ${TNUM}
# export FinalDir=${OUTDIR}/out_MaxDepth${MaxDepth}_MinNodeSize${MinNodeSize}_AdaBoostBeta${AdaBoostBeta}_NTrees${NTrees}
#python ${ImportanceDir}'/ExtractImpAndSep.py' ${FinalDir} 
#echo "Finished running Importance Table script"

# need to be careful with this command: 
# use pgrep sleep | while read line; do ps -p $line -o ppid; done
# if it gets stuck to kill to parent (this bash file) jobs
# while [ ! -f ${OUTDIR}/bdt2016test.root ] ;
# do
#       sleep 1
# done
# ##KS macro 3 lines:
# myKSArgs=\"${WORK_DIR}/\",\"${MaxDepth}\",\"${MinNodeSize}\",\"${AdaBoostBeta}\",\"${NTrees}\"
# root -l -q -b ''${MacrosDir}'/KSTestFeb7.C('${myKSArgs}')' >> ${OUTDIR}/output.txt 2>>${OUTDIR}/err.txt
# echo "Finished running ROC and KS calculation script"
# # Move diectory out of cernbox
# mv ${OUTDIR} ${Output_DIR}
      ((TNUM++))
    done     
  done
      done
  done
    done
done
