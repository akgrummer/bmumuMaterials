import sys
import os
import re

import ROOT
import collections
import atlas
import utils

ROOT.gROOT.SetBatch()
#*******************************************************
def SaveSlide(filename, slide):
    ofile=open(filename, "w")
    for line in slide:
        ofile.write(line + "\n")

    ofile.close()
#*******************************************************
def GetSlide(stream, year, period, col_ev, xad_ev, dad_ev):
    str_pref=""
    if stream == "Main":
        str_pref = "main"
    elif stream == "Delayed":
        str_pref = "dely"
    else:
        print("Error, stream = %s", stream)

    image_name = str_pref + "_" + year + "_" + period

    l_slide=list()
    l_slide.append("\\begin{frame}{Stream: %s, Year: %s, Period: %s}" % (stream, year, period) )
    l_slide.append("    \\begin{figure}")
    l_slide.append("    \centering")
    l_slide.append("        \\begin{subfigure}[b]{0.8\\textwidth}")
    l_slide.append("            \centering")
    l_slide.append("            \includegraphics[width=\\textwidth]{DxAOD_Production/%s}" % image_name)
    l_slide.append("        \end{subfigure}")
    l_slide.append("    \end{figure}")
    l_slide.append("")
    l_slide.append("\\begin{tabular}{| r  r  r |}")
    l_slide.append("    \hline")
    l_slide.append("    Format& Events& [\%] of Collected\\" + "\\")
    l_slide.append("    \hline")
    l_slide.append("    Collected& %d & %.2f \\" % (col_ev, 100*(col_ev/float(col_ev) )) + "\\")
    l_slide.append("    xAOD     & %d & %.2f \\" % (xad_ev, 100*(xad_ev/float(col_ev) )) + "\\")
    l_slide.append("    DxAOD    & %d & %.2f \\" % (dad_ev, 100*(dad_ev/float(col_ev) )) + "\\")
    l_slide.append("    \hline   ")
    l_slide.append("\end{tabular}")
    l_slide.append("\end{frame}")

    return l_slide
#*******************************************************
def HasDelayedStream(int_run):
    return int_run >= 302956 
#*******************************************************
def ZeroErrors(histogram):
    nbins=histogram.GetNbinsX()
    for i_bin in range(1, nbins + 1): 
        histogram.SetBinError(i_bin, 0)
#*******************************************************
def GetPeriod(run):
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
def GetLines(file_name):
    ifile = open(file_name)
    lines=ifile.read().splitlines()

    return lines
#*******************************************************
def PadDictionary(d_to_pad, d_padding):
    for key in d_padding:
        if key not in d_to_pad:
            d_to_pad[key] = 0
#*******************************************************
#Useful counters
#*******************************************************
RUN_QUERY_NEVENTS_MAIN=0
RUN_QUERY_NEVENTS_DELAYED=0

XAOD_NEVENTS_MAIN=0
XAOD_NEVENTS_DELAYED=0

DXAOD_NEVENTS_MAIN=0
DXAOD_NEVENTS_DELAYED=0
#*******************************************************
OUTPUT_DIR="./plots/"
if not os.path.isdir(OUTPUT_DIR):
    os.mkdir(OUTPUT_DIR)
#*******************************************************
#Get GRL runs
#*******************************************************
l_2015_GRL_runs=GetLines("GRL/runs_2015.txt")
l_2016_GRL_runs=GetLines("GRL/runs_2016.txt")

l_GRL_runs = l_2015_GRL_runs + l_2016_GRL_runs 
#*******************************************************
#Get events for GRL runs from run query
#*******************************************************
lines=GetLines("run_query/runquery_run_events.txt")

d_rq_main_st=dict()
d_rq_dely_st=dict()

l_rq_runs=list()

for line in lines:
    l_line = line.split("  ")
    run = l_line[0]
    int_run = int(run)
    main_st = int(l_line[1])
    dely_st = int(l_line[2])

    if run not in l_GRL_runs:
        continue

    RUN_QUERY_NEVENTS_MAIN += main_st
    d_rq_main_st[run] = main_st 

    if HasDelayedStream(int_run):
        RUN_QUERY_NEVENTS_DELAYED += dely_st
        d_rq_dely_st[run] = dely_st 

    l_rq_runs.append(run)

