
setupATLAS
lsetup "root 6.14.04-x86_64-slc6-gcc62-opt"

have to compile first with
g++ BranchNamesMacro_withType.cpp -o BranchNamesMacro_withType `root-config --glibs --cflags`
g++ BranchNamesMacro_withType_Tmv.cpp -o BranchNamesMacro_withType_Tmv `root-config --glibs --cflags`

Run with:

./BranchNamesMacro_withType /eos/home-a/agrummer/BsmumuData/AnalysisNtuples2020/v4/data15main.root

./BranchNamesMacro_withType /eos/home-a/agrummer/BsmumuData/AnalysisNtuples2020/v4/LASTskim.user.agrummer.Data1516.merged.root

./BranchNamesMacro_withType /eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/Nominal_NTUP_MC/bbmumuX/v4/user.mghneima.300307.BPHY8.TNTUP.e6179_a875_r9364_p4143.Bmumu/LASTskim.output_2688664.root


./BranchNamesMacro_withType /eos/home-a/agrummer/BsmumuData/AnalysisNtuples2020/v4/LASTskim.user.agrummer.mcBsmumu.merged.root

./BranchNamesMacro_withType /eos/home-a/agrummer/BsmumuData/AnalysisNtuples2020/v4/LASTskim.user.agrummer.bbmumuX.merged.root


./BranchNamesMacro_withType_Tmv /eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/AnalysisNtuples/Bsmumu/mc16a/v3/LASTskim.mc16Bs_BDT2016_v2.root

./BranchNamesMacro_withType_Tmv /eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/AnalysisNtuples/Bsmumu/data15a16/v3/data1516Bs_BDT2016_v2.root

./BranchNamesMacro_withType_Tmv /eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/AnalysisNtuples/bbmumuXBs/v2/LASTskim.bbmumuX2Bsmumu_combinatorial_testweight.root






./BranchNamesMacro_withType_Tmv /eos/home-a/agrummer/BsmumuData/AnalysisNtuples2020/v4/LASTskim.user.agrummer.Data1516.merged.root

./BranchNamesMacro_withType_Tmv /eos/home-a/agrummer/BsmumuData/AnalysisNtuples2020/v4/LASTskim.user.agrummer.mcBsmumu.merged.root

./BranchNamesMacro_withType_Tmv /eos/home-a/agrummer/BsmumuData/AnalysisNtuples2020/v4/LASTskim.user.agrummer.bbmumuX.merged.root

MC from Mazuza:

./BranchNamesMacro_withType_Tmv /eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/Nominal_NTUP_MC/Bsmumu/v4/user.mghneima.300426.BPHY8.NTUP.e4889_a875_r9364_p4143.Bmumu/merged/merged.root

Data from Mazuza:

./BranchNamesMacro_withType_Tmv /eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun2/BsMuMuVal2020/Nominal_NTUP_data/data16_Main/v4/user.mghneima.data16_13TeV.periodA.physics_Main.BPHY8.NTUP.grp16_v01_p4144_Bmumu/LASTskim.user.mghneima.21225363.Bmumu._000001.root


./ScanTree /eos/home-a/agrummer/BsmumuData/AnalysisNtuples2020/v4/LASTskim.user.agrummer.mcBsmumu.merged.root > /afs/cern.ch/user/a/agrummer/www/bmumu2020/nTupleBranchNames/v4/dump_MCsignal.txt

./ScanTree /eos/home-a/agrummer/BsmumuData/AnalysisNtuples2020/v4/LASTskim.user.agrummer.mcBsmumu.merged.2.root > /afs/cern.ch/user/a/agrummer/www/bmumu2020/nTupleBranchNames/v4/dump_MCsignal3.txt

./ScanTree /eos/home-a/agrummer/BsmumuData/AnalysisNtuples2020/v4/LASTskim.user.agrummer.Data1516.merged.root > /afs/cern.ch/user/a/agrummer/www/bmumu2020/nTupleBranchNames/v4/dump_Data1516.txt


./RoundFloats /eos/home-a/agrummer/BsmumuData/AnalysisNtuples2020/v4/LASTskim.user.agrummer.mcBsmumu.merged.root



2020 Nov 6
./BranchNamesMacro_withType /afs/cern.ch/user/a/agrummer/www/bmumu2020/Nominal_OneFileData2018_FinalIso/LASTskim.bsmumu.root

./BranchNamesMacro_withType_Tmv /eos/atlas/atlascerngroupdisk/phys-beauty/BsMuMuRun1/data/Bsmumu/data12_8TeVBsAllPeriodsUnblinded.root
