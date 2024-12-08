#ifndef QUEEN_H
#define QUEEN_H
#include "chessPiece.h"

using namespace std;


class Queen : public ChessPiece {

public:

    Queen(PieceColour colour);

   bool isValidPieceMove(const int startRow, const int startCol, const int targetRow, const int targetCol,
                          const bool isCapture) const override;
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