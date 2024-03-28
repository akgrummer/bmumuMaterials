import glob

#********************************************
def get_set(FILE):
    ifile=open(FILE)
    l_dataset=ifile.read().splitlines()
    s_dataset=set(l_dataset)
    ifile.close()

    return s_dataset
#********************************************
l_files=list()
for FILE in glob.glob("datasets/split*"):
    l_files.append( get_set(FILE) )
#********************************************
nfiles=len(l_files)

for i_file in range(0, nfiles):
    for j_file in range(0, nfiles):
        s_int = l_files[i_file].intersection(l_files[j_file])
        ninter = len(s_int)
        if ninter != 0:
            print("Non null interesection of %d at (i, j)=(%d,%d)" % (ninter, i_file, j_file) )
#********************************************

