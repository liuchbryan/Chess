
#include "ChessErrHandler.hpp"

ChessErrHandler::ChessErrHandler () {

}

void ChessErrHandler::printErr
  (int errNo, Piece* piece, string sourceFileRank, string destFileRank) {

  switch (errNo) {
    case ChessErrHandler::DEST_EQ_SOURCE : {
      cout << "Skipping your move by moving a piece to its original position? "
           << "Cunning...";
      break;
    }
    case ChessErrHandler::SOURCE_OUTOF_BOUND : {
      cout << "You cannot move a piece which is not even on the board!";
      break;
    }
    case ChessErrHandler::DEST_OUTOF_BOUND : {
      cout << "You cannot move a piece away from the board!";
      break;
    }
    case ChessErrHandler::NOT_OWNER_TURN : {
      cout << "It is not " << piece->playerToString() << " turn to move!";
      break;
    }
    case ChessErrHandler::MOVED_EMPTY_PIECE : {
      cout << "There is nothing to move at " << sourceFileRank << "!";
      break;
    }
    case ChessErrHandler::ILLEGAL_MOVE_PATTERN : {
      cout << "Illegal move for " << piece->toString() << ": "
           << "You cannot move it like that!";
      break;
    }
    case ChessErrHandler::OBSTRUCTION_EN_ROUTE : {
      cout << "Illegal move for " << piece->toString() << ": "
           << "There is obstruction between " << sourceFileRank
           << " and " << destFileRank;
      break;
    }
    case ChessErrHandler::FRIENDLY_AT_DEST : {
      cout << "Illegal move for " << piece->toString() << ": "
           << "You cannot force your friendlies at " << destFileRank
           << " out of their way!";
      break;
    }
  }

}
