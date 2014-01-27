// Bryan Liu (chl312), Dept. of Computing, Imperial College London
// KnightTest.cpp - Implementation of runTest for KnightTest

#include "header/KnightTest.hpp"

void KnightTest::runTest () {
  
  cout << "Running Unit Test for Knight" << endl;
  
  testKnightMovesInAnyLShape ();
  cout << ".";
  testKnightOnlyMovesInLShape ();
  cout << ".";

  testKnightCanJumpOverOtherPieces ();
  cout << ".";

  testKnightCanCaptureEnemyPieceInDestination ();
  cout << ".";
  testKnightCannotMoveAndCaptureFriendlies ();
  cout << ".";

  cout << endl;
}

void KnightTest::testKnightMovesInAnyLShape () {
  
  Board* theBoard = new Board ();
  
  Knight myKnight (true);
  assert (myKnight.isValidMove (string("D4"), string("B5"), theBoard)
            == ChessErrHandler::NO_ERROR);
  assert (myKnight.isValidMove (string("D4"), string("C6"), theBoard)
            == ChessErrHandler::NO_ERROR);
  assert (myKnight.isValidMove (string("D4"), string("E6"), theBoard)
            == ChessErrHandler::NO_ERROR);
  assert (myKnight.isValidMove (string("D4"), string("F5"), theBoard)
            == ChessErrHandler::NO_ERROR);
  assert (myKnight.isValidMove (string("D4"), string("F3"), theBoard)
            == ChessErrHandler::NO_ERROR);
  assert (myKnight.isValidMove (string("D4"), string("E2"), theBoard)
            == ChessErrHandler::NO_ERROR);
  assert (myKnight.isValidMove (string("D4"), string("C2"), theBoard)
            == ChessErrHandler::NO_ERROR);
  assert (myKnight.isValidMove (string("D4"), string("B3"), theBoard)
            == ChessErrHandler::NO_ERROR);

  Knight theirKnight (false);
  assert (theirKnight.isValidMove (string("D4"), string("B5"), theBoard)
            == ChessErrHandler::NO_ERROR);
  assert (theirKnight.isValidMove (string("D4"), string("C6"), theBoard)
            == ChessErrHandler::NO_ERROR);
  assert (theirKnight.isValidMove (string("D4"), string("E6"), theBoard)
            == ChessErrHandler::NO_ERROR);
  assert (theirKnight.isValidMove (string("D4"), string("F5"), theBoard)
            == ChessErrHandler::NO_ERROR);
  assert (theirKnight.isValidMove (string("D4"), string("F3"), theBoard)
            == ChessErrHandler::NO_ERROR);
  assert (theirKnight.isValidMove (string("D4"), string("E2"), theBoard)
            == ChessErrHandler::NO_ERROR);
  assert (theirKnight.isValidMove (string("D4"), string("C2"), theBoard)
            == ChessErrHandler::NO_ERROR);
  assert (theirKnight.isValidMove (string("D4"), string("B3"), theBoard)
            == ChessErrHandler::NO_ERROR);

  delete theBoard; 
}

void KnightTest::testKnightOnlyMovesInLShape () {

  Board* theBoard = new Board ();

  Knight myKnight (true);
  // Not a queen/ bishop
  assert (myKnight.isValidMove (string("D4"), string("B2"), theBoard)
            == ChessErrHandler::ILLEGAL_MOVE_PATTERN);
  // Not a rook either
  assert (myKnight.isValidMove (string("D4"), string("D1"), theBoard)
            == ChessErrHandler::ILLEGAL_MOVE_PATTERN);
  assert (myKnight.isValidMove (string("D4"), string("B4"), theBoard)
            == ChessErrHandler::ILLEGAL_MOVE_PATTERN);
  // Not a pawn especially - why do you want to walk when you have a horse?
  assert (myKnight.isValidMove (string("D4"), string("E5"), theBoard)
            == ChessErrHandler::ILLEGAL_MOVE_PATTERN);

  Knight theirKnight (false);
  // No one has the ability to fly
  assert (myKnight.isValidMove (string("B1"), string("D8"), theBoard)
            == ChessErrHandler::ILLEGAL_MOVE_PATTERN);

  delete theBoard;
}

void KnightTest::testKnightCanJumpOverOtherPieces () {

  Board* theBoard = new Board ();

  Pawn myPawn (true);
  Pawn theirPawn (false);
  Pawn anotherPawn (false);
  Pawn yetAnotherPawn (true);
  Pawn morePawn (true);
  Pawn stillAPawn (false);
  Pawn pawnAttack (true);
  
  // An unrealistic cluster of Pawn
  theBoard -> insert ({ string("A4"), &myPawn });
  theBoard -> insert ({ string("B4"), &theirPawn });
  theBoard -> insert ({ string("C4"), &anotherPawn });
  theBoard -> insert ({ string("D4"), &yetAnotherPawn });
  theBoard -> insert ({ string("A5"), &morePawn });
  theBoard -> insert ({ string("C5"), &stillAPawn });
  theBoard -> insert ({ string("B3"), &pawnAttack });

  Knight myKnight (true);
  assert (myKnight.isValidMove (string("C3"), string("B5"), theBoard)
            == ChessErrHandler::NO_ERROR);

  Knight theirKnight (false);
  assert (theirKnight.isValidMove (string("B5"), string("D6"), theBoard)
            == ChessErrHandler::NO_ERROR);

  delete theBoard;
}

