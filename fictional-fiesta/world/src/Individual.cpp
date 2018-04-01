/// @file Individual.cpp Implementation of the Individual class.

#include "fictional-fiesta/world/itf/Individual.h"

namespace fictionalfiesta
{

Individual::Individual(const Genotype& genotype, double initialEnergy):
  _genotype(genotype),
  _phenotype(initialEnergy)
{
}

const Genotype& Individual::getGenotype() const
{
  return _genotype;
}

const Phenotype& Individual::getPhenotype() const
{
  return _phenotype;
}

bool Individual::willReproduce(FSM::Rng &rng) const
{
  return !isDead() && _genotype.willReproduce(_phenotype, rng);
}

void Individual::die() noexcept
{
  _isDead = true;
}

bool Individual::isDead() const noexcept
{
  return _isDead;
}

bool Individual::isHungry() const
{
  // Temporary implementation, it should be influenced by the genotype and the phenotype.
  return true;
}

void Individual::feed(unsigned int units) const
{
}

Individual Individual::reproduce(FSM::Rng& rng)
{
  const auto& new_genotype = _genotype.reproduce(rng);
  const auto& new_phenotype = _phenotype.split(_genotype);

  auto offspring = Individual(new_genotype, new_phenotype.getEnergy());
  if (_genotype.producedDeadlyMutation(rng))
  {
    offspring.die();
  }
  return offspring;
}

} // namespace fictionalfiesta
