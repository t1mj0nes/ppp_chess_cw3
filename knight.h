#ifndef KNIGHT_H
#define KNIGHT_H
#include "chessPiece.h"
#include "colour.h"
#include <iostream> //remove

class Knight : public ChessPiece {

public:

    Knight(Colour pieceColour);

   bool isValidPieceMove(const int startRow, const int startCol, const int targetRow, const int targetCol,
                          const bool isCapture) const override;
    const char* getPieceName() const override {
      if(pieceColour == Colour::WHITE){
        return "WN";
      } else if (pieceColour == Colour::BLACK){
        return "bn";
        }
        return "Unknown";
      }

    ~Knight() override{
        std::cout << "Destructor Knight" << std::endl;
        }

};

#endif