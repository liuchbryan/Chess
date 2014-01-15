// Skeleton header file, you will need to edit this for your submission.

// Your final submission must expose the constructor, deconstructor, 
// submitMove and resetBoard methods.
// You may add any additonal files/methods as you see fit
// (be sure to also include them in the makefile).


#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <map>
#include <iostream>
#include <string>

#include "Piece.hpp"
#include "EmptyPiece.hpp"

using namespace std;

class ChessBoard {

  private:
    const int ZERO = 0;
    const int FILE_INDEX = 0;
    const int RANK_INDEX = 1;

    const char MIN_FILE = 'A';
    const char MAX_FILE = 'H';
    const char MIN_RANK = '1';
    const char MAX_RANK = '8';
    const char MIN_INIT_EMPTY_RANK = '3';
    const char MAX_INIT_EMPTY_RANK = '6';
    const char BLACK_INIT_PAWN_RANK = '7';
    const char WHITE_INIT_PAWN_RANK = '8';

    map<string, Piece*>* board;
    bool _isWhiteTurn = true;

  public:
    ChessBoard();
    ~ChessBoard();

    void resetBoard();

    void submitMove(const char* fromSquare, const char* toSquare);

  private:
    bool isWhiteTurn ();
    bool isBlackTurn ();

    bool withinChessBoard (string destFileRank);

};

#endif
