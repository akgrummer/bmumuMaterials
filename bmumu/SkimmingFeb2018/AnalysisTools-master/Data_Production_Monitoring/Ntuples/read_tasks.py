import sys 
import os
import glob

import requests
import re
import bs4
import urllib3 
#*********************************************************
def CheckMissing(l_tp_data, user):
    main_datasets = d_jobs[user][0]
    dely_datasets = d_jobs[user][1]

    ifile_main = open("updated_datasets/%s" % main_datasets )
    ifile_dely = open("updated_datasets/%s" % dely_datasets )
    
    l_main_dataset=ifile_main.read().splitlines()
    l_dely_dataset=ifile_dely.read().splitlines()

    ifile_main.close()
    ifile_dely.close()

    ofile_missing=open("%s/%s_missing.txt" % (directory, user), "a")
    l_dataset = l_main_dataset + l_dely_dataset
    for dataset in l_dataset:
        found = False
        for inp_ds, otp_ds, status in l_tp_data:
            if inp_ds == dataset:
                found = True
                break

        if not found:
            ofile_missing.write("%s\n" % dataset )

    ofile_missing.close()
#*********************************************************
def SaveData(l_tp_data, user):
    broken=open("%s/%s_broken.txt" % (directory, user), "w")
    finish=open("%s/%s_finished.txt" % (directory, user), "w")
    processing=open("%s/%s_processing.txt" % (directory, user), "w")

    done_in=open("%s/done_input.txt" % directory, "a")
    done_ot=open("%s/done_output.txt" % directory, "a")

    for inp_ds, otp_ds, status in l_tp_data:
        if status == "broken":
            broken.write("%s\n" % inp_ds)
        elif status == "finished" or status == "failed":
            finish.write("%s\n" % inp_ds)
        elif status == "done":
            done_in.write("%s\n" % inp_ds)
            for output in otp_ds:
                output=output.replace("\n", "")
                done_ot.write("%s\n" % output)
        elif status == "running" or status == "submitting":
            processing.write("{0:>50} {1:>20}\n".format(inp_ds, status) )

    broken.close()
    finish.close()
    done_in.close()
    done_ot.close()
    processing.close()
#*********************************************************
def fill_grl_runs():
    ifile_2015=open("runs_2015")
    l_2015_runs=ifile_2015.read().splitlines()
    s_runs_2015=set(l_2015_runs)

    ifile_2016=open("runs_2016")
    l_2016_runs=ifile_2016.read().splitlines()
    s_runs_2016=set(l_2016_runs)

    global s_grl_runs
    s_grl_runs=s_runs_2015.union(s_runs_2016)
#*********************************************************
def check_object(obj, loc, message):
    try:
        val=obj[loc]
    except:
        print(message)
        val=""

    return val
#*********************************************************
def GetInputDS(row):
    message="Cannot retrieve box with task number for row: %s" % row.text
    task=check_object( row.find_all("td"), 0, message )

    message="Cannot retrieve task id for box: %s" % task.text
    task_id=check_object(task.find_all("a"), 0, message)

    task_url="https://bigpanda.cern.ch/" + task_id.get("href")

    r=requests.get(task_url, verify=False)
    soup=bs4.BeautifulSoup(r.content, "html.parser")

    message="Cannot find input for url:%s" % task_url
    inp = check_object(soup.find_all("tr", class_="type-input type-all"), 0, message)
    if inp == "": return "" 

    message="Cannot find input dataset for url:%s" % task_url 
    inpt = check_object(inp.find_all("a"), 0, message)
    if inpt == "": return "" 

    input_dataset = (inpt.text).split(":")[1]

    return input_dataset
#*********************************************************
def GetOutputDS(row):
    message="Cannot retrieve box with task number for row: %s" % row.text
    task=check_object( row.find_all("td"), 0, message )

    message="Cannot retrieve task id for box: %s" % task.text
    task_id=check_object(task.find_all("a"), 0, message)

    task_url="https://bigpanda.cern.ch/" + task_id.get("href")

    r=requests.get(task_url, verify=False)
    soup=bs4.BeautifulSoup(r.content, "html.parser")

    message="Cannot find table with output datasets, for url %s" % task_url
    table=check_object( soup.find_all("table"), 4, message )

    message="Cannot find hist dataset, for url %s" % task_url
    out_ds_1=check_object( table.find_all("tr"), 1, message )

    message="Cannot find log dataset, for url %s" % task_url
    out_ds_2=check_object( table.find_all("tr"), 2, message )

    message="Cannot find BpJpsiK dataset, for url %s" % task_url
    out_ds_3=check_object( table.find_all("tr"), 3, message )

    message="Cannot find BsJpsiPhi dataset, for url %s" % task_url
    out_ds_4=check_object( table.find_all("tr"), 4, message )

    message="Cannot find Bsmumu dataset, for url %s" % task_url
    out_ds_5=check_object( table.find_all("tr"), 5, message )

    return [out_ds_1.text, out_ds_2.text, out_ds_3.text, out_ds_4.text, out_ds_5.text] 
