import ROOT

#-------------------------------------
#Get number of events and candidates
#in ntuples produced from DxAODs
#-------------------------------------
def NtupleStatistics(FILES_PATH):
    print("File: %s" % FILES_PATH)
    chain_candidates=ROOT.TChain("T_mv")
    chain_candidates.Add("%s/*.root" % FILES_PATH)
    
    chain_events=ROOT.TChain("EventInfo")
    chain_events.Add("%s/*.root" % FILES_PATH)
    nevents=chain_events.Draw("ev_processed", "ev_processed == 1")
    ncandidates=chain_candidates.GetEntries()
    
    print("Candidates: %d" % ncandidates )
    print("Events: %d" % nevents )

    return ("%.1E" % ncandidates, "%.1E" % nevents)
#-------------------------------------
#Print information about how many
#candidates were matched and not matched
#-------------------------------------
def TreeStatistics(FILES_PATH):
    print("File: %s" % FILES_PATH)
    chain_tree=ROOT.TChain("decays")
    chain_tree.Add("%s/output_*.root" % FILES_PATH)

    ncombinatorial=chain_tree.Draw("Bmass", "decay==\"comb\"")
    nunmatched    =chain_tree.Draw("Bmass", "decay==\"unmatched\"")
    ndecay        =chain_tree.Draw("Bmass", "decay!=\"unmatched\" && decay!=\"comb\"")
    ntotal        = ncombinatorial + nunmatched + ndecay

    print("Combinatorial candidates: %d" % ncombinatorial)
    print("Unmatched candidates: %d" % nunmatched)
    print("Decay associated candidates: %d" % ndecay)
    print("Total candidates: %d" % ntotal)

    return ("%.1E" % ncombinatorial, "%.1E" % nunmatched, "%.1E" % ndecay)
#-------------------------------------
#CHANGE THIS WHEN USING NEW SAMPLES
#-------------------------------------
xAOD_MEVENTS="%.1E" %  50000000
DxAOD_MEVENTS="%.1E" % 14000000
#-------------------------------------
#Print DxAOD statistics
#-------------------------------------
ROOT.gROOT.SetBatch()
TABLE_DIR="Tables"
#-------------------------------------------
#For bbJpsiX Rel20
#-------------------------------------------
#NTUP_DIR="/nfs/monet_3/home/campoverde/Data/user.acampove.undefined_TruthDecay_002.300203.e4889_a766_a845_r8423_p3254/"
#NT_BSMUMU_DIR="user.acampove.undefined_TruthDecay_002.300203.e4889_a766_a845_r8423_p3254_Bmumu.root"
#NT_BPLUS_DIR="user.acampove.undefined_TruthDecay_002.300203.e4889_a766_a845_r8423_p3254_BpJpsiKp.root"
#NT_BSJPSIPHI_DIR="user.acampove.undefined_TruthDecay_002.300203.e4889_a766_a845_r8423_p3254_BsJpsiPhi.root"

#TREE_DIR="/data/atlasb7/grid/data15a16/NTUP/Classification/"
#TR_BSMUMU_DIR="user.acampove.undefined_TruthDecay_002.300203.e4889_a766_a845_r8423_p3254_Bmumu.root"
#TR_BPLUS_DIR="user.acampove.undefined_TruthDecay_002.300203.e4889_a766_a845_r8423_p3254_BpJpsiKp.root"
#TR_BSJPSIPHI_DIR="user.acampove.undefined_TruthDecay_002.300203.e4889_a766_a845_r8423_p3254_BsJpsiPhi.root"
#-------------------------------------------
#For bbmumuX Rel21
#-------------------------------------------
NTUP_DIR="/nfs/moroni_7/data/atlasb7/grid/BpJpsiKplus/xAOD15_ac/"
NT_BSMUMU_DIR="user.acampove.undefined_TruthClasiffication_001.300306.e4911_e5984_a875_r9364_r9315_p3371_Bmumu.root"
NT_BPLUS_DIR="user.acampove.undefined_TruthClasiffication_001.300306.e4911_e5984_a875_r9364_r9315_p3371_BpJpsiKp.root"
NT_BSJPSIPHI_DIR="user.acampove.undefined_TruthClasiffication_001.300306.e4911_e5984_a875_r9364_r9315_p3371_BsJpsiPhi.root"

