#include "colour.h"

std::ostream& operator<< ( std::ostream &out, const Colour& colour)
{
 if(colour == Colour::BLACK){
  out << "BLACK";
 } else {
  out << "WHITE";
 }
 return out;
}