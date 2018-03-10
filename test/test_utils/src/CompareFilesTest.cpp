/// @file Test of the file comparation test utilities.

#include "catch/catch.hpp"

#include "test/test_utils/itf/CompareFiles.h"

namespace fs = std::experimental::filesystem;

using namespace testutils;

static const fs::path input_directory = fs::path(TEST_SOURCE_DIRECTORY)
    / fs::path("test_utils/input");

static const fs::path benchmark_directory = fs::path(TEST_SOURCE_DIRECTORY)
    / fs::path("test_utils/benchmark");

static const fs::path result_directory = fs::path(TEST_BINARY_DIRECTORY)
    / fs::path("test_utils/result");

TEST_CASE("3: Test comparing the same file twice (pass)", "[TestCompareFiles][TestFilesAreEqual]")
{
  const fs::path input_file = input_directory / fs::path("example_0.xml");
  REQUIRE(filesAreEqual(input_file, input_file));
}

TEST_CASE("Test comparing with unexisting files (throws)", "[CompareFilesTest][TestFilesAreEqual]")
{
  const fs::path input_file_0 = input_directory / fs::path("example_0.xml");
  const fs::path input_file_1 = input_directory / fs::path("no_example_0.xml");
  REQUIRE_THROWS(filesAreEqual(input_file_0, input_file_1));
  REQUIRE_THROWS(filesAreEqual(input_file_1, input_file_0));
  REQUIRE_THROWS(filesAreEqual(input_file_1, input_file_1));
}

TEST_CASE("Test comparing two empty files (pass)", "[CompareFilesTest][TestFilesAreEqual]")
{
  const fs::path input_file_0 = input_directory / fs::path("example_0.xml");
  const fs::path input_file_1 = input_directory / fs::path("example_1.xml");
  REQUIRE(filesAreEqual(input_file_0, input_file_1));
}

TEST_CASE("Test comparing files that differ in a charachter (same size)", "[CompareFilesTest][TestFilesAreEqual]")
{
  const fs::path input_file_0 = input_directory / fs::path("example_2.xml");
  const fs::path input_file_1 = input_directory / fs::path("example_3.xml");
  REQUIRE(!filesAreEqual(input_file_0, input_file_1));
  REQUIRE(!filesAreEqual(input_file_1, input_file_0));
}

TEST_CASE("Test comparing files that differ size", "[CompareFilesTest][TestFilesAreEqual]")
{
  const fs::path input_file_0 = input_directory / fs::path("example_3.xml");
  const fs::path input_file_1 = input_directory / fs::path("example_4.xml");
  REQUIRE(!filesAreEqual(input_file_0, input_file_1));
  REQUIRE(!filesAreEqual(input_file_1, input_file_0));
}

TEST_CASE("Test comparing equal files", "[CompareFilesTest][TestFilesAreEqual]")
{
  const fs::path input_file_0 = input_directory / fs::path("example_2.xml");
  const fs::path input_file_1 = input_directory / fs::path("example_5.xml");
  REQUIRE(filesAreEqual(input_file_0, input_file_0));
  REQUIRE(filesAreEqual(input_file_1, input_file_1));
}

TEST_CASE("Test diff equal files", "[CompareFilesTest][TestDiffFiles]")
{
  {
    const fs::path input_file_0 = input_directory / fs::path("example_0.xml");
    const fs::path input_file_1 = input_directory / fs::path("example_1.xml");
    const fs::path result_file_0 = result_directory / fs::path("diff_0.diff");

    const bool success = diffFiles(input_file_0, input_file_1, result_file_0);

    if (success)
    {
      const fs::path benchmark_file_0 = benchmark_directory / fs::path("diff_0.diff");
      REQUIRE(filesAreEqual(result_file_0, benchmark_file_0));
    }
  }
  {
    const fs::path input_file_0 = input_directory / fs::path("example_2.xml");
    const fs::path input_file_1 = input_directory / fs::path("example_5.xml");
    const fs::path result_file_0 = result_directory / fs::path("diff_3.diff");

    const bool success = diffFiles(input_file_0, input_file_1, result_file_0);

    if (success)
    {
      const fs::path benchmark_file_0 = benchmark_directory / fs::path("diff_3.diff");
      REQUIRE(filesAreEqual(result_file_0, benchmark_file_0));
    }
  }
}

TEST_CASE("Test diff different files", "[CompareFilesTest][TestDiffFiles]")
{
  {
    const fs::path input_file_0 = input_directory / fs::path("example_0.xml");
    const fs::path input_file_1 = input_directory / fs::path("example_2.xml");
    const fs::path result_file_0 = result_directory / fs::path("diff_1.diff");

    const bool success = (diffFiles(input_file_0, input_file_1, result_file_0) == 0);

    if (success)
    {
      const fs::path benchmark_file_0 = benchmark_directory / fs::path("diff_1.diff");
      REQUIRE(filesAreEqual(result_file_0, benchmark_file_0));
    }
  }
  {
    const fs::path input_file_0 = input_directory / fs::path("example_3.xml");
    const fs::path input_file_1 = input_directory / fs::path("example_2.xml");
    const fs::path result_file_0 = result_directory / fs::path("diff_2.diff");

    const bool success = (diffFiles(input_file_0, input_file_1, result_file_0) == 0);

    if (success)
    {
      const fs::path benchmark_file_0 = benchmark_directory / fs::path("diff_2.diff");
      REQUIRE(filesAreEqual(result_file_0, benchmark_file_0));
    }
  }
}
