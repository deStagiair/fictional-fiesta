#ifndef INCLUDE_FICTIONAL_FIESTA_WORLD_INDIVIDUAL_H
#define INCLUDE_FICTIONAL_FIESTA_WORLD_INDIVIDUAL_H

#include "fictional-fiesta/world/itf/FSM.h"

namespace fictionalfiesta
{

/// @brief Class that represents an individual.
class Individual
{
  public:

    class Genotype;

    /// @brief Class that represents the set of features that are the expression of the genotype
    ///     in an individual.
    class Phenotype
    {
      public:

        /// @brief Constructor from the energy.
        /// @param initialEnergy Initial energy of the phenotype.
        explicit Phenotype(double initialEnergy);

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

      private:

        /// Energy level of the individual.
        double _energy;
    };

    /// @brief Class that represents the set of features that are inherited by individuals.
    class Genotype
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

        /// @brief Get the reproduction energy threshold.
        /// @return Reproduction energy threshold.
        double getReproductionEnergyThreshold() const;

        /// @brief Get the reproduction probability.
        /// @return Reproduction probability.
        double getReproductionProbability() const;

        /// @brief Get the mutability ratio.
        /// @return Mutability ration.
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

      private:

        /// Ammount of energy required to be able to reproduce.
        const double _reproductionEnergyThreshold;

        /// Probability of reproducing (when the individual is above the
        /// reproduction energy threshold.
        const double _reproductionProbability;

        /// Mutability ratio that influences how fast the features change upon reproduction.
        const double _mutabilityRatio;
    };

    /// @brief Constructor from the genotype and initial energy.
    /// @param genotype Genotype of the new individual.
    /// @param initialEnergy Inital energy of the new individual.
    Individual(const Genotype& genotype, double initialEnergy);

  private:

    /// Genotype of the individual (inherited features).
    const Genotype _genotype;

    /// Phenotype of the individual (expression of the genotype).
    Phenotype _phenotype;
};

} // namespace fictionalfiesta

#endif
