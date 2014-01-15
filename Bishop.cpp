
#include "Bishop.hpp"

Bishop::Bishop (string fileRank, bool isWhitePlayer)
  : Piece (fileRank, isWhitePlayer) {

}

bool Bishop::isValidMove (string destFileRank, map<string, Piece*>* board) {
  
  return false;
}

string Bishop::toString () {
  
  string name (playerToString());
  name.append(" Bishop");
  return name;  
}
