import ROOT
import math
import atlas

import os
import json

#*******************************************************
CME="#sqrt{s}=13TeV"
RATIO_LOW=0
RATIO_HIGH=3

LEG_DX=0.3
LEG_DY=0.28

MAX_NSCALE=1.4
#*******************************************************
class MergePlots(object):
    def __init__(self, l_graphs):
        super(MergePlots, self).__init__()
        self.l_graphs    = l_graphs
        self.l_pads      = list()
        self.num_xlabels = 5 if len(l_graphs) > 5 else len(l_graphs)

        self.max_y = 0
        self.min_y = 0
    #******************************************
    def Print(self):
        for graph in self.l_graphs:
            graph.Print()
    #******************************************
    def SetRange(self, max_y, min_y):
        self.max_y = max_y
        self.min_y = min_y
    #******************************************
    def GetRange(self):

        if self.max_y != 0 and self.min_y != 0:
            return [self.min_y, self.max_y]

        maximum = 0
        minimum = 0

        for graph in self.l_graphs:
            xmax = ROOT.Double()
            xmin = ROOT.Double()

            ymax = ROOT.Double()
            ymin = ROOT.Double()

            graph.ComputeRange(xmin, ymin, xmax, ymax)

            if ymax > maximum:
                maximum = ymax

            if ymin < minimum:
                minimum = ymin

        return [minimum, maximum]
    #******************************************
    def GetyAxis(self):
        Range=self.GetRange()
        yaxis = ROOT.TGaxis(0.1, 0.192, 0.1, 0.906, Range[0], Range[1], 510)
        yaxis.SetLineColor(4)

        return yaxis
    #******************************************
    def FormatGraphs(self):
        n_graphs = len(self.l_graphs)
        for i_graph in range(0, n_graphs):
            graph = self.l_graphs[i_graph]

            x_axis = graph.GetXaxis()
            y_axis = graph.GetYaxis()

            x_axis.SetTickLength(0.00)
            nbins = x_axis.GetNbins()
            x_axis.SetBinLabel(nbins/2, graph.GetTitle() )
            x_axis.LabelsOption("v")
            graph.SetTitle("")

            graph.GetXaxis().SetLabelSize(0.026 * math.pow(n_graphs, 1) )

            if i_graph != 0:
                graph.GetYaxis().SetLabelColor(0)
                graph.GetYaxis().SetAxisColor(0)
            else:
                graph.GetYaxis().SetLabelColor(0)
                graph.GetYaxis().SetAxisColor(4)

            graph.GetYaxis().SetTitle("")
    #******************************************
    def GetPads(self):
        if len(self.l_pads) > 0:
            return

        pad_width = 0.8/len(self.l_graphs)
        xmin = 0.1

        npads = len(self.l_graphs)
        for i_pad in range(0, npads):
            xlo = xmin + (i_pad + 0.) * pad_width
            xhi = xmin + (i_pad + 1.) * pad_width
            ylo = 0.05
            yhi = 1

            pad = ROOT.TPad("pad_%d" % i_pad, "", xlo, ylo, xhi, yhi)
            pad.SetNumber(i_pad)
            pad.SetFrameLineColor(0)
            pad.SetBottomMargin(0.15)

            self.l_pads.append(pad)
    #******************************************
    def SetYaxisTitle(self, title):
        self.YTitle = title
    #******************************************
    def Plot(self, file_name):
        can_mrg = ROOT.TCanvas("can_mrg", "", 800, 600)
        can_mrg.SetLeftMargin(0)
        self.GetPads()

        n_graphs = len(self.l_graphs)

        l_range = self.GetRange()

        if len(self.l_pads) != len(self.l_graphs):
            print( "Number of pads %d and graphs %s, are different." % ( len(self.l_pads), len(self.l_graphs) ) )
            exit(1)

        self.FormatGraphs()
        for i_graph, graph in enumerate(self.l_graphs):
            # graph.GetYaxis().SetAxisMinimum(l_range[0])
            # graph.GetYaxis().SetAxisMaximum(l_range[1])
            graph.GetYaxis().SetLimits( l_range[0], l_range[1] )

            pad = self.l_pads[i_graph]
            can_mrg.cd()

            pad.Draw()
            pad.cd()
            graph.Draw("AC")

            if i_graph != 0:
                pad.SetLeftMargin(0)

            if i_graph != n_graphs -1:
                pad.SetRightMargin(0)

        can_mrg.cd()

        yaxis = self.GetyAxis()
        yaxis.SetTitle(self.YTitle)
        yaxis.SetTitleOffset(1)
        yaxis.Draw()

        can_mrg.SaveAs("%s.pdf" % file_name)

        ofile=ROOT.TFile("%s.root" % file_name,"recreate")
        can_mrg.Write()
        ofile.Close()
