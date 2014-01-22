// Bryan Liu (chl312), Dept. of Computing, Imperial College London
// King.cpp - implementation of King extending Piece (info in King.hpp)

#include "King.hpp"

King::King (string fileRank, bool isWhitePlayer)
  : Piece (fileRank, isWhitePlayer) {

}

King* King::clone () {
  return new King (this -> getFileRank (), this -> isWhitePlayer ());
}

/* A King's move is valid iff:
   - The destination is on its adjacent square
   - The (possibly) existing piece at destination is not a friendly
     (or destination is empty)

   King.isValidMove() post-cond: retrun 0 if move is valid as above
                                 respective error code otherwise
*/
int King::isValidMove (string destFileRank, map<string, Piece*>* board) {

  if (isSameFile(destFileRank) && isSameRank(destFileRank)) {
    return ChessErrHandler::DEST_EQ_SOURCE;
  }
  
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

/* King.isAdjacentSquare():
   pre-cond: arg is valid file & rank representation of a different square
   post-cond: return true iff the displacement of file and rank is at most 1
*/
bool King::isAdjacentSquare (string thatFileRank) {
  
  char thatFile = thatFileRank.at(ChessInfo::FILE_INDEX);
  char thatRank = thatFileRank.at(ChessInfo::RANK_INDEX);

  return max (abs (thatFile - file), abs (thatRank - rank)) == 1;
}
