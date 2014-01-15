#ifndef KNIGHT_H
#define KNIGHT_H

#include <map>
#include <string>

#include "Piece.hpp"

class Knight : public Piece {

  private:


  public:
    Knight (string fileRank, bool isWhitePlayer);
    bool isValidMove (string destFileRank, map<string, Piece*>* board);
    string toString ();
  
  private:

};

#endif
