/// @file Genotype.cpp Implementation of the Genotype class.

#include "fictional-fiesta/world/itf/Genotype.h"

#include "fictional-fiesta/world/itf/Phenotype.h"

#include <iostream>

namespace fictionalfiesta
{

namespace
{

double normalized_distance(const double first, const double second);

} // anonymous namespace

Genotype::Genotype(
    double reproductionEnergyThreshold,
    double reproductionProbability,
    double mutabilityRatio):
  _reproductionEnergyThreshold(reproductionEnergyThreshold),
  _reproductionProbability(reproductionProbability),
  _mutabilityRatio(mutabilityRatio)
{
}

double Genotype::getReproductionEnergyThreshold() const
{
  return _reproductionEnergyThreshold;
}

double Genotype::getReproductionProbability() const
{
  return _reproductionProbability;
}

double Genotype::getMutabilityRatio() const
{
  return _mutabilityRatio;
}

bool Genotype::willReproduce(const Phenotype& phenotype, FSM::Rng& rng) const
{
  if (phenotype.getEnergy() >= _reproductionEnergyThreshold)
  {
    return std::bernoulli_distribution(_reproductionProbability)(rng);
  }
  return false;
}

Genotype Genotype::reproduce(FSM::Rng& rng) const
{
  // The genotype features change accordingly to a normal distribution with mean,
  // the original value and standard deviation, the mutability ratio.
  const auto reproduction_energy_threshold =
      std::normal_distribution(_reproductionEnergyThreshold,
      _mutabilityRatio * _reproductionEnergyThreshold)(rng);
  const auto reproduction_probability =
      std::normal_distribution(_reproductionProbability,
      _mutabilityRatio * _reproductionProbability)(rng);
  const auto mutabilityRatio = std::normal_distribution(_mutabilityRatio,
      _mutabilityRatio * _mutabilityRatio)(rng);

  return Genotype{reproduction_energy_threshold, reproduction_probability, mutabilityRatio};
}

bool Genotype::producedDeadlyMutation(FSM::Rng& rng) const
{
  return std::bernoulli_distribution(_mutabilityRatio)(rng);
}

double Genotype::distance(const Genotype& other) const
{
  const unsigned int feature_number = 3;

  const double ret_dist =
      normalized_distance(_reproductionEnergyThreshold, other._reproductionEnergyThreshold);

  const double rp_dist =
      normalized_distance(_reproductionProbability, other._reproductionProbability);

  const double mut_dist = normalized_distance(_mutabilityRatio, other._mutabilityRatio);

  return (ret_dist + rp_dist + mut_dist) / feature_number;
}

namespace
{

double normalized_distance(const double first, const double second)
{
  if (first == second)
  {
    return 0;
  }

  // This assumes that both first and second non-negative numbers.
  return 2 * std::abs(first - second) / (first + second);
}

} // anonymous namespace

} // namespace fictionalfiesta
