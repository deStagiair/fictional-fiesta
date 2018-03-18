/// @file Location.cpp Implementation of the Location class.

#include "fictional-fiesta/world/itf/Location.h"

#include "fictional-fiesta/world/itf/Source.h"
#include "fictional-fiesta/world/itf/SourceFactory.h"

#include "fictional-fiesta/utils/itf/Exception.h"
#include "fictional-fiesta/utils/itf/XmlNode.h"

namespace fictionalfiesta
{

Location::Location(const XmlNode& node)
{
  const auto& source_nodes = node.getChildNodes(Source::XML_MAIN_NODE_NAME);
  for (const auto& source_node : source_nodes)
  {
    _sources.push_back(SourceFactory::createSource(source_node));
  }
}

void Location::save(XmlNode node) const
{
  for (const auto& source : _sources)
  {
    source->save(node.appendChildNode(Source::XML_MAIN_NODE_NAME));
  }
}

} // namespace fictionalfiesta
