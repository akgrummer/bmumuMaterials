#zip -r OutMVAapr10.zip . -x \*2016test\*

#mdval=( 2 3 4 5 6 7 8 9 10 11 12 13 14 15 )
# ndsize=( 0.1 0.2 0.5 1.0 2.0 5.0 10.0 )
# bbeta=( 0.1 0.2 0.4 0.5 0.6 )
# ntrees=(200 400 500)

#Best 15 vars config so far:
mdval_core1=( 4 )
ndsize_core1=( 0.2 )
bbeta_core1=( 0.5 )
ntrees_core1=( 500 )
# ntrees_core1=( 1 )

# # corr Matrix
# mdval_core1=( 1 )
# ndsize_core1=( 0.2 )
# bbeta_core1=( 1 )
# ntrees_core1=( 1 )

#best 7 vars configuration:
# mdval_core1=( 8 )
# ndsize_core1=( 1.0 )
# bbeta_core1=( 0.1 )
# ntrees_core1=( 500 )
# mdval_core1=( 6 )
# ndsize_core1=( 0.1 )
# bbeta_core1=( 0.2 )
# ntrees_core1=( 500 )


# mdval_core1=( 3 5 7 9 11 )
# ndsize_core1=( 0.3 0.4 0.6 0.7 2.2 2.3 2.4)
# bbeta_core1=( 0.5 )
# ntrees_core1=( 500 )

# mdval_core2=( 2 4 6 8 10 )
# ndsize_core2=( 0.3 0.4 0.6 0.7 2.2 2.3 2.4)
# bbeta_core2=( 0.5 )
# ntrees_core2=( 500 )

# mdval_core3=( 3 5 7 9 11 )
# ndsize_core3=( 0.8 0.9 1.1 1.2 2.5 2.6 )
# bbeta_core3=( 0.5 )
# ntrees_core3=( 500 )

# mdval_core4=( 2 4 6 8 10 )
# ndsize_core4=( 0.8 0.9 1.1 1.2 2.5 2.6 )
# bbeta_core4=( 0.5 )
# ntrees_core4=( 500 )

# mdval_core5=( 3 5 7 9 11 )
# ndsize_core5=( 1.3 1.4 1.5 1.6 2.7 2.8 )
# bbeta_core5=( 0.5 )
# ntrees_core5=( 500 )

# mdval_core6=( 2 4 6 8 10 )
# ndsize_core6=( 1.3 1.4 1.5 1.6 2.7 2.8 )
# bbeta_core6=( 0.5 )
# ntrees_core6=( 500 )

# mdval_core7=( 3 5 7 9 11 )
# ndsize_core7=( 1.7 1.8 1.9 2.1 2.9 3.0 )
# bbeta_core7=( 0.5 )
# ntrees_core7=( 500 )

# mdval_core8=( 2 4 6 8 10 )
# ndsize_core8=( 1.7 1.8 1.9 2.1 2.9 3.0 )
# bbeta_core8=( 0.5 )
# ntrees_core8=( 500 )

# # # mdval_core9=( 3 5 7 9 11 )
# # # ndsize_core9=( 2.3 2.4 2.5 2.6 )
# # # bbeta_core9=( 0.5 )
# # # ntrees_core9=( 500 )

# # # mdval_core10=( 2 4 6 8 10 )
# # # ndsize_core10=( 2.3 2.4 2.5 2.6 )
# # # bbeta_core10=( 0.5 )
# # # ntrees_core10=( 500 )

# # # mdval_core11=( 3 5 7 9 11 )
# # # ndsize_core11=( 2.7 2.8 2.9 3.0 )
# # # bbeta_core11=( 0.5 )
# # # ntrees_core11=( 500 )

# # # mdval_core12=( 2 4 6 8 10 )
# # # ndsize_core12=( 2.7 2.8 2.9 3.0 )
# # # bbeta_core12=( 0.5 )
# # # ntrees_core12=( 500 )


