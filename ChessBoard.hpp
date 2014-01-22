// Skeleton header file, you will need to edit this for your submission.

// Your final submission must expose the constructor, deconstructor, 
// submitMove and resetBoard methods.
// You may add any additonal files/methods as you see fit
// (be sure to also include them in the makefile).


#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <map>
#include <iostream>
#include <string>
#include <stdexcept>

#include "ChessErrHandler.hpp"
#include "ChessInfo.hpp"

#include "Piece.hpp"
#include "EmptyPiece.hpp"
#include "King.hpp"
#include "Queen.hpp"
#include "Bishop.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Pawn.hpp"

using namespace std;

typedef map<string, Piece*> Board;

class ChessBoard {

  private:
    Board* board;
    ChessErrHandler* errorHandler;

    Piece* whiteKing;
    Piece* blackKing;

    bool isWhiteTurn = true;
    bool isInCheck = false;
    bool hasEnded = false;

  public:
    ChessBoard();
    ~ChessBoard();

    void resetBoard();

    void submitMove(const char* fromSquare, const char* toSquare);

  private:
    bool gameCanContinue (string sourceFileRank, string destFileRank);

    bool sourceAndDestIsValid (string sourceFileRank, string destFileRank);
    bool withinChessBoard (string fileRank);

    bool sourceIsNotEmpty (string sourceFileRank);
    bool isCurrentPlayerPiece (Piece* piece);
    void handleInvalidMove (int returnCode, Piece* piece, 
      string sourceFileRank, string destFileRank);

    bool kingIsSafeFromRivalry 
      (bool isWhiteTurn, map<string, Piece*>* board);

    Piece* tryMoveAndReturnCaptured (string sourceFileRank, string destFileRank, Board* board);
    void confirmMove (Piece* movingPiece, 
  string sourceFileRank, string destFileRank, Board* board);

    void switchPlayers ();

    bool playerHaveValidMove (bool isWhiteTurn, Board* board);
  
    Piece* findPlayersKing (bool isWhiteTurn, Board* board);
    Board* cloneBoard (Board* board);

    void printMove (Piece* piece, string sourceFileRank, string destFileRank);
    void printCapture (Piece* capturedPiece);
    void printCheck ();
    void printCheckmate (bool isWhitePlayer);
    void printStalemate ();

    void printBoard (Board* board);
};

#endif
