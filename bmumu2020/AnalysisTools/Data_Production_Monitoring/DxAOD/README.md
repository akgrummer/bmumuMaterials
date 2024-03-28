#### Description

In order to do the monitoring of the DxAOD production you have to:

1. Go to [this](https://prodtask-dev.cern.ch/prodtask/task_table/) page and find the tasks you want.

2. Save as complete webpage in the **data_web** directory, it should be saved as **data_web.html**.

3. Run:

   `python read_tasks.py`
   
   This should create text files about what is done and not done.
   These textfiles will end up in **samples_status/**.

4. Some files will be "not done". At the end these will be most likely missing just a few
   events. Use them anyway, including them as "done" by running:

   `source merge_status.sh`

4. Now you need to count the number of events in the input and output datasets. You need to
   specify in `get_nevents.txt` the text file name where these datasets are. This should have 
   been made in step 3, do it. Now run:
   
   `source get_nevents.sh`

5. Now you have to make the plots. This is done by doing:

   `python plot_runs.py`

6. Now you need a list of all the datasets available so that jobs can be sent to the grid with 
   those datasets as inputs. For this run:
   
   `python get_datasets.py IFILENAME TYPE`

   where **IFILENAME** is the appropiate file in **samples_status** and **TYPE** is output or input, for
   xAOD or DxAODs.

7. Now you need lists of datasets for both the main and delayed streams to produce ntuples 
   from them. This is done by doing 
   
   `source make_lists.sh`

8. Finally run:

   `source count_job_events.sh`

   to find the number of events corresponding to each list of datasets. They all should have the
   same number of events, roughly.

9. If you want to know wether you are double counting a dataset run:

   `python test_split.py`

   the only intersection should be between the datasets and themselves.

10. If you want to know the size in MB of the files, run:

   `source check_file_size.sh`

   which will provide the sizes in two different text files, one for the main and the other 
   for the delayed stream.

11. Sometimes jobs break and you want to assign them to yourself. So you run:
   
   `python reclassify.py`

   in order to modify the files in **datasets/** to contain an updated version of the lists of datasets.
   These lists go to **updated_datasets/**
