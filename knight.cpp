#include "knight.h"
#include <iostream>


using namespace std;

Knight::Knight(PieceColour colour): ChessPiece(colour){}

bool Knight::isValidPieceMove(const int start_row, const int start_col, const int target_row, const int target_col,
                          const bool isCapture) const
  {
    return true;
  }
