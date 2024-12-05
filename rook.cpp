#include "rook.h"
#include <iostream>


using namespace std;

Rook::Rook(PieceColour colour): ChessPiece(colour){}

bool Rook::isValidPieceMove(const char position, const char target)
  {
    return true;
  }