d_rq_main_st = collections.OrderedDict( sorted(d_rq_main_st.items())  )
d_rq_dely_st = collections.OrderedDict( sorted(d_rq_dely_st.items())  )
#*******************************************************
#Did Run Query miss a GRL run?
#*******************************************************
for grl_run in l_GRL_runs:
    if grl_run not in l_rq_runs:
        print("GRL run %d not found in run query." % grl_run)
        exit(1)
#*******************************************************
#Fill main and delayed stream dictionaries
#*******************************************************
l_input_main = GetLines("rucio/input_main_run_event.txt" )
l_output_main = GetLines("rucio/output_main_run_event.txt" )

l_input_delayed= GetLines("rucio/input_delayed_run_event.txt" )
l_output_delayed= GetLines("rucio/output_delayed_run_event.txt" )

d_in_main_st = dict()
d_ot_main_st = dict()

d_in_dely_st = dict()
d_ot_dely_st = dict()

for line in l_input_main:
    l_line = line.split("   ")
    run=l_line[0]

    if run not in l_GRL_runs:
        continue

    events = int(l_line[1])
    XAOD_NEVENTS_MAIN+=events    
    if run in d_in_main_st:
        print("Repeated run at: %s" % line)
        d_in_main_st[run] += events
    else:
        d_in_main_st[run] = events

for line in l_input_delayed:
    l_line = line.split("   ")
    run=l_line[0]

    if run not in l_GRL_runs:
        continue

    events = int(l_line[1])
    XAOD_NEVENTS_DELAYED+=events
    if run in d_in_dely_st:
        d_in_dely_st[run] += events
        print("Repeated run at: %s" % line)
    else:
        d_in_dely_st[run] = events

for line in l_output_main:
    l_line = line.split("   ")
    run=l_line[0]
 
    if run not in l_GRL_runs:
        continue

    events = int(l_line[1])
    DXAOD_NEVENTS_MAIN+=events
    if run in d_ot_main_st:
        d_ot_main_st[run] += events
        print("Repeated run at: %s" % line)
    else:
        d_ot_main_st[run] = events

for line in l_output_delayed:
    l_line = line.split("   ")
    run=l_line[0]
 
    if run not in l_GRL_runs:
        continue

    events = int(l_line[1])
    DXAOD_NEVENTS_DELAYED+=events
    if run in d_ot_dely_st:
        d_ot_dely_st[run] += events
        print("Repeated run at: %s" % line)
    else:
        d_ot_dely_st[run] = events
#*******************************************************
#Padd missing in or ot dictionaries with rq dictionaries in case of missing runs
#*******************************************************
PadDictionary(d_in_main_st, d_rq_main_st)
PadDictionary(d_in_dely_st, d_rq_dely_st)

PadDictionary(d_ot_main_st, d_rq_main_st)
PadDictionary(d_ot_dely_st, d_rq_dely_st)
#*******************************************************
#Get number of runs per period
#*******************************************************
d_period_nruns_main_st=dict()
d_period_nruns_dely_st=dict()
for run in d_rq_main_st:
    int_run=int(run)
    period=GetPeriod(int_run) 

    if period in d_period_nruns_main_st:
        d_period_nruns_main_st[period] += 1
    else:
        d_period_nruns_main_st[period] = 1
    
    if not HasDelayedStream(int_run):
        continue

    if period in d_period_nruns_dely_st:
        d_period_nruns_dely_st[period] += 1
    else:
        d_period_nruns_dely_st[period] = 1
#*******************************************************
#Get number of events per period
#*******************************************************
d_period_nevents_main_st_rq=dict()
d_period_nevents_main_st_in=dict()
d_period_nevents_main_st_ot=dict()

d_period_nevents_dely_st_rq=dict()
d_period_nevents_dely_st_in=dict()
d_period_nevents_dely_st_ot=dict()

