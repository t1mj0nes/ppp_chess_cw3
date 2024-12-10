#ifndef KING_H
#define KING_H
#include <iostream> //remove
#include "colour.h"
#include "chessPiece.h"


class King : public ChessPiece {

public:

    King(Colour pieceColour);

   bool isValidPieceMove(const int startRow, const int startCol, const int targetRow, const int targetCol,
                          const bool isCapture) const override;

    // rename
    const char* getPieceName() const override {
      if(pieceColour == Colour::WHITE){
        return "WK";
      } else if (pieceColour == Colour::BLACK){
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