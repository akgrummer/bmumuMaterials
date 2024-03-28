TFile *myFile = new TFile("bdt2020.root", "read");
TDirectory *f2 = (TDirectory*)myFile->Get("BDToutput/2020May29/out_Nom/Set1")
f2->cd()
TestTree->Print()

mkdir BDToutput
mkdir BDToutput/2020May29
mkdir BDToutput/2020May29/out_Nom
mkdir BDToutput/2020May29/out_Nom/Set1
cd

mkdir plots
root -l -b -q -e 'TMVA::variables("BDToutput/2020May29/out_Nom/Set1","bdt2020.root","B_pT", "")'

cd ../../../../
root -l -b -q -e 'TMVA::variables("BDToutput/2020May29/out_Nom/Set1","BDToutput/2020May29/out_Nom/Set1/bdt2020.root","InputVariables_Id", "")'

root -l -b -q -e 'TMVA::variables("out_BIso_2018_MC16a","bdt2020.root","InputVariables_Id", "")'



root -l -b -q -e 'TMVA::variables("BDToutput/2020May29/out_Nom/Set1","BDToutput/2020May29/out_Nom/Set1/bdt2020.root","InputVariables_Id", "")'
root -l -b -q -e 'TMVA::variables("BDToutput/2020May29/out_Nom/Set2","BDToutput/2020May29/out_Nom/Set2/bdt2020.root","InputVariables_Id", "")'
root -l -b -q -e 'TMVA::variables("BDToutput/2020May29/out_Nom/Set3","BDToutput/2020May29/out_Nom/Set3/bdt2020.root","InputVariables_Id", "")'

root -l -b -q -e 'TMVA::variables("BDToutput/2020May29/out_Custom/Set1","BDToutput/2020May29/out_Custom/Set1/bdt2020.root","InputVariables_Id", "")'
root -l -b -q -e 'TMVA::variables("BDToutput/2020May29/out_Custom/Set2","BDToutput/2020May29/out_Custom/Set2/bdt2020.root","InputVariables_Id", "")'
root -l -b -q -e 'TMVA::variables("BDToutput/2020May29/out_Custom/Set3","BDToutput/2020May29/out_Custom/Set3/bdt2020.root","InputVariables_Id", "")'

root -l -b -q -e 'TMVA::variables("BDToutput/2020May29/out_Loose/Set1","BDToutput/2020May29/out_Loose/Set1/bdt2020.root","InputVariables_Id", "")'
root -l -b -q -e 'TMVA::variables("BDToutput/2020May29/out_Loose/Set2","BDToutput/2020May29/out_Loose/Set2/bdt2020.root","InputVariables_Id", "")'
root -l -b -q -e 'TMVA::variables("BDToutput/2020May29/out_Loose/Set3","BDToutput/2020May29/out_Loose/Set3/bdt2020.root","InputVariables_Id", "")'

root -l -b -q -e 'TMVA::variables("BDToutput/2020May29/out_Run1/Set1","BDToutput/2020May29/out_Run1/Set1/bdt2020.root","InputVariables_Id", "")'
root -l -b -q -e 'TMVA::variables("BDToutput/2020May29/out_Run1/Set2","BDToutput/2020May29/out_Run1/Set2/bdt2020.root","InputVariables_Id", "")'
root -l -b -q -e 'TMVA::variables("BDToutput/2020May29/out_Run1/Set3","BDToutput/2020May29/out_Run1/Set3/bdt2020.root","InputVariables_Id", "")'



2020July 3
run from pc01:
setupATLAS
lsetup "root 6.14.04-x86_64-slc6-gcc62-opt"
/home/agrummer/bmumu2020/BDT

mkdir BDToutput/2020Jun16/out_Nom/Set1/plots
mkdir BDToutput/2020Jun16/out_Nom/Set2/plots
mkdir BDToutput/2020Jun16/out_Nom/Set3/plots
mkdir BDToutput/2020Jun16/out_Custom/Set1/plots
mkdir BDToutput/2020Jun16/out_Custom/Set2/plots
mkdir BDToutput/2020Jun16/out_Custom/Set3/plots
mkdir BDToutput/2020Jun16/out_Loose/Set1/plots
mkdir BDToutput/2020Jun16/out_Loose/Set2/plots
mkdir BDToutput/2020Jun16/out_Loose/Set3/plots
mkdir BDToutput/2020Jun16/out_Run1/Set1/plots
mkdir BDToutput/2020Jun16/out_Run1/Set2/plots
mkdir BDToutput/2020Jun16/out_Run1/Set3/plots
mkdir BDToutput/2020Jun26/out_Run1Custom/Set1/plots
mkdir BDToutput/2020Jun26/out_Run1Custom/Set2/plots
mkdir BDToutput/2020Jun26/out_Run1Custom/Set3/plots
mkdir BDToutput/2020Jun26/out_BestSep/Set1/plots
mkdir BDToutput/2020Jun26/out_BestSep/Set2/plots
mkdir BDToutput/2020Jun26/out_BestSep/Set3/plots
mkdir BDToutput/2020Jun26/out_Run1nPV/Set1/plots
mkdir BDToutput/2020Jun26/out_Run1nPV/Set2/plots
mkdir BDToutput/2020Jun26/out_Run1nPV/Set3/plots
mkdir BDToutput/2020Jun26/out_Run1privxmu/Set1/plots
mkdir BDToutput/2020Jun26/out_Run1privxmu/Set2/plots
mkdir BDToutput/2020Jun26/out_Run1privxmu/Set3/plots

