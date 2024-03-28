all: libgeneric.so

genericDict.cxx: generic.h Linkdef.h
	rootcint -f $@ -c $(CXXFLAGS) -p $^
libgeneric.so: genericDict.cxx
	g++ -shared -fPIC -o $@ `root-config --cflags --glibs` $(CXXFLAGS) -I$(ROOTSYS)/include $^
clean:
	rm -f genericDict* *.so

