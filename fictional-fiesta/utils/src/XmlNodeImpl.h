#ifndef INCLUDE_FICTIONAL_FIESTA_UTILS_XML_NODE_IMPL_H
#define INCLUDE_FICTIONAL_FIESTA_UTILS_XML_NODE_IMPL_H

#include <pugixml.hpp>

namespace fictionalfiesta
{

/// Implementation of the public class XmlNode.
/// In this case we use pugixml.
class XmlNodeImpl
{
  private:

    /// Pointer to the internal XML node from pugi.
    pugi::xml_node _node;

  public:

    /// @brief Constructor from the pointer.
    ///
    /// @param node pugi node
    explicit XmlNodeImpl(const pugi::xml_node &node);

};

} // namespace fictionalfiesta

#endif
