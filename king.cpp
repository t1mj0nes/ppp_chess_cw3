#include "king.h"
#include <iostream>


using namespace std;

King::King(Colour pieceColour): ChessPiece(pieceColour){}

King::~King(){}

const char* King::getPieceName() const {
        return "King";
      }

bool King::isValidPieceMove(const int startRow, const int startCol, const int targetRow, const int targetCol,
                          const bool isCapture) const
  {
  int rowDiff = abs(targetRow - startRow);
  int colDiff = abs(targetCol - startCol);

    if (rowDiff <= 1 && colDiff <= 1) {
        return true;
    }

    if (rowDiff == 0 && colDiff == 2){
        cout << "attempting to castle, is valid piece move" << endl;
        return true;
    }
    
    //cout << "Invalid king move: The move is not within 1 square in any direction." << endl;
    return false;
} 