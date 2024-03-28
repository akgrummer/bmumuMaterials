import glob
import os
import shutil

TARGET="/nfs/monet_3/home/campoverde/Test/failed_jobs/"

l_FILE=glob.glob("data*/*.err")
for ERR_SOURCE in l_FILE:
    is_empty=os.stat(ERR_SOURCE).st_size == 0
    if is_empty:
        continue

    LOG_SOURCE=ERR_SOURCE.replace(".err", ".out")

    ERR_TARGET=TARGET+os.path.basename(ERR_SOURCE)
    LOG_TARGET=TARGET+os.path.basename(LOG_SOURCE)

    shutil.copyfile(ERR_SOURCE, ERR_TARGET)
    shutil.copyfile(LOG_SOURCE, LOG_TARGET)

