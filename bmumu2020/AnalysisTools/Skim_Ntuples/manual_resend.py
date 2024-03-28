import subprocess

import os
#---------------------------------------
#---------------------------------------
def Resend(l_argument):
    OUTPUT_DIR=l_argument[0]
    i_job     =l_argument[1]
    EXECUTABLE=l_argument[2]
    JOB_NAME  =l_argument[3]

    LOG_DIR="-o%s/%%j.out" % JOB_NAME
    ERR_DIR="-e%s/%%j.err" % JOB_NAME
    SJ_NAME="-J %s" % JOB_NAME

    JSONFILENAME="json_args/jobs_%s.json" % (JOB_NAME)
    if not os.path.isfile(JSONFILENAME):
        print("File %s not found" % JSONFILENAME)
        exit(1)

    l_call=["sbatch", SJ_NAME, LOG_DIR, ERR_DIR,"split.job", OUTPUT_DIR, i_job, EXECUTABLE, JOB_NAME ] 
    subprocess.call(l_call)
#---------------------------------------
#---------------------------------------
Resend(['/nfs/moroni_7/data/atlasb7/grid/data16/FNTUP/v2/user.acampove.data16K.physics_Main.BPHY8_FNTUP.grp16_v01_p3372_BJpsiK.root', '4', 'skim_trees.py', 'data16K_BJpsiK_skimming'])
Resend(['/nfs/moroni_7/data/atlasb7/grid/data16/FNTUP/v2/user.acampove.data16I.physics_Main.BPHY8_FNTUP.grp16_v01_p3372_Bmumu.root', '34', 'skim_trees.py', 'data16I_Bmumu_skimming'])
Resend(['/nfs/moroni_7/data/atlasb7/grid/data16/FNTUP/v2/user.acampove.data16I.physics_Main.BPHY8_FNTUP.grp16_v01_p3372_BJpsiK.root', '0', 'skim_trees.py', 'data16I_BJpsiK_skimming'])
Resend(['/nfs/moroni_7/data/atlasb7/grid/data16/FNTUP/v2/user.acampove.data16I.physics_Main.BPHY8_FNTUP.grp16_v01_p3372_BJpsiK.root', '3', 'skim_trees.py', 'data16I_BJpsiK_skimming'])
Resend(['/nfs/moroni_7/data/atlasb7/grid/data16/FNTUP/v2/user.acampove.data16I.physics_Main.BPHY8_FNTUP.grp16_v01_p3372_BJpsiK.root', '4', 'skim_trees.py', 'data16I_BJpsiK_skimming'])
Resend(['/nfs/moroni_7/data/atlasb7/grid/data16/FNTUP/v2/user.acampove.data16I.physics_Main.BPHY8_FNTUP.grp16_v01_p3372_BsJpsiPhi.root', '24', 'skim_trees.py', 'data16I_BsJpsiPhi_skimming'])
Resend(['/nfs/moroni_7/data/atlasb7/grid/data16/FNTUP/v2/user.acampove.data16I.physics_Main.BPHY8_FNTUP.grp16_v01_p3372_BsJpsiPhi.root', '25', 'skim_trees.py', 'data16I_BsJpsiPhi_skimming'])
Resend(['/nfs/moroni_7/data/atlasb7/grid/data16/FNTUP/v2/user.acampove.data16K.physics_Main.BPHY8_FNTUP.grp16_v01_p3372_BsJpsiPhi.root', '11', 'skim_trees.py', 'data16K_BsJpsiPhi_skimming'])
Resend(['/nfs/moroni_7/data/atlasb7/grid/data16/FNTUP/v2/user.acampove.data16K.physics_Main.BPHY8_FNTUP.grp16_v01_p3372_BsJpsiPhi.root', '12', 'skim_trees.py', 'data16K_BsJpsiPhi_skimming'])
#---------------------------------------
#---------------------------------------

