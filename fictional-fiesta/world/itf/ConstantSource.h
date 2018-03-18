#ifndef INCLUDE_FICTIONAL_FIESTA_WORLD_CONSTANT_SOURCE_H
#define INCLUDE_FICTIONAL_FIESTA_WORLD_CONSTANT_SOURCE_H

#include "fictional-fiesta/world/itf/Source.h"

#include <string>

namespace fictionalfiesta
{

class XmlNode;

/// @brief Class that represents a constant source whose resource units are always
///   regenerated to the initial value.
class ConstantSource : public Source
{
  public:

    /// @brief Constructor from the resource name and the fixed unit count.
    ///   It assumes that the source starts from the cycle start so it uses the fixed unit count
    ///   as the current number of units.
    /// @param resourceId Resource identifier.
    /// @param fixedUnitCount Number of units of resource at the beggining. Note that it is also
    ///   the number of units that will be available at the start of each cycle.
    ConstantSource(const std::string& resourceId, unsigned int fixedUnitCount);

    /// @brief Constructor from the resource name, the fixed unit count and the current unit count.
    /// @param resourceId Resource identifier.
    /// @param fixedUnitCount Number of units of resource at the beggining. Note that it is also
    ///   the number of units that will be available at the start of each cycle.
    /// @param currentUnitCount Current number of units available.
    ConstantSource(const std::string& resourceId, unsigned int fixedUnitCount,
        unsigned int currentUnitCount);

    /// @brief Constructor from an XmlNode.
    /// @param node XmlNode from where to read the contents of the instance.
    explicit ConstantSource(const XmlNode& node);

    /// @copydoc Source::regenerate
    void regenerate() override;

    /// Name of the node with the fixed unit count.
    static constexpr char XML_FIXED_UNIT_COUNT_NODE_NAME[]{"FixedUnits"};

    /// Value of the type node for Constant sources.
    static constexpr char XML_SOURCE_TYPE_NODE_VALUE[]{"Constant"};

  private:

    void doSave(XmlNode node) override;

    /// Nuber of units at the begining of each cycle.
    unsigned int _fixedUnitCount;
};

}

#endif
