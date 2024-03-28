#!/bin/bash

TARGET=/nfs/monet_3/home/campoverde/Presentations/BplusYield_Update_I/images/cluster_jobs/

if [[ -z plots ]];then
    echo "Cannot find \"plots\" directory."
    kill -INT $$
fi



cp -r plots $TARGET
