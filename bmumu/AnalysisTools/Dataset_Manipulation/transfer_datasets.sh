#!/bin/bash

#------------------------------------------------------
findDSID()
{
    DIR=$1

    if [[ $DIR =~ .*\.([0-9]{6})\..* ]];then
	DSID=${BASH_REMATCH[1]}
    fi
}
#------------------------------------------------------
transfer()
{
    OPREFIX=$1

    for DIR in `find -mindepth 1 -type d -name "*$OPREFIX*"`;do
	findDSID $DIR

	if [ $OPREFIX == "BPHY8_NTUP" ];then
	    SAMPLE=${SAMPLES_UNSKIM[$DSID]}
	elif [ $OPREFIX == "BPHY8_FNTUP" ];then
	    SAMPLE=${SAMPLES_SKIM[$DSID]}
	fi

	if [[ -z $SAMPLE ]];then
	    continue
	fi

	TARGET=$DESTIN/$SAMPLE/$VERSION/$DIR
	echo "Source $DIR"
	echo "Target $TARGET"
	echo ""

	xrdfs root://$SERVER/$DESTIN mkdir -p $TARGET
	xrdcp -r $DIR root://$SERVER/$TARGET/
    done
}
#------------------------------------------------------
#Check if XROOTD is there
#------------------------------------------------------
which xrdfs
if [ $? != 0 ];then
    echo "Cannot find xrdfs"
    kill -INT $$
fi

which xrdcp
if [ $? != 0 ];then
    echo "Cannot find xrdcp"
    kill -INT $$
fi
#------------------------------------------------------
SERVER=eosatlas.cern.ch
DESTIN=/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuRel21Prod1/ntup/skimmed_MC/
VERSION="v3"

declare -A SAMPLES_SKIM
SAMPLES_SKIM=( ["300306"]="bbmumuX" ["300307"]="bbmumuX" ["300203"]="bbJpsiX"
               ["300404"]="BpJpsiKplus" ["300405"]="BmJpsiKminus" 
	       ["300406"]="BpJpsiPiPlus" ["300437"]="BmJpsiPiMinus"
	       ["300426"]="Bsmumu" ["300430"]="Bmumu" ["300438"]="BsJpsiPhi")

declare -A SAMPLES_UNSKIM
SAMPLES_UNSKIM=( ["300431"]="Bhh" ["300432"]="BsKmunu" ["300433"]="BdPimunu" ["300434"]="LamPmunu" )
#------------------------------------------------------
transfer $SAMPLES_SKIM   "BPHY8_FNTUP"
#transfer $SAMPLES_UNSKIM "BPHY8_NTUP"
#------------------------------------------------------

