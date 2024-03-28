#!/bin/bash

cd samples_status

for FILE in `ls *`;do
    echo "Moving $FILE to old_$FILE"

    if [[ $FILE == *old* ]];then
        continue
    fi

    mv $FILE "old_"$FILE
done

cat old_done_bphy8.txt old_not_done_bphy8.txt > done_bphy8.txt
cat old_done_bphy9.txt old_not_done_bphy9.txt > done_bphy9.txt

cd -

