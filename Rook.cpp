
#include "Rook.hpp"

Rook::Rook (string fileRank, bool isWhitePlayer)
  : Piece (fileRank, isWhitePlayer) {

}

int Rook::isValidMove (string destFileRank, map<string, Piece*>* board) {
  
  return ChessErrHandler::ILLEGAL_MOVE_PATTERN;
}

string Rook::toString () {
  
  string name (playerToString());
  name.append(" Rook");
  return name;  
}
