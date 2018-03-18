/// @file Source.cpp Implementation of the Source class.

#include "fictional-fiesta/world/itf/Source.h"

#include "fictional-fiesta/utils/itf/Exception.h"
#include "fictional-fiesta/utils/itf/XmlNode.h"

namespace fictionalfiesta
{

namespace
{
constexpr char XML_RESOURCE_ID_NODE_NAME[]{"Resource"};
}

Source::Source(const std::string& resourceId, unsigned int initialUnitCount):
  _resourceId(resourceId),
  _currentUnitCount(initialUnitCount)
{
}

Source::Source(const XmlNode& node, unsigned int initialUnitCount):
  _resourceId(node.getChildNodeText(XML_RESOURCE_ID_NODE_NAME)),
  _currentUnitCount(initialUnitCount)
{
}

const std::string& Source::getResourceId() const
{
  return _resourceId;
}

const unsigned int Source::getCurrentUnitCount() const
{
  return _currentUnitCount;
}

unsigned int Source::consume(const unsigned int requiredUnits)
{
  unsigned int consumed_units = requiredUnits;
  if (_currentUnitCount != INFINITY_UNITS)
  {
    consumed_units = std::min(requiredUnits, _currentUnitCount);
    _currentUnitCount -= consumed_units;
  }

  return consumed_units;
}


void Source::setCurrentUnitCount(unsigned int currentUnitCount)
{
  _currentUnitCount = currentUnitCount;
}

} // namespace fictionalfiesta
