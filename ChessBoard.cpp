// Skeleton C++ file, you will need to edit this for your submission.

// Your final submission must expose the constructor, deconstructor, 
// submitMove and resetBoard methods.
// You may add any additonal files/methods as you see fit
// (be sure to also include them in the makefile).

#include <map>
#include <iostream>
#include <string>

#include "Piece.hpp"
#include "EmptyPiece.hpp"
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
  
  if (board->at(string(fromSquare))->isValidMove(string(toSquare), board)) {
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

