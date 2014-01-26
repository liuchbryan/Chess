// Bryan Liu (chl312), Dept. of Computing, Imperial College London
// Bishop.cpp - implementation of Bishop extending Piece (info in Bishop.hpp)

#include "header/Bishop.hpp"

Bishop::Bishop (bool isWhitePlayer) : Piece (isWhitePlayer) {

}

Bishop::~Bishop () {

}

Bishop* Bishop::clone () {
  return new Bishop (this -> isWhitePlayer());
}

/* A Bishop's move is valid iff:
   - The destination is on the same diagonal as its current position
   - There is no obstruction (any piece) in intermediate squares
   - The (possibly) existing piece on destination square is not a friendly
     (or destination is empty)

   Bishop.isValidMove() post-cond: retrun 0 if move is valid as above
                                   respective error code otherwise
*/
int Bishop::isValidMove
  (string sourceFileRank, string destFileRank, map<string, Piece*>* board) {

  if (isSameFile(sourceFileRank, destFileRank) && 
      isSameRank(sourceFileRank, destFileRank)) {
    return ChessErrHandler::DEST_EQ_SOURCE;
  }
 
  if (!isSameDiagonal (sourceFileRank, destFileRank)) {
    return ChessErrHandler::ILLEGAL_MOVE_PATTERN;
  }
  
  if (!noDiagonalObstruction (sourceFileRank, destFileRank, board)) {
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

string Bishop::toGraphics () {
  if (_isWhitePlayer) {
    return string("♗");
  }
  return string("♝");
}
