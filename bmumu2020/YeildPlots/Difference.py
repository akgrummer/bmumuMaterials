# import pandas as pd
# from pandas.io.json import json_normalize
# import ROOT
# from ROOT import TFile, TCanvas, gROOT, gDirectory, TBrowser
# from ROOT import TGraphErrors
# import numpy as np
# from numpy.random import randn
# import collections

EventNumbers = [4735, 41112, 27571, 65512, 22935, 133513, 51896, 126956, 209209, 340051, 125663, 216609, 220670, 341157, 149914, 348265]
EventNumbers2020 = [4799, 41620, 27893, 66281, 23187, 135123, 52663, 130136, 211752, 343879, 126915, 219151, 223655, 345202, 151681, 351639]

for i in range(len(EventNumbers)):
    print(EventNumbers[i]/EventNumbers2020[i])