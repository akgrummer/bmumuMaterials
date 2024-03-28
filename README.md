# Bmumu Materials

This repo contains files for bmumu analysis up to 2021. 

Two main development directories are added here: `bmumu/` and `bmumu2020/`. `bmumu/` is 'historical' - the later trainings on full run 2 data were in `bmumu2020/`.

I've added lists of the more important files for the different stages of the analysis. These lists can be found in the directory `files_for_each_topic`. This is where I would start in recovering the analysis.

## BDT training

List of files in this repo: `files_for_each_topic/BDT.txt`

The BDT was trained on the UNM computer (pcatlunm01). The command line submission script was here: `bmumu2020/BDT/MultiCoreSubmit_pc01.sh` which sent lists of hyper parameters to `bmumu2020/BDT/SubmitBDT_pc01.sh`. This script in turn submitted `runMVA_pc01.cxx` to train the BDT for all hyperparameters in `bmumu2020/BDT/MultiCoreSubmit_pc01.sh`

The output was sent to this directory `bmumu2020/BDT/BDToutput/`. It contains various scenarios that were studied. (some of the ouptut in these directories are from the diagnostic scripts run after the completion of the training.)

For the analysis we were performing a k-fold rotation of training, testing and evaluating on 3 random divisions of the datasets (based on event number I believe).

## BDT testing and evaluation

The `files_for_each_topic/BDTmacros.txt` list contains some diagnostic tools.
The `files_for_each_topic/BDTEvaluationStep.txt` has scripts for applying the training to the ntuples. There are also some ROC comparison scripts (comparing different BDT trainings) in this list.

## setup notes

some atlas environment setup notes and command line entries for running macros are in these files:
`files_for_each_topic/BDTnotesandSyncs.txt`

## other file lists:

`files_for_each_topic/AllVars.txt` - variable plotting
`files_for_each_topic/GetBranchNames.txt` - custom interaction with root branch names
`files_for_each_topic/IsolationPlots.txt` - special variable plotting for isolation variables.
`files_for_each_topic/SepandImp.txt` - getting separation and importance from the TMVA output.
`files_for_each_topic/SkimmingMacros.txt` - used for skimming step in the analysis.
`files_for_each_topic/VarEfficiencies.txt` 


