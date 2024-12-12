#ifndef KING_H
#define KING_H
#include <iostream> //remove
#include "colour.h"
#include "chessPiece.h"


class King : public ChessPiece {

public:

   King(Colour pieceColour);
   
   ~King() override;

   bool isValidPieceMove(const int startRow, const int startCol, const int targetRow, const int targetCol,
                          const bool isCapture) const override;

    const char* getPieceName() const override;

};

#endif