root -l -b -q -e 'TMVA::variables("BDToutput/2020Jun16/out_Nom/Set1","BDToutput/2020Jun16/out_Nom/Set1/bdt2020.root","InputVariables_Id", "")'
root -l -b -q -e 'TMVA::variables("BDToutput/2020Jun16/out_Nom/Set2","BDToutput/2020Jun16/out_Nom/Set2/bdt2020.root","InputVariables_Id", "")'
root -l -b -q -e 'TMVA::variables("BDToutput/2020Jun16/out_Nom/Set3","BDToutput/2020Jun16/out_Nom/Set3/bdt2020.root","InputVariables_Id", "")'

root -l -b -q -e 'TMVA::variables("BDToutput/2020Jun16/out_Custom/Set1","BDToutput/2020Jun16/out_Custom/Set1/bdt2020.root","InputVariables_Id", "")'
root -l -b -q -e 'TMVA::variables("BDToutput/2020Jun16/out_Custom/Set2","BDToutput/2020Jun16/out_Custom/Set2/bdt2020.root","InputVariables_Id", "")'
root -l -b -q -e 'TMVA::variables("BDToutput/2020Jun16/out_Custom/Set3","BDToutput/2020Jun16/out_Custom/Set3/bdt2020.root","InputVariables_Id", "")'

root -l -b -q -e 'TMVA::variables("BDToutput/2020Jun16/out_Loose/Set1","BDToutput/2020Jun16/out_Loose/Set1/bdt2020.root","InputVariables_Id", "")'
root -l -b -q -e 'TMVA::variables("BDToutput/2020Jun16/out_Loose/Set2","BDToutput/2020Jun16/out_Loose/Set2/bdt2020.root","InputVariables_Id", "")'
root -l -b -q -e 'TMVA::variables("BDToutput/2020Jun16/out_Loose/Set3","BDToutput/2020Jun16/out_Loose/Set3/bdt2020.root","InputVariables_Id", "")'

root -l -b -q -e 'TMVA::variables("BDToutput/2020Jun16/out_Run1/Set1","BDToutput/2020Jun16/out_Run1/Set1/bdt2020.root","InputVariables_Id", "")'
root -l -b -q -e 'TMVA::variables("BDToutput/2020Jun16/out_Run1/Set2","BDToutput/2020Jun16/out_Run1/Set2/bdt2020.root","InputVariables_Id", "")'
root -l -b -q -e 'TMVA::variables("BDToutput/2020Jun16/out_Run1/Set3","BDToutput/2020Jun16/out_Run1/Set3/bdt2020.root","InputVariables_Id", "")'


root -l -b -q -e 'TMVA::variables("BDToutput/2020Jun26/out_Run1Custom/Set1","BDToutput/2020Jun26/out_Run1Custom/Set1/bdt2020.root","InputVariables_Id", "")'
root -l -b -q -e 'TMVA::variables("BDToutput/2020Jun26/out_Run1Custom/Set2","BDToutput/2020Jun26/out_Run1Custom/Set2/bdt2020.root","InputVariables_Id", "")'
root -l -b -q -e 'TMVA::variables("BDToutput/2020Jun26/out_Run1Custom/Set3","BDToutput/2020Jun26/out_Run1Custom/Set3/bdt2020.root","InputVariables_Id", "")'

root -l -b -q -e 'TMVA::variables("BDToutput/2020Jun26/out_BestSep/Set1","BDToutput/2020Jun26/out_BestSep/Set1/bdt2020.root","InputVariables_Id", "")'
root -l -b -q -e 'TMVA::variables("BDToutput/2020Jun26/out_BestSep/Set2","BDToutput/2020Jun26/out_BestSep/Set2/bdt2020.root","InputVariables_Id", "")'
root -l -b -q -e 'TMVA::variables("BDToutput/2020Jun26/out_BestSep/Set3","BDToutput/2020Jun26/out_BestSep/Set3/bdt2020.root","InputVariables_Id", "")'

