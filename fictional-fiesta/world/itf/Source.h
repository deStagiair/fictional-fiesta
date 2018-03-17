#ifndef INCLUDE_FICTIONAL_FIESTA_WORLD_SOURCE_H
#define INCLUDE_FICTIONAL_FIESTA_WORLD_SOURCE_H

#include <limits>
#include <string>

namespace fictionalfiesta
{

/// @brief Class that represents a source that generates a given resource.
class Source
{
  public:

    /// @brief Constructor from the resource name.
    /// @param resourceId Resource identifier.
    /// @param initialUnitCount Inital number of units of the resource available.
    Source(const std::string& resourceId, unsigned int initialUnitCount);

    /// @brief Default destructor.
    virtual ~Source() = default;

    /// @brief Get the resource identifier.
    /// @return Resource identifier.
    const std::string& getResourceId() const;

    /// @brief Get the number of units of resource available.
    /// @return Current number of units of the resource.
    const unsigned int getUnitCount() const;

    /// @brief Consume a given number of units of the resource.
    /// It is not possible to consume more units than available.
    /// @param requiredUnits Units of the resource required.
    /// @return Effective number if units consumed.
    virtual unsigned int consume(const unsigned int requiredUnits) = 0;

    /// @brief Regenerates the number of units of the resource.
    virtual void regenerate() = 0;

    /// @brief Get the representation of an infinity number of units.
    /// @return Infinity number of units.
    static constexpr unsigned int INFINITY_UNITS{std::numeric_limits<unsigned int>::max()};

  protected:

    /// @brief Set the number of units of the resource.
    /// @param unitCount Number of units to be set.
    void setUnitCount(unsigned int unitCount);

  private:

    std::string _resourceId;

    unsigned int _unitCount;
};

}

#endif
