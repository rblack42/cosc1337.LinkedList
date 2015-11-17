# Makefile for Linked List class

# application names ---------------------------------------
APP		= demo
TEST	= test

# project directory names ---------------------------------
SRC 	= src
LIB		= lib
TESTS	= tests
INCS	= includes

# do not modify anything below this point -----------------
CFLAGS	= -I $(INCS)
include makevars/system.mak
include makevars/files.mak

DEMOAPP = $(APP)$(EXT)
TESTAPP	= $(TEST)$(EXT)

# build targets follow ------------------------------------

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

-include $(DEPENDS)
