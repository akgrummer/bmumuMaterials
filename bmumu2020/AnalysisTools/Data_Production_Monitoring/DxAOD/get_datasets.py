import os
import sys
import re
#*********************************************************
GRL_2015="GRL/runs_2015.txt"
GRL_2016="GRL/runs_2016.txt"

def GetGRLRuns():
    if not os.path.isfile(GRL_2015):
        print("Cannot find %s" % GRL_2015)
        exit(1)

    if not os.path.isfile(GRL_2016):
        print("Cannot find %s" % GRL_2015)
        exit(1)

    ifile_2015=open(GRL_2015)
    ifile_2016=open(GRL_2016)

    l_run_2015 = ifile_2015.read().splitlines()
    l_run_2016 = ifile_2016.read().splitlines()

    s_run = set(l_run_2015 + l_run_2016)

    ifile_2015.close()
    ifile_2016.close()

    return s_run
#*********************************************************
if len(sys.argv) < 3:
    print("Usage:")
    print("   get_datasets.py inputfile input/output")
    exit(1)

IFILENAME=sys.argv[1]
TYPE=sys.argv[2]
#*********************************************************
s_runs = GetGRLRuns()

ifile=open(IFILENAME)
l_line = ifile.read().splitlines()

l_input=list()
l_output=list()

for line in l_line:
    capt = re.findall("Input:.*:(.*),\sOutput:(.*),\sTaskID:.*", line)
    in_ds = capt[0][0]
    ot_ds = capt[0][1]

    l_run_number = re.findall("data[0-9]{2}_13TeV.([0-9]{8}).physics.*", in_ds)
    if len(l_run_number) != 1:
        print("Cannot retrieve run number from %s" % in_ds)
        exit(1)

    run_number = l_run_number[0]
    if run_number not in s_runs:
        continue

    l_input.append( capt[0][0] )
    l_output.append( capt[0][1] )
#*********************************************************
if not os.path.isdir("datasets"):
    os.mkdir("datasets")

basename=os.path.basename(IFILENAME)
l_name = re.findall("(.*)\.txt", basename)

main_ofile=open("datasets/main_%s_%s.txt" % (l_name[0], TYPE), "w")
delayed_ofile=open("datasets/delayed_%s_%s.txt" % (l_name[0], TYPE), "w")
#*********************************************************
if TYPE == "input":
    for inpt in l_input:
        if "Main" in inpt:
            main_ofile.write("%s\n" % inpt)
        elif "Delayed" in inpt:
            delayed_ofile.write("%s\n" % inpt)
elif TYPE == "output":
    for outpt in l_output:
        if "Main" in outpt:
            main_ofile.write("%s\n" % outpt)
        elif "Delayed" in outpt:
            delayed_ofile.write("%s\n" % outpt)
#*********************************************************
main_ofile.close()
delayed_ofile.close()
