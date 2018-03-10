#ifndef INCLUDE_FICTIONAL_FIESTA_UTILS_XML_DOCUMENT_H
#define INCLUDE_FICTIONAL_FIESTA_UTILS_XML_DOCUMENT_H

#include <experimental/filesystem>

#include <memory>

namespace fictionalfiesta
{

class XmlDocumentImpl;

class XmlDocument
{
  private:

    /// Pointer to the document implementation.
    /// We use PIMPL to avoid exposing the XML dependecies.
    std::unique_ptr<XmlDocumentImpl> _document;

  public:

    /// @brief Constructor from the document path.
    ///
    /// @param documentPath path to the XML document.
    explicit XmlDocument(const std::experimental::filesystem::path& documentPath);

    ~XmlDocument();

    /// @brief Save the document to a file in disk.
    ///
    /// @param savePath path where the XML document will be written.
    /// @param prettyPrint whether the document will be saved formated or not.
    ///   Defaults to true.
    /// @throw Exception if the file could not be written.
    void save(const std::experimental::filesystem::path& savePath, bool prettyPrint = true) const;
};

}

#endif
