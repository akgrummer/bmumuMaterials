#==========================================================================
#
# Makefile for mvaBsmumu (BDT training for Bsmumu analysis)
# (modified version of the BsMuMuNtupleReader by W. Walkowiak)
#
# author : W. Walkowiak, 2011-04-03
# changed: I. Ibragimov, 2016-11-24
#
# (c) Siegen University
#
# [Based on ROOT: http://root.cern.ch]
#
# $Id: Makefile 176 2011-05-18 17:29:48Z WolfgangWalkowiak $
#
#==========================================================================
#
# Makefile for the ROOT test programs.
# This Makefile shows nicely how to compile and link applications
# using the ROOT libraries on all supported platforms.
#
# Copyright (c) 2000 Rene Brun and Fons Rademakers
#
# Author: Fons Rademakers, 29/2/2000
#

ROOTCONFIG   := root-config
ARCH         := $(shell $(ROOTCONFIG) --arch)
PLATFORM     := $(shell $(ROOTCONFIG) --platform)

CXX           =
ObjSuf        = o
SrcSuf        = cxx
HdrSuf        = h
ExeSuf        =
DllSuf        = so
OutPutOpt     = -o

PROGNAME   = runMVA

LIBNAME    = mvaInterface

SRCDIR     = src
HDRDIR     = inc
OBJDIR     = obj
LIBDIR     = lib
BINDIR     = bin

DLLFILE    = lib$(LIBNAME).$(DllSuf)

