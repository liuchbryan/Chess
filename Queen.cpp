
#include "Queen.hpp"

Queen::Queen (string fileRank, bool isWhitePlayer)
  : Piece (fileRank, isWhitePlayer) {

}

int Queen::isValidMove (string destFileRank, map<string, Piece*>* board) {

  if (!(isSameFile (destFileRank) || isSameRank (destFileRank) ||
        isSameDiagonal (destFileRank))) {
    return ChessErrHandler::ILLEGAL_MOVE_PATTERN;
  }

  if ((isSameFile (destFileRank) && 
       !noVerticalObstruction (destFileRank, board)) ||
      (isSameRank (destFileRank) &&
       !noHorizontalObstruction (destFileRank, board)) ||
      (isSameDiagonal (destFileRank) &&
       !noDiagonalObstruction (destFileRank, board))) {
    return ChessErrHandler::OBSTRUCTION_EN_ROUTE;
  }
  
  if (destExistFriendlyPiece (destFileRank, board)) {
    return ChessErrHandler::FRIENDLY_AT_DEST;
  }
  
  return ChessErrHandler::NO_ERROR;
}

string Queen::toString () {
  
  string name (playerToString());
  name.append(" Queen");
  return name;  
}
