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

ConstantSource::ConstantSource(const XmlNode& node, unsigned int fixedUnitCount):
  Source(node, fixedUnitCount),
  _fixedUnitCount(fixedUnitCount)
{
  const std::string type = node.getAttribute(XML_SOURCE_TYPE_ATTRIBUTE_NAME);
  // Check that the type is correct.
  if (type != XML_SOURCE_TYPE_ATTRIBUTE_VALUE)
  {
    throw Exception("Incorrect source type '" + type + "', expected type '"
        + XML_SOURCE_TYPE_ATTRIBUTE_VALUE + "'.");
  }
}

ConstantSource::ConstantSource(const XmlNode& node):
  ConstantSource(node, get_unit_count_from_node(node.getChildNode(XML_FIXED_UNIT_COUNT_NODE_NAME)))
{
}

void ConstantSource::regenerate()
{
  setCurrentUnitCount(_fixedUnitCount);
}

std::string ConstantSource::str(unsigned int indentLevel) const
{
  std::stringstream ss;
  ss << indent(indentLevel) << "Constant source '" << getResourceId() << "' (" <<
      _fixedUnitCount << ")\n";

  ss << indent(indentLevel) << "Current units: " << getCurrentUnitCount() << "\n";
  return ss.str();
}

void ConstantSource::doSave(XmlNode& node) const
{
  node.setAttribute(XML_SOURCE_TYPE_ATTRIBUTE_NAME, XML_SOURCE_TYPE_ATTRIBUTE_VALUE);

  auto fixed_units_node = node.appendChildNode(XML_FIXED_UNIT_COUNT_NODE_NAME);
  fixed_units_node.setText(unitsToString(_fixedUnitCount));
}

ConstantSource* ConstantSource::doClone() const
{
  return new ConstantSource(*this);
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
