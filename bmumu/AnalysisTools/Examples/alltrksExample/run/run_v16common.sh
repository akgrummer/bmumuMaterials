echo "Starting _v16common"
bin/IsolationStudy_v16common 2016 >>output/out2016_v16common.txt 2>>output/err2016_v16common.txt
echo "finished _v16common 2016"
bin/IsolationStudy_v16common 2017 >>output/out2017_v16common.txt 2>>output/err2017_v16common.txt
echo "finished _v16common 2017"
bin/IsolationStudy_v16common 2018 >>output/out2018_v16common.txt 2>>output/err2018_v16common.txt
echo "finished _v16common 2018"
bin/IsolationStudy_v16common MC16a >>output/outMC16a_v16common.txt 2>>output/errMC16a_v16common.txt
echo "finished _v16common MC16a"
bin/IsolationStudy_v16common MC16d >>output/outMC16d_v16common.txt 2>>output/errMC16d_v16common.txt
echo "finished _v16common MC16d"
bin/IsolationStudy_v16common MC16e >>output/outMC16e_v16common.txt 2>>output/errMC16e_v16common.txt
echo "finished _v16common MC16e, all done _v16common"

cat output/out2016_v16common.txt | grep -e "error" -e "Error" -e "ERROR"
cat output/err2016_v16common.txt | grep -e "error" -e "Error" -e "ERROR"
cat output/out2017_v16common.txt | grep -e "error" -e "Error" -e "ERROR"
cat output/err2017_v16common.txt | grep -e "error" -e "Error" -e "ERROR"
cat output/out2018_v16common.txt | grep -e "error" -e "Error" -e "ERROR"
cat output/err2018_v16common.txt | grep -e "error" -e "Error" -e "ERROR"
cat output/outMC16a_v16common.txt | grep -e "error" -e "Error" -e "ERROR"
cat output/errMC16a_v16common.txt | grep -e "error" -e "Error" -e "ERROR"
cat output/outMC16d_v16common.txt | grep -e "error" -e "Error" -e "ERROR"
cat output/errMC16d_v16common.txt | grep -e "error" -e "Error" -e "ERROR"
cat output/outMC16e_v16common.txt | grep -e "error" -e "Error" -e "ERROR"
cat output/errMC16e_v16common.txt | grep -e "error" -e "Error" -e "ERROR"
