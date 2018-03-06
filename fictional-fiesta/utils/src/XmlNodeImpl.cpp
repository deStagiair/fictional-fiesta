/// Implementation of the XmlNodeImpl class

#include "fictional-fiesta/utils/src/XmlNodeImpl.h"

using pugi::xml_node;

namespace fictionalfiesta
{

XmlNodeImpl::XmlNodeImpl(const xml_node &node):
  _node(node)
{
}
    

} // namespace fictionalfiesta
