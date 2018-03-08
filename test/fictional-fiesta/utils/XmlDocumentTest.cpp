#include "catch/catch.hpp"

#include "fictional-fiesta/utils/itf/Exception.h"
#include "fictional-fiesta/utils/itf/XmlDocument.h"

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;
using namespace fictionalfiesta;

static const fs::path input_directory = fs::path(TEST_SOURCE_DIRECTORY)
    / fs::path("fictional-fiesta/utils/input");

TEST_CASE("2: Test loading a XML document (pass)", "[multi-file:2]")
{
  {
    const fs::path input_file = input_directory / fs::path("example_0.xml");
    REQUIRE_NOTHROW(XmlDocument{input_file});
  }

  {
    const fs::path input_file = input_directory / fs::path("no_example_0.xml");
    REQUIRE_THROWS_AS(XmlDocument{input_file}, Exception);
  }
}
