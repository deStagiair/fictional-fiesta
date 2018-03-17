/// @file Source.cpp Implementation of the Source class.

#include "fictional-fiesta/world/itf/Source.h"

#include "fictional-fiesta/utils/itf/Exception.h"

namespace fictionalfiesta
{

Source::Source(const std::string& resourceId, unsigned int initialUnitCount):
  _resourceId(resourceId),
  _unitCount(initialUnitCount)
{
}

const std::string& Source::getResourceId() const
{
  return _resourceId;
}

const unsigned int Source::getUnitCount() const
{
  return _unitCount;
}

void Source::setUnitCount(unsigned int unitCount)
{
  _unitCount = unitCount;
}

} // namespace fictionalfiesta
