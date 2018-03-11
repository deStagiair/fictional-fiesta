/// @file XmlDocument.cpp Implementation of the XmlDocument class.

#include "fictional-fiesta/utils/itf/XmlDocument.h"

#include "fictional-fiesta/utils/itf/Exception.h"

#include "fictional-fiesta/utils/src/PimplImpl.h"

#include <pugixml.hpp>

namespace fs = std::experimental::filesystem;

namespace fictionalfiesta
{

namespace
{

constexpr const char* INDENT_STRING = "  ";

} // anonymous namespace

/// @brief Implementation of the XmlDocument class.
class XmlDocument::Impl
{
  public:
    /// @brief Constructor from the document path.
    ///
    /// @param documentPath path to the XML document.
    Impl(const fs::path& documentPath);

    Impl(const Impl&) = delete;

    /// Internal XML document from pugi.
    pugi::xml_document _document;
};

/// @brief Implementation of the XmlNode class.
class XmlNode::Impl
{
  public:
    /// @brief Constructor from the pugi xml_node.
    ///
    /// @param node pugi xml_node
    Impl(const pugi::xml_node& node);

    /// Internal XML document from pugi.
    pugi::xml_node _node;
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
  return XmlNode{_pimpl->_document.first_child()};
}

XmlNode::XmlNode(const XmlNode::Impl& node):
  _pimpl(node._node)
{
}

XmlNode::~XmlNode() = default;

std::string XmlNode::getName() const
{
   return (*_pimpl)._node.name();
}

XmlNode::Impl::Impl(const pugi::xml_node& node) :
  _node(node)
{
}

} // namespace fictionalfiesta
