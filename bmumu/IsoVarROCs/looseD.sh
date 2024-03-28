cd v8IsoScripts/mixVars_looseD
rm out.txt err.txt
root -l -b -q NcloseTracks_logAccept_ROCs_v8_looseD.cpp  >>out.txt 2>>err.txt
# root -l -b -q DOCA_logAccept_ROCs_v8_looseD.cpp  >>out.txt 2>>err.txt
root -l -b -q NcloseTracks_MultiROCs_TTVA_v8_looseD.cpp  >>out.txt 2>>err.txt
# root -l -b -q DOCA_MultiROCs_TTVA_v8_looseD.cpp  >>out.txt 2>>err.txt
root -l -b -q Iso_MultiROCs_TTVA_v8_looseD.cpp  >>out.txt 2>>err.txt
root -l -b -q Iso_MultiROCs_TTVA_logAccept_v8_looseD.cpp  >>out.txt 2>>err.txt

root -l -b -q Iso_MultiVar_TTVA_v8_looseD.cpp  >>out.txt 2>>err.txt
root -l -b -q OtherIso_MultiVar_TTVA_v8_looseD.cpp  >>out.txt 2>>err.txt
cd ../..

cd v8IsoScripts/mixVars_looseD1
rm out.txt err.txt
root -l -b -q DOCA_logAccept_ROCs_v8_looseD1.cpp  >>out.txt 2>>err.txt
root -l -b -q DOCA_MultiROCs_TTVA_v8_looseD1.cpp  >>out.txt 2>>err.txt
root -l -b -q OtherIso_MultiVar_TTVA_v8_looseD1.cpp  >>out.txt 2>>err.txt
cd ../..

cd v8IsoScripts/mixVars_looseD2
rm out.txt err.txt
root -l -b -q DOCA_logAccept_ROCs_v8_looseD2.cpp  >>out.txt 2>>err.txt
root -l -b -q DOCA_MultiROCs_TTVA_v8_looseD2.cpp  >>out.txt 2>>err.txt
root -l -b -q OtherIso_MultiVar_TTVA_v8_looseD2.cpp  >>out.txt 2>>err.txt
cd ../..
