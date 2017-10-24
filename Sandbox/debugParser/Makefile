# makefile
# use to compile and test the assembler ASM for the STACK computer and
# its various components

DEBUG_FLAG= -DDEBUG -g -Wall
CFLAGS=-DDEBUG -g -Wall

.SUFFIXES: .cpp .o

.cpp.o:
	g++ $(CFLAGS) -c $<


TEST: ScanParser_test.o Scan.o ScanParser.o 
	g++ -o TEST ScanParser_test.o Scan.o ScanParser.o 

ScanParser.o: ScanParser.h Scan.h

Scan.o: Scan.h 


clean:
	/bin/rm -f TEST *.o core


