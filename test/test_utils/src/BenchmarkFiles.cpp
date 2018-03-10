/// @file Test of the file comparation test utilities.

#include "test/test_utils/itf/BenchmarkFiles.h"

#include "test/test_utils/itf/CompareFiles.h"

#include "catch/catch.hpp"

namespace fs = std::experimental::filesystem;

namespace testutils
{

bool benchmarkFiles(const fs::path& firstFile, const fs::path& secondFile, const fs::path& resultsPath)
{
  if (filesAreEqual(firstFile, secondFile))
  {
    return true;
  }
  else
  {
    const fs::path result_file = resultsPath / fs::path(firstFile.stem().string() +
        "_" + secondFile.stem().string() + ".diff");

    const bool diff_success = diffFiles(firstFile, secondFile, result_file);

    INFO( "" << result_file);

    INFO("The files are different:\n  " << firstFile << "\n  " << secondFile << "\n");

    if (diff_success)
    {
      INFO("Diff file: " << result_file << "\n");
      FAIL();
    }

    FAIL();

    return false;
  }
}

} // namespace testutils