#*********************************************************
def SkipRow(in_ds_name, user):
    file_name=d_jobs[user]

    ifile_main=open("updated_datasets/%s" % file_name[0])
    ifile_dely=open("updated_datasets/%s" % file_name[1])
    l_dataset_main=ifile_main.read().splitlines()
    l_dataset_dely=ifile_dely.read().splitlines()
    ifile_main.close()
    ifile_dely.close()

    if (in_ds_name not in l_dataset_main) and (in_ds_name not in l_dataset_dely):
        return 1

    return 0
#*********************************************************
def ProcessRow(row, panda_url, user):
    in_ds_name = GetInputDS(row)

    if SkipRow(in_ds_name, user):
        print("Skipping dataset %s" % in_ds_name)
        return ("", [], "")

    ot_ds_name = GetOutputDS(row)

    message="Cannot find status box for url:%s" % panda_url
    status = check_object(row.find_all("td"), 3, message)
    if status == "": 
        return ("", [], "")

    message="Cannot find status name for url:%s" % panda_url
    st_name = check_object(status.find_all("a"), 0, message)
    if st_name == "": 
        print("No stream name found in %s" % status.text)
        return ("", [], "")

    return (in_ds_name, ot_ds_name, st_name.text)
#*********************************************************
def ProcessRows(panda_url, user):
    r=requests.get(panda_url, verify=False)
    soup=bs4.BeautifulSoup(r.content, "html.parser")

    message="Cannot find table for:%s" % panda_url
    table = check_object( soup.find_all("table"), 2, message)
    if table == "": return ("", "")

    rows = table.find_all("tr")
    nrows = len(rows)
    if nrows <= 0:
        print("Found %d rows for url %s." % (nrows, panda_url) )
        return []
    else:
        print("Found %d rows." % nrows)

    l_tp_data=list()
    print("User:%s" % user)
    for i_row in range(2, nrows):
        print("Processing row %d" % i_row)

        message="Cannot find row for:%s" % panda_url
        row = check_object( rows, i_row, message)
        if row == "":
            print("Could not find row %d, break" % i_row)
            break
        else:
            tp_data = ProcessRow(row, panda_url, user)
            if tp_data == ("", [], ""):
                continue

            l_tp_data.append(tp_data)
            
    return l_tp_data
#*********************************************************
urllib3.disable_warnings(urllib3.exceptions.InsecureRequestWarning)
s_grl_runs=set()

angel_url="https://bigpanda.cern.ch/user/?user=Angel+Fernando+Campoverde+Quezada&days=11"
iskander_url="https://bigpanda.cern.ch/user/?user=Iskander+Ibragimov&days=11"
aidan_url="https://bigpanda.cern.ch/user/?user=Aidan+Grummer&days=11"
serguei_url="https://bigpanda.cern.ch/user/?user=sivokl&days=11"
umberto_url="https://bigpanda.cern.ch/user/?user=umberto+de+sanctis&days=11"
pavel_url="https://bigpanda.cern.ch/user/?user=Pavel+Reznicek&days=11"
fabio_url="https://bigpanda.cern.ch/user/?user=Fabio+Tresoldi&days=11"

fill_grl_runs()
#*********************************************************
d_jobs=dict()

d_jobs["aidan"]   =("split_main_00", "split_dely_00")
d_jobs["angel"]   =("split_main_06", "split_dely_04")
d_jobs["iskander"]=("split_main_01", "split_dely_01")
d_jobs["fabio"]   =("split_main_02", "split_dely_02")
d_jobs["pavel"]   =("split_main_03", "split_dely_03")
d_jobs["serguei"] =("split_main_04", "split_dely_05")
d_jobs["umberto"] =("split_main_05", "split_dely_06")
#*********************************************************
directory="jobs_status"
if not os.path.isdir(directory):
    os.mkdir(directory)

for FILE in glob.glob("%s/*.txt" % directory):
    os.remove(FILE)
#*********************************************************
print("Starting")

l_tp_data=ProcessRows(angel_url, "angel")
SaveData(l_tp_data, "angel")
CheckMissing(l_tp_data, "angel")

l_tp_data=ProcessRows(iskander_url, "iskander")
SaveData(l_tp_data, "iskander")
CheckMissing(l_tp_data, "iskander")

l_tp_data=ProcessRows(aidan_url, "aidan")
SaveData(l_tp_data, "aidan")
CheckMissing(l_tp_data, "aidan")

l_tp_data=ProcessRows(serguei_url, "serguei")
SaveData(l_tp_data, "serguei")
CheckMissing(l_tp_data, "serguei")

l_tp_data=ProcessRows(umberto_url, "umberto")
SaveData(l_tp_data, "umberto")
CheckMissing(l_tp_data, "umberto")

l_tp_data=ProcessRows(pavel_url, "pavel")
SaveData(l_tp_data, "pavel")
CheckMissing(l_tp_data, "pavel")

l_tp_data=ProcessRows(fabio_url, "fabio")
SaveData(l_tp_data, "fabio")
CheckMissing(l_tp_data, "fabio")
#*********************************************************

