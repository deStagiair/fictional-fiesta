/// @file XmlNode.cpp Implementation of the XmlNode class.

#include "fictional-fiesta/utils/itf/XmlNode.h"

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
   return (*_pimpl)._node.name();
}

} // namespace fictionalfiesta
