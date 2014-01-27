// Bryan Liu (chl312), Dept. of Computing, Imperial College London
// KnightTest.hpp - KnightTest implementing Test (Unit Test for Knight Moves)

#ifndef KNIGHTTEST_H
#define KNIGHTTEST_H

#include "Test.hpp"
#include "../../src/header/Knight.hpp"
#include "../../src/header/Pawn.hpp"

class KnightTest : public Test {

  public:
    void runTest ();

  private:
    void testKnightMovesInAnyLShape ();
    void testKnightOnlyMovesInLShape ();

    void testKnightCanJumpOverOtherPieces ();

    void testKnightCanCaptureEnemyPieceInDestination ();
    void testKnightCannotMoveAndCaptureFriendlies ();
};

#endif
