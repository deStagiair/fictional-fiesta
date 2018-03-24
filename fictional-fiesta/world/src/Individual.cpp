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

bool Individual::willReproduce(FSM::Rng &rng) const
{
  return _genotype.willReproduce(_phenotype, rng);
}

void Individual::die() noexcept
{
  _isDead = true;
}

bool Individual::isDead() const noexcept
{
  return _isDead;
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
