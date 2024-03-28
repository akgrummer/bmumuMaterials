#!/bin/bash 
#########script for creating MVA training jobs on the lxplus batch
. /afs/cern.ch/sw/lcg/external/gcc/4.9/x86_64-slc6-gcc49-opt/setup.sh
cd /afs/cern.ch/sw/lcg/app/releases/ROOT/6.06.06/x86_64-slc6-gcc49-opt/root
. bin/thisroot.sh
cd -

queue=1nh
### all available: bqueues -u <username>

export WORK_DIR=${HOME}/bsmumu-cbdt
export EXE_PATH=${WORK_DIR}/bin
mkdir -p ${WORK_DIR}/out/
export OUTDIR=${WORK_DIR}/out

#mdval=( 2 3 4 5 6 )
#mdval=( 2 3 4 5 6 7 8 9 10 11 12 13 14 15 )
mdval=(2)    
#ndsize=( 0.1 0.2 0.5 1.0 2.0 5.0 10.0 )
ndsize=(0.5)
#bbeta=( 0.1 0.2 0.4 0.5 0.6 )
bbeta=(0.5)
ntrees=(500)
#ncuts=(100)
TNUM=0
for NTrees in "${ntrees[@]}"
    do
    for AdaBoostBeta in "${bbeta[@]}"
	do
	for MinNodeSize in "${ndsize[@]}"
	    do
	    for MaxDepth in "${mdval[@]}"
		do
		cd ${OUTDIR}
		ScriptName=job_${TNUM}.sh
		echo "::: INFO creating Batch steering script: ${ScriptName}"
		JobName=mvatraining_${TNUM}
		cat <<EOF > ${ScriptName}
#!/bin/bash
#############################################################################
# Job for submitting a batch job (on lxplus batch system)
# This script sets parameters steering each job
# Then each individual job is executed
#############################################################################

export LD_LIBRARY_PATH=${WORK_DIR}/:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=${WORK_DIR}/lib:$LD_LIBRARY_PATH
${EXE_PATH}/runMVA ${WORK_DIR}/cfg/bdt2012final.cfg :MaxDepth=${MaxDepth}:MinNodeSize=${MinNodeSize}:AdaBoostBeta=${AdaBoostBeta}:NTrees=${NTrees} ${TNUM}

EOF
	    chmod 755 ${ScriptName}
	    bsub -q ${queue} -J ${JobName} -o ${OUTDIR} -N ${ScriptName}
            cd -
	    ((TNUM++))
	    done
	done
    done
done
