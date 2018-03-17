#include "catch/catch.hpp"

#include "fictional-fiesta/world/itf/ConstantSource.h"

#include "fictional-fiesta/utils/itf/Exception.h"
#include "fictional-fiesta/utils/itf/XmlDocument.h"
#include "fictional-fiesta/utils/itf/XmlNode.h"

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

TEST_CASE("Test constructor from XML node", "[ConstantSourceTest][TestConstructorFromXmlNode]")
{
  const auto& input_file = input_directory / fs::path("example_0.xml");
  const auto& document = XmlDocument{input_file};
  const auto& root_node = document.getRootNode();

  const auto& source_nodes{root_node.getChildNodes("Source")};

  REQUIRE(source_nodes.size() == 5);

  {
    const auto source{ConstantSource(source_nodes[0])};
    REQUIRE(source.getResourceId() == "Water");
    REQUIRE(source.getUnitCount() == Source::INFINITY_UNITS);
  }

  {
    const auto source{ConstantSource(source_nodes[1])};
    REQUIRE(source.getResourceId() == "Light");
  }

  {
    // Incorrect source type.
    REQUIRE_THROWS(ConstantSource(source_nodes[2]));
    // Missing resource.
    REQUIRE_THROWS(ConstantSource(source_nodes[3]));
    // Missing type.
    REQUIRE_THROWS(ConstantSource(source_nodes[4]));
  }
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

TEST_CASE("Test consuming and regenerating units", "[ConstantSourceTest][TestRegenerate]")
{
  ConstantSource source("Heat");

  REQUIRE(source.getUnitCount() == Source::INFINITY_UNITS);
  REQUIRE(source.consume(10) == 10);
  REQUIRE(source.getUnitCount() == Source::INFINITY_UNITS);
  source.regenerate();
  REQUIRE(source.getUnitCount() == Source::INFINITY_UNITS);
}
