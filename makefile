# Bryan Liu (chl312), Dept. of Computing, Imperial College London
# makefile for (required) Chess and SampleGames (extra self-defined games)
#  in root directory level

CFLAGS = -Wall -g -c -std=c++11

Chess: bin/Piece.o bin/EmptyPiece.o bin/King.o bin/Queen.o bin/Bishop.o bin/Rook.o bin/Knight.o bin/Pawn.o bin/ChessErrHandler.o bin/ChessBoard.o bin/ChessMain.o
	g++ -Wall -g $^ -o Chess

SampleGames: bin/Piece.o bin/EmptyPiece.o bin/King.o bin/Queen.o bin/Bishop.o bin/Rook.o bin/Knight.o bin/Pawn.o bin/ChessErrHandler.o bin/ChessBoard.o bin/SampleGames.o
	g++ -Wall -g $^ -o SampleGames

bin/ChessMain.o: ChessMain.cpp
	mkdir -p bin
	g++ $(CFLAGS) $^ -o $@

bin/SampleGames.o: SampleGames.cpp
	mkdir -p bin
	g++ $(CFLAGS) $^ -o $@

bin/ChessBoard.o: ChessBoard.hpp ChessBoard.cpp
	mkdir -p bin
	g++ $(CFLAGS) $(word 2,$^) -o $@

bin/%.o: src/header/%.hpp src/%.cpp
	mkdir -p bin
	g++ $(CFLAGS) $(word 2,$^) -o $@

clean:
	rm -rf Chess SampleGames bin

.PHONY: clean
