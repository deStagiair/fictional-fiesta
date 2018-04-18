#include "catch/catch.hpp"

#include "fictional-fiesta/world/itf/World.h"

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

TEST_CASE("Test saving a world to XML", "[WorldTest][TestSave]")
{
  {
    const auto& result_file = result_directory / fs::path("world_0.xml");
    World().save(result_file);

    const auto& benchmark_file = benchmark_directory / fs::path("world_0.xml");
    benchmarkFiles(benchmark_file, result_file, result_directory);
  }
  //{
    //const auto& result_file = result_directory / fs::path("world_1.xml");
    //World world;
    //world.

    //world.save(result_file);

    //const auto& benchmark_file = benchmark_directory / fs::path("world_1.xml");
    //benchmarkFiles(benchmark_file, result_file, result_directory);
  //}
}

//TEST_CASE("Test loading a world from XML", "[WorldTest][TestLoad]")
//{
  //const auto& input_file = input_directory / fs::path("world_0.xml");
  //const auto& document = XmlDocument{input_file};

  //const auto& location = Location{input_file.getRootNode()};

  //const auto& result_file = result_directory / fs::path("location_0.xml");
  //REQUIRE_NOTHROW(location.save(result_file));


  //const auto& benchmark_file = benchmark_directory / fs::path("location_0.xml");
  //benchmarkFiles(benchmark_file, result_file, result_directory);
//}
