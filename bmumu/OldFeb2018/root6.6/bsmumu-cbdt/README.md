--- How to use the code ---

- compile: make
- change the paths to input and output root files in cfg/bdt2012final.cfg
- submit job to lxplus batch system: "source scripts/submittraining.sh"
- check results of the BDT training:
  cd out/
  root -l
  TMVA::TMVAGui("bdt2012final_0.root")

--- Where to find BDT training options ---

the options (static) are set in cfg/bdt2012final.cfg 
the rest is set in scripts/submittraining.sh
(to facilitate grid scan on batch system) 
