#ifndef QUEEN_H
#define QUEEN_H
#include "chessPiece.h"
#include "colour.h"

using namespace std;


class Queen : public ChessPiece {

public:

  Queen(Colour pieceColour);

  bool isValidPieceMove(const int startRow, const int startCol, const int targetRow, const int targetCol,
                          const bool isCapture) const override;
  
  const char* getPieceName() const override;

  ~Queen() override;

};

#endif