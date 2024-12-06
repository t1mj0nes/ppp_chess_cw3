#ifndef CHESSPIECE_H
#define CHESSPIECE_H
#include <ostream>
#include <iostream> //remove


/**
 * @enum colour.
 * @brief Represents the possible colors of a traffic light.
 *
 */
enum class PieceColour {BLACK, WHITE};

std::ostream& operator<< ( std::ostream &out, const PieceColour& colour);


class ChessPiece {

public:
  ChessPiece(PieceColour colour);

  virtual bool isValidPieceMove(const int start_row, const int start_col, const int target_row, const int target_col, const bool isCapture) const = 0;



   //change this at the end so it is just "king"
  virtual const char* getPieceName() const = 0;

  const PieceColour getPieceColour() const;

  virtual ~ChessPiece(){
    std::cout << "chessPiece destructor called" << std::endl;
  }



protected:
   PieceColour colour;

};

#endif
