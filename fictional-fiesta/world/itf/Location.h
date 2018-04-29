#ifndef INCLUDE_FICTIONAL_FIESTA_WORLD_LOCATION_H
#define INCLUDE_FICTIONAL_FIESTA_WORLD_LOCATION_H

#include "fictional-fiesta/utils/itf/Descriptable.h"
#include "fictional-fiesta/utils/itf/XmlSavable.h"

#include "fictional-fiesta/world/itf/FSM.h"
#include "fictional-fiesta/world/itf/Individual.h"

#include <memory>
#include <vector>

namespace fictionalfiesta
{

class Individual;
class Source;
class XmlNode;

/// @brief Class that represents a location in the world.
/// @details A location has a set of Sources.
class Location : public XmlSavable, public Descriptable
{
  public:

    /// @brief Default constructor.
    /// @details Constructs an empty location (no sources).
    Location();

    /// @brief Constructor from an XmlNode.
    /// @param node XmlNode with the class contents.
    Location(const XmlNode& node);

    /// @brief Move constructor.
    /// @param other Instance to be moved.
    Location(Location&& other);

    /// @brief Copy constructor.
    /// @param other Instance to be copied.
    Location(const Location& other);

    /// @brief Assignment operator.
    /// @param other Location to be assigned.
    /// @return Reference to the current Location.
    Location& operator=(Location other);

    /// @brief Default destructor.
    ~Location();

    /// @brief Splits resources between individuals.
    /// @param rng Random number generator.
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

    /// @brief Performs the actions of the resource phase.
    /// @details The resource phase includes spliting resources between individuals and
    ///    also the resource regeneration for the next cycle.
    /// @param rng Random number generator.
    void resourcePhase(FSM::Rng& rng);

    /// @brief Performs the actions of the individual's maintenance phase.
    /// @details The maintenance phase includes the use of energy by the individuals in maintenance
    ///    and growth.
    /// @param rng Random number generator.
    void maintenancePhase(FSM::Rng& rng);

    /// @brief Performs the actions of the individual's reproduction phase.
    /// @param rng Random number generator.
    void reproductionPhase(FSM::Rng& rng);

    /// @brief Removes the dead individuals from the individuals list.
    void cleanDeadIndividuals();

    /// @brief Performs a full cycle.
    /// @param rng Random number generator.
    void cycle(FSM::Rng& rng);

    /// @copydoc Descriptable::str
    std::string str(unsigned int indentLevel) const override;

    /// @brief Name of the main XML node for this class.
    static constexpr char XML_MAIN_NODE_NAME[]{"Location"};

  private:

    /// @brief Swaps the contents of this instance with the one passed per parameter.
    /// @param other Instance to be swapped.
    void swap(Location& other);

    /// @copydoc XmlSavable::doSave
    void doSave(XmlNode& node) const override;

    /// @copydoc XmlSavable::getDefaultXmlName
    virtual std::string getDefaultXmlName() const override;

    std::vector<std::unique_ptr<Source>> _sources;
    std::vector<Individual> _individuals;
};

} // namespace fictionalfiesta

#endif
