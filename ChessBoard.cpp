// Skeleton C++ file, you will need to edit this for your submission.

// Your final submission must expose the constructor, deconstructor, 
// submitMove and resetBoard methods.
// You may add any additonal files/methods as you see fit
// (be sure to also include them in the makefile).

#include "ChessBoard.hpp"

using namespace std;

ChessBoard::ChessBoard() {
  errorHandler = new ChessErrHandler();
  resetBoard();
}

ChessBoard::~ChessBoard()
{
  cout << "TODO: implement ChessBoard deconstructor" << endl;
}

void ChessBoard::submitMove(const char* fromSquare, const char* toSquare){
  string sourceFileRank (fromSquare);
  string destFileRank (toSquare);

  if (!sourceAndDestIsValid (sourceFileRank, destFileRank)) return;
  if (!sourceIsNotEmpty (sourceFileRank)) return;

  Piece* piece = board->at(sourceFileRank);
  if (!isCurrentPlayerPiece (piece)) return;

  int returnCode = piece->isValidMove (destFileRank, board);
  if (returnCode != ChessErrHandler::NO_ERROR) {
    handleInvalidMove (returnCode, piece, sourceFileRank, destFileRank);
    return;
  }

  handleMove (piece, sourceFileRank, destFileRank, board);


  switchPlayers();
}    

void ChessBoard::resetBoard(){
  // apprently we need to delete recursively all the pieces within the map
  // leave it to later stage then

  board = new map<string, Piece*>;
  isWhiteTurn = true;
  isInCheck = false;
  
  string fileRank ("A1");

  for (char i = ChessInfo::MIN_FILE; i <= ChessInfo::MAX_FILE; i++) {
    fileRank.front() = i;

    fileRank.back() = ChessInfo::WHITE_INIT_PAWN_RANK;
    board->insert ({fileRank, new Pawn (fileRank, true)});

    fileRank.back() = ChessInfo::BLACK_INIT_PAWN_RANK;
    board->insert ({fileRank, new Pawn (fileRank, false)});
  }

  board->insert ({string("A1"), new Rook (string("A1"), true)});
  board->insert ({string("B1"), new Knight (string("B1"), true)});
  board->insert ({string("C1"), new Bishop (string("C1"), true)});
  board->insert ({string("D1"), new Queen (string("D1"), true)});
  board->insert ({string("E1"), new King (string("E1"), true)});
  board->insert ({string("F1"), new Bishop (string("F1"), true)});
  board->insert ({string("G1"), new Knight (string("G1"), true)});
  board->insert ({string("H1"), new Rook (string("H1"), true)});

  board->insert ({string("A8"), new Rook (string("A8"), false)});
  board->insert ({string("B8"), new Knight (string("B8"), false)});
  board->insert ({string("C8"), new Bishop (string("C8"), false)});
  board->insert ({string("D8"), new Queen (string("D8"), false)});
  board->insert ({string("E8"), new King (string("E8"), false)});
  board->insert ({string("F8"), new Bishop (string("F8"), false)});
  board->insert ({string("G8"), new Knight (string("G8"), false)});
  board->insert ({string("H8"), new Rook (string("H8"), false)});

  cout << "Let the game begin..." << endl;

/* 
// testing (printing) the state of the chessboard
  cout << "Total Number of Squares: " << board->size() << endl;
  for (map<string, Piece*>::iterator it = board->begin();
       it != board->end(); ++it) {
    cout << "Square " << it->first << " contains " << it->second->toString() << endl;
  }
// end of testing (printing) the state of chessboard
*/

}

bool ChessBoard::sourceAndDestIsValid 
  (string sourceFileRank, string destFileRank) {

  if (sourceFileRank.compare(destFileRank) == 0) {
    errorHandler->printErr(ChessErrHandler::DEST_EQ_SOURCE,
                           new EmptyPiece("  ", true),
                           sourceFileRank, destFileRank); 
    return false;
  }

  if (!withinChessBoard(sourceFileRank)) {
    errorHandler->printErr(ChessErrHandler::SOURCE_OUTOF_BOUND,
                           new EmptyPiece("  ", true),
                           sourceFileRank, destFileRank);
    return false;
  }

  if (!withinChessBoard(sourceFileRank)) {
    errorHandler->printErr(ChessErrHandler::DEST_OUTOF_BOUND,
                           new EmptyPiece("  ", true),
                           sourceFileRank, destFileRank);
    return false;
  }

  return true;
}


bool ChessBoard::withinChessBoard (string fileRank) {
  
  char file = fileRank.at(ChessInfo::FILE_INDEX);
  char rank = fileRank.at(ChessInfo::RANK_INDEX);
  return ChessInfo::MIN_FILE <= file && file <= ChessInfo::MAX_FILE &&
         ChessInfo::MIN_RANK <= rank && rank <= ChessInfo::MAX_RANK;
}

bool ChessBoard::sourceIsNotEmpty (string sourceFileRank) {

  try {
    board->at (sourceFileRank);
  } catch (const std::out_of_range &err) {
    errorHandler->printErr(ChessErrHandler::MOVED_EMPTY_PIECE,
                           new EmptyPiece("  ", true), sourceFileRank, "  "); 
    return false;
  }
  return true;
}

bool ChessBoard::isCurrentPlayerPiece (Piece* piece) {

  bool currentPlayerPiece = isWhiteTurn == piece->isWhitePlayer();
  if (!currentPlayerPiece) {
    errorHandler->printErr(ChessErrHandler::NOT_OWNER_TURN, piece, "  ", "  "); 
  }
  return currentPlayerPiece;
}

void ChessBoard::handleInvalidMove 
  (int returnCode, Piece* piece, string sourceFileRank, string destFileRank) {

  errorHandler->printErr(returnCode, piece, sourceFileRank, destFileRank);
}

void ChessBoard::handleMove (Piece* piece, string sourceFileRank, 
  string destFileRank, map<string, Piece*>* board) {

  try {
    Piece* destPiece = board -> at (destFileRank);
    printMove (piece, sourceFileRank, destFileRank, destPiece);
    board -> at (destFileRank) = piece;
    
  } catch (const std::out_of_range &err) {
    printMove (piece, sourceFileRank, destFileRank);
    board -> insert ({ destFileRank, piece });
  }

  board -> erase (sourceFileRank);
}

void ChessBoard::printMove 
  (Piece* movingPiece, string sourceFileRank, string destFileRank) {

  cout << movingPiece -> toString() << " moves from "
       << sourceFileRank << " to " << destFileRank << endl;
}

void ChessBoard::printMove (Piece* movingPiece, string sourceFileRank, 
  string destFileRank, Piece* capturedPiece) {

  cout << movingPiece -> toString() << " moves from "
       << sourceFileRank << " to " << destFileRank
       << " taking " << capturedPiece -> toString() << endl;
}

void ChessBoard::switchPlayers() {
  isWhiteTurn = !(isWhiteTurn);
}
