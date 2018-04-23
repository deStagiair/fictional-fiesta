/// @file XmlSavable.cpp Implementation of the XmlSavable interface.

#include "fictional-fiesta/utils/itf/XmlDocument.h"
#include "fictional-fiesta/utils/itf/XmlNode.h"
#include "fictional-fiesta/utils/itf/XmlSavable.h"

namespace fictionalfiesta
{

void XmlSavable::save(XmlNode node) const
{
  doSave(node);
}

void XmlSavable::save(const std::experimental::filesystem::path& filePath) const
{
  auto result_document = XmlDocument{};
  auto node = result_document.appendRootNode(getDefaultXmlName());
  doSave(node);
  result_document.save(filePath);
}

void XmlSavable::save(std::ostream& stream) const
{
  auto result_document = XmlDocument{};
  auto node = result_document.appendRootNode(getDefaultXmlName());
  doSave(node);
  result_document.save(stream);
}

}
