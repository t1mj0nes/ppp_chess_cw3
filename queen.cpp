#include "queen.h"
#include "colour.h"
#include <iostream>


using namespace std;

Queen::Queen(Colour pieceColour): ChessPiece(pieceColour){}

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