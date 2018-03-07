/// Implementation of the XmlDocument class.

#include "fictional-fiesta/utils/itf/XmlDocument.h"

#include "fictional-fiesta/utils/src/XmlDocumentImpl.h"

namespace fictionalfiesta
{

XmlDocument::XmlDocument(const std::experimental::filesystem::path& documentPath):
  _document(std::make_unique<XmlDocumentImpl>(documentPath))
{
}

XmlDocument::~XmlDocument() = default;

} // namespace fictionalfiesta
