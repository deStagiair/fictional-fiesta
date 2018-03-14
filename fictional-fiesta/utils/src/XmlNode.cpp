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

XmlNode::XmlNode(XmlNode&&) = default;

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

bool XmlNode::hasChildNode(const std::string& name) const
{
  const auto child = _pimpl->_node.child(name.c_str());
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

XmlNode XmlNode::getChildNode(const std::string& name) const
{
  if (!hasChildNode(name))
  {
    throw Exception("The current node '" + getName() + "' has no children with the name '" + name + "'.");
  }

  const auto child = _pimpl->_node.child(name.c_str());

  return XmlNode(child);
}

std::vector<XmlNode> XmlNode::getChildNodes() const
{
  std::vector<XmlNode> result;
  for (auto child = _pimpl->_node.first_child(); child; child = child.next_sibling())
  {
    if (child.type() == pugi::node_element)
    {
      result.emplace_back(child);
    }
  }
  return result;
}

std::vector<XmlNode> XmlNode::getChildNodes(const std::string& name) const
{
  std::vector<XmlNode> result;
  for (auto child = _pimpl->_node.child(name.c_str()); child; child = child.next_sibling(name.c_str()))
  {
    if (child.type() == pugi::node_element)
    {
      result.emplace_back(child);
    }
  }
  return result;
}

std::string XmlNode::getText() const
{
  const auto text = _pimpl->_node.text();
  if (!text)
  {
    throw Exception("The current node '" + getName() + "' has no text content.");
  }

  return text.get();
}

} // namespace fictionalfiesta
