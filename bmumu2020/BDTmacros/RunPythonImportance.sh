# run Python Importance on one directory

export ScriptDir=/Users/agrummer/cernbox/www/bmumu2020/BDTmacros/PythonImportance
export RunDir="/Users/agrummer/cernbox/www/bmumu2020/BDTmacros/"
# export preDataDir=/Users/agrummer/cernbox/www/bmumu/myMVAOut/OutMVAmay3

# export HOME_DIR=/

# MaxDepth=14
# MinNodeSize=0.1
# AdaBoostBeta=0.1
# NTrees=500

# export DataDir=${preDataDir}/out_MaxDepth${MaxDepth}_MinNodeSize${MinNodeSize}_AdaBoostBeta${AdaBoostBeta}_NTrees${NTrees}

# MaxDepth=14
# MinNodeSize=0.1
# AdaBoostBeta=0.1
# NTrees=500

# export DataDir=${preDataDir}/out_MaxDepth${MaxDepth}_MinNodeSize${MinNodeSize}_AdaBoostBeta${AdaBoostBeta}_NTrees${NTrees}
# export DataDir=/Users/agrummer/cernbox/www/bmumu/Data/May15/May24npv/out_MaxDepth4_MinNodeSize0.2_AdaBoostBeta0.5_NTrees500
# export DataDir=/Users/agrummer/cernbox/www/bmumu/Data/TrainedMVAs/May31_noPVweightsBkg/out_MaxDepth4_MinNodeSize0.2_AdaBoostBeta0.5_NTrees500
# export DataDir=/Users/agrummer/cernbox/www/bmumu/Data/TrainedMVAs/Jun7_RS_train1_test2/out_MaxDepth4_MinNodeSize0.2_AdaBoostBeta0.5_NTrees500
# export DataDir=/Users/agrummer/cernbox/www/bmumu/Data/TrainedMVAs/Jun7_train2_test1/out_MaxDepth4_MinNodeSize0.2_AdaBoostBeta0.5_NTrees500
# export DataDir=/Users/agrummer/cernbox/www/bmumu/Data/TrainedMVAs/May24/out_MaxDepth4_MinNodeSize0.2_AdaBoostBeta0.5_NTrees500
# export DataDir=/Users/agrummer/cernbox/www/bmumu/Data/TrainedMVAs/Jun12/train2_test3/out_MaxDepth4_MinNodeSize0.2_AdaBoostBeta0.5_NTrees500
# outdnamelist=(out_BIso_2018_MC16e out_nCloseTracks_2018_MC16e\
#               out_DOCA_2018_MC16e out_muM_2018_MC16e out_muP_2018_MC16e\
#               out_BIso_2017_MC16d out_nCloseTracks_2017_MC16d\
#               out_DOCA_2017_MC16d out_muM_2017_MC16d out_muP_2017_MC16d\
#               out_BIso_2016_MC16a out_nCloseTracks_2016_MC16a\
#               out_DOCA_2016_MC16a out_muM_2016_MC16a out_muP_2016_MC16a\
#               )
SplitSets=(
    Set1
    Set2
    Set3
    )
outdnamelist=( 
    # out_Custom 
    # out_Loose 
    # out_Nom 
    # out_Run1 
    # out_Run1privxmu
    # out_Run1nPV
    # out_BestSep
    # out_Run1Custom
    #from july 16:
    # out_Run1nPV_npvweights
    # out_Run1privxmu_round
    #from July 22
    # out_Run1_npvweights
    #from Aug 6
    Custom_privxmu
    Custom_nPV
    #
    # out_muM out_muP 
    )
for outdname in "${outdnamelist[@]}"
    do
    for whichSet in "${SplitSets[@]}"
        do
        # export DataDir=/Users/agrummer/cernbox/www/bmumu/myMVA/${outdname}
        # export DataDir=/Users/agrummer/cernbox/www/bmumu2020/BDT/BDToutput/2020May20/${outdname}
        # export DataDir=/Users/agrummer/cernbox/www/bmumu2020/BDT/BDToutput/2020May29/${outdname}/${whichSet}
        # export DataDir=/Users/agrummer/cernbox/www/bmumu2020/BDT/BDToutput/2020Jun16/${outdname}/${whichSet}
        # export DataDir=/Users/agrummer/cernbox/www/bmumu2020/BDT/BDToutput/2020Jun26/${outdname}/${whichSet}
        # export DataDir=/Users/agrummer/cernbox/www/bmumu2020/BDT/BDToutput/2020July16/${outdname}/${whichSet}
        # export DataDir=/Users/agrummer/cernbox/www/bmumu2020/BDT/BDToutput/2020July16/${outdname}/${whichSet}
        export DataDir=/Users/agrummer/cernbox/www/bmumu2020/BDT/BDToutput/2020Aug6/${outdname}/${whichSet}
        python ${ScriptDir}/ExtractImpAndSep.py ${DataDir} Sep
        python ${ScriptDir}/ExtractImpAndSep.py ${DataDir} Imp
        cd ${DataDir}
        latexmk -lualatex ${DataDir}/Separation.tex >>${DataDir}/SepOut.txt 2>>${DataDir}/SepErr.txt 
        latexmk -lualatex ${DataDir}/Importance.tex >>${DataDir}/ImpOut.txt 2>>${DataDir}/ImpErr.txt 
        rm  ${DataDir}/*.fls ${DataDir}/*.fdb_latexmk ${DataDir}/*.aux ${DataDir}/*.log 
    cd ${RunDir}
    done
done

    # for outdname in "${outdnamelist[@]}"
    #     do
    # outdname=out_DOCA_2016_MC16a
    # export DataDir=/Users/agrummer/cernbox/www/bmumu/myMVA/${outdname}

    # # ${DataDir}/*.log ${DataDir}/*.dvi
    # done

    # export RunDir="/Users/agrummer/cernbox/www/bmumu/myMVA/Macros/"

