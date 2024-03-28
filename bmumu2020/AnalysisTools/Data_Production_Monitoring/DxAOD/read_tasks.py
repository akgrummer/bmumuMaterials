import sys 
import os

import requests
import re
import bs4

#*********************************************************
def check():
    if not os.path.isdir("samples_status"):
        os.mkdir("samples_status")
#*********************************************************
def check_object(obj, loc, message):
    try:
        val=obj[loc]
    except:
        print(message)
        val=""

    return val
#*********************************************************
def GetOutputDS(panda_url):
    r=requests.get(panda_url, verify=False)
    soup=bs4.BeautifulSoup(r.content, "html.parser")

    message="Cannot find input for url:%s" % panda_url
    inp = check_object(soup.find_all("tr", class_="type-input type-all"), 0, message)
    if inp == "": return ("", "")
    
    message="Cannot find output for url:%s" % panda_url
    out = check_object(soup.find_all("tr", class_="type-output type-all"), 0, message)
    if out == "": return ("", "")
   
    message="Cannot find input dataset for url:%s" % panda_url
    inpt = check_object(inp.find_all("a"), 0, message)
    if inpt == "": return ("", "")

    message="Cannot find output dataset for url:%s" % panda_url
    output = check_object(out.find_all("a"), 0, message)
    if output == "": return ("", "")

    return (inpt.text, output.text)
#*********************************************************
check()
#*********************************************************
htm_file="data_web/data_web.html"

s=bs4.BeautifulSoup( open(htm_file), "html.parser" )
sections = s.find_all("tr", class_=re.compile("(even|odd)"))
#*********************************************************
done_bphy8=open("samples_status/done_bphy8.txt", "w")
done_bphy9=open("samples_status/done_bphy9.txt", "w")

not_done_bphy8=open("samples_status/not_done_bphy8.txt", "w")
not_done_bphy9=open("samples_status/not_done_bphy9.txt", "w")
#*********************************************************
n_sections=len(sections)
print("#Sections:%d" % n_sections )

output_log=open("read_tasks.log", "w")
for i_section, section in enumerate(sections):
    print("Processing section %d/%d." % (i_section, n_sections))

    tsk = section.find_all("td", class_="numbers taskid sorting_1")[0]
    elm = tsk.find_all("a")[0]

    url_tsk = elm.get("href")
    tsk_id = elm.text

    sta_1 = section.find_all("td", class_="centered")[1]
    sta_2 = sta_1.find_all("span")[0]

    status= sta_2.text

    DSID=GetOutputDS(url_tsk)

    if status == "done" and re.search("BPHY8", DSID[1]):
        done_bphy8.write("Input:%s, Output:%s, TaskID:%s\n" % (DSID[0], DSID[1], tsk_id))
    elif status == "done" and re.search("BPHY9", DSID[1]):
        done_bphy9.write("Input:%s, Output:%s, TaskID:%s\n" % (DSID[0], DSID[1], tsk_id))
    elif status != "done" and re.search("BPHY8", DSID[1]):
        not_done_bphy8.write("Input:%s, Output:%s, TaskID:%s, Status:%s\n" % (DSID[0], DSID[1], tsk_id, status))
    elif status != "done" and re.search("BPHY9", DSID[1]):
        not_done_bphy9.write("Input:%s, Output:%s, TaskID:%s, Status:%s\n" % (DSID[0], DSID[1], tsk_id, status))
    else:
        print("XXXXXXXXXXXXXXXXXXXXXXXXX")
        print("Wrong status:%s" % status)
        print("Dataset: %s" % DSID[1])
        print("XXXXXXXXXXXXXXXXXXXXXXXXX")

        output_log.write("Wrong status:%s\n" % status)
        output_log.write("Dataset: %s\n" % DSID[1])

output_log.close()
#*********************************************************
not_done_bphy8.close()
done_bphy8.close()

not_done_bphy9.close()
done_bphy9.close()
#*********************************************************

