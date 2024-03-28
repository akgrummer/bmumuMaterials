#!/bin/bash

#***********************************
#Do preliminary checks
#***********************************
check()
{
    if [[ ! -f $SAMPLES ]];then
	echo "File \"$SAMPLES\" not found."
	kill -INT $$
    fi

    if [[ ! -d $TARGET ]];then
	echo "Target directory \"$TARGET\", does not exist"
	kill -INT $$
    fi
}
#***********************************
#Setup everything
#***********************************
source ../Utils/setup_atlas.sh

setup_tool rucio rucio

TARGET="/nfs/moroni_7/data/atlasb7/grid/BpJpsiKplus/xAOD15_ac/Production_MC_DxAOD"
SAMPLES="$(pwd)/text/download_samples.txt"

check
#***********************************
#Download datasets
#***********************************
cd $TARGET

while read DATASET;do
    echo $DATASET
    rucio download $DATASET
done<$SAMPLES

cd -
#***********************************
#***********************************

