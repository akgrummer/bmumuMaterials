all: libdefinitions.so cutBatchBsJpsiPhi.exe cutBatchBsmumu.exe cutBatchBpJpsiKp.exe cutBatchBsmumu_fileloop.exe cutBatchBsmumu_fileloop_oldnTuples.exe Run1doca3Macro.exe

libdefinitions.so: definitionsDICT.cxx
	g++ -shared -fPIC -o $@ $^ `root-config --evelibs --cflags`

cutBatchBpJpsiKp.exe: cutBatchBpJpsiKp.cxx
	g++ cutBatchBpJpsiKp.cxx -o cutBatchBpJpsiKp `root-config --glibs --cflags`

cutBatchBsJpsiPhi.exe: cutBatchBsJpsiPhi.cxx
	g++ cutBatchBsJpsiPhi.cxx -o cutBatchBsJpsiPhi `root-config --glibs --cflags`

cutBatchBsmumu.exe: cutBatchBsmumu.cxx
	g++ cutBatchBsmumu.cxx -o cutBatchBsmumu `root-config --glibs --cflags`

cutBatchBsmumu_fileloop.exe: cutBatchBsmumu_fileloop.cxx
	g++ cutBatchBsmumu_fileloop.cxx -o cutBatchBsmumu_fileloop `root-config --glibs --cflags`

cutBatchBsmumu_fileloop_oldnTuples.exe: cutBatchBsmumu_fileloop_oldnTuples.cxx
	g++ cutBatchBsmumu_fileloop_oldnTuples.cxx -o cutBatchBsmumu_fileloop_oldnTuples `root-config --glibs --cflags`

Run1doca3Macro.exe: Run1doca3Macro.cpp
	g++ Run1doca3Macro.cpp -o Run1doca3Macro `root-config --glibs --cflags`

definitionsDICT.cxx: *.hh
	rootcint -f $@ -c -p $^

clean:
	rm -f *.o *.so *.lib *.pcm *DICT* *.exe *.pdf
