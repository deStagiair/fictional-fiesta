#include "catch/catch.hpp"

#include "fictional-fiesta/world/itf/ConstantSource.h"
#include "fictional-fiesta/world/itf/SourceFactory.h"

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

TEST_CASE("Test creating sources from XML nodes", "[SourceFactoryTest][TestCreateFromXmlNode]")
{
  const auto& input_file = input_directory / fs::path("sources_0.xml");
  const auto& document = XmlDocument{input_file};
  const auto& root_node = document.getRootNode();

  const auto& source_nodes{root_node.getChildNodes("Source")};
  REQUIRE(source_nodes.size() == 5);

  {
    const auto source{SourceFactory::createSource(source_nodes[0])};
    REQUIRE(source->getResourceId() == "Water");
    REQUIRE(source->getCurrentUnitCount() == 100);
  }

  {
    const auto source{SourceFactory::createSource(source_nodes[1])};
    REQUIRE(source->getResourceId() == "Light");
  }

  {
    // Unknown source type.
    REQUIRE_THROWS(SourceFactory::createSource(source_nodes[2]));

    // Missing resource identifier.
    REQUIRE_THROWS(SourceFactory::createSource(source_nodes[3]));

    // Missing source type.
    REQUIRE_THROWS(SourceFactory::createSource(source_nodes[4]));
  }
}

TEST_CASE("Test cloning sources", "[SourceFactoryTest][TestClone]")
{
  const auto& input_file = input_directory / fs::path("constant_source_0.xml");
  const auto& document = XmlDocument{input_file};
  const auto& root_node = document.getRootNode();

  const auto& constant_source = SourceFactory::createSource(root_node);
  const auto& cloned_source = constant_source->clone();

  const auto& result_file = result_directory / fs::path("constant_source_0.xml");
  REQUIRE_NOTHROW(document.save(result_file));

  const auto& benchmark_file = benchmark_directory / fs::path("constant_source_0.xml");
  benchmarkFiles(benchmark_file, result_file, result_directory);
}
