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

/* Piece.noVerticalObstruction()
   Pre-cond.: destFileRank is in the same file and not the same rank as
              this piece
   Post-cond.: return true iff there are no piece in between this rank and
               dest rank (exclusive)
*/
bool Piece::noVerticalObstruction 
  (string destFileRank, map<string, Piece*>* board){

  char destRank = destFileRank.at(ChessInfo::RANK_INDEX);
  char lowRank = (rank < destRank) ? rank : destRank;
  char highRank = (rank < destRank) ? destRank : rank;

  for (char i = lowRank + ChessInfo::EXCLUSIVE_SHIFT; i < highRank; i++) {
    string between ({ file, i });
    try {
      board -> at(between);
      return false;
    } catch (const std::out_of_range &err) {
      // No piece for this file & rank, no action required
    }
  }
  return true;
}

/* Piece.noHorizontalObstruction()
   Pre-cond.: destFileRank is in the same rank as this piece
   Post-cond.: return true iff there are no piece in between this file and
               dest file (exclusive)
*/
bool Piece::noHorizontalObstruction
  (string destFileRank, map<string, Piece*>* board){

  char destFile = destFileRank.at(ChessInfo::FILE_INDEX);
  char lowFile = (file < destFile) ? file : destFile;
  char highFile = (file < destFile) ? destFile : file;

  for (char i = lowFile + ChessInfo::EXCLUSIVE_SHIFT; i < highFile; i++) {
    string between ({ i, rank });
    try {
      board -> at (between);
      return false;
    } catch (const std::out_of_range &err) {
      // No piece for this file & rank, no action required
    }
  }
  return true;
}

/* Piece.noDiagonalObstruction()
   Pre-cond.: destFileRank is in the same diagonal as this piece
   Post-cond.: return true iff there are no piece in between this piece and
               dest file & rank on the diagonal (exclusive)
*/
bool Piece::noDiagonalObstruction
  (string destFileRank, map<string, Piece*>* board){

  char destFile = destFileRank.at(ChessInfo::FILE_INDEX);
  char lowFile = (file < destFile) ? file : destFile;
  char highFile = (file < destFile) ? destFile : file;

  char destRank = destFileRank.at(ChessInfo::RANK_INDEX);
  char lowRank = (rank < destRank) ? rank : destRank;
  char highRank = (rank < destRank) ? destRank : rank;

  bool isPositiveSlope = (destFile - file) == (destRank - rank);
  string between;

  for (int i = ChessInfo::EXCLUSIVE_SHIFT; i < (highFile - lowFile); i++) {
    if (isPositiveSlope) {
      between = { (char) (lowFile + i), (char) (lowRank + i) };
    } else {
      between = { (char) (lowFile + i), (char) (highRank - i) };
    }

    try {
      board -> at (between);
      return false;
    } catch (const std::out_of_range &err) {
      // No piece for this file & rank, no action required
    }
  }
  return true;
}

bool Piece::destExistFriendlyPiece 
  (string destFileRank, map<string, Piece*>* board) {

  try {
    if (isFriendly(board->at(destFileRank))) {
      return true;
    }
  } catch (const std::out_of_range &err) {
    // No piece for this file & rank, no action required
  }
  return false;
}
