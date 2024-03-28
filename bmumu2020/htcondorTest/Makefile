ROOTFLAGS=`root-config --cflags`
ROOTLIBS=`root-config --libs`

CXXFLAGS := -std=c++11 -Iinc
CXXFLAGS += $(ROOTFLAGS)
CXXFLAGS += -O2
CXXFLAGS += -Iinc

LIBS += $(ROOTLIBS)

all: selectbpbkg.exe

selectbpbkg.exe:selectbpbkg.cxx
	g++ selectbpbkg.cxx $(LIBS) -o selectbpbkg $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -f *.o *.so *.lib *.pcm *DICT* *.exe *.pdf
