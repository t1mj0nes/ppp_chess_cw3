/**
 * @file queen.h
 * 
 * @brief Declaration of the `Queen` class, which represents the queen chess 
 * piece.
 * 
 * This file defines the `Queen` class, a subclass of `ChessPiece`, that 
 * provides specific functionality for the queen piece, including move 
 * validation and piece identification.
 */

#ifndef QUEEN_H
#define QUEEN_H

#include "chessPiece.h"
#include "colour.h"

using namespace std;


class Queen : public ChessPiece {

public:
  /**
   * @brief Constructs a queen with a specified colour.
   * 
   * @param pieceColour The colour of the queen (`Colour::WHITE` or 
   * `Colour::BLACK`).
   */
  Queen(Colour pieceColour);

  /**
   * @brief Validates whether a move is valid for a queen.
   * 
   * A queen can move any number of squares along a row, column, or diagonal.
   * 
   * @param startRow The starting row of the move.
   * @param startCol The starting column of the move.
   * @param targetRow The target row of the move.
   * @param targetCol The target column of the move.
   * @param isCapture Indicates whether the move is a capture.
   * @return `true` if the move is valid for a queen; `false` otherwise.
   */
  bool isValidPieceMove(const int startRow, const int startCol, 
                        const int targetRow, const int targetCol,
                        const bool isCapture) const override;
  
  /**
   * @brief Retrieves the name of the piece.
   * 
   * @return A string literal ("Queen") representing the name of the piece.
   */
  const char* getPieceName() const override;

  /**
   * @brief Destructor for the `Queen` class.
   */
  ~Queen() override;

  private:
    // No specific members for Queen class, but can be extended in future.

};

#endif