// Bryan Liu (chl312), Dept. of Computing, Imperial College London
// Main Testing Program

#include "../ChessBoard.hpp"

#include "header/PawnTest.hpp"
#include "header/KnightTest.hpp"

int chessBoardTest () {
  
  ChessBoard cb;

  // Invalid file and rank representation
  cb.submitMove ("A", "B");
  cb.submitMove ("ABC", "DEF");
  cb.submitMove ("A5H", "B6H");
  cb.submitMove ("This is total madness", "I can't believe it");
 
  // Source/Dest not valid
  cb.submitMove ("J9", "H8");
  cb.submitMove ("2D", "4D");
  cb.submitMove ("A1", "H0");
  
  // Empty Square
  cb.submitMove ("G3", "G4");
  
  // Wrong player's turn (Currently white's turn);
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

  cout << endl << "End of tests" << endl;
  return 0;
}
