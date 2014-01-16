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
#include <stdexcept>

#include "ChessErrHandler.hpp"
#include "Piece.hpp"
#include "EmptyPiece.hpp"
#include "King.hpp"
#include "Queen.hpp"
#include "Bishop.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Pawn.hpp"

using namespace std;

class ChessBoard {

  private:
    const int ZERO = 0;
    const int FILE_INDEX = 0;
    const int RANK_INDEX = 1;

    const char MIN_FILE = 'A';
    const char MAX_FILE = 'H';

    const char MIN_RANK = '1';
    const char WHITE_INIT_PAWN_RANK = '2';
    const char MIN_INIT_EMPTY_RANK = '3';
    const char MAX_INIT_EMPTY_RANK = '6';
    const char BLACK_INIT_PAWN_RANK = '7';
    const char MAX_RANK = '8';

    map<string, Piece*>* board;
    ChessErrHandler* errorHandler;

    bool isWhiteTurn = true;
    bool isInCheck = false;

  public:
    ChessBoard();
    ~ChessBoard();

    void resetBoard();

    void submitMove(const char* fromSquare, const char* toSquare);

  private:
    bool sourceAndDestIsValid (string sourceFileRank, string destFileRank);
    bool withinChessBoard (string destFileRank);

    bool sourceIsNotEmpty (string fileRank);
    bool isCurrentPlayerPiece (Piece* piece);
    void handleInvalidMove (int returnCode, Piece* piece, 
                            string sourceFileRank, string destFileRank);

    void switchPlayers ();

};

#endif
