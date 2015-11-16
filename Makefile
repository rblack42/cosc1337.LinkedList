# Makefile for Linked List class

EXT		= .exe

APP		= demo
TEST	= test

DEMOAPP = $(APP)$(EXT)
TESTAPP	= $(TEST)$(EXT)

SRC 	= src
LIB		= lib
TEST	= tests
INCS	= includes

include makevars/files.mak

# tool definitions

CXX		= g++
AR		= ar
COV		= gcov

CFLAGS	= -MMD -I$(INCS) -std=c++11

# build targets follow

all:	$(DEMOAPP) $(TESTAPP)

$(TESTAPP):		$(TESTOBJS) $(LIBOBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(DEMOAPP):		$(APPOBJS) $(LIBOBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

docs:
	cd documentation && make html

# implicit rules follow
%.o:	%.cpp
	$(CXX) -c $(CFLAGS) $< -o $@

debug:
	@echo "TESTOBJS = $(TESTOBJS)"

clean:
	$(RM) $(ALLOBJS) $(DEMOAPP) $(TESTAPP)

include $(DEPENDS)