#*******************************************************
def IsHist(hist):
    is_TH1F = hist.InheritsFrom(ROOT.TH1F.Class())
    is_TH1D = hist.InheritsFrom(ROOT.TH1D.Class())

    return is_TH1F or is_TH1D
#*********************************************************
def DrawFit(frame, obs, canvas, minx, maxx, opt=""):
    pull = frame.pullHist()
    frame_pull = obs.frame()
    frame_pull.addPlotable(pull, "P")
    #******************************************
    frame_pull.GetXaxis().SetTitle("")
    frame_pull.GetYaxis().SetTitle("Pull")

    frame_pull.GetXaxis().SetLabelSize(0.1)
    frame_pull.GetYaxis().SetLabelSize(0.1)

    frame_pull.GetYaxis().SetTitleSize(0.1)
    frame_pull.GetYaxis().SetTitleOffset(0.7)
    #******************************************

    xaxis_frame = frame.GetXaxis()
    xaxis_pull  = frame_pull.GetXaxis()

    xaxis_frame.SetRangeUser(minx, maxx)
    xaxis_pull.SetRangeUser(minx, maxx)

    canvas.SetBit(ROOT.kMustCleanup)
    canvas.Divide(1, 2)
    canvas.cd(2)
    ROOT.gPad.SetPad(0, 0.03, 1, 0.3)
    frame_pull.Draw()

    if opt == "logx":
        ROOT.gPad.SetLogx()
    #********************************
    p2sigma = ROOT.TLine(minx, 2, maxx, 2)
    ROOT.SetOwnership(p2sigma, False)
    p2sigma.SetLineStyle(4)
    p2sigma.SetLineColor(4)
    p2sigma.Draw()

    m2sigma = ROOT.TLine(minx, -2, maxx, -2)
    ROOT.SetOwnership(m2sigma, False)
    m2sigma.SetLineStyle(4)
    m2sigma.SetLineColor(4)
    m2sigma.Draw()

    p1sigma = ROOT.TLine(minx, 1, maxx, 1)
    ROOT.SetOwnership(p1sigma, False)
    p1sigma.SetLineStyle(2)
    p1sigma.SetLineColor(2)
    p1sigma.Draw()

    m1sigma = ROOT.TLine(minx, -1, maxx, -1)
    ROOT.SetOwnership(m1sigma, False)
    m1sigma.SetLineStyle(2)
    m1sigma.SetLineColor(2)
    m1sigma.Draw()
    #********************************
    canvas.cd(1)
    ROOT.gPad.SetPad(0, 0.3, 1, 1)
    frame.Draw()

    if opt == "logx":
        ROOT.gPad.SetLogx()
#*********************************************************
def ReformatRooPlot(frame, pdf_names=["pdf"], data_names=["data"]):
    print( "utils.py::Reformating frame.")
    frame.Print("v")

    l_hist=list()
    l_pdf =list()
    l_text=list()

    for pdf_name in pdf_names:
        l_pdf.append( frame.findObject(pdf_name) )
        l_text.append( frame.findObject(pdf_name + "_paramBox") )

    for data_name in data_names:
        l_hist.append( frame.findObject(data_name) )

    for hist in l_hist:
        try:
            max_y = hist.GetHistogram().GetMaximum()
            frame.SetMaximum(1.3*max_y)
        except Exception as e:
            print("Histogram not found, maxy unchanged.")

    n_text = ROOT.TPaveText()
    n_text.Paint("NDC")

    for text in l_text:
        try:
            text.Paint("NDC")
            text.SetLineColor(0)
            text.SetFillStyle(0)
            text.SetX1NDC(0.55)
            text.SetX2NDC(0.90)
            text.SetY1NDC(0.80)
            text.SetY2NDC(0.92)
        except Exception as e:
            print("Parameters Box not found")

    return l_text
