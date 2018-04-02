#ifndef INCLUDE_FICTIONAL_FIESTA_WORLD_LOCATION_H
#define INCLUDE_FICTIONAL_FIESTA_WORLD_LOCATION_H

#include "fictional-fiesta/world/itf/FSM.h"

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
    Location();

    ~Location();

    /// @brief Constructor from an XmlNode.
    /// @param node XmlNode with the class contents.
    Location(const XmlNode& node);

    /// @brief Save this Location instance in a XmlNode.
    /// @param node Node where the Source instance will be saved.
    void save(XmlNode& node) const;

    /// @brief Splits resources between individuals.
    void splitResources(FSM::Rng& rng);

    /// @brief Add a new source to the location.
    /// @details It transfers the ownership of the source to the location.
    /// @param source Source to be added to the location.
    void addSource(std::unique_ptr<Source>&& source);

    /// @brief Add a new individual to the location.
    /// @param individual Individual to be added to the location.
    void addIndividual(const Individual& individual);

    /// @brief Gets the individuals currently in the Location.
    /// @return Individuals that are currently in this Location.
    const std::vector<Individual>& getIndividuals() const;

  private:

    std::vector<std::unique_ptr<Source>> _sources;
    std::vector<Individual> _individuals;
};

} // namespace fictionalfiesta

#endif
