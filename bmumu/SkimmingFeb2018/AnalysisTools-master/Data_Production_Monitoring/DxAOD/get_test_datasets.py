import os
import sys
import re
#*****************************************
NRUNS=5
STREAM=sys.argv[1]

FILE_EVENTS="rucio/output_%s_run_event.txt" % STREAM
FILE_DATASETS="samples_status/%s_done_bphy8.txt" % STREAM

OUTPUT_DIRECTORY="Test_Datasets"

print("File with events: %s" % FILE_EVENTS)
print("File with datasets: %s" % FILE_DATASETS)
#*****************************************
def GetKey(dictionary, value):
    for key, val in dictionary.items():
        if val == value:
            return key

    return ""
#*****************************************
#Get runs with lowest number of events
#*****************************************
if not os.path.isfile(FILE_EVENTS):
    print("File \"\" not found")
    exit(1)

ifile_events=open(FILE_EVENTS)
lines=ifile_events.read().splitlines()
ifile_events.close()

d_run_evs = dict()
for line in lines:
    l_line = line.split("   ")
    evs=int(l_line[1])
    run=l_line[0]

    if len(d_run_evs) == 0:
        max_evs = 0
        max_run = 0
    else:
        max_evs=max(d_run_evs.values())
        max_run=GetKey(d_run_evs, max_evs)

    if len(d_run_evs) >= NRUNS:
        if evs < max_evs and evs > 0:
            del d_run_evs[max_run]
            d_run_evs[run] = evs
    elif evs > 0:
        d_run_evs[run] = evs
#*****************************************
#Get datasets corresponding to those runs.
#*****************************************
ifile_datasets=open(FILE_DATASETS)
l_line=ifile_datasets.read().splitlines()
ifile_datasets.close()

l_dataset=list()
for line in l_line:
    for run_number in d_run_evs:
        if run_number in line:
            l_match = re.findall("Input:.*,\sOutput:(.*),\sTaskID.*", line)
            l_dataset.append(l_match[0])
#*****************************************
#Save datasets
#*****************************************
if not os.path.isdir(OUTPUT_DIRECTORY):
    os.mkdir(OUTPUT_DIRECTORY)

ofile = open("%s/%s_datasets.txt" % (OUTPUT_DIRECTORY, STREAM), "w")
for dataset in l_dataset:
    ofile.write("%s\n" % dataset)
ofile.close()
#*****************************************

