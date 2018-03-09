#ifndef INCLUDE_TEST_TEST_UTILE_COMPARE_FILES_H
#define INCLUDE_TEST_TEST_UTILE_COMPARE_FILES_H

#include <experimental/filesystem>

namespace testutils
{

/// @brief Check whether two given files are equal or not.
///
/// @param firstFile First file to be checked.
/// @param secondFile Second file to be checked.
/// @return true if the content of both files is exactly the same and false if not.
bool filesAreEqual(const std::experimental::filesystem::path& firstFile,
    const std::experimental::filesystem::path& secondFile);

/// @brief If possible, calls the diff command utility between the two first
///   arguments and stores the result in the third.
///
/// @param firstFile First file to be checked.
/// @param secondFile Second file to be checked.
/// @param diffFile Result diff file.
/// @return true if the diff could be called and false if not.
bool diffFiles(const std::experimental::filesystem::path& firstFile,
    const std::experimental::filesystem::path& secondFile,
    const std::experimental::filesystem::path& diffFile);

}

#endif
