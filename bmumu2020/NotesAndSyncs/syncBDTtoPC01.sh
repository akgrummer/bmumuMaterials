# from lxplus: 
rsync -avz --exclude "BDToutput/" --exclude "*.sys.*" /afs/cern.ch/user/a/agrummer/www/bmumu2020/BDT/ $USER@pcatlunm01.cern.ch:/home/agrummer/bmumu2020/BDT
# from aidan's mac:
rsync -avz --exclude "BDToutput/" --exclude "*.sys.*" --exclude ".DS_Store" ~/cernbox/www/bmumu2020/BDT/ $USER@pcatlunm01.cern.ch:/home/agrummer/bmumu2020/BDT
# rsync -avz /afs/cern.ch/user/a/agrummer/www/bmumu2020/AtlasStyle $USER@pcatlunm01.cern.ch:/home/agrummer/bmumu2020/
#sync the output back (without bdt2020.root or weights files)
# rsync -avz --exclude "bdt2020.root" --exclude "weights/" $USER@pcatlunm01.cern.ch:/home/agrummer/bmumu2020/BDT/BDToutput/ /afs/cern.ch/user/a/agrummer/www/bmumu2020/BDT/BDToutput
# rsync -avz --exclude "bdt2020.root" $USER@pcatlunm01.cern.ch:/home/agrummer/bmumu2020/BDT/BDToutput/2020Jun16 /afs/cern.ch/user/a/agrummer/www/bmumu2020/BDT/BDToutput/
# rsync -avz --exclude "bdt2020.root" $USER@pcatlunm01.cern.ch:/home/agrummer/bmumu2020/BDT/BDToutput/2020Jun16 /afs/cern.ch/user/a/agrummer/www/bmumu2020/BDT/BDToutput/
# sync output back from PC01 directly to Aidan's Mac, but probably better to sync back to lxplus first
# rsync -avz --exclude "bdt2020.root" --exclude "weights/" $USER@pcatlunm01.cern.ch:/home/agrummer/bmumu2020/BDT/BDToutput/2020July22 /Users/agrummer/cernbox/www/bmumu2020/BDT/BDToutput
#sync output back to lxplus:
# rsync -avz --exclude "bdt2020.root" --exclude "weights/" $USER@pcatlunm01.cern.ch:/home/agrummer/bmumu2020/BDT/BDToutput/2020July22 /afs/cern.ch/user/a/agrummer/www/bmumu2020/BDT/BDToutput/
rsync -avz --exclude "bdt2020.root" --exclude "weights/" $USER@pcatlunm01.cern.ch:/home/agrummer/bmumu2020/BDT/BDToutput/2020Aug6 /afs/cern.ch/user/a/agrummer/www/bmumu2020/BDT/BDToutput/
#sync BDT macros from Aidan's mac to PC01:
rsync -avz --exclude "*.sys.*" --exclude ".DS_Store" ~/cernbox/www/bmumu2020/BDTmacros/ $USER@pcatlunm01.cern.ch:/home/agrummer/bmumu2020/BDTmacros
