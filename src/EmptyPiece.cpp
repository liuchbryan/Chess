
#include "header/EmptyPiece.hpp"

EmptyPiece::EmptyPiece (bool isWhitePlayer) : Piece(isWhitePlayer) {

}

EmptyPiece::~EmptyPiece () {

}

EmptyPiece* EmptyPiece::clone () {
  return new EmptyPiece (this -> isWhitePlayer ());
}

int EmptyPiece::isValidMove 
  (string sourceFileRank, string destFileRank, map<string, Piece*>* board) {
  return ChessErrHandler::MOVED_EMPTY_PIECE;
}

string EmptyPiece::toString () {
  return string ("Empty Piece");  
}

string EmptyPiece::toGraphics () {
  return string (" ");
}
