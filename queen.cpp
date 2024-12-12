#include "queen.h"
#include "colour.h"
#include <iostream>


using namespace std;

/**
 * Queen constructor
 */
Queen::Queen(Colour pieceColour): ChessPiece(pieceColour){}

/**
 * Queen destructor
 */
Queen::~Queen(){}

bool Queen::isValidPieceMove(const int startRow, const int startCol, 
                             const int targetRow, const int targetCol,
                             const bool isCapture) const {
 //  move is diagonal if the absolute differences in rows and columns is 0
    if (abs(startRow - targetRow) == abs(startCol - targetCol)) {
        return true;
    }
    
    // valid vertical or horizontal move if rows or columns don't change.
    if (startRow == targetRow || startCol == targetCol) {
        return true;
    }
    
    return false;
}  

const char* Queen::getPieceName() const {
    return "Queen";
    }