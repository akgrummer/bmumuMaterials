import os
import glob

#---------------------------------------
l_orig_file=glob.glob("*_NTUP*/*.root")
l_skim_file=glob.glob("*_FNTUP*/*.root")

n_orig_file=len(l_orig_file)
n_skim_file=len(l_skim_file)

print("Original ntuples:%d" % n_orig_file)
print("Skimmed  ntuples:%d" % n_skim_file)
print("")
#---------------------------------------
l_orig_dir=glob.glob("*_NTUP*")

for orig_dir in l_orig_dir:
    skim_dir=orig_dir.replace("NTUP", "FNTUP")

    l_orig_file=glob.glob("%s/*.root" % orig_dir)
    l_skim_file=glob.glob("%s/*.root" % skim_dir)

    n_orig_file=len(l_orig_file)
    n_skim_file=len(l_skim_file)

    if n_orig_file != n_skim_file:
        print("For %s" % orig_dir)
        print("  Original Size:%d" % n_orig_file)
        print("  Skimmed  Size:%d" % n_skim_file)
#---------------------------------------

