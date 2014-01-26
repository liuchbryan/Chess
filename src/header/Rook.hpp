// Bryan Liu (chl312), Dept. of Computing, Imperial College London
// Rook.hpp - Rook extending Piece

/* Represent Implementation of a Rook piece in chess
   Including concrete implementation of clone(), isValidMove(), toString()
     and toGraphics(), inherited from abstract superclass Piece
*/

#ifndef ROOK_H
#define ROOK_H

#include <map>
#include <string>

#include "Piece.hpp"

class Rook : public Piece {

  public:
    Rook (bool isWhitePlayer);
    ~Rook ();
    Rook* clone ();

    int isValidMove 
      (string sourceFileRank, string destFileRank, map<string, Piece*>* board);
    string toString ();
    string toGraphics ();
};

#endif
