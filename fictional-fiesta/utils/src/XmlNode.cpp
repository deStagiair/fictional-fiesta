/// @file XmlNode.cpp Implementation of the XmlNode class.

#include "fictional-fiesta/utils/itf/XmlNode.h"

#include "fictional-fiesta/utils/itf/Exception.h"

#include "fictional-fiesta/utils/src/PimplImpl.h"
#include "fictional-fiesta/utils/src/XmlNodeImpl.h"

namespace fictionalfiesta
{

namespace
{
const pugi::xml_text& get_mandatory_text(const pugi::xml_node& node);
} // anonymous namespace

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

/// @brief Get the text of the node and pase it into an \c int.
/// @return \c int resulting from the conversion.
/// @throw Exception if the node has no text.
template <>
int XmlNode::getTextAs() const
{
  const auto text = get_mandatory_text(_pimpl->_node);
  return text.as_int();
}

/// @brief Get the text of the node and pase it into an \c unsigned \c int.
/// @return \c unsigned \c int resulting from the conversion.
/// @throw Exception if the node has no text.
template <>
unsigned int XmlNode::getTextAs() const
{
  const auto text = get_mandatory_text(_pimpl->_node);
  return text.as_uint();
}

/// @brief Get the text of the node and pase it into a \c double.
/// @return \c double resulting from the conversion.
/// @throw Exception if the node has no text.
template <>
double XmlNode::getTextAs() const
{
  const auto text = get_mandatory_text(_pimpl->_node);
  return text.as_double();
}

/// @brief Get the text of the node and pase it into a \c float.
/// @return \c float resulting from the conversion.
/// @throw Exception if the node has no text.
template <>
float XmlNode::getTextAs<float>() const
{
  const auto text = get_mandatory_text(_pimpl->_node);
  return text.as_float();
}

/// @brief Get the text of the node and pase it into a \c bool.
/// @return \c bool resulting from the conversion.
/// @throw Exception if the node has no text.
template <>
bool XmlNode::getTextAs() const
{
  const auto text = get_mandatory_text(_pimpl->_node);
  return text.as_bool();
}

/// @brief Get the text of the node and pase it into a \c long \c long.
/// @return \c long \c long resulting from the conversion.
/// @throw Exception if the node has no text.
template <>
long long XmlNode::getTextAs() const
{
  const auto text = get_mandatory_text(_pimpl->_node);
  return text.as_llong();
}

/// @brief Get the text of the node and pase it into an \c unsigned \c long \c long.
/// @return \c unsigned \c long \c long resulting from the conversion.
/// @throw Exception if the node has no text.
template <>
unsigned long long XmlNode::getTextAs() const
{
  const auto text = get_mandatory_text(_pimpl->_node);
  return text.as_ullong();
}

namespace
{

const pugi::xml_text& get_mandatory_text(const pugi::xml_node& node)
{
  const auto& text = node.text();
  if (!text)
  {
    throw Exception("The current node '" + std::string{node.name()} + "' has no text content.");
  }

  return text;
}

} // anonymous namespace.

} // namespace fictionalfiesta
