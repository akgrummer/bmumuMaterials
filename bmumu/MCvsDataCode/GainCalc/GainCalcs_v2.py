#This file creates a dataframe of with lumi, event numbers and gain values and then
#sends that data to a .C file (MakeATGraph.C) to be plotted in root (with Atlas style (hopefully all of the style)
#uses input data files for event numbers from Feb 2018
import pandas as pd
from pandas.io.json import json_normalize
import ROOT
from ROOT import TFile, TCanvas, gROOT, gDirectory, TBrowser
from ROOT import TGraphErrors
import numpy as np
from numpy.random import randn
import collections
gROOT.LoadMacro( "/Users/agrummer/cernbox/www/bmumu/MCvsDataCode/GainCalc/MakeATGraph.C" )
## get MyClass from ROOT
from ROOT import MakeATGraph

# fdnamePeriods = "/afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/LASTskimFeb13/LASTskim.Data_2015HLTand2016HLTLxy_Main_15Feb_SepPeriods.root";

d = {}
dict.fromkeys([1, 2, 3, 4])

d["2015Periods"] = dict.fromkeys({"D", "E", "F", "G", "H", "J"})
d["2016Periods"] = dict.fromkeys(["A", "B", "C", "D", "E", "F", "G", "I", "K", "L"])
CorrectedLumi = []
# EventNumbers = [4870, 42368, 28414, 67497, 23678, 137629, 53427, 130471, 215359, 349917, 129429, 222993, 227043, 351102, 154110, 357921]
#numbers from /afs/cern.ch/user/a/agrummer/WorkSpace/BsmumuData/SidebandTrained/data1516Bs_SepPeriods.root
# created with SeparatePeriods_v3.C in MCvsDataCode
EventNumbers = [4735, 41112, 27571, 65512, 22935, 133513, 51896, 126956, 209209, 340051, 125663, 216609, 220670, 341157, 149914, 348265]
# myfile = TFile(fdnamePeriods)
for Year in d:
  dfNew = pd.read_csv("/Users/agrummer/cernbox/www/bmumu/MCvsDataCode/GainCalc/Triggers/BphysTriggers"+Year[:4]+".csv", index_col=0)
  for Period in d[Year]:
    df = pd.read_csv("./LumiPerPeriod/"+Year[:4]+"_"+Period+"_Ar"+".csv", index_col=0)

    # myTree = gROOT.FindObject("T_mv_"+Year[:4]+Period) #Darn, need to get python libraries on lxplus!
    d[Year][Period] = dict.fromkeys([" LAr Corrected", " LRecorded", "Events", "Gain", "NewLumi"])
    if Period =="D" and "2015" in Year: #perid D is in nano barns everything else is in petabarns
        d[Year][Period][" LAr Corrected"] = df.loc["Total"][" LAr Corrected"]/1000
    else:
        d[Year][Period][" LAr Corrected"] = df.loc["Total"][" LAr Corrected"]
    if "2015" in Year:
        d[Year][Period]["NewLumi"] = float(dfNew.loc["HLT_mu6_mu4_bBmumu"][Period])
        # print(d[Year][Period]["NewLumi"])
    elif "2016" in Year and "K" not in Period:
        d[Year][Period]["NewLumi"] = float(dfNew.loc["HLT_mu6_mu4_bBmumu_Lxy0"][Period])
        # print(d[Year][Period]["NewLumi"])
    d[Year][Period][" LRecorded"] = df.loc["Total"][" LRecorded"]
    # d[Year][Period]["Events"] = myTree.GetEntries() #Darn, need to get python libraries on lxplus!
    # d[Year][Period]["Gain"] = d[Year][Period][" LAr Corrected"]/d[Year][Period]["Events"]

# dfNew was used for a cross check
dfNew = pd.read_csv("/Users/agrummer/cernbox/www/bmumu/MCvsDataCode/GainCalc/Triggers/BphysTriggers"+"2016"+".csv", index_col=0)
d["2016Periods"]["K"]["NewLumi"] = float(dfNew.loc["HLT_mu6_mu4_bBmumu_Lxy0"]["H"])
# result is made with the dataframe d which comes from ./LumiPerPeriod/ files
result = pd.DataFrame.from_dict({(i,j): d[i][j] 
                                  for i in d.keys() 
                                  for j in d[i].keys()},
                                  orient="index")

