CC := g++
OBJSUFFIX := cpp
OBJHSUFFIX := h

RUNSUFFIX := cc
RUNHSUFFIX := hh

ARDUINOSUFFIX := ino

CFLAGS := -pipe -g -std=c++11
CLIBS := -L/usr/lib64 -lpthread 
CTEST_LIBS = -lgtest
DIR := $(CURDIR)

CINCLUDES := -I/usr/include
CINCLUDES := -I$(DIR)/src -I$(DIR)/linux $(CINCLUDES)


OSRC := $(shell find -type f -iname '*.$(OBJSUFFIX)' )
OHSRC := $(shell find -type f -iname '*.$(OBJHSUFFIX)' )
OBJECTS := $(foreach x, $(basename $(OSRC)), $(x).o)

RSRC := $(shell find -type f -iname '*.$(RUNSUFFIX)' )
RHSRC := $(shell find -type f -iname '*.$(RUNHSUFFIX)' )
RUNS := $(foreach x, $(basename $(RSRC)), $(x).run)
TESTS := $(foreach x, $(basename $(RUNS)), $(x).test)

INOSRC := $(shell find -type f -iname '*.$(ARDUINOSUFFIX)' )
INOOBJ := $(foreach x, $(basename $(INOSRC)), $(x).ao)

test: $(TESTS)

all: $(OBJECTS) $(RUNS)

ino: $(INOOBJ)

clean:
	rm -f $(OBJECTS) $(RUNS) $(TESTS) $(INOOBJ)

%.o: %.cpp $(OHSRC)
	$(CC) $(CFLAGS) -c $< -o $@ $(CINCLUDES)

%.ao: %.ino $(OBJECTS)
	cp -f linux/template $<.cxx
	cat $< >> $<.cxx
	$(CC) $(CFLAGS) $<.cxx -o $@ $(CLIBS) $(CINCLUDES) $(OBJECTS)
	rm -f $<.cxx

%.run: %.cc $(OBJECTS)
	$(CC) $(CFLAGS) $< -o $@ $(CLIBS) $(CTEST_LIBS) $(CINCLUDES) $(OBJECTS)

%.test: %.run
	./$< > $@