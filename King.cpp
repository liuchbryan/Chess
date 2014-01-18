
#include "King.hpp"

King::King (string fileRank, bool isWhitePlayer)
  : Piece (fileRank, isWhitePlayer) {

}

int King::isValidMove (string destFileRank, map<string, Piece*>* board) {
  
  if (!isAdjacentSquare (destFileRank)) {
    return ChessErrHandler::ILLEGAL_MOVE_PATTERN;
  }

  if (destExistFriendlyPiece (destFileRank, board)) {
    return ChessErrHandler::FRIENDLY_AT_DEST;
  }
  
  return ChessErrHandler::NO_ERROR;
}

string King::toString () {
  
  string name (playerToString());
  name.append(" King");
  return name;  
}

bool King::isAdjacentSquare (string thatFileRank) {
  
  char thatFile = thatFileRank.at(ChessInfo::FILE_INDEX);
  char thatRank = thatFileRank.at(ChessInfo::RANK_INDEX);

  return max (abs (thatFile - file), abs (thatRank - rank)) == 1;
}
