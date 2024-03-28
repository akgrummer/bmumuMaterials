#!/bin/bash

JOBID=$1

if [ -z $JOBID ];then
    echo "Need a job id as argument, e.g. 4013".
    kill -INT $$
fi

pbook <<EOF
sync()
show($JOBID,forceUpdate=True, upperJobID=100000)
quit()
EOF

