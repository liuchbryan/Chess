// Bryan Liu (chl312), Dept. of Computing, Imperial College London
/* SampleGames.cpp - Representation of some extra valid games, utilising
     game engine class ChessBoard
   Sample games include:
   - Fool's Mate - quickest possible checkmate in chess
     (http://en.wikipedia.org/wiki/Fool's_mate)
   - Scholar's Mate - short game with simple mating attack by queen and bishop
     (http://en.wikipedia.org/wiki/Scholar's_mate)
   - Hohmeister vs Frank (1993) - short game on tournaments ending in stalemate
     (http://www.chessgames.com/perl/chessgame?gid=1281617)
*/

#include <iostream>

using namespace std;

#include "ChessBoard.hpp"

int main () {

  ChessBoard cb;

  cout << endl;
  cout << "===========================" << endl;
  cout << "Fool's Mate" << endl;
  cout << "===========================" << endl;
  cout << endl;
  
  cb.resetBoard();
  cb.submitMove ("F2", "F3");
  cb.submitMove ("E7", "E5");
  cb.submitMove ("G2", "G4");
  cb.submitMove ("D8", "H4");

  cout << endl;
  cout << "===========================" << endl;
  cout << "Scholar's Mate" << endl;
  cout << "===========================" << endl;
  cout << endl;

  cb.resetBoard();
  cb.submitMove ("E2", "E4");
  cb.submitMove ("E7", "E5");
  cb.submitMove ("D1", "H5");
  cb.submitMove ("B8", "C6");
  cb.submitMove ("F1", "C4");
  cb.submitMove ("G8", "F6");
  cb.submitMove ("H5", "F7");

  cout << endl;
  cout << "===========================" << endl;
  cout << "Hohmeister vs Frank (1993)" << endl;
  cout << "===========================" << endl;
  cout << endl;

  cb.resetBoard ();
  cb.submitMove ("D2", "D4");
  cb.submitMove ("E7", "E5");
  cb.submitMove ("D1", "D2");
  cb.submitMove ("E5", "E4");
  cb.submitMove ("D2", "F4");
  cb.submitMove ("F7", "F5");
  cb.submitMove ("H2", "H3");
  cb.submitMove ("F8", "B4");
  cb.submitMove ("B1", "D2");
  cb.submitMove ("D7", "D6");
  cb.submitMove ("F4", "H2");
  cb.submitMove ("C8", "E6");
  cb.submitMove ("A2", "A4");
  cb.submitMove ("D8", "H4");
  cb.submitMove ("A1", "A3");
  cb.submitMove ("C7", "C5");
  cb.submitMove ("A3", "G3");
  cb.submitMove ("F5", "F4");
  cb.submitMove ("F2", "F3");
  cb.submitMove ("E6", "B3");
  cb.submitMove ("D4", "D5");
  cb.submitMove ("B4", "A5");
  cb.submitMove ("C2", "C4");
  cb.submitMove ("E4", "E3");

  cout << endl;
  cout << "===============================================" << endl;
  cout << "Anderssen vs Kieseritzky (1851) - Immortal Game" << endl;
  cout << "===============================================" << endl;
  cout << endl;

  cb.resetBoard ();
  cb.submitMove ("E2", "E4");
  cb.submitMove ("E7", "E5");
  cb.submitMove ("F2", "F4");
  cb.submitMove ("E5", "F4");
  cb.submitMove ("F1", "C4");
  cb.submitMove ("D8", "H4");
  cb.submitMove ("E1", "F1");
  cb.submitMove ("B7", "B5");
  cb.submitMove ("C4", "B5");
  cb.submitMove ("G8", "F6");
  cb.submitMove ("G1", "F3");
  cb.submitMove ("H4", "H6");
  cb.submitMove ("D2", "D3");
  cb.submitMove ("F6", "H5");
  cb.submitMove ("F3", "H4");
  cb.submitMove ("H6", "G5");
  cb.submitMove ("H4", "F5");
  cb.submitMove ("C7", "C6");
  cb.submitMove ("G2", "G4");
  cb.submitMove ("H5", "F6");
  cb.submitMove ("H1", "G1");
  cb.submitMove ("C6", "B5");
  cb.submitMove ("H2", "H4");
  cb.submitMove ("G5", "G6");
  cb.submitMove ("H4", "H5");
  cb.submitMove ("G6", "G5");
  cb.submitMove ("D1", "F3");
  cb.submitMove ("F6", "G8");
  cb.submitMove ("C1", "F4");
  cb.submitMove ("G5", "F6");
  cb.submitMove ("B1", "C3");
  cb.submitMove ("F8", "C5");
  cb.submitMove ("C3", "D5");
  cb.submitMove ("F6", "B2");
  cb.submitMove ("F4", "D6");
  cb.submitMove ("C5", "G1");
  cb.submitMove ("E4", "E5");
  cb.submitMove ("B2", "A1");
  cb.submitMove ("F1", "E2");
  cb.submitMove ("B8", "A6");
  cb.submitMove ("F5", "G7");
  cb.submitMove ("E8", "D8");
  cb.submitMove ("F3", "F6");
  cb.submitMove ("G8", "F6");
  cb.submitMove ("D6", "E7");

}
