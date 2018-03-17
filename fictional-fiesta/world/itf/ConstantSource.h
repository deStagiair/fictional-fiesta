#ifndef INCLUDE_FICTIONAL_FIESTA_WORLD_CONSTANT_SOURCE_H
#define INCLUDE_FICTIONAL_FIESTA_WORLD_CONSTANT_SOURCE_H

#include "fictional-fiesta/world/itf/Source.h"

#include <string>

namespace fictionalfiesta
{

/// @brief Class that represents a constant source whose resource units are never consumed.
class ConstantSource : public Source
{
  public:

    /// @brief Constructor from the resource name.
    /// @param resourceId Resource identifier.
    ConstantSource(const std::string& resourceId);

    /// @copydoc Source::consume
    unsigned int consume(const unsigned int requiredUnits) override;
};

}

#endif