#*********************************************************Re sets maxima of histograms and erases legend's margin.
def ReformatCanvas(Pad):
    #**********************************
    l_hist =list()
    l_roohist = list()
    l_legd =list()
    multigraph = ROOT.TMultiGraph()
    stackhist = ROOT.THStack()

    primitives=Pad.GetListOfPrimitives()

    for primitive in primitives:
        if primitive.InheritsFrom(ROOT.RooHist.Class()):
            l_roohist.append(primitive)

        if primitive.InheritsFrom(ROOT.TH1.Class()):
            primitive.SetStats(False);
            l_hist.append(primitive)

        if primitive.InheritsFrom(ROOT.TLegend.Class()):
            l_legd.append(primitive)

        if primitive.InheritsFrom(ROOT.TMultiGraph.Class() ):
            multigraph=primitive

        if primitive.InheritsFrom(ROOT.THStack.Class() ):
            stackhist = primitive
            histograms = stackhist.GetHists()

    max_y=0

    for hist in l_hist:
        if max_y < hist.GetMaximum():
            max_y = hist.GetMaximum()

    for hist in l_roohist:
        if max_y < hist.GetMaximum():
            max_y = hist.GetMaximum()

    if max_y < stackhist.GetMaximum():
        max_y = stackhist.GetMaximum()

    if multigraph.GetListOfGraphs():
        for graph in multigraph.GetListOfGraphs():
            ymax = graph.GetYaxis().GetXmax()
            if max_y < ymax:
                max_y = ymax

    is_log = Pad.GetLogy()
    if is_log:
        scale = 10**1.9 * max_y
    else:
        scale = MAX_NSCALE * max_y

    print("utils.py::ReformatCanvas::New maximum: " + str(scale))
    for hist in l_hist:
        hist.SetMaximum(scale)
        if not is_log:
            yaxis = hist.GetYaxis()
            yaxis.SetRangeUser(0, scale)

        hist.SetTitle("")

    multigraph.SetMaximum(scale)
    stackhist.SetMaximum(scale)

    for legend in l_legd:
        legend.SetLineWidth(0)
        legend.SetFillStyle(0)

    Pad.SetTopMargin(0.05)
    Pad.SetRightMargin(0.08)
    Pad.SetBottomMargin(0.16)
    # Pad.SetLeftMargin(0.10)

    Pad.Update()
#*********************************************************
def Reformat2D(canvas):
    canvas.SetRightMargin(0.11)
    canvas.SetLeftMargin(0.16)
    canvas.SetBottomMargin(0.16)
    canvas.SetTopMargin(0.05)

    v_hist=ROOT.std.vector("TH2F*")()
    primitives = canvas.GetListOfPrimitives()
    for primitive in primitives:
        if primitive.InheritsFrom(ROOT.TH2.Class()) and primitive.GetEntries() > 0:
            v_hist.push_back(primitive)

    canvas.Update()
    for hist in v_hist:
        palette = hist.GetListOfFunctions().FindObject("palette")
        palette.SetX1NDC(0.895)
        palette.SetX2NDC(0.92)
        palette.SetY1NDC(0.25)
        palette.SetY2NDC(0.95)
# ********************************************************
def ATLASLabel(x, y, text, color, canvas, extra_txt=""):
    l=ROOT.TLatex()
    l.SetNDC()
    l.SetTextFont(72)
    l.SetTextColor(color)

    delx = 0.115*696*canvas.GetWh()/( 472*canvas.GetWw() )
    dely = 0.0001 * canvas.GetWh()

    l.DrawLatex(x,y,"ATLAS")

    p=ROOT.TLatex()
    p.SetNDC()
    p.SetTextFont(42)
    p.SetTextColor(color)
    p.DrawLatex(x+delx,y,text)
    p.DrawLatex(x,y-1.*dely, extra_txt)
    p.DrawLatex(x,y-2.*dely, CME)
#*********************************************************
def GetLegend(x1, x2, y1, y2, d_objects, header = ""):
    legend = ROOT.TLegend(x1, x2, y1, y2)
    legend.SetHeader(header)
    for key in d_objects:
        try:
            legend.AddEntry( d_objects[key], key, "l")
        except Exception as e:
            print("Cannot add legend for %d" % key)

    return legend
#*********************************************************
def GetHistogram(name, title, color, nbins, minx, maxx, miny=0, maxy=0, title_x="", title_y = ""):
    bin_width = float( (maxx-minx)/nbins )

    hist = ROOT.TH1F(name, title, nbins, minx, maxx)
    hist.SetLineColor(color)
    hist.SetMarkerColor(color)
    hist.GetXaxis().SetTitle(title_x)
    hist.GetYaxis().SetTitle(title_y)

    if maxy != 0:
        hist.GetYaxis().SetRangeUser(miny, maxy)

    return hist
