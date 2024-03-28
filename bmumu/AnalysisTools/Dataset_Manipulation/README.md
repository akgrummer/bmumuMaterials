###Description

These scripts are used to check the status of jobs and make lists
with the datasets available for download. The scripts do:

#####show_jobs.sh: 
Dumps to the screen a list of all the jobs
between a given task ID and 100000 (in practice, all above that
task ID).

To run this you need to setup panda and have a proxy. You run it
with:

source show_jobs.sh JOBID > jobs.txt

#####get_files.py
Produces two textfiles with the list of datasets
available to transfer and download.

#####move_datasets.sh
This script assumes that you have a set of MC samples
in the current directory. It will move them to a path
that you specify according to the variables at the
beggining of the file.

The DSIDs might need to be changed in the future. Also
other samples might need to be included.