result = result.reindex(["2015Periods", "2016Periods"], level=0)
result.to_csv('GainTableFeb2018.csv')#, index=None)


Year = list(result.index.get_level_values(0))#access the different index values
Period = list(result.index.get_level_values(1))
NumOfPeriodsList = []
NumOfPoints = []
for i in range(len(Period)):
  NumOfPoints.append(i)
  if Year[i] != Year[i-1]:
    NumOfPeriodsList.append(i)


NumOfPeriodsList.append(len(Year))
NumOfPeriodsList = np.asarray(NumOfPeriodsList)
Year = np.asarray(Year)
Period = np.asarray(Period)
NumOfPoints = np.asarray(NumOfPoints, dtype="d", order="C")
NumOfPoints = NumOfPoints + 1
Gain = list(result["Gain"])
# empty list
Gain = np.asarray(Gain, dtype="d", order="C")
# print("Gain1")
# print(Gain)
# print(NumOfPeriodsList)

PreScaleCorrected = list(result[" LAr Corrected"])
PreScaleCorrected = np.asarray(PreScaleCorrected, dtype="d", order="C")
PreScaleCorrected = np.divide(PreScaleCorrected, 1000)# convert pb to fb
EventNumbers = np.asarray(EventNumbers, dtype="d", order="C")
SumLumi = np.cumsum(PreScaleCorrected)
Gain = np.divide(EventNumbers, PreScaleCorrected)
# print("Gain2")
# print(Gain)

# NewLumi = np.nan_to_num(NewLumi)
# NewLumi comes from dfNew which is from the B group excel luminosity summary 
#       was used for a cross check
NewLumi = list(result["NewLumi"])
NewLumi = np.asarray(NewLumi, dtype="d", order="C")
SumLumi2 = np.cumsum(NewLumi)
NewLumi_pb = np.multiply(NewLumi, 1000)
# Gain2 = np.divide(EventNumbers, NewLumi_pb)
EventsError = np.power(EventNumbers, 1/2)
# LumiError = np.multiply(PreScaleCorrected, 0.021/1000)#2.1% and /1000 for converting to fb
LumiError = np.multiply(PreScaleCorrected, 0.021)#2.1% 
# Error = np.divide(EventsError,LumiError)
# Error = np.sqrt(np.square(np.divide(EventsError,EventNumbers)) + np.square(np.divide(LumiError,PreScaleCorrected)))
FirstCompQuad = np.square(np.divide(EventsError,EventNumbers))
SecondCompQuad = np.square(np.divide(LumiError,PreScaleCorrected))
# percentError = np.sqrt(np.square(np.divide(EventsError,EventNumbers)) + np.square(np.divide(LumiError,PreScaleCorrected)))
percentError = np.sqrt(FirstCompQuad + SecondCompQuad)
Error = np.multiply(np.sqrt(np.square(np.divide(EventsError,EventNumbers)) + np.square(np.divide(LumiError,PreScaleCorrected))), Gain)


print("EventsError")
print(EventsError)
print("LumiError")
print(LumiError)
print("Error")
print(Error)
print("FirstCompQuad")
print(FirstCompQuad)
print("SecondCompQuad")
print(SecondCompQuad)
print("percentError")
print(percentError)


print("EventNumbers")
print(EventNumbers)
print("PreScaleCorrected")
print(PreScaleCorrected)
# print(NumOfPoints)
# print(Gain)
# print(PreScaleCorrected)
# print(EventNumbers)

# print(len(NumOfPoints))
# print(result)

# result = result.reset_index()
# Periods = list(result.level_1.values)
# Periods = np.asarray(Periods, dtype="str", order="C")

# MakeATGraph = MakeATGraph()
# MakeATGraph.SetAtlasStyle()
# # MakeATGraph.MakeTheGraph(int(16), NumOfPoints, Gain*1000, SumLumi/1000, Error, SumLumi2)
# # MakeATGraph.MakeTheGraph(int(16), NumOfPoints, Gain*1000, SumLumi/1000, EventsError, SumLumi2)
# # MakeATGraph.MakeTheGraph(int(16), NumOfPoints, Gain, SumLumi, EventsError, SumLumi2)
# MakeATGraph.MakeTheGraph(int(16), NumOfPoints, Gain, SumLumi, Error, SumLumi2)
# #Gain *1000 to convert to fb-1
# #SumLumi/1000 to convert lumi to fb-1
input("Press Enter to continue...")

