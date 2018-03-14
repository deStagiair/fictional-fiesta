#ifndef INCLUDE_FICTIONAL_FIESTA_UTILS_XML_NODE_H
#define INCLUDE_FICTIONAL_FIESTA_UTILS_XML_NODE_H

#include "fictional-fiesta/utils/itf/Pimpl.h"

#include <string>
#include <vector>

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

    /// @brief Move Constructor
    XmlNode(XmlNode&&);

    /// @brief Default destructor.
    ~XmlNode();

    /// @brief Get the name of the node.
    /// @return returns a string with the name of the node.
    std::string getName() const;

    /// @brief Checks whether the node has any child node.
    /// Note that only element nodes are cosidered for this method.
    /// @return true if the current node has at least one element child node.
    bool hasChildNode() const;

    /// @brief Checks whether the node has at least a child node with the given @p name.
    /// Note that only element nodes are cosidered for this method.
    /// @param name name of the child node.
    /// @return true if the current node has at least one element child node with the given @p name.
    bool hasChildNode(const std::string& name) const;

    /// @brief Get the first child node of the current node.
    ///
    /// @return First child node of the current node.
    /// @throw Exception if the node has no children.
    XmlNode getChildNode() const;

    /// @brief Get the first child node of the current node with the given @p name.
    /// @param name name of the child node.
    /// @return First child node of the current node with the given @p name .
    /// @throw Exception if the node has no children with the given name.
    XmlNode getChildNode(const std::string& name) const;

    /// @brief Get all the child nodes.
    /// @return All the child nodes of the current node.
    std::vector<XmlNode> getChildNodes() const;

    /// @brief Get all the child nodes with a given @p name.
    /// @param name name of the child nodes to retrieve.
    /// @return All the child nodes with the given name.
    std::vector<XmlNode> getChildNodes(const std::string& name) const;

    /// @brief Get the text of the node.
    /// @return String with the text contents of the node.
    /// @throw Exception if the node has no text.
    std::string getText() const;

  private:

    /// Pointer to the node implementation.
    /// We use PIMPL to avoid exposing the XML dependecies.
    Pimpl<XmlNodeImpl> _pimpl;
};

}

#endif
