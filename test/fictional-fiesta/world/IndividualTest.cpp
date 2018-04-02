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
    CHECK(!individual.willReproduce(rng));
    CHECK(!individual.willReproduce(rng));
    CHECK(!individual.willReproduce(rng));
  }

  {
    auto rng{FSM::createRng(1)};

    const Genotype genotype{10, 1, 0.1};

    const auto individual = Individual{genotype, 10};

    // Energy greater or equal than the reproduction threshold and probability 1
    // (should be always true).
    CHECK(individual.willReproduce(rng));
    CHECK(individual.willReproduce(rng));
    CHECK(individual.willReproduce(rng));
    CHECK(individual.willReproduce(rng));
  }

  {
    auto rng{FSM::createRng(2)};

    const Genotype genotype{10, 0.5, 0.1};

    const auto individual = Individual{genotype, 11};

    // Energy greater or equal than the reproduction threshold and probability 0.5
    // (some true, some false).
    CHECK(individual.willReproduce(rng));
    CHECK(!individual.willReproduce(rng));
    CHECK(!individual.willReproduce(rng));
    CHECK(individual.willReproduce(rng));
  }
}

TEST_CASE("Test individual die and isDead methods", "[IndividualTest][TestDie]")
{
  const Genotype genotype{10, 0.5, 0.1};

  // An individual is not dead until it dies.
  auto dude = Individual{genotype, 0.3};
  REQUIRE(!dude.isDead());

  dude.die();
  REQUIRE(dude.isDead());
}

TEST_CASE("Test individual reproduce method", "[IndividualTest][TestReproduce]")
{
  {
    auto rng{FSM::createRng(0)};

    // Mutability = 0: no change and always alive offspring.
    const Genotype genotype{10, 0.5, 0};

    auto parent = Individual{genotype, 30};

    auto offspring = parent.reproduce(rng);

    // Distance between genotypes must be 0.
    CHECK(parent.getGenotype().distance(offspring.getGenotype()) == 0);

    CHECK(!offspring.isDead());
    CHECK(!parent.reproduce(rng).isDead());
    CHECK(!parent.reproduce(rng).isDead());
  }
  {
    auto rng{FSM::createRng(1)};

    // Mutability = 1: change and always dead offspring.
    const Genotype genotype{10, 0.5, 1};

    auto parent = Individual{genotype, 30};

    auto offspring = parent.reproduce(rng);

    // The distance could be 0, but the probability that that happens is quite small.
    CHECK(parent.getGenotype().distance(offspring.getGenotype()) != 0);

    CHECK(offspring.isDead());
    CHECK(parent.reproduce(rng).isDead());
    CHECK(parent.reproduce(rng).isDead());
  }
}

TEST_CASE("Test individual maintenance", "[IndividualTest][TestPerformMaintenanace]")
{
  {
    auto rng{FSM::createRng(0)};

    // Mutability = 0: no change and always alive offspring.
    const Genotype genotype{10, 0.5, 0};

    auto dude = Individual{genotype, 10};

    dude.feed(20);

    CHECK(dude.getResourceCount() == 20);

    dude.performMaintenance(rng);

    CHECK(dude.getResourceCount() == 0);
    CHECK(dude.getPhenotype().getEnergy() == 25);

    // Not enough resources. The dude could die (improbable in this case) but it won't grow.
    dude.feed(12);
    dude.performMaintenance(rng);

    CHECK(dude.getResourceCount() == 0);
    CHECK(dude.getPhenotype().getEnergy() == 25);

    // No resources. The dude will die.
    REQUIRE(!dude.isDead());
    dude.performMaintenance(rng);

    CHECK(dude.getResourceCount() == 0);
    CHECK(dude.getPhenotype().getEnergy() == 25);
    CHECK(dude.isDead());
  }
}
