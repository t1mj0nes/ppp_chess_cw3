#ifndef QUEEN_H
#define QUEEN_H
#include "chessPiece.h"

using namespace std;


class Queen : public ChessPiece {

public:

    Queen(PieceColour colour);

    bool isValidPieceMove(const char position, const char target) override;

    const char* getPieceName() const override {
      if(colour == PieceColour::WHITE){
        return "WQ";
      } else if (colour == PieceColour::BLACK){
        return "bq";
        }
        return "Unknown";


      }

};

#endif