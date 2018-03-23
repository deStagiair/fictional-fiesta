/// @file FSM.cpp Implementation of the static class that abstracts the random number generators.

#include "fictional-fiesta/world/itf/Individual.h"

namespace fictionalfiesta
{

FSM::Rng FSM::createRng()
{
  std::random_device rd;
  return createRng(rd());
}

FSM::Rng FSM::createRng(unsigned int seed)
{
  return FSM::Rng(seed);
}

} //namespace fictionalfiesta
