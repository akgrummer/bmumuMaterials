import os
import re

import pyAMI.client
import pyAMI.atlas.api as AtlasAPI

#*******************************************
#Needed for pyami to work
#*******************************************
client = pyAMI.client.Client('atlas')
AtlasAPI.init()
#*******************************************
#Returns size of dataset
#*******************************************
def get_size(dataset):
    l_dic=AtlasAPI.get_dataset_info(client, dataset)
    size=float(l_dic[0]["totalSize"])/(1024 ** 3)

    return size
#*******************************************
def save_as_text(d_dataset, filename):
#*******************************************
    ofile=open(filename, "w")

    total_size=0
    for dataset in d_dataset:
        ds_size = d_dataset[dataset]
        total_size+=ds_size
        ofile.write("{0:90} {1:8} GB\n".format(dataset, ds_size) )

    ofile.write("\n")
    ofile.write("Total Size: %.3f GB" % total_size) 
    ofile.close()
def check():
    if not os.path.isfile(FILENAME):
        print("File %s does not exist.")
        exit(1)
#*******************************************
def get_run_number(dataset):
    match=re.search(".*13TeV\.([0-9]{8})\.physics.*", dataset)
    if match:
        return int(match.group(1))
    else:
        return -1
#*******************************************
FILENAME="jobs_status/done_input.txt"
check()

ifile=open(FILENAME)
l_dataset=ifile.read().splitlines()
ifile.close()

d_ds_main=dict()
d_ds_dely=dict()
d_ds_main_dely=dict()

for i_dataset, dataset in enumerate(l_dataset):

    match=re.match("(.*)_tid.*", dataset)
    if not match:
        print("Cannot recognize dataset \"%s\"" % dataset)
        continue

    dataset=match.group(1)
    print("Processing dataset \"%s\"." % dataset)

    run_number=get_run_number(dataset)
    if run_number == -1:
        print("Cannot process dataset %s" % dataset)
        exit(1)

    is_main = "Delayed" not in dataset
    with_delayed = run_number >= 302956 
    
    ds_size = get_size(dataset)

    if not is_main:
        d_ds_dely[dataset]=ds_size
    elif is_main and with_delayed:
        d_ds_main_dely[dataset]=ds_size
    elif is_main and not with_delayed:
        d_ds_main[dataset]=ds_size
    else:
        print("Cannot recognize dataset %s." % dataset)
#*******************************************
OUTPUT_DIR="DxAOD_Lists"
if not os.path.isdir(OUTPUT_DIR):
    os.mkdir(OUTPUT_DIR)

save_as_text(d_ds_main,      "%s/main.txt" % OUTPUT_DIR)
save_as_text(d_ds_dely,      "%s/delayed.txt" % OUTPUT_DIR)
save_as_text(d_ds_main_dely, "%s/main_with_delayed.txt" % OUTPUT_DIR)
#*******************************************