#*********************************************************
def GetHistogram2D(name, title, nbins_x, min_x, max_x, nbins_y, min_y, max_y, title_x, title_y):
    hist = ROOT.TH2F(name, title, nbins_x, min_x, max_x, nbins_y, min_y, max_y)
    hist.GetXaxis().SetTitle(title_x)
    hist.GetYaxis().SetTitle(title_y)

    return hist
#*********************************************************
def SaveHistograms(l_histograms, out_path, kind , process, normalize=False, log=False, legend=0, ratio=False):
    if len(l_histograms) == 0:
        print("No histograms were found")
        exit(1)

    name=os.path.basename(out_path)

    can=ROOT.TCanvas("can_%s" % name , "", 800, 600)

    for histogram in l_histograms:
        if normalize:
            histogram.GetYaxis().SetTitle("Normalized")
            histogram.DrawNormalized("same E1")
        else:
            histogram.Draw("same E1")

    if log:
        can.SetLogy()

    if legend == 1:
        can.BuildLegend(0.6, 0.93 - LEG_DY, 0.6 + LEG_DX, 0.93)
    elif legend == -1:
        can.BuildLegend(0.6, 0.20, 0.9, 0.50)
    elif legend == 2:
        can.BuildLegend(0.2, 0.65, 0.5, 0.93)
    elif legend == -2:
        can.BuildLegend(0.2, 0.20, 0.5, 0.50)
    elif legend == 0:
        pass
    else:
        print("Legend = %d, not recognized." % legend)

    if ratio:
        reference_name = l_histograms[0].GetName()
        print("Using reference histogram: %s" % reference_name)
        can_ratio = GetRatios(can, reference_name, RATIO_LOW, RATIO_HIGH)

        can_ratio.cd(1)

        if log:
            ROOT.gPad.SetLogy()

        if legend == 1:
            ROOT.gPad.BuildLegend(0.6, 0.93 - LEG_DY, 0.6 + LEG_DX, 0.93)
        elif legend == -1:
            ROOT.gPad.BuildLegend(0.6, 0.20, 0.9, 0.50)
        elif legend == 2:
            ROOT.gPad.BuildLegend(0.2, 0.65, 0.5, 0.93)
        elif legend == -2:
            ROOT.gPad.BuildLegend(0.2, 0.20, 0.5, 0.50)
        elif legend == 0:
            pass
        else:
            print("Legend = %d, not recognized." % legend)

        ReformatCanvas(ROOT.gPad)
        ATLASLabel(0.20, 0.86, kind, 1, ROOT.gPad, process)

        can_ratio.SaveAs("%s.pdf" % out_path)
        return

    ReformatCanvas(can)
    ATLASLabel(0.20, 0.86, kind, 1, can, process)

    path = os.path.dirname(out_path)
    if not os.path.isdir(path):
        try:
            os.mkdir(path)
        except OSError:
            print("Could not make directory \"%s\"." % path)
            exit(1)

    can.SaveAs("%s.pdf" % out_path)
#*********************************************************
def SaveCanvas(canvas, out_path):
    path = os.path.dirname(out_path)
    if not os.path.isdir(path):
        try:
            os.mkdir(path)
        except OSError:
            print("Could not make directory \"%s\"." % path)
            exit(1)

    canvas.SaveAs("%s.pdf" % out_path)
#*********************************************************
def SaveHistograms2D(l_histograms, kind, process, log=False):
    for histogram in l_histograms:
        name = histogram.GetTitle()
        can = ROOT.TCanvas("can_%s" % name, "", 800, 600)
        histogram.Draw("colz")

        Reformat2D(can)
        ATLASLabel(0.20, 0.86, kind, 1, can, process)

        can.SaveAs("%s.pdf" % name)
