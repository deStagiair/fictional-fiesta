/// @file Individual.cpp Implementation of the Individual class.

#include "fictional-fiesta/world/itf/Individual.h"

namespace fictionalfiesta
{

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
