import json
import os

#*******************************************************
def SaveDictionary(dictionary, filename):
    ofile=open("%s/%s" % (JSON_DIR, filename), "w")
    json.dump(dictionary, ofile)
    ofile.close()
#*******************************************************
def GetPeriod(s_run):
    run=int(s_run)
    if run in range(276262 , 276954 + 1):
        return "2015_D"
    if run in range(278727 , 279928 + 1):
        return "2015_E"
    if run in range(279932 , 280422 + 1):
        return "2015_F"
    if run in range(280423 , 281075 + 1):
        return "2015_G"
    if run in range(281130 , 281411 + 1):
        return "2015_H"
    if run in range(281662 , 282482 + 1):
        return "2015_I"
    if run in range(282625 , 284484 + 1):
        return "2015_J"
    if run in range(286328 , 286474 + 1):
        return "2015_K"
    if run in range(286665 , 287983 + 1):
        return "2015_L"

    l_H_2016=[305359,309314,309346,310216]

    if run in range(289496 , 300287 + 1) and (run not in l_H_2016):
        return "2016_A"
    if run in range(300345 , 300908 + 1) and (run not in l_H_2016):
        return "2016_B"
    if run in range(301912 , 302393 + 1) and (run not in l_H_2016):
        return "2016_C"
    if run in range(302737 , 303560 + 1) and (run not in l_H_2016):
        return "2016_D"
    if run in range(303638 , 303892 + 1) and (run not in l_H_2016):
        return "2016_E"
    if run in range(303943 , 304494 + 1) and (run not in l_H_2016):
        return "2016_F"
    if run in range(305291 , 306714 + 1) and (run not in l_H_2016):
        return "2016_G"
    if run in range(307124 , 308084 + 1) and (run not in l_H_2016):
        return "2016_I"
    if run in range(308979 , 309166 + 1) and (run not in l_H_2016):
        return "2016_J"
    if run in range(309311 , 309759 + 1) and (run not in l_H_2016):
        return "2016_K"
    if run in range(310015 , 311481 + 1) and (run not in l_H_2016):
        return "2016_L"

    if run in l_H_2016:
        return "2016_H"

    print("Could not find run %s" % run)

    return ""
#*******************************************************
def process_file(filename):
    print("Processing file: %s" % filename)

    ifile=open(filename)
    l_line=ifile.read().splitlines()
    ifile.close()

    for line in l_line:
        l_element=line.split("         ")

        #drop scope, get only file name
        file_name=l_element[0].split(":")[1]
        run_number=l_element[1]

        if run_number in d_run_l_file:
            d_run_l_file[run_number].append(file_name)
        else:
            d_run_l_file[run_number]=[file_name]

        period=GetPeriod(run_number)
        if period in d_period_l_file:
            d_period_l_file[period].append(file_name)
        else:
            d_period_l_file[period]=[file_name]
#*******************************************************
DIR_FILES="Datasets_Files/"
d_run_l_file=dict()
d_period_l_file=dict()

process_file("%s/Delayed_Bmumu.txt" % DIR_FILES)              
process_file("%s/Delayed_Bplus.txt" % DIR_FILES)              
process_file("%s/Delayed_BsJpsiPhi.txt" % DIR_FILES)          
process_file("%s/Delayed_Log.txt" % DIR_FILES)                
process_file("%s/Delayed_Hist.txt" % DIR_FILES)               

process_file("%s/Main_Bmumu.txt" % DIR_FILES)                 
process_file("%s/Main_Bplus.txt" % DIR_FILES)                 
process_file("%s/Main_BsJpsiPhi.txt" % DIR_FILES)             
process_file("%s/Main_Log.txt" % DIR_FILES)                   
process_file("%s/Main_Hist.txt" % DIR_FILES)                  

process_file("%s/Main_With_Delayed_Bmumu.txt" % DIR_FILES)    
process_file("%s/Main_With_Delayed_Bplus.txt" % DIR_FILES)    
process_file("%s/Main_With_Delayed_BsJpsiPhi.txt" % DIR_FILES)
process_file("%s/Main_With_Delayed_Log.txt"  % DIR_FILES)     
process_file("%s/Main_With_Delayed_Hist.txt" % DIR_FILES)    
#*******************************************************
JSON_DIR="json_files"
if not os.path.isdir(JSON_DIR):
    os.mkdir(JSON_DIR)

SaveDictionary(d_run_l_file, "run_files.json")
SaveDictionary(d_period_l_file, "period_files.json")
#*******************************************************

