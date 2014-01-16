// Bryan Liu (chl312), Dept. of Computing, Imperial College London

#ifndef PIECES_H
#define PIECES_H

#include <map>
#include <string>
#include <cmath>

using namespace std;

class Piece {

  private:
    const int ZERO = 0;
    const char MIN_FILE = 'A';
    const char MAX_FILE = 'H';
    const char MIN_RANK = '1';
    const char MAX_RANK = '8';

    char file;
    char rank;
    bool _isWhitePlayer;

  public:
    Piece (string fileRank, bool isWhitePlayer);
    ~Piece ();

    bool isWhitePlayer ();
    
    virtual int isValidMove 
      (string destFileRank, map<string, Piece*>* board) = 0;

    string playerToString ();

    virtual string toString () = 0;

  protected:
    bool isSameFile (char thatFile);
    bool isSameRank (char thatRank);
    bool isSameDiagonal (char thatFile, char thatRank);
   
};

#include "ChessErrHandler.hpp"

#endif
