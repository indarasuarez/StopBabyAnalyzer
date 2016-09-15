ROOTCFLAGS    = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS      = $(shell $(ROOTSYS)/bin/root-config --libs)
ROOTGLIBS     = $(shell $(ROOTSYS)/bin/root-config --glibs)

#######################################
# -- DEFINE ARCH to something sensible!
#######################################

#
CXX           = g++
CXXFLAGS      = -g -Wall -fPIC
LD            = g++
LDFLAGS       = -g
SOFLAGS       = -shared

CXXFLAGS      += $(ROOTCFLAGS)
LIBS           = $(ROOTLIBS)

NGLIBS         = $(ROOTGLIBS)
NGLIBS        += -lMinuit
GLIBS          = $(filter-out -lNew, $(NGLIBS))

TABLEPATH      = /home/users/isuarez/Software/tableMaker
CXXFLAGS       += -I$(TABLEPATH)

FWLIB          = /home/users/isuarez/Software/MiniFWLite/libMiniFWLite.so
TABLELIB       = $(TABLEPATH)/libSimpleTable.so

COREPATH       = $(HOME)/CORE_8X
TOOLSPATH      = $(COREPATH)/Tools
DORKYPATH      = $(TOOLSPATH)/dorky

CXXFLAGS       += -I$(COREPATH)
CXXFLAGS       += -I$(TOOLSPATH)
CXXFLAGS       += -I$(DORKYPATH)

CORELIB        = $(COREPATH)/CMS3_CORE.so
STOPVARLIB     = stop_variables/StopVariables.so

MakePlots: MakePlots.o BabyLooper.o StopCMS3.o PlotMaker2D.o dataMCplotMaker.o stoputils.o BasicHistos.o PlotMakingTools.o badEventFilter.o dorky.o  MT2.o LinkDef_out.so
	$(LD) $(LDFLAGS) -o MakePlots MakePlots.o BabyLooper.o StopCMS3.o  PlotMaker2D.o dataMCplotMaker.o PlotMakingTools.o stoputils.o BasicHistos.o badEventFilter.o dorky.o MT2.o $(GLIBS) -lGenVector -lEG $(CORELIB) $(STOPVARLIB) LinkDef_out.so -Wl,-rpath,./ $(TABLELIB)
MakePlots.o: MakePlots.C BabyLooper.h
	$(CXX) $(CXXFLAGS) -c MakePlots.C
BabyLooper.o: BabyLooper.cc BabyLooper.h StopCMS3.h dataMCplotMaker.h stoputils.h dorky.h
	$(CXX) $(CXXFLAGS) -c BabyLooper.cc
stoputils.o: stoputils.cc stoputils.h 
	$(CXX) $(CXXFLAGS) -c stoputils.cc
MT2.o:MT2.cc MT2.h
	$(CXX) $(CXXFLAGS) -c MT2.cc 
BasicHistos.o: BasicHistos.cc BasicHistos.h
	$(CXX) $(CXXFLAGS) -c BasicHistos.cc
StopCMS3.o: StopCMS3.cc StopCMS3.h
	$(CXX) $(CXXFLAGS) -c StopCMS3.cc
dataMCplotMaker.o: dataMCplotMaker.cc dataMCplotMaker.h PlotMakingTools.h
	$(CXX) $(CXXFLAGS) -c dataMCplotMaker.cc
PlotMaker2D.o: PlotMaker2D.cc PlotMaker2D.h PlotMakingTools.h
	$(CXX) $(CXXFLAGS) -c PlotMaker2D.cc
PlotMakingTools.o: PlotMakingTools.C PlotMakingTools.h
	$(CXX) $(CXXFLAGS) -c PlotMakingTools.C
badEventFilter.o: badEventFilter.cc badEventFilter.h
	$(CXX) $(CXXFLAGS) -c badEventFilter.cc
dorky.o: dorky.cc dorky.h
	$(CXX) $(CXXFLAGS) -c dorky.cc
LinkDef_out.so: LinkDef.h
	@rootcling -v -f LinkDef.cc -c -p Math/Vector4D.h LinkDef.h
	$(CXX) $(CXXFLAGS) $(SOFLAGS) LinkDef.cc -o $@
.PHONY: clean
clean:  
	rm -v -f \
	runBabyMaker \
	*o *d *.so; echo "Done"
junk:
	rm  -v -f \
	*pdf *png *tex *txt *root
