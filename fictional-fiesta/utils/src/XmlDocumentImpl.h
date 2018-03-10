#ifndef INCLUDE_FICTIONAL_FIESTA_UTILS_XML_DOCUMENT_IMPL_H
#define INCLUDE_FICTIONAL_FIESTA_UTILS_XML_DOCUMENT_IMPL_H

#include <pugixml.hpp>

#include <experimental/filesystem>

namespace fictionalfiesta
{

/// Implementation of the public class XmlDocument.
/// In this case we use pugixml.
class XmlDocumentImpl
{
  private:

    /// Internal XML document from pugi.
    pugi::xml_document _document;

  public:

    /// @brief Constructor from the document path.
    ///
    /// @param documentPath path to the XML document.
    explicit XmlDocumentImpl(const std::experimental::filesystem::path& documentPath);

    /// @brief Save the document to a file in disk.
    ///
    /// @param savePath path where the XML document will be written.
    /// @param prettyPrint whether the document will be saved formated or not.
    ///   Defaults to true.
    /// @return true if the file was written successfully and false otherwise.
    bool save(const std::experimental::filesystem::path& savePath, bool prettyPrint = true) const;
};

} // namespace fictionalfiesta

#endif
