// Bryan Liu (chl312), Dept. of Computing, Imperial College London
// ChessErrHandler.hpp - ChessErrHandler
/* An Error Handler which would print *helpful* error messages when required
   by Chess game engine (ChessBoard)
*/

#ifndef CHESSERRHANDLER_H
#define CHESSERRHANDLER_H

#include <string>
#include <iostream>

#include "Piece.hpp"

class ChessErrHandler {

  public:
    // The list of error codes for error hander to understand the problem
    static const int NO_ERROR = 0;
    static const int DEST_EQ_SOURCE = 10;
    static const int SOURCE_OUTOF_BOUND = 11;
    static const int DEST_OUTOF_BOUND = 12;
    static const int INVALID_FILE_RANK = 13;
    static const int MOVED_EMPTY_PIECE = 20;
    static const int NOT_OWNER_TURN = 30;
    static const int ILLEGAL_MOVE_PATTERN = 40;
    static const int OBSTRUCTION_EN_ROUTE = 41;
    static const int FRIENDLY_AT_DEST = 42;
    static const int PAWN_ILLEGAL_CAPTURE_PATTERN = 43;
    static const int ALLOW_KING_IN_CHECK = 45;
    static const int GAME_HAS_ENDED = 50;

  public:
    ChessErrHandler ();

    // print the error with one or more given information
    void printErr (int errNo, Piece* piece, 
      string sourceFileRank, string destFileRank); 
};

#endif
