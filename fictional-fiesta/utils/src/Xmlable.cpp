/// @file Xmlable.cpp Implementation of the Xmlable interface.

#include "fictional-fiesta/world/itf/Genotype.h"

#include "fictional-fiesta/world/itf/Phenotype.h"

#include "fictional-fiesta/utils/itf/XmlNode.h"

namespace fictionalfiesta
{

void Xmlable::save(XmlNode node) const
{
  doSave(node);
}

}
