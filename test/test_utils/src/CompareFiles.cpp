/// @file CompareFiles.cpp Implementation of the file comparation test utilities.

#include "test/test_utils/itf/CompareFiles.h"

#include "test/test_utils/itf/CommandLineUtils.h"

#include <fstream>

namespace fs = std::experimental::filesystem;

namespace testutils
{

bool filesAreEqual(const fs::path& firstFile, const fs::path& secondFile)
{
  // If both paths resolve to the same element, the contents are equal.
  if (fs::equivalent(firstFile, secondFile))
  {
    return true;
  }

  // If each file has a different size, the files are different.
  if (fs::file_size(firstFile) != fs::file_size(secondFile))
  {
    return false;
  }

  std::ifstream first_stream(firstFile);
  std::ifstream second_stream(secondFile);

  constexpr size_t buffer_size = 1024;
  std::string first_buffer(buffer_size, '\0');
  std::string second_buffer(buffer_size, '\0');

  while (first_stream.good() && second_stream.good())
  {
    first_stream.read(&first_buffer[0], buffer_size);
    second_stream.read(&second_buffer[0], buffer_size);
    if (first_buffer != second_buffer)
    {
      return false;
    }
  }

  if (first_stream.bad())
  {
    throw std::runtime_error("Error reading " + firstFile.string());
  }

  if (second_stream.bad())
  {
    throw std::runtime_error("Error reading " + secondFile.string());
  }

  return true;
}

bool diffFiles(const fs::path& firstFile, const fs::path& secondFile, const fs::path& diffFile)
{
  if (!commandLineAccessible())
  {
    return false;
  }

  const std::string command = "diff " + firstFile.string() + " " + secondFile.string() +
      " > " + diffFile.string();

  return (runCommand(command) != -1);
}

} // namespace testutils
