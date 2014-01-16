
#include "King.hpp"

King::King (string fileRank, bool isWhitePlayer)
  : Piece (fileRank, isWhitePlayer) {

}

int King::isValidMove (string destFileRank, map<string, Piece*>* board) {
  
  return ChessErrHandler::ILLEGAL_MOVE_PATTERN;
}

string King::toString () {
  
  string name (playerToString());
  name.append(" King");
  return name;  
}
