
#include "EmptyPiece.hpp"

EmptyPiece::EmptyPiece (string fileRank, bool isWhitePlayer) 
  : Piece(fileRank, isWhitePlayer) {

}

int EmptyPiece::isValidMove (string destFileRank, map<string, Piece*>* board) {
  
  return ChessErrHandler::ILLEGAL_MOVE_PATTERN;
}

string EmptyPiece::toString () {
  
  return string ("Empty Piece");  
}
