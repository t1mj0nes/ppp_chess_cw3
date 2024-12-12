#ifndef ROOK_H
#define ROOK_H
#include <iostream> //remove
#include "chessPiece.h"
#include "colour.h"


class Rook : public ChessPiece {

public:

  Rook(Colour pieceCcolour);

  bool isValidPieceMove(const int startRow, const int startCol, const int targetRow, const int targetCol,
                          const bool isCapture) const override;

  const char* getPieceName() const override;

  void incrementCounter();

  void decrementCounter();

  int getMoves() const;

  ~Rook() override;

  private: 
  //tracks the number of moves the rook has made. Necessary for castling. 
  int moves = 0;
};

#endif