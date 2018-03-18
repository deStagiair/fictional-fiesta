#ifndef INCLUDE_FICTIONAL_FIESTA_WORLD_SOURCE_H
#define INCLUDE_FICTIONAL_FIESTA_WORLD_SOURCE_H

#include <limits>
#include <string>

namespace fictionalfiesta
{

class XmlNode;

/// @brief Class that represents a source that generates a given resource.
class Source
{
  public:

    /// @brief Constructor from the resource name.
    /// @param resourceId Resource identifier.
    /// @param initialUnitCount Inital number of units of the resource available.
    Source(const std::string& resourceId, unsigned int initialUnitCount);

    /// @brief Constructor from an XmlNode and a number of initial units.
    /// @param node XmlNode with the class contents.
    /// @param initialUnitCount Inital number of units of the resource available.
    Source(const XmlNode& node, unsigned int initialUnitCount);

    /// @brief Default destructor.
    virtual ~Source() = default;

    /// @brief Get the resource identifier.
    /// @return Resource identifier.
    const std::string& getResourceId() const;

    /// @brief Get the number of units of resource available.
    /// @return Current number of units of the resource.
    const unsigned int getCurrentUnitCount() const;

    /// @brief Consume a given number of units of the resource.
    /// It is not possible to consume more units than available.
    /// @param requiredUnits Units of the resource required.
    /// @return Effective number if units consumed.
    virtual unsigned int consume(const unsigned int requiredUnits);

    /// @brief Regenerates the number of units of the resource.
    virtual void regenerate() = 0;

    /// Representation of an infinity number of units.
    static constexpr unsigned int INFINITY_UNITS{std::numeric_limits<unsigned int>::max()};

    /// Name of the source type node.
    static constexpr char XML_SOURCE_TYPE_NODE_NAME[]{"Type"};

  protected:

    /// @brief Set the number of units of the resource.
    /// @param currentUnitCount Number of units to be set.
    void setCurrentUnitCount(unsigned int currentUnitCount);

  private:

    std::string _resourceId;

    unsigned int _currentUnitCount;
};

}

#endif
