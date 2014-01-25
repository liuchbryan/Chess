// Bryan Liu (chl312), Dept. of Computing, Imperial College London
// ChessBoard.hpp - ChessBoard 
// (Representing implementation of a Chess game engine)

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <map>
#include <iostream>
#include <string>
#include <stdexcept>

#include "src/header/ChessErrHandler.hpp"
#include "src/header/ChessInfo.hpp"

#include "src/header/Piece.hpp"
#include "src/header/EmptyPiece.hpp"
#include "src/header/King.hpp"
#include "src/header/Queen.hpp"
#include "src/header/Bishop.hpp"
#include "src/header/Rook.hpp"
#include "src/header/Knight.hpp"
#include "src/header/Pawn.hpp"

using namespace std;

/* Improving clarity - the map of string (file & rank) to (ref. to) Piece would
                       be simply known as Board (as it represents a board)
*/
typedef map<string, Piece*> Board;

class ChessBoard {

/* 

*/
  private:
    Board* board;
    ChessErrHandler* errorHandler;

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
    bool isCurrentPlayerPiece (Piece* piece, string sourceFileRank);
    bool pieceMoveIsValid (int returnCode, Piece* piece,
                           string sourceFileRank, string destFileRank);
    void handleInvalidMove (int returnCode, Piece* piece,
                            string sourceFileRank, string destFileRank);

    bool kingIsSafeFromRivalry
      (bool isWhiteTurn, map<string, Piece*>* board);
    bool playerHaveValidMove (bool isWhiteTurn, Board* board);
    string findPlayersKingFileRank (bool isWhiteTurn, Board* board);

    Piece* tryMoveAndReturnCaptured (string sourceFileRank,
                                     string destFileRank, Board* board);
    void confirmMove
      (string sourceFileRank, string destFileRank, Board* board);

    void switchPlayers ();

    Board* cloneBoard (Board* board);

    void printMove (Piece* piece, string sourceFileRank, string destFileRank);
    void printCapture (Piece* capturedPiece);
    void printCheck ();
    void printCheckmate (bool isWhitePlayer);
    void printStalemate ();

    void printBoard (Board* board);
};

#endif
