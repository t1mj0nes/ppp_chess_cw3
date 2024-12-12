/**
 * @file rook.h
 * 
 * @brief Declaration of the `Rook` class, which represents the rook chess 
 * piece.
 * 
 * This file defines the `Rook` class, a subclass of `ChessPiece`, that 
 * provides specific functionality for rooks, including move validation and 
 * castling support.
 */
#ifndef ROOK_H
#define ROOK_H

#include "chessPiece.h"
#include "colour.h"

/**
 * @class Rook
 * 
 * @brief Represents a rook chess piece.
 * 
 * The `Rook` class provides functionality for validating rook-specific moves,
 * tracking the number of moves (required for castling), and identifying the 
 * piece.
 */
class Rook : public ChessPiece {

public:
  /**
   * @brief Constructs a rook with a specified colour.
   * 
   * @param pieceColour The colour of the rook (`Colour::WHITE` or 
   *                    `Colour::BLACK`).
   */
  Rook(Colour pieceCcolour);

  /**
   * @brief Validates whether a move is valid for a rook.
   * 
   * A rook can move any number of squares along a row or column but not 
   * diagonally.
   * 
   * @param startRow The starting row of the move.
   * @param startCol The starting column of the move.
   * @param targetRow The target row of the move.
   * @param targetCol The target column of the move.
   * @param isCapture Indicates whether the move is a capture.
   * @return `true` if the move is valid for a rook; `false` otherwise.
   */
  bool isValidPieceMove(const int startRow, const int startCol, 
                        const int targetRow, const int targetCol, 
                        const bool isCapture) const override;


  /**
   * @brief Retrieves the name of the piece.
   * 
   * @return A string literal ("Rook") representing the name of the piece.
   */
  const char* getPieceName() const override;

  /**
   * @brief Increments the rook's move counter.
   * 
   * This is used to track how many times the rook has moved, which is relevant
   * for determining castling rights.
   */
  void incrementCounter();

  /**
   * @brief Decrements the rook's move counter.
   * 
   * Ensures the counter does not become negative. This is used for undoing
   * moves.
   */
  void decrementCounter();

  /**
   * @brief Retrieves the number of moves the rook has made.
   * 
   * @return An integer representing the number of moves the rook has made.
   */
  int getMoves() const;

  /**
   * @brief Destructor for the `Rook` class.
   */
  ~Rook() override;

private: 
  /**
   * @brief Tracks the number of moves the rook has made.
   * 
   * This is necessary for determining castling eligibility.
   */
  int moves = 0;
};

#endif
