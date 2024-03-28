import os
import subprocess
import re
import glob

import ROOT

#----------------------------------------
#----------------------------------------
def GetSecond(tp):
    return tp[1]
#----------------------------------------
#----------------------------------------
def GetFNtupTable(l_tp_dataset, OUTPUT, TYPE, STREAM):
    SAMPLENAME= TYPE if TYPE == "MC" else "data"
    ID="DSID" if TYPE == "MC" else "Period"

    l_line=list()
    l_line.append("\\begin{table}[h!]")
    l_line.append("\centering")
    l_line.append("\\begin{tabular}{| r | c | l | l | l | l |}")
    l_line.append("\hline")
    l_line.append("Process & %s & Events & Candidates & $\epsilon_{evt}$ & $\epsilon_{cand}$\\\\" % ID)
    l_line.append("\hline")
    #--------
    for dataset, dsid, e_nentries, b_nentries, e_eff, b_eff in l_tp_dataset:
        process=dataset.split(".")[-2].split("_")[-1]
        l_line.append("%s & %s & %d & %d & %.3f & %.3f\\\\" % (process, dsid, e_nentries, b_nentries, e_eff, b_eff))
    #--------
    l_line.append("\hline")
    l_line.append("\end{tabular}")
    l_line.append("\caption{The table shows the statistics for each %s sample after skimming as well as the corresponding efficiencies.}" % SAMPLENAME)
    l_line.append("\label{tbl:%s_%s_fntup}" % (TYPE, STREAM))
    l_line.append("\end{table}")
    #-----------------------------
    ofile=file("%s/%s" % (LATEX_DIR, OUTPUT), "w")
    for LINE in l_line:
        ofile.write("%s\n" % LINE)
    ofile.close()
#----------------------------------------
def GetNtupTable(l_tp_dataset, OUTPUT, TYPE, STREAM):
    SAMPLENAME= TYPE if TYPE == "MC" else "data"
    ID="DSID" if TYPE == "MC" else "Period"

    l_line=list()
    l_line.append("\\begin{table}[h!]")
    l_line.append("\centering")
    l_line.append("\\begin{tabular}{| r | c | l | l |}")
    l_line.append("\hline")
    l_line.append("Process & %s & Events & Candidates\\\\" % ID)
    l_line.append("\hline")
    #--------
    for dataset, dsid, e_nentries, b_nentries in l_tp_dataset:
        process=dataset.split(".")[-2].split("_")[-1]
        l_line.append("%s & %s & %d & %d\\\\" % (process, dsid, e_nentries, b_nentries))
    #--------
    l_line.append("\hline")
    l_line.append("\end{tabular}")
    l_line.append("\caption{The table shows the statistics for each %s sample after processing the corresponding DxAOD.}" % SAMPLENAME) 
    l_line.append("\label{tbl:%s_%s_ntup}" % (TYPE, STREAM))
    l_line.append("\end{table}")
    #-----------------------------
    ofile=file("%s/%s" % (LATEX_DIR, OUTPUT), "w")
    for LINE in l_line:
        ofile.write("%s\n" % LINE)
    ofile.close()
#----------------------------------------
def GetEntries(dataset):
    print("Processing %s" % dataset)

    b_nentries=0
    e_nentries=0
    l_FILE=glob.glob("%s/*.root" % dataset)
    for FILE in l_FILE:
        ifile=ROOT.TFile.Open(FILE)
        b_tree=ifile.Get("T_mv")
        e_tree=ifile.Get("EventInfo")
        
        b_nentries+=b_tree.GetEntries()
        e_nentries+=e_tree.GetEntries()
        ifile.Close()

    return (b_nentries, e_nentries)
#----------------------------------------
def GetTables(FORMAT, TYPE, STREAM=""):
    output=subprocess.check_output(["find", DATA_DIR, "-type", "d", "-name", FORMAT])
    l_output=output.splitlines()

    if TYPE=="MC":
        l_sample=l_mc_dir
    elif "data" in TYPE:
        l_sample=l_dt_dir
    else:
        print("Wrong type %s" % TYPE)
        exit(1)
    
    global l_tp_dataset
    for output in l_output:
        for mc_dir in l_sample:
            if mc_dir in output:
                dataset=subprocess.check_output(["find", output, "-type", "d", "-name", "user.*BPHY8*.root"])
                l_dataset=dataset.splitlines()
                for dataset in l_dataset:
                    if STREAM not in dataset:
                        continue

                    if ("data" in TYPE) and (TYPE not in dataset):
                        continue

                    mtch=re.match(".*(user\.acampove\.([a-zA-Z0-9]+)\..*\.root).*", dataset)
                    if not mtch:
                        continue

                    dsname=mtch.group(1)
                    dsid=mtch.group(2)

                    b_nentries, e_nentries=GetEntries(dataset)

                    if FORMAT == "NTUP":
                        d_dsid_b_entries[dsid]=b_nentries
                        d_dsid_e_entries[dsid]=e_nentries
                        
                        l_tp_dataset.append( (dsname, dsid, e_nentries, b_nentries) )
                    else:
                        e_eff=float(e_nentries) / d_dsid_e_entries[dsid]
                        b_eff=float(b_nentries) / d_dsid_b_entries[dsid]

                        l_tp_dataset.append( (dsname, dsid, e_nentries, b_nentries, e_eff, b_eff) )

                break

    l_tp_dataset=sorted(l_tp_dataset, key=GetSecond)
    if FORMAT == "NTUP":
        GetNtupTable(l_tp_dataset, "%s_%s_stats_%s.tex" % (TYPE, STREAM, FORMAT), TYPE, STREAM)
        l_tp_dataset=list()
    else:
        GetFNtupTable(l_tp_dataset, "%s_%s_stats_%s.tex" % (TYPE, STREAM, FORMAT), TYPE, STREAM)
        l_tp_dataset=list()
#----------------------------------------
d_dsid_b_entries=dict()
d_dsid_e_entries=dict()
DATA_DIR="/data/atlasb7/grid/"
LATEX_DIR="latex"
l_tp_dataset=list()

l_mc_dir_1=["bbJpsiX", "BdPimunu", "BmJpsiKminus", "Bmumu", "BpJpsiPiPlus", "BsKmunu", "LamPmunu"]
l_mc_dir_2=["bbmumuX", "Bhh", "BmJpsiPiMinus", "BpJpsiKplus", "BsJpsiPhi", "Bsmumu"]
l_mc_dir=l_mc_dir_1+l_mc_dir_2
l_dt_dir=["data15", "data16"]
#----------------------------------------
GetTables("NTUP", "data15", "Main")
GetTables("FNTUP", "data15", "Main")

#GetTables("NTUP", "data16", "Main")
#GetTables("FNTUP", "data16", "Main")
#
#GetTables("NTUP", "data16", "Delayed")
#GetTables("FNTUP", "data16", "Delayed")
#
#GetTables("NTUP", "MC")
#GetTables("FNTUP", "MC")
#----------------------------------------

