#ifndef KING_H
#define KING_H
#include "chessPiece.h"
#include <iostream> //remove

class King : public ChessPiece {

public:

    King(PieceColour colour);

   bool isValidPieceMove(const int start_row, const int start_col, const int target_row, const int target_col,
                          const bool isCapture) const override;

    // rename
    const char* getPieceName() const override {
      if(colour == PieceColour::WHITE){
        return "WK";
      } else if (colour == PieceColour::BLACK){
        return "bk";
        }
        return "Unknown";
      }

	//all destructos should be virtual?
    virtual ~King() override {
        std::cout << "Destructor King" << std::endl;
        }

};

#endif