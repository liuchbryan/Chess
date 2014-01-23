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
  cout << " Scholar's Mate" << endl;
  cout << "===========================" << endl;
  cout << endl;

  cb.resetBoard ();
}
