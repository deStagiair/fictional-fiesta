#ifndef INCLUDE_FICTIONAL_FIESTA_WORLD_INDIVIDUAL_H
#define INCLUDE_FICTIONAL_FIESTA_WORLD_INDIVIDUAL_H

#include "fictional-fiesta/world/itf/FSM.h"
#include "fictional-fiesta/world/itf/Genotype.h"
#include "fictional-fiesta/world/itf/Phenotype.h"

namespace fictionalfiesta
{

/// @brief Class that represents an individual.
class Individual
{
  public:

    /// @brief Constructor from the genotype and initial energy.
    /// @param genotype Genotype of the new individual.
    /// @param initialEnergy Inital energy of the new individual.
    Individual(const Genotype& genotype, double initialEnergy);

    /// @brief Determines if the individual will reproduce in this cycle or not.
    /// @param rng Random number generator.
    /// @return @c true if the individual is going to reproduce and @c false if not.
    bool willReproduce(FSM::Rng &rng) const;

    /// @brief Kills the current individual.
    void die() noexcept;

    /// @brief Checks whether the current individual is dead or not.
    /// @return @e true if the current individual is dead and @e false if not.
    bool isDead() const noexcept;

    /// @brief The current Individual reproduces producing a new individual.
    /// @note The produced individual could be born dead due to excessive mutations.
    Individual reproduce(FSM::Rng& rng);

  private:

    /// Genotype of the individual (inherited features).
    const Genotype _genotype;

    /// Phenotype of the individual (expression of the genotype).
    Phenotype _phenotype;

    /// Flag indicating if the individual is dead.
    bool _isDead = false;
};

} // namespace fictionalfiesta

#endif
