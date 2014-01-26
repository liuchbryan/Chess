// Bryan Liu (chl312), Dept. of Computing, Imperial College London
// Bishop.hpp - Bishop extending Piece

/* Represent Implementation of a Bishop piece in chess
   Including concrete implementation of clone(), isValidMove(), toString()
     and toGraphics(), inherited from abstract superclass Piece
*/

#ifndef BISHOP_H
#define BISHOP_H

#include <map>
#include <string>

#include "Piece.hpp"

class Bishop : public Piece {

  public:
    Bishop (bool isWhitePlayer);
    ~Bishop ();
    Bishop* clone ();

    int isValidMove 
      (string sourceFileRank, string destFileRank, map<string, Piece*>* board);
    string toString ();
    string toGraphics ();
};

#endif
