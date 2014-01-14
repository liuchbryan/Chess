#include <map>
#include <string>

#include "Piece.hpp"
#include "EmptyPiece.hpp"

EmptyPiece::EmptyPiece(string fileRank, bool owningPlayer) 
  : Piece(fileRank, owningPlayer) {

}

bool EmptyPiece::isValidMove (string destFileRank, map<string, Piece*>* board) {
  
  return false;
}
