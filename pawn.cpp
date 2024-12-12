/**
 * @file pawn.cpp
 * 
 * @brief Implementation of the knight class, derived from the ChessPiece class. 
 *        It provides the specific functionality of a pawn, such as movement 
 *        validation for normal moves, moves of two spaces and captures..
 */
#include <cmath>
#include "pawn.h"
#include "colour.h"


using namespace std;

/**
 * Pawn constructor
 */
Pawn::Pawn(Colour pieceColour): ChessPiece(pieceColour){}

/**
 * Pawn destructor
 */
Pawn::~Pawn(){}

const char* Pawn::getPieceName() const {
        return "Pawn";
      }

bool Pawn::isValidPieceMove(const int startRow, const int startCol, 
                            const int targetRow, const int targetCol,
                            const bool isCapture) const
  {
  Colour pieceColour = getPieceColour();
  // white pawns move up the board, black pawns move down the board.
  int directionScalar = (pieceColour == Colour::WHITE) ? 1 : -1;


    if (!isCapture) {
      if (((targetRow - startRow) == (directionScalar)) && 
          (targetCol == startCol)) {
        return true;
      }
       // check if the pawn han't made a move. Therefore can move 2 places.
       else if ((((directionScalar == 1) && (startRow == 1)) || 
                ((directionScalar == -1) && (startRow == 6)))
           && ((targetRow - startRow) == (2 * directionScalar)) && 
              (targetCol == startCol)) {
             return true;
            }
     }
      // if capturing a piece, the pawn can move diagonally.
     if (isCapture) {
       if (((targetRow - startRow) == (directionScalar)) && 
       ((targetCol == startCol + 1) || (targetCol == startCol - 1))) {
            return true;
           }
     }

  return false;
}
