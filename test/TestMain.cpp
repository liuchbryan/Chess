// Bryan Liu (chl312), Dept. of Computing, Imperial College London
// Main Testing Program

#include "../ChessBoard.hpp"

#include "header/PawnTest.hpp"
#include "header/KnightTest.hpp"

int chessBoardTest () {
  
  ChessBoard cb;
 
  // Source/Dest not valid
  cb.submitMove ("J9", "H8"); 
  cb.submitMove ("A1", "H0");
  
  // Empty Square
  cb.submitMove ("G3", "G4");
  
  // Wrong player's turn (Currently white);
  cb.submitMove ("F7", "F6");
  
  // more subtle ones in SampleGames

  return 0;
}

int main () {

  cout << "Test Engine for Chess Simulation" << endl;

  cout << endl << "--- ChessBoard Test ---" << endl;
  chessBoardTest();

  cout << endl << "--- Piece Unit Tests ---" << endl;

  PawnTest pawnTest;
  pawnTest.runTest();
  
  KnightTest knightTest;
  knightTest.runTest();

  cout << "End of tests" << endl;
  return 0;
}
