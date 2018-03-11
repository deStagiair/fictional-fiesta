#include "catch/catch.hpp"

#include "fictional-fiesta/utils/itf/Exception.h"
#include "fictional-fiesta/utils/itf/XmlDocument.h"
#include "fictional-fiesta/utils/itf/XmlNode.h"

#include "test/test_utils/itf/BenchmarkFiles.h"

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;
using namespace fictionalfiesta;
using namespace testutils;

static const fs::path input_directory = fs::path(TEST_SOURCE_DIRECTORY)
    / fs::path("fictional-fiesta/utils/input");
static const fs::path result_directory = fs::path(TEST_BINARY_DIRECTORY)
    / fs::path("fictional-fiesta/utils/result");
static const fs::path benchmark_directory = fs::path(TEST_SOURCE_DIRECTORY)
    / fs::path("fictional-fiesta/utils/benchmark");

TEST_CASE("Test getting names of XML nodes", "[XmlNodeTest][TestGetName]")
{
  {
    const fs::path input_file = input_directory / fs::path("example_0.xml");
    const XmlDocument document{input_file};
    const XmlNode root_node = document.getRootNode();
    REQUIRE(std::string(root_node.getName()) == "Example");
  }
}
