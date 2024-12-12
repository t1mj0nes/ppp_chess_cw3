#ifndef PAWN_H
#define PAWN_H
#include "chessPiece.h"
#include "colour.h"
#include <iostream> //remove




class Pawn : public ChessPiece {

public:

    Pawn(Colour pieceColour);

  bool isValidPieceMove(const int startRow, const int startCol, const int targetRow, const int targetCol,
                         const bool isCapture) const override;

    const char* getPieceName() const override;

  ~Pawn() override;

};

#endif

