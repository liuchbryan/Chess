// Bryan Liu (chl312), Dept. of Computing, Imperial College London
// PawnTest.cpp - Implementation of runTest for PawnTest

#include "header/PawnTest.hpp"

void PawnTest::runTest () {
  
  cout << "Running Unit Test for Pawn" << endl;

  testWhiteAndBlackPawnAdvancesInCorrectDirection();
  cout << ".";

  testPawnCanAdvanceTwoRanksInFirstMove();
  cout << ".";
  testPawnCanOnlyAdvanceOneRankAfterFirstMove();
  cout << ".";

  testPawnCannotSkipOverPiecesWhileAdvanceTwoRanksInFirstMove();
  cout << ".";
  testPawnCannotMoveOrCaptureIfThereArePiecesDirectlyAhead();
  cout << ".";

  testPawnCannotMoveToOtherFilesIfNotCapturing();
  cout << ".";
  testPawnCannotMoveToOtherRandomSquaresIfNotCapturing();
  cout << ".";

  testPawnCanCaptureEnimiesDiagonally();
  cout << ".";
  testPawnCannotCaptureFriendliesDiagonally();
  cout << ".";


  cout << endl;
}

void PawnTest::testWhiteAndBlackPawnAdvancesInCorrectDirection() {

  Board* theBoard = new Board ();

  Pawn myPawn (true);
  assert (myPawn.isValidMove (string("D4"), string("D5"), theBoard)
            == ChessErrHandler::NO_ERROR);
  assert (myPawn.isValidMove (string("D4"), string("D3"), theBoard)
            == ChessErrHandler::ILLEGAL_MOVE_PATTERN);
  
  Pawn theirPawn (false);
  assert (theirPawn.isValidMove (string("D5"), string("D4"), theBoard)
            == ChessErrHandler::NO_ERROR);
  assert (theirPawn.isValidMove (string("D3"), string("D4"), theBoard)
            == ChessErrHandler::ILLEGAL_MOVE_PATTERN);

  delete theBoard;
}

void PawnTest::testPawnCanAdvanceTwoRanksInFirstMove() {

  Board* theBoard = new Board ();

  Pawn myPawn (true);
  assert (myPawn.isValidMove (string("D2"), string("D4"), theBoard)
            == ChessErrHandler::NO_ERROR);

  Pawn theirPawn (false);
  assert (theirPawn.isValidMove (string("E7"), string("E5"), theBoard)
            == ChessErrHandler::NO_ERROR);

  delete theBoard;
}

void PawnTest::testPawnCanOnlyAdvanceOneRankAfterFirstMove() {
  
  Board* theBoard = new Board ();

  Pawn myPawn (true);
  myPawn.confirmMove();
  assert (myPawn.isValidMove (string("D3"), string("D5"), theBoard)
            == ChessErrHandler::ILLEGAL_MOVE_PATTERN);
  assert (myPawn.isValidMove (string("D3"), string("D4"), theBoard)
            == ChessErrHandler::NO_ERROR);

  Pawn theirPawn (false);
  theirPawn.confirmMove();
  assert (theirPawn.isValidMove (string("E6"), string("E4"), theBoard)
            == ChessErrHandler::ILLEGAL_MOVE_PATTERN);
  assert (theirPawn.isValidMove (string("E6"), string("E5"), theBoard)
            == ChessErrHandler::NO_ERROR);

  delete theBoard;
}

void PawnTest::testPawnCannotSkipOverPiecesWhileAdvanceTwoRanksInFirstMove() {

  Board* theBoard = new Board ();

  Pawn myPawn (true);
  Pawn myOtherPawn (true);
  Bishop obstacle (false);

  theBoard -> insert ({ string("C3"), &obstacle });

  assert (myPawn.isValidMove (string("C2"), string ("C4"), theBoard)
            == ChessErrHandler::OBSTRUCTION_EN_ROUTE);
  assert (myOtherPawn.isValidMove (string("D2"), string("D4"), theBoard)
            == ChessErrHandler::NO_ERROR);

  Pawn theirPawn (false);
  Bishop anotherObstacle (false);
  
  theBoard -> insert ({ string("E6"), &anotherObstacle });
  assert (theirPawn.isValidMove (string("E7"), string ("E5"), theBoard)
            == ChessErrHandler::OBSTRUCTION_EN_ROUTE);
  assert (theirPawn.isValidMove (string("D7"), string("D5"), theBoard)
            == ChessErrHandler::NO_ERROR);

  delete theBoard;
}

