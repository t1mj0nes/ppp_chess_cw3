/**
 * @file king.h
 * 
 * @brief Declaration of the `King` class, which represents the king chess 
 * piece.
 * 
 * This file defines the `King` class, a subclass of `ChessPiece`, that 
 * provides specific functionality for the king piece, including move 
 * validation and piece identification.
 */
#ifndef KING_H
#define KING_H

#include "colour.h"
#include "chessPiece.h"

/**
 * @class King
 * 
 * @brief Represents a king chess piece.
 * 
 * The `King` class provides functionality for validating king-specific moves 
 * and identifying the piece.
 */
class King : public ChessPiece {

public:

    /**
     * @brief Constructs a king with a specified colour.
     * 
     * @param pieceColour The colour of the king (`Colour::WHITE` or
     * `Colour::BLACK`).
     */
   King(Colour pieceColour);

    /**
     * @brief Destructor for the `King` class.
     */
   ~King() override;

    /**
     * @brief Validates whether a move is valid for a king.
     * 
     * A king can move one square in any direction: horizontally, vertically, 
     * or diagonally. A king can move two squres horizontally when castling.
     * 
     * @param startRow The starting row of the move.
     * @param startCol The starting column of the move.
     * @param targetRow The target row of the move.
     * @param targetCol The target column of the move.
     * @param isCapture Indicates whether the move is a capture.
     * @return `true` if the move is valid for a king; `false` otherwise.
     */
   bool isValidPieceMove(const int startRow, const int startCol, 
                        const int targetRow, const int targetCol,
                        const bool isCapture) const override;

    /**
     * @brief Retrieves the name of the piece.
     * 
     * @return A string literal ("King") representing the name of the piece.
     */
    const char* getPieceName() const override;

private:
    // No specific members for the King class;

};

#endif
