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
        
    virtual int isValidMove 
      (string destFileRank, map<string, Piece*>* board) = 0;

    string playerToString ();
    virtual string toString () = 0;

  protected:
    bool isFriendly (Piece* that);

    bool isSameFile (string thatFileRank);
    bool isSameRank (string thatFileRank);
    bool isSameDiagonal (string thatFileRank);

    bool noObstruction (string destFileRank, map<string, Piece*>* board);
    
    bool destExistFriendlyPiece 
      (string destFileRank, map<string, Piece*>* board);   
};

#include "ChessErrHandler.hpp"

#endif
