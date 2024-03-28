cd v8IsoScripts/mixVars_1516AD
rm out.txt err.txt
root -l -b -q Iso_MultiROCs_TTVA_v8_1516AD.cpp >>out.txt 2>>err.txt
root -l -b -q Iso_MultiROCs_TTVA_logAccept_v8_1516AD.cpp>>out.txt 2>>err.txt
root -l -b -q Iso_MultiVar_TTVA_v8_1516AD.cpp>>out.txt 2>>err.txt
cd ../..
