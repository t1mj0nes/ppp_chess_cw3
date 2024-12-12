/**
 * @file bishop.h
 * @brief Declaration of the `Bishop` class, which represents a bishop chess 
 * piece.
 * 
 * The `Bishop` class inherits from `ChessPiece` and implements the specific 
 * movement rules for a bishop in chess. The bishop can move diagonally any 
 * number of squares, and the class defines the logic for validating moves
 * and retrieving the piece's name.
 */
#ifndef BISHOP_H
#define BISHOP_H

#include "colour.h"
#include "chessPiece.h"

/**
 * @class Bishop
 * @brief Represents a bishop piece in chess.
 * 
 * The `Bishop` class is derived from `ChessPiece` and represents a bishop 
 * in the game of chess. It defines the specific movement rules for the bishop, 
 * which can move diagonally any number of squares.
 */
class Bishop : public ChessPiece {

public:
 /**
   * @brief Constructs a Bishop with a given colour.
   * 
   * @param pieceColour The colour of the bishop (either `Colour::WHITE` or `Colour::BLACK`).
   */
  Bishop(Colour pieceColour);
/**
   * @brief Validates whether a move for the bishop is legal.
   * 
   * Bishops move diagonally, and this method checks whether the target position
   *  is a valid diagonal move from the start position..
   * 
   * @param startRow The starting row of the bishop's move.
   * @param startCol The starting column of the bishop's move.
   * @param targetRow The target row for the move.
   * @param targetCol The target column for the move.
   * @param isCapture Indicates whether the move is a capture 
   * 
   * @return `true` if the move is valid for a bishop; `false` otherwise.
   */
  bool isValidPieceMove(const int startRow, const int startCol, 
                        const int targetRow, const int targetCol,
                         const bool isCapture) const override;

 /**
   * @brief Gets the name of the piece.
   * 
   * This method returns a string representing the name of the piece, which is "Bishop".
   * 
   * @return A string literal `"Bishop"`.
   */
  const char* getPieceName() const override;

/**
   * @brief Destructor for the `Bishop` class.
   * 
   * The destructor is overridden to ensure proper cleanup of the `Bishop` 
   * object, though in this case,
   * no specific cleanup is required as the class doesn't allocate dynamic 
   * memory.
   */
  ~Bishop() override;

private:
  // No private member variables in this class. 

};

#endif