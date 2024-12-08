#include "queen.h"
#include <iostream>


using namespace std;

Queen::Queen(PieceColour colour): ChessPiece(colour){}

bool Queen::isValidPieceMove(const int startRow, const int startCol, const int targetRow, const int targetCol,
                          const bool isCapture) const {
    // Diagonal move 
    if (abs(startRow - targetRow) == abs(startCol - targetCol)) {
        return true;
    }
    
    // Straight line move 
    if (startRow == targetRow || startCol == targetCol) {
        return true;
    }
    
    return false;
}  