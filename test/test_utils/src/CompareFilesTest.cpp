/// @file Test of the file comparation test utilities.

#include "catch/catch.hpp"

#include "test/test_utils/itf/CompareFiles.h"

namespace fs = std::experimental::filesystem;

using namespace testutils;

static const fs::path input_directory = fs::path(TEST_SOURCE_DIRECTORY)
    / fs::path("test_utils/input");

TEST_CASE("3: Test comparing the same file twice (pass)", "[multi-file:3]")
{
  const fs::path input_file = input_directory / fs::path("example_0.xml");
  REQUIRE(filesAreEqual(input_file, input_file));
}

TEST_CASE("Test comparing with unexisting files (throws)", "[multi-file:3]")
{
  const fs::path input_file_0 = input_directory / fs::path("example_0.xml");
  const fs::path input_file_1 = input_directory / fs::path("no_example_0.xml");
  REQUIRE_THROWS(filesAreEqual(input_file_0, input_file_1));
  REQUIRE_THROWS(filesAreEqual(input_file_1, input_file_0));
  REQUIRE_THROWS(filesAreEqual(input_file_1, input_file_1));
}

TEST_CASE("Test comparing two empty files (pass)", "[multi-file:3]")
{
  const fs::path input_file_0 = input_directory / fs::path("example_0.xml");
  const fs::path input_file_1 = input_directory / fs::path("example_1.xml");
  REQUIRE(filesAreEqual(input_file_0, input_file_1));
}

TEST_CASE("Test comparing files that differ in a charachter (same size)", "[multi-file:3]")
{
  const fs::path input_file_0 = input_directory / fs::path("example_2.xml");
  const fs::path input_file_1 = input_directory / fs::path("example_3.xml");
  REQUIRE(!filesAreEqual(input_file_0, input_file_1));
  REQUIRE(!filesAreEqual(input_file_1, input_file_0));
}

TEST_CASE("Test comparing files that differ size", "[multi-file:3]")
{
  const fs::path input_file_0 = input_directory / fs::path("example_3.xml");
  const fs::path input_file_1 = input_directory / fs::path("example_4.xml");
  REQUIRE(!filesAreEqual(input_file_0, input_file_1));
  REQUIRE(!filesAreEqual(input_file_1, input_file_0));
}

TEST_CASE("Test comparing equal files", "[multi-file:3]")
{
  const fs::path input_file_0 = input_directory / fs::path("example_2.xml");
  const fs::path input_file_1 = input_directory / fs::path("example_5.xml");
  REQUIRE(filesAreEqual(input_file_0, input_file_0));
  REQUIRE(filesAreEqual(input_file_1, input_file_1));
}
