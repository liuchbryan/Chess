
#include "Rook.hpp"

Rook::Rook (string fileRank, bool isWhitePlayer)
  : Piece (fileRank, isWhitePlayer) {

}

bool Rook::isValidMove (string destFileRank, map<string, Piece*>* board) {
  
  return false;
}

string Rook::toString () {
  
  string name (playerToString());
  name.append(" Rook");
  return name;  
}
