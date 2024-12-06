#include "queen.h"
#include <iostream>


using namespace std;

Queen::Queen(PieceColour colour): ChessPiece(colour){}

bool Queen::isValidPieceMove(const int start_row, const int start_col, const int target_row, const int target_col,
                          const bool isCapture) const
  {
    return true;
  }