/**
 * @file pawn.h
 * 
 * @brief Declaration of the `Pawn` class, which represents the pawn chess 
 * piece.
 * 
 * This file defines the `Pawn` class, a subclass of `ChessPiece`, that 
 * provides specific functionality for the pawn piece, including move 
 * validation and piece identification.
 */
#ifndef PAWN_H
#define PAWN_H

#include "chessPiece.h"
#include "colour.h"


/**
 * @class Pawn
 * 
 * @brief Represents a pawn chess piece.
 * 
 * The `Pawn` class provides functionality for validating pawn-specific moves 
 * and identifying the piece.
 */
class Pawn : public ChessPiece {

public:
  /**
   * @brief Constructs a pawn with a specified colour.
   * 
   * @param pieceColour The colour of the pawn (`Colour::WHITE` or 
   * `Colour::BLACK`).
   */
  Pawn(Colour pieceColour);

  /**
   * @brief Validates whether a move is valid for a pawn.
   * 
   * A pawn can move one square forward, two squares forward from its starting 
   * position, or capture diagonally. 
   * 
   * @param startRow The starting row of the move.
   * @param startCol The starting column of the move.
   * @param targetRow The target row of the move.
   * @param targetCol The target column of the move.
   * @param isCapture Indicates whether the move is a capture, therefore allowing
   *                  the pawn to move diagonally.
   * @return `true` if the move is valid for a pawn; `false` otherwise.
   */
  bool isValidPieceMove(const int startRow, const int startCol, 
                        const int targetRow, const int targetCol,
                        const bool isCapture) const override;

  /**
   * @brief Retrieves the name of the piece.
   * 
   * @return A string literal ("Pawn") representing the name of the piece.
   */
  const char* getPieceName() const override;

  /**
   * @brief Destructor for the `Pawn` class.
   */
  ~Pawn() override;

};

#endif