outdnamelistBIso=( out_BIso )
outdnamelistDOCA=( out_DOCA )
outdnamelistnCloseTracks=( out_nCloseTracks )
outdnamelistmuM=( out_muM )
outdnamelistmuP=( out_muP )
outdnamelistNom=( out_Nom)
outdnamelistCustom=( out_Custom)
outdnamelistLoose=( out_Loose)
outdnamelistRun1=( out_Run1)
#june26:
outdnamelistRun1Custom=( out_Run1Custom )
outdnamelistBestSep=( out_BestSep )
#July 16-17,
# outdnamelistRun1nPV=( out_Run1nPV )
# outdnamelistRun1privxmu=( out_Run1privxmu )
outdnamelistRun1privxmu=( out_Run1privxmu_round )
outdnamelistALLvars=( out_ALLvars )

# outdnamelistRun1nPV=( out_Run1nPV_npvweights )
# outdnamelistALLvars=( out_ALLvars_npvweights )
#July 22, 
outdnamelistRun1nPVweights=( out_Run1_npvweights) # use As in Run 1 B Iso, as in Run 2 close track vars, 12 nominal vars, and apply NPV weights.
outdnamelistCustomprivxmu=( Custom_privxmu ) 
outdnamelistCustomnPV=( Custom_nPV ) 
# outdnamelistSets=( AllNoWeights )
# outdnamelistSets=( All )
# outdnamelistSets=( OldNoWeights )
# outdnamelistSets=( Old )
outdnamelistSets=( Set1 Set2 Set3 )
outdnamelistSet1=( Set1 )
outdnamelistSet2=( Set2 )
outdnamelistSet3=( Set3 )
# outdnamelistSets=( Set1 )


# array=( "1" "3" )

