/// @file XmlDocument.cpp Implementation of the XmlDocument class.

#include "fictional-fiesta/utils/itf/XmlDocument.h"

#include "fictional-fiesta/utils/itf/Exception.h"
#include "fictional-fiesta/utils/itf/XmlNode.h"

#include "fictional-fiesta/utils/src/PimplImpl.h"
#include "fictional-fiesta/utils/src/XmlNodeImpl.h"

#include <pugixml.hpp>

namespace fs = std::experimental::filesystem;


namespace
{

constexpr const char* INDENT_STRING = "  ";

} // anonymous namespace

namespace fictionalfiesta
{

XmlDocument::XmlDocument() = default;

/// @brief Implementation of the XmlDocument class.
class XmlDocument::Impl
{
  public:
    /// @brief Constructor from the document path.
    Impl() = default;

    /// @brief Constructor from the document path.
    /// @param documentPath path to the XML document.
    Impl(const fs::path& documentPath);

    /// Internal XML document from pugi.
    pugi::xml_document _document;
};

XmlDocument::Impl::Impl(const fs::path& documentPath)
{
  const pugi::xml_parse_result &result = _document.load_file(documentPath.c_str());

  if (!result)
  {
    throw Exception("Error loading XML file '" + documentPath.string() + "':" + std::string(result.description()));
  }
}

XmlDocument::XmlDocument(const fs::path& documentPath):
  _pimpl(documentPath)
{
}

XmlDocument::~XmlDocument() = default;

void XmlDocument::save(const fs::path& savePath, bool prettyPrint) const
{
  const unsigned int format = (prettyPrint ? pugi::format_default : pugi::format_raw);
  if (!_pimpl->_document.save_file(savePath.c_str(), INDENT_STRING, format))
  {
    throw Exception("Error saving XML to '" + savePath.string() + "'.");
  }
}

XmlNode XmlDocument::getRootNode() const
{
  return XmlNode{XmlNodeImpl(_pimpl->_document.first_child())};
}

XmlNode XmlDocument::appendRootNode(const std::string& name)
{
  auto node = _pimpl->_document.append_child();
  node.set_name(name.c_str());
  return XmlNode(node);
}

} // namespace fictionalfiesta
