cd v8IsoScriptsIntersect/mixVars_looseN
rm out.txt err.txt
root -l -b -q NcloseTracks_logAccept_ROCs_v8_looseN.cpp  >>out.txt 2>>err.txt
root -l -b -q DOCA_logAccept_ROCs_v8_looseN.cpp  >>out.txt 2>>err.txt
root -l -b -q NcloseTracks_MultiROCs_TTVA_v8_looseN.cpp  >>out.txt 2>>err.txt
root -l -b -q DOCA_MultiROCs_TTVA_v8_looseN.cpp  >>out.txt 2>>err.txt
root -l -b -q Iso_MultiROCs_TTVA_v8_looseN.cpp  >>out.txt 2>>err.txt
root -l -b -q Iso_MultiROCs_TTVA_logAccept_v8_looseN.cpp  >>out.txt 2>>err.txt

root -l -b -q Iso_MultiVar_TTVA_v8_looseN.cpp  >>out.txt 2>>err.txt
root -l -b -q OtherIso_MultiVar_TTVA_v8_looseN.cpp  >>out.txt 2>>err.txt
cd ../..
