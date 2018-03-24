#ifndef INCLUDE_FICTIONAL_FIESTA_WORLD_FSM_H
#define INCLUDE_FICTIONAL_FIESTA_WORLD_FSM_H

#include <random>

namespace fictionalfiesta
{

/// @brief @e He @e who @e created @e all @e that @e we @e see @e and @e all @e that @e we @e feel.
/// @details No, seriously, a static class that abstracts the random number generator used and
///   can create new generators (noodly appendages) with or without seed.
class FSM
{
  public:

    /// Abstraction for the random number generator type.
    using Rng = std::mt19937;

    /// @brief Creates a random number generator (rng) with a (pseudo) random seed.
    /// @return Random number generator with a random seed.
    static Rng createRng();

    /// @brief Creates a random number generator (rng) with a given seed.
    /// @param seed Seed of the random number generator.
    /// @return Random number generator with a given seed.
    static Rng createRng(unsigned int seed);

};

} // namespace fictionalfiesta

#endif
