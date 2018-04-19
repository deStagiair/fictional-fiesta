#ifndef INCLUDE_FICTIONAL_FIESTA_WORLD_WORLD_H
#define INCLUDE_FICTIONAL_FIESTA_WORLD_WORLD_H

#include "fictional-fiesta/utils/itf/Descriptable.h"
#include "fictional-fiesta/utils/itf/XmlSavable.h"

#include "fictional-fiesta/world/itf/FSM.h"
#include "fictional-fiesta/world/itf/Location.h"

#include <experimental/filesystem>
#include <string>
#include <vector>

namespace fictionalfiesta
{

/// @brief Class that represents the world.
class World : public XmlSavable, public Descriptable
{
  public:

    /// @brief Default empty constructor.
    World() = default;

    /// @brief Constructor from a path to a XML document.
    /// @param xmlPath Path to the world XML document.
    explicit World(const std::experimental::filesystem::path& xmlPath);

    /// @brief Add a location to the world.
    /// @param location Location to be added.
    void addLocation(Location&& location);

    /// @brief Run a cycle over all the locations of the world.
    /// @param rng Random number generator.
    void cycle(FSM::Rng& rng);

    /// @copydoc Descriptable::str
    std::string str(unsigned int indentLevel) const override;

    /// Name of the main XML node for this class.
    static constexpr char XML_MAIN_NODE_NAME[]{"World"};

  private:

    /// @brief Constructor from a XmlNode.
    /// @param node XML node from where to load the class contents.
    explicit World(const XmlNode& node);

    /// @copydoc XmlSavable::doSave
    void doSave(XmlNode& node) const override;

    /// @copydoc XmlSavable::getDefaultXmlName
    virtual std::string getDefaultXmlName() const override;

    /// Location vector.
    std::vector<Location> _locations;

};

} // namespace fictionalfiesta

#endif
