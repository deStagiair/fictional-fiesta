/// Implementation of the Descriptable class.

#include "fictional-fiesta/utils/itf/Descriptable.h"

#include <sstream>

namespace fictionalfiesta
{

std::string Descriptable::indent(unsigned int indentLevel)
{
  return std::string(2 * indentLevel, ' ');
}

std::ostream& operator<<(std::ostream& os, const Descriptable& descriptable)
{
    os << descriptable.str(0);
    return os;
}

} // namespace fictionalfiesta
