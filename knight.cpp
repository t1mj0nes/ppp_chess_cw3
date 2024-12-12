#include "knight.h"
#include "colour.h"
#include <iostream>


using namespace std;

Knight::Knight(Colour pieceColour) : ChessPiece(pieceColour){}

Knight::~Knight(){}

const char* Knight::getPieceName() const  {
        return "Knight";
      }


bool Knight::isValidPieceMove(const int startRow, const int startCol, const int targetRow, const int targetCol,
                          const bool isCapture) const
  {
    int dx = abs(targetRow - startRow);
    int dy = abs(targetCol - startCol);

    // Valid if the move is 2 in one direction and 1 in the other
    if((dx == 2 && dy == 1) || (dx == 1 && dy == 2)) {
       // cout << "valid move for knight" << endl;
       return true;
    }
    // cout << "Invalid move: The move is not a L." << endl;
    return false;
}
