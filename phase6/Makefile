CXX		= g++
CXXFLAGS	= -g -Wall
OBJS		= allocator.o checker.o generator.o lexer.o parser.o \
		  Scope.o Symbol.o Tree.o Type.o
PROG		= scc

all:		$(PROG)

$(PROG):	$(OBJS)
		$(CXX) -o $(PROG) $(OBJS)

clean:;		$(RM) -f $(PROG) core *.o
