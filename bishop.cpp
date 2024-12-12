#include <iostream>
#include "colour.h"
#include "bishop.h"


using namespace std;

Bishop::Bishop(Colour pieceColour): ChessPiece(pieceColour){}

Bishop::~Bishop(){}

const char* Bishop::getPieceName() const {
        return "Bishop";
      }


bool Bishop::isValidPieceMove(const int startRow, const int startCol, const int targetRow, const int targetCol,
                          const bool isCapture) const {
 // Check if the move is diagonal by checking if the absolute differences in rows and columns are equal
    int rowDiff = targetRow - startRow;
    int colDiff = targetCol - startCol;

    if (abs(rowDiff) != abs(colDiff)) {
        //cout << "Invalid move: The move is not diagonal." << endl;
        return false;
    }
    return true;
}