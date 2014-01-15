// Skeleton C++ file, you will need to edit this for your submission.

// Your final submission must expose the constructor, deconstructor, 
// submitMove and resetBoard methods.
// You may add any additonal files/methods as you see fit
// (be sure to also include them in the makefile).

#include "ChessBoard.hpp"

using namespace std;

ChessBoard::ChessBoard() {
  
  resetBoard();
}

ChessBoard::~ChessBoard()
{
  cout << "TODO: implement ChessBoard deconstructor" << endl;
}

void ChessBoard::submitMove(const char* fromSquare, const char* toSquare){
  string initFileRank (fromSquare);
  string destFileRank (toSquare);

  if (initFileRank.compare(destFileRank) == 0) {
    cout << "Invalid move: destination is the same as the source" << endl;
    return;
  }
  if (board->at(initFileRank)->isValidMove(destFileRank, board)) {
  } else {
    cout << "You idiot! This is not Valid!" << endl;
  }
}    

void ChessBoard::resetBoard(){
  // apprently we need to delete recursively all the pieces within the map
  // leave it to later stage then

  board = new map<string, Piece*>;

  string fileRank({ 'A', '1' });

  for (char i = MIN_FILE; i <= MAX_FILE; i++) {
    fileRank.front() = i;

    fileRank.back() = WHITE_INIT_PAWN_RANK;
    board->insert ({fileRank, new Pawn (fileRank, true)});

    for (char j = MIN_INIT_EMPTY_RANK; j <= MAX_INIT_EMPTY_RANK; j++) {
      fileRank.back() = j;
      board->insert ({fileRank, new EmptyPiece (fileRank, true)});
    }

    fileRank.back() = BLACK_INIT_PAWN_RANK;
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

bool ChessBoard::isWhiteTurn(){
  return _isWhiteTurn;
}

bool ChessBoard::isBlackTurn(){
  return !(_isWhiteTurn);
}

bool ChessBoard::withinChessBoard(string destFileRank) {
  char destFile = destFileRank.at(FILE_INDEX);
  char destRank = destFileRank.at(RANK_INDEX);
  return MIN_FILE <= destFile && destFile <= MAX_FILE &&
         MIN_RANK <= destRank && destRank <= MAX_RANK;
}
