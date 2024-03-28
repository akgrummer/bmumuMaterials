#!/bin/bash

which ami

if [[ $? -ne 0 ]];then
    echo "pyami not setup."
    kill -INT $$
fi

mkdir -p runs

PERIODS=("15_D" "15_E" "15_F" "15_G" "15_H" "15_J" "16_A" "16_B" "16_C" "16_D" "16_E" "16_F" "16_G" "16_I" "16_K" "16_L")

for PERIOD in ${PERIODS[@]};do
    YEAR=$(cut -d'_' -f1 <<< $PERIOD)
    PERIOD=$(cut -d'_' -f2 <<< $PERIOD)

    FILENAME=./runs/runs_"$YEAR"_"$PERIOD".txt
    rm -f $FILENAME

    ami list runs --year $YEAR --data-periods $PERIOD >> $FILENAME
done

