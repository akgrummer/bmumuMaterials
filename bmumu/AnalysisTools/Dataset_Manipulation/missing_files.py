import glob
import os

#---------------------------------------------
#---------------------------------------------
def CountFiles(DIRECTORY):
    if not os.path.isdir(DIRECTORY):
        return -1

    l_FILE=os.listdir(DIRECTORY)

    return len(l_FILE)
#---------------------------------------------
#---------------------------------------------
norg_tot=0
nslm_tot=0
for ORG_DIR in glob.glob("*300*BPHY8_NTUP*"):
    SLM_DIR=ORG_DIR.replace("NTUP", "FNTUP")

    norg=CountFiles(ORG_DIR)
    nslm=CountFiles(SLM_DIR)

    norg_tot+=norg
    nslm_tot+=nslm if nslm >= 0 else 0

    if norg != nslm:
        print("{0:110}{1:4}{2:4}".format(ORG_DIR, norg, nslm) )

print("{0:110}{1:4}{2:4}".format("", norg_tot, nslm_tot) )
print("Missing %d files:" % (norg_tot - nslm_tot) )

