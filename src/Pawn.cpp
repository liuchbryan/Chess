// Bryan Liu (chl312), Dept. of Computing, Imperial College London
// Pawn.cpp - implementation of Pawn extending Piece (info in Pawn.hpp)

#include "header/Pawn.hpp"

Pawn::Pawn (bool isWhitePlayer)
  : Piece (isWhitePlayer) {

}

Pawn::~Pawn () {

}

Pawn* Pawn::clone () {
  return new Pawn (this -> isWhitePlayer());
}

/* A Pawn has the following valid moves:
   Move vertically (advance in rank in same file): 
   Allow to advance 2 ranks iff 
    - it is its first move; and 
    - there is no obstruction in the intermediate square
   Allow to advance (1 or 2 ranks) iff
    - there is no piece at the destination square

   Capture diagonally:
   Allow move diagonally (and capture) iff
    - destination is 1 rank ahead and in adjacent file; and
    - (existing) piece in destination belongs to the rivalry

   Pawn.isValidMove() post-cond: retrun 0 if move is valid as above
                                 respective error code otherwise
*/
int Pawn::isValidMove 
  (string sourceFileRank, string destFileRank, map<string, Piece*>* board) {

  if (isSameFile(sourceFileRank, destFileRank) && 
      isSameRank(sourceFileRank, destFileRank)) {
    return ChessErrHandler::DEST_EQ_SOURCE;
  }
  
  /* Pawn is only allowed to move "forward"
     with calculations depending on which side it belongs
  */
  char destRank = destFileRank.at (ChessInfo::RANK_INDEX);
  char sourceRank = sourceFileRank.at(ChessInfo::RANK_INDEX);
  int rankAdvancement =
    _isWhitePlayer ? destRank - sourceRank : sourceRank - destRank;

  if (isSameFile (sourceFileRank, destFileRank)) {
    switch (rankAdvancement) {
      case 2: {
        if (!isFirstMove) {
          return ChessErrHandler::ILLEGAL_MOVE_PATTERN;
        }
        if (!noVerticalObstruction (sourceFileRank, destFileRank, board)) {
          return ChessErrHandler::OBSTRUCTION_EN_ROUTE;
        }
        break;
      }
      
      case 1: break;
      default: return ChessErrHandler::ILLEGAL_MOVE_PATTERN;
    }
    
    try {
      /* If no exception is thrown, a piece is occupying the destination
         Which is undesirable regardless of its friendliness
         The if clause is simply to check which error number to return
      */
      if (isFriendly (board -> at (destFileRank))) {
        return ChessErrHandler::FRIENDLY_AT_DEST;
      } else {
        return ChessErrHandler::PAWN_ILLEGAL_CAPTURE_PATTERN;
      }
    } catch (const std::out_of_range &err) {
      // No piece at destination, expected to return NO_ERROR
    }

  } else {

    try {
      if (!(rankAdvancement == 1 && 
            isAdjacentFile (sourceFileRank, destFileRank) &&
            !isFriendly (board -> at (destFileRank)))) {
        return ChessErrHandler::ILLEGAL_MOVE_PATTERN;
      }
    } catch (const std::out_of_range &err) {
      // Pawn cannot move diagonally if it is not capturing a rivalry piece
      return ChessErrHandler::ILLEGAL_MOVE_PATTERN;
    }
  }
  return ChessErrHandler::NO_ERROR;
}

string Pawn::toString () {
  
  string name (playerToString ());
  name.append(" Pawn");
  return name;  
}

string Pawn::toGraphics () {

  if (_isWhitePlayer) {
    return string("♙");
  }
  return string("♟");
}

/* Pawn.isAdjacentFile(): 
   pre-cond: args are valid file & rank representations of a different square
   post-cond: return true iff absolute file difference of args is 1
*/
bool Pawn::isAdjacentFile (string sourceFileRank, string destFileRank) {

  char sourceFile = sourceFileRank.at(ChessInfo::FILE_INDEX);
  char destFile = destFileRank.at (ChessInfo::FILE_INDEX);
  return abs (destFile - sourceFile) == 1;
}
