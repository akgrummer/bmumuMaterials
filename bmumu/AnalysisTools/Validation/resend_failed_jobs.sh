#!/bin/bash

cd err

JOBIDS=$(cat *.err | grep CANCELLED | awk -F " " '{print$4}')

cd ..

for JOBID in ${JOBIDS[@]};do
    ARGS=$(cat ./out/output-"$JOBID".out | grep -Eo "([0-9]+\s[0-9]+\s[0-9]+\s[0-9]+\sValidate.py)")
    sbatch split.job $ARGS
done

