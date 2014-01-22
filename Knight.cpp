// Bryan Liu (chl312), Dept. of Computing, Imperial College London
// Knight.cpp - implementation of Knight extending Piece (info in Knight.hpp)

#include "Knight.hpp"

Knight::Knight (string fileRank, bool isWhitePlayer)
  : Piece (fileRank, isWhitePlayer) {

}

Knight* Knight::clone () {
  return new Knight (this -> getFileRank (), this -> isWhitePlayer ());
}

/* A Knight's move is valid iff:
   - It moves in "L"-pattern
   - The (possibly) existing piece on destination square is not a friendly
     (or destination is empty)

   Knight.isValidMove() post-cond: retrun 0 if move is valid as above
                                   respective error code otherwise
*/
int Knight::isValidMove (string destFileRank, map<string, Piece*>* board) {

  if (isSameFile(destFileRank) && isSameRank(destFileRank)) {
    return ChessErrHandler::DEST_EQ_SOURCE;
  }

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

/* Knight.movesInLShape()
   pre-cond: arg is a valid file & rank representation of a different square
   post-cond: return true iff abs file diff = 2(1) & abs rank diff = 1(2)
*/
bool Knight::movesInLShape (string destFileRank) {

  char destFile = destFileRank.at(ChessInfo::FILE_INDEX);
  char destRank = destFileRank.at(ChessInfo::RANK_INDEX);

  return abs (file-destFile) * abs (rank-destRank) == 2;
}
