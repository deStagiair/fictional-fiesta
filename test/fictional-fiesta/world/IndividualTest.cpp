#include "catch/catch.hpp"

#include "fictional-fiesta/world/itf/Individual.h"

#include "fictional-fiesta/utils/itf/Exception.h"

using namespace fictionalfiesta;

// Important note: Some of these tests force the seed of the RNG to allow testability.
// Changing the RNG or the order of the statements will probably cause this test to fail.

TEST_CASE("Test phenotype constructor and getters", "[IndividualTest][TestPhenotypeConstructor]")
{
  {
    const auto phenotype = Phenotype{16.1};
    CHECK(phenotype.getEnergy() == 16.1);
  }

  {
    const auto phenotype = Phenotype{0};
    CHECK(phenotype.getEnergy() == 0);
  }
}

TEST_CASE("Test phenotype feed method", "[IndividualTest][TestPhenotypeFeed]")
{
  {
    const auto genotype = Genotype{0, 0, 0};
    auto phenotype = Phenotype{16.1};
    CHECK(phenotype.getEnergy() == 16.1);
    phenotype.feed(1, genotype);
    CHECK(phenotype.getEnergy() == 17.1);
    phenotype.feed(0, genotype);
    CHECK(phenotype.getEnergy() == 17.1);
    phenotype.feed(30, genotype);
    CHECK(phenotype.getEnergy() == 47.1);
  }
}

TEST_CASE("Test phenotype split method", "[IndividualTest][TestPhenotypeSplit]")
{
  {
    const auto genotype = Genotype{0, 0, 0};
    auto phenotype = Phenotype{16.1};

    const auto splitted_0 = phenotype.split(genotype);
    CHECK(phenotype.getEnergy() == 8.05);
    CHECK(splitted_0.getEnergy() == 8.05);

    const auto splitted_1 = phenotype.split(genotype);
    CHECK(phenotype.getEnergy() == 4.025);
    CHECK(splitted_1.getEnergy() == 4.025);
  }
}

TEST_CASE("Test genotype constructor and getters", "[IndividualTest][TestGenotypeConstructor]")
{
  {
    const Genotype genotype{43, 0.5, 0.66};
    REQUIRE(genotype.getReproductionEnergyThreshold() == 43);
    REQUIRE(genotype.getReproductionProbability() == 0.5);
    REQUIRE(genotype.getMutabilityRatio() == 0.66);
  }

  {
    const Genotype genotype{0, 0.001, 0};
    REQUIRE(genotype.getReproductionEnergyThreshold() == 0);
    REQUIRE(genotype.getReproductionProbability() == 0.001);
    REQUIRE(genotype.getMutabilityRatio() == 0);
  }
}

TEST_CASE("Test genotype willReproduce method", "[IndividualTest][TestWillReproduce]")
{
  {
    auto rng{FSM::createRng(0)};

    const Genotype genotype{10, 1, 0.1};

    // Energy lower than the reproduction threshold (should be always false).
    REQUIRE(!genotype.willReproduce(Phenotype{5}, rng));
    REQUIRE(!genotype.willReproduce(Phenotype{9.99}, rng));
    REQUIRE(!genotype.willReproduce(Phenotype{0}, rng));
  }

  {
    auto rng{FSM::createRng(1)};

    const Genotype genotype{10, 1, 0.1};

    // Energy greater or equal than the reproduction threshold and probability 1
    // (should be always true).
    REQUIRE(genotype.willReproduce(Phenotype{10}, rng));
    REQUIRE(genotype.willReproduce(Phenotype{10}, rng));
    REQUIRE(genotype.willReproduce(Phenotype{10.1}, rng));
    REQUIRE(genotype.willReproduce(Phenotype{10}, rng));
  }

  {
    auto rng{FSM::createRng(2)};

    const Genotype genotype{10, 0.5, 0.1};

    // Energy greater or equal than the reproduction threshold and probability 0.5
    // (some true, some false).
    REQUIRE(genotype.willReproduce(Phenotype{10}, rng));
    REQUIRE(!genotype.willReproduce(Phenotype{10}, rng));
    REQUIRE(!genotype.willReproduce(Phenotype{10.1}, rng));
    REQUIRE(genotype.willReproduce(Phenotype{10}, rng));
  }
}

TEST_CASE("Test genotype reproduce method", "[IndividualTest][TestReproduce]")
{
  {
    auto rng{FSM::createRng(0)};

    const Genotype genotype{10, 1, 0};

    const Genotype mutated{genotype.reproduce(rng)};

    // No changes (mutabilityRatio = 0).
    CHECK(mutated.getReproductionEnergyThreshold() == genotype.getReproductionEnergyThreshold());
    CHECK(mutated.getReproductionProbability() == genotype.getReproductionProbability());
    CHECK(mutated.getMutabilityRatio() == genotype.getMutabilityRatio());
  }

  {
    auto rng{FSM::createRng(1)};

    const Genotype genotype{10, 1, 0.1};

    const Genotype mutated{genotype.reproduce(rng)};

    // Small variation.
    CHECK(mutated.getReproductionEnergyThreshold() == Approx(9.450253821));
    CHECK(mutated.getReproductionProbability() == Approx(1.1582752292));
    CHECK(mutated.getMutabilityRatio() == Approx(0.1025759354));
  }

  {
    auto rng{FSM::createRng(2)};

    const Genotype genotype{10, 1, 0.9};

    const Genotype mutated{genotype.reproduce(rng)};

    // Big variation.
    CHECK(mutated.getReproductionEnergyThreshold() == Approx(9.7969172834));
    CHECK(mutated.getReproductionProbability() == Approx(0.2012590006));
    CHECK(mutated.getMutabilityRatio() == Approx(0.3379887966));
  }
}

TEST_CASE("Test genotype producedDeadlyMutation method", "[IndividualTest][TestProducedDeadlyMutation]")
{
  {
    auto rng{FSM::createRng(0)};

    const Genotype genotype{10, 1, 1};

    // Always produce (mutabilityRatio = 1).
    CHECK(genotype.producedDeadlyMutation(rng));
    CHECK(genotype.producedDeadlyMutation(rng));
    CHECK(genotype.producedDeadlyMutation(rng));
  }
  {
    auto rng{FSM::createRng(1)};

    const Genotype genotype{10, 1, 0};

    // Never produce (mutabilityRatio = 0).
    CHECK(!genotype.producedDeadlyMutation(rng));
    CHECK(!genotype.producedDeadlyMutation(rng));
    CHECK(!genotype.producedDeadlyMutation(rng));
  }
  {
    auto rng{FSM::createRng(2)};

    const Genotype genotype{10, 1, 0.5};

    // Sometimes produce.
    CHECK(genotype.producedDeadlyMutation(rng));
    CHECK(!genotype.producedDeadlyMutation(rng));
    CHECK(!genotype.producedDeadlyMutation(rng));
  }
}

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
