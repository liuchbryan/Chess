
#include "Pawn.hpp"

Pawn::Pawn (string fileRank, bool isWhitePlayer)
  : Piece (fileRank, isWhitePlayer) {

}

bool Pawn::isValidMove (string destFileRank, map<string, Piece*>* board) {
  
  return false;
}

string Pawn::toString () {
  
  string name (playerToString());
  name.append(" Pawn");
  return name;  
}
