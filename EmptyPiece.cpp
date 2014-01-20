
#include "EmptyPiece.hpp"

EmptyPiece::EmptyPiece (string fileRank, bool isWhitePlayer) 
  : Piece(fileRank, isWhitePlayer) {

}

int EmptyPiece::isValidMove (string destFileRank, map<string, Piece*>* board) {
  return ChessErrHandler::MOVED_EMPTY_PIECE;
}

string EmptyPiece::toString () {
  return string ("Empty Piece");  
}
