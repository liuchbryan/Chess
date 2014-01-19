// Bryan Liu (chl312), Dept. of Computing, Imperial College London
// Knight.hpp - Knight extending Piece

/* Represent Implementation of a Knight piece in chess
   Including concrete implementation of isValidMove() and toString()
     inherited from abstract superclass Piece
   Private method movesInLShape() used in logic of validing move of a Knight
*/

#ifndef KNIGHT_H
#define KNIGHT_H

#include <map>
#include <string>

#include "Piece.hpp"

class Knight : public Piece {

  public:
    Knight (string fileRank, bool isWhitePlayer);
    int isValidMove (string destFileRank, map<string, Piece*>* board);
    string toString ();
  
  private:
    bool movesInLShape (string destFileRank);
};

#endif