root -l -b -q -e 'TMVA::variables("BDToutput/2020Jun26/out_Run1nPV/Set1","BDToutput/2020Jun26/out_Run1nPV/Set1/bdt2020.root","InputVariables_Id", "")'
root -l -b -q -e 'TMVA::variables("BDToutput/2020Jun26/out_Run1nPV/Set2","BDToutput/2020Jun26/out_Run1nPV/Set2/bdt2020.root","InputVariables_Id", "")'
root -l -b -q -e 'TMVA::variables("BDToutput/2020Jun26/out_Run1nPV/Set3","BDToutput/2020Jun26/out_Run1nPV/Set3/bdt2020.root","InputVariables_Id", "")'

root -l -b -q -e 'TMVA::variables("BDToutput/2020Jun26/out_Run1privxmu/Set1","BDToutput/2020Jun26/out_Run1privxmu/Set1/bdt2020.root","InputVariables_Id", "")'
root -l -b -q -e 'TMVA::variables("BDToutput/2020Jun26/out_Run1privxmu/Set2","BDToutput/2020Jun26/out_Run1privxmu/Set2/bdt2020.root","InputVariables_Id", "")'
root -l -b -q -e 'TMVA::variables("BDToutput/2020Jun26/out_Run1privxmu/Set3","BDToutput/2020Jun26/out_Run1privxmu/Set3/bdt2020.root","InputVariables_Id", "")'

root -l -b -q -e 'TMVA::variables("BDToutput/2020July3/out_Run1privxmu/Set1","BDToutput/2020July3/out_Run1privxmu/Set1/bdt2020.root","InputVariables_Id", "")'



root -l -b -q -e 'TMVA::correlations("BDToutput/2020July3/out_Run1privxmu/Set1", "BDToutput/2020July3/out_Run1privxmu/Set1/bdt2020.root")'

root -l -b -q -e 'TMVA::correlations("BDToutput/2020Jun26/out_Run1Custom/Set1","BDToutput/2020Jun26/out_Run1Custom/Set1/bdt2020.root")'
root -l -b -q -e 'TMVA::correlations("BDToutput/2020Jun26/out_Run1Custom/Set2","BDToutput/2020Jun26/out_Run1Custom/Set2/bdt2020.root")'
root -l -b -q -e 'TMVA::correlations("BDToutput/2020Jun26/out_Run1Custom/Set3","BDToutput/2020Jun26/out_Run1Custom/Set3/bdt2020.root")'

root -l -b -q -e 'TMVA::correlations("BDToutput/2020Jun26/out_BestSep/Set1","BDToutput/2020Jun26/out_BestSep/Set1/bdt2020.root")'
root -l -b -q -e 'TMVA::correlations("BDToutput/2020Jun26/out_BestSep/Set2","BDToutput/2020Jun26/out_BestSep/Set2/bdt2020.root")'
root -l -b -q -e 'TMVA::correlations("BDToutput/2020Jun26/out_BestSep/Set3","BDToutput/2020Jun26/out_BestSep/Set3/bdt2020.root")'

root -l -b -q -e 'TMVA::correlations("BDToutput/2020Jun26/out_Run1nPV/Set1","BDToutput/2020Jun26/out_Run1nPV/Set1/bdt2020.root")'
root -l -b -q -e 'TMVA::correlations("BDToutput/2020Jun26/out_Run1nPV/Set2","BDToutput/2020Jun26/out_Run1nPV/Set2/bdt2020.root")'
root -l -b -q -e 'TMVA::correlations("BDToutput/2020Jun26/out_Run1nPV/Set3","BDToutput/2020Jun26/out_Run1nPV/Set3/bdt2020.root")'

root -l -b -q -e 'TMVA::correlations("BDToutput/2020Jun26/out_Run1privxmu/Set1","BDToutput/2020Jun26/out_Run1privxmu/Set1/bdt2020.root")'
root -l -b -q -e 'TMVA::correlations("BDToutput/2020Jun26/out_Run1privxmu/Set2","BDToutput/2020Jun26/out_Run1privxmu/Set2/bdt2020.root")'
root -l -b -q -e 'TMVA::correlations("BDToutput/2020Jun26/out_Run1privxmu/Set3","BDToutput/2020Jun26/out_Run1privxmu/Set3/bdt2020.root")'



root -l -b -q -e 'TMVA::correlations("BDToutput/2020Jun16/out_Nom/Set1","BDToutput/2020Jun16/out_Nom/Set1/bdt2020.root")'
root -l -b -q -e 'TMVA::correlations("BDToutput/2020Jun16/out_Nom/Set2","BDToutput/2020Jun16/out_Nom/Set2/bdt2020.root")'
root -l -b -q -e 'TMVA::correlations("BDToutput/2020Jun16/out_Nom/Set3","BDToutput/2020Jun16/out_Nom/Set3/bdt2020.root")'

