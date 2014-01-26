// Bryan Liu (chl312), Dept. of Computing, Imperial College London
/* Implementation for abstract class Piece - info in Piece.hpp
   (Constructor, Deconstructor and common methods for extending classes)
*/

#include "header/Piece.hpp"

Piece::Piece (bool isWhitePlayer) {
  _isWhitePlayer = isWhitePlayer;
}

Piece::~Piece () {

}

/* Piece.confirmMove():
   set isFirstMove false when called as it has moved at least once
*/   
void Piece::confirmMove () {
  isFirstMove = false;
}

// Piece.isWhitePlayer() post-cond.: return if this piece belongs to White p.
bool Piece::isWhitePlayer () {
  return (_isWhitePlayer);
}

/* Piece.isKing() post-cond.: return true iff the piece is a King
     (represented by _isKing - only set to true by King constructor)
*/
bool Piece::isKing () {
  return _isKing;
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
   Pre-cond.: sourceFileRank, destFileRank valid file & rank representation
   Post-cond.: return true iff sourceFileRank and destFileRank is on the same
               file/ rank/ diagonal respectively
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
   Pre-cond.: sourceFileRank, destFileRank valid file & rank representation
              board a valid, existing reference to map rep. of the board
   Post-cond.: return true iff there are no pieces on intermediate ranks
               on the board
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

/* Piece.noVerticalObstruction()
   Pre-cond.: sourceFileRank, destFileRank valid file & rank representation
              board a valid, existing reference to map rep. of the board
   Post-cond.: return true iff there are no pieces on intermediate files
               on the board
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

/* Piece.noVerticalObstruction()
   Pre-cond.: sourceFileRank, destFileRank valid file & rank representation
              board a valid, existing reference to map rep. of the board
   Post-cond.: return true iff there are no pieces on intermediate files
               and ranks, which is on the same diagonal, on the board
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
