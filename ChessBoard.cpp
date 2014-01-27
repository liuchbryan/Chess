// Bryan Liu (chl312), Dept. of Computing, Imperial College London
// ChessBoard.cpp - Implementation of ChessBoard (Info in ChessBoard.hpp)

#include "ChessBoard.hpp"

using namespace std;

ChessBoard::ChessBoard() {
  board = new Board ();
  errorHandler = new ChessErrHandler ();
  piecePlaceholder = new EmptyPiece (true);
  resetBoard();
}

ChessBoard::~ChessBoard() {
  deepCleanBoard(board);
  delete errorHandler;
  delete piecePlaceholder;
}

/* ChessBoard.submitMove():
   Verifies the move is valid, conduct the move and print on screen (stdout)
   Before any constructive checking:
     - Is the game ended? (No point to continue if it is ended)
   Pre-move check:
     - Is the given source and destination valid file and rank representations?
     - Is the source an non-empty square?
     - Is the piece on source square belongs to the player making the move?
     - Is the piece's move on the current board valid based on its type?
   Try move: - In a sandbox to prevent messing up the original board
             - Check: Does the move keeps current player's King in a safe
                      position (i.e. NOT in check)?
   Confirm the move on both the board and the piece
   Print the move on screen, and check if the game can continue
     If yes, switch player and "wait" for next submitMove
     If no, print statement and final represenation of board
   Finally do some nice memory management to prevent memory leakage
*/
void ChessBoard::submitMove(const char* fromSquare, const char* toSquare){
  string sourceFileRank (fromSquare);
  string destFileRank (toSquare);

  if (!gameCanContinue (sourceFileRank, destFileRank)) return;
  if (!sourceAndDestIsValid (sourceFileRank, destFileRank)) return;
  if (!sourceIsNotEmpty (sourceFileRank, board)) return;

  Piece* piece = board->at(sourceFileRank);
  if (!isCurrentPlayerPiece (isWhiteTurn, piece, sourceFileRank)) return;

  int returnCode = piece -> isValidMove (sourceFileRank, destFileRank, board);
  if (!pieceMoveIsValid (returnCode, piece, 
       sourceFileRank, destFileRank)) return;
  
  Board* sandboxBoard = cloneBoard (board);
  Piece* capturedPiece 
    = tryMoveAndReturnCaptured (sourceFileRank, destFileRank, sandboxBoard);
  if (!pieceMoveKeepsKingSafe (isWhiteTurn, piece, 
       sourceFileRank, destFileRank, sandboxBoard)) return;
  
  confirmMoveOnBoard (sourceFileRank, destFileRank, board);
  
  if (!showMoveAndCheckIfGameCanContinue (piece, sourceFileRank, 
        capturedPiece, destFileRank, isWhiteTurn, board)) {
    endTheGame ();
  }

  switchPlayers();
  
  delete capturedPiece;
  deepCleanBoard (sandboxBoard);
}    

