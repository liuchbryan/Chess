#ifndef EMPTYPIECE_H
#define EMPTYPIECE_H

#include <map>
#include <string>

#include "Piece.hpp"

using namespace std;

class EmptyPiece : public Piece {

  public:
    EmptyPiece (bool isWhitePlayer);
    EmptyPiece* clone ();

    int isValidMove 
      (string sourceFileRank, string destFileRank, map<string, Piece*>* board);
    string toString ();
    string toGraphics ();
};

#endif
