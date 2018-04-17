/// @file Xmlable.cpp Implementation of the Xmlable interface.

#include "fictional-fiesta/world/itf/Genotype.h"

#include "fictional-fiesta/world/itf/Phenotype.h"

#include "fictional-fiesta/utils/itf/XmlDocument.h"
#include "fictional-fiesta/utils/itf/XmlNode.h"

namespace fictionalfiesta
{

void Xmlable::save(XmlNode node) const
{
  doSave(node);
}

void Xmlable::save(const std::experimental::filesystem::path& filePath) const
{
  auto result_document = XmlDocument{};
  auto node = result_document.appendRootNode(getDefaultXmlName());
  doSave(node);
  result_document.save(filePath);
}

}
