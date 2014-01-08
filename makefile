# Skeleton makefile for the C++ Chess exercise.
# Make sure that you add any new files you create to this makefile.

Chess: ChessMain.o ChessBoard.o
	g++ -Wall -g ChessMain.o ChessBoard.o -o Chess

ChessMain: ChessBoard.hpp ChessMain.cpp
	g++ -Wall -g -c ChessMain.cpp -o ChessMain.o

ChessBoard: ChessBoard.hpp ChessBoard.cpp
	g++ -Wall -g -c ChessBoard.cpp -o ChessBoard.o

clean:
	rm -f *.o Chess
