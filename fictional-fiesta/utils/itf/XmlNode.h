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

    /// @brief Get the text of the node or return the default value if there is no text.
    /// @param defaultValue Value to be returned if there's no text.
    /// @return String with the text contents of the node.
    std::string getOptionalText(const std::string& defaultValue) const;

    /// @brief Get the text of the child node.
    /// @return text of the child node.
    /// @throw Exception if the node has no child or the child has no text.
    std::string getChildNodeText() const;

    /// @brief Get the text of the child node with a given name.
    /// @param name name of the child node.
    /// @return text of the child node with the given name.
    /// @throw Exception if the node has no such a child or the child has no text.
    std::string getChildNodeText(const std::string& name) const;

    /// @brief Get the text of the child node or @p default if there is no child node.
    /// @param defaultValue value to return by default.
    /// @return text of the child node or @p defaultValue if there is no text.
    std::string getOptionalChildNodeText(const std::string& defaultValue = "") const;

    /// @brief Get the text of the node and parse it into @p T type.
    /// @tparam T Type into which the text needs to be parsed.
    /// @return value resulting of the parsing.
    /// @throw Exception if the node has no text.
    template <typename T>
    T getTextAs() const;

    ///// @brief Get the text of the node and parse it into @p T type.
    /////   If there is no text, return the default value.
    ///// @tparam T Type into which the text needs to be parsed.
    ///// @param defaultValue Value returned if there is no text in the node.
    ///// @return value resulting of the parsing.
    ///// @throw Exception if the node has no text.
    //template <typename T>
    //T getOptionalTextAs(const T& defaultValue) const;

    /// @brief Get the text of the child node and parse it into @p type.
    /// @tparam T Type into which the text needs to be parsed.
    /// @return value resulting of the parsing.
    /// @throw Exception if the node has no child or the child has no text.
    template <typename T>
    T getChildNodeTextAs() const;

    /// @brief Get the text of the child node with a give type and parse it into @p type.
    /// @tparam T Type into which the text needs to be parsed.
    /// @param name name of the child node.
    /// @return value resulting of the parsing.
    /// @throw Exception if the node has no such a child or the child has no text.
    template <typename T>
    T getChildNodeTextAs(const std::string& name) const;

  private:

    /// Pointer to the node implementation.
    /// We use PIMPL to avoid exposing the XML dependecies.
    Pimpl<XmlNodeImpl> _pimpl;
};

} // namespace fictional-fiesta

#endif
