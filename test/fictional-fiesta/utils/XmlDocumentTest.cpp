#include "catch/catch.hpp"

#include "fictional-fiesta/utils/itf/Exception.h"
#include "fictional-fiesta/utils/itf/XmlDocument.h"

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;
using namespace fictionalfiesta;

TEST_CASE("2: Test loading a XML document (pass)", "[multi-file:2]")
{
  const fs::path input_directory("input");

  {
    const fs::path input_file = input_directory / fs::path("example_0.xml");
    REQUIRE_THROWS_AS(XmlDocument{input_file}, Exception);
  }
}
