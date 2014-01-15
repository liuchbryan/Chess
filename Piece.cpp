// Bryan Liu (chl312), Dept. of Computing, Imperial College London

// Implementation for abstract class Piece (Constructor, Deconstructor)

#include "Piece.hpp"

Piece::Piece (string fileRank, bool _isWhitePlayer){
  file = fileRank[0];
  rank = fileRank[1];
  isWhitePlayer = _isWhitePlayer;
}

Piece::~Piece () {


}

bool Piece::isSameFile (char thatFile) {

  return this->file == thatFile;
}

bool Piece::isSameRank (char thatRank) {

  return this->rank == thatRank;
}

bool Piece::isSameDiagonal (char thatFile, char thatRank) {

  return (this->file - thatFile == this->rank - thatRank) ||
         (this->file - thatFile == -(this->rank - thatRank));
}
