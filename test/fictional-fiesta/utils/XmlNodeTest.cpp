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

TEST_CASE("Test getting attributes", "[XmlNodeTest][TestGetAttribute]")
{
  const auto& input_file = input_directory / fs::path("example_2.xml");
  const auto& document = XmlDocument {input_file};
  const auto& root_node = document.getRootNode();

  const auto children = root_node.getChildNodes();
  REQUIRE(children.size() == 4);

  REQUIRE(children[0].hasAttribute("name"));
  REQUIRE(children[0].getAttribute("name") == "fff");
  REQUIRE(!children[0].hasAttribute("other_name"));
  REQUIRE_THROWS(children[0].getAttribute("other_name"));
  REQUIRE(children[0].getOptionalAttribute("other_name", "MyOtherName") == "MyOtherName");

  REQUIRE(children[3].hasAttribute("name"));
  REQUIRE(children[3].getAttribute("name") == "MyName");
  REQUIRE(children[3].hasAttribute("type"));
  REQUIRE(children[3].getAttribute("type") == "MyType");
}

TEST_CASE("Test setting attributes", "[XmlNodeTest][TestSetAttribute]")
{
  XmlDocument document{};

  auto root = document.appendRootNode("Root");

  REQUIRE(!root.hasAttribute("att1"));

  // Add a new attribute.
  root.setAttribute("att1", "value_1");
  REQUIRE(root.hasAttribute("att1"));
  REQUIRE(root.getAttribute("att1") == "value_1");

  // Add a second attribute.
  root.setAttribute("att2", "v_2");
  REQUIRE(root.hasAttribute("att1"));
  REQUIRE(root.hasAttribute("att2"));
  REQUIRE(root.getAttribute("att2") == "v_2");

  // Reset attribute.
  REQUIRE(root.getAttribute("att1") == "value_1");
  root.setAttribute("att1", "v_1");
  REQUIRE(root.getAttribute("att1") == "v_1");
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

TEST_CASE("Test getting multiple child nodes of other XML nodes", "[XmlNodeTest][TestGetChildren]")
{
  const auto& input_file = input_directory / fs::path("example_2.xml");
  const auto& document = XmlDocument {input_file};
  const auto& root_node = document.getRootNode();

  {
    const std::vector<std::string> benchmark = {"N1_1", "N1_2", "N2_1", "N1_3"};
    const auto&& children = root_node.getChildNodes();
    REQUIRE(children.size() == benchmark.size());

    for (size_t i = 0; i < children.size(); ++i)
    {
      REQUIRE(children[i].getText() == benchmark[i]);
    }
  }

  {
    const std::vector<std::string> benchmark = {"N1_1", "N1_2", "N1_3"};
    const auto&& children = root_node.getChildNodes("Node1");
    REQUIRE(children.size() == benchmark.size());

    for (size_t i = 0; i < children.size(); ++i)
    {
      REQUIRE(children[i].getText() == benchmark[i]);
    }
  }

  {
    const std::vector<std::string> benchmark = {"N2_1"};
    const auto&& children = root_node.getChildNodes("Node2");
    REQUIRE(children.size() == benchmark.size());

    for (size_t i = 0; i < children.size(); ++i)
    {
      REQUIRE(children[i].getText() == benchmark[i]);
    }
  }
}

TEST_CASE("Test getting text as other types", "[XmlNodeTest][TestGetTextAs]")
{
  const auto& input_file = input_directory / fs::path("example_3.xml");
  const auto& document = XmlDocument {input_file};
  const auto& root_node = document.getRootNode();

  REQUIRE_THROWS(root_node.getTextAs<int>());
  REQUIRE(root_node.getChildNode("Int").getTextAs<int>() == 42);
  REQUIRE(root_node.getChildNode("UInt").getTextAs<unsigned int>() == 12);
  REQUIRE(root_node.getChildNode("Double").getTextAs<double>() == -34.99);
  REQUIRE(root_node.getChildNode("Float").getTextAs<float>() == float(1e-4));
  REQUIRE(root_node.getChildNode("LongLong").getTextAs<long long>() == -123456789);
  REQUIRE(root_node.getChildNode("Bool").getTextAs<bool>() == false);
  REQUIRE(root_node.getChildNode("ULongLong").getTextAs<unsigned long long>() == 555);
}

TEST_CASE("Test getting child node text as other types", "[XmlNodeTest][TestGetChildTextAs]")
{
  const auto& input_file = input_directory / fs::path("example_3.xml");
  const auto& document = XmlDocument {input_file};
  const auto& root_node = document.getRootNode();

  REQUIRE(root_node.getChildNodeText() == "42");
  REQUIRE(root_node.getChildNodeText("Bool") == "False");
  REQUIRE_THROWS(root_node.getChildNodeText("NO_NODE"));

  REQUIRE_THROWS(root_node.getTextAs<int>());
  REQUIRE(root_node.getChildNodeTextAs<int>() == 42);

  REQUIRE(root_node.getChildNodeTextAs<int>("Int") == 42);
  REQUIRE(root_node.getChildNodeTextAs<unsigned int>("UInt") == 12);
  REQUIRE(root_node.getChildNodeTextAs<double>("Double") == -34.99);
  REQUIRE(root_node.getChildNodeTextAs<float>("Float") == float(1e-4));
  REQUIRE(root_node.getChildNodeTextAs<long long>("LongLong") == -123456789);
  REQUIRE(root_node.getChildNodeTextAs<bool>("Bool") == false);
  REQUIRE(root_node.getChildNodeTextAs<unsigned long long>("ULongLong") == 555);
}

TEST_CASE("Test getting optional text.", "[XmlNodeTest][TestGetOptionalText]")
{
  const auto& input_file = input_directory / fs::path("example_3.xml");
  const auto& document = XmlDocument {input_file};
  const auto& root_node = document.getRootNode();

  REQUIRE(root_node.getOptionalTextAs<int>(-12) == -12);
  REQUIRE(root_node.getChildNode("Int").getOptionalTextAs<int>(-12) == 42);
  REQUIRE(root_node.getOptionalTextAs<unsigned int>(256) == 256);
  REQUIRE(root_node.getChildNode("UInt").getOptionalTextAs<unsigned int>(256) == 12);
  REQUIRE(root_node.getOptionalTextAs<double>(1e-10) == 1e-10);
  REQUIRE(root_node.getChildNode("Double").getOptionalTextAs<double>(1e-10) == -34.99);
  REQUIRE(root_node.getOptionalTextAs<float>(-3.141592) == float(-3.141592));
  REQUIRE(root_node.getChildNode("Float").getOptionalTextAs<float>(-3.14) == float(1e-4));
  REQUIRE(root_node.getOptionalTextAs<bool>(true));
  REQUIRE(root_node.getChildNode("Bool").getOptionalTextAs<bool>(true) == false);
  REQUIRE(root_node.getOptionalTextAs<long long>(-777) == -777);
  REQUIRE(root_node.getChildNode("LongLong").getOptionalTextAs<long long>(-777) == -123456789);
  REQUIRE(root_node.getOptionalTextAs<unsigned long long>(1024) == 1024);
  REQUIRE(root_node.getChildNode("ULongLong").getOptionalTextAs<unsigned long long>(1024) == 555);
}

TEST_CASE("Test getting optional child node text.", "[XmlNodeTest][TestGetChildNodeOptionalText]")
{
  const auto& input_file = input_directory / fs::path("example_3.xml");
  const auto& document = XmlDocument {input_file};
  const auto& root_node = document.getRootNode();

  REQUIRE(root_node.getOptionalChildNodeTextAs<int>(-12) == 42);
  REQUIRE(root_node.getChildNode("Int").getOptionalChildNodeTextAs<int>(-12) == -12);

  REQUIRE(root_node.getOptionalChildNodeTextAs<int>("Int", 256) == 42);
  REQUIRE(root_node.getOptionalChildNodeTextAs<int>("NoNode", 256) == 256);
  REQUIRE(root_node.getOptionalChildNodeTextAs<unsigned int>("UInt", 256) == 12);
  REQUIRE(root_node.getOptionalChildNodeTextAs<unsigned int>("NoNode", 256) == 256);
  REQUIRE(root_node.getOptionalChildNodeTextAs<double>("Double", 1e-10) == -34.99);
  REQUIRE(root_node.getOptionalChildNodeTextAs<double>("NoNode", 1e-10) == 1e-10);
  REQUIRE(root_node.getOptionalChildNodeTextAs<float>("Float", -3.141592) == float(1e-4));
  REQUIRE(root_node.getOptionalChildNodeTextAs<float>("NoNode", -3.141592) == float(-3.141592));
  REQUIRE(!root_node.getOptionalChildNodeTextAs<bool>("Bool", true));
  REQUIRE(root_node.getOptionalChildNodeTextAs<bool>("NoNode", true));
  REQUIRE(root_node.getOptionalChildNodeTextAs<long long>("LongLong", -777) == -123456789);
  REQUIRE(root_node.getOptionalChildNodeTextAs<long long>("NoNode", -777) == -777);
  REQUIRE(root_node.getOptionalChildNodeTextAs<unsigned long long>("ULongLong", 1024) == 555);
  REQUIRE(root_node.getOptionalChildNodeTextAs<unsigned long long>("NoNode", 1024) == 1024);
}

TEST_CASE("Test setting text in nodes", "[XmlNodeTest][TestSetText]")
{
  XmlDocument document{};

  auto root_1 = document.appendRootNode("Root1");
  root_1.setText("This will be overwritten");
  REQUIRE(root_1.getText() == "This will be overwritten");

  auto root_2 = document.appendRootNode("Root2");
  root_2.setText("Text 2");
  REQUIRE(root_2.getText() == "Text 2");

  auto root_3 = document.appendRootNode("Root3");
  REQUIRE_THROWS(root_3.getText());

  document.getRootNode().setText(-193);
  REQUIRE(root_1.getText() == "-193");
  REQUIRE(root_1.getTextAs<int>() == -193);

  const fs::path result_file = result_directory / fs::path("example_set_text.xml");
  REQUIRE_NOTHROW(document.save(result_file));

  const fs::path benchmark_file = benchmark_directory / fs::path("example_set_text.xml");
  benchmarkFiles(benchmark_file, result_file, result_directory);
}

TEST_CASE("Test adding child nodes", "[XmlNodeTest][TestAddChildNode]")
{
  XmlDocument document{};

  auto root = document.appendRootNode("Root");

  root.appendChildNode("Node1").appendChildNode("SubNode1").setText("sn1");
  root.appendChildNode("Node2").setText("n2");

  root.appendChildNode("Node3");

  root.appendChildNode("");

  const fs::path result_file = result_directory / fs::path("example_add_child_node.xml");
  REQUIRE_NOTHROW(document.save(result_file));

  const fs::path benchmark_file = benchmark_directory / fs::path("example_add_child_node.xml");
  benchmarkFiles(benchmark_file, result_file, result_directory);
}
