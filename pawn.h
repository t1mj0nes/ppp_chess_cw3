#ifndef PAWN_H
#define PAWN_H
#include "chessPiece.h"

using namespace std;


class Pawn : public ChessPiece {

public:

    Pawn(PieceColour colour);

    bool isValidPieceMove(const char position, const char target) override;

    const char* getPieceName() const override {
      if(colour == PieceColour::WHITE){
        return "WP";
      } else {
        return "BP";
        }
      }

};

#endif

