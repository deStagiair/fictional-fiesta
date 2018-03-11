/// @file XmlDocumentImpl.cpp Implementation of the public class XmlDocument.
///   In this case we use pugixml.

#include "fictional-fiesta/utils/src/XmlDocumentImpl.h"

#include "fictional-fiesta/utils/itf/Exception.h"

namespace fs = std::experimental::filesystem;

namespace fictionalfiesta
{

namespace
{

constexpr const char* INDENT_STRING = "  ";

} // anonymous namespace

XmlDocumentImpl::XmlDocumentImpl(const fs::path& documentPath)
{
  const pugi::xml_parse_result &result = _document.load_file(documentPath.c_str());

  if (!result)
  {
    throw Exception("Error loading XML file '" + documentPath.string() + "':" + std::string(result.description()));
  }
}

bool XmlDocumentImpl::save(const fs::path& savePath, bool prettyPrint) const
{
  const unsigned int format = (prettyPrint ? pugi::format_default : pugi::format_raw);
  return _document.save_file(savePath.c_str(), INDENT_STRING, format);
}

} // namespace fictionalfiesta
