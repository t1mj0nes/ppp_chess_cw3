#ifndef PAWN_H
#define PAWN_H
#include "chessPiece.h"
#include <iostream> //remove




class Pawn : public ChessPiece {

public:

    Pawn(PieceColour colour);

  bool isValidPieceMove(const int start_row, const int start_col, const int target_row, const int target_col,
                         const bool isCapture) const override;

    const char* getPieceName() const override {
      if(colour == PieceColour::WHITE){
        return "WP";
      } else if (colour == PieceColour::BLACK){
        return "bp";
        }
        return "Unknown";

      }


  ~Pawn() override{
  std::cout << "Destructor Pawn" << std::endl;
  }

};

#endif