# source SubmitmyMVA_pc01.sh "${mdval_core1[*]}" "${ndsize_core1[*]}" "${bbeta_core1[*]}" "${ntrees_core1[*]}" &
# source SubmitBDT_pc01.sh "${mdval_core1[*]}" "${ndsize_core1[*]}" "${bbeta_core1[*]}" "${ntrees_core1[*]}" "${outdnamelistNom[*]}" "${outdnamelistSets[*]}" &
# source SubmitBDT_pc01.sh "${mdval_core1[*]}" "${ndsize_core1[*]}" "${bbeta_core1[*]}" "${ntrees_core1[*]}" "${outdnamelistCustom[*]}" "${outdnamelistSets[*]}" &
# source SubmitBDT_pc01.sh "${mdval_core1[*]}" "${ndsize_core1[*]}" "${bbeta_core1[*]}" "${ntrees_core1[*]}" "${outdnamelistLoose[*]}" "${outdnamelistSets[*]}" &
# source SubmitBDT_pc01.sh "${mdval_core1[*]}" "${ndsize_core1[*]}" "${bbeta_core1[*]}" "${ntrees_core1[*]}" "${outdnamelistRun1[*]}" "${outdnamelistSets[*]}" &
#
# source SubmitBDT_pc01.sh "${mdval_core1[*]}" "${ndsize_core1[*]}" "${bbeta_core1[*]}" "${ntrees_core1[*]}" "${outdnamelistRun1Custom[*]}" "${outdnamelistSets[*]}" &
# source SubmitBDT_pc01.sh "${mdval_core1[*]}" "${ndsize_core1[*]}" "${bbeta_core1[*]}" "${ntrees_core1[*]}" "${outdnamelistBestSep[*]}" "${outdnamelistSets[*]}" &
# source SubmitBDT_pc01.sh "${mdval_core1[*]}" "${ndsize_core1[*]}" "${bbeta_core1[*]}" "${ntrees_core1[*]}" "${outdnamelistRun1privxmu[*]}" "${outdnamelistSet1[*]}" &
# source SubmitBDT_pc01.sh "${mdval_core1[*]}" "${ndsize_core1[*]}" "${bbeta_core1[*]}" "${ntrees_core1[*]}" "${outdnamelistRun1privxmu[*]}" "${outdnamelistSet2[*]}" &
# source SubmitBDT_pc01.sh "${mdval_core1[*]}" "${ndsize_core1[*]}" "${bbeta_core1[*]}" "${ntrees_core1[*]}" "${outdnamelistRun1privxmu[*]}" "${outdnamelistSet3[*]}" &
# # source SubmitBDT_pc01.sh "${mdval_core1[*]}" "${ndsize_core1[*]}" "${bbeta_core1[*]}" "${ntrees_core1[*]}" "${outdnamelistALLvars[*]}" "${outdnamelistSet1[*]}" &
# source SubmitBDT_pc01.sh "${mdval_core1[*]}" "${ndsize_core1[*]}" "${bbeta_core1[*]}" "${ntrees_core1[*]}" "${outdnamelistALLvars[*]}" "${outdnamelistSet2[*]}" &
# source SubmitBDT_pc01.sh "${mdval_core1[*]}" "${ndsize_core1[*]}" "${bbeta_core1[*]}" "${ntrees_core1[*]}" "${outdnamelistALLvars[*]}" "${outdnamelistSet3[*]}" &
# source SubmitBDT_pc01.sh "${mdval_core1[*]}" "${ndsize_core1[*]}" "${bbeta_core1[*]}" "${ntrees_core1[*]}" "${outdnamelistRun1nPV[*]}" "${outdnamelistSet1[*]}" &
# source SubmitBDT_pc01.sh "${mdval_core1[*]}" "${ndsize_core1[*]}" "${bbeta_core1[*]}" "${ntrees_core1[*]}" "${outdnamelistRun1nPV[*]}" "${outdnamelistSet2[*]}" &
# source SubmitBDT_pc01.sh "${mdval_core1[*]}" "${ndsize_core1[*]}" "${bbeta_core1[*]}" "${ntrees_core1[*]}" "${outdnamelistRun1nPV[*]}" "${outdnamelistSet3[*]}" &
# source SubmitBDT_pc01.sh "${mdval_core1[*]}" "${ndsize_core1[*]}" "${bbeta_core1[*]}" "${ntrees_core1[*]}" "${outdnamelistALLvars[*]}" "${outdnamelistSet1[*]}" &
# source SubmitBDT_pc01.sh "${mdval_core1[*]}" "${ndsize_core1[*]}" "${bbeta_core1[*]}" "${ntrees_core1[*]}" "${outdnamelistALLvars[*]}" "${outdnamelistSet2[*]}" &
# source SubmitBDT_pc01.sh "${mdval_core1[*]}" "${ndsize_core1[*]}" "${bbeta_core1[*]}" "${ntrees_core1[*]}" "${outdnamelistALLvars[*]}" "${outdnamelistSet3[*]}" &
# source SubmitBDT_pc01.sh "${mdval_core1[*]}" "${ndsize_core1[*]}" "${bbeta_core1[*]}" "${ntrees_core1[*]}" "${outdnamelistRun1nPVweights[*]}" "${outdnamelistSet1[*]}" &
# source SubmitBDT_pc01.sh "${mdval_core1[*]}" "${ndsize_core1[*]}" "${bbeta_core1[*]}" "${ntrees_core1[*]}" "${outdnamelistRun1nPVweights[*]}" "${outdnamelistSet2[*]}" &
# source SubmitBDT_pc01.sh "${mdval_core1[*]}" "${ndsize_core1[*]}" "${bbeta_core1[*]}" "${ntrees_core1[*]}" "${outdnamelistRun1nPVweights[*]}" "${outdnamelistSet3[*]}" &

source SubmitBDT_pc01.sh "${mdval_core1[*]}" "${ndsize_core1[*]}" "${bbeta_core1[*]}" "${ntrees_core1[*]}" "${outdnamelistCustomprivxmu[*]}" "${outdnamelistSet1[*]}" &
source SubmitBDT_pc01.sh "${mdval_core1[*]}" "${ndsize_core1[*]}" "${bbeta_core1[*]}" "${ntrees_core1[*]}" "${outdnamelistCustomprivxmu[*]}" "${outdnamelistSet2[*]}" &
source SubmitBDT_pc01.sh "${mdval_core1[*]}" "${ndsize_core1[*]}" "${bbeta_core1[*]}" "${ntrees_core1[*]}" "${outdnamelistCustomprivxmu[*]}" "${outdnamelistSet3[*]}" &

