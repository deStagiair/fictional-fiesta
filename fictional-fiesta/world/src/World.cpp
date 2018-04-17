/// @file World.cpp Implementation of the World class.

#include "fictional-fiesta/world/itf/World.h"

#include "fictional-fiesta/utils/itf/XmlDocument.h"
#include "fictional-fiesta/utils/itf/XmlNode.h"

namespace fictionalfiesta
{

namespace
{

constexpr char XML_LOCATIONS_NODE_NAME[]{"Locations"};

std::vector<Location> load_locations(const XmlNode& node);

}

World::World(const XmlNode& node):
  _locations(load_locations(node.getChildNode(XML_LOCATIONS_NODE_NAME)))
{
}

World::World(const std::experimental::filesystem::path& xmlPath)
{
  XmlDocument document{xmlPath};
  _locations = load_locations(document.getRootNode());
}

namespace
{

std::vector<Location> load_locations(const XmlNode& node)
{
  std::vector<Location> locations;

  const std::vector<XmlNode> location_nodes = node.getChildNodes(XML_LOCATIONS_NODE_NAME);
  for (const auto& location_node : location_nodes)
  {
    locations.push_back(std::move(Location(location_node)));
  }

  return locations;
}

} // anonymous namespace

} // namespace fictionalfiesta
