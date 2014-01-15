
#include "EmptyPiece.hpp"

EmptyPiece::EmptyPiece (string fileRank, bool isWhitePlayer) 
  : Piece(fileRank, isWhitePlayer) {

}

bool EmptyPiece::isValidMove (string destFileRank, map<string, Piece*>* board) {
  
  return false;
}

string EmptyPiece::toString () {
  
  return string ("Empty Piece");  
}