/* ChessBoard.resetBoard (): i.e. make a new game
   Rest the fields of the engine and insert appropriate pieces onto the board
*/
void ChessBoard::resetBoard(){

  getANewBoard();
  beginAGame();
  makeWhiteGoesNext ();
  makeGameNotInCheck ();
  
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

// The pre-defined setters (6 methods)
/* getANewBoard () assumption:
   board contains non-null pointer to a Board, thus can be deep cleaned
*/
void ChessBoard::getANewBoard () {
  deepCleanBoard (this -> board);
  board = new Board;
}

void ChessBoard::makeGameInCheck () {
  isInCheck = true;
}

void ChessBoard::makeGameNotInCheck () {
  isInCheck = false;
}

void ChessBoard::beginAGame () {
  hasEnded = false;
}

void ChessBoard::endTheGame () {
  hasEnded = true;
}

void ChessBoard::makeWhiteGoesNext () {
  isWhiteTurn = true;
}

/* The following methods check certain conditions required for a valid chess
     move and gives out an error to user (and return false) if it is not met
   N.B: A kind request not to judge on "if condition then false else true"
        It is, at the end, an over-literal program illustration
*/

// gameCanContine (): check if the game is not ended
bool ChessBoard::gameCanContinue (string sourceFileRank, string destFileRank) {
  if (hasEnded) {
    handleInvalidMove (ChessErrHandler::GAME_HAS_ENDED,
                       piecePlaceholder, sourceFileRank, destFileRank);
    return false;
  }
  return true;
}

/* sourceAndDestIsValid (): check if given source and dest's file and rank
                            represenation is valid (string with 2 chars)
                            and are within chess board
*/
bool ChessBoard::sourceAndDestIsValid 
  (string sourceFileRank, string destFileRank) {
  if (sourceFileRank.length() != ChessInfo::FILERANK_LENGTH || 
      destFileRank.length() != ChessInfo::FILERANK_LENGTH) {
    handleInvalidMove (ChessErrHandler::INVALID_FILE_RANK,
                         piecePlaceholder, sourceFileRank, destFileRank);
    return false;
  }
  
  if (!withinChessBoard(sourceFileRank)) {
    handleInvalidMove (ChessErrHandler::SOURCE_OUTOF_BOUND,
                       piecePlaceholder, sourceFileRank, destFileRank);
    return false;
  }

  if (!withinChessBoard(destFileRank)) {
    handleInvalidMove (ChessErrHandler::DEST_OUTOF_BOUND,
                       piecePlaceholder, sourceFileRank, destFileRank);
    return false;
  }
  return true;
}

/* withinChesBoard (): helper method
   check if file is in range 'A'-'H', rank is in range '1'-'8'
*/
bool ChessBoard::withinChessBoard (string fileRank) {
  
  char file = fileRank.at(ChessInfo::FILE_INDEX);
  char rank = fileRank.at(ChessInfo::RANK_INDEX);
  return ChessInfo::MIN_FILE <= file && file <= ChessInfo::MAX_FILE &&
         ChessInfo::MIN_RANK <= rank && rank <= ChessInfo::MAX_RANK;
}

/* sourceIsNotEmpty ():
   check if source is not an empty square (i.e. there is a piece to move)
*/
bool ChessBoard::sourceIsNotEmpty (string sourceFileRank, Board* board) {

  try {
    board -> at (sourceFileRank);
  } catch (const std::out_of_range &err) {
    handleInvalidMove (ChessErrHandler::MOVED_EMPTY_PIECE,
                       piecePlaceholder, sourceFileRank, sourceFileRank); 
    return false;
  }
  return true;
}

/* isCurrentPlayerPiece ():
   check if the piece at source belongs to the player in turn
*/
bool ChessBoard::isCurrentPlayerPiece 
  (bool isWhiteTurn, Piece* piece, string sourceFileRank) {

  bool isCurrentPlayerPiece = isWhiteTurn == piece -> isWhitePlayer ();
  if (!isCurrentPlayerPiece) {
    handleInvalidMove (ChessErrHandler::NOT_OWNER_TURN, piece, 
                       sourceFileRank, sourceFileRank);
  }
  return isCurrentPlayerPiece;
}

/* pieceMoveIsValid (): 
   check if the return code for validating piece move is zero
*/
bool ChessBoard::pieceMoveIsValid
  (int returnCode, Piece* piece, string sourceFileRank, string destFileRank) {

  if (returnCode != ChessErrHandler::NO_ERROR) {
    handleInvalidMove (returnCode, piece, sourceFileRank, destFileRank);
    return false;
  }
  return true;
}

/* pieceMoveKeepsKingSafe ():
   check if given side's King is safe under the given board
   (in ChessBoard it would be a sandbox), 
   if not give out an error to user and return false
*/
bool ChessBoard::pieceMoveKeepsKingSafe (bool isWhiteTurn, Piece* piece,
  string sourceFileRank, string destFileRank, Board* board) {

  if (!kingIsSafeFromRivalry (isWhiteTurn, board)) {
    handleInvalidMove (ChessErrHandler::ALLOW_KING_IN_CHECK, piece, 
                       sourceFileRank, destFileRank);
    return false;
  }
  return true;
}

/* handleInvalidMove ():
   Calls the error handler to print the error, 
   passing the information given by the calling functions
*/
void ChessBoard::handleInvalidMove
  (int errorCode, Piece* piece, string sourceFileRank, string destFileRank) {
  errorHandler -> printErr (errorCode, piece, sourceFileRank, destFileRank);
}

/* kingIsSafeFromRivalry ():
   pre-cond.: board valid, existing representation of a Board
   Return true iff none of the Pieces of the other side can capture the given
     side's King (i.e. has a valid move to the King's file and rank)
   Method: Check all pieces of the other side
           For each piece check if its move to the given side's King is valid
           (if true, the given side's King is not safe)
*/
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

/* playerHaveValidMove ():
   pre-cond.: board valid, existing representation of a Board
   Return true iff the given side have a valid move on the given board
   Method: Check all pieces of the given side
           For each piece check all its valid move
           For each valid move check if given side's King is safe from attack
           (if true, there is at least one valid move for the given side)
*/
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
            Piece* captured = tryMoveAndReturnCaptured 
              (possibleSource, possibleDest, sandboxBoard);
            bool haveValidMove 
              = kingIsSafeFromRivalry (isWhiteTurn, sandboxBoard);

            delete captured;
            deepCleanBoard (sandboxBoard);
            
            if (haveValidMove) return true;
          }
        }
      }
    }
  }
  return false;
}

