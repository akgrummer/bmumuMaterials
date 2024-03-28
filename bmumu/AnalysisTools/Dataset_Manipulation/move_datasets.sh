#!/bin/bash

SAMPLEDIR=/data/atlasb7/grid/
VERSION=v2
FORMAT=FNTUP

declare -A SAMPLES
SAMPLES=( ["300306"]="bbmumuX" ["300307"]="bbmumuX" ["300203"]="bbJpsiX"
          ["300404"]="BpJpsiKplus" ["300405"]="BmJpsiKminus" 
	  ["300406"]="BpJpsiPiPlus" ["300437"]="BmJpsiPiMinus"
	  ["300426"]="Bsmumu" ["300430"]="Bmumu"
	  ["300438"]="BsJpsiPhi"
	  ["300431"]="Bhh" ["300432"]="BsKmunu" ["300433"]="BdPimunu" ["300434"]="LamPmunu" )

for DIR in `find . -mindepth 1 -type d | sort -n`;do
    if [[ $DIR =~ user\.acampove\.([0-9]{6})\.BPHY8_$FORMAT.* ]];then
	DSID=${BASH_REMATCH[1]}
	DIR_SAMPLE=${SAMPLES[$DSID]}

        TARGET=$SAMPLEDIR/$DIR_SAMPLE/$FORMAT/$VERSION/
	if [[ ! -d $TARGET ]];then
	    echo "Making $TARGET"
	    mkdir -p $TARGET
	fi

	if [[ $? != 0 ]];then
	    echo "Could not make $TARGET"
	    kill -INT $$
	fi

	echo "$DIR > $TARGET"
	mv $DIR $TARGET
    fi
done

