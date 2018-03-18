#include "catch/catch.hpp"

#include "fictional-fiesta/world/itf/Location.h"

#include "fictional-fiesta/utils/itf/Exception.h"
#include "fictional-fiesta/utils/itf/XmlDocument.h"

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

  const auto& result_file = result_directory / fs::path("location_0.xml");
  REQUIRE_NOTHROW(document.save(result_file));

  const auto& benchmark_file = benchmark_directory / fs::path("location_0.xml");
  benchmarkFiles(benchmark_file, result_file, result_directory);
}
