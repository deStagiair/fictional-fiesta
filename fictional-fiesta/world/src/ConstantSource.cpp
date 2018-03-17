/// @file ConstantSource.cpp Implementation of the ConstantSource class.

#include "fictional-fiesta/world/itf/ConstantSource.h"

#include "fictional-fiesta/utils/itf/Exception.h"

#include <limits>

namespace fictionalfiesta
{

ConstantSource::ConstantSource(const std::string& resourceId):
  Source(resourceId, INFINITY_UNITS)
{
}

unsigned int ConstantSource::consume(const unsigned int requiredUnits)
{
  return requiredUnits;
}

} // namespace fictionalfiesta
