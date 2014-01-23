# Skeleton makefile for the C++ Chess exercise.
# Make sure that you add any new files you create to this makefile.

CFLAGS = -Wall -g -c -std=c++11

Chess: ChessMain.o ChessBoard.o Piece.o EmptyPiece.o King.o Queen.o Bishop.o Rook.o Knight.o Pawn.o ChessErrHandler.o
	g++ -Wall -g $^ -o Chess

Test: Test.o ChessBoard.o Piece.o EmptyPiece.o King.o Queen.o Bishop.o Rook.o Knight.o Pawn.o ChessErrHandler.o
	g++ -Wall -g $^ -o Test

SampleGames: SampleGames.o ChessBoard.o Piece.o EmptyPiece.o King.o Queen.o Bishop.o Rook.o Knight.o Pawn.o ChessErrHandler.o
	g++ -Wall -g $^ -o SampleGames

ChessMain.o: ChessMain.cpp
	g++ $(CFLAGS) $^ -o $@

Test.o: Test.cpp
	g++ $(CFLAGS) $^ -o $@

SampleGames.o: SampleGames.cpp
	g++ $(CFLAGS) $^ -o $@

%.o: %.hpp %.cpp
	g++ $(CFLAGS) $(word 2,$^) -o $@

clean:
	rm -f *.o Chess Test SampleGames

.PHONY: clean
