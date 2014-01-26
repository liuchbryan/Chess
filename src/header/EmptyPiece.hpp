// Bryan Liu (chl312), Dept. of Computing, Imperial College London
// EmptyPiece.hpp - EmptyPiece extending Piece

/* The Concrete Implementation of Piece, utilising Null Object Pattern
   Including concrete implementation of clone(), isValidMove(), toString()
     and toGraphics(), inherited from abstract superclass Piece
*/

#ifndef EMPTYPIECE_H
#define EMPTYPIECE_H

#include <map>
#include <string>

#include "Piece.hpp"

using namespace std;

class EmptyPiece : public Piece {

  public:
    EmptyPiece (bool isWhitePlayer);
    ~EmptyPiece ();
    EmptyPiece* clone ();

    int isValidMove 
      (string sourceFileRank, string destFileRank, map<string, Piece*>* board);
    string toString ();
    string toGraphics ();
};

#endif
