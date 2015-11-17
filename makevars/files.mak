APPFILES	= $(wildcard $(SRC)/*.cpp)
LIBFILES	= $(wildcard $(LIB)/*.cpp)
TESTFILES	= $(wildcard $(TESTS)/*.cpp)

APPOBJS		= $(APPFILES:.cpp=.o)
LIBOBJS		= $(LIBFILES:.cpp=.o)
TESTOBJS	= $(TESTFILES:.cpp=.o)
ALLOBJS		= $(APPOBJS) $(LIBOBJS) $(TESTOBJS)

DEPENDS		= $(ALLOBJS:.o=.d)

