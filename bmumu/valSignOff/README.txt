README.txt
final validation of the example files produced by Wolfgang and provided by Mazuza (see evernote notes)
the folder for the branch names of the various files is www/bmumu/valSignOff

The MC and Data plots for various variables was porduced in 
/Users/agrummer/cernbox/www/bmumu/myMVA/myMVApc01.sublime-workspace
the plots were produced using the TMVA::Variables.C code after running the BDT 
This command in is the notes in the sublime workspace.

the Bmass plots were produced with the "ExamplePlot.cpp" code in www/bmumu/valSignOff
the code was run with root -l ~/www/bmumu/valSignOff/ExamplePlot.cpp (actually from bmumu dir, but should work the same) 
The root - l command was executed on lxplus from the ~/AtlasStyle folder.



April 16 (round 2):
mc:
nmucalc: 3175 nvtx: 3175
nvtxSigMUCALC: 4827 nvtxSigVTX: 4676 nvtxSigBOTH: 4440
dcaACK: 12 dcaBEL: 2 dcaBGL: 4
Total: 3175

data:
nmucalc: 211 nvtx: 211
nvtxSigMUCALC: 23 nvtxSigVTX: 27 nvtxSigBOTH: 10
dcaACK: 0 dcaBEL: 0 dcaBGL: 0
Total: 251

2nd round of validation - 
BranchNamesMacro.sublime-workspace
ran the TMVA in myMVA
MassPlot.sublime-workspace
    - includes mass plot from Example file
    - and the B_cIDtrk comparisons 
    - and checked B_cIDtrk_trkidx==-1 numbers
also made plot of PV weights, muon reco weights, BIso, and ct plots: 
/Users/agrummer/cernbox/www/bmumu/AnalysisTools/Examples/alltrksExample/PlottingExamples.sublime-workspace



bplus 
data:
nmucalc: 2391 nvtx: 2391
nvtxSigMUCALC: 651 nvtxSigVTX: 649 nvtxSigBOTH: 557
dcaACK: 3 dcaBEL: 0 dcaBGL: 0
Total: 2391

mc:
nmucalc: 6390 nvtx: 6390
nvtxSigMUCALC: 4476 nvtxSigVTX: 4823 nvtxSigBOTH: 4360
dcaACK: 35 dcaBEL: 9 dcaBGL: 16
Total: 6390
