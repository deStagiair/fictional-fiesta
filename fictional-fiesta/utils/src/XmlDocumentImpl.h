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

    /// @brief Constructor from the pugi document.
    ///
    /// @param documentPath path to the XML document.
    explicit XmlDocumentImpl(const std::experimental::filesystem::path& documentPath);

};

} // namespace fictionalfiesta

#endif
