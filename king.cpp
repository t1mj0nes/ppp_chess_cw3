#include "king.h"
#include <iostream>


using namespace std;

King::King(PieceColour colour): ChessPiece(colour){}

bool King::isValidPieceMove(const char position, const char target)
  {
    return true;
  }