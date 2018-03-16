/// @file XmlNode.cpp Implementation of the XmlNode class.

#include "fictional-fiesta/utils/itf/XmlNode.h"

#include "fictional-fiesta/utils/itf/Exception.h"

#include "fictional-fiesta/utils/src/PimplImpl.h"
#include "fictional-fiesta/utils/src/XmlNodeImpl.h"

#include <iostream>

namespace fictionalfiesta
{

namespace
{

pugi::xml_text get_mandatory_text(const pugi::xml_node& node);

template <typename T>
T text_to(const pugi::xml_text& text);

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
  return get_mandatory_text(_pimpl->_node).get();
}

std::string XmlNode::getOptionalText(const std::string& defaultValue) const
{
  const auto& text = _pimpl->_node.text();

  if (!text)
  {
    return defaultValue;
  }

  return text.get();
}

std::string XmlNode::getChildNodeText() const
{
  return getChildNode().getText();
}

std::string XmlNode::getChildNodeText(const std::string& name) const
{
  return getChildNode(name).getText();
}

std::string XmlNode::getOptionalChildNodeText(const std::string &defaultValue) const
{
  if (!hasChildNode())
  {
    return defaultValue;
  }

  return getChildNode().getOptionalText(defaultValue);
}

template int XmlNode::getTextAs() const;
template unsigned int XmlNode::getTextAs() const;
template double XmlNode::getTextAs() const;
template float XmlNode::getTextAs() const;
template bool XmlNode::getTextAs() const;
template long long XmlNode::getTextAs() const;
template unsigned long long XmlNode::getTextAs() const;

template <typename T>
T XmlNode::getTextAs() const
{
  return text_to<T>(get_mandatory_text(_pimpl->_node));
}

template int XmlNode::getChildNodeTextAs() const;
template unsigned int XmlNode::getChildNodeTextAs() const;
template double XmlNode::getChildNodeTextAs() const;
template float XmlNode::getChildNodeTextAs() const;
template bool XmlNode::getChildNodeTextAs() const;
template long long XmlNode::getChildNodeTextAs() const;
template unsigned long long XmlNode::getChildNodeTextAs() const;

template <typename T>
T XmlNode::getChildNodeTextAs() const
{
  return getChildNode().getTextAs<T>();
}

template int XmlNode::getOptionalTextAs(const int& defaultValue) const;
template unsigned int XmlNode::getOptionalTextAs(const unsigned int& defaultValue) const;
template double XmlNode::getOptionalTextAs(const double& defaultValue) const;
template float XmlNode::getOptionalTextAs(const float& defaultValue) const;
template bool XmlNode::getOptionalTextAs(const bool& defaultValue) const;
template long long XmlNode::getOptionalTextAs(const long long& defaultValue) const;
template unsigned long long XmlNode::getOptionalTextAs(const unsigned long long& defaultValue) const;

template <typename T>
T XmlNode::getOptionalTextAs(const T& defaultValue) const
{
  const auto& text = _pimpl->_node.text();

  if (!text)
  {
    return defaultValue;
  }

  return text_to<T>(text);
}

template int XmlNode::getOptionalChildNodeTextAs(const int& defaultValue) const;
template unsigned int XmlNode::getOptionalChildNodeTextAs(const unsigned int& defaultValue) const;
template double XmlNode::getOptionalChildNodeTextAs(const double& defaultValue) const;
template float XmlNode::getOptionalChildNodeTextAs(const float& defaultValue) const;
template bool XmlNode::getOptionalChildNodeTextAs(const bool& defaultValue) const;
template long long XmlNode::getOptionalChildNodeTextAs(const long long& defaultValue) const;
template unsigned long long XmlNode::getOptionalChildNodeTextAs(const unsigned long long& defaultValue) const;

template <typename T>
T XmlNode::getOptionalChildNodeTextAs(const T& defaultValue) const
{
  if (!hasChildNode())
  {
    return defaultValue;
  }

  return getChildNode().getOptionalTextAs<T>(defaultValue);
}

template int XmlNode::getChildNodeTextAs(const std::string& name) const;
template unsigned int XmlNode::getChildNodeTextAs(const std::string& name) const;
template double XmlNode::getChildNodeTextAs(const std::string& name) const;
template float XmlNode::getChildNodeTextAs(const std::string& name) const;
template bool XmlNode::getChildNodeTextAs(const std::string& name) const;
template long long XmlNode::getChildNodeTextAs(const std::string& name) const;
template unsigned long long XmlNode::getChildNodeTextAs(const std::string& name) const;

template <typename T>
T XmlNode::getChildNodeTextAs(const std::string& name) const
{
  return getChildNode(name).getTextAs<T>();
}

namespace
{

pugi::xml_text get_mandatory_text(const pugi::xml_node& node)
{
  const auto& text = node.text();
  if (!text)
  {
    throw Exception("The current node '" + std::string{node.name()} + "' has no text content.");
  }

  return text;
}

// @todo Substitute all these method template specializations with std::from_chars when available.
template <>
int text_to(const pugi::xml_text& text)
{
  return text.as_int();
}

template <>
unsigned int text_to(const pugi::xml_text& text)
{
  return text.as_uint();
}

template <>
double text_to(const pugi::xml_text& text)
{
  return text.as_double();
}

template <>
float text_to(const pugi::xml_text& text)
{
  return text.as_float();
}

template <>
bool text_to(const pugi::xml_text& text)
{
  return text.as_bool();
}

template <>
long long text_to(const pugi::xml_text& text)
{
  return text.as_llong();
}

template <>
unsigned long long text_to(const pugi::xml_text& text)
{
  return text.as_ullong();
}

} // anonymous namespace.

} // namespace fictionalfiesta
