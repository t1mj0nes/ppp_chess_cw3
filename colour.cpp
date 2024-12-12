/**
 * @file colour.cpp
 * 
 * @brief Implementation of utility functions and operators related to the 
 *         Colour enum. This file includes an overload for outputting the 
 *         Colour enum to an output stream and a utility function to get the 
 *         opposite colour.
 */
#include "colour.h"

/**
 * Overload operator. Converts the enum into text
 */
std::ostream& operator<< ( std::ostream &out, const Colour& colour) {
  if(colour == Colour::BLACK){
    out << "Black";
  }
  else {
    out << "White";
  }
  return out;
}

/**
 * Provides the opposite colour
 */
Colour getOppositeColour(Colour currentColour){
  //If white, return black and vice versa.
  return(currentColour == Colour::WHITE) ? Colour::BLACK : Colour::WHITE;
}
