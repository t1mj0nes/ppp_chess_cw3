#include <iostream>
#include "rook.h"
#include "colour.h"


using namespace std;

Rook::Rook(Colour pieceColour) : ChessPiece(pieceColour){}

Rook::~Rook(){}

bool Rook::isValidPieceMove(const int startRow, const int startCol, const int targetRow, const int targetCol,
                          const bool isCapture) const {
 // Check if the move is diagonal by checking if the absolute differences in rows and columns are equall
    if (targetRow == startRow|| targetCol == startCol) {
        return true;
    }
    // cout << "Invalid move: The move is not horizontal or vertical." << endl;
    return false;
}

 const char* Rook::getPieceName() const {
    return "Rook";
}


void Rook::incrementCounter(){
    moves++;
}

void Rook::decrementCounter(){
    if (moves > 0)
    moves--;
}

int Rook::getMoves() const{
    return moves;

}