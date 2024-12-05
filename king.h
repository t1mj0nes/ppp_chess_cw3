#ifndef KING_H
#define KING_H
#include "chessPiece.h"

using namespace std;


class King : public ChessPiece {

public:

    King(PieceColour colour);

    bool isValidPieceMove(const char position, const char target) override;

    const char* getPieceName() const override {
      if(colour == PieceColour::WHITE){
        return "WK";
      } else if (colour == PieceColour::BLACK){
        return "bk";
        }
        return "Unknown";


      }

};

#endif