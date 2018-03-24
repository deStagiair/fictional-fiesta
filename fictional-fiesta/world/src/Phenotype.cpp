/// @file Phenotype.cpp Implementation of the Phenotype class.

#include "fictional-fiesta/world/itf/Phenotype.h"

namespace fictionalfiesta
{

Phenotype::Phenotype(double initialEnergy):
  _energy(initialEnergy)
{
}

double Phenotype::getEnergy() const
{
  return _energy;
}

void Phenotype::feed(unsigned int resourceUnits, const Genotype& genotype)
{
  // Currently the phenotype is just energy, so we just increase it in the same ammount than the
  // resource units aquired.
  _energy += resourceUnits;
}

Phenotype Phenotype::split(const Genotype& genotype)
{
  _energy *= 0.5;
  return Phenotype{_energy};
}

} // namespace fictionalfiesta
