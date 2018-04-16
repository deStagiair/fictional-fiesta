#include "catch/catch.hpp"

#include "fictional-fiesta/world/itf/Genotype.h"
#include "fictional-fiesta/world/itf/Phenotype.h"

#include "fictional-fiesta/utils/itf/Exception.h"
#include "fictional-fiesta/utils/itf/XmlDocument.h"
#include "fictional-fiesta/utils/itf/XmlNode.h"

#include "test/test_utils/itf/BenchmarkFiles.h"

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

using namespace testutils;
using namespace fictionalfiesta;

// Important note: Some of these tests force the seed of the RNG to allow testability.
// Changing the RNG or the order of the statements will probably cause this test to fail.

static const fs::path input_directory = fs::path(TEST_SOURCE_DIRECTORY)
    / fs::path("fictional-fiesta/world/input");

static const fs::path result_directory = fs::path(TEST_BINARY_DIRECTORY)
    / fs::path("fictional-fiesta/world/result");

static const fs::path benchmark_directory = fs::path(TEST_SOURCE_DIRECTORY)
    / fs::path("fictional-fiesta/world/benchmark");


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

TEST_CASE("Test phenotype XML save method", "[PhenotypeTest][TestPhenotypeSaveToXml]")
{
  auto document = XmlDocument{};

  const Phenotype phenotype{42.01};
  phenotype.save(document.appendRootNode("Phenotype"));

  const auto& result_file = result_directory / fs::path("phenotype_0.xml");
  REQUIRE_NOTHROW(document.save(result_file));

  const auto& benchmark_file = benchmark_directory / fs::path("phenotype_0.xml");
  benchmarkFiles(benchmark_file, result_file, result_directory);
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

TEST_CASE("Test (in)equality operators for Phenotype instances", "[PhenotypeTest][TestEquality]")
{
  {
    const Phenotype phenotype_0{13};
    CHECK(phenotype_0 == phenotype_0);
    CHECK(!(phenotype_0 != phenotype_0));

    const Phenotype phenotype_1{13};
    CHECK(phenotype_0 == phenotype_1);
    CHECK(!(phenotype_0 != phenotype_1));
  }
  {
    const Phenotype phenotype_0{13};
    const Phenotype phenotype_1{12.999};

    CHECK(!(phenotype_0 == phenotype_1));
    CHECK(phenotype_0 != phenotype_1);
  }
}
