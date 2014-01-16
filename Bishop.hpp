#ifndef BISHOP_H
#define BISHOP_H

#include <map>
#include <string>

#include "Piece.hpp"

class Bishop : public Piece {
  
  private:


  public:
    Bishop (string fileRank, bool isWhitePlayer);
    int isValidMove (string destFileRank, map<string, Piece*>* board);
    string toString ();

  private:

};

#endif
