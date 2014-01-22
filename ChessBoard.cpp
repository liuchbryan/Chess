// Bryan Liu (chl312), Dept. of Computing, Imperial College London
// Skeleton C++ file, you will need to edit this for your submission.

// Your final submission must expose the constructor, deconstructor, 
// submitMove and resetBoard methods.
// You may add any additonal files/methods as you see fit
// (be sure to also include them in the makefile).

#include "ChessBoard.hpp"

using namespace std;

ChessBoard::ChessBoard() {
  board = new Board ();
  errorHandler = new ChessErrHandler ();
  resetBoard();
}

ChessBoard::~ChessBoard() {
  delete board;
  delete errorHandler;
}

void ChessBoard::submitMove(const char* fromSquare, const char* toSquare){
  string sourceFileRank (fromSquare);
  string destFileRank (toSquare);

  if (!gameCanContinue (sourceFileRank, destFileRank)) return;
  if (!sourceAndDestIsValid (sourceFileRank, destFileRank)) return;
  if (!sourceIsNotEmpty (sourceFileRank)) return;

  Piece* piece = board->at(sourceFileRank);
  if (!isCurrentPlayerPiece (piece)) return;

  int returnCode = piece -> isValidMove (destFileRank, board);
  if (!pieceMoveIsValid (returnCode, piece, sourceFileRank, destFileRank)) return;
  
  Board* sandboxBoard = cloneBoard (board);
  Piece* capturedPiece 
    = tryMoveAndReturnCaptured (sourceFileRank, destFileRank, sandboxBoard);
  if (!kingIsSafeFromRivalry (isWhiteTurn, sandboxBoard)) {
    handleInvalidMove (ChessErrHandler::ALLOW_KING_IN_CHECK, piece, 
                       sourceFileRank, destFileRank);
    return;
  }

  confirmMove (piece, sourceFileRank, destFileRank, board);
  isInCheck = false;

  printMove (piece, sourceFileRank, destFileRank);
  if (capturedPiece != NULL) {
    printCapture (capturedPiece);
  }
  if (!kingIsSafeFromRivalry (!isWhiteTurn, board)) {
    printCheck ();
    isInCheck = true;
  }

  cout << endl;
  if (!playerHaveValidMove (!isWhiteTurn, board)) {
    if (isInCheck) {
      printCheckmate (!isWhiteTurn);
    } else {
      printStalemate () ;
    }
    hasEnded = true;
  }

  switchPlayers();
}    

void ChessBoard::resetBoard(){
  // apprently we need to delete recursively all the pieces within the map
  // leave it to later stage then
  delete board;
  board = new Board;

  isWhiteTurn = true;
  isInCheck = false;
  hasEnded = false;
  
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
}

// Please do not judge me on if condition then false else true,
// This is just an over-literal program illustration :D
bool ChessBoard::gameCanContinue (string sourceFileRank, string destFileRank) {
  if (hasEnded) {
    errorHandler -> printErr (ChessErrHandler::GAME_HAS_ENDED,
                              new EmptyPiece(sourceFileRank, true),
                              sourceFileRank, destFileRank);
    return false;
  }
  return true;
}

bool ChessBoard::sourceAndDestIsValid 
  (string sourceFileRank, string destFileRank) {

  if (!withinChessBoard(sourceFileRank)) {
    errorHandler->printErr(ChessErrHandler::SOURCE_OUTOF_BOUND,
                           new EmptyPiece(sourceFileRank, true),
                           sourceFileRank, destFileRank);
    return false;
  }

  if (!withinChessBoard(destFileRank)) {
    errorHandler->printErr(ChessErrHandler::DEST_OUTOF_BOUND,
                           new EmptyPiece(destFileRank, true),
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
                           new EmptyPiece(sourceFileRank, true), 
                           sourceFileRank, sourceFileRank); 
    return false;
  }
  return true;
}

bool ChessBoard::isCurrentPlayerPiece (Piece* piece) {

  bool isCurrentPlayerPiece = isWhiteTurn == piece -> isWhitePlayer ();
  if (!isCurrentPlayerPiece) {
    errorHandler->printErr(ChessErrHandler::NOT_OWNER_TURN, piece, 
                           piece -> getFileRank (), piece -> getFileRank ()); 
  }
  return isCurrentPlayerPiece;
}

bool ChessBoard::pieceMoveIsValid
  (int returnCode, Piece* piece, string sourceFileRank, string destFileRank) {

  if (returnCode != ChessErrHandler::NO_ERROR) {
    handleInvalidMove (returnCode, piece, sourceFileRank, destFileRank);
    return false;
  }
  return true;
}

void ChessBoard::handleInvalidMove
  (int returnCode, Piece* piece, string sourceFileRank, string destFileRank) {

  errorHandler->printErr(returnCode, piece, sourceFileRank, destFileRank);
}

