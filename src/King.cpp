// Bryan Liu (chl312), Dept. of Computing, Imperial College London
// King.cpp - implementation of King extending Piece (info in King.hpp)

#include "header/King.hpp"

King::King (bool isWhitePlayer) : Piece (isWhitePlayer) {
  _isKing = true;
}

King::~King () {

}

King* King::clone () {
  return new King (this -> isWhitePlayer ());
}

/* A King's move is valid iff:
   - The destination is on its adjacent square
   - The (possibly) existing piece at destination is not a friendly
     (or destination is empty)

   King.isValidMove() post-cond: retrun 0 if move is valid as above
                                 respective error code otherwise
*/
int King::isValidMove 
  (string sourceFileRank, string destFileRank, map<string, Piece*>* board) {

  if (isSameFile(sourceFileRank, destFileRank) && 
      isSameRank(sourceFileRank, destFileRank)) {
    return ChessErrHandler::DEST_EQ_SOURCE;
  }
  
  if (!isAdjacentSquare (sourceFileRank, destFileRank)) {
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

string King::toGraphics () {
  if (_isWhitePlayer) {
    return string("♔");
  }
  return string("♚");
}

/* King.isAdjacentSquare():
   pre-cond: args are valid file & rank representations of a different square
   post-cond: return true iff the displacement of file and rank is at most 1
*/
bool King::isAdjacentSquare (string sourceFileRank, string destFileRank) {

  char sourceFile = sourceFileRank.at(ChessInfo::FILE_INDEX);
  char sourceRank = sourceFileRank.at(ChessInfo::RANK_INDEX);  
  char destFile = destFileRank.at(ChessInfo::FILE_INDEX);
  char destRank = destFileRank.at(ChessInfo::RANK_INDEX);

  return max (abs (destFile - sourceFile), abs (destRank - sourceRank)) == 1;
}
