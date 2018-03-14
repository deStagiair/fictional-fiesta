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

    REQUIRE(root_node.getName() == "Example");

    const auto& child_node = root_node.getChildNode();
    REQUIRE(child_node.getName() == "Node1");
  }
}

TEST_CASE("Test getting child nodes of other XML nodes", "[XmlNodeTest][TestGetChild]")
{
  {
    const auto& input_file = input_directory / fs::path("example_0.xml");
    const auto& document = XmlDocument {input_file};
    const auto& root_node = document.getRootNode();

    REQUIRE(root_node.getName() == "Example");

    REQUIRE(root_node.hasChildNode());

    const auto& child_node = root_node.getChildNode();
    REQUIRE(child_node.getName() == "Node1");
    REQUIRE_THROWS(child_node.getText());

    REQUIRE(child_node.hasChildNode());

    const auto& grand_child_node = child_node.getChildNode();
    REQUIRE(grand_child_node.getName() == "SubNode1");
    REQUIRE(grand_child_node.getText() == "Content");

    REQUIRE(!grand_child_node.hasChildNode());

    REQUIRE_THROWS(grand_child_node.getChildNode());
  }
}

TEST_CASE("Test getting named child nodes of other XML nodes", "[XmlNodeTest][TestGetNamedChild]")
{
  {
    const auto& input_file = input_directory / fs::path("example_0.xml");
    const auto& document = XmlDocument {input_file};
    const auto& root_node = document.getRootNode();

    REQUIRE(root_node.getName() == "Example");

    REQUIRE(root_node.hasChildNode("Node1"));
    REQUIRE(!root_node.hasChildNode("NoNode1"));
    REQUIRE_THROWS(root_node.getChildNode("NoNode1"));

    const auto& child_node_1 = root_node.getChildNode("Node1");
    REQUIRE(child_node_1.getName() == "Node1");

    REQUIRE(child_node_1.hasChildNode("SubNode1"));

    const auto& grand_child_node_1 = child_node_1.getChildNode("SubNode1");
    REQUIRE(grand_child_node_1.getName() == "SubNode1");

    REQUIRE(!grand_child_node_1.hasChildNode("Something"));
    REQUIRE_THROWS(grand_child_node_1.getChildNode());

    REQUIRE(root_node.hasChildNode("Node2"));


    const auto& child_node_2 = root_node.getChildNode("Node2");
    REQUIRE(child_node_2.getName() == "Node2");
  }
}
