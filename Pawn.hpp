// Bryan Liu (chl312), Dept. of Computing, Imperial College London
// Pawn.hpp - Pawn extending Piece

/* Represent Implementation of a Pawn piece in chess
   Including concrete implementation of isValidMove() and toString()
     inherited from abstract superclass Piece
   Private variable isFirstMove and method isAdjacentFile() used in logic of
     validing move of a Pawn
*/

#ifndef PAWN_H
#define PAWN_H

#include <map>
#include <string>

#include "Piece.hpp"

class Pawn : public Piece {

  private:
    bool isFirstMove = true;

  public:
    Pawn (string fileRank, bool isWhitePlayer);
    int isValidMove (string destFileRank, map<string, Piece*>* board);
    string toString ();
  
  private:
    bool isAdjacentFile (string thatFileRank);
};

#endif
