CXX		= g++
CXXFLAGS	= -g -Wall
OBJS		= lexer.o syntax.cpp
PROG		= scc

all:		$(PROG)

$(PROG):	$(OBJS)
		$(CXX) -o $(PROG) $(OBJS)

clean:;		$(RM) -f $(PROG) core *.o
