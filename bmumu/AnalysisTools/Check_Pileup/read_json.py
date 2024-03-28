import json

#*************************************************
def pass_grl(run_number, lumi_block):
    key="%d_%d" % (run_number, lumi_block)

    if run_number > 284484 and (key in d_grl_2016):
        return 1
    elif run_number <= 284484 and (key in d_grl_2015):
        return 1
    else:
        return 0
#*************************************************
def pileup(run_number, lumi_block):
    key="%d_%d" % (run_number, lumi_block)

    if run_number > 284484 and (key in d_pileup_2016):
        return d_pileup_2016[key] 
    elif run_number <= 284484 and (key in d_pileup_2015):
        return d_pileup_2015[key] 
    else:
        return -1
#*************************************************
print("Loading GRL json file")
#*************************************************
grl_2015_filename="json/grl_2015.json"
grl_2016_filename="json/grl_2016.json"

ifile_grl_2015=open(grl_2015_filename)
d_grl_2015=json.load(ifile_grl_2015)

ifile_grl_2016=open(grl_2016_filename)
d_grl_2016=json.load(ifile_grl_2016)
#*************************************************
print("Loading pileup json file")
#*************************************************
pileup_2015_filename="json/pileup_2015.json"
pileup_2016_filename="json/pileup_2016.json"

ifile_pileup_2015=open(pileup_2015_filename)
d_pileup_2015=json.load(ifile_pileup_2015)

ifile_pileup_2016=open(pileup_2016_filename)
d_pileup_2016=json.load(ifile_pileup_2016)
#*************************************************

