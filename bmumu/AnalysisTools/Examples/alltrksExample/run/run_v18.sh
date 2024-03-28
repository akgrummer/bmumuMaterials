echo "Starting _v18"
bin/IsolationStudy_v18 2016 >>output_2020Mar16/out2016_v18.txt 2>>output_2020Mar16/err2016_v18.txt
echo "finished _v18 2016"
bin/IsolationStudy_v18 2017 >>output_2020Mar16/out2017_v18.txt 2>>output_2020Mar16/err2017_v18.txt
echo "finished _v18 2017"
bin/IsolationStudy_v18 2018 >>output_2020Mar16/out2018_v18.txt 2>>output_2020Mar16/err2018_v18.txt
echo "finished _v18 2018"
# bin/IsolationStudy_v18 MC16a >>output_2020Mar16/outMC16a_v18.txt 2>>output_2020Mar16/errMC16a_v18.txt
# echo "finished _v18 MC16a"
# bin/IsolationStudy_v18 MC16d >>output_2020Mar16/outMC16d_v18.txt 2>>output_2020Mar16/errMC16d_v18.txt
# echo "finished _v18 MC16d"
# bin/IsolationStudy_v18 MC16e >>output_2020Mar16/outMC16e_v18.txt 2>>output_2020Mar16/errMC16e_v18.txt
# echo "finished _v18 MC16e, all done _v18"

cat output_2020Mar16/out2016_v18.txt | grep -e "error" -e "Error" -e "ERROR"
cat output_2020Mar16/err2016_v18.txt | grep -e "error" -e "Error" -e "ERROR"
cat output_2020Mar16/out2017_v18.txt | grep -e "error" -e "Error" -e "ERROR"
cat output_2020Mar16/err2017_v18.txt | grep -e "error" -e "Error" -e "ERROR"
cat output_2020Mar16/out2018_v18.txt | grep -e "error" -e "Error" -e "ERROR"
cat output_2020Mar16/err2018_v18.txt | grep -e "error" -e "Error" -e "ERROR"
# cat output_2020Mar16/outMC16a_v18.txt | grep -e "error" -e "Error" -e "ERROR"
# cat output_2020Mar16/errMC16a_v18.txt | grep -e "error" -e "Error" -e "ERROR"
# cat output_2020Mar16/outMC16d_v18.txt | grep -e "error" -e "Error" -e "ERROR"
# cat output_2020Mar16/errMC16d_v18.txt | grep -e "error" -e "Error" -e "ERROR"
# cat output_2020Mar16/outMC16e_v18.txt | grep -e "error" -e "Error" -e "ERROR"
# cat output_2020Mar16/errMC16e_v18.txt | grep -e "error" -e "Error" -e "ERROR"
