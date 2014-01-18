
#include "Pawn.hpp"

Pawn::Pawn (string fileRank, bool isWhitePlayer)
  : Piece (fileRank, isWhitePlayer) {

}

/* A Pawn has the following valid moves:
   





*/

int Pawn::isValidMove (string destFileRank, map<string, Piece*>* board) {
  
  char destRank = destFileRank.at(ChessInfo::RANK_INDEX);
  int rankAdvancement =
    _isWhitePlayer ? destRank - rank : rank - destRank;

  switch (rankAdvancement) {
    case 2: {
      if (!(isSameFile(destFileRank) && isFirstMove)) {
         return ChessErrHandler::ILLEGAL_MOVE_PATTERN;
      }
      if (!noVerticalObstruction(destFileRank, board)) {
         return ChessErrHandler::OBSTRUCTION_EN_ROUTE;
      }
      break;
    }
    case 1: {
      if (isSameFile(destFileRank)) {
        try {
          if (isFriendly(board->at(destFileRank))) {
            return ChessErrHandler::FRIENDLY_AT_DEST;
          } else {
            return ChessErrHandler::PAWN_ILLEGAL_CAPTURE_PATTERN;
          }
        } catch (const std::out_of_range &err) {

        }
      } else {
        if (!canDiagonallyCapture(destFileRank, board)) {
          return ChessErrHandler::ILLEGAL_MOVE_PATTERN;
        }
      }
      break;
    }
    default: return ChessErrHandler::ILLEGAL_MOVE_PATTERN;
  }

  isFirstMove = false;
  return ChessErrHandler::NO_ERROR;
}

string Pawn::toString () {
  
  string name (playerToString());
  name.append(" Pawn");
  return name;  
}

/* A pawn can move diagonally (i.e. advance 1 rank and not in same file) iff:
   the destination file is adjacent to the current file (abs diff = 1), and
   the (non-empty) piece in destination is not a friendly (can capture)
*/
bool Pawn::canDiagonallyCapture 
  (string destFileRank, map<string, Piece*>* board) {
  
  try {
    if (isAdjacentFile(destFileRank) && !isFriendly(board->at(destFileRank))) {
      return true;
    }
  } catch (const std::out_of_range &err) {

  }
  return false;
}

bool Pawn::isAdjacentFile (string thatFileRank) {

  char thatFile = thatFileRank.at(ChessInfo::FILE_INDEX);
  return abs(thatFile - file) == 1;
} 
