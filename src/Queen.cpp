// Bryan Liu (chl312), Dept. of Computing, Imperial College London
// Queen.cpp - implementation of Queen extending Piece (info in Queen.hpp)

#include "header/Queen.hpp"

Queen::Queen (bool isWhitePlayer) : Piece (isWhitePlayer) {

}

Queen::~Queen () {

}

Queen* Queen::clone () {
  return new Queen (this -> isWhitePlayer());
}

/* A Queen's move is valid iff:
   - Destination is on the same file/rank/diagonal (note: mutually exclusive)
   - There are no other pieces in intermediate spaces
   - Piece at destination, if exist, is not a friendly
     (or there are no piece at destination)

   Queen.isValidMove() post-cond: return 0 iff move is valid
                                  respective error code otherwise
*/
int Queen::isValidMove 
  (string sourceFileRank, string destFileRank, map<string, Piece*>* board) {

  if (isSameFile(sourceFileRank, destFileRank) && 
      isSameRank(sourceFileRank, destFileRank)) {
    return ChessErrHandler::DEST_EQ_SOURCE;
  }

  if (!(isSameFile (sourceFileRank, destFileRank) || 
        isSameRank (sourceFileRank, destFileRank) ||
        isSameDiagonal (sourceFileRank, destFileRank))) {
    return ChessErrHandler::ILLEGAL_MOVE_PATTERN;
  }

  /* Obstruction for a Queen only occurs if it is on its intended way
     Lazy boolean evalution of C++ ensure !no_Obstruction is evaluated
      only after isSame_ is satisfied, preventing breaking pre-cond of
      no_Obstruction methods
  */
  if ((isSameFile (sourceFileRank, destFileRank) && 
       !noVerticalObstruction (sourceFileRank, destFileRank, board)) ||
      (isSameRank (sourceFileRank, destFileRank) &&
       !noHorizontalObstruction (sourceFileRank, destFileRank, board)) ||
      (isSameDiagonal (sourceFileRank, destFileRank) &&
       !noDiagonalObstruction (sourceFileRank, destFileRank, board))) {
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

string Queen::toGraphics () {
  
  if (_isWhitePlayer) {
    return string("♕");
  }
  return string("♛");
}
