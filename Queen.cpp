
#include "Queen.hpp"

Queen::Queen (string fileRank, bool isWhitePlayer)
  : Piece (fileRank, isWhitePlayer) {

}

int Queen::isValidMove (string destFileRank, map<string, Piece*>* board) {
  
  return ChessErrHandler::ILLEGAL_MOVE_PATTERN;
}

string Queen::toString () {
  
  string name (playerToString());
  name.append(" Queen");
  return name;  
}
