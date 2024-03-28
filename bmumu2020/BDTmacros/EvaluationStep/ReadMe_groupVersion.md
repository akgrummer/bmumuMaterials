#Contents of this folder 
/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BDT2020
├── ReadMe_groupVersion.md *This read me*
├── addClassBDT_2020_groupVersion.cpp *Code to apply BDT to nTuples*
└── out_Custom/ *This folder contains the BDT files (addClassBDT uses the .xml files)*
    ├── Set1/
    │   ├── bdt2020.root 
    │   ├── err.txt 
    │   ├── output.txt 
    │   ├── plots/
    │   │   ├── CorrelationMatrixB.eps
    │   │   ├── variables_id_c1.eps
    │   │   ├── variables_id_c2.eps
    │   │   ├── variables_id_c3.eps
    │   │   ├── *some other plotting files*
    │   └── weights/
    │       ├── bdt2020_BDT.class.C
    │       └── bdt2020_BDT.weights.xml
    ├── Set2/
    │   ├── *Same as Set1, including:*
    │   └── weights/
    │       └── bdt2020_BDT.weights.xml
    └── Set3/
        ├── *Same as Set1, including:*
        ├── bdt2020.root
        └── weights/
            └── bdt2020_BDT.weights.xml

- bdt2020.root: output root files for investigating the BDT testing and training
- err.txt: shows the percentage completed of the BDT during training 
- output.txt: contains output text info for BDT, like Variable importance and separation
- plots/: directory that contains some variable plots generated from bdt2020.root
- weights/: contains the xml files that addClassBDT_2020_groupVersion.cpp uses for applying the BDT weights (bdt2020_BDT.weights.xml) to a new file. The file bdt2020_BDT.class.C is the default TMVA generated weights application script (use the group version instead of this to apply all three BDT weights files appropriately)

#to RUN addClassBDT_2020_groupVersion.cpp:
##Setup Commands:
```
setupATLAS
lsetup "root 6.14.04-x86_64-slc6-gcc62-opt"
```
##run from directory:
```
/eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BDT2020 
``` 
##RUN with:
```
root -l -q 'addClassBDT_2020_groupVersion.cpp("/full/path/to/inputfile/in/double.quotes")'
```

output is a root file saved in the same directory as the input file
and a tag added to the output root file name \_BDT2020

This Macro applies 3 BDT weight files to create a variable called BDT_bb_2020. 
This Macro computes closeTrkDOCA_T0134217728_LooSiHi1Pt05_f2dc2 variable as: 
(double) TMath::Sqrt(pow(closeTrkDCA_T0134217728_LooSiHi1Pt05_f2dc2,2)+pow(closeTrkZCA_T0134217728_LooSiHi1Pt05_f2dc2,2));
closeTrkDOCA_T0134217728_LooSiHi1Pt05_f2dc2 will be in the output file.

The best performing isolation variables (computed using the Custom track to vertex association) are used in this BDT (along with the 12 other nominal analysis variables):
    1. "B_iso_10_noChi2_LooSiHi1Pt05_T0134217728"
    "closeTrkDCA_T0134217728_LooSiHi1Pt05_f2dc2"
    "closeTrkZCA_T0134217728_LooSiHi1Pt05_f2dc2"
    2. DCA and ZCA are used to compute (as above): closeTrkDOCA_T0134217728_LooSiHi1Pt05_f2dc2
    3. "closeTrkNtrksChi2_T0134217728_LooSiHi1Pt05_f2dc2" 
No pileup variable was used for training this BDT.

The BDT script is supposed to run on Nominal ntuples, which you can find on eos (see the Twiki: https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/BPhysRareDecaysData16MCDxAODMay2020 )
I suggest to merge the (data) files and save the merged files locally before applying the BDT. (again the output of the BDT script will save a new file in the same directroy as the input file)
