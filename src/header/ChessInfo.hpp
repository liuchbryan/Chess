// Bryan Liu (chl312), Dept. of Computing, Imperial College London
// ChessInfo.hpp - ChessInfo
// Provide general information for use across different Chess classes

#ifndef CHESSINFO_H
#define CHESSINFO_H

class ChessInfo {

  public:
    static const int ZERO = 0;
    static const unsigned int FILERANK_LENGTH = 2;
    static const int FILE_INDEX = 0;
    static const int RANK_INDEX = 1;

    static const char MIN_FILE = 'A';
    static const char MAX_FILE = 'H';

    static const char MIN_RANK = '1';
    static const char WHITE_INIT_PAWN_RANK = '2';
    static const char BLACK_INIT_PAWN_RANK = '7';
    static const char MAX_RANK = '8';

    static const int EXCLUSIVE_SHIFT = 1;
};

#endif
