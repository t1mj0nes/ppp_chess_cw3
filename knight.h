#ifndef KNIGHT_H
#define KNIGHT_H
#include "chessPiece.h"
#include <iostream> //remove

class Knight : public ChessPiece {

public:

    Knight(PieceColour colour);

   bool isValidPieceMove(const int start_row, const int start_col, const int target_row, const int target_col,
                          const bool isCapture) const override;
    const char* getPieceName() const override {
      if(colour == PieceColour::WHITE){
        return "WN";
      } else if (colour == PieceColour::BLACK){
        return "bn";
        }
        return "Unknown";
      }

    ~Knight() override{
        std::cout << "Destructor Knight" << std::endl;
        }

};

#endif