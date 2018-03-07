#include "fictional-fiesta/utils/src/XmlDocumentImpl.h"

#include "fictional-fiesta/utils/itf/Exception.h"

namespace fictionalfiesta
{

namespace fs = std::experimental::filesystem;

/// Implementation of the public class XmlDocument.
/// In this case we use pugixml.


XmlDocumentImpl::XmlDocumentImpl(const fs::path &documentPath)
{
  const pugi::xml_parse_result &result = _document.load(documentPath.c_str());

  if (!result)
  {
    throw Exception(result.description());
  }
}

} // namespace fictionalfiesta
