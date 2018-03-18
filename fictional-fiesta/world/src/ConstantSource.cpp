/// @file ConstantSource.cpp Implementation of the ConstantSource class.

#include "fictional-fiesta/world/itf/ConstantSource.h"

#include "fictional-fiesta/utils/itf/Exception.h"
#include "fictional-fiesta/utils/itf/XmlNode.h"

#include <limits>

namespace fictionalfiesta
{

namespace
{

unsigned int get_unit_count_from_node(const XmlNode& fixedUnitNode);

} // anonymous namespace

ConstantSource::ConstantSource(const std::string& resourceId, unsigned int fixedUnitCount,
    unsigned int currentUnitCount):
  Source(resourceId, currentUnitCount),
  _fixedUnitCount(fixedUnitCount)
{
}

ConstantSource::ConstantSource(const std::string& resourceId, unsigned int fixedUnitCount):
  ConstantSource(resourceId, fixedUnitCount, fixedUnitCount)
{
}

ConstantSource::ConstantSource(const XmlNode& node):
  Source(node, get_unit_count_from_node(node.getChildNode(XML_FIXED_UNIT_COUNT_NODE_NAME))),
  _fixedUnitCount(get_unit_count_from_node(node.getChildNode(XML_FIXED_UNIT_COUNT_NODE_NAME)))
{
  const std::string type = node.getChildNodeText(XML_SOURCE_TYPE_NODE_NAME);
  // Check that the type is correct.
  if (type != XML_SOURCE_TYPE_NODE_VALUE)
  {
    throw Exception("Incorrect source type '" + type + "', expected type '"
        + XML_SOURCE_TYPE_NODE_VALUE + "'.");
  }
}

void ConstantSource::regenerate()
{
  setCurrentUnitCount(_fixedUnitCount);
}

void ConstantSource::doSave(XmlNode node)
{
}

namespace
{

unsigned int get_unit_count_from_node(const XmlNode& fixedUnitNode)
{
  const std::string value_string = fixedUnitNode.getText();
  if (value_string == "infinity")
  {
    return Source::INFINITY_UNITS;
  }

  return fixedUnitNode.getTextAs<unsigned int>();
}

} // anonymous namespace

} // namespace fictionalfiesta
