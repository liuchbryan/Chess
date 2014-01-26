// Bryan Liu (chl312), Dept. of Computing, Imperial College London
// Test.hpp - Abstract Interface Test for All Unit Test Class

#ifndef TEST_H
#define TEST_H

#include <cassert>
#include <string>

#include "../src/header/ChessInfo.hpp"

class Test {

  public:
    virtual void runTest () = 0;
};

#endif
