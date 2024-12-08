#include <iostream>
#include <cmath>
#include "pawn.h"


using namespace std;

Pawn::Pawn(PieceColour colour): ChessPiece(colour){}

bool Pawn::isValidPieceMove(const int startRow, const int startCol, const int targetRow, const int targetCol,
                          const bool isCapture) const
  {
    // cout << "checking if valid piece move for pawn" << endl;
  PieceColour colour = getPieceColour();
  // white pawns move up the board, black pawns move down the board.
  int directionScalar = (colour == PieceColour::WHITE) ? 1 : -1;


    if (!isCapture) {
      if (((targetRow - startRow) == (directionScalar)) && (targetCol == startCol)) {
        // cout << "valid pawn move" << endl;
        return true;
      }
       // check if the pawn han't made a move
       else if ((((directionScalar == 1) && (startRow == 1)) || ((directionScalar == -1) && (startRow == 6)))
           && ((targetRow - startRow) == (2 * directionScalar)) && (targetCol == startCol)) {
             // cout << "valid pawn move" << endl;
             return true;
            }
     }
      // if capturing a piece, the pawn can move horizontal.
     if (isCapture) {
       if (((targetRow - startRow) == (directionScalar)) && ((targetCol == startCol + 1) ||
                                                               (targetCol == startCol - 1))) {
            // cout << "valid pawn move" << endl;
            return true;
           }
     }

  // cout << "invalid pawn move" << endl;
  return false;
}
