import pandas as pd
import sys
# import collections
#Searching code found on stack exchange

from Variables_2 import VariableInfo
from Variables_2 import Variables

# def ExtractImpAndSep(ifilename, opath, ofolder):
def ExtractImpAndSep(idirectory, SepFirst):
  dfSep = pd.DataFrame()
  dfImp = pd.DataFrame()
  variable ='----------------------' # if this is too long (too many dashes), the code will not run

  # df.append()
  # with open(opath + ofolder + "/STDOUT", "r") as f:
  with open(idirectory +  "/output.txt", "r") as myFile:
      searchlines = myFile.readlines()
      
  numOfLines = 20 #should be greater than the number of TMVA input variables
  check = 0
  for i, line in enumerate(searchlines):
      if "Separation\n" in line: 
          for lineNum, line in enumerate(searchlines[i:i+numOfLines]):
  #             print(lineNum)
              if variable in line:
                  check +=1
                  if check == 2:
                      break
                  continue
              line = ''.join(line.split())
              if i+lineNum == i:
                  headersList = line.split(':')
                  headersList.pop(0)
                  continue
              my_list = line.split(':')
              my_list.pop(0)
  #             print(my_list) 
              # print("here")
              dfSep = dfSep.append(pd.Series(my_list, index=headersList), ignore_index=True)
              # print("here2")
  check = 0
  for i, line in enumerate(searchlines):
      if "Importance\n" in line: 
          for lineNum, line in enumerate(searchlines[i:i+numOfLines]):
  #             print(lineNum)
              if variable in line:
                  check +=1
                  if check == 2:
                      break
                  continue
              line = ''.join(line.split())
              if i+lineNum == i:
                  headersList = line.split(':')
                  headersList.pop(0)
                  continue
              if '::' in line:
                  line = line[:line.find('::')] + '_' + line[line.find('::')+2:]
              my_list = line.split(':')
              my_list.pop(0)
  #             print(my_list)
  #             print(my_list) 
              dfImp = dfImp.append(pd.Series(my_list, index=headersList), ignore_index=True)
  # print(dfSep)
  # print(dfImp)

  numRows = dfImp.shape[0] # this gives the total number of rows (including header and first data starts at 0)
  for i in range(0, numRows):
    for j in range(0, len(Variables)):
      if (dfImp.loc[i, 'Variable'] == Variables[j].name):
        # print(i, " ", dfImp.loc[i, 'Variable'])
        dfImp.loc[i, 'Variable'] = Variables[j].LatexName
        continue
      # else:
      #   print('missing', ' ', dfImp.loc[i, 'Variable'])
  numRows = dfSep.shape[0] # this gives the total number of rows (including header and first data starts at 0)
  for i in range(0, numRows):
    # print(dfSep.loc[i, 'Variable'])
    for j in range(0, len(Variables)):
      if (dfSep.loc[i, 'Variable'] in Variables[j].axLabel):
        # print(i, " ", dfSep.loc[i, 'Variable'])
        dfSep.loc[i, 'Variable'] = Variables[j].LatexName
        continue
      # elif("BIsolation(I^{B}_{0.7})" in dfSep.loc[i, 'Variable'] and 'B_iso_7_Chi2_5_LoosePt05' in Variables[j].name):
      #   print("Debug, ", Variables[j].axLabel, dfSep.loc[i, 'Variable'])
      #   dfSep.loc[i, 'Variable'] = Variables[j].axLabel
      #   continue
      # else:
      #   print('missing', ' ', dfImp.loc[i, 'Variable'])

  # for i in range(55):
  #   print(Variables[i].name, " ", Variables[i].axLabel)

  # print(len(Variables))
  dfImp.rename(columns={'Rank': 'Imp. Rank', 'VariableImportance': 'Importance'}, inplace=True)
  dfSep.rename(columns={'Rank': 'Sep. Rank'}, inplace=True)
  # print(dfImp)
  dfImp['Importance'] = pd.to_numeric(dfImp['Importance'])
  dfSep['Separation'] = pd.to_numeric(dfSep['Separation'])

  # print(dfSep)
  # print(dfImp)
  # SepFirst = False
  if SepFirst:
    dfSep = dfSep.merge(dfImp, how='outer')
  else:
    dfImp = dfImp.merge(dfSep, how='outer')
  tdaysDate = ""
  if tdaysDate == "2020Mar27":
    repVals = {}
  else:
    repVals = {r"\textbackslash": "\\", r"\_": r"_", r"\{": r"{", r"\}": r"}", r"\textasciicircum": r"^", "\$": r"$"}#, r" ": "", r"&": r" & ", r"eltaR": r"elta R", r"Iso": r" Iso"}
  # dfImp = dfImp.append(pd.Series(['Total:', "", dfImp['Importance'].sum(), "", dfImp['Separation'].sum()], index=list(dfImp)), ignore_index=True)
  # dfImp.to_csv(opath + ofolder + '/Importance.csv', index=None)
  if SepFirst:
    OutputTable = dfSep.to_latex(longtable=True, index=False)
  else:
    OutputTable = dfImp.to_latex(longtable=True, index=False)
  for k, v in repVals.items():#for py27 use iteritems()
    OutputTable = OutputTable.replace(k, v)
  # OutputTable = OutputTable.replace(r"\textbackslash", "\\")
  # OutputTable = OutputTable.replace(r"\_", r"_")
  # OutputTable = OutputTable.replace(r"\{", r"{")
  # OutputTable = OutputTable.replace(r"\}", r"}")
  # OutputTable = OutputTable.replace(r"\textasciicircum", r"^")
  # OutputTable = OutputTable.replace("\$", r"$")
  # print(OutputTable)
  if SepFirst:
    tex_file = open(idirectory+"/Separation.tex", "w")
  else:
    tex_file = open(idirectory+"/Importance.tex", "w")
  tex_file.write(r"\input{/Users/agrummer/cernbox/www/bmumu/Data/TrainedMVAs/DocPreamble}")
  tex_file.write(r"\usepackage{lscape}")
  tex_file.write("\n")
  tex_file.write(r"\begin{document}")
  tex_file.write("\n")
  tex_file.write(r"\begin{landscape}")
  tex_file.write("\n")
  tex_file.write("%s" % OutputTable)
  tex_file.write("\n")
  tex_file.write(r"\end{landscape}")
  tex_file.write("\n")
  tex_file.write(r"\end{document}")
  tex_file.close()
  if SepFirst:
    print('Wrote file: Separation.tex in dir: ', idirectory)
  else:
    print('Wrote file: Importance.tex in dir: ', idirectory)
# opath = "/Users/agrummer/Desktop/Bmumu/Output/Trees/"
# opath = "/Users/agrummer/Desktop/Bmumu/Output/"
# # ofolder = 'LSFJOB_Trees500'
# ofolder = 'LSFJOB_FullDataset'
# ifilename = opath + ofolder + "/bdt2016test_0.root"

# ExtractImpAndSep(ifilename, opath, ofolder)

if __name__ == "__main__":
    idirectory = str(sys.argv[1])
    SepOrImp = str(sys.argv[2])
    if SepOrImp == "Sep":
        SepFirst = True
    else:
        SepFirst = False
    print(idirectory)
    # b = str(sys.argv[2])
    # c = str(sys.argv[3])
    ExtractImpAndSep(idirectory, SepFirst)
# python ExtractImpAndSep.py "/Users/agrummer/cernbox/www/bmumu/myMVA/OutputMVAMar8/out_MaxDepth1_MinNodeSize0.5_AdaBoostBeta0.5_NTrees500"
# python ExtractImpAndSep.py "/Users/agrummer/Desktop/Bmumu/Output/LSFJOB_FullDataset/bdt2016test_0.root" "/Users/agrummer/Desktop/Bmumu/Output/" 'LSFJOB_FullDataset'
