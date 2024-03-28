import os
import sys
import glob
import collections

#---------------------------------------------
#Get [process, nevents]
#---------------------------------------------
def GetInfo(FILE):
    NAME=os.path.basename(FILE).replace(".pdf", "")
    l_NAME=NAME.split("__")

    return [l_NAME[1], l_NAME[2]]
#---------------------------------------------
#Make slide for given pair of plots.
#---------------------------------------------
def MakeSlide(PFILES, iPFILES):
    narrow=PFILES[0]
    wide  =PFILES[1]

    l_wide_info  = GetInfo(wide)
    l_narrow_info= GetInfo(narrow)

    wide_proc  =l_wide_info[1].replace("_", "")
    narrow_proc=l_narrow_info[1].replace("_", "")

    nevents = int(l_wide_info[0])

    if wide_proc != narrow_proc:
        print("Processes differ %s vs %s" % (wide_proc, narrow_proc) )
        exit(1)

    slide=open("%s/%s_slide_%d.tex" % (SLIDE_DIR, PROCESS, iPFILES), "w")
    slide.write("\\begin{frame}{%s}\n" % wide_proc)
    slide.write("\\footnotesize \n")
    slide.write("\\begin{figure}\n")
    slide.write("\centering\n")
    slide.write("\\begin{subfigure}[b]{0.48\\textwidth}\n")
    slide.write("\includegraphics[width=\\textwidth]{%s}\n" % wide)
    slide.write("\end{subfigure}\n")
    slide.write("\\begin{subfigure}[b]{0.48\\textwidth}\n")
    slide.write("\includegraphics[width=\\textwidth]{%s}\n" % narrow)
    slide.write("\end{subfigure}\n")
    slide.write("\end{figure}\n")
    slide.write("\end{frame}\n")
    slide.close()
#---------------------------------------------
#Returns files in a list of ntuples: 
#(wide, narrow)
#---------------------------------------------
def GetPairs(l_FILES):
    l_narrow_file=[]
    l_wide_file=[]

    for FILE in l_FILES:
        if "narrow" in FILE:
            l_narrow_file.append(FILE)

        if "wide" in FILE:
            l_wide_file.append(FILE)

    l_narrow_file.sort()
    l_wide_file.sort()

    size_l_narrow_file=len(l_narrow_file)
    size_l_wide_file  =len(l_wide_file)
    if size_l_narrow_file != size_l_wide_file:
        print("Lists have different sizes %d vs %d" % (size_l_narrow_file, size_l_wide_file) )
        return []

    l_pairs=[]
    for wide_file, narrow_file in zip(l_narrow_file, l_wide_file):
        l_pairs.append( (wide_file, narrow_file) )

    return l_pairs
#---------------------------------------------
#Initialize variables
#---------------------------------------------
PROC_DIR=""
PROCESS=sys.argv[1]
SLIDE_DIR="Slides"

if PROCESS == "bsmumu":
    PROC_DIR="Plots/bsmumu_components/"
elif PROCESS == "bplus":
    PROC_DIR="Plots/bplus_components/"
elif PROCESS == "bsjpsiphi":
    PROC_DIR="Plots/bsjpsiphi_components/"
else:
    print("Wrong process %s." % PROCESS)
    exit(1)

if not os.path.isdir(SLIDE_DIR):
    os.mkdir(SLIDE_DIR)

for SLIDE in glob.glob("%s/%s_slide_*.tex" % (SLIDE_DIR, PROCESS)):
    os.remove(SLIDE)
#---------------------------------------------
#Preliminary checks
#---------------------------------------------
if not os.path.isdir(PROC_DIR):
    print("Cannot find %s." % PROC_DIR)
    exit(1)
#---------------------------------------------
#Create structures
#---------------------------------------------
d_nentries_files=dict()
#---------------------------------------------
#Filling structures
#---------------------------------------------
for FILE in glob.glob("%s/*.pdf" % PROC_DIR):
    NAME=os.path.basename(FILE).replace(".pdf", "")
    l_NAME=NAME.split("__")
    NENTRIES=int(l_NAME[1])

    if NENTRIES not in d_nentries_files:
        d_nentries_files[NENTRIES]=[FILE]
    else:
        d_nentries_files[NENTRIES].append(FILE)
#---------------------------------------------
#Sort dictionary
#---------------------------------------------
od_nentries_files=collections.OrderedDict( sorted(d_nentries_files.items(), reverse=True) )

l_PFILES=list()
for nentries in od_nentries_files:
    l_FILES=od_nentries_files[nentries]
    l_PFILES += GetPairs(l_FILES)
#---------------------------------------------
#Make slides
#---------------------------------------------
for i_PFILES, PFILES in enumerate(l_PFILES):
    MakeSlide(PFILES, i_PFILES)
#---------------------------------------------
#---------------------------------------------
