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

    /// @brief Default constructor. Creates a new empty document.
    XmlDocument();

    /// @brief Constructor from the document path.
    ///
    /// @param documentPath path to the XML document.
    explicit XmlDocument(const std::experimental::filesystem::path& documentPath);

    /// @brief Default destructor.
    ~XmlDocument();

    /// @brief Save the document to a file in disk.
    /// @param savePath path where the XML document will be written.
    /// @param prettyPrint whether the document will be saved formated or not.
    ///   Defaults to true.
    /// @throw Exception if the file could not be written.
    void save(const std::experimental::filesystem::path& savePath, bool prettyPrint = true) const;

    /// @brief Save the document to an output stream.
    /// @param stream stream where to write the document.
    /// @param prettyPrint whether the document will be saved formated or not.
    ///   Defaults to true.
    void save(std::ostream& stream, bool prettyPrint = true) const;

    /// @brief Obtain the root node of the document.
    /// @return Root node of the document.
    XmlNode getRootNode() const;

    /// @brief Appends a root node to the current document.
    /// @param name Name of the root node to be appended.
    /// @return Appended new node.
    XmlNode appendRootNode(const std::string& name);

  private:

    class Impl;

    /// Pointer to the document implementation.
    /// We use PIMPL to avoid exposing the XML dependecies.
    Pimpl<Impl> _pimpl;
};

}

#endif
