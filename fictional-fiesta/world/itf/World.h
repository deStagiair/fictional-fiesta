#ifndef INCLUDE_FICTIONAL_FIESTA_WORLD_WORLD_H
#define INCLUDE_FICTIONAL_FIESTA_WORLD_WORLD_H

//#include "fictional-fiesta/utils/itf/Descriptable.h"

//#include "fictional-fiesta/world/itf/FSM.h"
#include "fictional-fiesta/world/itf/Location.h"

#include <experimental/filesystem>
#include <vector>

namespace fictionalfiesta
{

/// @brief Class that represents the world.
class World// : public Descriptable
{
  public:

    /// @brief Default empty constructor.
    World() = default;

    /// @brief Constructor from a path to a XML document.
    /// @param xmlPath Path to the world XML document.
    explicit World(const std::experimental::filesystem::path& xmlPath);

    /// @brief Save this Individual instance in a XmlNode.
    /// @param node Node where the Individual instance will be saved.
    void save(XmlNode node) const;

    /// Name of the main XML node for this class.
    static constexpr char XML_MAIN_NODE_NAME[]{"World"};

  private:

    /// @brief Constructor from a XmlNode.
    /// @param node XML node from where to load the class contents.
    explicit World(const XmlNode& node);

    /// Location vector.
    std::vector<Location> _locations;

};

} // namespace fictionalfiesta

#endif