for run in d_rq_main_st:
    int_run = int(run)
    period=GetPeriod(int_run)

    if period in d_period_nevents_main_st_rq:
        d_period_nevents_main_st_rq[period] += d_rq_main_st[run]
    else:
        d_period_nevents_main_st_rq[period] = d_rq_main_st[run]

    if period in d_period_nevents_main_st_in:
        d_period_nevents_main_st_in[period] += d_in_main_st[run]
    else:
        d_period_nevents_main_st_in[period] = d_in_main_st[run]

    if period in d_period_nevents_main_st_ot:
        d_period_nevents_main_st_ot[period] += d_ot_main_st[run]
    else:
        d_period_nevents_main_st_ot[period] = d_ot_main_st[run]

for run in d_rq_dely_st:
    int_run = int(run)
    if not HasDelayedStream(int_run):
        continue

    period=GetPeriod(int_run)

    if period in d_period_nevents_dely_st_rq:
        d_period_nevents_dely_st_rq[period] += d_rq_dely_st[run]
    else:
        d_period_nevents_dely_st_rq[period] = d_rq_dely_st[run]

    if period in d_period_nevents_dely_st_in:
        d_period_nevents_dely_st_in[period] += d_in_dely_st[run]
    else:
        d_period_nevents_dely_st_in[period] = d_in_dely_st[run]

    if period in d_period_nevents_dely_st_ot:
        d_period_nevents_dely_st_ot[period] += d_ot_dely_st[run]
    else:
        d_period_nevents_dely_st_ot[period] = d_ot_dely_st[run]
#*******************************************************
d_period_nevents_main_st_rq = collections.OrderedDict( sorted( d_period_nevents_main_st_rq.items()) )
d_period_nevents_main_st_in = collections.OrderedDict( sorted( d_period_nevents_main_st_in.items()) )
d_period_nevents_main_st_ot = collections.OrderedDict( sorted( d_period_nevents_main_st_ot.items()) )

d_period_nevents_dely_st_rq = collections.OrderedDict( sorted( d_period_nevents_dely_st_rq.items()) )
d_period_nevents_dely_st_in = collections.OrderedDict( sorted( d_period_nevents_dely_st_in.items()) )
d_period_nevents_dely_st_ot = collections.OrderedDict( sorted( d_period_nevents_dely_st_ot.items()) )
#*******************************************************
#Make histograms for main and delayed stream periods
#*******************************************************
d_hist_rq_main_st=dict()
d_hist_xa_main_st=dict()
d_hist_dx_main_st=dict()

d_hist_rq_dely_st=dict()
d_hist_xa_dely_st=dict()
d_hist_dx_dely_st=dict()

for period in d_period_nruns_main_st:
    nruns=d_period_nruns_main_st[period]
    
    d_hist_rq_main_st[period]=utils.GetHistogram("h_rq_%s_main_st" % period, "Collected", 1, nruns, 0, 1, 1, 2e8, "GRL Run", "Events/GRL Runs")
    d_hist_xa_main_st[period]=utils.GetHistogram("h_xa_%s_main_st" % period, "xAOD", 2, nruns, 0, 1, 1, 2e8, "GRL Run", "Events/GRL Runs")
    d_hist_dx_main_st[period]=utils.GetHistogram("h_dx_%s_main_st" % period, "DxAOD", 4, nruns, 0, 1, 1, 2e8, "GRL Run", "Events/GRL Runs")

for period in d_period_nruns_dely_st:
    nruns=d_period_nruns_dely_st[period]
    if nruns == 0:
        continue

    d_hist_rq_dely_st[period]=utils.GetHistogram("h_rq_%s_dely_st" % period, "Collected", 1, nruns, 0, 1, 1, 2e8, "GRL Run", "Events/GRL Runs")
    d_hist_xa_dely_st[period]=utils.GetHistogram("h_xa_%s_dely_st" % period, "xAOD", 2, nruns, 0, 1, 1, 2e8, "GRL Run", "Events/GRL Runs")
    d_hist_dx_dely_st[period]=utils.GetHistogram("h_dx_%s_dely_st" % period, "DxAOD", 4, nruns, 0, 1, 1, 2e8, "GRL Run", "Events/GRL Runs")
