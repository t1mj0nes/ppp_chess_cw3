#include "colour.h"

std::ostream& operator<< ( std::ostream &out, const Colour& colour)
{
 if(colour == Colour::BLACK){
  out << "Black";
 } else {
  out << "White";
 }
 return out;
}

Colour getOppositeColour(Colour currentColour){
    return(currentColour == Colour::WHITE) ? Colour::BLACK : Colour::WHITE;
}
