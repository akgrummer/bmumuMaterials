all: libdefinitions.so cutBatchBsJpsiPhi.exe cutBatchBsmumu.exe cutBatchBpJpsiKp.exe MergeNominalnTuples.exe ReProcessPartialRun2nTuples.exe

libdefinitions.so: definitionsDICT.cxx
	g++ -shared -fPIC -o $@ $^ `root-config --evelibs --cflags`

cutBatchBpJpsiKp.exe: cutBatchBpJpsiKp.cxx
	g++ cutBatchBpJpsiKp.cxx -o cutBatchBpJpsiKp.exe `root-config --glibs --cflags`

cutBatchBsJpsiPhi.exe: cutBatchBsJpsiPhi.cxx
	g++ cutBatchBsJpsiPhi.cxx -o cutBatchBsJpsiPhi.exe `root-config --glibs --cflags`

cutBatchBsmumu.exe: cutBatchBsmumu.cxx
	g++ cutBatchBsmumu.cxx -o cutBatchBsmumu.exe `root-config --glibs --cflags`

MergeNominalnTuples.exe: MergeNominalnTuples.cxx
	g++ MergeNominalnTuples.cxx -o MergeNominalnTuples.exe `root-config --glibs --cflags`

ReProcessPartialRun2nTuples.exe: ReProcessPartialRun2nTuples.cpp
	g++ ReProcessPartialRun2nTuples.cpp -o ReProcessPartialRun2nTuples.exe `root-config --glibs --cflags`

definitionsDICT.cxx: *.hh
	rootcint -f $@ -c -p $^

clean:
	rm -f *.o *.so *.lib *.pcm *DICT* *.exe *.pdf
