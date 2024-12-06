#include "rook.h"
#include <iostream>


using namespace std;

Rook::Rook(PieceColour colour): ChessPiece(colour){}

bool Rook::isValidPieceMove(const int start_row, const int start_col, const int target_row, const int target_col,
                          const bool isCapture) const
  {
    return true;
  }
