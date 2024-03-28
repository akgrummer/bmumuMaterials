#### Introduction ####

These scripts are in charge of:

1. Sending the jobs to get the PRW files used for pile-up reweighting.

2. Running the code, locally, that produces lumifiles for a given trigger.

The code is pretty simple and you can just open the files, read it, and modify
it to:

1. Get PRW files for different MC.
2. Update GRLs.
3. Update the luminosity tag, which corresponds to a given GRL. 
   See [this](https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/GoodRunListsForAnalysisRun2)

   It is **VERY IMPORTANT** that the Lumi tag corresponds to the one GRL you will use.
   Different lumitags, actually will give you different results.

4. Try different triggers.

#### Usage ####

In order to produce the lumifiles just do:    

`source make_lumi_files.sh`

If you want to produce PRW files do:

`source grid_make_prw.sh`

After the jobs producing the PRW files finish, you can retrieve them by doing:

`source get_prw.sh`

This will read the names of the datasets from `prw_datasets.txt` (which you must make).
It will merge, rename and copy the resulting files to `PRW/`. The script reads the dataset ID
(DSID) from the name of the container and uses it to assign the name to the merged file.
You can change the names or add more samples by editting the script.

#### NTUP_PRW FILES ####

From 2017 the PRW files can be also produced while the derivation jobs run. If you asked the person in
charge of the derivation to make sure that the NTUP_PRW files be also produced (and you should) you can
just download them and rename them so that the ntuple making software picks them up. The script
`get_ntup_prw.sh` downloads all the files, merges the the ROOT files
corresponding to a given dataset and renames them in any way you want based on the DSID.

You can do all this yourself by hand, write your own script or read this script, understand it, modify
it and use it to do the job, it's up to you.
#### WARNING ####
**DO NOT** run `grid_make_prw.sh` if you have the directories produced by
`make_lumi_files.sh` still  in the directory. If you do, the jobs will pick
up this code and use it to run. As a result the jobs will fail.    

If you happen to have done that and you are reading this, then you will need
to remove those directories and resubmit the jobs. If your jobs are broken
you will have to resubmit with a different output DS name or add

`--allowTaskDuplication --useNewCode`

(read more by looking into `pathena --help`) to the pathena line.

