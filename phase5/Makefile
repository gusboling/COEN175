CXX		= g++
CXXFLAGS	= -g -Wall
OBJS		= checker.o lexer.o parser.o Scope.o Symbol.o Tree.o Type.o allocate.o generate.o
PROG		= scc

all:		$(PROG)

$(PROG):	$(OBJS)
		$(CXX) -o $(PROG) $(OBJS)

clean:;		$(RM) -f $(PROG) core *.o