void PawnTest::testPawnCannotMoveOrCaptureIfThereArePiecesDirectlyAhead() {
  
  Board* theBoard = new Board ();

  Pawn myPawn (true);
  Bishop obstacle (false);
  Bishop anotherObstacle (true);

  theBoard -> insert ({ string("D6"), &obstacle });
  assert (myPawn.isValidMove (string("D5"), string("D6"), theBoard)
            == ChessErrHandler::PAWN_ILLEGAL_CAPTURE_PATTERN);

  theBoard -> at (string("D6")) = &anotherObstacle;
  assert (myPawn.isValidMove (string("D5"), string("D6"), theBoard)
            == ChessErrHandler::FRIENDLY_AT_DEST);

  delete theBoard;
}

void PawnTest::testPawnCannotMoveToOtherFilesIfNotCapturing() {
  
  Board* theBoard = new Board ();

  Pawn myPawn (true);
  assert (myPawn.isValidMove (string("D5"), string("E6"), theBoard)
            == ChessErrHandler::ILLEGAL_MOVE_PATTERN);
  assert (myPawn.isValidMove (string("G2"), string("F3"), theBoard)
            == ChessErrHandler::ILLEGAL_MOVE_PATTERN);
  
  Pawn theirPawn (false);
  assert (myPawn.isValidMove (string("E7"), string("D6"), theBoard)
            == ChessErrHandler::ILLEGAL_MOVE_PATTERN);
  assert (myPawn.isValidMove (string("D7"), string("E6"), theBoard)
            == ChessErrHandler::ILLEGAL_MOVE_PATTERN);

  delete theBoard;
}

void PawnTest::testPawnCannotMoveToOtherRandomSquaresIfNotCapturing() {

  Board* theBoard = new Board ();

  Pawn myPawn (true);
  // Still a pawn before promoting, be patient lol
  assert (myPawn.isValidMove (string("E2"), string("E8"), theBoard)
            == ChessErrHandler::ILLEGAL_MOVE_PATTERN);
  // Not a bishop either, similarly not a queen
  assert (myPawn.isValidMove (string("E2"), string("H5"), theBoard)
            == ChessErrHandler::ILLEGAL_MOVE_PATTERN);
  // Not a knight either
  assert (myPawn.isValidMove (string("E2"), string("D4"), theBoard)
            == ChessErrHandler::ILLEGAL_MOVE_PATTERN);
 
  delete theBoard;
}

void PawnTest::testPawnCanCaptureEnimiesDiagonally() {

  Board* theBoard = new Board ();
  
  Pawn myPawn (true);
  Bishop theirBishop (false);
  Bishop theirOtherBishop (false);
  Bishop theirMagicalBishop (false);
 
  theBoard -> insert ({ string("C6"), &theirBishop });
  theBoard -> insert ({ string("E6"), &theirOtherBishop });
  theBoard -> insert ({ string("E4"), &theirMagicalBishop });

  assert (myPawn.isValidMove (string("D5"), string("C6"), theBoard)
            == ChessErrHandler::NO_ERROR);
  assert (myPawn.isValidMove (string("D5"), string("E6"), theBoard)
            == ChessErrHandler::NO_ERROR);
  assert (myPawn.isValidMove (string("D5"), string("E4"), theBoard)
            == ChessErrHandler::ILLEGAL_MOVE_PATTERN);

  Pawn theirPawn (false);
  Bishop myBishop (true);
  Bishop myOtherBishop (true);
 
  theBoard -> insert ({ string("C4"), &myBishop });
  theBoard -> at (string("E4")) = &myOtherBishop;

  assert (theirPawn.isValidMove (string("D5"), string("C4"), theBoard)
            == ChessErrHandler::NO_ERROR);
  assert (theirPawn.isValidMove (string("D5"), string("E4"), theBoard)
            == ChessErrHandler::NO_ERROR);

  delete theBoard;
}

void PawnTest::testPawnCannotCaptureFriendliesDiagonally() {
  
  Board* theBoard = new Board ();

  Pawn myPawn (true);
  Bishop myBishop (true);
  Bishop theirBishop (false);
 
  theBoard -> insert ({ string("C6"), &myBishop });
  theBoard -> insert ({ string("E6"), &theirBishop });

  assert (myPawn.isValidMove (string("D5"), string("C6"), theBoard)
            == ChessErrHandler::ILLEGAL_MOVE_PATTERN);
  assert (myPawn.isValidMove (string("D5"), string("E6"), theBoard)
            == ChessErrHandler::NO_ERROR);

  Pawn theirPawn (false);
 
  theBoard -> erase (string("C6"));
  theBoard -> erase (string("E6"));
  theBoard -> insert ({ string("C4"), &myBishop });
  theBoard -> insert ({ string("E4"), &theirBishop });

  assert (theirPawn.isValidMove (string("D5"), string("C4"), theBoard)
            == ChessErrHandler::NO_ERROR);
  assert (theirPawn.isValidMove (string("D5"), string("E4"), theBoard)
            == ChessErrHandler::ILLEGAL_MOVE_PATTERN);

  delete theBoard;
}
