#ifndef KING_H
#define KING_H

#include <map>
#include <string>

#include "Piece.hpp"

class King : public Piece {

  private:


  public:
    King (string fileRank, bool isWhitePlayer);
    bool isValidMove (string destFileRank, map<string, Piece*>* board);
    string toString ();
  
  private:

};

#endif
