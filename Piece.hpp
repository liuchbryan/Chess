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
    bool _isWhitePlayer;
    bool _isKing = false;
    bool isFirstMove = true;

  public:
    Piece (bool isWhitePlayer);
    virtual Piece* clone () = 0;

    void confirmMove (string destFileRank);
    bool isWhitePlayer ();
    bool isKing ();

    /* Piece.isValidMove()
       Pre-cond.: destFileRank is a valid file & rank representation
                  board is a reference to an existing map implementation of
                    current chess board situation
       Post-cond.: return 0 if the move is valid
                   respective error code (defined in ChessErrHandler class)
                     for error reporting otherwise
    */
    virtual int isValidMove (string sourceFileRank, 
      string destFileRank, map<string, Piece*>* board) = 0;

    string playerToString ();
    // Piece.toString() Post-cond.: return the string rep. of the piece
    virtual string toString () = 0;
    virtual string toGraphics () = 0;

  protected:
    bool isFriendly (Piece* that);

    bool isSameFile (string sourceFileRank, string destFileRank);
    bool isSameRank (string sourceFileRank, string destFileRank);
    bool isSameDiagonal (string sourceFileRank, string destFileRank);

    bool noVerticalObstruction
      (string sourceFileRank, string destFileRank, map<string, Piece*>* board);
    bool noHorizontalObstruction
      (string sourceFileRank, string destFileRank, map<string, Piece*>* board);
    bool noDiagonalObstruction
      (string sourceFileRank, string destFileRank, map<string, Piece*>* board);
    
    bool destExistFriendlyPiece 
      (string destFileRank, map<string, Piece*>* board);   
};

#include "ChessErrHandler.hpp"

#endif
