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

void Individual::feed(unsigned int units)
{
  _resourceCount += units;
}

unsigned int Individual::getResourceCount() const
{
  return _resourceCount;
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

void Individual::performMaintenance(FSM::Rng& rng)
{
  // An individual uses at least half its energy in resources just to survive.
  const auto maintenance_cost = _phenotype.getEnergy() / 2;

  // If there are not enough units, the individual might die out of starvation.
  if (_resourceCount < maintenance_cost)
  {
    const auto starvation_probability = 1.0 - (_resourceCount / maintenance_cost);
    if (std::bernoulli_distribution(starvation_probability)(rng))
    {
      die();
    }
    _resourceCount = 0;
  }
  else
  {
    // The units of resource are always consumed as integers.
    _resourceCount -= maintenance_cost;

    // TODO: Currently the individual consumes all the resources.
    _phenotype.feed(_resourceCount, _genotype);
    _resourceCount = 0;
  }
}

} // namespace fictionalfiesta
