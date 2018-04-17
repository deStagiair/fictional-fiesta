#ifndef INCLUDE_FICTIONAL_FIESTA_WORLD_PHENOTYPE_H
#define INCLUDE_FICTIONAL_FIESTA_WORLD_PHENOTYPE_H

#include "fictional-fiesta/utils/itf/Descriptable.h"
#include "fictional-fiesta/utils/itf/Xmlable.h"

#include "fictional-fiesta/world/itf/FSM.h"

namespace fictionalfiesta
{


class Genotype;
class XmlNode;

/// @brief Class that represents the set of features that are the expression of the genotype
///     in an individual.
class Phenotype : public Descriptable, public Xmlable
{
  public:

    /// @brief Constructor from the energy.
    /// @param initialEnergy Initial energy of the phenotype.
    explicit Phenotype(double initialEnergy);

    /// @brief Constructor from a XmlNode.
    /// @param node XML node from which to construct the Phenotype.
    explicit Phenotype(const XmlNode& node);

    /// @brief Gets the current energy level.
    /// @return Current energy level.
    double getEnergy() const;

    /// @brief Feed the phenotype with a given number of resource units.
    /// @details The phenotype will change depending on the units fed and the genotype.
    /// @param resourceUnits Unnits fet to the individual.
    /// @param genotype Genotype of the individual.
    void feed(unsigned int resourceUnits, const Genotype& genotype);

    /// @brief Splits the current Phenotype in two parts.
    /// @details Currently, the splitting is done in two equal parts and without energy loss.
    /// @todo Use more complex splitting strategies depending on the genotype.
    /// @param genotype Genotype of the individual.
    /// @return Phenotype that gets splitted from the current one.
    Phenotype split(const Genotype& genotype);

    /// @copydoc Descriptable::str
    virtual std::string str(unsigned int indentLevel) const override;

    friend bool operator==(const Phenotype& lhs, const Phenotype& rhs);

  private:

    /// @copydoc Xmlable::doLoad
    virtual void doLoad(const XmlNode& node) override;

    /// @copydoc Xmlable::doSave
    void doSave(XmlNode& node) const override;

    /// @copydoc Xmlable::getDefaultXmlName
    std::string getDefaultXmlName() const override;

    /// Energy level of the individual.
    double _energy;
};

/// @brief Phenotype equality comparison.
/// @param lhs Left hand side operand.
/// @param rhs Right hand side operand.
/// @return @e true if the two operands are exactly equal and @e false if not.
bool operator==(const Phenotype& lhs, const Phenotype& rhs);

/// @brief Phenotype inequality comparison.
/// @param lhs Left hand side operand.
/// @param rhs Right hand side operand.
/// @return @e false if the two operands are exactly equal and @e true if not.
bool operator!=(const Phenotype& lhs, const Phenotype& rhs);

} // namespace fictionalfiesta

#endif
