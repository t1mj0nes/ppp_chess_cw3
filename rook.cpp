/**
 * @file rook.cpp
 * 
 * @brief Implementation of the Rook class, derived from the ChessPiece class. 
 *        It provides the specific functionality of a rook, such as movement 
 *        validation and tracking the number of moves for castling rights.
 */

#include "rook.h"
#include "colour.h"


using namespace std;

/**
 * Rook constructor
 */
Rook::Rook(Colour pieceColour) : ChessPiece(pieceColour){}

/**
 * Rook destructor
 */
Rook::~Rook(){}

bool Rook::isValidPieceMove(const int startRow, 
                            const int startCol, const int targetRow, 
                            const int targetCol, const bool isCapture) const {
    // valid vertical or horizontal move if rows or columns don't change.
    if (targetRow == startRow|| targetCol == startCol) {
        return true;
    }
    return false;
}

 const char* Rook::getPieceName() const {
    return "Rook";
}


void Rook::incrementCounter(){
    moves++;
}

void Rook::decrementCounter(){
    // a rook can't have made negative moves.
    if (moves > 0)
    moves--;
}

int Rook::getMoves() const{
    return moves;

}