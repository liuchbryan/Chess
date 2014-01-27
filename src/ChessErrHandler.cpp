// Bryan Liu (chl312), Dept. of Computing, Imperial College London
// ChessErrHandler.cpp - Implementation of ChessErrHandler

#include "header/ChessErrHandler.hpp"

ChessErrHandler::ChessErrHandler () {

}

/* ChessErrHandler.printErr():
   Print the error message w.r.t. given error number
*/
void ChessErrHandler::printErr
  (int errNo, Piece* piece, string sourceFileRank, string destFileRank) {

  switch (errNo) {
    case DEST_EQ_SOURCE : {
      cout << "Skipping your move? You cannot move from "
           << sourceFileRank << " to " << sourceFileRank << "!" << endl;
      break;
    }
    case SOURCE_OUTOF_BOUND : {
      cout << "You cannot move pieces which are not on the board!" << endl;
      break;
    }
    case DEST_OUTOF_BOUND : {
      cout << "You cannot move the piece away from the board!" << endl;
      break;
    }
    case INVALID_FILE_RANK : {
      cout << "Stop submitting rubbish! You can't progress in such way!"
           << endl;
      break;
    }
    case MOVED_EMPTY_PIECE : {
      cout << "Playing Air Chess? There is nothing to move"
           << " at " << sourceFileRank << "!" << endl;
      break;
    }
    case NOT_OWNER_TURN : {
      cout << "It is not " << piece->playerToString () 
           << " turn to move! Be patient!" << endl;
      break;
    }
    /* The following five cases have common heading, thus the implementation
         of nested case statement to prevent duplicate code
     */
    case ILLEGAL_MOVE_PATTERN :
    case OBSTRUCTION_EN_ROUTE :
    case FRIENDLY_AT_DEST :
    case PAWN_ILLEGAL_CAPTURE_PATTERN :
    case ALLOW_KING_IN_CHECK : {
      cout << "Illegal move for " << piece->toString() 
           << " at " << sourceFileRank << ": ";
      switch (errNo) {
        case ILLEGAL_MOVE_PATTERN : {
          cout << "Have you even read the rules?" << endl;
          break;
        }
        case OBSTRUCTION_EN_ROUTE : {
          cout << "Way to " << destFileRank << " is blocked dude." << endl;
          break;
        }
        case FRIENDLY_AT_DEST : {
          cout << "You cannot force your friendlies at "
               << destFileRank << " out of their way!" << endl;
          break;
        }
        case PAWN_ILLEGAL_CAPTURE_PATTERN : {
          cout << "Head-on collision is not allowed!" << endl;
          break;
        }
        case ALLOW_KING_IN_CHECK : {
          cout << "Now go back and keep your King (or yourself) safe!" << endl;
          break;
        }
      }
      break;
    }
    case GAME_HAS_ENDED : {
      cout << "The game has ended! What are you still doing here?" << endl;
      break;
    }
    default : {
      cout << "An unexpected error has occured. Please try again." << endl;
    }
  }
}
