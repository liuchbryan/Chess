// Bryan Liu (chl312), Dept. of Computing, Imperial College London

// Implementation for abstract class Piece (Constructor, Deconstructor)

#include "Piece.hpp"

Piece::Piece (string fileRank, bool isWhitePlayer){
  file = fileRank.at(ChessInfo::FILE_INDEX);
  rank = fileRank.at(ChessInfo::RANK_INDEX);
  _isWhitePlayer = isWhitePlayer;
}

Piece::~Piece () {


}

bool Piece::isWhitePlayer () {
  return (_isWhitePlayer);
}

bool Piece::isFriendly (Piece* that) {
  return this->isWhitePlayer() == that->isWhitePlayer();
}

string Piece::playerToString () {
  return _isWhitePlayer? string("White's") : string("Black's");
}

bool Piece::isSameFile (string thatFileRank) {

  char thatFile = thatFileRank.at(ChessInfo::FILE_INDEX);
  return this->file == thatFile;
}

bool Piece::isSameRank (string thatFileRank) {

  char thatRank = thatFileRank.at(ChessInfo::RANK_INDEX);
  return this->rank == thatRank;
}

bool Piece::isSameDiagonal (string thatFileRank) {

  char thatFile = thatFileRank.at(ChessInfo::FILE_INDEX);
  char thatRank = thatFileRank.at(ChessInfo::RANK_INDEX);
  return (abs(this->file - thatFile) == abs(this->rank - thatRank));
}

bool Piece::noObstruction (string destFileRank, map<string, Piece*>* board) {
// yes require expansion
  return false;
}

bool Piece::destExistFriendlyPiece 
  (string destFileRank, map<string, Piece*>* board) {

  try {
    Piece* destPiece = board->at(destFileRank);
    if (isFriendly(destPiece)) {
      return true;
    }
  } catch (const std::out_of_range &err) {
    
  }
  return false;
}
