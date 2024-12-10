#ifndef ROOK_H
#define ROOK_H
#include <iostream> //remove
#include "chessPiece.h"
#include "colour.h"


class Rook : public ChessPiece {

public:

    Rook(Colour pieceCcolour);

   bool isValidPieceMove(const int startRow, const int startCol, const int targetRow, const int targetCol,
                          const bool isCapture) const override;
    const char* getPieceName() const override {
      if(pieceColour == Colour::WHITE){
        return "WR";
      } else if (pieceColour == Colour::BLACK){
        return "br";
        }
        return "Unknown";
      }

      ~Rook() override{
        std::cout << "Destructor Rook" << std::endl;
        }
};

#endif