bool ChessBoard::kingIsSafeFromRivalry 
  (bool isWhiteTurn, Board* board) {

  Piece* kingToBeExamined = findPlayersKing (isWhiteTurn, board) ;
  string kingFileRank = kingToBeExamined -> getFileRank ();

  for (Board::const_iterator it = board -> cbegin (); 
       it != board -> cend (); it++) {
    Piece* challengingPiece = it -> second;
    if (challengingPiece != kingToBeExamined &&
        challengingPiece -> isWhitePlayer () != isWhiteTurn &&
        challengingPiece -> isValidMove (kingFileRank, board)
          == ChessErrHandler::NO_ERROR) {
      return false;
    }
  }
  return true;
}

bool ChessBoard::playerHaveValidMove
  (bool isWhiteTurn, Board* board) {

  for (Board::const_iterator it = board -> cbegin (); 
       it != board -> cend (); ++it) {

    Piece* possiblePiece = it -> second;
    string possibleSource = possiblePiece -> getFileRank();

    if (possiblePiece -> isWhitePlayer() == isWhiteTurn) {

      for (char i = ChessInfo::MIN_FILE ; i <= ChessInfo::MAX_FILE; i++) {
        for (char j = ChessInfo::MIN_RANK; j <= ChessInfo::MAX_RANK; j++) {

          string possibleDest ({ i, j });
          if (possiblePiece -> isValidMove (possibleDest, board)
                == ChessErrHandler::NO_ERROR) {

            Board* sandboxBoard = cloneBoard (board);
            tryMoveAndReturnCaptured 
              (possibleSource, possibleDest, sandboxBoard);

            if (kingIsSafeFromRivalry (isWhiteTurn, sandboxBoard)) {
              return true;
            }
          }
        }
      }
    }
  }
  return false;
}

Piece* ChessBoard::findPlayersKing (bool isWhiteTurn, Board* board) {
  for (Board::const_iterator it = board -> cbegin ();
       it != board -> cend (); it++) {
    Piece* possiblePiece = it -> second;
    if (possiblePiece -> isWhitePlayer () == isWhiteTurn &&
        ((isWhiteTurn && 
         possiblePiece -> toString ().compare("White's King") == 0) ||
        (!(isWhiteTurn) &&
         possiblePiece -> toString ().compare("Black's King") == 0))) {
      return possiblePiece;
    }
  }
  return NULL;
}

Piece* ChessBoard::tryMoveAndReturnCaptured
  (string sourceFileRank, string destFileRank, Board* board) {
  
  Piece* sourcePiece = board -> at (sourceFileRank);
  Piece* destPiece;
  try {
    destPiece = board -> at (destFileRank);
    board -> at (destFileRank) = sourcePiece;
  } catch (const std::out_of_range &err) {
    destPiece = NULL;
    board -> insert ({ destFileRank, sourcePiece });
  }
  
  sourcePiece -> updateFileRank (destFileRank);
  board -> erase (sourceFileRank);

  return destPiece;
}

void ChessBoard::confirmMove (Piece* movingPiece, 
  string sourceFileRank, string destFileRank, Board* board) {

  try {
    board -> at (destFileRank) = movingPiece;
  } catch (const std::out_of_range &err) {
    board -> insert ({ destFileRank, movingPiece });
  }

  movingPiece -> confirmMove (destFileRank);
  board -> erase (sourceFileRank);

}

void ChessBoard::switchPlayers() {
  isWhiteTurn = !(isWhiteTurn);
}

// deep cloning for board at map
Board* ChessBoard::cloneBoard (Board* board) {
  
  Board* clone = new Board;
  for (Board::iterator it = board -> begin () ; it != board -> end (); it++) {
    clone -> insert ({ it -> first, it -> second -> clone ()});
  }
  return clone;
}


void ChessBoard::printMove
  (Piece* movingPiece, string sourceFileRank, string destFileRank) {

  cout << movingPiece -> toString() << " moves from "
       << sourceFileRank << " to " << destFileRank;
}

void ChessBoard::printCapture (Piece* capturedPiece) {
  cout << " taking " << capturedPiece -> toString();
}

void ChessBoard::printCheck () {
  cout << ", Check!";
}

void ChessBoard::printCheckmate (bool isWhiteTurn) {
  cout << "Checkmate! " << (isWhiteTurn? "White" : "Black")
       << " loses." << endl;
}

void ChessBoard::printStalemate () {
  cout << "Stalemate." << endl;
}

void ChessBoard::printBoard (Board* board) {
// testing (printing) the state of the chessboard
  cout << "Total Number of Squares: " << board->size() << endl;
  for (Board::iterator it = board->begin();
       it != board->end(); ++it) {
    cout << "Square " << it->first << " contains " << it->second->toString() << " at " << it->second->getFileRank() << endl;
  }
// end of testing (printing) the state of chessboard
}
