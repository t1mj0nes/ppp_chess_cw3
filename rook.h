#ifndef ROOK_H
#define ROOK_H
#include "chessPiece.h"

using namespace std;


class Rook : public ChessPiece {

public:

    Rook(PieceColour colour);

    bool isValidPieceMove(const char position, const char target) override;

    const char* getPieceName() const override {
      if(colour == PieceColour::WHITE){
        return "WR";
      } else if (colour == PieceColour::BLACK){
        return "br";
        }
        return "Unknown";


      }

};

#endif