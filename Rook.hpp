// Bryan Liu (chl312), Dept. of Computing, Imperial College London
// Rook.hpp - Rook extending Piece

/* Represent Implementation of a Rook piece in chess
   Including concrete implementation of isValidMove() and toString()
     inherited from abstract superclass Piece
*/

#ifndef ROOK_H
#define ROOK_H

#include <map>
#include <string>

#include "Piece.hpp"

class Rook : public Piece {

  public:
    Rook (string fileRank, bool isWhitePlayer);
    int isValidMove (string destFileRank, map<string, Piece*>* board);
    string toString ();
};

#endif
