#include "fictional-fiesta/utils/src/XmlDocumentImpl.h"

#include "fictional-fiesta/utils/itf/Exception.h"

namespace fictionalfiesta
{

namespace fs = std::experimental::filesystem;

/// Implementation of the public class XmlDocument.
/// In this case we use pugixml.


XmlDocumentImpl::XmlDocumentImpl(const fs::path &documentPath)
{
  const pugi::xml_parse_result &result = _document.load_file(documentPath.c_str());

  if (!result)
  {
    throw Exception("Error loading XML file '" + documentPath.string() + "':" + std::string(result.description()));
  }
}

} // namespace fictionalfiesta
