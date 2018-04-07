/// Implementation of the Descriptable class.

#include "fictional-fiesta/utils/itf/Descriptable.h"

#include <sstream>

namespace fictionalfiesta
{

std::string Descriptable::indent(unsigned int indentLevel)
{
  return std::string(2 * indentLevel, ' ');
}

} // namespace fictionalfiesta
