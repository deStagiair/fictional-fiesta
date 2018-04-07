#include "catch/catch.hpp"

#include "fictional-fiesta/world/itf/Genotype.h"
#include "fictional-fiesta/world/itf/Phenotype.h"

#include "fictional-fiesta/utils/itf/Exception.h"

using namespace fictionalfiesta;

// Important note: Some of these tests force the seed of the RNG to allow testability.
// Changing the RNG or the order of the statements will probably cause this test to fail.

TEST_CASE("Test phenotype constructor and getters", "[PhenotypeTest][TestConstructor]")
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

TEST_CASE("Test phenotype stringify method", "[PhenotypeTest][TestStr]")
{
  {
    const auto benchmark = "Energy: 16.1\n";
    const auto phenotype = Phenotype{16.1};

    CHECK(phenotype.str(0) == benchmark);
  }

  {
    const auto benchmark = "  Energy: 0\n";
    const auto phenotype = Phenotype{0};
    CHECK(phenotype.str(1) == benchmark);
  }
}

TEST_CASE("Test phenotype feed method", "[PhenotypeTest][TestFeed]")
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

TEST_CASE("Test phenotype split method", "[PhenotypeTest][TestSplit]")
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
