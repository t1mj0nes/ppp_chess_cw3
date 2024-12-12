#include "colour.h"

/**
 * Overload operator. Converts the enum into text
 */
std::ostream& operator<< ( std::ostream &out, const Colour& colour)
{
 if(colour == Colour::BLACK){
  out << "Black";
 } else {
  out << "White";
 }
 return out;
}

/**
 * Provides the opposite colour
 */
Colour getOppositeColour(Colour currentColour){
    //If white, return Black and vice versa.
    return(currentColour == Colour::WHITE) ? Colour::BLACK : Colour::WHITE;
}
