cd v8IsoScriptsIntersect/mixVars_1516AN
rm out.txt err.txt
root -l -b -q Iso_MultiROCs_TTVA_v8_1516AN.cpp  >>out.txt 2>>err.txt
root -l -b -q Iso_MultiROCs_TTVA_logAccept_v8_1516AN.cpp  >>out.txt 2>>err.txt
root -l -b -q Iso_MultiVar_TTVA_v8_1516AN.cpp  >>out.txt 2>>err.txt
cd ../..
