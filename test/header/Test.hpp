// Bryan Liu (chl312), Dept. of Computing, Imperial College London
// Test.hpp - Abstract Interface Test for All Unit Test Class

#ifndef TEST_H
#define TEST_H

#include <cassert>
#include <string>
#include <map>

#include "../../src/header/ChessInfo.hpp"
#include "../../src/header/ChessErrHandler.hpp"
#include "../../src/header/Piece.hpp"

typedef map<string, Piece*> Board;

class Test {

  public:
    virtual void runTest () = 0;
};

#endif