# source SubmitBDT_pc01.sh "${mdval_core1[*]}" "${ndsize_core1[*]}" "${bbeta_core1[*]}" "${ntrees_core1[*]}" "${outdnamelistCustomnPV[*]}" "${outdnamelistSet1[*]}" &
# source SubmitBDT_pc01.sh "${mdval_core1[*]}" "${ndsize_core1[*]}" "${bbeta_core1[*]}" "${ntrees_core1[*]}" "${outdnamelistCustomnPV[*]}" "${outdnamelistSet2[*]}" &
# source SubmitBDT_pc01.sh "${mdval_core1[*]}" "${ndsize_core1[*]}" "${bbeta_core1[*]}" "${ntrees_core1[*]}" "${outdnamelistCustomnPV[*]}" "${outdnamelistSet3[*]}" &
#
# source SubmitBDT_pc01.sh "${mdval_core1[*]}" "${ndsize_core1[*]}" "${bbeta_core1[*]}" "${ntrees_core1[*]}" "${outdnamelistBIso[*]}" &
# source SubmitBDT_pc01.sh "${mdval_core1[*]}" "${ndsize_core1[*]}" "${bbeta_core1[*]}" "${ntrees_core1[*]}" "${outdnamelistDOCA[*]}" &
# source SubmitBDT_pc01.sh "${mdval_core1[*]}" "${ndsize_core1[*]}" "${bbeta_core1[*]}" "${ntrees_core1[*]}" "${outdnamelistnCloseTracks[*]}" &
# source SubmitBDT_pc01.sh "${mdval_core1[*]}" "${ndsize_core1[*]}" "${bbeta_core1[*]}" "${ntrees_core1[*]}" "${outdnamelistmuM[*]}" &
# source SubmitBDT_pc01.sh "${mdval_core1[*]}" "${ndsize_core1[*]}" "${bbeta_core1[*]}" "${ntrees_core1[*]}" "${outdnamelistmuP[*]}" &
# source SubmitmyMVA_pc01.sh "${mdval_core2[*]}" "${ndsize_core2[*]}" "${bbeta_core2[*]}" "${ntrees_core2[*]}" &
# source SubmitmyMVA_pc01.sh "${mdval_core3[*]}" "${ndsize_core3[*]}" "${bbeta_core3[*]}" "${ntrees_core3[*]}" &
# source SubmitmyMVA_pc01.sh "${mdval_core4[*]}" "${ndsize_core4[*]}" "${bbeta_core4[*]}" "${ntrees_core4[*]}" &
# source SubmitmyMVA_pc01.sh "${mdval_core5[*]}" "${ndsize_core5[*]}" "${bbeta_core5[*]}" "${ntrees_core5[*]}" &
# source SubmitmyMVA_pc01.sh "${mdval_core6[*]}" "${ndsize_core6[*]}" "${bbeta_core6[*]}" "${ntrees_core6[*]}" &
# source SubmitmyMVA_pc01.sh "${mdval_core7[*]}" "${ndsize_core7[*]}" "${bbeta_core7[*]}" "${ntrees_core7[*]}" &
# source SubmitmyMVA_pc01.sh "${mdval_core8[*]}" "${ndsize_core8[*]}" "${bbeta_core8[*]}" "${ntrees_core8[*]}" &

# source SubmitmyMVA_pc01.sh "${mdval_core9[*]}" "${ndsize_core9[*]}" "${bbeta_core9[*]}" "${ntrees_core9[*]}" &
# source SubmitmyMVA_pc01.sh "${mdval_core10[*]}" "${ndsize_core10[*]}" "${bbeta_core10[*]}" "${ntrees_core10[*]}" &
# source SubmitmyMVA_pc01.sh "${mdval_core11[*]}" "${ndsize_core11[*]}" "${bbeta_core11[*]}" "${ntrees_core11[*]}" &
# source SubmitmyMVA_pc01.sh "${mdval_core12[*]}" "${ndsize_core12[*]}" "${bbeta_core12[*]}" "${ntrees_core12[*]}" &
# "${ndsize_core1[*]}" "${bbeta_core1[*]}" "${ntrees_core1[*]}" 