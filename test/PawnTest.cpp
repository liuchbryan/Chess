// Bryan Liu (chl312), Dept. of Computing, Imperial College London
// PawnTest.cpp - Implementation of runTest for PawnTest

#include "header/PawnTest.hpp"

void PawnTest::runTest () {
  
  testWhiteAndBlackPawnAdvancesInCorrectDirection();

  testPawnCanAdvanceOneRankInFirstMove();
  testPawnCanAdvanceTwoRanksInFirstMove();
  testPawnCanOnlyAdvanceOneRankAfterFirstMove();

  testPawnCannotMoveOrCaptureIfThereArePiecesDirectlyAhead();

  testPawnCannotMoveToOtherFilesIfNotCapturing();
  testPawnCannotMoveToOtherRandomSquaresIfNotCapturing();

  testPawnCanCaptureEnimiesDiagonally();
  testPawnCannotCaptureFriendliesDiagonally();
}


