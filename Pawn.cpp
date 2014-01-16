
#include "Pawn.hpp"

Pawn::Pawn (string fileRank, bool isWhitePlayer)
  : Piece (fileRank, isWhitePlayer) {

}

int Pawn::isValidMove (string destFileRank, map<string, Piece*>* board) {
  char destFile = destFileRank.at(ChessInfo::FILE_INDEX);
  char destRank = destFileRank.at(ChessInfo::RANK_INDEX);

  int rankAdvancement =
    _isWhitePlayer ? destRank - rank : rank - destRank;

  switch (rankAdvancement) {
    case 2: {
      if (isSameFile(destFile) && isFirstMove) {
        isFirstMove = !(isFirstMove);
        // Involve refactoring
      }
    }
    case 1: {


    }
    
    



  }

  if (isSameFile (destFile)) {
    

  } else {
    
  
  }
  
  return ChessErrHandler::ILLEGAL_MOVE_PATTERN;
}

string Pawn::toString () {
  
  string name (playerToString());
  name.append(" Pawn");
  return name;  
}

bool Pawn::canDiagonallyCapture () {



}
