/// @file Individual.cpp Implementation of the Individual class.

#include "fictional-fiesta/world/itf/Individual.h"

namespace fictionalfiesta
{

Individual::Fenotype::Fenotype(double initialEnergy):
  _energy(initialEnergy)
{
}

double Individual::Fenotype::getEnergy() const
{
  return _energy;
}

void Individual::Fenotype::feed(unsigned int resourceUnits, const Genotype& genotype)
{
  // Currently the fenotype is just energy, so we just increase it in the same ammount than the
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

bool Individual::Genotype::willReproduce(const Individual::Fenotype& fenotype) const
{
  if (fenotype.getEnergy() > _reproductionEnergyThreshold)
  {
    // Temporarily, we avoid the random draw.
    return true;
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
  _fenotype(initialEnergy)
{
}

} // namespace fictionalfiesta
