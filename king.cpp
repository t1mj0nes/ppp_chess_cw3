/**
 * @file king.cpp
 * 
 * @brief Implementation of the king class, derived from the ChessPiece class. 
 *        It provides the specific functionality of a king, such as movement 
 *        validations.
 */
#include "king.h"


using namespace std;

/**
 * King constructor
 */
King::King(Colour pieceColour): ChessPiece(pieceColour){}

/**
 * King destructor
 */
King::~King(){}

const char* King::getPieceName() const {
        return "King";
      }

bool King::isValidPieceMove(const int startRow, const int startCol, 
                            const int targetRow, const int targetCol,
                            const bool isCapture) const
  {
  int rowDiff = abs(targetRow - startRow);
  int colDiff = abs(targetCol - startCol);

    //valid move if it only moves by 1 in any direction (including diagonals)
    if (rowDiff <= 1 && colDiff <= 1) {
        return true;
    }

    //King can move 2 along a row if it is castling.
    if (rowDiff == 0 && colDiff == 2){
        return true;
    }
    
    return false;
} 