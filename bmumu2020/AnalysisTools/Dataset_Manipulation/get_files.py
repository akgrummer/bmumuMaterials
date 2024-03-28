import os
import sys

#-------------------------------------------------
if len(sys.argv) < 2:
    print("Need to introduce an argument.")
    exit(1)

JOB_STATUS=sys.argv[1]
#-------------------------------------------------
if not os.path.isfile("jobs.txt"):
    print("Cannot find job.txt")
    exit(1)

ifile=open("jobs.txt")
l_line=ifile.read().splitlines()
ifile.close()
#-------------------------------------------------
l_job=list()
for line in l_line:
    if "======================================" in line:
        l_job.append(dict())
        continue
    elif ">>>" in line:
        continue

    l_part=line.split(":")
    if line == "":
        continue

    if len(l_part) < 2:
        print("Line %s cannot be split into 2." % line)
        continue
    
    l_part[0]=l_part[0].replace(" ", "")
    l_part[1]=l_part[1].replace(" ", "")

    l_job[-1][l_part[0]]=l_part[1]
#-------------------------------------------------
njobs=0

l_dataset_dw=list()
l_dataset_tr=list()
for job in l_job:
    if job["taskStatus"] != JOB_STATUS:
        continue

    njobs+=1

    print("%s    %s" % (job["JobsetID"], job["taskStatus"]) )
    l_dataset=job["outDS"].split(",")
    for dataset in l_dataset:
        if ".root" in dataset and dataset not in l_dataset_dw:
            l_dataset_dw.append(dataset)

        if dataset != "" and dataset not in l_dataset_tr:
            l_dataset_tr.append(dataset)

    l_dataset_dw.append("\n")
    l_dataset_tr.append("\n")

print("Jobs done: %d" % njobs)
#-------------------------------------------------
ofile_dw=open("datasets_dw.txt", "w")
for dataset in l_dataset_dw:
    ofile_dw.write("%s\n" % dataset)
ofile_dw.close()

ofile_tr=open("datasets_tr.txt", "w")
for dataset in l_dataset_tr:
    ofile_tr.write("%s\n" % dataset)
ofile_tr.close()
#-------------------------------------------------
