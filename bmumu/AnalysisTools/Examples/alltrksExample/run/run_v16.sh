echo "Starting _v16"
bin/IsolationStudy_v16 2016 >>output/out2016_v16.txt 2>>output/err2016_v16.txt
echo "finished _v16 2016"
bin/IsolationStudy_v16 2017 >>output/out2017_v16.txt 2>>output/err2017_v16.txt
echo "finished _v16 2017"
bin/IsolationStudy_v16 2018 >>output/out2018_v16.txt 2>>output/err2018_v16.txt
echo "finished _v16 2018"
bin/IsolationStudy_v16 MC16a >>output/outMC16a_v16.txt 2>>output/errMC16a_v16.txt
echo "finished _v16 MC16a"
bin/IsolationStudy_v16 MC16d >>output/outMC16d_v16.txt 2>>output/errMC16d_v16.txt
echo "finished _v16 MC16d"
bin/IsolationStudy_v16 MC16e >>output/outMC16e_v16.txt 2>>output/errMC16e_v16.txt
echo "finished _v16 MC16e, all done _v16"

cat output/out2016_v16.txt | grep -e "error" -e "Error" -e "ERROR"
cat output/err2016_v16.txt | grep -e "error" -e "Error" -e "ERROR"
cat output/out2017_v16.txt | grep -e "error" -e "Error" -e "ERROR"
cat output/err2017_v16.txt | grep -e "error" -e "Error" -e "ERROR"
cat output/out2018_v16.txt | grep -e "error" -e "Error" -e "ERROR"
cat output/err2018_v16.txt | grep -e "error" -e "Error" -e "ERROR"
cat output/outMC16a_v16.txt | grep -e "error" -e "Error" -e "ERROR"
cat output/errMC16a_v16.txt | grep -e "error" -e "Error" -e "ERROR"
cat output/outMC16d_v16.txt | grep -e "error" -e "Error" -e "ERROR"
cat output/errMC16d_v16.txt | grep -e "error" -e "Error" -e "ERROR"
cat output/outMC16e_v16.txt | grep -e "error" -e "Error" -e "ERROR"
cat output/errMC16e_v16.txt | grep -e "error" -e "Error" -e "ERROR"
