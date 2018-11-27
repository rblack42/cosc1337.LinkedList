# Makefile for Linked List class

# application names ---------------------------------------
APP		= demo
TEST	= testapp

# project directory names ---------------------------------
SRC 	= src
LIB		= lib
TESTS	= tests
INCS	= includes

# do not modify anything below this point -----------------
CFLAGS	= -I $(INCS) -std=c++11
include makevars/system.mak
include makevars/files.mak

DEMOAPP = $(APP)$(EXT)
TESTAPP	= $(TEST)$(EXT)

# build targets follow ------------------------------------

.PHONY:all
all:	$(DEMOAPP) $(TESTAPP)

$(TESTAPP):		$(TESTOBJS) $(LIBOBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(DEMOAPP):		$(APPOBJS) $(LIBOBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

.PHONY: docs
docs:
	cd documentation && make html

# implicit rules follow
%.o:	%.cpp
	$(CXX) -c $(CFLAGS) $< -o $@

.PHONY: debug
debug:
	@echo "TESTOBJS = $(TESTOBJS)"

.PHONY: clean
clean:
	$(RM) $(ALLOBJS) $(DEMOAPP) $(TESTAPP) $(DEPENDS)

.PHONY: run
run:	$(DEMOAPPT)
	$(PREFIX)$(DEMOAPP)

.PHONY: test
test:	$(TESTAPP)
	$(PREFIX)$(TESTAPP)

-include $(DEPENDS)