#*******************************************************
#Fill histograms
#*******************************************************
for run in l_GRL_runs:
    int_run = int(run)
    period=GetPeriod(int_run)

    rq_events_main = d_rq_main_st[run]
    in_events_main = d_in_main_st[run]
    ot_events_main = d_ot_main_st[run]

    d_hist_rq_main_st[period].Fill(run, rq_events_main)
    d_hist_xa_main_st[period].Fill(run, in_events_main)
    d_hist_dx_main_st[period].Fill(run, ot_events_main)

    if not HasDelayedStream(int_run):
        continue

    rq_events_dely = d_rq_dely_st[run]
    in_events_dely = d_in_dely_st[run]
    ot_events_dely = d_ot_dely_st[run]

    d_hist_rq_dely_st[period].Fill(run, rq_events_dely)
    d_hist_xa_dely_st[period].Fill(run, in_events_dely)
    d_hist_dx_dely_st[period].Fill(run, ot_events_dely)
#*******************************************************
#Zero errors
#*******************************************************
for run in l_GRL_runs:
    int_run = int(run)
    period=GetPeriod(int_run)

    ZeroErrors(d_hist_rq_main_st[period])
    ZeroErrors(d_hist_xa_main_st[period])
    ZeroErrors(d_hist_dx_main_st[period])

    if period not in d_period_nruns_dely_st:
        continue

    ZeroErrors(d_hist_rq_dely_st[period])
    ZeroErrors(d_hist_xa_dely_st[period])
    ZeroErrors(d_hist_dx_dely_st[period])
#*******************************************************
#Make canvases
#*******************************************************
d_period_canvas_main_st=dict()

for period in d_period_nruns_main_st:
    d_period_canvas_main_st[period]=ROOT.TCanvas("can_main_%s" % period, "", 800, 600)

d_period_canvas_dely_st=dict()

for period in d_period_nruns_dely_st:
    nruns=d_period_nruns_dely_st[period]
    if nruns == 0:
        continue

    d_period_canvas_dely_st[period]=ROOT.TCanvas("can_dely_%s" % period, "", 800, 600)
#*******************************************************
#Draw in canvases
#*******************************************************
for period in d_period_nruns_main_st:
    d_period_canvas_main_st[period].cd()

    d_hist_rq_main_st[period].Draw("same Hist")
    d_hist_xa_main_st[period].Draw("same Hist")
    d_hist_dx_main_st[period].Draw("same Hist")

for period in d_period_nruns_dely_st:
    nruns = d_period_nruns_dely_st[period]
    if nruns == 0:
        continue

    d_period_canvas_dely_st[period].cd()

    d_hist_rq_dely_st[period].Draw("same Hist")
    d_hist_xa_dely_st[period].Draw("same Hist")
    d_hist_dx_dely_st[period].Draw("same Hist")
#*******************************************************
#Save canvases to file
#*******************************************************
ofile=ROOT.TFile("%s/histograms.root" % OUTPUT_DIR, "recreate")

for period in d_period_canvas_main_st:
    d_period_canvas_main_st[period].Write()

for period in d_period_canvas_dely_st:
    d_period_canvas_dely_st[period].Write()

ofile.Close()
#*******************************************************
#Save PDFs
#*******************************************************
for period in d_period_canvas_main_st:
    can = d_period_canvas_main_st[period]
    can_rad=utils.GetRatios(can, "h_rq_%s_main_st" % period, 0.01, 1.1, 1000, 600)
    can_rad.cd(1)
    ROOT.gPad.BuildLegend(0.7, 0.75, 0.95, 0.95)
    utils.ATLASLabel(0.20, 0.86, "Period %s" % period.replace("_", " "), 1, ROOT.gPad, "Data Main Stream")
    ROOT.gPad.SetLogy()
    utils.ReformatCanvas(ROOT.gPad)
    can_rad.cd(2)
    ROOT.gPad.SetLogy()
    can_rad.SaveAs("%s/main_%s.pdf" % (OUTPUT_DIR, period) )

