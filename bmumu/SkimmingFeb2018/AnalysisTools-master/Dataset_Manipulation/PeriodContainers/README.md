### Description

You will find here a set of scripts that are used to make containers, one per period (e.g 15 A, 15 B...).
Datasets can then be attached to these containers. This is useful when processing data in the Grid, given
that one usually has to process hundreds of runs, belonging to a few (between 10 and 20) periods.  
In order to use the scripts first do:  
`setupATLAS`  
`lsetup pyami`  

then you can:

`source make_period_containers.sh`  

which will make the period containers. You can adjust the names, by modifying the script. The names are
supposed to start with *user.your_username.*. After this you will need to attach the datasets. In order
to do this run:  

`source attach_datasets.sh`  

inside the script you will find a line that looks like:  

`PATTERN="data16_13TeV.%.physics_Main.deriv.DAOD_BPHY8.%p3583"`

Here you specify the pattern that the dataset names follow, % means wildcard (i.e. any character).  
After you run this, you will have two text files, one with the list of the datasets attached, and the name
of the container to which they were attached, and another with the list of datasets that were skipped.
Datasets are skipped when they have missing files. You will have to fix this eventually.

