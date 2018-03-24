/// @file Individual.cpp Implementation of the Individual class.

#include "fictional-fiesta/world/itf/Individual.h"

namespace fictionalfiesta
{

Individual::Phenotype::Phenotype(double initialEnergy):
  _energy(initialEnergy)
{
}

double Individual::Phenotype::getEnergy() const
{
  return _energy;
}

void Individual::Phenotype::feed(unsigned int resourceUnits, const Genotype& genotype)
{
  // Currently the phenotype is just energy, so we just increase it in the same ammount than the
  // resource units aquired.
  _energy += resourceUnits;
}

Individual::Phenotype Individual::Phenotype::split(const Genotype& genotype)
{
  _energy *= 0.5;
  return Phenotype{_energy};
}

Individual::Genotype::Genotype(
    double reproductionEnergyThreshold,
    double reproductionProbability,
    double mutabilityRatio):
  _reproductionEnergyThreshold(reproductionEnergyThreshold),
  _reproductionProbability(reproductionProbability),
  _mutabilityRatio(mutabilityRatio)
{
}

double Individual::Genotype::getReproductionEnergyThreshold() const
{
  return _reproductionEnergyThreshold;
}

double Individual::Genotype::getReproductionProbability() const
{
  return _reproductionProbability;
}

double Individual::Genotype::getMutabilityRatio() const
{
  return _mutabilityRatio;
}

bool Individual::Genotype::willReproduce(
    const Individual::Phenotype& phenotype,
    FSM::Rng& rng) const
{
  if (phenotype.getEnergy() >= _reproductionEnergyThreshold)
  {
    return std::bernoulli_distribution(_reproductionProbability)(rng);
  }
  return false;
}

Individual::Genotype Individual::Genotype::reproduce(FSM::Rng& rng) const
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

bool Individual::Genotype::producedDeadlyMutation(FSM::Rng& rng) const
{
  return std::bernoulli_distribution(_mutabilityRatio)(rng);
}

Individual::Individual(const Genotype& genotype, double initialEnergy):
  _genotype(genotype),
  _phenotype(initialEnergy)
{
}

bool Individual::willReproduce(FSM::Rng &rng) const
{
  return _genotype.willReproduce(_phenotype, rng);
}

} // namespace fictionalfiesta
