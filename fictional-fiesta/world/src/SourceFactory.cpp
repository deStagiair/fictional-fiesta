/// @file SourceFactory.cpp Implementation of the SourceFactory class.

#include "fictional-fiesta/world/itf/SourceFactory.h"

#include "fictional-fiesta/world/itf/ConstantSource.h"
#include "fictional-fiesta/world/itf/Source.h"

#include "fictional-fiesta/utils/itf/Exception.h"
#include "fictional-fiesta/utils/itf/XmlNode.h"

namespace fictionalfiesta
{

std::unique_ptr<Source> SourceFactory::createSource(const XmlNode& node)
{
  const std::string source_type{node.getChildNodeText(Source::XML_SOURCE_TYPE_NODE_NAME)};

  if (source_type == ConstantSource::XML_SOURCE_TYPE_NODE_VALUE)
  {
    return std::make_unique<ConstantSource>(node);
  }
  else
  {
    throw Exception("Unknown source type '" + source_type + "'.");
  }
}

} // namespace fictionalfiesta
