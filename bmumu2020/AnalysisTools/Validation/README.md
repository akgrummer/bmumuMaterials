#### Description

The scripts in this directory are in charge of producing validation plots from flat ntuples.

#### Usage

You just have to:

`python steer.py MC_SPECIFIER PROCESS`

where `MC_SPECIFIER=bsmumu/bplus/bsjpsiphi`, and you will get a root file with all the histograms you need. 
The un-merged files will end up in the `Ouput_PROCESS/` directory.

If you want to tweak things (number of jobs, etc) look into `steer_validation.py`

If any job fails, you just have to run:

`source resent_failed_jobs.sh`

to make sure that all the jobs get resent. You will have to merge the outputs by hand afterwards.

