# Skeleton makefile for the C++ Chess exercise.
# Make sure that you add any new files you create to this makefile.

CFLAGS = -Wall -g -c -std=c++11

Chess: ChessMain.o ChessBoard.o Piece.o EmptyPiece.o
	g++ -Wall -g $^ -o Chess

ChessMain.o: ChessMain.cpp
	g++ $(CFLAGS) $^ -o $@

%.o: %.hpp %.cpp
	g++ $(CFLAGS) $(word 2,$^) -o $@

clean:
	rm -f *.o Chess

.PHONY: clean
