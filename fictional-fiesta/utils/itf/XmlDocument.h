#ifndef INCLUDE_FICTIONAL_FIESTA_UTILS_XML_DOCUMENT_H
#define INCLUDE_FICTIONAL_FIESTA_UTILS_XML_DOCUMENT_H

#include "fictional-fiesta/utils/itf/Pimpl.h"

#include <experimental/filesystem>

namespace fictionalfiesta
{

class XmlNode;

/// @brief Class that represents a XML document
class XmlDocument
{
  public:

    /// @brief Constructor from the document path.
    ///
    /// @param documentPath path to the XML document.
    explicit XmlDocument(const std::experimental::filesystem::path& documentPath);

    /// @brief Default destructor.
    ~XmlDocument();

    /// @brief Save the document to a file in disk.
    ///
    /// @param savePath path where the XML document will be written.
    /// @param prettyPrint whether the document will be saved formated or not.
    ///   Defaults to true.
    /// @throw Exception if the file could not be written.
    void save(const std::experimental::filesystem::path& savePath, bool prettyPrint = true) const;

    XmlNode getRootNode() const;

  private:

    class Impl;

    /// Pointer to the document implementation.
    /// We use PIMPL to avoid exposing the XML dependecies.
    Pimpl<Impl> _pimpl;
};

/// @brief Class to represent a node in an XML document.
class XmlNode
{
  public:

    class Impl;

  public:

    /// @brief Constructor from a node implementation class instance.
    /// This constructor should only be used internally.
    ///
    /// @param node node implementation from which to construct this instance.
    explicit XmlNode(const Impl& node);

    /// @brief Default destructor.
    ~XmlNode();

    /// @brief Get the name of the node.
    /// @return returns a string with the name of the node.
    std::string getName() const;

  private:

    /// Pointer to the node implementation.
    /// We use PIMPL to avoid exposing the XML dependecies.
    Pimpl<Impl> _pimpl;
};

}

#endif
