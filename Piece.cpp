// Bryan Liu (chl312), Dept. of Computing, Imperial College London
/* Implementation for abstract class Piece - info in Piece.hpp
   (Constructor, Deconstructor and common methods for extending classes)
*/

#include "Piece.hpp"

Piece::Piece (bool isWhitePlayer){
  _isWhitePlayer = isWhitePlayer;
}


void Piece::confirmMove (string destFileRank) {
  isFirstMove = false;
}

// Piece.isWhitePlayer() post-cond.: return if this piece belongs to White P.
bool Piece::isWhitePlayer () {
  return (_isWhitePlayer);
}

/* Piece.isFriendly()
   Pre-cond.: that is a valid reference to a Piece
   Post-cond.: return true iff this and that Piece belongs to same player
*/
bool Piece::isFriendly (Piece* that) {
  return this->isWhitePlayer() == that->isWhitePlayer();
}

// Piece.playerToString() Post-cond.: return string rep. of the piece's player
string Piece::playerToString () {
  return _isWhitePlayer? string("White's") : string("Black's");
}

/* Piece::isSame_ ()
   Pre-cond.: 
   Post-cond.: 

*/ 

bool Piece::isSameFile (string sourceFileRank, string destFileRank) {
  return sourceFileRank.at(ChessInfo::FILE_INDEX) ==
         destFileRank.at(ChessInfo::FILE_INDEX);
}

bool Piece::isSameRank (string sourceFileRank, string destFileRank) {
  return sourceFileRank.at(ChessInfo::RANK_INDEX) ==
         destFileRank.at(ChessInfo::RANK_INDEX);

}

bool Piece::isSameDiagonal (string sourceFileRank, string destFileRank) {
  return abs (sourceFileRank.at(ChessInfo::FILE_INDEX) -
              destFileRank.at(ChessInfo::FILE_INDEX)) ==
         abs (sourceFileRank.at(ChessInfo::RANK_INDEX) -
              destFileRank.at(ChessInfo::RANK_INDEX));
}

/* Piece.noVerticalObstruction()
   Pre-cond.: 
   Post-cond.:
*/
bool Piece::noVerticalObstruction 
  (string sourceFileRank, string destFileRank, map<string, Piece*>* board){
  
  char sourceFile = sourceFileRank.at(ChessInfo::FILE_INDEX);
  char sourceRank = sourceFileRank.at(ChessInfo::RANK_INDEX);
  char destRank = destFileRank.at(ChessInfo::RANK_INDEX);
  char lowRank = (sourceRank < destRank) ? sourceRank : destRank;
  char highRank = (sourceRank < destRank) ? destRank : sourceRank;

  for (char i = lowRank + ChessInfo::EXCLUSIVE_SHIFT; i < highRank; i++) {
    string between ({ sourceFile, i });
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
   Pre-cond.: 
   Post-cond.: 
*/
bool Piece::noHorizontalObstruction
  (string sourceFileRank, string destFileRank, map<string, Piece*>* board){

  char sourceFile = sourceFileRank.at(ChessInfo::FILE_INDEX);
  char sourceRank = sourceFileRank.at(ChessInfo::RANK_INDEX);
  char destFile = destFileRank.at(ChessInfo::FILE_INDEX);
  char lowFile = (sourceFile < destFile) ? sourceFile : destFile;
  char highFile = (sourceFile < destFile) ? destFile : sourceFile;

  for (char i = lowFile + ChessInfo::EXCLUSIVE_SHIFT; i < highFile; i++) {
    string between ({ i, sourceRank });
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
   Pre-cond.: 
   Post-cond.: 
*/
bool Piece::noDiagonalObstruction
  (string sourceFileRank, string destFileRank, map<string, Piece*>* board){

  char sourceFile = sourceFileRank.at(ChessInfo::FILE_INDEX);
  char destFile = destFileRank.at(ChessInfo::FILE_INDEX);
  char lowFile = (sourceFile < destFile) ? sourceFile : destFile;
  char highFile = (sourceFile < destFile) ? destFile : sourceFile;

  char sourceRank = sourceFileRank.at(ChessInfo::RANK_INDEX);
  char destRank = destFileRank.at(ChessInfo::RANK_INDEX);
  char lowRank = (sourceRank < destRank) ? sourceRank : destRank;
  char highRank = (sourceRank < destRank) ? destRank : sourceRank;

  bool isPositiveSlope = (destFile - sourceFile) == (destRank - sourceRank);
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

/* Piece.destExistFriendlyPiece()
   Pre-cond.: destFileRank is a valid file & rank representation
   Post-cond.: return true if piece on the dest file & rank is a friendly,
               false otherwise (rivalry on dest or empty square)
*/
bool Piece::destExistFriendlyPiece 
  (string destFileRank, map<string, Piece*>* board) {

  try {
    if (isFriendly(board->at(destFileRank))) {
      return true;
    }
  } catch (const std::out_of_range &err) {
    // No piece for this file & rank, expect to return false
  }
  return false;
}
