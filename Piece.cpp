#include <map>
#include <string>

#include "Piece.hpp"

Piece::Piece (string fileRank, bool _owningPlayer){
  file = fileRank[0];
  rank = fileRank[1];
  owningPlayer = _owningPlayer;
}

Piece::~Piece () {


}
