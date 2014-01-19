// Bryan Liu (chl312), Dept. of Computing, Imperial College London
// Piece.hpp - (abstract class) Piece

/* Represent Implementation of a general piece in chess
   Including general, common methods a piece using to validate its own move
    and hook methods isValidMove() and toString()   
*/

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

    string getFileRank ();
    void updateFileRank (string fileRank);

    bool isWhitePlayer ();
        
  /* Piece.isValidMove()
     Pre-cond.: destFileRank is a valid file & rank representation
                board a reference to an existing map implementation of
                 current chess board situation
     Post-cond.: return 0 if the move is valid
                 respective error code (defined in ChessErrHandler class)
                  for error reporting otherwise
  */
    virtual int isValidMove 
      (string destFileRank, map<string, Piece*>* board) = 0;

  /* Piece.toString()
     Post-cond.: return the string representation of the piece
  */
    string playerToString ();
    virtual string toString () = 0;

  protected:
    bool isFriendly (Piece* that);

    bool isSameFile (string thatFileRank);
    bool isSameRank (string thatFileRank);
    bool isSameDiagonal (string thatFileRank);

    bool noVerticalObstruction 
      (string destFileRank, map<string, Piece*>* board);
    bool noHorizontalObstruction
      (string destFileRank, map<string, Piece*>* board);
    bool noDiagonalObstruction
      (string destFileRank, map<string, Piece*>* board);
    
    bool destExistFriendlyPiece 
      (string destFileRank, map<string, Piece*>* board);   
};

#include "ChessErrHandler.hpp"

#endif
