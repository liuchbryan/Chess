
#include "Knight.hpp"

Knight::Knight (string fileRank, bool isWhitePlayer)
  : Piece (fileRank, isWhitePlayer) {

}

bool Knight::isValidMove (string destFileRank, map<string, Piece*>* board) {
  
  return false;
}

string Knight::toString () {
  
  string name (playerToString());
  name.append(" Knight");
  return name;  
}
