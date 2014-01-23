
#include "EmptyPiece.hpp"

EmptyPiece::EmptyPiece (string fileRank, bool isWhitePlayer) 
  : Piece(fileRank, isWhitePlayer) {

}

EmptyPiece* EmptyPiece::clone () {
  return new EmptyPiece (this -> getFileRank (), this -> isWhitePlayer ());
}

int EmptyPiece::isValidMove (string destFileRank, map<string, Piece*>* board) {
  return ChessErrHandler::MOVED_EMPTY_PIECE;
}

string EmptyPiece::toString () {
  return string ("Empty Piece");  
}

string EmptyPiece::toGraphics () {
  return string (" ");
}
