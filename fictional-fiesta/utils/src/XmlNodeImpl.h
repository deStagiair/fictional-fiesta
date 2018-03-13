#ifndef INCLUDE_FICTIONAL_FIESTA_UTILS_XML_NODE_IMPL_H
#define INCLUDE_FICTIONAL_FIESTA_UTILS_XML_NODE_IMPL_H

#include "fictional-fiesta/utils/itf/Pimpl.h"

#include <pugixml.hpp>

namespace fictionalfiesta
{

/// @brief Implementation of the XmlNode class.
class XmlNodeImpl
{
  public:
    /// @brief Constructor from the pugi xml_node.
    ///
    /// @param node pugi xml_node
    XmlNodeImpl(const pugi::xml_node& node);

    /// Internal XML document from pugi.
    pugi::xml_node _node;
};

}

#endif
