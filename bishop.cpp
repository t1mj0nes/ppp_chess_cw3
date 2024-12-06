#include "bishop.h"
#include <iostream>


using namespace std;

Bishop::Bishop(PieceColour colour): ChessPiece(colour){}

bool Bishop::isValidPieceMove(const int start_row, const int start_col, const int target_row, const int target_col,
                          const bool isCapture) const
  {
    return true;
  }