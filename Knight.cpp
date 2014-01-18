
#include "Knight.hpp"

Knight::Knight (string fileRank, bool isWhitePlayer)
  : Piece (fileRank, isWhitePlayer) {

}

int Knight::isValidMove (string destFileRank, map<string, Piece*>* board) {
  if (!movesInLShape (destFileRank)) {
    return ChessErrHandler::ILLEGAL_MOVE_PATTERN;
  }

  if (destExistFriendlyPiece (destFileRank, board)) {
    return ChessErrHandler::FRIENDLY_AT_DEST;
  }

  return ChessErrHandler::NO_ERROR;
}

string Knight::toString () {
  
  string name (playerToString ());
  name.append(" Knight");
  return name;  
}

bool Knight::movesInLShape (string destFileRank) {

  char destFile = destFileRank.at(ChessInfo::FILE_INDEX);
  char destRank = destFileRank.at(ChessInfo::RANK_INDEX);

  return abs (file-destFile) * abs (rank-destRank) == 2;
}
