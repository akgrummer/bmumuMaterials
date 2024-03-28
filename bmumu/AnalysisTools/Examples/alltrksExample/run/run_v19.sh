echo "Starting _v19"
bin/IsolationStudy_v19 2016 >>output_2020Mar16/out2016_v19.txt 2>>output_2020Mar16/err2016_v19.txt
echo "finished _v19 2016"
bin/IsolationStudy_v19 2017 >>output_2020Mar16/out2017_v19.txt 2>>output_2020Mar16/err2017_v19.txt
echo "finished _v19 2017"
bin/IsolationStudy_v19 2018 >>output_2020Mar16/out2018_v19.txt 2>>output_2020Mar16/err2018_v19.txt
echo "finished _v19 2018"
# bin/IsolationStudy_v19 MC16a >>output_2020Mar16/outMC16a_v19.txt 2>>output_2020Mar16/errMC16a_v19.txt
# echo "finished _v19 MC16a"
# bin/IsolationStudy_v19 MC16d >>output_2020Mar16/outMC16d_v19.txt 2>>output_2020Mar16/errMC16d_v19.txt
# echo "finished _v19 MC16d"
# bin/IsolationStudy_v19 MC16e >>output_2020Mar16/outMC16e_v19.txt 2>>output_2020Mar16/errMC16e_v19.txt
# echo "finished _v19 MC16e, all done _v19"

cat output_2020Mar16/out2016_v19.txt | grep -e "error" -e "Error" -e "ERROR"
cat output_2020Mar16/err2016_v19.txt | grep -e "error" -e "Error" -e "ERROR"
cat output_2020Mar16/out2017_v19.txt | grep -e "error" -e "Error" -e "ERROR"
cat output_2020Mar16/err2017_v19.txt | grep -e "error" -e "Error" -e "ERROR"
cat output_2020Mar16/out2018_v19.txt | grep -e "error" -e "Error" -e "ERROR"
cat output_2020Mar16/err2018_v19.txt | grep -e "error" -e "Error" -e "ERROR"
# cat output_2020Mar16/outMC16a_v19.txt | grep -e "error" -e "Error" -e "ERROR"
# cat output_2020Mar16/errMC16a_v19.txt | grep -e "error" -e "Error" -e "ERROR"
# cat output_2020Mar16/outMC16d_v19.txt | grep -e "error" -e "Error" -e "ERROR"
# cat output_2020Mar16/errMC16d_v19.txt | grep -e "error" -e "Error" -e "ERROR"
# cat output_2020Mar16/outMC16e_v19.txt | grep -e "error" -e "Error" -e "ERROR"
# cat output_2020Mar16/errMC16e_v19.txt | grep -e "error" -e "Error" -e "ERROR"
