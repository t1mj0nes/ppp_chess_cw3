#ifndef COLOUR_H
#define COLOUR_H

#include <ostream>
  
/**
 * @enum colour.
 * @brief Represents the possible colors of a traffic light.
 *
 */
enum class Colour {BLACK, WHITE};

std::ostream& operator<< ( std::ostream &out, const Colour& colour);

#endif
