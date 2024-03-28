all: libdefinitions.so cutBatchBsJpsiPhi.exe cutBatchBsmumu.exe cutBatchBpJpsiKp.exe

libdefinitions.so: definitionsDICT.cxx
	g++ -shared -fPIC -o $@ $^ `root-config --evelibs --cflags`

cutBatchBpJpsiKp.exe: cutBatchBpJpsiKp.cxx
	g++ cutBatchBpJpsiKp.cxx -o cutBatchBpJpsiKp `root-config --glibs --cflags`

cutBatchBsJpsiPhi.exe: cutBatchBsJpsiPhi.cxx
	g++ cutBatchBsJpsiPhi.cxx -o cutBatchBsJpsiPhi `root-config --glibs --cflags`

cutBatchBsmumu.exe: cutBatchBsmumu.cxx
	g++ cutBatchBsmumu.cxx -o cutBatchBsmumu `root-config --glibs --cflags`

definitionsDICT.cxx: *.hh
	rootcint -f $@ -c -p $^

clean:
	rm -f *.o *.so *.lib *.pcm *DICT* *.exe *.pdf
