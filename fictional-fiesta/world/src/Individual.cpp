/// @file Individual.cpp Implementation of the Individual class.

#include "fictional-fiesta/world/itf/Individual.h"

#include "fictional-fiesta/utils/itf/XmlNode.h"

#include <sstream>

namespace
{

  constexpr char XML_PHENOTYPE_NODE_NAME[]{"Phenotype"};
  constexpr char XML_GENOTYPE_NODE_NAME[]{"Genotype"};
  constexpr char XML_INDIVIDUAL_NODE_NAME[]{"Individual"};

} // anonymous namespace

namespace fictionalfiesta
{

Individual::Individual(const Genotype& genotype, double initialEnergy):
  _genotype(genotype),
  _phenotype(initialEnergy)
{
}

Individual::Individual(const XmlNode& node):
  _genotype(node.getChildNode(XML_GENOTYPE_NODE_NAME)),
  _phenotype(node.getChildNode(XML_PHENOTYPE_NODE_NAME)),
  _isDead(node.getOptionalAttributeAs("IsDead", false)),
  _resourceCount(node.getOptionalAttributeAs("ResourceCount", 0))
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

Individual& Individual::die() noexcept
{
  _isDead = true;
  return *this;
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

Individual& Individual::feed(unsigned int units)
{
  _resourceCount += units;
  return *this;
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

std::string Individual::str(unsigned int indentLevel) const
{
  std::stringstream result;
  if (isDead())
  {
    result << indent(indentLevel) << "Dead individual\n";
  }

  result <<
      indent(indentLevel) << "Resources: " << _resourceCount << "\n" <<
      _genotype.str(indentLevel) <<
      _phenotype.str(indentLevel);

  return result.str();
}

void Individual::doSave(XmlNode& node) const
{
  _genotype.save(node.appendChildNode("Genotype"));
  _phenotype.save(node.appendChildNode("Phenotype"));
  if (_isDead)
  {
    node.setAttribute("IsDead", true);
  }

  if (_resourceCount)
  {
    node.setAttribute("ResourceCount", _resourceCount);
  }
}

std::string Individual::getDefaultXmlName() const
{
  return XML_INDIVIDUAL_NODE_NAME;
}

bool operator==(const Individual& lhs, const Individual& rhs)
{
  if (lhs._genotype != rhs._genotype)
  {
    return false;
  }

  if (lhs._phenotype != rhs._phenotype)
  {
    return false;
  }

  if (lhs._isDead != rhs._isDead)
  {
    return false;
  }

  if (lhs._resourceCount != rhs._resourceCount)
  {
    return false;
  }

  return true;
}

bool operator!=(const Individual& lhs, const Individual& rhs)
{
  return !(lhs == rhs);
}

} // namespace fictionalfiesta