SRCFILES = $(wildcard $(SRCDIR)/*.$(SrcSuf))
HDRFILES = $(wildcard $(HDRDIR)/*.$(HdrSuf))
LinkDef  = $(wildcard $(HDRDIR)/*_LinkDef.h) $(wildcard $(SRCDIR)/*_LinkDef.h)

EXTRAINCLUDES =
# EXTRAINCLUDES = -I$(HOME)/root/includes/

HTMLDOCDIR = htmldoc
WEBDAVURL  = https://dfs.cern.ch/dfs/websites/i/ibragimo/mvaBsmumu

ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLIBS     := $(shell root-config --libs)
ROOTGLIBS    := $(shell root-config --glibs) -lTMVA -lMinuit -lXMLIO -lMLP -lTreePlayer

ifeq ($(findstring linux, $(ARCH)),linux)
# Linux with gcc 4.9x
CXX           = g++
CXXFLAGS      = -O -Wall -fPIC -Wno-deprecated
#-Wno-deprecated to suppress 'deprecated' warnings. TS 6.6.6
LD            = g++
LDFLAGS       = -O
SOFLAGS       = -shared
endif

ifeq ($(PLATFORM),macosx)
MACOSX_MINOR := $(shell sw_vers | sed -n 's/ProductVersion://p' | cut -d . -f 2)
ifeq ($(MACOSX_DEPLOYMENT_TARGET),)
MACOSXTARGET := 10.$(MACOSX_MINOR)
else
MACOSXTARGET := $(MACOSX_DEPLOYMENT_TARGET)
endif
endif

ifeq ($(ARCH),macosx64)
# MacOS X >= 10.4 with gcc 64 bit mode (GNU gcc 4.*)
# Only specific option (-m64) comes from root-config

CXX           = g++
CXXFLAGS      = -O -pipe -Wall
LD            = g++
LDFLAGS       = -O -mmacosx-version-min=$(MACOSXTARGET)
# The SOFLAGS will be used to create the .dylib,
# the .so will be created separately
ifeq ($(subst $(MACOSX_MINOR),,1234),1234)
DllSuf        = so
else
DllSuf        = dylib
endif
SOFLAGS       = -dynamiclib -single_module -undefined dynamic_lookup -install_name 
endif
ifeq ($(CXX),)
$(error $(ARCH) invalid architecture)
endif

CXXFLAGS     += $(ROOTCFLAGS)
CXXFLAGS     += $(EXTRAINCLUDES)
LIBS          = $(ROOTLIBS) $(SYSLIBS)
GLIBS         = $(ROOTGLIBS) $(SYSLIBS)

# LIBS          = $(ROOTLIBS) -lm -ldl -rdynamic
# GLIBS         = $(ROOTLIBS) $(ROOTGLIBS) -L/usr/X11R6/lib \
#                 -lXpm -lX11 -lm -ldl -rdynamic

#------------------------------------------------------------------------------

PSRC        := $(SRCDIR)/$(PROGNAME).$(SrcSuf)
POBJ        := $(OBJDIR)/$(PROGNAME).$(ObjSuf)
SRCFILES    := $(patsubst $(PSRC),,$(SRCFILES))

ALLSOURCES  := $(SRCFILES) $(SRCDIR)/$(LIBNAME)Dict.$(SrcSuf)

OBJS        := $(patsubst %.$(SrcSuf), %.$(ObjSuf), $(ALLSOURCES))
OBJS        := $(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(OBJS))

HFILES      := $(HDRFILES)

DLLFILE     := $(patsubst %, $(LIBDIR)/%, $(DLLFILE))
PROG        := $(patsubst %, $(BINDIR)/%, $(PROGNAME))


PROGRAMS     = $(DLLFILE) $(PROG)

ifeq ($(ARCH),macosx64)
SOFLAGS     += $(patsubst %, $(CURDIR)/%, $(DLLFILE))
endif

$(shell mkdir -p $(BINDIR))
$(shell mkdir -p $(OBJDIR))
$(shell mkdir -p $(LIBDIR))
#------------------------------------------------------------------------------

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf)
.PHONY: all clean distclean check htmldoc htmldocroot cleanhtml \
        cleandoccern lsdoccern cpdoctocern doctocern

all:           	$(PROGRAMS)
		@echo Done compiling "$(PROGRAMS)" ...

$(PROG): $(DLLFILE) $(POBJ)
		@echo "compiling $(PROG) ..."
		$(LD) $(LDFLAGS) -L $(LIBDIR) -l $(LIBNAME) \
			$(LIBS) $(GLIBS) $(POBJ) -o $@

$(DLLFILE): $(OBJS)
		@echo compiling "$(DLLFILE)"
		$(LD) $(SOFLAGS) $(LDFLAGS) $^ $(OutPutOpt) $@
		@echo "$@ done"
clean:
		@rm -f $(OBJS) $(POBJ) $(BINDIR)/* $(OBJDIR)/*Dict.* $(SRCDIR)/*Dict.* core 

distclean:      clean cleanhtml
		@rm -f $(PROGRAMS) $(SRCDIR)/*Dict.* *.def *.exp \
		   $(LIBDIR)/*.so .def so_locations 

check:
		@echo "SRCFILES    = $(SRCFILES)"
		@echo "HFILES      = $(HFILES)"
		@echo "LinkDef     = $(LinkDef)"
		@echo "OJBS        = $(OBJS)"
		@echo "ALLSOURCES  = $(ALLSOURCES)"
		@echo "SRCDIR      = $(SRCDIR)"
		@echo "rootcint    = $(SRCDIR)/%Dict.$(SrcSuf): $(SRCFILES) $(HFILES) $(LinkDef)"

cleanhtml:
		@rm -rf $(HTMLDOCDIR)/*

htmldoc: cleanhtml all
		@echo "Creating html documentation ..."
		@cd thtml && root -l -b -q ./makehtml.C\(\"../$(HTMLDOCDIR)\"\)
		@echo "HTML documentation located at >> $(HTMLDOCDIR) << ..."

htmldocroot: cleanhtml all
		@echo "Creating html documentation ..."
		@cd thtml && root -l -b -q ./makehtml.C\(\"../$(HTMLDOCDIR)\",kTRUE\)
		@echo "HTML documentation located at $(HTMLDOCDIR) ..."

cleandoccern: 
		@echo "Cleaning html docs at $(WEBDAVURL) ..."
		@./scripts/bsnt_dave -s ./scripts/bsnt_dave_clean.scr $(WEBDAVURL)

lsdoccern:
		@echo "Files at $(WEBDAVURL):"
		@./scripts/bsnt_dave -s ./scripts/bsnt_dave_ls.scr $(WEBDAVURL)

cpdoctocern:
		@echo "Copying html doc to  $(WEBDAVURL) ..."
		@./scripts/bsnt_dave -s ./scripts/bsnt_dave_copy.scr $(WEBDAVURL)
		@echo "Html docs now at $(WEBDAVURL)"

doctocern: htmldoc cleandoccern cpdoctocern

###

$(SRCDIR)/%Dict.$(SrcSuf): $(SRCFILES) $(HFILES) $(LinkDef)
	@echo "Generating dictionary $@ ..."
	rootcint -f $@ -c $(EXTRAINCLUDES) $(HFILES) $(LinkDef)

$(OBJDIR)/%.$(ObjSuf): $(SRCDIR)/%.$(SrcSuf) $(HDRDIR)/%.$(HdrSuf)
	@echo ">>> $< -> $@"
	$(CXX) $(CXXFLAGS) -I $(HDRDIR) -I $(SRCDIR)/.. -c $< $(OutPutOpt) $@

$(OBJDIR)/%.$(ObjSuf): $(SRCDIR)/%.$(SrcSuf)
	@echo ">>> $< -> $@"
	$(CXX) $(CXXFLAGS) -I $(HDRDIR) -I $(SRCDIR)/.. -c $< $(OutPutOpt) $@

