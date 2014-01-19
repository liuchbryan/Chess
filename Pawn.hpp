#ifndef PAWN_H
#define PAWN_H

#include <map>
#include <string>

#include "Piece.hpp"

class Pawn : public Piece {

  private:
    bool isFirstMove = true;

  public:
    Pawn (string fileRank, bool isWhitePlayer);
    int isValidMove (string destFileRank, map<string, Piece*>* board);
    string toString ();
  
  private:
    bool isAdjacentFile (string thatFileRank);
};

#endif
