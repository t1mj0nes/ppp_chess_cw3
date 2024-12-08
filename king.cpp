#include "king.h"
#include <iostream>


using namespace std;

King::King(PieceColour colour): ChessPiece(colour){}

bool King::isValidPieceMove(const int startRow, const int startCol, const int targetRow, const int targetCol,
                          const bool isCapture) const
  {
  int rowDiff = abs(targetRow - startRow);
  int colDiff = abs(targetCol - startCol);

    if (rowDiff <= 1 && colDiff <= 1) {
        return true;
    }
    // cout << "Invalid move: The move is not within 1 square in any direction." << endl;

    return false;
} 