# Bryan Liu (chl312), Dept. of Computing, Imperial College London
# makefile for Test in test directory

CFLAGS = -Wall -g -c -std=c++11

Test: bin/PawnTest.o bin/TestMain.o
	g++ -Wall -g $^ -o Test

bin/TestMain.o: TestMain.cpp
	mkdir -p bin
	g++ $(CFLAGS) $^ -o $@

bin/%.o: header/%.hpp %.cpp
	mkdir -p bin
	g++ $(CFLAGS) $(word 2,$^) -o $@

clean:
	rm -rf Test bin

.PHONY: clean
