#-------------------------------------------------------------------------------
# Makefile			make --> creates Main.exe
#				make clean --> removes all *.o and *~
#
#
# Quarter Project Winter 2017
#-------------------------------------------------------------------------------

CC = g++
CFLAGS = -g -Wall -std=c++11 -lboost_filesystem -lboost_system -lpthread -pthread

default: Main

Main:	Main.o KB.o RB.o Transactions.o Node.o Inference_parse.o Thread.o
	$(CC) $(CFLAGS) Main.o KB.o RB.o Transactions.o Node.o Inference_parse.o Thread.o -o Main.exe

Main.o:	SRI_CLI.cpp
	$(CC) $(CFLAGS) -c SRI_CLI.cpp -o Main.o

KB.o:	KB.cpp KB.h
	$(CC) $(CFLAGS) -c KB.cpp -o KB.o

RB.o:	RB.cpp KB.h
	$(CC) $(CFLAGS) -c RB.cpp -o RB.o

Inference_parse.o:   Inference_parse.cpp Inference_parse.h
	$(CC) $(CFLAGS) -c Inference_parse.cpp -o Inference_parse.o

Transactions.o:	Transactions.cpp Transactions.h
	$(CC) $(CFLAGS) -c Transactions.cpp -o Transactions.o

Thread.o: Thread.cpp Thread.h
	$(CC) $(CFLAGS) -c Thread.cpp -o Thread.o

Node.o:	Node.cpp Node.h
	$(CC) $(CFLAGS) -c Node.cpp -o Node.o

clean:
	$(RM) Main *.o *~


