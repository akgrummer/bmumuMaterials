#!/bin/bash

cd Datasets_Files

cat Delayed_Log.txt | awk -F "." '{print$8}' | uniq -c > id_log_delayed.txt
cat Delayed_Hist.txt | awk -F "." '{print$4}' | uniq -c > id_hist_delayed.txt

cat Main_Log.txt | awk -F "." '{print$8}' | uniq -c > id_log_main.txt
cat Main_Hist.txt | awk -F "." '{print$4}' | uniq -c > id_hist_main.txt

cat Main_With_Delayed_Log.txt | awk -F "." '{print$8}' | uniq -c > id_log_main_with_delayed.txt
cat Main_With_Delayed_Hist.txt | awk -F "." '{print$4}' | uniq -c > id_hist_main_with_delayed.txt

cd -
