/**
 * @file knight.cpp
 * 
 * @brief Implementation of the knight class, derived from the ChessPiece class. 
 *        It provides the specific functionality of a knight, such as movement 
 *        validation.
 */
#include "knight.h"
#include "colour.h"


using namespace std;


/**
 * Knight constructor
 */
Knight::Knight(Colour pieceColour) : ChessPiece(pieceColour){}

/**
 * Knight destructor
 */
Knight::~Knight(){}

const char* Knight::getPieceName() const  {
        return "Knight";
      }


bool Knight::isValidPieceMove(const int startRow, const int startCol, 
                              const int targetRow, const int targetCol,
                               const bool isCapture) const
  {
    int dx = abs(targetRow - startRow);
    int dy = abs(targetCol - startCol);

    // Valid if the move is 2 in one direction and 1 in the other
    if((dx == 2 && dy == 1) || (dx == 1 && dy == 2)) {
       return true;
    }
    return false;
}
