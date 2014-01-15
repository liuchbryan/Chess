
#include "Queen.hpp"

Queen::Queen (string fileRank, bool isWhitePlayer)
  : Piece (fileRank, isWhitePlayer) {

}

bool Queen::isValidMove (string destFileRank, map<string, Piece*>* board) {
  
  return false;
}

string Queen::toString () {
  
  string name (playerToString());
  name.append(" Queen");
  return name;  
}
