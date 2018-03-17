/// @file ConstantSource.cpp Implementation of the ConstantSource class.

#include "fictional-fiesta/world/itf/ConstantSource.h"

#include "fictional-fiesta/utils/itf/Exception.h"
#include "fictional-fiesta/utils/itf/XmlNode.h"

#include <limits>

namespace fictionalfiesta
{

namespace
{
constexpr char XML_SOURCE_TYPE_NODE_VALUE[]{"Constant"};
}

ConstantSource::ConstantSource(const std::string& resourceId):
  Source(resourceId, INFINITY_UNITS)
{
}

ConstantSource::ConstantSource(const XmlNode& node):
  Source(node, INFINITY_UNITS)
{
  const std::string type = node.getChildNodeText(XML_SOURCE_TYPE_NODE_NAME);
  // Check that the type is correct.
  if (type != XML_SOURCE_TYPE_NODE_VALUE)
  {
    throw Exception("Incorrect source type '" + type + "', expected type '"
        + XML_SOURCE_TYPE_NODE_VALUE + "'.");
  }
}

unsigned int ConstantSource::consume(const unsigned int requiredUnits)
{
  return requiredUnits;
}

void ConstantSource::regenerate()
{
}

} // namespace fictionalfiesta
