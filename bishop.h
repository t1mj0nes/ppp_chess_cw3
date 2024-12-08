#ifndef BISHOPcolCounterH
#define BISHOPcolCounterH
#include "chessPiece.h"
#include <iostream> //remove

class Bishop : public ChessPiece {

public:

    Bishop(PieceColour colour);

  bool isValidPieceMove(const int startRow, const int startCol, const int targetRow, const int targetCol,
                         const bool isCapture) const override;

    const char* getPieceName() const override {
      if(colour == PieceColour::WHITE){
        return "WB";
      } else if (colour == PieceColour::BLACK){
        return "bb";
        }
        return "Unknown";
      }

  //all destructos should be virtual?
  virtual ~Bishop() override{
    std::cout << "Destructor Bishop" << std::endl;
    }

};

#endif