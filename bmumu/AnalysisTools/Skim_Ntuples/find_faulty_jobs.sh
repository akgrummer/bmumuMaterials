#!/bin/bash

#*******************************
get_node()
{
    OUT_FILE=$1
    RGX_NODE="INFO::RUNNING ON: (.*)"
    NODE="not found"
    
    while read LINE;do
        if [[ $LINE =~ $RGX_NODE ]];then
            NODE=${BASH_REMATCH[1]}
            break
        fi 
    done < $OUT_FILE
}
#*******************************
rm -f failed.log
rm -f failing_nodes.log

let "NTOTAL=0"
let "NFAULTY=0"
let "PENDING=0"

mkdir -p failed
rm -f failed/*
for FILE in `find ./300* -name "*.err" -type f`;do
    NLINES=$(wc -l $FILE | awk -F " " '{print$1}')
    let "NTOTAL+=1"
    if [[ $NLINES -gt 0 ]];then
	let "NFAULTY+=1"
        echo "Found problems with: $FILE" >> failed.log
	cp $FILE failed
        OUT_FILE=${FILE%.err}.out
        get_node $OUT_FILE
        echo "in node \"$NODE\"" >> failed.log
	echo $NODE >> failing_nodes.log
	echo "" >> failed.log
    fi
done

if [[ -f failing_nodes.log ]];then
    cat failing_nodes.log | sort | uniq -c > tmp.log
    mv tmp.log failing_nodes.log
fi
#*******************************
NRUNNING=$(squeue -u $USER | wc -l)
let "NRUNNING-=1"
let "NSUCCESS=NTOTAL-NRUNNING-NFAULTY"

echo "Total jobs $NTOTAL"
echo "Total failed jobs $NFAULTY"
echo "Jobs still running $NRUNNING"
echo "Jobs succeeded $NSUCCESS"







