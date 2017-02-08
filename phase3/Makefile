CXX		= g++
CXXFLAGS	= -g -Wall
OBJS		= lexer.o parser.o checker.o type.o
PROG		= scc

all:		$(PROG)

$(PROG):	$(OBJS)
		$(CXX) -o $(PROG) $(OBJS)

clean:;		$(RM) -f $(PROG) core *.o
