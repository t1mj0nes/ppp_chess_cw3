#include "pawn.h"
#include <iostream>


using namespace std;

Pawn::Pawn(PieceColour colour): ChessPiece(colour){}

bool Pawn::isValidPieceMove(const char position, const char target)
  {
    return true;
  }
