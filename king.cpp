#include "king.h"
#include <iostream>


using namespace std;

King::King(PieceColour colour): ChessPiece(colour){}

bool King::isValidPieceMove(const int start_row, const int start_col, const int target_row, const int target_col,
                          const bool isCapture) const
  {
    return true;
  }