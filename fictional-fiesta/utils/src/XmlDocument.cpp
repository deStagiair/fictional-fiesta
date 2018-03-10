/// @file Implementation of the XmlDocument class.

#include "fictional-fiesta/utils/itf/XmlDocument.h"

#include "fictional-fiesta/utils/itf/Exception.h"
#include "fictional-fiesta/utils/src/XmlDocumentImpl.h"

namespace fs = std::experimental::filesystem;

namespace fictionalfiesta
{

XmlDocument::XmlDocument(const fs::path& documentPath):
  _document(std::make_unique<XmlDocumentImpl>(documentPath))
{
}

XmlDocument::~XmlDocument() = default;

void XmlDocument::save(const fs::path& savePath, bool prettyPrint) const
{
  if (!_document->save(savePath, prettyPrint))
  {
    throw Exception("Error saving XML to '" + savePath.string() + "'.");
  }
}

} // namespace fictionalfiesta
