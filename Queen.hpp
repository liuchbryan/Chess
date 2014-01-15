#ifndef QUEEN_H
#define QUEEN_H

#include <map>
#include <string>

#include "Piece.hpp"

class Queen : public Piece {

  private:


  public:
    Queen (string fileRank, bool isWhitePlayer);
    bool isValidMove (string destFileRank, map<string, Piece*>* board);
    string toString ();
  
  private:

};

#endif
