ROOTFLAGS=`root-config --cflags`
ROOTLIBS=`root-config --libs`

BIN_DIR := bin
CXXFLAGS := -std=c++11 -Iinc
CXXFLAGS += $(ROOTFLAGS)
CXXFLAGS += -O2
CXXFLAGS += -Iinc

LDFLAGS := -lcurl
LIBS += $(ROOTLIBS)

$(shell mkdir -p $(BIN_DIR))

all: $(patsubst src/%.cpp,bin/%,$(wildcard src/*.cpp))

$(BIN_DIR)/%: src/%.cpp
	$(CXX) $(LIBS) -o $@ $< $(CXXFLAGS) $(LDFLAGS)
