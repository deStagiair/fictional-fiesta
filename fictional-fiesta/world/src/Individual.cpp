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

Individual::Genotype Individual::Genotype::reproduce() const
{
  // Temporarily, we avoid the random draw.
  return *this;
}

bool Individual::Genotype::producedDeadlyMutation() const
{
  // Temporarily, we avoid the random draw.
  return false;
}

Individual::Individual(const Genotype& genotype, double initialEnergy):
  _genotype(genotype),
  _phenotype(initialEnergy)
{
}

} // namespace fictionalfiesta
