#!/bin/bash

#----------------------------------------------
#Setup release
#----------------------------------------------
setup_release()
{
    if [[ $AnalysisBase_SET_UP -eq 1 ]];then
	echo "Already setup, skipping."
    elif [[ -f .asetup.save ]];then
	echo "Restoring last session release."
	asetup --restore
    else
	asetup AnalysisBase,21.2,latest,here
    fi
}
#----------------------------------------------
#Setup tool if not setup
#----------------------------------------------
setup_tool()
{
    TOOL=$1
    NAME=$2
    TOOL_PATH=$(which $TOOL)

    hash $TOOL &>/dev/null
    STATUS=$?
    if [[ $STATUS -ne 0 ]] || [[ $TOOL_PATH != *cvmfs* ]];then
        lsetup $NAME
    fi
}
#----------------------------------------------
#Setup if needed
#----------------------------------------------
type lsetup &>/dev/null
if [[ $? -ne 0 ]];then
    setupATLASSi || setupATLAS &>/dev/null
fi
#----------------------------------------------
#----------------------------------------------

