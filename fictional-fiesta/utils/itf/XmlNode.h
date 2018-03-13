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

    /// @brief Checks whether the node has children nodes.
    /// Note that only element nodes are cosidered for this method.
    /// @return true if the current node has at least one element child node.
    bool hasChildNodes() const;

    /// @brief Get the first child node of the current node.
    ///
    /// @return First child node of the current node.
    /// @throw Exception if the node has no children.
    XmlNode getChildNode() const;

  private:

    /// Pointer to the node implementation.
    /// We use PIMPL to avoid exposing the XML dependecies.
    Pimpl<XmlNodeImpl> _pimpl;
};

}

#endif
