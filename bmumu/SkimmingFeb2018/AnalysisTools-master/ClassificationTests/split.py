import glob
import os

#--------------------------------------------
#Returns size of list of files passed as
#argument
#--------------------------------------------
def GetSize(l_file):
    TOTAL_SIZE=0
    for FILE in l_file:
        TOTAL_SIZE+=os.path.getsize(FILE)

    return TOTAL_SIZE
#--------------------------------------------
#Fill size-file dictionary
#--------------------------------------------
def GetDictionary(l_FILE):
    d_size_file=dict()
    global TOTAL_SIZE
    TOTAL_SIZE=0

    for FILE in l_FILE:
        FILENAME=os.path.basename(FILE)
        FILESIZE=os.path.getsize(FILE)
        TOTAL_SIZE+=FILESIZE
        d_size_file[FILESIZE] = FILE

    return d_size_file
#--------------------------------------------
#Split files in roughly equally sized chunks
#--------------------------------------------
def MakeGroups(l_FILE, NGROUPS):
    d_size_file=GetDictionary(l_FILE)

    UNIT_SIZE=TOTAL_SIZE/NGROUPS
    print("Total size:%d" % TOTAL_SIZE)
    print("Unit size:%d" % UNIT_SIZE)

    d_igroup_lfile=dict()
    IGROUP=0
    CUMUL_SIZE=0
    for SIZE in d_size_file:
        FILE=d_size_file[SIZE]
    
        if CUMUL_SIZE >= UNIT_SIZE:
            IGROUP+=1
            CUMUL_SIZE=0
    
        if IGROUP not in d_igroup_lfile:
            d_igroup_lfile[IGROUP]=[FILE]
        else:
            d_igroup_lfile[IGROUP].append(FILE)
            
        CUMUL_SIZE+=SIZE

    for igroup in d_igroup_lfile:
        l_file=d_igroup_lfile[igroup]
        GROUP_SIZE=GetSize(l_file)
        print("Group:%d     Size:%d" % (igroup, GROUP_SIZE) )

    return d_igroup_lfile
#--------------------------------------------
#Print size of each chunk
#--------------------------------------------
def PrintGroups(l_FILE, NGROUPS):
    d_igroup_lfile=MakeGroups(l_FILE, NGROUPS)

    for igroup in d_igroup_lfile:
        l_file=d_igroup_lfile[igroup]
        size=GetSize(l_file)

        print("Group:%d  Size:%d" % (igroup, size))
#--------------------------------------------
#Initialize variables
#--------------------------------------------
TOTAL_SIZE=0
#--------------------------------------------
#--------------------------------------------

