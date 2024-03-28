cd v8IsoScripts/oldVars_v7_repeated
rm out.txt err.txt
root -l -b -q NcloseTracks_logAccept_ROCs_v7_2.cpp  >>out.txt 2>>err.txt
root -l -b -q DOCA_logAccept_ROCs_v7_2.cpp  >>out.txt 2>>err.txt
root -l -b -q NcloseTracks_MultiROCs_TTVA_v7_2.cpp  >>out.txt 2>>err.txt
root -l -b -q DOCA_MultiROCs_TTVA_v7_2.cpp  >>out.txt 2>>err.txt
root -l -b -q Iso_MultiROCs_TTVA_v7_2.cpp  >>out.txt 2>>err.txt
root -l -b -q Iso_MultiROCs_TTVA_logAccept_v7_2.cpp  >>out.txt 2>>err.txt

root -l -b -q Iso_MultiVar_TTVA_v7_PU_2.cpp  >>out.txt 2>>err.txt
root -l -b -q OtherIso_MultiVar_TTVA_v7_PU_2.cpp  >>out.txt 2>>err.txt
cd ../..
