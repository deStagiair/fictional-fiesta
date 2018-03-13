/// @file XmlNodeImpl.cpp Implementation of the XmlNodeImpl class.

#include "fictional-fiesta/utils/src/XmlNodeImpl.h"

namespace fictionalfiesta
{

XmlNodeImpl::XmlNodeImpl(const pugi::xml_node& node) :
  _node(node)
{
}

} // namespace fictionalfiesta
