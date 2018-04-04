CC := g++
OBJSUFFIX := cpp
OBJHSUFFIX := h

RUNSUFFIX := cc
RUNHSUFFIX := hh

CFLAGS := -pipe -g -std=c++11
CLIBS := -L/usr/lib64 -lpthread 
CTEST_LIBS = -lgtest
DIR := $(CURDIR)

CINCLUDES := -I/usr/include
CINCLUDES := -I$(DIR) -I$(DIR)/src $(CINCLUDES)


OSRC := $(shell find -type f -iname '*.$(OBJSUFFIX)' )
OHSRC := $(shell find -type f -iname '*.$(OBJHSUFFIX)' )
OBJECTS := $(foreach x, $(basename $(OSRC)), $(x).o)

RSRC := $(shell find -type f -iname '*.$(RUNSUFFIX)' )
RHSRC := $(shell find -type f -iname '*.$(RUNHSUFFIX)' )
RUNS := $(foreach x, $(basename $(RSRC)), $(x).run)
TESTS := $(foreach x, $(basename $(RUNS)), $(x).test)

test: $(TESTS)

all: $(OBJECTS) $(RUNS)

clean:
	rm -f $(OBJECTS) $(RUNS)

%.o: %.cpp $(OHSRC)
	$(CC) $(CFLAGS) -c $< -o $@ $(CINCLUDES)

%.run: %.cc $(OBJECTS)
	$(CC) $(CFLAGS) $< -o $@ $(CLIBS) $(CTEST_LIBS) $(CINCLUDES) $(OBJECTS)  

%.test: %.run
	./$< > $@