for period in d_period_canvas_dely_st:
    can = d_period_canvas_dely_st[period]
    can_rad=utils.GetRatios(can, "h_rq_%s_dely_st" % period, 0.01, 1.1, 1000, 600)
    can_rad.cd(1)
    ROOT.gPad.BuildLegend(0.7, 0.75, 0.95, 0.95)
    utils.ATLASLabel(0.20, 0.86, "Period %s" % period.replace("_", " "), 1, ROOT.gPad, "Data Delayed Stream")
    ROOT.gPad.SetLogy()
    utils.ReformatCanvas(ROOT.gPad)
    can_rad.cd(2)
    ROOT.gPad.SetLogy()
    can_rad.SaveAs("%s/dely_%s.pdf" % (OUTPUT_DIR, period) )
#*******************************************************
#Save yields information
#*******************************************************
ofile_log=open("%s/output.log" % OUTPUT_DIR, "w")

l_lines=list()
l_lines.append("******************************")
l_lines.append("Number of run query main runs %d" % len(d_rq_main_st ))
l_lines.append("Number of run query delayed runs %d" % len(d_rq_dely_st ))
l_lines.append("******************************")
l_lines.append("Number of output main runs %d" % len(d_ot_main_st ))
l_lines.append("Number of input main runs %d" % len(d_in_main_st ))
l_lines.append("******************************")
l_lines.append("Number of output delayed runs %d" % len(d_ot_dely_st ))
l_lines.append("Number of input delayed runs %d" % len(d_in_dely_st ))
l_lines.append("******************************")
l_lines.append("RUN_QUERY_NEVENTS_MAIN=%d" % RUN_QUERY_NEVENTS_MAIN)
l_lines.append("RUN_QUERY_NEVENTS_DELAYED=%d" % RUN_QUERY_NEVENTS_DELAYED)
l_lines.append("XAOD_NEVENTS_MAIN=%d" % XAOD_NEVENTS_MAIN)
l_lines.append("XAOD_NEVENTS_DELAYED=%d" % XAOD_NEVENTS_DELAYED)
l_lines.append("DXAOD_NEVENTS_MAIN=%d" % DXAOD_NEVENTS_MAIN)
l_lines.append("DXAOD_NEVENTS_DELAYED=%d" % DXAOD_NEVENTS_DELAYED)
l_lines.append("******************************")

for line in l_lines:
    ofile_log.write("%s\n" % line)
    print(line)
#*******************************************************
#Print nevents per period
#*******************************************************
print("MAIN STREAM")
for period in d_period_nevents_main_st_rq:
    rq_ev = d_period_nevents_main_st_rq[period]
    xa_ev = d_period_nevents_main_st_in[period]
    dx_ev = d_period_nevents_main_st_ot[period]

    print("Run Query, Period: %s, Events: %d" % (period, rq_ev))
    print("xAOD, Period: %s, Events: %d"      % (period, xa_ev))
    print("DxAOD, Period: %s, Events: %d"     % (period, dx_ev))
    print("#########################################")

    result = re.findall("([0-9]{4})_([A-Z])", period)
    yr = result[0][0]
    per= result[0][1]

    slide=GetSlide("Main", yr, per, rq_ev, xa_ev, dx_ev)
    SaveSlide("./plots/main_%s_%s.tex" % (yr, per), slide)

print("DELAYED STREAM")
for period in d_period_nevents_dely_st_rq:
    rq_ev = d_period_nevents_dely_st_rq[period]
    xa_ev = d_period_nevents_dely_st_in[period]
    dx_ev = d_period_nevents_dely_st_ot[period]

    print("Run Query, Period: %s, Events: %d" % (period, rq_ev))
    print("xAOD, Period: %s, Events: %d"      % (period, xa_ev))
    print("DxAOD, Period: %s, Events: %d"     % (period, dx_ev))
    print("#########################################")

    result = re.findall("([0-9]{4})_([A-Z])", period)
    yr = result[0][0]
    per= result[0][1]

    slide=GetSlide("Delayed", yr, per, rq_ev, xa_ev, dx_ev)
    SaveSlide("./plots/dely_%s_%s.tex" % (yr, per), slide)
#*******************************************************
