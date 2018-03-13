#ifndef INCLUDE_FICTIONAL_FIESTA_UTILS_XML_NODE_H
#define INCLUDE_FICTIONAL_FIESTA_UTILS_XML_NODE_H

#include "fictional-fiesta/utils/itf/Pimpl.h"

namespace fictionalfiesta
{

class XmlNodeImpl;

/// @brief Class to represent a node in an XML document.
class XmlNode
{
  public:

    /// @brief Constructor from a node implementation class instance.
    /// Since the XmlNodeImpl class is not visible from outside, this constructor
    /// can only be used internally.
    ///
    /// @param node node implementation from which to construct this instance.
    explicit XmlNode(const XmlNodeImpl& node);

    /// @brief Default destructor.
    ~XmlNode();

    /// @brief Get the name of the node.
    /// @return returns a string with the name of the node.
    std::string getName() const;

  private:

    /// Pointer to the node implementation.
    /// We use PIMPL to avoid exposing the XML dependecies.
    Pimpl<XmlNodeImpl> _pimpl;
};

}

#endif