void KnightTest::testKnightCanCaptureEnemyPieceInDestination () {

  Board* theBoard = new Board ();

  Pawn myPawn (true);
  Pawn theirPawn (true);
  Pawn anotherPawn (true);
  Pawn yetAnotherPawn (true);
  Pawn morePawn (false);
  Pawn stillAPawn (false);
  Pawn pawnAttack (false);
  Pawn finallyEnoughPawn (false);
  
  theBoard -> insert ({ string("B5"), &myPawn });
  theBoard -> insert ({ string("C6"), &theirPawn });
  theBoard -> insert ({ string("E6"), &anotherPawn });
  theBoard -> insert ({ string("F5"), &yetAnotherPawn });
  theBoard -> insert ({ string("F3"), &morePawn });
  theBoard -> insert ({ string("E2"), &stillAPawn });
  theBoard -> insert ({ string("C2"), &pawnAttack });
  theBoard -> insert ({ string("B3"), &finallyEnoughPawn });

  Knight myKnight (true);
  assert (myKnight.isValidMove (string("D4"), string("F3"), theBoard)
            == ChessErrHandler::NO_ERROR);
  assert (myKnight.isValidMove (string("D4"), string("E2"), theBoard)
            == ChessErrHandler::NO_ERROR);
  assert (myKnight.isValidMove (string("D4"), string("C2"), theBoard)
            == ChessErrHandler::NO_ERROR);
  assert (myKnight.isValidMove (string("D4"), string("B3"), theBoard)
            == ChessErrHandler::NO_ERROR);

  Knight theirKnight (false);
  assert (theirKnight.isValidMove (string("D4"), string("B5"), theBoard)
            == ChessErrHandler::NO_ERROR);
  assert (theirKnight.isValidMove (string("D4"), string("C6"), theBoard)
            == ChessErrHandler::NO_ERROR);
  assert (theirKnight.isValidMove (string("D4"), string("E6"), theBoard)
            == ChessErrHandler::NO_ERROR);
  assert (theirKnight.isValidMove (string("D4"), string("F5"), theBoard)
            == ChessErrHandler::NO_ERROR);

  delete theBoard;
}

void KnightTest::testKnightCannotMoveAndCaptureFriendlies () {
// Idea: flip the colour of the testing knights

  Board* theBoard = new Board ();

  Pawn myPawn (true);
  Pawn theirPawn (true);
  Pawn anotherPawn (true);
  Pawn yetAnotherPawn (true);
  Pawn morePawn (false);
  Pawn stillAPawn (false);
  Pawn pawnAttack (false);
  Pawn finallyEnoughPawn (false);
  
  theBoard -> insert ({ string("B5"), &myPawn });
  theBoard -> insert ({ string("C6"), &theirPawn });
  theBoard -> insert ({ string("E6"), &anotherPawn });
  theBoard -> insert ({ string("F5"), &yetAnotherPawn });
  theBoard -> insert ({ string("F3"), &morePawn });
  theBoard -> insert ({ string("E2"), &stillAPawn });
  theBoard -> insert ({ string("C2"), &pawnAttack });
  theBoard -> insert ({ string("B3"), &finallyEnoughPawn });

  Knight myKnight (true);
  assert (myKnight.isValidMove (string("D4"), string("B5"), theBoard)
            == ChessErrHandler::FRIENDLY_AT_DEST);
  assert (myKnight.isValidMove (string("D4"), string("C6"), theBoard)
            == ChessErrHandler::FRIENDLY_AT_DEST);
  assert (myKnight.isValidMove (string("D4"), string("E6"), theBoard)
            == ChessErrHandler::FRIENDLY_AT_DEST);
  assert (myKnight.isValidMove (string("D4"), string("F5"), theBoard)
            == ChessErrHandler::FRIENDLY_AT_DEST);
  
  Knight theirKnight (false);
  assert (theirKnight.isValidMove (string("D4"), string("F3"), theBoard)
            == ChessErrHandler::FRIENDLY_AT_DEST);
  assert (theirKnight.isValidMove (string("D4"), string("E2"), theBoard)
            == ChessErrHandler::FRIENDLY_AT_DEST);
  assert (theirKnight.isValidMove (string("D4"), string("C2"), theBoard)
            == ChessErrHandler::FRIENDLY_AT_DEST);
  assert (theirKnight.isValidMove (string("D4"), string("B3"), theBoard)
            == ChessErrHandler::FRIENDLY_AT_DEST);

  delete theBoard;
}
