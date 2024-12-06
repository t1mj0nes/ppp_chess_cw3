#ifndef BISHOP_H
#define BISHOP_H
#include "chessPiece.h"
#include <iostream> //remove

class Bishop : public ChessPiece {

public:

    Bishop(PieceColour colour);

  bool isValidPieceMove(const int start_row, const int start_col, const int target_row, const int target_col,
                         const bool isCapture) const override;

    const char* getPieceName() const override {
      if(colour == PieceColour::WHITE){
        return "WB";
      } else if (colour == PieceColour::BLACK){
        return "bb";
        }
        return "Unknown";
      }

  //all destructos should be virtual?
  virtual ~Bishop() override{
    std::cout << "Destructor Bishop" << std::endl;
    }

};

#endif