/* findPlayersKingFileRank ()
   pre-cond.: board valid, existing representation of a Board
   Iterate and return the location (file & rank) of the given side's King
*/
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

/* tryMoveAndReturnCaptured ():
   pre-cond.: sourceFileRank, destFileRank valid file & rank represenation
              board valid, existing rep. of a Board (expt. to be a sandbox)
   Given a board, conduct move from source to destination & get the captured
   Case 1 (try block) - Another piece in destination (conduct capture)
   Case 2 (catch block) - No piece exists in destination (conduct move)
   Return the piece if in case 1, NULL otherwise
*/
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

/* confirmMoveOnBoard ():
   pre-cond.: sourceFileRank, destFileRank valid file & rank represenation
              board valid, existing rep. of a Board (expected to be a real one)
   Given a board, conduct the move from source to destination
   Case 1 (try block) - Another piece in destination (conduct capture)
   Case 2 (catch block) - No piece exists in destination (conduct move)
*/
void ChessBoard::confirmMoveOnBoard
  (string sourceFileRank, string destFileRank, Board* board) {

  Piece* movingPiece = board -> at (sourceFileRank);
  try {
    Piece* destPiece = board -> at (destFileRank);
    delete destPiece;
    board -> at (destFileRank) = movingPiece;
  } catch (const std::out_of_range &err) {
    board -> insert ({ destFileRank, movingPiece });
  }

  movingPiece -> confirmMove ();
  board -> erase (sourceFileRank);
  makeGameNotInCheck();
}

/* Valid move report statement structure:
   A B? C?
   ((D|E)
   F)?

   A - "(name of piece) moves from (source) to (destination)"
   B - "taking (name of captured piece)" (if there is a captured piece)
   C - ", Check!" (if the other side is now in check) 
   D - "Stalemate." (if other side have no valid move while not in check)
   E - "Checkmate! (loser side) loses." (ditto, but while in check)
   F - "(unicode visualisation of chess board)"

   Also return if the game can continue or not (i.e. no checkmate/stalemate)
*/
bool ChessBoard::showMoveAndCheckIfGameCanContinue (Piece* piece, 
  string sourceFileRank, Piece* capturedPiece, string destFileRank, 
  bool isWhiteTurn, Board* board) {

  printMove (piece, sourceFileRank, destFileRank);
  if (capturedPiece != NULL) {
    printCapture (capturedPiece);
  }
  if (!kingIsSafeFromRivalry (!isWhiteTurn, board)) {
    printCheck ();
    makeGameInCheck ();
  }
  cout << endl;

  if (!playerHaveValidMove (!isWhiteTurn, board)) {
    if (isInCheck) {
      printCheckmate (!isWhiteTurn);
    } else {
      printStalemate () ;
    }
    printBoard (board);
    return false;
  }
  return true;
}

// Have a guess what it does :)
void ChessBoard::switchPlayers() {
  isWhiteTurn = !(isWhiteTurn);
}

// Deep clone the given board - including all the Piece within the map
Board* ChessBoard::cloneBoard (Board* board) {
  
  Board* clone = new Board;
  for (Board::iterator it = board -> begin () ; it != board -> end (); it++) {
    clone -> insert ({ it -> first, it -> second -> clone ()});
  }
  return clone;
}

/* deepCleanBoard ():
   deep clean the given board, free all containing Piece's memory and itself 
*/ 
void ChessBoard::deepCleanBoard (Board* board) {
  
  for (Board::iterator it = board -> begin () ; it != board -> end (); it++) {
    delete it -> second;
  }
  delete board;
}

/* print(Move|Capture|Check|Checkmate|Stalemate) ():
   Print in stdout with structured as specified in comments for 
     showMoveAndCheckIfGameCanContinue ()
*/ 
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

// Printing the state of the chessboard in unicode (graphic) representation
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
