cd v8IsoScripts/newVarCompsMuM
# rm out.txt err.txt
root -l -b -q muM_Iso_MultiROCs_TTVA_v8_newVars.cpp  >>out.txt 2>>err.txt
root -l -b -q muM_Iso_MultiROCs_TTVA_logAccept_v8_newVars.cpp  >>out.txt 2>>err.txt

root -l -b -q muM_Iso_MultiVar_TTVA_v8_newVars.cpp  >>out.txt 2>>err.txt
cd ../..
