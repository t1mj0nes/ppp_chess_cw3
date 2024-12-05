#ifndef KNIGHT_H
#define KNIGHT_H
#include "chessPiece.h"

using namespace std;


class Knight : public ChessPiece {

public:

    Knight(PieceColour colour);

    bool isValidPieceMove(const char position, const char target) override;

    const char* getPieceName() const override {
      if(colour == PieceColour::WHITE){
        return "WN";
      } else if (colour == PieceColour::BLACK){
        return "bn";
        }
        return "Unknown";


      }

};

#endif