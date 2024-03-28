import os

import requests
import re
import bs4
#*********************************************************
def check_regx(obj, loc, message):
    if len(obj) == 0:
        print(message)
        return ("", 0)
    else:
        return obj[loc]
#*********************************************************
def check_soup(obj, loc, message):
    try:
        val=obj[loc]
    except:
        print(message)
        return ""

    return val.text
#*********************************************************
OUTPUT_DIR="./run_query/"
htm_file="/home/acampove/Downloads/Runs_Events_2015_2016.htm"

if not os.path.isdir(OUTPUT_DIR):
    print("Cannot find %s, creating it." % OUTPUT_DIR)
    os.mkdir(OUTPUT_DIR)

if not os.path.isfile(htm_file):
    print("Cannot find %s." % htm_file)
    exit(1)
#*********************************************************
s=bs4.BeautifulSoup( open(htm_file), "html.parser" )
sections = s.find_all("tr", class_=re.compile("(out1|out2)"))
#*********************************************************
ofile=open("%s/runquery_run_events.txt" % OUTPUT_DIR, "w")

n_sections=len(sections)
print("#Runs:%d" % n_sections )
for i_section, section in enumerate(sections):
    col_1_text = check_soup( section.find_all("td"), 0, "Cannot find target in: %s" % section.text )

    result     = check_regx( re.findall("(\d+)(Period: )?([A-Z]\d+)?,?([A-Z])?.*", col_1_text), 0, "Cannot find run number in %s" % col_1_text )
    run_number = result[0]

    col_5_text = check_soup(section.find_all("td"), 5, "Cannot find 5 column %s" % section.text)
    col_6_text = check_soup(section.find_all("td"), 6, "Cannot find 6 column %s" % section.text)

    if "n.a." in col_5_text:
       num_events_delayed = "0"
    else:
        num_events_delayed = check_regx( re.findall("([0-9,]+)\s\(.*\)", col_5_text), 0, "Cannot find delayed st #events in: %s" % col_5_text ).replace(",","")

    if "n.a." in col_6_text:
       num_events_main = "0"
    else:
       num_events_main = check_regx( re.findall("([0-9,]+)\s\(.*\)", col_6_text), 0, "Cannot find delayed st #events in: %s" % col_6_text ).replace(",","")

    d_num_events_delayed = int(num_events_delayed) if num_events_delayed != "" else 0
    d_num_events_main = int(num_events_main) if num_events_main != "" else 0 

    num_events = str( d_num_events_delayed + d_num_events_main )
    run_number = "00" + run_number

    #print("%s,%s" % (CURRENT_SUBPERIOD, CURRENT_PERIOD))
    #print("%s %s %s %s" % (run_number, num_events, num_events_main, num_events_delayed))

    ofile.write("%s  %s  %s  %s\n" % (run_number, num_events_main, num_events_delayed, num_events) )

ofile.close()
#*********************************************************
