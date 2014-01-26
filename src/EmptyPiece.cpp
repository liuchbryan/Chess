// Bryan Liu (chl312), Dept. of Computing, Imperial College London
// EmptyPiece.cpp - Implementation of EmptyPiece, Null Object of Piece

#include "header/EmptyPiece.hpp"

EmptyPiece::EmptyPiece (bool isWhitePlayer) : Piece(isWhitePlayer) {

}

EmptyPiece::~EmptyPiece () {

}

EmptyPiece* EmptyPiece::clone () {
  return new EmptyPiece (this -> isWhitePlayer ());
}

// isValidMove(): return special code indicating it is an empty piece
int EmptyPiece::isValidMove 
  (string sourceFileRank, string destFileRank, map<string, Piece*>* board) {
  return ChessErrHandler::MOVED_EMPTY_PIECE;
}

string EmptyPiece::toString () {
  return string ("");  
}

string EmptyPiece::toGraphics () {
  return string (" ");
}
