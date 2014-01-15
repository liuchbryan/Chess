#ifndef PAWN_H
#define PAWN_H

#include <map>
#include <string>

#include "Piece.hpp"

class Pawn : public Piece {

  private:


  public:
    Pawn (string fileRank, bool isWhitePlayer);
    bool isValidMove (string destFileRank, map<string, Piece*>* board);
    string toString ();
  
  private:

};

#endif
