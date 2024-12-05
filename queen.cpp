#include "queen.h"
#include <iostream>


using namespace std;

Queen::Queen(PieceColour colour): ChessPiece(colour){}

bool Queen::isValidPieceMove(const char position, const char target)
  {
    return true;
  }