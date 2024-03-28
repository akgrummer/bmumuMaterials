import ROOT

import os
import collections
#-----------------------------------------------
#Retrieves nentries-decay ordered dictionary
#-----------------------------------------------
def GetData(PROCESS):
    d_nentries_decay=dict()
    FILENAME="Root/%s_components.root" % PROCESS
    if not os.path.isfile(FILENAME):
        print("File %s not found" % FILENAME)
        exit(1) 


    ifile=ROOT.TFile(FILENAME)
    l_key=ifile.GetListOfKeys()
    for key in l_key:
        hist=key.ReadObj()
        histname=hist.GetName()
        decay=hist.GetTitle()
        nbins=hist.GetNbinsX()

        if "narrow" not in histname:
            continue

        nentries=hist.Integral(1, nbins) 
        if nentries not in d_nentries_decay:
            d_nentries_decay[nentries]=[decay]
        else:
            d_nentries_decay[nentries].append(decay)

    od_nentries_decay=collections.OrderedDict( sorted(d_nentries_decay.items(), reverse=True) )

    ifile.Close()

    return od_nentries_decay
#-----------------------------------------------
#Prints table to textfile
#-----------------------------------------------
def PrintTable(PROCESS, all_decays=False):
    od_nentries_decay=GetData(PROCESS)
    latex_process=d_proc_latex[PROCESS]
    
    TYPE=""
    if all_decays:
        TYPE="alldecays"
    else:
        TYPE="limited"

    ofile=open("%s/%s_decays_%s.tex" % ("Tables", PROCESS, TYPE), "w")
    ofile.write("\\begin{table}\n")
    ofile.write("\\centering\n")
    ofile.write("\\begin{tabular}{| l | r |}\n")
    ofile.write("\\hline\n")
    ofile.write("{0:50}&{1:>15}\\\\\n".format("Process", "Candidates"))
    ofile.write("\\hline\n")

    i_decay=0
    for nentries in od_nentries_decay:
        if (i_decay >= 15 or nentries < 10) and not all_decays:
            break

        l_decay=od_nentries_decay[nentries]
        for decay in l_decay:
            decay=decay.replace("_", "\\_")
            ofile.write("{0:<50}&{1:>15}\\\\\n".format(decay, int(nentries) ))
            i_decay+=1

    ofile.write("\\hline\n")
    ofile.write("\\end{tabular}\n")
    ofile.write("\\caption*{Associated to $%s$}\n" % latex_process)
    ofile.write("\\end{table}\n")
    ofile.close()
#-----------------------------------------------
#Fill dictionary for latex names
#-----------------------------------------------
d_proc_latex=dict()
d_proc_latex["bsmumu"]   ="B_{s}^{0}\\rightarrow\mu^{+}\mu^{-}"
d_proc_latex["bplus"]    ="B^{+}\\rightarrow J/\\psi K^{+}"
d_proc_latex["bsjpsiphi"]="B_{s}^{0}\\rightarrow J/\\psi\\phi"
#-----------------------------------------------
#Run Everything
#-----------------------------------------------
PrintTable("bsmumu")
PrintTable("bplus")
PrintTable("bsjpsiphi")

PrintTable("bsmumu", all_decays=True)
PrintTable("bplus", all_decays=True)
PrintTable("bsjpsiphi", all_decays=True)
#-----------------------------------------------
#-----------------------------------------------

