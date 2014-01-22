#ifndef EMPTYPIECE_H
#define EMPTYPIECE_H

#include <map>
#include <string>

#include "Piece.hpp"

using namespace std;

class EmptyPiece : public Piece {

  public:
    EmptyPiece (string fileRank, bool isWhitePlayer);
    EmptyPiece* clone ();

    int isValidMove (string destFileRank, map<string, Piece*>* board);
    string toString ();

  private:

};

#endif
