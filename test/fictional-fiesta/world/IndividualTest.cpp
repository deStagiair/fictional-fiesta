#include "catch/catch.hpp"

#include "fictional-fiesta/world/itf/Individual.h"

#include "fictional-fiesta/utils/itf/Exception.h"
#include "fictional-fiesta/utils/itf/XmlDocument.h"
#include "fictional-fiesta/utils/itf/XmlNode.h"

#include "test/test_utils/itf/BenchmarkFiles.h"

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;
using namespace fictionalfiesta;
using namespace testutils;

static const fs::path input_directory = fs::path(TEST_SOURCE_DIRECTORY)
    / fs::path("fictional-fiesta/world/input");
static const fs::path result_directory = fs::path(TEST_BINARY_DIRECTORY)
    / fs::path("fictional-fiesta/world/result");
static const fs::path benchmark_directory = fs::path(TEST_SOURCE_DIRECTORY)
    / fs::path("fictional-fiesta/world/benchmark");

// Important note: Some of these tests force the seed of the RNG to allow testability.
// Changing the RNG or the order of the statements will probably cause this test to fail.

TEST_CASE("Test individual stringify method", "[IndividualTest][TestStr]")
{
  {
    const Genotype genotype{10, 1, 0.1};
    const auto individual = Individual{genotype, 0};

    const auto benchmark = "Resources: 0\n"
        "Reproduction threshold: 10\n"
        "Reproduction probability: 1\n"
        "Mutability: 0.1\n"
        "Energy: 0\n";

    CHECK(individual.str(0) == benchmark);
  }
  {
    const Genotype genotype{3, 0.44, 0.5};
    const auto individual = Individual{genotype, 1}.die();

    const auto benchmark = "    Dead individual\n"
        "    Resources: 0\n"
        "    Reproduction threshold: 3\n"
        "    Reproduction probability: 0.44\n"
        "    Mutability: 0.5\n"
        "    Energy: 1\n";

    CHECK(individual.str(2) == benchmark);
  }
}

TEST_CASE("Test individual constructor from XML", "[IndividualTest][TestFromXml]")
{
  const auto& input_file = input_directory / fs::path("individual_0.xml");
  const auto& document = XmlDocument{input_file};
  const auto& root_node = document.getRootNode();

  {
    const auto first = Individual{root_node.getChildNode("First")};
  }
  {
    const auto second = Individual{root_node.getChildNode("Second")};
  }
}

TEST_CASE("Test individual save method", "[IndividualTest][TestSave]")
{
  auto document = XmlDocument{};
  auto root_node = document.appendRootNode("Sources");

  {
    const Genotype genotype{10, 1, 0.1};
    const auto individual = Individual{genotype, 0};

    individual.save(root_node.appendChildNode("First"));
  }
  {
    const Genotype genotype{3, 0.44, 0.5};
    const auto individual = Individual{genotype, 1}.die().feed(140);

    individual.save(root_node.appendChildNode("Second"));
  }

  const auto& result_file = result_directory / fs::path("individual_0.xml");
  REQUIRE_NOTHROW(document.save(result_file));

  const auto& benchmark_file = benchmark_directory / fs::path("individual_0.xml");
  benchmarkFiles(benchmark_file, result_file, result_directory);
}

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

TEST_CASE("Test (in)equality operators for Individual instances", "[IndividualTest][TestEquality]")
{
  const Genotype genotype_0{10, 1, 0.5};
  const Genotype genotype_1{10, 0, 0.5};

  {
    const Individual individual_0{genotype_0, 1};
    CHECK(individual_0 == individual_0);
    CHECK(!(individual_0 != individual_0));

    const Individual individual_1{genotype_0, 1};
    CHECK(individual_0 == individual_1);
    CHECK(!(individual_0 != individual_1));
  }
  {
    const Individual individual_0{genotype_0, 1};
    const Individual individual_1{genotype_1, 1};
    CHECK(!(individual_0 == individual_1));
    CHECK(individual_0 != individual_1);
  }
  {
    const Individual individual_0{genotype_0, 1};
    const Individual individual_1{genotype_0, 0.99};
    CHECK(!(individual_0 == individual_1));
    CHECK(individual_0 != individual_1);
  }
  {
    const auto individual_0 = Individual{genotype_0, 1}.die();
    const Individual individual_1{genotype_0, 1};
    CHECK(!(individual_0 == individual_1));
    CHECK(individual_0 != individual_1);
  }
  {
    const auto individual_0 = Individual{genotype_0, 1}.feed(1);
    const Individual individual_1{genotype_0, 1};
    CHECK(!(individual_0 == individual_1));
    CHECK(individual_0 != individual_1);
  }
}
