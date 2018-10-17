
CC=gcc
CFLAGS=-Wall -Werror
BINS=testGraph

all: $(BINS)

#testGraph : testList.o DLList.o
	#$(CC) -o testL testList.o DLList.o

testGraph : graph.o graphList.o
	$(CC) -o testGraph graph.o graphList.o

graphList.o : graphList.c graphList.h

graph.o : graph.c graph.h

#myed.o : myed.c DLList.h

#testList.o : testGraph.c graphList.h graph.h

clean:
	rm -f $(BINS) *.o core
