#ifndef CHESSERRHANDLER_H
#define CHESSERRHANDLER_H

#include <string>

class ChessErrHandler {

  public:   
    static const int NO_ERR = 0;
    static const int ERR10 = 10;
    static const int ERR11 = 11;
    static const int ERR12 = 12;
    static const int ERR20 = 20;
    static const int ERR21 = 21;
    static const int ERR22 = 22;
    static const int ERR30 = 30;
    static const int ERR40 = 40;
    static const int ERR41 = 41;
    static const int ERR42 = 42;

  public:
    void printErr (int errNo); 

  private:
    ChessErrHandler ();

};

#endif
