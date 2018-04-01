/// @file Location.cpp Implementation of the Location class.

#include "fictional-fiesta/world/itf/Location.h"


#include "fictional-fiesta/world/itf/Individual.h"
#include "fictional-fiesta/world/itf/Source.h"
#include "fictional-fiesta/world/itf/SourceFactory.h"

#include "fictional-fiesta/utils/itf/Exception.h"
#include "fictional-fiesta/utils/itf/XmlNode.h"

#include <iostream>

namespace fictionalfiesta
{

Location::Location() = default;

Location::~Location() = default;

Location::Location(const XmlNode& node)
{
  const auto& source_nodes = node.getChildNodes(Source::XML_MAIN_NODE_NAME);
  for (const auto& source_node : source_nodes)
  {
    _sources.push_back(SourceFactory::createSource(source_node));
  }
}

void Location::save(XmlNode& node) const
{
  for (const auto& source : _sources)
  {
    source->save(node.appendChildNode(Source::XML_MAIN_NODE_NAME));
  }
}

const std::vector<Individual>& Location::getIndividuals() const
{
  return _individuals;
}

static unsigned int draw_resource_unit(
    const std::vector<double>& weights,
    FSM::Rng& rng)
{
  std::discrete_distribution<unsigned int> distribution(weights.begin(), weights.end());

  return distribution(rng);
}

static bool die_during_feed(
    const Individual& individual,
    FSM::Rng& rng)
{
  return std::bernoulli_distribution(0.01)(rng);
}

void Location::splitResources(FSM::Rng& rng)
{
  // Currently, all the individuals compete for all the resources.
  // TODO: Add resource preference in the individual genotype.
  // Assume by now that there is only a resource type.

  for (auto& source : _sources)
  {
    while (!source->empty())
    {

      std::vector<double> weights;
      double total_weight = 0;
      for (const auto& individual : _individuals)
      {
        const auto& weight = (individual.isDead() && individual.isHungry()) ?
          0 : individual.getPhenotype().getEnergy();
        weights.push_back(weight);
        total_weight += weight;
      }

      if (total_weight == 0)
      {
        break;
      }

      const auto individual_index = draw_resource_unit(weights, rng);
      auto& winner = _individuals[individual_index];
      winner.feed(1);

      source->consume(1);

      std::cout << "Feed " << individual_index << std::endl;
      if (die_during_feed(winner, rng))
      {
        winner.die();
        std::cout << "Died" << std::endl;
      }
    }
  }
}

void Location::addSource(std::unique_ptr<Source>&& source)
{
  _sources.push_back(std::move(source));
}

void Location::addIndividual(const Individual& individual)
{
  _individuals.push_back(individual);
}

} // namespace fictionalfiesta
