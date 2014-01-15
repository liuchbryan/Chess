#ifndef EMPTYPIECE_H
#define EMPTYPIECE_H

#include <map>
#include <string>

#include "Piece.hpp"

using namespace std;

class EmptyPiece : public Piece {

  public:
    EmptyPiece(string fileRank, bool owningPlayer);
    bool isValidMove (string destFileRank, map<string, Piece*>* board);

  private:

};

#endif
