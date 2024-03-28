import sys
import glob
import os
import subprocess

import utils

#---------------------------------------
#Get arguments used to send job when
#calling split.job
#---------------------------------------
def GetArguments(logfile):
    l_argument=list()

    ifile=open(logfile)
    l_line=ifile.read().splitlines()
    ifile.close()

    iline=0
    for iline, line in enumerate(l_line):
        if "INFO::ARGUMENTS USED:" in line:
            break

    arguments=l_line[iline + 1]
    l_argument=arguments.split(" ")

    if " " in l_argument:
        l_argument.remove(" ")

    if ""  in l_argument:
        l_argument.remove("")

    return l_argument
#---------------------------------------
#Returns list of input files in a logfile
#---------------------------------------
def GetInputFiles(logfile):
    l_input=list()

    ifile=open(logfile)
    l_line=ifile.read().splitlines()
    ifile.close()

    iline=0
    for iline, line in enumerate(l_line):
        if "Working with:" in line:
            break

    while ".root" in l_line[iline+1]:
        l_input.append(l_line[iline+1])
        iline+=1

    return l_input
#---------------------------------------
#Check if file is empty
#---------------------------------------
def isEmpty(filename):
    ifile=open(filename)
    l_LINE=ifile.read().splitlines()
    ifile.close()

    return len(l_LINE) == 0
#---------------------------------------
#Get logfiles for failed jobs 
#---------------------------------------
PREFIX=sys.argv[1]
l_jobid=list()
l_LOG=list()
l_ERR=list()

l_FILE=glob.glob("%s*/*.err" % PREFIX)
for FILE in l_FILE:
    if not isEmpty(FILE):
       logfile=FILE.replace(".err", ".out")
       FILENAME=os.path.basename(FILE)
       jobid=FILENAME.replace(".err", "")

       l_jobid.append(jobid)
       l_LOG.append(logfile)
       l_ERR.append(FILE)
#---------------------------------------
#For each log file of a failed job, get
#job arguments and resend it.
#---------------------------------------
for ERR, LOG, JOBID in zip(l_ERR, l_LOG, l_jobid):
    l_argument=GetArguments(LOG)

    narguments=len(l_argument)
    if narguments != 4:
        print("Found %d arguments." % narguments)
        print(l_argument)
        exit(1)

    OUTPUT_DIR=l_argument[0]
    i_job     =l_argument[1]
    EXECUTABLE=l_argument[2]
    JOB_NAME  =l_argument[3]

    LOG_DIR="-o%s/%%j.out" % JOB_NAME
    ERR_DIR="-e%s/%%j.err" % JOB_NAME
    SJ_NAME="-J %s" % JOB_NAME

    OLD_OUTPUT="%s/output_%s.root" % (OUTPUT_DIR, JOBID)

    JSONFILENAME="json_args/jobs_%s.json" % (JOB_NAME)
    if not os.path.isfile(JSONFILENAME):
        print("File %s not found" % JSONFILENAME)
        exit(1)

    d_jobs=utils.json_to_dict(JSONFILENAME)
    l_INPUTFILES=d_jobs[i_job]

    if os.path.isfile(LOG) and os.path.isfile(ERR):
        print("")
        print("Arguments %s" % l_argument)
        print("Input files %s." % l_INPUTFILES)
        print("Removing %s" % LOG)
        print("Removing %s" % ERR)

        if os.path.isfile(OLD_OUTPUT):
            os.remove(OLD_OUTPUT)
            print("Removing %s" % OLD_OUTPUT)

        os.remove(LOG)
        os.remove(ERR)
    else:
        print("Missing of the files:")
        print("  %s" % LOG)
        print("  %s" % ERR)
        exit(1)

    l_call=["sbatch", SJ_NAME, LOG_DIR, ERR_DIR,"split.job", OUTPUT_DIR, i_job, EXECUTABLE, JOB_NAME ] 
    subprocess.call(l_call)
#---------------------------------------
#---------------------------------------

