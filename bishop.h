#ifndef BISHOPcolCounterH
#define BISHOPcolCounterH
#include <iostream> //remove
#include "colour.h"
#include "chessPiece.h"

class Bishop : public ChessPiece {

public:

    Bishop(Colour pieceColour);

  bool isValidPieceMove(const int startRow, const int startCol, const int targetRow, const int targetCol,
                         const bool isCapture) const override;

    const char* getPieceName() const override {
      if(pieceColour == Colour::WHITE){
        return "WB";
      } else if (pieceColour == Colour::BLACK){
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