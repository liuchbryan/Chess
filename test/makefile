# Bryan Liu (chl312), Dept. of Computing, Imperial College London
# makefile for Test in test directory

CFLAGS = -Wall -g -c -std=c++11

Test: bin/Piece.o bin/Pawn.o bin/Bishop.o bin/PawnTest.o bin/TestMain.o 
	g++ -Wall -g $^ -o Test

bin/TestMain.o: TestMain.cpp
	mkdir -p bin
	g++ $(CFLAGS) $^ -o $@

bin/%Test.o: header/%Test.hpp %Test.cpp
	mkdir -p bin
	g++ $(CFLAGS) $(word 2,$^) -o $@

bin/%.o: ../src/header/%.hpp ../src/%.cpp
	mkdir -p bin
	g++ $(CFLAGS) $(word 2,$^) -o $@

clean:
	rm -rf Test bin

.PHONY: clean
