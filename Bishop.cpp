
#include "Bishop.hpp"

Bishop::Bishop (string fileRank, bool isWhitePlayer)
  : Piece (fileRank, isWhitePlayer) {

}

int Bishop::isValidMove (string destFileRank, map<string, Piece*>* board) {
  
  return ChessErrHandler::ILLEGAL_MOVE_PATTERN;
}

string Bishop::toString () {
  
  string name (playerToString());
  name.append(" Bishop");
  return name;  
}
