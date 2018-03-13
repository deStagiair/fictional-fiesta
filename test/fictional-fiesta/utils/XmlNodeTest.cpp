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
    const auto& input_file = input_directory / fs::path("example_0.xml");
    const auto& document = XmlDocument {input_file};
    const auto& root_node = document.getRootNode();

    REQUIRE(std::string(root_node.getName()) == "Example");

    const auto& child_node = root_node.getChildNode();
    REQUIRE(std::string(child_node.getName()) == "Node1");
  }
}

TEST_CASE("Test getting child nodes of other XML nodes", "[XmlNodeTest][TestGetChild]")
{
  {
    const auto& input_file = input_directory / fs::path("example_0.xml");
    const auto& document = XmlDocument {input_file};
    const auto& root_node = document.getRootNode();

    REQUIRE(std::string(root_node.getName()) == "Example");

    REQUIRE(root_node.hasChildNodes());

    const auto& child_node = root_node.getChildNode();
    REQUIRE(std::string(child_node.getName()) == "Node1");

    REQUIRE(child_node.hasChildNodes());

    const auto& grand_child_node = child_node.getChildNode();
    REQUIRE(std::string(grand_child_node.getName()) == "SubNode1");

    REQUIRE(!grand_child_node.hasChildNodes());

    REQUIRE_THROWS(grand_child_node.getChildNode());
  }
}
