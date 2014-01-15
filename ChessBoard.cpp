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

  for (char i = MIN_FILE; i <= MAX_FILE; i++) {
    for (char j = MIN_RANK; j <= MAX_RANK; j++) {
      string fileRank ({ i, j });
      
      board->insert({fileRank, new EmptyPiece(fileRank, true)});
    }
  }
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

