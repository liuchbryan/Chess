
#include "Pawn.hpp"

Pawn::Pawn (string fileRank, bool isWhitePlayer)
  : Piece (fileRank, isWhitePlayer) {

}

int Pawn::isValidMove (string destFileRank, map<string, Piece*>* board) {
  
  return ChessErrHandler::ILLEGAL_MOVE_PATTERN;
}

string Pawn::toString () {
  
  string name (playerToString());
  name.append(" Pawn");
  return name;  
}
