
#include "ChessErrHandler.hpp"

ChessErrHandler::ChessErrHandler () {

}

void ChessErrHandler::printErr
  (int errNo, Piece* piece, string sourceFileRank, string destFileRank) {

  switch (errNo) {
    case ChessErrHandler::DEST_EQ_SOURCE : {
      cout << "Skipping your move by moving a piece to its original position? "
           << "Cunning..." << endl;
      break;
    }
    case ChessErrHandler::SOURCE_OUTOF_BOUND : {
      cout << "You cannot move pieces which are not on the board!" << endl;
      break;
    }
    case ChessErrHandler::DEST_OUTOF_BOUND : {
      cout << "You cannot move the piece away from the board!" << endl;
      break;
    }
    case ChessErrHandler::NOT_OWNER_TURN : {
      cout << "It is not " << piece->playerToString () 
           << " turn to move! Be patient!" << endl;
      break;
    }
    case ChessErrHandler::MOVED_EMPTY_PIECE : {
      cout << "Playing Air Chess? There is nothing to move"
           << " at " << sourceFileRank << "!" << endl;
      break;
    }
    case ChessErrHandler::ILLEGAL_MOVE_PATTERN : {
      cout << "Illegal move for " << piece->toString() 
           << " at " << sourceFileRank << ": "
           << "Have you even read the rules?" << endl;
      break;
    }
    case ChessErrHandler::OBSTRUCTION_EN_ROUTE : {
      cout << "Illegal move for " << piece->toString()
           << " at " << sourceFileRank << ": Way"
           << " to " << destFileRank << " is blocked dude" << endl;
      break;
    }
    case ChessErrHandler::FRIENDLY_AT_DEST : {
      cout << "Illegal move for " << piece->toString()
           << " at " << sourceFileRank << ": You cannot force your friendlies"
           << " at " << destFileRank << " out of their way!" << endl;
      break;
    }
    case ChessErrHandler::PAWN_ILLEGAL_CAPTURE_PATTERN : {
      cout << "Illegal move for " << piece->toString()
           << " at " << sourceFileRank << ": You cannot capture piece"
           << "directly ahead!" << endl;
    }
  }

}
