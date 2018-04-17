#ifndef INCLUDE_FICTIONAL_FIESTA_WORLD_GENOTYPE_H
#define INCLUDE_FICTIONAL_FIESTA_WORLD_GENOTYPE_H

#include "fictional-fiesta/utils/itf/Descriptable.h"
#include "fictional-fiesta/utils/itf/Xmlable.h"

#include "fictional-fiesta/world/itf/FSM.h"

namespace fictionalfiesta
{

class Phenotype;
class XmlNode;

/// @brief Class that represents the set of features that are inherited by individuals.
class Genotype : public Descriptable, public Xmlable
{
  public:

    /// @brief Construction from members.
    /// @param reproductionEnergyThreshold Ammount of energy required to be able to reproduce.
    /// @param reproductionProbability Probability of reproducing (once the individual energy
    ///     is above the reproduction threshold.
    /// @param mutabilityRatio Ratio in which the individual features change upon reproduction.
    Genotype(
        double reproductionEnergyThreshold,
        double reproductionProbability,
        double mutabilityRatio);

    /// @brief Construction from an XmlNode.
    /// @param node XML node from which the genotype will be loaded.
    Genotype(const XmlNode& node);

    /// @brief Get the reproduction energy threshold.
    /// @return Reproduction energy threshold.
    double getReproductionEnergyThreshold() const;

    /// @brief Get the reproduction probability.
    /// @return Reproduction probability.
    double getReproductionProbability() const;

    /// @brief Get the mutability ratio.
    /// @return Mutability ratio.
    double getMutabilityRatio() const;

    /// @brief Determines whether a given individual with the passed phenotype and the current
    ///     genotype will reproduce or not.
    /// @note This is a probabilistic method that depends, among others, on the reproduction
    ///     probability.
    /// @param phenotype Phenotype of the individual.
    /// @param rng Random number generator.
    /// @return @c true if the individual is going to reproduce and @c false if not.
    bool willReproduce(const Phenotype& phenotype, FSM::Rng &rng) const;

    /// @brief Obtains a new (mutated) genotype from the current one.
    /// @param rng Random number generator.
    /// @return New mutated genotype.
    Genotype reproduce(FSM::Rng& rng) const;

    /// @brief Determines whether the current genotype produced a deadly mutation upon
    ///     reproduction or not.
    /// @details The probability of deadly mutations depends on several factors, like for
    ///     example, the mutability ratio or the complexity of the genotype.
    /// @param rng Random number generator.
    /// @return @c true if there was a deadly mutation upon reproduction and @c false
    ///     otherwise.
    bool producedDeadlyMutation(FSM::Rng& rng) const;

    /// @brief Determines the distance between the current Genotype and another one.
    /// @details The distance between two genotypes @e A and @e B is defined by
    ///   @f[
    ///       \frac{2}{|G|}\sum_{g\in G}\frac{|A_g-B_g|}{A_g+B_g}
    ///   @f]
    ///     where @e G is the set of features in a Genotype.
    /// @param other Genotype with which to compute the distance.
    /// @return Distance between both genotypes.
    double distance(const Genotype& other) const;

    /// @copydoc Descriptable::str
    virtual std::string str(unsigned int indentLevel) const override;

    /// @brief Computes the average of several genotypes.
    /// @param genotypes Genotypes from which to compute the average.
    /// @return Average genotype.
    static Genotype average(const std::vector<Genotype>& genotypes);

    friend bool operator==(const Genotype& lhs, const Genotype& rhs);

  private:

    /// @copydoc Xmlable::doLoad
    virtual void doLoad(const XmlNode& node) override;

    /// @copydoc Xmlable::doSave
    virtual void doSave(XmlNode& node) const override;

    /// @copydoc Xmlable::getDefaultXmlName
    virtual std::string getDefaultXmlName() const override;

    /// Ammount of energy required to be able to reproduce.
    double _reproductionEnergyThreshold;

    /// Probability of reproducing (when the individual is above the
    /// reproduction energy threshold.
    double _reproductionProbability;

    /// Mutability ratio that influences how fast the features change upon reproduction.
    double _mutabilityRatio;
};

/// @brief Genotype equality comparison.
/// @param lhs Left hand side operand.
/// @param rhs Right hand side operand.
/// @return @e true if the two operands are exactly equal and @e false if not.
bool operator==(const Genotype& lhs, const Genotype& rhs);

/// @brief Genotype inequality comparison.
/// @param lhs Left hand side operand.
/// @param rhs Right hand side operand.
/// @return @e false if the two operands are exactly equal and @e true if not.
bool operator!=(const Genotype& lhs, const Genotype& rhs);

} // namespace fictionalfiesta

#endif
