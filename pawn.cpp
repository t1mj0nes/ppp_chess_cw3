#include <iostream>
#include <cmath>
#include "pawn.h"


using namespace std;

Pawn::Pawn(PieceColour colour): ChessPiece(colour){}

bool Pawn::isValidPieceMove(const int start_row, const int start_col, const int target_row, const int target_col,
                          const bool isCapture) const
  {
  PieceColour colour = getPieceColour();
  // white pawns move up the board, black pawns move down the board.
  int directionScalar = (colour == PieceColour::WHITE) ? 1 : -1;


    if (!isCapture)
      {
      if (((target_row - start_row) == (directionScalar)) && (target_col == start_col))
        	return true;
      // check if the pawn han't made a move
      if ((((directionScalar == 1) && (start_row == 1)) || ((directionScalar == -1) && (start_row == 6)))
           && ((target_row - start_row) == (2 * directionScalar)) && (target_col == start_col))
          	return true;
     }

     if (isCapture)
     {
       if (((target_row - start_row) == (directionScalar)) && ((target_col == start_col + 1) ||
                                                               (target_col == start_col - 1)))
           return true;
     }

  return false;


}
