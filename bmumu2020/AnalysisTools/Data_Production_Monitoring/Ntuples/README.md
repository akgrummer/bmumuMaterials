#### Description and usage

So, a bunch of jobs have been sent, by a bunch of people to the grid.
You want to monitor them and to do that you need to:

1. In `read_tasks.py` you have a bunch of URLs of the pages of the people
   who sent these jobs. You have to adjust these URLs appropiately.
   Furthermore there are a bunch of text files with the list of input data
   sets for each of these people. These are found in the linked `updated_datasets`
   directory.

   The output of this should be a group of text files describing the names of the datasets
   for each type of file.

2. For all the tasks found, the files contained in the containers have to be kept somewhere.
   The lists with these files are obtained by doing:

   `source get_files.sh`

   which are stored in `Datasets_Files/`

3. These files have to be attached to a given type of dataset. This can be done by:
   
   `source attach_files.sh`

4. You might want to have: 

   `run_number --> files`    
   `period     --> files`

   correspondences. This is implemented in json files storing maps between strings and
   lists of strings. These json files are made by doing:

   `python make_json.py`

   The input needed is obtained with 2. and the output goes to `json_files/`

5. You want to have three lists with DxAODs belonging to the Delayed stream, Main stream
   for runs where there was not delayed stream and Main stream collected at the same time as
   delayed stream. To do this you do:

   `python get_input_lists.py`

   the output are three text files in `DxAOD_Lists/`

6. Finally, if you want to check if the datasets have been attached run:

   `source check_datasets.sh`


