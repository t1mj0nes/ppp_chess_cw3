
/**
 * @file chessPiece.h
 * 
 * @brief Declaration of the `ChessPiece` class, which serves as the base class
 *        for all chess pieces. This class defines common attributes and 
 *        methods shared across all pieces, such as the piece's colour and its 
 *        movement validation.
 */
#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include "colour.h"

/**
 * @class ChessPiece
 * 
 * @brief Represents a generic chess piece.
 * 
 * The `ChessPiece` class is the base class for all chess pieces, providing 
 * common functionality such as storing the piece's colour and ensuring that 
 * derived classes implement the necessary movement logic for each specific 
 * piece.
 */
class ChessPiece {

public:
  /**
   * @brief Constructs a chess piece with a specified colour.
   * 
   * @param pieceColour The colour of the piece (`Colour::WHITE` or
   `Colour::BLACK`).
   */
  ChessPiece(Colour pieceColour);

  /**
   * @brief Abstract method for validating a move for the piece.
   * 
   * Each piece has its own logic for move validation, and this method is 
   * overridden in the derived classes to implement specific move rules for 
   * each piece.
   * 
   * @param startRow The starting row of the move.
   * @param startCol The starting column of the move.
   * @param targetRow The target row of the move.
   * @param targetCol The target column of the move.
   * @param isCapture Indicates whether the move is a capture.
   * @return `true` if the move is valid; `false` otherwise.
   */
  virtual bool isValidPieceMove(const int startRow, const int startCol, 
                                const int targetRow, const int targetCol, 
                                const bool isCapture) const = 0;

  /**
   * @brief Abstract method for getting the name of the piece.
   * 
   * Each piece has its own name (e.g., "King", "Queen"), and this method is 
   * overridden in the derived classes to return the specific name of the 
   * piece.
   * 
   * @return A string literal representing the name of the piece.
   */
  virtual const char* getPieceName() const = 0;

  /**
   * @brief Gets the colour of the piece.
   * 
   * @return The colour of the piece (`Colour::WHITE` or `Colour::BLACK`).
   */
  const Colour getPieceColour() const;

  /**
   * @brief Destructor for the `ChessPiece` class.
   * 
   * The destructor is virtual to ensure proper cleanup of derived class 
   * objects.
   */
  virtual ~ChessPiece();

protected:
    // The colour of the chess piece (either white or black)
   Colour pieceColour;

};

#endif
