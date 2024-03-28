Hi Aidan,

I put an example of running on condor with transfer of input and output files to
/afs/cern.ch/user/i/ibragimo/public/forAidan/condortest

in consist of an example script and its Mafefile:
selectbpbkg.cxx
Makefile

then
setupjob.sh - to prepare condor job
condor.sub  - actual condor job setup
LASTskim.output_2685758.root - input file the script runs on


So to run the job you need to do:
make
condor_submit condor.sub
condor_q #for checking the job status

the script (runs normally few minutes, say <10) produces the file out.root and other condor output in the same directory.
NB
1. you can run without using condor by just executing the script setupjob.sh
2. all this setupATLAS is done just to mimic the environment at the time of compilation on lxplus
at the HTC condor, otherwise there is mismatch with the c++ libraries you need to take care about.
3. certainly I/O could be done cleaner by adding root paths - this is just an example, IMHO,
_the largest drawback_ of this example is that the same input and output file names are set in _both_ setupjob.sh and condor.sub
4. just FYI the script categorizes B+JpsiK+ background in bbJpsiX sample

Please let me know if the example works for you, HTH.
Cheers,
Iskander