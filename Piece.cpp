// Bryan Liu (chl312), Dept. of Computing, Imperial College London

// Implementation for abstract class Piece (Constructor, Deconstructor)

#include "Piece.hpp"

Piece::Piece (string fileRank, bool isWhitePlayer){
  file = fileRank[0];
  rank = fileRank[1];
  _isWhitePlayer = isWhitePlayer;
}

Piece::~Piece () {


}

bool Piece::isWhitePlayer () {
  return (_isWhitePlayer);
}

string Piece::playerToString () {
  return _isWhitePlayer? string("White's") : string("Black's");
}

bool Piece::isSameFile (char thatFile) {
  return this->file == thatFile;
}

bool Piece::isSameRank (char thatRank) {
  return this->rank == thatRank;
}

bool Piece::isSameDiagonal (char thatFile, char thatRank) {
  return (abs(this->file - thatFile) == abs(this->rank - thatRank));
}
