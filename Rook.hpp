#ifndef ROOK_H
#define ROOK_H

#include <map>
#include <string>

#include "Piece.hpp"

class Rook : public Piece {

  private:


  public:
    Rook (string fileRank, bool isWhitePlayer);
    int isValidMove (string destFileRank, map<string, Piece*>* board);
    string toString ();
  
  private:

};

#endif
