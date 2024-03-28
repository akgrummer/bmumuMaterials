#### Description

These are a couple of classes meant to read the pileup and the associated
systematics for each run number and lumiblock number.

In order to use it do:

`setupATLAS`  
`lsetup root`  
`mkdir build`  
`cd build`  
`cmake ..`  
`make`  

This will create a `libreader.so` and a `libwriter.so` libraries, which can be
used to create and read a JSON file with the pileup information. An example
of how to use it is in `source/tester.cxx`. Which corresponds to the `tester`
executable, which, when run pruduces the JSON file and reads one of the entries.

#### WARNING

In LXPLUS, you should also setup cmake and boost, additionally, you have to tell Cmake
where to find Boost; so that it does not pick up the built in package. This means that
you have to do:

`setupATLAS`  
`lsetup root`  
`lsetup "boost boost-1.62.0-python2.7-x86_64-slc6-gcc62"`  
`mkdir build`  
`cd build`  
`cmake -DBOOST_ROOT=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/boost/boost-1.62.0-python2.7-x86_64-slc6-gcc62 ..`  
`make`

of course, both in the setup and cmake steps the versions of boost must be the same.

