#include "catch/catch.hpp"

#include "fictional-fiesta/world/itf/ConstantSource.h"

#include "fictional-fiesta/utils/itf/Exception.h"

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;
using namespace fictionalfiesta;

static const fs::path input_directory = fs::path(TEST_SOURCE_DIRECTORY)
    / fs::path("fictional-fiesta/world/input");
static const fs::path result_directory = fs::path(TEST_BINARY_DIRECTORY)
    / fs::path("fictional-fiesta/world/result");
static const fs::path benchmark_directory = fs::path(TEST_SOURCE_DIRECTORY)
    / fs::path("fictional-fiesta/world/benchmark");

TEST_CASE("Test constructor from resource name", "[ConstantSourceTest][TestConstructorFromResource]")
{
  const ConstantSource source("Water");

  REQUIRE(source.getResourceId() == "Water");
  REQUIRE(source.getUnitCount() == Source::INFINITY_UNITS);
}

TEST_CASE("Test consuming units", "[ConstantSourceTest][TestConsume]")
{
  ConstantSource source("Light");

  REQUIRE(source.getUnitCount() == Source::INFINITY_UNITS);
  REQUIRE(source.consume(0) == 0);
  REQUIRE(source.getUnitCount() == Source::INFINITY_UNITS);
  REQUIRE(source.consume(3500) == 3500);
  REQUIRE(source.getUnitCount() == Source::INFINITY_UNITS);
  REQUIRE(source.consume(Source::INFINITY_UNITS) == Source::INFINITY_UNITS);
  REQUIRE(source.getUnitCount() == Source::INFINITY_UNITS);
}
