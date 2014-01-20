// Bryan Liu (chl312), Dept. of Computing, Imperial College London
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

ChessBoard::~ChessBoard() {
  cout << "TODO: implement ChessBoard deconstructor" << endl;
}

void ChessBoard::submitMove(const char* fromSquare, const char* toSquare){
  string sourceFileRank (fromSquare);
  string destFileRank (toSquare);

  if (!sourceAndDestIsValid (sourceFileRank, destFileRank)) return;
  if (!sourceIsNotEmpty (sourceFileRank)) return;

  Piece* piece = board->at(sourceFileRank);
  if (!isCurrentPlayerPiece (piece)) return;

  int returnCode = piece -> isValidMove (destFileRank, board);
  if (returnCode != ChessErrHandler::NO_ERROR) {
    handleInvalidMove (returnCode, piece, sourceFileRank, destFileRank);
    return;
  }

  Piece* capturedPiece = tryMoveAndReturnCaptured 
                         (piece, sourceFileRank, destFileRank, board);
  Piece* currPlayerKing = isWhiteTurn? whiteKing : blackKing;
  Piece* nextPlayerKing = isWhiteTurn? blackKing : whiteKing;
  if (!kingIsSafeFromRivalry (currPlayerKing, board)) {
    handleInvalidMove (ChessErrHandler::ALLOW_KING_IN_CHECK, piece, 
                       sourceFileRank, destFileRank);
    reverseMove (piece, sourceFileRank, capturedPiece, destFileRank, board);
    return;
  }

  piece -> confirmMove();
  isInCheck = false;

  printMove (piece, sourceFileRank, destFileRank);
  if (capturedPiece != NULL) {
    printCapture (capturedPiece);
  }
  if (!kingIsSafeFromRivalry (nextPlayerKing, board)) {
    printCheck ();
    isInCheck = true;
  }

  cout << endl;
  switchPlayers ();

  if (!playerHaveValidMove (isWhiteTurn, board)) {
    if (isInCheck) {
      printCheckmate (isWhiteTurn);
    } else {
      printStalemate () ;
    }
    hasEnded = true;
  }
}    

void ChessBoard::resetBoard(){
  // apprently we need to delete recursively all the pieces within the map
  // leave it to later stage then

  board = new map<string, Piece*>;
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
  board->insert ({string("F1"), new Bishop (string("F1"), true)});
  board->insert ({string("G1"), new Knight (string("G1"), true)});
  board->insert ({string("H1"), new Rook (string("H1"), true)});
  whiteKing = new King (string("E1"), true);
  board->insert ({string("E1"), whiteKing});

  board->insert ({string("A8"), new Rook (string("A8"), false)});
  board->insert ({string("B8"), new Knight (string("B8"), false)});
  board->insert ({string("C8"), new Bishop (string("C8"), false)});
  board->insert ({string("D8"), new Queen (string("D8"), false)});
  board->insert ({string("F8"), new Bishop (string("F8"), false)});
  board->insert ({string("G8"), new Knight (string("G8"), false)});
  board->insert ({string("H8"), new Rook (string("H8"), false)});
  blackKing = new King (string("E8"), false);
  board->insert ({string("E8"), blackKing});

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

void ChessBoard::handleInvalidMove 
  (int returnCode, Piece* piece, string sourceFileRank, string destFileRank) {

  errorHandler->printErr(returnCode, piece, sourceFileRank, destFileRank);
}

bool ChessBoard::kingIsSafeFromRivalry 
  (Piece* kingToBeExamined, map<string, Piece*>* board) {

  bool kingIsWhite = kingToBeExamined -> isWhitePlayer ();
  string kingFileRank = kingToBeExamined -> getFileRank ();

  for (map<string, Piece*>::const_iterator it = board -> cbegin (); 
       it != board -> cend (); it++) {
    Piece* challengingPiece = it -> second;
    if (challengingPiece != kingToBeExamined &&
        challengingPiece -> isWhitePlayer () != kingIsWhite &&
        challengingPiece -> isValidMove (kingFileRank, board)
          == ChessErrHandler::NO_ERROR) {
      return false;
    }
  }
  return true;
}

Piece* ChessBoard::tryMoveAndReturnCaptured (Piece* piece,
  string sourceFileRank, string destFileRank, map<string, Piece*>* board) {
  
  Piece* destPiece;
  try {
    destPiece = board -> at (destFileRank);    
    board -> at (destFileRank) = piece;
  } catch (const std::out_of_range &err) {
    destPiece = NULL;
    board -> insert ({ destFileRank, piece });
  }
  
  piece -> updateFileRank (destFileRank);
  board -> erase (sourceFileRank);

  return destPiece;
}

void ChessBoard::reverseMove (Piece* movingPiece, string sourceFileRank,
  Piece* capturedPiece, string destFileRank, map<string, Piece*>* board) {

  board -> erase (destFileRank);
  if (capturedPiece != NULL) {
    board -> insert ({ destFileRank, capturedPiece });
  }
  movingPiece -> updateFileRank (sourceFileRank);
  board -> insert ({ sourceFileRank, movingPiece });
}

void ChessBoard::switchPlayers() {
  isWhiteTurn = !(isWhiteTurn);
}

bool ChessBoard::playerHaveValidMove
  (bool isWhiteTurn, map<string, Piece*>* board) {
  /*for (map<string, Piece*>::const_iterator it = board -> cbegin (); 
       it != board -> cend (); ++it) {
    //the iterator got stuck in B6 - which is a problem to address
    //cout << it -> first << " ";
    Piece* currPiece = it -> second;
    string currFileRank = currPiece -> getFileRank();
    //cout << currPiece -> toString () << ": "<< currPiece << " ";
    if (currPiece -> isWhitePlayer() == isWhiteTurn) {
      for (char i = ChessInfo::MIN_FILE ; i <= ChessInfo::MAX_FILE; i++) {
        for (char j = ChessInfo::MIN_RANK; j <= ChessInfo::MAX_RANK; j++) {
          string possibleFileRank ({ i, j });
          if (currPiece -> isValidMove (possibleFileRank, board)
                == ChessErrHandler::NO_ERROR) {
            //cout << possibleFileRank << " ";
            Piece* captured = tryMoveAndReturnCaptured (currPiece, 
                               currFileRank, possibleFileRank, board);
            if (kingIsSafeFromRivalry ((isWhiteTurn? whiteKing : blackKing), board)) {
              reverseMove (currPiece, currFileRank, captured, possibleFileRank, board);
              return true;
            }
            reverseMove (currPiece, currFileRank, captured, possibleFileRank, board);
          }
        }
      }

    }
//    cout << endl;
  }*/
  return false;

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