TREE_DIR="/data/atlasb7/grid/data15a16/NTUP/Classification/"
TR_BSMUMU_DIR="user.acampove.undefined_TruthClasiffication_001.300306.e4911_e5984_a875_r9364_r9315_p3371_Bmumu.root"
TR_BPLUS_DIR="user.acampove.undefined_TruthClasiffication_001.300306.e4911_e5984_a875_r9364_r9315_p3371_BpJpsiKp.root"
TR_BSJPSIPHI_DIR="user.acampove.undefined_TruthClasiffication_001.300306.e4911_e5984_a875_r9364_r9315_p3371_BsJpsiPhi.root"
#-------------------------------------------
#-------------------------------------------
print("-------------------------------------------")
print("Ntuple Cutflow")
print("-------------------------------------------")
(NTP_CND_B1, NTP_EVT_B1) = NtupleStatistics( "%s/%s" % (NTUP_DIR, NT_BSMUMU_DIR) )
print("-------------------------------------------")
(NTP_CND_B2, NTP_EVT_B2) = NtupleStatistics( "%s/%s" % (NTUP_DIR, NT_BPLUS_DIR) )
print("-------------------------------------------")
(NTP_CND_B3, NTP_EVT_B3) = NtupleStatistics( "%s/%s" % (NTUP_DIR, NT_BSJPSIPHI_DIR) )
print("-------------------------------------------")
print("Tree Cutflow")
print("-------------------------------------------")
(TR_CMB_B1, TR_UNM_B1, TR_DEC_B1) = TreeStatistics( "%s/%s" % (TREE_DIR, TR_BSMUMU_DIR) )
print("-------------------------------------------")
(TR_CMB_B2, TR_UNM_B2, TR_DEC_B2) = TreeStatistics( "%s/%s" % (TREE_DIR, TR_BPLUS_DIR) )
print("-------------------------------------------")
(TR_CMB_B3, TR_UNM_B3, TR_DEC_B3) = TreeStatistics( "%s/%s" % (TREE_DIR, TR_BSJPSIPHI_DIR) )
#-------------------------------------
#Dump into textfile cutflow diagram.
#-------------------------------------
ofile=open("%s/cutflow.tex" % TABLE_DIR, "w")

ofile.write("\\begin{frame}{Candidate Classification Yields}\n")
ofile.write("\\footnotesize\n")
ofile.write("\n")
ofile.write("\\begin{center}\n")
ofile.write("    \\begin{tikzpicture}[node distance=2cm]\n")
ofile.write("        \\node (xAOD)  [Round-rectangle-blue, xshift=-3cm] {xAOD\\\\ %s};\n" % xAOD_MEVENTS)
ofile.write("\n")
ofile.write("        \\node (DxAOD) [Round-rectangle-blue, yshift=0.5cm, below of=xAOD] {DxAOD\\\\ %s};\n" % DxAOD_MEVENTS)
ofile.write("        \\draw [arrow, draw=black] (xAOD) --node[] {} (DxAOD);\n")
ofile.write("\n")
ofile.write("        \\node (NTP_B2) [Round-rectangle-blue, xshift=-4cm, yshift=-0.5cm, below of=DxAOD] {%s Candidates\\\\%s Events};\n" % (NTP_CND_B2, NTP_EVT_B2) )
ofile.write("        \\node (TREE_B2) [Round-rectangle-blue, yshift=0cm, below of=NTP_B2] {%s Combinatorial\\\\%s Unmatched\\\\%s Decays};\n" % (TR_CMB_B2, TR_UNM_B2, TR_DEC_B2) )
ofile.write("        \\draw [arrow, draw=black] (NTP_B2) --node[text centered, sloped, above] {cuts} (TREE_B2);\n")
ofile.write("\n")
ofile.write("        \\node (NTP_B1) [Round-rectangle-blue, xshift=0cm, yshift=-0.5cm, below of=DxAOD] {%s Candidates\\\\%s Events};\n" % (NTP_CND_B1, NTP_EVT_B1) )
ofile.write("        \\node (TREE_B1) [Round-rectangle-blue, yshift=0cm, below of=NTP_B1] {%s Combinatorial\\\\%s Unmatched\\\\%s Decays};\n" % (TR_CMB_B1, TR_UNM_B1, TR_DEC_B1) )
ofile.write("        \\draw [arrow, draw=black] (NTP_B1) --node[text centered, sloped, above] {cuts} (TREE_B1);\n")
ofile.write("\n")
ofile.write("        \\node (NTP_B3) [Round-rectangle-blue, xshift=+4cm, yshift=-0.5cm, below of=DxAOD] {%s Candidates\\\\%s Events};\n" % (NTP_CND_B3, NTP_EVT_B3) )
ofile.write("        \\node (TREE_B3) [Round-rectangle-blue, yshift=0cm, below of=NTP_B3] {%s Combinatorial\\\\%s Unmatched\\\\%s Decays};\n" % (TR_CMB_B3, TR_UNM_B3, TR_DEC_B3) )
ofile.write("        \\draw [arrow, draw=black] (NTP_B3) --node[text centered, sloped, above] {cuts} (TREE_B3);\n")
ofile.write("\n")
ofile.write("        \\draw [arrow, draw=black] (DxAOD) --node[text centered, sloped, above] {$B_{s}\\rightarrow\mu\mu$} (NTP_B1);\n")
ofile.write("        \\draw [arrow, draw=black] (DxAOD) --node[text centered, sloped, above] {$B^{+}\\rightarrow J/\psi K^{+}$} (NTP_B2);\n")
ofile.write("        \\draw [arrow, draw=black] (DxAOD) --node[text centered, sloped, above] {$B_{s}\\rightarrow J/\psi \phi$} (NTP_B3);\n")
ofile.write("    \\end{tikzpicture}\n")
ofile.write("\\end{center}\n")
ofile.write("\n")
ofile.write("\\end{frame}\n")

ofile.close()
#-------------------------------------
#-------------------------------------

