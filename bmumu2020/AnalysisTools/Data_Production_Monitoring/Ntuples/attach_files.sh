#!/bin/bash

DIR_FILES="Datasets_Files/"
#********************************************
check()
{
    if [[ ! -f $FILENAME ]];then
        echo "File $FILENAME not found."
        kill -INT $$
    fi
}
#********************************************
attach_files()
{
    FILENAME=$1
    DATASET=$2

    check

    while read LINE;do
        FILE=$(echo $LINE | awk -F " " '{print$1}')
        echo "Attaching $FILE to $DATASET"
        rucio attach $DATASET $FILE 
    done < $FILENAME
}
#********************************************
attach_files $DIR_FILES/Delayed_Bmumu.txt               user.acampove.BPHY8_201709.NTUP.Data_BPhysDelayed_001_Bmumu 
attach_files $DIR_FILES/Delayed_Bplus.txt               user.acampove.BPHY8_201709.NTUP.Data_BPhysDelayed_001_BJpsiK
attach_files $DIR_FILES/Delayed_BsJpsiPhi.txt           user.acampove.BPHY8_201709.NTUP.Data_BPhysDelayed_001_BJpsiPhi
attach_files $DIR_FILES/Delayed_Log.txt                 user.acampove.BPHY8_201709.NTUP.Data_BPhysDelayed_001_Log
attach_files $DIR_FILES/Delayed_Hist.txt                user.acampove.BPHY8_201709.NTUP.Data_BPhysDelayed_001_Hist

attach_files $DIR_FILES/Main_Bmumu.txt                  user.acampove.BPHY8_201709.NTUP.Data_Main_001_Bmumu 
attach_files $DIR_FILES/Main_Bplus.txt                  user.acampove.BPHY8_201709.NTUP.Data_Main_001_BJpsiK
attach_files $DIR_FILES/Main_BsJpsiPhi.txt              user.acampove.BPHY8_201709.NTUP.Data_Main_001_BJpsiPhi
attach_files $DIR_FILES/Main_Log.txt                    user.acampove.BPHY8_201709.NTUP.Data_Main_001_Log
attach_files $DIR_FILES/Main_Hist.txt                   user.acampove.BPHY8_201709.NTUP.Data_Main_001_Hist

attach_files $DIR_FILES/Main_With_Delayed_Bmumu.txt     user.acampove.BPHY8_201709.NTUP.Data_Main_With_Delayed_Available_001_Bmumu 
attach_files $DIR_FILES/Main_With_Delayed_Bplus.txt     user.acampove.BPHY8_201709.NTUP.Data_Main_With_Delayed_Available_001_BJpsiK
attach_files $DIR_FILES/Main_With_Delayed_BsJpsiPhi.txt user.acampove.BPHY8_201709.NTUP.Data_Main_With_Delayed_Available_001_BJpsiPhi
attach_files $DIR_FILES/Main_With_Delayed_Log.txt       user.acampove.BPHY8_201709.NTUP.Data_Main_With_Delayed_Available_001_Log
attach_files $DIR_FILES/Main_With_Delayed_Hist.txt      user.acampove.BPHY8_201709.NTUP.Data_Main_With_Delayed_Available_001_Hist
#********************************************

