
#include "Knight.hpp"

Knight::Knight (string fileRank, bool isWhitePlayer)
  : Piece (fileRank, isWhitePlayer) {

}

int Knight::isValidMove (string destFileRank, map<string, Piece*>* board) {
  
  return ChessErrHandler::ILLEGAL_MOVE_PATTERN;
}

string Knight::toString () {
  
  string name (playerToString());
  name.append(" Knight");
  return name;  
}
