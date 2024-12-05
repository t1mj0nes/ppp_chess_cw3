#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#


/**
 * @enum colour.
 * @brief Represents the possible colors of a traffic light.
 *
 */
enum class PieceColour {BLACK, WHITE};


class ChessPiece {

public:
  ChessPiece(PieceColour colour);

  virtual bool isValidPieceMove(const char position, const char target) = 0;
  
  virtual const char* getPieceName() const = 0;

protected:
   PieceColour colour;

};

#endif
