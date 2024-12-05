#ifndef BISHOP_H
#define BISHOP_H
#include "chessPiece.h"

using namespace std;


class Bishop : public ChessPiece {

public:

    Bishop(PieceColour colour);

    bool isValidPieceMove(const char position, const char target) override;

    const char* getPieceName() const override {
      if(colour == PieceColour::WHITE){
        return "WB";
      } else if (colour == PieceColour::BLACK){
        return "bb";
        }
        return "Unknown";


      }

};

#endif