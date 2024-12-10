#ifndef CHESSPIECE_H
#define CHESSPIECE_H
#include <ostream>
#include <iostream> //remove
#include "colour.h"


class ChessPiece {

public:
  ChessPiece(Colour pieceColour);

  virtual bool isValidPieceMove(const int startRow, const int startCol, const int targetRow, const int targetCol, const bool isCapture) const = 0;

   //change this at the end so it is just "king"
  virtual const char* getPieceName() const = 0;

  const Colour getPieceColour() const;

  virtual ~ChessPiece(){
    std::cout << "chessPiece destructor called" << std::endl;
  }

protected:
   Colour pieceColour;

};

#endif
