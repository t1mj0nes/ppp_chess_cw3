#include <iostream>
#include "colour.h"
#include "bishop.h"


using namespace std;

/**
 * Bishop constructor
 */
Bishop::Bishop(Colour pieceColour): ChessPiece(pieceColour){}

/**
 * Bishop destructor
 */
Bishop::~Bishop(){}

const char* Bishop::getPieceName() const {
        return "Bishop";
      }


bool Bishop::isValidPieceMove(const int startRow, const int startCol, 
                              const int targetRow, const int targetCol,
                              const bool isCapture) const {
 //  move is diagonal if the absolute differences in rows and columns is 0
    int rowDiff = targetRow - startRow;
    int colDiff = targetCol - startCol;

// not equal, return false. Invalid move
    if (abs(rowDiff) != abs(colDiff)) {
        return false;
    }
    return true;
}