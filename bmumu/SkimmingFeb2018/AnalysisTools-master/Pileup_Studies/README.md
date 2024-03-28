#### Description

The scripts in this directory are used to check the pileup distributions after
the PileupReweighting tool is applied.

#### Usage

You have to produce ntuples storing the pileup distributions after reweighting.
These ntuples should be made with the `pileup_reweighting` branch of the `Tester`
project, that can be found [here](https://:@gitlab.cern.ch:8443/RootCore_Pkgs/Tester.git).

##### Data/MC comparisons

The Data/MC comparison is done by running:    

`python mcrw_data.py` SETTING

where `SETTING` can be found in a list inside the script, right now it has:    
`["xaod_fixed", "xaod", "xaod_same_trigger", "xaod_2015", "xaod_2016", "dxaod", "dxaod_same_trigger", "dxaod_2015", "dxaod_2016"]`

The output goes in a directory with the name `plots_SETTING`. In case you want many settings run:

`source steer_mcrw_data.sh`

with its contents modified appropiately.

#### Copy plots somewhere else

By doing:

`source copy_plots.sh TARGET`

the directories with the plots will be copied to a given `TARGET` directory. You can do it by 
hand but this might be more practical

#### Cleanup

By calling:

`source clean.sh WHAT`

where `WHAT=root/plots`. The script will remove the directories with root files or PDFs. This is
safer than removing by hand.
