#include <iostream>

using namespace std;

#include "ChessBoard.hpp"

int main () {

  ChessBoard cb;

  cout << endl;
  cout << "===========================" << endl;
  cout << " Fool's Mate" << endl;
  cout << "===========================" << endl;
  cout << endl;
  
  cb.resetBoard();
  cb.submitMove ("F2", "F3");
  cb.submitMove ("E7", "E5");
  cb.submitMove ("G2", "G4");
  cb.submitMove ("D8", "H4");

  cout << endl;
  cout << "===========================" << endl;
  cout << " Scholar's Mate" << endl;
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
  cout << " Hohmeister vs Frank (1993)" << endl;
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
}
