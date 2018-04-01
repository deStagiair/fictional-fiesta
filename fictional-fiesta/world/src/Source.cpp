/// @file Source.cpp Implementation of the Source class.

#include "fictional-fiesta/world/itf/Source.h"

#include "fictional-fiesta/utils/itf/Exception.h"
#include "fictional-fiesta/utils/itf/XmlNode.h"

namespace fictionalfiesta
{

namespace
{
constexpr char XML_RESOURCE_ID_NODE_NAME[]{"Resource"};
constexpr char XML_CURRENT_RESOURCE_UNITS_NAME[]{"CurrentUnits"};
}

Source::Source(const std::string& resourceId, unsigned int initialUnitCount):
  _resourceId(resourceId),
  _currentUnitCount(initialUnitCount)
{
}

Source::Source(const XmlNode& node, unsigned int initialUnitCount):
  _resourceId(node.getChildNodeText(XML_RESOURCE_ID_NODE_NAME)),
  _currentUnitCount(node.getOptionalChildNodeTextAs<unsigned int>(
      XML_CURRENT_RESOURCE_UNITS_NAME, initialUnitCount))
{
}

const std::string& Source::getResourceId() const
{
  return _resourceId;
}

const unsigned int Source::getCurrentUnitCount() const noexcept
{
  return _currentUnitCount;
}

bool Source::empty() const noexcept
{
  return _currentUnitCount == 0;
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

void Source::save(XmlNode node) const
{
  auto resource_node = node.appendChildNode(XML_RESOURCE_ID_NODE_NAME);
  resource_node.setText(_resourceId);

  auto current_units_node = node.appendChildNode(XML_CURRENT_RESOURCE_UNITS_NAME);
  current_units_node.setText(unitsToString(_currentUnitCount));

  // Call to the private virtual method.
  doSave(node);
}

std::string Source::unitsToString(unsigned int units)
{
  if (units == INFINITY_UNITS)
  {
    return "infinite";
  }
  std::stringstream ss;
  ss << units;
  return ss.str();
}

void Source::setCurrentUnitCount(unsigned int currentUnitCount)
{
  _currentUnitCount = currentUnitCount;
}

} // namespace fictionalfiesta
