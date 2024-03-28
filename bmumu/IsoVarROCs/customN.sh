cd v8IsoScriptsIntersect/mixVars_customN
rm out.txt err.txt
root -l -b -q NcloseTracks_logAccept_ROCs_v8_customN.cpp  >>out.txt 2>>err.txt
root -l -b -q DOCA_logAccept_ROCs_v8_customN.cpp  >>out.txt 2>>err.txt
root -l -b -q NcloseTracks_MultiROCs_TTVA_v8_customN.cpp  >>out.txt 2>>err.txt
root -l -b -q DOCA_MultiROCs_TTVA_v8_customN.cpp  >>out.txt 2>>err.txt
root -l -b -q Iso_MultiROCs_TTVA_v8_customN.cpp  >>out.txt 2>>err.txt
root -l -b -q Iso_MultiROCs_TTVA_logAccept_v8_customN.cpp  >>out.txt 2>>err.txt

root -l -b -q Iso_MultiVar_TTVA_v8_customN.cpp  >>out.txt 2>>err.txt
root -l -b -q OtherIso_MultiVar_TTVA_v8_customN.cpp  >>out.txt 2>>err.txt
root -l -b -q Iso_MultiVar_TTVA_v8_customN_noI.cpp  >>out.txt 2>>err.txt
root -l -b -q OtherIso_MultiVar_TTVA_v8_customN_noI.cpp  >>out.txt 2>>err.txt
cd ../..
