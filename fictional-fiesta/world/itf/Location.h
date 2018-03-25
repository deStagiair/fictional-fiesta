#ifndef INCLUDE_FICTIONAL_FIESTA_WORLD_LOCATION_H
#define INCLUDE_FICTIONAL_FIESTA_WORLD_LOCATION_H

#include <memory>
#include <vector>

namespace fictionalfiesta
{

class Individual;
class Source;
class XmlNode;

/// @brief Class that represents a location in the world.
/// @details A location has a set of Sources.
class Location
{
  public:

    /// @brief Default constructor.
    /// @details Constructs an empty location (no sources).
    Location() = default;

    /// @brief Constructor from an XmlNode.
    /// @param node XmlNode with the class contents.
    Location(const XmlNode& node);

    /// @brief Save this Location instance in a XmlNode.
    /// @param node node where the Source instance will be saved.
    void save(XmlNode node) const;

    /// @brief Get the individuals in this location.
    /// @return individuals in this location.
    const std::vector<Individual>& getIndividuals() const;

  private:

    std::vector<std::unique_ptr<Source>> _sources;
    std::vector<Individual> _individuals;
};

} // namespace fictionalfiesta

#endif
