
#include "Bishop.hpp"

Bishop::Bishop (string fileRank, bool isWhitePlayer)
  : Piece (fileRank, isWhitePlayer) {

}

int Bishop::isValidMove (string destFileRank, map<string, Piece*>* board) {
  
  if (!isSameDiagonal (destFileRank)) {
    return ChessErrHandler::ILLEGAL_MOVE_PATTERN;
  }
  
  if (!noDiagonalObstruction (destFileRank, board)) {
    return ChessErrHandler::OBSTRUCTION_EN_ROUTE;
  }

  if (destExistFriendlyPiece (destFileRank, board)) {
    return ChessErrHandler::FRIENDLY_AT_DEST;
  }

  return ChessErrHandler::NO_ERROR;
}

string Bishop::toString () {
  
  string name (playerToString());
  name.append(" Bishop");
  return name;  
}
