
#include "Knight.hpp"

Knight::Knight (string fileRank, bool isWhitePlayer)
  : Piece (fileRank, isWhitePlayer) {

}

int Knight::isValidMove (string destFileRank, map<string, Piece*>* board) {
  char destFile = destFileRank.at(ChessInfo::FILE_INDEX);
  char destRank = destFileRank.at(ChessInfo::RANK_INDEX);

  if (abs(file-destFile) * abs(rank-destRank) != 2) {
    return ChessErrHandler::ILLEGAL_MOVE_PATTERN;
  }


// Involve refactoring
  try {
    Piece* destPiece = board->at(destFileRank);
    if (isFriendly(destPiece)) {
      return ChessErrHandler::FRIENDLY_AT_DEST;
    }
  } catch (const std::out_of_range &err) {
     
  }
  
  return ChessErrHandler::NO_ERROR;
}

string Knight::toString () {
  
  string name (playerToString());
  name.append(" Knight");
  return name;  
}
