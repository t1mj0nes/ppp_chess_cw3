#ifndef ROOK_H
#define ROOK_H
#include "chessPiece.h"
#include <iostream> //remove


class Rook : public ChessPiece {

public:

    Rook(PieceColour colour);

   bool isValidPieceMove(const int startRow, const int startCol, const int targetRow, const int targetCol,
                          const bool isCapture) const override;
    const char* getPieceName() const override {
      if(colour == PieceColour::WHITE){
        return "WR";
      } else if (colour == PieceColour::BLACK){
        return "br";
        }
        return "Unknown";
      }

      ~Rook() override{
        std::cout << "Destructor Rook" << std::endl;
        }
};

#endif