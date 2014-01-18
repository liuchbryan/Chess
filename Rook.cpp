
#include "Rook.hpp"

Rook::Rook (string fileRank, bool isWhitePlayer)
  : Piece (fileRank, isWhitePlayer) {

}

int Rook::isValidMove (string destFileRank, map<string, Piece*>* board) {

  if (!(isSameFile (destFileRank) || isSameRank (destFileRank))) {
    return ChessErrHandler::ILLEGAL_MOVE_PATTERN;
  }

  if ((isSameFile (destFileRank) && 
       !noVerticalObstruction (destFileRank, board)) ||
      (isSameRank (destFileRank) &&
       !noHorizontalObstruction (destFileRank, board))) {
    return ChessErrHandler::OBSTRUCTION_EN_ROUTE;
  }
  
  if (destExistFriendlyPiece (destFileRank, board)) {
    return ChessErrHandler::FRIENDLY_AT_DEST;
  }
  
  return ChessErrHandler::NO_ERROR;
}

string Rook::toString () {
  
  string name (playerToString());
  name.append(" Rook");
  return name;  
}
