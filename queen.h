#ifndef QUEEN_H
#define QUEEN_H
#include "chessPiece.h"

using namespace std;


class Queen : public ChessPiece {

public:

    Queen(PieceColour colour);

   bool isValidPieceMove(const int start_row, const int start_col, const int target_row, const int target_col,
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