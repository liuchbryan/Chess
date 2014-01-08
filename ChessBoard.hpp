// Skeleton header file, you will need to edit this for your submission.

// Your final submission must expose the constructor, deconstructor, 
// submitMove and resetBoard methods.
// You may add any additonal files/methods as you see fit
// (be sure to also include them in the makefile).

#define CHESSBOARD_H

class ChessBoard
{
  public:

    ChessBoard();
    ~ChessBoard();

    void resetBoard();

    void submitMove(const char* fromSquare, const char* toSquare);

};
