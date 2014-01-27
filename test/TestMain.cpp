// Bryan Liu (chl312), Dept. of Computing, Imperial College London
// Main Testing Program

#include "header/PawnTest.hpp"
#include "header/KnightTest.hpp"

int main () {
  PawnTest pawnTest;
  pawnTest.runTest();
  
  KnightTest knightTest;
  knightTest.runTest();

  cout << "End of tests." << endl;
  return 0;
}