#*********************************************************
def GetRatios(canvas, reference_hist, ratio_ylo = 0, ratio_yhi = 3, can_width=800, can_height=600):
    primitives = canvas.GetListOfPrimitives()

    h_ref = primitives.FindObject(reference_hist)

    try:
        print("Using reference %s " % h_ref.GetName())
    except ReferenceError:
        print("Could not retrieve reference histogram %s" % h_ref.GetName())
        exit(1)

    if not IsHist(h_ref):
        print("Reference histogram %s, is not a histogram." % reference_hist)
        exit(1)

    l_h_ratio = list()
    l_h_main  = list()

    for primitive in primitives:
        #********************************
        if not IsHist(primitive):
            continue
        #********************************
        h_main = primitive.Clone( "ratio_%s" % primitive.GetName() )
        ROOT.SetOwnership(h_main, False)
        l_h_main.append(h_main)
        #********************************
        is_reference = reference_hist == primitive.GetName()
        if is_reference:
            continue
        #********************************
        h_ratio = h_main.Clone()
        ROOT.SetOwnership(h_ratio, False)
        h_ratio.SetName( reference_hist + "_" + h_main.GetName() )
        h_ratio.Divide(h_main, h_ref)
        #********************************
        h_ratio.SetStats(False)
        h_ratio.SetTitle("")
        #********************************
        h_ratio.GetXaxis().SetTitle("")

        h_ratio.GetYaxis().SetTitle( "%s/%s" % (h_main.GetTitle(), h_ref.GetTitle()) )
        h_ratio.GetYaxis().SetTitleOffset(0.51)
        h_ratio.GetYaxis().SetTitleSize(0.08)
        #********************************
        l_h_ratio.append(h_ratio)
        #********************************

    can_ratio = ROOT.TCanvas("can_%s" % (reference_hist), "", can_width, can_height)
    can_ratio.SetBit(ROOT.kMustCleanup)
    can_ratio.Divide(1, 2, 0.01, 0.01, 0)

    can_ratio.cd(1)
    ROOT.gPad.SetPad(0, 0.33, 1, 1)
    for h_main in l_h_main:
        h_main.Draw("same")

    can_ratio.cd(2)
    ROOT.gPad.SetGridx()
    ROOT.gPad.SetGridy()
    ROOT.gPad.SetPad(0, 0.03, 1, 0.33)
    ROOT.gPad.SetRightMargin(0.08)

    for h_main, h_ratio in zip(l_h_main, l_h_ratio):
        h_ratio.GetYaxis().SetRangeUser(ratio_ylo, ratio_yhi)
        if len(l_h_ratio) == 1:
            h_ratio.SetMarkerColor(1)
            h_ratio.SetLineColor(1)
        else:
            color=h_main.GetLineColor()
            h_ratio.GetYaxis().SetTitle("X/%s" % h_ref.GetTitle() )

        h_ratio.Draw("same")

    return can_ratio
#*********************************************************
def SaveFrame(frame, pdf_names=[], data_names=[], kind="", process="", log=False, legend=False):
    can=ROOT.TCanvas("can", "", 800, 600)
    frame.Draw()

    if log:
        can.SetLogy()

    if legend:
        can.BuildLegend(0.6, 0.65, 0.9, 0.93)

    ReformatRooPlot(frame, pdf_names, data_names)
    ATLASLabel(0.20, 0.86, kind, 1, can, process)

    can.SaveAs("%s.pdf" % frame.GetName() )
#*********************************************************
def SaveFit(frame, name, obs, minx, maxx):
    can_frame = ROOT.TCanvas(name, "", 800, 600)
    frame.Draw()

    DrawFit(frame, obs, can_frame, minx, maxx)

    can_frame.SaveAs("%s.pdf" % name)
#*********************************************************
def GetFit(frame, name, obs, minx, maxx):
    can_frame = ROOT.TCanvas(name, "", 800, 600)
    ReformatRooPlot(frame)
    frame.Draw()

    DrawFit(frame, obs, can_frame, minx, maxx)

    return can_frame
#***********************************************
def save_as_txt(struct, filename):
    print("Creating %s" % filename)
    ofile=open(filename, "w")

    for line in struct:
        ofile.write("%s\n" % line)

    ofile.close()
#*********************************************************
def txt_to_set(filename):
    if not os.path.isfile(filename):
        print("File %s not found" % filename)
        exit(1)

    ifile = open(filename)
    l_lines = ifile.read().splitlines()
    s_lines = set(l_lines)

    return s_lines
#*********************************************************
def json_to_dict(filename):
    ifile=open(filename)
    json_dict=json.load(ifile)
    ifile.close()

    return json_dict
#*********************************************************
def dict_to_json(dictionary, filename):
    ofile=open(filename, "w")
    json.dump(dictionary, ofile)
    ofile.close()
#*********************************************************
