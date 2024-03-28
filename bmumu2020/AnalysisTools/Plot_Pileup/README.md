#### Introduction ####

This set of scripts are in charge of sending jobs to the Siegen cluster to
evaluate the pileup shape in data and MC and compare them. To use the scripts you 
have to:

#### Usage ####

1. You send the jobs by:
   
   `python steer.py PROCESS`

   where _PROCESS=bsmumu/bplus/bsjpsiphi_. This is going to send a given number of jobs
   that will _run pileup.py_. The result will be placed in _output_PROCESS_ and will be
   a ROOT file with a bunch of histograms for both data and MC.

2. If you want to get the plots you need to:

   `python plotter.py output_PROCESS/the_file.root`

   this will produce a bunch of PDFs and place them in _plots/_.


#### Brief Description ####

###### **steer.py** ####
This script starts the processing. You can specify the input files paths here.

###### **split.job** ####
Here are the SBATCH lines. You can specify which machines will run your jobs, time
limits, memory requirements...

###### **read_json.py** ####
The jobs are going to run over the original (not the skimmed) ntuples. So the pileup
values and the pass_grl flag are wrong and have to be picked up from json files in
_json/_. This script is in charge of reading those files.

###### **plotter.py** ####
This just makes plots from the histograms in a root file. The file is the output of the
job, located in _output_PROCESS_. You run the script by doing:

`python plotter.py output_PROCESS/the_file_inside.root`

###### **plotter.py** ####
This is the file that makes the histograms. Each worker node runs this script and picks up
the ROOT file made as a result.

###### **clean.sh** ####
Before sending the jobs again, this script cleans up the output of the last job. This is called
inside steer.py, so you do not have to do anything.


