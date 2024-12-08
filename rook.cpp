#include "rook.h"
#include <iostream>


using namespace std;

Rook::Rook(PieceColour colour): ChessPiece(colour){}

bool Rook::isValidPieceMove(const int startRow, const int startCol, const int targetRow, const int targetCol,
                          const bool isCapture) const
{
 // Check if the move is diagonal by checking if the absolute differences in rows and columns are equall
    if (targetRow == startRow|| targetCol == startCol) {
        return true;
    }
    // cout << "Invalid move: The move is not horizontal or vertical." << endl;
    return false;
}