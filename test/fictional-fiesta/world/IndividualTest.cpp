#include "catch/catch.hpp"

#include "fictional-fiesta/world/itf/Individual.h"

#include "fictional-fiesta/utils/itf/Exception.h"

using namespace fictionalfiesta;

// Important note: Some of these tests force the seed of the RNG to allow testability.
// Changing the RNG or the order of the statements will probably cause this test to fail.

TEST_CASE("Test individual willReproduce method", "[IndividualTest][TestWillReproduce]")
{
  {
    auto rng{FSM::createRng(0)};

    const Genotype genotype{10, 1, 0.1};

    const auto individual = Individual{genotype, 0};

    // Energy lower than the reproduction threshold (should be always false).
    REQUIRE(!individual.willReproduce(rng));
    REQUIRE(!individual.willReproduce(rng));
    REQUIRE(!individual.willReproduce(rng));
  }

  {
    auto rng{FSM::createRng(1)};

    const Genotype genotype{10, 1, 0.1};

    const auto individual = Individual{genotype, 10};

    // Energy greater or equal than the reproduction threshold and probability 1
    // (should be always true).
    REQUIRE(individual.willReproduce(rng));
    REQUIRE(individual.willReproduce(rng));
    REQUIRE(individual.willReproduce(rng));
    REQUIRE(individual.willReproduce(rng));
  }

  {
    auto rng{FSM::createRng(2)};

    const Genotype genotype{10, 0.5, 0.1};

    const auto individual = Individual{genotype, 11};

    // Energy greater or equal than the reproduction threshold and probability 0.5
    // (some true, some false).
    REQUIRE(individual.willReproduce(rng));
    REQUIRE(!individual.willReproduce(rng));
    REQUIRE(!individual.willReproduce(rng));
    REQUIRE(individual.willReproduce(rng));
  }
}
