#ifndef INCLUDE_FICTIONAL_FIESTA_UTILS_XML_NODE_H
#define INCLUDE_FICTIONAL_FIESTA_UTILS_XML_NODE_H

#include <memory>

namespace fictionalfiesta
{

class XmlNodeImpl;

class XmlNode
{
  private:

    /// Pointer to the node implementation.
    /// We use PIMPL to avoid exposing the XML dependecies.
    std::unique_ptr<XmlNodeImpl> _node;
};

} // namespace fictionalfiesta

#endif
