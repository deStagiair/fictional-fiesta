/// @file XmlNode.cpp Implementation of the XmlNode class.

#include "fictional-fiesta/utils/itf/XmlNode.h"

#include "fictional-fiesta/utils/itf/Exception.h"

#include "fictional-fiesta/utils/src/PimplImpl.h"
#include "fictional-fiesta/utils/src/XmlNodeImpl.h"

namespace fictionalfiesta
{

XmlNode::XmlNode(const XmlNodeImpl& node):
  _pimpl(node._node)
{
}

XmlNode::~XmlNode() = default;

std::string XmlNode::getName() const
{
   return _pimpl->_node.name();
}

bool XmlNode::hasChildNodes() const
{
  const auto child = _pimpl->_node.first_child();
  return child.type() == pugi::node_element;
}


XmlNode XmlNode::getChildNode() const
{
  if (!hasChildNodes())
  {
    throw Exception("The current node '" + getName() + "' has no children.");
  }

  const auto child = _pimpl->_node.first_child();

  if (child.type() == pugi::node_null)
  {
  }

  return XmlNode(child);
}

} // namespace fictionalfiesta
