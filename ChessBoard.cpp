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
  if (!isCurrentPlayerPiece (piece, sourceFileRank)) return;

  int returnCode = piece -> isValidMove (sourceFileRank, destFileRank, board);
  if (!pieceMoveIsValid (returnCode, piece, sourceFileRank, destFileRank)) 
    return;
  
  Board* sandboxBoard = cloneBoard (board);
  Piece* capturedPiece 
    = tryMoveAndReturnCaptured (sourceFileRank, destFileRank, sandboxBoard);
  if (!kingIsSafeFromRivalry (isWhiteTurn, sandboxBoard)) {
    handleInvalidMove (ChessErrHandler::ALLOW_KING_IN_CHECK, piece, 
                       sourceFileRank, destFileRank);
    return;
  }

  confirmMove (sourceFileRank, destFileRank, board);
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
    printBoard (board);
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
    board->insert ({fileRank, new Pawn (true)});

    fileRank.back() = ChessInfo::BLACK_INIT_PAWN_RANK;
    board->insert ({fileRank, new Pawn (false)});
  }

  board->insert ({string("A1"), new Rook (true)});
  board->insert ({string("B1"), new Knight (true)});
  board->insert ({string("C1"), new Bishop (true)});
  board->insert ({string("D1"), new Queen (true)});
  board->insert ({string("E1"), new King (true)});
  board->insert ({string("F1"), new Bishop (true)});
  board->insert ({string("G1"), new Knight (true)});
  board->insert ({string("H1"), new Rook (true)});

  board->insert ({string("A8"), new Rook (false)});
  board->insert ({string("B8"), new Knight (false)});
  board->insert ({string("C8"), new Bishop (false)});
  board->insert ({string("D8"), new Queen (false)});
  board->insert ({string("E8"), new King (false)});
  board->insert ({string("F8"), new Bishop (false)});
  board->insert ({string("G8"), new Knight (false)});
  board->insert ({string("H8"), new Rook (false)});

  cout << "Let the game begin..." << endl;
}

// Please do not judge me on if condition then false else true,
// This is just an over-literal program illustration :D
bool ChessBoard::gameCanContinue (string sourceFileRank, string destFileRank) {
  if (hasEnded) {
    errorHandler -> printErr (ChessErrHandler::GAME_HAS_ENDED,
                              new EmptyPiece(true),
                              sourceFileRank, destFileRank);
    return false;
  }
  return true;
}

bool ChessBoard::sourceAndDestIsValid 
  (string sourceFileRank, string destFileRank) {

  if (!withinChessBoard(sourceFileRank)) {
    errorHandler->printErr(ChessErrHandler::SOURCE_OUTOF_BOUND,
                           new EmptyPiece(true),
                           sourceFileRank, destFileRank);
    return false;
  }

  if (!withinChessBoard(destFileRank)) {
    errorHandler->printErr(ChessErrHandler::DEST_OUTOF_BOUND,
                           new EmptyPiece(true),
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
                           new EmptyPiece(true), 
                           sourceFileRank, sourceFileRank); 
    return false;
  }
  return true;
}

bool ChessBoard::isCurrentPlayerPiece (Piece* piece, string sourceFileRank) {

  bool isCurrentPlayerPiece = isWhiteTurn == piece -> isWhitePlayer ();
  if (!isCurrentPlayerPiece) {
    errorHandler->printErr(ChessErrHandler::NOT_OWNER_TURN, piece, 
                           sourceFileRank, sourceFileRank); 
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

  string kingFileRank = findPlayersKingFileRank (isWhiteTurn, board) ;

  for (Board::const_iterator it = board -> cbegin (); 
       it != board -> cend (); it++) {
    string challengingFileRank = it -> first;
    Piece* challengingPiece = it -> second;
    if (challengingPiece -> isWhitePlayer () != isWhiteTurn &&
        challengingPiece -> isValidMove (challengingFileRank, 
          kingFileRank, board) == ChessErrHandler::NO_ERROR) {
      return false;
    }
  }
  return true;
}

bool ChessBoard::playerHaveValidMove
  (bool isWhiteTurn, Board* board) {

  for (Board::const_iterator it = board -> cbegin (); 
       it != board -> cend (); ++it) {

    string possibleSource = it -> first;
    Piece* possiblePiece = it -> second;

    if (possiblePiece -> isWhitePlayer() == isWhiteTurn) {

      for (char i = ChessInfo::MIN_FILE ; i <= ChessInfo::MAX_FILE; i++) {
        for (char j = ChessInfo::MIN_RANK; j <= ChessInfo::MAX_RANK; j++) {

          string possibleDest ({ i, j });
          if (possiblePiece -> isValidMove (possibleSource, 
                possibleDest, board) == ChessErrHandler::NO_ERROR) {

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

string ChessBoard::findPlayersKingFileRank (bool isWhiteTurn, Board* board) {
  for (Board::const_iterator it = board -> cbegin ();
       it != board -> cend (); it++) {
    string possibleFileRank = it -> first;
    Piece* possiblePiece = it -> second;
    if (possiblePiece -> isWhitePlayer () == isWhiteTurn &&
        possiblePiece -> isKing () == true) {
      return possibleFileRank;
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
  
  board -> erase (sourceFileRank);

  return destPiece;
}

void ChessBoard::confirmMove 
  (string sourceFileRank, string destFileRank, Board* board) {

  Piece* movingPiece = board -> at (sourceFileRank);
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

// testing (printing) the state of the chessboard
void ChessBoard::printBoard (Board* board) {
  cout << endl << "  +--+--+--+--+--+--+--+--+" << endl;
  for (char i = ChessInfo::MAX_RANK ; i >= ChessInfo::MIN_RANK; i--) {
    cout << i << " ";
    for (char j = ChessInfo::MIN_FILE; j <= ChessInfo::MAX_FILE; j++) {
      cout << "|";
      string fileRank ({ j, i });
      try {
        Piece* piece = board -> at (fileRank);
        cout << piece -> toGraphics () << " ";
      } catch (const std::out_of_range &err) {
        cout << "  ";
      }
    }
    cout << "|" << endl << "  +--+--+--+--+--+--+--+--+" << endl;
  }
  cout << "    A  B  C  D  E  F  G  H" << endl;
}
