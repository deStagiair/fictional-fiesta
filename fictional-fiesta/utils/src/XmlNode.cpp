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

bool XmlNode::hasChildNode() const
{
  const auto child = _pimpl->_node.first_child();
  return child.type() == pugi::node_element;
}

XmlNode XmlNode::getChildNode() const
{
  if (!hasChildNode())
  {
    throw Exception("The current node '" + getName() + "' has no children.");
  }

  const auto child = _pimpl->_node.first_child();

  return XmlNode(child);
}

bool XmlNode::hasChildNode(const std::string& name) const
{
  const auto child = _pimpl->_node.child(name.c_str());
  return child.type() == pugi::node_element;
}

XmlNode XmlNode::getChildNode(const std::string& name) const
{
  if (!hasChildNode(name))
  {
    throw Exception("The current node '" + getName() + "' has no children with the name '" + name + "'.");
  }

  const auto child = _pimpl->_node.child(name.c_str());

  return XmlNode(child);
}

} // namespace fictionalfiesta
