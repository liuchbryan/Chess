// Bryan Liu (chl312), Dept. of Computing, Imperial College London

#ifndef PIECES_H
#define PIECES_H

#include <map>
#include <string>
#include <cmath>
#include <stdexcept>

#include "ChessInfo.hpp"

using namespace std;

class Piece {

  protected:
    char file;
    char rank;
    bool _isWhitePlayer;

  public:
    Piece (string fileRank, bool isWhitePlayer);
    ~Piece ();

    bool isWhitePlayer ();
    bool isFriendly (Piece* that);
    
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
