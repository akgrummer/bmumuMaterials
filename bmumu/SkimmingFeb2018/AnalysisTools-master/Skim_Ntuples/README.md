#### Introduction
The code in this directory is used to skim the ntuples used in the Bsmumu analysis. The first step is to setup the packages on which the code depends. This is done by:
```bash
source setup.sh
```
The big pictures is this:
1. The data comes in directories with the following structure:
`DATASETNAME_Process`
where the dataset name could be strings like:
`data15_13TeV.periodD.physics_Main`
and the process is one of:
`["Bmumu", "BpJpsiKp", "BsJpsiPhi", "BJpsiK", "BJpsiPi", "Bhh", "Bhmunu"]`
2. The skimming is run for one of these directories at a time. Ideally, one job should be sent for each of the ROOT files in the directory. The data needed by each of the jobs to run the skimming is saved in JSON files. These files are read by the process that does the skimming.
3. If any problem occurs when running the jobs, there are scripts that can be used to resend the job and this should be done once and again until there are no missing output files.

A detailed step-by-step description is below.
#### Setting up jobs
The jobs are sent by running:

```bash
python steer_skim.py $DATASETNAME $PROCESS
```
Given that you are likely to have about 15 datasets for MC and one dataset for each data taking period, you will need to run the line above tens of times. Therefore you should put those lines in a script to make the process less painful.
The script needs to know a few things:
1. `Executable name` This is the script that does the actual skimming, given that what you call is a steering script. In `steer_skim.py` this is set in the lines:
```python
d_arg["EXECUTABLE"] = "skim_trees.py"
d_arg["OUTPUTFILE"] = "output_%s_%s.root" % (d_arg["DSID"], d_arg["PROCESS"])
d_arg["TREENAME"]   = "T_mv"
d_arg["NFILES"]     = "1" 
```
In the same section of code, the `OUTPUTFILE` defines the name of the skimmed files. `T_mv` is the name of the candidate trees. All these lines probably will always stay like that. `NFILES` is the number of files that are processes in each job. You should keep it as "1", so that you can check if any job failed, because the number of inputs and outputs is different.

2. In case new samples be produced, the `l_dsid` variable has to be updated. This variable stores the names of the datasets in case of the data, and the DSID, in case of the MC. This variable just identifies the directory.
3. As you can see in the lines:
```python
if args_steer[1] == "test":
d_arg["TEST"]   = "1"
d_arg["NEVENTS"]= args_steer[2]
d_arg["DSID"]   = args_steer[3]
d_arg["PROCESS"]= args_steer[4] 
```
You can call the script as:

```bash
python steer_skim.py test $NEVENTS $DSID $PROCESS
```
i.e. the same as before but specifying that this is a test, and you are testing for `$NEVENTS`. You do this so that the code gets run for a single file and locally, not in the cluster. You should do this before sending the jobs, to check that the code won't fail.

To skim ntuples on the GRID do e.g.:
```bash
lsetup "root 6.12.06-x86_64-slc6-gcc62-opt" panda
prun --loadJson submit_grid_cfg.json --dumpJson some_json_out_file.json
```
an example configuration json file submit_grid_cfg_example.json is provided; the output json file is just the dump of the CL options.
