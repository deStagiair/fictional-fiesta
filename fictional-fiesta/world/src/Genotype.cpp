/// @file Genotype.cpp Implementation of the Genotype class.

#include "fictional-fiesta/world/itf/Genotype.h"

#include "fictional-fiesta/world/itf/Phenotype.h"

#include "fictional-fiesta/utils/itf/XmlNode.h"

#include <sstream>

namespace fictionalfiesta
{

namespace
{

double normalized_distance(const double first, const double second);

constexpr char XML_REPRODUCTION_ENERGY_THRESHOLD_NAME[]{"ReproductionEnergyThreshold"};
constexpr char XML_REPRODUCTION_PROBABILITY_NAME[]{"ReproductionProbability"};
constexpr char XML_MUTABILITY_RATIO_NAME[]{"MutabilityRatio"};
constexpr char XML_GENOTYPE_NODE_NAME[]{"Genotype"};

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

Genotype::Genotype(const XmlNode& node):
  _reproductionEnergyThreshold(
      node.getChildNodeTextAs<double>(XML_REPRODUCTION_ENERGY_THRESHOLD_NAME)),
  _reproductionProbability(node.getChildNodeTextAs<double>(XML_REPRODUCTION_PROBABILITY_NAME)),
  _mutabilityRatio(node.getChildNodeTextAs<double>(XML_MUTABILITY_RATIO_NAME))
{
}

void Genotype::doSave(XmlNode& node) const
{
  auto reproduction_threshold_node = node.appendChildNode(XML_REPRODUCTION_ENERGY_THRESHOLD_NAME);
  reproduction_threshold_node.setText(_reproductionEnergyThreshold);

  auto reproduction_probability_node = node.appendChildNode(XML_REPRODUCTION_PROBABILITY_NAME);
  reproduction_probability_node.setText(_reproductionProbability);

  auto mutability_ratio_node = node.appendChildNode(XML_MUTABILITY_RATIO_NAME);
  mutability_ratio_node.setText(_mutabilityRatio);
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

std::string Genotype::str(unsigned int indentLevel) const
{
  std::stringstream result;
  result <<
      indent(indentLevel) << "Reproduction threshold: " << _reproductionEnergyThreshold << "\n" <<
      indent(indentLevel) << "Reproduction probability: " << _reproductionProbability << "\n" <<
      indent(indentLevel) << "Mutability: " << _mutabilityRatio << "\n";

  return result.str();
}

Genotype Genotype::average(const std::vector<Genotype>& genotypes)
{
  double acum_repr_threshold = 0.0;
  double acum_repr_probability = 0.0;
  double acum_mutability = 0.0;
  for (const auto& genotype : genotypes)
  {
    acum_repr_threshold += genotype.getReproductionEnergyThreshold();
    acum_repr_probability += genotype.getReproductionProbability();
    acum_mutability += genotype.getMutabilityRatio();
  }

  const auto size = genotypes.size();
  return Genotype(acum_repr_threshold / size,
      acum_repr_probability / size,
      acum_mutability / size);
}

std::string Genotype::getDefaultXmlName() const
{
  return XML_GENOTYPE_NODE_NAME;
}

bool operator==(const Genotype& lhs, const Genotype& rhs)
{
  if (lhs._reproductionEnergyThreshold != rhs._reproductionEnergyThreshold)
  {
    return false;
  }

  if (lhs._reproductionProbability != rhs._reproductionProbability)
  {
    return false;
  }

  if (lhs._mutabilityRatio != rhs._mutabilityRatio)
  {
    return false;
  }

  return true;
}

bool operator!=(const Genotype& lhs, const Genotype& rhs)
{
  return !(lhs == rhs);
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
