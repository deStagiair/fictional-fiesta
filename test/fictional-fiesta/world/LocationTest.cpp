#include "catch/catch.hpp"

#include "fictional-fiesta/world/itf/ConstantSource.h"
#include "fictional-fiesta/world/itf/Genotype.h"
#include "fictional-fiesta/world/itf/Individual.h"
#include "fictional-fiesta/world/itf/Location.h"

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

TEST_CASE("Test loading and saving locations from/to XML", "[LocationTest][TestLoadAndSave]")
{
  const auto& input_file = input_directory / fs::path("location_0.xml");
  const auto& document = XmlDocument{input_file};

  const auto& location = Location{document.getRootNode()};

  const auto& result_file = result_directory / fs::path("location_0.xml");

  auto result_document = XmlDocument{};
  auto node = result_document.appendRootNode("Location");
  location.save(node);
  REQUIRE_NOTHROW(result_document.save(result_file));


  const auto& benchmark_file = benchmark_directory / fs::path("location_0.xml");
  benchmarkFiles(benchmark_file, result_file, result_directory);
}

TEST_CASE("Test creating a location and saving it to XML", "[LocationTest][TestCreateAndSave]")
{
  auto location = Location{};
  location.addSource(std::make_unique<ConstantSource>("Light", 10));

  const auto& result_file = result_directory / fs::path("location_1.xml");

  auto result_document = XmlDocument{};
  auto node = result_document.appendRootNode("Location");
  location.save(node);
  REQUIRE_NOTHROW(result_document.save(result_file));


  const auto& benchmark_file = benchmark_directory / fs::path("location_1.xml");
  benchmarkFiles(benchmark_file, result_file, result_directory);
}

TEST_CASE("Test splitting resources", "[LocationTest][TestSplitResources]")
{
  auto rng = FSM::createRng(1);
  Location location;
  location.addSource(std::make_unique<ConstantSource>("Light", 10));
  location.addSource(std::make_unique<ConstantSource>("Water", 3));

  const Genotype genotype{10, 0.5, 0.5};
  location.addIndividual(Individual{genotype, 60.0});
  location.addIndividual(Individual{genotype, 10.0});
  location.addIndividual(Individual{genotype, 10.0});
  location.addIndividual(Individual{genotype, 10.0});
  location.addIndividual(Individual{genotype, 1.0});

  location.splitResources(rng);

  const auto& individuals = location.getIndividuals();

  REQUIRE(individuals.size() == 5);

  CHECK(individuals[0].getResourceCount() == 8);
  CHECK(individuals[1].getResourceCount() == 1);
  CHECK(individuals[2].getResourceCount() == 1);
  CHECK(individuals[3].getResourceCount() == 2);
  CHECK(individuals[4].getResourceCount() == 1);
}

TEST_CASE("Test removing dead individuals", "[LocationTest][TestCleanDeadIndividuals]")
{
  Location location;

  CHECK(location.getIndividuals().size() == 0);

  const Genotype genotype{10, 0.5, 0.5};

  location.addIndividual(Individual{genotype, 1}.die());
  location.addIndividual(Individual{genotype, 1}.die());

  CHECK(location.getIndividuals().size() == 2);

  location.cleanDeadIndividuals();

  CHECK(location.getIndividuals().size() == 0);

  location.addIndividual(Individual{genotype, 1}.die());
  location.addIndividual(Individual{genotype, 60.0});
  location.addIndividual(Individual{genotype, 10.0});
  location.addIndividual(Individual{genotype, 10.0});
  location.addIndividual(Individual{genotype, 1.0});
  location.addIndividual(Individual{genotype, 1}.die());
  location.addIndividual(Individual{genotype, 1}.die());

  CHECK(location.getIndividuals().size() == 6);

  location.cleanDeadIndividuals();

  CHECK(location.getIndividuals().size() == 4);
}
