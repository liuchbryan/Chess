// Bryan Liu (chl312), Dept. of Computing, Imperial College London

#ifndef PIECES_H
#define PIECES_H

using namespace std;

class Piece {

  private:
    const int ZERO = 0;
    const char MIN_FILE = 'A';
    const char MAX_FILE = 'H';
    const char MIN_RANK = '1';
    const char MAX_RANK = '8';

    char file;
    char rank;
    bool owningPlayer;

  public:
    Piece (string fileRank, bool owningPlayer);
    ~Piece ();
    
    virtual bool isValidMove 
      (string destFileRank, map<string, Piece*>* board) = 0;
    
  private:
    
};


#endif
