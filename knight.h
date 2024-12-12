
/**
 * @file knight.h
 * 
 * @brief Declaration of the `Knight` class, which represents the knight chess 
 * piece.
 * 
 * This file defines the `Knight` class, a subclass of `ChessPiece`, that 
 * provides specific functionality for the knight piece, including move 
 * validation and piece identification.
 */
#ifndef KNIGHT_H
#define KNIGHT_H

#include "chessPiece.h"
#include "colour.h"

/**
 * @class Knight
 * 
 * @brief Represents a knight chess piece.
 * 
 * The `Knight` class provides functionality for validating knight-specific
 *  moves and identifying the piece.
 */
class Knight : public ChessPiece {

public:

    /**
     * @brief Constructs a knight with a specified colour.
     * 
     * @param pieceColour The colour of the knight (`Colour::WHITE` or 
     * `Colour::BLACK`).
     */
    Knight(Colour pieceColour);

    /**
     * @brief Validates whether a move is valid for a knight.
     * 
     * A knight moves in an L-shape: two squares in one direction and one 
     * square in a perpendicular direction. Knights can jump over other pieces 
     * and do not follow the regular movement rules of other pieces. The 
     * ability of the knight to jump is dealt within the chessGame class.
     * 
     * @param startRow The starting row of the move.
     * @param startCol The starting column of the move.
     * @param targetRow The target row of the move.
     * @param targetCol The target column of the move.
     * @param isCapture Indicates whether the move is a capture.
     * @return `true` if the move is valid for a knight; `false` otherwise.
     */
    bool isValidPieceMove(const int startRow, const int startCol, 
                        const int targetRow, const int targetCol,
                        const bool isCapture) const override;

    /**
     * @brief Retrieves the name of the piece.
     * 
     * @return A string literal ("Knight") representing the name of the piece.
     */
    const char* getPieceName() const override;

    /**
     * @brief Destructor for the `Knight` class.
     */
    ~Knight() override;

private:
    // No specific members for the Knight class; 
};

#endif