root -l -b -q -e 'TMVA::correlations("BDToutput/2020Jun16/out_Custom/Set1","BDToutput/2020Jun16/out_Custom/Set1/bdt2020.root")'
root -l -b -q -e 'TMVA::correlations("BDToutput/2020Jun16/out_Custom/Set2","BDToutput/2020Jun16/out_Custom/Set2/bdt2020.root")'
root -l -b -q -e 'TMVA::correlations("BDToutput/2020Jun16/out_Custom/Set3","BDToutput/2020Jun16/out_Custom/Set3/bdt2020.root")'

root -l -b -q -e 'TMVA::correlations("BDToutput/2020Jun16/out_Loose/Set1","BDToutput/2020Jun16/out_Loose/Set1/bdt2020.root")'
root -l -b -q -e 'TMVA::correlations("BDToutput/2020Jun16/out_Loose/Set2","BDToutput/2020Jun16/out_Loose/Set2/bdt2020.root")'
root -l -b -q -e 'TMVA::correlations("BDToutput/2020Jun16/out_Loose/Set3","BDToutput/2020Jun16/out_Loose/Set3/bdt2020.root")'

root -l -b -q -e 'TMVA::correlations("BDToutput/2020Jun16/out_Run1/Set1","BDToutput/2020Jun16/out_Run1/Set1/bdt2020.root")'
root -l -b -q -e 'TMVA::correlations("BDToutput/2020Jun16/out_Run1/Set2","BDToutput/2020Jun16/out_Run1/Set2/bdt2020.root")'
root -l -b -q -e 'TMVA::correlations("BDToutput/2020Jun16/out_Run1/Set3","BDToutput/2020Jun16/out_Run1/Set3/bdt2020.root")'



root -l -b -q 'Aidans_Correlations("BDToutput/2020Jun16/out_Run1/Set1","BDToutput/2020Jun16/out_Run1/Set1/bdt2020.root")'


out_Run1privxmu_round
out_Run1nPV_npvweights
root -l -b -q -e 'TMVA::variables("BDToutput/2020July16/out_Run1privxmu_round/Set1","BDToutput/2020July16/out_Run1privxmu_round/Set1/bdt2020.root","InputVariables_Id", "")'
root -l -b -q -e 'TMVA::variables("BDToutput/2020July16/out_Run1nPV_npvweights/Set1","BDToutput/2020July16/out_Run1nPV_npvweights/Set1/bdt2020.root","InputVariables_Id", "")'
root -l -b -q -e 'TMVA::variables("BDToutput/2020July16/out_ALLvars/Set1","BDToutput/2020July16/out_ALLvars/Set1/bdt2020.root","InputVariables_Id", "")'

out_ALLvars
out_ALLvars_npvweights
root -l -q 'Aidans_Correlations()'



#2020 July 22:
setupATLAS
lsetup "root 6.14.04-x86_64-slc6-gcc62-opt"
running BDT with
as in Run 1 B Iso, as in Run 2 close track vars, nominal 15 vars
and applying npv weights 
Saving in to 2020July22 folder in BDT output:
/home/agrummer/bmumu2020/BDT/BDToutput

this will allow comparison to the 


#2020 Aug 6:
setupATLAS
lsetup "root 6.14.04-x86_64-slc6-gcc62-opt"
running CUSTOM TVA BDTs with PU vars
Saving in to 2020Aug6 folder in BDT output:
/home/agrummer/bmumu2020/BDT/BDToutput

nominal 15 input vars + one pileup var (either npv or privx_mu round)
3 

Custom_privxmu
Custom_nPV

root -l -b -q -e 'TMVA::variables("BDToutput/2020Aug6/Custom_privxmu/Set1","BDToutput/2020Aug6/Custom_privxmu/Set1/bdt2020.root","InputVariables_Id", "")'
root -l -b -q -e 'TMVA::variables("BDToutput/2020Aug6/Custom_privxmu/Set2","BDToutput/2020Aug6/Custom_privxmu/Set2/bdt2020.root","InputVariables_Id", "")'
root -l -b -q -e 'TMVA::variables("BDToutput/2020Aug6/Custom_privxmu/Set3","BDToutput/2020Aug6/Custom_privxmu/Set3/bdt2020.root","InputVariables_Id", "")'

root -l -b -q -e 'TMVA::variables("BDToutput/2020Aug6/Custom_nPV/Set1","BDToutput/2020Aug6/Custom_nPV/Set1/bdt2020.root","InputVariables_Id", "")'
root -l -b -q -e 'TMVA::variables("BDToutput/2020Aug6/Custom_nPV/Set2","BDToutput/2020Aug6/Custom_nPV/Set2/bdt2020.root","InputVariables_Id", "")'
root -l -b -q -e 'TMVA::variables("BDToutput/2020Aug6/Custom_nPV/Set3","BDToutput/2020Aug6/Custom_nPV/Set3/bdt2020.root","InputVariables_Id", "")'


