#include "bishop.h"
#include <iostream>


using namespace std;

Bishop::Bishop(PieceColour colour): ChessPiece(colour){}

bool Bishop::isValidPieceMove(const char position, const char target)
  {
    return true;
  }