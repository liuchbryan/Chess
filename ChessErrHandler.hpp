#ifndef CHESSERRHANDLER_H
#define CHESSERRHANDLER_H

#include <string>
#include <iostream>

#include "Piece.hpp"

class ChessErrHandler {

  public:   
    static const int NO_ERROR = 0;
    static const int DEST_EQ_SOURCE = 10;
    static const int SOURCE_OUTOF_BOUND = 11;
    static const int DEST_OUTOF_BOUND = 12;
    static const int NOT_OWNER_TURN = 20;
    static const int MOVED_EMPTY_PIECE = 30;
    static const int ILLEGAL_MOVE_PATTERN = 40;
    static const int OBSTRUCTION_EN_ROUTE = 41;
    static const int FRIENDLY_AT_DEST = 42;

  public:
    ChessErrHandler ();
    void printErr 
      (int errNo, Piece* piece, string sourceFileRank, string destFileRank); 

};

#endif
