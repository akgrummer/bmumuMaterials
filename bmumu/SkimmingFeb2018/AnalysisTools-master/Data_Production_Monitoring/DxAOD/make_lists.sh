#!/bin/bash

#*******************************
check()
{
    if [[ ! -f $MAIN_FILE ]];then
        echo "File $MAIN_FILE not found."
        kill -INT $$
    fi

    if [[ ! -f $DELY_FILE ]];then
        echo "File $DELY_FILE not found."
        kill -INT $$
    fi
}
#*******************************
MAIN_FILE="main_done_bphy8_output.txt"
DELY_FILE="delayed_done_bphy8_output.txt"

cd datasets

check

rm -f split_*

shuf $MAIN_FILE > rdm_$MAIN_FILE
split -d -l 31 rdm_$MAIN_FILE split_main_

shuf $DELY_FILE > rdm_$DELY_FILE
split -d -l 15 rdm_$DELY_FILE split_dely_

cd -
#*******************************
