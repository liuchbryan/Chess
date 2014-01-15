
#include "King.hpp"

King::King (string fileRank, bool isWhitePlayer)
  : Piece (fileRank, isWhitePlayer) {

}

bool King::isValidMove (string destFileRank, map<string, Piece*>* board) {
  
  return false;
}

string King::toString () {
  
  string name (playerToString());
  name.append(" King");
  return name;  
}
