
#include "ChessErrHandler.hpp"

ChessErrHandler::ChessErrHandler () {

}

void ChessErrHandler::printErr
  (int errNo, Piece* piece, string sourceFileRank, string destFileRank) {

  switch (errNo) {
    case ChessErrHandler::DEST_EQ_SOURCE : {
      cout << "Skipping your move? You cannot move from "
           << sourceFileRank << " to " << sourceFileRank << "!" << endl;
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
    case ChessErrHandler::MOVED_EMPTY_PIECE : {
      cout << "Playing Air Chess? There is nothing to move"
           << " at " << sourceFileRank << "!" << endl;
      break;
    }
    case ChessErrHandler::NOT_OWNER_TURN : {
      cout << "It is not " << piece->playerToString () 
           << " turn to move! Be patient!" << endl;
      break;
    }
    case ChessErrHandler::ILLEGAL_MOVE_PATTERN :
    case ChessErrHandler::OBSTRUCTION_EN_ROUTE :
    case ChessErrHandler::FRIENDLY_AT_DEST :
    case ChessErrHandler::PAWN_ILLEGAL_CAPTURE_PATTERN :
    case ChessErrHandler::ALLOW_KING_IN_CHECK : {
      cout << "Illegal move for " << piece->toString() 
           << " at " << sourceFileRank << ": ";
      switch (errNo) {
        case ChessErrHandler::ILLEGAL_MOVE_PATTERN : {
          cout << "Have you even read the rules?" << endl;
          break;
        }
        case ChessErrHandler::OBSTRUCTION_EN_ROUTE : {
          cout << "Way to " << destFileRank << " is blocked dude." << endl;
          break;
        }
        case ChessErrHandler::FRIENDLY_AT_DEST : {
          cout << "You cannot force your friendlies at "
               << destFileRank << " out of their way!" << endl;
          break;
        }
        case ChessErrHandler::PAWN_ILLEGAL_CAPTURE_PATTERN : {
          cout << "Head-on collision is not allowed!" << endl;
          break;
        }
        case ChessErrHandler::ALLOW_KING_IN_CHECK : {
          cout << "Now go back and keep your King (or yourself) safe!" << endl;
          break;
        }
      }
      break;
    }
    case ChessErrHandler::GAME_HAS_ENDED : {
      cout << "The game has ended!" << endl;
      break;
    }
    
    default : {
      cout << "An unexpected error has occured. Please try again." << endl;
    }
  }

}
