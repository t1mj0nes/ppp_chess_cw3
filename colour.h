/**
 * @file colour.h
 * 
 * @brief Declaration of the Colour enum and related utilities for chess piece 
 *        management.
 * 
 * This file defines the `Colour` enum, which represents the two possible 
 * colours of chess pieces, and provides utility functions and operators for 
 * working with it.
 */

#ifndef COLOUR_H
#define COLOUR_H

#include <ostream>
  
/**
 * @enum Colour
 * 
 * @brief Represents the possible colours of chess pieces.
 * 
 * This enum is used to differentiate between the two sides in a chess game:
 * - `Colour::BLACK` for black pieces
 * - `Colour::WHITE` for white pieces
 */
enum class Colour {BLACK, WHITE};


/**
 * @brief Overloads the `<<` operator for the `Colour` enum.
 * 
 * This operator converts a `Colour` enum value into its textual representation 
 * ("Black" or "White") for easy output to an output stream.
 * 
 * @param out The output stream where the textual representation will be
 *            written.
 * @param colour The `Colour` enum value to be converted to text.
 * @return A reference to the modified output stream.
 */
std::ostream& operator<< ( std::ostream &out, const Colour& colour);

/**
 * @brief Returns the opposite colour of the given `Colour`.
 * 
 * This utility function is used to determine the opposing colour in chess
 * logic. 
 * If the input is `Colour::WHITE`, the function returns `Colour::BLACK`, and
 * vice versa.
 * 
 * @param currentColour The current colour (`Colour::WHITE` or `Colour::BLACK`).
 * @return The opposite colour (`Colour::BLACK` or `Colour::WHITE`).
 */
Colour getOppositeColour(Colour currentColour);

#endif
