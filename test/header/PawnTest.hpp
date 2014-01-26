// Bryan Liu (chl312), Dept. of Computing, Imperial College London
// PawnTest.hpp - PawnTest implementing Test

#ifndef PAWNTEST_H
#define PAWNTEST_H

#include "Test.hpp"
#include "../../src/header/Pawn.hpp"
#include "../../src/header/Bishop.hpp"

class PawnTest : public Test {

  public:
    void runTest ();

  private:
    void testWhiteAndBlackPawnAdvancesInCorrectDirection();

    void testPawnCanAdvanceTwoRanksInFirstMove();
    void testPawnCanOnlyAdvanceOneRankAfterFirstMove();

    void testPawnCannotSkipOverPiecesWhileAdvanceTwoRanksInFirstMove();
    void testPawnCannotMoveOrCaptureIfThereArePiecesDirectlyAhead();

    void testPawnCannotMoveToOtherFilesIfNotCapturing();
    void testPawnCannotMoveToOtherRandomSquaresIfNotCapturing();

    void testPawnCanCaptureEnimiesDiagonally();
    void testPawnCannotCaptureFriendliesDiagonally();
};

#endif
