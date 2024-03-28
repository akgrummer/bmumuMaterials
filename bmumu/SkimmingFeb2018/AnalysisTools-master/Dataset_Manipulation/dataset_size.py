import os
import sys

import pyAMI.client
import pyAMI.atlas.api as AtlasAPI

#***********************************************
#Check for file with list of datasets
#***********************************************
def check():
    if not os.path.isdir(TEXT_DIR):
        print("Directory %s not found." % TEXT_DIR)
        exit(1)

    if len(args) < 2:
        print("Usage:")
        print("    python get_dataset_size.py TEXTFILE")
        exit(1)

    if not os.path.isfile("%s/%s" % (TEXT_DIR, args[1]) ):
        print("Cannot find \"%s\"" % INPUTFILE)
        exit(1)
#***********************************************
#Preliminary pyAMI stuff
#***********************************************
client = pyAMI.client.Client('atlas')
AtlasAPI.init()
#***********************************************
#Open file with datasets
#***********************************************
args=sys.argv
TEXT_DIR="text"

check()

INPUTFILE=args[1]

ifile=open("%s/%s" % (TEXT_DIR, INPUTFILE) )
l_datasets=ifile.read().splitlines()
ifile.close()
#***********************************************
#Check sizes of datasets and save them
#***********************************************
OUTPUTFILE=INPUTFILE.split(".")[0] + "_size.txt"
ofile=open("%s/%s" % (TEXT_DIR, OUTPUTFILE), "w")

total_size=0
for dataset in l_datasets:
    print("Processing dataset \"%s\"" % dataset)
    l_dic=AtlasAPI.get_dataset_info(client, dataset)
    size = float(l_dic[0]["totalSize"]) / (1024**3)
    total_size += size
    ofile.write("{0:10.3f} GB {1:60}\n".format(size, dataset) )

ofile.write("\n")
ofile.write("Total Size: %.3f GB" % total_size)
ofile.close()
#***********************************************
#***********************************************
