#ifndef INCLUDE_TEST_TEST_UTILS_BENCHMARK_FILES_H
#define INCLUDE_TEST_TEST_UTILS_BENCHMARK_FILES_H

#include <experimental/filesystem>

namespace testutils
{

/// @brief Checks whether the two file contents are the same with a test check
///   that fails if not.
///
/// If the files are not equals and the command line and the diff utility are
/// available, it computes the diff between the two files.
///
/// @param firstFile First file to be checked.
/// @param secondFile Second file to be checked.
/// @param resultsPath Directory where the diff file will be created.
/// @return true if the content of both files is exactly the same and false if not.
bool BenchmarkFiles(const std::experimental::filesystem::path& firstFile,
    const std::experimental::filesystem::path& secondFile,
    const std::experimental::filesystem::path& resultsPath);

} // namespace testutils

#endif
